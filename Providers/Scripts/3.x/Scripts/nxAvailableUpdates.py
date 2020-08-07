#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================

import subprocess
import sys
import imp
import re
import copy
import fnmatch
import time
import os

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
helperlib = imp.load_source('helperlib', '../helperlib.py')
LG = nxDSCLog.DSCLog


# [ClassVersion("1.0.0"),FriendlyName("nxAvailableUpdates"),SupportsInventory()]
# class MSFT_nxAvailableUpdatesResource : OMI_BaseResource
# {
#   [Key, InventoryFilter] string Name;
#   [read] string BuildDate;
#   [read] string Repository;
#   [read] string Version;
#   [read] string Architecture;

# };

def Inventory_Marshall(Name):
    retval, pkgs = GetUpdates(Name)
    for p in pkgs:
        p['Name'] = protocol.MI_String(p['Name'])
        p['BuildDate'] = protocol.MI_String(p['BuildDate'])
        p['Repository'] = protocol.MI_String(p['Repository'])
        p['Version'] = protocol.MI_String(p['Version'])
        p['Architecture'] = protocol.MI_String(p['Architecture'])
    Inventory = protocol.MI_InstanceA(pkgs)
    retd = {}
    retd["__Inventory"] = Inventory
    return retval, retd


def GetUpdates(Name):
    d = {}
    LG().Log('DEBUG', "Starting to check Available Updates")
    mgr = GetPackageManager()
    if mgr == None:
        LG().Log('ERROR', "Unable to find one of 'apt', 'yum', or 'zypper'.")
        return -1, d
    if mgr == 'apt':
        d = GetAptUpdates(Name)
    elif mgr == 'yum':
        d = GetYumUpdates(Name)
    elif mgr == 'zypper':
        d = GetZypperUpdates(Name)
    LG().Log('DEBUG', "Completed checking Available Updates")
    return 0, d


def GetAptUpdates(Name):
    # Format:
    # Inst python3.5 (3.5.0-3 Ubuntu:15.10/wily [amd64])
    # Inst sosreport [3.2-2ubuntu1] (3.2-2ubuntu1.1 Ubuntu:15.10/wily-updates [amd64])

    updates_list = []
    d = {}
    # Refresh the repo
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        cmd = 'sudo /opt/microsoft/omsconfig/Scripts/OMSAptUpdates.sh'
    else:
        cmd = 'apt-get -q update'
    code, out = RunGetOutput(cmd, False, False)
    cmd = 'LANG=en_US.UTF8 apt-get -s dist-upgrade | grep "^Inst"'
    LG().Log('DEBUG', "Retrieving update package list using cmd:" + cmd)
    code, out = RunGetOutput(cmd, False, False)
    if len(out) < 2:
        return updates_list
    srch_txt = r'Inst[ ](.*?)[ ].*?[(](.*?)[ ](.*?)[ ]\[(.*?)\]'
    srch = re.compile(srch_txt, re.M | re.S)
    pkg_list = srch.findall(out)
    for pkg in pkg_list:
        d['BuildDate'] = ''
        d['Name'] = pkg[0]
        if len(Name) and not fnmatch.fnmatch(d['Name'], Name):
            continue
        d['Architecture'] = pkg[3]
        d['Version'] = pkg[1]
        d['Repository'] = pkg[2]
        updates_list.append(copy.deepcopy(d))
    LG().Log('DEBUG', "Number of packages being written to the XML: " + str(len(updates_list)))
    return updates_list


def GetYumUpdates(Name):
    # Format:
    # Name        : zsh
    # Arch        : x86_64
    # Version     : 5.0.2
    # Release     : 14.el7
    # Size        : 2.4 M
    # Repo        : base/7/x86_64
    # Summary     : Powerful interactive shell
    # URL         : http://zsh.sourceforge.net/
    # License     : MIT
    # Epoch and Buildtime are not available for 'yum info available'.
    # If 'repoquery is installed Epoch and Buildtime will be used.
    # Epoch is added to the front of the 'Version', and sanitized afterward.

    updates_list = []
    # No need to refresh the repo - 'check-update' will do this.

    if os.path.exists('/usr/bin/repoquery'):
        srch_str = r'Name.*?: (.*?)\n.*?Arch.*?: (.*?)\n.*?Version.*?: (.*?)\n.*?Release.*?: (.*?)\n.*?Repo.*?: (.*?)\n.*?Buildtime.*?: (.*?)\n'
    else:
        srch_str = r'Name.*?: (.*?)\n.*?Arch.*?: (.*?)\n.*?Version.*?: (.*?)\n.*?Release.*?: (.*?)\n.*?Repo.*?: (.*?)\n'

    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        yum_list = 'sudo /opt/microsoft/omsconfig/Scripts/OMSYumUpdates.sh '
        yum_info = yum_list
    else:
        yum_list = 'yum check-update '
        if os.path.exists('/usr/bin/repoquery'):
            yum_info = 'repoquery --queryformat "Name : %{NAME}\nArch : %{ARCH}\nVersion :  %{EPOCH}:%{VERSION}\nRelease : %{RELEASE}\nRepo : %{REPO}\nBuildtime : %{BUILDTIME}" '
        else:
            yum_info = 'yum info available '
    cmd = "LANG=en_US.UTF8 " + yum_list
    start_time = time.time()
    LG().Log('DEBUG', "Retrieving update package list using cmd: " + cmd)
    retcode, pkg_list = RunGetOutput(cmd, False, False)
    LG().Log('DEBUG', "Cmd execution time: " + str((time.time() - start_time) / 60))
    #LG().Log('DEBUG', "Cmd output for update list : " + pkg_list)    

    # Sample output from OMSYumUpdates.sh
    #   ca-certificates.noarch
    #   glibc.x86_64
    #   glibc-common.x86_64
    #   glibc-devel.x86_64
    #   glibc-headers.x86_64
    if validate_yum_pkg_list_output(pkg_list, retcode):
        # Remove the chatter.  Yum puts a blank line before the list.
        if pkg_list.find('\n\n') > -1:
            pkg_list = pkg_list[pkg_list.find('\n\n') + 2:]
        LG().Log('DEBUG', "Number of packages to be updated: " + str(len(pkg_list.splitlines())))
        srch = re.compile(srch_str, re.M | re.S)

        param_list = ""
        for pkg in pkg_list.splitlines():
            if pkg == "Obsoleting":
                LG().Log('DEBUG', "List including obsolete packages: " + pkg_list)
                break
            param_list = param_list + " " + pkg

        cmd = "LANG=en_US.UTF8 " + yum_info + param_list
        LG().Log('DEBUG', "Retrieving individual package information from Yum using cmd: " + cmd)
        start_time = time.time()
        code, out = RunGetOutput(cmd, False, False)
        LG().Log('DEBUG', "Cmd execution time: " + str((time.time() - start_time) / 60))
        #LG().Log('DEBUG', "Cmd output is : " + out)
        updates_list = []
        if len(out) < 1 or ':' not in out:
            LG().Log('DEBUG', "Failed retrieving individual package info. Output is too small : " + out)
            return updates_list
        yum_pkg_info_list = srch.finditer(out)
        updates_list = get_yum_updates_list(yum_pkg_info_list, Name)
    LG().Log('DEBUG', "Number of packages being written to the XML: " + str(len(updates_list)))
    return updates_list


def get_yum_updates_list(yum_pkg_info_list, Name):
    d = {}
    updates_list = []
    for yum_pkg_info in yum_pkg_info_list:
        d['Name'] = yum_pkg_info.group(1)
        if len(Name) and not fnmatch.fnmatch(d['Name'], Name):
            continue
        d['Architecture'] = yum_pkg_info.group(2)
        d['Version'] = yum_pkg_info.group(3) + '-' + yum_pkg_info.group(4)
        if ':' not in d['Version']:  # Add a '0:' for epoch.
            d['Version'] = '0:' + d['Version']
        d['Version'] = d['Version'].replace('(none)', '0')  # Handle the Epoch '(none)'.
        d['Repository'] = yum_pkg_info.group(5)
        d['BuildDate'] = ''
        if len(yum_pkg_info.groups()) == 6:  # Buildtime
            d['BuildDate'] = time.asctime(time.gmtime(int(yum_pkg_info.group(6))))
        updates_list.append(copy.deepcopy(d))
    return updates_list


def validate_yum_pkg_list_output(pkg_list, retcode):
    repo_urls_unreachable_error = "Could not contact any CDS load balancers"
    repo_urls_unconfigured_error = "Cannot find a valid baseurl for repo"
    yum_packageupdates_available_exitcode = 100
    yum_no_applicable_packages_exitcode = 0

    if retcode == yum_packageupdates_available_exitcode:
        if len(pkg_list) < 2:
            LG().Log('INFO', "Nothing to send info on. No packages")
        else:
            return True
    elif retcode == yum_no_applicable_packages_exitcode:
        LG().Log('DEBUG', "No packages are available for update")
    else:
        LG().Log('DEBUG', "Error return code when retrieving update package list: " + str(retcode))
        LG().Log('DEBUG', "Output when retrieving update package list: " + str(pkg_list))
        if repo_urls_unreachable_error in str(pkg_list):
            LG().Log('DEBUG', "Unable to contact YUM repos" + str(pkg_list))
        if repo_urls_unconfigured_error in str(pkg_list):
            LG().Log('DEBUG', "YUM Repo urls are not configured" + str(pkg_list))
    return False


def GetZypperUpdates(Name):
    # Format:
    # Repository         | Name                       | Version | Category    | Status
    # -------------------+----------------------------+---------+-------------+-------
    # SLES11-SP3-Updates | slessp3-WALinuxAgent       | 10531   | recommended | needed
    # SLES11-SP3-Updates | slessp3-WALinuxAgent-12085 | 1       | recommended | needed

    updates_list = []
    d = {}
    pkg_list = ''
    # For omsagent the repo is refreshed in OMSZypperUpdates.sh.
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        zypper = 'sudo /opt/microsoft/omsconfig/Scripts/OMSZypperUpdates.sh'
    else:
        zypper = 'zypper -q lu'
        # Refresh the repo.
        cmd = 'zypper -qn refresh'
        LG().Log('DEBUG', "Executing cmd: " + cmd)
        code, out = RunGetOutput(cmd, False, False)
    cmd = 'LANG=en_US.UTF8 ' + zypper + ' | grep "|" | grep -vE "Status|Current Version"'
    LG().Log('DEBUG', "Retrieving update package list using cmd:" + cmd)
    code, out = RunGetOutput(cmd, False, False)
    pkg_list = out
    if len(pkg_list) < 2:
        return updates_list
    for pkg in pkg_list.splitlines():
        pkg = pkg.split('|')
        d['BuildDate'] = ''
        d['Name'] = pkg[2].strip()
        if len(Name) and not fnmatch.fnmatch(d['Name'], Name):
            continue
        d['Architecture'] = pkg[5].strip()
        d['Version'] = "0:" + pkg[4].strip()
        d['Repository'] = pkg[1].strip()
        updates_list.append(copy.deepcopy(d))
    LG().Log('DEBUG', "Number of packages being written to the XML: " + str(len(updates_list)))
    return updates_list


        
def RunGetOutput(cmd, no_output, chk_err=True):
    """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT,
    trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    """
    def check_output(no_output, *popenargs, **kwargs):
        """
        Backport from subprocess module from python 2.7
        """
        if 'stdout' in kwargs:
            raise ValueError(
                'stdout argument not allowed, it will be overridden.')
        if no_output:
            out_file = None
        else:
            out_file = subprocess.PIPE
        process = subprocess.Popen(stdout=out_file, *popenargs, **kwargs)
        output, unused_err = process.communicate()
        retcode = process.poll()
        if retcode:
            cmd = kwargs.get("args")
            if cmd is None:
                cmd = popenargs[0]
            raise subprocess.CalledProcessError(retcode, cmd, output=output)
        return output

    # Exception classes used by this module.
    class CalledProcessError(Exception):

        def __init__(self, returncode, cmd, output=None):
            self.returncode = returncode
            self.cmd = cmd
            self.output = output

        def __str__(self):
            return "Command '%s' returned non-zero exit status %d" \
                   % (self.cmd, self.returncode)

    subprocess.check_output = check_output
    subprocess.CalledProcessError = CalledProcessError
    output=b''
    try:
        output = subprocess.check_output(
            no_output, cmd, stderr=subprocess.STDOUT, shell=True)
        if output is None:
            output=b''
    except subprocess.CalledProcessError as e:
        if chk_err:
            print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stderr)
            LG().Log(
                'ERROR', 'CalledProcessError.  Error Code is '
                + str(e.returncode))
            print(
                'CalledProcessError.  Command string was '
                + e.cmd, file=sys.stderr)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command string was ' + e.cmd)
            print('CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('ascii','ignore'), file=sys.stderr)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command result was '
                + (e.output[:-1]).decode('ascii','ignore'))
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, e.output.decode('ascii','ignore')

    if no_output:
        return 0, None
    else:
        return 0, output.decode('ascii','ignore')

def GetPackageManager():
    ret = None
    # choose default - almost surely one will match.
    for b in ('apt-get', 'zypper', 'yum'):
        code, out = RunGetOutput('which ' + b, False, False)
        if code is 0:
            ret = b
            if ret == 'apt-get':
                ret = 'apt'
            break
    return ret

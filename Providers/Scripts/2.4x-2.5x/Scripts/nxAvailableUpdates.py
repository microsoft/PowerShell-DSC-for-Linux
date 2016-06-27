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
    if Name is not None and len(Name) > 0:
        Name = Name.encode('ascii','ignore')
    retval, pkgs = GetUpdates(Name)
    for p in pkgs:
        p['Name'] = protocol.MI_String(p['Name'])
        p['BuildDate'] = protocol.MI_String('BuildDate')
        p['Repository'] = protocol.MI_String(p['Repository'])
        p['Version'] = protocol.MI_String(p['Version'])
        p['Architecture'] = protocol.MI_String(p['Architecture'])
    Inventory=protocol.MI_InstanceA(pkgs)
    retd = {}
    retd["__Inventory"] = Inventory
    return retval, retd

def GetUpdates(Name):
    d={}
    mgr = GetPackageManager()
    if mgr == None:
        Print("ERROR: Unable to find one of 'apt', 'yum', or 'zypper'.")
        LG().Log('ERROR', "Unable to find one of 'apt', 'yum', or 'zypper'.")
        return -1, d
    if mgr == 'apt':
        d = GetAptUpdates(Name)
    elif mgr == 'yum':
        d = GetYumUpdates(Name)
    elif mgr == 'zypper':
        d = GetZypperUpdates(Name)
    return 0, d

def GetAptUpdates(Name):
    # Format:
    # Inst python3.5 (3.5.0-3 Ubuntu:15.10/wily [amd64])
    # Inst sosreport [3.2-2ubuntu1] (3.2-2ubuntu1.1 Ubuntu:15.10/wily-updates [amd64])

    updates_list = []
    d={}
    # Refresh the repo
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        cmd = 'sudo /opt/microsoft/omsconfig/Scripts/OMSAptUpdates.sh'
    else:
        cmd = 'apt-get -q update'
    code, out = RunGetOutput(cmd, False, False)
    cmd = 'LANG=en_US.UTF8 apt-get -s dist-upgrade | grep "^Inst"'
    code, out = RunGetOutput(cmd, False, False)
    if len(out) < 2 :
        return updates_list
    srch_txt=r'Inst[ ](.*?)[ ].*?[(](.*?)[ ](.*?)[ ]\[(.*?)\]'
    srch=re.compile(srch_txt, re.M|re.S)
    pkg_list=srch.findall(out)
    for pkg in pkg_list:
        d['BuildDate'] = ''
        d['Name'] = pkg[0]
        if len(Name) and not fnmatch.fnmatch(d['Name'], Name):
            continue
        d['Architecture'] = pkg[3]
        d['Version'] = pkg[1]
        d['Repository'] = pkg[2]
        updates_list.append(copy.deepcopy(d))
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

    srch_str=r'Name.*?: (.*?)\n.*?Arch.*?: (.*?)\n.*?Epoch.*?: (.*?)\n.*?Version.*?: (.*?)\n.*?Release.*?: (.*?)\n.*?Repo.*?: (.*?)\n'
    srch = re.compile(srch_str, re.M | re.S)
    updates_list = []
    d={}
    # No need to refresh the repo - 'check-update' will do this.
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        yum_list = 'sudo /opt/microsoft/omsconfig/Scripts/OMSYumUpdates.sh '
        yum_info = yum_list
    else:
        yum_list = 'yum -q check-update '
        yum_info = 'yum info available '
    cmd = "LANG=en_US.UTF8 " + yum_list + "| awk '{print $1}'"
    code, pkg_list = RunGetOutput(cmd, False, False)
    if len(pkg_list) < 2 :
        LG().Log('INFO', "Nothing to send info on. No packages")
        return updates_list
    LG().Log('DEBUG', "Number of packages: " + len(pkg_list.splitlines()))
    for pkg in pkg_list.splitlines():
        if len(pkg) < 2 :
            LG().Log('VERBOSE', "Avoiding very small entries.")
            continue
        cmd = "LANG=en_US.UTF8 " + yum_info + pkg
        code, out = RunGetOutput(cmd, False, False)
        if len(out) < 1 or ':' not in out:
            LG().Log('DEBUG', "Checking the output in 'out': " + out)
            continue
        m = srch.search(out)
        if m == None:
            continue
            
        epoch =  0
        if m.group(3) == "(none)":
            epoch =  0
        else:
            epoch =  m.group(3)

        d['BuildDate'] = ''
        d['Name'] = m.group(1)
        if len(Name) and not fnmatch.fnmatch(d['Name'], Name):
            continue
        d['Architecture'] = m.group(2)
        d['Version'] = epoch + ":" + m.group(4) + m.group(5)
        d['Repository'] = m.group(6)
        updates_list.append(copy.deepcopy(d))
    LG().Log('DEBUG', "Number of packages being written to the XML: " + len(updates_list))
    return updates_list

def GetZypperUpdates(Name):
    # Format:
    # Repository         | Name                       | Version | Category    | Status
    # -------------------+----------------------------+---------+-------------+-------
    # SLES11-SP3-Updates | slessp3-WALinuxAgent       | 10531   | recommended | needed
    # SLES11-SP3-Updates | slessp3-WALinuxAgent-12085 | 1       | recommended | needed

    updates_list = []
    d={}
    pkg_list = ''
    # For omsagent the repo is refreshed in OMSZypperUpdates.sh.
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        zypper = 'sudo /opt/microsoft/omsconfig/Scripts/OMSZypperUpdates.sh'
    else:
        zypper = 'zypper -q'
        # Refresh the repo.
        cmd = 'zypper -qn refresh'
        code, out = RunGetOutput(cmd, False, False)
    cmd = 'LANG=en_US.UTF8 ' + zypper + ' lu | grep "|" | grep -vE "Status|Current Version"'
    code, out = RunGetOutput(cmd, False, False)
    pkg_list += out
    cmd = 'LANG=en_US.UTF8 ' + zypper + ' lp | grep "|" | grep -vE "Status|Current Version"'
    code, out = RunGetOutput(cmd, False, False)
    pkg_list += out
    if len(pkg_list) < 2:
        return updates_list
    for pkg in pkg_list.splitlines():
        pkg=pkg.split('|')
        d['BuildDate'] = ''
        d['Name'] = pkg[1]
        if len(Name) and not fnmatch.fnmatch(d['Name'], Name):
            continue
        d['Architecture'] = ''
        d['Version'] = "0:" + pkg[2]
        d['Repository'] = pkg[0]
        updates_list.append(copy.deepcopy(d))
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
    try:
        output = subprocess.check_output(
            no_output, cmd, stderr=subprocess.STDOUT, shell=True)
    except subprocess.CalledProcessError, e:
        if chk_err:
            Print("CalledProcessError.  Error Code is " + str(e.returncode), file=sys.stdout)
            Print("CalledProcessError.  Command string was " + e.cmd, file=sys.stdout)
            Print("CalledProcessError.  Command result was " + (e.output[:-1]).decode('utf8','ignore').encode("ascii", "ignore"), file=sys.stdout)
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, e.output.decode('utf8','ignore').encode('ascii', 'ignore')
    if no_output:
        return 0, None
    else:
        return 0, output.decode('utf8','ignore').encode('ascii', 'ignore')


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

def Print(s, file=sys.stdout):
    file.write(s + '\n')


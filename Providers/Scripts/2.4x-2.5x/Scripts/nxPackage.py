#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================
import subprocess
import os
import sys
import time
import imp
import urllib2
import threading
import re
apt = None
rpm = None
try:
    import apt
except:
    pass
if apt is None:
    try:
        import rpm
    except:
        pass
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

#   [write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
#   [write,ValueMap{"Yum", "Apt", "Zypper"},Values{"Yum", "Apt", "Zypper"}] string PackageManager;
#   [Key] string Name;
#   [write] string FilePath;
#   [write] Boolean PackageGroup;
#   [write] string Arguments;
#   [write] uint32 ReturnCode;
#   [read] string PackageDescription;
#   [read] string Publisher;
#   [read] string InstalledOn;
#   [read] uint32 Size;
#   [read] string Version;
#   [read] boolean Installed;

cache_file_dir = '/var/opt/microsoft/dsc/cache/nxPackage'
global show_mof
show_mof = False


def init_vars(Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    if Ensure is not None and Ensure != '':
        Ensure = Ensure.encode('ascii', 'ignore').lower()
    else:
        Ensure = 'present'
    if PackageManager is not None:
        PackageManager = PackageManager.encode('ascii', 'ignore').lower()
    else:
        PackageManager = ''
    if Name is not None:
        Name = Name.encode('ascii', 'ignore')
    else:
        Name = ''
    if FilePath is not None:
        FilePath = FilePath.encode('ascii', 'ignore')
    else:
        FilePath = ''
    if PackageGroup is None:
        PackageGroup = False
    PackageGroup = ( PackageGroup == True )
    if Arguments is not None:
        Arguments = Arguments.encode('ascii', 'ignore')
    else:
        Arguments = ''
    if ReturnCode is None:
        ReturnCode = 0
    return Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode


def Set_Marshall(Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    (Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode) = init_vars(
        Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode)
    retval = Set(Ensure, PackageManager, Name,
                 FilePath, PackageGroup, Arguments, ReturnCode)
    sys.stdin.flush()
    sys.stderr.flush()
    sys.stdout.flush()
    return retval


def Test_Marshall(Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    (Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode) = init_vars(
        Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode)
    retval = Test(Ensure, PackageManager, Name,
                  FilePath, PackageGroup, Arguments, ReturnCode)
    sys.stdin.flush()
    sys.stderr.flush()
    sys.stdout.flush()
    return retval


def Get_Marshall(Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    arg_names = list(locals().keys())
    (Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode) = init_vars(
        Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode)
    retval = 0
    retval, PackageManager, PackageDescription, Publisher, InstalledOn, Size, Version, Installed = Get(
        Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode)
    sys.stdin.flush()
    sys.stderr.flush()
    sys.stdout.flush()
    Ensure = protocol.MI_String(Ensure)
    PackageManager = protocol.MI_String(PackageManager)
    Name = protocol.MI_String(Name)
    FilePath = protocol.MI_String(FilePath)
    PackageGroup = protocol.MI_Boolean(PackageGroup)
    Arguments = protocol.MI_String(Arguments)
    ReturnCode = protocol.MI_Uint32(ReturnCode)
    PackageDescription = protocol.MI_String(PackageDescription)
    Publisher = protocol.MI_String(Publisher)
    InstalledOn = protocol.MI_String(InstalledOn)
    Size = protocol.MI_Uint32(int(Size))
    Version = protocol.MI_String(Version)
    Installed = protocol.MI_Boolean(Installed)
    arg_names.append('PackageDescription')
    arg_names.append('Publisher')
    arg_names.append('InstalledOn')
    arg_names.append('Size')
    arg_names.append('Version')
    arg_names.append('Installed')

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


#
# Begin user defined DSC functions
#
def GetPackageSystem():
    ret = None
    for b in ('dpkg', 'rpm'):
        code, out = RunGetOutput('which ' + b, False, False)
        if code is 0:
            ret = b
            break
    return ret


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


def ParseArguments(a):
    program_arg = ''
    cmd_arg = ''
    if len(a) > 1:
        if '|' in a:
            program_arg, cmd_arg = a.split('|')
        else:
            program_arg = a
    return program_arg, cmd_arg


class Params:

    def __init__(self, Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):

        if not ("present" in Ensure or "absent" in Ensure):
            Print(
                'ERROR: Param Ensure must be "Present" or "Absent".', file=sys.stdout)
            LG().Log(
                'ERROR', 'ERROR: Param Ensure must be "Present" or "Absent".')
            raise Exception('BadParameter')
        if len(PackageManager) > 0:
            if not ("yum" in PackageManager or "apt" in PackageManager or "zypper" in PackageManager):
                Print(
                    'ERROR: Param PackageManager values are "Yum", "Apt", or "Zypper".', file=sys.stdout)
                LG().Log(
                    'ERROR', 'ERROR: Param PackageManager values are "Yum", "Apt", or "Zypper".')
                raise Exception('BadParameter')
        if len(Name) < 1 and len(FilePath) < 1:
            Print(
                'ERROR: Param Name or FilePath must be set.', file=sys.stdout)
            LG().Log('ERROR', 'ERROR: Param Name or FilePath must be set.')
            raise Exception('BadParameter')
        if len(Name) > 0 and len(FilePath) > 0:
            Print('Ignoring Name because FilePath is set.', file=sys.stdout)
            LG().Log('INFO', 'Ignoring Name because FilePath is set.')
        Print('PackageGroup value is ' + repr(PackageGroup), file=sys.stdout)
        LG().Log('INFO',  'PackageGroup value is ' + repr(PackageGroup))
        Print('PackageGroup type is ' +
              repr(type(PackageGroup)), file=sys.stdout)
        LG().Log('INFO', 'PackageGroup type is ' + repr(type(PackageGroup)))
        if not (True is PackageGroup or False is PackageGroup):
            Print(
                'ERROR: Param PackageGroup must be true or false.', file=sys.stdout)
            LG().Log(
                'ERROR', 'ERROR: Param PackageGroup must be true or false.')
            raise Exception('BadParameter')

        self.Ensure = Ensure
        self.PackageManager = PackageManager
        self.Name = Name
        self.FilePath = FilePath
        self.PackageGroup = PackageGroup
        self.Arguments, self.CommandArguments = ParseArguments(Arguments)
        self.ReturnCode = ReturnCode
        self.PackageDescription = ''
        self.Publisher = ''
        self.InstalledOn = ''
        self.Size = 0
        self.Version = ''
        self.Installed = ''

        self.PackageSystem = ''

        self.PackageSystem = GetPackageSystem()

        if len(self.PackageManager) < 1:
            self.PackageManager = GetPackageManager()

        if len(self.PackageManager) < 1 or len(self.PackageSystem) < 1:
            Print(
                "ERROR: Unable to locate any of 'zypper', 'yum', 'apt-get', 'rpm' or 'dpkg' .", file=sys.stdout)
            LG().Log(
                'ERROR', "ERROR: Unable to locate any of 'zypper', 'yum', 'apt-get', 'rpm' or 'dpkg' .")
            raise Exception('BadParameter')
        self.LocalPath = ''
        self.cmds = {}
        self.cmds['dpkg'] = {}
        self.cmds['rpm'] = {}
        self.cmds['apt'] = {}
        self.cmds['yum'] = {}
        self.cmds['zypper'] = {}
        self.cmds['dpkg']['present'] = 'DEBIAN_FRONTEND=noninteractive dpkg % -i '
        self.cmds['dpkg']['absent'] = 'DEBIAN_FRONTEND=noninteractive dpkg % -P '
        self.cmds['dpkg'][
            'stat'] = "dpkg-query -W -f='${Description}|${Maintainer}|'Unknown'|${Installed-Size}|${Version}|${Status}\n' "
        self.cmds['dpkg']['stat_group'] = None
        self.cmds['rpm']['present'] = 'rpm % -i '
        self.cmds['rpm']['absent'] = 'rpm % -e '
        self.cmds['rpm'][
            'stat'] = 'rpm -q --queryformat "%{SUMMARY}|%{PACKAGER}|%{INSTALLTIME}|%{SIZE}|%{VERSION}|installed\n" '
        self.cmds['rpm']['stat_group'] = None
        self.cmds['apt'][
            'present'] = 'DEBIAN_FRONTEND=noninteractive apt-get % install ^ --allow-unauthenticated --yes '
        self.cmds['apt'][
            'absent'] = 'DEBIAN_FRONTEND=noninteractive apt-get % purge ^ --allow-unauthenticated --yes '
        self.cmds['apt']['stat'] = self.cmds['dpkg']['stat']
        self.cmds['apt']['stat_group'] = None
        self.cmds['yum']['present'] = 'yum -y % install ^ '
        self.cmds['yum']['absent'] = 'yum -y % remove ^ '
        self.cmds['yum']['grouppresent'] = 'yum -y % groupinstall ^ '
        self.cmds['yum']['groupabsent'] = 'yum -y % groupremove ^ '
        self.cmds['yum'][
            'stat_group'] = 'yum grouplist '  # the group mode is implemented when using YUM only.
        self.cmds['yum']['stat'] = self.cmds['rpm']['stat']
        self.cmds['zypper']['present'] = 'zypper --non-interactive % install ^'
        self.cmds['zypper']['absent'] = 'zypper --non-interactive  % remove ^'
        self.cmds['zypper']['stat'] = self.cmds['rpm']['stat']
        self.cmds['zypper']['stat_group'] = None
        if self.PackageGroup is True:
            if self.cmds[self.PackageManager]['stat_group'] is None:
                Print('ERROR.  PackageGroup is not valid for ' +
                      self.PackageManager, file=sys.stdout)
                LG().Log(
                    'ERROR', 'ERROR.  PackageGroup is not valid for ' + self.PackageManager)
                raise Exception('BadParameter')
            if len(self.FilePath) > 0:
                Print(
                    'ERROR.  PackageGroup cannot be True if FilePath is set.', file=sys.stdout)
                LG().Log(
                    'ERROR', 'ERROR.  PackageGroup cannot be True if FilePath is set.')
                raise Exception('BadParameter')


def SetShowMof(a):
    global show_mof
    show_mof = a


def ShowMof(op, Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    if not show_mof:
        return
    mof = '\n'
    mof += op + ' nxPackage MyPackage \n'
    mof += '{\n'
    mof += '    Name = "' + Name + '"\n'
    mof += '    Ensure = "' + Ensure + '"\n'
    mof += '    PackageManager = "' + PackageManager + '"\n'
    mof += '    FilePath = "' + FilePath + '"\n'
    mof += '    PackageGroup = "' + str(PackageGroup) + '"\n'
    mof += '    Arguments = "' + Arguments + '"\n'
    mof += '    ReturnCode = ' + str(ReturnCode) + '\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    Print(mof, file=f)
    f.close()


def IsPackageInstalled(p):
    out = ''
    if p is None:
        return False, out
    if len(p.FilePath) > 0 and '://' in p.FilePath:  # its a remote - try to file get name from cache
        if ReadCacheInfo(p) is False:
            return False, out
    elif len(p.FilePath) > 0 and os.path.exists(p.FilePath) is True:  # FilePath
        if apt is not None and os.path.splitext(p.FilePath)[-1] == '.deb':
            from apt.debfile import DebPackage
            pkg = DebPackage(p.FilePath)
            p.Name = pkg.pkgname
        elif rpm is not None and os.path.splitext(p.FilePath)[-1] == '.rpm':
            F = open(p.FilePath, 'r')
            ts = rpm.TransactionSet()
            ts.setVSFlags(-1)
            try:
                pkg = ts.hdrFromFdno(F.fileno())
            except rpm.error, e:
                F.close()
                Print(repr(e))
                LG().Log('ERROR', repr(e))
                pkg = None
            F.close()
            if pkg is None:
                return False, out
            p.Name = pkg.dsOfHeader().N()
    if len(p.Name) < 1:
        return False, out

    if p.PackageGroup is True:
        if p.cmds[p.PackageManager]['stat_group'] is not None:
            cmd = p.cmds[p.PackageManager]['stat_group'] + '"' + p.Name + '"'
        else:
            Print('ERROR.  PackageGroup is not valid for ' +
                  p.PackageManager, file=sys.stdout)
            LG().Log(
                'ERROR', 'ERROR.  PackageGroup is not valid for ' + p.PackageManager)
            return False, out
    else:
        cmd = 'LANG=en_US.UTF8 ' + p.cmds[p.PackageManager]['stat'] + p.Name
    code, out = RunGetOutput(cmd, False)
    if p.PackageGroup is True:  # implemented for YUM only.
        if 'Installed' in out:
            return True, out
        else:
            return False, out
    # regular packages
    Print('check installed:' + out)
    LG().Log('INFO',  'check installed:' + out)
    if code is 0:
        if 'deinstall' in out or 'not-installed' in out:
            code = 1
    if code is not int(p.ReturnCode):
        return False, out
    return True, out


def ParseInfo(p, info):
    p.PackageDescription = ''
    p.Publisher = ''
    p.InstalledOn = ''
    p.Size = '0'
    p.Version = ''
    p.Installed = False

    if len(info) > 1:
        f = info.split('|')
        if len(f) is 6:
            p.PackageDescription = f[0]
            p.Publisher = f[1]
            p.InstalledOn = f[2]
            if not p.InstalledOn.isalnum():
                p.InstalledOn = time.gmtime(int(p.InstalledOn))
            if len(f[3]) > 0:
                p.Size = f[3]
            p.Version = f[4]
            p.Installed = ('install' in f[5])

        if len(f) is not 5:
            Print('ERROR.   ' + p.PackageManager, file=sys.stdout)
            LG().Log('ERROR', 'ERROR.   ' + p.PackageManager)


def DoEnableDisable(p):
    # if the path is set, use the path and self.PackageSystem
    cmd = ""
    if len(p.FilePath) > 1 and 'present' in p.Ensure:  # don't use the path unless installing
        if '://' in p.FilePath and p.LocalPath == '':  # its a remote file
            ret = 0
            ret = GetRemoteFile(p)
            if ret is not 0:
                p.LocalPath = ""
                raise Exception(
                    'Unable to retrieve remote resource ' + p.FilePath + ' Error is ' + str(ret))
            else:
                p.FilePath = p.LocalPath

        if not os.path.isfile(p.FilePath):
            Print('ERROR.   File ' + p.FilePath +
                  ' not found.', file=sys.stdout)
            LG().Log('ERROR', 'ERROR.   File ' + p.FilePath + ' not found.')
            return False, ""
        cmd = p.cmds[p.PackageSystem][p.Ensure] + ' ' + p.FilePath
        cmd = cmd.replace('%', p.Arguments)
    elif p.PackageGroup is True:
        if p.cmds[p.PackageManager].has_key('group' + p.Ensure):
            cmd = p.cmds[p.PackageManager][
                'group' + p.Ensure] + '"' + p.Name + '"'
        else:
            Print('Error: Group mode not implemented for ' +
                  p.PackageManager, file=sys.stdout)
            LG().Log(
                'ERROR', 'Error: Group mode not implemented for ' + p.PackageManager)
            return False, 'Error: Group mode not implemented for ' + p.PackageManager
    else:
        cmd = 'LANG=en_US.UTF8 ' + p.cmds[p.PackageManager][p.Ensure] + ' ' + p.Name
    cmd = cmd.replace('%', p.Arguments)
    cmd = cmd.replace('^', p.CommandArguments)
    code, out = RunGetOutput(cmd, False)
    if len(p.LocalPath) > 1:  # create cache entry and remove the tmp file
        WriteCacheInfo(p)
        RemoveFile(p.LocalPath)
    if p.PackageManager == 'yum' and ( 'No Match for argument: ' + p.Name in out or 'Nothing to do' in out ): # yum returns 0 on unknown package
        return False, out
    if p.PackageManager == 'zypper' and "package '" + p.Name + "' not found" in out: # zypper returns 0 on unknown package
        return False, out
    if code is not int(p.ReturnCode):
        return False, out
    return True, out


def WriteCacheInfo(p):
    if not os.path.isdir(cache_file_dir):
        if MakeDirs(cache_file_dir) is not None:
            return False
    if len(p.LocalPath) < 1:
        return False
    if apt is not None and os.path.splitext(p.LocalPath)[-1] == '.deb':
        from apt.debfile import DebPackage
        try:
            pkg = DebPackage(p.LocalPath)
        except:
            Print("Exception opening file " + p.LocalPath, file=sys.stderr)
            LG().Log('ERROR',  "Exception opening file " + p.LocalPath)
            return False
        p.Name = pkg.pkgname
    elif rpm is not None and os.path.splitext(p.LocalPath)[-1] == '.rpm':
        F, error = opened_w_error(p.LocalPath, 'r')
        if error:
            Print("Exception opening file " + p.LocalPath, file=sys.stderr)
            LG().Log('ERROR',  "Exception opening file " + p.LocalPath)
            return False
        ts = rpm.TransactionSet()
        ts.setVSFlags(-1)
        try:
            pkg = ts.hdrFromFdno(F.fileno())
        except rpm.error, e:
            Print(repr(e))
            LG().Log('ERROR',  repr(e))
            pkg = None
            F.close()
        if pkg is None:
            return False
        p.Name = pkg.dsOfHeader().N()
    if len(p.Name) < 1:
        return False
    cache_file_path = cache_file_dir + '/' + os.path.basename(p.LocalPath)
    F, error = opened_w_error(cache_file_path, 'w+')
    if error:
        Print("Exception creating cache file " + cache_file_path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR',  "Exception creating cache file " + cache_file_path +
                 " Error: " + str(error))
        return False
    F.write(p.Name + '\n')
    F.close()
    return True


def ReadCacheInfo(p):
    cache_file_path = cache_file_dir + '/' + os.path.basename(p.FilePath)
    if not os.path.isfile(cache_file_path):
        return False
    F, error = opened_w_error(cache_file_path, 'r')
    if error:
        Print("Exception opening cache file " + cache_file_path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR',  "Exception creating cache file " + cache_file_path +
                 " Error: " + str(error))
        return False
    t = F.read()
    F.close()
    if len(t) < 2:
        return False
    p.Name = t.strip()
    return True


def Set(Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    ShowMof('SET', Ensure, PackageManager, Name,
            FilePath, PackageGroup, Arguments, ReturnCode)
    try:
        p = Params(Ensure, PackageManager, Name,
                   FilePath, PackageGroup, Arguments, ReturnCode)
    except Exception, e:
        Print('ERROR - Unable to initialize nxPackageProvider.  ' +
              str(e), file=sys.stdout)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxPackageProvider. ' + str(e))
        return [-1]
    installed, out = IsPackageInstalled(p)
    if (installed and Ensure == 'present') or (not installed and Ensure == 'absent'):  # Nothing to do
        return [0]

    result, out = DoEnableDisable(p)
    if result is False:
        op = ''
        if Ensure == 'present':
            op = 'Install'
        else:
            op = 'Un-install'
        Print('Failed to ' + op + ' ' + p.Name +
              ' output for command was: ' + out)
        LG().Log('ERROR', 'Failed to ' + op + ' ' +
                 p.Name + ' output for command was: ' + out)
        return [-1]
    return [0]


def Test(Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    ShowMof('TEST', Ensure, PackageManager, Name,
            FilePath, PackageGroup, Arguments, ReturnCode)
    try:
        p = Params(Ensure, PackageManager, Name,
                   FilePath, PackageGroup, Arguments, ReturnCode)
    except Exception, e:
        Print('ERROR - Unable to initialize nxPackageProvider.  ' +
              str(e), file=sys.stdout)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxPackageProvider. ' + str(e))
        return [-1]
    installed, out = IsPackageInstalled(p)
    if (installed and Ensure == 'present') or (not installed and Ensure == 'absent'):
        return [0]
    return [-1]


def Get(Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments, ReturnCode):
    retval = -1
    installed = False
    ShowMof('GET', Ensure, PackageManager, Name,
            FilePath, PackageGroup, Arguments, ReturnCode)
    try:
        p = Params(Ensure, PackageManager, Name,
                   FilePath, PackageGroup, Arguments, ReturnCode)
    except Exception, e:
        Print('ERROR - Unable to initialize nxPackageProvider.  ' +
              str(e), file=sys.stdout)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxPackageProvider. ' + str(e))
        return [retval, p.PackageDescription, p.Publisher, p.InstalledOn, p.Size, p.Version, installed]
    installed, out = IsPackageInstalled(p)
    ParseInfo(p, out)
    return [0, p.PackageManager, p.PackageDescription, p.Publisher, p.InstalledOn, p.Size, p.Version, installed]


def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except IOError, err:
        return None, err
    return f, None


def RunGetOutput(cmd, no_output, chk_err=True):
    """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT, trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    Kill inactivite subprocess and children if 6 second interval is exceeded.
    """
    class KillInactiveSubprocesses(object):
        """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT, trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    Kill inactivite subprocess and children if 6 second interval is exceeded.
        """
        def __init__(self):
            self.t = None
    
        def start(self):
            self.shutdown = False
            self.t = threading.Thread(target = self.monitor)
            self.t.setDaemon(True)
            self.pid=os.getpid()
            self.pid_path = '/proc/'+str(self.pid)+'/task/'+str(self.pid)+'/'
            self.status={}
            self.t.start()
            
        def monitor(self):
            time.sleep(1)
            same_state=0
            while not self.shutdown:
                if not os.path.exists(self.pid_path):
                    return
                children=self.get_children()
                LG().Log('INFO', 'Children:'+str(children))
                if children == None or len(children) == 0 :
                    return
                running = False
                cmd='timeout 2s strace'
                for c in children:
                    cmd+=' -p '+c
                    pargs=[cmd]
                    kwargs={'stderr':subprocess.STDOUT,'shell':True}
                process = subprocess.Popen(stdout=subprocess.PIPE, *pargs, **kwargs)
                output, unused_err = process.communicate()
                process.poll()                
                self.status[same_state]=output
                LG().Log('INFO', '\n'+cmd+' is '+output.decode('utf8','ignore').encode('ascii', 'ignore')+'\n')
                if same_state < 1:
                    running=True
                else:
                    s=same_state
                    while s > 0:
                        if self.status[s] != self.status[s-1]:
                            running=True
                            break
                        s-=1
                if not running and same_state > 1:
                    self.kill_subtree(children)
                    self.shutdown = True
                if not self.shutdown:
                    time.sleep(1)
                same_state+=1
            return
            
        def get_children(self):
            """
            If the subprocess is done, there will be nothing in list.
            """
            if not os.path.exists(self.pid_path):
                return None
            pids={}
            pid=str(self.pid)
            status_srch_parent=r'(?:.*?PPid:\t)([0-9]+)'
            srch=re.compile(status_srch_parent,re.S|re.M)
            for top, dirs, files in os.walk('/proc'):
                for d in dirs:
                    if d.isdigit() and int(d)>int(pid):
                      pids[d]=None
            for d in pids.keys():
                path='/proc/'+d+'/status'
                if not os.path.exists(path):
                    continue
                status=open(path).read()
                pids[d]=srch.search(status).group(1)
            children=[pid]
            count = 0
            while count < len(children):
                for p in pids.keys():
                    if pids[p] in children and p not in children:
                        children.append(p)
                count+=1
            children.remove(pid)
            children.sort(reverse=True)
            return children

        def kill_subtree(self,kill_list):
            """
            If the subprocess is done, there will be nothing to kill.
            """
            if not os.path.exists(self.pid_path):
                return
            for i in range(len(kill_list)):
                try:
                    p=kill_list.pop(0)
                    Print('ERROR: Inactivity period exceeded.  Killing '+str(p), file=sys.stdout)
                    LG().Log('ERROR', 'ERROR: Inactivity period exceeded.  Killing '+str(p))
                    os.kill(int(p),9)
                    Print('INFO', 'Killed '+str(p), file=sys.stdout)
                    LG().Log('INFO', 'Killed '+str(p))
                except Exception, e:
                    Print('Error killing '+str(p)+repr(e), file=sys.stdout) 
                    LG().Log('ERROR', 'Error killing '+str(p)+repr(e)) 
            return
    
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
            return "Command '%s' returned non-zero exit status %d" % (self.cmd, self.returncode)

    subprocess.check_output = check_output
    subprocess.CalledProcessError = CalledProcessError
    kin=KillInactiveSubprocesses()
    try:
        output = subprocess.check_output(
            no_output, cmd, stderr=subprocess.STDOUT, shell=True, preexec_fn=kin.start())
    except subprocess.CalledProcessError, e:
        if kin.t:
            kin.t.join()
        if chk_err:
            Print("CalledProcessError.  Error Code is " + str(e.returncode), file=sys.stdout)
            Print("CalledProcessError.  Command string was " + e.cmd, file=sys.stdout)
            Print("CalledProcessError.  Command result was " + (e.output[:-1]).decode('utf8','ignore').encode("ascii", "ignore"), file=sys.stdout)
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, e.output.decode('utf8','ignore').encode('ascii', 'ignore')
    if kin.t:
        kin.t.join()
    if no_output:
        return 0, None
    else:
        return 0, output.decode('utf8','ignore').encode('ascii', 'ignore')


def Print(s, file=sys.stdout):
    file.write(s + '\n')


def GetTimeFromString(s):
    if s is None or len(s) is 0:
        return None
    fmt = []
    fmt.append('%a, %d %b %Y %H:%M:%S %Z')
    st = None
    for f in fmt:
        try:
            st = time.strptime(s, f)
        except ValueError:
            continue
    return st


def RemoveFile(path):
    error = None
    try:
        os.remove(path)
    except OSError, error:
        Print("Exception removing file" + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception removing file" + path + " Error: " + str(error))
    except IOError, error:
        Print("Exception removing file" + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception removing file" + path + " Error: " + str(error))
    return error


def LStatFile(path):
    """
    LStat the file.  Do not follow the symlink.
    """
    d = None
    error = None
    try:
        d = os.lstat(path)
    except OSError, error:
        Print("Exception lstating file " + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception lstating file " + path + " Error: " + str(error))
    except IOError, error:
        Print("Exception lstating file " + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception lstating file " + path + " Error: " + str(error))
    return d


def MakeDirs(path):
    error = None
    try:
        os.makedirs(path)
    except OSError, error:
        Print("Exception making dir" + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR',  "Exception making dir" + path + " Error: " + str(error))
    except IOError, error:
        Print("Exception making dir" + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR',  "Exception making dir" + path + " Error: " + str(error))
    return error


def GetRemoteFile(p):
    req = urllib2.Request(p.FilePath)
    try:
        resp = urllib2.urlopen(req)
    except urllib2.URLError, e:
        Print(repr(e))
        LG().Log('ERROR',  repr(e))
        return 1
    p.LocalPath = '/tmp/' + os.path.basename(p.FilePath)
    h = resp.info()
    lm = h.getheader('last-modified')
    lm_mtime = GetTimeFromString(lm)
    dst_mtime = None
    dst_st = None
    data = None
    if os.path.exists(p.LocalPath):
        dst_st = LStatFile(p.LocalPath)
    if dst_st is not None:
        dst_mtime = time.gmtime(dst_st.st_mtime)
    if lm_mtime is not None and dst_mtime is not None and dst_mtime >= lm_mtime:
        data = '' # skip download, the file is the same
    else:
        data='keep going'
        try:
            F = open(p.LocalPath, 'wb+')
            while data:
                data = resp.read(1048576)
                if data is not None and len(data) > 0:
                    F.write(data)
            F.close()
        except  Exception, e:
            Print(repr(e))
            LG().Log('ERROR', repr(e))
            F.close()
            os.unlink(p.LocalPath)
            return 1
    return 0

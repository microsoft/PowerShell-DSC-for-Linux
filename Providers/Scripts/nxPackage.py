#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

from __future__ import print_function
from __future__ import with_statement
from contextlib import contextmanager

import subprocess
import platform
import os
import sys
import time
import codecs
import re

def Set_Marshall(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed):
    Ensure = Ensure.decode('utf-8')
    PackageManager = PackageManager.decode('utf-8')
    Name = Name.decode('utf-8')
    Path = Path.decode('utf-8')
    PackageGroup = PackageGroup.decode('utf-8')
    Arguments = Arguments.decode('utf-8')
    RepoUpdate = RepoUpdate.decode('utf-8')
    ReturnCode = ReturnCode.decode('utf-8')
    LogPath = LogPath.decode('utf-8')
    PackageDescription = PackageDescription.decode('utf-8')
    Publisher = Publisher.decode('utf-8')
    InstalledOn = InstalledOn.decode('utf-8')
    Size = Size.decode('utf-8')
    Version = Version.decode('utf-8')
    Installed = Installed.decode('utf-8')

    retval = Set(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed)
    return retval

def Test_Marshall(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed):
    Ensure = Ensure.decode('utf-8')
    PackageManager = PackageManager.decode('utf-8')
    Name = Name.decode('utf-8')
    Path = Path.decode('utf-8')
    PackageGroup = PackageGroup.decode('utf-8')
    Arguments = Arguments.decode('utf-8')
    RepoUpdate = RepoUpdate.decode('utf-8')
    ReturnCode = ReturnCode.decode('utf-8')
    LogPath = LogPath.decode('utf-8')
    PackageDescription = PackageDescription.decode('utf-8')
    Publisher = Publisher.decode('utf-8')
    InstalledOn = InstalledOn.decode('utf-8')
    Size = Size.decode('utf-8')
    Version = Version.decode('utf-8')
    Installed = Installed.decode('utf-8')

    retval = Test(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed)
    return retval

def Get_Marshall(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed):
    Ensure = Ensure.decode('utf-8')
    PackageManager = PackageManager.decode('utf-8')
    Name = Name.decode('utf-8')
    Path = Path.decode('utf-8')
    PackageGroup = PackageGroup.decode('utf-8')
    Arguments = Arguments.decode('utf-8')
    RepoUpdate = RepoUpdate.decode('utf-8')
    ReturnCode = ReturnCode.decode('utf-8')
    LogPath = LogPath.decode('utf-8')
    PackageDescription = PackageDescription.decode('utf-8')
    Publisher = Publisher.decode('utf-8')
    InstalledOn = InstalledOn.decode('utf-8')
    Size = Size.decode('utf-8')
    Version = Version.decode('utf-8')
    Installed = Installed.decode('utf-8')

    retval = 0
    retval,Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed = Get(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed)

    return [retval,Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,
            LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed]


############################################################
### Begin user defined DSC functions
############################################################
def GetPackageSystem():
    ret=None
    for b in ('rpm','dpkg'):
        code,out=RunGetOutput('which '+b,False,False)
        if code == 0:
            ret = b
            break
    return ret

def GetPackageManager():
    ret=None
    # choose default - almost surely one will match.
    for b in ('zypper','yum','apt-get'):
        code,out=RunGetOutput('which '+b,False,False)
        if code == 0:
            ret=b
            if ret == 'apt-get' :
                ret = 'apt'
            break
    return ret

def ParseArguments(a):
    program_arg=''
    cmd_arg=''
    if len(a)>1 :
        if '|' in a:
            program_arg,cmd_arg=a.split('|')
        else:
            program_arg=a
    return program_arg,cmd_arg

class Params:
    def __init__(self,Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,
     LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed):

        if not ( "Present" in Ensure or "Absent" in Ensure ):
            print('ERROR: Param Ensure must be Present or Absent.',file=sys.stderr)
            Log(LogPath,'ERROR: Param Ensure must be Present or Absent.')
            raise Exception('BadParameter')
        if len(PackageManager)>0:
            if not ( "yum" in PackageManager.lower() or  "apt" in PackageManager.lower() or "zypper" in PackageManager.lower() ) :
                print('ERROR: Param PackageManager values are Yum, Apt, or Zypper.',file=sys.stderr)
                Log(LogPath,'ERROR: Param PackageManager values are Yum, Apt, or Zypper.')
                raise Exception('BadParameter')
        if len(Name)<1 and len(Path)<1:
            print('ERROR: Param Name or Path must be set.',file=sys.stderr)
            Log(LogPath,'ERROR: Param Name or Path must be set.')
            raise Exception('BadParameter')
        if len(Name)>0 and len(Path)>0:
            print('Ignoring Name because Path is set.',file=sys.stderr)
            Log(LogPath,'Ignoring Name because Path is set.')

        if not ( "true" in PackageGroup or "false" in PackageGroup ):
            print('ERROR: Param PackageGroup must be true or false.',file=sys.stderr)
            Log(LogPath,'ERROR: Param PackageGroup must be true or false.')
            raise Exception('BadParameter')
        if not ( "true" in RepoUpdate or "false" in RepoUpdate ):
            print('ERROR: Param RepoUpdate must be true or false.',file=sys.stderr)
            Log(LogPath,'ERROR: Param RepoUpdate must be true or false.')
            raise Exception('BadParameter')
        
        self.Ensure = Ensure
        self.PackageManager = PackageManager.lower()
        self.Name = Name
        self.Path = Path
        self.PackageGroup = PackageGroup
        self.Arguments,self.CommandArguments=ParseArguments(Arguments)
        self.RepoUpdate = RepoUpdate
        self.ReturnCode = ReturnCode
        self.LogPath = LogPath
        self.PackageDescription = None
        self.Publisher = None
        self.InstalledOn = None
        self.Size = None
        self.Version = None
        self.Installed = None

        self.PackageSystem = None
        
        self.PackageSystem=GetPackageSystem()

        if len(self.PackageManager)<1:
            self.PackageManager=GetPackageManager()

        if len(self.PackageManager)<1 or len(self.PackageSystem)<1 :
            print("ERROR: Unable to locate any of 'zypper', 'yum', 'apt-get', 'rpm' or 'dpkg' .",file=sys.stderr)
            Log(LogPath,"ERROR: Unable to locate any of 'zypper', 'yum', 'apt-get', 'rpm' or 'dpkg' .")
            raise Exception('BadParameter')
            
        self.cmds={}
        self.cmds['dpkg']={}
        self.cmds['rpm']={}
        self.cmds['apt']={}
        self.cmds['yum']={}
        self.cmds['zypper']={}
        self.cmds['dpkg']['Present']='dpkg % -i '
        self.cmds['dpkg']['Absent']='dpkg % -r '
        self.cmds['dpkg']['stat']="dpkg-query -W -f='${Description}|${Maintainer}|'Unknown'|${Installed-Size}|${Version}|${Status}\n' "
        self.cmds['dpkg']['update_repo']=None
        self.cmds['dpkg']['stat_group']=None
        self.cmds['rpm']['Present']='rpm % -i '
        self.cmds['rpm']['Absent']='rpm % -e '
        self.cmds['rpm']['stat']='rpm -q --queryformat "%{SUMMARY}|%{PACKAGER}|%{INSTALLTIME}|%{SIZE}|%{VERSION}|installed\n" '
        self.cmds['rpm']['update_repo']=None
        self.cmds['rpm']['stat_group']=None
        self.cmds['apt']['Present']='apt-get % install ^ --yes '
        self.cmds['apt']['Absent']='apt-get % remove ^--yes '
        self.cmds['apt']['stat']=self.cmds['dpkg']['stat']
        self.cmds['apt']['update_repo']=None
        self.cmds['apt']['stat_group']=None
        self.cmds['yum']['Present']='yum -y % install ^ '
        self.cmds['yum']['Absent']='yum -y % remove ^ '
        self.cmds['yum']['GroupPresent']='yum -y % groupinstall ^ '
        self.cmds['yum']['GroupAbsent']='yum -y % groupremove ^ '
        self.cmds['yum']['update_repo']='yum makecache '
        self.cmds['yum']['stat_group']='yum grouplist ' # the group mode is implemented when using YUM only.  
        self.cmds['yum']['stat']=self.cmds['rpm']['stat']
        self.cmds['zypper']['Present']='zypper --non-interactive % install ^'
        self.cmds['zypper']['Absent']='zypper --non-interactive  % remove ^'
        self.cmds['zypper']['update_repo']='zypper --non-interactive --no-gpg-checks refresh'
        self.cmds['zypper']['stat']=self.cmds['rpm']['stat']
        self.cmds['zypper']['stat_group']=None
    
def IsPackageInstalled(p):
    if p==None:
        return False
    out=''
    if len(p.Path)>0:
        return False,out
    if p.PackageGroup == 'true':
        if p.cmds[p.PackageManager]['stat_group'] != None:
            cmd=p.cmds[p.PackageManager]['stat_group'] + '"' + p.Name + '"' 
        else:
            print('ERROR.  PackageGroup is not valid for '+ p.PackageManager,file=sys.stderr)
            Log(p.LogPath,'ERROR.  PackageGroup is not valid for '+ p.PackageManager)
            return False,out
    cmd=p.cmds[p.PackageManager]['stat'] + p.Name
    code,out=RunGetOutput(cmd,False)
    if p.PackageGroup == 'true': # implemented for YUM only.
        if 'Installed' in out:
            return True,out
        else : 
            return False,out
    # regular packages
    print('check installed:'+out)
    if code == 0 and 'deinstall' in out:
        code=1
    if code != int(p.ReturnCode) :
        return False,out
    return True,out

def ParseInfo(p,info):
    p.PackageDescription=''
    p.Publisher=''
    p.InstalledOn=''
    p.Size=''
    p.Version=''
    p.Installed='false'

    if len(info)>1:
        f=info.split('|')
        if len(f)==6:
            p.PackageDescription=f[0]
            p.Publisher=f[1]
            p.InstalledOn=f[2]
            if not p.InstalledOn.isalnum():
                p.InstalledOn=time.gmtime(int(p.InstalledOn))
            p.Size=f[3]
            p.Version=f[4]
            p.Installed= ( 'install' in f[5] )
            
    if len(f)!=5:
        print('ERROR.   '+ p.PackageManager,file=sys.stderr)
        Log(p.LogPath,'ERROR.   '+ p.PackageManager)

def DoEnableDisable(p):
    # if the path is set, use the path and self.PackageSystem
    cmd=""
    if len(p.Path) > 1 and 'Present' in p.Ensure : # don't use the path unless installing
        if not os.path.isfile(p.Path):
            print('ERROR.   File '+ p.Path + ' not found.',file=sys.stderr)
            Log(p.LogPath,'ERROR.   File '+ p.Path + ' not found.')
            return False,""
        cmd=p.cmds[p.PackageSystem][p.Ensure] + ' ' + p.Path
        cmd=cmd.replace('%',p.Arguments)
    elif p.PackageGroup == 'true' :
        if p.cmds[p.PackageManager].has_key('Group'+p.Ensure) :
            cmd=p.cmds[p.PackageManager]['Group'+p.Ensure] + '"' + p.Name +'"'
        else :
            print('Error: Group mode not implemented for ' + p.PackageManager,file=sys.stderr)
            Log(p.LogPath,'Error: Group mode not implemented for ' + p.PackageManager)
            return False,'Error: Group mode not implemented for ' + p.PackageManager
    else:
        cmd=p.cmds[p.PackageManager][p.Ensure] + ' ' + p.Name 
    cmd=cmd.replace('%',p.Arguments)
    cmd=cmd.replace('^',p.CommandArguments)
    code,out=RunGetOutput(cmd,False)
    
    if code != int(p.ReturnCode) :
        return False,out
    return True,out
    
def DoUpdateRepo(p):
    cmd=p.cmds[p.PackageManager]['update_repo']
    if cmd == None :
        return True,None
    code,out=RunGetOutput(cmd,False)
    if code != 0:
        return False,out
    return True,out

def Set(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed):
    try:
        p=Params(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed)
    except Exception,e:
        print('ERROR - Unable to initialize nxPackageProvider.  '+e.message,file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxPackageProvider. '+ e.message)
        return [-1]
    installed,out = IsPackageInstalled(p)
    if ( installed and Ensure == 'Present' ) or ( not installed and Ensure == 'Absent') : # Nothing to do
        return [0]
    DoUpdateRepo(p) # only updates if the flag RepoUpdate is true.
    result,out=DoEnableDisable(p)
    if result == False :
        op=''
        if Ensure == 'Present' :
            op = 'Install'
        else :
            op='Un-install'
        print('Failed to ' + op + ' ' + p.Name + ' output for command was: ' + out)
        Log(p.LogPath,'Failed to ' + op + ' ' + p.Name + ' output for command was: ' + out)
        return [-1]
    return [0]
   
def Test(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed):
    try:
        p=Params(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed)
    except Exception,e:
        print('ERROR - Unable to initialize nxPackageProvider.  '+e.message,file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxPackageProvider. '+ e.message)
        return [-1]
    installed,out = IsPackageInstalled(p)
    if ( installed and Ensure == 'Present' ) or ( not installed and Ensure == 'Absent') :
        return [0]
    return [-1]

def Get(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed):
    retval=-1
    try:
        p=Params(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed)
    except Exception,e:
        print('ERROR - Unable to initialize nxPackageProvider.  '+e.message,file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxPackageProvider. '+ e.message)
        return [-1]
    installed,out = IsPackageInstalled(p)
    ParseInfo(p,out)
    if  installed and Ensure == 'Present'  :
        retval = 0
    if not installed and Ensure == 'Absent' :
        retval =0
    if p.Installed:
        Installed='true'
    else :
        Installed='false'
        
    return [retval,p.Ensure,p.PackageManager,p.Name,p.Path,p.PackageGroup,p.RepoUpdate,p.ReturnCode,p.LogPath,p.PackageDescription,p.Publisher,p.InstalledOn,p.Size,p.Version,Installed]

@contextmanager
def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, encoding='utf-8' , mode=mode)
    except IOError, err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()

def RunGetOutput(cmd,no_output,chk_err=True):
    """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT, trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    """
    def check_output(no_output,*popenargs, **kwargs):
        r"""Backport from subprocess module from python 2.7"""
        if 'stdout' in kwargs:
            raise ValueError('stdout argument not allowed, it will be overridden.')
        if no_output:
            out_file=None
        else :
            out_file=subprocess.PIPE
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

    subprocess.check_output=check_output
    subprocess.CalledProcessError=CalledProcessError
    try:                                     
        output=subprocess.check_output(no_output,cmd,stderr=subprocess.STDOUT,shell=True)
    except subprocess.CalledProcessError,e :
        if chk_err :
            print('CalledProcessError.  Error Code is ' + str(e.returncode),file=sys.stderr  )
            print('CalledProcessError.  Command string was ' + e.cmd ,file=sys.stderr )
            print('CalledProcessError.  Command result was ' + (e.output[:-1]).decode('latin-1'),file=sys.stderr)
        if no_output:
            return e.returncode,None
        else:
            return e.returncode,e.output.decode('latin-1')
        
    if no_output:
        return 0,None
    else :
        return 0,output.decode('latin-1')


def Log(file_path,message):
    if len(file_path)<1 or len(message) < 1:
        return
    t = time.localtime()
    t = "%04u/%02u/%02u %02u:%02u:%02u " % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
    lines=re.sub(re.compile(r'^(.)',re.MULTILINE),t+r'\1',message)
    with opened_w_error(file_path,'a') as (F,error):
        if error:
            print("Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
        else:
            F.write(lines + "\n")
        

###############
# Unittest         #
###############

os.system('cd /tmp/Scripts && tar -zxvf ./unittest2-0.5.1.tar.gz ')
sys.path.append('/tmp/Scripts/unittest2-0.5.1')
import unittest2

class LinuxPackageTestCases(unittest2.TestCase):
    """
    Test cases for LinuxFile
    """
    def setUp(self):
        """
        Setup test resources
        """
        time.sleep(2)
        if os.system('which dpkg ') == 0 :
            os.system('dpkg -r nano &> /dev/null')
        else :
            os.system('rpm -e nano &> /dev/null')
        time.sleep(2)
        d=platform.dist()[0].lower()
        if 'cent' in d:
            self.package_path='/tmp/Scripts/nano-2.0.9-7.el6.x86_64.rpm'
        elif 'suse' in d:
            self.package_path='/tmp/Scripts/nano-2.3.2-2.1.2.x86_64.rpm'
        elif 'mint' in d or 'ubuntu' in d:
            self.package_path='/tmp/Scripts/nano_2.2.6-1ubuntu1_amd64.deb'
            
    def tearDown(self):
        """
        Remove test resources.
        """
        time.sleep(2)
        if os.system('which dpkg ') == 0 :
            os.system('dpkg -r nano &> /dev/null')
        else :
            os.system('rpm -e nano &> /dev/null')
        time.sleep(2)
    
    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass
    
    def testSetEnableNameDefaultProviderArguments(self):
        """
        use the appropriate argument to try-out a package
        with no installation, then test that the package is not installed.
        """
        dryrun={}
        dryrun['zypper']='--dry-run'
        dryrun['apt']='--dry-run'
        dryrun['yum']='-v' # no dry run in yum...
        dryrun['dpkg']='--dry-run'
        dryrun['rpm']='--test'
        pm=GetPackageManager()
        args=dryrun[pm]
        if pm == 'zypper':
            args='|'+args
        assert Set('Present','','nano','','false',args,'true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        
    def testSetEnablePathAndNameDefaultProvider(self):
        """
        Test that when Path and Name are set, Path is used.
        """
        assert Set('Present','','nano',self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','nano','','"+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"

    def testSetEnableNameDefaultProvider(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"

    def testSetEnableNameExplicitProvider(self):
        pm=GetPackageManager()
        assert Set('Present',pm,'nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','"+pm+"','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
 
    def testSetEnableNameBadExplicitProviderError(self):
        pm=GetPackageManager()
        for b in ('zypper','yum','apt-get'):
            if b != pm:
                break
        assert Set('Present',b,'nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[-1],"Set('Present','"+b+"','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]"

    def testSetEnableNameDefaultProviderBadReturnCodeError(self):
        assert Set('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')==[-1],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]"

    def testGetEnableNameDefaultProvider(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        print('GET:'+repr(Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','GET:'+repr(Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==0,"Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == 0"

    def testTestEnableNameDefaultProviderBadReturnCodeError(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        print('TEST:'+repr(Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','TEST:'+repr(Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')==[-1],"Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','') should return == [-1]"

    def testGetEnableNameDefaultProviderBadReturnCodeError(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        print('GET:'+repr(Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','GET:'+repr(Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')[0]==-1,"Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == -1"

    def testTestEnableNameDefaultProvider(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        print('TEST:'+repr(Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','TEST:'+repr(Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [0]"

    @unittest2.skipUnless(os.system('which yum ') == 0,'groupmode is not implemented.')
    def testSetEnableGroupDefaultProvider(self):
        assert Set('Present','','Remote Desktop Clients','','true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
            
    def testSetEnablePathDefaultProvider(self):
        assert Set('Present','','',self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','','"+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"

    def testSetDisableNameDefaultProvider(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        time.sleep(2)
        assert Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"

    def testGetDisableNameDefaultProvider(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        time.sleep(2)
        assert Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        time.sleep(2)
        print('GET:'+repr(Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','GET:'+repr(Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==0,"Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == 0"

    def testTestDisableNameDefaultProvider(self):
        assert Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        time.sleep(2)
        assert Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        time.sleep(2)
        print('TEST:'+repr(Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','TEST:'+repr(Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [0]"

    @unittest2.skipUnless(os.system('which yum ') == 0,'groupmode is not implemented.')
    def testSetDisableGroupDefaultProvider(self):
        assert Set('Present','','Remote Desktop Clients','','true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
        time.sleep(2)
        assert Set('Absent','','Remote Desktop Clients','','true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"
            
    def testSetDisablePathDefaultProvider(self):
        assert Set('Absent','','',self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','','"+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"

    def testSetEnableBadNameDefaultProvider(self):
        assert Set('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[-1],"Set('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]"

    def testGetEnableBadNameDefaultProvider(self):
        print('GET:'+repr(Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','GET:'+repr(Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==-1,"Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[-1] should return == -1"

    def testTestEnableBadNameDefaultProvider(self):
        print('TEST:'+repr(Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','TEST:'+repr(Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[-1],"Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [-1]"

    def testSetEnableBadPathDefaultProvider(self):
        assert Set('Present','','','BADPATH'+self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[-1],"Set('Present','','','"+ 'BADPATH'+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]"

    def testSetDisableBadNameDefaultProvider(self):
        assert Set('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"

    def testGetDisableBadNameDefaultProvider(self):
        print('GET:'+repr(Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','GET:'+repr(Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==0,"Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == 0"

    def testTestDisableBadNameDefaultProvider(self):
        print('TEST:'+repr(Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        Log('/tmp/DSC-nxPackage.log','TEST:'+repr(Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        assert Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [0]"

    def testSetDisableBadPathDefaultProvider(self):
        assert Set('Absent','','', 'BADPATH'+ self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==[0],"Set('Present','','','"+  'BADPATH'+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]"


#(Ensure,PackageManager,Name,Path,PackageGroup,Arguments,RepoUpdate,ReturnCode,LogPath,PackageDescription,Publisher,InstalledOn,Size,Version,Installed)
if __name__ == '__main__':
    # setup unittest2
    
    s=unittest2.TestLoader().loadTestsFromTestCase(LinuxPackageTestCases)
    unittest2.TextTestRunner(verbosity=2).run(s)


sdkfjsldk        fjsldkfjlskdfjsdfsdf
sdfsdfsdf
sdkfjsldk        fjsldkfjlskdfjsdfsdf
sdfsdfsdf        sdkfjsldkfjsldkfjlskdfjsdfsdf
sdfsdfsdf        sdkfjsldkfjsldkfjlskdfjsdfsdf
sdfsdfsdf        sdkfjsldkfjsldkfjlskdfjsdfsdf
sdfsdfsdf        sdkfjsldkfjsldkfjlskdfjsdfsdf
sdfsdfsdf        sdkfjsldkfjsldkfjlskdfjsdfsdf
sdfsdfsdf


sdkfjsldk        fjsldkfjlskdfjsdfsdf
sdfsdfsdf

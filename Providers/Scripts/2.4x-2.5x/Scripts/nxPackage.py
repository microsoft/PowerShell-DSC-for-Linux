#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================
import subprocess
import os
import sys
import time
import re
import imp
import urllib2
apt=None
rpm=None
try:
    import apt
except:
    pass
if apt==None:
    try:
        import rpm
    except:
        pass
protocol=imp.load_source('protocol','../protocol.py')

#   [write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
#   [write,ValueMap{"Yum", "Apt", "Zypper"},Values{"Yum", "Apt", "Zypper"}] string PackageManager;
#   [Key] string Name;
#   [write] string FilePath;
#   [write] Boolean PackageGroup;
#   [write] string Arguments;
#   [write] uint32 ReturnCode;
#   [write] string LogPath;
#   [read] string PackageDescription;
#   [read] string Publisher;
#   [read] string InstalledOn;
#   [read] uint32 Size;
#   [read] string Version;
#   [read] boolean Installed;

cache_file_dir='/var/opt/microsoft/dsc/cache/nxPackage'
global show_mof
show_mof=False

def init_vars(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    if Ensure != None :
        Ensure=Ensure.encode('ascii','ignore')
    else:
        Ensure = ''
    if PackageManager != None :
        PackageManager=PackageManager.encode('ascii','ignore')
    else:
        PackageManager = ''
    if Name != None :
        Name=Name.encode('ascii','ignore')
    else:
        Name = ''
    if FilePath != None :
        FilePath=FilePath.encode('ascii','ignore')
    else:
        FilePath = ''
    if PackageGroup == None :
        PackageGroup = False
    if Arguments != None :
        Arguments=Arguments.encode('ascii','ignore')
    else:
        Arguments = ''
    if ReturnCode == None :
        ReturnCode=0
    if LogPath != None :
        LogPath=LogPath.encode('ascii','ignore')
    else:
        LogPath = ''
    return Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath 
    
def Set_Marshall(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    (Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath) =  init_vars(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    retval = Set(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    sys.stdin.flush()
    sys.stderr.flush()
    sys.stdout.flush()
    return retval

def Test_Marshall(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    (Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath) =  init_vars(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    retval = Test(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    sys.stdin.flush()
    sys.stderr.flush()
    sys.stdout.flush()
    return retval

def Get_Marshall(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    arg_names=list(locals().keys())
    (Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath) =  init_vars(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    retval = 0
    retval,PackageManager,PackageDescription,Publisher,InstalledOn,Size,Version,Installed = Get(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    sys.stdin.flush()
    sys.stderr.flush()
    sys.stdout.flush()
    Ensure = protocol.MI_String(Ensure)
    PackageManager = protocol.MI_String(PackageManager)
    Name = protocol.MI_String(Name)
    FilePath = protocol.MI_String(FilePath)
    PackageGroup= protocol.MI_Boolean(PackageGroup)
    Arguments = protocol.MI_String(Arguments)
    ReturnCode= protocol.MI_Uint32(ReturnCode)
    LogPath = protocol.MI_String(LogPath)
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

    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k] 
    return retval, retd


############################################################
### Begin user defined DSC functions
############################################################
def GetPackageSystem():
    ret=None
    for b in ('dpkg','rpm'):
        code,out=RunGetOutput('which '+b,False,False)
        if code == 0:
            ret = b
            break
    return ret

def GetPackageManager():
    ret=None
    # choose default - almost surely one will match.
    for b in ('apt-get','zypper','yum'):
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
    def __init__(self,Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):

        if not ( "Present" in Ensure or "Absent" in Ensure ):
            Print('ERROR: Param Ensure must be Present or Absent.',file=sys.stdout)
            Log(LogPath,'ERROR: Param Ensure must be Present or Absent.')
            raise Exception('BadParameter')
        if len(PackageManager)>0:
            if not ( "yum" in PackageManager.lower() or  "apt" in PackageManager.lower() or "zypper" in PackageManager.lower() ) :
                Print('ERROR: Param PackageManager values are Yum, Apt, or Zypper.',file=sys.stdout)
                Log(LogPath,'ERROR: Param PackageManager values are Yum, Apt, or Zypper.')
                raise Exception('BadParameter')
        if len(Name)<1 and len(FilePath)<1:
            Print('ERROR: Param Name or FilePath must be set.',file=sys.stdout)
            Log(LogPath,'ERROR: Param Name or FilePath must be set.')
            raise Exception('BadParameter')
        if len(Name)>0 and len(FilePath)>0:
            Print('Ignoring Name because FilePath is set.',file=sys.stdout)
            Log(LogPath,'Ignoring Name because FilePath is set.')
        Print('PackageGroup value is '+repr(PackageGroup)) 
        Print('PackageGroup type is '+repr(type(PackageGroup)))
        if not ( True == PackageGroup or False == PackageGroup ):
            Print('ERROR: Param PackageGroup must be true or false.',file=sys.stdout)
            Log(LogPath,'ERROR: Param PackageGroup must be true or false.')
            raise Exception('BadParameter')
        
        self.Ensure = Ensure
        self.PackageManager = PackageManager.lower()
        self.Name = Name
        self.FilePath = FilePath
        self.PackageGroup = PackageGroup
        self.Arguments,self.CommandArguments=ParseArguments(Arguments)
        self.ReturnCode = ReturnCode
        self.LogPath = LogPath
        self.PackageDescription = ''
        self.Publisher = ''
        self.InstalledOn = ''
        self.Size = 0
        self.Version = ''
        self.Installed = ''

        self.PackageSystem = ''
        
        self.PackageSystem=GetPackageSystem()

        if len(self.PackageManager)<1:
            self.PackageManager=GetPackageManager()

        if len(self.PackageManager)<1 or len(self.PackageSystem)<1 :
            Print("ERROR: Unable to locate any of 'zypper', 'yum', 'apt-get', 'rpm' or 'dpkg' .",file=sys.stdout)
            Log(LogPath,"ERROR: Unable to locate any of 'zypper', 'yum', 'apt-get', 'rpm' or 'dpkg' .")
            raise Exception('BadParameter')
        self.LocalPath=''    
        self.cmds={}
        self.cmds['dpkg']={}
        self.cmds['rpm']={}
        self.cmds['apt']={}
        self.cmds['yum']={}
        self.cmds['zypper']={}
        self.cmds['dpkg']['Present']='dpkg % -i '
        self.cmds['dpkg']['Absent']='dpkg % -r '
        self.cmds['dpkg']['stat']="dpkg-query -W -f='${Description}|${Maintainer}|'Unknown'|${Installed-Size}|${Version}|${Status}\n' "
        self.cmds['dpkg']['stat_group']=None
        self.cmds['rpm']['Present']='rpm % -i '
        self.cmds['rpm']['Absent']='rpm % -e '
        self.cmds['rpm']['stat']='rpm -q --queryformat "%{SUMMARY}|%{PACKAGER}|%{INSTALLTIME}|%{SIZE}|%{VERSION}|installed\n" '
        self.cmds['rpm']['stat_group']=None
        self.cmds['apt']['Present']='apt-get % install ^ --allow-unauthenticated --yes '
        self.cmds['apt']['Absent']='apt-get % remove ^ --allow-unauthenticated --yes '
        self.cmds['apt']['stat']=self.cmds['dpkg']['stat']
        self.cmds['apt']['stat_group']=None
        self.cmds['yum']['Present']='yum -y % install ^ '
        self.cmds['yum']['Absent']='yum -y % remove ^ '
        self.cmds['yum']['GroupPresent']='yum -y % groupinstall ^ '
        self.cmds['yum']['GroupAbsent']='yum -y % groupremove ^ '
        self.cmds['yum']['stat_group']='yum grouplist ' # the group mode is implemented when using YUM only.  
        self.cmds['yum']['stat']=self.cmds['rpm']['stat']
        self.cmds['zypper']['Present']='zypper --non-interactive % install ^'
        self.cmds['zypper']['Absent']='zypper --non-interactive  % remove ^'
        self.cmds['zypper']['stat']=self.cmds['rpm']['stat']
        self.cmds['zypper']['stat_group']=None
        if self.PackageGroup == True:
            if self.cmds[self.PackageManager]['stat_group'] == None:
                Print('ERROR.  PackageGroup is not valid for '+ self.PackageManager,file=sys.stdout)
                Log(self.LogPath,'ERROR.  PackageGroup is not valid for '+ self.PackageManager)
                raise Exception('BadParameter')
            if len(self.FilePath)>0:
                Print('ERROR.  PackageGroup cannot be True if FilePath is set.',file=sys.stdout)
                Log(self.LogPath,'ERROR.  PackageGroup cannot be True if FilePath is set.')
                raise Exception('BadParameter')
                
        
    
def SetShowMof(a):
    global show_mof
    show_mof=a

def ShowMof(op, Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    if not show_mof:
        return
    mof='\n'
    mof+=op +' nxPackage MyPackage \n'
    mof+='{\n'
    mof+='    Name = "' + Name +'"\n'
    mof+='    Ensure = "' + Ensure + '"\n'
    mof+='    PackageManager = "' + PackageManager + '"\n'
    mof+='    FilePath = "' + FilePath + '"\n'
    mof+='    PackageGroup = "' + str(PackageGroup) + '"\n'
    mof+='    Arguments = "' + Arguments + '"\n'
    mof+='    ReturnCode = ' + str(ReturnCode) + '\n'
    mof+='    LogPath = "' + LogPath + '"\n'
    mof+='}\n'
    f=open('./test_mofs.log','a')
    Print(mof,file=f)
    f.close()
    
def IsPackageInstalled(p):
    out=''
    if p==None:
        return False,out
    if len(p.FilePath) > 0 and '://' in p.FilePath : # its a remote - try to file get name from cache
        if ReadCacheInfo(p) == False:
            return False,out
    elif len(p.FilePath) > 0 and os.path.exists(p.FilePath) == True : # FilePath                
        if apt != None and os.path.splitext(p.FilePath)[-1] == '.deb':
            from apt.debfile import DebPackage
            pkg = DebPackage(p.FilePath)
            p.Name=pkg.pkgname
        elif rpm != None and os.path.splitext(p.FilePath)[-1] == '.rpm':
            F=open(p.FilePath,'r')
            ts = rpm.TransactionSet()
            ts.setVSFlags(-1)
            try:
                pkg = ts.hdrFromFdno(F.fileno())
            except rpm.error, e:
                F.close()
                Print(e)
                pkg = None
            F.close()
            if pkg == None:
                return False,out
            p.Name=pkg.dsOfHeader().N()
    if len(p.Name)<1:
        return False,out
    
    if p.PackageGroup == True:
        if p.cmds[p.PackageManager]['stat_group'] != None:
            cmd=p.cmds[p.PackageManager]['stat_group'] + '"' + p.Name + '"' 
        else:
            Print('ERROR.  PackageGroup is not valid for '+ p.PackageManager,file=sys.stdout)
            Log(p.LogPath,'ERROR.  PackageGroup is not valid for '+ p.PackageManager)
            return False,out
    else:
        cmd=p.cmds[p.PackageManager]['stat'] + p.Name
    code,out=RunGetOutput(cmd,False)
    if p.PackageGroup == True: # implemented for YUM only.
        if 'Installed' in out:
            return True,out
        else : 
            return False,out
    # regular packages
    Print('check installed:'+out)
    if code == 0:
        if 'deinstall' in out or 'not-installed' in out:
            code=1
    if code != int(p.ReturnCode) :
        return False,out
    return True,out

def ParseInfo(p,info):
    p.PackageDescription=''
    p.Publisher=''
    p.InstalledOn=''
    p.Size='0'
    p.Version=''
    p.Installed=False

    if len(info)>1:
        f=info.split('|')
        if len(f)==6:
            p.PackageDescription=f[0]
            p.Publisher=f[1]
            p.InstalledOn=f[2]
            if not p.InstalledOn.isalnum():
                p.InstalledOn=time.gmtime(int(p.InstalledOn))
            if len(f[3])>0:
                p.Size=f[3]
            p.Version=f[4]
            p.Installed= ( 'install' in f[5] )
            
        if len(f)!=5:
            Print('ERROR.   '+ p.PackageManager,file=sys.stdout)
            Log(p.LogPath,'ERROR.   '+ p.PackageManager)

def DoEnableDisable(p):
    # if the path is set, use the path and self.PackageSystem
    cmd=""
    if len(p.FilePath) > 1 and 'Present' in p.Ensure : # don't use the path unless installing
        if '://' in p.FilePath and p.LocalPath == '': # its a remote file
            ret=0
            ret=GetRemoteFile(p)
            if ret != 0:
                p.LocalPath=""
                raise Exception('Unable to retrieve remote resource '+p.FilePath+' Error is ' + str(ret))
            else:
                p.FilePath=p.LocalPath
        
        if not os.path.isfile(p.FilePath):
            Print('ERROR.   File '+ p.FilePath + ' not found.',file=sys.stdout)
            Log(p.LogPath,'ERROR.   File '+ p.FilePath + ' not found.')
            return False,""
        cmd=p.cmds[p.PackageSystem][p.Ensure] + ' ' + p.FilePath
        cmd=cmd.replace('%',p.Arguments)
    elif p.PackageGroup == True :
        if p.cmds[p.PackageManager].has_key('Group'+p.Ensure) :
            cmd=p.cmds[p.PackageManager]['Group'+p.Ensure] + '"' + p.Name +'"'
        else :
            Print('Error: Group mode not implemented for ' + p.PackageManager,file=sys.stdout)
            Log(p.LogPath,'Error: Group mode not implemented for ' + p.PackageManager)
            return False,'Error: Group mode not implemented for ' + p.PackageManager
    else:
        cmd=p.cmds[p.PackageManager][p.Ensure] + ' ' + p.Name 
    cmd=cmd.replace('%',p.Arguments)
    cmd=cmd.replace('^',p.CommandArguments)
    code,out=RunGetOutput(cmd,False)
    if len(p.LocalPath) > 1 : # create cache entry and remove the tmp file
        WriteCacheInfo(p)
        RemoveFile(p.LocalPath)
    if code != int(p.ReturnCode) :
        return False,out
    return True,out
    
def WriteCacheInfo(p):
    if not os.path.isdir(cache_file_dir):
        if MakeDirs(cache_file_dir) != None:
            return False
    if len(p.LocalPath)<1:
        return False
    if apt != None and os.path.splitext(p.LocalPath)[-1] == '.deb':
        from apt.debfile import DebPackage
        try:
            pkg = DebPackage(p.LocalPath)
        except:
            Print("Exception opening file " + p.LocalPath,file=sys.stderr)
            return False
        p.Name=pkg.pkgname
    elif rpm != None and os.path.splitext(p.LocalPath)[-1] == '.rpm':
        F,error = opened_w_error(p.LocalPath,'r')
        if error:
            Print("Exception opening file " + p.LocalPath,file=sys.stderr)
            return False
        ts = rpm.TransactionSet()
        ts.setVSFlags(-1)
        try:
            pkg = ts.hdrFromFdno(F.fileno())
        except rpm.error, e:
            Print(e)
            pkg = None
            F.close()
        if pkg == None:
            return False
        p.Name=pkg.dsOfHeader().N()
    if len(p.Name)<1:
        return False
    cache_file_path=cache_file_dir+'/'+os.path.basename(p.LocalPath)
    F,error = opened_w_error(cache_file_path,'w+')
    if error:
        Print("Exception creating cache file " + cache_file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
        return False
    F.write(p.Name+'\n')
    F.close()
    return True

def ReadCacheInfo(p):
    cache_file_path=cache_file_dir+'/'+os.path.basename(p.FilePath)
    if not os.path.isfile(cache_file_path):
        return False
    F,error = opened_w_error(cache_file_path,'r')
    if error:
        Print("Exception opening cache file " + cache_file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
        return False
    t=F.read()
    F.close()
    if len(t) < 2:
        return False
    p.Name=t.strip()
    return True

def Set(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    ShowMof('SET', Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    try:
        p=Params(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    except Exception,e:
        Print('ERROR - Unable to initialize nxPackageProvider.  '+e.message,file=sys.stdout)
        Log(LogPath,'ERROR - Unable to initialize nxPackageProvider. '+ e.message)
        return [-1]
    installed,out = IsPackageInstalled(p)
    if ( installed and Ensure == 'Present' ) or ( not installed and Ensure == 'Absent') : # Nothing to do
        return [0]

    result,out=DoEnableDisable(p)
    if result == False :
        op=''
        if Ensure == 'Present' :
            op = 'Install'
        else :
            op='Un-install'
        Print('Failed to ' + op + ' ' + p.Name + ' output for command was: ' + out)
        Log(p.LogPath,'Failed to ' + op + ' ' + p.Name + ' output for command was: ' + out)
        return [-1]
    return [0]
   
def Test(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    ShowMof('TEST', Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    try:
        p=Params(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    except Exception,e:
        Print('ERROR - Unable to initialize nxPackageProvider.  '+e.message,file=sys.stdout)
        Log(LogPath,'ERROR - Unable to initialize nxPackageProvider. '+ e.message)
        return [-1]
    installed,out = IsPackageInstalled(p)
    if ( installed and Ensure == 'Present' ) or ( not installed and Ensure == 'Absent') :
        return [0]
    return [-1]

def Get(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath):
    retval=-1
    installed=False
    ShowMof('GET', Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)  
    try:
        p=Params(Ensure,PackageManager,Name,FilePath,PackageGroup,Arguments,ReturnCode,LogPath)
    except Exception,e:
        Print('ERROR - Unable to initialize nxPackageProvider.  '+e.message,file=sys.stdout)
        Log(LogPath,'ERROR - Unable to initialize nxPackageProvider. '+ e.message)
        return [retval,p.PackageDescription,p.Publisher,p.InstalledOn,p.Size,p.Version,installed]
    installed,out = IsPackageInstalled(p)
    ParseInfo(p,out)
    return [0,p.PackageManager,p.PackageDescription,p.Publisher,p.InstalledOn,p.Size,p.Version,installed]

def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError, err:
        return None, err
    return f, None

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
            Print('CalledProcessError.  Error Code is ' + str(e.returncode),file=sys.stdout  )
            Print('CalledProcessError.  Command string was ' + e.cmd ,file=sys.stdout )
            Print('CalledProcessError.  Command result was ' + (e.output[:-1]).decode('latin-1'),file=sys.stdout)
        if no_output:
            return e.returncode,None
        else:
            return e.returncode,e.output.decode('latin-1')
        
    if no_output:
        return 0,None
    else :
        return 0,output.decode('latin-1')

def Print(s,file=sys.stdout):
    file.write(s+'\n')
    
def Log(file_path,message):
    if len(file_path)<1 or len(message) < 1:
        return
    t = time.localtime()
    t = "%04u/%02u/%02u %02u:%02u:%02u " % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
    lines=re.sub(re.compile(r'^(.)',re.MULTILINE),t+r'\1',message)
    F,error = opened_w_error(file_path,'a')
    if error:
        Print("Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stdout)
    else:
        F.write(lines + "\n")
        F.close()
        

def GetTimeFromString(s):
    if s == None or len(s) == 0:
        return None
    fmt=[]
    fmt.append('%a, %d %b %Y %H:%M:%S %Z')
    st=None
    for f in fmt:
        try:
            st=time.strptime(s,f) 
        except ValueError:
            continue
    return st

def RemoveFile(path):
    error=None
    try:
        os.remove(path)
    except OSError, error:
         Print("Exception removing file" + path  + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
    except IOError, error:
         Print("Exception removing file" + path  + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
    return error

def LStatFile(path):
    """
    LStat the file.  Do not follow the symlink.
    """
    d=None
    error=None
    try:
        d=os.lstat(path)
    except OSError, error:
         Print("Exception lstating file " + path  + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
    except IOError, error:
         Print("Exception lstating file " + path  + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
    return d

def MakeDirs(path):
    error=None
    try:
        os.makedirs(path)
    except OSError, error:
         Print("Exception making dir" + path  + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
    except IOError, error:
         Print("Exception making dir" + path  + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
    return error

def GetRemoteFile(p):
    req = urllib2.Request(p.FilePath)
    try:
        resp = urllib2.urlopen(req)
    except urllib2.URLError , e:
        Print(repr(e))
        return 1
    p.LocalPath='/tmp/'+os.path.basename(p.FilePath)
    h=resp.info()
    lm=h.getheader('last-modified')
    lm_mtime=GetTimeFromString(lm)
    dst_mtime = None
    dst_st= None
    data = None
    if os.path.exists(p.LocalPath):
        dst_st=LStatFile(p.LocalPath)
    if dst_st != None:
        dst_mtime =  time.gmtime(dst_st.st_mtime)
    if lm_mtime !=None and dst_mtime != None and dst_mtime>=lm_mtime: 
        data = ''
        p.LocalPath=''
    else:
        data = resp.read()
    if data != None and len(data)>0:
        try:
            F = open(p.LocalPath,'wb+')
            F.write(data)
            F.close()
        except  Exception , e:
            F.close()
            Print(repr(e))
            return 1
    return 0

#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

from contextlib import contextmanager

import subprocess
import pwd
import grp
import os
import sys
import time
import re
import shlex 
import imp
protocol=imp.load_source('protocol','../protocol.py')
LogPath='/tmp/nxExec.log'

#   [key] string Command;
#   [write] string[] Environment;
#   [write] boolean Shell;
#   [write] uint16 Returncode;
#   [write] uint32 Timeout;
#   [write] string User;
#   [write] string Group;
#   [write] string TestCommand;

global show_mof
show_mof=False

def Set_Marshall(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    if Command == None:
        Command=''
    if Environment == None:
        Environment=''
    if Shell == None:
        Shell=False
    if Returncode == None:
        Returncode=0
    if Timeout == None:
        Timeout=0
    if User == None:
        User=''
    if Group == None:
        Group=''
    if TestCommand == None:
        TestCommand=''

    retval = Set(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    return retval

def Test_Marshall(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    if Command == None:
        Command=''
    if Environment == None:
        Environment=''
    if Shell == None:
        Shell=False
    if Returncode == None:
        Returncode=0
    if Timeout == None:
        Timeout=0
    if User == None:
        User=''
    if Group == None:
        Group=''
    if TestCommand == None:
        TestCommand=''

    retval = Test(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    return retval

def Get_Marshall(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    arg_names=list(locals().keys())
    if Command == None:
        Command=''
    if Environment == None:
        Environment=''
    if Shell == None:
        Shell=False
    if Returncode == None:
        Returncode=0
    if Timeout == None:
        Timeout=0
    if User == None:
        User=''
    if Group == None:
        Group=''
    if TestCommand == None:
        TestCommand=''

    (retval,Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand) = Get(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)

    Command = protocol.MI_String(Command)
    Environment = protocol.MI_String(Environment)
    Shell = protocol.MI_Boolean(Shell)
    Returncode = protocol.MI_Uint16(Returncode)
    Timeout = protocol.MI_Uint32(Timeout)
    User = protocol.MI_String(User)
    Group = protocol.MI_String(Group)
    TestCommand = protocol.MI_String(TestCommand)
    
    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k] 
    return retval, retd


############################################################
### Begin user defined DSC functions
############################################################

@contextmanager
def opened_w_error(filename, mode="a"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError as err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()

def SetShowMof(a):
    global show_mof
    show_mof=a

def ShowMof(op, Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    if not show_mof:
        return
    mof=''
    mof+=op + ' nxExec MyCmd' + '\n'
    mof+='{\n'
    mof+='    Command' + Command +'\n'
    mof+='    Environment = "' + Environment + '"\n'
    mof+='    Shell = "' + str(Shell) + '"\n'
    mof+='    Returncode = ' + str(Returncode) + '\n'
    mof+='    Timeout = ' + str(Timeout) + '\n'
    mof+='    User = "' + User + '"\n'
    mof+='    Group = "' + Group + '"\n'
    mof+='    TestCommand = "' + TestCommand + '"\n'
    mof+='}\n'
    f=open('./test_mofs.log','a')
    Print(mof,file=f)
    f.close()
    
def Print(s,file=sys.stdout):
    file.write(s+'\n')
    
def Log(file_path,message):
    if len(file_path)<1 or len(message) < 1:
        return
    t = time.localtime()
    t = "%04u/%02u/%02u %02u:%02u:%02u " % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
    lines=re.sub(re.compile(r'^(.)',re.MULTILINE),t+r'\1',message)
    with opened_w_error(file_path,'a') as (F,error):
        if error:
            Print("Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
            Log(LogPath,"Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
        else:
            F.write(lines + "\n")

class Params:

    def __init__(self,Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
        if len(Command)<1:
            Print('ERROR: Mandatory Param Command missing.',file=sys.stderr)
            Log(LogPath,'ERROR: Mandatory Param Command missing.')
            raise Exception('BadParameter')
        self.Command = Command

        self.Environment = Environment

        if Shell != True and Shell != False:
            Print('ERROR: Mandatory Param Shell missing.',file=sys.stderr)
            Log(LogPath,'ERROR: Mandatory Param Shell missing.')
            raise Exception('BadParameter')
        self.Shell = Shell

        self.Returncode = Returncode

        self.User = User

        self.Group = Group

        self.Timeout = Timeout

        if len(TestCommand)<1:
            Print('ERROR: Mandatory Param TestCommand missing.',file=sys.stderr)
            Log(LogPath,'ERROR: Mandatory Param TestCommand missing.')
            raise Exception('BadParameter')
        self.TestCommand = TestCommand
        
def Exec(p,is_test):
    exit_code = -1
    tcmd=''
    if is_test :
        tcmd=p.TestCommand
    else:
        tcmd=p.Command
    uid = gid = -1
    if p.User:
        uid = GetUID(p.User)
        if uid == None :
            Print('ERROR: Unknown UID for '+p.User,file=sys.stderr)
            return [-1]
    if p.Group:
        gid = GetGID(p.Group)
        if gid == None :
            Print('ERROR: Unknown GID for '+p.Group,file=sys.stderr)
            return [-1]
    s=''
    cmd=tcmd
    if True == p.Shell:
        s=' in shell'
    else:
        cmd=shlex.split(cmd)
    Print('Executing Command'+s+ ' '+ repr(cmd))
    try:
        proc = subprocess.Popen(cmd, shell=p.Shell,stdout=subprocess.PIPE, stderr=subprocess.PIPE, preexec_fn=PreExec(uid,gid,p.User,p.Environment))
    except Exception as e:
        Print('Exception launching ' + repr(cmd) + str(e),file=sys.stderr)
        Log(LogPath,'Exception launching ' + repr(cmd) + str(e))
        return exit_code
    retry = p.Timeout/5
    pid=proc.pid
    while retry > 0 and proc.poll() == None:
        Log(LogPath,repr(cmd) + ' still running with PID ' + str(pid))
        time.sleep(5)
        retry-=1
        if retry==0:
            Log(LogPath,'Process exceeded timeout of ' + p.Timeout + ' seconds. Terminating process ' + str(pid))
            os.kill(pid,9)
            return exit_code
    exit_code = proc.wait()
    Result = proc.stdout.read().decode("utf-8")
    Print("exit_code: " + str(exit_code))
    Print("stdout: " + Result)
    Print("stderr: " + proc.stderr.read().decode("utf-8"))
    retcode=-1
    if is_test:
        if exit_code == 0:
            retcode=0
    elif exit_code == p.Returncode: # only chek the Returncode if this is running the Set.
        retcode = 0
    return retcode



def GetUID(User):
    uid = None
    try:
        uid = pwd.getpwnam(User)[2]
    except KeyError:
        Print('ERROR: Unknown UID for '+User,file=sys.stderr)
    return uid

def GetGID(Group):
    gid = None
    try:
        gid = grp.getgrnam(Group)[2]
    except KeyError:
        Print('ERROR: Unknown GID for '+Group,file=sys.stderr)
    return gid


# This is a function that returns a callback function.  The callback function is called prior to a user's exec being executed
def PreExec(uid, gid, User, Environment):
    def SetIDs_callback():
        if gid != -1:
            os.setgroups([gid])
            os.setgid(gid)
        if uid != -1:
            os.setuid(uid)
            os.environ["HOME"] = os.path.expanduser("~" + User)
        if len(Environment)>1 and '=' in Environment :
            for e in Environment.split(','):
                n,v=e.split('=')
                os.environ[n]=v
                Print('Setting ' + n + ' to ' + v,file=sys.stderr)
    return SetIDs_callback


def Set(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    retcode=-1
    ShowMof('SET', Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    try:
        p=Params(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    except :
        return [retcode]
    is_test=True
    code=Exec(p,is_test)
    if code == 0:
        Print("Test command successful:"+p.TestCommand+" with code of "+ str(code) ,file=sys.stderr)
        Log(LogPath,"Test command successful:"+p.TestCommand+" with code of "+ str(code) )
        is_test=False
        retcode=Exec(p,is_test)
    else:
        Print("Test command failed:"+p.TestCommand+" return code of "+ str(code),file=sys.stderr)
        Log(LogPath,"Test command failed:"+p.TestCommand+" return code of "+ str(code))
    return [ retcode ]

def Test(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    retcode=-1
    ShowMof('TEST', Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    try:
        p=Params(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    except :
        return [retcode]
    is_test=True
    code=Exec(p,is_test)
    if code== 0:
        retcode=0
        Print("Test command successful:"+p.TestCommand+" with code of "+ str(code),file=sys.stderr)
        Log(LogPath,"Test command successful:"+p.TestCommand+" with code of "+ str(code))
    else:
        Print("Test command failed:"+p.TestCommand+" return code of "+ str(code)  ,file=sys.stderr)
        Log(LogPath,"Test command failed:"+p.TestCommand+" return code of "+ str(code)  )
    return [ retcode ]

def Get(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    retcode=-1
    ShowMof('GET', Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    try:
        p=Params(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    except :
        return [retcode,Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand]
    is_test=True
    code=Exec(p,is_test)
    if code== 0:
        retcode=0
        Print("Test command successful:"+p.TestCommand+" with code of "+ str(code),file=sys.stderr)
        Log(LogPath,"Test command successful:"+p.TestCommand+" with code of "+ str(code))
        is_test=False
        retcode=Exec(p,is_test)
    else:
        Print("Test command failed:"+p.TestCommand+" return code of "+ str(code)   ,file=sys.stderr)
        Log(LogPath,"Test command failed:"+p.TestCommand+" return code of "+ str(code) )
        retcode=0
    return [ retcode,Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand ]












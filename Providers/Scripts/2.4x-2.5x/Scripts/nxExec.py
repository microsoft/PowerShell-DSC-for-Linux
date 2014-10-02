#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

import subprocess
import pwd
import grp
import os
import sys
import time
import re
import shlex 
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
    Command = Command.decode("utf-8")
    Environment = Environment.decode("utf-8")
    Shell = Shell
    Returncode = Returncode
    Timeout = Timeout
    User = User.decode("utf-8")
    Group = Group.decode("utf-8")
    TestCommand = TestCommand.decode("utf-8")

    retval = Set(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    return retval

def Test_Marshall(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    Command = Command.decode("utf-8")
    Environment = Environment.decode("utf-8")
    Shell = Shell
    Returncode = Returncode
    Timeout = Timeout
    User = User.decode("utf-8")
    Group = Group.decode("utf-8")
    TestCommand = TestCommand.decode("utf-8")

    retval = Test(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)
    return retval

def Get_Marshall(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand):
    Command = Command.decode("utf-8")
    Environment = Environment.decode("utf-8")
    Shell = Shell
    Returncode = Returncode
    Timeout = Timeout
    User = User.decode("utf-8")
    Group = Group.decode("utf-8")
    TestCommand = TestCommand.decode("utf-8")

    (retval,Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand) = Get(Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)

    return [Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand]


############################################################
### Begin user defined DSC functions
############################################################
def opened_w_error(filename, mode="a"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError, err:
        return None, err
    return f, None

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
    # no yield in try/except/finally, no as keyword
    F,error = opened_w_error(file_path,'a')
    if error:
        Print("Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
        Log(LogPath,"Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
    else:
        try:
            F.write(lines + "\n")
        except (IOError) :
            error=sys.exc_info()[1].args[0]
            Print("Exception opening logfile " + file_path + " Error: " + error,file=sys.stderr)
            Log(LogPath,"Exception opening logfile " + file_path + " Error: " + error)
        F.close()

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

        if type(Returncode) == str:
            if len(Returncode)<1:
                Print('ERROR: Mandatory Param Returncode missing.',file=sys.stderr)
                Log(LogPath,'ERROR: Mandatory Param Returncode missing.')
                raise Exception('BadParameter')
        self.Returncode = int(Returncode)

        self.User = User

        self.Group = Group

        if type(Timeout) == str:
            if len(Timeout)<1:
                Print('ERROR: Mandatory Param Timeout missing.',file=sys.stderr)
                Log(LogPath,'ERROR: Mandatory Param Timeout missing.')
                raise Exception('BadParameter')
        self.Timeout = int(Timeout)

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
    cmd=tcmd.encode('ascii')
    if True == p.Shell:
        s=' in shell'
    else:
        cmd=shlex.split(cmd)
    Print('Executing Command'+s+ ' '+ repr(cmd))
    try:
        proc = subprocess.Popen(cmd, shell=p.Shell,stdout=subprocess.PIPE, stderr=subprocess.PIPE, preexec_fn=PreExec(uid,gid,p.User,p.Environment))
    except Exception, e:
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
        return [retcode]
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
    return [ retcode ]












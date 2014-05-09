#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

import subprocess
import shutil
import pwd
import grp
import os
import stat
import time
import tempfile

def Set_Marshall(GetScript, SetScript, TestScript, User, Group):
    GetScript = GetScript.decode("utf-8")
    SetScript = SetScript.decode("utf-8")
    TestScript = TestScript.decode("utf-8")
    User = User.decode("utf-8")
    Group = Group.decode("utf-8")
    
    retval = Set(GetScript, SetScript, TestScript, User, Group)
    return retval

def Test_Marshall(GetScript, SetScript, TestScript, User, Group):
    GetScript = GetScript.decode("utf-8")
    SetScript = SetScript.decode("utf-8")
    TestScript = TestScript.decode("utf-8")
    User = User.decode("utf-8")
    Group = Group.decode("utf-8")
    
    retval = Test(GetScript, SetScript, TestScript, User, Group)
    return retval

def Get_Marshall(GetScript, SetScript, TestScript, User, Group):
    GetScript = GetScript.decode("utf-8")
    SetScript = SetScript.decode("utf-8")
    TestScript = TestScript.decode("utf-8")
    User = User.decode("utf-8")
    Group = Group.decode("utf-8")

    retval = 0
    (retval, GetScript, SetScript, TestScript, User, Group, Result) = Get(GetScript, SetScript, TestScript, User, Group)

    GetScript = GetScript.encode("utf-8")
    SetScript = SetScript.encode("utf-8")
    TestScript = TestScript.encode("utf-8")
    User = User.encode("utf-8")
    Group = Group.encode("utf-8")
    Result = Result.encode("utf-8")

    return [retval, GetScript, SetScript, TestScript, User, Group, Result]


############################################################
### Begin user defined DSC functions
############################################################
def WriteFile(path, contents):
    try:
        f = open(path, "w")
        f.write(contents.replace("\r",""))
        return 0
    except IOError:
        return -1

# This is a function that returns a callback function.  The callback function is called prior to a user's script being executed
def PreExec(uid, gid, User):
    def SetIDs_callback():
        if gid != -1:
            os.setgroups([gid])
            os.setgid(gid)
        if uid != -1:
            os.setuid(uid)
            os.environ["HOME"] = os.path.expanduser("~" + User)
    return SetIDs_callback

def Set(GetScript, SetScript, TestScript, User, Group):
    # write out SetScript to a file, run it as User/Group, return exit code
    tempdir = TempWorkingDirectory(User, Group)
    path = tempdir.GetTempPath()
    command = path

    uid = gid = -1
    if User:
        uid = pwd.getpwnam(User)[2]
    if Group:
        gid = grp.getgrnam(Group)[2]

    WriteFile(path, SetScript)
    os.chmod(path, stat.S_IXUSR | stat.S_IRUSR | stat.S_IXGRP | stat.S_IRGRP)
    os.chown(path, uid, gid)

    proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, preexec_fn=PreExec(uid,gid,User))
    exit_code = proc.wait()
    print("stdout: " + proc.stdout.read().decode("utf-8"))
    print("stderr: " + proc.stderr.read().decode("utf-8"))

    os.remove(path)
    return [exit_code]

def Test(GetScript, SetScript, TestScript, User, Group):
    # write out TestScript to a file, run it as User/Group, return exit code
    tempdir = TempWorkingDirectory(User, Group)
    path = tempdir.GetTempPath()
    command = path

    uid = gid = -1
    if User:
        uid = pwd.getpwnam(User)[2]
    if Group:
        gid = grp.getgrnam(Group)[2]

    WriteFile(path, TestScript)
    os.chmod(path, stat.S_IXUSR | stat.S_IRUSR | stat.S_IXGRP | stat.S_IRGRP)
    os.chown(path, uid, gid)

    proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, preexec_fn=PreExec(uid,gid,User))
    exit_code = proc.wait()
    print("stdout: " + proc.stdout.read().decode("utf-8"))
    print("stderr: " + proc.stderr.read().decode("utf-8"))

    os.remove(path)
    return [exit_code]

def Get(GetScript, SetScript, TestScript, User, Group):
    # write out GetScript to a file, run it as User/Group, then return stderr/stdout and exit code
    tempdir = TempWorkingDirectory(User, Group)
    path = tempdir.GetTempPath()
    command = path

    uid = gid = -1
    if User:
        uid = pwd.getpwnam(User)[2]
    if Group:
        gid = grp.getgrnam(Group)[2]

    WriteFile(path, GetScript)
    os.chmod(path, stat.S_IXUSR | stat.S_IRUSR | stat.S_IXGRP | stat.S_IRGRP)
    os.chown(path, uid, gid)

    proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, preexec_fn=PreExec(uid,gid,User))
    exit_code = proc.wait()
    Result = proc.stdout.read().decode("utf-8")
    print("stdout: " + Result)
    print("stderr: " + proc.stderr.read().decode("utf-8"))

    os.remove(path)
    return [exit_code, GetScript, SetScript, TestScript, User, Group, Result]


class TempWorkingDirectory:
    def __init__(self, User, Group):
        self.dir = tempfile.mkdtemp()
        uid = gid = -1
        if User:
            uid = pwd.getpwnam(User)[2]
        if Group:
            gid = grp.getgrnam(Group)[2]

        os.chown(self.dir, uid, gid)        
        os.chmod(self.dir, stat.S_IXUSR | stat.S_IRUSR | stat.S_IXGRP | stat.S_IRGRP)

    
    def __del__(self):
        shutil.rmtree(self.dir)

    def GetTempPath(self):
        return os.path.join(self.dir, "temp_script.sh")

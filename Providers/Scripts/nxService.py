#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

from __future__ import print_function
from __future__ import with_statement
from contextlib import contextmanager

import subprocess
import os
import sys
import glob
import codecs
import platform

def Set_Marshall(Name, Controller, Enabled, State):
    Name = Name.decode("utf-8")
    Controller = Controller.decode("utf-8")
    Enabled = Enabled.decode("utf-8")
    State = State.decode("utf-8")

    retval = Set(Name, Controller, Enabled, State)
    return retval

def Test_Marshall(Name, Controller, Enabled, State):
    Name = Name.decode("utf-8")
    Controller = Controller.decode("utf-8")
    Enabled = Enabled.decode("utf-8")
    State = State.decode("utf-8")

    retval = Test(Name, Controller, Enabled, State)
    return retval

def Get_Marshall(Name, Controller, Enabled, State):
    Name = Name.decode("utf-8")
    Controller = Controller.decode("utf-8")
    Enabled = Enabled.decode("utf-8")
    State = State.decode("utf-8")

    retval = 0
    (retval, Name, Controller, Enabled, State, Path) = Get(Name, Controller, Enabled, State)

    Name = Name.encode("utf-8")
    Controller = Controller.encode("utf-8")
    Enabled = Enabled.encode("utf-8")
    State = State.encode("utf-8")
    Path = Path.encode("utf-8")

    return [retval, Name, Controller, Enabled, State, Path]


############################################################
### Begin user defined DSC functions
############################################################

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



systemctl_path = ""
upstart_start_path = "/sbin/start"
upstart_stop_path = "/sbin/stop"
upstart_status_path = "/sbin/status"
initd_service = "/sbin/service"
initd_chkconfig = "/sbin/chkconfig"
initd_invokerc = "/usr/sbin/invoke-rc.d"
initd_updaterc = "/usr/sbin/update-rc.d"
lsb_install_initd = "/usr/lib/lsb/install_initd"
lsb_remove_initd = "/usr/lib/lsb/remove_initd"
runlevel_path = "/sbin/runlevel"

def ReadFile(path):
    """
    Safely attempt to read a file,
    ensuring file is always closed at exit.
    Return the data and the exception object.
    The data is None if an error occurred.
    The error is None if the data was read.
    Log results to stderr.
    """
    d=None
    error=None
    with opened_w_error(path,'rb') as (F,error):
        if error:
            print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr )
        else:
            d=F.read()
    return d,error

def WriteFile(path,contents):
    """
    Safely attempt to write data to a file,
    replacing the existing file or creating it and
    ensuring file is always closed at exit.
    Return the exception object.
    The error is None if the data was written.
    Log results to stderr.
    """
    error=None
    with opened_w_error(path,'wb+') as (F,error):
        if error:
            print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
        else:
            F.write(contents)
    return error


def Process(params,no_output=False):
    line=''
    spc=''
    for p in params:
        line+=(spc+p)
        if len(spc) == 0:
            spc=' '
    code,out=RunGetOutput(line,no_output,False)
    return (out, out, code)


def StartService(sc):
    if sc.Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "start", sc.Name])

        if retval != 0:
            print("Error: " + systemctl_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, sc.Name])

        if retval != 0:
            print("Error: " + upstart_start_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "start"])

        if retval != 0:
            print("Error: " + check_state_program + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    if not IsServiceRunning(sc):
        print("Error: " +  sc.Name + " start failed: " + process_stderr,file=sys.stderr)
        return [-1]
    return [0]
 
def StopService(sc):
    if sc.Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "stop", sc.Name])

        if retval != 0:
            print("Error: " + systemctl_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, sc.Name])

        if retval != 0:
            print("Error: " + upstart_stop_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "stop"])

        if retval != 0:
            print("Error: " + check_state_program + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    if IsServiceRunning(sc):
        print("Error: " +  sc.Name + " stop failed: " + process_stderr,file=sys.stderr)
        return [-1]

    return [0]

def GetRunLevel():
    (process_stdout, process_stderr, retval) = Process([runlevel_path])
    
    if retval != 0:
        print("Error: " + runlevel_path + " failed: " + process_stderr,file=sys.stderr)
        return -1

    tokens = process_stdout.split(" ")
    if len(tokens) != 2:
        print("Error: unexpected number of tokens from " + runlevel_path + ".  stdout: " + process_stdout,file=sys.stderr)
        return -1

    return int(tokens[1])

def DetermineInitState(stdout):
    if "running" in stdout:
        return True
    elif stdout.strip() == "Running":
        return True
    elif "(running)" in stdout:
        return True
    else:
        return False

def DetermineInitEnabled(stdout, runlevel):
    tokens = stdout.split()
    tokens = tokens[1:]
    
    if runlevel > (len(tokens) - 1):
        print("runlevel " + str(runlevel) + " not found in chkconfig",file=sys.stderr)
        return False

    runlevel_tokens = tokens[runlevel].split(":")

    if len(runlevel_tokens) != 2:
        print("Unable to determine format for chkconfig run level",file=sys.stderr)
        return False

    if runlevel_tokens[1] == "on":
        return True
    else:
        return False

def GetSystemdState(sc):
    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", sc.Name])
    if retval == 0:
        return "running"
    else:
        return "stopped"

def TestSystemdState(sc):
    if sc.State and sc.State != GetSystemdState(sc):
        return False
    
    return True

def GetSystemdEnabled(sc):
    (process_stdout, process_stderr, retval) = Process([systemctl_path, "is-enabled", sc.Name])
    if retval == 0:
        return "true"
    else:
        return "false"

def TestSystemdEnabled(sc):
    if sc.Enabled and sc.Enabled != GetSystemdEnabled(sc):
        return False
    return True

def TestSystemd(sc):
    if not SystemdExists():
        return [-1]
    if not TestSystemdState(sc):
        return [-1]
    if not TestSystemdEnabled(sc):
        return [-1]

    return [0]

def GetUpstartState(sc):
    (process_stdout, process_stderr, retval) = Process([upstart_status_path, sc.Name])
    
    if retval != 0:
        print("Error: " + upstart_status_path + " failed: " + process_stderr,file=sys.stderr)
        return ""

    if (sc.Name + " start") in process_stdout:
        return "running"
    else:
        return "stopped"

def TestUpstartState(sc):
    if sc.State and sc.State != GetUpstartState(sc):
        return False
    return True

def GetUpstartEnabled(sc):
    if os.path.isfile("/etc/init/" + sc.Name + ".conf"):
        file_lines,error = ReadFile("/etc/init/" + sc.Name + ".conf")
        if error != None:
               print("Error reading:/etc/init/" + sc.Name + ".conf",file=sys.stderr)
               return "Error"   
        start_on_exists = False
        start_on_is_enabled = False
        stop_on_exists = False
        stop_on_is_enabled = False
        for full_line in file_lines.splitlines():
            # everything after a '#' character is a comment, so strip it off
            line = full_line.split("#")[0]  
            if "start on" in line:
                start_on_exists = True
                if ("(" in line) or ("and" in line) or ("or" in line):
                    return "Complex"
                elif "start on runlevel [" in line:
                    runlevel = GetRunLevel()    
                    specified_runlevel_digits = line.split("[")[1][:-1]
                    if str(runlevel) in specified_runlevel_digits:
                        start_on_is_enabled = True
                    else:
                        start_on_is_enabled = False
                    if "!" in specified_runlevel_digits:
                        start_on_is_enabled = not start_on_is_enabled
                else:
                    return "Complex"
            if "stop on" in line:
                stop_on_exists = True
                if ("(" in line) or ("and" in line) or ("or" in line):
                    return "Complex"
                elif "stop on runlevel [" in line:
                    runlevel = GetRunLevel()    
                    specified_runlevel_digits = line.split("[")[1][:-1]
                    if str(runlevel) in specified_runlevel_digits:
                        stop_on_is_enabled = True
                    else:
                        stop_on_is_enabled = False
                    if "!" in specified_runlevel_digits:
                        stop_on_is_enabled = not stop_on_is_enabled
                else:
                    return "Complex"
        

        if start_on_exists and start_on_is_enabled:
            if stop_on_exists and stop_on_is_enabled:
                print("Error: Having trouble determining whether service " + sc.Name + " is enabled or disabled.",file=sys.stderr)
                return "Complex"
            else:
                return "true"
        else:
            return "false"

        print("Info: Unable to find line containing 'start on' in " + sc.Name + ".conf",file=sys.stderr)
        return "false"
    else:
        print("Error: conf file does not exist for service named " + sc.Name,file=sys.stderr)
        return "false"

def TestUpstartEnabled(sc):
    if sc.Enabled:
        currently_enabled = GetUpstartEnabled(sc)
        if sc.Enabled == "true" and currently_enabled == "false":
            return False
        elif sc.Enabled == "false" and currently_enabled == "true":
            return False
        elif currently_enabled == "Complex":
            print("Info: Cannot modify 'Enabled' state for service " + sc.Name + ", conf file too complex.  Please use the File provider to write your own conf file for this service.",file=sys.stderr)
            return True
    return True

def TestUpstart(sc):
    if not UpstartExists():
        return [-1]
    if not TestUpstartState(sc):
        return [-1]
    if not TestUpstartEnabled(sc):
        return [-1]
    return [0]

def GetInitState(sc):
    check_state_program = initd_service
    check_enabled_program = initd_chkconfig
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc
        check_enabled_program = initd_updaterc

    (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "status"])
    
    if DetermineInitState(process_stdout):
        return "running"
    else:
        return "stopped"

def TestInitState(sc):
    if sc.State and sc.State != GetInitState(sc):
        return False
    return True

def GetInitEnabled(sc):
    runlevel = GetRunLevel()
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        # A service is enabled if a symbolic link exists in /etc/rc${RUNLEVEL}.d/ with the name:
        #    S??${sc.Name}
        matched_files = glob.glob("/etc/rc" + str(runlevel) + ".d/S??" + sc.Name)
        for f in matched_files:
            if os.path.islink(f):
                return "true"
        return "false"
    else:
        check_state_program = initd_service
        check_enabled_program = initd_chkconfig
        (process_stdout, process_stderr, retval) = Process([check_enabled_program, "--list", sc.Name])

        if retval != 0:
            print("Error: " + check_enabled_program + " failed: " + process_stderr,file=sys.stderr)
            return ""

        if DetermineInitEnabled(process_stdout, runlevel):
            return "true"
        else:
            return "false"

def TestInitEnabled(sc):
    if sc.Enabled and sc.Enabled != GetInitEnabled(sc):
        return False
    return True

def TestInit(sc):
    if not InitExists():
        return [-1]
    if not TestInitState(sc):
        return [-1]
    if not TestInitEnabled(sc):
        return [-1]

    return [0]

def SystemdExists():
    global systemctl_path
    code,out=RunGetOutput('which systemctl',False,False)
    if code == 0 :
        systemctl_path=out.strip()
        return True
    else:
        return False

def UpstartExists():
    if os.path.isfile('/sbin/upstart-local-bridge') and os.path.isfile(upstart_start_path) and os.path.isfile(upstart_stop_path) and os.path.isfile(upstart_status_path):
        return True
    else:
        return False

def InitExists():
    if os.path.isfile(initd_service) and os.path.isfile(initd_chkconfig):
        return True
    elif os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        return True
    else:
        return False

def ServiceExistsInSystemd(sc):
    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", sc.Name])
    if retval !=0 :
        if "Loaded: loaded" in process_stdout:
            return True
        else:
            return False
    else:
        return True
    
def ServiceExistsInUpstart(sc):
    (process_stdout, process_stderr, retval) = Process([upstart_status_path, sc.Name])
    
    if retval != 0:
        return False
    else:
        return True

def ServiceExistsInInit(sc):
    check_state_program = initd_service
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc

    (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "status"])

    if "unrecognized service" in process_stderr or "no such service" in process_stderr:
        print(process_stderr,file=sys.stderr)
        return False
    else:
        return True

def CreateSystemdService(sc):
    print("Error: systemd services cannot be created from the service provider.  Please use the file provider to create a systemd conf file, then modify the service using this service provider.",file=sys.stderr)
    return [-1]

def ModifySystemdService(sc):
    if sc.Enabled == "true":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "enable", sc.Name + '.service'])
        
        if retval != 0:
            print("Error: " + systemctl_path + " enable " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]
    elif sc.Enabled == "false":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "disable", sc.Name + '.service'])
        
        if retval != 0:
            print("Error: " + systemctl_path + " disable " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", sc.Name + '.service'])
    if retval == 0:
        print("running",file=sys.stderr)
        if sc.State and sc.State != "running":
            return StopService(sc)
            
    else:
        print("stopped",file=sys.stderr)
        if sc.State and sc.State != "stopped":
            return StartService(sc)

    return [0]

def CreateUpstartService(sc):
    print("Error: Upstart services cannot be created from the service provider.  Please use the file provider to create an upstart conf file, then modify the service using this service provider.",file=sys.stderr)
    return [-1]

def ModifyUpstartConfFile(sc):
    
    file_lines,error = ReadFile("/etc/init/" + sc.Name + ".conf")
    if len(file_lines) == 0 or error != None:
        print("Error: Conf file unable to be read for service " + sc.Name,file=sys.stderr)
        return False

    outfile = ""
    start_on_exists = False

    for full_line in file_lines.splitlines():
        line = full_line.split("#")[0]  
        if "start on" in line and not start_on_exists:
            # If we got to this point, we can assume that we're allowed to modify the conf file. No need to check for a "Complex" conf file.
            start_on_exists = True
            if sc.Enabled == "true":
                outfile += "start on runlevel [2345]\n"
                outfile += "stop on runlevel [!2345]\n"
            elif sc.Enabled == "false":
                outfile += "stop on runlevel [0123456]\n"
        elif "stop on" in line:
            # Let the 'start on' clause of this if statement handle the insertion of 'stop on'
            pass
        else:
            outfile += full_line + "\n"

    if not start_on_exists:
        # If there was no "start on", make sure to add one
        if sc.Enabled == "true":
            outfile += "start on runlevel [2345]\n"
            outfile += "stop on runlevel [!2345]\n"
        elif sc.Enabled == "false":
            outfile += "stop on runlevel [0123456]\n"

    if WriteFile("/etc/init/" + sc.Name + ".conf", outfile) != None :
        print("Error: Unable to write conf file for service " + sc.Name,file=sys.stderr)
        return False

    return True

def ModifyUpstartService(sc):
    if sc.Enabled and sc.Enabled != GetUpstartEnabled(sc):
        if not ModifyUpstartConfFile(sc):
            print("Error: Failed to modify upstart conf file",file=sys.stderr)
            return [-1]
    
    if sc.State == "running":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, sc.Name])
        
        if retval != 0:
            if "Job is already running" not in process_stderr:
                print("Error: " + upstart_start_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
                return [-1]
        if not IsServiceRunning(sc):
            print("Error: " +  upstart_start_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]
    elif sc.State == "stopped":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, sc.Name])
        if retval != 0:
            if "Unknown instance" not in process_stderr:
                print("Error: " + upstart_stop_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
                return [-1]
        if IsServiceRunning(sc):
            print("Error: " +  upstart_stop_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    return [0]

def CreateInitService(sc):
    (process_stdout, process_stderr, retval) = Process([lsb_install_initd, sc.Name])
    if retval != 0:
        print("Error: " + lsb_install_initd + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
        return [-1]

    return ModifyInitService(sc)

def ModifyInitService(sc):
    check_state_program = initd_service
    check_enabled_program = initd_chkconfig
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc
        check_enabled_program = initd_updaterc
        if sc.Enabled == "true":
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, "-f", sc.Name, "enable"])
            if retval != 0:
                print("Error: " + check_enabled_program + " -f " + sc.Name + " on failed: " + process_stderr,file=sys.stderr)
                return [-1]
        elif sc.Enabled == "false":
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, "-f", sc.Name, "disable"])
            if retval != 0:
                print("Error: " + check_enabled_program + " -f " + sc.Name + " on failed: " + process_stderr,file=sys.stderr)
                return [-1]   
    else:
        if sc.Enabled == "true":
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, sc.Name, "on"])
            if retval != 0:
                print("Error: " + check_enabled_program + " " + sc.Name + " on failed: " + process_stderr,file=sys.stderr)
                return [-1]
        elif sc.Enabled == "false":
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, sc.Name, "off"])
            if retval != 0:
                print("Error: " + check_enabled_program + " " + sc.Name + " on failed: " + process_stderr,file=sys.stderr)
                return [-1]   

    if sc.State == "running":
        # don't try to read stdout or stderr as 'service start' comand re-directs them, causing a hang in subprocess.communicate()
        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "start"],True) 
        if retval != 0:
            print("Error: " + check_state_program + " " + sc.Name + " start failed: " + process_stderr,file=sys.stderr)
            return [-1]
        if not IsServiceRunning(sc):
            print("Error: " + check_state_program + " " + sc.Name + " start failed: " + process_stderr,file=sys.stderr)
            return [-1]
            
    elif sc.State == "stopped":
        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "stop"])
        if retval != 0:
            print("Error: " + check_state_program + " " + sc.Name + " stop failed: " + process_stderr,file=sys.stderr)
            return [-1]
        if IsServiceRunning(sc):
            print("Error: " + check_state_program + " " + sc.Name + " stop failed: " + process_stderr,file=sys.stderr)
            return [-1]

    return [0]

def IsServiceRunning(sc):
    cmd = "ps -ef | grep -v grep | grep "+  sc.Name 
    code,out=RunGetOutput(cmd,False,False)
    if code != 0:
        return False
    return True

def Set(Name, Controller, Enabled, State):
    sc = ServiceContext(Name, Controller, Enabled, State)
    if sc.Controller == "systemd" :
        if SystemdExists() == True :
            if ServiceExistsInSystemd(sc):
                return ModifySystemdService(sc)
            else:
                return CreateSystemdService(sc)
    elif sc.Controller == "upstart"  :
        if UpstartExists() == True :
            if ServiceExistsInUpstart(sc):
                return ModifyUpstartService(sc)
            else:
                return CreateUpstartService(sc)
    elif sc.Controller == "init":
        if InitExists() == True:
            if ServiceExistsInInit(sc) :
                return ModifyInitService(sc)
            else:
                return CreateInitService(sc)
    
    return [-1]

def Test(Name, Controller, Enabled, State):
    sc = ServiceContext(Name, Controller, Enabled, State)

    if sc.Controller == "systemd":
        return TestSystemd(sc)
    elif sc.Controller == "upstart":
        return TestUpstart(sc)
    elif sc.Controller == "init":
        return TestInit(sc)
    else:
        print("Invalid service controller (" + sc.Controller + ",file=sys.stderr) specified for service: " + sc.Name)
        return [-1]

    return [-1]

def Get(Name, Controller, Enabled, State):
    sc = ServiceContext(Name, Controller, Enabled, State)

    Path = ""
    exit_code = 0

    if not sc.Controller:
        print("Error: Controller not specified",file=sys.stderr)
        exit_code = -1
    elif sc.Controller == "systemd":
        if not ServiceExistsInSystemd(sc):
            print("Error: Unable to find service named " + sc.Name + " in systemd.",file=sys.stderr)
            exit_code = -1
        else:
            Enabled = GetSystemdEnabled(sc)
            State = GetSystemdState(sc)
            Path = "/usr/lib/systemd/system/" + sc.Name + ".service"
    elif sc.Controller == "upstart":
        if not ServiceExistsInUpstart(sc):
            print("Error: Unable to find service named " + sc.Name + " in upstart.",file=sys.stderr)
            exit_code = -1
        else:
            temp = GetUpstartEnabled(sc)
            if temp == "false":
                Enabled = "false"
            else:
                # When GetUpstartEnabled returns "Complex", we assume that it is enabled (and we won't modify it).
                Enabled = "true"
                
            State = GetUpstartState(sc)
            Path = "/etc/init/" + sc.Name + ".conf"
    elif sc.Controller == "init":
        if not ServiceExistsInInit(sc):
            print("Error: Unable to find service named " + sc.Name + " in init.",file=sys.stderr)
            exit_code = -1
        else:
            Enabled = GetInitEnabled(sc)
            State = GetInitState(sc)
            Path = "/etc/init.d/" + sc.Name

    return [exit_code, Name, Controller, Enabled, State, Path]


class ServiceContext:
    def __init__(self, Name, Controller, Enabled, State):
        if not Name:
            raise Exception("Error: Service has no name.")
        
        if not Controller:
            raise Exception("Error: Controller not specified.")

        self.Name = Name
        self.Controller = Controller.lower()
        self.Enabled = Enabled.lower()
        self.State = State.lower()




import unittest,time


dummy_service_file=r"""#!/usr/bin/env python
import time
import os
with open('/var/run/dummy_service.pid','w') as F: 
        F.write(str(os.getpid()) + "\n")
        F.flush()
        F.close()
while True:
    time.sleep(5)
    with open('/tmp/dummy_service.log','a') as F: 
        F.write('dummy_service is running at '+time.asctime()+'\n')
        F.flush()
        F.close()
"""

#sample init files for testing
upstart_etc_default="""\
# To disable the Windows Azure Agent, set DUMMY_SERVICE_ENABLED=0
DUMMY_SERVICE_ENABLED=1
"""
upstart_init_conf="""\
description "Windows Azure Linux agent"
author "Ben Howard <ben.howard@canonical.com>"
export PATH=$PATH:/usr/local/bin
start on mounted MOUNTPOINT=/
stop on runlevel [!2345]

pre-start script

    [ -r /etc/default/dummy_service ] && . /etc/default/dummy_service

    if [ "$DUMMY_SERVICE_ENABLED" != "1" ]; then
        stop ; exit 0
    fi

    if [ ! -x /usr/sbin/dummy_service.py ]; then
        stop ; exit 0
    fi

    #Load the udf module
    modprobe -b udf

end script

exec /usr/sbin/dummy_service.py -daemon
"""

upstart_init_d_file = """\
#!/bin/sh -e
# upstart-job
#
# Symlink target for initscripts that have been converted to Upstart.

set -e

UPSTART_JOB_CONF="/etc/default/upstart-job"
INITSCRIPT="$(basename "$0")"
JOB="${INITSCRIPT%.sh}"

if [ "$JOB" = "upstart-job" ]; then
    if [ -z "$1" ]; then
        echo "Usage: upstart-job JOB COMMAND" 1>&2
	exit 1
    fi

    JOB="$1"
    INITSCRIPT="$1"
    shift
else
    if [ -z "$1" ]; then
        echo "Usage: $0 COMMAND" 1>&2
	exit 1
    fi
fi

COMMAND="$1"
shift

ECHO=echo
ECHO_ERROR=echo
if [ -e "$UPSTART_JOB_CONF" ]; then
	. "$UPSTART_JOB_CONF"
fi
if [ -n "$DPKG_MAINTSCRIPT_PACKAGE" ]; then
	ECHO=:
	ECHO_ERROR=:
fi

$ECHO "Rather than invoking init scripts through /etc/init.d, use the service(8)"
$ECHO "utility, e.g. service $INITSCRIPT $COMMAND"

# Only check if jobs are disabled if the currently _running_ version of
# Upstart (which may be older than the latest _installed_ version)
# supports such a query.
#
# This check is necessary to handle the scenario when upgrading from a
# release without the 'show-config' command (introduced in
# Upstart for Ubuntu version 0.9.7) since without this check, all
# installed packages with associated Upstart jobs would be considered
# disabled.
#
# Once Upstart can maintain state on re-exec, this change can be
# dropped (since the currently running version of Upstart will always
# match the latest installed version).

UPSTART_VERSION_RUNNING=$(initctl version|awk '{print $3}'|tr -d ')')

if dpkg --compare-versions "$UPSTART_VERSION_RUNNING" ge 0.9.7
then
    initctl show-config -e "$JOB"|grep -q '^  start on' || DISABLED=1
fi

case $COMMAND in
status)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the $COMMAND(8) utility, e.g. $COMMAND $JOB"
    $COMMAND "$JOB"
    ;;
start|stop)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the $COMMAND(8) utility, e.g. $COMMAND $JOB"
    if status "$JOB" 2>/dev/null | grep -q ' start/'; then
        RUNNING=1
    fi
    if [ -z "$RUNNING" ] && [ "$COMMAND" = "stop" ]; then
        exit 0
    elif [ -n "$RUNNING" ] && [ "$COMMAND" = "start" ]; then
        exit 0
    elif [ -n "$DISABLED" ] && [ "$COMMAND" = "start" ]; then
        exit 0
    fi
    $COMMAND "$JOB"
    ;;
restart)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the stop(8) and then start(8) utilities,"
    $ECHO "e.g. stop $JOB ; start $JOB. The restart(8) utility is also available."
    if status "$JOB" 2>/dev/null | grep -q ' start/'; then
        RUNNING=1
    fi
    if [ -n "$RUNNING" ] ; then
        stop "$JOB"
    fi
    # If the job is disabled and is not currently running, the job is
    # not restarted. However, if the job is disabled but has been forced into the
    # running state, we *do* stop and restart it since this is expected behaviour
    # for the admin who forced the start.
    if [ -n "$DISABLED" ] && [ -z "$RUNNING" ]; then
        exit 0
    fi
    start "$JOB"
    ;;
reload|force-reload)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the reload(8) utility, e.g. reload $JOB"
    reload "$JOB"
    ;;
*)
    $ECHO_ERROR
    $ECHO_ERROR "The script you are attempting to invoke has been converted to an Upstart" 1>&2
    $ECHO_ERROR "job, but $COMMAND is not supported for Upstart jobs." 1>&2
    exit 1
esac
"""

debian_init_file = """\
#!/bin/sh
### BEGIN INIT INFO
# Provides:          dummy_service
# Required-Start:    $network $syslog
# Required-Stop:     $network $syslog
# Should-Start:      $network $syslog
# Should-Stop:       $network $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: dummy_service
# Description:       dummy_service
### END INIT INFO

. /lib/lsb/init-functions

OPTIONS="-daemon"
WAZD_BIN=/usr/sbin/dummy_service.py
WAZD_PID=/var/run/dummy_service.pid

case "$1" in
    start)
        log_begin_msg "Starting dummy_service..."
        pid=$( pidofproc $WAZD_BIN )
        if [ -n "$pid" ] ; then
              log_begin_msg "Already running."
              log_end_msg 0
              exit 0
        fi
        start-stop-daemon --start --quiet --oknodo --background --exec $WAZD_BIN -- $OPTIONS
        log_end_msg $?
        ;;

    stop)
        log_begin_msg "Stopping dummy_service..."
        start-stop-daemon --stop --quiet --oknodo --pidfile $WAZD_PID
        ret=$?
        rm -f $WAZD_PID
        log_end_msg $ret
        ;;
    force-reload)
        $0 restart
        ;;
    restart)
        $0 stop
        $0 start
        ;;
    status)
        status_of_proc $WAZD_BIN && exit 0 || exit $?
        ;;
    *)
        log_success_msg "Usage: /etc/init.d/dummy_service {start|stop|force-reload|restart|status}"
        exit 1
        ;;
esac

exit 0
"""

suse_init_file = """\
#! /bin/sh
#
# Windows Azure Linux Agent sysV init script
#
# Copyright 2013 Microsoft Corporation
# Copyright SUSE LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# /etc/init.d/dummy_service
#
#  and symbolic link
#
# /usr/sbin/rcdummy_service
#
# System startup script for the dummy_service 
#
### BEGIN INIT INFO
# Provides: dummy_service
# Required-Start: $network sshd
# Required-Stop: $network sshd
# Default-Start: 3 5
# Default-Stop: 0 1 2 6
# Description: Start the dummy_service
### END INIT INFO

PYTHON=/usr/bin/python
WAZD_BIN=/usr/sbin/dummy_service.py
WAZD_PIDFILE=/var/run/dummy_service.pid

test -x "$WAZD_BIN" || { echo "$WAZD_BIN not installed"; exit 5; }

. /etc/rc.status

# First reset status of this service
rc_reset

# Return values acc. to LSB for all commands but status:
# 0 - success
# 1 - misc error
# 2 - invalid or excess args
# 3 - unimplemented feature (e.g. reload)
# 4 - insufficient privilege
# 5 - program not installed
# 6 - program not configured
#
# Note that starting an already running service, stopping
# or restarting a not-running service as well as the restart
# with force-reload (in case signalling is not supported) are
# considered a success.


case "$1" in
    start)
        echo -n "Starting dummy_service"
        ## Start daemon with startproc(8). If this fails
        ## the echo return value is set appropriate.
        startproc -f ${PYTHON} ${WAZD_BIN} -daemon
        rc_status -v
        ;;
    stop)
        echo -n "Shutting down dummy_service"
        ## Stop daemon with killproc(8) and if this fails
        ## set echo the echo return value.
        killproc -p ${WAZD_PIDFILE} ${PYTHON} ${WAZD_BIN}
        rc_status -v
        ;;
    try-restart)
        ## Stop the service and if this succeeds (i.e. the
        ## service was running before), start it again.
        $0 status >/dev/null && $0 restart
        rc_status
        ;;
    restart)
        ## Stop the service and regardless of whether it was
        ## running or not, start it again.
        $0 stop
        sleep 1
        $0 start
        rc_status
        ;;
    force-reload|reload)
        rc_status
        ;;
    status)
        echo -n "Checking for service dummy_service "
        ## Check status with checkproc(8), if process is running
        ## checkproc will return with exit status 0.

        checkproc -p ${WAZD_PIDFILE} ${PYTHON} ${WAZD_BIN}
        rc_status -v
        ;;
    probe)
        ;;
    *)
        echo "Usage: $0 {start|stop|status|try-restart|restart|force-reload|reload}"
        exit 1
        ;;
esac
rc_exit
"""
redhat_init_file= """\
#!/bin/bash
#
# Init file for dummy_service.
#
# chkconfig: 2345 60 80
# description: dummy_service
# pidfile: /var/run/dummy_service.pid
# processname dummy_service.py
# source function library
. /etc/rc.d/init.d/functions

RETVAL=0
FriendlyName="dummy_service"
WAZD_BIN=/usr/sbin/dummy_service.py

start()
{
    echo -n $"Starting $FriendlyName: "
    $WAZD_BIN &
}

stop()
{
    echo -n $"Stopping $FriendlyName: "
    killproc -p /var/run/dummy_service.pid $WAZD_BIN
    RETVAL=$?
    echo
    return $RETVAL
}

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        stop
        start
        ;;
    reload)
        ;;
    report)
        ;;
    status)
        status $FriendlyName
        RETVAL=$?
        ;;
    *)
        echo $"Usage: $0 {start|stop|restart|status}"
        RETVAL=1
esac
exit $RETVAL
"""



class LinuxServiceTestCases(unittest.TestCase):
    """
    Test cases for LinuxFile
    """
    def setUp(self):
        """
        Setup test resources
        """
        self.provider = None

        dist=platform.dist()[0].lower()
        if 'suse' in dist:
            init_file=suse_init_file
        elif 'redhat' in dist:
            init_file=redhat_init_file
        elif 'cent' in dist:
            init_file=redhat_init_file
        elif 'debian' in dist:
            init_file=debian_init_file
            
        if SystemdExists():
            self.provider='systemd'
            try:
                WriteFile('/etc/rc.d/dummy_service',init_file)
                os.chmod('/etc/rc.d/dummy_service',0744)
                WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print(repr(sys.sys_info()))
                sys.exit(1)

        elif UpstartExists():
            self.provider='upstart'
            try:
                WriteFile('/etc/default/dummy_service',upstart_etc_default)
                os.chmod('/etc/default/dummy_service',0744)
                WriteFile('/etc/init/dummy_service.conf',upstart_init_conf)
                WriteFile('/etc/init.d/dummy_service',upstart_init_d_file)
                os.chmod('/etc/init.d/dummy_service',0744)
                WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print(repr(sys.sys_info()))
                sys.exit(1)
        elif InitExists():
            self.provider='init'
            try:
                WriteFile('/etc/init.d/dummy_service',init_file)
                os.chmod('/etc/init.d/dummy_service',0744)
                WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print(repr(sys.sys_info()))
                sys.exit(1)
            

    def tearDown(self):
        """
        Remove test resources.
        """
        if SystemdExists():
            os.system('chkconfig --del dummy_service &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/rc.d/dummy_service &> /dev/null')
            os.system('systemctl --system daemon-reload &> /dev/null')
        if InitExists():
            os.system('chkconfig --del dummy_service &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/init.d/dummy_service &> /dev/null')
        if UpstartExists():
            os.system('update-rc.d -f dummy_service remove &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/init/dummy_service.conf /etc/init.d/dummy_service /etc/default/dummy_service &> /dev/null')
            
        time.sleep(1)
        os.system("ps -ef | grep -v grep | grep dummy_service | awk '{print $2}' | xargs -L1 kill &> /dev/null")
        
    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass
    
    def testSetEnable(self):
        provider=self.provider
        assert Set("dummy_service", provider, "true", "running")==[0],'Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]'

    def testSetDisable(self):
        provider=self.provider
        assert Set("dummy_service", provider, "true", "running")==[0],'Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]'
        assert Set("dummy_service", provider, "false", "stopped")==[0],'Set("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]'

    def testSetEnableError(self):
        provider=self.provider
        assert Set("yummyservice", provider, "true", "running")==[-1],'Set("yummyservice", "'+provider+'", "true", "running") should return ==[-1]'

    def testSetDisableError(self):
        provider=self.provider
        assert Set("yummyservice", provider, "false", "stopped")==[-1],'Set("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]'

    def testGetEnable(self):
        provider=self.provider
        assert Set("dummy_service", provider, "true", "running")==[0],'Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]'
        assert Get("dummy_service", provider, "true", "running")[0:5]==[0,"dummy_service",provider,"true","running"],'Get("dummy_service", "'+provider+'", "true", "running") should return ==[0]'

    def testGetDisable(self):
        provider=self.provider
        assert Set("dummy_service", provider, "true", "running")==[0],'Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]'
        assert Set("dummy_service", provider, "false", "stopped")==[0],'Set("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]'
        print('GET:'+repr(Get("dummy_service", provider, "false", "stopped")))
        assert Get("dummy_service", provider, "false", "stopped")[0:5]==[0,"dummy_service", provider, "false", "stopped"],'Get("dummy_service", "'+provider+'", "false", "stopped") should return ==[0,"dummy_service", provider, "false", "stopped"]'

    def testGetEnableError(self):
        provider=self.provider
        assert Set("yummyservice", provider, "true", "running")==[-1],'Set("yummyservice", "'+provider+'", "true", "running") should return ==[-1]'
        print('GET:'+repr(Get("yummyservice", provider, "true", "running")[0:5]))
        assert Get("yummyservice", provider, "true", "running")[0:5]==[-1,"yummyservice", provider, "true", "running"],'Get("yummyservice", "'+provider+'", "true", "running")[0:5] should return ==[-1,"yummyservice", provider, "true", "running"]'

    def testGetDisableError(self):
        provider=self.provider
        assert Set("yummyservice", provider, "false", "stopped")==[-1],'Set("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]'
        print('GET:'+repr(Get("yummyservice", provider, "false", "stopped")))
        assert Get("yummyservice", provider, "false", "stopped")[0:5]==[-1,"yummyservice", provider, "false", "stopped"],'Get("yummyservice", "'+provider+'", "false", "stopped")[0:5] should return ==[-1,"yummyservice", provider, "false", "stopped"]'

    def testTestEnable(self):
        provider=self.provider
        assert Set("dummy_service", provider, "true", "running")==[0],'Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]'
        assert Test("dummy_service", provider, "true", "running")==[0],'Test("dummy_service", "'+provider+'", "true", "running") should return ==[0]'

    def testTestDisable(self):
        provider=self.provider
        assert Set("dummy_service", provider, "true", "running")==[0],'Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]'
        assert Set("dummy_service", provider, "false", "stopped")==[0],'Set("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]'
        print('GET:'+repr(Test("dummy_service", provider, "false", "stopped")))
        assert Test("dummy_service", provider, "false", "stopped")==[0],'Test("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]'

    def testTestEnableError(self):
        provider=self.provider
        assert Set("yummyservice", provider, "true", "running")==[-1],'Set("yummyservice", "'+provider+'", "true", "running") should return ==[-1]'
        print('GET:'+repr(Test("yummyservice", provider, "true", "running")[0:5]))
        assert Test("yummyservice", provider, "true", "running")==[-1],'Test("yummyservice", "'+provider+'", "true", "running") should return ==[-1]'

    def testTestDisableError(self):
        """
        It is correct for us to get back [0]
        if we ask for a non-enabled, non-existing service.
        To foce the error, we send enabled = 'true'.
        """
        provider=self.provider
        assert Set("yummyservice", provider, "false", "stopped")==[-1],'Set("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]'
        print('GET:'+repr(Test("yummyservice", provider, "false", "stopped")))
        assert Test("yummyservice", provider, "true", "stopped")==[-1],'Test("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]'


if __name__ == '__main__':
    s=unittest.TestLoader().loadTestsFromTestCase(LinuxServiceTestCases)
    unittest.TextTestRunner(verbosity=2).run(s)



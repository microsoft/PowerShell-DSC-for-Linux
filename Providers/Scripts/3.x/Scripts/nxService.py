#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================


from contextlib import contextmanager

import subprocess
import os
import sys
import glob
import codecs
import platform

# 	[key] string Name;
# 	[write,required,ValueMap{"init", "upstart", "systemd"},Values{"init","upstart","systemd"}] string Controller;
# 	[write] boolean Enabled;
# 	[write,ValueMap{"Running", "Stopped"},Values{"Running", "Stopped"}] string State;
# 	[read] string Path;

global show_mof
show_mof=False

def Set_Marshall(Name, Controller, Enabled, State):
    if Name == None:
        Name=''
    if Controller == None:
        Controller=''
    if Enabled == None:
        Enabled=False
    if State == None:
        State=''

    retval = Set(Name, Controller, Enabled, State)
    return retval

def Test_Marshall(Name, Controller, Enabled, State):
    if Name == None:
        Name=''
    if Controller == None:
        Controller=''
    if Enabled == None:
        Enabled=False
    if State == None:
        State=''

    retval = Test(Name, Controller, Enabled, State)
    return retval

def Get_Marshall(Name, Controller, Enabled, State):
    arg_names=locals().keys()
    if Name == None:
        Name=''
    if Controller == None:
        Controller=''
    if Enabled == None:
        Enabled=False
    if State == None:
        State=''

    retval = 0
    (retval, Name, Controller, Enabled, State, Path) = Get(Name, Controller, Enabled, State)

    Name = Name.encode("utf-8")
    Controller = Controller.encode("utf-8")
    Enabled = Enabled
    State = State.encode("utf-8")
    Path = Path.encode("utf-8")

    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k] 
    return retval, retd


############################################################
### Begin user defined DSC functions
############################################################

def SetShowMof(a):
    global show_mof
    show_mof=a

def ShowMof(op, Name, Controller, Enabled, State):
    if not show_mof:
        return
    mof=''
    mof+= op + ' nxService MyService'
    mof+='{\n'
    mof+='    Name = "'  + Name + '"\n'
    mof+='    Controller = "' + Controller + '"\n'
    mof+='    Enabled = ' + str(Enabled) + '\n'
    mof+='    State = "' + State + '"\n'
    mof+='}\n'
    f=open('./test_mofs.log','a')
    Print(mof,file=f)
    f.close()

def Print(s,file=sys.stdout):
    file.write(s+'\n')
    
@contextmanager
def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, encoding='utf-8' , mode=mode)
    except IOError as err:
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
    except subprocess.CalledProcessError as e :
        if chk_err :
            Print('CalledProcessError.  Error Code is ' + str(e.returncode),file=sys.stderr  )
            Print('CalledProcessError.  Command string was ' + e.cmd ,file=sys.stderr )
            Print('CalledProcessError.  Command result was ' + (e.output[:-1]).decode('latin-1'),file=sys.stderr)
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
            Print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr )
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
            Print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
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
            Print("Error: " + systemctl_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, sc.Name])

        if retval != 0:
            Print("Error: " + upstart_start_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "start"])

        if retval != 0:
            Print("Error: " + check_state_program + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    if not IsServiceRunning(sc):
        Print("Error: " +  sc.Name + " start failed: " + process_stderr,file=sys.stderr)
        return [-1]
    return [0]
 
def StopService(sc):
    if sc.Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "stop", sc.Name])

        if retval != 0:
            Print("Error: " + systemctl_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, sc.Name])

        if retval != 0:
            Print("Error: " + upstart_stop_path + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "stop"])

        if retval != 0:
            Print("Error: " + check_state_program + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    if IsServiceRunning(sc):
        Print("Error: " +  sc.Name + " stop failed: " + process_stderr,file=sys.stderr)
        return [-1]

    return [0]

def GetRunLevel():
    (process_stdout, process_stderr, retval) = Process([runlevel_path])
    
    if retval != 0:
        Print("Error: " + runlevel_path + " failed: " + process_stderr,file=sys.stderr)
        return -1

    tokens = process_stdout.split(" ")
    if len(tokens) != 2:
        Print("Error: unexpected number of tokens from " + runlevel_path + ".  stdout: " + process_stdout,file=sys.stderr)
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
        Print("runlevel " + str(runlevel) + " not found in chkconfig",file=sys.stderr)
        return False

    runlevel_tokens = tokens[runlevel].split(":")

    if len(runlevel_tokens) != 2:
        Print("Unable to determine format for chkconfig run level",file=sys.stderr)
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
        return True
    else:
        return False

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
        Print("Error: " + upstart_status_path + " failed: " + process_stderr,file=sys.stderr)
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
               Print("Error reading:/etc/init/" + sc.Name + ".conf",file=sys.stderr)
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
                Print("Error: Having trouble determining whether service " + sc.Name + " is enabled or disabled.",file=sys.stderr)
                return "Complex"
            else:
                return True
        else:
            return False

        Print("Info: Unable to find line containing 'start on' in " + sc.Name + ".conf",file=sys.stderr)
        return False
    else:
        Print("Error: conf file does not exist for service named " + sc.Name,file=sys.stderr)
        return False

def TestUpstartEnabled(sc):
    if sc.Enabled:
        currently_enabled = GetUpstartEnabled(sc)
        if sc.Enabled == True and currently_enabled == False:
            return False
        elif sc.Enabled == False and currently_enabled == True:
            return False
        elif currently_enabled == "Complex":
            Print("Info: Cannot modify 'Enabled' state for service " + sc.Name + ", conf file too complex.  Please use the File provider to write your own conf file for this service.",file=sys.stderr)
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
                return True
        return False
    else:
        check_state_program = initd_service
        check_enabled_program = initd_chkconfig
        (process_stdout, process_stderr, retval) = Process([check_enabled_program, "--list", sc.Name])

        if retval != 0:
            Print("Error: " + check_enabled_program + " failed: " + process_stderr,file=sys.stderr)
            return False

        if DetermineInitEnabled(process_stdout, runlevel):
            return True
        else:
            return False

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
        Print(process_stderr,file=sys.stderr)
        return False
    else:
        return True

def CreateSystemdService(sc):
    Print("Error: systemd services cannot be created from the service provider.  Please use the file provider to create a systemd conf file, then modify the service using this service provider.",file=sys.stderr)
    return [-1]

def ModifySystemdService(sc):
    if sc.Enabled == True:
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "enable", sc.Name + '.service'])
        
        if retval != 0:
            Print("Error: " + systemctl_path + " enable " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]
    elif sc.Enabled == False:
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "disable", sc.Name + '.service'])
        
        if retval != 0:
            Print("Error: " + systemctl_path + " disable " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", sc.Name + '.service'])
    if retval == 0:
        Print("running",file=sys.stderr)
        if sc.State and sc.State != "running":
            return StopService(sc)
            
    else:
        Print("stopped",file=sys.stderr)
        if sc.State and sc.State != "stopped":
            return StartService(sc)

    return [0]

def CreateUpstartService(sc):
    Print("Error: Upstart services cannot be created from the service provider.  Please use the file provider to create an upstart conf file, then modify the service using this service provider.",file=sys.stderr)
    return [-1]

def ModifyUpstartConfFile(sc):
    
    file_lines,error = ReadFile("/etc/init/" + sc.Name + ".conf")
    if len(file_lines) == 0 or error != None:
        Print("Error: Conf file unable to be read for service " + sc.Name,file=sys.stderr)
        return False

    outfile = ""
    start_on_exists = False

    for full_line in file_lines.splitlines():
        line = full_line.split("#")[0]  
        if "start on" in line and not start_on_exists:
            # If we got to this point, we can assume that we're allowed to modify the conf file. No need to check for a "Complex" conf file.
            start_on_exists = True
            if sc.Enabled == True:
                outfile += "start on runlevel [2345]\n"
                outfile += "stop on runlevel [!2345]\n"
            elif sc.Enabled == False:
                outfile += "stop on runlevel [0123456]\n"
        elif "stop on" in line:
            # Let the 'start on' clause of this if statement handle the insertion of 'stop on'
            pass
        else:
            outfile += full_line + "\n"

    if not start_on_exists:
        # If there was no "start on", make sure to add one
        if sc.Enabled == True:
            outfile += "start on runlevel [2345]\n"
            outfile += "stop on runlevel [!2345]\n"
        elif sc.Enabled == False:
            outfile += "stop on runlevel [0123456]\n"

    if WriteFile("/etc/init/" + sc.Name + ".conf", outfile) != None :
        Print("Error: Unable to write conf file for service " + sc.Name,file=sys.stderr)
        return False

    return True

def ModifyUpstartService(sc):
    if sc.Enabled and sc.Enabled != GetUpstartEnabled(sc):
        if not ModifyUpstartConfFile(sc):
            Print("Error: Failed to modify upstart conf file",file=sys.stderr)
            return [-1]
    
    if sc.State == "running":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, sc.Name])
        
        if retval != 0:
            if "Job is already running" not in process_stderr:
                Print("Error: " + upstart_start_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
                return [-1]
        if not IsServiceRunning(sc):
            Print("Error: " +  upstart_start_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]
    elif sc.State == "stopped":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, sc.Name])
        if retval != 0:
            if "Unknown instance" not in process_stderr:
                Print("Error: " + upstart_stop_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
                return [-1]
        if IsServiceRunning(sc):
            Print("Error: " +  upstart_stop_path + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
            return [-1]

    return [0]

def CreateInitService(sc):
    (process_stdout, process_stderr, retval) = Process([lsb_install_initd, sc.Name])
    if retval != 0:
        Print("Error: " + lsb_install_initd + " " + sc.Name + " failed: " + process_stderr,file=sys.stderr)
        return [-1]

    return ModifyInitService(sc)

def ModifyInitService(sc):
    check_state_program = initd_service
    check_enabled_program = initd_chkconfig
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc
        check_enabled_program = initd_updaterc
        if sc.Enabled == True:
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, "-f", sc.Name, "enable"])
            if retval != 0:
                Print("Error: " + check_enabled_program + " -f " + sc.Name + " on failed: " + str(process_stderr),file=sys.stderr)
                return [-1]
        elif sc.Enabled == False:
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, "-f", sc.Name, "disable"])
            if retval != 0:
                Print("Error: " + check_enabled_program + " -f " + sc.Name + " on failed: " + str(process_stderr),file=sys.stderr)
                return [-1]   
    else:
        if sc.Enabled == True:
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, sc.Name, "on"])
            if retval != 0:
                Print("Error: " + check_enabled_program + " " + sc.Name + " on failed: " + str(process_stderr),file=sys.stderr)
                return [-1]
        elif sc.Enabled == False:
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, sc.Name, "off"])
            if retval != 0:
                Print("Error: " + check_enabled_program + " " + sc.Name + " on failed: " + str(process_stderr),file=sys.stderr)
                return [-1]   

    if sc.State == "running":
        # don't try to read stdout or stderr as 'service start' comand re-directs them, causing a hang in subprocess.communicate()
        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "start"],True) 
        if retval != 0:
            Print("Error: " + check_state_program + " " + sc.Name + " start failed: " + str(process_stderr),file=sys.stderr)
            return [-1]
        if not IsServiceRunning(sc):
            Print("Error: " + check_state_program + " " + sc.Name + " start failed: " + str(process_stderr),file=sys.stderr)
            return [-1]
            
    elif sc.State == "stopped":
        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "stop"])
        if retval != 0:
            Print("Error: " + check_state_program + " " + sc.Name + " stop failed: " + str(process_stderr),file=sys.stderr)
            return [-1]
        if IsServiceRunning(sc):
            Print("Error: " + check_state_program + " " + sc.Name + " stop failed: " + str(process_stderr),file=sys.stderr)
            return [-1]

    return [0]

def IsServiceRunning(sc):
    cmd = "ps -ef | grep -v grep | grep "+  sc.Name 
    code,out=RunGetOutput(cmd,False,False)
    if code != 0:
        return False
    return True

def Set(Name, Controller, Enabled, State):
    ShowMof('SET', Name, Controller, Enabled, State)
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
    ShowMof('TEST', Name, Controller, Enabled, State)
    sc = ServiceContext(Name, Controller, Enabled, State)

    if sc.Controller == "systemd":
        return TestSystemd(sc)
    elif sc.Controller == "upstart":
        return TestUpstart(sc)
    elif sc.Controller == "init":
        return TestInit(sc)
    else:
        Print("Invalid service controller (" + sc.Controller + ",file=sys.stderr) specified for service: " + sc.Name)
        return [-1]

    return [-1]

def Get(Name, Controller, Enabled, State):
    ShowMof('GET', Name, Controller, Enabled, State)
    sc = ServiceContext(Name, Controller, Enabled, State)

    Path = ""
    exit_code = 0

    if not sc.Controller:
        Print("Error: Controller not specified",file=sys.stderr)
        exit_code = -1
    elif sc.Controller == "systemd":
        if not ServiceExistsInSystemd(sc):
            Print("Error: Unable to find service named " + sc.Name + " in systemd.",file=sys.stderr)
            exit_code = -1
        else:
            Enabled = GetSystemdEnabled(sc)
            State = GetSystemdState(sc)
            Path = "/usr/lib/systemd/system/" + sc.Name + ".service"
    elif sc.Controller == "upstart":
        if not ServiceExistsInUpstart(sc):
            Print("Error: Unable to find service named " + sc.Name + " in upstart.",file=sys.stderr)
            exit_code = -1
        else:
            temp = GetUpstartEnabled(sc)
            if temp == False:
                Enabled = False
            else:
                # When GetUpstartEnabled returns "Complex", we assume that it is enabled (and we won't modify it).
                Enabled = True
                
            State = GetUpstartState(sc)
            Path = "/etc/init/" + sc.Name + ".conf"
    elif sc.Controller == "init":
        if not ServiceExistsInInit(sc):
            Print("Error: Unable to find service named " + sc.Name + " in init.",file=sys.stderr)
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
        self.Enabled = Enabled
        self.State = State.lower()
        self.Path = ''




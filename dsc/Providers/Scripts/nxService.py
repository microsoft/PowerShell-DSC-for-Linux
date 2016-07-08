#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================

import subprocess
import shutil
import pwd
import grp
import os
import stat
import time
import datetime
import glob

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

systemctl_path = "/bin/systemctl"
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

def WriteFile(path, contents):
    try:
        f = open(path, "w")
        f.write(contents.replace("\r",""))
        return 0
    except IOError:
        return -1


def ReadFile(filename):
    if os.path.isfile(filename):
        f = open(filename, "r")
        lines = f.read().split("\n")
        return lines
    else:
        return []

def Process(params):
    process = subprocess.Popen(params, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    (process_stdout, process_stderr) = process.communicate()

    return (process_stdout.decode("utf-8"), process_stderr.decode("utf-8"), process.returncode)


def StartService(sc):
    if sc.Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "start", sc.Name])

        if retval != 0:
            print("Error: " + systemctl_path + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, sc.Name])

        if retval != 0:
            print("Error: " + upstart_start_path + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "start"])

        if retval != 0:
            print("Error: " + check_state_program + " failed: " + process_stderr)
            return [-1]

    return [0]
 
def StopService(sc):
    if sc.Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "stop", sc.Name])

        if retval != 0:
            print("Error: " + systemctl_path + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, sc.Name])

        if retval != 0:
            print("Error: " + upstart_stop_path + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "stop"])

        if retval != 0:
            print("Error: " + check_state_program + " failed: " + process_stderr)
            return [-1]

    return [0]

def GetRunLevel():
    (process_stdout, process_stderr, retval) = Process([runlevel_path])
    
    if retval != 0:
        print("Error: " + runlevel_path + " failed: " + process_stderr)
        return -1

    tokens = process_stdout.split(" ")
    if len(tokens) != 2:
        print("Error: unexpected number of tokens from " + runlevel_path + ".  stdout: " + process_stdout)
        return -1

    return int(tokens[1])

def DetermineInitState(stdout):
    if "is running" in stdout:
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
        print("runlevel " + str(runlevel) + " not found in chkconfig")
        return False

    runlevel_tokens = tokens[runlevel].split(":")

    if len(runlevel_tokens) != 2:
        print("Unable to determine format for chkconfig run level")
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
    if not TestSystemdState(sc):
        return [-1]
    if not TestSystemdEnabled(sc):
        return [-1]

    return [0]

def GetUpstartState(sc):
    (process_stdout, process_stderr, retval) = Process([upstart_status_path, sc.Name])
    
    if retval != 0:
        print("Error: " + upstart_status_path + " failed: " + process_stderr)
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
        file_lines = ReadFile("/etc/init/" + sc.Name + ".conf")

        start_on_exists = False
        start_on_is_enabled = False
        stop_on_exists = False
        stop_on_is_enabled = False
        for full_line in file_lines:
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
                print("Error: Having trouble determining whether service " + sc.Name + " is enabled or disabled.")
                return "Complex"
            else:
                return "true"
        else:
            return "false"

        print("Info: Unable to find line containing 'start on' in " + sc.Name + ".conf")
        return "false"
    else:
        print("Error: conf file does not exist for service named " + sc.Name)
        return "false"

def TestUpstartEnabled(sc):
    if sc.Enabled:
        currently_enabled = GetUpstartEnabled(sc)
        if sc.Enabled == "true" and currently_enabled == "false":
            return False
        elif sc.Enabled == "false" and currently_enabled == "true":
            return False
        elif currently_enabled == "Complex":
            print("Info: Cannot modify 'Enabled' state for service " + sc.Name + ", conf file too complex.  Please use the File provider to write your own conf file for this service.")
            return True
    return True

def TestUpstart(sc):
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
            print("Error: " + check_enabled_program + " failed: " + process_stderr)
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
    if not TestInitState(sc):
        return [-1]
    if not TestInitEnabled(sc):
        return [-1]

    return [0]

def SystemdExists():
    if os.path.isfile(systemctl_path):
        return True
    else:
        return False

def UpstartExists():
    if os.path.isfile(upstart_start_path) and os.path.isfile(upstart_stop_path) and os.path.isfile(upstart_status_path):
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
    
    if sc.Name + ".service" in process_stdout.decode('utf-8'):
        if "Loaded: not-found" in process_stdout.decode('utf-8'):
            return False
        else:
            return True
    else:
        return False
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

    if "unrecognized service" in process_stderr:
        print(process_stderr)
        return False
    else:
        return True

def CreateSystemdService(sc):
    print("Error: systemd services cannot be created from the service provider.  Please use the file provider to create a systemd conf file, then modify the service using this service provider.")
    return [-1]

def ModifySystemdService(sc):
    if sc.Enabled == "true":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "enable", sc.Name])
        
        if retval != 0:
            print("Error: " + systemctl_path + " enable " + sc.Name + " failed: " + process_stderr)
            return [-1]
    elif sc.Enabled == "false":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "disable", sc.Name])
        
        if retval != 0:
            print("Error: " + systemctl_path + " disable " + sc.Name + " failed: " + process_stderr)
            return [-1]

    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", sc.Name])
    if retval == 0:
        print("running")
        if sc.State and sc.State != "running":
            return StopService(sc)
            
    else:
        print("stopped")
        if sc.State and sc.State != "stopped":
            return StartService(sc)

    return [0]

def CreateUpstartService(sc):
    print("Error: Upstart services cannot be created from the service provider.  Please use the file provider to create an upstart conf file, then modify the service using this service provider.")
    return [-1]

def ModifyUpstartConfFile(sc):
    file_lines = ReadFile("/etc/init/" + sc.Name + ".conf")
    if len(file_lines) == 0:
        print("Error: Conf file unable to be read for service " + sc.Name)
        return False

    outfile = ""
    start_on_exists = False

    for full_line in file_lines:
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

    if WriteFile("/etc/init/" + sc.Name + ".conf", outfile) == -1:
        print("Error: Unable to write conf file for service " + sc.Name)
        return False

    return True

def ModifyUpstartService(sc):
    if sc.Enabled and sc.Enabled != GetUpstartEnabled(sc):
        if not ModifyUpstartConfFile(sc):
            print("Error: Failed to modify upstart conf file")
            return [-1]
    
    if sc.State == "running":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, sc.Name])
        
        if retval != 0:
            if "Job is already running" not in process_stderr:
                print("Error: " + upstart_start_path + " " + sc.Name + " failed: " + process_stderr)
                return [-1]
    elif sc.State == "stopped":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, sc.Name])
        if retval != 0:
            if "Unknown instance" not in process_stderr:
                print("Error: " + upstart_stop_path + " " + sc.Name + " failed: " + process_stderr)
                return [-1]

    return [0]

def CreateInitService(sc):
    (process_stdout, process_stderr, retval) = Process([lsb_install_initd, sc.Name])
    if retval != 0:
        print("Error: " + lsb_install_initd + " " + sc.Name + " failed: " + process_stderr)
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
                print("Error: " + check_enabled_program + " -f " + sc.Name + " on failed: " + process_stderr)
                return [-1]
        elif sc.Enabled == "false":
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, "-f", sc.Name, "disable"])
            if retval != 0:
                print("Error: " + check_enabled_program + " -f " + sc.Name + " on failed: " + process_stderr)
                return [-1]   
    else:
        if sc.Enabled == "true":
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, sc.Name, "on"])
            if retval != 0:
                print("Error: " + check_enabled_program + " " + sc.Name + " on failed: " + process_stderr)
                return [-1]
        elif sc.Enabled == "false":
            (process_stdout, process_stderr, retval) = Process([check_enabled_program, sc.Name, "off"])
            if retval != 0:
                print("Error: " + check_enabled_program + " " + sc.Name + " on failed: " + process_stderr)
                return [-1]   

    if sc.State == "running":
        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "start"])
        if retval != 0:
            print("Error: " + check_state_program + " " + sc.Name + " start failed: " + process_stderr)
            return [-1]
    elif sc.State == "stopped":
        (process_stdout, process_stderr, retval) = Process([check_state_program, sc.Name, "stop"])
        if retval != 0:
            print("Error: " + check_state_program + " " + sc.Name + " stop failed: " + process_stderr)
            return [-1]

    return [0]

def Set(Name, Controller, Enabled, State):
    sc = ServiceContext(Name, Controller, Enabled, State)

    if sc.Controller == "systemd":
        if ServiceExistsInSystemd(sc):
            return ModifySystemdService(sc)
        else:
            return CreateSystemdService(sc)
    elif sc.Controller == "upstart":
        if ServiceExistsInUpstart(sc):
            return ModifyUpstartService(sc)
        else:
            return CreateUpstartService(sc)
    elif sc.Controller == "init":
        if ServiceExistsInInit(sc):
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
        print("Invalid service controller (" + sc.Controller + ") specified for service: " + sc.Name)
        return [-1]

    return [-1]

def Get(Name, Controller, Enabled, State):
    sc = ServiceContext(Name, Controller, Enabled, State)

    Path = ""
    exit_code = 0

    if not sc.Controller:
        print("Error: Controller not specified")
        exit_code = -1
    elif sc.Controller == "systemd":
        if not ServiceExistsInSystemd(sc):
            print("Error: Unable to find service named " + sc.Name + " in systemd.")
            exit_code = -1
        else:
            Enabled = GetSystemdEnabled(sc)
            State = GetSystemdState(sc)
            Path = "/usr/lib/systemd/system/" + sc.Name + ".service"
    elif sc.Controller == "upstart":
        if not ServiceExistsInUpstart(sc):
            print("Error: Unable to find service named " + sc.Name + " in upstart.")
            exit_code = -1
        else:
            temp = GetUpstartEnabled(sc)
            if temp == "false":
                Enabled = "False"
            else:
                # When GetUpstartEnabled returns "Complex", we assume that it is enabled (and we won't modify it).
                Enabled = "True"
                
            State = GetUpstartState(sc)
            Path = "/etc/init/" + sc.Name + ".conf"
    elif sc.Controller == "init":
        if not ServiceExistsInInit(sc):
            print("Error: Unable to find service named " + sc.Name + " in init.")
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


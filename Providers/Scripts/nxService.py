import subprocess
import shutil
import pwd
import grp
import os
import stat
import time
import datetime

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

# TODO: These paths might differ across platforms, and we might want to check and set these properly
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

    return (process_stdout, process_stderr, process.returncode)


def StartService(Name, Controller):
    if Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "start", Name])

        if retval != 0:
            print("Error: " + systemctl_path + " failed: " + process_stderr)
            return [-1]

    elif Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, Name])

        if retval != 0:
            print("Error: " + upstart_start_path + " failed: " + process_stderr)
            return [-1]

    elif Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, Name, "start"])

        if retval != 0:
            print("Error: " + check_state_program + " failed: " + process_stderr)
            return [-1]

    return [0]
 
def StopService(Name, Controller):
    if Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "stop", Name])

        if retval != 0:
            print("Error: " + systemctl_path + " failed: " + process_stderr)
            return [-1]

    elif Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, Name])

        if retval != 0:
            print("Error: " + upstart_stop_path + " failed: " + process_stderr)
            return [-1]

    elif Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process([check_state_program, Name, "stop"])

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

def GetSystemdState(Name):
    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", Name])
    if retval == 0:
        return "Running"
    else:
        return "Stopped"

def TestSystemdState(Name, State):
    if State and State != GetSystemdState(Name):
        return False
    
    return True

def GetSystemdEnabled(Name):
    (process_stdout, process_stderr, retval) = Process([systemctl_path, "is-enabled", Name])
    if retval == 0:
        return "True"
    else:
        return "False"

def TestSystemdEnabled(Name, Enabled):
    if Enabled and Enabled != GetSystemdEnabled(Name):
        return False
    return True

def TestSystemd(Name, Enabled, State):
    if not TestSystemdState(Name, State):
        return [-1]
    if not TestSystemdEnabled(Name, Enabled):
        return [-1]

    return [0]

def GetUpstartState(Name):
    (process_stdout, process_stderr, retval) = Process([upstart_status_path, Name])
    
    if retval != 0:
        print("Error: " + upstart_status_path + " failed: " + process_stderr)
        return ""

    if (Name + " start") in process_stdout:
        return "Running"
    else:
        return "Stopped"

def TestUpstartState(Name, State):
    if State and State != GetUpstartState(Name):
        return False
    return True

def GetUpstartEnabled(Name):
    if os.path.isfile("/etc/init/" + Name + ".conf"):
        file_lines = ReadFile("/etc/init/" + Name + ".conf")

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
                    specified_runlevel_digits = line.split("[")[:-1]
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
                    specified_runlevel_digits = line.split("[")[:-1]
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
                print("Error: Having trouble determining whether service " + Name + " is enabled or disabled.")
                return "Complex"
            else:
                return "True"
        else:
            return "False"

        print("Info: Unable to find line containing 'start on' in " + Name + ".conf")
        return "False"
    else:
        print("Error: conf file does not exist for service named " + Name)
        return "False"

def TestUpstartEnabled(Name, Enabled):
    if Enabled:
        currently_enabled = GetUpstartEnabled(name)
        if Enabled == "True" and currently_enabled == "False":
            return False
        elif Enabled == "False" and currently_enabled == "True":
            return False
        elif currently_enabled == "Complex":
            print("Info: Cannot modify 'Enabled' state for service " + Name + ", conf file too complex.  Please use the File provider to write your own conf file for this service.")
            return True
    return True

def TestUpstart(Name, Enabled, State):
    if not TestUpstartState(Name, State):
        return [-1]
    if not TestUpstartEnabled(Name, Enabled):
        return [-1]
    return [0]

def GetInitState(Name):
    check_state_program = initd_service
    check_enabled_program = initd_chkconfig
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc
        check_enabled_program = initd_updaterc

    (process_stdout, process_stderr, retval) = Process([check_state_program, Name, "status"])
    
    if DetermineInitState(process_stdout):
        return "Running"
    else:
        return "Stopped"

def TestInitState(Name, State):
    if State and State != GetInitState(Name):
        return False
    return True

def GetInitEnabled(Name):
    check_state_program = initd_service
    check_enabled_program = initd_chkconfig
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc
        check_enabled_program = initd_updaterc

    (process_stdout, process_stderr, retval) = Process([check_enabled_program, "--list", Name])
    
    if retval != 0:
        print("Error: " + check_enabled_program + " failed: " + process_stderr)
        return ""

    runlevel = GetRunLevel()
    if DetermineInitEnabled(process_stdout, runlevel):
        return "True"
    else:
        return "False"

def TestInitEnabled(Name, Enabled):
    if Enabled and Enabled != GetInitEnabled(Name):
        return False
    return True

def TestInit(Name, Enabled, State):
    if not TestInitState(Name, State):
        return [-1]
    if not TestInitEnabled(Name, Enabled):
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

def ServiceExistsInSystemd(Name):
    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", Name])
    
    if Name + ".service" in process_stdout:
        if "Loaded: not-found" in process_stdout:
            return False
        else:
            return True
    else:
        return False
def ServiceExistsInUpstart(Name):
    (process_stdout, process_stderr, retval) = Process([upstart_status_path, Name])
    
    if retval != 0:
        return False
    else:
        return True

def ServiceExistsInInit(Name):
    check_state_program = initd_service
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc

    (process_stdout, process_stderr, retval) = Process([check_state_program, Name, "status"])

    if "unrecognized service" in process_stderr:
        print(process_stderr)
        return False
    else:
        return True

def CreateSystemdService(Name, Enabled, State):
    print("Error: systemd services cannot be created from the service provider.  Please use the file provider to create a systemd conf file, then modify the service using this service provider.")
    return [-1]

def ModifySystemdService(Name, Enabled, State):
    if Enabled == "True":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "enable", Name])
        
        if retval != 0:
            print("Error: " + systemctl_path + " enable " + Name + " failed: " + process_stderr)
            return [-1]
    elif Enabled == "False":
        (process_stdout, process_stderr, retval) = Process([systemctl_path, "disable", Name])
        
        if retval != 0:
            print("Error: " + systemctl_path + " disable " + Name + " failed: " + process_stderr)
            return [-1]

    (process_stdout, process_stderr, retval) = Process([systemctl_path, "status", Name])
    if retval == 0:
        print("Running")
        if State and State != "Running":
            return StartService(Name, "systemd")
            
    else:
        print("Stopped")
        if State and State != "Stopped":
            return StopService(Name, "systemd")

    return [0]

def CreateUpstartService(Name, Enabled, State):
    print("Error: Upstart services cannot be created from the service provider.  Please use the file provider to create an upstart conf file, then modify the service using this service provider.")
    return [-1]

def ModifyUpstartConfFile(Name, Enabled):
    file_lines = ReadFile("/etc/init/" + Name + ".conf")
    if len(file_lines) == 0:
        print("Error: Conf file unable to be read for service " + Name)
        return False

    outfile = ""
    start_on_exists = False

    for full_line in file_lines:
        line = full_line.split("#")[0]  
        if "start on" in line and not start_on_exists:
            # If we got to this point, we can assume that we're allowed to modify the conf file. No need to check for a "Complex" conf file.
            start_on_exists = True
            if Enabled == "True":
                outfile += "start on runlevel [2345]\n"
                outfile += "stop on runlevel [!2345]\n"
            elif Enabled == "False":
                outfile += "stop on runlevel [0123456]\n"
        elif "stop on" in line:
            # Let the 'start on' clause of this if statement handle the insertion of 'stop on'
            pass
        else:
            outfile += full_line + "\n"

    if not start_on_exists:
        # If there was no "start on", make sure to add one
        if Enabled == "True":
            outfile += "start on runlevel [2345]\n"
            outfile += "stop on runlevel [!2345]\n"
        elif Enabled == "False":
            outfile += "stop on runlevel [0123456]\n"

    if WriteFile("/etc/init/" + Name + ".conf", outfile) == -1:
        print("Error: Unable to write conf file for service " + Name)
        return False

    return True

def ModifyUpstartService(Name, Enabled, State):
    if Enabled != GetUpstartEnabled(Name):
        if not ModifyUpstartConfFile(Name, Enabled):
            print("Error: Failed to modify upstart conf file")
            return [-1]
    
    if State == "Running":
        (process_stdout, process_stderr, retval) = Process([upstart_start_path, Name])
        
        if retval != 0:
            if "Job is already running" not in process_stderr:
                print("Error: " + upstart_start_path + " " + Name + " failed: " + process_stderr)
                return [-1]
    elif State == "Stopped":
        (process_stdout, process_stderr, retval) = Process([upstart_stop_path, Name])
        if retval != 0:
            if "Unknown instance" not in process_stderr:
                print("Error: " + upstart_stop_path + " " + Name + " failed: " + process_stderr)
                return [-1]

    return [0]

def CreateInitService(Name, Enabled, State):
    (process_stdout, process_stderr, retval) = Process([lsb_install_initd, Name])
    if retval != 0:
        print("Error: " + lsb_install_initd + " " + Name + " failed: " + process_stderr)
        return [-1]

    return ModifyInitService(Name, Enabled, State)

def ModifyInitService(Name, Enabled, State):
    check_state_program = initd_service
    check_enabled_program = initd_chkconfig
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc
        check_enabled_program = initd_updaterc

    if Enabled == "True":
        (process_stdout, process_stderr, retval) = Process([check_enabled_program, Name, "on"])
        if retval != 0:
            print("Error: " + check_enabled_program + " " + Name + " on failed: " + process_stderr)
            return [-1]
    elif Enabled == "False":
        (process_stdout, process_stderr, retval) = Process([check_enabled_program, Name, "off"])
        if retval != 0:
            print("Error: " + check_enabled_program + " " + Name + " on failed: " + process_stderr)
            return [-1]   

    if State == "Running":
        (process_stdout, process_stderr, retval) = Process([check_state_program, Name, "start"])
        if retval != 0:
            print("Error: " + check_state_program + " " + Name + " start failed: " + process_stderr)
            return [-1]
    elif State == "Stopped":
        (process_stdout, process_stderr, retval) = Process([check_state_program, Name, "stop"])
        if retval != 0:
            print("Error: " + check_state_program + " " + Name + " stop failed: " + process_stderr)
            return [-1]

    return [0]

def Set(Name, Controller, Enabled, State):
    if not Name:
        print("Error: Service has no name.")

    if not Controller:
        print("Error: Controller not specified")
        return [-1]

    elif Controller == "systemd":
        if ServiceExistsInSystemd(Name):
            return ModifySystemdService(Name, Enabled, State)
        else:
            return CreateSystemdService(Name, Enabled, State)
    elif Controller == "upstart":
        if ServiceExistsInUpstart(Name):
            return ModifyUpstartService(Name, Enabled, State)
        else:
            return CreateUpstartService(Name, Enabled, State)
    elif Controller == "init":
        if ServiceExistsInInit(Name):
            return ModifyInitService(Name, Enabled, State)
        else:
            return CreateInitService(Name, Enabled, State)
    
    return [-1]

def Test(Name, Controller, Enabled, State):
    if not Name:
        print("Error: Service has no name.")
        return [-1]

    if not Controller:
        print("Error: Controller not specified")
        return [-1]

    elif Controller == "systemd":
        return TestSystemd(Name, Enabled, State)
    elif Controller == "upstart":
        return TestUpstart(Name, Enabled, State)
    elif Controller == "init":
        return TestInit(Name, Enabled, State)
    else:
        print("Invalid service controller (" + Controller + ") specified for service: " + Name)
        return [-1]

    return [-1]

def Get(Name, Controller, Enabled, State):
    Path = ""
    exit_code = 0

    if not Controller:
        print("Error: Controller not specified")
        exit_code = -1
    elif Controller == "systemd":
        if not ServiceExistsInSystemd(Name):
            print("Error: Unable to find service named " + Name + " in systemd.")
            exit_code = -1
        else:
            Enabled = GetSystemdEnabled(Name)
            State = GetSystemdState(Name)
            Path = "/usr/lib/systemd/system/" + Name + ".service"
    elif Controller == "upstart":
        if not ServiceExistsInUpstart(Name):
            print("Error: Unable to find service named " + Name + " in upstart.")
            exit_code = -1
        else:
            Enabled = GetUpstartEnabled(Name)
            State = GetUpstartState(Name)
            Path = "/etc/init/" + Name + ".conf"
    elif Controller == "init":
        if not ServiceExistsInInit(Name):
            print("Error: Unable to find service named " + Name + " in init.")
            exit_code = -1
        else:
            Enabled = GetInitEnabled(Name)
            State = GetInitState(Name)
            Path = "/etc/init.d/" + Name

    return [exit_code, Name, Controller, Enabled, State, Path]


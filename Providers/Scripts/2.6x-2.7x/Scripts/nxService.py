#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================
from __future__ import with_statement
from contextlib import contextmanager

import subprocess
import os
import sys
import glob
import codecs
import imp
import time
import copy
import re
import fnmatch
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
helperlib = imp.load_source('helperlib', '../helperlib.py')
LG = nxDSCLog.DSCLog

# [ClassVersion("1.0.0"),FriendlyName("nxService"), SupportsInventory()]
# class MSFT_nxServiceResource : OMI_BaseResource
# {
#        [key, InventoryFilter] string Name;
#        [write,required,ValueMap{"init", "upstart", "systemd"},Values{"init","upstart","systemd"}, InventoryFilter] string Controller;
#        [write, InventoryFilter] boolean Enabled;
#        [write,ValueMap{"Running", "Stopped"},Values{"Running", "Stopped"}, InventoryFilter] string State;
#        [read] string Path;
#        [read] string Description;
#        [read] string Runlevels;
# };

global show_mof
show_mof = False


def init_vars(Name, Controller, Enabled, State):
    if Name is not None:
        Name = Name.encode('ascii', 'ignore')
    else:
        Name = ''
    if Name == '*':
        Name = ''
    if Controller is not None and Controller != '*' and Controller != '':
        Controller = Controller.encode('ascii', 'ignore').lower()
    else:
        Controller = GetController()
    if Enabled is None:
        Enabled = False
    Enabled = (Enabled == True)
    if State is not None:
        State = State.encode('ascii', 'ignore').lower()
    else:
        State = ''
    return Name, Controller.lower(), Enabled, State.lower()


def Set_Marshall(Name, Controller, Enabled, State):
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        return [-1]
    (Name, Controller, Enabled, State) = init_vars(
        Name, Controller, Enabled, State)
    if Controller == '':
        return [-1]
    retval = Set(Name, Controller, Enabled, State)
    return retval


def Test_Marshall(Name, Controller, Enabled, State):
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        return [-1]
    (Name, Controller, Enabled, State) = init_vars(
        Name, Controller, Enabled, State)
    if Controller == '':
        return [-1]
    retval = Test(Name, Controller, Enabled, State)
    return retval


def Get_Marshall(Name, Controller, Enabled, State):
    arg_names = list(locals().keys())
    arg_names.append('Path')
    arg_names.append('Runlevels')
    arg_names.append('Description')
    (Name, Controller, Enabled, State) = init_vars(
        Name, Controller, Enabled, State)
    if Controller == '':
        return [-1], {}
    retval = 0
    (retval, Name, Controller, Enabled, State, Path, Description, Runlevels) = Get(
        Name, Controller, Enabled, State)

    Name = protocol.MI_String(Name)
    Controller = protocol.MI_String(Controller)
    Enabled = protocol.MI_Boolean(Enabled)
    State = protocol.MI_String(State)
    Path = protocol.MI_String(Path)
    Description = protocol.MI_String(Description)
    Runlevels = protocol.MI_String(Runlevels)

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


def Inventory_Marshall(Name, Controller, Enabled, State):
    FilterEnabled = (Enabled != None)
    (Name, Controller, Enabled, State) = init_vars(
        Name, Controller, Enabled, State)
    if Controller == '':
        return -1, {"__Inventory": {}}
    sc = ServiceContext(Name, Controller, Enabled, State)
    sc.FilterEnabled = FilterEnabled
    if not GetAll(sc):
        return -1, {"__Inventory": {}}
    for srv in sc.services_list:
        srv['Name'] = protocol.MI_String(srv['Name'])
        srv['Controller'] = protocol.MI_String(srv['Controller'])
        srv['Enabled'] = protocol.MI_Boolean(srv['Enabled'])
        if 'running' in srv['State'].lower():
            srv['State'] = protocol.MI_String('Running')
        else:
            srv['State'] = protocol.MI_String('Stopped')
        srv['Path'] = protocol.MI_String(srv['Path'])
        srv['Description'] = protocol.MI_String(srv['Description'])
        srv['Runlevels'] = protocol.MI_String(srv['Runlevels'])
    Inventory = protocol.MI_InstanceA(sc.services_list)
    retd = {}
    retd["__Inventory"] = Inventory
    return 0, retd

#
# Begin user defined DSC functions
#


def SetShowMof(a):
    global show_mof
    show_mof = a


def ShowMof(op, Name, Controller, Enabled, State):
    if not show_mof:
        return
    mof = ''
    mof += op + ' nxService MyService'
    mof += '{\n'
    mof += '    Name = "' + Name + '"\n'
    mof += '    Controller = "' + Controller + '"\n'
    mof += '    Enabled = ' + str(Enabled) + '\n'
    mof += '    State = "' + State + '"\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    Print(mof, file=f)
    LG().Log('INFO', mof)
    f.close()


def Print(s, file=sys.stdout):
    file.write(s + '\n')


@contextmanager
def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, encoding='utf-8', mode=mode)
    except IOError, err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()


def RunGetOutput(cmd, no_output, chk_err=True):
    """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT,
    trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    """
    def check_output(no_output, *popenargs, **kwargs):
        r"""Backport from subprocess module from python 2.7"""
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
            return "Command '%s' returned non-zero exit status %d" \
                   % (self.cmd, self.returncode)

    subprocess.check_output = check_output
    subprocess.CalledProcessError = CalledProcessError
    try:
        output = subprocess.check_output(
            no_output, cmd, stderr=subprocess.STDOUT, shell=True)
    except subprocess.CalledProcessError, e:
        if chk_err:
            Print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stderr)
            LG().Log(
                'ERROR', 'CalledProcessError.  Error Code is '
                + str(e.returncode))
            Print(
                'CalledProcessError.  Command string was '
                + e.cmd, file=sys.stderr)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command string was ' + e.cmd)
            Print('CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'),
                  file=sys.stderr)
            LG().Log('ERROR', 'CalledProcessError.  Command result was ' +
                     (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'))
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, \
                   e.output.decode('utf-8').encode('ascii', 'ignore')

    if no_output:
        return 0, None
    else:
        return 0, output.decode('utf-8').encode('ascii', 'ignore')


def RunGetOutputNoStderr(cmd, no_output, chk_err=True):
    """
    Wrapper for subprocess.check_output without stderr.
    Execute 'cmd'.  Returns return code and STDOUT,
    trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    """
    def check_output(no_output, *popenargs, **kwargs):
        r"""Backport from subprocess module from python 2.7"""
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
            return "Command '%s' returned non-zero exit status %d" \
                   % (self.cmd, self.returncode)

    subprocess.check_output = check_output
    subprocess.CalledProcessError = CalledProcessError
    devnull = open('/dev/null','w')
    try:
        output = subprocess.check_output(
            no_output, cmd, stderr=devnull, shell=True)
    except subprocess.CalledProcessError, e:
        if chk_err:
            Print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stderr)
            LG().Log(
                'ERROR', 'CalledProcessError.  Error Code is '
                + str(e.returncode))
            Print(
                'CalledProcessError.  Command string was '
                + e.cmd, file=sys.stderr)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command string was ' + e.cmd)
            Print('CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'),
                  file=sys.stderr)
            LG().Log('ERROR', 'CalledProcessError.  Command result was ' +
                     (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'))
        devnull.close()
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, \
                   e.output.decode('utf-8').encode('ascii', 'ignore')

    if no_output:
        return 0, None
    else:
        return 0, output.decode('utf-8').encode('ascii', 'ignore')


systemctl_path = "/usr/bin/systemctl"
upstart_start_path = "/sbin/start"
upstart_stop_path = "/sbin/stop"
upstart_status_path = "/sbin/status"
if os.path.exists('/sbin'):
    os.environ['PATH']=os.environ['PATH']+':/sbin'
code, out = RunGetOutput('which service', False, False)
initd_service = out.strip('\n')
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
    d = None
    error = None
    with opened_w_error(path, 'rb') as (F, error):
        if error:
            Print("Exception opening file " + path + " Error Code: "
                  + str(error.errno) +
                  " Error: " + error.message + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file " + path
                     + " Error Code: " + str(error.errno)
                     + " Error: " + error.message + error.strerror)
        else:
            d = F.read()
    return d, error


def WriteFile(path, contents):
    """
    Safely attempt to write data to a file,
    replacing the existing file or creating it and
    ensuring file is always closed at exit.
    Return the exception object.
    The error is None if the data was written.
    Log results to stderr.
    """
    error = None
    with opened_w_error(path, 'wb+') as (F, error):
        if error:
            Print("Exception opening file " + path +
                  " Error Code: " + str(error.errno) +
                  " Error: " + error.message + error.strerror,
                  file=sys.stderr)
            LG().Log('ERROR', "Exception opening file "
                     + path + " Error Code: " +
                     str(error.errno) + " Error: " + error.message
                     + error.strerror)
        else:
            F.write(contents)
    return error


def Process(params, no_output=False):
    line = ''
    spc = ''
    for p in params:
        line += (spc + p)
        if len(spc) is 0:
            spc = ' '
    code, out = RunGetOutput(line, no_output, False)
    return (out, out, code)


def StartService(sc):
    if sc.Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process(
            [systemctl_path, "start", sc.Name])
        if retval is not 0:
            Print("Error: " + systemctl_path + " start " + sc.Name +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log('ERROR', "Error: " + systemctl_path +
                     " start " + sc.Name + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process(
            [upstart_start_path, sc.Name])
        if retval is not 0:
            Print("Error: " + upstart_start_path +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log(
                'ERROR', "Error: " + upstart_start_path
                + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc
        (process_stdout, process_stderr, retval) = Process(
            [check_state_program, sc.Name, "start"])
        if retval is not 0:
            Print("Error: " + check_state_program +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log(
                'ERROR', "Error: " + check_state_program
                + " failed: " + process_stderr)
            return [-1]

    if not IsServiceRunning(sc):
        Print("Error: " + sc.Name + " start failed: " +
              process_stderr, file=sys.stderr)
        LG().Log('ERROR', "Error: " + sc.Name +
                 " start failed: " + process_stderr)
        return [-1]
    return [0]


def StopService(sc):
    if sc.Controller == "systemd":
        (process_stdout, process_stderr, retval) = Process(
            [systemctl_path, "stop", sc.Name])

        if retval is not 0:
            Print("Error: " + systemctl_path + " failed: " +
                  process_stderr, file=sys.stderr)
            LG().Log(
                'ERROR', "Error: " + systemctl_path
                + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "upstart":
        (process_stdout, process_stderr, retval) = Process(
            [upstart_stop_path, sc.Name])

        if retval is not 0:
            Print("Error: " + upstart_stop_path +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log(
                'ERROR', "Error: " + upstart_stop_path
                + " failed: " + process_stderr)
            return [-1]

    elif sc.Controller == "init":
        check_state_program = initd_service
        if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
            check_state_program = initd_invokerc

        (process_stdout, process_stderr, retval) = Process(
            [check_state_program, sc.Name, "stop"])

        if retval is not 0:
            Print("Error: " + check_state_program +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log(
                'ERROR', "Error: " + check_state_program
                + " failed: " + process_stderr)
            return [-1]

    if IsServiceRunning(sc):
        Print("Error: " + sc.Name + " stop failed: " +
              process_stderr, file=sys.stderr)
        LG().Log('ERROR', "Error: " + sc.Name +
                 " stop failed: " + process_stderr)
        return [-1]

    return [0]


def GetRunLevel():
    (process_stdout, process_stderr, retval) = Process([runlevel_path])

    if retval is not 0:
        Print("Error: " + runlevel_path + " failed: " +
              process_stderr, file=sys.stderr)
        LG().Log(
            'ERROR', "Error: " + runlevel_path + " failed: " + process_stderr)
        return -1

    tokens = process_stdout.split(" ")
    if len(tokens) is not 2:
        Print("Error: unexpected number of tokens from " +
              runlevel_path + ".  stdout: " + process_stdout, file=sys.stderr)
        LG().Log('ERROR', "Error: unexpected number of tokens from " +
                 runlevel_path + ".  stdout: " + process_stdout)
        return -1

    return int(tokens[1])


def DetermineInitState(stdout):
    if "is running" in stdout or "start/running" in stdout \
          or "..running" in stdout:
        return True
    elif stdout.strip() == "running":
        return True
    elif "(running)" in stdout:
        return True
    else:
        return False


def DetermineInitEnabled(stdout, runlevel):
    tokens = stdout.split()
    tokens = tokens[1:]

    if runlevel > (len(tokens) - 1):
        Print("runlevel " + str(runlevel) +
              " not found in chkconfig", file=sys.stderr)
        LG().Log(
            'ERROR', "runlevel " + str(runlevel) + " not found in chkconfig")
        return False

    runlevel_tokens = tokens[runlevel].split(":")

    if len(runlevel_tokens) is not 2:
        Print(
            "Unable to determine format for chkconfig run level",
            file=sys.stderr)
        LG().Log(
            'ERROR', "Unable to determine format for chkconfig run level")
        return False

    if runlevel_tokens[1] == "on":
        return True
    else:
        return False


def GetSystemdState(sc):
    (process_stdout, process_stderr, retval) = Process(
        [systemctl_path, "status", sc.Name])
    if retval is 0:
        if '(running)' in process_stdout:
            return "running"
    return "stopped"


def TestSystemdState(sc):
    if sc.State and sc.State != GetSystemdState(sc):
        return False

    return True


def GetSystemdEnabled(sc):
    (process_stdout, process_stderr, retval) = Process(
        [systemctl_path, "is-enabled", sc.Name])
    if retval is 0:
        return True
    else:
        return False


def TestSystemdEnabled(sc):
    if sc.Enabled is not GetSystemdEnabled(sc):
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
    (process_stdout, process_stderr, retval) = Process(
        [upstart_status_path, sc.Name])

    if retval is not 0:
        Print("Error: " + upstart_status_path +
              " failed: " + process_stderr, file=sys.stderr)
        LG().Log('ERROR', "Error: " + upstart_status_path +
                 " failed: " + process_stderr)
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
        start_on_exists = False
        start_on_is_enabled = False
        stop_on_exists = False
        stop_on_is_enabled = False
        file_lines, error = ReadFile("/etc/init/" + sc.Name + ".conf")
        if error is not None:
            Print(
                "Error reading:/etc/init/" + sc.Name + ".conf",
                file=sys.stderr)
            LG().Log('ERROR', "Error reading:/etc/init/" +
                     sc.Name + ".conf")
            return "Error"
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

        if not start_on_exists and not stop_on_exists:   # not upstart
            if os.path.islink('/etc/init.d/' + sc.Name) and \
                   os.readlink('/etc/init.d/' + sc.Name) \
                   == '/lib/init/upstart-job':
                # this is a 'converted' init script, check the default rc2.d
                # for smylink to conf file. if so its enabled.
                file_list = os.listdir('/etc/rc2.d')
                for f in file_list:
                    f = '/etc/rc2.d/' + f
                    if os.path.islink(f) and os.readlink(f) == \
                           "../init.d/" + sc.Name:
                        return True
                return False
            (process_stdout, process_stderr, retval) = Process(
                ['chkconfig', sc.Name, ''])  # try init style
            if retval is 0:
                if 'off' not in process_stdout:
                    return True
            return False
        if start_on_exists and start_on_is_enabled:
            if stop_on_exists and stop_on_is_enabled:
                Print("Error: Having trouble determining whether service " +
                      sc.Name + " is enabled or disabled.", file=sys.stderr)
                LG().Log('ERROR',
                         "Error: Having trouble determining whether service " +
                         sc.Name + " is enabled or disabled.")
                return "Complex"
            else:
                return True
        else:
            return False

        Print("Error: Unable to find line containing 'start on' in " +
              sc.Name + ".conf", file=sys.stderr)
        LG().Log('ERROR',
                 "Error: Unable to find line containing 'start on' in " +
                 sc.Name + ".conf")
        return False
    else:
        Print("Error: conf file does not exist for service named " +
              sc.Name, file=sys.stderr)
        LG().Log('ERROR',
                 "Error: conf file does not exist for service named " +
                 sc.Name)
        return False


def TestUpstartEnabled(sc):
    currently_enabled = GetUpstartEnabled(sc)
    if currently_enabled == "Complex":
        Print("Error: Cannot modify 'Enabled' state for service " + sc.Name +
              ", conf file too complex.  Please use the File provider to " +
              "write your own conf file for this service.", file=sys.stderr)
        LG().Log('ERROR', "Error: Cannot modify 'Enabled' state for service "
                 + sc.Name +
                 ", conf file too complex.  Please use the File provider to " +
                 " writeyour own conf file for this service.")
        return False
    return currently_enabled


def TestUpstart(sc):
    if not UpstartExists():
        return [-1]
    if not TestUpstartState(sc):
        return [-1]
    if sc.Enabled is not TestUpstartEnabled(sc):
        return [-1]
    return [0]


def GetInitState(sc):
    check_state_program = initd_service
    # debian style init. These are missing in redhat.
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_service
        if os.path.isfile(initd_service):
            check_state_program = initd_service
        else:  # invoke the service directly
            check_state_program = '/etc/init.d/'
    if check_state_program == '/etc/init.d/':
        (process_stdout, process_stderr, retval) = Process(
            [check_state_program + sc.Name, "status"], True)
        if retval is not 0:
            Print("Error: " + check_state_program +
                  sc.Name + " status failed: ", file=sys.stderr)
            LG().Log('ERROR', "Error: " + check_state_program +
                     sc.Name + " status failed: ")
            if IsServiceRunning(sc):
                return "running"
            else:
                return "stopped"
    else:
        (process_stdout, process_stderr, retval) = Process(
            [check_state_program, sc.Name, "status"])
    if retval is not 0:
        if IsServiceRunning(sc):
            return "running"
        else:
            return "stopped"
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
        # A service is enabled if a symbolic link
        # exists in /etc/rc${RUNLEVEL}.d/ with the name:
        #    S??${sc.Name}
        matched_files = glob.glob(
            "/etc/rc" + str(runlevel) + ".d/S??" + sc.Name)
        for f in matched_files:
            if os.path.islink(f):
                return True
        return False
    else:
        check_enabled_program = initd_chkconfig
        (process_stdout, process_stderr, retval) = Process(
            [check_enabled_program, "--list", sc.Name])

        if retval is not 0:
            Print("Error: " + check_enabled_program +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log('ERROR', "Error: " + check_enabled_program +
                     " failed: " + process_stderr)
            return False

        if DetermineInitEnabled(process_stdout, runlevel):
            return True
        else:
            return False


def TestInitEnabled(sc):
    if sc.Enabled is not GetInitEnabled(sc):
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
    code, out = RunGetOutput('which systemctl', False, False)
    if code is 0:
        systemctl_path = out.strip()
        return True
    else:
        return False


def UpstartExists():
    if (os.path.isfile('/sbin/upstart-local-bridge')
        or os.path.isfile('/sbin/upstart-udev-bridge')) \
        and os.path.isfile(upstart_start_path) \
        and os.path.isfile(upstart_stop_path) \
        and os.path.isfile(upstart_status_path):
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
    (process_stdout, process_stderr, retval) = Process(
        [systemctl_path, "status", sc.Name])
    if retval is not 0:
        if "Loaded: loaded" in process_stdout:
            return True
        else:
            return False
    else:
        return True


def ServiceExistsInUpstart(sc):
    (process_stdout, process_stderr, retval) = Process(
        [upstart_status_path, sc.Name])

    if retval is not 0:
        return False
    else:
        return True


def ServiceExistsInInit(sc):
    check_state_program = initd_service
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        check_state_program = initd_invokerc

    (process_stdout, process_stderr, retval) = Process(
        [check_state_program, sc.Name, "status"])

    if "unrecognized service" in process_stderr \
           or "no such service" in process_stderr \
           or "not found" in process_stderr:
        Print(process_stderr, file=sys.stderr)
        LG().Log('INFO', process_stderr)
        return False
    else:
        return True


def CreateSystemdService(sc):
    Print("Error: systemd services cannot be created from the service " +
          "provider.  Please use the file provider to create a systemd " +
          "conf file, then modify the service using this service provider.",
          file=sys.stderr)
    LG().Log('ERROR',
             "Error: systemd services cannot be created from the service provider.  \
             Please use the file provider to create a systemd conf file, \
             then modify the service using this service provider.")
    return [-1]


def ModifySystemdService(sc):
    if sc.Enabled is True:
        (process_stdout, process_stderr, retval) = Process(
            [systemctl_path, "enable", sc.Name + '.service'])
        if retval is not 0:
            Print("Error: " + systemctl_path + " enable " + sc.Name +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log('ERROR', "Error: " + systemctl_path +
                     " enable " + sc.Name + " failed: " + process_stderr)
            return [-1]
    elif sc.Enabled is False:
        (process_stdout, process_stderr, retval) = Process(
            [systemctl_path, "disable", sc.Name + '.service'])
        if retval is not 0:
            Print("Error: " + systemctl_path + " disable " + sc.Name +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log('ERROR', "Error: " + systemctl_path +
                     " disable " + sc.Name + " failed: " + process_stderr)
            return [-1]

    (process_stdout, process_stderr, retval) = Process(
        [systemctl_path, "status", sc.Name + '.service'])
    # retval may be non zero even if service exists for 'status'.
    if 'No such file or directory' in process_stdout:
        Print("Error: " + systemctl_path + " status " + sc.Name +
              " failed: " + process_stderr, file=sys.stderr)
        LG().Log('ERROR', "Error: " + systemctl_path +
                 " status " + sc.Name + " failed: " + process_stderr)
        return [-1]
    if 'Active: active' in process_stdout:
        Print("Running", file=sys.stderr)
        LG().Log('INFO', "Running")
        if sc.State and sc.State != "running":
            return StopService(sc)
    else:
        Print("Stopped", file=sys.stderr)
        LG().Log('INFO', "Stopped")
        if sc.State and sc.State != "stopped":
            return StartService(sc)
    return [0]


def CreateUpstartService(sc):
    Print("Error: Upstart services cannot be created from the service " +
          "provider.  Please use the file provider to create an upstart " +
          "conf file, then modify the service using this service provider.",
          file=sys.stderr)
    LG().Log('ERROR',
             "Error: Upstart services cannot be created from the service " +
             "provider.  Please use the file provider to create an upstart " +
             "conf file, then modify the service using this service provider.")
    return [-1]


def ModifyUpstartConfFile(sc):
    if os.path.isfile("/etc/init/" + sc.Name + ".conf"):
        file_lines, error = ReadFile("/etc/init/" + sc.Name + ".conf")
        if len(file_lines) is 0 or error is not None:
            Print("Error: Conf file unable to be read for service " +
                  sc.Name, file=sys.stderr)
            LG().Log(
                'ERROR', "Error: Conf file unable to be read for service " +
                sc.Name)
            return False

        outfile = ""
        start_on_exists = False
        stop_on_exists = False

        for full_line in file_lines.splitlines():
            line = full_line.split("#")[0]
            if "start on" in line or "stop on" in line and not start_on_exists:
                # If we got to this point, we can assume that we're allowed to
                # modify the conf file. No need to check for a "Complex" conf
                # file.
                start_on_exists = True
                if sc.Enabled is True:
                    outfile += "start on runlevel [2345]\n"
                    outfile += "stop on runlevel [!2345]\n"
                elif sc.Enabled is False:
                    outfile += "stop on runlevel [0123456]\n"
            elif "start on" in line or "stop on" in line and start_on_exists:
                continue  # its xtra now
            else:
                outfile += full_line + "\n"

        if start_on_exists or stop_on_exists:
            if WriteFile("/etc/init/" + sc.Name + ".conf", outfile) \
                   is not None:
                Print(
                    "Error: Unable to write conf file for service " + sc.Name,
                    file=sys.stderr)
                LG().Log(
                    'ERROR', "Error: Unable to write conf file for service " +
                    sc.Name)
                return False
            return True
    else:  # not an upstart service
        if os.path.islink('/etc/init.d/' + sc.Name) \
               and os.readlink('/etc/init.d/' + sc.Name) \
               == '/lib/init/upstart-job':
            # this is a 'converted' init script, check the default rc[2345].d
            # for smylink to conf file. if so its enabled.
            for rc in range(2, 6):
                file_list = os.listdir('/etc/rc' + str(rc) + '.d')
                found = False
                for f in file_list:
                    f = '/etc/rc' + str(rc) + '.d/' + f
                    if os.path.islink(f) and os.readlink(f) \
                           == "../init.d/" + sc.Name:
                        found = True
                        break
                if sc.Enabled is True:
                    if not found:
                        # create the symlink
                        os.symlink(
                            "../init.d/" + sc.Name, "/etc/rc2.d/S22" + sc.Name)
                        return True
                else:
                    if found:
                        os.unlink(f)
                        return True
        if sc.Enabled is True:
            (process_stdout, process_stderr, retval) = Process(
                ['update-rc.d', sc.Name, ' defaults'])
            if retval is not 0:
                Print("Error: " + process_stdout + " enable " +
                      sc.Name + " failed: " + process_stderr, file=sys.stderr)
                LG().Log('ERROR', "Error: " + process_stdout +
                         " enable " + sc.Name + " failed: " + process_stderr)
                return False
        else:
            (process_stdout, process_stderr, retval) = Process(
                ['update-rc.d -f ', sc.Name, ' remove'])
            if retval is not 0:
                Print("Error: " + process_stdout + " disable " +
                      sc.Name + " failed: " + process_stderr, file=sys.stderr)
                LG().Log('ERROR', "Error: " + process_stdout +
                         " disable " + sc.Name + " failed: " + process_stderr)
                return False
        return True


def ModifyUpstartService(sc):
    if sc.Enabled is not TestUpstartEnabled(sc):
        if not ModifyUpstartConfFile(sc):
            Print("Error: Failed to modify upstart conf file", file=sys.stderr)
            LG().Log('ERROR', "Error: Failed to modify upstart conf file")
            return [-1]

    if sc.State == "running":
        (process_stdout, process_stderr, retval) = Process(
            [upstart_start_path, sc.Name])

        if retval is not 0:
            if "Job is already running" not in process_stderr:
                Print("Error: " + upstart_start_path + " " + sc.Name +
                      " failed: " + process_stderr, file=sys.stderr)
                LG().Log('ERROR', "Error: " + upstart_start_path +
                         " " + sc.Name + " failed: " + process_stderr)
                return [-1]
        if not IsServiceRunning(sc):
            Print("Error: " + upstart_start_path + " " + sc.Name +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log('ERROR', "Error: " + upstart_start_path +
                     " " + sc.Name + " failed: " + process_stderr)
            return [-1]
    elif sc.State == "stopped":
        (process_stdout, process_stderr, retval) = Process(
            [upstart_stop_path, sc.Name])
        if retval is not 0:
            if "Unknown instance" not in process_stderr:
                Print("Error: " + upstart_stop_path + " " + sc.Name +
                      " failed: " + process_stderr, file=sys.stderr)
                LG().Log('ERROR', "Error: " + upstart_stop_path +
                         " " + sc.Name + " failed: " + process_stderr)
                return [-1]
        if IsServiceRunning(sc):
            Print("Error: " + upstart_stop_path + " " + sc.Name +
                  " failed: " + process_stderr, file=sys.stderr)
            LG().Log('ERROR', "Error: " + upstart_stop_path +
                     " " + sc.Name + " failed: " + process_stderr)
            return [-1]

    return [0]


def CreateInitService(sc):
    (process_stdout, process_stderr, retval) = Process(
        [lsb_install_initd, sc.Name])
    if retval is not 0:
        Print("Error: " + lsb_install_initd + " " + sc.Name +
              " failed: " + process_stderr, file=sys.stderr)
        LG().Log('ERROR', "Error: " + lsb_install_initd +
                 " " + sc.Name + " failed: " + process_stderr)
        return [-1]

    return ModifyInitService(sc)


def ModifyInitService(sc):
    check_state_program = initd_service
    check_enabled_program = initd_chkconfig
    # debian style init. These are missing in redhat.
    if os.path.isfile(initd_invokerc) and os.path.isfile(initd_updaterc):
        if os.path.isfile(initd_service):
            check_state_program = initd_service
        else:  # invoke the service directly
            check_state_program = '/etc/init.d/'
        check_enabled_program = initd_updaterc
        if sc.Enabled is True:
            (process_stdout, process_stderr, retval) = Process(
                [check_enabled_program, "-f", sc.Name, "enable"])
            if retval is not 0:
                Print("Error: " + check_enabled_program + " -f " +
                      sc.Name + " enable failed: " + process_stderr,
                      file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_enabled_program +
                         " -f " + sc.Name + " enable failed: " + process_stderr)
                # try 'defaults'
                (process_stdout, process_stderr, retval) = Process(
                [check_enabled_program, "-f", sc.Name, "defaults"])
                if retval is not 0:
                    Print("Error: " + check_enabled_program + " -f " +
                          sc.Name + " defaults failed: " + process_stderr,
                          file=sys.stderr)
                    LG().Log('ERROR', "Error: " + check_enabled_program +
                             " -f " + sc.Name + " defaults failed: " + process_stderr)
                    return [-1]
                if 'already exist' in process_stdout:  # we need to remove them first
                    (process_stdout, process_stderr, retval) = Process(
                        [check_enabled_program, "-f", sc.Name, "remove"])
                    if retval is not 0:
                        Print("Error: " + check_enabled_program + " -f " +
                              sc.Name + " remove failed: " + process_stderr,
                              file=sys.stderr)
                        LG().Log('ERROR', "Error: " + check_enabled_program +
                                 " -f " + sc.Name + " remove failed: " + process_stderr)
                        return [-1]
                    # it should work now
                    (process_stdout, process_stderr, retval) = Process(
                        [check_enabled_program, "-f", sc.Name, "defaults"])
                    if retval is not 0:
                        Print("Error: " + check_enabled_program + " -f " +
                              sc.Name + " defaults failed: " + process_stderr,
                              file=sys.stderr)
                        LG().Log('ERROR', "Error: " + check_enabled_program +
                                 " -f " + sc.Name + " defaults failed: " + process_stderr)
                        return [-1]
        elif sc.Enabled is False:
            (process_stdout, process_stderr, retval) = Process(
                [check_enabled_program, "-f", sc.Name, "disable"])
            if retval is not 0:
                Print("Error: " + check_enabled_program + " -f " +
                      sc.Name + " disable failed: " + process_stderr,
                      file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_enabled_program +
                         " -f " + sc.Name + " disable failed: " + process_stderr)
                # try remove
                (process_stdout, process_stderr, retval) = Process(
                    [check_enabled_program, "-f", sc.Name, "remove"])
                if retval is not 0:
                    Print("Error: " + check_enabled_program + " -f " +
                          sc.Name + " remove failed: " + process_stderr,
                          file=sys.stderr)
                    LG().Log('ERROR', "Error: " + check_enabled_program +
                             " -f " + sc.Name + " remove failed: " + process_stderr)
                    return [-1]
    else:
        if sc.Enabled is True:
            (process_stdout, process_stderr, retval) = Process(
                [check_enabled_program, sc.Name, "on"])
            if retval is not 0:
                Print("Error: " + check_enabled_program + " " + sc.Name +
                      " on failed: " + process_stderr, file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_enabled_program +
                         " " + sc.Name + " on failed: " + process_stderr)
                # try 'defaults'
                (process_stdout, process_stderr, retval) = Process(
                [check_enabled_program, "-f", sc.Name, "defaults"])
                if retval is not 0:
                    Print("Error: " + check_enabled_program + " -f " +
                          sc.Name + " defaults failed: " + process_stderr,
                          file=sys.stderr)
                    LG().Log('ERROR', "Error: " + check_enabled_program +
                             " -f " + sc.Name + " defaults failed: " + process_stderr)
                    return [-1]
                if 'already exist' in process_stdout:  # we need to remove them first
                    (process_stdout, process_stderr, retval) = Process(
                        [check_enabled_program, "-f", sc.Name, "remove"])
                    if retval is not 0:
                        Print("Error: " + check_enabled_program + " -f " +
                              sc.Name + " remove failed: " + process_stderr,
                              file=sys.stderr)
                        LG().Log('ERROR', "Error: " + check_enabled_program +
                                 " -f " + sc.Name + " remove failed: " + process_stderr)
                        return [-1]
                    # it should work now
                    (process_stdout, process_stderr, retval) = Process(
                        [check_enabled_program, "-f", sc.Name, "defaults"])
                    if retval is not 0:
                        Print("Error: " + check_enabled_program + " -f " +
                              sc.Name + " defaults failed: " + process_stderr,
                              file=sys.stderr)
                        LG().Log('ERROR', "Error: " + check_enabled_program +
                                 " -f " + sc.Name + " defaults failed: " + process_stderr)
                        return [-1]

        elif sc.Enabled is False:
            (process_stdout, process_stderr, retval) = Process(
                [check_enabled_program, sc.Name, "off"])
            if retval is not 0:
                Print("Error: " + check_enabled_program + " " + sc.Name +
                      " off failed: " + process_stderr, file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_enabled_program +
                         " " + sc.Name + " off failed: " + process_stderr)
                # try remove
                (process_stdout, process_stderr, retval) = Process(
                    [check_enabled_program, "-f", sc.Name, "remove"])
                if retval is not 0:
                    Print("Error: " + check_enabled_program + " -f " +
                          sc.Name + " remove failed: " + process_stderr,
                          file=sys.stderr)
                    LG().Log('ERROR', "Error: " + check_enabled_program +
                             " -f " + sc.Name + " remove failed: " + process_stderr)
                    return [-1]

    if sc.State == "running":
        # don't try to read stdout or stderr as 'service start' comand
        # re-directs them, causing a hang in subprocess.communicate()
        if check_state_program == '/etc/init.d/':
            (process_stdout, process_stderr, retval) = Process(
                [check_state_program + sc.Name, "start"], True)
            if retval is not 0:
                Print("Error: " + check_state_program +
                      sc.Name + " start failed: ", file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_state_program +
                         sc.Name + " start failed: ")
                return [-1]
        else:
            (process_stdout, process_stderr, retval) = Process(
                [check_state_program, sc.Name, "start"], True)
            if retval is not 0:
                Print("Error: " + check_state_program + " " +
                      sc.Name + " start failed: ", file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_state_program +
                         " " + sc.Name + " start failed: ")
                return [-1]
        if not IsServiceRunning(sc):
            Print("Error: " + check_state_program + " " +
                  sc.Name + " start failed: ", file=sys.stderr)
            LG().Log('ERROR', "Error: " + check_state_program +
                     " " + sc.Name + " start failed: ")
            return [-1]

    elif sc.State == "stopped":
        if check_state_program == '/etc/init.d/':
            (process_stdout, process_stderr, retval) = Process(
                [check_state_program + sc.Name, "stop"], True)
            if retval is not 0:
                Print("Error: " + check_state_program +
                      sc.Name + " stop failed: ", file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_state_program +
                         sc.Name + " stop failed: ")
                return [-1]
        else:
            (process_stdout, process_stderr, retval) = Process(
                [check_state_program, sc.Name, "stop"])
            if retval is not 0:
                Print("Error: " + check_state_program + " " + sc.Name +
                      " stop failed: " + process_stderr, file=sys.stderr)
                LG().Log('ERROR', "Error: " + check_state_program +
                         " " + sc.Name + " stop failed: " + process_stderr)
                return [-1]
        if IsServiceRunning(sc):
            Print("Error: " + check_state_program + " " + sc.Name +
                  " stop failed: " + process_stderr, file=sys.stderr)
            LG().Log('ERROR', "Error: " + check_state_program +
                     " " + sc.Name + " stop failed: " + process_stderr)
            return [-1]

    return [0]


def IsServiceRunning(sc):
    time.sleep(1)
    cmd = 'ps -ef | grep -v grep | grep -E ".*( ' + \
        sc.Name + '|/' + sc.Name + ')(\..*?|.?)( |$)"'
    code, out = RunGetOutput(cmd, False, False)
    if code is not 0:
        return False
    return True


def Set(Name, Controller, Enabled, State):
    ShowMof('SET', Name, Controller, Enabled, State)
    sc = ServiceContext(Name, Controller, Enabled, State)
    if sc.Controller == "systemd":
        if SystemdExists() is True:
            if ServiceExistsInSystemd(sc):
                return ModifySystemdService(sc)
            else:
                return CreateSystemdService(sc)
    elif sc.Controller == "upstart":
        if UpstartExists() is True:
            if ServiceExistsInUpstart(sc):
                return ModifyUpstartService(sc)
            else:
                return CreateUpstartService(sc)
    elif sc.Controller == "init":
        if InitExists() is True:
            if ServiceExistsInInit(sc):
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
        Print("Invalid service controller (" + sc.Controller +
              ") specified for service: " + sc.Name, file=sys.stderr)
        LG().Log('ERROR', "Invalid service controller (" +
                 sc.Controller + ") specified for service: " + sc.Name)
        return [-1]

    return [-1]


def Get(Name, Controller, Enabled, State):
    ShowMof('GET', Name, Controller, Enabled, State)
    sc = ServiceContext(Name, Controller, Enabled, State)

    Path = ""
    exit_code = 0

    if not sc.Controller:
        Print("Error: Controller not specified.", file=sys.stderr)
        LG().Log('ERROR', "Error: Controller not specified.")
        exit_code = -1
    elif sc.Controller == "systemd":
        if not ServiceExistsInSystemd(sc):
            Print("Error: Unable to find service named " +
                  sc.Name + " in systemd.", file=sys.stderr)
            LG().Log(
                'ERROR', "Error: Unable to find service named " +
                sc.Name + " in systemd.")
            exit_code = -1
        else:
            Enabled = GetSystemdEnabled(sc)
            State = GetSystemdState(sc)
            Path = "/usr/lib/systemd/system/" + sc.Name + ".service"
    elif sc.Controller == "upstart":
        if not ServiceExistsInUpstart(sc):
            Print("Error: Unable to find service named " +
                  sc.Name + " in upstart.", file=sys.stderr)
            LG().Log(
                'ERROR', "Error: Unable to find service named " +
                sc.Name + " in upstart.")
            exit_code = -1
        else:
            temp = GetUpstartEnabled(sc)
            if temp is False:
                Enabled = False
            else:
                # When GetUpstartEnabled returns "Complex", we assume that it
                # is enabled (and we won't modify it).
                Enabled = True

            State = GetUpstartState(sc)
            Path = "/etc/init/" + sc.Name + ".conf"
    elif sc.Controller == "init":
        if not ServiceExistsInInit(sc):
            Print("Error: Unable to find service named " +
                  sc.Name + " in init.", file=sys.stderr)
            LG().Log(
                'ERROR', "Error: Unable to find service named " +
                sc.Name + " in init.")
            exit_code = -1
        else:
            Enabled = GetInitEnabled(sc)
            State = GetInitState(sc)
            Path = "/etc/init.d/" + sc.Name
        GetOne(sc)
    return [exit_code, Name, Controller, Enabled, State, Path, sc.Description, sc.Runlevels]


def GetOne(sc):
    GetAll(sc)
    if len(sc.services_list):
        sc.Description = sc.services_list[0]['Description']
        sc.Runlevels = sc.services_list[0]['Runlevels']


def GetAll(sc):
    if sc.Controller == 'init':
        return InitdGetAll(sc)
    if sc.Controller == 'systemd':
        return SystemdGetAll(sc)
    if sc.Controller == 'upstart':
        return UpstartGetAll(sc)


def GetRunlevels(sc, Name):
    if sc.runlevels_d == None:
        sc.runlevels_d = {}
        cmd = "file /etc/rc*.d/* | grep link | awk '{print $5,$1}' | sort"
        code, out = RunGetOutput(cmd, False, False)
        for line in out.splitlines():
            line = line.replace("'", '')
            srv = line.split(' ')[0]
            rl = line.split(' ')[1]
            n = os.path.basename(srv)
            if n not in sc.runlevels_d.keys():
                sc.runlevels_d[n] = {}
            if 'Path' not in sc.runlevels_d[n].keys():
                sc.runlevels_d[n]['Path'] = srv.replace('..', '/etc')
            if 'Runlevels' not in sc.runlevels_d[n].keys():
                sc.runlevels_d[n]['Runlevels'] = ''
            s = 'off'
            if rl[11].lower() == 's':
                s = 'on'
            sc.runlevels_d[n]['Runlevels'] += rl[7] + ':' + s + ' '
    if Name in sc.runlevels_d.keys():
        return sc.runlevels_d[Name]
    return None


def SystemdGetAll(sc):
    d = {}
    if os.system('which systemctl') != 0:
        Print("Error: 'Controller' = " + sc.Controller +
              " is incorrectly specified.", file=sys.stderr)
        LG().Log('ERROR', "Error: 'Controller' = " +
           sc.Controller + " is incorrectly specified.")
        return False
    Name = sc.Name
    if '*' not in Name and '?' not in Name and len(Name) > 0:
        Name = Name.replace('.service', '')
        Name += '.service'
    # Do the commands work?
    # There may be no error detected in our multi-pipe command below.
    # To keep from returning garbage, we must test the commands.
    # RunGetOutput(chk_err = True) will log the error message here if it
    # occurs.
    cmd = 'systemctl -a list-unit-files ' + Name
    code, txt = RunGetOutputNoStderr(cmd, False, True)
    if code != 0:
        return False
    sname = ''
    # Get the last service name from the output.
    m = re.search(r'.*?\n(.*?)[.]service.*?\n', txt, re.M)
    if m is not None:
        sname = m.group(1)
    cmd = 'systemctl -a --no-pager --no-legend -p "Names,WantedBy,Description,SubState,FragmentPath,UnitFileState" show ' + sname
    code, txt = RunGetOutputNoStderr(cmd, False, True)
    if code != 0: 
        return False
    # Now we know it will work.
    cmd = 'systemctl -a list-unit-files ' + Name +  '| grep \.service | grep -v "@" | awk \'{print $1}\' | xargs systemctl -a --no-pager --no-legend -p "Names,WantedBy,Description,SubState,FragmentPath,UnitFileState" show'
    code, txt = RunGetOutputNoStderr(cmd, False, False)
    txt=txt.replace('\n\n','@@')
    txt=txt.replace('\n','|')
    services=txt.split('@@')
    subs=re.compile(r'(.*?=)')
    for srv in services:
        if len(srv) == 0:
            continue
        s=srv.split('|')
        d['Name'] = subs.sub('',s[0].replace('.service',''))
        d['Controller'] =  sc.Controller
        d['Description'] =subs.sub('',s[2])
        d['State'] = subs.sub('',s[3])
        if len(sc.State) and sc.State != d['State'].lower():
            continue
        d['Path'] = subs.sub('',s[4])
        d['Enabled'] = 'enabled' in subs.sub('',s[5])
        if sc.FilterEnabled and sc.Enabled != d['Enabled']:
            continue
        rld=GetRunlevels(sc,d['Name'])
        if rld != None and 'Runlevels' in rld.keys():
            d['Runlevels'] = rld['Runlevels']
        else:
            d['Runlevels'] = subs.sub('',s[1])
        sc.services_list.append(copy.deepcopy(d))
    return True

def UpstartGetAll(sc):
    d={}
    names={}
    if os.system('which initctl') != 0:
        Print("Error: 'Controller' = " + sc.Controller + " is incorrectly specified.", file=sys.stderr)
        LG().Log('ERROR', "Error: 'Controller' = " + sc.Controller + " is incorrectly specified.")
        return False
    # Do the commands work?
    # There may be no error detected in our multi-pipe command below.
    # To keep from returning garbage, we must test the commands.
    # RunGetOutput(chk_err = True) will log the error message here if it occurs.
    cmd = 'initctl list'
    code, txt = RunGetOutputNoStderr(cmd, False, True)
    if code != 0: 
        return False
    cmd = initd_service + ' --status-all'
    code, txt = RunGetOutputNoStderr(cmd, False, True)
    if code != 0: 
        return False
    # Now we know it will work.
    cmd = "initctl list  | sed 's/[(].*[)] //g' | tr ', ' ' ' | awk '{print $1,$2}'"
    code, txt = RunGetOutputNoStderr(cmd, False, False)
    services = txt.splitlines()
    cmd = initd_service + " --status-all &> /tmp/tmpfile ; cat /tmp/tmpfile ; rm /tmp/tmpfile"
    code, txt = RunGetOutputNoStderr(cmd, False, False)
    txt = txt.replace('[','')
    txt = txt.replace(']','')
    services.extend(txt.splitlines())
    for srv in services:
        if len(srv) == 0:
            continue
        s=srv.split()
        if len(s[0]) == 1: #swap them.
            s.reverse()
        d['Name'] = s[0]
        if len(sc.Name) and not fnmatch.fnmatch(d['Name'],sc.Name):
            continue
        if d['Name'] in names.keys():
            continue
        names[d['Name']] = None
        d['Controller'] =  sc.Controller
        d['Description'] = ''
        d['State'] = 'stopped'
        if 'running' in s[1] or '+' in s[1]:
            d['State'] = 'running'
        if len(sc.State) and sc.State != d['State'].lower():
            continue
        d['Path'] = ''
        if os.path.exists('/etc/init.d/' + s[0]):
            d['Path'] = '/etc/init.d/' + s[0]
        elif os.path.exists('/etc/init/' + s[0] + '.conf'):
            d['Path'] = '/etc/init/' + s[0] + '.conf'
        # 'initctl list' won't show disabled services
        d['Enabled'] = True
        if sc.FilterEnabled and sc.Enabled != d['Enabled']:
            continue
        if len(s[1]) > 1:
            cmd = 'initctl show-config ' + d['Name'] + ' | grep -E "start |stop " | tr "\n" " " | tr -s " " '
            code, out = RunGetOutputNoStderr(cmd, False, False) 
            d['Runlevels'] = out[1:]
        else:
            rld=GetRunlevels(sc,d['Name'])
            if rld != None and 'Runlevels' in rld.keys():
                d['Runlevels'] = rld['Runlevels']
        sc.services_list.append(copy.deepcopy(d))
    return True

def InitdGetAll(sc):
    d={}
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        initd_service_status = 'sudo /opt/microsoft/omsconfig/Scripts/OMSServiceStat.sh'
        status_postfix = ''
        initd_service_status_all = 'sudo /opt/microsoft/omsconfig/Scripts/OMSServiceStatAll.sh'
    else:
        initd_service_status = initd_service
        status_postfix = ' status'
        initd_service_status_all = initd_service + ' --status-all '
    if os.path.exists(initd_chkconfig):
        # SLES 11-SP4 chkconfig can return error code on success,
        # so don't check chkconfig error code if this is the case.
        if os.path.exists('/etc/SuSE-release'):
            txt = open('/etc/SuSE-release','r').read()
            s=r'.*?VERSION.*?=(.*?)\n.*?PATCHLEVEL.*?=(.*?)\n'
            m = re.search(s, txt, re.M)
            if m != None:
                if not (int(m.group(1)) == 11 and  int(m.group(2)) == 4 ) : 
                    # Does the command work?
                    # There may be no error detected in our multi-pipe command below.
                    # To keep from returning garbage, we must test the command.
                    # RunGetOutput(chk_err = True) will log the error message here if it occurs.
                    cmd = initd_chkconfig + ' --list '
                    code, txt = RunGetOutputNoStderr(cmd, False, True)
                    if code != 0: 
                        return False
                    # Now we know it will work.
        cmd = initd_chkconfig + ' --list | grep on | grep -v based'
        code, txt = RunGetOutputNoStderr(cmd, False, False)
        services=txt.splitlines()
        for srv in services:
            if len(srv) == 0:
                continue
            s=srv.split()
            d['Name'] = s[0]
            if len(sc.Name) and not fnmatch.fnmatch(d['Name'],sc.Name):
                continue
            d['Controller'] =  sc.Controller
            d['Description'] = ''
            d['State'] = 'stopped'
            cmd = initd_service_status + ' ' + s[0] + status_postfix
            code, txt = RunGetOutputNoStderr(cmd, False, False)
            if 'running' in txt:
                d['State'] = 'running'
            if len(sc.State) and sc.State != d['State'].lower():
                continue
            d['Path'] = ''
            if os.path.exists('/etc/init.d/' + s[0]):
                d['Path'] = '/etc/init.d/' + s[0]
            d['Enabled'] = ':on' in srv
            if sc.FilterEnabled and sc.Enabled != d['Enabled']:
                continue
            d['Runlevels'] = reduce(lambda x, y: x + ' ' + y, s[1:])
            sc.services_list.append(copy.deepcopy(d))
    else:
        # Does the command work?
        # There may be no error detected in our multi-statement command below.
        # To keep from returning garbage, we must test the command.
        # RunGetOutput(chk_err = True) will log the error message here if it occurs.
        cmd =  initd_service_status_all
        code, txt = RunGetOutputNoStderr(cmd, False, True)
        if code != 0: 
            return False
        # Now we know it will work.
        cmd = initd_service_status_all + ' &> /tmp/tmpfile ; cat /tmp/tmpfile ; rm /tmp/tmpfile'
        code, txt = RunGetOutputNoStderr(cmd, False, False)
        txt = txt.replace('[','')
        txt = txt.replace(']','')
        services = txt.splitlines()
    for srv in services:
        if len(srv) == 0:
            continue
        s=srv.split()
        d['Name'] = s[1]
        if len(sc.Name) and not fnmatch.fnmatch(d['Name'],sc.Name):
            continue
        d['Controller'] =  sc.Controller
        d['Description'] = ''
        d['State'] = 'stopped'
        if '+' in s[0]:
            d['State'] = 'running'
        if len(sc.State) and sc.State != d['State'].lower():
            continue
        d['Path'] = ''
        if os.path.exists('/etc/init.d/' + s[1]):
            d['Path'] = '/etc/init.d/' + s[1]
        elif os.path.exists('/etc/init/' + s[1] + '.conf'):
            d['Path'] = '/etc/init/' + s[1] + '.conf'
        rld=GetRunlevels(sc,d['Name'])
        if rld != None and 'Runlevels' in rld.keys():
            d['Runlevels'] = rld['Runlevels']
        d['Enabled'] = 'on' in d['Runlevels']
        if sc.FilterEnabled and sc.Enabled != d['Enabled']:
            continue
        sc.services_list.append(copy.deepcopy(d))
    return True

def GetController():
    if UpstartExists():
        return 'upstart'
    if SystemdExists():
        return 'systemd'
    if InitExists():
        return 'init'
    Print('ERROR: Unable to determine Controller.')
    LG().Log('ERROR', 'Unable to determine Controller.')
    return ''

class ServiceContext:

    def __init__(self, Name, Controller, Enabled, State):
        self.services_list=[]
        self.runlevels_d=None
        self.Name = Name
        self.Controller = Controller
        self.Enabled = Enabled
        self.State = State
        self.Path = ''
        self.Description = ''
        self.Runlevels = ''
        self.FilterEnabled = False

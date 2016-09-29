#!/usr/bin/env python
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ====================================
import os
import sys
import configparser
import subprocess
import signal
import datetime
import time

import imp
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

def init_locals(WorkspaceId, AzureDnsAgentSvcZone):
    if WorkspaceId is None:
        WorkspaceId = ''
    if AzureDnsAgentSvcZone is None:
        AzureDnsAgentSvcZone = ''
    return WorkspaceId, AzureDnsAgentSvcZone


def Set_Marshall(WorkspaceId, Enabled, AzureDnsAgentSvcZone):
    WorkspaceId, AzureDnsAgentSvcZone = init_locals(WorkspaceId, AzureDnsAgentSvcZone)
    if Enabled:
        try:
            if not os.path.isdir(WORKER_STATE_DIR):
                os.mkdir(WORKER_STATE_DIR)
            agent_id = read_oms_config_file()
            proc = subprocess.Popen(
                ["python", REGISTRATION_FILE_PATH, "--register", "-w", WorkspaceId, "-a", agent_id,
                 "-c", OMS_CERTIFICATE_PATH, "-k", OMS_CERT_KEY_PATH, "-f", WORKING_DIRECTORY_PATH, "-s",
                 WORKER_STATE_DIR, "-e", AzureDnsAgentSvcZone, "-p", PROXY_CONF_PATH, "-g", KEYRING_PATH],
                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = proc.communicate()
            log(DEBUG, "Trying to register Linux hybrid worker")
            if proc.wait() != 0:
                log(ERROR, "Linux Hybrid Worker registration failed: " + stderr + "\n" + stdout)
                return [-1]
            if not os.path.isfile(WORKER_CONF_FILE_PATH):
                log(ERROR, "Linux Hybrid Worker registration file could not be created")
                return [-1]
        except Exception, exception:
            log(ERROR, exception.message)
            return [-1]

        # Read the worker state file and try to kill linux hybrid worker process if running
        log(DEBUG, "Linux Hybrid Worker registration succeeded")
        try:
            # Kill hybrid worker if its already running
            kill_hybrid_worker()

            # Start the worker again
            start_daemon(["python", HYBRID_WORKER_START_PATH, WORKER_CONF_FILE_PATH, WorkspaceId,
                         read_resoruce_version_file()])

            # Take your sweet time to check for the worker process
            success = False
            for i in range(0,5):
                time.sleep(5)
                if verify_hybrid_worker() > 0:
                    success = True
                    break
            if not success:
                log(ERROR, "Linux Hybrid worker process was not detected")
                return [-1]

        except Exception, exception:
            log(ERROR, exception.message)
            return [-1]
        log(INFO, "Set method exited successfully for Enabled = True")
    else:
        # enabled is set to false
        try:
            kill_hybrid_worker()
            os.remove(WORKER_CONF_FILE_PATH)
            os.remove(WORKER_STATE_FILE_PATH)
        except Exception, exception:
            log(ERROR, exception.message)
            return [-1]
        log(INFO, "Set method exited successfully for Enabled = False")
    return [0]


def Test_Marshall(WorkspaceId, Enabled, AzureDnsAgentSvcZone):
    init_locals(WorkspaceId, AzureDnsAgentSvcZone)
    if Enabled:
        if os.path.isfile(WORKER_CONF_FILE_PATH):
            if os.path.isfile(WORKER_STATE_FILE_PATH):
                if worker_is_latest():
                    if verify_hybrid_worker() > 0:
                        log(INFO, "Test returned [0] for Enabled = True")
                        return [0]
                    else:
                        log(INFO, "The process for Linux hybrid worker was not running")
                else:
                    log(INFO, "Running worker version does not match the DSC resource version")
            else:
                log(INFO, "state.conf file was not found")
        else:
            log(INFO, "worker.conf file was not found")
    else:
        # Enabled is False
        if not os.path.isfile(WORKER_CONF_FILE_PATH):
            if not os.path.isfile(WORKER_STATE_FILE_PATH):
                log(INFO, "Test returned [0] for Enabled = False")
                return [0]
    log(INFO, "Test returned [-1] for Enabled = " + str(Enabled))
    return [-1]


def Get_Marshall(WorkspaceId, Enabled, AzureDnsAgentSvcZone):
    WorkspaceId, AzureDnsAgentSvcZone = init_locals(WorkspaceId, AzureDnsAgentSvcZone)
    arg_names = list(locals().keys())
    retval = 0
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


# ###########################################################
# Begin user defined DSC functions
# ###########################################################
ERROR  = 'ERROR'
DEBUG = 'DEBUG'
INFO = 'INFO'

STATE_SECTION = "state"
PID = "pid"
WORKSPACE_ID = "workspace_id"
CONFIGURATION = "configuration"
DSC_RESOURCE_VERSION = "resource_version"
AGENT_ID = "AGENT_GUID"

WORKER_STATE_DIR = "/var/opt/microsoft/omsagent/state/automationworker"
WORKER_CONF_FILE_PATH = os.path.join(WORKER_STATE_DIR, "worker.conf")
WORKER_STATE_FILE_PATH = os.path.join(WORKER_STATE_DIR, "state.conf")

DSC_RESOURCE_VERSION_FILE = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/VERSION"
OMS_ADMIN_CONFIG_FILE = "/etc/opt/microsoft/omsagent/conf/omsadmin.conf"
OMS_CERTIFICATE_PATH = "/etc/opt/microsoft/omsagent/certs/oms.crt"
OMS_CERT_KEY_PATH = "/etc/opt/microsoft/omsagent/certs/oms.key"
WORKING_DIRECTORY_PATH = "/var/opt/microsoft/omsagent/run"
REGISTRATION_FILE_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/scripts/register_oms.py"
HYBRID_WORKER_START_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/main.py"
PROXY_CONF_PATH="/etc/opt/microsoft/omsagent/conf/proxy.conf"
KEYRING_PATH="/etc/opt/omi/conf/omsconfig/keyring.gpg"


def read_worker_state():
    # Reads the state.config file and returns the values of pid, workspace_id, resource_running_version
    if os.path.isfile(WORKER_STATE_FILE_PATH):
        state = configparser.configparser()
        try:
            state.read(WORKER_STATE_FILE_PATH)
            pid = state.get(STATE_SECTION, PID)
            workspace_id = state.get(STATE_SECTION, WORKSPACE_ID)
            resource_running_version = state.get(STATE_SECTION, DSC_RESOURCE_VERSION)
        except configparser.NoSectionError, exception:
            log(DEBUG, exception.message)
            raise configparser.Error(exception.message)

        except configparser.NoOptionError, exception:
            log(DEBUG, exception.message)
            raise configparser.Error(exception.message)

        return pid, workspace_id, resource_running_version
    else:
        error_string = "could not find file" + WORKER_STATE_FILE_PATH
        log('DEUBG', error_string)
        raise configparser.Error(error_string);


def read_oms_config_file():
    # Reads the oms config file
    # Returns: AgentID config value
    if os.path.isfile(OMS_ADMIN_CONFIG_FILE):
        try:
            keyvals = config_file_to_kv_pair(OMS_ADMIN_CONFIG_FILE)
            return keyvals[AGENT_ID].strip()
        except configparser.NoSectionError, exception:
            log(DEBUG, exception.message)
            raise configparser.Error(exception.message)
        except configparser.NoOptionError, exception:
            log('DEUBG', exception.message)
            raise configparser.Error(exception.message)
    else:
        error_string = "could not find file" + OMS_ADMIN_CONFIG_FILE
        log('DEUBG', error_string)
        raise configparser.Error(error_string);


def config_file_to_kv_pair(filename):
    # gets key value pairs from files with similar format to omsadmin.conf
    retval = dict()
    f = open(filename, "r")
    contents = f.read()
    f.close()
    lines = contents.splitlines()
    for line in lines:
        # Find first '='; everything before is key, everything after is value
        midpoint = line.find("=")
        if (midpoint == 0 or midpoint == -1):
            # Skip over lines without = or lines that begin with =
            continue
        key = line[:midpoint]
        value = line[midpoint + 1:]
        retval[key] = value
    return retval


def verify_hybrid_worker():
    # Returns the pid of the hybrid worker if its running, -1 otherwise
    try:
        pid, workspace_id, running_version = read_worker_state()
        proc = subprocess.Popen(["ps", "-p", pid, "-o", "args="], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        command, error = proc.communicate()
        proc.wait()
    except Exception, e:
        log(DEBUG, e.message)
        return -1
    if proc.returncode == 0 and command.__contains__(workspace_id):
        log(DEBUG, "PID was identified as " + pid + " workspace_id was " + workspace_id)
        return int(pid)
    log(DEBUG, "PID was not identified for workspace id " + workspace_id)
    return -1


def kill_hybrid_worker():
    """Kill hybrid worker process if it exists
    Returns:
        true if it was running and killed
        false if it was not running
    Exceptions:
        throws exception if process was running and could not be killed
    """
    pid = verify_hybrid_worker()
    if pid > 0:
        try:
            os.kill(pid, signal.SIGTERM)
        except Exception, exception:
            log(ERROR, "Could not kill Linux Hybrid Worker process pid: " + pid + " " + exception.message)
            raise exception

def read_resoruce_version_file():
    version_file_handle = open(DSC_RESOURCE_VERSION_FILE, 'r')
    version = version_file_handle.read().strip()
    version_file_handle.close()
    return version

def worker_is_latest():
    # compares the versions of the DSC resoruce that stated the hybrid worker and the latest present version of DSC resoruce
    # returns true of the versions match, false otherwise
    pid, workspaceid, runningversion = read_worker_state()
    runningversion = runningversion.strip()
    latest_available_version = read_resoruce_version_file()
    log(DEBUG, "running version is: " + runningversion)
    log(DEBUG, "latest available version is: " + latest_available_version)
    return runningversion == latest_available_version

def start_daemon(args):
    # Forks a subprocess from args
    try:
        pid = os.fork()
        if pid > 0:
            # exit the first parent
            log(DEBUG, "Forked first child")
            log(DEBUG, "Parent PID was: " + str(os.getpid()))
            return
    except OSError, e:
        log(ERROR, "fork #1 failed: " + e.errno + "\n strerror: " + e.strerror)
        raise e
    # Child process will continue to run in absence of parent
    # Will start the Linux Hybrid Worker as a Popen process and wait forever for it to exit
    os.chdir("/")
    os.setsid()
    os.umask(077)
    try:
        pc = subprocess.Popen(args)
        log(DEBUG, "pid of child python process is: " + str(os.getpid()))
        log(DEBUG, "pid of Popened linux hybrid worker is: " + str(pc.pid))
        pc.wait()
        sys.exit(0)
    except Exception, e:
        log(ERROR, "fork #2 failed: " + e.message)
        sys.exit(-1)


def log(level, message):
    log_local(level, message)
    try:
        LG().Log(level, message)
    except Exception, e:
        log_local(INFO, "DSC log to omsconfig.log failed with error " + e.message)


def log_local(level, message):
    try:
        fileh = open("/var/opt/microsoft/omsagent/log/nxOMSAutomationWorker.log", "a")
        line = level + ": " + message + " " + str(datetime.datetime.now()) + "\n"
        fileh.writelines(line)
        fileh.flush()
        fileh.close()
    except Exception:
        ## If you want to disable logging, change the permissions to the nxOMSAutomationWorker.log file
        pass

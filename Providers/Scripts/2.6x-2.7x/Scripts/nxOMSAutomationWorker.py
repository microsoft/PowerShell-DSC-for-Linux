#!/usr/bin/env python
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ====================================
import os
import sys
import ConfigParser
import subprocess
import signal
import time
import logging
import logging.handlers

import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

def init_locals(WorkspaceId, AzureDnsAgentSvcZone):
    if WorkspaceId is None:
        WorkspaceId = ''
    if AzureDnsAgentSvcZone is None:
        AzureDnsAgentSvcZone = ''
    return WorkspaceId.encode('ascii', 'ignore'), AzureDnsAgentSvcZone.encode('ascii', 'ignore')


def Set_Marshall(WorkspaceId, Enabled, AzureDnsAgentSvcZone):
    WorkspaceId, AzureDnsAgentSvcZone = init_locals(WorkspaceId, AzureDnsAgentSvcZone)
    return set_marshall_helper(WorkspaceId, Enabled, AzureDnsAgentSvcZone)

def set_marshall_helper(WorkspaceId, Enabled, AzureDnsAgentSvcZone, mock_worker_config_file=False):
    try:
        is_primary = is_oms_primary_workspace(WorkspaceId)
    except Exception, e:
        log(ERROR, "Could not detect if workspace is primary\n %s" %(str(e)))
        return [-1]

    if is_primary is False:
        # Set_Marshall is a no-op on non-primary workspaces
        log(INFO, "Set_Marshall skipped because workspace was not primary")
        return [0]

    if Enabled:
        try:
            if not os.path.isdir(WORKER_STATE_DIR):
                os.mkdir(WORKER_STATE_DIR)
            if not os.path.isdir(WORKING_DIRECTORY_PATH):
                os.makedirs(WORKING_DIRECTORY_PATH)
            oms_workspace_id, agent_id = read_oms_primary_workspace_config_file()
            # If both proxy files exist use the new one
            # If neither exist use the new path, path will have no file in it, but no file means no proxy set up
            # If one of them exists, use that
            proxy_conf_path = PROXY_CONF_PATH_NEW
            if not os.path.isfile(PROXY_CONF_PATH_NEW) and os.path.isfile(PROXY_CONF_PATH_LEGACY):
                proxy_conf_path = PROXY_CONF_PATH_LEGACY
            if mock_worker_config_file is True:
                proc = subprocess.Popen(
                    ["python", REGISTRATION_FILE_PATH, "--register", "-w", WorkspaceId, "-a", agent_id,
                     "-c", OMS_CERTIFICATE_PATH, "-k", OMS_CERT_KEY_PATH, "-f", WORKING_DIRECTORY_PATH, "-s",
                     WORKER_STATE_DIR, "-e", AzureDnsAgentSvcZone, "-p", proxy_conf_path, "-g", KEYRING_PATH,
                     "--mock_powershelldsc_test"],
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            else:
                proc = subprocess.Popen(
                    ["python", REGISTRATION_FILE_PATH, "--register", "-w", WorkspaceId, "-a", agent_id,
                     "-c", OMS_CERTIFICATE_PATH, "-k", OMS_CERT_KEY_PATH, "-f", WORKING_DIRECTORY_PATH, "-s",
                     WORKER_STATE_DIR, "-e", AzureDnsAgentSvcZone, "-p", proxy_conf_path, "-g", KEYRING_PATH],
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

            # Wait for the worker process to actually start
            success = False
            for i in range(0, 5):
                time.sleep(5)
                if verify_hybrid_worker() > 0:
                    success = True
                    break
            if not success:
                log(ERROR, "Linux Hybrid worker process was not detected")
                return [-1]
        except SystemExit:
            # very important for the first child of the start_daemon method to die properly
            exit(0)
        except Exception, exception:
            log(ERROR, exception.message)
            return [-1]
        log(INFO, "Set method exited successfully for Enabled = True")
    else:
        # enabled is set to false
        try:
            kill_hybrid_worker()
            if os.path.isfile(WORKER_CONF_FILE_PATH):
                os.remove(WORKER_CONF_FILE_PATH)
            if os.path.isfile(WORKER_STATE_FILE_PATH):
                os.remove(WORKER_STATE_FILE_PATH)
        except Exception, exception:
            log(ERROR, exception.message)
            return [-1]
        log(INFO, "Set method exited successfully for Enabled = False")
    return [0]


def Test_Marshall(WorkspaceId, Enabled, AzureDnsAgentSvcZone):
    init_locals(WorkspaceId, AzureDnsAgentSvcZone)
    try:
        isprimary = is_oms_primary_workspace(WorkspaceId)
    except Exception, e:
        log(ERROR, "Could not detect if workspace is primary\n %s" %(str(e)))
        return [-1]

    if isprimary is False:
        # Test_Marshall is a no-op on non-primary workspaces
        log(INFO, "Test_Marshall skipped because workspace was not primary")
        return [0]

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
    retval = 0
    retd = dict()
    retd['WorkspaceId'] = protocol.MI_String(WorkspaceId)
    retd['Enabled'] = protocol.MI_Boolean(Enabled)
    retd['AzureDnsAgentSvcZone'] = protocol.MI_String(AzureDnsAgentSvcZone)
    return retval, retd


# ###########################################################
# Begin user defined DSC functions
# ###########################################################
ERROR = logging.ERROR
DEBUG = logging.DEBUG
INFO = logging.INFO

STATE_SECTION = "state"
PID = "pid"
WORKSPACE_ID = "workspace_id"
OMS_WORKSPACE_ID_KEY = "WORKSPACE_ID"
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
WORKING_DIRECTORY_PATH = "/var/opt/microsoft/omsagent/run/automationworker"
REGISTRATION_FILE_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/scripts/register_oms.py"
HYBRID_WORKER_START_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/main.py"
PROXY_CONF_PATH_LEGACY="/etc/opt/microsoft/omsagent/conf/proxy.conf"
PROXY_CONF_PATH_NEW="/etc/opt/microsoft/omsagent/proxy.conf"
KEYRING_PATH="/etc/opt/omi/conf/omsconfig/keyring.gpg"
LOCAL_LOG_LOCATION = "/var/opt/microsoft/omsagent/log/nxOMSAutomationWorker.log"


def is_oms_primary_workspace(mof_workspace_id):
    """
    Detect if the passed workspace id is primary workspace on multi-homing enabled OMS agent
    Mulit-homing for OMS is 2 tiered, one primary and multiple secondary workspaces are allowed
    Currently, the Automation Worker should only run on primary workspace
    A primary OMS workspace is pointed to by the symbolic links of old style (single homing) paths like
    /etc/opt/microsoft/omsagent/ the actual location of which is /etc/opt/microsoft/omsagent/<workspace id>.
    A sufficient test for checking whether a given workspace id belongs to a primary is to compare it against the
    workspace id found in the oms config file in the old style path
    :return: True, if the given workspace id belongs to the primary OMS workspace, False otherwise
    """
    oms_workspace_id, agent_id = read_oms_primary_workspace_config_file()
    if oms_workspace_id == mof_workspace_id:
        return True
    else:
        return False

def read_worker_state():
    # Reads the state.config file and returns the values of pid, workspace_id, resource_running_version
    if os.path.isfile(WORKER_STATE_FILE_PATH):
        state = ConfigParser.ConfigParser()
        try:
            state.read(WORKER_STATE_FILE_PATH)
            pid = state.get(STATE_SECTION, PID)
            workspace_id = state.get(STATE_SECTION, WORKSPACE_ID)
            resource_running_version = state.get(STATE_SECTION, DSC_RESOURCE_VERSION)
        except ConfigParser.NoSectionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)

        except ConfigParser.NoOptionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)

        return pid, workspace_id, resource_running_version
    else:
        error_string = "could not find file " + WORKER_STATE_FILE_PATH
        log(DEBUG, error_string)
        raise ConfigParser.Error(error_string)


def read_oms_primary_workspace_config_file():
    # Reads the oms config file
    # Returns: AgentID config value
    if os.path.isfile(OMS_ADMIN_CONFIG_FILE):
        # the above path always points to the oms configuration file of the primary workspace
        try:
            keyvals = config_file_to_kv_pair(OMS_ADMIN_CONFIG_FILE)
            return keyvals[OMS_WORKSPACE_ID_KEY].strip(), keyvals[AGENT_ID].strip()
        except ConfigParser.NoSectionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)
        except ConfigParser.NoOptionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)
    else:
        error_string = "could not find file" + OMS_ADMIN_CONFIG_FILE
        log(DEBUG, error_string)
        raise ConfigParser.Error(error_string)


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
            os.wait()
            return
    except OSError, e:
        log(ERROR, "fork #1 failed: " + e.errno + "\n strerror: " + e.strerror)
        raise e
    # Child process will continue to run in absence of parent
    # Will start the Linux Hybrid Worker as a Popen process and wait forever for it to exit
    os.chdir("/")
    os.setsid()
    os.umask(077)
    os.close(1)
    os.close(2)
    try:
        pc = subprocess.Popen(args)
        log(DEBUG, "pid of child python process is: " + str(os.getpid()))
        log(DEBUG, "pid of Popened linux hybrid worker is: " + str(pc.pid))
    except Exception, e:
        log(ERROR, "fork #2 failed: " + e.message)
        sys.exit(-1)
    sys.exit(0)

def log(level, message):
    try:
        LG().Log(logging._levelNames[level], message)
    except:
        pass

class local_log():
    logger = None
    logfh = None
    def __init__(self):
        if local_log.logger is None or local_log.logfh is None:
            local_log.logger = logging.getLogger()
            local_log.logfh = logging.handlers.RotatingFileHandler(LOCAL_LOG_LOCATION, mode='a', maxBytes=1048576, backupCount=20)
            formatter = logging.Formatter('%(levelname)s - %(asctime)s - %(message)s')
            local_log.logger.setLevel(DEBUG)
            local_log.logfh.setFormatter(formatter)
            local_log.logger.addHandler(local_log.logfh)
    def log(self, level, message):
        local_log.logger.log(level, message)



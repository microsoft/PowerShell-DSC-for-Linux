#!/usr/bin/env python
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ====================================
import os
import sys
import ConfigParser
import subprocess
import time
import logging
import logging.handlers
import pwd

import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
try:
    serializerfactory = imp.load_source('serializerfactory', '../../modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/serializerfactory.py')
except:
    # this is the path when running tests
    serializerfactory = imp.load_source('serializerfactory', '../../nxOMSAutomationWorker/automationworker/worker/serializerfactory.py')
LG = nxDSCLog.DSCLog

def Set_Marshall(ResourceSettings):
    settings = read_settings_from_mof_json(ResourceSettings)
    if not is_oms_primary_workspace(settings.workspace_id):
        # not primary workspace
        # return unconditional [0] for a NOOP on non-primary workspace
        log(DEBUG, "Set_Marshall skipped: non primary workspace. Set marshall returned [0]")
        return [0]

    try:
        # compatibility from 1.3 remove state.conf file
        if os.path.isfile(STATE_CONF_FILE_PATH):
            os.remove(STATE_CONF_FILE_PATH)

        # Kill worker managers that might already be running
        kill_worker_manager(settings.workspace_id)

        # Set up conf and working directories if it doesn't exit
        if not os.path.isdir(WORKER_STATE_DIR):
            os.makedirs(WORKER_STATE_DIR, PERMISSION_LEVEL_0770)
        if not os.path.isdir(WORKING_DIRECTORY_PATH):
            os.makedirs(WORKING_DIRECTORY_PATH, PERMISSION_LEVEL_0770)

        # if the directory does not have permision level 770, reset the permission level
        if os.stat(WORKING_DIRECTORY_PATH).st_mode & PERMISSION_LEVEL_0777 != PERMISSION_LEVEL_0770:
            # bitwise AND with PERMISSION_LEVEL_0777 will give true permission level
            os.chmod(WORKING_DIRECTORY_PATH, PERMISSION_LEVEL_0770)

        # if the directory does not have permision level 770, reset the permission level
        if os.stat(WORKER_STATE_DIR).st_mode & PERMISSION_LEVEL_0777 != PERMISSION_LEVEL_0770:
            # bitwise AND with PERMISSION_LEVEL_0777 will give true permission level
            os.chmod(WORKER_STATE_DIR, PERMISSION_LEVEL_0770)

        # Create the configuration object
        write_omsconf_file(settings.workspace_id, settings.updates_enabled, settings.diy_enabled)
        os.chmod(OMS_CONF_FILE_PATH, PERMISSION_LEVEL_0770)

        log(DEBUG, "oms.conf file was written")

        # Write worker.conf file
        oms_workspace_id, agent_id = read_oms_primary_workspace_config_file()
        # If both proxy files exist use the new one
        # If neither exist use the new path, path will have no file in it, but no file means no proxy set up
        # If one of them exists, use that
        proxy_conf_path = PROXY_CONF_PATH_NEW
        if not os.path.isfile(PROXY_CONF_PATH_NEW) and os.path.isfile(PROXY_CONF_PATH_LEGACY):
            proxy_conf_path = PROXY_CONF_PATH_LEGACY
        args = ["python", REGISTRATION_FILE_PATH, "--register", "-w", settings.workspace_id, "-a", agent_id, "-c",
                OMS_CERTIFICATE_PATH, "-k", OMS_CERT_KEY_PATH, "-f", WORKING_DIRECTORY_PATH, "-s", WORKER_STATE_DIR,
                "-e", settings.azure_dns_agent_svc_zone, "-p", proxy_conf_path, "-g", KEYRING_PATH]
        proc = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()
        # log(DEBUG, "Trying to register Linux hybrid worker with args: %s" % str(args))
        if proc.returncode != 0:
            log(ERROR, "Linux Hybrid Worker registration failed: " + stderr + "\n" + stdout)
            return [-1]
        if not os.path.isfile(AUTO_REGISTERED_WORKER_CONF_PATH):
            log(ERROR, "Linux Hybrid Worker registration file could not be created")
            return [-1]
        else:
            os.chmod(AUTO_REGISTERED_WORKER_CONF_PATH, PERMISSION_LEVEL_0770)


        # start the worker manager proc

        if (settings.updates_enabled or settings.diy_enabled) and start_worker_manager_process(settings.workspace_id) < 0:
            log(ERROR, "Worker manager process could not be started. Set_Marshall returned [-1]")
            return [-1]

        log(INFO, "Set_Marshall returned [0]. Exited successfully")
        return [0]

    except Exception, e:
        log(ERROR, "Set_Marshall returned [-1] with following error %s" %e.message)
        return [-1]


def Test_Marshall(ResourceSettings):
    """
    Test method for the DSC resoruce
    If it returns [0] no further action is taken
    If it returns [-1] Set_Marshall is called
    It tests for whether oms.conf exists and the worker manager is running and the latest version
    :param ResourceSettings:
    :return: [0] if all tests pass [-1] otherwise
    """
    settings = read_settings_from_mof_json(ResourceSettings)
    if not is_oms_primary_workspace(settings.workspace_id):
        # not primary workspace
        # return unconditional [0] for a NOOP on non-primary workspace
        log(DEBUG, "Test_Marshall skipped: non primary workspace. Test_Marshall returned [0]")
        return [0]

    if not os.path.isfile(OMS_CONF_FILE_PATH):
        log(INFO, "Test_Marshall returned [-1]: oms.conf file not found")
        return [-1]
    if (settings.updates_enabled or settings.diy_enabled ) and is_worker_manager_running_latest_version(settings.workspace_id) is False:
        # Either the worker manager is not running, or its not latest
        log(INFO, "Test_Marshall returned [-1]: worker manager isn't running or is not latest")
        return [-1]
    if not settings.updates_enabled and not settings.diy_enabled and get_worker_manager_pid_and_version(settings.workspace_id, False)[0] > 0:
        log(INFO, "Test_Marshall returned [-1]: worker manager is running when no solution is enabled")
        return [-1]
    if not is_oms_config_consistent_with_mof(settings.updates_enabled, settings.diy_enabled):
        # Current oms.conf is inconsistent with the mof
        log(INFO, "Test_Marshall returned [-1]: oms.conf differs from configuration mof")
        return [-1]

    # All went well
    log(DEBUG, "Test_Marshall returned [0]")
    return [0]


def Get_Marshall(ResourceSettings):
    settings = read_settings_from_mof_json(ResourceSettings)
    retval = 0
    retd = dict()
    retd['WorkspaceId'] = protocol.MI_String(settings.workspace_id)
    retd['AzureDnsAgentSvcZone'] = protocol.MI_String(settings.azure_dns_agent_svc_zone)
    retd['UpdatesEnabled'] = protocol.MI_Boolean(settings.updates_enabled)
    retd['DiyEnabled'] = protocol.MI_Boolean(settings.diy_enabled)
    return retval, retd


# ###########################################################
# Begin user defined DSC functions
# ###########################################################
ERROR = logging.ERROR
DEBUG = logging.DEBUG
INFO = logging.INFO

OPTION_OMS_WORKSPACE_ID = "WORKSPACE_ID"
OPTION_AGENT_ID = "AGENT_GUID"

SECTION_OMS_GLOBAL = "oms-global"
OPTION_AUTO_REGISTERED_WORKER_CONF_PATH =  "auto_registered_worker_conf_path"
OPTION_MANUALLY_REGISTERED_WORKER_CONF_PATH = "manually_registered_worker_conf_path"
OPTION_WORKSPACE_ID = "workspace_id"


SECTION_OMS_WORKER_CONF = "oms-worker-conf"
OPTION_RESOURCE_VERSION = "resource_version"
OPTION_HYBRID_WORKER_PATH = "hybrid_worker_path"
OPTION_DISABLE_WORKER_CREATION = "disable_worker_creation"


WORKER_STATE_DIR = "/var/opt/microsoft/omsagent/state/automationworker"
DIY_WORKER_STATE_DIR = os.path.join(WORKER_STATE_DIR, "diy")
OMS_CONF_FILE_PATH = os.path.join(WORKER_STATE_DIR, "oms.conf")
AUTO_REGISTERED_WORKER_CONF_PATH = os.path.join(WORKER_STATE_DIR, "worker.conf")
MANUALLY_REGISTERED_WORKER_CONF_PATH = os.path.join(DIY_WORKER_STATE_DIR, "worker.conf")
STATE_CONF_FILE_PATH = os.path.join(WORKER_STATE_DIR, "state.conf")

DSC_RESOURCE_VERSION_FILE = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/VERSION"
OMS_ADMIN_CONFIG_FILE = "/etc/opt/microsoft/omsagent/conf/omsadmin.conf"
WORKING_DIRECTORY_PATH = "/var/opt/microsoft/omsagent/run/automationworker"
WORKER_MANAGER_START_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/main.py"
HYBRID_WORKER_START_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py"
PROXY_CONF_PATH_LEGACY="/etc/opt/microsoft/omsagent/conf/proxy.conf"
PROXY_CONF_PATH_NEW="/etc/opt/microsoft/omsagent/proxy.conf"
REGISTRATION_FILE_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/scripts/register_oms.py"
OMS_CERTIFICATE_PATH = "/etc/opt/microsoft/omsagent/certs/oms.crt"
OMS_CERT_KEY_PATH = "/etc/opt/microsoft/omsagent/certs/oms.key"
KEYRING_PATH="/etc/opt/omi/conf/omsconfig/keyring.gpg"

# permission level rwx rwx ---
# leading zero is necessary because this is an octal number
# Note: for python 3.x use 0o770 instead of 0770
PERMISSION_LEVEL_0770 = 0770
PERMISSION_LEVEL_0777 = 0777

AUTOMATION_USER = "nxautomation"

LOCAL_LOG_LOCATION = "/var/opt/microsoft/omsagent/log/nxOMSAutomationWorker.log"
LOG_LOCALLY = False

# User defined functions

class Settings:
    workspace_id = ""
    azure_dns_agent_svc_zone = ""
    updates_enabled = ""
    diy_enabled = ""
    def __init__(self, workpsace_id, azure_dns_agent_svc_zone, updates_enabled, diy_enabled):
        self.workspace_id = workpsace_id
        self.azure_dns_agent_svc_zone = azure_dns_agent_svc_zone
        self.updates_enabled = updates_enabled
        self.diy_enabled = diy_enabled


def read_settings_from_mof_json(json_serialized_string):
    """
    Deserializes a JSON serialized string
    :param json_serialized_string: the serialized JOSN string
    :return: Settings object
    """
    try:
        json_serializer = serializerfactory.get_serializer(sys.version_info)
        settings = json_serializer.loads(json_serialized_string)
        workspace_id = settings[0]["WorksapceId"].encode("ascii", "ignore")
        azure_dns_agent_svc_zone = settings[0]["AzureDnsAgentSvcZone"].encode("ascii", "ignore")
        updates_enabled = settings[0]["Solutions"]["Updates"]["Enabled"]
        diy_enabled = settings[0]["Solutions"]["AzureAutomation"]["Enabled"]
        return Settings(workspace_id, azure_dns_agent_svc_zone, updates_enabled, diy_enabled)
    except Exception as e:
        log(ERROR, "Json parameters deserialization Error: " + Exception.message)
        raise e


def is_oms_config_consistent_with_mof(updates_enabled, diy_enabled, oms_conf_file_path = OMS_CONF_FILE_PATH):
    if not os.path.isfile(oms_conf_file_path):
        return False

    oms_config = ConfigParser.ConfigParser()
    oms_config.read(oms_conf_file_path)
    if not oms_config.has_section(SECTION_OMS_WORKER_CONF):
        return False
    updates_present = oms_config.has_option(SECTION_OMS_WORKER_CONF, OPTION_AUTO_REGISTERED_WORKER_CONF_PATH)
    diy_present = oms_config.has_option(SECTION_OMS_WORKER_CONF, OPTION_MANUALLY_REGISTERED_WORKER_CONF_PATH)

    return updates_present == updates_enabled and diy_present == diy_enabled


def write_omsconf_file(workspace_id, updates_enabled, diy_enabled):
    oms_config = ConfigParser.ConfigParser()
    if os.path.isfile(OMS_CONF_FILE_PATH):
        oms_config.read(OMS_CONF_FILE_PATH)

    # oms.conf region [oms-worker-conf]
    if not oms_config.has_section(SECTION_OMS_WORKER_CONF):
        oms_config.add_section(SECTION_OMS_WORKER_CONF)
    if updates_enabled:
        oms_config.set(SECTION_OMS_WORKER_CONF, OPTION_AUTO_REGISTERED_WORKER_CONF_PATH,
                       AUTO_REGISTERED_WORKER_CONF_PATH)
    else:
        oms_config.remove_option(SECTION_OMS_WORKER_CONF, OPTION_AUTO_REGISTERED_WORKER_CONF_PATH)
    if diy_enabled:
        oms_config.set(SECTION_OMS_WORKER_CONF, OPTION_MANUALLY_REGISTERED_WORKER_CONF_PATH,
                       MANUALLY_REGISTERED_WORKER_CONF_PATH)
    else:
        oms_config.remove_option(SECTION_OMS_WORKER_CONF, OPTION_MANUALLY_REGISTERED_WORKER_CONF_PATH)

    # oms.conf region [oms-global]
    if not oms_config.has_section(SECTION_OMS_GLOBAL):
        oms_config.add_section(SECTION_OMS_GLOBAL)
    oms_config.set(SECTION_OMS_GLOBAL, OPTION_RESOURCE_VERSION, get_module_version())
    oms_config.set(SECTION_OMS_GLOBAL, OPTION_HYBRID_WORKER_PATH, HYBRID_WORKER_START_PATH)
    oms_config.set(SECTION_OMS_GLOBAL, OPTION_WORKSPACE_ID, workspace_id)
    if not oms_config.has_option(SECTION_OMS_GLOBAL, OPTION_DISABLE_WORKER_CREATION):
        oms_config.set(SECTION_OMS_GLOBAL, OPTION_DISABLE_WORKER_CREATION, "False")
    oms_config_fp = open(OMS_CONF_FILE_PATH, 'wb')
    oms_config.write(oms_config_fp)
    oms_config_fp.close()

def is_oms_primary_workspace(workspace_id):
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
    oms_workspace_id, agent_id = get_workspaceid_agentid_from_oms_config()
    if oms_workspace_id == workspace_id:
        return True
    else:
        return False


def get_workspaceid_agentid_from_oms_config():
    # Reads the oms config file
    # Returns: AgentID config value
    if os.path.isfile(OMS_ADMIN_CONFIG_FILE):
        # the above path always points to the oms configuration file of the primary workspace
        try:
            keyvals = config_file_to_kv_pair(OMS_ADMIN_CONFIG_FILE)
            return keyvals[OPTION_OMS_WORKSPACE_ID].strip(), keyvals[OPTION_AGENT_ID].strip()
        except ConfigParser.NoSectionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)
        except ConfigParser.NoOptionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)
    else:
        error_string = "could not find file " + OMS_ADMIN_CONFIG_FILE
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


def start_worker_manager_process(workspace_id):
    """
    Start the worker_manager_process
    :param workspace_id:
    :return: the pid of the worker manager process
    """
    proc = subprocess.Popen(["sudo", "-u", AUTOMATION_USER, "python", WORKER_MANAGER_START_PATH, OMS_CONF_FILE_PATH, workspace_id,
                             get_module_version()])
    for i in range(0, 5):
        time.sleep(3)
        pid = get_worker_manager_pid_and_version(workspace_id, throw_error_on_multiple_found=False)[0]
        if pid > 0:
            # if the pid is greater than 0
            return pid

    # Failure path
    proc.kill()
    return -1


def get_worker_manager_pid_and_version(workspace_id, throw_error_on_multiple_found = True):
    """
    Returns the PID of the worker manager
    :return: pid of the worker manager, -1 if it isn't running
    """
    if 'COLUMNS' in os.environ:
        os.environ['COLUMNS'] = "3000"
    else:
        log(DEBUG, "environment variable COLUMNS was not found")
    proc = subprocess.Popen(["ps", "-u", AUTOMATION_USER, "-o", "pid=", "-o", "args="], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    command, error = proc.communicate()
    if proc.returncode != 0 or error:
        log(INFO, "Failed to detect instance of worker manager")
        return -1, "0.0"
    processes = command.strip().split('\n')
    manager_processes_found = 0
    pid = -1
    version = "0.0"
    for process_line in processes:
        if process_line:
            # make sure process_line is not null or empty
            split_line = process_line.strip().split(" ")
            args = " ".join(split_line[1:])
            if WORKER_MANAGER_START_PATH in args and workspace_id in args:
                pid = int(split_line[0])
                version = split_line[-1].strip()
                manager_processes_found += 1
                if throw_error_on_multiple_found and manager_processes_found > 1:
                    raise AssertionError("More than one manager processes found")
    if pid == -1:
        log(INFO, "Failed to detect instance of worker manager")
    return pid, version


def is_worker_manager_running_latest_version(workspace_id):
    try:
        pid, running_version = get_worker_manager_pid_and_version(workspace_id)
    except AssertionError:
        # more than one manager processes were found
        return False
    available_version = get_module_version()
    log(DEBUG, "running version is: " + running_version)
    log(DEBUG, "latest available version is: " + available_version)
    return pid > 0 and running_version == available_version


def kill_worker_manager(workspace_id):
    """ Worker manger process if it exists
    Exceptions:
        throws exception if process was running and could not be killed
    """
    pattern_match_string = "python\s.*main\.py.*\s%s\s" %workspace_id

    #---- section for debugging
    proc = subprocess.Popen(["pgrep", "-u", AUTOMATION_USER, "-f", pattern_match_string], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    result, error = proc.communicate()
    result = str(result)
    result = result.replace('\n', ' ')
    log(DEBUG, "The following worker manager processes will be terminated: %s" %result)
    #---- end section

    subprocess.call(["sudo", "pkill", "-u", AUTOMATION_USER, "-f", pattern_match_string])
    # can't depend on the return value to ensure that the process was killed since it pattern matches
    pid, version = get_worker_manager_pid_and_version(workspace_id)
    if pid > 0:
        # worker was not killed
        raise OSError("Could not kill worker manager process")
    log(DEBUG, "Processes for worker manager were terminated successfully")

def get_module_version():
    """
    Gets the version of the installed nxOMSAutomationWorker module
    :return: str: module version number
    """
    version_file_handle = open(DSC_RESOURCE_VERSION_FILE, 'r')
    version = version_file_handle.read().strip()
    version_file_handle.close()
    return version


def nxautomation_user_exists():
    """
    Tests if the user nxautomation exists on the machine
    Newer OMS agent installs will have that user
    :return: True if user "nxautomation" exists on the system, False otherwise
    """
    try:
        pwd.getpwnam(AUTOMATION_USER)
    except KeyError:
        # if the user was not found
        log(INFO, "%s was NOT found on the system" %(AUTOMATION_USER))
        return False
    log(INFO, "%s was found on the system" %(AUTOMATION_USER))
    return True

def read_oms_primary_workspace_config_file():
    # Reads the oms config file
    # Returns: AgentID config value
    if os.path.isfile(OMS_ADMIN_CONFIG_FILE):
        # the above path always points to the oms configuration file of the primary workspace
        try:
            keyvals = config_file_to_kv_pair(OMS_ADMIN_CONFIG_FILE)
            return keyvals[OPTION_OMS_WORKSPACE_ID].strip(), keyvals[OPTION_AGENT_ID].strip()
        except ConfigParser.NoSectionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)
        except ConfigParser.NoOptionError, exception:
            log(DEBUG, exception.message)
            raise ConfigParser.Error(exception.message)
    else:
        error_string = "could not find file " + OMS_ADMIN_CONFIG_FILE
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

def log(level, message):
    try:
        LG().Log(logging._levelNames[level], message)
    except:
        pass
    if LOG_LOCALLY:
        try:
            log_local(level, message)
        except:
            pass


def log_local(level, message):
    log_fh = open(LOCAL_LOG_LOCATION, 'ab')
    log_fh.write("%s: %s" %(logging._levelNames[level], message))
    log_fh.close()




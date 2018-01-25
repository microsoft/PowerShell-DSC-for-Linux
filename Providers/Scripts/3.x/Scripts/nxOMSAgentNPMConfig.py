#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================
from contextlib import contextmanager

import socket
import os
import sys
import imp
import hashlib
import codecs
import base64
import platform
import shutil
import uuid
from fileinput import FileInput
from distutils.version import LooseVersion

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

# Paths
PREFIX_ETC = '/etc/opt/microsoft/omsagent/'
PREFIX_VAR = '/var/opt/microsoft/omsagent/'

RPATH_AGENT_CONF = 'conf/'
RPATH_PLUGIN_CONF = 'conf/omsagent.d/'
RPATH_RUN = 'run/'

FNAME_UDS_SERVER = 'npmdagent.sock'
FNAME_AGENT_CONF = 'npmd_agent_config.xml'
FNAME_NPM_VERSION = 'npm_version'
FNAME_PLUGIN_CONF = 'npmd.conf'

PATH_NPM_PLUGIN = '/opt/microsoft/omsagent/plugin/'
PATH_NPM_STATE = os.path.join(PREFIX_VAR, 'npm_state')
PATH_AGENT_BINARY = '/opt/microsoft/omsagent/plugin/'
PATH_SETCAP_SCRIPT = '/opt/microsoft/omsconfig/Scripts/NPMAgentBinaryCap.sh'

RESOURCE_MODULE_PATH = '/opt/microsoft/omsconfig/modules/nxOMSAgentNPMConfig/DSCResources/MSFT_nxOMSAgentNPMConfigResource/NPM/'
DSC_RESOURCE_VERSION_PATH = '/opt/microsoft/omsconfig/modules/nxOMSAgentNPMConfig/VERSION'
DSC_X64_AGENT_PATH = 'Agent/64/'
DSC_X86_AGENT_PATH = 'Agent/32/'
DSC_PLUGIN_PATH = 'Plugin/plugin/'
DSC_PLUGIN_CONF_PATH = 'Plugin/conf/'

# Constants
X64 = '64bit'
def enum(**enums):
    return type('Enum', (), enums)
Commands = enum(LogNPM = 'ErrorLog', StartNPM = 'StartNPM', StopNPM = 'StopNPM', Config = 'Config', Purge = 'Purge')
LogType  = enum(Error = 'ERROR', Info = 'INFO')

class INPMDiagnosticLog:
    def log(self):
        pass

class NPMDiagnosticLogUtil(INPMDiagnosticLog):
    def log(self, logType, logString):
        # Create a UDS socket
        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

        try:
            message = Commands.LogNPM + ':' + '[' + logType + ']' + logString
            serverAddress = os.path.join(PATH_NPM_STATE, FNAME_UDS_SERVER)
            if not os.path.exists(serverAddress):
                # Dump to DSC log if server sock does not exist
                LG().Log(logType, message)
                return
            # Connect the socket to the port where the server is listening
            sock.connect(serverAddress)
            # Send data
            sock.sendall(message.encode('utf-8'))
        except Exception as msg:
            LG().Log(LogType.Error, str(msg))
        finally:
            sock.close()

LOG_ACTION = NPMDiagnosticLogUtil()

class IOMSAgent:
    def restart_oms_agent(self):
        pass

class OMSAgentUtil(IOMSAgent):
    def restart_oms_agent(self, workspaceId):
        wsId = workspaceId
        if wsId is None:
            wsId = ''
        if os.system('sudo /opt/microsoft/omsagent/bin/service_control restart %s' %(wsId)) == 0:
            return True
        else:
            LOG_ACTION.log(LogType.Error, 'Error restarting omsagent for workspace ' + wsId)
            return False

class INPMAgent:
    def binary_setcap(self):
        pass

class NPMAgentUtil(IOMSAgent):
    def binary_setcap(self, binaryPath):
        if os.path.exists(PATH_SETCAP_SCRIPT) and os.system('sudo %s %s' %(PATH_SETCAP_SCRIPT, binaryPath)) == 0:
            return True
        else:
            LOG_ACTION.log(LogType.Error, 'Error setting capabilities to npmd agent binary.')
            return False

global show_mof
show_mof = False

OMS_ACTION = OMSAgentUtil()
NPM_ACTION = NPMAgentUtil()

#   [key] string ConfigType;
#   [write] string ConfigID;
#   [write] string Contents;
#   [write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
#   [write] string ContentChecksum;

def init_vars(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    if ConfigType is not None and ConfigType != '':
        ConfigType = ConfigType
    else:
        ConfigType = 'UpdatedAgentConfig'
    if ConfigID is not None:
        ConfigID = ConfigID
    else:
        ConfigID = ''
    if Contents is not None:
        Contents = base64.b64decode(Contents.encode('utf-8')).decode('ascii', 'ignore')
    else:
        Contents = ''
    if Ensure is not None and Ensure != '':
        Ensure = Ensure
    else:
        Ensure = 'Present'
    if ContentChecksum is not None:
        ContentChecksum = ContentChecksum
    else:
        ContentChecksum = ''
    return ConfigType, ConfigID, Contents, Ensure, ContentChecksum


def Set_Marshall(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    recvdContentChecksum = hashlib.md5(Contents.encode('utf-8')).hexdigest().upper()
    if recvdContentChecksum != ContentChecksum:
        # data is corrupt do not proceed further
        LG().Log(LogType.Error, 'Content received did not match checksum, exiting Set')
        return [-1]
    (ConfigType, ConfigID, Contents, Ensure, ContentChecksum) = init_vars(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = Set(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    return retval


def Test_Marshall(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    recvdContentChecksum = hashlib.md5(Contents.encode('utf-8')).hexdigest().upper()
    if recvdContentChecksum != ContentChecksum:
        # data is corrupt do not proceed further
        LOG_ACTION.log(LogType.Error, 'Content received did not match checksum, exiting Test for ' + ConfigID)
        return [0]
    (ConfigType, ConfigID, Contents, Ensure, ContentChecksum) = init_vars(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = Test(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    return retval


def Get_Marshall(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    arg_names = list(locals().keys())
    (ConfigType, ConfigID, Contents, Ensure, ContentChecksum) = init_vars(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = 0
    retval = Get(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    ConfigType = protocol.MI_String(ConfigType)
    ConfigID = protocol.MI_String(ConfigID)
    Ensure = protocol.MI_String(Ensure)
    Contents = protocol.MI_String(Contents)
    ContentChecksum = protocol.MI_String(ContentChecksum)

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


############################################################
# Begin user defined DSC functions
############################################################

def SetShowMof(a):
    global show_mof
    show_mof = a


def ShowMof(op, ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    if not show_mof:
        return
    mof = ''
    mof += op + ' nxOMSAgentNPMConfig MyNPMConfig \n'
    mof += '{\n'
    mof += '    ConfigType = "' + ConfigType + '"\n'
    mof += '    ConfigID = "' + ConfigID + '"\n'
    mof += '    Contents = "' + Contents + '"\n'
    mof += '    Ensure = "' + Ensure + '"\n'
    mof += '    ContentChecksum = "' + ContentChecksum + '"\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    Print(mof, file=f)
    LG().Log(LogType.Info, mof)
    f.close()


def Set(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    ShowMof('SET', ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = 0
    if ConfigID == '' or not os.path.exists(os.path.join(PREFIX_ETC, ConfigID)):
        # incorrect config id
        LG().Log(LogType.Error, 'Received nonexistant workspace id ' + ConfigID)
        return [-1]
    if ConfigType != 'UpdatedAgentConfig':
        LG().Log(LogType.Error, 'Config type did not match, exiting set for workspace ' + ConfigID)
        return [-1]
    if SetMultiHoming(ConfigID, Ensure) != 0:
        LG().Log(LogType.Error, 'Set failed for ' + ConfigID + ' and Ensure=' + Ensure)
        retval = -1
        return [retval]

    if Ensure == 'Present':
        if TestConfigUpdate(ConfigID, Contents) != 0:
            retval = SetConfigUpdate(ConfigID, Contents)

        if retval == 0:
            retval = SetFilesUpdate(ConfigID)
    return [retval]


def Test(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    ShowMof('TEST', ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = 0
    if ConfigID == '' or not os.path.exists(os.path.join(PREFIX_ETC, ConfigID)):
        # incorrect config id
        LOG_ACTION.log(LogType.Error, 'Received nonexistant workspace id ' + ConfigID)
        return [retval]
    if not os.path.exists(PATH_SETCAP_SCRIPT):
        LOG_ACTION.log(LogType.Error, 'npmd set cap script does not exist, exiting test')
        return [retval]
    if ConfigType != 'UpdatedAgentConfig':
        LOG_ACTION.log(LogType.Error, 'Config type did not match, exiting test for workspace ' + ConfigID)
        return [retval]
    if TestMultiHoming(ConfigID, Ensure) != 0:
        retval = -1
        return [retval]
    # check for config update or resource version only if ensure is present
    if Ensure == 'Present' and (TestResourceVersion() != 0 or TestConfigUpdate(ConfigID, Contents) != 0):
        retval = -1
    return [retval]


def Get(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    retval = 0
    ShowMof('GET', ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    return [retval]


def Print(s, file=sys.stdout):
    file.write(s + '\n')

# Compare resource version in DSC and agent machine
# Returns
#   0 if version is same
#   dsc version number if there is a mismatch or agent config not present
def TestResourceVersion():
    retval = 0
    dscVersion = ReadFile(DSC_RESOURCE_VERSION_PATH)
    agentVersionFile = os.path.join(PATH_NPM_STATE, FNAME_NPM_VERSION)
    if not os.path.exists(agentVersionFile):
        #npmd agent is not present, copy binaries
        retval = dscVersion
    else:
        agentVersion = ReadFile(agentVersionFile)
        if agentVersion != dscVersion:
            #version mismatch, copy binaries
            retval = dscVersion
    return retval

def TestConfigUpdate(ConfigID, Contents):
    retval = 0
    destFileDirPath = os.path.join(PREFIX_ETC, ConfigID, RPATH_AGENT_CONF)
    destFileFullPath = os.path.join(destFileDirPath, FNAME_AGENT_CONF)
    if not os.path.exists(destFileDirPath):
        LOG_ACTION.log(LogType.Error, 'Conf directory for workspace ' + ConfigID + ' does not exist')
        retval = 0
    elif not os.path.exists(destFileFullPath):
        # Configuration does not exist, fail
        retval = -1
    else:
        origConfigData = ReadFile(destFileFullPath)
        #compare
        if origConfigData is None or origConfigData != Contents:
            retval = -1
    return retval

def TestMultiHoming(ConfigID, Ensure):
    wsRunningNPM = GetWorkspaceRunningNPM()
    if wsRunningNPM is None:
        if os.path.exists(PATH_NPM_STATE):
            LG().Log(LogType.Info, 'NPM State directory exists when NPM is not running, set to clean up')
            return -1
        if Ensure == 'Present':
            LG().Log(LogType.Info, 'NPM should be started for workspace ' + ConfigID + ' set to set it up')
            return -1
    elif not os.path.exists(PATH_NPM_STATE):
        LG().Log(LogType.Info, 'NPM State directory deleted when NPM is running, set to check setup')
        return -1
    if wsRunningNPM == ConfigID and Ensure == 'Absent':
        LG().Log(LogType.Info, 'NPM should be purged, set to purge')
        return -1
    return 0

def SetMultiHoming(ConfigID, Ensure):
    wsRunningNPM = GetWorkspaceRunningNPM()
    retval = 0

    if wsRunningNPM is None:
        if os.path.exists(PATH_NPM_STATE):
            LG().Log(LogType.Info, 'NPM State directory exists when NPM is not running, now removed')
            shutil.rmtree(PATH_NPM_STATE, ignore_errors=True)
        if Ensure == 'Present':
            LG().Log(LogType.Info, 'NPM now getting setup for workspace ' + ConfigID)
            retval = SetupNPM(ConfigID)
    elif not os.path.exists(PATH_NPM_STATE):
        # Ignore case when purge is supposed to be called
        if wsRunningNPM != ConfigID or Ensure != 'Absent':
            LOG_ACTION.log(LogType.Info, 'NPM State directory deleted when NPM is running, now again setting up')
            retval = SetupNPM(wsRunningNPM)
    if wsRunningNPM == ConfigID and Ensure == 'Absent':
        LG().Log(LogType.Info, 'Purging NPM solution')
        if not PurgeSolution(ConfigID):
            LG().Log(LogType.Error, 'Purging NPM solution failed')
            retval = -1

    return retval

def SetConfigUpdate(ConfigID, Contents):
    destFileDirPath = os.path.join(PREFIX_ETC, ConfigID, RPATH_AGENT_CONF)
    destFileFullPath = os.path.join(destFileDirPath, FNAME_AGENT_CONF)

    # Update config after checking if directory exists
    if not os.path.exists(destFileDirPath):
        LG().Log(LogType.Error, 'Conf directory for workspace ' + ConfigID + ' does not exist')
        retval = -1
    else:
        retval = WriteFile(destFileFullPath, Contents)
        if retval == 0:
            LOG_ACTION.log(LogType.Info, 'Updated agent config file for workspace ' + ConfigID)
            if ConfigID == GetWorkspaceRunningNPM():
                NotifyServer(Commands.Config)
        elif retval != 0:
            LOG_ACTION.log(LogType.Error, 'Updating agent config file failed for workspace ' + ConfigID)
    return retval

def SetFilesUpdate(ConfigID):
    retval = True
    version = TestResourceVersion()
    if version != 0:
        retval = UpdateAgentBinary(version)
        retval &= UpdatePluginFiles()
        retval &= UpdatePluginConfFiles(ConfigID)
    if retval:
        return 0
    return -1

def SetupNPM(ConfigID):
    retval = 0
    # Create the npm state directory
    if not os.path.exists(os.path.join(PATH_NPM_STATE)):
        try:
            os.makedirs(PATH_NPM_STATE, 0o755)
        except:
            retval = -1
    if retval == 0:
        retval = SetFilesUpdate(ConfigID)
    return retval

def UpdateAgentBinary(newVersion):
    retval = True
    arch = platform.architecture()
    src = ''
    if arch is not None and arch[0] == X64:
        src = RESOURCE_MODULE_PATH.__add__(DSC_X64_AGENT_PATH)
        retval &= DeleteAllFiles(src, PATH_AGENT_BINARY)
        retval &= CopyAllFiles(src, PATH_AGENT_BINARY)
    else:
        src = RESOURCE_MODULE_PATH.__add__(DSC_X86_AGENT_PATH)
        retval &= DeleteAllFiles(src, PATH_AGENT_BINARY)
        retval &= CopyAllFiles(src, PATH_AGENT_BINARY)

    # set capabilities to binary
    src_files = os.listdir(src)
    for file_name in src_files:
        full_file_name = os.path.join(PATH_AGENT_BINARY, file_name) # assuming only file in directory
        break
    retval &= NPM_ACTION.binary_setcap(full_file_name)

    #Update version number
    if retval == True:
        WriteFile(os.path.join(PATH_NPM_STATE, FNAME_NPM_VERSION), newVersion)
    return retval

def UpdatePluginFiles():
    retval = True
    #replace files
    retval &= DeleteAllFiles(RESOURCE_MODULE_PATH.__add__(DSC_PLUGIN_PATH), PATH_NPM_PLUGIN)
    retval &= CopyAllFiles(RESOURCE_MODULE_PATH.__add__(DSC_PLUGIN_PATH), PATH_NPM_PLUGIN)
    return retval

def UpdatePluginConfFiles(workspaceID):
    retval = True
    # restart oms agent
    if workspaceID is not None:
        pluginConfPath = os.path.join(PREFIX_ETC, workspaceID, RPATH_PLUGIN_CONF)
        retval &= DeleteAllFiles(RESOURCE_MODULE_PATH.__add__(DSC_PLUGIN_CONF_PATH), pluginConfPath)
        retval &= CopyAllFiles(RESOURCE_MODULE_PATH.__add__(DSC_PLUGIN_CONF_PATH), pluginConfPath)
        # Update the plugin conf file to have correct directory info for agent config file
        retval &= UpdateControlDataPathInPluginConfFile(workspaceID)
        retval &= OMS_ACTION.restart_oms_agent(workspaceID)
    return retval

def UpdateControlDataPathInPluginConfFile(workspaceID):
    # Check for presence of the plugin conf file
    confFilePath = os.path.join(PREFIX_ETC, workspaceID, RPATH_PLUGIN_CONF, FNAME_PLUGIN_CONF)
    if not os.path.exists(confFilePath):
        return False

    controlDataDirPath = os.path.join(PREFIX_ETC, workspaceID, RPATH_AGENT_CONF)
    # Update the plugin conf file control data path variable
    for line in FileInput(confFilePath, inplace=True):
        if "%CONF_DIR_WS%" in line:
            line = line.replace("%CONF_DIR_WS%", controlDataDirPath)
        print(line, end='')
    return True

def CopyAllFiles(src, dest):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(src, file_name)
            if (os.path.isfile(full_file_name)):
                shutil.copy(full_file_name, dest)
    except:
        LOG_ACTION.log(LogType.Error, 'copy_all_files failed for src: ' + src + ' dest: ' + dest)
        return False
    return True

# Deletes all files present in both directories
def DeleteAllFiles(src, dest):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(dest, file_name)
            if (os.path.isfile(full_file_name)):
                os.remove(full_file_name)
    except:
        LOG_ACTION.log(LogType.Error, 'delete_all_files failed for src: ' + src + ' dest: ' + dest)
        return False
    return True

def PurgeSolution(ConfigID):
    retval = True

    # remove resource version file
    try:
        confFile = os.path.join(PREFIX_ETC, ConfigID, RPATH_PLUGIN_CONF, FNAME_PLUGIN_CONF)
        if os.path.exists(confFile):
            os.remove(confFile)
    except:
        LOG_ACTION.log(LogType.Error, 'Purge attempt failed')
        retval = False

    # notify ruby plugin to purge agent
    NotifyServer(Commands.Purge)

    return retval

def NotifyServer(command):
    serverAddress = os.path.join(PATH_NPM_STATE, FNAME_UDS_SERVER)
    # Create a UDS socket
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    LG().Log(LogType.Info, 'connecting to ' +  serverAddress)

    try:
        # Connect the socket to the port where the server is listening
        if not os.path.exists(serverAddress):
            return retval
        sock.connect(serverAddress)

        # Send data
        message = command.encode('utf-8')
        LG().Log(LogType.Info, 'sending ' + message.decode('utf-8'))
        sock.sendall(message)
    except Exception as msg:
        LG().Log(LogType.Error, str(msg))
        # restart omsagent if command was config update and sock conn failed
        if (command == Commands.Config):
            currentWsRunningNPM = GetWorkspaceRunningNPM()
            if (currentWsRunningNPM != None):
                OMS_ACTION.restart_oms_agent(currentWsRunningNPM)
    finally:
        LG().Log(LogType.Info, 'closing socket')
        sock.close()

def WriteFile(path, contents):
    retval = 0
    try:
        with open(path, 'w+') as dFile:
            dFile.write(contents)
    except IOError as error:
        errno, strerror = error.args
        LOG_ACTION.log(LogType.Error, "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
        retval = -1
    return retval

def ReadFile(path):
    content = None
    try:
        with codecs.open (path, encoding = 'utf8', mode = "r") as dFile:
            content = dFile.read()
    except IOError as error:
        errno, strerror = error.args
        LOG_ACTION.log(LogType.Error, "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
    return content

def GetWorkspaceListFromDirectories():
    listOfDirs = os.listdir(PREFIX_ETC)
    return filter(IsUUID, listOfDirs)

def GetWorkspaceRunningNPM():
    listOfDirs = GetWorkspaceListFromDirectories()
    for x in listOfDirs:
        if os.path.exists(os.path.join(PREFIX_ETC, x, RPATH_PLUGIN_CONF, FNAME_PLUGIN_CONF)):
            return x
    return None

def IsUUID(uuidStr):
    try:
        uuidOut = uuid.UUID(uuidStr)
    except:
        return False
    return str(uuidOut).encode('utf-8') == str(uuidStr).encode('utf-8')


#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================

import os
import sys
import imp
import re
import codecs
import shutil

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

MODULE_RESOURCE_DIR ='/opt/microsoft/omsconfig/modules/nxOMSContainers/DSCResources/MSFT_nxOMSContainersResource/Containers'

PLUGIN_PATH = '/opt/microsoft/omsagent/plugin/'
CONF_PATH = '/etc/opt/microsoft/omsagent/conf/omsagent.d/'
REG_PATH = '/etc/opt/omi/conf/omiregister/root-cimv2'
LIB_PATH = '/opt/microsoft/docker-cimprov/lib'

class IOMSAgent:
    def restart_oms_agent(self):
        pass
    
class OMSAgentUtil(IOMSAgent):
    def restart_oms_agent(self):
        LG().Log('DEBUG', "Restarting the agent")
        if os.system('sudo /opt/microsoft/omsagent/bin/service_control restart') == 0:
            return True
        else:
            LG().Log('ERROR', 'Error restarting omsagent.')
            return False

class TestOMSAgent(IOMSAgent):
    def restart_oms_agent(self):
        return True

OMS_ACTION = OMSAgentUtil()

def Set_Marshall(ResourceSettings):
    WorkspaceId = "Test Workspace"
    Ensure = ResourceSettings
    LG().Log('DEBUG', "3 SET MARSHAL  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + WorkspaceId + " " + Ensure + "  - - - - - - - - - - - - ")
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')
    return Set(WorkspaceId, Ensure)

def Test_Marshall(ResourceSettings):
    WorkspaceId = "Test Workspace"
    Ensure = ResourceSettings
    LG().Log('DEBUG', "3 TEST MARSHAL  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + WorkspaceId + " " + Ensure + "  - - - - - - - - - - - - ")
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')
    return Test(WorkspaceId, Ensure)

def Get_Marshall(ResourceSettings):
    WorkspaceId = "Test Workspace"
    Ensure = ResourceSettings
    LG().Log('DEBUG', "3 GET MARSHAL  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + WorkspaceId + " " + Ensure + "  - - - - - - - - - - - - ")
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')

    arg_names = list(locals().keys())

    retval = 0
    (retval, Ensure) = Get(WorkspaceId)

    WorkspaceId = protocol.MI_String(WorkspaceId)
    Ensure = protocol.MI_String(Ensure)

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

# for each plugin name plugin module directory
# copy the plugin(s) and conf file  
def Set(WorkspaceId,Ensure):
    LG().Log('DEBUG', "SET ENSURE MARSHAL  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + WorkspaceId + " " + Ensure + "  - - - - - - - - - - - - ")
    if not IsValidWorkspaceId(WorkspaceId):
        return [1]

    # test for the existence of plugin and conf subfolders in the current plugin
    plugin_dir = os.path.join(MODULE_RESOURCE_DIR, "plugin")
    conf_dir = os.path.join(MODULE_RESOURCE_DIR, "conf")
    lib_dir = os.path.join(MODULE_RESOURCE_DIR, "lib")
    reg_dir = os.path.join(MODULE_RESOURCE_DIR, "reg")

    if Ensure == 'Present':
        LG().Log('DEBUG', "SET ENSURE PRESENT MARSHAL  - - - - - - - - - - - - ")
        # copy all files under conf and plugin
        copy_all_files(plugin_dir, PLUGIN_PATH)
        copy_all_files(conf_dir, CONF_PATH)
        copy_all_files(lib_dir, LIB_PATH)
        copy_all_files(reg_dir, REG_PATH)
    elif Ensure == 'Absent':
        LG().Log('DEBUG', "SET ENSURE ABSENT MARSHAL  - - - - - - - - - - - - ")
        # and delete all CONF files in the directory
        delete_all_files(plugin_dir, PLUGIN_PATH)
        delete_all_files(conf_dir, CONF_PATH)
        delete_all_files(lib_dir, LIB_PATH)
        delete_all_files(reg_dir, REG_PATH)
    else:
        # log error Ensure value not expected
        LG().Log('ERROR', "Ensure value: " + Ensure + " not expected")
        return [-1]
    
    # restart oms agent
    if OMS_ACTION.restart_oms_agent():
        return [0]
    else:
        return [-1]

def Get(WorkspaceId):
    LG().Log('DEBUG', "GET ENSURE MARSHAL  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + WorkspaceId + "  - - - - - - - - - - - - ")
    disk_plugins = []
    plugin_dir = os.path.join(MODULE_RESOURCE_DIR, "plugin")
    conf_dir = os.path.join(MODULE_RESOURCE_DIR, "conf")
    lib_dir = os.path.join(MODULE_RESOURCE_DIR, "lib")
    reg_dir = os.path.join(MODULE_RESOURCE_DIR, "reg")
    if (os.path.isdir(plugin_dir) and os.path.isdir(conf_dir)):
        # Test for the existence of BOTH the plugin(s) and conf files
        if (check_all_files(plugin_dir, PLUGIN_PATH) and check_all_files(conf_dir, CONF_PATH) and check_all_files(lib_dir, LIB_PATH) and check_all_files(reg_dir, REG_PATH)):
            disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})

    return disk_plugins

def copy_all_files(src, dest):
    LG().Log('DEBUG', "COPY FILE " + src  + " " + dest + "  - - - - - - - - - - - - ")
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(src, file_name)
            if (os.path.isfile(full_file_name)):
                shutil.copy(full_file_name, dest)
    except:
        LG().Log('ERROR', 'copy_all_files failed for src: ' + src + ' dest: ' + dest)
        return False
            
def delete_all_files(src, dest):
    LG().Log('DEBUG', "DEL FILE " + src  + " " + dest + "  - - - - - - - - - - - - ")
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(dest, file_name)
            if (os.path.isfile(full_file_name)):
                os.remove(full_file_name)
    except:
        LG().Log('ERROR', 'delete_all_files failed for src: ' + src + ' dest: ' + dest)
        return False


def check_all_files(src, dest):
    LG().Log('DEBUG', "Check FILE " + src  + " " + dest + "  - - - - - - - - - - - - ")
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_src_file = os.path.join(src, file_name)
            full_dest_file = os.path.join(dest, file_name)
            if os.path.isfile(full_dest_file):
                if CompareFiles(full_dest_file, full_src_file, "md5") == -1:
                    return False
            else:
                return False
        return True
    except:
        LG().Log('ERROR', 'check_all_files failed for src: ' + src + ' dest: ' + dest)
        return False

def CompareFiles(DestinationPath, SourcePath, Checksum):
    LG().Log('DEBUG', "COMPATE FILE " + SourcePath  + " " + DestinationPath + "  - - - - - - - - - - - - ")
    """
    If the files differ in size, return -1.
    Reading and computing the hash here is done in a block-by-block manner,
    in case the file is quite large.
    """
    if SourcePath == DestinationPath:  # Files are the same!
        return 0
    stat_dest = StatFile(DestinationPath)
    stat_src = StatFile(SourcePath)
    if stat_src.st_size != stat_dest.st_size:
        return -1
    if Checksum == "md5":
        src_error = None
        dest_error = None
        src_hash = md5const()
        dest_hash = md5const()
        src_block = 'loopme'
        dest_block = 'loopme'
        src_file,src_error = opened_bin_w_error(SourcePath, 'rb')
        if src_error:
            Print("Exception opening source file " + SourcePath + " Error : " + str(src_error), file=sys.stderr)
            LG().Log('ERROR', "Exception opening source file " + SourcePath + " Error : " + str(src_error))
            return -1
        dest_file, dest_error = opened_bin_w_error(DestinationPath, 'rb')
        if dest_error:
            Print("Exception opening destination file " + DestinationPath + " Error : " + str(dest_error), file=sys.stderr)
            LG().Log('ERROR', "Exception opening destination file " + DestinationPath + " Error : " + str(dest_error))
            src_file.close()
            return -1
        while src_block != '' and dest_block != '':
            src_block = src_file.read(BLOCK_SIZE)
            dest_block = dest_file.read(BLOCK_SIZE)
            src_hash.update(src_block)
            dest_hash.update(dest_block)
            if src_hash.hexdigest() != dest_hash.hexdigest():
                src_file.close()
                dest_file.close()
                return -1  
        if src_hash.hexdigest() == dest_hash.hexdigest():
            src_file.close()
            dest_file.close()
            return 0  
    elif Checksum == "ctime":
        if stat_src.st_ctime != stat_dest.st_ctime:
            return -1
        else:
            return 0
    elif Checksum == "mtime":
        if stat_src.st_mtime != stat_dest.st_mtime:
            return -1
        else:
            return 0

def Test(WorkspaceId, Ensure):
    LG().Log('DEBUG', "TEST ENSURE MARSHAL  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + WorkspaceId + " " + Ensure + "  - - - - - - - - - - - - ")
    # test for the existence of plugin and conf subfolders in the current plugin
    plugin_dir = os.path.join(MODULE_RESOURCE_DIR, "plugin")
    conf_dir = os.path.join(MODULE_RESOURCE_DIR, "conf")
    lib_dir = os.path.join(MODULE_RESOURCE_DIR, "lib")
    reg_dir = os.path.join(MODULE_RESOURCE_DIR, "reg")
    
    if Ensure == 'Present':
        # check all files exist under conf and dir
        if (not check_all_files(plugin_dir, PLUGIN_PATH) or not check_all_files(conf_dir, CONF_PATH) or not check_all_files(lib_dir, LIB_PATH) or not check_all_files(reg_dir, REG_PATH)):
            return [-1]
    elif Ensure == 'Absent':
        # check all conf files do NOT exist under conf directory
        if (check_all_files(conf_dir, CONF_PATH)):
            return [-1];
    else:
        # log error Ensure value not expected
        LG().Log('ERROR', "Ensure value: " + Ensure + " not expected")
        return [-1]

def IsUUID(uuidStr):
    LG().Log('DEBUG', "isUUID  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + uuidStr + "  - - - - - - - - - - - - ")
    try:
        uuidOut = re.match('^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$', uuidStr, re.I)
    except:
        return False
    return uuidOut is not None

def IsValidWorkspaceId(WorkspaceId):
    LG().Log('DEBUG', "IsValidWorkspaceId  - - - - - - - - - - - - ")
    LG().Log('DEBUG', "PARAMS " + WorkspaceId + "  - - - - - - - - - - - - ")
    if not IsUUID(WorkspaceId):
        return False
    return os.path.isdir(os.path.join(AGENT_VAR_ROOT, WorkspaceId))
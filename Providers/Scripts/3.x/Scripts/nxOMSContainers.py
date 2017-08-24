#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================

from contextlib import contextmanager

import os
import sys
import imp
import re
import pwd
import grp
import codecs
import shutil

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

MODULE_RESOURCE_DIR ='/opt/microsoft/omsconfig/modules/nxOMSContainers/DSCResources/MSFT_nxOMSContainersResource/containers'

PLUGIN_PATH = '/opt/microsoft/omsagent/plugin/'
CONF_PATH = '/etc/opt/microsoft/omsagent/<WorkspaceId>/conf/omsagent.d'
REG_PATH = '/etc/opt/omi/conf/omiregister/root-cimv2'
LIB_PATH = '/opt/microsoft/docker-cimprov/lib'
YAML_PATH = '/var/opt/microsoft/docker-cimprov/state'

class IOMSAgent:
    def restart_oms_agent(self):
        pass
    
class OMSAgentUtil(IOMSAgent):
    def restart_oms_agent(self):
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
    global CONF_PATH
    WorkspaceId,Ensure = ResourceSettings.split(":")
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    CONF_PATH = CONF_PATH.replace('<WorkspaceId>',WorkspaceId)
    Ensure = Ensure.encode('ascii', 'ignore')
    return Set(WorkspaceId, Ensure)

def Test_Marshall(ResourceSettings):
    global CONF_PATH
    WorkspaceId,Ensure = ResourceSettings.split(":")
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')
    CONF_PATH = CONF_PATH.replace('<WorkspaceId>',WorkspaceId)
    return Test(WorkspaceId, Ensure)

def Get_Marshall(ResourceSettings):
    WorkspaceId,Ensure = ResourceSettings.split(":")
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')

    retval = 0
    retd = dict()
    retd['WorkspaceId'] = WorkspaceId
    retd['Ensure'] = Ensure
    return retval, retd
 
def Set(WorkspaceId,Ensure):
    plugin_dir = os.path.join(MODULE_RESOURCE_DIR, "plugin")
    conf_dir = os.path.join(MODULE_RESOURCE_DIR, "conf")
    lib_dir = os.path.join(MODULE_RESOURCE_DIR, "lib")
    reg_dir = os.path.join(MODULE_RESOURCE_DIR, "reg")
    yaml_dir = os.path.join(MODULE_RESOURCE_DIR, "yaml")

    if Ensure == 'Present':
        # copy all the required files to the client machine
        copy_all_files(plugin_dir, PLUGIN_PATH)
        copy_all_files(conf_dir, CONF_PATH)
        copy_all_files(lib_dir, LIB_PATH)
        copy_all_files(reg_dir, REG_PATH)
        check_and_create_yaml(yaml_dir, YAML_PATH)
    elif Ensure == 'Absent':
        # and delete CONF file in the directory
        delete_all_files(conf_dir, CONF_PATH)
    else:
        # log error Ensure value not expected
        LG().Log('ERROR', "Ensure value: " + Ensure + " not expected")
        return [-1]
    
    # restart oms agent
    if OMS_ACTION.restart_oms_agent():
        return [0]
    else:
        return [-1]

def Test(WorkspaceId, Ensure):
    """
    Test method for the DSC resoruce
    If it returns [0] no further action is taken
    If it returns [-1] Set_Marshall is called
    """

    # test for the existence of plugin and conf subfolders in the current plugin
    plugin_dir = os.path.join(MODULE_RESOURCE_DIR, "plugin")
    conf_dir = os.path.join(MODULE_RESOURCE_DIR, "conf")
    lib_dir = os.path.join(MODULE_RESOURCE_DIR, "lib")
    reg_dir = os.path.join(MODULE_RESOURCE_DIR, "reg")
    yaml_dir = os.path.join(MODULE_RESOURCE_DIR, "yaml")
    
    if Ensure == 'Present':
        # check all files exist
        if (not check_all_files(plugin_dir, PLUGIN_PATH) or not check_all_files(conf_dir, CONF_PATH) or not check_all_files(lib_dir, LIB_PATH) or not check_all_files(reg_dir, REG_PATH) or not check_all_files(yaml_dir, YAML_PATH)):
            return [-1]
    elif Ensure == 'Absent':
        return [-1];
    else:
        # log error Ensure value not expected
        LG().Log('ERROR', "Ensure value: " + Ensure + " not expected")
        return [-1]

def copy_all_files(src, dest):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(src, file_name)
            if (os.path.isfile(full_file_name)):
                shutil.copy(full_file_name, dest)
    except:
        LG().Log('ERROR', 'copy_all_files failed for src: ' + src + ' dest: ' + dest)
        return False

def check_and_create_yaml(src, dest):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(src, file_name)
            if (not os.path.isfile(full_file_name)):
                shutil.copy(full_file_name, dest)
                os.chmod(os.path.join(dest, file_name), 0644)
                os.chown(os.path.join(dest, file_name), GetUID('omsagent'), GetGID('omsagent'))
    except:
        LG().Log('ERROR', 'copy_all_files failed for src: ' + src + ' dest: ' + dest)
        return False
            
def delete_all_files(src, dest):
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

def GetUID(User):
    uid = None
    try:
        uid = pwd.getpwnam(User)[2]
    except KeyError:
        Print('ERROR: Unknown UID for ' + User, file=sys.stderr)
        LG().Log('ERROR', 'ERROR: Unknown UID for ' + User)
    return uid


def GetGID(Group):
    gid = None
    try:
        gid = grp.getgrnam(Group)[2]
    except KeyError:
        Print('ERROR: Unknown GID for ' + Group, file=sys.stderr)
        LG().Log('ERROR', 'ERROR: Unknown GID for ' + Group)
    return gid

def StatFile(path):
    """
    Stat the file, following the symlink.
    """
    d = None
    error = None
    try:
        d = os.stat(path)
    except OSError as error:
        Print("Exception stating file " + path  + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception stating file " + path  + " Error: " + str(error))
    except IOError as error:
        Print("Exception stating file " + path  + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception stating file " + path  + " Error: " + str(error))
    return d
    
@contextmanager
def opened_bin_w_error(filename, mode="rb"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except IOError as err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()
#!/usr/bin/env python2
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================

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
CONF_PATH = '/etc/opt/microsoft/omsagent/<WorkspaceID>/conf/omsagent.d'
REG_PATH = '/etc/opt/omi/conf/omiregister/root-cimv2'
LIB_PATH = '/opt/microsoft/docker-cimprov/lib'
YAML_PATH = '/var/opt/microsoft/docker-cimprov/state'
STATE_DIR_PATH = '/var/opt/microsoft/omsagent/<WorkspaceID>/state'

PLUGIN_DIR = os.path.join(MODULE_RESOURCE_DIR, "plugin")
CONF_DIR = os.path.join(MODULE_RESOURCE_DIR, "conf")
REG_DIR = os.path.join(MODULE_RESOURCE_DIR, "reg")
LIB_DIR = os.path.join(MODULE_RESOURCE_DIR, "lib")
YAML_DIR = os.path.join(MODULE_RESOURCE_DIR, "yaml")


class IOMSAgent:
    def restart_oms_agent(self):
        pass
    
class OMSAgentUtil(IOMSAgent):
    def restart_oms_agent(self, WorkspaceID):
        wsId = WorkspaceID
        if wsId is None:
            wsId = ''
        if os.system('sudo /opt/microsoft/omsagent/bin/service_control restart ' + wsId) == 0:
            return True
        else:
            LG().Log('ERROR', 'Error restarting omsagent for workspace ' + wsId)
            return False

class TestOMSAgent(IOMSAgent):
    def restart_oms_agent(self):
        return True

OMS_ACTION = OMSAgentUtil()

def init_vars(WorkspaceID = '', Ensure = ''):
    global CONF_PATH
    WorkspaceID = WorkspaceID.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')
    CONF_PATH = CONF_PATH.replace('<WorkspaceID>',WorkspaceID)

def Set_Marshall(WorkspaceID, Ensure):
    init_vars(WorkspaceID, Ensure)
    return Set(WorkspaceID, Ensure)

def Test_Marshall(WorkspaceID, Ensure):
    init_vars(WorkspaceID, Ensure)
    return Test(WorkspaceID, Ensure)

def Get_Marshall(WorkspaceID, Ensure):
    init_vars(WorkspaceID, Ensure)

    retval = 0
    retd = dict()
    retd['WorkspaceID'] = WorkspaceID
    retd['Ensure'] = Ensure
    return retval, retd
 
def Set(WorkspaceID, Ensure):
    if Ensure == 'Present':
        # copy all the required files to the client machine
        copy_all_files(CONF_DIR, CONF_PATH)
        update_state_dir_path(os.path.join(CONF_PATH, "container.conf"), WorkspaceID)
        copy_all_files(PLUGIN_DIR, PLUGIN_PATH)
        copy_all_files(LIB_DIR, LIB_PATH)
        copy_all_files(REG_DIR, REG_PATH)
        check_and_create_yaml(YAML_DIR, YAML_PATH)
    elif Ensure == 'Absent':
        # and delete CONF file in the directory
        delete_all_files(CONF_DIR, CONF_PATH)
    else:
        # log error Ensure value not expected
        LG().Log('ERROR', "Ensure value: " + Ensure + " not expected")
        return [-1]
    
    # restart oms agent
    if OMS_ACTION.restart_oms_agent(WorkspaceID):
        return [0]
    else:
        return [-1]

def Test(WorkspaceID, Ensure):
    """
    Test method for the DSC resoruce
    If it returns [0] no further action is taken
    If it returns [-1] Set_Marshall is called
    """

    # test for the existence of plugin and conf subfolders in the current plugin
    if Ensure == 'Present':
        # check all files exist
        if (not check_all_files(PLUGIN_DIR, PLUGIN_PATH) or not check_all_files(CONF_DIR, CONF_PATH) or not check_all_files(LIB_DIR, LIB_PATH) or not check_all_files(REG_DIR, REG_PATH) or not check_all_files(YAML_DIR, YAML_PATH)):
            return [-1]
    elif Ensure == 'Absent':
        if (check_conf_presence(conf_dir, CONF_PATH)):
            return [-1]
    else:
        # log error Ensure value not expected
        LG().Log('ERROR', "Ensure value: " + Ensure + " not expected")
        return [-1]

def update_state_dir_path(dest, WorkspaceID):
    replace_text = STATE_DIR_PATH.replace('<WorkspaceID>',WorkspaceID)
    with open(dest) as f:
        s = f.read()

    with open(dest, 'w') as f:
        s = s.replace('%STATE_DIR_WS%', replace_text)
        f.write(s)

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

def check_conf_presence(src, dest):
    src_files = os.listdir(src)
    for file_name in src_files:
        full_dest_file = os.path.join(dest, file_name)
        if os.path.isfile(full_dest_file):
            return True
    return False

def check_and_create_yaml(src, dest):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(src, file_name)
            if (not os.path.isfile(full_file_name)):
                shutil.copy(full_file_name, dest)
                os.chmod(os.path.join(dest, file_name), 0644)
                os.chown(os.path.join(dest, file_name), GetUID('omsagent'), GetGID('omiusers'))
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
            LG().Log('ERROR', "Exception opening source file " + SourcePath + " Error : " + str(src_error))
            return -1
        dest_file, dest_error = opened_bin_w_error(DestinationPath, 'rb')
        if dest_error:
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
        LG().Log('ERROR', 'ERROR: Unknown UID for ' + User)
    return uid


def GetGID(Group):
    gid = None
    try:
        gid = grp.getgrnam(Group)[2]
    except KeyError:
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
        LG().Log('ERROR', "Exception stating file " + path  + " Error: " + str(error))
    except IOError as error:
        LG().Log('ERROR', "Exception stating file " + path  + " Error: " + str(error))
    return d
    
def opened_bin_w_error(filename, mode='rb'):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except IOError, error:
        return None, error
    return f, None
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
import platform

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog
try:
    import hashlib
    hashconst = hashlib.sha256
except ImportError:
    print("Error while importing hashlib")


class IOMSAgent:
    def restart_oms_agent(self):
        pass

    
class OMSAgentUtil(IOMSAgent):
    def restart_oms_agent(self, workspace_id_to_add):
        cmd = 'sudo /opt/microsoft/omsagent/bin/service_control restart'
        process_to_restart = 'omsagent'
        if workspace_id_to_add is not None:
            cmd += ' ' + workspace_id_to_add
            process_to_restart += '-' + workspace_id_to_add
        if os.system(cmd) is 0:
            return True
        else:
            LG().Log('ERROR', 'Error restarting ' + process_to_restart + '.')
            return False


class TestOMSAgent(IOMSAgent):
    def restart_oms_agent(self):
        return True

def pf_arch():
    arch = platform.architecture()
    if len(arch) == 2 and len(arch[0]) > 0:
        if arch[0] == '64bit':
            return "x64"
        elif arch[0] == '32bit':
            return "x86"

    arch = platform.processor()
    if arch == "x86_64":
        return "x64"
    elif arch == "i686":
        return "x86"
    elif arch == "i386":
        return "x86"

    arch = platform.machine()
    if arch == "x86_64":
        return "x64"
    elif arch == "i686":
        return "x86"
    elif arch == "i386":
        return "x86"

    LG().Log('WARN', "Failed to determine the system architecture (64bit or 32bit) the usual way. Relying on 'is_64bit = sys.maxsize > 2**32' instead.")

    if sys.maxsize > 2**32:
        return "x64"
    else:
        return "x86"

BLOCK_SIZE = 8192        
PLUGIN_PATH = '/opt/microsoft/omsagent/plugin/'
ETC_OMSAGENT_DIR = '/etc/opt/microsoft/omsagent/'
CONF_PATH_SUFFIX = 'conf/omsagent.d/'
CONF_PATH = os.path.join(ETC_OMSAGENT_DIR, CONF_PATH_SUFFIX)
MODULE_RESOURCE_DIR = '/opt/microsoft/omsconfig/modules/nxOMSPlugin/DSCResources/MSFT_nxOMSPluginResource'
PLUGIN_MODULE_PATH = os.path.join(MODULE_RESOURCE_DIR, "Plugins")
PLUGIN_ARCH_MODULE_PATH = os.path.join(MODULE_RESOURCE_DIR, pf_arch(), "Plugins")
OMS_ACTION = OMSAgentUtil()
MULTI_HOMED = None


def init_vars(Plugins, WorkspaceID):
    """
    Initialize global variables for this resource
    """
    if Plugins is not None:
        for plugin in Plugins:
            if 'value' in dir(plugin['PluginName']):
                plugin['PluginName'] = plugin['PluginName'].value
            plugin['PluginName'] = plugin['PluginName'].encode('ascii', 'ignore')
            if 'value' in dir(plugin['Ensure']):
                plugin['Ensure'] = plugin['Ensure'].value
            plugin['Ensure'] = plugin['Ensure'].encode('ascii', 'ignore')
    if WorkspaceID is not None:
         WorkspaceID = WorkspaceID.encode('ascii', 'ignore')
    else:
         WorkspaceID = ''

    global MULTI_HOMED
    global CONF_PATH
    mh_conf_dir = os.path.join(ETC_OMSAGENT_DIR, WorkspaceID, CONF_PATH_SUFFIX)
    MULTI_HOMED = os.path.isdir(mh_conf_dir)
    if MULTI_HOMED and WorkspaceID: # only log this if WorkspaceID is not None or empty
        LG().Log('INFO', 'OMSAgent is multi-homed and resource is updating workspace ' + WorkspaceID)
        CONF_PATH = mh_conf_dir


def Set_Marshall(Name, WorkspaceID, Plugins):
    init_vars(Plugins, WorkspaceID)
    return Set(WorkspaceID, Plugins)


def Test_Marshall(Name, WorkspaceID, Plugins):
    init_vars(Plugins, WorkspaceID)
    return Test(Plugins)


def Get_Marshall(Name, WorkspaceID, Plugins):
    arg_names = list(locals().keys())
    init_vars(Plugins, WorkspaceID)
    retval = 0
    local_plugins = Get(Plugins)
    for plugin in local_plugins:
        plugin['PluginName'] = protocol.MI_String(plugin['PluginName'])
        plugin['Ensure'] = protocol.MI_String(plugin['Ensure'])
    Plugins = protocol.MI_InstanceA(local_plugins)
    WorkspaceID = protocol.MI_String(WorkspaceID)
    Name = protocol.MI_String(Name) 
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


def Set(WorkspaceID, Plugins):
    """
    For each plugin name plugin module directory, copy the plugin(s) and conf
    files to the directory that the directory that omsagent uses to run
    (PLUGIN_PATH and CONF_PATH)
    """
    for plugin in Plugins:
        # test for the existence of plugin and conf subfolders in the current plugin
        plugin_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], 'plugin')
        plugin_arch_dir = os.path.join(PLUGIN_ARCH_MODULE_PATH, plugin['PluginName'], 'plugin')
        conf_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], 'conf')
        # 4 cases here:
        # Case 1: The IP has both plugin and conf directories
        # Case 2: The IP has only plugin(s)
        # Case 3: The IP has only conf
        # Case 4: The IP has neither plugin nor conf directory, which is invalid if the MOF has "ensure: present"
        if os.path.isdir(plugin_dir) and os.path.isdir(conf_dir):
            if plugin['Ensure'] == 'Present':
                # copy all files under conf and plugin
                copy_all_files(plugin_dir, PLUGIN_PATH, False)
                copy_all_files(conf_dir, CONF_PATH, False)
            elif plugin['Ensure'] == 'Absent':
                # and delete all CONF files in the directory
                delete_all_files(conf_dir, CONF_PATH)
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        elif os.path.isdir(plugin_dir):
            if plugin['Ensure'] == 'Present':
                # copy all files under plugin
                copy_all_files(plugin_dir, PLUGIN_PATH, False)
            elif plugin['Ensure'] == 'Absent':
                # NO-OP as we do *NOT* remove common plugins
                pass
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        elif os.path.isdir(conf_dir):
            if plugin['Ensure'] == 'Present':
                # copy all file under conf
                copy_all_files(conf_dir, CONF_PATH, False)
            elif plugin['Ensure'] == 'Absent':
                # remove the conf
                delete_all_files(conf_dir, CONF_PATH)
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        else:
            if plugin['Ensure'] == 'Present':
                # log error - neither conf nor plugin directory was found in IP to set
                LG().Log('ERROR', plugin['PluginName'] + ' contains neither plugin nor conf')
                return [-1]
            elif plugin['Ensure'] == 'Absent':
                # log warning - this scenario is unexpected but should not cause plugin set to fail 
                LG().LOG('WARN', plugin['PluginName'] + ' contains neither plugin nor conf, but was not to be installed anyways')
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]

        # Some Plugins (e.g. Security Baseline) have arch specific files
        if os.path.isdir(plugin_arch_dir):
            if plugin['Ensure'] == 'Present':
                # copy all files under plugin
                copy_all_files(plugin_arch_dir, PLUGIN_PATH, True)
            elif plugin['Ensure'] == 'Absent':
                # NO-OP as we do *NOT* remove common plugins
                pass
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        
    # restart omsagent process to pick up new plugins and conf
    if MULTI_HOMED:
        workspace_id_to_add = WorkspaceID
    else:
        workspace_id_to_add = None
    if OMS_ACTION.restart_oms_agent(workspace_id_to_add):
        return [0]
    else:
        return [-1]


def Test(Plugins):
    """
    For each IP plugin inside the plugin module directory, test for the
    existence of plugin(s) and conf files in the directory that omsagent
    uses to run (PLUGIN_PATH and CONF_PATH)
    """
    for plugin in Plugins:
        # test for the existence of plugin and conf subfolders in the current plugin
        plugin_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], 'plugin')
        plugin_arch_dir = os.path.join(PLUGIN_ARCH_MODULE_PATH, plugin['PluginName'], 'plugin')
        conf_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], 'conf')
        # 4 cases here:
        # Case 1: The IP has both plugin and conf directories
        # Case 2: The IP has only plugin(s)
        # Case 3: The IP has only conf
        # Case 4: The IP has neither plugin nor conf directory, which is invalid if the MOF has "ensure: present"
        if os.path.isdir(plugin_dir) and os.path.isdir(conf_dir):
            if plugin['Ensure'] == 'Present':
                # check all files exist under conf and dir
                if (not check_all_files(plugin_dir, PLUGIN_PATH, False)
                        or not check_all_files(conf_dir, CONF_PATH, False)):
                    return [-1]
            elif plugin['Ensure'] == 'Absent':
                # check all conf files do NOT exist under conf directory
                if check_all_files(conf_dir, CONF_PATH, False):
                    return [-1];
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        elif os.path.isdir(plugin_dir):
            if plugin['Ensure'] == 'Present':
                # check all files exist under conf and dir
                if not check_all_files(plugin_dir, PLUGIN_PATH, False):
                    return [-1]
            elif plugin['Ensure'] == 'Absent':
                # NO-OP as we do *NOT* test for the absence of common plugins
                pass
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        elif os.path.isdir(conf_dir):
            if plugin['Ensure'] == 'Present':
                # check all files exist under conf and dir
                if not check_all_files(conf_dir, PLUGIN_PATH, False):
                    return [-1]
            elif plugin['Ensure'] == 'Absent':
                # check all conf files do NOT exist under conf directory
                if check_all_files(conf_dir, CONF_PATH, False):
                    return [-1];
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        else:
            if plugin['Ensure'] == 'Present':
                # log error - neither conf nor plugin directory was found in IP to set
                LG().Log('ERROR', plugin['PluginName'] + ' contains neither plugin nor conf')
                return [-1]
            elif plugin['Ensure'] == 'Absent':
                # log warning - this scenario is unexpected but should not cause plugin test to fail 
                LG().LOG('WARN', plugin['PluginName'] + ' contains neither plugin nor conf, but was not to be installed anyways')
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]

        # Some Plugins (e.g. Security Baseline) have arch specific files
        if os.path.isdir(plugin_arch_dir):
            if plugin['Ensure'] == 'Present':
                # check all files exist under conf and dir
                if not check_all_files(plugin_arch_dir, PLUGIN_PATH, True):
                    return [-1]
            elif plugin['Ensure'] == 'Absent':
                # NO-OP as we do *NOT* test for the absence of common plugins
                pass
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', 'Ensure value: ' + plugin['Ensure'] + ' not expected')
                return [-1]
        
    # files are all present and hash matches
    return [0]


def Get(Plugins):
    """
    For each plugin and conf in the module, check for its existence against
    what exists in the directory that omsagent uses to run (PLUGIN_PATH and
    CONF_PATH)
    """
    disk_plugins = []
    module_plugins = get_immediate_subdirectories(PLUGIN_MODULE_PATH)
    for plugin_name in module_plugins:
        plugin_dir = os.path.join(PLUGIN_MODULE_PATH, plugin_name, 'plugin')
        plugin_arch_dir = os.path.join(PLUGIN_ARCH_MODULE_PATH, plugin_name, 'plugin')
        conf_dir = os.path.join(PLUGIN_MODULE_PATH, plugin_name, 'conf')
        if os.path.isdir(plugin_dir) and os.path.isdir(plugin_arch_dir) and os.path.isdir(conf_dir):
            # Test for the existence of the plugin(s) arch specific plugin files and conf files
            if (check_all_files(plugin_dir, PLUGIN_PATH, False)
                    and check_all_files(plugin_arch_dir, PLUGIN_PATH, True)
                    and check_all_files(conf_dir, CONF_PATH, False)):
                disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})
        elif os.path.isdir(plugin_dir) and os.path.isdir(conf_dir):
            # Test for the existence of BOTH the plugin(s) and conf files
            if (check_all_files(plugin_dir, PLUGIN_PATH, False)
                    and check_all_files(conf_dir, CONF_PATH, False)):
                disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})
        elif os.path.isdir(plugin_dir):
            # Test for the existence of ONLY the plugin(s)
            if check_all_files(plugin_dir, PLUGIN_PATH, False):
                disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})
        elif os.path.isdir(conf_dir):
            # Test for the existence of ONLY the conf
            if check_all_files(conf_dir, CONF_PATH, False):
                disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})
    disk_plugins.sort()
    return disk_plugins

    
def get_immediate_subdirectories(a_dir):
    try:
        subdirectories = [name for name in os.listdir(a_dir)
                if os.path.isdir(os.path.join(a_dir, name))]
        return subdirectories
    except:
        LG().Log('ERROR', 'get_immediate_subdirectories failed for ' + a_dir
                          + ' with error ' + str(sys.exc_info()[0]))
        return []

# If is_exec is True, the files will be made executable (e.g. chmod ugo+x).
# Some of the files being copied might not need to be executable but it
# doesn't cause any harm to make it true for all files being copied from
# a source dir.
def copy_all_files(src, dest, is_exec):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_src_file = os.path.join(src, file_name)
            full_dest_file = os.path.join(dest, file_name)
            if os.path.isfile(full_src_file):
                shutil.copy(full_src_file, dest)
                if is_exec:
                    mode = os.stat(full_dest_file).st_mode
                    mode |= 0555
                    os.chmod(full_dest_file, mode)
    except:
        LG().Log('ERROR', 'copy_all_files failed for src: ' + src + ' dest: '
                          + dest + ' with error ' + str(sys.exc_info()[0]))
        return False

            
def delete_all_files(src, dest):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_file_name = os.path.join(dest, file_name)
            if os.path.isfile(full_file_name):
                os.remove(full_file_name)
    except:
        LG().Log('ERROR', 'delete_all_files failed for src: ' + src + ' dest: '
                          + dest + ' with error ' + str(sys.exc_info()[0]))
        return False


def check_all_files(src, dest, is_exec):
    try:
        src_files = os.listdir(src)
        for file_name in src_files:
            full_src_file = os.path.join(src, file_name)
            full_dest_file = os.path.join(dest, file_name)
            if os.path.isfile(full_dest_file):
                if CompareFiles(full_dest_file, full_src_file, 'sha256') == -1:
                    return False
                if is_exec:
                    mode = os.stat(full_dest_file).st_mode
                    if mode & 0555 != 0555:
                        return False
            else:
                return False
        return True
    except:
        LG().Log('ERROR', 'check_all_files failed for src: ' + src + ' dest: '
                          + dest + ' with error ' + str(sys.exc_info()[0]))
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
    if Checksum == 'sha256':
        src_error = None
        dest_error = None
        src_hash = hashconst()
        dest_hash = hashconst()
        src_block = 'loopme'
        dest_block = 'loopme'
        src_file, src_error = opened_bin_w_error(SourcePath, 'rb')
        if src_error:
            print_error('Exception opening source file ' + SourcePath
                        + ' Error : ' + str(src_error))
            return -1
        dest_file, dest_error = opened_bin_w_error(DestinationPath, 'rb')
        if dest_error:
            print_error('Exception opening destination file ' + DestinationPath
                        + ' Error : ' + str(dest_error))
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
    elif Checksum == 'ctime':
        if stat_src.st_ctime != stat_dest.st_ctime:
            return -1
        else:
            return 0
    elif Checksum == 'mtime':
        if stat_src.st_mtime != stat_dest.st_mtime:
            return -1
        else:
            return 0


def StatFile(path):
    """
    Stat the file, following the symlink.
    """
    d = None
    error = None
    try:
        d = os.stat(path)
    except OSError, error:
        print_error('Exception stating file ' + path  + ' Error: '
                    + str(error))
    except IOError, error:
        print_error('Exception stating file ' + path  + ' Error: '
                    + str(error))
    return d


def print_error(message):
    """
    Print the message in both the DSC debugging file and the DSC LG Log
    """
    try:
        Print(message, file=sys.stderr)
        LG().Log('ERROR', message)
    except:
        pass


def opened_bin_w_error(filename, mode='rb'):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except IOError, error:
        return None, error
    return f, None

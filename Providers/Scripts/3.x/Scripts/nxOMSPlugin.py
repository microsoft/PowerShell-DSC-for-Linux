#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================

from contextlib import contextmanager

import os
import sys
import imp
import re
import codecs
import shutil
import pdb

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog
try:
    import hashlib
    md5const = hashlib.md5
except ImportError:
    import md5
    md5const = md5.md5

BLOCK_SIZE = 8192

# [ClassVersion("1.0.0"), FriendlyName("nxOMSPlugin")]
# class MSFT_nxOMSPlugin
# {
    # [Key] string PluginName;
    # [Write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure; 
# };
 
# [ClassVersion("1.0.0")] 
# class MSFT_nxOMSPluginResource : OMI_BaseResource
# {
    # [key, EmbeddedInstance("MSFT_nxOMSPlugin") : ToSubclass] string Plugins[];
# };
    
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
        
PLUGIN_PATH = '/opt/microsoft/omsagent/plugin/'
CONF_PATH = '/etc/opt/microsoft/omsagent/conf/omsagent.d/'
PLUGIN_MODULE_PATH = '/opt/microsoft/omsconfig/modules/nxOMSPlugin/DSCResources/MSFT_nxOMSPluginResource/Plugins'
OMS_ACTION = OMSAgentUtil()

def init_vars(Plugins):
    if Plugins is not None:
        for plugin in Plugins:
            if 'value' in dir(plugin['PluginName']):
                plugin['PluginName'] = plugin['PluginName'].value
            plugin['PluginName'] = plugin['PluginName'].encode('ascii', 'ignore')
            if 'value' in dir(plugin['Ensure']):
                plugin['Ensure'] = plugin['Ensure'].value
            plugin['Ensure'] = plugin['Ensure'].encode('ascii', 'ignore')

def Set_Marshall(Name, Plugins):
    init_vars(Plugins)
    return Set(Plugins)

def Test_Marshall(Name, Plugins):
    init_vars(Plugins)
    return Test(Plugins)

def Get_Marshall(Name, Plugins):
    arg_names = list(locals().keys())
    init_vars(Plugins)
    retval = 0
    local_plugins = Get(Plugins)
    for plugin in local_plugins:
        plugin['PluginName'] = protocol.MI_String(plugin['PluginName'])
        plugin['Ensure'] = protocol.MI_String(plugin['Ensure'])
    Plugins = protocol.MI_InstanceA(local_plugins)
    Name = protocol.MI_String(Name) 
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

# for each plugin name plugin module directory
# copy the plugin(s) and conf file  
def Set(Plugins):
    for plugin in Plugins:
        # test for the existence of plugin and conf subfolders in the current plugin
        if type(plugin['PluginName']) == bytes:
            plugin['PluginName'] = plugin['PluginName'].decode('utf-8')
        if type(plugin['Ensure']) == bytes:
            plugin['Ensure'] = plugin['Ensure'].decode('utf-8')
        plugin_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], "plugin")
        conf_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], "conf")
        # 4 cases here:
        # Case 1: The IP has both plugin and conf directories (i.e. BlueStripe, ChangeTracking)
        # Case 2: The IP has only plugin(s) (i.e. Common)
        # Case 3: The IP has only conf (i.e. CustomLog)
        # Case 4: The IP does not have either plugin or conf directory - this is invalid!
        if (os.path.isdir(plugin_dir) and os.path.isdir(conf_dir)):
            if plugin['Ensure'] == 'Present':
                # copy all files under conf and plugin
                copy_all_files(plugin_dir, PLUGIN_PATH)
                copy_all_files(conf_dir, CONF_PATH)
            elif plugin['Ensure'] == 'Absent':
                # and delete all CONF files in the directory
                delete_all_files(conf_dir, CONF_PATH)
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', "Ensure value: " + plugin['Ensure'] + " not expected")
                return [-1]
        elif (os.path.isdir(plugin_dir)):
            if plugin['Ensure'] == 'Present':
                # copy all files under plugin
                copy_all_files(plugin_dir, PLUGIN_PATH)
            elif plugin['Ensure'] == 'Absent':
                # NO-OP as we do *NOT* remove common plugins
                pass
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', "Ensure value: " + plugin['Ensure'] + " not expected")
                return [-1]
        elif (os.path.isdir(conf_dir)):
            if plugin['Ensure'] == 'Present':
                # copy all file under conf
                copy_all_files(conf_dir, CONF_PATH)
            elif plugin['Ensure'] == 'Absent':
                # remove the conf
                delete_all_files(conf_dir, CONF_PATH)
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', "Ensure value: " + plugin['Ensure'] + " not expected")
                return [-1]
        else:
            # log error - neither conf nor plugin directory was found in IP to set
            LG().Log('ERROR', plugin['PluginName'] + " does not contain neither plugin nor conf")
            return [-1]
        
    # restart oms agent
    if OMS_ACTION.restart_oms_agent():
        return [0]
    else:
        return [-1]

# for each IP plugin inside the plugin module directory
# test for the existence of plugin(s) and conf file
def Test(Plugins):
    for plugin in Plugins:
        # test for the existence of plugin and conf subfolders in the current plugin
        if type(plugin['PluginName']) == bytes:
            plugin['PluginName'] = plugin['PluginName'].decode('utf-8')
        if type(plugin['Ensure']) == bytes:
            plugin['Ensure'] = plugin['Ensure'].decode('utf-8')
        plugin_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], "plugin")
        conf_dir = os.path.join(PLUGIN_MODULE_PATH, plugin['PluginName'], "conf")
        # 4 cases here:
        # Case 1: The IP has both plugin and conf directories (i.e. BlueStripe, ChangeTracking)
        # Case 2: The IP has only plugin(s) (i.e. Common)
        # Case 3: The IP has only conf (i.e. CustomLog)
        # Case 4: The IP does not have either plugin or conf directory - this is invalid!
        if (os.path.isdir(plugin_dir) and os.path.isdir(conf_dir)):
            if plugin['Ensure'] == 'Present':
                # check all files exist under conf and dir
                if (not check_all_files(plugin_dir, PLUGIN_PATH) or not check_all_files(conf_dir, CONF_PATH)):
                    return [-1]
            elif plugin['Ensure'] == 'Absent':
                # check all conf files do NOT exist under conf directory
                if (check_all_files(conf_dir, CONF_PATH)):
                    return [-1];
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', "Ensure value: " + plugin['Ensure'] + " not expected")
                return [-1]
        elif (os.path.isdir(plugin_dir)):
            if plugin['Ensure'] == 'Present':
                # check all files exist under conf and dir
                if (not check_all_files(plugin_dir, PLUGIN_PATH)):
                    return [-1]
            elif plugin['Ensure'] == 'Absent':
                # NO-OP as we do *NOT* test for the absence of common plugins
                pass
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', "Ensure value: " + plugin['Ensure'] + " not expected")
                return [-1]
        elif (os.path.isdir(conf_dir)):
            if plugin['Ensure'] == 'Present':
                # check all files exist under conf and dir
                if (not check_all_files(conf_dir, PLUGIN_PATH)):
                    return [-1]
            elif plugin['Ensure'] == 'Absent':
                # check all conf files do NOT exist under conf directory
                if (check_all_files(conf_dir, CONF_PATH)):
                    return [-1];
            else:
                # log error Ensure value not expected
                LG().Log('ERROR', "Ensure value: " + plugin['Ensure'] + " not expected")
                return [-1]
        else:
            # log error - neither conf nor plugin directory was found in IP
            LG().Log('ERROR', plugin['PluginName'] + " does not contain neither plugin nor conf")
            return [-1]
        
    # files are all present and hash matches
    return [0]

# for each plugin and conf in the module, check for the existence of those 
# plugins and conf with what exists in PLUGIN_PATH and CONF_PATH
def Get(Plugins):
    disk_plugins = []
    module_plugins = get_immediate_subdirectories(PLUGIN_MODULE_PATH)
    for plugin_name in module_plugins:
        if type(plugin_name) == bytes:
            plugin_name = plugin_name.decode('utf-8')

        plugin_dir = os.path.join(PLUGIN_MODULE_PATH, plugin_name, "plugin")
        conf_dir = os.path.join(PLUGIN_MODULE_PATH, plugin_name, "conf")
        if (os.path.isdir(plugin_dir) and os.path.isdir(conf_dir)):
            # Test for the existence of BOTH the plugin(s) and conf files
            if (check_all_files(plugin_dir, PLUGIN_PATH) and check_all_files(conf_dir, CONF_PATH)):
                disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})
        elif (os.path.isdir(plugin_dir)):
            # Test for the existence of ONLY the plugin(s)
            if (check_all_files(plugin_dir, PLUGIN_PATH)):
                disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})
        elif (os.path.isdir(conf_dir)):
            # Test for the existence of ONLY the conf
            if (check_all_files(conf_dir, CONF_PATH)):
                disk_plugins.append({'PluginName': plugin_name, 'Ensure': 'Present'})
    return disk_plugins
    
def get_immediate_subdirectories(a_dir):
    try:
        subdirectories = [name for name in os.listdir(a_dir)
                if os.path.isdir(os.path.join(a_dir, name))]
        return subdirectories
    except:
        LG().Log('ERROR', 'get_immediate_subdirectories failed for ' + a_dir)
        return []
            
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
        src_block = b'loopme'
        dest_block = b'loopme'
        with opened_bin_w_error(SourcePath, 'rb') as (src_file, src_error):
            if src_error:
                print("Exception opening source file " + SourcePath  + " Error Code: " + str(src_error.errno) +
                      " Error: " + src_error.strerror, file=sys.stderr)
                LG().Log('ERROR', "Exception opening source file " + SourcePath + " Error Code: " + str(src_error.errno) +
                        " Error: " + src_error.strerror)
                return -1
            with opened_bin_w_error(DestinationPath, 'rb') as (dest_file, dest_error):
                if dest_error:
                    print("Exception opening destination file " + DestinationPath + " Error Code: " + str(dest_error.errno) +
                          " Error: " + dest_error.strerror, file=sys.stderr)
                    LG().Log('ERROR', "Exception opening destination file " + DestinationPath + " Error Code: " + str(dest_error.errno) +
                          " Error: " + dest_error.strerror)
                    return -1
                while src_block and dest_block :
                    src_block = src_file.read(BLOCK_SIZE)
                    dest_block = dest_file.read(BLOCK_SIZE)
                    src_hash.update(src_block)
                    dest_hash.update(dest_block)
                    if src_hash.hexdigest() != dest_hash.hexdigest():
                        return -1
                    if src_hash.hexdigest() == dest_hash.hexdigest():
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

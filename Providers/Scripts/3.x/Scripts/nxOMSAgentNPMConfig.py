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
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

global show_mof
show_mof = False
CONFIG_PATH = '/etc/opt/microsoft/omsagent/conf/'
SERVER_ADDRESS = '/var/opt/microsoft/omsagent/run/npmdagent.sock'
DEST_FILE_NAME = 'npmd_agent_config'

#   [key] string ConfigType;
#   [write] string ConfigID;
#   [write] string Contents;
#   [write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
#   [write] string ContentChecksum;

def init_vars(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    if ConfigType is not None and ConfigType != '':
        ConfigType = ConfigType.encode('ascii', 'ignore')
    else:
        ConfigType = 'UpdatedAgentConfig'
    if ConfigID is not None:
        ConfigID = ConfigID.encode('ascii', 'ignore')
    else:
        ConfigID = ''
    if Contents is not None:
        Contents = base64.b64decode(Contents)#Contents.encode('ascii', 'ignore')
    else:
        Contents = ''
    if Ensure is not None and Ensure != '':
        Ensure = Ensure.encode('ascii', 'ignore')
    else:
        Ensure = 'Present'
    if ContentChecksum is not None:
        ContentChecksum = ContentChecksum.encode('ascii', 'ignore')
    else:
        ContentChecksum = ''
    return ConfigType, ConfigID, Contents, Ensure, ContentChecksum


def Set_Marshall(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    recvdContentChecksum = hashlib.md5(Contents).hexdigest()
    if recvdContentChecksum != ContentChecksum:
        # data is corrupt do not proceed further
        LG().Log('ERROR', 'Content received did not match checksum, exiting Set')
        return [-1]
    (ConfigType, ConfigID, Contents, Ensure, ContentChecksum) = init_vars(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = Set(ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    return retval


def Test_Marshall(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    recvdContentChecksum = hashlib.md5(Contents).hexdigest()
    if recvdContentChecksum != ContentChecksum:
        # data is corrupt do not proceed further
        LG().Log('ERROR', 'Content received did not match checksum, exiting Test')
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
    LG().Log('INFO', mof)
    f.close()


def Set(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    ShowMof('SET', ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = 0
    destFileFullPath = CONFIG_PATH.__add__(DEST_FILE_NAME)
    if ConfigType != 'UpdatedAgentConfig':
        LG().Log('ERROR', 'Config type did not match, exiting set')
        return [-1]
    if Ensure != 'Present':
        LG().Log('INFO', 'Ensure is not present, exiting set')
        return [retval]

    # Update config after checking if directory exists
    if not os.path.exists(CONFIG_PATH):
        LG().Log('ERROR', 'CONFIG_PATH does not exist')
        retval = -1
    else:
        retval = WriteFile(destFileFullPath, Contents)
        if retval == 0:
            LG().Log('INFO', 'Updated the file, going to notify server')
            retval = NotifyServer()
    return [retval]


def Test(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    ShowMof('TEST', ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    retval = 0
    destFileFullPath = CONFIG_PATH.__add__(DEST_FILE_NAME)
    if ConfigType != 'UpdatedAgentConfig':
        LG().Log('ERROR', 'Config type did not match, exiting test')
        return [retval]
    if Ensure != 'Present':
        LG().Log('INFO', 'Ensure is not present, exiting test')
        return [retval]

    if not os.path.exists(CONFIG_PATH):
        LG().Log('ERROR', 'CONFIG_PATH does not exist')
        retval = 0
    elif not os.path.exists(destFileFullPath):
        # Configuration does not exist, fail
        retval = -1
    else:
        origConfigData = ReadFile(destFileFullPath)
        #compare
        if origConfigData is None or origConfigData != Contents:
            retval = -1
    return [retval]


def Get(ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
    retval = 0
    ShowMof('GET', ConfigType, ConfigID, Contents, Ensure, ContentChecksum)
    return [retval]


def Print(s, file=sys.stdout):
    file.write(s + '\n')

def NotifyServer():
    retval = 0
    # Create a UDS socket
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    LG().Log('INFO', 'connecting to ' +  SERVER_ADDRESS)

    try:
        # Connect the socket to the port where the server is listening
        sock.connect(SERVER_ADDRESS)

        # Send data
        message = 'UpdatedAgentConfig'
        LG().Log('INFO', 'sending ' + message)
        sock.sendall(message)
    except Exception, msg:
        LG().Log('ERROR', str(msg))
        retval = -1
    finally:
        LG().Log('INFO', 'closing socket')
        sock.close()
    return retval

def WriteFile(path, contents):
    retval = 0
    try:
        with open(path, 'w+') as dFile:
            dFile.write(contents)
    except IOError, error:
        LG().Log('ERROR', "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
        retval = -1
    return retval

def ReadFile(path):
    content = None
    try:
        with codecs.open (path, encoding = 'utf8', mode = "r") as dFile:
            content = dFile.read()
    except IOError, error:
        LG().Log('ERROR', "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)        
    return content


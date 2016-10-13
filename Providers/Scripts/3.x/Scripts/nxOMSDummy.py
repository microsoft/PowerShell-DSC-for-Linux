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

def init_vars(Properties):
    if Properties is not None:
        for property in Properties:
            if 'value' in dir(property['Name']):
                property['Name'] = property['Name'].value
            property['Name'] = property['Name'].encode('ascii', 'ignore')
            if 'value' in dir(property['Ensure']):
                property['Ensure'] = property['Ensure'].value
            property['Ensure'] = property['Ensure'].encode('ascii', 'ignore')

def Set_Marshall(Name, Properties):
    init_vars(Properties)
    #return Set(Properties)
    return [0]

def Test_Marshall(Name, Properties):
    init_vars(Properties)
    #return Test(Properties)
    return [0]

def Get_Marshall(Name, Properties):
    arg_names = list(locals().keys())
    init_vars(Properties)
    retval = 0
    #local_properties = Get(Properties)
    #for property in local_properties:
    #    property['PluginName'] = protocol.MI_String(property['Name'])
    #    property['Ensure'] = protocol.MI_String(property['Ensure'])
    #Properties= protocol.MI_InstanceA(local_properties)
    #Name = protocol.MI_String(Name)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


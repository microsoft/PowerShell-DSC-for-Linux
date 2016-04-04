#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

import os
import imp
import re
import codecs
import shutil
import string

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

conf_path = '/etc/opt/microsoft/omsagent/conf/omsagent.d/customlog.conf'

def init_vars(CustomLogObjects):
    new_customlogs = []
    if CustomLogObjects is not None :
        for customlog in CustomLogObjects:
            if customlog['LogName'].value is not None:
                customlog['LogName']=customlog['LogName'].value.encode('ascii','ignore')

                new_filepaths = []
                if customlog['FilePath'] is not None and len(customlog['FilePath'].value) > 0:
                    for filepath in customlog['FilePath'].value:
                        if filepath is not None and len(filepath) > 0:
                            new_filepaths.append(filepath.encode('ascii','ignore'))

                if len(new_filepaths) > 0:
                    customlog['FilePath'] = new_filepaths
                    new_customlogs.append(customlog)

    CustomLogObjects = new_customlogs
    
def Set_Marshall(Name, EnableCustomLogConfiguration = False, CustomLogObjects = None):
    init_vars(CustomLogObjects)
    Set(EnableCustomLogConfiguration, CustomLogObjects)
    return [0]

def Test_Marshall(Name, EnableCustomLogConfiguration = False, CustomLogObjects = None):
    init_vars(CustomLogObjects)
    return Test(EnableCustomLogConfiguration, CustomLogObjects)

def Get_Marshall(Name, EnableCustomLogConfiguration = False, CustomLogObjects = None):
    arg_names = list(locals().keys())
    init_vars(CustomLogObjects)
    
    CurrentCustomLogObjects = Get(EnableCustomLogConfiguration, CustomLogObjects)
    Name = protocol.MI_String(Name)
    EnableCustomLogConfiguration = protocol.MI_Boolean(EnableCustomLogConfiguration)
    for customlog in CurrentCustomLogObjects:
        customlog['LogName'] = protocol.MI_String(customlog['LogName'])
        if customlog['FilePath'] is not None and len(customlog['FilePath']):
            customlog['FilePath'] = protocol.MI_StringA(customlog['FilePath'])
    CustomLogObjects = protocol.MI_InstanceA(CurrentCustomLogObjects)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return 0, retd
            
def Set(EnableCustomLogConfiguration, CustomLogObjects):
    if Test(EnableCustomLogConfiguration, CustomLogObjects) == [0]:
        return [0]

    UpdateConf(CustomLogObjects)

    return [0]

def Test(EnableCustomLogConfiguration, CustomLogObjects):
    if EnableCustomLogConfiguration:
        CurrentCustomLogObjects = ReadConf()
        if CurrentCustomLogObjects is None and CustomLogObjects is None:
            return [0]
        elif CurrentCustomLogObjects is None or CustomLogObjects is None:
            return [-1]
        
        CustomLogObjects.sort()
        for customlog in CustomLogObjects:
            customlog['FilePath'].sort()

        CurrentCustomLogObjects.sort()
        for customlog in CurrentCustomLogObjects:
            customlog['FilePath'].sort()

        if CustomLogObjects != CurrentCustomLogObjects:
            return [-1]

    return [0]

def Get(EnableCustomLogConfiguration, CustomLogObjects):
    CurrentCustomLogObjects = ReadConf()
    return CurrentCustomLogObjects 

def ReadConf():
    if not os.path.isfile(conf_path):
        return [];
    txt = codecs.open(conf_path, 'r', 'utf8').read().encode('ascii','ignore')
    customlog_src_srch_str=r'\n<source>\n  type tail.*?path (.*?)\n.*?pos_file /var/opt/microsoft/omsagent/state/(.*?)\.pos.*?tag oms\.blob\.CustomLog\.(.*?)\.\*.*?format none.*?</source>\n'
    customlog_src_srch=re.compile(customlog_src_srch_str,re.M|re.S)
    new_customlogs=[]
    sources=customlog_src_srch.findall(txt)
    for source in sources:
        s_filepaths=[]
        if len(source[0]):
            s_filepaths = source[0].split(',')
        logname=source[1]
        new_customlogs.append({'FilePath':s_filepaths,'LogName':logname})
    return new_customlogs
            
    
def UpdateConf(CustomLogObjects):
    header = '# this file is configured by the OMS service\n'
    new_source = ''
    if CustomLogObjects is not None:
        for customlog in CustomLogObjects:
            logname = customlog['LogName']
            filepaths = ','.join(customlog['FilePath'])
            new_source+='\n<source>\n  type tail\n  path ' + filepaths + '\n  pos_file /var/opt/microsoft/omsagent/state/' + logname + '.pos\n  read_from_head true\n  tag oms.blob.CustomLog.' + logname + '.*\n  format none\n</source>\n'
    txt = header + new_source
    if os.path.isfile(conf_path): 
        shutil.copy2(conf_path, conf_path + '.bak')
    codecs.open(conf_path, 'w', 'utf8').write(txt)
    os.system('sudo /opt/microsoft/omsagent/bin/service_control restart')

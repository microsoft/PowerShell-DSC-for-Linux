#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================

import os
import imp
import re
import codecs
import json
from functools import reduce
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

conf_path = '/etc/opt/microsoft/omsagent/conf/omsagent.conf'
omi_map_path = '/etc/opt/microsoft/omsagent/conf/omsagent.d/omi_mapping.json'
omi_map = None

def init_omi_map():
    global omi_map
    txt = codecs.open(omi_map_path, 'r', 'utf8').read()
    omi_map = eval(txt)


def init_vars(HeartbeatIntervalSeconds, PerfObject):
    init_omi_map()
    if PerfObject is not None:
        for perf in PerfObject:
            new_perfs = []
            if len(perf['PerformanceCounter'].value):
                for perf_counter in perf['PerformanceCounter'].value:
                    new_perfs.append(perf_counter)
                perf['PerformanceCounter'] = new_perfs
            if perf['InstanceName'].value is None:
                perf['InstanceName'] = ''
            else:
                perf['InstanceName'] = perf['InstanceName'].value
            if perf['ObjectName'].value is None:
                perf['ObjectName'] = ''
            else:
                perf['ObjectName'] = perf['ObjectName'].value
            if perf['AllInstances'].value is None:
                perf['AllInstances'] = False
            else:
                perf['AllInstances'] = perf['AllInstances'].value.value
            perf['IntervalSeconds'] = perf['IntervalSeconds'].value.value


def Set_Marshall(HeartbeatIntervalSeconds, PerfObject):
    init_vars(HeartbeatIntervalSeconds, PerfObject)
    return Set(HeartbeatIntervalSeconds, PerfObject)


def Test_Marshall(HeartbeatIntervalSeconds, PerfObject):
    init_vars(HeartbeatIntervalSeconds, PerfObject)
    return Test(HeartbeatIntervalSeconds, PerfObject)


def Get_Marshall(HeartbeatIntervalSeconds, PerfObject):
    arg_names = list(locals().keys())
    init_vars(HeartbeatIntervalSeconds, PerfObject)
    retval = 0
    NewHeartbeatIntervalSeconds, NewPerf = Get(
        HeartbeatIntervalSeconds, PerfObject)
    for perf in NewPerf:
        if len(perf['PerformanceCounter']):
            perf['PerformanceCounter'] = protocol.MI_StringA(
                perf['PerformanceCounter'])
        perf['ObjectName'] = protocol.MI_String(perf['ObjectName'])
        perf['InstanceName'] = protocol.MI_String(perf['InstanceName'])
        perf['AllInstances'] = protocol.MI_Boolean(perf['AllInstances'])
        perf['IntervalSeconds'] = protocol.MI_Uint16(perf['IntervalSeconds'])
    PerfObject = protocol.MI_InstanceA(NewPerf)
    HeartbeatIntervalSeconds = protocol.MI_Uint16(NewHeartbeatIntervalSeconds)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


def Set(HeartbeatIntervalSeconds, PerfObject):
    if Test(HeartbeatIntervalSeconds, PerfObject) == [0]:
        return [0]
    if UpdateOMSAgentConf(HeartbeatIntervalSeconds, PerfObject):
        return [0]
    else:
        return [-1]


def Test(HeartbeatIntervalSeconds, PerfObject):
    prune_perfs(PerfObject)
    NewHeartbeatIntervalSeconds, NewPerfs = ReadOMSAgentConf(
        HeartbeatIntervalSeconds, PerfObject)
    if NewHeartbeatIntervalSeconds != HeartbeatIntervalSeconds:
        return [-1]
    for perf in PerfObject:
        perf['PerformanceCounter'].sort()
        perf['AllInstances'] = True
    for perf in NewPerfs:
        perf['PerformanceCounter'].sort()
    if PerfObject != NewPerfs:
            return [-1]
    return [0]


def Get(HeartbeatIntervalSeconds, PerfObject):
    NewHeartbeatIntervalSeconds, NewPerf = ReadOMSAgentConf(
        HeartbeatIntervalSeconds, PerfObject)
    return NewHeartbeatIntervalSeconds, NewPerf


def TranslatePerfs(object_name, perfs):
    d = {}
    for p in perfs:
        for cname in omi_map:
            for prop in cname['CimProperties']:
                if (p == prop['CounterName'] or p == prop['CimPropertyName']) and cname['ObjectName'] == object_name:
                    if cname['ObjectName'] not in d.keys():
                        d[cname['ObjectName']] = [p]
                    else:
                        d[cname['ObjectName']].append(p)
    return d


def ReadOMSAgentConf(HeartbeatIntervalSeconds, PerfObject):
    txt = ''
    try:
        txt = codecs.open(conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Read omsagent configuration ' + conf_path + '.')
    except:
        LG().Log(
            'ERROR', 'Unable to read omsagent configuration ' + conf_path + '.')
    heartbeat_srch_str = r'<source>.*?tag heartbeat.*?run_interval ([0-9]+[a-z])\n</source>\n'
    heartbeat_srch = re.compile(heartbeat_srch_str, re.M | re.S)
    m = heartbeat_srch.search(txt)
    if m is not None:
        interval = int(m.group(1)[:-1])
        if m.group(1)[-1:] == 'm':
            interval *= 60
    else:
        interval = None
    new_heartbeat = interval
    perf_src_srch_str = r'\n<source>\n  type oms_omi.*?object_name "(.*?)".*?instance_regex "(.*?)".*?counter_name_regex "(.*?)".*?interval ([0-9]+[a-z]).*?</source>\n'
    perf_src_srch = re.compile(perf_src_srch_str, re.M | re.S)
    new_perfobj = []
    sources = perf_src_srch.findall(txt)
    inst = ''
    interval = 0
    for source in sources:
        s_perf = []
        if len(source[2]):
            s_perf = source[2].strip('(').strip(')').split('|')
        object_name = source[0]
        interval = int(source[3][:-1])
        if source[3][-1:] == 'm':
            interval *= 60
        inst = source[1]
        inst = inst.replace('.*', '*')
        new_perfobj.append({'PerformanceCounter': s_perf, 'InstanceName': inst,
                           'IntervalSeconds': interval, 'AllInstances': True, 'ObjectName': object_name})
    return new_heartbeat, new_perfobj


def UpdateOMSAgentConf(HeartbeatIntervalSeconds, PerfObject):
    if os.path.exists(conf_path):
        txt = codecs.open(conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Read omsagent configuration ' + conf_path + '.')
    else:
        LG().Log(
            'INFO', 'No omsagent configuration file present.  Will create new  configuration file at ' + conf_path + '.')
        txt = ''
    heartbeat_srch_str = r'<source>.*?tag heartbeat.*?</source>\n'
    heartbeat_srch = re.compile(heartbeat_srch_str, re.M | re.S)
    heartbeat_src = '<source>\n  type exec\n  tag heartbeat.output\n  command /opt/microsoft/omsagent/bin/omsadmin.sh -b > /dev/null\n  format tsv\n  keys severity,message\n  run_interval ' + \
        str(HeartbeatIntervalSeconds) + 's\n</source>\n'
    txt = heartbeat_srch.sub(heartbeat_src, txt)
    d = {}
    perf_src_srch_str = r'\n<source>\n  type oms_omi.*?</source>\n'
    perf_src_srch = re.compile(perf_src_srch_str, re.M | re.S)
    for source in perf_src_srch.findall(txt):
        txt = txt.replace(source, '')
    new_source = ''
    for perf in PerfObject:
        d = TranslatePerfs(perf['ObjectName'], perf['PerformanceCounter'])
        for k in d.keys():
            names = '(' + reduce(lambda x, y: x + '|' + y, d[k]) + ')'
            instances = re.sub(r'([><]|&gt|&lt)', '', perf['InstanceName'])
            instances = re.sub(r'([*])', '.*', instances)
            new_source += '\n<source>\n  type oms_omi\n  object_name "' + k + '"\n  instance_regex "' + instances + \
                '"\n  counter_name_regex "' + names + '"\n  interval ' + \
                str(perf['IntervalSeconds']) + 's\n</source>\n'
    m = heartbeat_srch.search(txt)
    if m is not None:
        i = m.end(0) + 1
        txt = txt[:i] + new_source + txt[i:]
    else:
        txt = new_source         
    try:
        codecs.open(conf_path, 'w', 'utf8').write(txt)
        LG().Log(
            'INFO', 'Created omsagent configuration at ' + conf_path + '.')
    except:
        LG().Log(
            'ERROR', 'Unable to create omsagent configuration at ' + conf_path + '.')
        return False
    if os.system('sudo /opt/microsoft/omsagent/bin/service_control restart') == 0:
        LG().Log('INFO', 'Successfully restarted omsagent.')
    else:
        LG().Log('ERROR', 'Error restarting omsagent.')
        return False
    return True


def rm_unicode(obj):
    if isinstance(obj, dict):
        d = {}
        for k, v in obj.iteritems():
            d[rm_unicode(k)] = rm_unicode(v)
        return d
    elif isinstance(obj, list):
        return [rm_unicode(i) for i in obj]
    elif isinstance(obj, unicode):
        return obj.encode('ascii', 'ignore')
    else:
        return obj


def prune_perfs(PerfObject):
    l = len(PerfObject)
    i = 0
    while i < l:
        d = TranslatePerfs(PerfObject[i]['ObjectName'], PerfObject[i]['PerformanceCounter'])
        if PerfObject[i]['ObjectName'] in d.keys():
            for p in PerfObject[i]['PerformanceCounter']:
                if p not in d[PerfObject[i]['ObjectName']]:
                    LG().Log('INFO', 'No match for PerformanceCounter \'' \
                             + p + '\' in ' \
                             + repr(PerfObject[i]['ObjectName']) + ' in omi_mapping.json, ignoring.')
                    PerfObject[i]['PerformanceCounter'].remove(p)
            if len(PerfObject[i]['PerformanceCounter']) == 0:
                PerfObject.pop(i)
                l -= 1
                i -= 1
        else:
            LG().Log('INFO', 'No matches for ObjectName ' \
                     + repr(PerfObject[i]['ObjectName']) + ' and PerformanceCounter ' \
                     + repr(PerfObject[i]['PerformanceCounter']) + ' in omi_mapping.json, ignoring.')
            PerfObject.pop(i)
            l -= 1
            i -= 1
        i += 1

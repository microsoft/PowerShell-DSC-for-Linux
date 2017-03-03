#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================

import os
import imp
import re
import codecs

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

# backwards compatibility with pre-multi-homing bundles
conf_path = '/etc/opt/microsoft/omsagent/conf/omsagent.conf'
omi_map_path = '/etc/opt/microsoft/omsagent/conf/omsagent.d/omi_mapping.json'
omi_map = None
multi_homed = None
non_mh_heartbeat_cmd = '/opt/microsoft/omsagent/bin/omsadmin.sh -b'
oms_restart_cmd = 'sudo /opt/microsoft/omsagent/bin/service_control restart'

def init_paths(WorkspaceID):
    global conf_path
    global omi_map_path
    global multi_homed

    omsagent_dir = '/etc/opt/microsoft/omsagent/'
    mh_conf_dir = omsagent_dir + WorkspaceID + '/conf'

    multi_homed = os.path.isdir(mh_conf_dir)

    if multi_homed:
        LG().Log('INFO', 'OMSAgent is multi-homed and resource is updating workspace ' + WorkspaceID)
        conf_path = mh_conf_dir + '/omsagent.conf'
        omi_map_path = mh_conf_dir + '/omsagent.d/omi_mapping.json'


def init_omi_map():
    global omi_map
    txt = codecs.open(omi_map_path, 'r', 'utf8').read()
    omi_map = eval(txt)


def init_vars(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject):
    init_paths(WorkspaceID)
    init_omi_map()

    if WorkspaceID is not None:
        WorkspaceID = WorkspaceID.encode('ascii', 'ignore')
    else:
        WorkspaceID = ''
    if PerfCounterObject is not None:
        for perf in PerfCounterObject:
            new_perfs = []
            if len(perf['PerformanceCounter'].value):
                for perf_counter in perf['PerformanceCounter'].value:
                    new_perfs.append(perf_counter.encode('ascii', 'ignore'))
                perf['PerformanceCounter'] = new_perfs
            if perf['InstanceName'].value is None:
                perf['InstanceName'] = ''
            else:
                perf['InstanceName'] = perf[
                    'InstanceName'].value.encode('ascii', 'ignore')
            if perf['ObjectName'].value is None:
                perf['ObjectName'] = ''
            else:
                perf['ObjectName'] = perf[
                    'ObjectName'].value.encode('ascii', 'ignore')
            if perf['AllInstances'].value is None:
                perf['AllInstances'] = False
            else:
                if perf['AllInstances'].value.value == 1:
                    perf['AllInstances'] = True
                else:
                    perf['AllInstances'] = False
            perf['IntervalSeconds'] = perf['IntervalSeconds'].value.value


def Set_Marshall(Name, WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject):
    init_vars(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject)
    return Set(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject)


def Test_Marshall(Name, WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject):
    init_vars(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject)
    return Test(HeartbeatIntervalSeconds, PerfCounterObject)


def Get_Marshall(Name, WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject):
    arg_names = list(locals().keys())
    init_vars(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject)
    retval = 0
    NewHeartbeatIntervalSeconds, NewPerf = Get(
        HeartbeatIntervalSeconds, PerfCounterObject)
    for perf in NewPerf:
        if len(perf['PerformanceCounter']):
            perf['PerformanceCounter'] = protocol.MI_StringA(
                perf['PerformanceCounter'])
        perf['ObjectName'] = protocol.MI_String(perf['ObjectName'])
        perf['InstanceName'] = protocol.MI_String(perf['InstanceName'])
        perf['AllInstances'] = protocol.MI_Boolean(perf['AllInstances'])
        perf['IntervalSeconds'] = protocol.MI_Uint16(perf['IntervalSeconds'])
    PerfCounterObject = protocol.MI_InstanceA(NewPerf)
    HeartbeatIntervalSeconds = protocol.MI_Uint16(NewHeartbeatIntervalSeconds)
    WorkspaceID = protocol.MI_String(WorkspaceID)
    Name = protocol.MI_String(Name)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


def Set(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject):
    if Test(HeartbeatIntervalSeconds, PerfCounterObject) == [0]:
        return [0]
    if UpdateOMSAgentConf(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject):
        return [0]
    else:
        return [-1]


def Test(HeartbeatIntervalSeconds, PerfCounterObject):
    prune_perfs(PerfCounterObject)
    NewHeartbeatIntervalSeconds, NewPerfs = ReadOMSAgentConf(
        HeartbeatIntervalSeconds, PerfCounterObject)
    if NewHeartbeatIntervalSeconds != HeartbeatIntervalSeconds:
        return [-1]
    PerfCounterObject.sort()
    for perf in PerfCounterObject:
        perf['PerformanceCounter'].sort()
        perf['AllInstances'] = True
    NewPerfs.sort()
    for perf in NewPerfs:
        perf['PerformanceCounter'].sort()
    if PerfCounterObject != NewPerfs:
            return [-1]
    return [0]


def Get(HeartbeatIntervalSeconds, PerfCounterObject):
    NewHeartbeatIntervalSeconds, NewPerf = ReadOMSAgentConf(
        HeartbeatIntervalSeconds, PerfCounterObject)
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


def ReadOMSAgentConf(HeartbeatIntervalSeconds, PerfCounterObject):
    txt = ''
    try:
        txt = codecs.open(conf_path, 'r', 'utf8').read().encode(
            'ascii', 'ignore')
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


def UpdateOMSAgentConf(WorkspaceID, HeartbeatIntervalSeconds, PerfCounterObject):
    if os.path.exists(conf_path):
        txt = codecs.open(conf_path, 'r', 'utf8').read().encode(
            'ascii', 'ignore')
        LG().Log('INFO', 'Read omsagent configuration ' + conf_path + '.')
    else:
        LG().Log(
            'INFO', 'No omsagent configuration file present.  Will create new  configuration file at ' + conf_path + '.')
        txt = ''
    heartbeat_srch_str = r'<source>.*?tag heartbeat.*?</source>\n'
    heartbeat_srch = re.compile(heartbeat_srch_str, re.M | re.S)
    heartbeat_cmd = non_mh_heartbeat_cmd
    if multi_homed:
        heartbeat_cmd = 'echo'
    heartbeat_src = '<source>\n  type exec\n  tag heartbeat.output\n  command ' + heartbeat_cmd + ' > /dev/null\n  format tsv\n  keys severity,message\n  run_interval ' + \
        str(HeartbeatIntervalSeconds) + 's\n</source>\n'
    txt = heartbeat_srch.sub(heartbeat_src, txt)
    d = {}
    perf_src_srch_str = r'\n<source>\n  type oms_omi.*?</source>\n'
    perf_src_srch = re.compile(perf_src_srch_str, re.M | re.S)
    for source in perf_src_srch.findall(txt):
        txt = txt.replace(source, '')
    new_source = ''
    for perf in PerfCounterObject:
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

    global oms_restart_cmd
    process_to_restart = 'omsagent'
    if multi_homed:
        restart_cmd += ' ' + WorkspaceID
        process_to_restart += '-' + WorkspaceID
    if os.system(restart_cmd) == 0:
        LG().Log('INFO', 'Successfully restarted ' + process_to_restart + '.')
    else:
        LG().Log('ERROR', 'Error restarting ' + process_to_restart + '.')
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


def prune_perfs(PerfCounterObject):
    l = len(PerfCounterObject)
    i = 0
    while i < l:
        d = TranslatePerfs(PerfCounterObject[i]['ObjectName'], PerfCounterObject[i]['PerformanceCounter'])
        if PerfCounterObject[i]['ObjectName'] in d.keys():
            for p in PerfCounterObject[i]['PerformanceCounter']:
                if p not in d[PerfCounterObject[i]['ObjectName']]:
                    LG().Log('INFO', 'No match for PerformanceCounter \'' \
                             + p + '\' in ' \
                             + repr(PerfCounterObject[i]['ObjectName']) + ' in omi_mapping.json, ignoring.')
                    PerfCounterObject[i]['PerformanceCounter'].remove(p)
            if len(PerfCounterObject[i]['PerformanceCounter']) == 0:
                PerfCounterObject.pop(i)
                l -= 1
                i -= 1
        else:
            LG().Log('INFO', 'No matches for ObjectName ' \
                     + repr(PerfCounterObject[i]['ObjectName']) + ' and PerformanceCounter ' \
                     + repr(PerfCounterObject[i]['PerformanceCounter']) + ' in omi_mapping.json, ignoring.')
            PerfCounterObject.pop(i)
            l -= 1
            i -= 1
        i += 1

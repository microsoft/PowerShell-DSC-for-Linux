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

rsyslog_conf_path = '/etc/rsyslog.conf'
rsyslog_inc_conf_path = '/etc/rsyslog.d/95-omsagent.conf'
syslog_ng_conf_path = '/etc/syslog-ng/syslog-ng.conf'
sysklog_conf_path='/etc/syslog.conf'
oms_syslog_ng_conf_path = '/etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf'
oms_rsyslog_conf_path = '/etc/opt/omi/conf/omsconfig/rsyslog-oms.conf'
conf_path = ''


def init_vars(SyslogSource):
    global conf_path
    for source in SyslogSource:
        if source['Severities'] is not None:
            if 'value' in dir(source['Severities']):
                source['Severities'] = source['Severities'].value
            for s in (source['Severities']):
                s = s.encode('ascii', 'ignore')
        if 'value' in dir(source['Facility']):
            source['Facility'] = source['Facility'].value
        source['Facility'] = source['Facility'].encode('ascii', 'ignore')
    if os.path.exists(rsyslog_conf_path):
        conf_path = oms_rsyslog_conf_path
    elif os.path.exists(syslog_ng_conf_path):
        conf_path = oms_syslog_ng_conf_path
    else:
        LG().Log('ERROR', 'Unable to find OMS config files.')
        raise Exception('Unable to find OMS config files.')
    LG().Log('INFO', 'Config file is ' + conf_path + '.')


def Set_Marshall(SyslogSource):
    if os.path.exists(sysklog_conf_path):
        LG().Log('ERROR', 'Sysklogd is unsupported.')
        return [0]
    init_vars(SyslogSource)
    retval = Set(SyslogSource)
    if retval is False:
        retval = [-1]
    else:
        retval = [0]
    return retval


def Test_Marshall(SyslogSource):
    if os.path.exists(sysklog_conf_path):
        LG().Log('ERROR', 'Sysklogd is unsupported.')
        return [0]
    init_vars(SyslogSource)
    return Test(SyslogSource)


def Get_Marshall(SyslogSource):
    if os.path.exists(sysklog_conf_path):
        LG().Log('ERROR', 'Sysklogd is unsupported.')
        return 0, {'SyslogSource':protocol.MI_InstanceA([])}
    arg_names = list(locals().keys())
    init_vars(SyslogSource)
    retval = 0
    NewSource = Get(SyslogSource)
    for source in NewSource:
        if source['Severities'] is not None:
            source['Severities'] = protocol.MI_StringA(source['Severities'])
        source['Facility'] = protocol.MI_String(source['Facility'])
    SyslogSource = protocol.MI_InstanceA(NewSource)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


def Set(SyslogSource):
    if Test(SyslogSource) == [0]:
        return [0]
    if conf_path == oms_syslog_ng_conf_path:
        ret = UpdateSyslogNGConf(SyslogSource)
    else:
        ret = UpdateSyslogConf(SyslogSource)
    if ret:
        ret = [0]
    else:
        ret = [-1]
    return ret


def Test(SyslogSource):
    if conf_path == oms_syslog_ng_conf_path:
        NewSource = ReadSyslogNGConf(SyslogSource)
    else:
        NewSource = ReadSyslogConf(SyslogSource)
    SyslogSource.sort()
    for d in SyslogSource:
        found = False
        if 'Severities' not in d.keys() or d['Severities'] is None or len(d['Severities']) is 0:
            d['Severities'] = ['none']  # redundant?
        d['Severities'].sort()
    NewSource.sort()
    for n in NewSource:
        n['Severities'].sort()
    if SyslogSource != NewSource:
        return [-1]
    return [0]


def Get(SyslogSource):
    if conf_path == oms_syslog_ng_conf_path:
        NewSource = ReadSyslogNGConf(SyslogSource)
    else:
        NewSource = ReadSyslogConf(SyslogSource)
    for d in NewSource:
        if d['Severities'] == ['none']:
            d['Severities'] = []
    return NewSource


def ReadSyslogConf(SyslogSource):
    out = []
    txt = ''
    if len(SyslogSource) == 0:
        return out
    if not os.path.exists('/etc/rsyslog.d'):
        try:
            txt = codecs.open(rsyslog_conf_path, 'r', 'utf8').read()
            LG().Log('INFO', 'Successfully read ' + rsyslog_conf_path + '.')
        except:
            LG().Log('ERROR', 'Unable to read ' + rsyslog_conf_path + '.')
    else:
        src_conf_path = conf_path
        if os.path.exists(rsyslog_inc_conf_path):
            src_conf_path = rsyslog_inc_conf_path
        try:
            txt = codecs.open(src_conf_path, 'r', 'utf8').read()
            LG().Log('INFO', 'Successfully read ' + src_conf_path + '.')
        except:
            LG().Log('ERROR', 'Unable to read ' + src_conf_path + '.')
            return out
    facility_search = r'^(.*?)@.*?25224$'
    facility_re = re.compile(facility_search, re.M)
    for line in facility_re.findall(txt):
        l = line.replace('=', '')
        l = l.replace('\t', '').split(';')
        sevs = []
        fac = l[0].encode('ascii', 'ignore').split('.')[0]
        for sev in l:
            sevs.append(sev.encode('ascii', 'ignore').split('.')[1])
        out.append({'Facility': fac, 'Severities': sevs})
    return out


def UpdateSyslogConf(SyslogSource):
    arg = ''
    if 'rsyslog' in conf_path:
        if os.path.exists('/etc/rsyslog.d'):
            txt = ''
        elif os.path.exists(rsyslog_conf_path):
            arg = '1'
            try:
                txt = codecs.open(rsyslog_conf_path, 'r', 'utf8').read()
                LG().Log(
                    'INFO', 'Successfully read ' + rsyslog_conf_path + '.')
            except:
                LG().Log('ERROR', 'Unable to read ' + rsyslog_conf_path + '.')
    facility_search = r'(#facility.*?\n.*?25224\n)|(^[^#].*?25224\n)'
    facility_re = re.compile(facility_search, re.M)
    for t in facility_re.findall(txt):
        for r in t:
            txt = txt.replace(r, '')
    for d in SyslogSource:
        facility_txt = '#facility = ' + d['Facility'] + '\n'
        for s in d['Severities']:
            facility_txt += d['Facility'] + '.=' + s + ';'
        facility_txt = facility_txt[0:-1] + '\t@127.0.0.1:25224\n'
        txt += facility_txt
    try:
        codecs.open(conf_path, 'w', 'utf8').write(txt)
        LG().Log(
            'INFO', 'Created omsagent rsyslog configuration at ' + conf_path + '.')
    except:
        LG().Log(
            'ERROR', 'Unable to create omsagent rsyslog configuration at ' + conf_path + '.')
        return False
    if os.system('sudo /opt/microsoft/omsconfig/Scripts/OMSRsyslog.post.sh ' + arg) == 0:
        LG().Log('INFO', 'Successfully executed OMSRsyslog.post.sh.')
    else:
        LG().Log('ERROR', 'Error executing OMSRsyslog.post.sh.')
        return False
    return True


def ReadSyslogNGConf(SyslogSource):
    out = []
    txt = ''
    try:
        txt = codecs.open(syslog_ng_conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Successfully read ' + syslog_ng_conf_path + '.')
    except:
        LG().Log('ERROR', 'Unable to read ' + syslog_ng_conf_path + '.')
        return out
    facility_search = r'^filter f_(?P<facility>.*?)_oms.*?level\((?P<severities>.*?)\)'
    facility_re = re.compile(facility_search, re.M)
    for s in facility_re.findall(txt):
        sevs = []
        if len(s[1]):
            if ',' in s[1]:
                sevs = s[1].encode('ascii', 'ignore').split(',')
            else:
                sevs.append(s[1].encode('ascii', 'ignore'))
        out.append(
            {'Facility': s[0].encode('ascii', 'ignore'), 'Severities': sevs})
    return out


def UpdateSyslogNGConf(SyslogSource):
    txt = ''
    try:
        txt = codecs.open(syslog_ng_conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Successfully read ' + syslog_ng_conf_path + '.')
    except:
        LG().Log('ERROR', 'Unable to read ' + syslog_ng_conf_path + '.')
        return False
    facility_search = r'(\n+)?(#OMS_Destination.*?25224.*?\n)?(\n)?(#OMS_facility.*?filter.*?_oms.*?log.*destination.*?\n)'
    facility_re = re.compile(facility_search, re.M | re.S)
    txt = facility_re.sub('', txt)
    txt += '\n\n#OMS_Destination\ndestination d_oms { udp("127.0.0.1" port(25224)); };\n'
    for d in SyslogSource:
        if 'Severities' not in d.keys() or d['Severities'] is None or len(d['Severities']) is 0:
            facility_txt = ''
        else:
            facility_txt = '\n#OMS_facility = ' + d['Facility'] + '\n'
            sevs = reduce(lambda x, y: x + ',' + y, d['Severities'])
            facility_txt += 'filter f_' + \
                d['Facility'] + \
                '_oms { level(' + sevs + ') and facility(' + d[
                    'Facility'] + '); };\n'
            facility_txt += 'log { source(src); filter(f_' + d[
                'Facility'] + '_oms); destination(d_oms); };\n'
            txt += facility_txt
    try:
        codecs.open(conf_path, 'w', 'utf8').write(txt)
        LG().Log(
            'INFO', 'Created omsagent syslog-ng configuration at ' + conf_path + '.')
    except:
        LG().Log(
            'ERROR', 'Unable to create omsagent syslog-ng configuration at ' + conf_path + '.')
        return False
    if os.system('sudo /opt/microsoft/omsconfig/Scripts/OMSSyslog-ng.post.sh') == 0:
        LG().Log('INFO', 'Successfully executed OMSSyslog-ng.post.sh.')
    else:
        LG().Log('ERROR', 'Error executing OMSSyslog-ng.post.sh.')
        return False
    return True

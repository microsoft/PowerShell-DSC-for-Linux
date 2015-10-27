#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

from __future__ import print_function
from __future__ import with_statement

import os
import imp
import re
import codecs
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

rsyslog_conf_path='/etc/rsyslog.conf'
syslog_ng_conf_path='/etc/syslog-ng/syslog-ng.conf'
sysklog_conf_path='/etc/syslog.conf'
oms_syslog_ng_conf_path = '/etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf'
oms_rsyslog_conf_path = '/etc/opt/omi/conf/omsconfig/rsyslog-oms.conf'
oms_sysklog_conf_path = '/etc/opt/omi/conf/omsconfig/sysklog-oms.conf'
conf_path=''

def init_vars(SyslogSource):
    global conf_path
    for source in SyslogSource:
        if source['Severities'] is not None:
            if 'value' in dir(source['Severities']):
                source['Severities']=source['Severities'].value
            for s in (source['Severities']):
                s=s.encode('ascii','ignore')
        if 'value' in dir(source['Facility']):
            source['Facility']=source['Facility'].value
        source['Facility']=source['Facility'].encode('ascii','ignore')
    if os.path.exists(rsyslog_conf_path):
        conf_path=oms_rsyslog_conf_path
    elif os.path.exists(syslog_ng_conf_path):
        conf_path=oms_syslog_ng_conf_path
    elif os.path.exists(sysklog_conf_path):
        conf_path=oms_sysklog_conf_path
    else:
        LG().Log('ERROR', 'Unable to find OMS config files')
        raise Exception('Unable to find OMS config files')
    
def Set_Marshall(SyslogSource):
    init_vars(SyslogSource)
    retval = Set(SyslogSource)
    if retval is False:
        retval = [-1]
    else:
        retval = [0]
    return retval

def Test_Marshall(SyslogSource):
    init_vars(SyslogSource)
    return Test(SyslogSource)

def Get_Marshall(SyslogSource):
    arg_names = list(locals().keys())
    init_vars(SyslogSource)
    retval = 0
    NewSource = Get(SyslogSource)
    for source in NewSource:
        if source['Severities'] is not None:
            source['Severities'] = protocol.MI_StringA(source['Severities'])
        source['Facility']=protocol.MI_String(source['Facility'])
    SyslogSource=protocol.MI_InstanceA(NewSource)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd
            
def Set(SyslogSource):
    if Test(SyslogSource) == [0]:
        return [0]
    if conf_path==oms_syslog_ng_conf_path:
        ret=UpdateSyslogNGConf(SyslogSource)
    else:
        ret=UpdateSyslogConf(SyslogSource)
    if ret:
        ret = [0]
    else:
        ret = [-1]
    return ret

def Test(SyslogSource):
    if conf_path==oms_sysklog_conf_path:
        return [0]
    if conf_path==oms_syslog_ng_conf_path:
        NewSource=ReadSyslogNGConf(SyslogSource)
    else:
        NewSource=ReadSyslogConf(SyslogSource)
    for d in SyslogSource:
        found = False
        if 'Severities' not in d.keys() or d['Severities'] is None or len(d['Severities']) is 0:
            d['Severities']=['none'] # redundant?
        d['Severities'].sort()
        for n in NewSource:
            n['Severities'].sort()
            if d['Facility'] == n['Facility'] and d['Severities'] == n['Severities']:
                found = True
        if not found:
            return [-1]
    return [0]

def Get(SyslogSource):
    if conf_path==oms_sysklog_conf_path:
        return SyslogSource
    if conf_path==oms_syslog_ng_conf_path:
        NewSource=ReadSyslogNGConf(SyslogSource)
    else:
        NewSource=ReadSyslogConf(SyslogSource)
    for d in NewSource:
        if d['Severities'] == ['none']:
            d['Severities'] = []
    return NewSource

def ReadSyslogConf(SyslogSource):
    out = []
    if len(SyslogSource) == 0:
        return out
    if not os.path.exists('/etc/rsyslog.d'):
        txt = codecs.open(rsyslog_conf_path, 'r', 'utf8').read()
    else:
        if not os.path.exists(conf_path):
            LG().Log('ERROR', 'Unable to read ' + conf_path + '.')
            return out
        txt = codecs.open(conf_path, 'r', 'utf8').read()
    count=0
    for d in SyslogSource:
        out.append({'Facility':d['Facility'],'Severities':[]})
        facility_search = r'(?P<facility>'+d['Facility']+r')(?P<op>[.]=|[.])(?P<severity>.*?)[ ;\t]'
        facility_re=re.compile(facility_search,re.M|re.S)
        s=facility_re.findall(txt)
        if 'Severities' not in d.keys() or d['Severities'] is None or len(d['Severities']) is 0:
            d['Severities']=['none']
        for m in s:
            if m[2].encode('ascii','ignore') in d['Severities']:
                (out[count])['Severities'].append(m[2].encode('ascii','ignore'))
        count+=1
    return out

def UpdateSyslogConf(SyslogSource):
    arg=''
    if 'rsyslog' in conf_path :
        if os.path.exists('/etc/rsyslog.d'):
            txt = ''
        elif os.path.exists(rsyslog_conf_path):    
            txt = codecs.open(rsyslog_conf_path, 'r', 'utf8').read()
            arg = '1'
        else :
            LG().Log('ERROR', 'Unable to read ' + rsyslog_conf_path + '.')
    elif not os.path.exists(conf_path):
        LG().Log('ERROR', 'Unable to read ' + conf_path + '.')
        return False
#     else :
#         txt = codecs.open(sysklog_conf_path, 'r', 'utf8').read()
    facility_search = r'(#facility.*?\n.*?25224\n)|(^[^#].*?25224\n)'
    facility_re=re.compile(facility_search,re.M|re.S)
    for t in facility_re.findall(txt):
        for r in t:
            txt=txt.replace(r,'')
    for d in SyslogSource:
        facility_txt = '#facility = ' + d['Facility'] + '\n'
        for s in d['Severities']:
            facility_txt += d['Facility'] + '.=' + s + ';'
        facility_txt=facility_txt[0:-1]+'\t@127.0.0.1:25224\n'
        txt += facility_txt
    codecs.open(conf_path, 'w', 'utf8').write(txt)
    if 'rsyslog' in conf_path:
        os.system('sudo /opt/microsoft/omsconfig/Scripts/OMSRsyslog.post.sh '+arg)
#     else: # sysklogd
#         os.system('sudo /opt/microsoft/omsconfig/Scripts/OMSSysklog.post.sh')
    return True
    
def ReadSyslogNGConf(SyslogSource):
    out = []
    if not os.path.exists(syslog_ng_conf_path):
        LG().Log('ERROR', 'Unable to read ' + syslog_ng_conf_path + '.')
        return out
    txt = codecs.open(syslog_ng_conf_path, 'r', 'utf8').read()
    count=0
    for d in SyslogSource:
        out.append({'Facility':d['Facility'],'Severities':[]})
        facility_search = r'filter f_'+d['Facility']+r'_oms.*level[(](?P<severities>.*?)[)]'
        facility_re=re.compile(facility_search,re.M|re.S)
        s=facility_re.search(txt)
        sevs=[]
        if s is not None:
            sevs=s.group('severities').encode('ascii','ignore').split(',')
        if 'Severities' not in d.keys() or d['Severities'] is None or len(d['Severities']) is 0:
            d['Severities']=['none']
        for m in sevs:
            if m in d['Severities']:
                (out[count])['Severities'].append(m)
        count+=1
    return out
    
def UpdateSyslogNGConf(SyslogSource):
    if not os.path.exists(syslog_ng_conf_path):
        LG().Log('ERROR', 'Unable to read ' + conf_path + '.')
        return False
    txt = codecs.open(syslog_ng_conf_path, 'r', 'utf8').read()
    facility_search = r'(\n+)?(#OMS_Destination.*?25224.*?\n)?(\n)?(#OMS_facility.*?filter.*?_oms.*?log.*destination.*?\n)'
    facility_re = re.compile(facility_search,re.M|re.S)
    txt = facility_re.sub('',txt)
    txt += '\n\n#OMS_Destination\ndestination d_oms { udp("127.0.0.1" port(25224)); };\n'
    for d in SyslogSource:
        if 'Severities' not in d.keys() or d['Severities'] is None or len(d['Severities']) is 0:
            facility_txt = ''
        else :
            facility_txt = '\n#OMS_facility = ' + d['Facility'] + '\n'
            sevs=reduce(lambda x, y: x + ',' + y,d['Severities'])
            facility_txt += 'filter f_' + d['Facility'] + '_oms { level('+ sevs +') and facility(' + d['Facility'] + '); };\n'
            facility_txt += 'log { source(src); filter(f_' + d['Facility'] + '_oms); destination(d_oms); };\n'
            txt += facility_txt
    codecs.open(conf_path, 'w', 'utf8').write(txt)
    os.system('sudo /opt/microsoft/omsconfig/Scripts/OMSSyslog-ng.post.sh')
    return True

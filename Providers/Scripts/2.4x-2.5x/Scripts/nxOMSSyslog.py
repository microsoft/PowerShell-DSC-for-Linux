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
omsagent_dir = '/etc/opt/microsoft/omsagent/'
default_port = '25224'
default_host = '127.0.0.1'
default_protocol = 'udp'
oms_wkspc_regex = '[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}'
non_oms_wkspcs = ['LAD', 'scom']
rsyslog_conf_separator = '\t'

def init_vars(SyslogSource, WorkspaceID):
    """
    Initialize global variables for this resource
    """
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

    if WorkspaceID is not None:
        WorkspaceID = WorkspaceID.encode('ascii', 'ignore')
    else:
        WorkspaceID = ''

    if os.path.exists(rsyslog_conf_path):
        conf_path = oms_rsyslog_conf_path
    elif os.path.exists(syslog_ng_conf_path):
        conf_path = oms_syslog_ng_conf_path
    else:
        LG().Log('ERROR', 'Unable to find OMS config files.')
        raise Exception('Unable to find OMS config files.')
    LG().Log('INFO', 'Config file is ' + conf_path + '.')


def Set_Marshall(SyslogSource, WorkspaceID):
    """
    Set the syslog conf for specified workspace on the machine
    """
    if os.path.exists(sysklog_conf_path):
        LG().Log('ERROR', 'Sysklogd is unsupported.')
        return [0]

    init_vars(SyslogSource, WorkspaceID)
    retval = Set(SyslogSource, WorkspaceID)

    if retval is False:
        retval = [-1]
    else:
        retval = [0]
    return retval


def Test_Marshall(SyslogSource, WorkspaceID):
    """
    Test if the syslog conf for specified workspace matches the provided conf
    """
    if os.path.exists(sysklog_conf_path):
        LG().Log('ERROR', 'Sysklogd is unsupported.')
        return [0]

    init_vars(SyslogSource, WorkspaceID)
    return Test(SyslogSource, WorkspaceID)


def Get_Marshall(SyslogSource, WorkspaceID):
    """
    Get the syslog conf for specified workspace from the machine and update
    the parameters
    """
    if os.path.exists(sysklog_conf_path):
        LG().Log('ERROR', 'Sysklogd is unsupported.')
        return 0, {'SyslogSource':protocol.MI_InstanceA([])}

    arg_names = list(locals().keys())
    init_vars(SyslogSource, WorkspaceID)
    retval = 0
    NewSource = Get(SyslogSource, WorkspaceID)
    for source in NewSource:
        if source['Severities'] is not None:
            source['Severities'] = protocol.MI_StringA(source['Severities'])
        source['Facility'] = protocol.MI_String(source['Facility'])
    SyslogSource = protocol.MI_InstanceA(NewSource)
    WorkspaceID = protocol.MI_String(WorkspaceID)

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


def Set(SyslogSource, WorkspaceID):
    """
    Set the syslog conf for specified workspace on the machine
    """
    if Test(SyslogSource, WorkspaceID) == [0]:
        return [0]

    if conf_path == oms_syslog_ng_conf_path:
        ret = UpdateSyslogNGConf(SyslogSource, WorkspaceID)
    else:
        ret = UpdateSyslogConf(SyslogSource, WorkspaceID)

    if ret:
        ret = [0]
    else:
        ret = [-1]
    return ret


def Test(SyslogSource, WorkspaceID):
    """
    Test if the syslog conf for specified workspace matches the provided conf
    """
    if conf_path == oms_syslog_ng_conf_path:
        NewSource = ReadSyslogNGConf(SyslogSource, WorkspaceID)
    else:
        NewSource = ReadSyslogConf(SyslogSource, WorkspaceID)

    SyslogSource.sort()
    for d in SyslogSource:
        found = False
        if ('Severities' not in d.keys() or d['Severities'] is None 
                or len(d['Severities']) is 0):
            d['Severities'] = ['none']

        d['Severities'].sort()

    NewSource.sort()
    for n in NewSource:
        n['Severities'].sort()
    if SyslogSource != NewSource:
        return [-1]
    return [0]


def Get(SyslogSource, WorkspaceID):
    """
    Get the syslog conf for specified workspace from the machine
    """
    if conf_path == oms_syslog_ng_conf_path:
        NewSource = ReadSyslogNGConf(SyslogSource, WorkspaceID)
    else:
        NewSource = ReadSyslogConf(SyslogSource, WorkspaceID)

    for d in NewSource:
        if d['Severities'] == ['none']:
            d['Severities'] = []
    return NewSource


def ReadSyslogConf(SyslogSource, WorkspaceID):
    """
    Read syslog conf file in rsyslog format for specified workspace and
    return the relevant facilities and severities
    """
    # Check for the current conf even if it should be set to collect nothing
    out = []
    txt = ''

    # Read text from syslog conf file
    src_conf_path = GetSyslogConfPath()
    try:
        txt = codecs.open(src_conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Successfully read ' + src_conf_path + '.')
    except:
        LG().Log('ERROR', 'Unable to read ' + src_conf_path + '.')
        return out

    # Find all lines sending to this workspace's port, protocol and addr
    # Use port + protocol + addr to look for a match, ex: \t@127.0.0.1:25224
    port = ExtractFieldFromFluentDConf(WorkspaceID, 'port', default_port)
    protocol_type = ExtractFieldFromFluentDConf(WorkspaceID, 'protocol_type', default_protocol)
    bind_addr = ExtractFieldFromFluentDConf(WorkspaceID, 'bind', default_host)
    pattern_value = rsyslog_conf_separator + protocol_type.replace('tcp', '@@').replace('udp', '@') + bind_addr + ':' + port

    facility_search = r'^([^#].*?)' + pattern_value + '$'
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


def UpdateSyslogConf(SyslogSource, WorkspaceID):
    """
    Update syslog conf file in rsyslog format with specified facilities and
    severities for the specified workspace
    """
    # Read text from syslog conf file
    src_conf_path = GetSyslogConfPath()
    if src_conf_path == rsyslog_conf_path:
        arg = '1'
    else:
        arg = ''

    try:
        txt = codecs.open(src_conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Successfully read ' + src_conf_path + '.')
    except: 
        LG().Log('ERROR', 'Unable to read ' + src_conf_path + '.')
        return False

    # Remove all lines related to this workspace ID (correlated by port)
    port = ExtractFieldFromFluentDConf(WorkspaceID, 'port', default_port)
    protocol_type = ExtractFieldFromFluentDConf(WorkspaceID, 'protocol_type', default_protocol).replace('tcp','@@').replace('udp', '@')
    bind_addr = ExtractFieldFromFluentDConf(WorkspaceID, 'bind', default_host)
    wkspc_comment = GetSyslogConfMultiHomedHeaderString(WorkspaceID)
    wkspc_comment_search = r'(\n+)?(' + wkspc_comment + '.*)$'
    wkspc_comment_re = re.compile(wkspc_comment_search, re.M)
    txt = wkspc_comment_re.sub('', txt)

    wkspc_port_search = r'(\n+)?(#facility.*?\n.*?' + port + '\n)|(^[^#]' \
                             '.*?' + port + '\n)'
    wkspc_port_re = re.compile(wkspc_port_search, re.M)
    for group in wkspc_port_re.findall(txt):
        for match in group:
            txt = txt.replace(match, '')

    # Remove all OMS-related lines not marked with a workspace ID
    comment_search = r'(\n+)?(# OMS Syslog collection)$'
    comment_re = re.compile(comment_search, re.M)
    txt = comment_re.sub('', txt)

    # Append conf lines for this workspace
    txt += wkspc_comment + '\n'
    for d in SyslogSource:
        facility_txt = ''
        for s in d['Severities']:
            facility_txt += d['Facility'] + '.=' + s + ';'
        facility_txt = facility_txt[0:-1] + rsyslog_conf_separator + protocol_type + bind_addr + ':' + port + '\n'
        txt += facility_txt

    # Write the new complete txt to the conf file
    try:
        codecs.open(conf_path, 'w', 'utf8').write(txt)
        LG().Log('INFO', 'Created omsagent rsyslog configuration at ' + \
                         conf_path + '.')
    except:
        LG().Log('ERROR', 'Unable to create omsagent rsyslog configuration ' \
                          'at ' + conf_path + '.')
        return False

    if os.system('sudo /opt/microsoft/omsconfig/Scripts/OMSRsyslog.post.sh ' \
                 + arg) is 0:
        LG().Log('INFO', 'Successfully executed OMSRsyslog.post.sh.')
    else:
        LG().Log('ERROR', 'Error executing OMSRsyslog.post.sh.')
        return False
    return True


def ReadSyslogNGConf(SyslogSource, WorkspaceID):
    """
    Read syslog conf file in syslog-ng format for specified workspace and
    return the relevant facilities and severities
    """
    out = []
    txt = ''

    # Read text from syslog conf file
    try:
        txt = codecs.open(syslog_ng_conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Successfully read ' + syslog_ng_conf_path + '.')
    except:
        LG().Log('ERROR', 'Unable to read ' + syslog_ng_conf_path + '.')
        return out

    # Check if the destination for that workspace has identical protocol + addr + port
    # Use port + protocol + addr to look for a match, ex: \t@127.0.0.1:25224
    port = ExtractFieldFromFluentDConf(WorkspaceID, 'port', default_port)
    protocol_type = ExtractFieldFromFluentDConf(WorkspaceID, 'protocol_type', default_protocol)
    bind_addr = ExtractFieldFromFluentDConf(WorkspaceID, 'bind', default_host)
    dest_config_search = r'^destination d_.*' + WorkspaceID + '.*' + protocol_type + '\("' + bind_addr + '" port\(' + port + '\)\).*'
    dest_re = re.compile(dest_config_search, re.M)
    # when there is no WorkspaceID destination that match protocol + addr + port, just return empty list
    if len(dest_re.findall(txt)) == 0:
        return []

    # Check first if there are conf lines labelled with this workspace ID
    wkspc_id_search = r'^filter f_.*' + WorkspaceID + '_oms'
    wkspc_id_re = re.compile(wkspc_id_search, re.M)
    wkspc_found = wkspc_id_re.search(txt)

    if wkspc_found:
        facility_re = ParseSyslogNGConfMultiHomed(txt, WorkspaceID)
    else:
        facility_re = ParseSyslogNGConf(txt)

    for s in facility_re.findall(txt):
        sevs = []
        if len(s[1]):
            if ',' in s[1]:
                sevs = s[1].encode('ascii', 'ignore').split(',')
            else:
                sevs.append(s[1].encode('ascii', 'ignore'))
        out.append({'Facility': s[0].encode('ascii', 'ignore'),
                    'Severities': sevs})
    return out


def UpdateSyslogNGConf(SyslogSource, WorkspaceID):
    """
    Update syslog conf file in syslog-ng format with specified facilities and
    severities for the specified workspace
    Clean up any old format lines (no workspace ID)
    """
    try:
        txt = codecs.open(syslog_ng_conf_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Successfully read ' + syslog_ng_conf_path + '.')
    except:
        LG().Log('ERROR', 'Unable to read ' + syslog_ng_conf_path + '.')
        return False

    # Extract the correct source from the conf file
    # Different distros may use different source name:
    # in redhat 7.4 the source is 's_sys'
    # in ubuntu/debian the source is 's_src'
    source_search = r'^source (.*){$'
    source_re = re.compile(source_search, re.M)
    source_result = source_re.search(txt)
    source_expr = 'src'
    if source_result:
        source_expr = source_result.group(1).strip()

    port = ExtractFieldFromFluentDConf(WorkspaceID, 'port', default_port)
    protocol_type = ExtractFieldFromFluentDConf(WorkspaceID, 'protocol_type', default_protocol)
    bind_addr = ExtractFieldFromFluentDConf(WorkspaceID, 'bind', default_host)

    # Remove all lines related to this workspace ID
    wkspc_comment = '#OMS Workspace ' + WorkspaceID
    wkspc_comment_search = r'(\n+)?(' + wkspc_comment + '.*$)'
    wkspc_comment_re = re.compile(wkspc_comment_search, re.M)
    txt = wkspc_comment_re.sub('', txt)

    wkspc_search = r'(\n+)?(destination.*' + WorkspaceID + '_oms.*\n)?' \
                        '(\n)*filter.*' + WorkspaceID + '_oms.*\n' \
                        '(destination.*' + WorkspaceID + '_oms.*\n)?log.*'
    wkspc_re = re.compile(wkspc_search)
    txt = wkspc_re.sub('', txt)

    # Remove all lines related to this port
    # If that port was previously used for a particular workspace, then the
    # lines referencing this destination line with port also need to be removed
    port_search = r'(^.*(d_.*oms).*port\(' + port + '\).*$)'
    port_re = re.compile(port_search, re.M)
    for group in port_re.findall(txt):
        if len(group) < 2:
            continue
        # Replace all the lines with the destination which uses the port
        # (this will include the port line itself)
        destination_search = r'^.*' + group[1] + '.*\n*'
        destination_re = re.compile(destination_search, re.M)
        txt = destination_re.sub('', txt)
            
    # Remove all OMS-related lines not marked with a workspace ID
    non_mh_search = r'^(#OMS_Destination\n)|(destination.*_oms.*\n*)|' \
                     '(#OMS_facility.*\n)|(filter.*_oms.*\n*)|(log.*_oms.*\n*)'
    non_mh_re = re.compile(non_mh_search, re.M)

    # Check all lines a match with a workspace identifier; if a workspace
    # is in the line, then we don't want to replace it
    oms_wkspc_regex_search = r'' + oms_wkspc_regex
    oms_wkspc_regex_re = re.compile(oms_wkspc_regex_search)
    for group in non_mh_re.findall(txt):
        for possible_non_mh_line in group:
            oms_wkspc_found = oms_wkspc_regex_re.search(possible_non_mh_line)
            if oms_wkspc_found is not None:
                continue

            found = False
            for non_oms_wkspc in non_oms_wkspcs:
                non_oms_wkspc_search = r'' + non_oms_wkspc
                non_oms_wkspc_re = re.compile(non_oms_wkspc_search)
                non_oms_wkspc_found = non_oms_wkspc_re.search(possible_non_mh_line)
                if non_oms_wkspc_found is not None:
                    found = True
                    break

            if found:
                continue
            txt = txt.replace(possible_non_mh_line, '')
    
    # Append conf lines for this workspace
    destination_str = 'd_' + WorkspaceID + '_oms'
    txt += '\n\n' + wkspc_comment + ' Destination\ndestination ' \
           + destination_str + ' { ' + protocol_type + '("' + bind_addr + '" port(' + port + ')); };\n'
    for d in SyslogSource:
        if ('Severities' in d.keys() and d['Severities'] is not None
                and len(d['Severities']) > 0):
            facility_txt = '\n' + wkspc_comment + ' Facility = ' \
                           + d['Facility'] + '\n'
            sevs = reduce(lambda x, y: x + ',' + y, d['Severities'])
            filter_str = 'f_' + d['Facility'] + '_' + WorkspaceID + '_oms'
            facility_txt += 'filter ' + filter_str + ' { level(' + sevs \
                            + ') and facility(' + d['Facility'] + '); };\n'
            facility_txt += 'log { source(' + source_expr + '); filter(' \
                            + filter_str + '); destination(' \
                            + destination_str + '); };\n'
            txt += facility_txt

    # Write the new complete txt to the conf file
    try:
        codecs.open(conf_path, 'w', 'utf8').write(txt)
        LG().Log('INFO', 'Created omsagent syslog-ng configuration at ' + \
                         conf_path + '.')
    except:
        LG().Log('ERROR', 'Unable to create omsagent syslog-ng configuration ' \
                          'at ' + conf_path + '.')
        return False

    if os.system('sudo /opt/microsoft/omsconfig/Scripts/' \
                 'OMSSyslog-ng.post.sh') is 0:
        LG().Log('INFO', 'Successfully executed OMSSyslog-ng.post.sh.')
    else:
        LG().Log('ERROR', 'Error executing OMSSyslog-ng.post.sh.')
        return False

    return True


def GetSyslogConfMultiHomedHeaderString(WorkspaceID):
    """
    Return the header for the multi-homed section from an rsyslog conf file
    """
    return '# OMS Syslog collection for workspace ' + WorkspaceID


def ExtractFieldFromFluentDConf(WorkspaceID, field_name, default_field_value):
    """
    Search only on the first <source>..</source> config.
    Returns the field used for this workspace's syslog collection from the
    FluentD configuration file:
    If multi-homed:
    /etc/opt/microsoft/omsagent/<workspace-ID>/conf/omsagent.d/syslog.conf
    if not multi-homed:
    /etc/opt/microsoft/omsagent/conf/omsagent.conf
    """
    global omsagent_dir
    fluentd_syslog_conf = 'conf/omsagent.d/syslog.conf'
    fluentd_omsagent_conf = 'conf/omsagent.conf'
    if os.path.exists(omsagent_dir + WorkspaceID + '/' + fluentd_syslog_conf):
        config_path = omsagent_dir + WorkspaceID + '/' + fluentd_syslog_conf
    elif os.path.exists(omsagent_dir + fluentd_omsagent_conf):
        config_path = omsagent_dir + fluentd_omsagent_conf
    else:
        LG().Log('ERROR', 'No FluentD syslog configuration found: using ' \
                          'default syslog ' + field_name + ' ' + default_field_value + '.')
        return default_field_value

    try:
        txt = codecs.open(config_path, 'r', 'utf8').read()
        LG().Log('INFO', 'Succesfully read ' + config_path + ' for syslog "' + field_name + '" field.')
    except:
        LG().Log('ERROR', 'Unable to read ' + config_path + ': using default ' \
                          'syslog ' + field_name + ' "' + default_field_value + '".')
        return default_field_value
    txt_list = txt.split('</source>')
    first_source_txt = txt_list[0] + '</source>' if len(txt_list) >= 1 else txt
    field_search = r'^<source>.*type syslog[^#]*'+field_name+r' (.*?)\n.*</source>$'
    field_re = re.compile(field_search, re.M | re.S)
    field_result = field_re.search(first_source_txt)
    if field_result:
        field_value = str(field_result.group(1))
    else:
        LG().Log('ERROR', 'No protocol found in ' + config_path + ': using ' \
                          'default syslog ' + field_name + ' "' + default_field_value + '".')
        field_value = default_field_value
    return field_value


def GetSyslogConfPath():
    """
    Determine the correct rsyslog conf file path to read/update OMS
    configuration in
    """
    if not os.path.exists('/etc/rsyslog.d'):
        return rsyslog_conf_path
    elif os.path.exists(rsyslog_inc_conf_path):
        return rsyslog_inc_conf_path
    else:
        return conf_path


def ParseSyslogNGConfMultiHomed(txt, WorkspaceID):
    """
    Returns a search to extract facilities and severities for the specified
    workspace for syslog-ng format
    """
    facility_search = r'^filter f_(?P<facility>.*?)_' + WorkspaceID + '_oms.*?level\((?P<severities>.*?)\)'
    return re.compile(facility_search, re.M)


def ParseSyslogNGConf(txt):
    """
    Returns a search to extract facilities and severities for the default
    workspace for syslog-ng format
    """
    facility_search = r'^filter f_(?P<facility>.*?)_oms.*?level' \
                       '\((?P<severities>.*?)\)'
    return re.compile(facility_search, re.M)


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

# backwards compatibility with pre-multi-homing bundles
conf_path = '/etc/opt/microsoft/omsagent/conf/omsagent.conf'
omi_map_path = '/etc/opt/microsoft/omsagent/conf/omsagent.d/omi_mapping.json'
omi_map = None
workspace_specific = None
non_mh_heartbeat_cmd = '/opt/microsoft/omsagent/bin/omsadmin.sh -b'
oms_restart_cmd = 'sudo /opt/microsoft/omsagent/bin/service_control restart'

def init_omi_map():
    """
    Initialize OMI value mapping
    """
    global omi_map
    txt = codecs.open(omi_map_path, 'r', 'utf8').read()
    omi_map = eval(txt)


def init_vars(Name, GithubPath):
    init_omi_map()

    if Name is None:
        Name = ''
    if GithubPath is None:
        GithubPath = ''

def Set_Marshall(Name, GithubPath):
    init_vars(Name,GithubPath)
    return [0]

def Test_Marshall(Name, GithubPath):
    init_vars(Name,GithubPath)
    return [0]



def Get_Marshall(Name, GithubPath):
    arg_names = list(locals().keys())
    init_vars(Name, GithubPath)
    retval = 0
    output = Get(
        Name, GithubPath)
    for res in output["controls"]:
        res['id'] = protocol.MI_String(res['id'])
        res['codec_desc'] = protocol.MI_String(res['codec_desc'])
    output["version"] = protocol.MI_String(output["version"])
    controls = protocol.MI_InstanceA(output["controls"])
    Name = protocol.MI_String(Name)
    GithubPath = protocol.MI_String(GithubPath)
    Result = protocol.MI_Instance(output)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd



def Get(Name, GithubPath):
    RunCompliance("/home/nitin/InSpecProfiles/linux-baseline", "outdata.json")
    import json
    data = json.load(open('outdata.json'))
    return data


def RunCompliance (PolicyPath, OutPath)
    from subprocess import Popen, PIPE
    Command = "inspec exec %s --reporter=json-min:%s" % (PolicyPath,OutPath,)
    proc = Popen(Command, shell=True)
    proc.wait()

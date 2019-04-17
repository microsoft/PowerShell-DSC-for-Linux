#!/usr/bin/python
import fileinput
import sys
import subprocess

from imp                import load_source
from os.path            import dirname, isfile, join, realpath
from fcntl              import flock, LOCK_EX, LOCK_UN, LOCK_NB

import json
import time
import datetime
import os
import os.path
from OmsConfigHostHelpers import write_omsconfig_host_telemetry, write_omsconfig_host_event

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

omi_bindir = "<CONFIG_BINDIR>"
omicli_path = omi_bindir + "/omicli"
dsc_host_base_path = '/opt/dsc'
dsc_host_path = join(dsc_host_base_path, 'bin/dsc_host')
dsc_host_output_path = join(dsc_host_base_path, 'output')
dsc_host_lock_path = join(dsc_host_base_path, 'dsc_host_lock')
dsc_host_switch_path = join(dsc_host_base_path, 'dsc_host_ready')

if ("omsconfig" in helperlib.DSC_SCRIPT_PATH):
    write_omsconfig_host_event(pathToCurrentScript, isfile(dsc_host_switch_path))

if ("omsconfig" in helperlib.DSC_SCRIPT_PATH) and (isfile(dsc_host_switch_path)):
    is_oms_config = True
else:
    is_oms_config = False

parameters = []
if is_oms_config:
    parameters.append(dsc_host_path)
    parameters.append(dsc_host_output_path)
    parameters.append("RollBack")
else:
    parameters.append(omicli_path)
    parameters.append("iv")
    parameters.append("<DSC_NAMESPACE>")
    parameters.append("{")
    parameters.append("MSFT_DSCLocalConfigurationManager")
    parameters.append("}")
    parameters.append("RollBack")

if is_oms_config:
    try:
        # Open the dsc host lock file. This also creates a file if it does not exist
        dschostlock_filehandle = open(dsc_host_lock_path, 'w')
        print("Opened the dsc host lock file at the path '" + dsc_host_lock_path + "'")
        
        dschostlock_acquired = True

        # Acquire dsc host file lock
        try:
            flock(dschostlock_filehandle, LOCK_EX | LOCK_NB)
        except IOError:
            dschostlock_acquired = False

        if dschostlock_acquired:
            p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = p.communicate()
            print(stdout)
        else:
            print("dsc host lock already acuired by a different process")
            stdout = ''
            stderr = ''
    finally:
        # Release dsc host file lock
        flock(dschostlock_filehandle, LOCK_UN)

        # Close dsc host lock file handle
        dschostlock_filehandle.close()
else:
    p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = p.communicate()

print(stdout)
print(stderr)

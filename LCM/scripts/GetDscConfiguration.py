#!/usr/bin/python
import fileinput
import sys
import subprocess

from imp                import load_source
from os.path            import dirname, isfile, join, realpath
from fcntl              import flock, LOCK_EX, LOCK_UN

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

omi_bindir = "<CONFIG_BINDIR>"
omicli_path = omi_bindir + "/omicli"

parameters = []

if "omsconfig" in helperlib.DSC_SCRIPT_PATH:
    parameters.append("/opt/dsc/bin/dsc_host")
    parameters.append("/opt/dsc/output")
    parameters.append("GetConfiguration")
else:
    parameters.append(omicli_path)
    parameters.append("iv")
    parameters.append("<DSC_NAMESPACE>")
    parameters.append("{")
    parameters.append("MSFT_DSCLocalConfigurationManager")
    parameters.append("}")
    parameters.append("GetConfiguration")

p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = p.communicate()

print(stdout)
print(stderr)



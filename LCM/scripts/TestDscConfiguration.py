#!/usr/bin/python
import fileinput
import sys
import subprocess

# omi_bindir = "<CONFIG_BINDIR>"
# omicli_path = omi_bindir + "/omicli"

parameters = []
parameters.append("/opt/dsc/bin/dsc_host")
parameters.append("/opt/dsc/output")
parameters.append("TestConfiguration")
# parameters.append(omicli_path)
# parameters.append("iv")
# parameters.append("<DSC_NAMESPACE>")
# parameters.append("{")
# parameters.append("MSFT_DSCLocalConfigurationManager")
# parameters.append("}")
# parameters.append("TestConfiguration")

#s = ""
#for param in parameters:
#    s += param + " "

p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = p.communicate()

print(stdout)
print(stderr)



#!/usr/bin/python
import fileinput
import sys
import subprocess

omicli_path = "/opt/omi/bin/omicli"

parameters = []
parameters.append(omicli_path)
parameters.append("iv")
parameters.append("root/Microsoft/DesiredStateConfiguration")
parameters.append("{")
parameters.append("MSFT_DSCLocalConfigurationManager")
parameters.append("}")
parameters.append("GetConfiguration")

#s = ""
#for param in parameters:
#    s += param + " "

p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = p.communicate()

print(stdout)
print(stderr)



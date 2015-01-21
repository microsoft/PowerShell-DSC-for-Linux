#!/usr/bin/python
import fileinput
import sys
import subprocess

def usage():
    print("Usage:")
    print("    " + sys.argv[0] + " -configurationmof FILE")
    exit(1)
    

if len(sys.argv) != 3:
    usage()

if sys.argv[1].lower() != "-configurationmof":
    usage()

filedata = open(sys.argv[2], "r").read()

outtokens = []
for char in filedata:
    outtokens.append(str(ord(char)))

omicli_path = "/opt/omi/bin/omicli"

parameters = []
parameters.append(omicli_path)
parameters.append("iv")
parameters.append("root/Microsoft/DesiredStateConfiguration")
parameters.append("{")
parameters.append("MSFT_DSCLocalConfigurationManager")
parameters.append("}")
parameters.append("SendConfigurationApply")
parameters.append("{")
parameters.append("ConfigurationData")
parameters.append("[")
# insert configurationmof data here
for token in outtokens:
    parameters.append(token)
parameters.append("]")
parameters.append("}")

#s = ""
#for param in parameters:
#    s += param + " "

p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = p.communicate()

print(stdout)
print(stderr)



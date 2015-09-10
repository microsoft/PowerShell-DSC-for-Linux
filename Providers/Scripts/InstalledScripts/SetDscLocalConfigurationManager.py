#!/usr/bin/python
import fileinput
import sys
import subprocess

def usage():
    print("Usage:")
    print("    " + sys.argv[0] + " -configurationmof FILE")
    sys.exit(1)
    

if len(sys.argv) != 3:
    usage()

if sys.argv[1].lower() != "-configurationmof":
    usage()

filedata = open(sys.argv[2], "r").read()

outtokens = []
for char in filedata:
    outtokens.append(str(ord(char)))

omi_bindir = "<CONFIG_BINDIR>"
omicli_path = omi_bindir + "/omicli"

parameters = []
parameters.append(omicli_path)
parameters.append("iv")
parameters.append("root/Microsoft/DesiredStateConfiguration")
parameters.append("{")
parameters.append("MSFT_DSCLocalConfigurationManager")
parameters.append("}")
parameters.append("SendMetaConfigurationApply")
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



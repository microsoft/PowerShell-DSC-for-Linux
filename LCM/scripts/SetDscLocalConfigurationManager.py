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

try:
    filedata = open(sys.argv[2], "r").read()
except:
    filedata = open(sys.argv[2], "r", encoding="utf-16").read()

outtokens = []
for char in filedata:
    outtokens.append(str(ord(char)))

omi_bindir = "<CONFIG_BINDIR>"
omicli_path = omi_bindir + "/omicli"

parameters = []
parameters.append(omicli_path)
parameters.append("iv")
parameters.append("<DSC_NAMESPACE>")
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


# Apply the metaconfig
proc = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE, close_fds=True)
exit_code = proc.wait()
print(proc.stdout.read())
errorMsg = proc.stderr.read()

if ((exit_code != 0) or (errorMsg)):
    sys.stderr.write(errorMsg)
    sys.exit(1)
else:
    print("Successfully applied metaconfig.")



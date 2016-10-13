#!/usr/bin/python
import fileinput
import sys
import subprocess
import os
import fcntl
import shutil
from xml.dom.minidom import parse

def usage():
   print("""Usage: PerformInventory.py [OPTIONS]
OPTIONS (case insensitive):
 --InMOF PATH_TO_INVENTORY.MOF
 --OutXML PATH_TO_OUTPUT_REPORT.XML
 --help
""")

Variables = dict()

# Parse command line arguments
args = []
optlist = []

command_line_length = len(sys.argv)
i = 0
inArgument = False
currentArgument = ""
arg = ""
while i < command_line_length:
   arg = sys.argv[i]
   if i == 0:
      # skip the program name
      i += 1
      continue

   if inArgument:
      Variables[currentArgument] = arg
      inArgument = False
   else:
      if arg[0:2] == "--":
         inArgument = True
         currentArgument = arg[2:].lower()
      else:
         # The rest are not options
         args = sys.argv[i:]
         break
   i += 1
   
if inArgument:
   Variables[currentArgument] = arg

AcceptableOptions = ["inmof", "outxml", "help"]

if "help" in Variables:
   usage()
   sys.exit(0)

optionsValid = True
for arg in Variables.keys():
   if arg.lower() not in AcceptableOptions:
      optionsValid = False
      print("Error: %s is not a valid option" % arg)

if optionsValid == False:
   usage()
   sys.exit(1)

omi_bindir = "<CONFIG_BINDIR>"
omi_sysconfdir = "<CONFIG_SYSCONFDIR>"
dsc_sysconfdir = omi_sysconfdir + "/<CONFIG_SYSCONFDIR_DSC>"
dsc_reportdir = dsc_sysconfdir + "/InventoryReports"
omicli_path = omi_bindir + "/omicli"
temp_report_path = dsc_sysconfdir + "/configuration/Inventory.xml.temp"
report_path = dsc_sysconfdir + "/configuration/Inventory.xml"

if "outxml" in Variables:
    report_path = Variables["outxml"]

parameters = []
parameters.append(omicli_path)
parameters.append("iv")
parameters.append("<DSC_NAMESPACE>")
parameters.append("{")
parameters.append("MSFT_DSCLocalConfigurationManager")
parameters.append("}")

if "inmof" in Variables:
    parameters.append("PerformInventoryOOB")
    parameters.append("{")
    parameters.append("InventoryMOFPath")
    parameters.append(Variables["inmof"])
    parameters.append("}")
else:
    parameters.append("PerformInventory")

if len(dsc_sysconfdir) < 10:
    # something has gone horribly wrong. error out before we attempt to remove the entire file system
    print("Error: Something has gone horribly wrong with the directory paths.")
    sys.exit(1)

# Acquire inventory file lock
inventory_lock = open(dsc_sysconfdir + "/inventory_lock", "w+")
fcntl.flock(inventory_lock, fcntl.LOCK_EX)

os.system("touch " + temp_report_path)
os.system("rm -f " + dsc_reportdir + "/*")

p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = p.communicate()
retval = p.returncode

print(stdout)
print(stderr)

# combine reports together
reportFiles = os.listdir(dsc_reportdir)

final_xml_report = '<INSTANCE CLASSNAME="Inventory"><PROPERTY.ARRAY NAME="Instances" TYPE="string" EmbeddedObject="object"><VALUE.ARRAY>'
values = []
for f in reportFiles:
    if not os.path.isfile(dsc_reportdir + "/" + f):
        continue
    d = parse(dsc_reportdir + "/" + f)
    for valueNode in d.getElementsByTagName('VALUE'):
        values.append(valueNode.toxml())

final_xml_report = final_xml_report + "".join(values) + "</VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"

f = open(temp_report_path, "w")
f.write(final_xml_report)
f.close()
os.system("rm -f " + dsc_reportdir + "/*")
shutil.move(temp_report_path, report_path)

# Release inventory file lock
fcntl.flock(inventory_lock, fcntl.LOCK_UN)

sys.exit(retval)

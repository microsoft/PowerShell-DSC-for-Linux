#!/usr/bin/python
import fileinput
import sys
import subprocess
import os
from xml.dom.minidom import parse

omi_bindir = "<CONFIG_BINDIR>"
omi_sysconfdir = "<CONFIG_SYSCONFDIR>"
dsc_sysconfdir = omi_sysconfdir + "/<CONFIG_SYSCONFDIR_DSC>"
dsc_reportdir = dsc_sysconfdir + "/InventoryReports"
omicli_path = omi_bindir + "/omicli"

parameters = []
parameters.append(omicli_path)
parameters.append("iv")
parameters.append("<DSC_NAMESPACE>")
parameters.append("{")
parameters.append("MSFT_DSCLocalConfigurationManager")
parameters.append("}")
parameters.append("PerformInventory")

if len(dsc_sysconfdir) < 10:
    # something has gone horribly wrong. error out before we attempt to remove the entire file system
    print("Error: Something has gone horribly wrong with the directory paths.")
    sys.exit(1)
    
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

f = open(dsc_sysconfdir + "/configuration/Inventory.xml.temp", "w")
f.write(final_xml_report)
f.close()
os.system("rm -f " + dsc_reportdir + "/*")
os.rename(dsc_sysconfdir + "/configuration/Inventory.xml.temp", dsc_sysconfdir + "/configuration/Inventory.xml")
sys.exit(retval)

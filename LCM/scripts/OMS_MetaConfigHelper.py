#!/usr/bin/python
import os
import sys

conf_path = "/etc/opt/microsoft/omsagent/conf/omsadmin.conf"
metamof_path = "/etc/opt/omi/conf/omsconfig/generated_meta_config.mof"
agentid_path = "/etc/opt/omi/conf/omsconfig/agentid"
omshelper_disable_path = "/etc/opt/omi/conf/omsconfig/omshelper_disable"

def generate_meta_mof(serverurl):
    return """
instance of MSFT_WebDownloadManager as $MSFT_WebDownloadManager1ref
{
 ResourceID = "[ConfigurationRepositoryWeb]OMSConfigurationManager";
 SourceInfo = "GeneratedLocally";
 ServerURL = "%s";
};


instance of MSFT_WebReportManager as $MSFT_WebReportManager1ref
{
SourceInfo = "GeneratedLocally";
 ServerURL = "%s";
 ResourceID = "[ReportServerWeb]OMSConfigurationManager";
};


instance of MSFT_WebResourceManager as $MSFT_WebResourceManager1ref
{
SourceInfo = "GeneratedLocally";
ServerURL = "%s";
ResourceID = "[ResourceRepositoryWeb]OMSConfigurationManager";
};


instance of MSFT_DSCMetaConfiguration as $MSFT_DSCMetaConfiguration1ref
{
 RefreshMode = "Pull";
 AllowModuleOverwrite = True;
 RefreshFrequencyMins = 5;
 RebootNodeIfNeeded = False;
 ConfigurationModeFrequencyMins = 5;
 ConfigurationMode = "ApplyAndAutoCorrect";

  ResourceModuleManagers = {
   $MSFT_WebResourceManager1ref  
  };
  
  ReportManagers = {
   $MSFT_WebReportManager1ref
  };

  ConfigurationDownloadManagers = {
   $MSFT_WebDownloadManager1ref  
  };

};

instance of OMI_ConfigurationDocument
{
 Version="2.0.0";
 MinimumCompatibleVersion = "2.0.0";
};
""" % (serverurl, serverurl, serverurl)



def generate_push_meta_mof():
    return """
instance of MSFT_DSCMetaConfiguration as $MSFT_DSCMetaConfiguration1ref
{
 RefreshMode = "Push";
 AllowModuleOverwrite = True;
 RefreshFrequencyMins = 30;
 RebootNodeIfNeeded = True;
 ConfigurationModeFrequencyMins = 60;
 ConfigurationMode = "ApplyAndAutoCorrect";
};

instance of OMI_ConfigurationDocument
{
 Version="2.0.0";
 MinimumCompatibleVersion = "2.0.0";
};
"""

def source_file(filename):
    retval = dict()
    f = open(filename, "r")
    contents = f.read()
    f.close()
    lines = contents.splitlines()
    for line in lines:
        # Find first '='; everything before is key, everything after is value
        midpoint = line.find("=")
        if (midpoint == 0 or midpoint == -1):
            # Skip over lines without = or lines that begin with =
            continue
        key = line[:midpoint]
        value = line[midpoint+1:]
        retval[key] = value
    return retval


Variables = dict()
Defines = []

# Parse command line arguments
args = []
optlist = []
for arg in sys.argv[1:]:
    if len(arg) < 2:
        # Must be a file
        args.append(arg)
        continue
    
    if arg[0:2] == "--":
        tokens = arg[2:].split("=",1)
        if len(tokens) == 1:
            # This is a define
            Defines.append(tokens[0])
            Variables[tokens[0]] = ""
        else:
            # This is a variable
            Variables[tokens[0]] = tokens[1]
    else:
        args.append(arg)

enable_flag = False
disable_flag = False
if "enable" in Variables:
    enable_flag = True
if "disable" in Variables:
    disable_flag = True

if enable_flag == True and disable_flag == True:
    print("Error: Cannot use both disable and enable options at the same time.")
    sys.exit(1)

if enable_flag == True:
    if os.path.isfile(omshelper_disable_path):
        os.remove(omshelper_disable_path)
if disable_flag == True:
    open(omshelper_disable_path, "w").write("a")


if not os.path.isfile(omshelper_disable_path):
    # source the omsadmin conf file and get the key/value pairs
    keyvals = source_file(conf_path)
    
    # Looking for DSC_ENDPOINT and AGENT_GUID

    if "DSC_ENDPOINT" not in keyvals or "AGENT_GUID" not in keyvals:
        print("Error: Unable to find needed key/value pairs in " + conf_path)
        sys.exit(1)

    DSC_ENDPOINT = keyvals["DSC_ENDPOINT"].strip()

    # Cut off everything after Nodes in the URL including Nodes, if Nodes is in URL (it should be)
    Nodes_loc = DSC_ENDPOINT.find("/Nodes")
    if Nodes_loc != -1:
        DSC_ENDPOINT = DSC_ENDPOINT[:Nodes_loc]
    AGENT_GUID = keyvals["AGENT_GUID"].strip()
    
    # Write out agentID
    f = open(agentid_path, "w")
    f.write(AGENT_GUID)
    f.close()

    os.system("chown omsagent " + agentid_path)
    
    # Write metaconfig
    metaConfig = generate_meta_mof(DSC_ENDPOINT)
else:
    metaConfig = generate_push_meta_mof()

f = open(metamof_path, "w")
f.write(metaConfig)
f.close()

os.system("chown omsagent " + metamof_path)

if os.geteuid() == 0:
    commandToRun = "su - omsagent -c '/opt/microsoft/omsconfig/Scripts/SetDscLocalConfigurationManager.py -configurationmof " + metamof_path + "'"
else:
    commandToRun = "/opt/microsoft/omsconfig/Scripts/SetDscLocalConfigurationManager.py -configurationmof " + metamof_path

# Apply the metaconfig using SetDscLocalConfiguration
commandToRun += " 1> /dev/null"
retval = os.system(commandToRun)
if (retval != 0):
    print("Error on running command: " + commandToRun)
    sys.exit(1)
else:
    print("Successfully configured omsconfig.")


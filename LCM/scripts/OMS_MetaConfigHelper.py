#!/usr/bin/python
import os
import sys

conf_path = "/etc/opt/microsoft/omsagent/conf/omsadmin.conf"
metamof_path = "/etc/opt/omi/conf/omsconfig/generated_meta_config.mof"
agentid_path = "/etc/opt/omi/conf/omsconfig/agentid"

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


instance of MSFT_DSCMetaConfiguration as $MSFT_DSCMetaConfiguration1ref
{
 RefreshMode = "Pull";
 AllowModuleOverwrite = True;
 RefreshFrequencyMins = 30;
 RebootNodeIfNeeded = True;
 ConfigurationModeFrequencyMins = 60;
 ConfigurationMode = "ApplyAndAutoCorrect";

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
""" % (serverurl, serverurl)

def source_file(filename):
    retval = dict()
    contents = open(filename,"r").read()
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

metaConfig = generate_meta_mof(DSC_ENDPOINT)

# Write out agentID
f = open(agentid_path, "w")
f.write(AGENT_GUID)
f.close()

# Write metaconfig
f = open(metamof_path, "w")
f.write(metaConfig)
f.close()

# Apply the metaconfig using SetDscLocalConfiguration
commandToRun = "/opt/microsoft/omsconfig/Scripts/SetDscLocalConfigurationManager.py -configurationmof " + metamof_path
retval = os.system(commandToRun)
if (retval != 0):
    print("Error on running command: " + commandToRun)
    sys.exit(1)


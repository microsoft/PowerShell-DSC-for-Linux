#!/usr/bin/python
import os
import sys
import glob

conf_path = "/etc/opt/microsoft/omsagent/conf/omsadmin.conf" # TODO shouldn't use
omsagent_path = "/etc/opt/microsoft/omsagent/"
oms_agentid_path = "/etc/opt/microsoft/omsagent/agentid"
conf_path2 = "/etc/opt/microsoft/omsagent/*/conf/omsadmin.conf"
conf_files = glob.glob(conf_path2) 

metamof_path = "/etc/opt/omi/conf/omsconfig/generated_meta_config.mof"
agentid_path = "/etc/opt/omi/conf/omsconfig/agentid"
omshelper_disable_path = "/etc/opt/omi/conf/omsconfig/omshelper_disable" # TODO do I need to change this file?

# TODO IDEA to guard against circular logic, copy list_workspaces here to check for active workspaces
guid_regex = '^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$'

def generate_webdownloadmgr_mof(val, serverurl):
    return """
instance of MSFT_WebDownloadManager as $MSFT_WebDownloadManager%sref
{
 ResourceID = "[ConfigurationRepositoryWeb]OMSConfigurationManager%s";
 SourceInfo = "GeneratedLocally";
 ServerURL = "%s";
 ConfigurationNames = {
     "Workspace%s"
 };
};

""" % (val, val, serverurl, val)

# TODO make sure no unnecessary semicolons are present in MOFs
# TODO change spacing of brackets?
def generate_partial_config_mof(val):
    return """
instance of MSFT_PartialConfiguration as $MSFT_PartialConfiguration%sref
{
 SourceInfo = "GeneratedLocally";
 RefreshMode = "Pull";
 Description = "Workspace%s";
 ResourceID = "[PartialConfiguration]Workspace%s";
 ConfigurationSource = {
     "[ConfigurationRepositoryWeb]OMSConfigurationManager%s"
 };
};

""" % (val, val, val, val)

def generate_meta_mof(serverurl, dm, pf):
    """
    ? serverurls: An array of strings, each a server URL
    TODO
    TODO partial configurations must be available through AMS first
    """
    return """
instance of MSFT_WebReportManager as $MSFT_WebReportManager1ref
{
 SourceInfo = "GeneratedLocally";
 ServerURL = "%s";
 ResourceID = "[ReportServerWeb]OMSConfigurationManager1";
};

instance of MSFT_DSCMetaConfiguration as $MSFT_DSCMetaConfiguration1ref
{
 RefreshMode = "Pull";
 AllowModuleOverwrite = True;
 RefreshFrequencyMins = 5;
 RebootNodeIfNeeded = False;
 ConfigurationModeFrequencyMins = 5;
 ConfigurationMode = "ApplyAndAutoCorrect";

  ReportManagers = {
   $MSFT_WebReportManager1ref
  };

  ConfigurationDownloadManagers = {
    %s
  };
  
  PartialConfigurations = {
    %s
  };

};

instance of OMI_ConfigurationDocument
{
 Version="2.0.0";
 MinimumCompatibleVersion = "2.0.0";
};
""" % (serverurl, dm, pf)

def generate_push_meta_mof():
    """
    TODO: do I need to change the format of this?
    TODO IDEA: perhaps eventually we can make options to pull from one workspace and not another, but for now, let's just turn all values of "Pull" to "Push"
    """
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
    # print retval
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
    open(omshelper_disable_path, "w").write("a") # TODO why am I creating this file? what does it do?


if not os.path.isfile(omshelper_disable_path): # TODO is this file still shipped? Do I have to change it?
    # source the omsadmin conf file and get the key/value pairs
    # TODO source all valid omsadmin.conf files (use regex? or uuid?)
    # remember: valid omsadmin.conf files only apply when the omsagent process for that workspace is running
    # If any version of python may be running, then I should use regex
    print("omsadmin.conf files:")
    print(conf_files)
    metaConfig = ""
    downloadManagers = []
    partialConfigs = []

    # loop through every omsadmin conf file and get the key/value pairs
    for index, conf_path in enumerate(conf_files):
        keyvals = source_file(conf_path)

        # If machine-wide agentid file is available, then read agent guid from there
        # TODO move outside of for loop
        if os.path.isfile(oms_agentid_path):
            f = open(oms_agentid_path, "r")
            contents = f.read().strip()
            f.close()
            keyvals["AGENT_GUID"] = contents
    
        # Looking for DSC_ENDPOINT and AGENT_GUID
        if "DSC_ENDPOINT" not in keyvals or "AGENT_GUID" not in keyvals or "WORKSPACE_ID" not in keyvals:
            print("Error: Unable to find needed key/value pairs in " + conf_path)
            sys.exit(1)

        DSC_ENDPOINT = keyvals["DSC_ENDPOINT"].strip()

        # Cut off everything after Nodes in the URL including Nodes, if Nodes is in URL (it should be)
        Nodes_loc = DSC_ENDPOINT.find("/Nodes")
        if Nodes_loc != -1:
            DSC_ENDPOINT = DSC_ENDPOINT[:Nodes_loc]
        AGENT_GUID = keyvals["AGENT_GUID"].strip()
        WORKSPACE_ID = keyvals["WORKSPACE_ID"].strip()
    
        # TODO just pick the first workspace ID in the list to be the singular MSFT_WebReportManager (what is it used for, anyway?)
        # Check if workspace is primary; get values for primary wsid and dsc endpoint 
        if not os.path.isfile(os.path.join(omsagent_path, WORKSPACE_ID, "conf/.multihoming_marker")):
            PRIMARY_WS =  WORKSPACE_ID  
            PRIMARY_DSC_ENDPOINT = DSC_ENDPOINT

        # Write out agentID
        f = open(agentid_path, "w")
        f.write(AGENT_GUID)
        f.close()

        os.system("chown omsagent " + agentid_path)

        # Write metaconfig for download manager and partial config
        val = str(index + 1)
        downloadManagers.append("$MSFT_WebDownloadManager%sref" %(val))
        metaConfig += generate_webdownloadmgr_mof(val, DSC_ENDPOINT)

        partialConfigs.append("$MSFT_PartialConfiguration%sref" %(val))
        metaConfig += generate_partial_config_mof(val)

    dm = ",\n    ".join(downloadManagers)
    pf = ",\n    ".join(partialConfigs)
    # Write metaconfig 
    metaConfig += generate_meta_mof(PRIMARY_DSC_ENDPOINT, dm, pf)
else:
    metaConfig = generate_push_meta_mof()

print("Metaconfig:\n")
print metaConfig

# f = open(metamof_path, "w")
# f.write(metaConfig)
# f.close()
# 
# os.system("chown omsagent " + metamof_path)
# 
# if os.geteuid() == 0:
#     commandToRun = "su - omsagent -c '/opt/microsoft/omsconfig/Scripts/SetDscLocalConfigurationManager.py -configurationmof " + metamof_path + "'"
# else:
#     commandToRun = "/opt/microsoft/omsconfig/Scripts/SetDscLocalConfigurationManager.py -configurationmof " + metamof_path
# 
# # Apply the metaconfig using SetDscLocalConfiguration
# #commandToRun += " 1> /dev/null"
# retval = os.system(commandToRun)
# if (retval != 0):
#     print("Error on running command: " + commandToRun)
#     sys.exit(1)
# else:
#     print("Successfully configured omsconfig.")

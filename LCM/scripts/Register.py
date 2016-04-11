#!/usr/bin/python
import sys
import os
import os.path
import tempfile
import shutil

def usage():
   print("""Usage: Register.py [OPTIONS]
OPTIONS:
--RegistrationKey KEY
--ServerURL URL
--RefreshFrequencyMins NUM
--ConfigurationModeFrequencyMins NUM
--ConfigurationMode MODE
--RefreshMode (Pull|Push)
""")

# register Linux DSC agent with AA
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
        current_option = tokens[0]
        if len(tokens) == 1:
            # This is a define
            Defines.append(current_option.lower())
            Variables[current_option] = ""
        else:
            # This is a variable
            Variables[current_option] = tokens[1]
    else:
        args.append(arg)

AcceptableOptions = ["registrationkey", "serverurl", "refreshfrequencymins", "configurationmodefrequencymins", "configurationmode", "refreshmode"]

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

# If RefreshMode == Pull (which is default), then RegistrationKey and ServerURL are required.
RefreshMode = "Pull"
if "refreshmode" in Varables:
   RefreshMode = Variables["refreshmode"]

if RefreshMode == "Pull":
   if "registrationkey" not in Variables:
      print("Error: RegistrationKey must be specified for Pull mode")
      sys.exit(1)
   if "serverurl" not in Variables:
      print("Error: ServerURL must be specified for Pull mode")
      sys.exit(1)

ConfigurationMode = "ApplyAndMonitor"
if "configurationmode" in Variables:
   ConfigurationMode = Variables["configurationmode"]

RefreshFrequencyMins = "30"
if "refreshfrequencymins" in Variables:
   RefreshFrequencyMins = Variables["refreshfrequencymins"]
   
ConfigurationModeFrequencyMins = "15"
if "configurationmodefrequencymins" in Variables:
   ConfigurationModeFrequencyMins = Variables["configurationmodefrequencymins"]

metaConfig = ""
if Refreshmode == "Push":
   metaConfig = """
     instance of MSFT_DSCMetaConfiguration as $MSFT_DSCMetaConfiguration1ref
     {
     DownloadManagerName = "WebDownloadManager";
     RefreshMode = "<REFRESHMODE>";
     ConfigurationMode = "<CONFIGURATIONMODE>";
     
     };
     
     instance of OMI_ConfigurationDocument
     {
     Version="1.0.0";
     };
     """
else:
   metaConfig="""
     instance of MSFT_WebDownloadManager as $MSFT_WebDownloadManager1ref
     {
     ResourceID = "[ConfigurationRepositoryWeb]AzureAutomationDSC";
     SourceInfo = "C:\\\\OaaS-RegistrationMetaConfig2.ps1::20::9::ConfigurationRepositoryWeb";
     RegistrationKey = "<REGKEY>"; 
     ServerURL = "<SERVERURL>";
     };
     
     instance of MSFT_WebResourceManager as $MSFT_WebResourceManager1ref
     {
     SourceInfo = "C:\\\\OaaS-RegistrationMetaConfig2.ps1::27::9::ResourceRepositoryWeb";
     ResourceID = "[ResourceRepositoryWeb]AzureAutomationDSC";
     RegistrationKey = "<REGKEY>"; 
     ServerURL = "<SERVERURL>";
     };
     
     instance of MSFT_WebReportManager as $MSFT_WebReportManager1ref
     {
     SourceInfo = "C:\\\\OaaS-RegistrationMetaConfig2.ps1::34::9::ReportServerWeb";
     ResourceID = "[ReportServerWeb]AzureAutomationDSC";
     RegistrationKey = "<REGKEY>"; 
     ServerURL = "<SERVERURL>";
     };
     
     instance of MSFT_DSCMetaConfiguration as $MSFT_DSCMetaConfiguration1ref
     {
     RefreshMode = "<REFRESHMODE>";
     AllowModuleOverwrite = False;
     RefreshFrequencyMins = <REFRESHFREQUENCYMINS>;
     RebootNodeIfNeeded = False;
     ConfigurationModeFrequencyMins = <CONFIGURATIONMODEFREQUENCYMINS;
     ConfigurationMode = "<CONFIGURATIONMODE>";
     
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
     CompatibleVersionAdditionalProperties= { "MSFT_DSCMetaConfiguration:StatusRetentionTimeInDays" };
     Author="azureautomation";
     Name="RegistrationMetaConfig";
     };
"""
metaConfig = metaConfig.replace("<REFRESHMODE>", RefreshMode)
metaConfig = metaConfig.replace("<REFRESHFREQUENCYMINS>", RefreshFrequencyMins)
metaConfig = metaConfig.replace("<CONFIGURATIONMODEFREQUENCYMINS>", ConfigurationModeFrequencyMins)
metaConfig = metaConfig.replace("<CONFIGURATIONMODE>", ConfigurationMode)
metaConfig = metaConfig.replace("<SERVERURL>", ServerURL)
metaConfig = metaConfig.replace("<REGKEY>", RegistrationKey)


# Write to file and run SendMetaConfigurationApply.py
tempdir = tempfile.mkdtemp()
meta_path = tempdir + "/metaconf.mof"
f = open(meta_path, "w")
f.write(metaConfig)
f.close()

os.system("<DSC_SCRIPT_PATH>/SetDscLocalConfigurationManager.py -configurationmof " + meta_path)

shutil.rmtree(tempdir)

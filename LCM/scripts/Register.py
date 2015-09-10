#!/usr/bin/python
import sys
import os
import os.path
import tempfile
import shutil

# register Linux DSC agent with AA

#agentidpath = "/etc/opt/omi/conf/dsc/agentid"
#
#if os.path.isfile(agentidpath):
#   agentid = open(agentidpath, "r").read()
#else:
#   agentid = open("/proc/sys/kernel/random/uuid", "r").read()
#   agentid = agentid.upper()

#input:
#  endpoint
#  key
# output:
#  MetaConfig to apply, OR apply the metaconfig after generating it and silent output?

def usage():
   print("Usage: Register.py RegistrationKey ServerURL")

if len(sys.argv) != 3:
   usage()
   exit(1)

RegistrationKey = sys.argv[1]
ServerURL = sys.argv[2]


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
     RefreshMode = "Pull";
     AllowModuleOverwrite = False;
     RefreshFrequencyMins = 30;
     RebootNodeIfNeeded = False;
     ConfigurationModeFrequencyMins = 15;
     ConfigurationMode = "ApplyAndMonitor";

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

metaConfig = metaConfig.replace("<SERVERURL>", ServerURL)
metaConfig = metaConfig.replace("<REGKEY>", RegistrationKey)

#print(metaConfig)


# Write to file and run SendMetaConfigurationApply.py
tempdir = tempfile.mkdtemp()
meta_path = tempdir + "/metaconf.mof"
f = open(meta_path, "w")
f.write(metaConfig)
f.close()

os.system("/opt/microsoft/dsc/Scripts/SetDscLocalConfigurationManager.py -configurationmof " + meta_path)

shutil.rmtree(tempdir)

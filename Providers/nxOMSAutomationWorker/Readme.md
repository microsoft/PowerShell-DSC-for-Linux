# Releasing a new Automation Linux Hybrid Worker version

## Merging and Releasing Code Changes

1. Merge your changes in repo - https://github.com/microsoft/PowerShell-DSC-for-Linux
Upgrade the worker version in Makefile and 3 other configuration files. 
   Approver DL - aaeng@microsoft.com

2. Fork and raise a PR to repo - https://github.com/microsoft/Build-OMS-Agent-for-Linux to update dsc-module. Approver DL - OMSLinuxAgent@microsoft.com, hestolz@microsoft.com

```
git clone --recursive https://github.com/microsoft/Build-OMS-Agent-for-Linux.git
cd dsc
git pull origin master
cd ..
git add dsc
commit -a -m "update dsc master branch"
git push origin master
```

3. Join this myaccess project '1BPipelineGHMicrosoft' for downloading the new module. The repository generates a daily build and updated package can be downloaded from the artifacts from here - https://github-private.visualstudio.com/microsoft/_build?definitionId=93&_a=summary

4. Check-in the new version zip file in src\Modules in https://dev.azure.com/msazure/One/_git/Mgmt-Automation-DSC-Modules and merge the PR.
Approver DL - aaeng@microsoft.com

5. Release the new module version in all regions using the release - https://dev.azure.com/msazure/One/_release?definitionId=20089&view=mine&_a=releases

## Releasing to Dev Scope for Testing

1. Execute a Geneva Action to promote some workspace to Dev Scope. Geneva portal -> Test Environment -> AzureLogAnalyticsControlPlane -> Ams -> ChangeCustomerType
    - Endpoint - AzureLogAnalyticsControlPlane
    - Ams Region - inteus
    - Workspace Id - <workspace_id>
    - Customer Type Parameter - Dev

2. Execute Geneva Action to upgrade the version of dsc module. Geneva portal -> Test Environment -> AzureLogAnalyticsControlPlane -> Ams -> UpdateModuleVersion
    - Endpoint - AzureLogAnalyticsControlPlane
    - Ams Region - inteus
    - Module - nxOMSAutomationWorker
    - Version - 1.7.5.0
    - Scope - Dev




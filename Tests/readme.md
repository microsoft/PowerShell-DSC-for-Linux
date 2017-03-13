## Running Tests

Two pull servers are needed to successfully run all tests.

Update Linux Client information in DSCLinuxTestConfig.json. Add information about VM Name, root user password.
Install-Package Pester on windows machine


```
$env:DSC_LINUX_TEST_CONFIG = 'MyTestConfiguration.json'
Invoke-Pester
```


## Test Configuration file.
The pester tests read a json file to determine the target Linux system to test as well
as the two pull servers to use. This file is parsed by Get-TestConfiguration and consumed by various support methods such as New-PartialConfigPullScript.

The default file expected by the tests is DSCLinuxTestConfig.json.  To provide custom settings, such as when running on private dev machines or automation systems, two approaches are supported:

1: Overwrite the file

2: Create a new file and set the ```DSC_LINUX_TEST_CONFIG``` environment variable before running tests.  The environment variable takes precedence.

The current file is a simple dictionary containing the below entries. 

### Settings
This section defines meta configuration settings to set on the Linux system.

### LinuxClient: 
The LinuxClient settings require three values
* Name: The name of the linux machine containing the build to test.
* UserName: The name of the user to use to connect to the machine. This is typically 'root'
* Password: The password associated with the user.
* Port: The optional port to use to connect to the target OMI server. If not defined, 5986 is used.

### PullServer1
The first of two pull servers needed to run the tests. This setting requires 3 settings:
* Name: The name of the machine containing the pull server.
* ServerURL: The server URL to use to connect to the pull server.
* RegistrationKey: The registration key to use to register with the pull server.
  Update-PullServer in DscLinux.Tests.Helper.psm1 will ensure this value is added to the registrationkeys.txt file on the pull server.
* DscServicePath: the full qualified [UNC] path to the DscService directory on the target server. For remote servers, this should be the UNC path. For local pull servers, the local file system path. This is typically the path to c:\Program Files\WindowsPowerShell\DscService. Update-PullServer and Publish-Mof will use this path to copy mof files to the pull server.

### PullServer2
The second of two pull servers needed to run the tests. The pull servers can be hosted on the same 
machine as long as the ports in the ServiceURL are different.  The settings are the same as the first pull server.

### ReportServer
The settings required to register and send status to the report server.
* Name: The name of the machine containing the pull server.
* ServerURL: The server URL to use to connect to the pull server.
* RegistrationKey: The registration key to use to register with the pull server.
  Update-PullServer in DscLinux.Tests.Helper.psm1 will ensure this value is added to the registrationkeys.txt file on the pull server.

### ResourceServer
The settings required to register and query a resource server.  Typically, the values here mirror the values for the first pull server.
* Name: The name of the machine containing the pull server.
* ServerURL: The server URL to use to connect to the pull server.
* RegistrationKey: The registration key to use to register with the pull server.
  Update-PullServer in DscLinux.Tests.Helper.psm1 will ensure this value is added to the registrationkeys.txt file on the pull server.
* ModulePath: the pull qualfied path to DscServer\Modules directory. For remote systems, this must be the UNC path. For local systems, the local file path.  Update-PullServer and Publish-ResourcePackage will use this information, when provided, to update resource modules.   

### NOTES
* When publishing MOF or resource packages, a checksum file will be generated automatically as part of the copy step. This applies to Update-PullServer, Publish-Mof, and Publish-ResourcePackage.
* For meta configuration settings that can not be defined on a windows system, Update-MetaConfigurationSetting can be used to set the value directly in the MOF. See DSCLinux.PartialConfig.Pester.Tests.ps1 for an example of it's usage. Examples include RefreshFrequencyMins to set a value < 30 and DisableModuleSignatureValidation which has been replaced on Windows but still present on Linux.

### Example configuration file
```
{
    "Settings": {
        "AllowModuleOverwrite": true,
        "ConfigurationMode": "ApplyAndAutoCorrect",
        "ConfigurationModeFrequencyMins": 15,
        "RebootNodeIfNeeded": true,
        "RefreshFrequencyMins": 15,
        "RefreshMode": "PULL"      
    },

    "LinuxClient": {
        "Name": "mylinuxsystem",
        "UserName": "root",
        "Password": "rootpassword"
    },

    "PullServer1": {
        "Name": "mypullserver1",
        "ServerURL": "http://mypullserver1:8080/PSDSCPullServer.svc",
registrationkeys.txt file on the pull server
        "RegistrationKey": "7f466f8e-027e-44c2-9a7b-897c08b355f1",
        "DscServicePath": "\\\\mypullserver1\\c$\\Program Files\\WindowsPowerShell\\DscService"
    },

    "PullServer2": {
        "Name": "mypullserver1b",
        "ServerURL": "http://mypullserver2:8080/PSDSCPullServer.svc",
        "RegistrationKey": "599f9c7d-a0b1-4a1a-8593-8728a99c3fb2",
        "DscServicePath": "\\\\mypullserver1b\\c$\\Program Files\\WindowsPowerShell\\DscService"
    },

    "ResourceServer": {
        "ServerURL": "http://mypullserver1:8080/PSDSCPullServer.svc",
        "RegistrationKey": "7f466f8e-027e-44c2-9a7b-897c08b355f1",
        "ModulePath": "\\\\mypullserver1\\c$\\Program Files\\WindowsPowerShell\\DscService\\Modules"
    },

    "ReportServer": {
        "Name": "mypullserver1",
        "ServerURL": "http://mypullserver1:8080/PSDSCPullServer.svc",
        "RegistrationKey": "7f466f8e-027e-44c2-9a7b-897c08b355f1"
    }   
}
```

## Using the test configuration file
Pester tests use the file DSCLinuxTestConfig.json for configuration settings.  To override this 
file, set the environment variable ```DSC_LINUX_TEST_CONFIG``` to use a custom configuration.
This is useful for running on private machines.


##Building the Desired State Configuration (DSC) Local Configuration Manager and Linux Resource Providers

###Prerequisites
1. At least one modern Linux system with:
  1. root login capability
  3. Open Management Infrastructure (OMI) 1.0.8+ [Download](https://collaboration.opengroup.org/omi/documents/30532/omi-1.0.8.tar.gz)
    1. pam-devel
    2. openssl-devel
    3. python-devel (version 2.5 or higher)


###Building and installing the Local Configuration Manager and Linux Resource Providers

1. Clone [WPSDSCLinux](https://github.com/MSFTOSSMgmt/WPSDSCLinux.git) to a build directory
2. Download and extract OMI 1.0.8 into a directory named "omi-1.0.8" in a directory parallel to the LCM and Providers directory.  The directory tree should look something like:
```
   .dsc/configure
   .dsc/LCM
   .dsc/license.txt
   .dsc/omi-1.0.8
   .dsc/omi-1.0.8/agent
   .dsc/omi-1.0.8/base
   .dsc/Providers
   ...
```
3. Building
  1. Configuring OMI and building
    1. Configure OMI with desired options (refer to OMI documentation for this step).
      1. The default configuration installs to /opt/omi-1.0.8
      2. To use the default configuration, run: **(cd omi-1.0.8 && ./configure)**
    2. Run: **make**
  2. Installing OMI:
    1. Run: **(cd omi-1.0.8 && sudo ./output/install)**
  3. Registering the LCM + nxProviders with OMI:
    1. Run: **sudo make reg**

4. Running OMI
  1. On the Linux system, run omiserver with environment variable OMI_HOME set to OMI's installed directory
    1. Run as root: **OMI_HOME=*PATH_TO_INSTALLED_OMI_DIR* *PATH_TO_INSTALLED_OMI_DIR*/bin/omiserver**
    2. The default installation for OMI 1.0.8 is **/opt/omi-1.0.8**.  Thus, for default installations:
            OMI_HOME=/opt/omi-1.0.8 /opt/omi-1.0.8/bin/omiserver
  2. Note: In order to run following reboots, it is recommended to configure OMI as a System-V, Upstart, or SystemD daemon 


##To author DSC MOF configuration for Linux on a Windows computer:

###Prerequisites

1. A Windows computer with:
  1. Adminstrative privileges
  2. Windows PowerShell (>=4.0)


###Install the Linux Resource Provider MOF module:
  1. Extract the nx.zip file into %ProgramFiles%\WindowsPowerShell\Modules\ such that the directory tree looks like:
      ```
      %ProgramFiles%\WindowsPowerShell\Modules\nx\nx.psd1
      %ProgramFiles%\WindowsPowerShell\Modules\nx\Readme.txt
      %ProgramFiles%\WindowsPowerShell\Modules\nx\DSCResources
      %ProgramFiles%\WindowsPowerShell\Modules\nx\DSCResources\MSFT_nxFileResource
      ...
      ```
  2. In order to compile a Configuration MOF that uses the DSC for Linux resources, use **"Import-DscResource -Module nx"** inside a DSC Configuration block.
  3. Example DSC Configuration blocks provided in the "Example DSCs" directory.
  
###Managing a Linux system with DSC
  1. You need a compiled configuration MOF to apply a new configuration to a system.  Please refer to part 1 of this section, as well as the DSC for Windows documentation, for instructions on how to generate a configuration MOF.
  2. Once you have a MOF, you can apply it by running:
        **Start-DscConfiguration -CimSession:$myCimSession -Path "C:\path_to_compiled_mof_directory\" -Wait -Verbose**
  3. You can get the current configuration of the system by running:
        **Get-DscConfiguration -CimSession:$myCimSession**
  4. You can test the current configuration of the system by running:
        **Test-DscConfiguration -CimSession:$myCimSession**
  5. For more information on creating a CimSession for use with the -CimSession parameter, see: (http://technet.microsoft.com/en-us/library/jj590760.aspx)

####Notes
  1. More detail on errors can be found in the stderr/stdout of omiserver on the Linux system. For diagnostic purposes, omiserver can be run in a tty so that stderr/stdout are visible.
  2. The DSC Local Configuration Manager log can be found at $OMI_HOME/var/log/dsc.log
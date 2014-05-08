Prerequisites
----------------------------------------------------------------------
1. At least one modern Linux system with:
    a. root login capability
    b. These build tools:
        i.  GNU Make
        ii. g++
   
2. A Windows system with:
    a. Adminstrative privileges
    b. Powershell (>=4.0)


On each Linux system to be managed by DSC:
----------------------------------------------------------------------
1. Extract DSC_for_Linux.tar into a directory that you will build it from.
2. Download and unzip OMI 1.0.8 into a directory named "omi-1.0.8" in a directory parallel to the LCM and Providers directory.  The directory tree should look something like:

   ./configure
   ./LCM
   ./license.txt
   ./omi-1.0.8
   ./omi-1.0.8/agent
   ./omi-1.0.8/base
   ...

3. Building
   A. Configuring OMI and building
      i.  Configure OMI with desired options (refer to OMI documentation for this step).
      	  a. The default configuration installs to /opt/omi-1.0.8
	  b. To use the default configuration, run: (cd omi-1.0.8 && ./configure)
      ii. Run: make
   B. Installing OMI:
      i.  Run: (cd omi-1.0.8 && sudo ./output/install)
   C. Registering the LCM + nxProviders with OMI:
      i.  Run: sudo make reg

4. Running OMI
   A. On the Linux system, run omiserver with environment variable OMI_HOME set to OMI's installed directory
      i.  Run as root: OMI_HOME=*PATH_TO_INSTALLED_OMI_DIR* *PATH_TO_INSTALLED_OMI_DIR*/bin/omiserver
      ii. The default installation for OMI 1.0.8 is "/opt/omi-1.0.8".  Thus, for default installations, part 4Ai above becomes:
      	      OMI_HOME=/opt/omi-1.0.8 /opt/omi-1.0.8/bin/omiserver



On a Windows system that will manage Linux systems:
----------------------------------------------------------------------
1. Compiling a DSC package to MOF using our providers:
   A. Extract the nx.zip file into %SystemRoot%\system32\WindowsPowerShell\v1.0\Modules\ such that the directory tree looks like:
      %SystemRoot%\system32\WindowsPowerShell\v1.0\Modules\nx\nx.psd1
      %SystemRoot%\system32\WindowsPowerShell\v1.0\Modules\nx\Readme.txt
      %SystemRoot%\system32\WindowsPowerShell\v1.0\Modules\nx\DSCResources
      %SystemRoot%\system32\WindowsPowerShell\v1.0\Modules\nx\DSCResources\MSFT_nxFileResource
      ...

   B. In order to compile a Configuration MOF that uses the DSC for Linux resources, use "Import-DscResource -Module nx" inside a DSC Configuration block.
   C. Example DSC Configuration blocks provided in the "Example DSCs" directory.

2. Configuring Powershell environment
   A. Make sure PowerShell can run scripts unrestricted:
      	  Set-ExecutionPolicy unrestricted
   B. Make sure winrm can trust any host (this can be changed to trust only specific hosts if desired):
      	  winrm set winrm/config/client '@{TrustedHosts="*"}'

3. Connecting to a Linux system:
   A. Encrypt your password for the root user:
      	  $securePass=ConvertTo-SecureString -string "MyRootPassword" -AsPlainText –Force
   B. Set the root credentials: 
      	  $cred= New-Object System.Management.Automation.PSCredential "root", $SecurePass
   C. Set the CimSession options (these can be configured differently if certificates have been installed to OMI): 
      	  $opt = New-CimSessionOption -UseSsl:$true -SkipCACheck:$true -SkipCNCheck:$true -SkipRevocationCheck:$true
   D. Connect to the Linux system: 
      	  $myCimSession = New-CimSession -Credential:$cred -ComputerName:LinuxSystemHostname -Port:5986 -Authentication:basic -SessionOption:$opt

4. Managing a Linux system with DSC
   A. You need a compiled configuration MOF to apply a new configuration to a system.  Please refer to part 1 of this section, as well as the DSC for Windows documentation, for instructions on how to generate a configuration MOF.
   B. Once you have a MOF, you can apply it by running:
          Start-DscConfiguration -CimSession:$myCimSession -Path:"C:\path_to_compiled_mof_directory\" -Wait -Verbose
   C. You can get the current configuration of the system by running:
      	  Get-DscConfiguration -CimSession:$myCimSession
   D. You can test the current configuration of the system by running:
      	  Test-DscConfiguration -CimSession:$myCimSession

5. Notes
   A. More detail on errors can be found in the stderr/stdout of omiserver on the Linux system.

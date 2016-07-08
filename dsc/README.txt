/**
PowerShell Desired State Configuration for Linux
Copyright (c) Microsoft Corporation ver. 1.1.0
All rights reserved. 

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

PowerShell Desired State Configuration for Linux - v1.1.0

Building the Desired State Configuration (DSC) Local Configuration Manager and Linux Resource Providers

Prerequisites
----------------------------------------------------------------------
1. At least one modern Linux system with:
    a. root login capability
    b. These build tools:
        i.  GNU Make
        ii. g++
		iii. Python version 2.5 or later, the package python-devel
	c. Open Management Infrastructure (OMI) 1.0.8. http://theopengroup.org/software/omi
		i. pam-devel
		ii. openssl-devel


Building and installing the Local Configuration Manager and Linux Resource Providers
----------------------------------------------------------------------
1. Extract PSDSC.tar into a directory that you will build it from.
2. Download and extract OMI 1.0.8 into a directory named "omi-1.0.8" in a directory parallel to the LCM and Providers directory.  The directory tree should look something like:

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
   B. Note: In order to run following reboots, it is recommended to configure OMI as a System-V, Upstart, or SystemD daemon 



To author DSC MOF configuration for Linux on a Windows computer:
----------------------------------------------------------------------

Prerequisites
----------------------------------------------------------------------
1. A Windows computer with:
    A. Adminstrative privileges
    B. Windows PowerShell (>=4.0)


1. Install the Linux Resource Provider MOF module:
   A. The "nx" moduel can be installed from the PowerShell Gallery with:
	install-module nx
   B. In order to compile a Configuration MOF that uses the DSC for Linux resources, use "Import-DscResource -Module nx" inside a DSC Configuration block.
  
2. Managing a Linux system with DSC
   A. You need a compiled configuration MOF to apply a new configuration to a system.  Please refer to part 1 of this section, as well as the DSC for Windows documentation, for instructions on how to generate a configuration MOF.
   B. Once you have a MOF, you can apply it by running:
        Start-DscConfiguration -CimSession:$myCimSession -Path:"C:\path_to_compiled_mof_directory\" -Wait -Verbose
   C. You can get the current configuration of the system by running:
        Get-DscConfiguration -CimSession:$myCimSession
   D. You can test the current configuration of the system by running:
        Test-DscConfiguration -CimSession:$myCimSession
   E. For more information on creating a CimSession for use with the -CimSession parameter, see: http://technet.microsoft.com/en-us/library/jj590760.aspx

3. Notes
  A. The DSC Local Configuration Manager log can be found at $OMI_HOME/var/log/dsc.log


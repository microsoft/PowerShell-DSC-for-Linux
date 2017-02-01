#
# This is a Pester test suite for validating DSC on Linux 
#
# Copyright (c) Microsoft Corporation, 2017
#


Import-Module ".\Dsclinux.Tests.Helper.psm1" -force -DisableNameChecking

Describe "DSC Linux Sanity Tests" -Tags @('Feature') {

    BeforeAll {               

        #Install Modules needed for compliation on Windows machine 
        Install-Module nx, nxComputerManagement, nxNetworking

        # Create a Cim session to Client Linux machine on which that we are testing DSC Functionality 
        $linuxClient = ImportLinuxTestConfigurtaion  -testConfigFile ".\DSCLinuxTestConfig.json"
        $script:linuxClientName  = $linuxClient.LinuxClient.Name
        $rootUser = $linuxClient.LinuxClient.UserName
        $rootPassword = $linuxClient.LinuxClient.Password
        # Create a Cim session to Client Linux machine on which that we are testing DSC Functionality 
        $linuxClient = ImportLinuxTestConfigurtaion         
        $script:linuxClientName  = $linuxClient.Name
        $rootUser = $linuxClient.UserName
        $rootPassword = $linuxClient.Password

        $rootUserPassword = ConvertTo-SecureString -String $rootPassword -AsPlainText -Force
        $rootCredentials = New-Object -TypeName "System.Management.Automation.PSCredential" -ArgumentList $rootUser, $rootUserPassword
        $script:session  = CreateCimSession -credential $rootCredentials  -server $linuxClientName         
    
    }

    AfterAll {
   
    }
    
    BeforeEach {
      
    }

    AfterEach {
      
    }
	
	It "Verify we can Set and get Meta Configuration" {
            
           & "$PWD\Configurations\MetaConfigPush.ps1" -targetClient $script:linuxClientName 
           Set-DscLocalConfigurationManager -Path "$PWD\MetaConfigPush\"  -Verbose -CimSession $script:session
           
           $metaConfig = Get-DscLocalConfigurationManager -Verbose -CimSession $script:session
           $metaConfig.RefreshMode | Should Be "Push" 
           $metaConfig.ConfigurationModeFrequencyMins | Should Be "60"           
	}

	
	It "Verify we can do Start DSC Configuration And Get Dsc Configuration" {
           
           & "$PWD\Configurations\FileProviderTestConfig1.ps1" -targetClient $script:linuxClientName -Ensure "Present"
           #Verify Get Dsc 
           Start-DscConfiguration -Path "$PWD\FileProviderTestConfig1\"  -Verbose -CimSession $script:session -wait 
           
           $dscConfig = Get-DscConfiguration -Verbose -CimSession $script:session
           $dscConfig.Ensure | Should Be "Present" 
           $dscConfig.DestinationPath | Should Be "/tmp/dsctest1" 
           $dscConfig.Contents | Should Be "Linux DSC Test1!" 

           #Verify Test Dsc 
           $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
           $testDscConfig.InDesiredState | Should Be "True" 

           # Use Dsc to cleanup by deleting the file created above            
            & "$PWD\Configurations\FileProviderTestConfig1.ps1" -targetClient $script:linuxClientName -Ensure "Absent"
           Start-DscConfiguration -Path "$env:temp\FileProviderTestConfig1" -Verbose -CimSession $script:session -wait            
           
           # Use Dsc to cleanup by deleting the file created above            
            & "$PWD\Configurations\FileProviderTestConfig1.ps1" -targetClient $script:linuxClientName -Ensure "Absent"
           Start-DscConfiguration -Path "$PWD\FileProviderTestConfig1\"  -Verbose -CimSession $script:session -wait            
           $dscConfig = Get-DscConfiguration -Verbose -CimSession $script:session
           $dscConfig.Ensure | Should Be "Absent" 
           $dscConfig.DestinationPath | Should Be "/tmp/dsctest1"            
	}
	      

    It "Verify we can do Publish and Start DSC -Useexisting " {
            
            & "$PWD\Configurations\FileProviderTestConfig1.ps1" -targetClient $script:linuxClientName -Ensure "Present"
           Publish-DscConfiguration -Path "$env:temp\FileProviderTestConfig1" -Verbose -CimSession $script:session                 
           Publish-DscConfiguration -Path "$PWD\FileProviderTestConfig1\"  -Verbose -CimSession $script:session                 
           Start-DscConfiguration -UseExisting  -Verbose -CimSession $script:session -wait   
           $dscConfig = Get-DscConfiguration -Verbose -CimSession $script:session
           $dscConfig.Ensure | Should Be "Present" 
           $dscConfig.DestinationPath | Should Be "/tmp/dsctest1"            
	}	

    It "Verify we can do Update Dsc Configuration " {
       
           & "$PWD\Configurations\FileProviderTestConfig1.ps1" -targetClient $script:linuxClientName -Ensure "Absent"
           Publish-DscConfiguration -Path "$env:temp\FileProviderTestConfig1" -Verbose -CimSession $script:session                 
           Publish-DscConfiguration -Path "$PWD\FileProviderTestConfig1\"  -Verbose -CimSession $script:session                 
           Update-DscConfiguration -wait -Verbose -CimSession $script:session 
           $dscConfig = Get-DscConfiguration -Verbose -CimSession $script:session
           $dscConfig.Ensure | Should Be "Absent" 
           $dscConfig.DestinationPath | Should Be "/tmp/dsctest1"    
	}	

}

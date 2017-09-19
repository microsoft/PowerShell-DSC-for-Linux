<#
    .SYNOPSIS
        Test suite for validating basic DSC functionality on Linux. 
        Copyright (c) Microsoft Corporation, 2017
#>

$ErrorActionPreference = 'Stop'

Describe 'DSC Linux Sanity Tests' -Tags @('Feature') {
    BeforeAll {
        $dscLinuxTestHelperPath = Join-Path -Path $PSScriptRoot -ChildPath 'Dsclinux.Tests.Helper.psm1'
        Import-Module -Name $dscLinuxTestHelperPath -DisableNameChecking -Force

        # Install Modules needed for compliation on Windows machine 
        $modulesNeeded = @('nx')
        $modulesToInstall = @()

        foreach ($moduleName in $modulesNeeded)
        {
            $moduleNeeded = Get-Module -Name $moduleName -ListAvailable -ErrorAction 'SilentlyContinue'
            $moduleInstalled = $null -ne $moduleNeeded

            if (-not $moduleInstalled)
            {
                $modulesToInstall += $moduleName
            }
        }

        if ($modulesToInstall.Count -gt 0)
        {
            Install-Module -Name $modulesToInstall
        }

        # Create a Cim session to Client Linux machine on which that we are testing DSC Functionality 
        $connectionConfiguration = Get-TestConfiguration
        
        $script:linuxClientName = $connectionConfiguration.LinuxClient.Name
        $rootUser = $connectionConfiguration.LinuxClient.UserName
        $rootPassword = $connectionConfiguration.LinuxClient.Password

        $secureRootPassword = ConvertTo-SecureString -String $rootPassword -AsPlainText -Force
        $rootCredential = New-Object -TypeName 'System.Management.Automation.PSCredential' -ArgumentList @($rootUser, $secureRootPassword)
        $script:session = CreateCimSession -Credential $rootCredential -Server $linuxClientName

        # Set up file path script variables
        $configurationFolderPath = Join-Path -Path $PSScriptRoot -ChildPath 'Configurations'
        $script:testMetaconfigurationFilePath = Join-Path -Path $configurationFolderPath -ChildPath 'MetaConfigPush.ps1'
        $script:testConfigurationFilePath = Join-Path -Path $configurationFolderPath -ChildPath 'FileProviderTestConfig1.ps1'
    }

    AfterAll {
        $null = Remove-CimSession -CimSession $script:session
    }

	It 'Verify we can set and get the metaconfiguration' {        
        $metaconfigurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'MetaConfigPush'
        $lcmSettings = @{
            RefreshMode = 'PUSH'
            ConfigurationModeFrequencyMins = 60
        }

        $null = & $script:testMetaconfigurationFilePath -TargetClient $script:linuxClientName -Output $metaconfigurationOutputPath @lcmSettings
        { Set-DscLocalConfigurationManager -Path $metaconfigurationOutputPath -CimSession $script:session } | Should Not Throw
        
        $metaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
        $metaConfig.RefreshMode.ToUpper() | Should Be $lcmSettings.RefreshMode.ToUpper()
        $metaConfig.ConfigurationModeFrequencyMins | Should Be $lcmSettings.ConfigurationModeFrequencyMins
	}
	
	It 'Verify we can start, test, and retrieve a DSC configuration' {
        $configurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'FileProviderTestConfig1'
        $nxFileParameters = @{
            Ensure = 'Present'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile1'
            Contents = 'DSC test contents 1'
        }

        $null = & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters
        { Start-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Wait -Force } | Should Not Throw
        
        # Verify Get-DscConfiguration
        $dscConfig = Get-DscConfiguration -CimSession $script:session
        $dscConfig.Ensure | Should Be $nxFileParameters.Ensure
        $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
        $dscConfig.Contents | Should Be $nxFileParameters.Contents

        # Verify Test-DscConfiguration
        $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
        $testDscConfig.InDesiredState | Should Be $true

        # Use DSC to cleanup by deleting the file created above
        $nxFileParameters.Ensure = 'Absent'

        $null = & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters
        { Start-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Wait -Force } | Should Not Throw
                   
        $dscConfig = Get-DscConfiguration -CimSession $script:session
        $dscConfig.Ensure | Should Be $nxFileParameters.Ensure
        $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
	}
      
    It 'Verify we can publish a DSC configuration and start an existing DSC configuration' {
        $configurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'FileProviderTestConfig1'
        $nxFileParameters = @{
            Ensure = 'Present'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile1'
            Contents = 'DSC test contents 1'
        }

        $null = & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters

        { Publish-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Force } | Should Not Throw
        { Start-DscConfiguration -UseExisting -CimSession $script:session -Wait -Force } | Should Not Throw

        $dscConfig = Get-DscConfiguration -CimSession $script:session
        $dscConfig.Ensure | Should Be $nxFileParameters.Ensure
        $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
	}	

    It 'Verify we can update a DSC configuration' {
        $configurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'FileProviderTestConfig1'
        $nxFileParameters = @{
            Ensure = 'Present'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile1'
            Contents = 'DSC test contents 1'
        }

        $null = & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters
        { Update-DscConfiguration -Wait -CimSession $script:session } | Should Not Throw

        $dscConfig = Get-DscConfiguration -CimSession $script:session
        $dscConfig.Ensure | Should Be $nxFileParameters.Ensure
        $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
	}
}

<#
    .SYNOPSIS
        Test suite for MonitorOnly Configuration Mode 
        Copyright (c) Microsoft Corporation, 2017
#>

Describe 'MonitorOnly Configuration Mode' -Tags @('BVT') {
    BeforeAll {
        $dscLinuxTestHelperPath = Join-Path -Path $PSScriptRoot -ChildPath 'Dsclinux.Tests.Helper.psm1'
        Import-Module -Name $dscLinuxTestHelperPath -DisableNameChecking

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
        $testMetaconfigurationFilePath = Join-Path -Path $configurationFolderPath -ChildPath 'MetaConfigPush.ps1'
        $testConfigurationFilePath = Join-Path -Path $configurationFolderPath -ChildPath 'FileProviderTestConfig1.ps1'

        # Generate metaconfiguration with MonitorOnly mode
        $script:lcmSettingsMonitorOnly = @{
            RefreshMode = 'PUSH'
            ConfigurationMode = 'MonitorOnly'
        }
        $script:metaconfigurationMonitorOnlyOutput = Join-Path -Path $TestDrive -ChildPath 'MetaConfigPushMonitorOnly'
        $null = & $testMetaconfigurationFilePath -TargetClient $script:linuxClientName -Output $script:metaconfigurationMonitorOnlyOutput @lcmSettingsMonitorOnly

        # Generate configuartion with file absent
        $script:fileAbsentParameters = @{
            Ensure = 'Absent'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile'
            Contents = 'DSC test contents'
        }
        $script:configurationFileAbsentOutput = Join-Path -Path $TestDrive -ChildPath 'TestFileAbsentConfig'
        $null = & $testConfigurationFilePath -TargetClient $script:linuxClientName -Output $script:configurationFileAbsentOutput @fileAbsentParameters

        # Generate configuartion with file present
        $script:filePresentParameters = @{
            Ensure = 'Present'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile'
            Contents = 'DSC test contents'
        }
        $script:configurationFilePresentOutput = Join-Path -Path $TestDrive -ChildPath 'TestFilePresentConfig'
        $null = & $testConfigurationFilePath -TargetClient $script:linuxClientName -Output $script:configurationFilePresentOutput @filePresentParameters
    }

    AfterAll {
        $null = Remove-CimSession -CimSession $script:session
    }

    $applyConfigurationModes = @('ApplyOnly', 'ApplyAndMonitor', 'ApplyAndAutocorrect')

    foreach ($configurationMode in $applyConfigurationModes)
    {
        # Generate metaconfiguration with specified apply configuration mode
        $script:lcmSettingsApply = @{
            RefreshMode = 'PUSH'
            ConfigurationMode = $configurationMode
        }
        $script:metaconfigurationApplyOutput = Join-Path -Path $TestDrive -ChildPath ('MetaConfigPush' + $configurationMode)
        $null = & $testMetaconfigurationFilePath -TargetClient $script:linuxClientName -Output $script:metaconfigurationApplyOutput @lcmSettingsApply

        Context "$configurationMode Mode - Ensure set to Absent and unsure if file exists or not" {
            # Send metaconfig
            It "Should set LCM ConfigurationMode to $configurationMode without throwing" {
                { Set-DscLocalConfigurationManager -Path $script:metaconfigurationApplyOutput -CimSession $script:session } | Should Not Throw
            }

            # Validate metaconfig
            It "Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of $configurationMode" {
                $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
                $currentMetaConfig | Should Not Be $null
                $currentMetaConfig.RefreshMode | Should Be $script:lcmSettingsApply.RefreshMode
                $currentMetaConfig.ConfigurationMode | Should Be $script:lcmSettingsApply.ConfigurationMode
            }

            # Push configuration
            It 'Should push a configuration without throwing' {
                { Start-DscConfiguration -Path $script:configurationFileAbsentOutput -CimSession $script:session -Wait -Force } | Should Not Throw
            }

            # Verify Get-DscConfiguration
            It 'Should retrieve DSC configuration with Ensure property as Absent' {
                $dscConfig = Get-DscConfiguration -CimSession $script:session
                $dscConfig | Should Not Be $null
                $dscConfig.Ensure | Should Be 'Absent'
                $dscConfig.DestinationPath | Should Be $script:fileAbsentParameters.DestinationPath
                $dscConfig.Contents | Should Be $script:fileAbsentParameters.Contents
            }

            # Verify Test-DscConfiguration
            It 'Should test DSC configuration and return InDesiredState as true' {
                $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
                $testDscConfig.InDesiredState | Should Be $true
            }
        }

        Context 'MonitorOnly Mode - Ensure set to Absent and file does not exist' {
            # Send metaconfig
            It 'Should set LCM ConfigurationMode to MonitorOnly without throwing' {
                { Set-DscLocalConfigurationManager -Path $script:metaconfigurationMonitorOnlyOutput -CimSession $script:session } | Should Not Throw
            }

            # Validate metaconfig
            It 'Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of MonitorOnly' {
                $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
                $currentMetaConfig | Should Not Be $null
                $currentMetaConfig.RefreshMode | Should Be $script:lcmSettingsMonitorOnly.RefreshMode
                $currentMetaConfig.ConfigurationMode | Should Be $script:lcmSettingsMonitorOnly.ConfigurationMode
            }

            It 'Should push a configuration without throwing' {
                { Start-DscConfiguration -Path $script:configurationFileAbsentOutput -CimSession $script:session -Wait -Force } | Should Not Throw
            }
            
            # Verify Get-DscConfiguration
            It 'Should retrieve DSC configuration with Ensure property as Absent' {
                $dscConfig = Get-DscConfiguration -CimSession $script:session
                $dscConfig | Should Not Be $null
                $dscConfig.Ensure | Should Be 'Absent'
                $dscConfig.DestinationPath | Should Be $script:fileAbsentParameters.DestinationPath
                $dscConfig.Contents | Should Be $script:fileAbsentParameters.Contents
            }

            # Verify Test-DscConfiguration
            It 'Should test DSC configuration and return InDesiredState as true' {
                $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
                $testDscConfig.InDesiredState | Should Be $true
            }
        }

        Context 'MonitorOnly Mode - Ensure set to Present and file does not exist' {
            It 'Should push a configuration without throwing' {
                { Start-DscConfiguration -Path $script:configurationFilePresentOutput -CimSession $script:session -Wait -Force } | Should Not Throw
            }
                    
            # Verify Get-DscConfiguration
            It 'Should retrieve DSC configuration with Ensure property as Absent' {
                $dscConfig = Get-DscConfiguration -CimSession $script:session
                $dscConfig | Should Not Be $null
                $dscConfig.Ensure | Should Be 'Absent'
                $dscConfig.DestinationPath | Should Be $script:filePresentParameters.DestinationPath
                $dscConfig.Contents | Should Be $script:filePresentParameters.Contents
            }

            # Verify Test-DscConfiguration
            It 'Should test DSC configuration and return InDesiredState as false' {
                $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
                $testDscConfig.InDesiredState | Should Be $false
            }
        }

        Context "$configurationMode Mode - Ensure set to Present and file does not exist" {
            # Send metaconfig
            It "Should set LCM ConfigurationMode to $configurationMode without throwing" {
                { Set-DscLocalConfigurationManager -Path $script:metaconfigurationApplyOutput -CimSession $script:session } | Should Not Throw
            }

            # Validate metaconfig
            It "Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of $configurationMode" {
                $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
                $currentMetaConfig | Should Not Be $null
                $currentMetaConfig.RefreshMode | Should Be $script:lcmSettingsApply.RefreshMode
                $currentMetaConfig.ConfigurationMode | Should Be $script:lcmSettingsApply.ConfigurationMode
            }

            # Send command to start existing config
            It 'Should start existing configuration without throwing' {
                { Start-DscConfiguration -UseExisting -CimSession $script:session -Wait -Force } | Should Not Throw
            }

            # Verify Get-DscConfiguration
            It 'Should retrieve DSC configuration with Ensure property as Present' {
                $dscConfig = Get-DscConfiguration -CimSession $script:session
                $dscConfig | Should Not Be $null
                $dscConfig.Ensure | Should Be 'Present'
                $dscConfig.DestinationPath | Should Be $script:filePresentParameters.DestinationPath
                $dscConfig.Contents | Should Be $script:filePresentParameters.Contents
            }

            # Verify Test-DscConfiguration
            It 'Should test DSC configuration and return InDesiredState as true' {
                $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
                $testDscConfig.InDesiredState | Should Be $true
            }
        }

        Context 'MonitorOnly Mode - Ensure set to Present and file exists' {
            # Send metaconfig with MonitorOnly
            It 'Should set LCM ConfigurationMode to MonitorOnly without throwing' {
                { Set-DscLocalConfigurationManager -Path $script:metaconfigurationMonitorOnlyOutput -CimSession $script:session } | Should Not Throw
            }

            # Validate metaconfig
            It 'Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of MonitorOnly' {
                $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
                $currentMetaConfig | Should Not Be $null
                $currentMetaConfig.RefreshMode | Should Be $script:lcmSettingsMonitorOnly.RefreshMode
                $currentMetaConfig.ConfigurationMode | Should Be $script:lcmSettingsMonitorOnly.ConfigurationMode
            }

            # Verify Get-DscConfiguration
            It 'Should retrieve DSC configuration with Ensure property as Present' {
                $dscConfig = Get-DscConfiguration -CimSession $script:session
                $dscConfig | Should Not Be $null
                $dscConfig.Ensure | Should Be 'Present'
                $dscConfig.DestinationPath | Should Be $script:filePresentParameters.DestinationPath
                $dscConfig.Contents | Should Be $script:filePresentParameters.Contents
            }

            # Verify Test-DscConfiguration
            It 'Should test DSC configuration and return InDesiredState as true' {
                $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
                $testDscConfig.InDesiredState | Should Be $true
            }
        }

        Context 'MonitorOnly Mode - Ensure set to Absent and file exists' {
            It 'Should push a configuration without throwing' {
                { Start-DscConfiguration -Path $script:configurationFileAbsentOutput -CimSession $script:session -Wait -Force } | Should Not Throw
            }
                    
            # Verify Get-DscConfiguration
            It 'Should retrieve DSC configuration with Ensure property as Present' {
                $dscConfig = Get-DscConfiguration -CimSession $script:session
                $dscConfig | Should Not Be $null
                $dscConfig.Ensure | Should Be 'Present'
                $dscConfig.DestinationPath | Should Be $script:fileAbsentParameters.DestinationPath
                $dscConfig.Contents | Should Be $script:fileAbsentParameters.Contents
            }

            # Verify Test-DscConfiguration
            It 'Should test DSC configuration and return InDesiredState as false' {
                $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
                $testDscConfig.InDesiredState | Should Be $false
            }
        }

        Context "$configurationMode Mode - Ensure set to Absent and file exists" {
            # Send metaconfig
            It "Should set LCM ConfigurationMode to $configurationMode without throwing" {
                { Set-DscLocalConfigurationManager -Path $script:metaconfigurationApplyOutput -CimSession $script:session } | Should Not Throw
            }

            # Validate metaconfig
            It "Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of $configurationMode" {
                $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
                $currentMetaConfig | Should Not Be $null
                $currentMetaConfig.RefreshMode | Should Be $script:lcmSettingsApply.RefreshMode
                $currentMetaConfig.ConfigurationMode | Should Be $script:lcmSettingsApply.ConfigurationMode
            }

            It 'Should push a configuration without throwing' {
                { Start-DscConfiguration -Path $script:configurationFileAbsentOutput -CimSession $script:session -Wait -Force } | Should Not Throw
            }

            # Verify Get-DscConfiguration
            It 'Should retrieve DSC configuration with Ensure property as Absent' {
                $dscConfig = Get-DscConfiguration -CimSession $script:session
                $dscConfig | Should Not Be $null
                $dscConfig.Ensure | Should Be 'Absent'
                $dscConfig.DestinationPath | Should Be $script:fileAbsentParameters.DestinationPath
                $dscConfig.Contents | Should Be $script:fileAbsentParameters.Contents
            }

            # Verify Test-DscConfiguration
            It 'Should test DSC configuration and return InDesiredState as true' {
                $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
                $testDscConfig.InDesiredState | Should Be $true
            }
        }
    }
}

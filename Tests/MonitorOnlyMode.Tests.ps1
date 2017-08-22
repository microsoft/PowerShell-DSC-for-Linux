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
        $script:testMetaconfigurationFilePath = Join-Path -Path $configurationFolderPath -ChildPath 'MetaConfigPush.ps1'
        $script:testConfigurationFilePath = Join-Path -Path $configurationFolderPath -ChildPath 'FileProviderTestConfig1.ps1'
    }

    AfterAll {
        $null = Remove-CimSession -CimSession $script:session
    }

    Context 'Set up using DSC' {
        # Generate metaconfig mof with ApplyAndMonitor mode
        $metaconfigurationApplyOutputPath = Join-Path -Path $TestDrive -ChildPath 'MetaConfigPushApply'
        $lcmSettings = @{
            RefreshMode = 'PUSH'
            ConfigurationMode = 'ApplyAndMonitor'
        }

        & $script:testMetaconfigurationFilePath -TargetClient $script:linuxClientName -Output $metaconfigurationApplyOutputPath @lcmSettings

        # Send metaconfig
        It 'Should set LCM ConfigurationMode to ApplyAndMonitor without throwing' {
            { Set-DscLocalConfigurationManager -Path $metaconfigurationApplyOutputPath -CimSession $script:session } | Should Not Throw
        }

        # Validate metaconfig
        It 'Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of ApplyAndMonitor' {
            $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
            $currentMetaConfig | Should Not Be $null
            $currentMetaConfig.RefreshMode.ToLower() | Should Be $lcmSettings.RefreshMode.ToLower()
            $currentMetaConfig.ConfigurationMode.ToLower() | Should Be $lcmSettings.ConfigurationMode.ToLower()
        }

        # Push configuration
        $configurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'FileProviderTestConfig2'
        $nxFileParameters = @{
            Ensure = 'Absent'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile'
            Contents = 'DSC test contents'
        }

        & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters

        It 'Should push a configuration without throwing' {
            { Start-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Wait -Force } | Should Not Throw
        }

        # Verify Get-DscConfiguration
        It 'Should retrieve DSC configuration with Ensure property as Absent' {
            $dscConfig = Get-DscConfiguration -CimSession $script:session
            $dscConfig | Should Not Be $null
            $dscConfig.Ensure | Should Be 'Absent'
            $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
            $dscConfig.Contents | Should Be $nxFileParameters.Contents
        }

        # Verify Test-DscConfiguration
        It 'Should test DSC configuration and return InDesiredState as true' {
            $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
            $testDscConfig.InDesiredState | Should Be $true
        }
    }

    <#
        Summary: Verify in MonitorOnly Mode in Push Refresh we do not apply new configurations 
        Action: Apply metaconfig with Refresh Mode as Push and Configuration Mode as MonitorOnly  
                Start some configuration. Verify it is executed in Test Only Mode  
                Apply metaconfig with Configuration mode as ApplyAndMonitor 
                Run Start-DSC with -UseExisting Verfiy now configuraion is applied  
        Expected Result: Verify configuration application results for each mode 
    #>
    Context 'RefreshMode is PUSH' {
        # Generate metaconfig mof        
        $metaconfigurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'MetaConfigPush'
        $lcmSettings = @{
            RefreshMode = 'PUSH'
            ConfigurationMode = 'MonitorOnly'
        }

        & $script:testMetaconfigurationFilePath -TargetClient $script:linuxClientName -Output $metaconfigurationOutputPath @lcmSettings
	
        # Send metaconfig
        It 'Should set LCM ConfigurationMode to MonitorOnly without throwing' {
            { Set-DscLocalConfigurationManager -Path $metaconfigurationOutputPath -CimSession $script:session } | Should Not Throw
        }

        # Validate metaconfig
        It 'Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of MonitorOnly' {
            $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
            $currentMetaConfig | Should Not Be $null
            $currentMetaConfig.RefreshMode.ToLower() | Should Be $lcmSettings.RefreshMode.ToLower()
            $currentMetaConfig.ConfigurationMode.ToLower() | Should Be $lcmSettings.ConfigurationMode.ToLower()
        }

        # Push configuration
        $configurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'FileProviderTestConfig2'
        $nxFileParameters = @{
            Ensure = 'Absent'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile'
            Contents = 'DSC test contents'
        }

        & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters

        It 'Should push a configuration without throwing' {
            { Start-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Wait -Force } | Should Not Throw
        }
        
        # Verify Get-DscConfiguration
        It 'Should retrieve DSC configuration with Ensure property as Absent' {
            $dscConfig = Get-DscConfiguration -CimSession $script:session
            $dscConfig | Should Not Be $null
            $dscConfig.Ensure | Should Be 'Absent'
            $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
            $dscConfig.Contents | Should Be $nxFileParameters.Contents
        }

        # Verify Test-DscConfiguration
        It 'Should test DSC configuration and return InDesiredState as true' {
            $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
            $testDscConfig.InDesiredState | Should Be $true
        }

        $nxFileParameters.Ensure = 'Present'
        & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters
       
        It 'Should push a configuration without throwing' {
            { Start-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Wait -Force } | Should Not Throw
        }
                   
        # Verify Get-DscConfiguration
        It 'Should retrieve DSC configuration with Ensure property as Absent' {
            $dscConfig = Get-DscConfiguration -CimSession $script:session
            $dscConfig | Should Not Be $null
            $dscConfig.Ensure | Should Be 'Absent'
            $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
            $dscConfig.Contents | Should Be $nxFileParameters.Contents
        }

        # Verify Test-DscConfiguration
        It 'Should test DSC configuration and return InDesiredState as false' {
            $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
            $testDscConfig.InDesiredState | Should Be $false
        }

        # Generate metaconfig mof with ApplyAndMonitor mode
        $metaconfigurationApplyOutputPath = Join-Path -Path $TestDrive -ChildPath 'MetaConfigPushApply'
        $lcmSettings = @{
            RefreshMode = 'PUSH'
            ConfigurationMode = 'ApplyAndMonitor'
        }

        & $script:testMetaconfigurationFilePath -TargetClient $script:linuxClientName -Output $metaconfigurationApplyOutputPath @lcmSettings

        # Send metaconfig
        It 'Should set LCM ConfigurationMode to ApplyAndMonitor without throwing' {
            { Set-DscLocalConfigurationManager -Path $metaconfigurationApplyOutputPath -CimSession $script:session } | Should Not Throw
        }

        # Validate metaconfig
        It 'Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of ApplyAndMonitor' {
            $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
            $currentMetaConfig | Should Not Be $null
            $currentMetaConfig.RefreshMode.ToLower() | Should Be $lcmSettings.RefreshMode.ToLower()
            $currentMetaConfig.ConfigurationMode.ToLower() | Should Be $lcmSettings.ConfigurationMode.ToLower()
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
            $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
            $dscConfig.Contents | Should Be $nxFileParameters.Contents
        }

        # Verify Test-DscConfiguration
        It 'Should test DSC configuration and return InDesiredState as true' {
            $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
            $testDscConfig.InDesiredState | Should Be $true
        }

        # Send metaconfig with MonitorOnly
        $lcmSettings.ConfigurationMode = 'MonitorOnly'
        It 'Should set LCM ConfigurationMode to MonitorOnly without throwing' {
            { Set-DscLocalConfigurationManager -Path $metaconfigurationOutputPath -CimSession $script:session } | Should Not Throw
        }

        # Validate metaconfig
        It 'Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of MonitorOnly' {
            $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
            $currentMetaConfig | Should Not Be $null
            $currentMetaConfig.RefreshMode.ToLower() | Should Be $lcmSettings.RefreshMode.ToLower()
            $currentMetaConfig.ConfigurationMode.ToLower() | Should Be $lcmSettings.ConfigurationMode.ToLower()
        }

        # Verify Get-DscConfiguration
        It 'Should retrieve DSC configuration with Ensure property as Present' {
            $dscConfig = Get-DscConfiguration -CimSession $script:session
            $dscConfig | Should Not Be $null
            $dscConfig.Ensure | Should Be 'Present'
            $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
            $dscConfig.Contents | Should Be $nxFileParameters.Contents
        }

        # Verify Test-DscConfiguration
        It 'Should test DSC configuration and return InDesiredState as true' {
            $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
            $testDscConfig.InDesiredState | Should Be $true
        }

        $nxFileParameters.Ensure = 'Absent'

        & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters
       
        It 'Should push a configuration without throwing' {
            { Start-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Wait -Force } | Should Not Throw
        }
                   
        # Verify Get-DscConfiguration
        It 'Should retrieve DSC configuration with Ensure property as Present' {
            $dscConfig = Get-DscConfiguration -CimSession $script:session
            $dscConfig | Should Not Be $null
            $dscConfig.Ensure | Should Be 'Present'
            $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
            $dscConfig.Contents | Should Be $nxFileParameters.Contents
        }

        # Verify Test-DscConfiguration
        It 'Should test DSC configuration and return InDesiredState as false' {
            $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
            $testDscConfig.InDesiredState | Should Be $false
        }
    }

    Context 'Clean up using DSC' {
        # Generate metaconfig mof with ApplyAndMonitor mode
        $metaconfigurationApplyOutputPath = Join-Path -Path $TestDrive -ChildPath 'MetaConfigPushApply'
        $lcmSettings = @{
            RefreshMode = 'PUSH'
            ConfigurationMode = 'ApplyAndMonitor'
        }

        & $script:testMetaconfigurationFilePath -TargetClient $script:linuxClientName -Output $metaconfigurationApplyOutputPath @lcmSettings

        # Send metaconfig
        It 'Should set LCM ConfigurationMode to ApplyAndMonitor without throwing' {
            { Set-DscLocalConfigurationManager -Path $metaconfigurationApplyOutputPath -CimSession $script:session } | Should Not Throw
        }

        # Validate metaconfig
        It 'Should retrieve the LCM settings with expected RefreshMode of PUSH and ConfigurationMode of ApplyAndMonitor' {
            $currentMetaConfig = Get-DscLocalConfigurationManager -CimSession $script:session
            $currentMetaConfig | Should Not Be $null
            $currentMetaConfig.RefreshMode.ToLower() | Should Be $lcmSettings.RefreshMode.ToLower()
            $currentMetaConfig.ConfigurationMode.ToLower() | Should Be $lcmSettings.ConfigurationMode.ToLower()
        }

        # Push configuration
        $configurationOutputPath = Join-Path -Path $TestDrive -ChildPath 'FileProviderTestConfig2'
        $nxFileParameters = @{
            Ensure = 'Absent'
            Type = 'File'
            DestinationPath = '/tmp/dsctestfile'
            Contents = 'DSC test contents'
        }

        & $script:testConfigurationFilePath -TargetClient $script:linuxClientName -Output $configurationOutputPath @nxFileParameters

        It 'Should push a configuration without throwing' {
            { Start-DscConfiguration -Path $configurationOutputPath -CimSession $script:session -Wait -Force } | Should Not Throw
        }

        # Verify Get-DscConfiguration
        It 'Should retrieve DSC configuration with Ensure property as Absent' {
            $dscConfig = Get-DscConfiguration -CimSession $script:session
            $dscConfig | Should Not Be $null
            $dscConfig.Ensure | Should Be 'Absent'
            $dscConfig.DestinationPath | Should Be $nxFileParameters.DestinationPath
            $dscConfig.Contents | Should Be $nxFileParameters.Contents
        }

        # Verify Test-DscConfiguration
        It 'Should test DSC configuration and return InDesiredState as true' {
            $testDscConfig = Test-DscConfiguration -CimSession $script:session -Detailed                      
            $testDscConfig.InDesiredState | Should Be $true
        }
    }
}

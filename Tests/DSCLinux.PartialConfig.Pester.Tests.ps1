#
# This is a Pester test suite for validating Pulling Partial Configurations on Linux 
#
# Copyright (c) Microsoft Corporation, 2017
#

Import-Module ".\Dsclinux.Tests.Helper.psm1" -force -DisableNameChecking

Describe 'Partial Configurations on two pull servers from Linux' -Tag @('Feature') `
{
    BeforeAll `
    {
        $script:cfg = Get-TestConfiguration
        $script:ConfigDir = Join-Path $pwd -ChildPath 'Configurations'
        $script:PackageDir = Join-Path $pwd -ChildPath 'Packages'
        $script:Packages = @(
            (Join-Path -Path $script:PackageDir -ChildPath nxNop_1.0.zip),
            (Join-Path -Path $script:PackageDir -ChildPath nxNop_1.0.1.zip),
            (Join-Path -Path $script:PackageDir -ChildPath nxNop_1.0.7.zip)
        )

        $clientPassword = ConvertTo-SecureString -String $cfg.LinuxClient.Password -AsPlainText -Force
        $script:clientCredentials = [System.Management.Automation.PSCredential]::new($cfg.LinuxClient.Username, $clientPassword)

        # Deploy the partial config test files to the  pull servers
        # NOTE: nxNopTest1 goes to PUllServer1 and nxNopTest2 goes to PullServer2
        # This also updates the registrationkeys.txt file on each pull server.
        Update-PullServer -PullServerCfg $cfg.PullServer1 -ConfigurationFiles (Join-Path -Path $script:ConfigDir -ChildPath nxNopTest1.mof)
        Update-PullServer -PullServerCfg $cfg.PullServer2 -ConfigurationFiles (Join-Path -Path $script:ConfigDir -ChildPath nxNopTest2.mof)

        # deploy the three versions of the nxNop resource to the resource server
        Publish-ResourcePackage -ResourcePackages $script:Packages $cfg.ResourceServer.ModulePath
    }

    <#
        This test verifies that a Linux client can pull a partial configuration from 2 pull servers.

        Test steps
        1: Create the compilation script for the Linux client - configures it to pull a partial configuration from from 2 pull servers
        2: Generate the MOF
        3: Edit the resulting MOF to add settings that are not available with the windows schema.
        4: Send the mof to the client (Set-DscLocalConfigurationManager)
        5: Call Get-DscLocalCOnfigurationManager and verify the expected meta
        6: Call Update-DscConfiguration against the Linux machine.
        7: Call Get-DscConfiguration and verify the configuration contents.
    #>
    Context 'Pulling a partial configuration from two different pull servers' `
    {
        BeforeAll `
        {
            [CimSession] $script:cimSession = $null

            [string] $configName = 'Configure2PullServers'

            Write-Verbose -Message "Create the compilation script"
            [string] $script:scriptFile = New-PartialConfigPullScript -ConfigurationName $configName `
                                                    -Destination $script:ConfigDir `
                                                    -TestConfig $script:cfg `
                                                    -PartialConfigName1 'nxNopTest1' `
                                                    -PartialConfigName2 'nxNopTest2' `
                                                    -IncludeResourceServer

            Write-Verbose -Message "Invoke the compilation script"
            
            $mofDir = Join-Path $script:ConfigDir -ChildPath $configName
            Invoke-Expression "$scriptFile -outputPath $mofdir -ErrorAction Stop"

            Write-Verbose -Message "Edit the MOF to add additional settings"

            $mofFile = Join-Path -Path $mofDir -ChildPath ($script:cfg.LinuxClient.Name + '.meta.mof')
            $mofContent = Get-Content -Path $mofFile -Raw
            # Set/Update the MOF settings that cannot be set in the script due to schema differences between Windows and Linux
            $mofContent = Update-MetaConfigurationSetting -Content $mofContent -Name 'RefreshFrequencyMins' -Value '1'
            $mofContent = Update-MetaConfigurationSetting -Content $mofContent -Name 'DisableModuleSignatureValidation' -Value $true
            Set-Content -Path $mofFile -Value $mofContent

            $cimSession = Connect-Dsc -TargetCfg $cfg.LinuxClient

            Set-DscLocalConfigurationManager -path $mofDir -CimSession $cimSession -Verbose
            $dscMetaCfg = Get-DscLocalConfigurationManager -CimSession $cimSession -Verbose
            Update-DscConfiguration -CimSession $cimSession -Wait -Verbose
            $dscCfg = Get-DscConfiguration -CimSession $cimSession -Verbose
        }

        AfterAll `
        {
            if ($cimSession -ne $null)
            {
                $cimSession.Close()
            }
        }

        It 'Verifies LocalConfigurationManager PartialConfigurations' `
        {
            # Partial configurations
            $dscMetaCfg.PartialConfigurations[0].ResourceId | Should Be "[PartialConfiguration]nxNopTest1"
            $dscMetaCfg.PartialConfigurations[1].ResourceId | Should Be "[PartialConfiguration]nxNopTest2"
        }
        
        It 'Verifies the Meta configuration for the PullServer1' `
        {
            $dscMetaCfg.ConfigurationDownloadManagers[0].ResourceId | Should Be "[ConfigurationRepositoryWeb]$($script:cfg.PullServer1.Name)"
            $dscMetaCfg.ConfigurationDownloadManagers[0].ConfigurationNames | Should Be "nxNopTest1"
            $dscMetaCfg.ConfigurationDownloadManagers[0].ServerURL | Should Be $script:cfg.PullServer1.ServerURL
        }

        It 'Verifies the Meta configuration for the PullServer2' `
        {
            $dscMetaCfg.ConfigurationDownloadManagers[1].ResourceId | Should Be "[ConfigurationRepositoryWeb]$($script:cfg.PullServer2.Name)"
            $dscMetaCfg.ConfigurationDownloadManagers[1].ConfigurationNames | Should Be "nxNopTest2"
            $dscMetaCfg.ConfigurationDownloadManagers[1].ServerURL | Should Be $script:cfg.PullServer2.ServerURL
        }

        It 'Verifies the Meta configuration for the ResourceServer' `
        {
            $dscMetaCfg.ResourceModuleManagers[0].ResourceId | Should Be "[ResourceRepositoryWeb]WebResourceManager"
            $dscMetaCfg.ResourceModuleManagers[0].ServerURL | Should Be $script:cfg.ResourceServer.ServerURL
        }

        It 'Verifies the configuration reports two resources' `
        {
            $dscCfg.GetType().FullName | Should Be 'System.Object[]'
            $dscCfg.Count | Should Be 2
        }

        It 'Verifies the configuration reports the first partial configuration' `
        {
            $cfg = $dscCfg[0]
            $cfg.Name | Should Be 'nxNopTest1'
            $cfg.Value | Should Be 'nop test 1.0'
            $cfg.Ensure | Should Be 'present'
            $cfg.CimClassName | Should Be 'MSFT_nxNopResource'
        }

        It 'Verifies the configuration reports the second partial configuration' `
        {
            $cfg = $dscCfg[1]
            $cfg.Name | Should Be 'nxNopTest2'
            $cfg.Value | Should Be 'nop test 2.0'
            $cfg.Ensure | Should Be 'present'
            $cfg.CimClassName | Should Be 'MSFT_nxNopResource'
        }
    }

<#
        This test verifies that a Linux client can pull a partial configuration from 2 pull servers.

        Test steps
        1: Create the compilation script for the Linux client - configures it to pull a partial configuration from from 2 pull servers
        2: Generate the MOF
        3: Edit the resulting MOF to add settings that are not available with the windows schema.
        4: Send the mof to the client (Set-DscLocalConfigurationManager)
        5: Call Update-DscConfiguration against the Linux machine.
        6: Call Get-DscConfiguration and verify the configuration contents.
        7: Update nxNopTest1.mof with a change and deploy it to the first pull server
        8: Wait for the refresh to occur (60 seconds)
        9: Call Get-DscConfiguration and verify the configuration reports the expected changes.
    #>
    Context 'Refreshing a partial configuration on one of two pull servers' `
    {
        BeforeAll `
        {
            [CimSession] $script:cimSession = $null

            [string] $configName = 'Configure2PullServers'

            Write-Verbose -Message "Create the compilation script"
            [string] $script:scriptFile = New-PartialConfigPullScript -ConfigurationName $configName `
                                                    -Destination $script:ConfigDir `
                                                    -TestConfig $script:cfg `
                                                    -PartialConfigName1 'nxNopTest1' `
                                                    -PartialConfigName2 'nxNopTest2' `
                                                    -IncludeResourceServer

            Write-Verbose -Message "Invoke the compilation script"
            
            $mofDir = Join-Path $script:ConfigDir -ChildPath $configName
            Invoke-Expression "$scriptFile -outputPath $mofdir -ErrorAction Stop"

            Write-Verbose -Message "Edit the MOF to add additional settings"

            $mofFile = Join-Path -Path $mofDir -ChildPath ($script:cfg.LinuxClient.Name + '.meta.mof')
            $mofContent = Get-Content -Path $mofFile -Raw
            # Set/Update the MOF settings that cannot be set in the script due to schema differences between Windows and Linux
            $mofContent = Update-MetaConfigurationSetting -Content $mofContent -Name 'RefreshFrequencyMins' -Value '1'
            $mofContent = Update-MetaConfigurationSetting -Content $mofContent -Name 'DisableModuleSignatureValidation' -Value $true
            Set-Content -Path $mofFile -Value $mofContent

            $cimSession = Connect-Dsc -TargetCfg $cfg.LinuxClient

            Set-DscLocalConfigurationManager -path $mofDir -CimSession $cimSession -Verbose
            $dscMetaCfg = Get-DscLocalConfigurationManager -CimSession $cimSession -Verbose
            Update-DscConfiguration -CimSession $cimSession -Wait -Verbose
            $dscCfg = Get-DscConfiguration -CimSession $cimSession -Verbose
        }

        AfterAll `
        {
            if ($cimSession -ne $null)
            {
                $cimSession.Close()
            }
        }

        It 'Verifies the initial meta configuration for both pull servers' `
        {
            # Partial configurations
            $dscMetaCfg.PartialConfigurations[0].ResourceId | Should Be "[PartialConfiguration]nxNopTest1"
            $dscMetaCfg.PartialConfigurations[1].ResourceId | Should Be "[PartialConfiguration]nxNopTest2"
            $dscMetaCfg.ConfigurationDownloadManagers[0].ResourceId | Should Be "[ConfigurationRepositoryWeb]$($script:cfg.PullServer1.Name)"
            $dscMetaCfg.ConfigurationDownloadManagers[0].ConfigurationNames | Should Be "nxNopTest1"
            $dscMetaCfg.ConfigurationDownloadManagers[0].ServerURL | Should Be $script:cfg.PullServer1.ServerURL
            $dscMetaCfg.ConfigurationDownloadManagers[1].ResourceId | Should Be "[ConfigurationRepositoryWeb]$($script:cfg.PullServer2.Name)"
            $dscMetaCfg.ConfigurationDownloadManagers[1].ConfigurationNames | Should Be "nxNopTest2"
            $dscMetaCfg.ConfigurationDownloadManagers[1].ServerURL | Should Be $script:cfg.PullServer2.ServerURL
        }

        It 'Verifies the initial partial configurations' `
        {
            $dscCfg.GetType().FullName | Should Be 'System.Object[]'
            $dscCfg.Count | Should Be 2

            $cfg = $dscCfg[0]
            $cfg.Name | Should Be 'nxNopTest1'
            $cfg.Value | Should Be 'nop test 1.0'
            $cfg.Ensure | Should Be 'present'
            $cfg.CimClassName | Should Be 'MSFT_nxNopResource'

            $cfg = $dscCfg[1]
            $cfg.Name | Should Be 'nxNopTest2'
            $cfg.Value | Should Be 'nop test 2.0'
            $cfg.Ensure | Should Be 'present'
            $cfg.CimClassName | Should Be 'MSFT_nxNopResource'
        }

        It 'Updates one of the partial configurations and the referenced DSC resource and verifies the refresh' `
        {
            $updatedMof = Join-Path -Path $Env:TEMP -ChildPath 'nxNopTest1.mof'
            # Copy the nxNopTest1.0.1.mof file which references the 1.0.1 version of the nxNop resource.
            # This will be deployed to PullServer1 as nxNopTest1.mof which should cause a refresh of  
            # the partial configuration and pull down the DSC resource
            Copy-Item -Path (Join-Path -Path $script:ConfigDir -ChildPath 'nxNopTest1_1.0.1.mof') `
                      -Destination $updatedMof

            # Update the pull server
            Publish-Mof -MofFiles $updatedMof -DscServicePath $cfg.PullServer1.DscServicePath
            # Refresh is set to 60 seconds so wait for it to expire.
            Start-Sleep -Seconds 60
            $dscCfg = Get-DscConfiguration -CimSession $cimSession -Verbose

            $cfg = $dscCfg[0]
            $cfg.Name | Should Be 'nxNopTest1'
            $cfg.Value | Should Be 'Nop test 1.0.1'
            $cfg.Ensure | Should Be 'present'
            $cfg.CimClassName | Should Be 'MSFT_nxNopResource'
            # TODO: Update the resource to report the module's version as a read-only property.
        }
    }    
}

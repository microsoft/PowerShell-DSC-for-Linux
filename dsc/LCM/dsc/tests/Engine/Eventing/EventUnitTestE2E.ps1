function Deploy-TestPsProvider()
{
    $psProviderName = "DscTestPsResourceProvider"
    $destination = "$pshome\\Modules\\$psProviderName\\"
    New-Item -ItemType directory -Path $destination -Force

    # copy module files + schema mof
    Copy-Item ("..\..\..\tools\TestProviders\LcmTestProviders\\$psProviderName"+".psm1") -Destination $destination -Force
    Copy-Item ("..\..\..\tools\TestProviders\LcmTestProviders\\$psProviderName"+".psd1") -Destination $destination -Force
    Copy-Item ("..\..\..\tools\TestProviders\LcmTestProviders\\$psProviderName"+".schema.mof") -Destination $destination -Force
}

function Setup
(
)
{
#clean the log 
wevtutil set-log Microsoft-Windows-DSC/Debug /e:false /q:true
wevtutil set-log Microsoft-Windows-DSC/Analytic /e:false /q:true
wevtutil set-log Microsoft-Windows-DSC/operational /e:false /q:true
wevtutil cl Microsoft-Windows-DSC/operational
wevtutil cl Microsoft-Windows-DSC/Analytic
wevtutil cl Microsoft-Windows-DSC/Debug

#enable the log
wevtutil set-log Microsoft-Windows-DSC/Debug /e:true /q:true
wevtutil set-log Microsoft-Windows-DSC/Analytic /e:true /q:true
wevtutil set-log Microsoft-Windows-DSC/operational /e:true /q:true

}

function VerifyExpectedEvents
(
        [string][Parameter(Mandatory=$true)]$channel,
        [int[]][Parameter(Mandatory=$true)]$expectedEventsId
)
{
    $events = get-winevent -logname Microsoft-Windows-DSC/$channel -oldest
    if($? -eq $false)
    {
        echo "events didn't find in $channel" >> $resultfile
        return
    }

    foreach($expectedId in $expectedEventsId)
    {
        $find = $false
        foreach($event in $events)
        {
            if($event.id -eq $expectedId)
            {
                #check message contents of the event 0x1001
                if($expectedId -eq 0x1001)
                {

                    #check part of the messages in en-us
                    if([System.Threading.Thread]::CurrentThread.CurrentCulture.Name -eq "en-US")
                    {
                        if($event.Message -ne $null -and $event.Message.Contains("0x4") `
                            -and $event.Message.Contains("ResourceId is Res1") `
                            -and $event.Message.Contains("SourceInfo is SourceInfo1"))
                        {
                            $find = $true
                            break
                        }
                    }
                    else
                    {
                        $find = $true
                        break
                    }
                }
                #check message contents of the event 0x1015
                elseif($expectedId -eq 0x1015)
                {

                    #check part of the messages in en-us
                    if([System.Threading.Thread]::CurrentThread.CurrentCulture.Name -eq "en-US")
                    {
                        if($event.Message -ne $null -and $event.Message.Contains("Displaying verbose messages from Powershell provider:"))
                        {
                            $find = $true
                            break
                        }
                    }
                    else
                    {
                        $find = $true
                        break
                    }
                }
                #check message contents of the event 0x1016
                elseif($expectedId -eq 0x1016)
                {

                    #check part of the messages in en-us
                    if([System.Threading.Thread]::CurrentThread.CurrentCulture.Name -eq "en-US")
                    {
                        if($event.Message -ne $null -and $event.Message.Contains("Displaying debug messages from Powershell provider:"))
                        {
                            $find = $true
                            break
                        }
                    }
                    else
                    {
                        $find = $true
                        break
                    }
                }
                else
                {
                    $find = $true
                    break
                }

            }
        }
        if($find -eq $false)
        {
            echo "event $expectedId is expected in $channel" >> $resultfile
        }
    }

}

function VerifyFileProviderScenario()
{
    #file provider scenario
    Setup

    set-content localhost.mof -value "instance of MSFT_FileDirectoryConfiguration
    {
        ResourceId = `"Res1`";
        SourceInfo = `"SourceInfo1`";
        DestinationPath = `"C:\\DSCInstanceDoc.txt`";
        Contents = `"ABCD ABCD`";
        checksum = `"sha-20`";
    };

    instance of OMI_ConfigurationDocument
    {
        Version=`"1.0.0`";
    
    };
    "

    start-DscConfiguration -Path . -ComputerName localhost -wait

    #verification
    VerifyExpectedEvents "debug" @(0x1003)
    VerifyExpectedEvents "Analytic" @(0x1002, 0x1004, 0x1005) 
    #for some strange reason the operational events cannot be retrieved immedately
    sleep  1
    VerifyExpectedEvents "Operational" @(0x1001, 0x1006)
}

function VerifyScriptBlockScenario()
{
    #ScriptBlock provider scenario
    Setup

    set-content testscriptblock.mof -value "instance of MSFT_ScriptResource
    {
        ResourceId = `"b`";
        GetScript = `"get-ExecutionPolicy`";
        SetScript = `"Get-ExecutionPolicy`";
        TestScript = `"`$false`";
    };
 
    instance of MSFT_ScriptResource as `$MSFT_ScriptResource2ref
    {
        ResourceId = `"script2`";
        GetScript = `"get-ExecutionPolicy`";
        SetScript = `"Get-ExecutionPolicy`";
        TestScript = `"throw \`"something bad\`"`";
    };

    instance of OMI_ConfigurationDocument
    {
        Version=`"1.0.0`";
 
    };
    "


    $configdata =[system.io.file]::ReadAllBytes("testscriptblock.mof")
    Invoke-CimMethod -Namespace root/Microsoft/Windows/DesiredStateConfiguration -ClassName MSFT_DSCLocalConfigurationManager -Name SendConfigurationApply -Arguments @{ConfigurationData = $configdata;force=$false} 

    #verification
    VerifyExpectedEvents "debug" @(0x1003)
    VerifyExpectedEvents "Analytic" @(0x1004, 0x1005) 
    #No operational event in this case

}


function VerifyPsVerBoseDebugMessage()
{
    #use DscTestPSResourceProvider to verify that we can dump vebose and debug message from ps provider
    Setup

    set-content testverbosedebug.mof -value "instance of DscTestPSResourceProvider
    {
        ResourceId = `"Res1`";
        Name = `"namenotimportant`";
    };

    instance of OMI_ConfigurationDocument
    {
        Version=`"1.0.0`";
    };
    "


    $configdata =[system.io.file]::ReadAllBytes("testverbosedebug.mof")
    Invoke-CimMethod -Namespace root/Microsoft/Windows/DesiredStateConfiguration -ClassName MSFT_DSCLocalConfigurationManager -Name SendConfigurationApply -Arguments @{ConfigurationData = $configdata;force=$false} 

    #verification
    VerifyExpectedEvents "debug" @(0x1016)
    VerifyExpectedEvents "Analytic" @(0x1015) 
    #No operational event in this case

}


.\EventUnitTestCleanup.ps1


Deploy-TestPsProvider
mkdir eventunitestdata
cd eventunitestdata
[System.IO.Directory]::SetCurrentDirectory($pwd);

$resultfile = "result.txt"
VerifyFileProviderScenario
VerifyScriptBlockScenario
VerifyPsVerBoseDebugMessage





cd ..
[System.IO.Directory]::SetCurrentDirectory($pwd);

<#
    .SYNOPSIS
        Retrieves the metadata of all installed applications in the current environment.

    .DESCRIPTION
        Installed applications are searched for under the following 3 paths:
            - HKLM:SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall
            - HKLM:SOFTWARE\Wow6432node\Microsoft\Windows\CurrentVersion\Uninstall
            - HKCU:Software\Microsoft\Windows\CurrentVersion\Uninstall

        The child items of these three paths are returned as the meta data for all currently
        installed applications in the current environment.

    .EXAMPLE
        Get-AllInstalledApplications
#>
function Get-AllInstalledApplications
{
    [OutputType([Microsoft.Win32.RegistryKey[]])]
    param()

    # Installed applications can be found under 2 system paths and the current user path
    $applicationPaths = @(
        "HKLM:SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall",
        "HKLM:SOFTWARE\Wow6432node\Microsoft\Windows\CurrentVersion\Uninstall",
        "HKCU:Software\Microsoft\Windows\CurrentVersion\Uninstall"
    )

    $applicationMetaData = @()
    foreach ($applicationPath in $applicationPaths)
    {
        if (Test-Path -Path $applicationPath)
        {
            $applicationMetaData += Get-ChildItem -Path $applicationPath
        }
    }

    return $applicationMetaData
}

<#
    .SYNOPSIS
        Retrieves the metadata of the application with the specified name from the specified list
        of all applications.

    .PARAMETER Name
        The name of the application to find in the specified list of all applications.

    .PARAMETER AllInstalledApplications
        A list of the metadata of all installed applications in which to search for the application
        with the specified name.

        This should be the output of the cmdlet 'Get-AllInstalledApplications'.

    .EXAMPLE
        Find-InstalledApplication -Name 'Google Chrome' -AllInstalledApplications $(Get-AllInstalledApplications)
#>
function Test-ApplicationInstalled
{
    [OutputType([Boolean])]
    param
    (
        [Parameter(Mandatory = $true)]
        [String]
        $Name
    )

    $foundApplications = @()
    $allInstalledApplications = Get-AllInstalledApplications

    $foundApplications += $allInstalledApplications | Where-Object { $_.PSChildName -ilike $Name}
    $foundApplications += $allInstalledApplications | Where-Object { $_.GetValue('DisplayName') -ilike $Name}

    if ($foundApplications.Count -gt 0)
    {
        return $true
    }

    return $false
}

<#
    .SYNOPSIS
        Installs LogAnalyticsAgent and connects it to specified Azure Automation Workspace.

    .PARAMETER WorkspaceId
        The Azure Automation Workspace ID.

    .PARAMETER WorkspaceKey
        The Azure Automation Workspace Key.

    .EXAMPLE
        Install-LogAnalyticsAgent -WorkspaceId <Workspace ID> -WorkspaceKey <Workspace Key>
#>
function Install-LogAnalyticsAgent
{
    [CmdletBinding()]
    param
    (
        [Parameter(Mandatory = $true)]
        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceId,

        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceKey
    )

    $workspaceIdList = @($WorkspaceId.Split(';').Trim())
    if($workspaceIdList.Count -gt 1) 
    {
        Throw 'Connecting MMA agent to multiple workspace is not supported by Guest Configuration assignment.'
    }

    $parentFolderPath = Split-Path -Path $PSScriptRoot -Parent
    $agentInstallerPath = Join-Path (Join-Path $parentFolderPath '..') 'MMASetup-AMD64.exe'
    Write-Verbose "Installing MMA Agent .."  -Verbose
    $ArgumentList = '/C:"setup.exe /qn ADD_OPINSIGHTS_WORKSPACE=1 '+  "OPINSIGHTS_WORKSPACE_ID=$WorkspaceId " + "OPINSIGHTS_WORKSPACE_KEY=$WorkspaceKey " +'AcceptEndUserLicenseAgreement=1"' 
    Start-Process $agentInstallerPath -ArgumentList $ArgumentList -ErrorAction Stop -Wait
}

function Get-ReasonsLogAnalyticsAgentNotHealthy
{
    [CmdletBinding()]
    [OutputType([Hashtable[]])]
    param
    (
        [Parameter(Mandatory = $true)]
        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceId
    )

    $reasons = @()
    $reasonCodePrefix = 'LogAnalyticsAgent:LogAnalyticsAgent'

    $mmaInstalled = Test-ApplicationInstalled -Name 'Microsoft Monitoring Agent'

    if (-not $mmaInstalled)
    {
        Write-Verbose -Message "Micorosft Monitoring Agent application is not installed."
        $reason = @{
            Code = $reasonCodePrefix + ':ApplicationNotInstalled'
            Phrase = "The Log Analytics agent application is not installed."
        }
        $reasons += $reason
    }
    else
    {
        Write-Verbose -Message "Micorosft Monitoring Agent application is installed."

        try
        {
            $healthService = New-Object -ComObject 'AgentConfigManager.MgmtSvcCfg'
        }
        catch
        {
            Write-Verbose -Message "Failed to create an AgentConfigManager.MgmtSvcCfg COM object to read the status of the Log Analytics agent connection."
            $reason = @{
                Code = $reasonCodePrefix + ':COMObjectCreationFailure'
                Phrase = "Failed to create an AgentConfigManager.MgmtSvcCfg COM object to read the status of the Log Analytics agent connection. The Microsoft Monitoring Agent application may not have installed correctly."
            }
            $reasons += $reason
            $mmaInstalled = $false
        }

        if ($mmaInstalled)
        {
            $workspaceIdList = @($WorkspaceId.Split(';').Trim())
            foreach ($individualWorkspaceId in $workspaceIdList)
            {
                $workspace = $healthService.GetCloudWorkspace($individualWorkspaceId)

                if ($null -eq $workspace)
                {
                    Write-Verbose -Message "Could not find a workspace with the specified workspace ID '$individualWorkspaceId' connected to this machine."
                    $reason = @{
                        Code = $reasonCodePrefix + ':WorkspaceNotFound'
                        Phrase = "Could not find a workspace with the specified workspace ID '$individualWorkspaceId' connected to this machine."
                    }
                    $reasons += $reason
                }
                else
                {
                    $workspaceConnectionStatus = $workspace.ConnectionStatus

                    if ($workspaceConnectionStatus -ne 0)
                    {
                        Write-Verbose -Message "The connected workspace with the ID '$individualWorkspaceId' has an unexpected connection status with the code '$($workspaceConnectionStatus)' and the message '$($workspace.ConnectionStatusText)'."
                        $reason = @{
                            Code = $reasonCodePrefix + ':WorkspaceUnexpectedConnectionStatus'
                            Phrase = "The connected workspace with the ID '$individualWorkspaceId' has an unexpected connection status with the code '$($workspaceConnectionStatus)' and the message '$($workspace.ConnectionStatusText)'."
                        }
                        $reasons += $reason
                    }
                }
            }
        }
    }

    return $reasons
}

function Get-TargetResource
{
    [CmdletBinding()]
    [OutputType([Hashtable])]
    param
    (
        [Parameter(Mandatory = $true)]
        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceId,

        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceKey
    )

    $reasons = @(Get-ReasonsLogAnalyticsAgentNotHealthy -WorkspaceId $WorkspaceId)

    $mmaInfo = @{
        WorkspaceId = $WorkspaceId
    }

    if ($null -ne $reasons -and $reasons.Count -gt 0)
    {
        $mmaInfo['Reasons'] = $reasons
    }

    return $mmaInfo
}

function Test-TargetResource
{
    [CmdletBinding()]
    [OutputType([Boolean])]
    param
    (
        [Parameter(Mandatory = $true)]
        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceId,

        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceKey
    )

    $reasons = @(Get-ReasonsLogAnalyticsAgentNotHealthy -WorkspaceId $WorkspaceId)

    if ($null -ne $reasons -and $reasons.Count -gt 0)
    {
        return $false
    }

    return $true
}

function Set-TargetResource
{
    [CmdletBinding()]
    param
    (
        [Parameter(Mandatory = $true)]
        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceId,

        [ValidateNotNullOrEmpty()]
        [String]
        $WorkspaceKey
    )

    Install-LogAnalyticsAgent -WorkspaceId $WorkspaceId -WorkspaceKey $WorkspaceKey
}

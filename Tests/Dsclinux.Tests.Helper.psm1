
<#
.SYNOPSIS
    Creates a connection to the OMI server
#>
function CreateCimSession

{
    param
    (
     [Parameter(Mandatory=$true)]
     [PSCredential] $credential,

     [Parameter(Mandatory=$true)]
     [ValidateNotNullOrEmpty()]
     [string] $server,

     [ValidateNotNull()]
     [Uint32] $port = 5986

    )

    $sessionOptions = New-CimSessionOption -SkipCACheck -SkipCNCheck -SkipRevocationCheck -UseSsl
    $session = New-CimSession -Credential $credential -ComputerName $server -Port $port -Authentication Basic -SessionOption $sessionOptions -OperationTimeoutSec:30
    return $session

}

<#
.SYNOPSIS
    Gets information about test environment for DSC Linux

.DESCRIPTION
    Reads Information about DSC Linux client & Pull Server from JSON file. 
#>
function ImportLinuxTestConfigurtaion

{
     param
    (     
     [Parameter(Mandatory=$true)]
     [ValidateNotNullOrEmpty()]
     [string] $testConfigFile
   )

    $testMatrix = Get-Content $testConfigFile | ConvertFrom-Json            
    return $testMatrix[0]
}

Export-ModuleMember -function ImportLinuxTestConfigurtaion, CreateCimSession

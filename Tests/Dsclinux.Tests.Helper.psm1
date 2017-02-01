#
# Create a connection to the OMI server: 
#
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

#
# Get Linux Client Information 
#
function ImportLinuxTestConfigurtaion

{
    $testMatrix = Get-Content .\DSCLinuxTestConfig.json | ConvertFrom-Json            
    return $testMatrix[0].LinuxClient
}

Export-ModuleMember -function ImportLinuxTestConfigurtaion, CreateCimSession

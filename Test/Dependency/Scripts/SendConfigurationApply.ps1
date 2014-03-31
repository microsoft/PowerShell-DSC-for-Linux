Param
(
    [Parameter(mandatory = $true)]
    [String] $ConfigurationMof,

    [Parameter(mandatory = $true)]
    [String] $HostName,

    [Parameter(mandatory = $false)]
    [String] $Username = "scxuser",

    [Parameter(mandatory = $false)]
    [String] $Password = "scxuser"
)

$options=New-Object -type Microsoft.Management.Infrastructure.Options.CimOperationOptions
$buf = Get-Content $ConfigurationMof -Encoding Byte -Raw
$buf2 = @()
$bufLength = [BitConverter]::GetBytes($buf.Length+4)
$buf2 = $buf2 + $bufLength[3]
$buf2 = $buf2 + $bufLength[2]
$buf2 = $buf2 + $bufLength[1]
$buf2 = $buf2 + $bufLength[0]
$buf2 = $buf2 + $buf
$configParam=[Microsoft.Management.Infrastructure.CimMethodParameter]::Create("ConfigurationData", $buf2, [Microsoft.Management.Infrastructure.CimType]::UInt8Array,0)
$forceParam=[Microsoft.Management.Infrastructure.CimMethodParameter]::Create("Force", $true, [Microsoft.Management.Infrastructure.CimType]::Boolean,0)
$t=New-Object -type Microsoft.Management.Infrastructure.CimMethodParametersCollection
$t.Add($configParam)
$t.Add($forceParam)
$secpass =  ConvertTo-SecureString $Password -AsPlainText -Force
$cimCred= new-object -TypeName Microsoft.Management.Infrastructure.Options.CimCredential -ArgumentList @("Basic", "", $Username, $secpass)
$sessionOptions=New-CimSessionOption -Protocol WSMAN 
$sessionOptions.AddDestinationCredentials($cimCred)
$cimSession = [Microsoft.Management.Infrastructure.CimSession]::Create($HostName,$sessionOptions)
$cimSession.InvokeMethod("dsc","MSFT_DSCLocalConfigurationManager","SendConfigurationApply", $t, $options) 

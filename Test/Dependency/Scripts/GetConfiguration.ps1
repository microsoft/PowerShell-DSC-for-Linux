Param
(
    [Parameter(mandatory = $true)]
    [String] $HostName,

    [Parameter(mandatory = $false)]
    [String] $Username = "scxuser",

    [Parameter(mandatory = $false)]
    [String] $Password = "scxuser"
)

$secpass =  ConvertTo-SecureString $Password -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential($Username,$secpass)
$omiSess = New-CimSession -ComputerName $HostName -Authentication Basic -SessionOption (New-CimSessionOption -Protocol Wsman) -Credential $cred -SkipTestConnection
$r=Invoke-CimMethod -CimSession $omiSess -Namespace "dsc" -ClassName MSFT_DSCLocalConfigurationManager -MethodName GetConfiguration
echo $r.configurations
# Get-CimInstance -Namespace "/dsc" -ClassName XYZ_Dog -CimSession $omiSess
[CmdletBinding()]
Param(
	[Parameter(Mandatory=$True)][string]$ComputerName,
	[Parameter(Mandatory=$True)][string]$Login,
	[Parameter(Mandatory=$True)][string]$Password
)

$secpass =  ConvertTo-SecureString $Password -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential($Login,$secpass)
$omiSess = New-CimSession -ComputerName $ComputerName -Authentication Basic -SessionOption (New-CimSessionOption -Protocol Wsman) -Credential $cred -SkipTestConnection
$r=Invoke-CimMethod -CimSession $omiSess -Namespace "root/Microsoft/DesiredStateConfiguration" -ClassName MSFT_DSCLocalConfigurationManager -MethodName GetConfiguration
echo $r.configurations
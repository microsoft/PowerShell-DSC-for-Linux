$secpass =  ConvertTo-SecureString "OpsMgr2007R2" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential("root",$secpass)
$omiSess = New-CimSession -ComputerName 10.30.69.134 -Authentication Basic -SessionOption (New-CimSessionOption -Protocol Wsman) -Credential $cred -SkipTestConnection
$r=Invoke-CimMethod -CimSession $omiSess -Namespace "dsc" -ClassName MSFT_DSCLocalConfigurationManager -MethodName GetConfiguration
echo $r.configurations
# Get-CimInstance -Namespace "/dsc" -ClassName XYZ_Dog -CimSession $omiSess
$options=New-Object -type Microsoft.Management.Infrastructure.Options.CimOperationOptions
$buf = Get-Content "C:\Users\jkordic\Documents\DSC Work\Configuration MOF Files\File_test2.mof" -Encoding Byte -Raw
#$buf = Get-Content .\157.59.136.151.mof  -Encoding Byte -Raw
#$buf = Get-Content .\157.59.138.106_logonly.mof -Encoding Byte -Raw
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
$secpass =  ConvertTo-SecureString "OpsMgr2007R2" -AsPlainText -Force
$cimCred= new-object -TypeName Microsoft.Management.Infrastructure.Options.CimCredential -ArgumentList @("Basic", "", "johnkord",$secpass)
$sessionOptions=New-CimSessionOption -Protocol WSMAN 
$sessionOptions.AddDestinationCredentials($cimCred)
$cimSession = [Microsoft.Management.Infrastructure.CimSession]::Create("10.30.69.134",$sessionOptions)
$cimSession.InvokeMethod("dsc","MSFT_DSCLocalConfigurationManager","SendConfigurationApply", $t, $options) 

[CmdletBinding()]
param # support -verbose
(

)
$resources = @{
    'nxArchive'='MSFT_nxArchiveResource';
    'nxEnvironment' = 'MSFT_nxEnvironmentResource';
    'nxFileLine' = 'MSFT_nxFileLineResource';
    'nxFile'='MSFT_nxFileResource';
    'nxGroup' = 'MSFT_nxGroupResource'
    'nxPackage' = 'MSFT_nxPackageResource';
    'nxService' = 'MSFT_nxServiceResource';
    'nxScript' = 'MSFT_nxScriptResource';
    'nxSshAuthorizedKeys' = 'MSFT_nxSshAuthorizedKeysResource';
    'nxUser' = 'MSFT_nxUserResource';
}
& "$PSScriptRoot/PackageResource.ps1" -ModuleName nx -Resources $resources -Version 1.0

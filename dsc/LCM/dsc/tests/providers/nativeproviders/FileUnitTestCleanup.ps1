param(
     [switch][Parameter(Mandatory=$false, Position=0)]$keepcache=$false
)

if(Test-Path fileunitestdata)
{
    del fileunitestdata -Force -Recurse
}
if($keepcache -eq $false -and (Test-Path $env:windir"\system32\Configuration\BuiltinProvCache\MSFT_FileDirectoryConfiguration"))
{
    del $env:windir"\system32\Configuration\BuiltinProvCache\MSFT_FileDirectoryConfiguration" -Force -Recurse
}



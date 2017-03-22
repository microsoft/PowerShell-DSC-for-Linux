# Simple File provider Test 

param
(
    [Parameter(Mandatory=$true)]
    [ValidateNotNullOrEmpty()]
    [string] $targetClient,

    [Parameter(Mandatory=$true)]
    [ValidateNotNullOrEmpty()]
    [string] $Ensure
)

Configuration FileProviderTestConfig1
{
 param
 (
    [Parameter(Mandatory=$true)]
    [ValidateNotNullOrEmpty()]
    [string] $targetClient,

 	[Parameter(Mandatory=$true)]
 	[ValidateNotNullOrEmpty()]
 	[string] $Ensure
 )

    Import-DSCResource -Module nx

    Node $targetClient
    {
        nxFile myTestFile
        {
            Ensure = $Ensure
            Type = "File"
            DestinationPath = "/tmp/dsctest1"
            Contents="Linux DSC Test1!"
        }
    }
}

FileProviderTestConfig1 -targetClient $targetClient -Ensure $Ensure -Output "$env:temp\FileProviderTestConfig1"
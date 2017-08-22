<#
    .SYNOPSIS
        Simple test configuration with one nxFile resource.
#>
param
(
    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [String]
    $TargetClient,

    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [String]
    $Output,

    [Parameter()]
    [ValidateSet('Present', 'Absent')]
    [String]
    $Ensure,

    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [String]
    $Type,

    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [String]
    $DestinationPath,

    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [String]
    $Contents
)

Configuration FileProviderTestConfig1
{
    param
    (
        [Parameter(Mandatory = $true)]
        [ValidateNotNullOrEmpty()]
        [String]
        $TargetClient,

        [Parameter()]
        [ValidateSet('Present', 'Absent')]
        [String]
        $Ensure = 'Present',

        [Parameter()]
        [ValidateNotNullOrEmpty()]
        [String]
        $Type = 'File',

        [Parameter()]
        [ValidateNotNullOrEmpty()]
        [String]
        $DestinationPath = '/tmp/dsctest1',

        [Parameter()]
        [ValidateNotNullOrEmpty()]
        [String]
        $Contents = 'Linux DSC Test1!'
    )

    Import-DSCResource -Module nx

    Node $TargetClient
    {
        nxFile myTestFile
        {
            Ensure = $Ensure
            Type = $Type
            DestinationPath = $DestinationPath
            Contents = $Contents
        }
    }
}

FileProviderTestConfig1 @PSBoundParameters

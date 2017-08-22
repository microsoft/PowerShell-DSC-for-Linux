<#
    .SYNOPSIS
        Meta Configuration for Push DSC 

    .PARAMETER TargetClient
        The target machine for which to compile the metaconfiguration.
    
    .PARAMETER Output
        The file path at which to output the compiled mof.
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
    [ValidateNotNullOrEmpty()] 
    [String]
    $RefreshMode,

    [Parameter()]
    [Boolean]
    $RebootNodeIfNeeded,

    [Parameter()]
    [ValidateRange(1, [Int]::MaxValue)]
    [Int]
    $RefreshFrequencyMins,

    [Parameter()]
    [ValidateRange(1, [Int]::MaxValue)]
    [Int]
    $ConfigurationModeFrequencyMins,

    [Parameter()] 
    [ValidateNotNullOrEmpty()] 
    [String]
    $ConfigurationMode
)

Configuration MetaConfigPush
{    
    param 
    ( 
        [Parameter(Mandatory = $true)] 
        [ValidateNotNullOrEmpty()] 
        [String]
        $TargetClient,

        [Parameter()] 
        [ValidateNotNullOrEmpty()] 
        [String]
        $RefreshMode = 'PUSH',

        [Parameter()]
        [Boolean]
        $RebootNodeIfNeeded = $true,

        [Parameter()]
        [ValidateRange(1, [Int]::MaxValue)]
        [Int]
        $RefreshFrequencyMins = 30,

        [Parameter()]
        [ValidateRange(1, [Int]::MaxValue)]
        [Int]
        $ConfigurationModeFrequencyMins = 60,

        [Parameter()] 
        [ValidateNotNullOrEmpty()] 
        [String]
        $ConfigurationMode = 'ApplyAndAutoCorrect' 
    ) 

    Node $TargetClient
    {
        LocalConfigurationManager
        {
            RefreshMode = $RefreshMode
            RebootNodeIfNeeded = $RebootNodeIfNeeded
            RefreshFrequencyMins = $RefreshFrequencyMins
            ConfigurationModeFrequencyMins = $ConfigurationModeFrequencyMins
            ConfigurationMode = $ConfigurationMode
        }
    }
}

MetaConfigPush @PSBoundParameters

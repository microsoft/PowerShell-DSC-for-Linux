# Meta Configuration for Push DSC 
 
param 
( 
    [Parameter(Mandatory=$true)] 
    [ValidateNotNullOrEmpty()] 
    [string] $targetClient
)

Configuration MetaConfigPush
{    
   param 
    ( 
        [Parameter(Mandatory=$true)] 
        [ValidateNotNullOrEmpty()] 
        [string] $targetClient 
    ) 

    Node $targetClient
    {
        LocalConfigurationManager
        {
            RefreshMode = "PUSH";
            RebootNodeIfNeeded = $true;
            RefreshFrequencyMins = 30;
            ConfigurationModeFrequencyMins = 60;
            ConfigurationMode = "ApplyAndAutoCorrect";
        }
    }
}


MetaConfigPush -targetClient $targetClient -Output "$env:temp\MetaConfigPush"


$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

<#
.SYNOPSIS
    Creates a connection to the OMI server
#>


<#
.SYNOPSIS
    Gets information about test environment for DSC Linux

.DESCRIPTION
    Reads Information about DSC Linux client & Pull Server from JSON file. 
#>
function ImportLinuxTestConfigurtaion

{
     param
    (     
     [Parameter(Mandatory=$true)]
     [ValidateNotNullOrEmpty()]
     [string] $testConfigFile
   )

    $testMatrix = Get-Content $testConfigFile | ConvertFrom-Json            
    return $testMatrix[0]
}


#
# Create a connection to the OMI server: 
#

function CreateCimSession
{
    param
    (
        [Parameter(Mandatory=$true)]
        [PSCredential]  [System.Management.Automation.Credential()] $credential,

        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string] $server,

        [ValidateNotNull()]
        [Uint32] $port = 5986
    )

    $sessionOptions = New-CimSessionOption -SkipCACheck -SkipCNCheck -SkipRevocationCheck -UseSsl
    $session = New-CimSession -Credential $credential -ComputerName $server -Port $port -Authentication Basic -SessionOption $sessionOptions -OperationTimeoutSec:30
    return $session
}

<#
.Synopsis
    Creates a CIM session to the machine defined in the specified ClientCfg
.Parameter TargetCfg
    The configuration defining the target machine, port, and username/password
.Example
    Example json from the test configuration file.
    "LinuxClient": {
            "Name": "machinename",
            "UserName": "root",
            "Password": "password",
            "Port": 5986
        },
.Example
    Connect to a linux server defined in a test configuration file.
    $cfg = Get-TestConfiguration
    Connect-Dsc -TargetCfg $cfg.LinuxClient
#>
function Connect-Dsc
{
    param
    (
        [System.Management.Automation.PSObject] $TargetCfg
    )
    $password = ConvertTo-SecureString -String $TargetCfg.Password -AsPlainText -Force
    $credential = [System.Management.Automation.PSCredential]::new($TargetCfg.Username, $password)
    [Uint32] $port = 5986
    if ($TargetCfg.psobject.properties['Port'] -ne $null)
    {
        $port = $TargetCfg.Port
    }
    return CreateCimSession -credential $credential -server $TargetCfg.Name -port $port
}

<#
.SYNOPSIS
    Loads the test configuration file containing information about test environment for DSC Linux

.Parameter Path
    The path of the file to load.  If not specified, the environment variable DSC_LINUX_TEST_CONFIG will be
    used. If the environemtn variable is not defined, '.\DSCLinuxTestConfig.json' will be used.

.DESCRIPTION
    The test configuration file should contain a dictionary with 3 entries, LinuxClient
    PullServer1, and PullServer2.

.EXAMPLE
    The following illustrates an example configuration.

{
    "Settings": {
        "AllowModuleOverwrite": true,
        "ConfigurationMode": "ApplyAndAutoCorrect",
        "ConfigurationModeFrequencyMins": 15,
        "RebootNodeIfNeeded": true,
        "RefreshFrequencyMins": 15,
        "RefreshMode": "PULL"
    },

    "LinuxClient": {
        "Name": "mylinux",
        "UserName": "root",
        "Password": "foobar*"
    },

    "PullServer1": {
        "Name": "mypullserver1",
        "ServerURL": "http://mypullserver1:8080/PSDSCPullServer.svc",
        "RegistrationKey": "7f466f8e-027e-44c2-9a7b-897c08b355f1",
        "DscServicePath": "\\\\dantra12kr2\\c$\\Program Files\\WindowsPowerShell\\DscService"
    },

    "PullServer2": {
        "Name": "mypullserver2",
        "ServerURL": "http://mypullserver2:8080/PSDSCPullServer.svc",
        "RegistrationKey": "599f9c7d-a0b1-4a1a-8593-8728a99c3fb2",
        "DscServicePath": "\\\\dantra12kr2b\\c$\\Program Files\\WindowsPowerShell\\DscService"
    },

    "ResourceServer": {
        "Name": "myresourceserver",
        "ServerURL": "http://myresourceserver:8080/PSDSCPullServer.svc",
        "RegistrationKey": "7f466f8e-027e-44c2-9a7b-897c08b355f1",
        "ModulePath": "\\\\myresourceserver\\c$\\Program Files\\WindowsPowerShell\\DscService\\Modules"
    },

    "ReportServer": {
        "Name": "myreportserver",
        "ServerURL": "http://myreportserver:8080/PSDSCPullServer.svc",
        "RegistrationKey": "7f466f8e-027e-44c2-9a7b-897c08b355f1"
    }
}

#>
function Get-TestConfiguration
{
    param
    (
        [string] $Path
    )
    if ([string]::IsNullOrEmpty($Path))
    {
        $Path = $env:DSC_LINUX_TEST_CONFIG
        if ($null -eq $Path)
        {
            Write-Verbose -Message 'Using default test configuration file .\DSCLinuxTestConfig.json'
            # fallback
            $Path = '.\DSCLinuxTestConfig.json'
        }
        else
        {
            Write-Verbose -Message 'Using test configuration file from the DSC_LINUX_TEST_CONFIG environment variable'
        }
    }
    else
    {
        Write-Verbose -Message 'Using the passed in test configuration file'
    }

    if (-not (Test-Path -Path $Path))
    {
        throw "The test configuration file does not exist: $testConfigFile"
    }
    Write-Verbose "Using test configuration file $Path"
    $testcfg = Get-Content -Path $Path | ConvertFrom-Json
    $testCfg = Get-Content $Path | ConvertFrom-Json
    return $testCfg
}

<#
    provides a class for building test configuration scripts based
    on test configuration data.
#>
class ConfigScriptBuilder
{
    hidden [System.Text.StringBuilder] $sb
    hidden [string] $indentSpaces
    hidden [int] $indentCount
    hidden [string] $configurationName

    ConfigScriptBuilder([string] $configurationName)
    {
        $this.configurationName = $configurationName
        $this.sb = [System.Text.StringBuilder]::new()
        $this.indentCount = 0
        $this.indentSpaces = ''
        $this.WriteLine('[CmdletBinding()]')
        $this.WriteLine('param')
        $this.WriteLine('(')
        $this.Indent()
        $this.WriteLine('[Parameter(Mandatory, Position=0)]')
        $this.WriteLine('[string] $OutputPath')
        $this.Outdent()
        $this.WriteLine(')')
        $this.WriteLine('Set-StrictMode -Version latest')
        $this.WriteLine('$ErrorActionPreference = "Stop"')
        $this.WriteLine()
    }

    [string] GetText()
    {
        return $this.sb.ToString()
    }

    hidden [void] Indent()
    {
        $this.indentCount = $this.indentCount + 1
        $this.indentSpaces = $this.indentSpaces + '    '
    }

    hidden [void] Outdent()
    {
        if ($this.indentCount -gt 0)
        {
            $this.indentCount = $this.indentCount - 1
            $this.indentSpaces = $this.indentSpaces.SubString(0, $this.indentCount * 4)
        }
    }

    [void] WriteLine([string] $value)
    {
        $this.sb.Append($this.indentSpaces)
        $this.sb.Append($value)
        $this.sb.AppendLine()
    }

    [void] WriteLine()
    {
        $this.sb.AppendLine()
    }

    # Writes a name=value integer setting without quotes around the value
    [void] WriteInteger([string] $name, [int] $value)
    {
        $this.sb.Append($this.indentSpaces)
        $this.sb.AppendFormat('{0} = {1:d}', $name, $value)
        $this.sb.AppendLine()
    }

    # Writes a name=value boolean setting using the strings $true and $false
    [void] WriteBoolean([string] $name, [bool] $value)
    {
        $this.sb.Append($this.indentSpaces)
        if ($value)
        {
            $formattedvalue = '$true'
        }
        else
        {
            $formattedvalue = '$false'
        }
        $this.sb.AppendFormat("{0} = {1}", $name, $formattedvalue)
        $this.sb.AppendLine()
    }

    # Writes a name=value string setting without quotes around the value
    [void] WriteString([string] $name, [string] $value)
    {
        $this.sb.Append($this.indentSpaces)
        $this.sb.AppendFormat("{0} = {1}", $name, $value)
        $this.sb.AppendLine()
    }

    # Writes a name=value setting with single quotes around the value
    [void] WriteValue([string] $name, [object] $value)
    {
        $this.sb.Append($this.indentSpaces)
        $this.sb.AppendFormat("{0} = '{1}'", $name, $value)
        $this.sb.AppendLine()
    }

    # Opens a named element, such as the 'Node' element.
    # This method is for elements that have an associated value, such as Node and ConfigurationRepositoryWeb.
    [void] OpenElement([string] $name, [string] $value)
    {
        $this.sb.Append($this.indentSpaces)
        $this.sb.AppendFormat("{0} {1}", $name, $value)
        $this.sb.AppendLine()
        $this.sb.Append($this.indentSpaces)
        $this.sb.AppendLine("{")
        $this.Indent()
    }

    # Opens a named element, such as the 'Configuration' or 'Settings' element.
    # This method is for elements that do not have an associated value.
    [void] OpenElement([string] $name)
    {
        $this.OpenElement($name, '')
    }

    # Closes an element, such as the 'Configuration' or 'Node' element.
    [void] CloseElement()
    {
        $this.Outdent()
        $this.sb.Append($this.IndentSpaces)
        $this.sb.AppendLine("}")
    }

    # Defines the set of 'supported' meta configuration properties and their associated type.
    # NOTE: The table is a hash of setting name to type where type is one of the following:
    # 'value' - a quoted string
    # 'string' - an unquoted string
    # 'integer' - an unquoted, integer value
    # 'boolean' - a true or false value. For MOF, the constants True and False. For configuration scripts, $true and $false
    hidden static $SettingsProperties = @{
        'ActionAfterReboot' = 'value';
        'AllowModuleOverwrite' = 'boolean';
        'Certificateid' = 'value';
        'ConfigurationID' = 'value';
        'ConfigurationMode' = 'value';
        'ConfigurationModeFrequencyMins' = 'integer';
        'DisableModuleSignatureValidation' = 'boolean';
        'DownloadManagerName' = 'value';
        'MaximumDownloadSizeMB' = 'integer';
        'RebootNodeIfNeeded' = 'boolean';
        'RefreshFrequencyMins' = 'integer';
        'RefreshMode' = 'value';
        'SignatureValidationPolicy' = 'value';
        'StatusRetentionTimeInDays' = 'integer';
        # TODO
        # 'Credential' = '????';
        # 'DebugMode' = 'stringarray';
    }

    static [string] GetSettingType([string] $name)
    {
        if ([ConfigScriptBuilder]::SettingsProperties.ContainsKey($name))
        {
            return [ConfigScriptBuilder]::SettingsProperties[$name]
        }
        return $null
    }

    # Writes the Settings element of a meta configuration file.
    [void] WriteSettings([System.Management.Automation.PSObject] $settings)
    {
        $this.OpenElement('Settings')

        foreach ($note in $settings.psobject.Properties)
        {
            if (![ConfigScriptBuilder]::SettingsProperties.ContainsKey($note.Name))
            {
                throw "Setting property $($note.Name) is not supported. value = $($note.Value)"
            }

            $type = [ConfigScriptBuilder]::SettingsProperties[$note.Name]
            switch ($type)
            {
                # Write the value as a single quoted string.
                'value' {$this.WriteValue($note.Name, $note.Value)}
                # Write the value as an unquoted integer
                'integer' {$this.WriteInteger($note.Name, $note.Value)}
                # Write the value using $true or $false
                'boolean' {$this.WriteBoolean($note.Name, $note.Value)}
                # Write the value as an unquoted string.
                'string' {$this.WriteString($note.Name, $note.Value)}
            }
        }

        $this.CloseElement()
    }

<#
    Future - consider verifying mandatory properties on the various test configuration json
    -or-
    create a schema for it.

    static hidden [void] VerifyProperties([System.Management.Automation.PSObject] $object, [string] $objectName, [string[]] $propertyNames)
    {
        [bool] $success = $true
        foreach ($propertyName in $propertyNames)
        {
            if ($object.psobject.Properties[$propertyName] -eq $null)
            {
                Write-Error -Message "$objectName must contain the property $propertyName"
                $success = $false
            }
        }
        if ($false -eq $success)
        {
            throw "$objectName object is missing required properties"
        }
    }
#>

    static hidden [bool] IsUnsecureConnection([string] $url)
    {
        [Uri] $uri = [Uri]::new($url)
        return ([StringComparer]::OrdinalIgnoreCase.Compare($uri.Scheme, 'http') -eq 0)
    }

    # Writes the PartialConfiguration and associated ConfigurationRepositoryWeb elements of the meta configuration file.
    [void] WritePartialConfiguration([string] $configName, [System.Management.Automation.PSObject] $pullServer)
    {
        $this.OpenElement('ConfigurationRepositoryWeb', $pullServer.Name)

        $this.WriteValue('ServerURL', $pullServer.ServerURL)
        $this.WriteValue('RegistrationKey', $pullServer.RegistrationKey)
        if ([ConfigScriptBuilder]::IsUnsecureConnection($pullServer.ServerURL))
        {
            $this.WriteBoolean('AllowUnsecureConnection', $true)
        }

        [string] $value = [string]::Format("@('{0}')", $configName)
        $this.WriteString('ConfigurationNames', $value)

        $this.CloseElement()

        $this.OpenElement('PartialConfiguration', $configName)

        $this.WriteValue('Description', $configName)
        $value = [string]::Format('@("[ConfigurationRepositoryWeb]{0}")', $pullServer.Name)
        $this.WriteString('ConfigurationSource', $value)
        $this.WriteValue('RefreshMode', 'PULL')

        $this.CloseElement()
    }

    # Writes ReportServerWeb element of the meta configuration file.
    [void] WriteReportServer([System.Management.Automation.PSObject] $reportServer)
    {
        $this.OpenElement('ReportServerWeb', $reportServer.Name)
        $this.WriteValue('ServerURL', $reportServer.ServerURL)
        $this.WriteValue('RegistrationKey', $reportServer.RegistrationKey)
        if ([ConfigScriptBuilder]::IsUnsecureConnection($reportServer.ServerURL))
        {
            $this.WriteBoolean('AllowUnsecureConnection', $true)
        }

        $this.CloseElement()
    }

    # Writes ResourceRepositoryWeb element of the meta configuration file.
    [void] WriteResourceServer([System.Management.Automation.PSObject] $resourceServer)
    {
        $this.OpenElement('ResourceRepositoryWeb', 'WebResourceManager')
        $this.WriteValue('ServerURL', $resourceServer.ServerURL)
        $this.WriteValue('RegistrationKey', $resourceServer.RegistrationKey)
        if ([ConfigScriptBuilder]::IsUnsecureConnection($resourceServer.ServerURL))
        {
            $this.WriteBoolean('AllowUnsecureConnection', $true)
        }

        $this.CloseElement()
    }

    [void] WriteInvokeStatement()
    {
        $this.WriteLine()
        $this.sb.Append("$($this.configurationName) -output")
        $this.sb.AppendLine(' $OutputPath')
    }
}

<#
.Synopsis
    Create as a compilation configuration script to configure the LCM to pull partial configuration(s) from the pull server(s)
.Parameter ConfigurationName
    The name to assign to the configuration.
.Parameter Destination
    The path to the directory where the script should be created.
.Parameter TestConfig
    The test configuration to use to create the script.
    See Get-TestConfiguration or ImportLinuxTestConfiguration.
.Parameter PartialConfigName1
    The name of the first partial configuration
    The script will configure this partial configuration to be pulled from the PullServer1 settings of the test configuration..
.Parameter PartialConfigName2
    The name of the second partial configuration
    The script will configure this partial configuration to be pulled from the PullServer1 settings of the test configuration.
.Parameter IncludeReportServer
    Adds ReportServerWeb settings to the configuration script
    This uses the ReportServer settings from the test configuration
.Parameter IncludeResourceServer
    Add ResourceRepositoryWeb settings the configuration script.
    This uses the ResourceServer settings from the test configuration
.Outputs
    The fully qualified path to the configuration script
#>
function New-PartialConfigPullScript
{
    [CmdletBinding()]
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $ConfigurationName,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $Destination,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [System.Management.Automation.PSObject] $TestConfig,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $PartialConfigName1,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $PartialConfigName2,

        [switch] $IncludeReportServer,

        [switch] $IncludeResourceServer
    )

    [ConfigScriptBuilder] $builder = [ConfigScriptBuilder]::new($ConfigurationName)

    $builder.WriteLine("Import-Module 'PSDesiredStateConfiguration'")

    $builder.WriteLine('[DSCLocalConfigurationManager()]')
    $builder.OpenElement('Configuration', $ConfigurationName)
    $builder.OpenElement('Node', $TestConfig.LinuxClient.Name)

    if ($null -ne $testConfig.Settings)
    {
        $builder.WriteSettings($testConfig.Settings)
    }
    $builder.WritePartialConfiguration($PartialConfigName1, $testConfig.PullServer1)

    if (-not [string]::IsNullOrEmpty($PartialConfigName2))
    {
        $builder.WritePartialConfiguration($PartialConfigName2, $testConfig.PullServer2)
    }

    if ($IncludeReportServer)
    {
        $builder.WriteReportServer($testConfig.ReportServer)
    }

    if ($IncludeResourceServer)
    {
        $builder.WriteResourceServer($testConfig.ResourceServer)
    }

    # Close the Node
    $builder.CloseElement()
    # Close the Configuration
    $builder.CloseElement()

    $builder.WriteInvokeStatement()

    $cfgScript = Join-Path -Path $Destination -ChildPath ($ConfigurationName + '.ps1')
    Set-Content -Path $cfgScript  -Value $builder.GetText()
    return $cfgScript
}

function Add-RegistrationKey
{
    param
    (
        [string] $Registrationkey,
        [string] $DscServicePath
    )
    [string] $registrationKeys = $null
    [string] $registrationKeysFile = Join-Path -Path $DscServicePath -ChildPath 'registrationkeys.txt'

    if (Test-Path -Path $registrationKeysFile -ErrorAction Ignore)
    {
        $registrationKeys = Get-Content -Path $registrationKeysFile -Raw
        if($registrationKeys.IndexOf($registrationKey, 0, [StringComparison]::OrdinalIgnoreCase) -eq -1)
        {
            [System.Text.StringBuilder] $sb = [System.Text.StringBuiler]::new()
            $null = $sb.Append($registrationKeys)
            $null = $sb.AppendLine($registrationKey)
            $registrationKeys = $sb.ToString()
        }
        else
        {
            # key is already present
            $registrationKeys = $null
        }
    }
    else
    {
        $registrationKeys = [string]::Format("{0}`n", $registrationKey)
    }

    if (-not [string]::IsNullOrEmpty($registrationKeys))
    {
        Set-Content -Path $registrationKeysFile -Value $registrationKeys
    }
}

function New-ChecksumFile
{
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $SourceFile
    )
    $fileName = Split-Path -Path $SourceFile -Leaf
    # Create the checksum file
    $checksumFile = Join-Path -Path $Env:TEMP -ChildPath ($fileName + '.checksum')
    New-DscChecksum -Path $SourceFile -OutPath $Env:TEMP -Force

    return $checksumFile
}

function Publish-File
{
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNull()]
        [string[]] $SourceFiles,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $Destination
    )
    foreach ($sourceFile in $SourceFiles)
    {
        if (-not (Test-Path -Path $sourceFile -ErrorAction SilentlyContinue))
        {
            throw "Publish-File - could not find or access the file $SourceFile"
        }
        # Create the checksum file
        $checksumFile = New-ChecksumFile -SourceFile $sourceFile
        # copy the file and it's checksum file
        Copy-Item -Path $sourceFile -Destination $Destination
        Copy-Item -Path $checksumFile -Destination $Destination
    }
}

<#
.Synopsis
    Updates a pull server with one or more MOF configuration files.
.Parameter MofFiles
    A list of one or more MOF files to deploy.
    A checksum file will be generated for each MOF file and copied with the MOF file.
.Parameter DscServicePath
    The path to the DscServer directory on the pull server.
.Example
    Deploys a MOF file to a remote DSC pull server
    Publish-Mof -MofFiles @('c:\test\mytest.mof') -DscServicePath '\\mypullserver\c$\Program Files\WindowsPowerShell\DscService'
.Example
    Deploys a MOF file to a DSC pull server configured on the local system
    Publish-Mof -MofFiles @('c:\test\mytest.mof') -DscServicePath 'c:\Program Files\WindowsPowerShell\DscService'
#>
function Publish-Mof
{
    [CmdletBinding()]
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNull()]
        [string[]] $MofFiles,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $DscServicePath
    )

    Write-Verbose -Message 'Deploying mof files to the pull server.'
    $configurationPath = Join-Path -Path $DscServicePath -ChildPath 'Configuration'
    Test-Path -Path $configurationPath

    Publish-File -SourceFiles $mofFiles -Destination $configurationPath
}

<#
.Synopsis
    Updates a resource server (or pull server) with one or more DSC resource packages

.Parameter ResourcePackages
    A list of one or more DSC resource packages to publish.
    A checksum file will be generated for each package and copied with the package.

.Parameter ModulesPath
    The path to the Modules directory on the resource server.

.Example
    Deploys a resource package to a remote DSC resource server
    Publish-Mof -MofFiles @('c:\test\mytest.mof') -ModulePath $cfg.ResourceServer.ModulesPath

.Example
    Deploys a resource package to a DSC pull server configured on the local system
    Publish-Mof -MofFiles @('c:\test\myresource.zip') -ModulePath 'c:\Program Files\WindowsPowerShell\DscService\Modules'
#>
function Publish-ResourcePackage
{
    [CmdletBinding()]
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNull()]
        [string[]] $ResourcePackages,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $ModulesPath
    )

    Write-Verbose -Message 'Deploying resource package(s) to the resource server at $ModulesPath.'
    Test-Path -Path $ModulesPath

    Publish-File -SourceFiles $ResourcePackages -Destination $ModulesPath
}

<#
.Synopsis
    Updates a pull server with a registration key,
    full or partial configuration files,
    and optional list of DSC resource packages

.Parameter PullServerCfg
    The test configuration describing the pull server to update.

.Parameter ConfigurationFiles
    The list of mof files to place in the pull server's configuration directory.
    The checksum files will be generated for each configuration file as part of the update.

.Parameter ResourcePackages
    The optional list of DSC resource module packages (zip files) to place in the pull server's modules directory.
    The checksum files will be generated for each package as part of the update.
#>
function Update-PullServer
{
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNull()]
        [System.Management.Automation.PSObject] $PullServerCfg,

        [Parameter(Mandatory)]
        [ValidateNotNull()]
        [string[]] $ConfigurationFiles,

        [string[]] $ResourcePackages
    )

    # add the registration key to the pull server's registrationkeys.txt file.
    Add-RegistrationKey -Registrationkey $PullServerCfg.RegistrationKey -DscServicePath $PullServerCfg.DscServicePath

    Publish-Mof -MofFiles $ConfigurationFiles -DscServicePath $PullServerCfg.DscServicePath

    if ($null -ne $ResourcePackages -and $ResourcePackages.Count -gt 0)
    {
        $modulesPath = Join-Path -Path $PullServerCfg.DscServicePath -ChildPath 'Modules'
        Publish-ResourcePackage -ResourcePackages $ResourcePackages -ModulesPath $modulesPath
    }
}

function Format-MofSetting
{
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $Name,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [object] $Value,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [object] $Type
    )
    [string] $result = $null
    switch ($Type)
    {
        'integer' {$result = [string]::Format(' {0} = {1:d};', $Name, $Value)}
        'string' {$result = [string]::Format(' {0} = "{1}";', $Name, $Value)}
        'value' {$result = [string]::Format(' {0} = "{1}";', $Name, $Value)}
        'boolean'
        {
            if ($Value -eq $true)
            {
                $Value = 'True'
            }
            else
            {
                $Value = 'False'
            }
            $result = [string]::Format(' {0} = {1};', $Name, $Value)
        }
    }
    return $result
}

[string[]] $script:lineSeparators = "`r`n", "`r", "`n"
<#
.Synopsis
    Updates the value of an existing setting in the MSFT_DSCMetaConfiguration section of a mof string.
.Parameter Content
    The MOf content to update.
.Parameter Name
    The name of the setting to update.
.Parameter Value
    The value to update.
.Outputs
    The updated MOF content as a string.
#>
function Update-MetaConfigurationSetting
{
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $Content,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $Name,

        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [object] $Value
    )
    [string] $type = [ConfigScriptBuilder]::GetSettingType($Name)
    if ([string]::IsNullOrEmpty($type))
    {
        throw "Update-MetaConfigurationMof - Setting name, $Name, is not supported. Verify the name or update ConfigScriptBuilder::SettingsProperties with the setting information."
    }

    [string[]] $lines = $Content.Split($script:lineSeparators, [StringSplitOptions]::None)

    # search for the MSFT_DSCMetaConfiguration instance entry
    [int] $metaConfigLine = -1
    for ($x = 0; $x -lt $lines.Length; $x++)
    {
        [string] $line = $lines[$x].Trim()
        if ($line.StartsWith('instance of MSFT_DSCMetaConfiguration'))
        {
            $metaConfigLine = $x
            break
        }
    }

    # look for the opening '{'
    [int] $insertLine = -1
    for ($x = $metaConfigLine + 1; $x -lt $lines.Length; $x++)
    {
        [string] $line = $lines[$x].Trim()
        if ($line -eq "{")
        {
            $insertLine = $x
            break;
        }
    }

    if ($metaConfigLine -eq -1 -or $insertLine -eq -1)
    {
        throw "Could not find the line containing 'instance of MSFT_DSCMetaConfiguration'"
    }

    [bool] $replaced = $false
    [string] $newline = Format-MofSetting -Name $Name -Value $Value -Type $type
    for ($x = $insertLine + 1; $x -lt $lines.Length; $x++)
    {
        [string] $line = $lines[$x].Trim()
        if ($line.StartsWith($Name, [StringComparison]::InvariantCultureIgnoreCase))
        {
            # replace the previous entry with the new one.
            $lines[$x] = $newline
            $replaced = $true
            break
        }
        if ($line -eq '}')
        {
            break
        }
    }

    $sb = [System.Text.StringBuilder]::new()
    for ($x = 0; $x -lt $lines.Length; $x++)
    {
        $line = $lines[$x]
        $null = $sb.AppendLine($line)
        # if we did not replace an existing setting, insert it after
        # the 'instance of MSFT_DSCMetaConfiguration' line.
        if (!$replaced -and $x -eq $insertLine)
        {
            $null = $sb.AppendLine($newline)
            $replaced = $true
        }
    }
    return $sb.ToString()
}

<#
.Synopsis
    Installs a Test Linux DSC Resource ZIP package to the modules directory under Program Files

.Notes
    This function should be called to install a Test Linux DSC resource, such as nxNop to enable compilation.
    Releases resources should use Install-Module.

.Parameter Path
    The path to the zip package.

.Parameter ModuleName
    The name of the module in the package.
    This value determines the name of the directory to use to unpackage the resource files.
    If the zip package includes the module's containing folder, leave this parameter empty.
#>
function Install-LinuxResource
{
    param
    (
        [Parameter(Mandatory)]
        [ValidateNotNullOrEmpty()]
        [string] $Path,

        [string] $ModuleName
    )
    if (-not (Test-Path -Path $Path))
    {
        throw "Could not find resource package $Path"
    }

    [string] $destination = Join-Path -Path $env:ProgramFiles -ChildPath 'WindowsPowerShell'
    $destination = Join-Path -Path $destination -ChildPath 'Modules'
    if (-not [string]::IsNullOrEmpty($ModuleName))
    {
        $destination = Join-Path -Path $destination -ChildPath $ModuleName
    }

    Expand-Archive -Path $Path -DestinationPath $destination -Force -ErrorAction Stop
}

# test configuration loading  functions
Export-ModuleMember -function Get-TestConfiguration
# CIM session functions
Export-ModuleMember -function CreateCimSession, Connect-Dsc
# Configuration script functions
Export-ModuleMember -function New-PartialConfigPullScript, Update-MetaConfigurationSetting
# publishing (copying) functions.
Export-ModuleMember -function Update-PullServer, Publish-Mof, Publish-ResourcePackage


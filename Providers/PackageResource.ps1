<#
.Synopsis
    Creates a .zip for a single, DSC resource built under Providers.

.Description
    This script is a prototype for packaging a resources into a zip file.
    The zip file is created in the Providers/bin directory and should be run
    from the Providers directory.
    
    The current version is for Linux only and does not support signing.

.Parameter ModuleName
    The name of the resource's containing module.
    This determines the zip file name as well as the module's manifest name.

.Parameter ResourceName
    The name of the resource; such as nxNop.
    This value determines the source directory for the resource as well as the name 
    of the resource script.

.Parameter ClassName
    The class name of the resource; such as MSFT_MyResource 

.Parameter Resources
    A hashtable of ResourceName = ClassName defining the resources to package.
    This resource name determines the source directory for the resource as well as the name 
    of the resource script.

.Parameter GitLocation
    The location of the Providers parent diretory in the git repository.
    The default value is the current location.

.Parameter x86
    Indicates the bin directory contains an x86 version of the binary.
    The default is x64.

.Example
    ./PackageResource -ModuleName nxNop -ResourceName nxNop -ClassName MSFT_nxNopResource
    Package a module containing a single resource

.Example
    $resources = 
    @{
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
    ./PackageResource -ModuleName nx -Resources $resources

    Packages a module containing multiple resources.

.Notes
    This script should be run after a successful build. It expects to find the files in the
    following locations relatiev to the root of the Providers directory
    
    Manifest: 
        ./Modules/$(ModuleName).psd1
    Binary:
        ./bin/lib$(ClassName).so

    Schema MOF:
        ./$(ResourceName)/$(ClassName).schema.mof

    Registration file:
        ./$(ResourceName)/$(ClassName).reg

    Python Scripts: 
        Scripts/2.4x-2.5x/Scripts/$(ResourceName).py
        Scripts/2.6x-2.7x/Scripts/$(ResourceName).py
        Scripts/3.x/Scripts/$(ResourceName).py

    It is assumed that the bin directory contains an x64 version of the binary.
    Use the -x86 switch for x86 binaries.
#>
[CmdletBinding()] # support -verbose
param
(
    [Parameter(Mandatory, Position=0)]
    [ValidateNotNullOrEmpty()]
    [string] $ModuleName,

    [Parameter(Mandatory, Position=1, ParameterSetName='SingleResource')]
    [ValidateNotNullOrEmpty()]
    [string] $ResourceName,

    [Parameter(Mandatory, Position=2, ParameterSetName='SingleResource')]
    [ValidateNotNullOrEmpty()]
    [string] $ClassName,

    [Parameter(Mandatory, Position=3, ParameterSetName='MultipleResources')]
    [ValidateNotNullOrEmpty()]
    [HashTable] $Resources,

    [Parameter(Position=4)]
    [string] $GitLocation = $pwd,

    [switch] $x86
)

<#
    Future: Support packaging multiple resources by changing
    the ResourceName and ClassName parameters into a single 
    hashtable of ResourceName = ClassName
#>

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

<#
    Zip package structure  $ModuleName$Version.zip

    $ModuleName/
        $ModuleName.psd1
        $ModuleName.asc  - if signed, not yet supported.
        $ModuleName.sha256sums - if signed, not yet supported.
        DSCResources/
            $ClassName/
                $ClassName.reg
                $ClassName.schema.mof
                x64/
                    lib$ClassName.so
                    Scripts/
                        2.4x-2.5x/
                            Scripts/
                                $ResourceName.py
                        2.6x-2.7x/
                            Scripts/
                                $ResourceName.py
                        3.x
                            Scripts/
                                $ResourceName.py
#>

<#
    Provides a class for managing copying DSC resource artificats from the build
    to a target Module/DSCResources/'resourcename' location.
    This is used by packaging logic to copy the parts of an individual resource
#>
class Resource
{
    # The name of the resource. Used for the $ResourceScript filename and the source code directory name.
    [string] $Name
    # The CIM class name of the resource
    [string] $ClassName
    # The fully qualified path to lib$ClassName.so binary
    [string] $BinarySource
    # The fully qualified path to resources source directory
    [string] $SourcePath
    # The fully qualified path to Provider/Scripts directory
    [string] $ScriptsSource
    [string] $ResourceScript
    # The fully qualified path to the source $ClassName.schema.mof
    [string] $SchemaSource
    # The fully qualified path to the source $ClassName.reg
    [string] $RegistrationSource
    # The name of the target binary directory, x86 or x64
    hidden [string] $BinDirName

    hidden static [string[]] $versionDirs = @(
        (Join-Path -Path '2.4x-2.5x' -ChildPath 'Scripts'),
        (Join-Path -Path '2.6x-2.7x' -ChildPath 'Scripts'),
        (Join-Path -Path '3.x' -ChildPath 'Scripts')
    )

    <#
    .Synopsis
        Initializes a new instance of this class
    .Parameter name
        The friendly name of the reosuce.
        This determines the source directory and the python script name
    .Parameter className
        The CIM class name of the resource
    .Parameter binPath 
        The path to Providers/bin directory where the resource binaries are built.
    .Parameter providersPath
        The path to the root of the Providers source tree.
    .Parameter x86
        $true if the build produced x86 binaries; otherwise, $false for x64 binaries.
    #>
    Resource([string] $name, [string] $className, [string] $binPath, [string]$providersPath, [bool] $x86)
    {
        $this.Name = $name
        $this.ClassName = $className
        if ($x86)
        {
            $this.BinDirName = 'x86'
        }
        else 
        {
            $this.BinDirName = 'x64'    
        }
        $this.SourcePath = Join-Path -Path $providersPath -ChildPath $name
        $this.SchemaSource = Join-Path -Path $this.SourcePath -ChildPath "$className.schema.mof"
        $this.RegistrationSource = Join-Path -Path $this.SourcePath -ChildPath "$className.reg"
        $this.ScriptsSource = Join-Path -Path $providersPath -ChildPath 'Scripts'
        $this.ResourceScript = "$Name.py"
        $this.BinarySource = Join-Path -Path $binPath -ChildPath "lib$className.so"
    }

    <#
    .Synopsis
        Copies a file to a target location.
    .Parameter sourceFile
        The fully qualified path of the file to copy.        
    .Parameter targetPath
        The fully qualified path to copy to.
        The path will be created if it does not exist.
    .Notes
        This method uses -ErrorAction Stop        
    #>
    static [void] CopyItem ([string] $sourceFile, [string] $targetPath)
    {
        if (-not (Test-Path -Path $TargetPath))
        {
            $null = New-Item -Path $TargetPath -ItemType Directory -ErrorAction Stop
        }
        $null = Copy-Item -Path $sourceFile -Destination $TargetPath -ErrorAction Stop
    }    

    hidden [void] CopyScripts ([string] $binRoot)
    {
        # The target root directory for scripts 
        # Example: .../$ModuleName/DSCResources/$ClassName/x64/Scripts
        [string] $scriptsRoot = Join-Path -Path $binRoot -ChildPath 'Scripts'

        foreach ($versionDir in [Resource]::versionDirs) 
        {
            [string] $scriptDir = Join-Path $this.ScriptsSource -ChildPath $versionDir

            # The fully qualified source script
            # Example: .../Providers/Scripts/3.x/$ResourceName.py
            [string] $scriptSource = Join-Path -Path $scriptDir -ChildPath $this.ResourceScript
            if (-not (Test-Path -Path $scriptSource))
            {
                Write-Warning -Message "Could not find expected resource script $scriptSource"
                continue
            }
            # The fully qualified target directory for the script
            # Example: .../$ModuleName/DSCResources/$ClassName/x64/Scripts/3.x/Scripts
            [string] $scriptDest = Join-Path -Path $scriptsRoot -ChildPath $versionDir

            [Resource]::CopyItem($scriptSource, $scriptDest)
        }
    }

    <#
    .Synopsis
        Copies the resource counts to a target DSCResources directory.
    .Parameter dscResourcePath
        The path to the target directory.
    #>
    [void] CopyResource([string] $dscResourcePath)
    {
        # Target resource directory: .../$ModuleName/DSCResources/$ClassName
        [string] $resourceRoot = Join-Path -Path $dscResourcePath -ChildPath $this.ClassName

         # Target resource bin directory: .../$ModuleName/DSCResources/$ClassName/x64
        [string] $binRoot = Join-Path -Path $resourceRoot -ChildPath $this.BinDirName

        [Resource]::CopyItem($this.BinarySource, $binRoot)
        [Resource]::CopyItem($this.RegistrationSource, $resourceRoot)
        [Resource]::CopyItem($this.SchemaSource, $resourceRoot)
        
        $this.CopyScripts($binRoot)

    }
}

[string] $script:binPath = Join-Path -Path $GitLocation -ChildPath 'bin'
[string] $script:scriptSrc = Join-Path -Path $GitLocation -ChildPath 'Scripts'
[string] $script:moduleSrc = Join-Path -Path $GitLocation -ChildPath 'Modules'
[string] $script:manifestFile = Join-Path $script:moduleSrc -ChildPath "$ModuleName.psd1"

$script:Paths = @(
    $script:binPath,
    $script:scriptSrc
    $script:moduleSrc,
    $script:manifestFile
)

<#
.Synopsis
    Verify the expected content for the resource exists
.Outputs
    $true if the expected content is present; otherwise, $false.
#>    
function Test-ExpectedItems
{
    param
    (
        [string[]] $items
    )
    Write-Verbose -Message 'Verifying resource content'
    [bool] $success = $true

    foreach ($item in $items)
    {
        if (-not (Test-Path -Path $item -ErrorAction SilentlyContinue))
        {
            Write-Warning -Message "Could not find $item"
            $success = false
        }
    }

    return $success
}

if (-not $IsLinux)
{
    Write-Error -Message "This script must be run on a Linux system in the Providers source directory."
    return
}

if (-not (Test-ExpectedItems -items $script:Paths))
{
    Write-Error -Message @"

    Some of the resource content was not found.
    This script must be run on a Linux system in the Providers source directory after
    a completing a successful build.
"@
    return
}

#
# Verify the manifest and extract the version
#
$manifest = Test-ModuleManifest -Path $script:manifestFile -ErrorAction Stop
[string] $Version = $manifest.Version

[string] $moduleVersionName = [string]::Format("{0}_{1}", $ModuleName, $Version)
[string] $outputPath = Join-Path -Path '/tmp' -ChildPath $moduleVersionName
[bool] $isX86 = ($PSBoundParameters.ContainsKey('x86')) -and ($x86 -eq $true)
[string] $providersPath = $pwd

#
# Build the set of resources to include in the package
#
$resourceList = [System.Collections.Generic.List[Resource]]::new()
if ($PSBoundParameters.ContainsKey('Resources'))
{
    foreach ($key in $Resources.Keys)
    {
        [string] $value = $Resources[$key]
        $item = [Resource]::new($key, $value, $script:binPath, $providersPath, $x86);
        $null = $resourceList.Add($item)
    }
}
else 
{
    $item = [Resource]::new($ResourceName, $ClassName, $script:binPath, $providersPath, $x86) 
    $null = $resourceList.Add($item)
}


# Create the output directory
if (Test-Path -Path $outputPath)
{
    Remove-Item -Path $outputPath -Force -Recurse
}
$null = New-Item -Path $outputPath -ItemType Directory

######################
Write-Verbose -Message 'Copying resource(s) content'
######################
[string] $moduleRoot = Join-Path -Path $outputPath -ChildPath $ModuleName

# Copy the manifest
[Resource]::CopyItem($script:manifestFile, $moduleRoot)

# Copy the resource(s)
$dscResources = Join-Path -Path $moduleRoot -ChildPath 'DSCResources'

# NOTE: 
foreach ($resource in $resourceList)
{
    $resource.CopyResource($dscResources)
}

######################
Write-Verbose -Message 'Creating package file: $zipFile'
######################

$zipFile = Join-Path $script:binPath -ChildPath ($moduleVersionName + '.zip')
if (Test-Path $zipFile)
{
    Remove-Item -Path $zipFile -Force -ErrorAction Stop
}

# NOTE: run from the output path to ensure the zip file contains
# just the module folder and it's contents.
Push-Location -Path $outputPath
Compress-Archive -Path ./* -DestinationPath $zipFile 
New-DscChecksum -Path $zipFile -Force
Pop-Location

if (Test-Path $zipFile)
{
    return Get-Item -Path $zipFile
}
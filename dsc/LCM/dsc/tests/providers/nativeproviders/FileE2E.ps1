function WhatifInvoke
(
        [CimInstance][Parameter(Mandatory=$true)]$inputResource
)
{
    Set-FileDirectory $inputResource -whatif
    if($? -eq $false)
    {
        echo $Error[0] >>result.txt
    }
}

function TryInvoke
(
        [CimInstance][Parameter(Mandatory=$true)]$inputResource,
        [bool][Parameter(Mandatory=$true)]$expectedResult
)
{
    Set-FileDirectory $inputResource 
    if($expectedResult -eq $true)
    {
        if($? -eq $false)
        {
            echo $Error[0] >>result.txt
        }
    }
    if($expectedResult -eq $false)
    {
        if($? -eq $true)
        {
            echo "should not succeed" >>result.txt
        }
    }
}



import-module .\SetFileDirectory.cdxml
.\FileUnitTestCleanup.ps1
mkdir fileunitestdata
cd fileunitestdata
[System.IO.Directory]::SetCurrentDirectory($pwd);

#the following cases will cover the "whatif" scenario for 
mkdir dir
$destinationPath = $pwd.Path+"\dir"
$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\dir"; ensure="absent"; Type="Directory"} -Key DestinationPath
WhatifInvoke $inputResource

echo ""> file.txt
$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\file.txt"; ensure="absent"; Type="File"} -Key DestinationPath
WhatifInvoke $inputResource

$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\copyingfromsource.txt"; sourcepath=$pwd.Path+ "\file.txt"; ensure="Present"; Type="File"} -Key DestinationPath
WhatifInvoke $inputResource

$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\not_existdir"; ensure="Absent"; Type="Directory"} -Key DestinationPath
WhatifInvoke $inputResource

mkdir existing_dir
$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\existing_dir"; ensure="Present"; Type="Directory"; attributes=@('hidden')} -Key DestinationPath
WhatifInvoke $inputResource

$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\existing_dir"; ensure="present"; Type="Directory"; attributes=@('hidden')} -Key DestinationPath
TryInvoke $inputResource $true

$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\existing_dir"; ensure="Present"; Type="Directory"; attributes=@('hidden'); sourcepath="C:\*.txt"} -Key DestinationPath
TryInvoke $inputResource $false

echo "">singlefile.txt
$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\existing_dir"; ensure="Present"; Type="Directory"; attributes=@('hidden'); sourcepath=$pwd.Path+"\singlefile.txt"} -Key DestinationPath
TryInvoke $inputResource $false


$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\filefromcontent.txt"; contents=""; ensure="Present"; Type="File"} -Key DestinationPath
WhatifInvoke $inputResource

echo "">filenosource.txt
$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\filenosource.txt"; ensure="present"; Type="File"; Checksum="None"} -Key DestinationPath
TryInvoke $inputResource $true


$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath=$pwd.Path+"\filenosource.txt"; ensure="present"; attributes=@('notsupport')} -Key DestinationPath
TryInvoke $inputResource $false

$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath="%SystemRoot%\System32\Configuration\Schema"; recurse=$false; Type="Directory"; ensure="Present"} -Key DestinationPath
TryInvoke $inputResource $true

# Positive Test Case to validate that Environment Variables can be used in DestinationPath parameter.
$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{DestinationPath="%SystemRoot%\System32\Configuration\Schema"; recurse=$false; Type="Directory"; ensure="Present"} -Key DestinationPath
TryInvoke $inputResource $true

# Positive Test Case to validate that Environment Variables can be used in SourePath parameter.
$inputResource = New-CimInstance -Local -Namespace ROOT/microsoft/windows/desiredstateconfiguration -ClassName MSFT_FileDirectoryConfiguration -Property @{SourcePath="%SystemRoot%\System32\Configuration\Schema"; DestinationPath="%SystemRoot%\System32\Configuration\Schema"; recurse=$false; Type="Directory"; ensure="Present"} -Key DestinationPath
TryInvoke $inputResource $true


cd ..
[System.IO.Directory]::SetCurrentDirectory($pwd);
function VerifyProperties
(
    [string][Parameter(Mandatory=$true)]$fileName
)
{
    if(Test-Path $fileName)
    {
        $fileinfo = Get-Item $fileName -Force
        if(-not $fileinfo.Attributes.ToString().Contains("ReadOnly"))
        {
            echo "$fileName attributes mismatch" >> $resultfile
        }
    }
    else
    {
        echo "$fileName not exists" >> $resultfile
    }
}


function VerifySingleFile
(
    [string][Parameter(Mandatory=$true)]$fileName,
    [string][Parameter(Mandatory=$true)]$content
)
{
    if(Test-Path $fileName)
    {
        if($content -eq $desiredcontents)
        {
            $str =$null
            $str = [System.IO.File]::ReadAllText($fileName)
            if($str -eq $null -or $str -ne $content)
            {
                echo "$fileName content mismatch" >> $resultfile
            }
        }
        else
        {
            if((Get-Item $fileName).Length -ne 0)
            {
                echo "$fileName is not empty" >> $resultfile
            }
        }
    }
    else
    {
        echo "$fileName not exists" >> $resultfile
    }

    VerifyProperties $fileName
}

function VerifyAbsent
(
    [string][Parameter(Mandatory=$true)]$fileName,
    [bool][Parameter(Mandatory=$true)]$existing
)
{
    if((Test-Path $fileName) -ne $existing)
    {
        echo "$fileName different!" >> $resultfile
    }

}

cd fileunitestdata
[System.IO.Directory]::SetCurrentDirectory($pwd);

$singledestfilecontentmismatch= "singledestfilecontentmismatch.txt"
$singledestfileattributesmismatch= "singledestfileattributesmismatch.txt"
$singledestfileSourcemismatch="singledestfileSourcemismatch.txt"
$emptyFile="emptyFile.txt"

$singledestfileoriginallynotexistcontent= "singledestfileoriginallynotexistcontent.txt"
$singledestfileoriginallynotexistsource= "test\test\test\test\test\singledestfileoriginallynotexistsource.txt"

$singledestdirname="singledestdirname"
$singledestdiroriginallynotexist="singledestdiroriginallynotexist"


$singlesource="singlesource.txt"
$singlesourcedirname="singlesourcedirname"
$desiredcontents="1"
$emptycontent = "empty"

$DestDirForAbsent="DestDirForAbsent"
$DestFileForAbsent="DestFileForAbsent.txt"
$DestDirNotEmptyForceTrue="DestDirNotEmptyForceTrue"
$DestDirNotEmptyForceFALSE="DestDirNotEmptyForceFALSE"


$DestDirEnsureFileContentForce = "DestDirEnsureFileContentForce";
$DestFileParentNotExistContent= "notexist\notexst2\..\DestFileParentNotExistContent";
$DestFileEnsureDirForce = "DestFileEnsureDirForce";
$DestDirParentNotExistForSet= "notexist\notexst2\..\DestDirParentNotExistForSet";


$content="1"
$resultfile = "result.txt"

if(Test-Path $resultfile)
{
    del $resultfile -Force 
}


VerifySingleFile $singledestfilecontentmismatch $content
VerifySingleFile $singledestfileattributesmismatch $content
VerifySingleFile $singledestfileSourcemismatch $content
VerifySingleFile $emptyFile $emptycontent
VerifySingleFile $singledestfileoriginallynotexistcontent $content
VerifySingleFile $singledestfileoriginallynotexistsource $content
VerifySingleFile $DestDirEnsureFileContentForce  $content
VerifySingleFile $DestFileParentNotExistContent $content

VerifyProperties $singledestdirname
VerifyProperties $singledestdiroriginallynotexist
VerifyProperties $DestFileEnsureDirForce
VerifyProperties $DestDirParentNotExistForSet

VerifyAbsent $DestDirForAbsent $false
VerifyAbsent $DestFileForAbsent $false
VerifyAbsent $DestDirNotEmptyForceTrue $false
VerifyAbsent $DestDirNotEmptyForceFALSE $true

#recursive set
$RDestdirForSet = "RDestdirForSet"
VerifyProperties $RDestdirForSet
VerifyProperties $RDestdirForSet"\dir1"
VerifyProperties $RDestdirForSet"\dir2"
VerifyProperties $RDestdirForSet"\dir3"
VerifyProperties $RDestdirForSet"\dir4"

VerifySingleFile $RDestdirForSet"\dir2\file.txt" $content
VerifySingleFile $RDestdirForSet"\file1.txt" $content
VerifySingleFile $RDestdirForSet"\file2.txt" $content


cd ..
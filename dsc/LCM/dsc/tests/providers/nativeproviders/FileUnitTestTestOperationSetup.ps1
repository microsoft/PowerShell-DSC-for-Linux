param(
     [switch][Parameter(Mandatory=$false, Position=0)]$keepcache=$false
)



function SetSingleFileDir
(
        [string][Parameter(Mandatory=$true)]$sourcefileName,
        [string][Parameter(Mandatory=$true)]$destfileName
)
{
#add readonly attribute
attrib +R $sourcefileName
attrib +S $sourcefileName

#add some acl (security descriptor)
$colRights = [System.Security.AccessControl.FileSystemRights]"Read, Write" 

$InheritanceFlag = [System.Security.AccessControl.InheritanceFlags]::None 
$PropagationFlag = [System.Security.AccessControl.PropagationFlags]::None 


$objType =[System.Security.AccessControl.AccessControlType]::Deny 

$objUser = New-Object System.Security.Principal.NTAccount("guests") 

$objACE = New-Object System.Security.AccessControl.FileSystemAccessRule ($objUser, $colRights, $InheritanceFlag, $PropagationFlag, $objType) 

$objACL = Get-ACL $sourcefileName 
$objACL.AddAccessRule($objACE) 

Set-ACL $sourcefileName $objACL

copy $sourcefileName $destfileName

attrib +R $destfileName
attrib +S $destfileName


$fileinfo = Get-Item $destfileName 

$attributes = $fileinfo.Attributes.ToString().Split(', ', [System.StringSplitOptions]::RemoveEmptyEntries)
foreach($attribute in $attributes)
{
    #"Directory" is not settable
    if($attribute -ne "Directory")
    {
        [System.IO.File]::AppendAllText("properties.txt", $attribute + " ",[System.Text.Encoding]::ASCII);
    }
}
[System.IO.File]::AppendAllText("properties.txt", [System.Environment]::NewLine,[System.Text.Encoding]::ASCII);

$securitydescriptor = (get-acl $destfileName).Sddl
[System.IO.File]::AppendAllText("properties.txt", $securitydescriptor,[System.Text.Encoding]::ASCII);
[System.IO.File]::AppendAllText("properties.txt", [System.Environment]::NewLine,[System.Text.Encoding]::ASCII);


}


.\FileUnitTestCleanup.ps1 $keepcache
mkdir fileunitestdata
cd fileunitestdata
[System.IO.Directory]::SetCurrentDirectory($pwd);

$singledestfilewithbom= "singledestfilewithbom" +".txt"
$singledestfilewithoutbom = "singledestfilewithoutbom" +".txt"
$singlesourcewithbom="singlesourcewithbom" +".txt"
$singlesourcewithoutbom="singlesourcewithoutbom" +".txt"
$singledestdirname="singledestdirname";
$singlesourcedirname="singlesourcedirname";
$content="1"

#single object case
#create the file
[System.IO.File]::WriteAllText($singlesourcewithbom, $content, [System.Text.Encoding]::UTF8);
[System.IO.File]::WriteAllText($singlesourcewithoutbom, $content);


SetSingleFileDir $singlesourcewithbom $singledestfilewithbom
SetSingleFileDir $singlesourcewithoutbom $singledestfilewithoutbom


#create the dir
mkdir $singlesourcedirname

SetSingleFileDir $singlesourcedirname $singledestdirname

copy $singlesourcewithbom $singledestdirname

#recursive object case
$Rsourcedir = "Rsourcedir"
mkdir $Rsourcedir
mkdir $Rsourcedir"\dir1"
mkdir $Rsourcedir"\dir2"
[System.IO.File]::WriteAllText($Rsourcedir+"\dir2\file.txt", $content, [System.Text.Encoding]::UTF8);
 attrib +R +S +H $Rsourcedir
(dir -recurse $Rsourcedir)|ForEach-Object{  attrib +R +S +H $_.FullName}

$RDestdirIdentical = "RDestdirIdentical"
copy $Rsourcedir $RDestdirIdentical -Recurse
 attrib +R +S +H $RDestdirIdentical
 (dir -recurse $RDestdirIdentical)|ForEach-Object{  attrib +R +S +H $_.FullName}

$RDestdirMissingFile = "RDestdirMissingFile"
copy $Rsourcedir $RDestdirMissingFile -Recurse
 attrib +R +S +H $RDestdirMissingFile
(dir -recurse $RDestdirMissingFile)|ForEach-Object{  attrib +R +S +H $_.FullName}
del $RDestdirMissingFile"\dir2\file.txt" -Force

$RDestdirMoreFile = "RDestdirMoreFile"
copy $Rsourcedir $RDestdirMoreFile -Recurse
 attrib +R +S +H $RDestdirMoreFile
(dir -recurse $RDestdirMoreFile)|ForEach-Object{  attrib +R +S +H $_.FullName}
[System.IO.File]::WriteAllText($RDestdirMoreFile+"\dir1\file.txt", $content, [System.Text.Encoding]::UTF8);
attrib +R +S +H $RDestdirMoreFile"\dir1\file.txt"

$RDestdirMissingSubdir = "RDestdirMissingSubdir"
copy $Rsourcedir $RDestdirMissingSubdir -Recurse
 attrib +R +S +H $RDestdirMissingSubdir
(dir -recurse $RDestdirMissingSubdir)|ForEach-Object{  attrib +R +S +H $_.FullName}
del $RDestdirMissingSubdir"\dir1" -Force

$RDestdirMoreSubdir = "RDestdirMoreSubdir"
copy $Rsourcedir $RDestdirMoreSubdir -Recurse
 attrib +R +S +H $RDestdirMoreSubdir
(dir -recurse $RDestdirMoreSubdir)|ForEach-Object{  attrib +R +S +H $_.FullName}
mkdir $RDestdirMoreSubdir"\dir3"
attrib +R +S +H $RDestdirMoreSubdir"\dir3"

$RDestdirFileContentMismatch = "RDestdirFileContentMismatch"
copy $Rsourcedir $RDestdirFileContentMismatch -Recurse
 attrib +R +S +H $RDestdirFileContentMismatch 
(dir -recurse $RDestdirFileContentMismatch)|ForEach-Object{  attrib +R +S +H $_.FullName}
attrib -R -S -H $RDestdirFileContentMismatch"\dir2\file.txt"
echo "notmatch">> $RDestdirFileContentMismatch"\dir2\file.txt" 
attrib +R +S +H $RDestdirFileContentMismatch"\dir2\file.txt"

$RDestDirsubFileAttributeMismatch = "RDestDirsubFileAttributeMismatch"
copy $Rsourcedir $RDestDirsubFileAttributeMismatch -Recurse
 attrib +R +S +H $RDestDirsubFileAttributeMismatch
(dir -recurse $RDestDirsubFileAttributeMismatch)|ForEach-Object{  attrib +R +S +H $_.FullName}
attrib -R -S -H $RDestDirsubFileAttributeMismatch"\dir2\file.txt"

$RDestDirSubdirAttributeMismatch = "RDestDirSubdirAttributeMismatch"
copy $Rsourcedir $RDestDirSubdirAttributeMismatch -Recurse
 attrib +R +S +H $RDestDirSubdirAttributeMismatch
(dir -recurse $RDestDirSubdirAttributeMismatch)|ForEach-Object{  attrib +R +S +H $_.FullName}
attrib -R -S -H $RDestDirSubdirAttributeMismatch"\dir2"

$RDestDirExpectSubdirButFile = "RDestDirExpectSubdirButFile"
copy $Rsourcedir $RDestDirExpectSubdirButFile -Recurse
 attrib +R +S +H $RDestDirExpectSubdirButFile
(dir -recurse $RDestDirExpectSubdirButFile)|ForEach-Object{  attrib +R +S +H $_.FullName}
rmdir $RDestDirExpectSubdirButFile"\dir1" -Force
echo "content" >> $RDestDirExpectSubdirButFile"\dir1"
attrib +R +S +H $RDestDirExpectSubdirButFile"\dir1"


$RDestDirExpectFileButSubDir = "RDestDirExpectFileButSubDir"
copy $Rsourcedir $RDestDirExpectFileButSubDir -Recurse
 attrib +R +S +H $RDestDirExpectFileButSubDir
(dir -recurse $RDestDirExpectFileButSubDir)|ForEach-Object{  attrib +R +S +H $_.FullName}
del $RDestDirExpectFileButSubDir"\dir2\file.txt" -force
mkdir $RDestDirExpectFileButSubDir"\dir2\file.txt" 
attrib +R +S +H $RDestDirExpectFileButSubDir"\dir2\file.txt"



cd ..
[System.IO.Directory]::SetCurrentDirectory($pwd);
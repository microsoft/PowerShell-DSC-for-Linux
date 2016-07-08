param(
     [switch][Parameter(Mandatory=$false, Position=0)]$keepcache=$false
)

.\FileUnitTestCleanup.ps1 $keepcache
mkdir fileunitestdata
cd fileunitestdata
[System.IO.Directory]::SetCurrentDirectory($pwd);

$singledestfilecontentmismatch= "singledestfilecontentmismatch.txt"
$singledestfileattributesmismatch= "singledestfileattributesmismatch.txt"
$singledestfileSourcemismatch="singledestfileSourcemismatch.txt"
$emptyFile="emptyFile.txt"

$singlesource="singlesource.txt"
$singledestdirname="singledestdirname"
$singlesourcedirname="singlesourcedirname"
$content="1"

$DestDirForAbsent="DestDirForAbsent"
$DestFileForAbsent="DestFileForAbsent.txt"

$DestDirNotEmptyForceTrue="DestDirNotEmptyForceTrue"
$DestDirNotEmptyForceFALSE="DestDirNotEmptyForceFALSE"

$DestDirEnsureFileContentForce = "DestDirEnsureFileContentForce";
$DestFileEnsureDirForce = "DestFileEnsureDirForce";

$DestFileEnsureDirForce = "DestFileEnsureDirForce";


[System.IO.File]::WriteAllText($singlesource, $content, [System.Text.Encoding]::UTF8);
[System.IO.File]::WriteAllText($singledestfilecontentmismatch, "notmatch", [System.Text.Encoding]::UTF8);
[System.IO.File]::WriteAllText($emptyFile, "notmatch", [System.Text.Encoding]::UTF8); #should be empty after set
[System.IO.File]::WriteAllText($singledestfileattributesmismatch, $content, [System.Text.Encoding]::UTF8);
[System.IO.File]::WriteAllText($singledestfileSourcemismatch, "notmatch", [System.Text.Encoding]::UTF8);

attrib +r $singlesource
attrib +r $singledestfilecontentmismatch
attrib +r $singledestfileSourcemismatch
attrib +r $emptyFile
attrib +r $singledestfileattributesmismatch


#create the dir
mkdir $singlesourcedirname
mkdir $singledestdirname

mkdir $DestDirForAbsent


mkdir $DestDirNotEmptyForceTrue
mkdir $DestDirNotEmptyForceTrue"\dir1"
mkdir $DestDirNotEmptyForceFALSE
mkdir $DestDirNotEmptyForceFALSE"\dir1"

echo $content > $DestFileForAbsent

mkdir $DestDirEnsureFileContentForce 
echo $content > $DestFileEnsureDirForce 


#recursive cases
$Rsourcedir = "Rsourcedir"
mkdir $Rsourcedir
mkdir $Rsourcedir"\dir1"
mkdir $Rsourcedir"\dir2"
mkdir $Rsourcedir"\dir3"
mkdir $Rsourcedir"\dir4"
[System.IO.File]::WriteAllText($Rsourcedir+"\dir2\file.txt", $content, [System.Text.Encoding]::UTF8);
[System.IO.File]::WriteAllText($Rsourcedir+"\file1.txt", $content, [System.Text.Encoding]::UTF8);
[System.IO.File]::WriteAllText($Rsourcedir+"\file2.txt", $content, [System.Text.Encoding]::UTF8);
 attrib +R +S +H $Rsourcedir
(dir -recurse $Rsourcedir)|ForEach-Object{  attrib +R +S +H $_.FullName}

$RDestdirForSet = "RDestdirForSet"
copy $Rsourcedir $RDestdirForSet -Recurse
attrib +R +S +H $RDestdirForSet
(dir -recurse $RDestdirForSet)|ForEach-Object{  attrib +R +S +H $_.FullName}
#missing one file
del $RDestdirForSet"\file1.txt" -Force
#one more file
[System.IO.File]::WriteAllText($RDestdirForSet+"\dir1\file.txt", $content, [System.Text.Encoding]::UTF8);
#missing subdir
del $RDestdirForSet"\dir4" -Force
#one more dir
mkdir $RDestdirForSet"\dir5"
#content and attribute mismatch
attrib -R -S -H $RDestdirForSet"\dir2\file.txt"
echo "notmatch">> $RDestdirForSet"\dir2\file.txt" 
#subdir attribute mismatch
attrib -R -S -H $RDestdirForSet"\dir2"
#expecting dir but actually a file
rmdir $RDestdirForSet"\dir3" -Force
echo "content" >> $RDestdirForSet"\dir3"
attrib +R +S +H $RDestdirForSet"\dir3"
#expecting a file but a dir
del $RDestdirForSet"\file2.txt" -force
mkdir $RDestdirForSet"\file2.txt" 
attrib +R +S +H $RDestdirForSet"\file2.txt"


cd ..
[System.IO.Directory]::SetCurrentDirectory($pwd);

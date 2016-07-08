.\FileUnitTestCleanup.ps1
mkdir fileunitestdata
cd fileunitestdata

$guid=[System.Guid]::NewGuid()
$singledestfilename = "singledestfilename" +$guid  +".txt"
$destdirname="destdirname" +$guid ;

#create the file
echo "1" >$singledestfilename

#add readonly attribute
attrib +R $singledestfilename


#create the local dir
mkdir $destdirname
attrib +r $destdirname
mkdir $destdirname"\dir1"
attrib +R $destdirname"\dir1"
mkdir $destdirname"\dir2"
attrib +R $destdirname"\dir2"
copy $singledestfilename $destdirname"\dir2"

$sharename = "recursivegetshare"
#prepare the share
mkdir $sharename
copy $destdirname $sharename -Recurse
cd $sharename
#share the folder
net share recursivegetshare /delete
net share "recursivegetshare=$pwd"

cd ..
cd ..
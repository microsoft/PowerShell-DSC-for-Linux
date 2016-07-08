.\FileUnitTestCleanup.ps1
mkdir fileunitestdata
cd fileunitestdata

$guid=[System.Guid]::NewGuid()
$singledestfilename = "singledestfilename" +$guid +".txt"
$singledestdirname="singledestdirname" + $guid;
$singlesourcefilename="singlesourcefilename" +$guid +".txt"
$singlesourcedirname="singlesourcedirname" + $guid;

#create the file
echo "1" >$singledestfilename

#add readonly attribute
attrib +R $singledestfilename


#create the dir
mkdir $singledestdirname
attrib +r $singledestdirname


cd ..
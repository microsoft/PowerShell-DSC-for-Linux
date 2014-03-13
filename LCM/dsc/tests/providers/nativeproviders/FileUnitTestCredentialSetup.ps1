param(
     [switch][Parameter(Mandatory=$false, Position=0)]$keepcache=$false
)

    .\FileUnitTestCredentialCleanup.ps1 $keepcache

    #set up the user
    $computer="localhost"
    $user = "paxnj"
    $password = "123456Q(("
  

    $objOu = [ADSI]"WinNT://$computer"
    $objUser = $objOU.Create("User", $user)
    $objUser.setpassword($password)
    $objUser.SetInfo()
    $objUser.description = "Test user"
    $objUser.SetInfo()

    #create the folder
    mkdir fileunitestdata
    cd fileunitestdata
    mkdir credentialshare
    cd credentialshare
    [System.IO.Directory]::SetCurrentDirectory($pwd);

    #share the folder
    $NSCMD = "credentialshare=$pwd"
    $nscmd
    $ComputerName = (Get-WmiObject -Class Win32_ComputerSystem).Name
    net share $NSCMD  "/grant:$ComputerName\paxnj,read"
    
    if(test-path \\localhost\credentialshare -ErrorAction Ignore)
    {
        throw "should not be able to access the share"
    }

    #create the file
    echo "1" >> 1.txt
    mkdir dir1

    cd ..
    echo "2" >> singlefileDest.txt
    cd ..
    [System.IO.Directory]::SetCurrentDirectory($pwd);

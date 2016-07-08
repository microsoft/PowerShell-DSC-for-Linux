param(
     [switch][Parameter(Mandatory=$false, Position=0)]$keepcache=$false
)

#delete the share
net share credentialshare /delete

#delete the folder
.\FileUnitTestCleanup.ps1  $keepcache
#delete the user

$computer="localhost"
$user = "paxnj"

      

$objOu = [ADSI]"WinNT://$computer"
$objOu.delete("user", $user)

currentuser=$(id -u -n)
echo $currentuser
export HOME="/home/$currentuser"


/usr/bin/inspec exec $1/$2 --reporter=json-min:$3



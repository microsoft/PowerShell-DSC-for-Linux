#!/bin/bash

cleanup_and_exit()
{
    echo $tmpdir | grep "/tmp/"
    if [ $? -ne 0 ]; then 
	echo "Error: tmpdir ($tmpdir) is invalid."
	exit 1
    fi
    rm -rf $tmpdir
    exit $1
}

if [ -d ./release ]; then
    echo "Error: Please run make clean before running this script."
    exit 1
fi

printf "Making temporary directory..."
tmpdir=`mktemp -d`
if [ $? -ne 0 ]; then
    echo "Error: Unable to create temp directory in /tmp"
    exit 1
fi
echo " $tmpdir/dsc."
mkdir -p $tmpdir/dsc
echo "Copying current directory to $tmpdir/dsc."
cp -R ./* $tmpdir/dsc
cd $tmpdir/dsc

echo `pwd` | grep "/tmp/"
if [ $? -ne 0 ]; then
    echo "Error: Unable to change directory to $tmpdir/dsc"
    cleanup_and_exit 1
fi

echo "Removing unwanted files."
# Remove omi symlink
if [ -h ./omi-1.0.8 ]; then
    rm omi-1.0.8
fi

# Remove unwanted base directories
rm -rf ./bootstrap ./build ./build_source_kit.sh ./doc ./ext ./installbuilder ./Test ./Docs

# Remove blue win7 win8
rm -rf ./LCM/codec/mof/blue ./LCM/codec/mof/win7 ./LCM/codec/mof/win8

# Remove tests
rm -rf ./LCM/dsc/tests

# Remove cs files
rm -rf ./LCM/dsc/engine/ca/psinfrastructure/PsPluginManager.cs

# Remove module providers
rm -rf ./Providers/nxMySqlDatabase ./Providers/nxMySqlGrant ./Providers/nxMySqlUser

rm -rf \
./Providers/Scripts/2.4x-2.5x/Scripts/nxMySqlDatabase.py \
./Providers/Scripts/2.4x-2.5x/Scripts/nxMySqlGrant.py \
./Providers/Scripts/2.4x-2.5x/Scripts/nxMySqlUser.py \
./Providers/Scripts/2.6x-2.7x/Scripts/nxMySqlDatabase.py \
./Providers/Scripts/2.6x-2.7x/Scripts/nxMySqlGrant.py \
./Providers/Scripts/2.6x-2.7x/Scripts/nxMySqlUser.py \
./Providers/Scripts/3.x/Scripts/nxMySqlDatabase.py \
./Providers/Scripts/3.x/Scripts/nxMySqlGrant.py \
./Providers/Scripts/3.x/Scripts/nxMySqlUser.py

# sed out Makefile stuff for Providers removed
cat ./Providers/Makefile \
    | sed "s@PROVIDERS+=nxMySqlDatabase@#PROVIDERS+=nxMySqlDatabase@" \
    | sed "s@PROVIDERS+=nxMySqlGrant@#PROVIDERS+=nxMySqlGrant@" \
    | sed "s@PROVIDERS+=nxMySqlUser@#PROVIDERS+=nxMySqlUser@" \
    > ./tmp_makefile
mv -f ./tmp_makefile ./Providers/Makefile

# Remove tests associated with above providers
rm -rf ./Providers/Scripts/2.4x-2.5x/Scripts/Tests ./Providers/Scripts/2.6x-2.7x/Scripts/Tests ./Providers/Scripts/3.x/Scripts/Tests

# add "BUILD_LOCAL=1" to configure
sed '2 aBUILD_LOCAL=1' ./configure > ./tmp_configure
mv -f ./tmp_configure ./configure
chmod +x ./configure

# Remove stuff from Providers/Extras
rm -rf ./Providers/Extras/Config* ./Providers/Extras/Exampl* ./Providers/Extras/Provider* ./Providers/Extras/Scripts/*.ps1 ./Providers/Extras/Threat* ./Providers/Extras/Window*

rm -f `find . -name "*~"`
rm -f `find . -name .tpattributes`

cd ..
tar --numeric-owner -c -z -f /tmp/PSDSC.tar.gz ./dsc
if [ $? -eq 0 ]; then
    echo "Created tarball at /tmp/PSDSC.tar.gz"
else
    echo "Error: Unable to create tarball."
    exit 1
fi
cleanup_and_exit 0

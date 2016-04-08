#!/bin/sh

if [ -z "$1" ]; then
    echo "Usage:"
    echo "   $0 PUBLIC_GPG_KEY"
    exit 1
fi

if [ -z "$2" ]; then
    KEYRING_NAME="keyring.gpg"
else
    KEYRING_NAME=$2
fi

DSC_ETC_DIR=<CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC>
HOME=$DSC_ETC_DIR gpg --no-default-keyring  --keyring $DSC_ETC_DIR/$KEYRING_NAME --import $1
RETVAL=$?

if [ "<CONFIG_SYSCONFDIR_DSC>" = "omsagent" ]; then
    if [ `id -u` = 0 ] ; then
        chown omsagent $DSC_ETC_DIR/$KEYRING_NAME
    fi
fi

exit $RETVAL

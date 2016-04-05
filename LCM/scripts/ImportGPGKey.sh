#!/bin/sh

if [ -z "$1" ]; then
    echo "Usage:"
    echo "   $0 PUBLIC_GPG_KEY"
    exit 1
fi

DSC_ETC_DIR=<CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC>
HOME=$DSC_ETC_DIR gpg --no-default-keyring  --keyring $DSC_ETC_DIR/keyring.gpg --import $1
RETVAL=$?

if [ "<CONFIG_SYSCONFDIR_DSC>" = "omsagent" ]; then
    chown omsagent $DSC_ETC_DIR/keyring.gpg
else
    chown root $DSC_ETC_DIR/keyring.gpg
fi

exit $RETVAL

#!/bin/sh

if [ -z "$1" ]; then
    echo "Usage:"
    echo "   $0 PUBLIC_GPG_KEY"
    exit 1
fi

HOME=<CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC> gpg --no-default-keyring  --keyring <CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC>/keyring.gpg --import $1
RETVAL=$?

if [ "<CONFIG_SYSCONFDIR_DSC>" = "omsagent" ]; then
    chown omsagent <CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC>/keyring.gpg
else
    chown root <CONFIG_SYSCONFDIR>/<CONFIG_SYSCONFDIR_DSC>/keyring.gpg
fi

exit $RETVAL

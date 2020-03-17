#!/bin/sh
if [ ! -f /etc/opt/omi/conf/dsc/configuration/schema/MSFT_nxFileResource/MSFT_nxFileResource.schema.mof -o ! -f /opt/microsoft/dsc/Scripts/2.6x-2.7x/Scripts/nxFile.py -o ! -f /opt/omi/lib/libMSFT_nxFileResource.so ]; then
    /opt/microsoft/dsc/Scripts/InstallModule.py /opt/microsoft/dsc/module_packages/nx_1.0.zip 0
fi
exit 0

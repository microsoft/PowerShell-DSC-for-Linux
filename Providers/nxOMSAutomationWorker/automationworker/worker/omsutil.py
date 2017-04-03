#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

from optparse import OptionParser
import sys
import os
import pwd
import grp
import subprocess

import configuration
import serializerfactory

json = serializerfactory.get_serializer(sys.version_info)
configuration.clear_config()
configuration.set_config({configuration.PROXY_CONFIGURATION_PATH: "/etc/opt/microsoft/omsagent/proxy.conf",
                          configuration.WORKER_VERSION: "OMSUtil",
                          configuration.WORKING_DIRECTORY_PATH: "/tmp"})

USERNAME_NXAUTOMATION = "nxautomation"
GROUPNAME_NXAUTOMATION = "nxautomation"
GROUPNAME_OMSAGENT = "omsagent"


def initialize():
    """Initializes the OMS environment. Meant to be executed everytime the resource's set method is invoked.
    Steps:
        - Sets omsagent group to nxautomation user (if needed).
        - Sets group read permission to MSFT keyring.gpg
        - Sets group read and execute to the OMS certificate folder.

    Args:
        None
    """
    command = ["sudo", "chmod", "g+rx", "-R", "/etc/opt/microsoft/omsagent/certs"]
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if process.returncode != 0:
        raise Exception("Unable set owners of certificate folder. Error: " + str(error))
    else:
        print "Successfully set owners of certificate folder."


def main():
    parser = OptionParser(usage="usage: %prog --initialize",
                          version="%prog " + str(configuration.get_worker_version()))
    parser.add_option("--initialize", action="store_true", dest="initialize", default=False)
    (options, args) = parser.parse_args()

    nxautomation_uid = int(pwd.getpwnam("nxautomation").pw_uid)
    if os.getuid() != nxautomation_uid:
        raise Exception("OMSUtil can only be ran as nxautomation user.")

    if options.initialize is True:
        initialize()
    else:
        raise Exception("No option specified.")


if __name__ == "__main__":
    main()

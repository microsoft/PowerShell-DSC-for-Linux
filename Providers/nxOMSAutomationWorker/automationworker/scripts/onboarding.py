#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 2

import sys
import os
import subprocess
from optparse import OptionParser


def get_options_and_arguments():
    version_info = sys.version
    parser = None
    if int(version_info[PY_MAJOR_VERSION]) == 2 and int(version_info[PY_MINOR_VERSION]) <= 5:
        sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
        import configuration2
        configuration2.clear_config()
        configuration2.set_config({configuration2.PROXY_CONFIGURATION_PATH: "/etc/opt/microsoft/omsagent/proxy.conf",
                          configuration2.WORKER_VERSION: "LinuxDIYRegister",
                          configuration2.WORKING_DIRECTORY_PATH: "/tmp"})
        parser = OptionParser(
        usage="usage: %prog [--register, --deregister] -e endpoint -k key -g groupname -w workspaceid [-p gpgkeyring]",
        version="%prog " + str(configuration2.get_worker_version()))
    else:
        AUTOMATIONWORKER_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x/worker"
        sys.path.insert(1,AUTOMATIONWORKER_PATH)
        import configuration3
        configuration3.clear_config()
        configuration3.set_config({configuration3.PROXY_CONFIGURATION_PATH: "/etc/opt/microsoft/omsagent/proxy.conf",
                          configuration3.WORKER_VERSION: "LinuxDIYRegister",
                          configuration3.WORKING_DIRECTORY_PATH: "/tmp"})
        parser = OptionParser(
        usage="usage: %prog [--register, --deregister] -e endpoint -k key -g groupname -w workspaceid [-p gpgkeyring]",
        version="%prog " + str(configuration3.get_worker_version()))
    parser.add_option("-e", "--endpoint", dest="registration_endpoint", help="Agent service registration endpoint.")
    parser.add_option("-k", "--key", dest="automation_account_key", help="Automation account primary/secondary key.")
    parser.add_option("-g", "--groupname", dest="hybrid_worker_group_name", help="Hybrid worker group name.")
    parser.add_option("-w", "--workspaceid", dest="workspace_id", help="Workspace id.")
    parser.add_option("-r", "--register", action="store_true", dest="register", default=False)
    parser.add_option("-d", "--deregister", action="store_true", dest="deregister", default=False)
    parser.add_option("-t", "--test", action="store_true", dest="test", default=False)
    parser.add_option("-p", "--gpg-keyring", dest="gpg_keyring", help="GPG keyring path")
    (options, args) = parser.parse_args()

    if options.register is False and options.deregister is False:
        raise Exception("Please specify the onboarding action to perform (--register | --deregister).")

    # --register requirements
    if options.register is True and (options.registration_endpoint is not None
                                     and options.automation_account_key is not None
                                     and options.hybrid_worker_group_name is not None
                                     and options.workspace_id is not None) is False:
        parser.print_help()
        sys.exit(-1)
    # --deregister requirements
    elif options.deregister is True and (options.registration_endpoint is not None
                                         and options.automation_account_key is not None
                                         and options.hybrid_worker_group_name is not None
                                         and options.workspace_id is not None) is False:
        parser.print_help()
        sys.exit(-1)
    elif options.register is False and options.deregister is False:
        parser.print_help()
        sys.exit(-1)

    return options, args


def register(options):
    version_info = sys.version
    if int(version_info[PY_MAJOR_VERSION]) == 2 and int(version_info[PY_MINOR_VERSION]) <= 7:
        import onboarding2
        onboarding2.register(options)
    else:
        AUTOMATIONWORKER_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x/scripts"
        sys.path.insert(1,AUTOMATIONWORKER_PATH)
        import onboarding3
        onboarding3.register(options)

def deregister(options):
    version_info = sys.version
    if int(version_info[PY_MAJOR_VERSION]) == 2 and int(version_info[PY_MINOR_VERSION]) <= 7:
        import onboarding2
        onboarding2.deregister(options)
    else:
        AUTOMATIONWORKER_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x/scripts"
        sys.path.insert(1,AUTOMATIONWORKER_PATH)
        import onboarding3
        onboarding3.deregister(options)


def main():
    options, args = get_options_and_arguments()

    if options.register is True:
        register(options)
    elif options.deregister is True:
        deregister(options)


if __name__ == "__main__":
    # is running as root
    if os.getuid() != 0:
        raise Exception("You need to run this script as root to register a new automation worker.")

    # requied for cases where the diy registration is trigger before the worker manager start (.pyc will be owned by root in that case and have to be owned by omsagent:omiusers)
    proc = subprocess.Popen(["find",
                             "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/",
                             "-type", "f", "-name", "*.pyc", "-exec", "rm", "{}", "+"], stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE)
    output, error = proc.communicate()
    if proc.returncode != 0:
        raise Exception("Unable to remove root-owned .pyc")

    main()
    
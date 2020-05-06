#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 2

from optparse import OptionParser
import os
import sys


def main():
    if os.getuid() != 0:
        raise Exception("You need to run this script as root.")
    parser = OptionParser(usage="usage: %prog ( --true | --false )")
    parser.add_option("-t", "--true", dest="t", action="store_true", default=False, help="Require runbooks to be signed for execution on this host")
    parser.add_option("-f", "--false", dest="f", action="store_true", default=False, help="Do not require runbooks to be signed for execution on this host")
    (options, args) = parser.parse_args()
    if options.f is True and options.t is True:
        # Both options should not be true at the same time
        parser.print_help(sys.stderr)
        sys.stderr.write("Both \"--true\" and \"--false\" options cannot be selected at the same time.\n")
        sys.exit(1)
    if options.f is False and options.t is False:
        parser.print_help(sys.stderr)
        sys.stderr.write("Please select at least one of \"--true\" or \"--false\" options.\n")
        sys.exit(1)

    version_info = sys.version
    if int(version_info[PY_MAJOR_VERSION]) == 2 and int(version_info[PY_MINOR_VERSION]) <= 7:
        sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
        import require_runbook_signature2
        if options.f is True:
            require_runbook_signature2.set_signature_enforcement_policy(False)
            print ("Successfully configured this host to execute both signed and unsigned runbooks.")
        else:
            require_runbook_signature2.set_signature_enforcement_policy(True)
            print ("Successfully configured this host to execute signed runbook exclusively.")
    else:
        AUTOMATIONWORKER_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x/worker"
        AUTOMATIONSCRIPTS_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x/scripts"
        sys.path.insert(1,AUTOMATIONWORKER_PATH)
        sys.path.insert(2, AUTOMATIONSCRIPTS_PATH)
        import require_runbook_signature3
        if options.f is True:
            require_runbook_signature3.set_signature_enforcement_policy(False)
            print ("Successfully configured this host to execute both signed and unsigned runbooks.")
        else:
            require_runbook_signature3.set_signature_enforcement_policy(True)
            print ("Successfully configured this host to execute signed runbook exclusively.")


if __name__ == "__main__":
    main()


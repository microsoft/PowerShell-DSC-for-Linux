#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

"""Runtime factory module."""
from runtime import *
from workerexception import *
import configuration3 as configuration

# This has to map with JRDS : RunbookDefinitionKind enum
PowerShell = 5
PYTHON2 = 9
PYTHON3 = 10
BASH = 11
PowerShell7 = 13


def create_runtime(job_data, runbook_data):
    """Create a new instance of the appropriate language Runtime.

    :param job_data     : the job data
    :param runbook_data : the runbook_data
    :type job_data      : jrdsclient.JobData
    :type runbook_data  : jrdsclient.RunbookData

    Returns:
        An instance of Python2Runtime if the runbook_definition_kind parameter is "Python2".
        An instance of Python3Runtime if the runbook_definition_kind parameter is "Python3".
        An instance of BashRuntime if the runbook_definition_kind parameter is "Bash".
        An instance of PowerShell7 if the runbook_definition_kind parameter is "PowerShell7".

    Throws:
        UnsupportedRunbookType : If the OS or the worker doesn't support the specified runbook_definition_kind.
    """
    """
        Special case handling for update management.
        Currently update management runbook comes runbook kind as python2
        So it won't work on the python3 only machine so fixing that case.
    """
    if runbook_data.name == "PatchMicrosoftOMSLinuxComputer" and configuration.get_worker_type() == "auto-registered":
        import sys
        if sys.version_info[0] >= 3:
            runbook_data.runbook_definition_kind = PYTHON3
    
    runbook_definition_kind = runbook_data.runbook_definition_kind

    if runbook_definition_kind == PowerShell:
        runbook = PowerShellRunbook(runbook_data)
        runtime = PowerShellRuntime(job_data, runbook)
    elif runbook_definition_kind == PYTHON2:
        runbook = Python2Runbook(runbook_data)
        runtime = Python2Runtime(job_data, runbook)
    elif runbook_definition_kind == PYTHON3:
        runbook = Python3Runbook(runbook_data)
        runtime = Python3Runtime(job_data, runbook)
    elif runbook_definition_kind == BASH:
        runbook = BashRunbook(runbook_data)
        runtime = BashRuntime(job_data, runbook)
    elif runbook_definition_kind == PowerShell7:
        runbook = PowerShell7Runbook(runbook_data)
        runtime = PowerShell7Runtime(job_data, runbook)
    else:
        raise WorkerUnsupportedRunbookType()

    if runtime.is_runtime_supported() is False:
        raise OSUnsupportedRunbookType()

    return runbook, runtime

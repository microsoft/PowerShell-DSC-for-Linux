#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Runtime factory module."""

from runtime import *
from workerexception import *

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

#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import os

import configuration
import tracer

configuration.set_config({configuration.COMPONENT: "runbook"})


def get_activity_id():
    try:
        return os.environ["AUTOMATION_ACTIVITY_ID"]
    except KeyError:
        return None


def log(trace, activity_id=get_activity_id()):
    tracer.log_runbook_runtime_trace(trace, activity_id=activity_id)

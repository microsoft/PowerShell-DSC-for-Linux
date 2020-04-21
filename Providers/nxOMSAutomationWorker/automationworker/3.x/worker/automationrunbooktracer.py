#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

import os

import configuration3 as configuration
import tracer

configuration.set_config({configuration.COMPONENT: "runbook"})


def get_activity_id():
    try:
        return os.environ["AUTOMATION_ACTIVITY_ID"]
    except KeyError:
        return None


def log(trace, activity_id=get_activity_id()):
    tracer.log_runbook_runtime_trace(trace, activity_id=activity_id)

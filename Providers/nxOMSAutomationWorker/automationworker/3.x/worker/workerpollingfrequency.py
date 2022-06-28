#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

JRDS_SANDBOX_POLLING_FREQUENCY = ['30']

def set_jrds_sandbox_actions_polling_freq(pollingfrequency):
    JRDS_SANDBOX_POLLING_FREQUENCY[0] = pollingfrequency

def get_jrds_get_sandbox_actions_polling_freq():
    return int(JRDS_SANDBOX_POLLING_FREQUENCY[0]) 
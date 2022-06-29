#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Contains functions to get polling frequency value and set values based on the header received as part of GetSandboxActions """

JRDS_SANDBOX_POLLING_FREQUENCY = ['30']

def set_jrds_sandbox_actions_polling_freq(pollingfrequency):
    JRDS_SANDBOX_POLLING_FREQUENCY[0] = pollingfrequency


def get_jrds_get_sandbox_actions_polling_freq():
    return int(JRDS_SANDBOX_POLLING_FREQUENCY[0])
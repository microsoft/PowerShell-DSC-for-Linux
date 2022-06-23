#!/usr/bin/env python3
#
# Copyright (C) Microsoft Corporation, All rights reserved.

#import os

JRDS_SANDBOX_POLLING_FREQUENCY = ['120']

def set_jrds_sandbox_actions_polling_freq(pollingfrequency):
    JRDS_SANDBOX_POLLING_FREQUENCY[0] = pollingfrequency
    
def get_jrds_get_sandbox_actions_polling_freq():
    #import linuxutil
    #import diydirs
    
    #DIY_STATE_PATH = diydirs.DIY_STATE_PATH

    #certificate_path = os.path.join(DIY_STATE_PATH, "worker_diy.crt")
    #linuxutil.get_cert_info(certificate_path)
    return int(JRDS_SANDBOX_POLLING_FREQUENCY[0])
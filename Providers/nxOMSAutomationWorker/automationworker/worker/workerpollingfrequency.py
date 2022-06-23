#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

#import os

JRDS_SANDBOX_POLLING_FREQUENCY = ['120']

def set_jrds_sandbox_actions_polling_freq(pollingfrequency):
    import tracer
    JRDS_SANDBOX_POLLING_FREQUENCY[0] = pollingfrequency
    tracer.log_worker_debug("setting freq"+JRDS_SANDBOX_POLLING_FREQUENCY[0])
    
def get_jrds_get_sandbox_actions_polling_freq():
    import tracer
    #import linuxutil
    #import diydirs
    
    #DIY_STATE_PATH = diydirs.DIY_STATE_PATH

    #certificate_path = os.path.join(DIY_STATE_PATH, "worker_diy.crt")
    #linuxutil.get_cert_info(certificate_path)
    tracer.log_worker_debug("getting freq"+JRDS_SANDBOX_POLLING_FREQUENCY[0])
    return int(JRDS_SANDBOX_POLLING_FREQUENCY[0])
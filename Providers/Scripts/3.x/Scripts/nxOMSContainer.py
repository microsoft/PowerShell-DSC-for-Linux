#!/usr/bin/env python
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ====================================


import imp
import logging
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

error_message = "Python 3.x versions currently not supported"

def Set_Marshall(ResourceSettings):
    log(ERROR, error_message)
    return [-1]


def Test_Marshall(ResourceSettings):
    log(ERROR, error_message)
    return [-1]


def Get_Marshall(ResourceSettings):
    log(ERROR, error_message)
    return -1, dict()

# ###########################################################
# Begin user defined DSC functions
# ###########################################################
ERROR = logging.ERROR
DEBUG = logging.DEBUG
INFO = logging.INFO




def log(level, message):
    try:
        LG().Log(logging._levelNames[level], message)
    except:
        pass
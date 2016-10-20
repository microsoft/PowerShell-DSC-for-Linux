#!/usr/bin/env python
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ====================================
import os
import sys
import datetime

def init_locals(DestinationPath):
    if DestinationPath is None:
        DestinationPath = ''
    return DestinationPath.encode('ascii', 'ignore')


def Set_Marshall(DestinationPath):
    DestinationPath = init_locals(DestinationPath)
    fileHandle = open(DestinationPath, mode='a')
    fileHandle.write("Hello world:  ")
    fileHandle.write(str(datetime.datetime.now()) + "\n")
    fileHandle.flush()
    fileHandle.close()
    return [0]

def Test_Marshall(DestinationPath):
    DestinationPath = init_locals(DestinationPath)
    if os.path.isfile(DestinationPath):
        return [0]
    else:
        return [-1]


def Get_Marshall(DestinationPath):
    arg_names = list(locals().keys())
    DestinationPath = init_locals(DestinationPath)
    retval = 0
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


# ###########################################################
# Begin user defined DSC functions
# ###########################################################


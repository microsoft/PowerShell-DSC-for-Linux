#!/usr/bin/env python
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ====================================
import os
import sys


def init_locals(DestinationPath):
    if DestinationPath is None:
        DestinationPath = ''
    return DestinationPath.encode('ascii', 'ignore')


def Set_Marshall(DestinationPath):
    DestinationPath = init_locals(DestinationPath)
    return [0]


def Test_Marshall(DestinationPath):
    DestinationPath = init_locals(DestinationPath)
    return [0]


def Get_Marshall(DestinationPath):
    arg_names = list(locals().keys())
    DestinationPath = init_locals(DestinationPath)
    retval = 0
    arg_names.append('ModifiedDate')
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


# ###########################################################
# Begin user defined DSC functions
# ###########################################################


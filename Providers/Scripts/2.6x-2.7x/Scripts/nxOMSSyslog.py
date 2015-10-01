#!/usr/bin/env python
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
#  See license.txt for license information.
# ====================================

from __future__ import print_function
from __future__ import with_statement
from contextlib import contextmanager

import os
import sys
import pwd
import shutil
import grp
import codecs
import urllib2
import time
import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog
try:
    import hashlib
    md5const = hashlib.md5
except ImportError:
    import md5
    md5const = md5.md5

BLOCK_SIZE = 8192

global show_mof
show_mof = False


def Set_Marshall(SyslogSource):
    return [0]


def Test_Marshall(SyslogSource):
    print("Running Test")
    print("****************************************")
    print("SyslogSource: " + str(SyslogSource))
    return [0]

def Get_Marshall(SyslogSource):
    return [0]

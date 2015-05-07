#!/usr/bin/env python
# ============================================================================
#  Copyright (C) Microsoft Corporation, All rights reserved.
# ============================================================================

import os
import sys
import time
import inspect


def Print(s, file=sys.stderr):
    file.write(s + '\n')


def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except:
        return None, Exception('IOError')
    return f, None

# YYYY/MM/DD HH:MM:SS: LEVEL: FILE(LINE): \n message \n


class DSCLog(object):

    def __init__(self):
        self.levels = ((0, 'FATAL'), (1, 'ERROR'), (2, 'WARNING'), (3, 'INFO'),
                       (4, 'DEBUG'), (5, 'VERBOSE'))
        self.current_level = self.GetCurrentLogLevel()
        prefix = '/opt/omi'
        if 'OMI_HOME' in os.environ.keys():
            prefix = os.environ['OMI_HOME']
        self.file_path = prefix+'/var/log/dsc.log'

    def Log(self, log_level, message):
        last_frame = inspect.currentframe().f_back
        place = last_frame.f_globals['__file__'] + \
            '('+str(last_frame.f_lineno)+')'
        if message is None or len(message) is 0:
            return
        if log_level is None:
            log_level = self.current_level
        if type(log_level) == str:
            t = log_level
            log_level = 5
            for num, strng in self.levels:
                if t == strng:
                    log_level = num
        if log_level < 0 or log_level > 5 or len(message) < 1:
            return
        if log_level > self.current_level:
            return
        if type(message) != str: # this should only happen if the type is unicode.
            message = message.decode('utf-8').encode('ascii', 'ignore')
        t = time.localtime()
        line = "%04u/%02u/%02u %02u:%02u:%02u: %s: %s:\n%s\n" % (t.tm_year,
            t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
            self.levels[log_level][1], place, message)
        try:
            F, error = opened_w_error(self.file_path, 'a')
            if error:
                Print("Exception opening logfile " + self.file_path +
                      " Error: " + str(error), file=sys.stderr)
            else:
                F.write(line)
                F.close()
        except:
            F.close()
            Print("Exception opening logfile " + self.file_path +
                  " Error: " + str(error), file=sys.stderr)

    def GetCurrentLogLevel(self):
        return 5

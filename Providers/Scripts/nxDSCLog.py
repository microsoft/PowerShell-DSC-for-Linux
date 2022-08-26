#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python
# ============================================================================
#  Copyright (C) Microsoft Corporation, All rights reserved.
# ============================================================================

import os
import sys
import time
import inspect
import codecs
import imp

scriptFolderPath = os.path.dirname(os.path.realpath(__file__))
fullPath = os.path.join(scriptFolderPath, 'helperlib.py')
helperlib = imp.load_source('helperlib', fullPath)
VarDir = helperlib.PYTHON_PID_DIR
LogFile = VarDir + "/log/dsc.log"

if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
    LogFile = "/var/opt/microsoft/omsconfig/omsconfig.log"

def Print(s, file=sys.stderr):
    file.write(s + '\n')


def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, mode, 'utf8')
    except:
        return None, Exception('IOError')
    return f, None

# YYYY/MM/DD HH:MM:SS: LEVEL: FILE(LINE): \n message \n


class DSCLog(object):

    def __init__(self, logpath = LogFile):
        self.levels = ((0, 'FATAL'), (1, 'ERROR'), (2, 'WARNING'), (3, 'INFO'),
                       (4, 'DEBUG'), (5, 'VERBOSE'))
        self.current_level = self.GetCurrentLogLevel()
        if helperlib.CONFIG_SYSCONFDIR_DSC != "omsconfig":
            os.system('mkdir -p ' + VarDir + '/log')
        self.file_path = logpath

    def Log(self, log_level, message):
        last_frame = inspect.currentframe().f_back
        place = last_frame.f_globals['__file__'] + \
            '('+str(last_frame.f_lineno)+')'
        if message == None or len(message) == 0:
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
        t = time.localtime()
        line = "%04u/%02u/%02u %02u:%02u:%02u: %s: %s:\n%s\n" % (t.tm_year,
            t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
            self.levels[log_level][1], place, message)
        error = None
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

class ConsoleAndFileLogger(object):
    def __init__(self, path=LogFile):
        self.console = sys.stdout
        self.logpath = path
        self.errorreported = False
        
    def write(self, message):
        self.console.write(message)
        try:
            file_handle = codecs.open(self.logpath, 'a', 'utf8')
            try:
                try:
                    file_handle.write(message)
                except:
                    if not self.errorreported:
                        self.console.write("Failed to write the dsc log file " + self.logpath + "\n")
                        self.errorreported = True
            finally:
                file_handle.close()
        except:
            if not self.errorreported:
                self.console.write("Failed to open the dsc log file " + self.logpath + "\n")
                self.errorreported = True
                
    def flush(self):
        pass
    def __del__(self):
        sys.stdout = self.console
#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import errno
import os
import random
import sys
import tempfile

import linuxutil
from workerexception import *

PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 1
PY_MICRO_VERSION = 2


def exit_on_error(filename, message, exit_code=-1):
    """Generates a crash log on disk in the temp directory then kills the current process."""
    print str(message)
    try:
        crash_log = open(os.path.join(tempfile.gettempdir(), filename), "w")
        crash_log.write(message)
        crash_log.close()
    except:
        pass
    sys.exit(exit_code)


def generate_uuid():
    """ UUID module isn't available in python 2.4. Since activity id are only required for tracing this is enough.

    Returns: string, an activity id which has a GUID format
    """
    version_info = sys.version_info
    try:
        if version_info[PY_MAJOR_VERSION] == 2 and version_info[PY_MINOR_VERSION] >= 5:
            import uuid
            uuid = str(uuid.uuid4())
        elif linuxutil.is_posix_host():
            uuid = linuxutil.generate_uuid()
    except:
        uuid = [random.randint(10000000, 99999999),
                random.randint(1000, 9999),
                random.randint(1000, 9999),
                random.randint(1000, 9999),
                random.randint(100000000000, 999999999999)]
        uuid = '-'.join(map(str, uuid))
    return uuid


def assert_file_read_permission(file_path):
    """ Asserts that the specified file exists and can be read.

        Returns: bool, True if the file can be read, False otherwise
    """
    if os.path.isfile(file_path) is False:
        raise FileNotFoundException(file_path)

    try:
        f = open(file_path)
        f.close()
        return True
    except IOError, e:
        if e.errno == errno.EACCES:
            return False
        raise
    except:
        raise

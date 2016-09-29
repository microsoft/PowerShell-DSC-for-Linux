#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Process factory which returns a process enforcing the preexec_fn."""

try:
    import ctypes
    # See : http://man7.org/linux/man-pages/man2/prctl.2.html
    # See : http://lxr.free-electrons.com/source/include/uapi/linux/prctl.h
    libc = ctypes.CDLL("libc.so.6")
    PR_SET_PDEATHSIG = 1

    def set_process_death_signal(death_signal):
        libc.prctl(PR_SET_PDEATHSIG, death_signal)
except ImportError:
    # TODO(dalbe): Trace
    pass
except:
    # For test to run on windows
    # TODO(dalbe): Trace
    pass

import os
import signal
import subprocess
import sys

CTYPES_MODULE_NAME = "ctypes"


def get_env_var(env):
    environment_var = os.environ.copy()
    if env is not None:
        environment_var.update(env)
    return environment_var


def create_subprocess(cmd, env=None, stdout=None, stderr=None, cwd=None):
    """Creates a process forcing and sets the SIGTERM signal handler using Ctypes (when available). Else creates a
    process based on the pipe_output argument.

    Ctypes are only available in 2.5+ so processes create in python 2.4 won't die if their parent process dies.

    Args:
        cmd         : string            , the cmd to execute.
        env         : dictonary(string) , the process level environment variable.
        stdout      : boolean           , sets the stdout to subprocess.PIPE when True, else stdout is left untouched.
        stderr      : boolean           , sets the stderr to subprocess.PIPE when True, else stdout is left untouched.

    Returns:
        The process object.
    """
    environment_var = get_env_var(env)

    if CTYPES_MODULE_NAME not in sys.modules or os.name.lower() == "nt":
        return subprocess.Popen(cmd, env=environment_var, stdout=stdout, stderr=stderr, cwd=cwd)
    else:
        return subprocess.Popen(cmd, env=environment_var, stdout=stdout, stderr=stderr, cwd=cwd,
                                preexec_fn=set_process_death_signal(signal.SIGTERM))

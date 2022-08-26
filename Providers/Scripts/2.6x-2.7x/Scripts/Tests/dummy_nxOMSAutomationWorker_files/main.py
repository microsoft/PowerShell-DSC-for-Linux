#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python2
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================
import time
import os
import sys

def fork_and_exit_parent():
    pid = os.fork()
    if pid > 0:
        sys.exit(0)

def daemonize():
    fork_and_exit_parent()
    os.setsid()
    os.close(sys.stdin.fileno())
    os.close(sys.stdout.fileno())
    os.close(sys.stderr.fileno())
    fork_and_exit_parent()



def main():
    # do not trace anything before this point

    # start a non terminating job
    daemonize()
    while (True):
        time.sleep(60)

if __name__ == "__main__":
    main()

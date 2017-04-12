#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Worker exceptions."""


class JrdsSandboxTerminated(Exception):
    def __init___(self, msg=None):
        if msg is None:
            self.message = "JRDS sandbox terminated."
        else:
            self.message = msg


class JrdsAuthorizationException(Exception):
    def __init___(self, msg=None):
        if msg is None:
            self.message = "JRDS authorization exception."
        else:
            self.message = msg


class SandboxRuntimeException(Exception):
    def __init__(self, msg=None):
        if msg is None:
            self.message = "Sandbox unhandled runtime exception."
        else:
            self.message = msg


class WorkerUnsupportedRunbookType(Exception):
    def __init__(self, msg=None):
        if msg is None:
            self.message = "This runbook type isn't supported by Linux hybrid workers."
        else:
            self.message = msg


class OSUnsupportedRunbookType(Exception):
    def __init__(self, msg=None):
        if msg is None:
            self.message = "This runbook type isn't supported on this host."
        else:
            self.message = msg


class InvalidRunbookSignature(Exception):
    def __init__(self, msg=None):
        if msg is None:
            self.message = "The runbook signature is invalid."
        else:
            self.message = msg


class AutomationAssetNotFound(Exception):
    def __init__(self, msg=None):
        if msg is None:
            self.message = "The requested asset was not found."
        else:
            self.message = msg


class AutomationAssetException(Exception):
    def __init__(self, msg=None):
        if msg is None:
            self.message = "An unknown error occurred while performing the operation."
        else:
            self.message = msg

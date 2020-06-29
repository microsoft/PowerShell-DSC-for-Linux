#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

"""Worker specific exceptions.

For backward compatibility, do not use super(CustomException, self).__init__() when instantiating custom exception.
This is not supported in 2.4 with 'old style' classes (not inheriting 'object').

Model to follow :

class CustomException(Exception):
    def __init__(self, path):
        Exception.__init__(self, "Custom exception messsage. [path=" + str(path) + "]")

"""


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


class Jrds503Exception(Exception):
    def __init___(self, msg=None):
        my_message = "JRDS returned status code 503 exception."
        if msg is None:
            self.message = my_message
        else:
            self.message = my_message + "\n" + msg


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


class GPGKeyringNotConfigured(Exception):
    def __init__(self):
        self.message = "Signature validation failed. No GPG keyring was found in the configuration."


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


class InvalidFilePermissionException(Exception):
    def __init__(self, path):
        Exception.__init__(self, "Invalid permission. [path=" + str(path) + "]")


class FileNotFoundException(Exception):
    def __init__(self, path):
        Exception.__init__(self, "File not found. [path=" + str(path) + "]")


class RetryAttemptExceededException(Exception):
    def __init__(self, exception):
        Exception.__init__(self, "Retry attempt exceeded. [exception=" + str(exception) + "]")
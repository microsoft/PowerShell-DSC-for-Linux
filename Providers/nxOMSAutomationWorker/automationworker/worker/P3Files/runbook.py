#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Runbook module."""

import os

import configuration
import gpg
import iohelper
import jrdsclient
import linuxutil
from workerexception import *

definition_kind_int_to_str = {0: "Unknown",
                              1: "Script",
                              2: "Workflow",
                              3: "Graph",
                              4: "Configuration",
                              5: "PowerShell",
                              6: "PowerShellWorkflow",
                              7: "GraphPowerShell",
                              8: "GraphPowerShellWorkflow",
                              9: "Python2",
                              10: "Python3",
                              11: "Bash"}


class Runbook:
    def __init__(self, runbook_data):
        """:type runbook_data: jrdsclient.RunbookData"""
        self.runbook_data = runbook_data
        self.definition_kind = runbook_data.runbook_definition_kind
        self.definition_kind_str = definition_kind_int_to_str[runbook_data.runbook_definition_kind]
        self.runbook_file_path = ""

        # should be overwritten by derived class
        self.file_extension = ""

    def initialize(self):
        """Initializes the runbook."""
        self.write_to_disk()
        if configuration.get_enforce_runbook_signature_validation():
            self.validate_signature()

    def write_to_disk(self):
        """Writes the runbook's definition to disk."""
        file_name = self.runbook_data.name + self.runbook_data.runbook_version_id + self.file_extension
        self.runbook_file_path = os.path.join(configuration.get_working_directory_path(), file_name)
        runbook_definition = str(self.runbook_data.definition.encode("utf-8"))
        if linuxutil.is_posix_host() is True:
            # replace dos end of line to unix end of line
            runbook_definition = runbook_definition.replace("\r\n", "\n")
        iohelper.write_to_file(self.runbook_file_path, data=runbook_definition, mode="w+b")

    def validate_signature(self):
        """Validates that the runbook signature is valid.

        Raises:
            InvalidRunbookSignature if the signature is invalid
        """
        decrypted_runbook_path = self.runbook_file_path + ".d"
        is_valid = gpg.verify_signature(self.runbook_file_path, decrypted_runbook_path)

        if is_valid:
            os.remove(self.runbook_file_path)
            os.rename(decrypted_runbook_path, self.runbook_file_path)
        else:
            raise InvalidRunbookSignature()


class Python2Runbook(Runbook):
    def __init__(self, runbook_data):
        Runbook.__init__(self, runbook_data)
        self.file_extension = ".py"
        self.initialize()


class Python3Runbook(Runbook):
    def __init__(self, runbook_data):
        Runbook.__init__(self, runbook_data)
        self.file_extension = ".py"
        self.initialize()


class BashRunbook(Runbook):
    def __init__(self, runbook_data):
        Runbook.__init__(self, runbook_data)
        self.file_extension = ".sh"
        self.initialize()


class PowerShellRunbook(Runbook):
    def __init__(self, runbook_data):
        Runbook.__init__(self, runbook_data)
        self.file_extension = ".ps1"
        self.initialize()

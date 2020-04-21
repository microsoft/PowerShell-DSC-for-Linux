#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

"""Gpg module. Used for runbook signature validation."""

import os
import subprocess

import configuration3 as configuration
import subprocessfactory
import tracer
from workerexception import *

GPG = "gpg"
GPG_BATCH_OPTION = "--batch"
GPG_DECRYPT_OPTION = "--decrypt"
GPG_KEYRING_OPTION = "--keyring"
GPG_NO_DEFAULT_KEYRING_OPTION = "--no-default-keyring"
GPG_OUTPUT_OPTION = "--output"
GPG_YES_OPTION = "--yes"


def verify_signature(signed_file_path, output_file_path):
    """Verifies the signed file's signature.

    Returns:
        True    : If the signature is valid.
        False   : If the signature is invalid.
    """
    keyrings = configuration.get_gpg_public_keyrings_path()

    if (len(keyrings) == 0) or (len(keyrings) == 1 and keyrings[0] == configuration.DEFAULT_GPG_PUBLIC_KEYRING_PATH):
        raise GPGKeyringNotConfigured()

    for keyring_path in keyrings:
        # do not rely on default user keyring
        if keyring_path == "" or keyring_path == configuration.DEFAULT_GPG_PUBLIC_KEYRING_PATH:
            continue

        cmd = [GPG, GPG_BATCH_OPTION, GPG_YES_OPTION, GPG_DECRYPT_OPTION]

        # if a keyring is specified in the conf, used it, else use default one
        if keyring_path != "":
            cmd += [GPG_NO_DEFAULT_KEYRING_OPTION, GPG_KEYRING_OPTION, keyring_path]
        cmd += [GPG_OUTPUT_OPTION, output_file_path, signed_file_path]

        # temporary workaround for the omi/gpg bug causing gpg to create a .gpg folder in the wrong home dir
        # only apply the workaround for oms installation
        env = None
        if os.name.lower() != "nt" and "nxOMSAutomationWorkerResource" in os.path.abspath(__file__):
            import pwd
            env = os.environ.copy()
            current_username = pwd.getpwuid(os.getuid()).pw_name
            if "omsagent" in current_username:
                env["HOME"] = "/var/opt/microsoft/omsagent/run"
            elif "nxautomation" in current_username:
                env["HOME"] = "/var/opt/microsoft/omsagent/run/automationworker"

        proc = subprocessfactory.create_subprocess(cmd=cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()

        stderr = stderr.decode() if isinstance(stderr, bytes) else stderr
        if proc.poll() == 0:
            tracer.log_sandbox_job_runbook_signature_validation_succeeded(keyring_path)
            return True
        else:
            tracer.log_sandbox_job_runbook_signature_validation_failed(keyring_path, stderr)

    tracer.log_sandbox_job_runbook_signature_invalid()
    return False

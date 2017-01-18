#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Gpg module. Used for runbook signature validation."""

import os
import subprocess

import configuration
import subprocessfactory
import tracer

GPG_NO_DEFAULT_KEYRING_OPTION = "--no-default-keyring"
GPG_KEYRING_ARG = "--keyring"


def verify_signature(signed_file_path, output_file_path):
    """Verifies the signed file's signature.

    Returns:
        True    : If the signature is valid.
        False   : If the signature is invalid.
    """
    cmd = ["gpg", "-d"]
    keyring_path = configuration.get_gpg_public_keyring_path()

    # if a keyring is specified in the conf, used it, else use default one
    if keyring_path != "":
        cmd += [GPG_NO_DEFAULT_KEYRING_OPTION, GPG_KEYRING_ARG, keyring_path]
    cmd += ["--output", output_file_path, signed_file_path]

    # temporary workaround for the omi/gpg bug causing gpg to create a .gpg folder in the wrong home dir
    # only apply the workaround for oms installation
    env = None
    if "nxOMSAutomationWorkerResource" in os.path.abspath(__file__):
        env = os.environ.copy()
        env["HOME"] = "/var/opt/microsoft/omsagent/run"

    proc = subprocessfactory.create_subprocess(cmd=cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = proc.communicate()

    if proc.poll() == 0:
        tracer.log_debug_trace("Signature is valid.")
        return True

    tracer.log_sandbox_job_runbook_signature_validation_failed(stderr)
    return False

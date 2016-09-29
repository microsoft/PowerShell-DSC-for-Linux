#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Gpg module. Used for runbook signature validation."""

import subprocess

import configuration
import subprocessfactory
import tracer

GPG_DECRYPT_BASE_CMD = ["gpg", "-d"]
GPG_NO_DEFAULT_KEYRING_OPTION = "--no-default-keyring"
GPG_KEYRING_ARG = "--keyring"


def verify_signature(signed_file_path, output_file_path):
    """Verifies the signed file's signature.

    Returns:
        True    : If the signature is valid.
        False   : If the signature is invalid.
    """
    cmd = GPG_DECRYPT_BASE_CMD
    keyring_path = configuration.get_gpg_public_keyring_path()

    # if a keyring is specified in the conf, used it, else use default one
    if keyring_path != "":
        cmd += [GPG_NO_DEFAULT_KEYRING_OPTION, GPG_KEYRING_ARG, keyring_path]
    cmd += ["--output", output_file_path, signed_file_path]

    proc = subprocessfactory.create_subprocess(cmd=cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = proc.communicate()

    if proc.poll() == 0:
        tracer.log_debug_trace("Signature is valid.")
        return True

    tracer.log_debug_trace("Signature is invalid.[exception=" + str(stderr) + "]")
    return False

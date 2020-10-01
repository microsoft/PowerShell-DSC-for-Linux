#!/usr/bin/env python3
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================
from contextlib import contextmanager

import os
import sys
import subprocess
import imp
import re

# class MSFT_nxOMSKeyMgmt:OMI_BaseResource
# {
#   [Key] string KeyContents;
#   [Write,required] string KeySignature;
#   [Write,ValueMap{"present", "absent"},Values{"present", "absent"}] string Ensure;
# };

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

dsc_keyring_path = '/etc/opt/omi/conf/omsconfig/keyring.gpg'
signature_keyring_path = '/etc/opt/omi/conf/omsconfig/keymgmtring.gpg'
gpg_bin = '/usr/bin/gpg'
tmpdir = '/tmp/omsmgmt'
key_contents_path = tmpdir + '/' + 'tmpkey.pub'
key_signature_path = tmpdir + '/' + 'tmpkey.asc'


def init_vars(KeyContents, KeySignature, Ensure):
    return KeyContents, KeySignature, Ensure.lower()


def Set_Marshall(KeyContents, KeySignature, Ensure):
    if KeyContents is None or len(KeyContents) == 0 or \
            KeySignature is None or len(KeySignature) == 0:
        LG().Log('ERROR', 'Both "KeyContents" and "KeySignature" must be set.')
        print(
            'Both "KeyContents" and "KeySignature" must be set.', file=sys.stderr)
        return [-1]
    KeyContents, KeySignature, Ensure = init_vars(KeyContents, KeySignature, Ensure)
    return Set(KeyContents, KeySignature, Ensure)


def Test_Marshall(KeyContents, KeySignature, Ensure):
    if KeyContents is None or len(KeyContents) == 0 or \
            KeySignature is None or len(KeySignature) == 0:
        LG().Log('ERROR', 'Both "KeyContents" and "KeySignature" must be set.')
        print(
            'Both "KeyContents" and "KeySignature" must be set.', file=sys.stderr)
        return [-1]
    KeyContents, KeySignature, Ensure = init_vars(
        KeyContents, KeySignature, Ensure)
    return Test(KeyContents, KeySignature, Ensure)


def Get_Marshall(KeyContents, KeySignature, Ensure):
    if KeyContents is None or len(KeyContents) == 0 or \
            KeySignature is None or len(KeySignature) == 0:
        LG().Log('ERROR', 'Both "KeyContents" and "KeySignature" must be set.')
        print(
            'Both "KeyContents" and "KeySignature" must be set.', file=sys.stderr)
        return 0, KeyContents, KeySignature, Ensure
    arg_names = list(locals().keys())
    KeyContents, KeySignature, Ensure = init_vars(
        KeyContents, KeySignature, Ensure)
    KeyContents, KeySignature, Ensure = Get(KeyContents, KeySignature, Ensure)
    KeyContents = protocol.MI_String(KeyContents)
    KeySignature = protocol.MI_String(KeySignature)
    Ensure = protocol.MI_String(Ensure)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return 0, retd


def Set(KeyContents, KeySignature, Ensure):
    if Test(KeyContents, KeySignature, Ensure) == [0]:
        return [0]
    if not os.path.isdir(tmpdir):
        if MakeDirs(tmpdir) != None:
            LG().Log('ERROR', "Exception - Unable to creaste " + tmpdir)
            print("Exception - Unable to creaste " + tmpdir, file=sys.stderr)
            return [-1]
    error = None
    with opened_w_error(key_signature_path, 'w+') as (F, error):
        if error:
            print("ERROR:  Exception opening file " +
                  key_signature_path + " " + str(error), file=sys.stderr)
            LG().Log('ERROR', "Exception opening file " +
                     key_signature_path + " " + str(error))
            cleanup()
            return [-1]
        else:
            F.write(KeySignature)
            F.close()
    with opened_w_error(key_contents_path, 'w+') as (F, error):
        if error:
            print("ERROR:  Exception opening file " +
                  key_contents_path + " " + str(error), file=sys.stderr)
            LG().Log('ERROR', "Exception opening file " +
                     key_contents_path + " " + str(error))
            cleanup()
            return [-1]
        else:
            F.write(KeyContents)
            F.close()
    # Verify the signature.
    cmd = 'HOME=/var/opt/microsoft/omsagent/run ' + gpg_bin + ' --no-default-keyring --keyring ' \
        + signature_keyring_path + ' --verify ' + \
        key_signature_path + ' ' + key_contents_path
    code, out = RunGetOutput(cmd, False, False)
    if code != 0:
        LG().Log('ERROR',
                 '"KeyContents" could not be verified by "KeySignature".  Output is ' + out)
        print('"KeyContents" could not be verified by "KeySignature".  Output is ' + out, file=sys.stderr)
        cleanup()
        return [-1]
    if Ensure == 'absent':
        # Get the id so we can remove the key.
        cmd = 'HOME=/var/opt/microsoft/omsagent/run ' + gpg_bin + ' --dry-run --no-default-keyring --keyring ' \
            + dsc_keyring_path + ' --import ' + key_contents_path
        code, out = RunGetOutput(cmd, False, False)
        r = re.search(r'.*?key (.*?):.*?not changed', out)
        if r != None:
            key_id = r.group(1)
        else:
            LG().Log(
                'ERROR', 'Key ID could not be determined.  Output is ' + out)
            cleanup()
            return [-1]
        # We must use the fingerprint in batch mode to prevent interactive questions
        cmd = 'HOME=/var/opt/microsoft/omsagent/run ' + gpg_bin + ' --batch --yes --no-default-keyring --keyring ' \
            + dsc_keyring_path + ' --fingerprint ' + key_id
        code, out = RunGetOutput(cmd, False, False)
        r = re.search(r'.*?fingerprint = (.*?)\n', out)
        if r != None:
            # Older versions of gpg cannot parse space padding.
            key_fingerprint = r.group(1).replace(' ','')
        else:
            LG().Log(
                'ERROR', 'Key fingerprint could not be determined.  Output is ' + out)
            cleanup()
            return [-1]
        # Delete the key.
        cmd = 'HOME=/var/opt/microsoft/omsagent/run ' + gpg_bin + ' --batch --yes --no-default-keyring --keyring ' \
            + dsc_keyring_path + ' --delete-secret-and-public-key "' + key_fingerprint + '"'
        code, out = RunGetOutput(cmd, False, False)
        if code != 0:
            LG().Log('ERROR', 'Unable to delete Key.  Output is ' + out)
            print('Unable to delete Key.  Output is ' + out, file=sys.stderr)
            cleanup()
            return [-1]
    else:
        # Add the key.
        cmd = 'HOME=/var/opt/microsoft/omsagent/run ' + gpg_bin + ' --no-default-keyring --keyring ' \
            + dsc_keyring_path + ' --import ' + key_contents_path
        code, out = RunGetOutput(cmd, False, False)
    if code != 0:
        LG().Log('ERROR', 'Unable to import Key.  Output is ' + out)
        print('Unable to import Key.  Output is ' + out, file=sys.stderr)
        cleanup()
        return [-1]
    cleanup()
    return [0]


def Test(KeyContents, KeySignature, Ensure):
    if not os.path.isdir(tmpdir):
        if MakeDirs(tmpdir) != None:
            LG().Log('ERROR', "Exception - Unable to creaste " + tmpdir)
            print("Exception - Unable to creaste " + tmpdir, file=sys.stderr)
            return [-1]
    error = None
    with opened_w_error(key_contents_path, 'w+') as (F, error):
        if error:
            LG().Log('ERROR', "Exception opening file " +
                     key_contents_path + " " + str(error))
            print("ERROR: Exception opening file " +
                  key_contents_path + " " + str(error), file=sys.stderr)
            return [-1]
        else:
            F.write(KeyContents)
            F.close()
    cmd = 'HOME=/var/opt/microsoft/omsagent/run ' + gpg_bin + ' --dry-run --options /dev/null --no-default-keyring --keyring ' \
        + dsc_keyring_path + ' --import ' + key_contents_path
    code, out = RunGetOutput(cmd, False, False)
    if code != 0:
        LG().Log('ERROR', '"KeyContents" may be invalid. Output is: ' + out)
        print('ERROR: "KeyContents" may be invalid. Output is: ' + out, file=sys.stderr)
    present = 'not changed' in out

    if ( Ensure == 'present' and not present ) or \
            (Ensure == 'absent' and present):
        cleanup()
        return [-1]
    cleanup()
    return [0]


def Get(KeyContents, KeySignature, Ensure):
    # Get wil not determine the value of Ensure.
    return KeyContents, KeySignature, Ensure


def cleanup():
    if os.path.isdir(tmpdir):
        os.system('rm -rf ' + tmpdir + ' 2>&1 >/dev/null')


def MakeDirs(path):
    error = None
    try:
        os.makedirs(path)
    except OSError as error:
        print("Exception making dir " + path +
              " " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception making dir" + path + " " + str(error))
    except IOError as error:
        print("Exception making dir " + path + " " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception making dir " + path + " " + str(error))
    return error


@contextmanager
def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f=open(filename, mode)
    except IOError as err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()


def RunGetOutput(cmd, no_output, chk_err=True):
    """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT,
    trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    """
    def check_output(no_output, *popenargs, **kwargs):
        r"""Backport from subprocess module from python 2.7"""
        if 'stdout' in kwargs:
            raise ValueError(
                'stdout argument not allowed, it will be overridden.')
        if no_output:
            out_file = None
        else:
            out_file = subprocess.PIPE
        process = subprocess.Popen(stdout=out_file, *popenargs, **kwargs)
        output, unused_err = process.communicate()
        retcode = process.poll()
        if retcode:
            cmd = kwargs.get("args")
            if cmd is None:
                cmd = popenargs[0]
            raise CalledProcessError(retcode, cmd, output=output)
        return output

    # Exception classes used by this module.
    class CalledProcessError(Exception):

        def __init__(self, returncode, cmd, output=None):
            self.returncode = returncode
            self.cmd = cmd
            self.output = output

        def __str__(self):
            return "Command '%s' returned non-zero exit status %d" \
                   % (self.cmd, self.returncode)

    output=b''
    try:
        output = check_output(no_output, cmd, stderr=subprocess.STDOUT, shell=True)
        if output is None:
            output=b''
    except CalledProcessError as e:
        if chk_err:
            print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stdout)
            LG().Log(
                'ERROR', 'CalledProcessError.  Error Code is '
                + str(e.returncode))
            print(
                'CalledProcessError.  Command string was '
                + e.cmd, file=sys.stdout)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command string was ' + e.cmd)
            print('CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('ascii','ignore'), file=sys.stdout)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command result was '
                + (e.output[:-1]).decode('ascii','ignore'))
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, e.output.decode('ascii','ignore')

    if no_output:
        return 0, None
    else:
        return 0, output.decode('ascii','ignore')

#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================

from __future__ import print_function
from __future__ import with_statement
from contextlib import contextmanager

import os
import sys
import imp
import tarfile
import zipfile
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog
try:
    import hashlib
    md5const = hashlib.md5
except ImportError:
    import md5
    md5const = md5.md5

BLOCK_SIZE = 8192
cache_file_dir = '/var/opt/microsoft/dsc/cache/nxArchive/'

# [ClassVersion("1.1.0"),FriendlyName("nxArchive")]
# class OMI_nxArchiveResource : OMI_BaseResource
# {
#   [Key] string SourcePath;
#   [Key] string DestinationPath;
#   [write,ValueMap{"ctime", "mtime", "md5"},Values{"ctime", "mtime","md5"}] string Checksum;
#   [write] boolean Force;
#   [Write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
# };


def init_vars(DestinationPath, SourcePath, Ensure, Force, Checksum):
    if DestinationPath is None:
        DestinationPath = ''
    if SourcePath is None:
        SourcePath = ''
    if Ensure is None or Ensure == '':
        Ensure = 'present'
    if Force is None:
        Force = False
    if Checksum is None or Checksum == '':
        Checksum = 'md5'
    return DestinationPath.encode('ascii', 'ignore'), SourcePath.encode('ascii', 'ignore'), \
        Ensure.encode('ascii', 'ignore').lower(), Force, Checksum.encode(
            'ascii', 'ignore').lower()


def Set_Marshall(DestinationPath, SourcePath, Ensure, Force, Checksum):
    (DestinationPath, SourcePath, Ensure, Force, Checksum) = init_vars(
        DestinationPath, SourcePath, Ensure, Force, Checksum)
    retval = Set(DestinationPath, SourcePath, Ensure, Force, Checksum)
    if retval is False:
        retval = [-1]
    else:
        retval = [0]
    return retval


def Test_Marshall(DestinationPath, SourcePath, Ensure, Force, Checksum):
    (DestinationPath, SourcePath, Ensure, Force, Checksum) = init_vars(
        DestinationPath, SourcePath, Ensure, Force, Checksum)
    retval = Test(DestinationPath, SourcePath, Ensure, Force, Checksum)
    if retval is False:
        retval = [-1]
    else:
        retval = [0]
    return retval


def Get_Marshall(DestinationPath, SourcePath, Ensure, Force, Checksum):
    arg_names = list(locals().keys())
    (DestinationPath, SourcePath, Ensure, Force, Checksum) = init_vars(
        DestinationPath, SourcePath, Ensure, Force, Checksum)
    retval = 0
    (DestinationPath, SourcePath, Ensure, Force, Checksum) = Get(
        DestinationPath, SourcePath, Ensure, Force, Checksum)
    DestinationPath = protocol.MI_String(DestinationPath)
    Ensure = protocol.MI_String(Ensure)
    SourcePath = protocol.MI_String(SourcePath)
    Force = protocol.MI_Boolean(Force)
    Checksum = protocol.MI_String(Checksum)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

############################################################
# Begin user defined DSC functions
############################################################


def LStatFile(path):
    """
    LStat the file.  Do not follow the symlink.
    """
    d = None
    error = None
    try:
        d = os.lstat(path)
    except OSError, error:
        print("Exception lstating file " + path + " Error Code: " + str(error.errno) +
              " Error: " + error.message + error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception lstating file " + path + " Error Code: " + str(error.errno) +
                " Error: " + error.message + error.strerror)
    except IOError, error:
        print("Exception lstating file " + path + " Error Code: " + str(error.errno) +
              " Error: " + error.message + error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception lstating file " + path + " Error Code: " + str(error.errno) +
                " Error: " + error.message + error.strerror)
    return d, error


def MakeDirs(path):
    error = None
    try:
        os.makedirs(path)
    except OSError, error:
        print("Exception making dir" + path + " Error Code: " + str(error.errno) +
              " Error: " + error.message + error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception making dir" + path + " Error Code: " + str(error.errno) +
                " Error: " + error.message + error.strerror)
    except IOError, error:
        print("Exception making dir" + path + " Error Code: " + str(error.errno) +
              " Error: " + error.message + error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception making dir" + path + " Error Code: " + str(error.errno) +
                " Error: " + error.message + error.strerror)
    return error


def RemoveFile(path):
    error = None
    try:
        os.remove(path)
    except OSError, error:
        print("Exception removing file" + path + " Error Code: " + str(error.errno) +
              " Error: " + error.message + error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception removing file" + path + " Error Code: " + str(error.errno) +
                " Error: " + error.message + error.strerror)
    except IOError, error:
        print("Exception removing file" + path + " Error Code: " + str(error.errno) +
              " Error: " + error.message + error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception removing file" + path + " Error Code: " + str(error.errno) +
                " Error: " + error.message + error.strerror)
    return error


@contextmanager
def opened_w_error(filename, mode="rb"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except IOError, err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()


def ReadCacheInfo(SourcePath, DestinationPath):
    cache_file_path = cache_file_dir + \
        SourcePath.replace('/', '_') + DestinationPath.replace('/', '_')
    with opened_w_error(cache_file_path, 'r') as (F, error):
        if error:
            print("Exception opening file " + cache_file_path + " Error Code: " +
                  str(error.errno) + " Error: " + error.message + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file " + cache_file_path + " Error Code: " +
                    str(error.errno) + " Error: " + error.message + error.strerror)
            return False, 0.0, 0.0, ''
        ln = (F.read()).splitlines()
        F.close()
    if len(ln) != 3:
        print("Exception reading file " + cache_file_path, file=sys.stderr)
        LG().Log('ERROR', "Exception reading file " + cache_file_path)
        return False, 0.0, 0.0, ''
    ctime = float(ln[0])
    mtime = float(ln[1])
    chksum = ln[2]
    return True, ctime, mtime, chksum


def WriteCacheInfo(SourcePath, DestinationPath):
    src_hash = md5const()
    src_block = b'loopme'
    with opened_w_error(SourcePath, 'rb') as (src_file, src_error):
        if src_error:
            print("Exception opening source file " + SourcePath + " Error Code: " + str(src_error.errno) +
                  " Error: " + src_error.message + src_error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening source file " + SourcePath + " Error Code: " + str(src_error.errno) +
                    " Error: " + src_error.message + src_error.strerror)
            return -1
        while src_block:
            src_block = src_file.read(BLOCK_SIZE)
            src_hash.update(src_block)
    chksum = src_hash.hexdigest()
    st, error = LStatFile(SourcePath)
    cache_file_path = cache_file_dir + \
        SourcePath.replace('/', '_') + DestinationPath.replace('/', '_')
    with opened_w_error(cache_file_path, 'w+') as (F, error):
        if error:
            print("Exception opening file " + cache_file_path + " Error Code: " +
                  str(error.errno) + " Error: " + error.message + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file " + cache_file_path + " Error Code: " +
                    str(error.errno) + " Error: " + error.message + error.strerror)
            return False
        F.write(
            repr(st.st_ctime) + '\n' + repr(st.st_mtime) + '\n' + chksum + '\n')
        F.close()
    return True


def CompareFileWithCacheFile(SourcePath, DestinationPath, Checksum):
    """
    Reading and computing the hash here is done in a block-by-block manner,
    in case the file is quite large.
    """
    retval, stat_cache_st_ctime, stat_cache_st_mtime, cache_hash = ReadCacheInfo(
        SourcePath, DestinationPath)
    if retval is False:
        return False
    stat_src, error = LStatFile(SourcePath)
    if stat_src is None:
        print("Exception opening SourcePath " + SourcePath + " Error Code: " +
              str(error.errno) + " Error: " + error.message + error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception opening SourcePath " + SourcePath + " Error Code: " +
                str(error.errno) + " Error: " + error.message + error.strerror)
        return False
    if Checksum == "md5":
        src_error = None
        src_hash = md5const()
        src_block = b'loopme'
        with opened_w_error(SourcePath, 'rb') as (src_file, src_error):
            if src_error:
                print("Exception opening source file " + SourcePath + " Error Code: " + str(src_error.errno) +
                      " Error: " + src_error.message + src_error.strerror, file=sys.stderr)
                LG().Log('ERROR', "Exception opening source file " + SourcePath + " Error Code: " + str(src_error.errno) +
                        " Error: " + src_error.message + src_error.strerror)
                return -1
            while src_block:
                src_block = src_file.read(BLOCK_SIZE)
                src_hash.update(src_block)
        if src_hash.hexdigest() == cache_hash:
            return True
        else:
            return False
    elif Checksum == "ctime":
        if stat_src.st_ctime > stat_cache_st_ctime:
            return False
        else:
            return True
    elif Checksum == "mtime":
        if stat_src.st_mtime > stat_cache_st_mtime:
            return False
        else:
            return True


def Set(DestinationPath, SourcePath, Ensure, Force, Checksum):
    # Do nothing.  Set should not get called as previous Test will evaluate to
    # True
    if Ensure == 'absent':
        return True
    # if the sourcepath is not valid file return False
    if not os.path.isfile(SourcePath):
        print('ERROR: SourcePath<' + SourcePath + '> is not a valid file')
        LG().Log('ERROR', 'ERROR: SourcePath<' +
                SourcePath + '> is not a valid file')
        return False
    if not os.path.exists(DestinationPath):
        if MakeDirs(DestinationPath) is not None:
            return False
    if not os.path.isdir(DestinationPath):
        if Force == False:  # Force is False, return False
            print(
                'ERROR: Force must be True if DestinationPath is not a directory.')
            LG().Log(
                'ERROR', 'ERROR: Force must be True if DestinationPath is not a directory.')
            return False
        if RemoveFile(DestinationPath) is not None:  # error
            return False
    # if the dircache is not present create if error return False
    if not os.path.isdir(cache_file_dir):
        if MakeDirs(cache_file_dir) is not None:
            return False
    # is the sourcepath a valid archive?
    archive_type = 'tar'
    ext = os.path.splitext(SourcePath)
    if len(ext) > 1 and ext[1].lower() == '.zip':
        archive_type = 'zip'
    if archive_type == 'zip':
        try:
            arch = zipfile.ZipFile(SourcePath)
            # Exploit check - make sure no names start with '/' or '..'
            for n in arch.namelist():
                if n.startswith('/') or n.startswith('..'):
                    raise Exception(
                        'Error: corrupted filename "' + n + '" in zipfile!')
            bad = arch.testzip()
            if bad is not None:
                raise Exception('Error: First bad filename is "' + bad + '"')
        except Exception, error:
            print("Exception opening zipfile" + SourcePath +
                  " Error: " + error.message, file=sys.stderr)
            LG().Log('ERROR', "Exception opening zipfile" + SourcePath +
                    " Error: " + error.message)
            return False
        # extract archive to destinationpath if error return False
        try:
            arch.extractall(DestinationPath)
        except Exception, error:
            print("Exception extracting zipfile" + SourcePath + " to " +
                  DestinationPath + " Error: " + error.message, file=sys.stderr)
            LG().Log('ERROR', "Exception extracting zipfile" + SourcePath + " to " +
                    DestinationPath + " Error: " + error.message)
            return False
    else:  # tarfile
        if not tarfile.is_tarfile(SourcePath):
            print(
                'ERROR: SourcePath<' + SourcePath + '> is not a valid tarfile')
            LG().Log('ERROR', 'ERROR: SourcePath<' +
                    SourcePath + '> is not a valid tarfile')
        arch = None
        try:
            arch = tarfile.open(SourcePath, 'r')
        except Exception, error:
            if arch is not None:
                arch.close()
            print("Exception opening tarfile" + SourcePath +
                  " Error: " + error.message, file=sys.stderr)
            LG().Log('ERROR', "Exception opening tarfile" + SourcePath +
                    " Error: " + error.message)
            return False
        for n in arch.getnames():
            if n.startswith('/') or n.startswith('..'):
                arch.close()
                raise Exception(
                    'Error: corrupted filename "' + n + '" in tarfile!')
        try:
            arch.extractall(DestinationPath)
        except Exception, error:
            arch.close()
            print("Exception extracting tarfile" + SourcePath + " to " +
                  DestinationPath + " Error: " + error.message, file=sys.stderr)
            LG().Log('ERROR', "Exception extracting tarfile" + SourcePath + " to " +
                    DestinationPath + " Error: " + error.message)
            return False
        arch.close()
        os.system('touch '+DestinationPath) # existing dirs won't get an updated time, so update it.
    if WriteCacheInfo(SourcePath, DestinationPath) is False:
        return False
    return True


def Test(DestinationPath, SourcePath, Ensure, Force, Checksum):
    if not os.path.isdir(cache_file_dir):
        return False
    if not os.path.isfile(SourcePath):
        return False
    if not os.path.isdir(DestinationPath):
        return False
    if CompareFileWithCacheFile(SourcePath, DestinationPath, Checksum) is True:
        if Ensure == 'present':
            return True
        else:
            return False
    else:
        if Ensure == 'present':
            return False
        else:
            return True


def Get(DestinationPath, SourcePath, Ensure, Force, Checksum):
    if Test(DestinationPath, SourcePath, Ensure, Force, Checksum) is False:
        Ensure = 'absent'
    else:
        Ensure = 'present'
    return DestinationPath, SourcePath, Ensure, Force, Checksum

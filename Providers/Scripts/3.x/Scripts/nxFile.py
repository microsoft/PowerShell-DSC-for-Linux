#!/usr/bin/env python
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
#  See license.txt for license information.
# ====================================

from contextlib import contextmanager

import os
import sys
import pwd
import shutil
import grp
import codecs
import urllib.request
import time
import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
helperlib = imp.load_source('helperlib', '../helperlib.py')

LG = nxDSCLog.DSCLog
try:
    import hashlib
    md5const = hashlib.md5
except ImportError:
    import md5
    md5const = md5.md5

BLOCK_SIZE = 8192

global show_mof
show_mof = False
RemoteFileRetryCount = 5
RemoteFileRetryInterval = 10


def init_locals(DestinationPath, SourcePath, Ensure, Type, Force, Contents,
                Checksum, Recurse, Links, Owner, Group, Mode):
    if DestinationPath is None :
        DestinationPath = ''
    if SourcePath is None :
        SourcePath = ''
    if Ensure is None or Ensure == '':
        Ensure = 'present'
    if Type is None :
        Type = 'file'
    if Force is None :
        Force = False
    if Contents is None :
        Contents = ''
    if Checksum is None :
        Checksum = ''
    if Recurse is None :
        Recurse = False
    if Links is None :
        Links = 'follow'
    if Owner is None :
        Owner = ''
    if Group is None :
        Group = ''
    if Mode is None :
        Mode = ''

    return DestinationPath, SourcePath, \
        Ensure.lower(), Type.lower(), Force,\
        Contents, Checksum.lower(), Recurse, \
        Links.lower(), Owner, Group, Mode


def Set_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode \
                     = init_locals(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    retval = Set(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    return retval


def Test_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode \
                     = init_locals(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    retval = Test(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    return retval


def Get_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    arg_names = list(locals().keys())
    DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode \
            = init_locals(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    retval = 0
    (retval, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate) \
            = Get(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    DestinationPath = protocol.MI_String(DestinationPath)
    SourcePath = protocol.MI_String(SourcePath)
    Ensure = protocol.MI_String(Ensure)
    Type = protocol.MI_String(Type)
    Force = protocol.MI_Boolean(Force)
    Contents = protocol.MI_String(Contents)
    Checksum = protocol.MI_String(Checksum)
    Recurse = protocol.MI_Boolean(Recurse)
    Links = protocol.MI_String(Links)
    Owner = protocol.MI_String(Owner)
    Group = protocol.MI_String(Group)
    Mode = protocol.MI_String(Mode)
    ModifiedDate = protocol.MI_Timestamp.from_time(ModifiedDate)
    arg_names.append('ModifiedDate')
    retd = {}
    ld = locals()
    for k in arg_names :
        retd[k] = ld[k]
    return retval, retd

# ###########################################################
# Begin user defined DSC functions
# ###########################################################

@contextmanager
def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, encoding='utf8', mode=mode)
    except IOError as err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()


@contextmanager
def opened_bin_w_error(filename, mode="rb"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except IOError as err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()


def ReadFile1k(path):
    """
    Safely attempt to read a file,
    ensuring file is always closed at exit.
    Read only 1k.
    Return the data and the exception object.
    The data is None if an error occurred.
    The error is None if the data was read.
    Log results to stderr.
    """
    d = None
    error = None
    with opened_bin_w_error(path) as (F, error):
        if error:
            print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error. strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
        else:
            d = F.read(1024)
    return d, error


def ReadFile(path):
    """
    Safely attempt to read a file,
    ensuring file is always closed at exit.
    Return the data and the exception object.
    The data is None if an error occurred.
    The error is None if the data was read.
    Log results to stderr.
    """
    d = None
    error = None
    with opened_w_error(path, 'r') as (F, error):
        if error:
            print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr )
            LG().Log('ERROR', "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        else:
            d = F.read()
    return d, error


def WriteFile(path, contents):
    """
    Safely attempt to write data to a file,
    replacing the existing file or creating it and
    ensuring file is always closed at exit.
    Return the exception object.
    The error is None if the data was written.
    Log results to stderr.
    """
    error = None
    with opened_w_error(path, 'w+') as (F, error):
        if error:
            print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " +error.strerror)
        else:
            F.write(contents)
    return error


def LStatFile(path):
    """
    LStat the file.  Do not follow the symlink.
    """
    d = None
    error = None
    try:
        d=os.lstat(path)
    except OSError as error:
         print("Exception lstating file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
         LG().Log('ERROR', "Exception lstating file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
    except IOError as error:
         print("Exception lstating file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
         LG().Log('ERROR', "Exception lstating file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
    return d


def StatFile(path):
    """
    Stat the file, following the symlink.
    """
    d = None
    error = None
    try:
        d=os.stat(path)
    except OSError as error:
        print("Exception stating file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception stating file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
    except IOError as error:
        print("Exception stating file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception stating file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
    return d


def Chown(path, owner, group):
    error = None
    try:
        os.chown(path,owner,group)
    except OSError as error:
        print("Exception changing ownership of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception changing ownership of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception changing ownership of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception changing ownership of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def Chmod(path, mode):
    error = None
    if type(mode) != int:
        mode = int(mode, 8)
    try:
        os.chmod(path,mode)
    except OSError as error:
        print("Exception  changing mode of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception  changing mode of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception  changing mode of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception  changing mode of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def LChown(path, owner, group):
    error = None
    try:
        os.lchown(path,owner,group)
    except OSError as error:
        print("Exception changing ownership of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception changing ownership of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception changing ownership of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception changing ownership of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def LChmod(path, mode):
    error = None
    try:
        os.lchmod(path,mode)
    except OSError as error:
        print("Exception  changing mode of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception  changing mode of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception  changing mode of file " + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception  changing mode of file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def ListDir(path):
    d = None
    error = None
    try:
        d = os.listdir(path)
    except OSError as error:
        print("Exception listing dir" + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception listing dir " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
    except IOError as error:
        print("Exception listing dir" + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception listing dir " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
    return d


def Symlink(spath, dpath):
    error = None
    if spath == dpath:  # Nothing to Link
        return error

    # remove the destination if present
    if os.path.exists(dpath):
        try:
            os.unlink(dpath)
        except OSError as error:
            print("Exception removing " + dpath + " Error Code: " + str(error.errno) +  " Error Code: " + str(error.errno) + " Error: "  + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception removing " + dpath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
            return error
        except IOError as error:
            print("Exception removing " + dpath + " Error Code: " + str(error.errno) +  " Error Code: " + str(error.errno) + " Error: "  + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception removing " + dpath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
            return error
    try:
        os.symlink(spath, dpath)
    except OSError as error:
        print("Exception creating symlink from " + spath  + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception creating symlink from " + spath + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception creating symlink from " + spath  + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception creating symlink from " + spath + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def MakeDirs(path):
    error = None
    try:
        os.makedirs(path)
    except OSError as error:
        print("Exception making dir" + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception making dir" + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception making dir" + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception making dir" + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def RemoveFile(path):
    error = None
    try:
        os.remove(path)
    except OSError as error:
        print("Exception removing file" + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception removing file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception removing file" + path  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception removing file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def CopyFile(spath, dpath):
    error = None
    if spath == dpath:  # Nothing to copy!
        return error
    try:
        shutil.copyfile(spath,dpath)
    except OSError as error:
        print("Exception copying tree " + spath  + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception copying tree " + spath + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception copying tree " + spath  + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception copying tree " + spath + ' to ' + dpath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def CompareFiles(DestinationPath, SourcePath, Checksum):
    """
    If the files differ in size, return -1.
    Reading and computing the hash here is done in a block-by-block manner,
    in case the file is quite large.
    """
    if SourcePath == DestinationPath:  # Files are the same!
        return 0
    stat_dest = StatFile(DestinationPath)
    stat_src = StatFile(SourcePath)
    if stat_src.st_size != stat_dest.st_size:
        return -1
    if Checksum == "md5":
        src_error = None
        dest_error = None
        src_hash = md5const()
        dest_hash = md5const()
        src_block = b'loopme'
        dest_block = b'loopme'
        with opened_bin_w_error(SourcePath, 'rb') as (src_file, src_error):
            if src_error:
                print("Exception opening source file " + SourcePath  + " Error Code: " + str(src_error.errno) +
                      " Error: " + src_error.strerror, file=sys.stderr)
                LG().Log('ERROR', "Exception opening source file " + SourcePath + " Error Code: " + str(src_error.errno) +
                        " Error: " + src_error.strerror)
                return -1
            with opened_bin_w_error(DestinationPath, 'rb') as (dest_file, dest_error):
                if dest_error:
                    print("Exception opening destination file " + DestinationPath + " Error Code: " + str(dest_error.errno) +
                          " Error: " + dest_error.strerror, file=sys.stderr)
                    LG().Log('ERROR', "Exception opening destination file " + DestinationPath + " Error Code: " + str(dest_error.errno) +
                          " Error: " + dest_error.strerror)
                    return -1
                while src_block or dest_block :
                    src_block = src_file.read(BLOCK_SIZE)
                    dest_block = dest_file.read(BLOCK_SIZE)
                    src_hash.update(src_block)
                    dest_hash.update(dest_block)
                    if src_hash.hexdigest() != dest_hash.hexdigest():
                        return -1
        if src_hash.hexdigest() == dest_hash.hexdigest():
            return 0
    elif Checksum == "ctime":
        if stat_src.st_ctime != stat_dest.st_ctime:
            return -1
        else:
            return 0
    elif Checksum == "mtime":
        if stat_src.st_mtime != stat_dest.st_mtime:
            return -1
        else:
            return 0


def RemoveTree(path):
    error = None
    try:
        shutil.rmtree(path)
    except OSError as error:
        print("Exception removing folder " + path + " Error Code: "
              + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception removing folder " + path + " Error Code: " +
              str(error.errno) + " Error: " + error.strerror)
        return error
    except IOError as error:
        print("Exception removing folder " + path + " Error Code: "
              + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
        LG().Log('ERROR', "Exception removing folder " + path + " Error Code: " +
              str(error.errno) + " Error: " + error.strerror)
        return error
    return error


def RemovePath(path):
    error = None
    if os.path.islink(path) or os.path.isfile(path):
        error = RemoveFile(path)
    elif os.path.isdir(path):
        error = RemoveTree(path)
    else:
        print("Error: Unknown file type for file: " + path, file=sys.stderr)
        LG().Log('ERROR', "Error: Unknown file type for file: " + path)
    return error


def TestOwnerGroupMode(DestinationPath, SourcePath, fc):
    stat_info = LStatFile(DestinationPath)
    if stat_info is None :
        return False

    if SourcePath:
        stat_info_src = LStatFile(SourcePath)
        if stat_info_src is None :
            return False

    if fc.Owner:
        try:
            Specified_Owner_ID = pwd.getpwnam(fc.Owner)[2]
        except KeyError as error:
            print("Exception obtaining gid from group name " + fc.Group  + " Error: " + repr(error), file=sys.stderr)
            LG().Log('ERROR', "Exception obtaining gid from group name " + fc.Group + " Error: " + repr(error))
            return False
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            return False
    elif SourcePath:
        # Owner wasn't specified, if SourcePath is specified then check that the Owners match
        if pwd.getpwuid(stat_info.st_uid)[2] != pwd.getpwuid(stat_info_src.st_uid)[2]:
            return False

    if fc.Group:
        try:
            Specified_Group_ID = grp.getgrnam(fc.Group)[2]
        except KeyError as error:
            print("Exception obtaining gid from group name " + fc.Group  + " Error: " +  repr(error), file=sys.stderr)
            LG().Log('ERROR', "Exception obtaining gid from group name " + fc.Group + " Error: " + repr(error))
            return False
        if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
            return False
    elif SourcePath:
        # Group wasn't specified, if SourcePath is specified then check that the Groups match
        if grp.getgrgid(stat_info.st_gid)[2] != grp.getgrgid(stat_info_src.st_gid)[2]:
            return False
    # Mode is irrelevant to symlinks
    if not os.path.islink(DestinationPath):
        if fc.Mode:
            if str(oct(stat_info.st_mode))[-3:] != fc.Mode:
                return False
        elif SourcePath:
            # Mode wasn't specified, if SourcePath is specified then check that the Modes match
            if str(oct(stat_info.st_mode))[-3:] != str(oct(stat_info_src.st_mode))[-3:]:
                return False
    return True


def ConvertLongModeToNumeric(Mode):
    u_r = Mode[0]
    u_w = Mode[1]
    u_x = Mode[2]
    g_r = Mode[3]
    g_w = Mode[4]
    g_x = Mode[5]
    o_r = Mode[6]
    o_w = Mode[7]
    o_x = Mode[8]
    first_digit = 0
    second_digit = 0
    third_digit = 0
    if u_r == "r":
        first_digit += 4
    elif u_r == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 0 in Mode")

    if u_w == "w":
        first_digit += 2
    elif u_w == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 1 in Mode")

    if u_x == "x":
        first_digit += 1
    elif u_x == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 2 in Mode")

    if g_r == "r":
        second_digit += 4
    elif g_r == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 3 in Mode")

    if g_w == "w":
        second_digit += 2
    elif g_w == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 4 in Mode")

    if g_x == "x":
        second_digit += 1
    elif g_x == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 5 in Mode")

    if o_r == "r":
        third_digit += 4
    elif o_r == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 6 in Mode")

    if o_w == "w":
        third_digit += 2
    elif o_w == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 7 in Mode")

    if o_x == "x":
        third_digit += 1
    elif o_x == "-":
        pass
    else:
        raise Exception("Error: Invalid character for character 8 in Mode")

    return str(first_digit) + str(second_digit) + str(third_digit)


def SetOwnerGroupMode(DestinationPath, SourcePath, fc):
    stat_info = LStatFile(DestinationPath)
    if stat_info is None :
        return False

    if SourcePath:
        stat_info_src = LStatFile(SourcePath)
        if stat_info_src is None:
            return False

    if fc.Owner:
        Specified_Owner_ID = pwd.getpwnam(fc.Owner)[2]
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            print("Changing owner of " + DestinationPath + " to " + str(Specified_Owner_ID))
            LG().Log('INFO', "Changing owner of " + DestinationPath + " to " + str(Specified_Owner_ID))
            if LChown(DestinationPath, Specified_Owner_ID, -1) is not None :
                return False

    elif SourcePath:
        src_uid = pwd.getpwuid(stat_info_src.st_uid)[2]
        if pwd.getpwuid(stat_info.st_uid)[2] != src_uid:
            print("Changing owner of " + DestinationPath + " to " + str(src_uid))
            LG().Log('INFO', "Changing owner of " + DestinationPath + " to " + str(src_uid))
            if LChown(DestinationPath, src_uid, -1) is not None :
                return False

    if fc.Group:
        Specified_Group_ID = grp.getgrnam(fc.Group)[2]
        if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
            print("Changing group of " + DestinationPath + " to " + str(Specified_Group_ID))
            LG().Log('INFO', "Changing group of " + DestinationPath + " to " + str(Specified_Group_ID))
            if LChown(DestinationPath, -1, Specified_Group_ID) is not None :
                return False

    elif SourcePath:
        src_gid = grp.getgrgid(stat_info_src.st_gid)[2]
        if grp.getgrgid(stat_info.st_gid)[2] != src_gid:
            print("Changing group of " + DestinationPath + " to " + str(src_gid))
            LG().Log('INFO', "Changing group of " + DestinationPath + " to " + str(src_gid))
            if LChown(DestinationPath, src_gid , -1) is not None :
                return False

    # Mode is irrelevant to symlinks
    if not os.path.islink(DestinationPath):
        if fc.Mode:
            if str(oct(stat_info.st_mode))[-3:] != fc.Mode:
                print("Changing mode of " + DestinationPath + " to " + fc.Mode)
                LG().Log('INFO', "Changing mode of " + DestinationPath + " to " + fc.Mode)
                if Chmod(DestinationPath, fc.Mode) is not None :
                    return False
        elif SourcePath:
            src_mode = str(oct(stat_info_src.st_mode))[-3:]
            if str(oct(stat_info.st_mode))[-3:] != src_mode:
                print("Changing mode of " + DestinationPath + " to " + src_mode)
                LG().Log('INFO', "Changing mode of " + DestinationPath + " to " + src_mode)
                if Chmod(DestinationPath, src_mode) is not None :
                    return False
    return True


def SetDirectoryRecursive(DestinationPath, SourcePath, fc):
    if not os.path.exists(DestinationPath):
        if MakeDirs(DestinationPath) is not None:
            return False
    if SetOwnerGroupMode(DestinationPath, SourcePath, fc) is False:
        return False
    Destination_subfiles = ListDir(DestinationPath)
    if Destination_subfiles is None:
        return False
    if not SourcePath:
        if not fc.Recurse :
            return True

        # Enforce Owner/Group/Mode specified
        for f in Destination_subfiles:
            f_destpath = os.path.join(DestinationPath, f)
            if not os.path.islink(f_destpath):
                if os.path.isfile(f_destpath):
                    if SetOwnerGroupMode(f_destpath, "", fc) is False :
                        return False
                elif os.path.isdir(f_destpath):
                    if SetDirectoryRecursive(f_destpath, "", fc) is False :
                        return False
        return True

    Source_subfiles = ListDir(SourcePath)
    # For all files in SourcePath's directory, ensure they exist with proper contents and stat in DestionationPath's directory
    for f in Source_subfiles:
        f_srcpath = os.path.join(SourcePath, f)
        f_destpath = os.path.join(DestinationPath, f)

        if os.path.islink(f_srcpath):
            if TestLink(f_destpath, f_srcpath, fc) is False:
                if SetLink(f_destpath, f_srcpath, fc) is False:
                    return False
        elif os.path.isfile(f_srcpath):
            if TestFile(f_destpath, f_srcpath, fc) is False:
                if SetFile(f_destpath, f_srcpath, fc) is False:
                    return False
        elif os.path.isdir(f_srcpath):
            if fc.Recurse :
                if SetDirectoryRecursive(f_destpath, f_srcpath, fc) is False:
                    return False
    return True


def SetFile(DestinationPath, SourcePath, fc):
    error = None
    if os.path.exists(DestinationPath) and (os.path.islink(DestinationPath) or os.path.isdir(DestinationPath)):
        if fc.Force :
            if RemovePath(DestinationPath) is not None:
                return False
        else:
            print("Error: " + DestinationPath + " is not a file; cannot overwrite without the 'Force' option being true")
            LG().Log("ERROR", DestinationPath + " is not a file; cannot overwrite without the 'Force' option being true")
            return False
    if SourcePath and len(SourcePath) > 0:
        if '://' in SourcePath and fc.LocalPath == '':
            ret = GetRemoteFileWithRetries(fc)
            if ret != 0:
                raise Exception('Unable to retrieve remote resource '+fc.SourcePath+' Error is ' + str(ret))
            else:
                SourcePath = fc.LocalPath
        should_copy_file = False
        if os.path.isfile(DestinationPath):
            if CompareFiles(DestinationPath, SourcePath,  fc.Checksum) == -1:
                should_copy_file = True
            else:
                should_copy_file = False
        else:
            should_copy_file = True
        if should_copy_file:
            if CopyFile(SourcePath, DestinationPath) is not None :
                return False
    elif fc.Contents:
        if WriteFile(DestinationPath, fc.Contents) is not None:
            print("Error: Unable to write file at " + DestinationPath)
            LG().Log("ERROR", "Unable to write file at " + DestinationPath)
            return False
    else:
        # Create a file with nothing in it
        try:
            open(DestinationPath, 'a').close()
        except OSError as error:
            print("Exception creating file " + DestinationPath  + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception creating file " + DestinationPath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
        except IOError as error:
            print("Exception creating file " + DestinationPath + " Error Code: " + str(error.errno) + " Error: " +error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception creating file " + DestinationPath + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
    SetOwnerGroupMode(DestinationPath, SourcePath, fc)
    if len(fc.LocalPath) > 0 :
        if RemoveFile(fc.LocalPath) is not None:
            return False
    return True


def SetDirectory(DestinationPath, SourcePath, fc):
    if os.path.exists(DestinationPath) and not os.path.isdir(DestinationPath):
        if fc.Force :
            if RemovePath(DestinationPath) is not None:
                return False
        else:
            print("Error: Unable to overwrite currently existing non-directory object at " + DestinationPath + " without the Force option being true.")
            LG().Log("ERROR", "Unable to overwrite currently existing non-directory object at " + DestinationPath + " without the Force option being true.")
            return False

    return SetDirectoryRecursive(DestinationPath, SourcePath, fc)


def SetLink(DestinationPath, SourcePath, fc):
    if SourcePath is None or len(SourcePath) < 1 or not os.path.exists(SourcePath) :
        print("Error: Need a valid source path in order to create a new symbolic link.")
        LG().Log("ERROR", "Need a valid source path in order to create a new symbolic link.")
        return False

    if os.path.exists(DestinationPath) and not os.path.islink(DestinationPath) :
        if fc.Force :
            if RemovePath(DestinationPath) is not None:
                return False
        else:
            print("Error: Unable to overwrite currently existing non-link object at " + DestinationPath + " without the Force option being true.")
            LG().Log("ERROR", "Unable to overwrite currently existing non-link object at " + DestinationPath + " without the Force option being true.")
            return False

    if os.path.islink(SourcePath):
        if fc.Links == "follow":
            if os.path.isfile(SourcePath):
                if SetFile(DestinationPath, os.path.realpath(SourcePath), fc) is False:
                    return False
            elif os.path.isdir(SourcePath):
                if SetDirectoryRecursive(DestinationPath, os.path.realpath(SourcePath), fc) is False:
                    return False

        elif fc.Links == "manage":
            if Symlink(os.readlink(SourcePath), DestinationPath) is not None:
                return False

        elif fc.Links == "ignore":
            # Ignore all symlinks
            return True
    else:
        if Symlink(SourcePath, DestinationPath) is not None:
            return False
    SetOwnerGroupMode(DestinationPath, SourcePath, fc)
    return True


def SetShowMof(a):
    global show_mof
    show_mof = a


def ShowMof(op, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    if not show_mof:
        return
    mof = ''
    mof += op + ' nxFile MyFile\n'
    mof += '{\n'
    mof += '    DestinationPath = "' + DestinationPath + '"\n'
    mof += '    SourcePath = "' + SourcePath + '"\n'
    mof += '    Ensure = "' + Ensure + '"\n'
    mof += '    Type = "' + Type + '"\n'
    mof += '    Force = ' + str(Force) + '\n'
    mof += '    Contents = "' + Contents + '"\n'
    mof += '    Checksum = "' + Checksum + '"\n'
    mof += '    Recurse = ' + str(Recurse) + '\n'
    mof += '    Links = "' + Links + '"\n'
    mof += '    Group = "' + Group + '"\n'
    mof += '    Mode = "' + Mode + '"\n'
    mof += '    Owner = "' + Owner + '"\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    print(mof, file=f)
    LG().Log('INFO', mof)
    f.close()


def Set(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    ShowMof('SET', DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    fc = FileContext(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    if not DestinationPath:
        return [-1]

    if fc.Ensure == "present":
        if fc.Type == "file":
            if SetFile(DestinationPath, SourcePath, fc) is False:
                return [-1]
        elif fc.Type == "directory":
            if SetDirectory(DestinationPath, SourcePath, fc) is False:
                return [-1]
        elif fc.Type == "link":
            if SetLink(DestinationPath, SourcePath, fc) is False:
                return [-1]

    elif fc.Ensure == "absent":
        if RemovePath(DestinationPath) is not None:
            return [-1]

    return [0]


def TestDirectory(DestinationPath, SourcePath, fc):
    if not os.path.exists(DestinationPath) or not os.path.isdir(DestinationPath):
        return False

    if TestOwnerGroupMode(DestinationPath, SourcePath, fc) is False:
        return False

    if fc.Recurse is False:
        return True

    Destination_subfiles = ListDir(DestinationPath)
    if Destination_subfiles is None:
        return False

    if not SourcePath:
        # Enforce Owner/Group/Mode specified
        for f in Destination_subfiles:
            f_destpath = os.path.join(DestinationPath, f)
            if not os.path.islink(f_destpath):
                if os.path.isfile(f_destpath):
                    if TestOwnerGroupMode(f_destpath, "", fc) is False:
                        return False
                elif os.path.isdir(f_destpath):
                    if TestDirectory(f_destpath, "", fc) is False:
                        return False
        return True

    Source_subfiles = ListDir(SourcePath)
    if Source_subfiles is None:
        return False

    for f in Source_subfiles:
        if f not in Destination_subfiles:
            print("File: " + f + " does not exist in: " + SourcePath)
            LG().Log('ERROR', "File: " + f + " does not exist in: " + SourcePath)
            return False

        f_destpath = os.path.join(DestinationPath, f)
        f_srcpath = os.path.join(SourcePath, f)

        if os.path.islink(f_srcpath):
            if TestLink(f_destpath, f_srcpath, fc) is False:
                return False
        elif os.path.isfile(f_srcpath):
            if TestFile(f_destpath, f_srcpath, fc) is False:
                return False
        elif os.path.isdir(f_srcpath):
            if TestDirectory(f_destpath, f_srcpath, fc) is False:
                return False

    return True


def TestFile(DestinationPath, SourcePath, fc):
    if not os.path.exists(DestinationPath) or not os.path.isfile(DestinationPath) or os.path.islink(DestinationPath):
        return False

    if '://' in SourcePath:
        return TestRemoteFileWithRetries(fc)

    if TestOwnerGroupMode(DestinationPath, SourcePath, fc) is False:
        return False

    if SourcePath and len(SourcePath) > 0:
        if not os.path.isfile(SourcePath):
            return False

        if os.path.islink(SourcePath):
            if fc.Links == "follow":
                if os.path.isdir(os.path.realpath(SourcePath)):
                    print("Error: Expecting a file, but source link points to directory")
                    LG().Log("ERROR", "Expecting a file, but source link points to directory")
                    return False
            else:
                if not os.path.islink(DestinationPath):
                    return False
                if os.readlink(DestinationPath) != os.readlink(SourcePath):
                    return False
        elif CompareFiles(DestinationPath, SourcePath,  fc.Checksum) == -1:
            return False

    elif fc.Contents:
        dest_file, error = ReadFile(DestinationPath)
        if fc.Contents.encode('utf8') != dest_file:
            return False

    return True


def TestLink(DestinationPath, SourcePath, fc):
    if SourcePath:
        if os.path.islink(SourcePath):
            if fc.Links == "follow":
                if os.path.isdir(SourcePath):
                    if TestDirectory(DestinationPath, os.path.realpath(SourcePath), fc) is False:
                        return False
                elif os.path.isfile(SourcePath):
                    if TestFile(DestinationPath, os.path.realpath(SourcePath), fc) is False:
                        return False
            elif fc.Links == "manage":
                if not os.path.islink(DestinationPath):
                    return False

                if os.readlink(DestinationPath) != os.readlink(SourcePath):
                    return False
            elif fc.Links == "ignore":
                return True
        else:
            if not os.path.exists(DestinationPath) or not os.path.exists(SourcePath) or not os.path.islink(DestinationPath) :
                return False
            if os.readlink(DestinationPath) != SourcePath:
                return False
    if os.path.exists(DestinationPath) != True:
        return False          
    if TestOwnerGroupMode(DestinationPath, SourcePath, fc) is False:
        return False

    return True


def Test(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    ShowMof('TEST', DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    fc = FileContext(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    if not DestinationPath:
        return [-1]

    if fc.Ensure == "present":
        if fc.Type == "file":
            if TestFile(DestinationPath, SourcePath, fc) is False:
                return [-1]
        elif fc.Type == "directory":
            if TestDirectory(DestinationPath, SourcePath, fc) is False:
                return [-1]
        elif fc.Type == "link":
            if TestLink(DestinationPath, SourcePath, fc) is False:
                return [-1]
    elif fc.Ensure == "absent":
        if os.path.exists(DestinationPath):
            return [-1]

        return [0]

    return [0]


def Get(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    ShowMof('GET', DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    if '://' in SourcePath and Type != 'file':
        raise Exception('ERROR: Remote paths are only valid for Type = "file".')
    if not DestinationPath:
        Ensure = "absent"
        ModifiedDate = 0
        return [-1, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]

    if not os.path.exists(DestinationPath):
        Ensure = "absent"
        ModifiedDate = 0
        return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]

    Ensure = "present"
    stat_info = os.lstat(DestinationPath)

    Owner = pwd.getpwuid(stat_info.st_uid)[0]
    Group = grp.getgrgid(stat_info.st_gid)[0]
    Mode = str(oct(stat_info.st_mode))[-3:]
    if os.path.islink(DestinationPath):
        Type = "link"
    elif os.path.isfile(DestinationPath):
        Type = "file"
    elif os.path.isdir(DestinationPath):
        Type = "directory"
    ModifiedDate = stat_info.st_mtime
    if Type == "directory":
        Contents = repr(ListDir(DestinationPath))
    elif Type == 'link':
        if Links == 'manage' :
            Contents = LStatFile(DestinationPath)
            Contents = repr(Contents)
        elif Links == 'follow':
            if os.path.isdir(os.readlink(DestinationPath)):
                Contents = repr(ListDir(DestinationPath))
            else:
                Contents, error = ReadFile1k(DestinationPath)
    else :
        Contents, error = ReadFile1k(DestinationPath)

    if Contents is None:
        Contents = ''

    return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]


def GetTimeFromString(s):
    if s is None or len(s) == 0:
        return None
    fmt = []
    fmt.append('%a, %d %b %Y %H:%M:%S %Z')
    st = None
    for f in fmt:
        try:
            st = time.strptime(s, f)
        except ValueError:
            continue
    return st


def SetProxyFromConf():
    """
    Check for PROXY definition in dsc.conf.
    All we must do is set the appropriate value in the environment.
    HTTP_PROXY
    HTTPS_PROXY
    """
    path = helperlib.CONFIG_SYSCONFDIR + '/' + helperlib.CONFIG_SYSCONFDIR_DSC + '/dsc.conf'
    txt, error = ReadFile(path)
    if error :
        return
    for l in txt.splitlines():
        if l.startswith('PROXY'):
            info = l.split('=')[1].strip()
            if 'https' in info:
                os.environ['HTTPS_PROXY'] = info
            if 'http:' in info:
                os.environ['HTTP_PROXY'] = info
    return

def GetRemoteFileWithRetries(fc):
    retryCount = 0
    ret = 1
    while True:
      try:
          ret = GetRemoteFile(fc)
      except  urllib.error.URLError as e:
          print("Exception encountered when getting Remote File '" + fc.SourcePath  + "', No Retry attempts will be done - " + repr(e))
          LG().Log('ERROR', "Exception encountered when getting Remote File '" + fc.SourcePath  + "', No Retry attempts will be done - " + repr(e))
          if hasattr(e, 'code'):
             # Client code are not likely to succeed on retry
             if e.code >= 400 and e.code < 500:
                return 1
      retryCount = retryCount + 1	
      if ret == 0 or retryCount > RemoteFileRetryCount:
         return ret
      print("Exception encountered when getting Remote File, Sleeping for " + str(RemoteFileRetryInterval) + " seconds Then Retrying again")
      LG().Log('ERROR', "Exception encountered when getting Remote File, Sleeping for " + str(RemoteFileRetryInterval) + " seconds Then Retrying again")
      time.sleep(RemoteFileRetryInterval)
      
    return ret
        
def GetRemoteFile(fc):
    SetProxyFromConf()
    req = urllib.request.Request(fc.SourcePath)
    resp = urllib.request.urlopen(req)
    fc.LocalPath = '/tmp/'+os.path.basename(fc.DestinationPath)+'_remote'
    data=b'keep going'
    hasWritten = False
    with (open(fc.LocalPath, 'wb+')) as F:
        try:
            while data:
                data = resp.read(1048576)
                if data is not None and len(data) > 0:
                    hasWritten = True
                    F.write(data)
            if hasWritten == False:
                LG().Log('ERROR', "Data at URL: " + fc.SourcePath + " was empty. Please ensure this file exists at this remote location.")
                F.close()
                os.unlink(fc.LocalPath)
                return 1
        except Exception as e:
            F.close()
            os.unlink(fc.LocalPath)
            print(repr(e))
            LG().Log('ERROR', repr(e))
            return 1
    return 0

def TestRemoteFileWithRetries(fc):
    retryCount = 0
    ret = False
    while True:
      try:
          ret = TestRemoteFile(fc)
      except  urllib.error.URLError as e:
          print("Exception encountered when getting Remote File '" + fc.SourcePath  + "', No Retry attempts will be done - " + repr(e))
          LG().Log('ERROR', "Exception encountered when getting Remote File '" + fc.SourcePath  + "', No Retry attempts will be done - " + repr(e))
          if hasattr(e, 'code'):
             # Client code are not likely to succeed on retry
             if e.code >= 400 and e.code < 500:
                return 1
      retryCount = retryCount + 1	
      if ret or retryCount > RemoteFileRetryCount:
         return ret
      print("ERROR encountered when getting Remote File "+ fc.SourcePath  + " Sleeping for " + str(RemoteFileRetryInterval) + " seconds Then Retrying again")
      LG().Log('ERROR', "ERROR encountered when getting Remote File "+ fc.SourcePath  + " Sleeping for " + str(RemoteFileRetryInterval) + " seconds Then Retrying again")
      time.sleep(RemoteFileRetryInterval)

    return ret

def TestRemoteFile(fc):
    SetProxyFromConf()
    req = urllib.request.Request(fc.SourcePath)
    resp = urllib.request.urlopen(req)
    h = resp.info()
    if fc.Checksum != 'md5' :  # if not 'md5' check the last_modified header time before we download
        lm = h.get('last-modified')
        remote_mtime = GetTimeFromString(lm)
        destination_mtime = None
        dst_st = None
        if os.path.exists(fc.DestinationPath):
            dst_st = LStatFile(fc.DestinationPath)
        if dst_st is not None:
            if fc.Checksum == 'ctime':
                destination_mtime = time.gmtime(dst_st.st_ctime)
            else:
                destination_mtime = time.gmtime(dst_st.st_mtime)
        if remote_mtime is not None and destination_mtime is not None and destination_mtime >= remote_mtime:
            return True
        else:
            return False
    #md5
    if not os.path.exists(fc.DestinationPath):
        return False
    src_data=b'keep going'
    dest_data=b'keep going'
    src_hash = md5const()
    dest_hash = md5const()
    with (open(fc.DestinationPath, 'rb')) as F:
        try:
            while src_data or dest_data:
                src_data = resp.read(1048576)
                src_hash.update(src_data)
                dest_data = F.read(1048576)
                dest_hash.update(dest_data)
                if src_hash.hexdigest() != dest_hash.hexdigest():
                    return False
        except Exception as e:
            F.close()
            return False
    return True


class FileContext:
    def __init__(self, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
        if not Checksum:
            Checksum = "md5"
        if not Type:
            Type = "file"
        if not Ensure:
            Ensure = "present"
        if not Links or len(Links) == 0:
            Links = "follow"
        self.DestinationPath = DestinationPath
        self.SourcePath = SourcePath
        if len(SourcePath) > 0 and '://' in SourcePath and Type != 'file':
            raise Exception('ERROR: Remote paths are only valid for Type = file.')
        self.LocalPath = ''
        self.Ensure = Ensure.lower()
        self.Type = Type.lower()
        self.Force = Force
        self.Contents = Contents
        self.Checksum = Checksum.lower()
        self.Recurse = Recurse
        self.Links = Links.lower()
        self.Owner = Owner
        self.Group = Group
        self.ModifiedDate=None
        error=None

        if Mode:
            if len(Mode) == 9:
                try:
                    Mode = ConvertLongModeToNumeric(Mode)
                except Exception as error:
                    print("Exception in ConvertLongModeToNumeric on " + Mode  + " Error: " + error.strerror, file=sys.stderr)    
                    LG().Log('ERROR', "Exception in ConvertLongModeToNumeric on " + Mode + " Error: " + error.strerror)
            elif len(Mode) == 3:
                # Already in proper format
                pass
            else:
                print("Error: Invalid Mode: " + Mode)
                LG().Log("ERROR", "Invalid Mode: " + Mode)
                Mode = ""

        self.Mode = Mode

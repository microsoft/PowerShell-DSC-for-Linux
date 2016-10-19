#!/usr/bin/env python
# ====================================
#  Copyright (c) Microsoft Corporation.
#  All rights reserved.
#  See license.txt for license information.
# ====================================

import os
import sys
import pwd
import grp
import codecs
import fnmatch
import copy
import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog
try:
    import hashlib
    md5const = hashlib.md5
    shaconst = hashlib.sha256
except ImportError: # Only sha-1 is available for python2.4.
    import md5
    md5const = md5.md5
    import sha
    shaconst = sha.sha

# [ClassVersion("1.0.0"), Description("The configuration provider for files and directories."), FriendlyName("nxFileInventory")]
# class MSFT_nxFileInventoryResource:OMI_BaseResource
# {
#   [Key, InventoryFilter] string DestinationPath;
#   [Write, InventoryFilter] boolean Recurse;  //default = false
#   [Write, InventoryFilter] boolean UseSudo;  //default = false
#   [Write, ValueMap{"follow", "manage", "ignore" }, Values{"follow", "manage", "ignore"},InventoryFilter] string Links; //default follow
#   [Write, ValueMap{"md5", "sha-256", "mtime", "ctime"}, Values{"md5","sha-256","mtime","ctime"},InventoryFilter] string Checksum; //default md5
#   [Write, ValueMap{"file", "directory", "*"},Values{"file", "directory","*"}, InventoryFilter] string Type; //default *
#   [Write, InventoryFilter] uint32 MaxContentsReturnable;  //default 1024 bytes
#   [Write, InventoryFilter] uint64 MaxOutputSize; //default 10485760 bytes
#   [Read] string Contents;
#   [Read] datetime ModifiedDate;
#   [Read] datetime CreatedDate; 
#   [Read] string Mode;
#   [Read] string Group;
#   [Read] string Owner;     
#   [Read] uint64 FileSize;
# };

#{'Links': u'ignore', 'MaxOutputSize': None, 'Checksum': u'md5', 'Recurse': None, 'MaxContentsReturnable': None, 'DestinationPath': u'/tmp', 'Type': u'directory'}

def init_locals(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo):
    if DestinationPath is None :
        DestinationPath = ''
    if Recurse is None :
        Recurse = False
    if UseSudo is None :
        UseSudo = False
    if Links is None :
        Links = 'follow'
    if Checksum is None :
        Checksum = 'md5'
    if Type is None :
        Type = '*'
    if MaxContentsReturnable is None or MaxContentsReturnable < 0:
        MaxContentsReturnable = 1024
    if MaxOutputSize is None or MaxOutputSize < 0:
        MaxOutputSize = 10485760
    return DestinationPath.encode('ascii', 'ignore'), Recurse, Links.encode('ascii', 'ignore').lower(), \
        Checksum.encode('ascii', 'ignore').lower(), Type.encode('ascii', 'ignore').lower(), \
        MaxContentsReturnable, MaxOutputSize, UseSudo


def Set_Marshall(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo):
    return [0]

def Test_Marshall(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo):
    return [0]

def Get_Marshall(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo):
    arg_names = list(locals().keys())
    DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo \
            = init_locals(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo)
    retval = 0
    DestinationPath = protocol.MI_String(DestinationPath)
    Type = protocol.MI_String(Type)
    MaxContentsReturnable =  protocol.MI_Uint32(MaxContentsReturnable)
    MaxOutputSize =  protocol.MI_Uint64(MaxOutputSize)
    Recurse = protocol.MI_Boolean(Recurse)
    UseSudo = protocol.MI_Boolean(UseSudo)
    Links = protocol.MI_String(Links)
    Checksum = protocol.MI_String(Checksum)
    Contents = protocol.MI_String('')
    ModifiedDate = protocol.MI_Timestamp.from_time(0)
    CreatedDate = protocol.MI_Timestamp.from_time(0)
    Mode = protocol.MI_String('')
    Group = protocol.MI_String('')
    Owner = protocol.MI_String('')
    FileSize = protocol.MI_Uint64(0)
    arg_names.extend(['Contents', 'ModifiedDate', 'CreatedDate', 'Mode', 'Group', 'Owner', 'FileSize'])
    retd = {}
    ld = locals()
    for k in arg_names :
        retd[k] = ld[k]
    return retval, retd

def Inventory_Marshall(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo):
    DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo \
                     = init_locals(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo)
    retval = 0
    out_size_cur = 158 # xml output header + footer length.
    xml_overhead_array_element = 99 # xml output overhead per Inventory array entry.
    xml_overhead_param = 102 # xml output overhead per Inventory parameter.
    _Inventory = []
    Inventory = DoInventory(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo)
    for d in Inventory:
        if out_size_cur <  MaxOutputSize:
            out_size_cur += xml_overhead_array_element
            for k,v in d.items():
                out_size_cur += xml_overhead_param
                if 'Date' in k:
                    out_size_cur += len(k) + 25 + 3 # The final date format wil be 25 chars, +3 for type tag. 
                else:
                    out_size_cur += len(k) + len(repr(v)) -2 # The repr(v) will add two quotes.
        if out_size_cur >=  MaxOutputSize:
            break
        d['DestinationPath'] = protocol.MI_String(d['DestinationPath'])
        d['Checksum'] = protocol.MI_String(d['Checksum'])
        d['Type'] = protocol.MI_String(d['Type'])
        d['Contents'] = protocol.MI_String(d['Contents'])
        d['ModifiedDate'] = protocol.MI_Timestamp.from_time(d['ModifiedDate'])
        d['CreatedDate'] = protocol.MI_Timestamp.from_time(d['CreatedDate'])
        d['Mode'] = protocol.MI_String(d['Mode'])
        d['Group'] = protocol.MI_String(d['Group'])
        d['Owner'] = protocol.MI_String(d['Owner'])
        d['FileSize'] = protocol.MI_Uint64(d['FileSize'])
        _Inventory.append(d)
    _Inventory = protocol.MI_InstanceA(_Inventory)
    retd = {}
    retd["__Inventory"] = _Inventory
    return retval, retd


def DoInventory(DestinationPath, Recurse, Links, Checksum, Type, MaxContentsReturnable, MaxOutputSize, UseSudo):
    Inventory = []
    full_path = DestinationPath.split('/')
    if full_path[-1] == '':
        full_path[-1] = '*'
    wildcard_path = False
    for p in full_path:
        if '*' in p or '?' in p:
            wildc_start=full_path.index(p)
            wildcard_path = True
            break
    if wildcard_path:
        top = '/' + os.path.join(*full_path[:wildc_start])
    else :
        top = '/' + os.path.join(*full_path)
    if not os.path.exists(top):
        print("Error: Unable to read 'DestinationPath': " + DestinationPath)
        LG().Log("ERROR","Unable to read 'DestinationPath': " + DestinationPath)
        return Inventory
    if not wildcard_path:
        if Links == 'ignore' and os.path.islink(top):
            return Inventory
        if Type != 'directory' and os.path.isfile(top): # This is s single file.
            d = GetFileInfo(top, Links, MaxContentsReturnable, Checksum)
            if 'DestinationPath' in d.keys():
                Inventory.append(copy.deepcopy(d))
            return Inventory
        if '*' not in full_path[-1] and '?' not in full_path[-1]:
            full_path.append('*') # It is a directory without the trailing '/', so add it.
    dirs = set()
    full_path_len =  len(full_path)
    for dirpath, dirnames, filenames in walk(top, followlinks=(Links == 'follow'), topdown=True):
        dlen = len(dirpath.split('/'))
        if dirpath.split('/')[-1] == '':
            dlen -= 1
        if wildcard_path and full_path_len >= dlen+1:
            do_wildcard = True
        else :
            do_wildcard = False
        st = os.stat(dirpath)
        scandirs = []
        if dlen+1 == full_path_len  or ( Recurse and dlen >= full_path_len ):
            for filename in filenames:
                if (dlen+1 == full_path_len  or ( Recurse and dlen >= full_path_len )) \
                       and not fnmatch.fnmatch(filename, full_path[-1]):
                    continue
                if Type != 'directory':
                    d = GetFileInfo(os.path.join(dirpath, filename),\
                                    Links, MaxContentsReturnable, Checksum)
                    if 'DestinationPath' in d.keys():
                        Inventory.append(copy.deepcopy(d))
        for dirname in dirnames:
            if not ( Recurse and dlen+1 >= full_path_len ):
                if ( do_wildcard and not fnmatch.fnmatch(dirname, full_path[dlen]) ) or \
                       ( not Recurse and dlen > full_path_len ):
                    continue
            st = os.stat(os.path.join(dirpath, dirname)) # use Lstat if follow?
            dirkey = st.st_dev, st.st_ino
            if dirkey not in dirs:
                if Recurse or (not Recurse and dlen+1 < full_path_len)  :
                    dirs.add(dirkey)
                    scandirs.append(dirname)
            if Type != 'file' and ( dlen+1 == full_path_len  or  ( Recurse and dlen >= full_path_len ) ) :
                d = GetDirInfo(os.path.join(dirpath, dirname), st, Checksum, Links)
                if 'DestinationPath' in d.keys():
                    Inventory.append(copy.deepcopy(d))
        dirnames[:] = scandirs
    return Inventory


def GetFileInfo(fname, Links, MaxContentsReturnable, Checksum):
    """
    Return a dictionary of info for file.
    If 'Links' == 'follow', no link files will appear here,
    those links will be sent to GetDirInfo() as direcroties.
    Therefore only LStatFile is used.
    If file is link and 'Links' == 'ignore' {} is returned.
    """
    d = {}
    if os.path.islink(fname):
        d['Type'] = 'link'
    else :
        d['Type'] = 'file'
    if d['Type'] == 'link' and Links == 'ignore':
        return {}
    stat_info = None
    stat_info = LStatFile(fname)
    if stat_info == None:
        return {}
    d['DestinationPath'] = fname
    try:
        d['Owner'] = pwd.getpwuid(stat_info.st_uid).pw_name
    except:
        d['Owner'] = str(stat_info.st_uid)
    try:
        d['Group'] = grp.getgrgid(stat_info.st_gid).gr_name
    except:
        d['Group'] = str(stat_info.st_gid)
    d['Mode'] = str(oct(stat_info.st_mode))[-3:]
    d['ModifiedDate'] = int(stat_info.st_mtime)
    d['CreatedDate'] = int(stat_info.st_ctime)
    d['FileSize'] = stat_info.st_size
    if Checksum == 'md5' or Checksum == 'sha-256':
        d['Checksum'] = GetChecksum(fname,Checksum)
    elif Checksum == "ctime":
        d['Checksum']= str(int(stat_info.st_ctime))
    else : # Checksum == "mtime":
        d['Checksum']= str(int(stat_info.st_mtime))
    if d['Type'] == 'link' and Links == 'manage' :
        d['Contents'] = 'Symlink to ' + os.readlink(fname) 
    else :
        d['Contents'], error = ReadFileLimited(fname,MaxContentsReturnable)
    if d['Contents'] is None:
        d['Contents'] = ''
    return d

def GetDirInfo(dname, stat_info, Checksum, Links):
    """
    Return a dictionary of info for directory.
    Only if 'Links' == 'follow' will links be
    processed here as directories.
    """
    d = {}
    if stat_info == None:
        return d
    d['Type'] = 'directory'
    d['DestinationPath'] = dname
    try:
        d['Owner'] = pwd.getpwuid(stat_info.st_uid).pw_name
    except:
        d['Owner'] = str(stat_info.st_uid)
    try:
        d['Group'] = grp.getgrgid(stat_info.st_gid).gr_name
    except:
        d['Group'] = str(stat_info.st_gid)
    if Checksum == 'md5' or Checksum == 'sha-256':
        d['Checksum'] = '0'
    elif Checksum == "ctime":
        d['Checksum']= str(int(stat_info.st_ctime))
    else : # Checksum == "mtime":
        d['Checksum']= str(int(stat_info.st_mtime))
    d['Mode'] = str(oct(stat_info.st_mode))[-3:]
    d['ModifiedDate'] = int(stat_info.st_mtime)
    d['CreatedDate'] = int(stat_info.st_ctime)
    d['FileSize'] = stat_info.st_size
    d['Contents'] = ''
    if Links == 'manage' and os.path.islink(dname):
        d['Contents'] = 'Symlink to ' + os.readlink(dname)
    return d

def opened_w_error(filename, mode="r"):
    try:
        f = codecs.open(filename, encoding='utf8', mode=mode)
    except IOError, err:
        return None, err
    return f, None

def opened_bin_w_error(filename, mode="rb"):
    try:
        f = open(filename, mode)
    except IOError, err:
        return None, err
    return f, None

def ReadFileLimited(path, MaxContentsReturnable):
    """
    Safely attempt to read a text file,
    ensuring file is always closed at exit.
    Read up to MaxContentsReturnable.
    """
    d = ''
    error = None
    F, error = opened_w_error(path)
    if not error:
        try:
            d = F.read(MaxContentsReturnable)
        except:
            pass
    F.close()
    return d.encode('ascii', 'ignore'), error

def Print(s, file=sys.stderr):
    file.write(s.encode('utf8') + '\n')
    
def LStatFile(path):
    """
    LStat the file.  Do not follow the symlink.
    """
    d = None
    try:
        d = os.lstat(path)
    except:
        pass
    return d


def StatFile(path):
    """
    Stat the file, following the symlink.
    """
    d = None
    try:
        d = os.stat(path)
    except:
        pass
    return d

def GetChecksum(fname, Checksum):
    src_error = None
    src_block = 'loopme'
    if Checksum == "md5":
        src_hash = md5const()
    else : # sha-256
        src_hash = shaconst()
    src_file, src_error = opened_bin_w_error(fname, 'rb')
    if src_error:
        return ""
    while src_block :
        src_block = src_file.read(8192)
        src_hash.update(src_block)
    return src_hash.hexdigest()

# From python2.7 os.py
def walk(top, topdown=True, onerror=None, followlinks=False):
    islink, join, isdir = os.path.islink, os.path.join, os.path.isdir

    # We may not have read permission for top, in which case we can't
    # get a list of the files the directory contains.  os.path.walk
    # always suppressed the exception then, rather than blow up for a
    # minor reason when (say) a thousand readable directories are still
    # left to visit.  That logic is copied here.
    try:
        # Note that listdir and error are globals in this module due
        # to earlier import-*.
        names = os.listdir(top)
    except os.error, err:
        if onerror is not None:
            onerror(err)
        return

    dirs, nondirs = [], []
    for name in names:
        if isdir(join(top, name)):
            dirs.append(name)
        else:
            nondirs.append(name)

    if topdown:
        yield top, dirs, nondirs
    for name in dirs:
        new_path = join(top, name)
        if followlinks or not islink(new_path):
            for x in walk(new_path, topdown, onerror, followlinks):
                yield x
    if not topdown:
        yield top, dirs, nondirs

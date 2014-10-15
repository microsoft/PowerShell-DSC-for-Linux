#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import os
import sys
import pwd
import shutil
import grp
import codecs

# 	[Key] string DestinationPath; 
# 	[Write] string SourcePath;
# 	[Write,ValueMap{"present", "absent"},Values{"present", "absent"}] string Ensure;
# 	[Write,ValueMap{"file", "directory", "link"},Values{"file", "directory","link"}] string Type;
# 	[Write] boolean Force;
# 	[Write] string Contents;
# 	[Write, ValueMap{"md5", "mtime", "ctime"}] string Checksum;
# 	[Write] boolean Recurse;
# 	[Write, ValueMap{"follow", "manage", "ignore" }] string Links;
# 	[Write] string Group;
# 	[Write] string Mode;
# 	[Write] string Owner;
# 	[Read] datetime ModifiedDate; 

try:
    import hashlib
    md5const = hashlib.md5
except ImportError:
    import md5
    md5const = md5.md5

BLOCK_SIZE = 8192

global show_mof
show_mof=False

def Set_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    if DestinationPath  != None :
        DestinationPath = DestinationPath.decode("utf-8")
    else:
        DestinationPath=''
    if SourcePath != None :
        SourcePath = SourcePath.decode("utf-8")
    else:
        SourcePath = ''
    if Ensure != None :
        Ensure = Ensure.decode("utf-8")
    else:
        Ensure = ''
    if Type != None :
        Type = Type.decode("utf-8")
    else:
        Type = ''
    if Force != None :
        Force = Force
    else:
        Force = False
    if Checksum != None :
        Checksum = Checksum.decode("utf-8")
    else:
        Checksum = ''
    if Recurse != None :
        Recurse = Recurse
    else:
        Recurse = False
    if Links != None :
        Links = Links.decode("utf-8")
    else:
        Links = ''
    if Owner != None :
        Owner = Owner.decode("utf-8")
    else:
        Owner = ''
    if Group != None :
        Group = Group.decode("utf-8")
    else:
        Group = ''
    if Mode != None :
        Mode = Mode.decode("utf-8")
    else:
        Mode = ''
    
    retval = Set(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    return retval

def Test_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    if DestinationPath != None :
        DestinationPath = DestinationPath.decode("utf-8")
    else:
        DestinationPath = ''
    if SourcePath != None :
        SourcePath = SourcePath.decode("utf-8")
    else:
        SourcePath = ''
    if Ensure != None :
        Ensure = Ensure.decode("utf-8")
    else:
        Ensure = ''
    if Type != None :
        Type = Type.decode("utf-8")
    else:
        Type = ''
    if Force != None :
        Force = Force
    else:
        Force = False
    if Checksum != None :
        Checksum = Checksum.decode("utf-8")
    else:
        Checksum = ''
    if Recurse != None :
        Recurse = Recurse
    else:
        Recurse = False
    if Links != None :
        Links = Links.decode("utf-8")
    else:
        Links = ''
    if Owner != None :
        Owner = Owner.decode("utf-8")
    else:
        Owner = ''
    if Group != None :
        Group = Group.decode("utf-8")
    else:
        Group = ''

    if Mode != None :
        Mode = Mode.decode("utf-8")
    else:
        Mode = ''
        
    retval = Test(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    return retval

def Get_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    arg_names=locals().keys()
    if DestinationPath != None :
        DestinationPath = DestinationPath.decode("utf-8")
    else:
        DestinationPath = ''
    if SourcePath != None :
        SourcePath = SourcePath.decode("utf-8")
    else:
        SourcePath = ''
    if Ensure != None :
        Ensure = Ensure.decode("utf-8")
    else:
        Ensure = ''
    if Type != None :
        Type = Type.decode("utf-8")
    else:
        Type = ''
    if Force != None :
        Force = Force
    else:
        Force = False
    if Checksum != None :
        Checksum = Checksum.decode("utf-8")
    else:
        Checksum = ''
    if Recurse != None :
        Recurse = Recurse
    else:
        Recurse = False
    if Links != None :
        Links = Links.decode("utf-8")
    else:
        Links = ''
    if Owner != None :
        Owner = Owner.decode("utf-8")
    else:
        Owner = ''
    if Group != None :
        Group = Group.decode("utf-8")
    else:
        Group = ''
    if Mode != None :
        Mode = Mode.decode("utf-8")
    else:
        Mode = ''

    retval = 0
    (retval, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate) = Get(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

    DestinationPath = DestinationPath.encode("utf-8")
    SourcePath = SourcePath.encode("utf-8")
    Ensure = Ensure.encode("utf-8")
    Type = Type.encode("utf-8")
    Force = Force
    Contents = Contents.encode("utf-8")
    Checksum = Checksum.encode("utf-8")
    Recurse = Recurse
    Links = Links.encode("utf-8")
    Owner = Owner.encode("utf-8")
    Group = Group.encode("utf-8")
    Mode = Mode.encode("utf-8")
    ModifiedDate = ModifiedDate.encode("utf-8")
    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k] 
    return retval, retd


############################################################
### Begin user defined DSC functions
############################################################

def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError, err:
        return None, err
    return f, None



def ReadFile(path):
    """
    Safely attempt to read a file,
    ensuring file is always closed at exit.
    Return the data and the exception object.
    The data is None if an error occurred.
    The error is None if the data was read.
    Log results to stderr.
    """
    d=None
    error=None
    F,Error = opened_w_error(path,'rb')
    if error:
        Print("Exception opening file " + path + " Error: " + str(error),file=sys.stderr )
    else:
        d=F.read()
        F.close()
    return d,error

def WriteFile(path,contents):
    """
    Safely attempt to write data to a file,
    replacing the existing file or creating it and
    ensuring file is always closed at exit.
    Return the exception object.
    The error is None if the data was written.
    Log results to stderr.
    """
    error=None
    F,error =  opened_w_error(path,'wb+')
    if error:
        Print("Exception opening file " + path + " Error Code: " + str(error) ,file=sys.stderr)
    else:
        F.write(contents)
        F.close()
    return error

def Print(s,file=sys.stdout):
    file.write(s+'\n')
    
def LStatFile(path):
    """
    LStat the file.  Do not follow the symlink.
    """
    d=None
    error=None
    try:
        d=os.lstat(path)
    except OSError, error:
         Print("Exception lstating file " + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception lstating file " + path  + " Error: " + str(error),file=sys.stderr)
    return d

def StatFile(path):
    """
    Stat the file, following the symlink.
    """
    d=None
    error=None
    try:
        d=os.stat(path)
    except OSError, error:
         Print("Exception stating file " + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception stating file " + path  + " Error: " + str(error),file=sys.stderr)
    return d

def Chown(path,owner,group):
    error=None
    try:
        os.chown(path,owner,group)
    except OSError, error:
         Print("Exception changing ownership of file " + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception changing ownership of file " + path  + " Error: " + str(error),file=sys.stderr)
    return error

def Chmod(path,mode):
    error=None
    if type(mode) == str:
        mode=int(mode,8)
    try:
        os.chmod(path,mode)
    except OSError, error:
         Print("Exception  changing mode of file " + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception  changing mode of file " + path  + " Error: " + str(error),file=sys.stderr)
    return error

def LChown(path,owner,group):
    error=None
    try:
        os.lchown(path,owner,group)
    except OSError, error:
         Print("Exception changing ownership of file " + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception changing ownership of file " + path  + " Error: " + str(error),file=sys.stderr)
    return error

def LChmod(path,mode):
    error=None
    try:
        os.lchmod(path,mode)
    except OSError, error:
         Print("Exception  changing mode of file " + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception  changing mode of file " + path  + " Error: " + str(error),file=sys.stderr)
    return error

def ListDir(path):
    d=None
    error=None
    try:
        d=os.listdir(path)
    except OSError, error:
         Print("Exception listing dir" + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception listing dir" + path  + " Error: " + str(error),file=sys.stderr)
    return d

def Symlink(spath,dpath):
    error=None
    try:
        os.symlink(os.readlink(spath), dpath)
    except OSError, error:
        Print("Exception creating symlink from " + spath  + ' to ' + dpath + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
        Print("Exception creating symlink from " + spath  + ' to ' + dpath + " Error: " + str(error),file=sys.stderr)
    return error
    
def MakeDirs(path):
    error=None
    try:
        os.makedirs(path)
    except OSError, error:
         Print("Exception making dir" + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception making dir" + path  + " Error: " + str(error),file=sys.stderr)
    return error

def RemoveFile(path):
    error=None
    try:
        os.remove(path)
    except OSError, error:
         Print("Exception removing file" + path  + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception removing file" + path  + " Error: " + str(error),file=sys.stderr)
    return error

def CopyFile(spath,dpath):
    error=None
    try:
        shutil.copyfile(spath,dpath)
    except OSError, error:
         Print("Exception removing tree" + spath  + ' to ' + dpath + " Error: " + str(error),file=sys.stderr)
    except IOError, error:
         Print("Exception removing tree" + spath  + ' to ' + dpath + " Error: " + str(error),file=sys.stderr)
    return error

def CompareFiles(DestinationPath, SourcePath, Checksum):
    """
    If the files differ in size, return -1.
    Reading and computing the hash here is done in a block-by-block manner, 
    in case the file is quite large.
    """
    stat_dest = StatFile(DestinationPath)
    stat_src = StatFile(SourcePath)
    if stat_src.st_size != stat_dest.st_size:
        return -1
    if Checksum == "md5":
        src_error = None
        dest_error = None
        src_hash = md5const()
        dest_hash = md5const()
        src_block ='loopme'
        dest_block ='loopme'
        src_file,src_error = opened_w_error(SourcePath,'r')
        if src_error:
            Print("Exception opening source file " + SourcePath  + " Error : " + str(src_error),file=sys.stderr)
            return -1
        dest_file,dest_error = opened_w_error(DestinationPath,'r')
        if dest_error:
            Print("Exception opening destination file " + DestinationPath + " Error : " + str(dest_error),file=sys.stderr)
            src_file.close()
            return -1
        while src_block != '' and dest_block != '':
            src_block=src_file.read(BLOCK_SIZE)
            dest_block=dest_file.read(BLOCK_SIZE)
            src_hash.update(src_block)
            dest_hash.update(dest_block)
            if src_hash.hexdigest() != dest_hash.hexdigest():
                src_file.close()
                dest_file.close()
                return -1  
        if src_hash.hexdigest() == dest_hash.hexdigest():
            src_file.close()
            dest_file.close()
            return 0  
    elif Checksum == "ctime":
        if stat_src.st_ctime > stat_dest.st_ctime:
            # Source is newer than Destination
            return -1
        else:
            return 0
    elif Checksum == "mtime":
        if stat_src.st_mtime > stat_dest.st_mtime:
            # Source is newer than Destination
            return -1
        else:
            return 0

def RemoveTree(path):
    error=None
    try:
        shutil.rmtree(path)
    except OSError, error:
        Print("Exception removing folder " + path + " Error Code: "
              +  " Error: " + str(error),file=sys.stderr)
    except IOError, error:
        Print("Exception removing folder " + path + " Error Code: "
              +  " Error: " + str(error),file=sys.stderr)
    return error
    
def RemovePath(path):
    error=None
    if os.path.islink(path) or os.path.isfile(path):
        RemoveFile(path)
    elif os.path.isdir(path):
        RemoveTree(path)
    else:
        Print("Error: Unknown file type for file: " + path,file=sys.stderr)
    return error
        
def TestOwnerGroupMode(DestinationPath, SourcePath, fc):
    stat_info = LStatFile(DestinationPath)

    if SourcePath:
        stat_info_src = LStatFile(SourcePath)

    if fc.Owner:
        try:
            Specified_Owner_ID = pwd.getpwnam(fc.Owner)[2]
        except KeyError, error:
             Print("Exception obtaining gid from group name " + fc.Group  + " Error: " + str(error),file=sys.stderr)
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
        except KeyError, error:
             Print("Exception obtaining gid from group name " + fc.Group  + " Error: " + str(error),file=sys.stderr)
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
    if stat_info == None :
        return False
    
    if SourcePath:
        stat_info_src = LStatFile(SourcePath)
        if stat_info_src == None:
            return False
    
    if fc.Owner:
        Specified_Owner_ID = pwd.getpwnam(fc.Owner)[2]
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            Print("Changing owner of " + DestinationPath + " to " + str(Specified_Owner_ID))
            if LChown(DestinationPath, Specified_Owner_ID, -1) != None :
                return False

    elif SourcePath:
        src_uid = pwd.getpwuid(stat_info_src.st_uid)[2]
        if pwd.getpwuid(stat_info.st_uid)[2] != src_uid:
            Print("Changing owner of " + DestinationPath + " to " + str(src_uid))
            if LChown(DestinationPath, Specified_Owner_ID, -1) != None :
                return False

    if fc.Group:
        Specified_Group_ID = grp.getgrnam(fc.Group)[2]
        if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
            Print("Changing group of " + DestinationPath + " to " + str(Specified_Group_ID))
            if LChown(DestinationPath, -1, Specified_Group_ID) != None :
                return False


    elif SourcePath:
        src_gid = grp.getgrgid(stat_info_src.st_gid)[2]
        if grp.getgrgid(stat_info.st_gid)[2] != src_gid:
            Print("Changing group of " + DestinationPath + " to " + str(src_gid))
            if LChown(DestinationPath,src_gid , -1) != None :
                return False

    # Mode is irrelevant to symlinks
    if not os.path.islink(DestinationPath):
        if fc.Mode:
            if str(oct(stat_info.st_mode))[-3:] != fc.Mode:
                Print("Changing mode of " + DestinationPath + " to " + fc.Mode)
                if Chmod(DestinationPath, fc.Mode) != None :
                    return False
        elif SourcePath:
            src_mode = str(oct(stat_info_src.st_mode))[-3:]
            if str(oct(stat_info.st_mode))[-3:] != src_mode:
                Print("Changing mode of " + DestinationPath + " to " + src_mode)
                if Chmod(DestinationPath, src_mode) != None :
                    return False
    return True
    
def SetDirectoryRecursive(DestinationPath, SourcePath, fc):
    if not os.path.exists(DestinationPath):
        MakeDirs(DestinationPath)
    if SetOwnerGroupMode(DestinationPath, SourcePath, fc) == False:
        return False
    if fc.Recurse == False:
        return True
    Destination_subfiles = ListDir(DestinationPath)
    if Destination_subfiles == None:
        return False
    if not SourcePath:
        # Enforce Owner/Group/Mode specified
        for f in Destination_subfiles:
            f_destpath = os.path.join(DestinationPath, f)
            if not os.path.islink(f_destpath):
                if os.path.isfile(f_destpath):
                    if SetOwnerGroupMode(f_destpath, "", fc) == False :
                        return False
                elif os.path.isdir(f_destpath):
                    if SetDirectoryRecursive(f_destpath, "", fc) == False :
                        return False
        return True

    Source_subfiles = ListDir(SourcePath)

    # For all files in SourcePath's directory, ensure they exist with proper contents and stat in DestionationPath's directory 
    for f in Source_subfiles:
        f_srcpath = os.path.join(SourcePath, f)
        f_destpath = os.path.join(DestinationPath, f)

        if os.path.islink(f_srcpath):
            if TestLink(f_destpath, f_srcpath, fc) == False:
                if SetLink(f_destpath, f_srcpath, fc) == False:
                    return False
        elif os.path.isfile(f_srcpath):
            if TestFile(f_destpath, f_srcpath, fc) == False:
                if SetFile(f_destpath, f_srcpath, fc) == False:
                    return False
        elif os.path.isdir(f_srcpath):
            if SetDirectoryRecursive(f_destpath, f_srcpath, fc) == False:
                return False
        
    return True
      
def SetFile(DestinationPath, SourcePath, fc):
    error=None
    if os.path.exists(DestinationPath) and (os.path.islink(DestinationPath) or os.path.isdir(DestinationPath)):
        if fc.Force == True:
            RemovePath(DestinationPath)
        else:
            Print("Error: " + DestinationPath + " is not a file; cannot overwrite without the 'Force' option being true")
            return False

    if SourcePath:
        should_copy_file = False
        if fc.Checksum == "ctime" or fc.Checksum == "mtime":
            if os.path.isfile(DestinationPath):
                if CompareFiles(DestinationPath, SourcePath,  fc.Checksum) == -1:
                    should_copy_file = True
            else:
                should_copy_file = True
        else:
            # Just copy the file if this is a resource intensive file comparison
            should_copy_file = True

        if should_copy_file:
            if CopyFile(SourcePath, DestinationPath) == False :
                return False;
            
    elif fc.Contents:
        if WriteFile(DestinationPath, fc.Contents) != None:
            Print("Error: Unable to write file at " + DestinationPath)
            return False
    else:
        # Create a file with nothing in it
        try:
            open(DestinationPath, 'a').close()
        except OSError, error:
            Print("Exception creating file " + DestinationPath  + " Error: " + str(error),file=sys.stderr)
        except IOError, error:
            Print("Exception creating file " + DestinationPath + " Error: " + str(error),file=sys.stderr)

    SetOwnerGroupMode(DestinationPath, SourcePath, fc)

    return True
         
def SetDirectory(DestinationPath, SourcePath, fc):
    if os.path.exists(DestinationPath) and not os.path.isdir(DestinationPath):
        if fc.Force == True:
            RemovePath(DestinationPath)
        else:
            return False

    return SetDirectoryRecursive(DestinationPath, SourcePath, fc)

def SetLink(DestinationPath, SourcePath, fc):
    if not SourcePath:
        Print("Error: Need a source path in order to create a new symbolic link.")
        return False

    if os.path.exists(DestinationPath):
        if os.path.islink(DestinationPath) or fc.Force == True:
            RemovePath(DestinationPath)
        else:
            Print("Error: Unable to overwrite currently existing file at " + DestinationPath + " without the Force option being true.")
            return False

    if os.path.islink(SourcePath):
        if fc.Links == "follow":
            if os.path.isfile(SourcePath):
                SetFile(DestinationPath, os.path.realpath(SourcePath), fc)
            elif os.path.isdir(SourcePath):
                SetDirectoryRecursive(DestinationPath, os.path.realpath(SourcePath), fc)
        elif fc.Links == "manage":
            Symlink(os.readlink(SourcePath), DestinationPath)
            
        elif fc.Links == "ignore":
            # Ignore all symlinks
            return True
    else:
        Symlink(SourcePath, DestinationPath)

    SetOwnerGroupMode(DestinationPath, SourcePath, fc)

    return True

def SetShowMof(a):
    global show_mof
    show_mof=a

def ShowMof(op, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    if not show_mof:
        return
    mof=''
    mof+=op + ' nxFile MyFile\n'
    mof+='{\n'
    mof+='    DestinationPath = "' + DestinationPath + '"\n'
    mof+='    SourcePath = "' + SourcePath + '"\n'
    mof+='    Ensure = "' + Ensure + '"\n'
    mof+='    Type = "' + Type + '"\n'
    mof+='    Force = ' + str(Force) + '\n'
    mof+='    Contents = "' + Contents + '"\n'
    mof+='    Checksum = "' + Checksum + '"\n'
    mof+='    Recurse = ' + str(Recurse) + '\n'
    mof+='    Links = "' + Links + '"\n'
    mof+='    Group = "' + Group + '"\n'
    mof+='    Mode = "' + Mode + '"\n'
    mof+='    Owner = "' + Owner + '"\n'
    mof+='}\n'
    f=open('./test_mofs.log','a')
    Print(mof,file=f)
    f.close()

def Set(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    ShowMof('SET', DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    fc = FileContext(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

    if not DestinationPath:
        return [-1]

    if fc.Ensure == "present":
        if fc.Type == "file":
            if SetFile(DestinationPath, SourcePath, fc) == False:
                return [-1]
        elif fc.Type == "directory":
            if SetDirectory(DestinationPath, SourcePath, fc) == False:
                return [-1]
        elif fc.Type == "link":
            if SetLink(DestinationPath, SourcePath, fc) == False:
                return [-1]

    elif fc.Ensure == "absent":
        RemovePath(DestinationPath)
        return [0]

    return [0]

def TestDirectory(DestinationPath, SourcePath, fc):
    if not os.path.exists(DestinationPath) or not os.path.isdir(DestinationPath):
        return False

    if TestOwnerGroupMode(DestinationPath, SourcePath, fc) == False:
        return False

    if fc.Recurse == False:
        return True

    Destination_subfiles = ListDir(DestinationPath)
    if Destination_subfiles == None:
        return False

    if not SourcePath:
        # Enforce Owner/Group/Mode specified
        for f in Destination_subfiles:
            f_destpath = os.path.join(DestinationPath, f)
            if not os.path.islink(f_destpath):
                if os.path.isfile(f_destpath):
                    if TestOwnerGroupMode(f_destpath, "", fc) == False:
                        return False
                elif os.path.isdir(f_destpath):
                    if TestDirectory(f_destpath, "", fc) == False:
                        return False
        return True

    Source_subfiles = ListDir(SourcePath)
    if Source_subfiles == None:
        return False

    for f in Source_subfiles:
        if f not in Destination_subfiles:
            Print("File: " + f + " does not exist in: " + SourcePath)
            return False

        f_destpath = os.path.join(DestinationPath, f)
        f_srcpath = os.path.join(SourcePath, f)

        if os.path.islink(f_srcpath):
            if TestLink(f_destpath, f_srcpath, fc) == False:
                return False
        elif os.path.isfile(f_srcpath):
            if TestFile(f_destpath, f_srcpath, fc) == False:
                return False
        elif os.path.isdir(f_srcpath):
            if TestDirectory(f_destpath, f_srcpath, fc) == False:
                return False

    return True

def TestFile(DestinationPath, SourcePath, fc):
    if not os.path.exists(DestinationPath) or not os.path.isfile(DestinationPath) or os.path.islink(DestinationPath):
        return False

    if TestOwnerGroupMode(DestinationPath, SourcePath, fc) == False:
        return False

    if SourcePath:
        if not os.path.isfile(SourcePath):
            return False

        if os.path.islink(SourcePath):
            if fc.Links == "follow":
                if os.path.isdir(os.path.realpath(SourcePath)):
                    Print("Error: Expecting a file, but source link points to directory")
                    return False
            else:
                if not os.path.islink(DestinationPath):
                    return False
                if os.readlink(DestinationPath) != os.readlink(SourcePath):
                    return False

        elif CompareFiles(DestinationPath, SourcePath,  fc.Checksum) == -1:
            return False

    elif fc.Contents:
        dest_file,error = ReadFile(DestinationPath)
        if fc.Contents != dest_file:
            return False

    return True

def TestLink(DestinationPath, SourcePath, fc):
    if SourcePath:
        if os.path.islink(SourcePath):
            if fc.Links == "follow":
                if os.path.isdir(SourcePath):
                    if TestDirectory(DestinationPath, os.path.realpath(SourcePath), fc) == False:
                        return False
                elif os.path.isfile(SourcePath):
                    if TestFile(DestinationPath, os.path.realpath(SourcePath), fc) == False:
                        return False
            elif fc.Links == "manage":
                if not os.path.islink(DestinationPath):
                    return False

                if os.readlink(DestinationPath) != os.readlink(SourcePath):
                    return False
            elif fc.Links == "ignore":
                return True
        else:
            if os.readlink(DestinationPath) != SourcePath:
                return False

    if TestOwnerGroupMode(DestinationPath, SourcePath, fc) == False:
        return False

    return True

def Test(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    ShowMof('TEST', DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    fc = FileContext(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

    if not DestinationPath:
        return [-1]

    if fc.Ensure == "present":
        if fc.Type == "file":
            if TestFile(DestinationPath, SourcePath, fc) == False:
                return [-1]
        elif fc.Type == "directory":
            if TestDirectory(DestinationPath, SourcePath, fc) == False:
                return [-1]
        elif fc.Type == "link":
            if TestLink(DestinationPath, SourcePath, fc) == False:
                return [-1]
    elif fc.Ensure == "absent":
        if os.path.exists(DestinationPath):
            return [-1]

        return [0]

    return [0]

def Get(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    ShowMof('GET', DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    if not DestinationPath:
        Ensure = "Absent"
        SourcePath = Type = Contents = Checksum = Links = Owner = Group = Mode = ModifiedDate = ""
        return [-1, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]

    if not os.path.exists(DestinationPath):
        Ensure = "Absent"
        SourcePath = Type = Contents = Checksum = Links = Owner = Group = Mode = ModifiedDate = ""
        return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]
    fc = FileContext(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

    Contents = ""
    Checksum = ""
    Force = False
    Recurse = False
    Links = ""

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
        
    ModifiedDate = str(int(stat_info.st_mtime))
    Contents,error=ReadFile(DestinationPath)
    return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]

class FileContext:
    def __init__(self, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
        if not Checksum:
            Checksum = "md5"
        if not Type:
            Type = "file"
        if not Ensure:
            Ensure = "present"
        if not Links:
            Links = "manage"
        self.DestinationPath = DestinationPath
        self.SourcePath = SourcePath
        self.Ensure = Ensure.lower()
        self.Type = Type.lower()
        self.Force = Force
        self.Contents = Contents
        self.Checksum = Checksum.lower()
        self.Recurse = Recurse
        self.Links = Links.lower()
        self.Owner = Owner
        self.Group = Group
        self.ModifiedDate=''
        error=None

        if Mode:
            if len(Mode) == 9:
                try:
                    Mode = ConvertLongModeToNumeric(Mode)
                except Exception, error:
                    Print("Exception in ConvertLongModeToNumeric on " + Mode  + " Error: " + str(error),file=sys.stderr)    
            elif len(Mode) == 3:
                # Already in proper format
                pass
            else:
                Print("Error: Invalid Mode: " + Mode)
                Mode = ""

        self.Mode = Mode

import os
import pwd
import shutil
import grp
import time

try:
    import hashlib
    md5const = hashlib.md5
except ImportError:
    import md5
    md5const = md5.md5

BLOCK_SIZE = 8192

def Set_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    DestinationPath = DestinationPath.decode("utf-8")
    SourcePath = SourcePath.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    Type = Type.decode("utf-8")
    Force = Force.decode("utf-8")
    Checksum = Checksum.decode("utf-8")
    Recurse = Recurse.decode("utf-8")
    Links = Links.decode("utf-8")
    Owner = Owner.decode("utf-8")
    Group = Group.decode("utf-8")
    Mode = Mode.decode("utf-8")
    
    retval = Set(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    return retval

def Test_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    DestinationPath = DestinationPath.decode("utf-8")
    SourcePath = SourcePath.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    Type = Type.decode("utf-8")
    Force = Force.decode("utf-8")
    Checksum = Checksum.decode("utf-8")
    Recurse = Recurse.decode("utf-8")
    Links = Links.decode("utf-8")
    Owner = Owner.decode("utf-8")
    Group = Group.decode("utf-8")
    Mode = Mode.decode("utf-8")
    
    retval = Test(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)
    return retval

def Get_Marshall(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    DestinationPath = DestinationPath.decode("utf-8")
    SourcePath = SourcePath.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    Type = Type.decode("utf-8")
    Force = Force.decode("utf-8")
    Checksum = Checksum.decode("utf-8")
    Recurse = Recurse.decode("utf-8")
    Links = Links.decode("utf-8")
    Owner = Owner.decode("utf-8")
    Group = Group.decode("utf-8")
    Mode = Mode.decode("utf-8")

    retval = 0
    (retval, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate) = Get(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

    DestinationPath = DestinationPath.encode("utf-8")
    SourcePath = SourcePath.encode("utf-8")
    Ensure = Ensure.encode("utf-8")
    Type = Type.encode("utf-8")
    Force = Force.encode("utf-8")
    Contents = Contents.encode("utf-8")
    Checksum = Checksum.encode("utf-8")
    Recurse = Recurse.encode("utf-8")
    Links = Links.encode("utf-8")
    Owner = Owner.encode("utf-8")
    Group = Group.encode("utf-8")
    Mode = Mode.encode("utf-8")
    ModifiedDate = ModifiedDate.encode("utf-8")

    return [retval, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]


############################################################
### Begin user defined DSC functions
############################################################
def read_block():
    return current_file.read(BLOCK_SIZE)


def CompareFiles(DestinationPath, SourcePath, fc):
    # Reading and computing the hash here should be done in a block-by-block manner, 
    # in case the file is quite large.
    if fc.Checksum == "md5":
        src_hash = md5const()
        dest_hash = md5const()

        global current_file
        current_file = open(SourcePath)
        for block in iter(read_block, ''):
            src_hash.update(block)

        current_file = open(DestinationPath)
        for block in iter(read_block, ''):
            dest_hash.update(block)

        if src_hash.hexdigest() != dest_hash.hexdigest():
            return False
        else:
            return True
    elif fc.Checksum == "ctime":
        stat_dest = os.lstat(DestinationPath)
        stat_src = os.lstat(SourcePath)
        if stat_src.st_ctime > stat_dest.st_ctime:
            # Source is newer than Destination
            return False
        else:
            return True
    elif fc.Checksum == "mtime":
        stat_dest = os.lstat(DestinationPath)
        stat_src = os.lstat(SourcePath)
        if stat_src.st_mtime > stat_dest.st_mtime:
            # Source is newer than Destination
            return False
        else:
            return True
    return False

def WriteFile(path, contents):
    try:
        f = open(path, "wb")
        f.write(contents)
        return 0
    except IOError:
        return -1

def RemovePath(path):
    if os.path.islink(path) or os.path.isfile(path):
        os.remove(path)
    elif os.path.isdir(path):
        shutil.rmtree(path)
    else:
        print("Error: Unknown file type for file: " + path)
        
def TestOwnerGroupMode(DestinationPath, SourcePath, fc):
    stat_info = os.lstat(DestinationPath)

    if SourcePath:
        stat_info_src = os.lstat(SourcePath)

    if fc.Owner:
        Specified_Owner_ID = pwd.getpwnam(fc.Owner)[2]
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            return False
    elif SourcePath:
        # Owner wasn't specified, if SourcePath is specified then check that the Owners match
        if pwd.getpwuid(stat_info.st_uid)[2] != pwd.getpwuid(stat_info_src.st_uid)[2]:
            return False

    if fc.Group:
        Specified_Group_ID = grp.getgrnam(fc.Group)[2]
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

def ConvertLongModeToNumeric(DestinationPath, Mode):
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
        print("Error: Invalid character for character 0 in Mode for DestinationPath " + DestinationPath)

    if u_w == "w":
        first_digit += 2
    elif u_w == "-":
        pass
    else:
        print("Error: Invalid character for character 1 in Mode for DestinationPath " + DestinationPath)

    if u_x == "x":
        first_digit += 1
    elif u_x == "-":
        pass
    else:
        print("Error: Invalid character for character 2 in Mode for DestinationPath " + DestinationPath)

    if g_r == "r":
        second_digit += 4
    elif g_r == "-":
        pass
    else:
        print("Error: Invalid character for character 3 in Mode for DestinationPath " + DestinationPath)

    if g_w == "w":
        second_digit += 2
    elif g_w == "-":
        pass
    else:
        print("Error: Invalid character for character 4 in Mode for DestinationPath " + DestinationPath)

    if g_x == "x":
        second_digit += 1
    elif g_x == "-":
        pass
    else:
        print("Error: Invalid character for character 5 in Mode for DestinationPath " + DestinationPath)

    if o_r == "r":
        third_digit += 4
    elif o_r == "-":
        pass
    else:
        print("Error: Invalid character for character 6 in Mode for DestinationPath " + DestinationPath)

    if o_w == "w":
        third_digit += 2
    elif o_w == "-":
        pass
    else:
        print("Error: Invalid character for character 7 in Mode for DestinationPath " + DestinationPath)

    if o_x == "x":
        third_digit += 1
    elif o_x == "-":
        pass
    else:
        print("Error: Invalid character for character 8 in Mode for DestinationPath " + DestinationPath)

    return str(first_digit) + str(second_digit) + str(third_digit)

def SetOwnerGroupMode(DestinationPath, SourcePath, fc):
    stat_info = os.lstat(DestinationPath)

    if SourcePath:
        stat_info_src = os.lstat(SourcePath)
    
    if fc.Owner:
        Specified_Owner_ID = pwd.getpwnam(fc.Owner)[2]
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            print("Changing owner of " + DestinationPath + " to " + str(Specified_Owner_ID))
            os.lchown(DestinationPath, Specified_Owner_ID, -1)
    elif SourcePath:
        src_uid = pwd.getpwuid(stat_info_src.st_uid)[2]
        if pwd.getpwuid(stat_info.st_uid)[2] != src_uid:
            print("Changing owner of " + DestinationPath + " to " + str(src_uid))
            os.lchown(DestinationPath, src_uid, -1)

    if fc.Group:
        Specified_Group_ID = grp.getgrnam(fc.Group)[2]
        if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
            print("Changing group of " + DestinationPath + " to " + str(Specified_Group_ID))
            os.lchown(DestinationPath, -1, Specified_Group_ID)
    elif SourcePath:
        src_gid = grp.getgrgid(stat_info_src.st_gid)[2]
        if grp.getgrgid(stat_info.st_gid)[2] != src_gid:
            print("Changing group of " + DestinationPath + " to " + str(src_gid))
            os.lchown(DestinationPath, -1, src_gid)

    # Mode is irrelevant to symlinks
    if not os.path.islink(DestinationPath):
        if fc.Mode:
            if str(oct(stat_info.st_mode))[-3:] != fc.Mode:
                print("Changing mode of " + DestinationPath + " to " + fc.Mode)
                os.chmod(DestinationPath, int(fc.Mode, 8))
        elif SourcePath:
            src_mode = str(oct(stat_info_src.st_mode))[-3:]
            if str(oct(stat_info.st_mode))[-3:] != src_mode:
                print("Changing mode of " + DestinationPath + " to " + src_mode)
                os.chmod(DestinationPath, int(src_mode, 8))

    return True
    

       
def SetDirectoryRecursive(DestinationPath, SourcePath, fc):
    if not os.path.exists(DestinationPath):
        os.makedirs(DestinationPath)

    SetOwnerGroupMode(DestinationPath, SourcePath, fc)

    if fc.Recurse == "false":
        return True

    Destination_subfiles = os.listdir(DestinationPath)

    if not SourcePath:
        # Enforce Owner/Group/Mode specified
        for f in Destination_subfiles:
            f_destpath = os.path.join(DestinationPath, f)
            if not os.path.islink(f_destpath):
                if os.path.isfile(f_destpath):
                    SetOwnerGroupMode(f_destpath, "", fc)
                elif os.path.isdir(f_destpath):
                    SetDirectoryRecursive(f_destpath, "", fc)
        return True

    Source_subfiles = os.listdir(SourcePath)

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
    if os.path.exists(DestinationPath) and (os.path.islink(DestinationPath) or os.path.isdir(DestinationPath)):
        if fc.Force == "true":
            RemovePath(DestinationPath)
        else:
            print("Error: " + DestinationPath + " is not a file; cannot overwrite without the 'Force' option being true")
            return False

    if SourcePath:
        shutil.copyfile(SourcePath, DestinationPath)
    elif fc.Contents:
        if WriteFile(DestinationPath, fc.Contents) != 0:
            print("Error: Unable to write file at " + DestinationPath)
            return False
    else:
        # Create a file with nothing in it
        open(DestinationPath, 'a').close()

    SetOwnerGroupMode(DestinationPath, SourcePath, fc)

    return True
         
def SetDirectory(DestinationPath, SourcePath, fc):
    if os.path.exists(DestinationPath) and not os.path.isdir(DestinationPath):
        if fc.Force == "true":
            RemovePath(DestinationPath)
        else:
            return False

    return SetDirectoryRecursive(DestinationPath, SourcePath, fc)

def SetLink(DestinationPath, SourcePath, fc):
    if not SourcePath:
        print("Error: Need a source path in order to create a new symbolic link.")
        return False

    if os.path.exists(DestinationPath):
        if os.path.islink(DestinationPath) or fc.Force == "true":
            RemovePath(DestinationPath)
        else:
            print("Error: Unable to overwrite currently existing file at " + DestinationPath + " without the Force option being true.")
            return False

    if os.path.islink(SourcePath):
        if fc.Links == "follow":
            if os.path.isfile(SourcePath):
                SetFile(DestinationPath, os.path.realpath(SourcePath), fc)
            elif os.path.isdir(SourcePath):
                SetDirectoryRecursive(DestinationPath, os.path.realpath(SourcePath), fc)
        elif fc.Links == "manage":
            os.symlink(os.readlink(SourcePath), DestinationPath)
        elif fc.Links == "ignore":
            # Ignore all symlinks
            return True
    else:
        os.symlink(SourcePath, DestinationPath)

    SetOwnerGroupMode(DestinationPath, SourcePath, fc)

    return True

def Set(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    fc = FileContext(Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

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

    if fc.Recurse == "false":
        return True

    Destination_subfiles = os.listdir(DestinationPath)

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

    Source_subfiles = os.listdir(SourcePath)

    for f in Source_subfiles:
        if f not in Destination_subfiles:
            print("File: " + f + " does not exist in: " + SourcePath)
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
                    print("Error: Expecting a file, but source link points to directory")
                    return False
            else:
                if not os.path.islink(DestinationPath):
                    return False
                if os.readlink(DestinationPath) != os.readlink(SourcePath):
                    return False

        elif CompareFiles(DestinationPath, SourcePath, fc) == False:
            return False

    elif fc.Contents:
        dest_file = open(DestinationPath, "rb").read()
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
    fc = FileContext(Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

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
    if not DestinationPath:
        Ensure = "Absent"
        SourcePath = Type = Force = Contents = Checksum = Recurse = Links = Owner = Group = Mode = ModifiedDate = ""
        return [-1, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]

    if not os.path.exists(DestinationPath):
        Ensure = "Absent"
        SourcePath = Type = Force = Contents = Checksum = Recurse = Links = Owner = Group = Mode = ModifiedDate = ""
        return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]

    Contents = ""
    Checksum = ""
    Force = ""
    Recurse = ""
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

    return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate]


class FileContext:
    def __init__(self, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
        if not Checksum:
            Checksum = "md5"
        if not Recurse:
            Recurse = "false"
        if not Force:
            Force = "false"
        if not Type:
            Type = "file"
        if not Ensure:
            Ensure = "present"
        if not Links:
            Links = "manage"
    
        self.Ensure = Ensure.lower()
        self.Type = Type.lower()
        self.Force = Force.lower()
        self.Contents = Contents
        self.Checksum = Checksum.lower()
        self.Recurse = Recurse.lower()
        self.Links = Links.lower()
        self.Owner = Owner
        self.Group = Group

        if Mode:
            if len(Mode) == 9:
                Mode = ConvertLongModeToNumeric(DestinationPath, Mode)
            elif len(Mode) == 3:
                # Already in proper format
                pass
            else:
                print("Error: Invalid Mode: " + Mode)
                Mode = ""

        self.Mode = Mode

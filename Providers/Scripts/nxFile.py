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
    (retval, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, CreatedDate, ModifiedDate) = Get(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode)

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
    CreatedDate = CreatedDate.encode("utf-8")
    ModifiedDate = ModifiedDate.encode("utf-8")

    return [retval, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, CreatedDate, ModifiedDate]


############################################################
### Begin user defined DSC functions
############################################################
def read_block():
    return current_file.read(BLOCK_SIZE)


def CompareFiles(DestinationPath, SourcePath, Checksum):
    # Reading and computing the hash here should be done in a block-by-block manner, 
    # in case the file is quite large.
    if Checksum == "md5":
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
    elif Checksum == "ctime":
        stat_dest = os.stat(DestinationPath)
        stat_src = os.stat(SourcePath)
        if stat_src.st_ctime > stat_dest.st_ctime:
            # Source is newer than Destination
            return False
        else:
            return True
    elif Checksum == "mtime":
        stat_dest = os.stat(DestinationPath)
        stat_src = os.stat(SourcePath)
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
        
        

def CheckOwnerGroupMode(DestinationPath, SourcePath, Owner, Group, Mode):
    stat_info = os.stat(DestinationPath)

    if SourcePath:
        stat_info_src = os.stat(SourcePath)

    if Owner:
        Specified_Owner_ID = pwd.getpwnam(Owner)[2]
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            return False
    elif SourcePath:
        # Owner wasn't specified, if SourcePath is specified then check that the Owners match
        if pwd.getpwuid(stat_info.st_uid)[2] != pwd.getpwuid(stat_info_src.st_uid)[2]:
            return False

    if Group:
        Specified_Group_ID = grp.getgrnam(Group)[2]
        if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
            return False
    elif SourcePath:
        # Group wasn't specified, if SourcePath is specified then check that the Groups match
        if grp.getgrgid(stat_info.st_gid)[2] != grp.getgrgid(stat_info_src.st_gid)[2]:
            return False
        
    if Mode:
        if str(oct(stat_info.st_mode))[-3:] != Mode:
            return False
    elif SourcePath:
        # Mode wasn't specified, if SourcePath is specified then check that the Modes match
        if str(oct(stat_info.st_mode))[-3:] != str(oct(stat_info_src.st_mode))[-3:]:
            return False

    return True

def SetOwnerGroupMode(DestinationPath, SourcePath, Owner, Group, Mode):
    stat_info = os.stat(DestinationPath)

    if SourcePath:
        stat_info_src = os.stat(SourcePath)
    
    if Owner:
        Specified_Owner_ID = pwd.getpwnam(Owner)[2]
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            print("Changing owner of " + DestinationPath + " to " + str(Specified_Owner_ID))
            os.chown(DestinationPath, Specified_Owner_ID, -1)
    elif SourcePath:
        src_uid = pwd.getpwuid(stat_info_src.st_uid)[2]
        if pwd.getpwuid(stat_info.st_uid)[2] != src_uid:
            print("Changing owner of " + DestinationPath + " to " + str(src_uid))
            os.chown(DestinationPath, src_uid, -1)

    if Group:
        Specified_Group_ID = grp.getgrnam(Group)[2]
        if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
            print("Changing group of " + DestinationPath + " to " + str(Specified_Group_ID))
            os.chown(DestinationPath, -1, Specified_Group_ID)
    elif SourcePath:
        src_gid = grp.getgrgid(stat_info_src.st_gid)[2]
        if grp.getgrgid(stat_info.st_gid)[2] != src_gid:
            print("Changing group of " + DestinationPath + " to " + str(src_gid))
            os.chown(DestinationPath, -1, src_gid)

    if Mode:
        if str(oct(stat_info.st_mode))[-3:] != Mode:
            print("Changing mode of " + DestinationPath + " to " + Mode)
            os.chmod(DestinationPath, int(Mode, 8))
    elif SourcePath:
        src_mode = str(oct(stat_info_src.st_mode))[-3:]
        if str(oct(stat_info.st_mode))[-3:] != src_mode:
            print("Changing mode of " + DestinationPath + " to " + src_mode)
            os.chmod(DestinationPath, int(src_mode, 8))

    return True
    

        
def TestDirectory(DestinationPath, SourcePath, Owner, Group, Mode, Checksum, Recurse):
    if not os.path.exists(DestinationPath):
        return False

    Destination_subfiles = os.listdir(DestinationPath)

    if not SourcePath:
        if Recurse == "True":
            # Enforce Owner/Group/Mode specified
            for f in Destination_subfiles:
                f_destpath = os.path.join(DestinationPath, f)
                if not os.path.islink(f_destpath):
                    if os.path.isfile(f_destpath):
                        if CheckOwnerGroupMode(f_destpath, "", Owner, Group, Mode) == False:
                            return False
                    elif os.path.isdir(f_destpath):
                        if CheckOwnerGroupMode(f_destpath, "", Owner, Group, Mode) == False:
                            return False
                        if SetDirectory(f_destpath, "", Owner, Group, Mode, Checksum, Recurse) == False:
                            return False
        return True

    Source_subfiles = os.listdir(SourcePath)

    if len(Destination_subfiles) != len(Source_subfiles):
        print("Number of files do not match in dirs: " + DestinationPath + " != " + SourcePath)
        return False

    for f in Destination_subfiles:
        if f not in Source_subfiles:
            print("File: " + f + " does not exist in: " + SourcePath)
            return False

        f_destpath = os.path.join(DestinationPath, f)
        f_srcpath = os.path.join(SourcePath, f)

        if os.path.isfile(f_destpath) != os.path.isfile(f_srcpath):
            return False
        if os.path.isdir(f_destpath) != os.path.isdir(f_srcpath):
            return False
        if os.path.islink(f_destpath) != os.path.islink(f_srcpath):
            return False
        if CheckOwnerGroupMode(f_destpath, f_srcpath, Owner, Group, Mode) == False:
            return False

        if not os.path.islink(f_destpath):
            if os.path.isfile(f_destpath):
                if CompareFiles(f_destpath, f_srcpath, Checksum) == False:
                    return False
            if os.path.isdir(f_destpath):
                if TestDirectory(f_destpath, f_srcpath, Owner, Group, Mode, Checksum, Recurse) == False:
                    return False

    return True

def SetDirectory(DestinationPath, SourcePath, Owner, Group, Mode, Checksum, Recurse):
    if not os.path.exists(DestinationPath):
        os.makedirs(DestinationPath)

    Destination_subfiles = os.listdir(DestinationPath)

    if not SourcePath:
        if Recurse == "True":
            # Enforce Owner/Group/Mode specified
            for f in Destination_subfiles:
                f_destpath = os.path.join(DestinationPath, f)
                if not os.path.islink(f_destpath):
                    if os.path.isfile(f_destpath):
                        SetOwnerGroupMode(f_destpath, "", Owner, Group, Mode)
                    elif os.path.isdir(f_destpath):
                        SetOwnerGroupMode(f_destpath, "", Owner, Group, Mode)
                        SetDirectory(f_destpath, "", Owner, Group, Mode, Checksum, Recurse)
        return True

    Source_subfiles = os.listdir(SourcePath)

    # For all files in SourcePath's directory, ensure they exist with proper contents and stat in DestionationPath's directory 
    for f in Source_subfiles:
        f_srcpath = os.path.join(SourcePath, f)
        f_destpath = os.path.join(DestinationPath, f)

        replace_f = False
        if f not in os.listdir(DestinationPath):
            replace_f = True

        else:
            if os.path.islink(f_srcpath):
                if os.path.islink(f_destpath):
                    # Ensure readlink returns identical paths
                    if os.readlink(f_srcpath) != os.readlink(f_destpath):
                        RemovePath(f_destpath)
                        replace_f = True
                else:
                    RemovePath(f_destpath)
                    replace_f = True
            elif os.path.isfile(f_srcpath):
                if os.path.isfile(f_destpath):
                    # Ensure contents equivalent
                    if CompareFiles(f_destpath, f_srcpath, Checksum) == False:
                        RemovePath(f_destpath)
                        replace_f = True
                else:
                    RemovePath(f_destpath)
                    replace_f = True
            elif os.path.isdir(f_srcpath):
                if os.path.isdir(f_destpath):
                    SetDirectory(f_destpath, f_srcpath, Owner, Group, Mode, Checksum, Recurse)
                else:
                    RemovePath(f_destpath)
                    replace_f = True
        
        if replace_f:
            print("Adding: " + f + " to directory: " + DestinationPath)
            if os.path.isfile(f_srcpath):
                shutil.copyfile(f_srcpath, f_destpath)
            elif os.path.islink(f_srcpath):
                linkloc = os.readlink(f_srcpath)
                os.symlink(linkloc, f_destpath)
            elif os.path.isdir(f_srcpath):
                SetDirectory(f_destpath, f_srcpath, Owner, Group, Mode, Checksum, Recurse)

        if Recurse == "True":
            SetOwnerGroupMode(f_destpath, f_srcpath, Owner, Group, Mode)
        else:
            SetOwnerGroupMode(f_destpath, f_srcpath, "", "", "")
            
    # Remove files that are in DestinationPath but not in SourcePath
    for f in Destination_subfiles:
        if f not in Source_subfiles:
            RemovePath(os.path.join(DestinationPath, f))

    return True
            
def Set(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    if not DestinationPath:
        return [-1]

    if not Checksum:
        Checksum = "md5"
    if not Recurse:
        Recurse = "False"
    if not Force:
        Force = "False"
    if not Type:
        Type = "File"
    if not Ensure:
        Ensure = "Present"
    
    if Ensure == "Present":
        if Type == "File":
            if SourcePath:
                shutil.copyfile(SourcePath, DestinationPath)
            elif Contents:
                if (WriteFile(DestinationPath, Contents) != 0):
                    return [-1]
            else:
                if not os.path.isfile(DestinationPath):
                    # Create a file with nothing in it
                    open(DestinationPath, 'a').close()
                    
        elif Type == "Directory":
            if SourcePath:
                SetDirectory(DestinationPath, SourcePath, Owner, Group, Mode, Checksum, Recurse)
            elif not os.path.exists(DestinationPath):
                # Create a directory with nothing in it
                os.makedirs(DestinationPath)
            elif not os.path.isdir(DestinationPath):
                if Force == "True":
                    # Remove file. create directory
                    RemovePath(DestinationPath)
                    os.makedirs(DestinationPath)
                else:
                    # Error, file exists when we want it to be a directory, and Force is not True
                    return [-1]
    elif Ensure == "Absent":
        if Type == "File":
            if os.path.isfile(DestinationPath):
                os.remove(DestinationPath)
        if Type == "Directory":
            if os.path.isdir(DestinationPath):
                os.removedirs(DestinationPath)
                
        return [0]

    SetOwnerGroupMode(DestinationPath, SourcePath, Owner, Group, Mode)

    return [0]

def Test(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    if not DestinationPath:
        return [-1]

    if not Checksum:
        Checksum = "md5"
    if not Recurse:
        Recurse = "False"
    if not Force:
        Force = "False"
    if not Type:
        Type = "File"
    if not Ensure:
        Ensure = "Present"
    
    if Ensure == "Present":
        if Type == "File":
            if not os.path.isfile(DestinationPath):
                return [-1]
            if SourcePath:
                if not os.path.isfile(SourcePath):
                    return [-1]

                if CompareFiles(DestinationPath, SourcePath, Checksum) == False:
                    return [-1]

            elif Contents:
                dest_file = open(DestinationPath, "rb").read()
                if Contents != dest_file:
                    return [-1]
                
            else:
                # If file exists, we're good so far!
                pass
        elif Type == "Directory":
            if TestDirectory(DestinationPath, SourcePath, Owner, Group, Mode, Checksum, Recurse) == False:
                return [-1]

    elif Ensure == "Absent":
        if Type == "File":
            if os.path.isfile(DestinationPath):
                 return [-1]
        if Type == "Directory":
            if os.path.isdir(DestinationPath):
                 return [-1]
        return [0]

    if not CheckOwnerGroupMode(DestinationPath, SourcePath, Owner, Group, Mode):
        return [-1]

    return [0]

def Get(DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode):
    if not DestinationPath:
        Ensure = "Absent"
        SourcePath = Type = Force = Contents = Checksum = Recurse = Links = Owner = Group = Mode = CreatedDate = ModifiedDate = ""
        return [-1, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, CreatedDate, ModifiedDate]

    if not os.path.exists(DestinationPath):
        Ensure = "Absent"
        SourcePath = Type = Force = Contents = Checksum = Recurse = Links = Owner = Group = Mode = CreatedDate = ModifiedDate = ""
        return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, CreatedDate, ModifiedDate]

    Contents = ""
    Checksum = ""
    Force = ""
    Recurse = ""
    Links = ""

    stat_info = os.stat(DestinationPath)

    Owner = pwd.getpwuid(stat_info.st_uid)[0]
    Group = grp.getgrgid(stat_info.st_gid)[0]
    Mode = str(oct(stat_info.st_mode))[-3:]
    if os.path.isfile(DestinationPath):
        Type = "File"
    elif os.path.isdir(DestinationPath):
        Type = "Directory"
    else:
        Type = "Unknown"
        
    ModifiedDate = str(int(stat_info.st_mtime))

    # Linux does not keep track of file creation date
    CreatedDate = str(int(stat_info.st_mtime))

    return [0, DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, CreatedDate, ModifiedDate]


#def BasicUnitTests():
#    print(Test("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", ""))
#    print(Set("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", ""))

#BasicUnitTests()

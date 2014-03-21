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
            return -1
        else:
            return 0
    elif Checksum == "ctime":
        stat_dest = os.stat(DestinationPath)
        stat_src = os.stat(SourcePath)
        if stat_src.st_ctime > stat_dest.st_ctime:
            # Source is newer than Destination
            return -1
        else:
            return 0
    elif Checksum == "mtime":
        stat_dest = os.stat(DestinationPath)
        stat_src = os.stat(SourcePath)
        if stat_src.st_mtime > stat_dest.st_mtime:
            # Source is newer than Destination
            return -1
        else:
            return 0

def WriteFile(path, contents):
    try:
        f = open(path, "wb")
        f.write(contents)
        return 0
    except IOError:
        return -1

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
                if os.path.isdir(DestinationPath):
                    shutil.rmtree(DestinationPath)
                elif os.path.isfile(DestinationPath):
                    os.remove(DestinationPath)

                shutil.copytree(SourcePath, DestinationPath)
            elif not os.path.exists(DestinationPath):
                # Create a file with nothing in it
                os.makedirs(DestinationPath)
            elif not os.path.isdir(DestinationPath):
                if Force == "True":
                    # Remove file. create directory
                    os.remove(DestinationPath)
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

    if Type == "Directory" and Recurse == "True":
        for root, dirs, files in os.walk(DestinationPath):
            all_files_and_dirs = files
            all_files_and_dirs[len(all_files_and_dirs):] = dirs
            for name in files:
                path = os.path.join(root,name)
                stat_info = os.stat(path)
                if Owner:
                    # handle owner stuff
                    Specified_Owner_ID = pwd.getpwnam(Owner)[2]
                    if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
                        os.chown(path, Specified_Owner_ID, -1)

                if Group:
                    # handle group stuff
                    Specified_Group_ID = grp.getgrnam(Group)[2]
                    if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
                        os.chown(path, -1, Specified_Group_ID)

                if Mode:
                    # handle mode stuff
                    os.chmod(path, int(Mode, 8))


    stat_info = os.stat(DestinationPath)
    if Owner:
        # handle owner stuff
        Specified_Owner_ID = pwd.getpwnam(Owner)[2]
        if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
            os.chown(DestinationPath, Specified_Owner_ID, -1)

    if Group:
        # handle group stuff
        Specified_Group_ID = grp.getgrnam(Group)[2]
        if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
            os.chown(DestinationPath, -1, Specified_Group_ID)

    if Mode:
        # handle mode stuff
        os.chmod(DestinationPath, int(Mode, 8))


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

                if CompareFiles(DestinationPath, SourcePath, Checksum) != 0:
                    return [-1]

            elif Contents:
                dest_file = open(DestinationPath, "rb").read()
                if Contents != dest_file:
                    return [-1]
                
            else:
                # If file exists, we're good so far!
                pass
        elif Type == "Directory":
            if not os.path.isdir(DestinationPath):
                return [-1]

            # TODO: RECURSIVE DIRECTORIES

            pass
    elif Ensure == "Absent":
        if Type == "File":
            if os.path.isfile(DestinationPath):
                 return [-1]
        if Type == "Directory":
            if os.path.isdir(DestinationPath):
                 return [-1]
        return [0]

    if Type == "Directory" and Recurse == "True":
        for root, dirs, files in os.walk(DestinationPath):
            all_files_and_dirs = files
            all_files_and_dirs[len(all_files_and_dirs):] = dirs
            for name in files:
                path = os.path.join(root,name)
                stat_info = os.stat(path)
                if Owner:
                    # handle owner stuff
                    Specified_Owner_ID = pwd.getpwnam(Owner)[2]
                    if Specified_Owner_ID != pwd.getpwuid(stat_info.st_uid)[2]:
                        return [-1]

                if Group:
                    # handle group stuff
                    Specified_Group_ID = grp.getgrnam(Group)[2]
                    if Specified_Group_ID != grp.getgrgid(stat_info.st_gid)[2]:
                        return [-1]

                if Mode:
                    # handle mode stuff
                    if str(oct(stat_info.st_mode))[-3:] != Mode:
                        return [-1]


    stat_info = os.stat(DestinationPath)    
    if Owner:
        # handle owner stuff
        dest_owner = pwd.getpwuid(stat_info.st_uid)[0]
        if Owner != dest_owner:
            return [-1]

    if Group:
        # handle group stuff
        dest_group = grp.getgrgid(stat_info.st_uid)[0]
        if Group != dest_group:
            return [-1]

    if Mode:
        # handle mode stuff
        if str(oct(stat_info.st_mode))[-3:] != Mode:
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

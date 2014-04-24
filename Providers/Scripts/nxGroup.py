import subprocess
import shutil
import pwd
import grp
import os
import stat
import time
import datetime
import operator

def Set_Marshall(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    GroupName = GroupName.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    Members = Members.decode("utf-8")
    MembersToInclude = MembersToInclude.decode("utf-8")
    MembersToExclude = MembersToExclude.decode("utf-8")
    PreferredGroupID = PreferredGroupID.decode("utf-8")

    retval = Set(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID)
    return retval

def Test_Marshall(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    GroupName = GroupName.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    Members = Members.decode("utf-8")
    MembersToInclude = MembersToInclude.decode("utf-8")
    MembersToExclude = MembersToExclude.decode("utf-8")
    PreferredGroupID = PreferredGroupID.decode("utf-8")

    retval = Test(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID)
    return retval

def Get_Marshall(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    GroupName = GroupName.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    Members = Members.decode("utf-8")
    MembersToInclude = MembersToInclude.decode("utf-8")
    MembersToExclude = MembersToExclude.decode("utf-8")
    PreferredGroupID = PreferredGroupID.decode("utf-8")

    retval = 0
    (retval, GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID) = Get(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID)

    GroupName = GroupName.encode("utf-8")
    Ensure = Ensure.encode("utf-8")
    Members = Members.encode("utf-8")
    MembersToInclude = MembersToInclude.encode("utf-8")
    MembersToExclude = MembersToExclude.encode("utf-8")
    PreferredGroupID = PreferredGroupID.encode("utf-8")

    return [retval, GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID]

############################################################
### Begin user defined DSC functions
############################################################

groupadd_path = "/usr/sbin/groupadd"
groupdel_path = "/usr/sbin/groupdel"
groupmod_path = "/usr/sbin/groupmod"
gpasswd_path = "/usr/bin/gpasswd"
add_user_to_group_gpasswd = gpasswd_path + " -a "
delete_user_from_group_gpasswd = gpasswd_path + " -d "
add_user_to_group_groupmod = groupmod_path + " -A "
delete_user_from_group_groupmod = groupmod_path + " -R "

add_user_to_group = add_user_to_group_gpasswd
delete_user_from_group = delete_user_from_group_gpasswd

# If gpasswd fails to let us add/remove users, try groupmod
def SwapGroupModCommand():
    global add_user_to_group
    global delete_user_from_group

    if add_user_to_group == add_user_to_group_gpasswd:
        add_user_to_group = add_user_to_group_groupmod
        delete_user_from_group = delete_user_from_group_groupmod
    else:
        add_user_to_group = add_user_to_group_gpasswd
        delete_user_from_group = delete_user_from_group_gpasswd

def ReadPasswd(filename):
    f = open(filename, "r")
    lines = f.read().split("\n")
    
    entries = dict()
    for line in lines:
        tokens = line.split(":")
        if len(tokens) > 1:
            entries[tokens[0]] = tokens[1:]

    return entries

def ParseList(s):
    return s.split("\n")[:-1]

def get_GID(n):
    return int(n[1][1])

def AddUserToGroup(UserName, GroupName):
    retval = os.system(add_user_to_group + UserName + " " + GroupName)
    if retval != 0:
        SwapGroupModCommand()
        retval = os.system(add_user_to_group + UserName + " " + GroupName)
        if retval != 0:
            print("Error adding user: " + UserName + " to group: " + GroupName)
            return False
    return True

def DeleteUserFromGroup(UserName, GroupName):
    retval = os.system(delete_user_from_group + UserName + " " + GroupName)
    if retval != 0:
        SwapGroupModCommand()
        retval = os.system(delete_user_from_group + UserName + " " + GroupName)
        if retval != 0:
            print("Error removing user: " + UserName + " from group: " + GroupName)
            return False
    return True

def Set(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    if not Ensure:
        Ensure = "present"

    group_entries = ReadPasswd("/etc/group")
    Members_list = ParseList(Members)

    if Ensure.lower() == "absent":
        if GroupName in group_entries:
            # Delete group
            print("Deleting group")
            retval = os.system(groupdel_path + " " + GroupName)
            if retval != 0:
                print(groupdel_path + " " + GroupName + " failed.")
                return [-1]
    else:
        if GroupName not in group_entries:
            print("Group does not exist. Creating it.")
            retval = os.system(groupadd_path + " " + GroupName)
            if retval != 0:
                print(groupadd_path + " " + GroupName + " failed.")
                return [-1]

        if Members:
            if MembersToInclude or MembersToExclude:
                print("If Members is provided, Include and Exclude are not allowed.")
                return [-1]

            group_members = group_entries[GroupName][2].split(",")
            for member in Members_list:
                if member not in group_members:
                    print("Member: " + member + " not in member list for group: " + GroupName + ".  Adding.")
                    if AddUserToGroup(member, GroupName) == False:
                        return [-1]
            for member in group_members:
                if member not in Members_list:
                    print("Member: " + member + " is in the member list for group: " + GroupName + " but not speficied in Members.  Removing.")
                    if DeleteUserFromGroup(member, GroupName) == False:
                        return [-1]
                

        else:
            group_members = group_entries[GroupName][2].split(",")
            if MembersToInclude:
                MembersToInclude_list = ParseList(MembersToInclude)
                for member in MembersToInclude_list:
                    if member not in group_members:
                        print("Member: " + member + " not in member list for group: " + GroupName + ".  Adding.")
                        if AddUserToGroup(member, GroupName) == False:
                            return [-1]
            if MembersToExclude:
                MembersToExclude_list = ParseList(MembersToExclude)
                for member in MembersToExclude_list:
                    if member in group_members:
                        print("Member: " + member + " is in member list for group: " + GroupName + ".  Removing.")
                        if DeleteUserFromGroup(member, GroupName) == False:
                            return [-1]
    
    return [0]


def Test(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    if not Ensure:
        Ensure = "present"

    group_entries = ReadPasswd("/etc/group")
    Members_list = ParseList(Members)

    if Ensure.lower() == "absent":
        if GroupName not in group_entries:
            return [0]
        else:
            return [-1]
    else:
        if GroupName not in group_entries:
            print("Group does not exist.")
            return [-1]
        
        if Members:
            if MembersToInclude or MembersToExclude:
                print("If Members is provided, Include and Exclude are not allowed.")
                return [-1]

            group_members = group_entries[GroupName][2].split(",")

            for member in Members_list:
                if member not in group_members:
                    print("Member: " + member + " not in member list for group: " + GroupName)
                    return [-1]
            for member in group_members:
                if member not in Members_list:
                    print("Member: " + member + " is in the member list for group: " + GroupName + " but not speficied in Members")
                    return [-1]
                
        else:
            group_members = group_entries[GroupName][2].split(",")
            if MembersToInclude:
                MembersToInclude_list = ParseList(MembersToInclude)
                for member in MembersToInclude_list:
                    if member not in group_members:
                        print("Member: " + member + " not in member list for group: " + GroupName)
                        return [-1]
            if MembersToExclude:
                MembersToExclude_list = ParseList(MembersToExclude)
                for member in MembersToExclude_list:
                    if member in group_members:
                        print("Member: " + member + " is in member list for group: " + GroupName)
                        return [-1]

    return [0]


def Get(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    group_entries = ReadPasswd("/etc/group")
    Members = MembersToInclude = MembersToExclude = ""

    if GroupName not in group_entries:
        Ensure = "absent"
        PreferredGroupID = ""
    else:
        Ensure = "present"
        PreferredGroupID = group_entries[GroupName][1]
        group_members = group_entries[GroupName][2].split(",")
        for member in group_members:
            Members += member + "\n"

    return [0, GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID]


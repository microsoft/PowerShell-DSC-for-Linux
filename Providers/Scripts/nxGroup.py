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

def GetClosestGID(group_entries, PreferredGroupID):
    sorted_gids = sorted(group_entries.iteritems(), key=get_GID)
    finalGID = -1

    for i in range(0, len(sorted_gids)):
        currentGID = get_GID(sorted_gids[i])
        if int(PreferredGroupID) == int(currentGID):
            # Group exists with preferred GID.  Find next GID that's open.
            print("Found group with matching GID at: " + str(i))
            break
        elif int(PreferredGroupID) < int(currentGID):
            print("No group with PreferredGroupID.")
            finalGID = PreferredGroupID

    # If we're here, we found a GroupID that matches our PreferredID.  Now we're going to increment one GID
    # at a time to find the next available GID.
    currentGID = get_GID(sorted_gids[i])
    while finalGID == -1:
        if i+1 >= len(sorted_gids):
            finalGID = int(currentGID) + 1

        nextGID = get_GID(sorted_gids[i])
        if (int(nextGID) - int(currentGID)) != 1:
            finalGID = int(currentGID) + 1

        currentGID = nextGID
        

    print("GetClosestGID returning: " + str(finalGID))
    return str(finalGID)

def Set(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    if not Ensure:
        Ensure = "Present"

    group_entries = ReadPasswd("/etc/group")
    Members_list = ParseList(Members)

    if Ensure == "Absent":
        if GroupName in group_entries:
            # Delete group
            print("Deleting group")
            retval = os.system("/usr/sbin/groupdel " + GroupName)
            return [retval]
    else:
        if GroupName not in group_entries:
            print("Group does not exist. Creating it.")
            if PreferredGroupID:
                # GetClosestGID to PreferredGroupID and set it
                newGID = GetClosestGID(group_entries, PreferredGroupID)
                retval = os.system("/usr/sbin/groupadd -g " + newGID + " " + GroupName)

                # Reread group
                group_entries = ReadPasswd("/etc/group")
                if retval != 0:
                    print("/usr/sbin/groupadd -g " + newGID + " " + GroupName + " failed.")
                    return [-1]
        else:
            if PreferredGroupID:
                # If group's ID is not PreferredGroupID, check if its possible to change to the Preferred.
                GroupID = group_entries[GroupName][1]
                if PreferredGroupID != GroupID:
                    closestGID = GetClosestGID(group_entries, PreferredGroupID)
                    if GroupID != closestGID:
                        retval = os.system("/usr/sbin/groupmod -g " + closestGID + " " + GroupName)
                        if retval != 0:
                            print("/usr/sbin/groupmod -g " + closestGID + " " + GroupName + " failed.")
                            return [-1]

        if Members:
            if MembersToInclude or MembersToExclude:
                print("If Members is provided, Include and Exclude are not allowed.")
                return [-1]

            group_members = group_entries[GroupName][2].split(",")
            for member in Members_list:
                if member not in group_members:
                    print("Member: " + member + " not in member list for group: " + GroupName + ".  Adding.")
                    retval = os.system("/usr/bin/gpasswd -a " + member + " " + GroupName)
                    if retval != 0:
                        print("Error adding user: " + member + " to group: " + GroupName)
                        return [-1]
            for member in group_members:
                if member not in Members_list:
                    print("Member: " + member + " is in the member list for group: " + GroupName + " but not speficied in Members.  Removing.")
                    retval = os.system("/usr/bin/gpasswd -d " + member + " " + GroupName)
                    if retval != 0:
                        print("Error removing user: " + member + " from group: " + GroupName)
                        return [-1]
                

        else:
            group_members = group_entries[GroupName][2].split(",")
            if MembersToInclude:
                MembersToInclude_list = ParseList(MembersToInclude)
                for member in MembersToInclude_list:
                    if member not in group_members:
                        print("Member: " + member + " not in member list for group: " + GroupName + ".  Adding.")
                        retval = os.system("/usr/bin/gpasswd -a " + member + " " + GroupName)
                        if retval != 0:
                            print("Error adding user: " + member + " to group: " + GroupName)
                            return [-1]
            if MembersToExclude:
                MembersToExclude_list = ParseList(MembersToExclude)
                for member in MembersToExclude_list:
                    if member in group_members:
                        print("Member: " + member + " is in member list for group: " + GroupName + ".  Removing.")
                        retval = os.system("/usr/bin/gpasswd -d " + member + " " + GroupName)
                        if retval != 0:
                            print("Error removing user: " + member + " from group: " + GroupName)
                            return [-1]
    
    return [0]


def Test(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    if not Ensure:
        Ensure = "Present"

    group_entries = ReadPasswd("/etc/group")
    Members_list = ParseList(Members)

    if Ensure == "Absent":
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

        if PreferredGroupID:
            # If group's ID is not PreferredGroupID, check if its possible to change to the Preferred.
            GroupID = group_entries[GroupName][1]
            if PreferredGroupID != GroupID:
                if GroupID != GetClosestGID(group_entries, PreferredGroupID):
                    print("There's a GID closer to the PreferredGroupID available.")
                    return [-1]
    return [0]


def Get(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID):
    group_entries = ReadPasswd("/etc/group")
    Members = MembersToInclude = MembersToExclude = ""

    if GroupName not in group_entries:
        Ensure = "Absent"
        PreferredGroupID = ""
    else:
        Ensure = "Present"
        PreferredGroupID = group_entries[GroupName][1]
        group_members = group_entries[GroupName][2].split(",")
        for member in group_members:
            Members += member + "\n"

    return [0, GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID]

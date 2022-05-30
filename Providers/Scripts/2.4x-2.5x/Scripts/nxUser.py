#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================
import os
import sys
import datetime
import imp
import copy
import fnmatch
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
helperlib = imp.load_source('helperlib', '../helperlib.py')
LG = nxDSCLog.DSCLog

# [ClassVersion("1.0.0"), FriendlyName("nxUser"),SupportsInventory()]
# class MSFT_nxUserResource : OMI_BaseResource
# {
#        [Key, InventoryFilter] string UserName;
#        [write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
#        [write, InventoryFilter] string FullName;
#        [write, InventoryFilter] string Description;
#        [write] string Password;
#        [write] boolean Disabled;
#        [write] boolean PasswordChangeRequired;
#        [write] string HomeDirectory;
#        [write] string GroupID;
#        [read] string UserID;
# };
global show_mof
show_mof = False


def init_vars(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if UserName is not None:
        UserName = UserName.encode('ascii', 'ignore')
    else:
        UserName = ''
    if Ensure is not None and Ensure != '':
        Ensure = Ensure.encode('ascii', 'ignore').lower()
    else:
        Ensure = 'present'
    if FullName is not None:
        FullName = FullName.encode('ascii', 'ignore')
    else:
        FullName = ''
    if Description is not None:
        Description = Description.encode('ascii', 'ignore')
    else:
        Description = ''
    if Password is not None:
        Password = Password.encode('ascii', 'ignore')
    else:
        Password = ''
    if Disabled is None:
        Disabled = False
    Disabled = ( Disabled == True ) # this arrives as a 0 or 1
    if PasswordChangeRequired is None:
        PasswordChangeRequired = False
    PasswordChangeRequired = ( PasswordChangeRequired == True ) # this arrives as a 0 or 1
    if HomeDirectory is not None:
        HomeDirectory = HomeDirectory.encode('ascii', 'ignore')
    else:
        HomeDirectory = ''
    if GroupID is not None:
        GroupID = GroupID.encode('ascii', 'ignore')
    else:
        GroupID = ''

    return UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID


def Set_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        return [-1]
    (UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID) = \
        init_vars(UserName, Ensure, FullName, Description, Password,
                  Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    retval = Set(UserName, Ensure, FullName, Description, Password,
                 Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    return retval


def Test_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        return [-1]
    (UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID) = \
        init_vars(UserName, Ensure, FullName, Description, Password,
                  Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    retval = Test(UserName, Ensure, FullName, Description, Password,
                  Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    return retval


def Get_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if helperlib.CONFIG_SYSCONFDIR_DSC == "omsconfig":
        return [-1]
    arg_names = list(locals().keys())
    (UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID) = \
        init_vars(UserName, Ensure, FullName, Description, Password,
                  Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    retval = 0
    (retval, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID, UserID) = Get(
        UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    UserName = protocol.MI_String(UserName)
    Ensure = protocol.MI_String(Ensure)
    FullName = protocol.MI_String(FullName)
    PasswordChangeRequired = protocol.MI_Boolean(PasswordChangeRequired)
    Disabled = protocol.MI_Boolean(Disabled)
    Description = protocol.MI_String(Description)
    Password = protocol.MI_String(Password)
    HomeDirectory = protocol.MI_String(HomeDirectory)
    GroupID = protocol.MI_String(GroupID)
    UserID = protocol.MI_String(UserID)
    arg_names.append('UserID')
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

def Inventory_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    (UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID) = \
        init_vars(UserName, Ensure, FullName, Description, Password,
                  Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    (retval, Inventory) = GetInventory(
        UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    for d in Inventory:
        d['UserName'] = protocol.MI_String(d['UserName'])
        d['Ensure'] = protocol.MI_String('Present')
        d['FullName'] = protocol.MI_String(d['FullName'])
        d['PasswordChangeRequired'] = protocol.MI_Boolean(d['PasswordChangeRequired'])
        d['Disabled'] = protocol.MI_Boolean(d['Disabled'])
        d['Description'] = protocol.MI_String(d['Description'])
        d['Password'] = protocol.MI_String(d['Password'])
        d['HomeDirectory'] = protocol.MI_String(d['HomeDirectory'])
        d['GroupID'] = protocol.MI_String(d['GroupID'])
        d['UserID'] = protocol.MI_String(d['UserID'])
        d = protocol.MI_Instance(d)
    Inventory = protocol.MI_InstanceA(Inventory)
    retd = {}
    retd["__Inventory"] = Inventory
    return retval, retd


############################################################
# Begin user defined DSC functions
############################################################

def SetShowMof(a):
    global show_mof
    show_mof = a


def ShowMof(op, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if not show_mof:
        return
    mof = ''
    mof += op + ' nxUser MyUser \n'
    mof += '{\n'
    mof += '    UserName = "' + UserName + '"\n'
    mof += '    Ensure = "' + Ensure + '"\n'
    mof += '    FullName = "' + FullName + '"\n'
    mof += '    Description = "' + Description + '"\n'
    mof += '    Password = "' + Password + '"\n'
    mof += '    Disabled = ' + str(Disabled) + '\n'
    mof += '    PasswordChangeRequired = ' + str(PasswordChangeRequired) + '\n'
    mof += '    HomeDirectory = "' + HomeDirectory + '"\n'
    mof += '    GroupID = "' + str(GroupID) + '"\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    Print(mof, file=f)
    LG().Log('INFO', mof)
    f.close()


def Print(s, file=sys.stdout):
    file.write(s + '\n')


def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError, err:
        return None, err
    return f, None

userdel_path = "/usr/sbin/userdel"
useradd_path = "/usr/sbin/useradd"
usermod_path = "/usr/sbin/usermod"
chage_path = "/usr/bin/chage"


def ReadPasswd(filename):
    f, error = opened_w_error(filename, 'rb')
    if error:
        Print("Exception opening file " + filename + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + filename + " Error: " + str(error))
        return None
    else:
        lines = f.read().split("\n")
        f.close()
    entries = dict()
    for line in lines:
        tokens = line.split(":")
        if len(tokens) > 1:
            entries[tokens[0]] = tokens[1:]

    return entries


def PasswordExpired(shadow_entry):
    # No entries for the "last" field means Password is Expired.
    if shadow_entry[1] == "":
        return True

    # Passwords must be changed if their "last" day is 0
    if shadow_entry[1] == "0":
        return True

    # "99999" means "never expire"
    if shadow_entry[3] == "99999" or shadow_entry[3] == "" :
        return False

    day_0 = datetime.datetime.utcfromtimestamp(0)
    day_now = datetime.datetime.today()
    days_since_day_0 = (day_now - day_0).days

    days_since_last_password_change = days_since_day_0 - int(shadow_entry[1])
    number_of_days_password_is_valid_for = int(shadow_entry[3])

    if days_since_last_password_change > number_of_days_password_is_valid_for:
        return True

    return False


def Set(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    ShowMof('SET', UserName, Ensure, FullName, Description, Password,
            Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    passwd_entries = None
    shadow_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries is None:
        return [-1]
    shadow_entries = ReadPasswd("/etc/shadow")
    if shadow_entries is None:
        return [-1]
    old_passwd_entries = passwd_entries
    usermod_string = ""
    usermodonly_string = ""
    if Ensure == "absent":
        exit_code = os.system(userdel_path + " " + UserName)
    else:
        usermod_string = ""

        if FullName or Description:
            usermod_string += " -c \""

            if FullName:
                usermod_string += FullName
            if Description:
                usermod_string += "," + Description

            usermod_string += "\""

        if HomeDirectory:
            usermod_string += " -d \"" + HomeDirectory + "\" -m "

        if GroupID:
            usermod_string += " -g " + GroupID

        if UserName not in passwd_entries:
            exit_code = os.system(
                useradd_path + " " + usermod_string + " " + UserName)
            if exit_code is not 0:
                return [exit_code]

            if len(usermodonly_string) > 0:
                exit_code = os.system(
                    usermod_path + " " + usermodonly_string + " " + UserName)
        else:
            Print(usermod_string, file=sys.stderr)
            LG().Log('INFO', usermod_string)
            if len(usermodonly_string + usermod_string) > 0:
                exit_code = os.system(
                    usermod_path + " " + usermodonly_string + usermod_string + " " + UserName)

        disabled_user_string = ""
        usermod_string = ""
        if Disabled is True:
            disabled_user_string = "!"

        if len(Password) > 0:
            usermod_string += " -p \"" + disabled_user_string + \
                Password.replace("$", "\$") + "\""
        elif Disabled is True:
            usermodonly_string += " -L"
        elif Disabled is False:
            passwd_entries = ReadPasswd("/etc/passwd")
            if passwd_entries is None:
                return [-1]
            shadow_entries = ReadPasswd("/etc/shadow")
            if shadow_entries is None:
                return [-1]
            if UserName in shadow_entries:
                cur_pass = shadow_entries[UserName][0]
                if cur_pass == "!!":
                    Print("Unable to unlock user: " + UserName +
                          ".  Password is not set.", file=sys.stderr)
                    LG().Log('ERROR', "Unable to unlock user: " +
                             UserName + ".  Password is not set.")
                    return [-1]
                elif cur_pass[0] == '!':
                    if len(cur_pass) > 1:
                        usermodonly_string += " -U"
                    else:
                        Print("Unable to unlock user: " + UserName +
                              ".  Doing so would result in a passwordless account.", file=sys.stderr)
                        LG().Log('ERROR', "Unable to unlock user: " + UserName +
                                 ".  Doing so would result in a passwordless account.")
                        return [-1]
        Print(usermod_string, file=sys.stderr)
        LG().Log('INFO', usermod_string)
        if len(usermodonly_string + usermod_string) > 0:
            exit_code = os.system(
                usermod_path + " " + usermodonly_string + usermod_string + " " + UserName)
        # force password change only if we created the account
        if PasswordChangeRequired is True and UserName not in old_passwd_entries:
            exit_code = os.system(chage_path + " -d  0 " + UserName)

    return [exit_code]


def Test(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    ShowMof('TEST', UserName, Ensure, FullName, Description, Password,
            Disabled, PasswordChangeRequired, HomeDirectory, GroupID)

    passwd_entries = None
    shadow_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries is None:
        return [-1]
    shadow_entries = ReadPasswd("/etc/shadow")
    if shadow_entries is None:
        return [-1]

    if not Ensure:
        Ensure = "present"

    if Ensure == "absent":
        if UserName not in passwd_entries:
            return [0]
        else:
            Print(UserName + " in passwd_entries", file=sys.stderr)
            LG().Log('ERROR', UserName + " in passwd_entries")
            return [-1]
    elif Ensure == "present":
        if UserName not in passwd_entries:
            Print(UserName + " not in passwd_entries", file=sys.stderr)
            LG().Log('ERROR', UserName + " not in passwd_entries")
            return [-1]
        if UserName not in shadow_entries:
            Print(UserName + " not in shadow_entries", file=sys.stderr)
            LG().Log('ERROR', UserName + " not in shadow_entries")
            return [-1]

        if len(passwd_entries[UserName]) < 6:
            Print("Unable to read /etc/passwd entry for username: " +
                  UserName, file=sys.stderr)
            LG().Log(
                'ERROR', "Unable to read /etc/passwd entry for username: " + UserName)
            return [-1]
        if len(shadow_entries[UserName]) < 8:
            Print("Unable to read /etc/shadow entry for username: " +
                  UserName, file=sys.stderr)
            LG().Log(
                'ERROR', "Unable to read /etc/shadow entry for username: " + UserName)
            return [-1]

        extra_fields = passwd_entries[UserName][3].split(",")

        if FullName and extra_fields[0] != FullName:
            Print("Incorrect full name (" + extra_fields[
                  0] + "), should be: " + FullName + ", for username: " + UserName, file=sys.stderr)
            LG().Log('ERROR', "Incorrect full name (" +
                     extra_fields[0] + "), should be: " + FullName + ", for username: " + UserName)
            return [-1]

        if Description:
            if len(extra_fields) < 2:
                Print("There is no description.", file=sys.stderr)
                LG().Log('ERROR', "There is no description.")
                return [-1]
            elif extra_fields[1] != Description:
                Print(
                    "Incorrect description for username: " + UserName, file=sys.stderr)
                LG().Log(
                    'ERROR', "Incorrect description for username: " + UserName)
                return [-1]

        if HomeDirectory and passwd_entries[UserName][4] != HomeDirectory:
            Print("Home directories do not match", file=sys.stderr)
            LG().Log('ERROR', "Home directories do not match")
            return [-1]

        if GroupID and passwd_entries[UserName][2] != GroupID:
            Print("GroupID does not match", file=sys.stderr)
            LG().Log('ERROR', "GroupID does not match")
            return [-1]

        if len(Password) > 0:
            read_password = shadow_entries[UserName][0]
            if len(read_password) is 0:
                Print("Password does not match", file=sys.stderr)
                LG().Log('ERROR', "Password does not match")
                return [-1]
            if read_password[0] == "!":
                read_password = read_password[1:]
            if read_password != Password:
                Print("Password does not match", file=sys.stderr)
                LG().Log('ERROR', "Password does not match")
                return [-1]
        if PasswordChangeRequired is True and not PasswordExpired(shadow_entries[UserName]):
            Print(
                "PasswordChangeRequired is True and the password is not expired.", file=sys.stderr)
            LG().Log(
                'ERROR', "PasswordChangeRequired is True and the password is not expired.")
            return [-1]
        elif PasswordChangeRequired is False and PasswordExpired(shadow_entries[UserName]):
            Print(
                "PasswordChangeRequired is False and the password is expired.", file=sys.stderr)
            LG().Log(
                'ERROR', "PasswordChangeRequired is False and the password is expired.")
            return [-1]

        if Disabled is True and shadow_entries[UserName][0][0] != "!":
            Print("Account not disabled", file=sys.stderr)
            LG().Log('ERROR', "Account not disabled")
            return [-1]
        if Disabled is False and shadow_entries[UserName][0][0] == "!":
            Print("Account disabled", file=sys.stderr)
            LG().Log('ERROR', "Account disabled")
            return [-1]

    return [0]


def Get(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    ShowMof('GET', UserName, Ensure, FullName, Description, Password,
            Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    UserID = ''
    passwd_entries = None
    shadow_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries is None:
        return [-1, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID, UserID]
    shadow_entries = ReadPasswd("/etc/shadow")
    if shadow_entries is None:
        return [-1, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID, UserID]

    exit_code = 0

    if UserName not in passwd_entries:
        FullName = Description = Password = HomeDirectory = GroupID = ""
        return [exit_code, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID, UserID]

    extra_fields = passwd_entries[UserName][3].split(",")
    FullName = extra_fields[0]
    if len(extra_fields) > 1:
        Description = extra_fields[1]

    HomeDirectory = passwd_entries[UserName][4]
    UserID = passwd_entries[UserName][1]
    GroupID = passwd_entries[UserName][2]
    Password = shadow_entries[UserName][0]
    Disabled = False
    if len(Password) > 0:
        if Password[0] == "!":
            Disabled = True
    Password = '' # not showing the password.
    if PasswordExpired(shadow_entries[UserName]):
        PasswordChangeRequired = True
    else:
        PasswordChangeRequired = False

    return [exit_code, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID, UserID]

def GetInventory(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    Inventory=[]
    passwd_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries is None:
        return [-1, Inventory]
    exit_code = 0
    d={}
    for Uname in passwd_entries.keys():
        if len(UserName) and not fnmatch.fnmatch(Uname,UserName):
            continue
        d['UserName'] = Uname
        extra_fields = passwd_entries[Uname][3].split(",")
        d['FullName'] = extra_fields[0]
        if len(FullName) and not fnmatch.fnmatch(d['FullName'],FullName):
            continue
        d['Description'] = ''
        if len(extra_fields) > 1:
            d['Description'] = extra_fields[1]
        if len(Description) and not fnmatch.fnmatch(d['Description'],Description):
            continue
        d['HomeDirectory'] = passwd_entries[Uname][4]
        d['UserID'] = passwd_entries[Uname][1]
        d['GroupID'] = passwd_entries[Uname][2]
        d['Disabled'] = False
        d['Password'] = '' # not showing the password.
        d['PasswordChangeRequired'] = False
        Inventory.append(copy.deepcopy(d))
    return [exit_code, Inventory]

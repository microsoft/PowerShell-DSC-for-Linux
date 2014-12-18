#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================

import os
import sys
import datetime
import grp
import codecs
import imp
protocol=imp.load_source('protocol','../protocol.py')
# 	[Key] string UserName;
# 	[write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
# 	[write] string FullName;
# 	[write] string Description;
# 	[write] string Password;
# 	[write] boolean Disabled;
# 	[write] boolean PasswordChangeRequired;
# 	[write] string HomeDirectory;
# 	[write] string GroupID;

global show_mof
show_mof=False

def Set_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if UserName != None :
        UserName=UserName.decode("utf-8")
    else:
        UserName = ''
    if Ensure != None :
        Ensure=Ensure.decode("utf-8")
    else:
        Ensure = ''
    if FullName != None :
        FullName=FullName.decode("utf-8")
    else:
        FullName = ''
    if Description != None :
        Description=Description.decode("utf-8")
    else:
        Description = ''
    if Password != None :
        Password=Password.decode("utf-8")
    else:
        Password = ''
    if Disabled == None :
        Disabled = False
    if PasswordChangeRequired == None :
        PasswordChangeRequired = False
    if HomeDirectory != None :
        HomeDirectory=HomeDirectory.decode("utf-8")
    else:
        HomeDirectory = ''
    if GroupID != None :
        GroupID=GroupID.decode("utf-8")
    else:
        GroupID = ''

    retval = Set(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    return retval

def Test_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if UserName != None :
        UserName=UserName.decode("utf-8")
    else:
        UserName = ''
    if Ensure != None :
        Ensure=Ensure.decode("utf-8")
    else:
        Ensure = ''
    if FullName != None :
        FullName=FullName.decode("utf-8")
    else:
        FullName = ''
    if Description != None :
        Description=Description.decode("utf-8")
    else:
        Description = ''
    if Password != None :
        Password=Password.decode("utf-8")
    else:
        Password = ''
    if Disabled == None :
        Disabled = False
    if PasswordChangeRequired == None :
        PasswordChangeRequired = False
    if HomeDirectory != None :
        HomeDirectory=HomeDirectory.decode("utf-8")
    else:
        HomeDirectory = ''
    if GroupID != None :
        GroupID=GroupID.decode("utf-8")
    else:
        GroupID = ''
    
    retval = Test(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    return retval

def Get_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    arg_names=list(locals().keys())
    if UserName != None :
        UserName=UserName.decode("utf-8")
    else:
        UserName = ''
    if Ensure != None :
        Ensure=Ensure.decode("utf-8")
    else:
        Ensure = ''
    if FullName != None :
        FullName=FullName.decode("utf-8")
    else:
        FullName = ''
    if Description != None :
        Description=Description.decode("utf-8")
    else:
        Description = ''
    if Password != None :
        Password=Password.decode("utf-8")
    else:
        Password = ''
    if Disabled == None :
        Disabled = False
    if PasswordChangeRequired == None :
        PasswordChangeRequired = False
    if HomeDirectory != None :
        HomeDirectory=HomeDirectory.decode("utf-8")
    else:
        HomeDirectory = ''
    if GroupID != None :
        GroupID=GroupID.decode("utf-8")
    else:
        GroupID = ''

    retval = 0
    (retval, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID) = Get(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)

    UserName = protocol.MI_String( UserName.encode("utf-8"))
    Ensure = protocol.MI_String( Ensure.encode("utf-8"))
    FullName = protocol.MI_String( FullName.encode("utf-8"))
    PasswordChangeRequired = protocol.MI_Boolean(PasswordChangeRequired)
    Disabled = protocol.MI_Boolean(Disabled)
    Description = protocol.MI_String( Description.encode("utf-8"))
    Password = protocol.MI_String( Password.encode("utf-8"))
    HomeDirectory = protocol.MI_String( HomeDirectory.encode("utf-8"))
    GroupID = protocol.MI_String( GroupID.encode("utf-8"))


    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k] 
    return retval, retd


############################################################
### Begin user defined DSC functions
############################################################

class Params:
    def __init__(self,UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
        self.UserName = UserName
        self.Ensure = Ensure
        self.FullName = FullName
        self.Description = Description
        self.Password = Password
        self.Disabled = Disabled
        self.PasswordChangeRequired = PasswordChangeRequired
        self.HomeDirectory = HomeDirectory
        self.GroupID = GroupID


def SetShowMof(a):
    global show_mof
    show_mof=a

def ShowMof(op, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    if not show_mof:
        return
    mof=''
    mof+= op + ' nxUser MyUser \n'
    mof+='{\n'
    mof+='    UserName = "' + UserName + '"\n'
    mof+='    Ensure = "' + Ensure + '"\n'
    mof+='    FullName = "' + FullName + '"\n'
    mof+='    Description = "' + Description + '"\n'
    mof+='    Password = "' + Password + '"\n'
    mof+='    Disabled = ' + str(Disabled) + '\n'
    mof+='    PasswordChangeRequired = ' + str(PasswordChangeRequired) + '\n'
    mof+='    HomeDirectory = "' + HomeDirectory + '"\n'
    mof+='    GroupID = "' + str(GroupID) + '"\n'
    mof+='}\n'
    f=open('./test_mofs.log','a')
    Print(mof,file=f)
    f.close()
    
def Print(s,file=sys.stdout):
    file.write(s+'\n')
    
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
    f,error = opened_w_error(filename,'rb')
    if error:
        Print("Exception opening file " + filename + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr )
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
    # No entries for the "last" or "must" fields means Password is Expired
    if shadow_entry[1] == "" or shadow_entry[3] == "":
        return True

    # Passwords must be changed if their "last" day is 0
    if shadow_entry[1] == "0":
        return True

    # "99999" means "never expire"
    if shadow_entry[3] == "99999":
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
    ShowMof('SET', UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    p=Params(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    passwd_entries = None
    shadow_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries == None:
        return [-1]
    shadow_entries = ReadPasswd("/etc/shadow")
    if shadow_entries == None:
        return [-1]

    usermod_string = ""
    usermodonly_string = ""

    if Ensure.lower() == "absent":
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

        disabled_user_string = ""
        if Disabled == True:
            disabled_user_string = "!"

        if len(Password)>0:
            usermod_string += " -p \"" + disabled_user_string + Password.replace("$", "\$") + "\""
        elif Disabled == True:
            usermodonly_string += " -L"
        elif Disabled == False:
            if UserName in shadow_entries:
                cur_pass = shadow_entries[UserName][0]
                if cur_pass == "!!":
                    Print("Unable to unlock user: " + UserName + ".  Password is not set.",file=sys.stderr)
                    return [-1]
                elif cur_pass[0] == '!':
                    if len(cur_pass) > 1:
                        usermodonly_string += " -U"
                    else:
                        Print("Unable to unlock user: " + UserName + ".  Doing so would result in a passwordless account.",file=sys.stderr)
                        return [-1]
            
        if HomeDirectory:
            usermod_string += " -m -d \"" + HomeDirectory + "\""

        if GroupID:
            usermod_string += " -g " + GroupID

        if UserName not in passwd_entries:
            exit_code = os.system(useradd_path + " " + usermod_string + " " + UserName)
            if exit_code != 0:
                return [exit_code]

            if len(usermodonly_string) > 0:
                exit_code = os.system(usermod_path + " " + usermodonly_string + " " + UserName)
                if exit_code != 0:
                    return [exit_code]
        else:
            Print(usermod_string,file=sys.stderr)
            if len(usermodonly_string + usermod_string) > 0:
                exit_code = os.system(usermod_path + " " + usermodonly_string + usermod_string + " " + UserName)
                if exit_code != 0:
                    return [exit_code]


        if PasswordChangeRequired == True:
            # Set last password change to today
            day_0 = datetime.datetime.utcfromtimestamp(0)
            day_now = datetime.datetime.today()
            days_since_day_0 = (day_now - day_0).days
            
            exit_code = os.system(chage_path + " -d "+ str(days_since_day_0) + " " + UserName)
           
    return [exit_code]

def Test(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    ShowMof('TEST', UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    p=Params(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)

    passwd_entries = None
    shadow_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries == None:
        return [-1]
    shadow_entries = ReadPasswd("/etc/shadow")
    if shadow_entries == None:
        return [-1]

    if not Ensure:
        Ensure = "Present"

    if Ensure.lower() == "absent":
        if UserName not in passwd_entries:
            return [0]
        else:
            Print(UserName + " in passwd_entries",file=sys.stderr)
            return [-1]
    elif Ensure.lower() == "present":
        if UserName not in passwd_entries:
            Print(UserName + " not in passwd_entries",file=sys.stderr)
            return [-1]
        if UserName not in shadow_entries:
            Print(UserName + " not in shadow_entries",file=sys.stderr)
            return [-1]

        if len(passwd_entries[UserName]) < 6:
            Print("Unable to read /etc/passwd entry for username: " + UserName,file=sys.stderr)
            return [-1]
        if len(shadow_entries[UserName]) < 8:
            Print("Unable to read /etc/shadow entry for username: " + UserName,file=sys.stderr)
            return [-1]

        extra_fields = passwd_entries[UserName][3].split(",")

        if FullName and extra_fields[0] != FullName:
            Print("Incorrect full name (" + extra_fields[0] + "), should be: " + FullName + ", for username: " + UserName,file=sys.stderr)
            return [-1]

        if Description:
            if len(extra_fields) < 2:
                Print("There is no description.",file=sys.stderr)
                return [-1]
            elif extra_fields[1] != Description:
                Print("Incorrect description for username: " + UserName,file=sys.stderr)
                return [-1]

        if HomeDirectory and passwd_entries[UserName][4] != HomeDirectory:
            Print("Home directories do not match",file=sys.stderr)
            return [-1]
    
        if GroupID and passwd_entries[UserName][2] != GroupID:
            Print("GroupID does not match",file=sys.stderr)
            return [-1]

        if len(Password)>0:
            read_password = shadow_entries[UserName][0]
            if len(read_password) == 0:
                Print("Password does not match",file=sys.stderr)
                return [-1]
            if read_password[0] == "!":
                read_password = read_password[1:]
            if read_password != Password:
                Print("Password does not match",file=sys.stderr)
                return [-1]

        if PasswordChangeRequired == True and not PasswordExpired(shadow_entries[UserName]):
            Print("PasswordChangeRequired is True and the password is not expired.",file=sys.stderr)
            return [-1]
        elif PasswordChangeRequired == False and PasswordExpired(shadow_entries[UserName]):
            Print("PasswordChangeRequired is False and the password is expired.",file=sys.stderr)
            return [-1]
            
        if Disabled == True and shadow_entries[UserName][0][0] != "!":
            Print("Account not disabled",file=sys.stderr)
            return [-1]
        if Disabled == False and shadow_entries[UserName][0][0] == "!":
            Print("Account disabled",file=sys.stderr)
            return [-1]

    return [0]

def Get(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    ShowMof('GET', UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    p=Params(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    passwd_entries = None
    shadow_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries == None:
        return [-1, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID]
    shadow_entries = ReadPasswd("/etc/shadow")
    if shadow_entries == None:
        return [-1, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID]

    exit_code = 0

    if UserName not in passwd_entries:
        FullName = Description = Password = HomeDirectory = GroupID = ""
        if Ensure != "Absent":
            exit_code = -1
        return [exit_code, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID]
        
    extra_fields = passwd_entries[UserName][3].split(",")
    FullName = extra_fields[0]
    if len(extra_fields) > 1:
        Description = extra_fields[1]

    HomeDirectory = passwd_entries[UserName][4]
    GroupID = passwd_entries[UserName][2]
    
    Password = shadow_entries[UserName][0]
    Disabled = False
    if len(Password) > 0:
        if Password[0] == "!":
            Disabled = True
            Password = Password[1:]
    if PasswordExpired(shadow_entries[UserName]):
        PasswordChangeRequired = True
    else:
        PasswordChangeRequired = False

    return [exit_code, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID]

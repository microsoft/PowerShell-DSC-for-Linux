import subprocess
import shutil
import pwd
import grp
import os
import stat
import time
import datetime

def Set_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    UserName = UserName.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    FullName = FullName.decode("utf-8")
    Description = Description.decode("utf-8")
    Password = Password.decode("utf-8")
    Disabled = Disabled.decode("utf-8")
    PasswordChangeRequired = PasswordChangeRequired.decode("utf-8")
    HomeDirectory = HomeDirectory.decode("utf-8")
    GroupID = GroupID.decode("utf-8")

    retval = Set(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    return retval

def Test_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    UserName = UserName.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    FullName = FullName.decode("utf-8")
    Description = Description.decode("utf-8")
    Password = Password.decode("utf-8")
    Disabled = Disabled.decode("utf-8")
    PasswordChangeRequired = PasswordChangeRequired.decode("utf-8")
    HomeDirectory = HomeDirectory.decode("utf-8")
    GroupID = GroupID.decode("utf-8")
    
    retval = Test(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)
    return retval

def Get_Marshall(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    UserName = UserName.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    FullName = FullName.decode("utf-8")
    Description = Description.decode("utf-8")
    Password = Password.decode("utf-8")
    Disabled = Disabled.decode("utf-8")
    PasswordChangeRequired = PasswordChangeRequired.decode("utf-8")
    HomeDirectory = HomeDirectory.decode("utf-8")
    GroupID = GroupID.decode("utf-8")

    retval = 0
    (retval, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID) = Get(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID)

    UserName = UserName.encode("utf-8")
    Ensure = Ensure.encode("utf-8")
    FullName = FullName.encode("utf-8")
    Description = Description.encode("utf-8")
    Password = Password.encode("utf-8")
    Disabled = Disabled.encode("utf-8")
    PasswordChangeRequired = PasswordChangeRequired.encode("utf-8")
    HomeDirectory = HomeDirectory.encode("utf-8")
    GroupID = GroupID.encode("utf-8")

    return [retval, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID]


############################################################
### Begin user defined DSC functions
############################################################
def ReadPasswd(filename):
    f = open(filename, "r")
    lines = f.read().split("\n")
    
    entries = dict()
    for line in lines:
        tokens = line.split(":")
#        print(tokens)
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
    passwd_entries = ReadPasswd("/etc/passwd")
    shadow_entries = ReadPasswd("/etc/shadow")

    usermod_string = ""
    usermodonly_string = ""

    if Ensure == "Absent":
        exit_code = os.system("/usr/sbin/userdel " + UserName)
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
        if Disabled == "True":
            disabled_user_string = "!"

        if Password:
            usermod_string += " -p \"" + disabled_user_string + Password + "\""
        elif Disabled:
            if Disabled == "True":
                usermodonly_string += " -L"
            elif Disabled == "False":
                cur_pass = shadow_entries[UserName][0]
                if cur_pass == "!!":
                    print("Unable to unlock user: " + UserName + ".  Password is not set.")
                    return [-1]
                elif cur_pass[0] == '!':
                    if len(cur_pass) > 1:
                        usermodonly_string += " -U"
                    else:
                        print("Unable to unlock user: " + UserName + ".  Doing so would result in a passwordless account.")
                        return [-1]
            
        if HomeDirectory:
            usermod_string += " -m -d \"" + HomeDirectory + "\""

        if GroupID:
            usermod_string += " -g " + GroupID

        if UserName not in passwd_entries:
            exit_code = os.system("/usr/sbin/useradd " + usermod_string + " " + UserName)
            if exit_code != 0:
                return [exit_code]

            if len(usermodonly_string) > 0:
                exit_code = os.system("/usr/sbin/usermod " + usermodonly_string + " " + UserName)
            if exit_code != 0:
                return [exit_code]
        else:
            print(usermod_string)
            exit_code = os.system("/usr/sbin/usermod " + usermodonly_string + usermod_string + " " + UserName)
            if exit_code != 0:
                return [exit_code]


        if PasswordChangeRequired:
            if PasswordChangeRequired == "True":
                exit_code = os.system("/usr/bin/chage -d 0 " + UserName)
            else:
                # Set last password change to today
                day_0 = datetime.datetime.utcfromtimestamp(0)
                day_now = datetime.datetime.today()
                days_since_day_0 = (day_now - day_0).days

                exit_code = os.system("/usr/bin/chage -d "+ str(days_since_day_0) + " " + UserName)
           
    return [exit_code]

def Test(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    passwd_entries = ReadPasswd("/etc/passwd")
    shadow_entries = ReadPasswd("/etc/shadow")

    if not Ensure:
        Ensure = "Present"

    if Ensure == "Absent":
        if UserName not in passwd_entries:
            return [0]
        else:
            print(UserName + " in passwd_entries")
            return [-1]
    elif Ensure == "Present":
        if UserName not in passwd_entries:
            print(UserName + " not in passwd_entries")
            return [-1]
        if UserName not in shadow_entries:
            print(UserName + " not in shadow_entries")
            return [-1]

        if len(passwd_entries[UserName]) < 6:
            print("Unable to read /etc/passwd entry for username: " + UserName)
            return [-1]
        if len(shadow_entries[UserName]) < 8:
            print("Unable to read /etc/shadow entry for username: " + UserName)
            return [-1]

        extra_fields = passwd_entries[UserName][3].split(",")

        if FullName and extra_fields[0] != FullName:
            print("Incorrect full name (" + extra_fields[0] + "), should be: " + FullName + ", for username: " + UserName)
            return [-1]

        if Description:
            if len(extra_fields) < 2:
                print("There is no description.")
                return [-1]
            elif extra_fields[1] != Description:
                print("Incorrect description for username: " + UserName)
                return [-1]

        if HomeDirectory and passwd_entries[UserName][4] != HomeDirectory:
            print("Home directories do not match")
            return [-1]
    
        if GroupID and passwd_entries[UserName][2] != GroupID:
            print("GroupID does not match")
            return [-1]

        if Password and shadow_entries[UserName][0] != Password:
            print("Password does not match")
            return [-1]

        if PasswordChangeRequired:
            if PasswordChangeRequired == "True" and not PasswordExpired(shadow_entries[UserName]):
                print("PasswordChangeRequired is True and the password is not expired.")
                return [-1]
            elif PasswordChangeRequired == "False" and PasswordExpired(shadow_entries[UserName]):
                print("PasswordChangeRequired is False and the password is expired.")
                return [-1]
            
        if Disabled:
            if Disabled == "True" and shadow_entries[UserName][0][0] != "!":
                print("Account not disabled")
                return [-1]
            if Disabled == "False" and shadow_entries[UserName][0][0] == "!":
                print("Account disabled")
                return [-1]

    return [0]

def Get(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    passwd_entries = ReadPasswd("/etc/passwd")
    shadow_entries = ReadPasswd("/etc/shadow")
    exit_code = 0

    if UserName not in passwd_entries:
        FullName = Description = Password = Disabled = PasswordChangeRequired = HomeDirectory = GroupID = ""
        if Ensure == "Present":
            Ensure = "Absent"
    else:
        Ensure = "Present"
        
        extra_fields = passwd_entries[UserName][3].split(",")
        FullName = extra_fields[0]
        if len(extra_fields) > 1:
            Description = extra_fields[1]

        HomeDirectory = passwd_entries[UserName][4]
        GroupID = passwd_entries[UserName][2]
        
        Password = shadow_entries[UserName][0]
        Disabled = "False"
        if len(Password) > 0:
            if Password[0] == "!":
                Disabled = "True"
        if PasswordExpired(shadow_entries[UserName]):
            PasswordChangeRequired = "True"
        else:
            PasswordChangeRequired = "False"

    return [exit_code, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID]


#def UnitTests():
#    print(Get("testuser", "Present", "Test User", "TEST DESCRIPTION", "", "True", "False", "/home/testhome", "3482"))
#    print(Test("testuser", "Present", "Test User", "TEST DESCRIPTION", "", "True", "False", "/home/testhome", "3482"))
#    print(Set("testuser", "Present", "Test User", "TEST DESCRIPTION", "", "True", "False", "/home/testhome", "3482"))
#    print(Test("testuser", "Present", "Test User", "TEST DESCRIPTION", "", "True", "False", "/home/testhome", "3482"))
#    print(Get("testuser", "Present", "Test User", "TEST DESCRIPTION", "", "True", "False", "/home/testhome", "3482"))

#UnitTests()

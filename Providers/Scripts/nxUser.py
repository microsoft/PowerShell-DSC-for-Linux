#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
from __future__ import print_function
from __future__ import with_statement
from contextlib import contextmanager

import os
import sys
import datetime
import grp
import codecs

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
@contextmanager
def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, encoding='utf-8' , mode=mode)
    except IOError, err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()

userdel_path = "/usr/sbin/userdel"
useradd_path = "/usr/sbin/useradd"
usermod_path = "/usr/sbin/usermod"
chage_path = "/usr/bin/chage"

def ReadPasswd(filename):
    with opened_w_error(filename,'rb') as (f,error):
        if error:
            print("Exception opening file " + filename + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr )
            return None
        else:
            lines = f.read().split("\n")
    
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
        if Disabled == "True":
            disabled_user_string = "!"

        if Password:
            usermod_string += " -p \"" + disabled_user_string + Password.replace("$", "\$") + "\""
        elif Disabled:
            if Disabled == "True":
                usermodonly_string += " -L"
            elif Disabled == "False":
                cur_pass = shadow_entries[UserName][0]
                if cur_pass == "!!":
                    print("Unable to unlock user: " + UserName + ".  Password is not set.",file=sys.stderr)
                    return [-1]
                elif cur_pass[0] == '!':
                    if len(cur_pass) > 1:
                        usermodonly_string += " -U"
                    else:
                        print("Unable to unlock user: " + UserName + ".  Doing so would result in a passwordless account.",file=sys.stderr)
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
            print(usermod_string,file=sys.stderr)
            if len(usermodonly_string + usermod_string) > 0:
                exit_code = os.system(usermod_path + " " + usermodonly_string + usermod_string + " " + UserName)
                if exit_code != 0:
                    return [exit_code]


        if PasswordChangeRequired:
            if PasswordChangeRequired == "True":
                exit_code = os.system(chage_path + " -d 0 " + UserName)
            else:
                # Set last password change to today
                day_0 = datetime.datetime.utcfromtimestamp(0)
                day_now = datetime.datetime.today()
                days_since_day_0 = (day_now - day_0).days

                exit_code = os.system(chage_path + " -d "+ str(days_since_day_0) + " " + UserName)
           
    return [exit_code]

def Test(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):

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
            print(UserName + " in passwd_entries",file=sys.stderr)
            return [-1]
    elif Ensure.lower() == "present":
        if UserName not in passwd_entries:
            print(UserName + " not in passwd_entries",file=sys.stderr)
            return [-1]
        if UserName not in shadow_entries:
            print(UserName + " not in shadow_entries",file=sys.stderr)
            return [-1]

        if len(passwd_entries[UserName]) < 6:
            print("Unable to read /etc/passwd entry for username: " + UserName,file=sys.stderr)
            return [-1]
        if len(shadow_entries[UserName]) < 8:
            print("Unable to read /etc/shadow entry for username: " + UserName,file=sys.stderr)
            return [-1]

        extra_fields = passwd_entries[UserName][3].split(",")

        if FullName and extra_fields[0] != FullName:
            print("Incorrect full name (" + extra_fields[0] + "), should be: " + FullName + ", for username: " + UserName,file=sys.stderr)
            return [-1]

        if Description:
            if len(extra_fields) < 2:
                print("There is no description.",file=sys.stderr)
                return [-1]
            elif extra_fields[1] != Description:
                print("Incorrect description for username: " + UserName,file=sys.stderr)
                return [-1]

        if HomeDirectory and passwd_entries[UserName][4] != HomeDirectory:
            print("Home directories do not match",file=sys.stderr)
            return [-1]
    
        if GroupID and passwd_entries[UserName][2] != GroupID:
            print("GroupID does not match",file=sys.stderr)
            return [-1]

        if Password:
            read_password = shadow_entries[UserName][0]
            if len(read_password) == 0:
                print("Password does not match",file=sys.stderr)
                return [-1]
            if read_password[0] == "!":
                read_password = read_password[1:]
            if read_password != Password:
                print("Password does not match",file=sys.stderr)
                return [-1]

        if PasswordChangeRequired:
            if PasswordChangeRequired == "True" and not PasswordExpired(shadow_entries[UserName]):
                print("PasswordChangeRequired is True and the password is not expired.",file=sys.stderr)
                return [-1]
            elif PasswordChangeRequired == "False" and PasswordExpired(shadow_entries[UserName]):
                print("PasswordChangeRequired is False and the password is expired.",file=sys.stderr)
                return [-1]
            
        if Disabled:
            if Disabled == "True" and shadow_entries[UserName][0][0] != "!":
                print("Account not disabled",file=sys.stderr)
                return [-1]
            if Disabled == "False" and shadow_entries[UserName][0][0] == "!":
                print("Account disabled",file=sys.stderr)
                return [-1]

    return [0]

def Get(UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID):
    passwd_entries = None
    shadow_entries = None
    passwd_entries = ReadPasswd("/etc/passwd")
    if passwd_entries == None:
        return [-1]
    shadow_entries = ReadPasswd("/etc/shadow")
    if shadow_entries == None:
        return [-1]

    exit_code = 0

    if UserName not in passwd_entries:
        FullName = Description = Password = Disabled = PasswordChangeRequired = HomeDirectory = GroupID = ""
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
                Password = Password[1:]
        if PasswordExpired(shadow_entries[UserName]):
            PasswordChangeRequired = "True"
        else:
            PasswordChangeRequired = "False"

    return [exit_code, UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID]

import unittest,time

class LinuxUserTestCases(unittest.TestCase):
    """
    Test cases for LinuxFile
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('userdel -r jojoma &> /dev/null')
        time.sleep(1)
        
    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('userdel -r jojoma &> /dev/null')
        time.sleep(1)

    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass

    def pswd_hash(self,pswd):
        import subprocess,hashlib,base64
        salt=(subprocess.Popen("openssl rand -base64 3", shell=True, bufsize=100, stdout=subprocess.PIPE).stdout).readline().rstrip()
        m = hashlib.sha1()
        m.update(pswd+salt)
        return base64.b64encode(m.digest()+salt)
    
    def testSetUserAbsentError(self):
        assert Set("jojoma", "Absent", "", "", "", "", "", "", "" )!=[0],'Set("jojoma", "Absent", "", "", "", "", "", "", "" ) should return !=[0]'

    def testSetUserPresent(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==    \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'

    def testGetUserAbsent(self):
        assert Get("jojoma", "", "", "", "", "", "", "", "" )[:3]== \
               [0,"jojoma","Absent"],'Get("jojoma", "", "", "", "", "", "", "", "" )[:3] should return ==[0,"jojoma","Absent"]'

    def testGetUserPresent(self):
        """
        Note - GroupID is currently returned as the string representation of a number, eg - '27'
        """
        pswd=self.pswd_hash('jojoma')
        grpid=str(grp.getgrnam('mail')[2])
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Get("jojoma", "", "", "", "", "", "", "", "" )== \
               [0,"jojoma","Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma",grpid], \
               'Get("jojoma", "", "", "", "", "", "", "", "" )[:3] should return ==[0,"jojoma","Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail"]'

    def testTestUserAbsent(self):
        assert Test("jojoma", "Absent", "", "", "", "", "", "", "" ) == [0],'Test("jojoma", "Absent", "", "", "", "", "", "", "" ) should return ==[0]'

    def testTestUserAbsentError(self):
        assert Test("root", "Absent", "", "", "", "", "", "", "" )== \
               [-1],'Test("root", "", "", "", "", "", "", "", "" ) should return ==[-1]'

    def testTestUserPresent(self):
        assert Test("root", "Present", "", "", "", "", "", "", "" )== \
               [0],'Test("root", "Present", "", "", "", "", "", "", "" ) should return ==[0]'

    def testTestUserPresentError(self):
        assert Test("jojoma", "Present", "", "", "", "", "", "", "" )== \
               [-1],'Test("jojoma", "Present", "", "", "", "", "", "", "" ) should return ==[-1]'

    def testTestUserFullName(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "JO JO MA", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "JO JO MA", "", "", "", "", "", "" )== \
               [0],'Test("jojoma", "Present", "JO JO MA", "", "", "", "", "", "" ) should return ==[0]'

    def testTestUserDescription(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "", "JOJOMA", "", "", "", "", "" )== \
               [0],'Test("jojoma", "Present", "", "JOJOMA", "", "", "", "", "" ) should return ==[0]'

    def testTestUserHomeDirectory(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "", "", "", "False", "False", "/home/jojoma", "" )== \
               [0],'Test("jojoma", "Present", "", "", "", "False", "False", "/home/jojoma", "" ) should return ==[0]'

    def testTestUserGroupID(self):
        pswd=self.pswd_hash('jojoma')
        grpid=str(grp.getgrnam('mail')[2])
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "", "", "", "", "", "", grpid )== \
               [0],'Test("jojoma", "Present", "", "", "", "", "", "", "'+ grpid+ '" ) should return ==[0]'

    def testTestUserPassword(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "", "", "", pswd, "", "", "" )== \
               [0],'Test("jojoma", "Present", "", "", "", '+pswd+', "", "", "" ) should return ==[0]'

    def testTestUserFullNameError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "JO JO MA", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "JO JO MAMA", "", "", "", "", "", "" )== \
               [-1],'Test("jojoma", "Present", "JO JO MAMA", "", "", "", "", "", "" ) should return ==[-1]'

    def testTestUserDescriptionError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "", "NOTJOJOMA", "", "", "", "", "" )== \
               [-1],'Test("jojoma", "Present", "", "NOTJOJOMA", "", "", "", "", "" ) should return ==[-1]'

    def testTestUserHomeDirectoryError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "", "", "", "", "", "/home/ojoma", "" )== \
               [-1],'Test("jojoma", "Present", "", "", "", "", "", "/home/ojoma", "" ) should return ==[-1]'

    def testTestUserGroupIDError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        assert Test("jojoma", "Present", "", "", "", "", "", "", 1200 )== \
               [-1],'Test("jojoma", "Present", "", "", "", "", "", "", 1200 ) should return ==[-1]'

    def testTestUserPasswordError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==           \
               [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]'
        pswd=self.pswd_hash('jojomama')
        assert Test("jojoma", "Present", "", "", pswd , "", "", "", "" )== \
               [-1],'Test("jojoma", "Present", "", "", "'+pswd+'", "", "", "", "" ) should return ==[-1]'

    def testSetUserDisabled(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" )==  \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "True", "False", "/home/jojoma", "" ) should return == [0]'
        assert Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" )== \
               [0],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" ) should return ==[0]'


    def testSetUserDisabledError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "" )==  \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "" ) should return == [0]'
        assert Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" )== \
               [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" ) should return ==[-1]'

    def testSetUserExpired(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )==  \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "True", "/home/jojoma", "" ) should return == [0]'
        assert Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )== \
               [0],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" ) should return ==[0]'


    def testSetUserExpiredError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "" )==  \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "" ) should return == [0]'
        assert Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )== \
               [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" ) should return ==[-1]'

    def testSetUserNotExpiredError(self):
        pswd=self.pswd_hash('jojoma')
        assert Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )==  \
               [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "True", "/home/jojoma", "" ) should return == [0]'
        assert Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "" )==  \
               [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "" ) should return == [-1]'





if __name__ == '__main__':
    s=unittest.TestLoader().loadTestsFromTestCase(LinuxUserTestCases)
    unittest.TextTestRunner(verbosity=2).run(s)



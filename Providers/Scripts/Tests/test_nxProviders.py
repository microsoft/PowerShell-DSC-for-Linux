#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
from __future__ import print_function




import time
import os
import sys
import hashlib
import grp
import imp
import subprocess
import base64
import platform
import pwd

os.system('tar -zxvf ./unittest2-0.5.1.tar.gz ')
sys.path.append('.:'+os.path.realpath('./Scripts'))
import unittest2

nxUser=imp.load_source('nxUser','../nxUser.py') 
nxGroup=imp.load_source('nxGroup','../nxGroup.py') 
nxFile=imp.load_source('nxFile','../nxFile.py') 
nxScript=imp.load_source('nxScript','../nxScript.py') 
nxService=imp.load_source('nxService','../nxService.py') 
nxPackage=imp.load_source('nxPackage','../nxPackage.py') 
nxSshAuthorizedKeys=imp.load_source('nxSshAuthorizedKeys','../nxSshAuthorizedKeys.py')
nxEnvironment=imp.load_source('nxEnvironment','../nxEnvironment.py')

class LinuxUserTestCases(unittest2.TestCase):
    """
    Test cases for nxUser.py
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
        salt=(subprocess.Popen("openssl rand -base64 3", shell=True, bufsize=100, stdout=subprocess.PIPE).stdout).readline().rstrip()
        m = hashlib.sha1()
        m.update(pswd+salt)
        return base64.b64encode(m.digest()+salt)
    
    def testSetUserAbsentError(self):
        self.assertTrue(nxUser.Set("jojoma", "Absent", "", "", "", "", "", "", "" )!=
                        [0],'Set("jojoma", "Absent", "", "", "", "", "", "", "" ) should return !=[0]')

    def testSetUserPresent(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')

    def testGetUserAbsent(self):
        assert nxUser.Get("jojoma", "", "", "", "", "", "", "", "" )[:3]== \
               [0,"jojoma","Absent"],'Get("jojoma", "", "", "", "", "", "", "", "" )[:3] should return ==[0,"jojoma","Absent"]'

    def testGetUserPresent(self):
        """
        Note - GroupID is currently returned as the string representation of a number, eg - '27'
        """
        pswd=self.pswd_hash('jojoma')
        grpid=str(grp.getgrnam('mail')[2])
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Get("jojoma", "", "", "", "", "", "", "", "" )==[0,"jojoma","Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma",grpid],
                        'Get("jojoma", "", "", "", "", "", "", "", "" )[:3] should return ==[0,"jojoma","Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail"]')

    def testTestUserAbsent(self):
        self.assertTrue(nxUser.Test("jojoma", "Absent", "", "", "", "", "", "", "" ) ==
                        [0],'Test("jojoma", "Absent", "", "", "", "", "", "", "" ) should return ==[0]')

    def testTestUserAbsentError(self):
        self.assertTrue(nxUser.Test("root", "Absent", "", "", "", "", "", "", "" )==
                        [-1],'Test("root", "", "", "", "", "", "", "", "" ) should return ==[-1]')
        
    def testTestUserPresent(self):
        self.assertTrue(nxUser.Test("root", "Present", "", "", "", "", "", "", "" )==
                        [0],'Test("root", "Present", "", "", "", "", "", "", "" ) should return ==[0]')

    def testTestUserPresentError(self):
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "", "", "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "", "", "", "", "", "", "" ) should return ==[-1]')

    def testTestUserFullName(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "JO JO MA", "", "", "", "", "", "" )==
                        [0],'Test("jojoma", "Present", "JO JO MA", "", "", "", "", "", "" ) should return ==[0]')

    def testTestUserDescription(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "JOJOMA", "", "", "", "", "" )==
                        [0],'Test("jojoma", "Present", "", "JOJOMA", "", "", "", "", "" ) should return ==[0]')

    def testTestUserHomeDirectory(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "", "", "False", "False", "/home/jojoma", "" )==
                        [0],'Test("jojoma", "Present", "", "", "", "False", "False", "/home/jojoma", "" ) should return ==[0]')

    def testTestUserGroupID(self):
        pswd=self.pswd_hash('jojoma')
        grpid=str(grp.getgrnam('mail')[2])
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "", "", "", "", "", grpid )==
                        [0],'Test("jojoma", "Present", "", "", "", "", "", "", "'+ grpid+ '" ) should return ==[0]')
        
    def testTestUserPassword(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "", "", pswd, "", "", "" )==
                        [0],'Test("jojoma", "Present", "", "", "", '+pswd+', "", "", "" ) should return ==[0]')

    def testTestUserFullNameError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "JO JO MAMA", "", "", "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "JO JO MAMA", "", "", "", "", "", "" ) should return ==[-1]')

    def testTestUserDescriptionError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "", "JOJOMA", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "NOTJOJOMA", "", "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "", "NOTJOJOMA", "", "", "", "", "" ) should return ==[-1]')

    def testTestUserHomeDirectoryError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "", "", "", "", "/home/ojoma", "" )==
                        [-1],'Test("jojoma", "Present", "", "", "", "", "", "/home/ojoma", "" ) should return ==[-1]')

    def testTestUserGroupIDError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "", "", "", "", "", 1200 )==
                        [-1],'Test("jojoma", "Present", "", "", "", "", "", "", 1200 ) should return ==[-1]')

    def testTestUserPasswordError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "", "", pswd, "False", "False", "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', "False", "False", "/home/jojoma", "mail" ) should return == [0]')
        pswd=self.pswd_hash('jojomama')
        self.assertTrue(nxUser.Test("jojoma", "Present", "", "", pswd , "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "", "", "'+pswd+'", "", "", "", "" ) should return ==[-1]')

    def testSetUserDisabled(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "True", "False", "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" )==
                        [0],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" ) should return ==[0]')
        

    def testSetUserDisabledError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" )==
                        [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "True", "False", "/home/jojoma", "" ) should return ==[-1]')

    def testSetUserExpired(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "True", "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )==
                        [0],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" ) should return ==[0]')


    def testSetUserExpiredError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )==
                        [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" ) should return ==[-1]')

    def testSetUserNotExpiredError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "True", "/home/jojoma", "" )==
 [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "True", "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, "False", "False", "/home/jojoma", "" )==
 [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', "False", "False", "/home/jojoma", "" ) should return == [-1]')

class LinuxGroupTestCases(unittest2.TestCase):
    """
    Test cases for nxGroup.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('groupdel jojomamas &> /dev/null')
        os.system('useradd -m jojoma &> /dev/null')
        time.sleep(1)
        
    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('userdel -r jojoma &> /dev/null')
        os.system('groupdel jojomamas &> /dev/null')
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

    # Set(GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID)
    
    def testSetGroupPresent(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", ["jojoma"], "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", ["jojoma"], "", "", 1101 ) should return == [0]')

    def testSetGroupAbsent(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", ["jojoma"], "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", ["jojoma"], "", "", 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Set("jojomamas", "Absent", ["jojoma"], "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Absent", ["jojoma"], "", "", 1101 ) should return == [0]')

    def testGetGroupAbsent(self):
        self.assertTrue(nxGroup.Get("jojomamas", "", "", "", "", "")[:3]==
                        [0,"jojomamas","Absent"],'Get("jojomamas", "", "", "", "", "")[:3] should return ==[0,"jojomamas","Absent"]')

    def testGetGroupPresent(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", ["jojoma"], "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", ["jojoma"], "", "", 1101 ) should return == [0]')
        print('GET='+repr(nxGroup.Get("jojomamas", "", "", "", "", "")[:6]))
        self.assertTrue(nxGroup.Get("jojomamas", "", "", "", "", "")[:6]==
                        [0,"jojomamas","Present", ['jojoma'], "", ""],                'Get("jojomamas", "", "", "", "", "")[:6] should return ==[0,"jojomamas","Present", "", "", ""]')

    def testTestGroupAbsent(self):
        self.assertTrue(nxGroup.Test("jojomamas", "Absent", "", "", "", "") ==
                        [0],'Test("jojomamas", "Absent", "", "", "", "") should return ==[0]')

    def testTestGroupAbsentError(self):
        self.assertTrue(nxGroup.Test("mail", "Absent", "", "", "", "")==
                        [-1],'Test("mail", "Absent", "", "", "", "") should return ==[-1]')

    def testTestGroupPresent(self):
        self.assertTrue(nxGroup.Test("mail", "Present", "", "", "", "")==
                        [0],'Test("mail", "Present", "", "", "", "") should return ==[0]')

    def testTestGroupPresentError(self):
        self.assertTrue(nxGroup.Test("jojomamas", "Present", "", "", "", "")==
                        [-1],'Test("jojomamas", "Present", "", "", "", "") should return ==[-1]')

    def testSetGroupPresentMembers(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", ("jojoma","root"), "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", ("jojoma","root"), "", "", 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Test("jojomamas", "Present", ("jojoma","root"), "", "", "")==
                        [0],'Test("jojomamas", "Present", ("jojoma","root"), "", "", "") should return ==[0]')

    def testSetGroupPresentMembersInclude(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", "", "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", "", "", "", 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Set("jojomamas", "Present", "", ["jojoma"], "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", "", ["jojoma"], "", 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Test("jojomamas", "Present", ["jojoma"], "", "", "")==
                        [0],'Test("jojomamas", "Present", ["jojoma"], "", "", "") should return ==[0]')

    def testSetGroupPresentMembersExclude(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", ("jojoma","root"), "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", ("jojoma","root"), "", "", 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Set("jojomamas", "Present", "", "", ["jojoma"], 1101 ) ==
                        [0],'Set("jojomamas", "Present", "", "", ("jojoma"), 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Test("jojomamas", "Present", ["root"], "", "", "")==
                        [0],'Test("jojomamas", "Present", "root", "", "", "") should return ==[0]')

    def testSetGroupPresentMembersIncludeError(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", "", "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", "", "", "", 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Set("jojomamas", "Present", "", ["ojoma"], "", 1101 ) ==
                        [-1],'Set("jojomamas", "Present", "", "ojoma", "", 1101 ) should return == [-1]')
        print("TEST="+repr(nxGroup.Test("jojomamas", "Present", ["ojoma"], "", "", "")))
        self.assertTrue(nxGroup.Test("jojomamas", "Present", ["ojoma"], "", "", "")==
                        [-1],'Test("jojomamas", "Present", ["ojoma"], "", "", "") should return ==[-1]')

    def testSetGroupPresentMembersExcludeError(self):
        self.assertTrue(nxGroup.Set("jojomamas", "Present", ["root"], "", "", 1101 ) ==
                        [0],'Set("jojomamas", "Present", ["root"], "", "", 1101 ) should return == [0]')
        self.assertTrue(nxGroup.Set("jojomamas", "Present", "", "", ["jojoma"], 1101 ) ==
                        [0],'Set("jojomamas", "Present", "", "", ["jojoma"], 1101 ) should return == [0]')
        print("TEST="+repr(nxGroup.Test("jojomamas", "Present", ["jojoma"], "", "", "")))
        self.assertTrue(nxGroup.Test("jojomamas", "Present", ["jojoma"], "", "", "")==
                        [-1],'Test("jojomamas", "Present", "root", "", "", "") should return ==[-1]')


class LinuxScriptTestCases(unittest2.TestCase):
    """
    Test cases for nxScript.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('useradd -m jojoma &> /dev/null')
        time.sleep(1)
        self.get_script='#!/bin/bash \ncd ~\nls -lart\n'
        self.test_script='#!/bin/bash \ncd ~\ntouch ./testfile\n'
        self.set_script='#!/bin/bash \ncd ~\necho "set script successfull" > ./testfile\n'
        self.get_script_loop='#!/bin/bash \ncd ~\nwhile true ; do ls -lart; sleep 5; done\n'

        
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

    def testGetScriptUser(self):
        r=nxScript.Get(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        print('GET='+repr(r))
        self.assertTrue(r[0] == 0,'nxScript.Get(self.get_script,self.set_script,self.test_script, "jojoma", "" )[0] should return == 0')

    def testTestScriptUser(self):
        r=nxScript.Test(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        print('TEST='+repr(r))
        self.assertTrue(r == [0],'nxScript.Test(self.get_script,self.set_script,self.test_script, "jojoma", "" )[0] should return == 0')

    def testSetScriptUser(self):
        r=nxScript.Set(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        print('SET='+repr(r))
        self.assertTrue(r[0] == 0,'nxScript.Set(self.get_script,self.set_script,self.test_script, "jojoma", "" )[0] should return == 0')

    def testGetScriptGroup(self):
        r=nxScript.Get(self.get_script,self.set_script,self.test_script, "", "mail" )
        print('GET='+repr(r))
        self.assertTrue(r[0] == 0,'nxScript.Get(self.get_script,self.set_script,self.test_script, "", "mail" )[0] should return == 0')

    def testTestScriptGroup(self):
        r=nxScript.Test(self.get_script,self.set_script,self.test_script, "", "mail" )
        print('TEST='+repr(r))
        self.assertTrue(r == [0],'nxScript.Test(self.get_script,self.set_script,self.test_script, "", "mail" )[0] should return == 0')

    def testSetScriptGroup(self):
        r=nxScript.Set(self.get_script,self.set_script,self.test_script, "", "mail" )
        print('SET='+repr(r))
        self.assertTrue(r[0] == 0,'nxScript.Set(self.get_script,self.set_script,self.test_script, "", "mail" )[0] should return == 0')


    def testGetScriptUserError(self):
        r=nxScript.Get(self.get_script,self.set_script,self.test_script, "ojoma", "" )
        print('GET='+repr(r))
        self.assertTrue(r[0] == -1,'nxScript.Get(self.get_script,self.set_script,self.test_script, "ojoma", "" )[-1] should return == -1')

    def testTestScriptUserError(self):
        r=nxScript.Test(self.get_script,self.set_script,self.test_script, "ojoma", "" )
        print('TEST='+repr(r))
        self.assertTrue(r == [-1],'nxScript.Test(self.get_script,self.set_script,self.test_script, "ojoma", "" )[-1] should return == -1')

    def testSetScriptUserError(self):
        r=nxScript.Set(self.get_script,self.set_script,self.test_script, "ojoma", "" )
        print('SET='+repr(r))
        self.assertTrue(r[0] == -1,'nxScript.Set(self.get_script,self.set_script,self.test_script, "ojoma", "" )[-1] should return == -1')

    def testGetScriptGroupError(self):
        r=nxScript.Get(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        print('GET='+repr(r))
        self.assertTrue(r[0] == -1,'nxScript.Get(self.get_script,self.set_script,self.test_script, "", "ojoma" )[-1] should return == -1')

    def testTestScriptGroupError(self):
        r=nxScript.Test(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        print('TEST='+repr(r))
        self.assertTrue(r == [-1],'nxScript.Test(self.get_script,self.set_script,self.test_script, "", "ojoma" )[-1] should return == -1')

    def testSetScriptGroupError(self):
        r=nxScript.Set(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        print('SET='+repr(r))
        self.assertTrue(r[0] == -1,'nxScript.Set(self.get_script,self.set_script,self.test_script, "", "ojoma" )[-1] should return == -1')

class LinuxPackageTestCases(unittest2.TestCase):
    """
    Test cases for nxPackage
    """
    def setUp(self):
        """
        Setup test resources
        """
        time.sleep(2)
        if os.system('which dpkg ') == 0 :
            os.system('dpkg -r nano &> /dev/null')
        else :
            os.system('rpm -e nano &> /dev/null')
        time.sleep(2)
        d=platform.dist()[0].lower()
        if 'cent' in d:
            self.package_path='./nano-2.0.9-7.el6.x86_64.rpm'
        elif 'suse' in d:
            self.package_path='./nano-2.3.2-2.1.2.x86_64.rpm'
        elif 'mint' in d or 'ubuntu' in d:
            self.package_path='./nano_2.2.6-1ubuntu1_amd64.deb'
            
    def tearDown(self):
        """
        Remove test resources.
        """
        time.sleep(2)
        if os.system('which dpkg ') == 0 :
            os.system('dpkg -r nano &> /dev/null')
        else :
            os.system('rpm -e nano &> /dev/null')
        time.sleep(2)
    
    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass
    
    def testSetEnableNameDefaultProviderArguments(self):
        """
        use the appropriate argument to try-out a package
        with no installation, then test that the package is not installed.
        """
        dryrun={}
        dryrun['zypper']='--dry-run'
        dryrun['apt']='--dry-run'
        dryrun['yum']='-v' # no dry run in yum...
        dryrun['dpkg']='--dry-run'
        dryrun['rpm']='--test'
        pm=nxPackage.GetPackageManager()
        args=dryrun[pm]
        if pm == 'zypper':
            args='|'+args
        self.assertTrue(nxPackage.Set('Present','','nano','','false',args,'true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        
    def testSetEnablePathAndNameDefaultProvider(self):
        """
        Test that when Path and Name are set, Path is used.
        """
        self.assertTrue(nxPackage.Set('Present','','nano',self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','nano','','"+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")

    def testSetEnableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")

    def testSetEnableNameExplicitProvider(self):
        pm=nxPackage.GetPackageManager()
        self.assertTrue(nxPackage.Set('Present',pm,'nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','"+pm+"','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
 
    def testSetEnableNameBadExplicitProviderError(self):
        pm=nxPackage.GetPackageManager()
        for b in ('zypper','yum','apt-get'):
            if b != pm:
                break
        self.assertTrue(nxPackage.Set('Present',b,'nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [-1],"nxPackage.Set('Present','"+b+"','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]")

    def testSetEnableNameDefaultProviderBadReturnCodeError(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [-1],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]")

    def testGetEnableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        print('GET:'+repr(nxPackage.Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','GET:'+repr(nxPackage.Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==
                        0,"nxPackage.Get('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == 0")

    def testTestEnableNameDefaultProviderBadReturnCodeError(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        print('TEST:'+repr(nxPackage.Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','TEST:'+repr(nxPackage.Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [-1],"nxPackage.Test('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','') should return == [-1]")

    def testGetEnableNameDefaultProviderBadReturnCodeError(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        print('GET:'+repr(nxPackage.Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','GET:'+repr(nxPackage.Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')[0]==
                        -1,"nxPackage.Get('Present','','nano','','false','','true',6,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == -1")

    def testTestEnableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        print('TEST:'+repr(nxPackage.Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','TEST:'+repr(nxPackage.Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Test('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [0]")

    @unittest2.skipUnless(os.system('which yum ') ==
                          0,'groupmode is not implemented.')
    def testSetEnableGroupDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','Remote Desktop Clients','','true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
            
    def testSetEnablePathDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','',self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','','"+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")

    def testSetDisableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        time.sleep(2)
        self.assertTrue(nxPackage.Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")

    def testGetDisableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        time.sleep(2)
        self.assertTrue(nxPackage.Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        time.sleep(2)
        print('GET:'+repr(nxPackage.Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','GET:'+repr(nxPackage.Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==
                        0,"nxPackage.Get('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == 0")

    def testTestDisableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        time.sleep(2)
        self.assertTrue(nxPackage.Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        time.sleep(2)
        print('TEST:'+repr(nxPackage.Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','TEST:'+repr(nxPackage.Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Test('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [0]")

    @unittest2.skipUnless(os.system('which yum ') ==
                          0,'groupmode is not implemented.')
    def testSetDisableGroupDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','Remote Desktop Clients','','true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
        time.sleep(2)
        self.assertTrue(nxPackage.Set('Absent','','Remote Desktop Clients','','true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Absent','','nano','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")
            
    def testSetDisablePathDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Absent','','',self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','','"+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")

    def testSetEnableBadNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [-1],"nxPackage.Set('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]")

    def testGetEnableBadNameDefaultProvider(self):
        print('GET:'+repr(nxPackage.Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','GET:'+repr(nxPackage.Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==
                        -1,"nxPackage.Get('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[-1] should return == -1")

    def testTestEnableBadNameDefaultProvider(self):
        print('TEST:'+repr(nxPackage.Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','TEST:'+repr(nxPackage.Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [-1],"nxPackage.Test('Present','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [-1]")

    def testSetEnableBadPathDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Present','','','BADPATH'+self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [-1],"nxPackage.Set('Present','','','"+ 'BADPATH'+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[-1]")

    def testSetDisableBadNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")

    def testGetDisableBadNameDefaultProvider(self):
        print('GET:'+repr(nxPackage.Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','GET:'+repr(nxPackage.Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0]==
                        0,"nxPackage.Get('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')[0] should return == 0")

    def testTestDisableBadNameDefaultProvider(self):
        print('TEST:'+repr(nxPackage.Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        nxPackage.Log('/tmp/DSC-nxPackage.log','TEST:'+repr(nxPackage.Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')))
        self.assertTrue(nxPackage.Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Test('Absent','','nanoo','','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return == [0]")

    def testSetDisableBadPathDefaultProvider(self):
        self.assertTrue(nxPackage.Set('Absent','','', 'BADPATH'+ self.package_path,'true','','true',0,'/tmp/DSC-nxPackage.log','','','','','','')==
                        [0],"nxPackage.Set('Present','','','"+  'BADPATH'+ self.package_path +"','false','','true',0,'/tmp/DSC-nxPackage.log','','','','','','') should return ==[0]")

class LinuxFileTestCases(unittest2.TestCase):
    """
    Test cases for nxFile
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('rm -rf /tmp/*pp*')

    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('rm -rf /tmp/*pp*')

    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass

    def testSetFileAbsent(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetFileAbsentError(self):
        self.assertTrue(nxFile.Set("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetFileData(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/1.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)

    def testSetFileDataError(self):
        self.assertTrue(nxFile.Set("/tp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Set("/tp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [-1]')

    def testSetFileNoData(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/1.pp')
        self.assertTrue(len(d)==
                        0,"The contents of 1.pp should be empty.  File contents mismatch:"+d)

    def testTestCompareFilesMD5Same(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        
    def testTestCompareFilesMD5Different(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        
    def testTestCompareFilesMD5Error(self):
        self.assertTrue(nxFile.Test("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Test("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testSetFileCopy(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/12.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)

    def testSetDirectoryPresent(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        True,'Directory /tmp/pp is missing.')

    def testSetDirectoryAbsent(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        False,'Directory /tmp/pp is present.')

    def testSetDirectoryAbsentError(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetCopyDirectoryToNew(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        True,'Directory /tmp/pp is missing.')
        self.assertTrue(nxFile.Set("/tmp/ppp", "/tmp/pp", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/ppp') ==
                        True,'Directory /tmp/ppp is missing.')
        
    def testSetCopyDirectoryToExistingForce(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        True,'Directory /tmp/pp is missing.')
        self.assertTrue(nxFile.Set("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/pp/1.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)
        self.assertTrue(nxFile.Set("/tmp/ppp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/ppp') ==
                        True,'Directory /tmp/ppp is missing.')
        self.assertTrue(nxFile.Set("/tmp/ppp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/ppp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/ppp/1.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)
        self.assertTrue(nxFile.Set("/tmp/ppp", "/tmp/pp", "Present", "Directory", "Force", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetModeRecursive(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755") should return [0]')
        self.assertTrue((nxFile.StatFile('/tmp/pp/1.pp').st_mode & 0755 ) ==
                        0755 and (nxFile.StatFile('/tmp/pp/12.pp').st_mode & 0755) == 0755,'Mode of /tmp/pp/1.pp and /tmp/pp/12.pp should be 755')

    def testSetOwnerRecursive(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "mail", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.StatFile('/tmp/pp/1.pp').st_gid ==
                        grp.getgrnam('mail')[2]  and nxFile.StatFile('/tmp/pp/12.pp').st_gid == grp.getgrnam('mail')[2] ,'Group of /tmp/pp/1.pp and /tmp/pp/12.pp should be mail')

    def testTestNoDestPathError(self):
        self.assertTrue(nxFile.Test("", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Test("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testTestFilePresentError(self):
        self.assertTrue(nxFile.Test("/tp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Test("/tp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testTestFilePresent(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestFileAbsentError(self):
        self.assertTrue(nxFile.Test("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestFileAbsent(self):
        self.assertTrue(nxFile.Test("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestDirectoryRecurseCheckOwnerError(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "udos", "", "")==
                        [-1],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "udos", "", "") should return [-1]')

    def testTestDirectoryRecurseCheckGroupError(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "mail", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "udos", "")==
                        [-1],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "udos", "") should return [-1]')

    def testTestDirectoryRecurseCheckModeError(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "755")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "755") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "744")==
                        [-1],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "744") should return [-1]')

    def testTestDirectoryRecurseCheckOwner(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        me =  pwd.getpwuid(os.getuid()).pw_name
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", me, "", "")==
                        [0],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryRecurseCheckGroup(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        me = grp.getgrgid(os.getgid()).gr_name
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", me, "")==
                        [0],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryRecurseCheckMode(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755") should return [0]')
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "755")==
                        [0],'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "755") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755")==
                        [0],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "True", "", "", "", "755") should return [0]')

    def testGetNoDestPathError(self):
        self.assertTrue(nxFile.Get("", "", "Present", "File", "", "", "md5", "", "", "", "", "")[0]==
                        -1,'nxFile.Get("", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testGetFilePresent(self):
        self.assertTrue(nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")[0]==
                        0,'nxFile.Set("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Get("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")[0]==
                        0,'nxFile.Get("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testGetDirectoryPresent(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")[0]==
                        0,'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "","", "")==
                        [0],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Get("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")[0]==
                        0,'nxFile.Get("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestDirectoryCheckOwnerError(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "udos", "", "")==
                        [-1],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "udos", "", "") should return [-1]')

    def testTestDirectoryCheckGroupError(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "mail", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "udos", "")==
                        [-1],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "udos", "") should return [-1]')

    def testTestDirectoryCheckOwner(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        me =  pwd.getpwuid(os.getuid()).pw_name
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", me, "", "")==
                        [0],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryCheckGroup(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "mail", "") should return [0]')
        me = grp.getgrgid(os.getgid()).gr_name
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", me, "")==
                        [0],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryCheckMode(self):
        self.assertTrue(nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "776")==
                        [0],'nxFile.Set("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "776") should return [0]')
        self.assertTrue(nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "776")==
                        [0],'nxFile.Test("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "776") should return [0]')

dummy_service_file=r"""#!/usr/bin/env python
import time
import os
with open('/var/run/dummy_service.pid','w') as F: 
        F.write(str(os.getpid()) + "\n")
        F.flush()
        F.close()
while True:
    time.sleep(5)
    with open('/tmp/dummy_service.log','a') as F: 
        F.write('dummy_service is running at '+time.asctime()+'\n')
        F.flush()
        F.close()
"""

#sample init files for testing
upstart_etc_default="""# To disable the Windows Azure Agent, set DUMMY_SERVICE_ENABLED=0
DUMMY_SERVICE_ENABLED=1
"""
upstart_init_conf="""description "Windows Azure Linux agent"
author "Ben Howard <ben.howard@canonical.com>"
export PATH=$PATH:/usr/local/bin
start on mounted MOUNTPOINT=/
stop on runlevel [!2345]

pre-start script

    [ -r /etc/default/dummy_service ] && . /etc/default/dummy_service

    if [ "$DUMMY_SERVICE_ENABLED" != "1" ]; then
        stop ; exit 0
    fi

    if [ ! -x /usr/sbin/dummy_service.py ]; then
        stop ; exit 0
    fi

    #Load the udf module
    modprobe -b udf

end script

exec /usr/sbin/dummy_service.py -daemon
"""

upstart_init_d_file = """#!/bin/sh -e
# upstart-job
#
# Symlink target for initscripts that have been converted to Upstart.

set -e

UPSTART_JOB_CONF="/etc/default/upstart-job"
INITSCRIPT="$(basename "$0")"
JOB="${INITSCRIPT%.sh}"

if [ "$JOB" = "upstart-job" ]; then
    if [ -z "$1" ]; then
        echo "Usage: upstart-job JOB COMMAND" 1>&2
	exit 1
    fi

    JOB="$1"
    INITSCRIPT="$1"
    shift
else
    if [ -z "$1" ]; then
        echo "Usage: $0 COMMAND" 1>&2
	exit 1
    fi
fi

COMMAND="$1"
shift

ECHO=echo
ECHO_ERROR=echo
if [ -e "$UPSTART_JOB_CONF" ]; then
	. "$UPSTART_JOB_CONF"
fi
if [ -n "$DPKG_MAINTSCRIPT_PACKAGE" ]; then
	ECHO=:
	ECHO_ERROR=:
fi

$ECHO "Rather than invoking init scripts through /etc/init.d, use the service(8)"
$ECHO "utility, e.g. service $INITSCRIPT $COMMAND"

# Only check if jobs are disabled if the currently _running_ version of
# Upstart (which may be older than the latest _installed_ version)
# supports such a query.
#
# This check is necessary to handle the scenario when upgrading from a
# release without the 'show-config' command (introduced in
# Upstart for Ubuntu version 0.9.7) since without this check, all
# installed packages with associated Upstart jobs would be considered
# disabled.
#
# Once Upstart can maintain state on re-exec, this change can be
# dropped (since the currently running version of Upstart will always
# match the latest installed version).

UPSTART_VERSION_RUNNING=$(initctl version|awk '{print $3}'|tr -d ')')

if dpkg --compare-versions "$UPSTART_VERSION_RUNNING" ge 0.9.7
then
    initctl show-config -e "$JOB"|grep -q '^  start on' || DISABLED=1
fi

case $COMMAND in
status)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the $COMMAND(8) utility, e.g. $COMMAND $JOB"
    $COMMAND "$JOB"
    ;;
start|stop)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the $COMMAND(8) utility, e.g. $COMMAND $JOB"
    if status "$JOB" 2>/dev/null | grep -q ' start/'; then
        RUNNING=1
    fi
    if [ -z "$RUNNING" ] && [ "$COMMAND" = "stop" ]; then
        exit 0
    elif [ -n "$RUNNING" ] && [ "$COMMAND" = "start" ]; then
        exit 0
    elif [ -n "$DISABLED" ] && [ "$COMMAND" = "start" ]; then
        exit 0
    fi
    $COMMAND "$JOB"
    ;;
restart)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the stop(8) and then start(8) utilities,"
    $ECHO "e.g. stop $JOB ; start $JOB. The restart(8) utility is also available."
    if status "$JOB" 2>/dev/null | grep -q ' start/'; then
        RUNNING=1
    fi
    if [ -n "$RUNNING" ] ; then
        stop "$JOB"
    fi
    # If the job is disabled and is not currently running, the job is
    # not restarted. However, if the job is disabled but has been forced into the
    # running state, we *do* stop and restart it since this is expected behaviour
    # for the admin who forced the start.
    if [ -n "$DISABLED" ] && [ -z "$RUNNING" ]; then
        exit 0
    fi
    start "$JOB"
    ;;
reload|force-reload)
    $ECHO
    $ECHO "Since the script you are attempting to invoke has been converted to an"
    $ECHO "Upstart job, you may also use the reload(8) utility, e.g. reload $JOB"
    reload "$JOB"
    ;;
*)
    $ECHO_ERROR
    $ECHO_ERROR "The script you are attempting to invoke has been converted to an Upstart" 1>&2
    $ECHO_ERROR "job, but $COMMAND is not supported for Upstart jobs." 1>&2
    exit 1
esac
"""

debian_init_file = """#!/bin/sh
### BEGIN INIT INFO
# Provides:          dummy_service
# Required-Start:    $network $syslog
# Required-Stop:     $network $syslog
# Should-Start:      $network $syslog
# Should-Stop:       $network $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: dummy_service
# Description:       dummy_service
### END INIT INFO

. /lib/lsb/init-functions

OPTIONS="-daemon"
WAZD_BIN=/usr/sbin/dummy_service.py
WAZD_PID=/var/run/dummy_service.pid

case "$1" in
    start)
        log_begin_msg "Starting dummy_service..."
        pid=$( pidofproc $WAZD_BIN )
        if [ -n "$pid" ] ; then
              log_begin_msg "Already running."
              log_end_msg 0
              exit 0
        fi
        start-stop-daemon --start --quiet --oknodo --background --exec $WAZD_BIN -- $OPTIONS
        log_end_msg $?
        ;;

    stop)
        log_begin_msg "Stopping dummy_service..."
        start-stop-daemon --stop --quiet --oknodo --pidfile $WAZD_PID
        ret=$?
        rm -f $WAZD_PID
        log_end_msg $ret
        ;;
    force-reload)
        $0 restart
        ;;
    restart)
        $0 stop
        $0 start
        ;;
    status)
        status_of_proc $WAZD_BIN && exit 0 || exit $?
        ;;
    *)
        log_success_msg "Usage: /etc/init.d/dummy_service {start|stop|force-reload|restart|status}"
        exit 1
        ;;
esac

exit 0
"""

suse_init_file = """#! /bin/sh
#
# Windows Azure Linux Agent sysV init script
#
# Copyright 2013 Microsoft Corporation
# Copyright SUSE LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# /etc/init.d/dummy_service
#
#  and symbolic link
#
# /usr/sbin/rcdummy_service
#
# System startup script for the dummy_service 
#
### BEGIN INIT INFO
# Provides: dummy_service
# Required-Start: $network sshd
# Required-Stop: $network sshd
# Default-Start: 3 5
# Default-Stop: 0 1 2 6
# Description: Start the dummy_service
### END INIT INFO

PYTHON=/usr/bin/python
WAZD_BIN=/usr/sbin/dummy_service.py
WAZD_PIDFILE=/var/run/dummy_service.pid

test -x "$WAZD_BIN" || { echo "$WAZD_BIN not installed"; exit 5; }

. /etc/rc.status

# First reset status of this service
rc_reset

# Return values acc. to LSB for all commands but status:
# 0 - success
# 1 - misc error
# 2 - invalid or excess args
# 3 - unimplemented feature (e.g. reload)
# 4 - insufficient privilege
# 5 - program not installed
# 6 - program not configured
#
# Note that starting an already running service, stopping
# or restarting a not-running service as well as the restart
# with force-reload (in case signalling is not supported) are
# considered a success.


case "$1" in
    start)
        echo -n "Starting dummy_service"
        ## Start daemon with startproc(8). If this fails
        ## the echo return value is set appropriate.
        startproc -f ${PYTHON} ${WAZD_BIN} -daemon
        rc_status -v
        ;;
    stop)
        echo -n "Shutting down dummy_service"
        ## Stop daemon with killproc(8) and if this fails
        ## set echo the echo return value.
        killproc -p ${WAZD_PIDFILE} ${PYTHON} ${WAZD_BIN}
        rc_status -v
        ;;
    try-restart)
        ## Stop the service and if this succeeds (i.e. the
        ## service was running before), start it again.
        $0 status >/dev/null && $0 restart
        rc_status
        ;;
    restart)
        ## Stop the service and regardless of whether it was
        ## running or not, start it again.
        $0 stop
        sleep 1
        $0 start
        rc_status
        ;;
    force-reload|reload)
        rc_status
        ;;
    status)
        echo -n "Checking for service dummy_service "
        ## Check status with checkproc(8), if process is running
        ## checkproc will return with exit status 0.

        checkproc -p ${WAZD_PIDFILE} ${PYTHON} ${WAZD_BIN}
        rc_status -v
        ;;
    probe)
        ;;
    *)
        echo "Usage: $0 {start|stop|status|try-restart|restart|force-reload|reload}"
        exit 1
        ;;
esac
rc_exit
"""
redhat_init_file= """#!/bin/bash
#
# Init file for dummy_service.
#
# chkconfig: 2345 60 80
# description: dummy_service
# pidfile: /var/run/dummy_service.pid
# processname dummy_service.py
# source function library
. /etc/rc.d/init.d/functions

RETVAL=0
FriendlyName="dummy_service"
WAZD_BIN=/usr/sbin/dummy_service.py

start()
{
    echo -n $"Starting $FriendlyName: "
    $WAZD_BIN &
}

stop()
{
    echo -n $"Stopping $FriendlyName: "
    killproc -p /var/run/dummy_service.pid $WAZD_BIN
    RETVAL=$?
    echo
    return $RETVAL
}

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        stop
        start
        ;;
    reload)
        ;;
    report)
        ;;
    status)
        status $FriendlyName
        RETVAL=$?
        ;;
    *)
        echo $"Usage: $0 {start|stop|restart|status}"
        RETVAL=1
esac
exit $RETVAL
"""



class LinuxServiceTestCases(unittest2.TestCase):
    """
    Test cases for nxService
    """
    def setUp(self):
        """
        Setup test resources
        """
        self.provider = None

        dist=platform.dist()[0].lower()
        if 'suse' in dist:
            init_file=suse_init_file
        elif 'redhat' in dist:
            init_file=redhat_init_file
        elif 'cent' in dist:
            init_file=redhat_init_file
        elif 'debian' in dist:
            init_file=debian_init_file
            
        if nxService.SystemdExists():
            self.provider='systemd'
            try:
                nxService.WriteFile('/etc/rc.d/dummy_service',init_file)
                os.chmod('/etc/rc.d/dummy_service',0744)
                nxService.WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print(repr(sys.sys_info()))
                sys.exit(1)

        elif nxService.UpstartExists():
            self.provider='upstart'
            try:
                nxService.WriteFile('/etc/default/dummy_service',upstart_etc_default)
                os.chmod('/etc/default/dummy_service',0744)
                nxService.WriteFile('/etc/init/dummy_service.conf',upstart_init_conf)
                nxService.WriteFile('/etc/init.d/dummy_service',upstart_init_d_file)
                os.chmod('/etc/init.d/dummy_service',0744)
                nxService.WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print(repr(sys.sys_info()))
                sys.exit(1)
        elif nxService.InitExists():
            self.provider='init'
            try:
                nxService.WriteFile('/etc/init.d/dummy_service',init_file)
                os.chmod('/etc/init.d/dummy_service',0744)
                nxService.WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print(repr(sys.sys_info()))
                sys.exit(1)
            

    def tearDown(self):
        """
        Remove test resources.
        """
        if nxService.SystemdExists():
            os.system('chkconfig --del dummy_service &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/rc.d/dummy_service &> /dev/null')
            os.system('systemctl --system daemon-reload &> /dev/null')
        if nxService.InitExists():
            os.system('chkconfig --del dummy_service &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/init.d/dummy_service &> /dev/null')
        if nxService.UpstartExists():
            os.system('update-rc.d -f dummy_service remove &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/init/dummy_service.conf /etc/init.d/dummy_service /etc/default/dummy_service &> /dev/null')
            
        time.sleep(1)
        os.system("ps -ef | grep -v grep | grep dummy_service | awk '{print $2}' | xargs -L1 kill &> /dev/null")
        
    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass
    
    def testSetEnable(self):
        provider=self.provider
        self.assertTrue(nxService.Set("dummy_service", provider, "true", "running")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]')

    def testSetDisable(self):
        provider=self.provider
        self.assertTrue(nxService.Set("dummy_service", provider, "true", "running")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]')
        self.assertTrue(nxService.Set("dummy_service", provider, "false", "stopped")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]')

    def testSetEnableError(self):
        provider=self.provider
        self.assertTrue(nxService.Set("yummyservice", provider, "true", "running")==
                        [-1],'nxService.Set("yummyservice", "'+provider+'", "true", "running") should return ==[-1]')

    def testSetDisableError(self):
        provider=self.provider
        self.assertTrue(nxService.Set("yummyservice", provider, "false", "stopped")==
                        [-1],'nxService.Set("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]')

    def testGetEnable(self):
        provider=self.provider
        self.assertTrue(nxService.Set("dummy_service", provider, "true", "running")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]')
        self.assertTrue(nxService.Get("dummy_service", provider, "true", "running")[0:5]==
                        [0,"dummy_service",provider,"true","running"],'nxService.Get("dummy_service", "'+provider+'", "true", "running") should return ==[0]')

    def testGetDisable(self):
        provider=self.provider
        self.assertTrue(nxService.Set("dummy_service", provider, "true", "running")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]')
        self.assertTrue(nxService.Set("dummy_service", provider, "false", "stopped")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]')
        print('GET:'+repr(nxService.Get("dummy_service", provider, "false", "stopped")))
        self.assertTrue(nxService.Get("dummy_service", provider, "false", "stopped")[0:5]==
                        [0,"dummy_service", provider, "false", "stopped"],'nxService.Get("dummy_service", "'+provider+'", "false", "stopped") should return ==[0,"dummy_service", provider, "false", "stopped"]')

    def testGetEnableError(self):
        provider=self.provider
        self.assertTrue(nxService.Set("yummyservice", provider, "true", "running")==
                        [-1],'nxService.Set("yummyservice", "'+provider+'", "true", "running") should return ==[-1]')
        print('GET:'+repr(nxService.Get("yummyservice", provider, "true", "running")[0:5]))
        self.assertTrue(nxService.Get("yummyservice", provider, "true", "running")[0:5]==
                        [-1,"yummyservice", provider, "true", "running"],'nxService.Get("yummyservice", "'+provider+'", "true", "running")[0:5] should return ==[-1,"yummyservice", provider, "true", "running"]')

    def testGetDisableError(self):
        provider=self.provider
        self.assertTrue(nxService.Set("yummyservice", provider, "false", "stopped")==
                        [-1],'nxService.Set("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]')
        print('GET:'+repr(nxService.Get("yummyservice", provider, "false", "stopped")))
        self.assertTrue(nxService.Get("yummyservice", provider, "false", "stopped")[0:5]==
                        [-1,"yummyservice", provider, "false", "stopped"],'nxService.Get("yummyservice", "'+provider+'", "false", "stopped")[0:5] should return ==[-1,"yummyservice", provider, "false", "stopped"]')

    def testTestEnable(self):
        provider=self.provider
        self.assertTrue(nxService.Set("dummy_service", provider, "true", "running")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]')
        self.assertTrue(nxService.Test("dummy_service", provider, "true", "running")==
                        [0],'nxService.Test("dummy_service", "'+provider+'", "true", "running") should return ==[0]')

    def testTestDisable(self):
        provider=self.provider
        self.assertTrue(nxService.Set("dummy_service", provider, "true", "running")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "true", "running") should return ==[0]')
        self.assertTrue(nxService.Set("dummy_service", provider, "false", "stopped")==
                        [0],'nxService.Set("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]')
        print('GET:'+repr(nxService.Test("dummy_service", provider, "false", "stopped")))
        self.assertTrue(nxService.Test("dummy_service", provider, "false", "stopped")==
                        [0],'nxService.Test("dummy_service", "'+provider+'", "false", "stopped") should return ==[0]')

    def testTestEnableError(self):
        provider=self.provider
        self.assertTrue(nxService.Set("yummyservice", provider, "true", "running")==
                        [-1],'nxService.Set("yummyservice", "'+provider+'", "true", "running") should return ==[-1]')
        print('GET:'+repr(nxService.Test("yummyservice", provider, "true", "running")[0:5]))
        self.assertTrue(nxService.Test("yummyservice", provider, "true", "running")==
                        [-1],'nxService.Test("yummyservice", "'+provider+'", "true", "running") should return ==[-1]')

    def testTestDisableError(self):
        """
        It is correct for us to get back [0]
        if we ask for a non-enabled, non-existing service.
        To foce the error, we send enabled = 'true'.
        """
        provider=self.provider
        self.assertTrue(nxService.Set("yummyservice", provider, "false", "stopped")==
                        [-1],'nxService.Set("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]')
        print('GET:'+repr(nxService.Test("yummyservice", provider, "false", "stopped")))
        self.assertTrue(nxService.Test("yummyservice", provider, "true", "stopped")==
                        [-1],'nxService.Test("yummyservice", "'+provider+'", "false", "stopped") should return ==[-1]')


class LinuxSshAuthorizedKeysTestCases(unittest2.TestCase):
    """
    Test cases for nxSshAuthorizedKeys.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        self.mykey='MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDLXp6PkCtbpV+P1gwFQWH6Ez0U83uEmS8IGnpeI8Fk8rY/vHOZzZZaxRCw+loyc342qCDIQheMOCNm5Fkevz06q757/oooiLR3yryYGKiKG1IZIiplmtsC95oKrzUSKk60wuI1mbgpMUP5LKi/Tvxes5PmkUtXfimz2qgkeUcPpQIDAQAB'
        if not os.path.isdir('/home/jojoma') :
            nxUser.Set("jojoma", "Present", "JO JO MA", "JOJOMA", 'badpass', "False", "False", "/home/jojoma", "mail" )    
        path='/home/jojoma/.ssh/authorized_keys'
        if not os.path.isfile(path):
            os.system('echo '+ self.mykey + ' > ' + path +' ; echo ' + self.mykey +' >> ' + path )
        os.system('cp -p ' + path + ' /tmp/')

    def tearDown(self):
        """
        Remove test resources.
        """
        path='/home/jojoma/.ssh/authorized_keys'
        if os.path.isfile('/tmp/authorized_keys'):
            os.system('mv /tmp/authorized_keys ' + path)
        os.system('chown jojoma ' + path)
            


    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass

    def testSetKeyPresentTwice(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',key) should be == [0]")
        # do this twice to prove there is no error if the same key already exists
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',key) should be == [0]")

    def testSetKeyAbsentTwice(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',key) should be == [0]")
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Absent','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set('MyKey','Absent','jojoma',key) should be == [0]")
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Absent','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set('MyKey','Absent','jojoma',key) should be == [0]")

    def testTestKeyPresent(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',key) should be == [0]")
        self.assertTrue(nxSshAuthorizedKeys.Test('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Test('MyKey','Present','jojoma',key) should be == [0]")
        
    def testTestKeyPresentError(self):
        self.assertTrue(nxSshAuthorizedKeys.Test('MyKey','Present','jojoma',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Test('MyKey','Present','jojoma',key) should be == [-1]")
        
    def testGetKeyPresent(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set('MyKey','Present','jojoma',key) should be == [0]")
        self.assertTrue(nxSshAuthorizedKeys.Get('MyKey','Present','jojoma',self.mykey)[0] ==
                        0,"assert nxSshAuthorizedKeys.Get('MyKey','Present','jojoma',key)[0] should be == 0")
        
    def testGetKeyPresentError(self):
        self.assertTrue(nxSshAuthorizedKeys.Get('MyKey','Present','jojoma',self.mykey)[0] ==
                        -1,"assert nxSshAuthorizedKeys.Get('MyKey','Present','jojoma',key)[0] should be == -1")

    def testGetKeyPresentBadUser(self):
        self.assertTrue(nxSshAuthorizedKeys.Get('MyKey','Present','jojoma',self.mykey)[0] ==
                        -1,"assert nxSshAuthorizedKeys.Get('MyKey','Present','jojoma',key)[0] should be == -1")

    def testTestKeyPresentBadUser(self):
        self.assertTrue(nxSshAuthorizedKeys.Test('MyKey','Present','jojoma',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Test('MyKey','Present','jojoma',key) should be == [-1]")

    def testSetKeyPresentMissingKeyComment(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('','Present','jojoma',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Set('','Present','jojoma',key) should be == [-1]")
        
    def testSetKeyPresentMissingEnsure(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','','jojoma',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Set('MyKey','','jojoma',key) should be == [-1]")
        
    def testSetKeyPresentMissingUserName(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Present','',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Set('MyKey','Present','',key) should be == [-1]")
        
    def testSetKeyPresentMissingKey(self):
        self.assertTrue(nxSshAuthorizedKeys.Set('MyKey','Present','jojoma','') ==
                        [-1],"assert nxSshAuthorizedKeys.Set('MyKey','Present','jojoma','') should be == [-1]")



class LinuxEnvironmentTestCases(unittest2.TestCase):
    """
    Test cases for nxEnvironment.py
    """
    
    def setUp(self):
        """
        Setup test resources
        """
        os.system('rm /tmp/environment /tmp/DSCEnvironment.sh')
        path='/etc/environment'
        if os.path.isfile(path) :
            os.system('cp -p ' + path + ' /tmp/')

        path='/etc/profile.d/DSCEnvironment.sh'
        if os.path.isfile(path) :
            os.system('cp -p ' + path + ' /tmp/')

    def tearDown(self):
        """
        Remove test resources.
        """
        print("TEARDOWN")
        os.system('echo "Contents of /etc/environment are: " 1>&2' )
        os.system('cat /etc/environment 1>&2')
        os.system('echo "Contents of /etc/profile.d/DSCEnvironment.sh are: " 1>&2')
        os.system('cat /etc/profile.d/DSCEnvironment.sh 1>&2')
        path='/etc/environment'
        if os.path.isfile('/tmp/environment') :
            os.system('mv ' + ' /tmp/environment ' + path)
        path='/etc/profile.d/DSCEnvironment.sh'
        if os.path.isfile('/tmp/DSCEnvironment.sh') :
            os.system('mv ' + ' /tmp/DSCEnvironment.sh ' + path)
            

    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass


    def testSetVarPresentTwice(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') ==
                        [0],"self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [0]")
        # do this twice to prove there is no error if the same path already exists
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') ==
                        [0],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [0]")

    def testSetVarPresentTwoValues(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') ==
                        [0],"self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [0]")
        # do this twice to prove there is no error if the same path already exists
        self.assertTrue(nxEnvironment.Set('MYVAR2','/tmp','Present','False') ==
                        [0],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [0]")
        self.assertTrue(nxEnvironment.Get('MYVAR','/tmp','Present','False')[0] ==
                        0,"assert nxEnvironment.Get('MYVAR','/tmp','Present','False')[0] should == [0]")
        self.assertTrue(nxEnvironment.Get('MYVAR2','/tmp','Present','False')[0] ==
                        0,"assert nxEnvironment.Get('MYVAR2','/tmp','Present','False')[0] should == [0]")


    def testSetVarAbsentTwice(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') ==
                        [0],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [0]")
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Absent','False') ==
                        [0],"assert nxEnvironment.Set('MYVAR','/tmp','Absent','False') should == [0]")
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Absent','False') ==
                        [0],"assert nxEnvironment.Set('MYVAR','/tmp','Absent','False') should == [0]")

    def testTestVarPresent(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') ==
                        [0],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [0]")
        self.assertTrue(nxEnvironment.Test('MYVAR','/tmp','Present','False') ==
                        [0],"assert nxEnvironment.Test('MYVAR','/tmp','Present','False') should == [0]")
        
    def testTestVarPresentError(self):
        self.assertTrue(nxEnvironment.Test('MYVAR','/tp','Present','False') ==
                        [-1],"assert nxEnvironment.Test('MYVAR','/tmp','Present','False') should == [-1]")

    def testGetVarPresent(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','False') ==
                        [0],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [0]")
        print('GET:'+repr(nxEnvironment.Get('MYVAR','/tmp','Present','False')))
        self.assertTrue(nxEnvironment.Get('MYVAR','/tmp','Present','False')[0] ==
                        0,"assert nxEnvironment.Get('MYVAR','/tmp','Present','False')[0] should == [0]")
        
    def testGetVarPresentError(self):
        print('GET:'+repr(nxEnvironment.Get('MYVAR','/tp','Present','False')))
        self.assertTrue(nxEnvironment.Get('MYVAR','/tp','Present','False')[0] ==
                        -1,"assert nxEnvironment.Get('MYVAR','/tmp','Present','False')[0] should == [-1]")

    def testSetPathPresentTwice(self):
        self.assertTrue(nxEnvironment.Set('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Present','True') should == [0]")
        # do this twice to prove there is no error if the same path already exists
        self.assertTrue(nxEnvironment.Set('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Present','True') should == [0]")


    def testSetPathAbsentTwice(self):
        self.assertTrue(nxEnvironment.Set('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Present','True') should == [0]")
        self.assertTrue(nxEnvironment.Set('','/tmp','Absent','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Absent','True') should == [0]")
        self.assertTrue(nxEnvironment.Set('','/tmp','Absent','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Absent','True') should == [0]")

    def testTestPathPresent(self):
        self.assertTrue(nxEnvironment.Set('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Present','True') should == [0]")
        self.assertTrue(nxEnvironment.Test('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Test('','/tmp','Present','True') should == [0]")

    def testTestPathPresentTwoValues(self):
        self.assertTrue(nxEnvironment.Set('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Present','True') should == [0]")
        self.assertTrue(nxEnvironment.Set('','/tmp2','Present','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp2','Present','True') should == [0]")
        self.assertTrue(nxEnvironment.Test('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Test('','/tmp','Present','True') should == [0]")
        self.assertTrue(nxEnvironment.Test('','/tmp2','Present','True') ==
                        [0],"assert nxEnvironment.Test('','/tmp2','Present','True') should == [0]")
        
    def testTestPathPresentError(self):
        self.assertTrue(nxEnvironment.Test('','/tp','Present','True') ==
                        [-1],"assert nxEnvironment.Test('','/tmp','Present','True') should == [-1]")

    def testGetPathPresent(self):
        self.assertTrue(nxEnvironment.Set('','/tmp','Present','True') ==
                        [0],"assert nxEnvironment.Set('','/tmp','Present','True') should == [0]")
        print('GET:'+repr(nxEnvironment.Get('','/tmp','Present','True')))
        self.assertTrue(nxEnvironment.Get('','/tmp','Present','True')[0] ==
                        0,"assert nxEnvironment.Get('','/tmp','Present','True') should == [0]")
        
    def testGetPathPresentError(self):
        print('GET:'+repr(nxEnvironment.Get('','/tp','Present','True')))
        self.assertTrue(nxEnvironment.Get('','/tp','Present','True')[0] ==
                        -1,"assert nxEnvironment.Get('','/tmp','Present','True')[0] should == [-1]")

    def testSetPathPresentMissingPath(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','Present','') ==
                        [-1],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [-1]")

        
    def testSetPathPresentMissingEnsure(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','/tmp','','False') ==
                        [-1],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [-1]")

        
    def testSetPathPresentMissingNamePathFalse(self):
        self.assertTrue(nxEnvironment.Set('','/tmp','Present','False') ==
                        [-1],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [-1]")

    def testSetPathPresentMissingValue(self):
        self.assertTrue(nxEnvironment.Set('MYVAR','','Present','False') ==
                        [-1],"assert nxEnvironment.Set('MYVAR','/tmp','Present','False') should == [-1]")

 

 class LinuxExecTestCases(unittest2.TestCase):
    """
    Test cases for nxExec.py
    """
    
    def setUp(self):
        """
        Setup test resources
        """
        os.system('rm /tmp/environment /tmp/DSCExec.sh')
        path='/etc/environment'
        if os.path.isfile(path) :
            os.system('cp -p ' + path + ' /tmp/')

        path='/etc/profile.d/DSCExec.sh'
        if os.path.isfile(path) :
            os.system('cp -p ' + path + ' /tmp/')

    def tearDown(self):
        """
        Remove test resources.
        """
        print("TEARDOWN")
        os.system('echo "Contents of /etc/environment are: " 1>&2' )
        os.system('cat /etc/environment 1>&2')
        os.system('echo "Contents of /etc/profile.d/DSCExec.sh are: " 1>&2')
        os.system('cat /etc/profile.d/DSCExec.sh 1>&2')
        path='/etc/environment'
        if os.path.isfile('/tmp/environment') :
            os.system('mv ' + ' /tmp/environment ' + path)
        path='/etc/profile.d/DSCExec.sh'
        if os.path.isfile('/tmp/DSCExec.sh') :
            os.system('mv ' + ' /tmp/DSCExec.sh ' + path)
            

    def noop(self,arg2):
        """
        Set a method to noop() to prevent its operation.
        """
        pass

# (Command,Environment,Shell,Returncode,Timeout,User,Group,TestCommand)

    def testSetVarPresentTwice(self):
        self.assertTrue(nxExec.Set('export JOJO=MAMA','/tmp','Present','if [ $JOJO != "MAMA" ]; then echo 0 ; else echo 1; fi') ==
                        [0],"self.assertTrue(nxExec.Set('MYVAR','/tmp','Present','False') should == [0]")

######################################
if __name__ == '__main__':
    s1=unittest2.TestLoader().loadTestsFromTestCase(LinuxUserTestCases)
    s2=unittest2.TestLoader().loadTestsFromTestCase(LinuxGroupTestCases)
    s3=unittest2.TestLoader().loadTestsFromTestCase(LinuxFileTestCases)
    s4=unittest2.TestLoader().loadTestsFromTestCase(LinuxScriptTestCases)
    s5=unittest2.TestLoader().loadTestsFromTestCase(LinuxServiceTestCases)
    s6=unittest2.TestLoader().loadTestsFromTestCase(LinuxPackageTestCases)
    s7=unittest2.TestLoader().loadTestsFromTestCase(LinuxSshAuthorizedKeysTestCases)
    s8=unittest2.TestLoader().loadTestsFromTestCase(LinuxEnvironmentTestCases)
    s9=unittest2.TestLoader().loadTestsFromTestCase(LinuxEnvironmentTestCases)
#    alltests = unittest2.TestSuite([s1,s2,s3,s4,s5,s6,s7,s8,s9])
    unittest2.TextTestRunner(verbosity=3).run(s9)


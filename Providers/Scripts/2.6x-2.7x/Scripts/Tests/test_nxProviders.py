#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
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
import codecs
import ctypes
import re
import inspect
import copy
import fnmatch
import hashlib
import base64
import socket
import thread
import shutil
import signal
import filecmp
import cPickle as pickle
from contextlib import contextmanager

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

try:
    import unittest2
except:
    os.system('tar -zxvf ./unittest2-0.5.1.tar.gz')
    sys.path.append(os.path.realpath('./unittest2-0.5.1'))
    import unittest2

def ParseMOF(mof_file):
    srch_list_elem=r'(=[ ]+)({)(.*?)(})([ ]?;)'
    repl_list_elem = r'\1[\3]\5'
    srch_instance=r'(?P<instance>instance)[ ,\n]+of[ ,\n]+(?!OMI)(?P<inst_type>.*?)[ ,\n]+as[ ,\n]+(?P<inst_value>.*?)[ ,\n]?{([ ,\n]+)?(?P<inst_text>.*?)}[ ,\n]?;'
    value_srch_str=r'([ ,\n]+)?(?P<name>.*?)([ ]+)?=([ ]+)?(?P<value>.*?)([ ]+)?;'
    instance_srch_str=r'([ ,\n]+)?ResourceID([ ]+)?=([ ]+)?"\[(?P<module>.*?)\](?P<ResourceID>.*?)"([ ]+)?;'
    list_elem=re.compile(srch_list_elem,re.M|re.S)
    instance=re.compile(srch_instance,re.M|re.S)
    value_srch=re.compile(value_srch_str,re.M|re.S)
    instance_srch=re.compile(instance_srch_str,re.M|re.S)
    mof_text=open(mof_file,'r').read()
    mof_text=list_elem.sub(repl_list_elem,mof_text)
    matches=instance.finditer(mof_text)
    d={}
    d.clear()
    curinst=''
    for match in matches:
        values=match.group('inst_text')
        values=re.sub('(/[*].*?[*]/)','',values)
        i=instance_srch.search(values)
        curinst='['+i.group('module')+']'+i.group('ResourceID').strip('"')
        d[curinst]={}
        v=value_srch.finditer(values)
        for pair in v:
            name=pair.group('name')
            value=pair.group('value')
            if value.lower().strip() == 'false':
                value='False'
            if value.lower().strip() == 'true':
                value='True'
            d[curinst][name]=eval(value)
    d[curinst].pop('ResourceID')
    d[curinst].pop('ModuleName')
    d[curinst].pop('ModuleVersion')
    if 'DependsOn' in d[curinst].keys():
        d[curinst].pop('DependsOn')
    the_module = globals ()[i.group('module')]
    argspec=inspect.getargspec(the_module.__dict__['Set_Marshall'])
    if type(argspec) == tuple :
        args=argspec[0]
    else :
        args=argspec.args
    for arg in args:
        if arg not in d[curinst].keys():
            d[curinst][arg]=None
    return d[curinst]

def check_values(s,d):
    if s is None and d is None:
        return True
    elif s is None or d is None:
        return False
    if s[0] != d[0]:
        return False
    sd=s[1]
    dd=d[1]
    for k in sd.keys():
        if sd[k] == None or dd[k] == None:
            continue
        if sd[k].value==None or dd[k].value==None:
            continue
        if type(sd[k].value) == ctypes.c_bool:
            if sd[k].value.value==None or dd[k].value.value==None:
                continue
            if sd[k].value.value != dd[k].value.value:
                print k+': '+str(sd[k].value.value)+' != '+str(dd[k].value.value)+'\n'
                return False
            continue
        if type(sd[k].value) == ctypes.c_uint or type(sd[k].value) == ctypes.c_ushort :
            if sd[k].value.value==None or dd[k].value.value==None:
                continue
            if sd[k].value.value != dd[k].value.value:
                print k+': '+str(sd[k].value.value)+' != '+str(dd[k].value.value)+'\n'
                return False
            continue
        if not deep_compare(sd[k].value, dd[k].value):  
            print k+': '+str(sd[k].value)+' != '+str(dd[k].value)+'\n'
            return False
    return True

def deep_compare(obj1, obj2):
    if type(obj1) == unicode:
        obj1 = obj1.decode('utf-8').encode('ascii', 'ignore')
    if type(obj2) == unicode:
        obj1 = obj2.decode('utf-8').encode('ascii', 'ignore')
    t1 = type(obj1)
    t2 = type(obj2)
    if t1 != t2:
        return False
    
    if t1 == list and len(obj1) == len(obj2):
        for i in range(len(obj1)):
            if not deep_compare(obj1[i], obj2[i]):
                return False
        return True

    if t1 == dict and len(obj1) == len(obj2):
        for k in obj1.keys():
            if not deep_compare(obj1[k], obj2[k]):
                return False
        return True

    try:
        if obj1 == obj2:
            return True
        if obj1.value == obj2.value:
            return True
    except:
        return False

    return False

sys.path.append('.')
sys.path.append(os.path.realpath('./Scripts'))
os.chdir('../..')
nxUser=imp.load_source('nxUser','./Scripts/nxUser.py') 
nxGroup=imp.load_source('nxGroup','./Scripts/nxGroup.py') 
nxFile=imp.load_source('nxFile','./Scripts/nxFile.py') 
nxScript=imp.load_source('nxScript','./Scripts/nxScript.py') 
nxService=imp.load_source('nxService','./Scripts/nxService.py') 
nxPackage=imp.load_source('nxPackage','./Scripts/nxPackage.py') 
nxSshAuthorizedKeys=imp.load_source('nxSshAuthorizedKeys','./Scripts/nxSshAuthorizedKeys.py')
nxEnvironment=imp.load_source('nxEnvironment','./Scripts/nxEnvironment.py')
nxFirewall=imp.load_source('nxFirewall','./Scripts/nxFirewall.py')
nxIPAddress=imp.load_source('nxIPAddress', './Scripts/nxIPAddress.py')
nxComputer=imp.load_source('nxComputer', './Scripts/nxComputer.py')
nxDNSServerAddress=imp.load_source('nxDNSServerAddress', './Scripts/nxDNSServerAddress.py')
nxFileLine=imp.load_source('nxFileLine', './Scripts/nxFileLine.py')
nxArchive=imp.load_source('nxArchive', './Scripts/nxArchive.py')
nxMySqlUser=imp.load_source('nxMySqlUser', './Scripts/nxMySqlUser.py')
nxMySqlGrant=imp.load_source('nxMySqlGrant', './Scripts/nxMySqlGrant.py')
nxMySqlDatabase=imp.load_source('nxMySqlDatabase', './Scripts/nxMySqlDatabase.py')
nxOMSSyslog=imp.load_source('nxOMSSyslog','./Scripts/nxOMSSyslog.py')
nxOMSPerfCounter=imp.load_source('nxOMSPerfCounter','./Scripts/nxOMSPerfCounter.py')
nxOMSCustomLog=imp.load_source('nxOMSCustomLog','./Scripts/nxOMSCustomLog.py')
nxOMSSudoCustomLog=imp.load_source('nxOMSSudoCustomLog','./Scripts/nxOMSSudoCustomLog.py')
nxOMSKeyMgmt=imp.load_source('nxOMSKeyMgmt','./Scripts/nxOMSKeyMgmt.py')
nxFileInventory=imp.load_source('nxFileInventory', './Scripts/nxFileInventory.py')
nxOMSGenerateInventoryMof=imp.load_source('nxOMSGenerateInventoryMof', './Scripts/nxOMSGenerateInventoryMof.py')
nxNPMD=imp.load_source('nxNPMD','./Scripts/nxOMSAgentNPMConfig.py')
nxOMSAutomationWorker=imp.load_source('nxOMSAutomationWorker', './Scripts/nxOMSAutomationWorker.py')

class nxUserTestCases(unittest2.TestCase):
    """
    Test cases for nxUser.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        if not os.system('grep jojoma /etc/passwd'):
            os.system('userdel -r jojoma &> /dev/null')
        if not os.system('grep jojoma /etc/group'):
            os.system('groupdel jojoma &> /dev/null')
        time.sleep(1)
        nxUser.SetShowMof(True)
        print self.id() + '\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        if not os.system('grep jojoma /etc/passwd'):
            os.system('userdel -r jojoma &> /dev/null')
        if not os.system('grep jojoma /etc/group'):
            os.system('groupdel jojoma &> /dev/null')
        time.sleep(1)

    def pswd_hash(self,pswd):
        salt=(subprocess.Popen("openssl rand -base64 3", shell=True, bufsize=100, stdout=subprocess.PIPE).stdout).readline().rstrip()
        m = hashlib.sha1()
        m.update(pswd+salt)
        return base64.b64encode(m.digest()+salt)

    def CheckInventory(self, UserName, FullName, Description, Inventory):
        if len(Inventory['__Inventory'].value) < 1:
            return False
        for i in Inventory['__Inventory'].value:
            if UserName != None and len(UserName) and not fnmatch.fnmatch(i['UserName'].value,UserName):
                print 'UserName:' + UserName + ' != ' + i['UserName'].value
                return False
            if FullName != None and len(FullName) and not fnmatch.fnmatch(i['FullName'].value,FullName):
                print 'FullName:' + FullName + ' != ' + i['FullName'].value
                return False
            if Description != None and len(Description) and not fnmatch.fnmatch(i['Description'].value,Description):
                print 'Description:' + Description + ' != ' + i['Description'].value
                return False
            print 'Inventory Matched: ' + repr(i)
        return True

    def make_MI(self,retval,UserName, Ensure, FullName, Description, Password, Disabled, PasswordChangeRequired, HomeDirectory, GroupID, UserID):
        d=dict();
        if UserName == None :
            d['UserName'] = None
        else :
            d['UserName'] = nxUser.protocol.MI_String(UserName)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxUser.protocol.MI_String(Ensure)
        if FullName == None :
            d['FullName'] = None
        else :
            d['FullName'] = nxUser.protocol.MI_String(FullName)
        if PasswordChangeRequired == None :
            d['PasswordChangeRequired'] = None
        else :
            d['PasswordChangeRequired'] = nxUser.protocol.MI_Boolean(PasswordChangeRequired)
        if Disabled == None :
            d['Disabled'] = None
        else :
            d['Disabled'] = nxUser.protocol.MI_Boolean(Disabled)
        if Description == None :
            d['Description'] = None
        else :
            d['Description'] = nxUser.protocol.MI_String(Description)
        if Password == None :
            d['Password'] = None
        else :
            d['Password'] = nxUser.protocol.MI_String(Password)
        if HomeDirectory == None :
            d['HomeDirectory'] = None
        else :
            d['HomeDirectory'] = nxUser.protocol.MI_String(HomeDirectory)
        if GroupID == None :
            d['GroupID'] = None
        else :
            d['GroupID'] = nxUser.protocol.MI_String(GroupID)
        if UserID == None :
            d['UserID'] = None
        else :
            d['UserID'] = nxUser.protocol.MI_String(UserID)
        return retval,d
    
    def testSetUserAbsentError(self):
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Absent", "", "", "", "", "", "", "" )!=
                        [0],'Set("jojoma", "Absent", "", "", "", "", "", "", "" ) should return !=[0]')

    def testSetUserPresent(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')

    def testGetUserAbsent(self):
        assert check_values(nxUser.Get_Marshall("jojoma", "absent", "", "", "", "", "", "", "" ), \
                self.make_MI(0,"jojoma", "absent", "", "", "", False, False, "", "", None))  ==  True, \
                'Get("jojoma", "", "", "", "", "", "", "", "" )[:3] should return ==[0,"jojoma","absent"]'

    def testGetUserPresent(self):
        """
        Note - GroupID is currently returned as the string representation of a number, eg - '27'
        """
        pswd=self.pswd_hash('jojoma')
        grpid=str(grp.getgrnam('mail')[2])
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", grpid )==  [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "8" ) should return == [0]')
        self.assertTrue(check_values(nxUser.Get_Marshall \
        ("jojoma", "", "", "", "", "", "", "", "" ),self.make_MI(0,"jojoma","present", \
        "JO JO MA", "JOJOMA", None, False, False, "/home/jojoma",grpid, None)), \
        'Get("jojoma", "", "", "", "", "", "", "", "" )[:3] should return ==[0,"jojoma","present", "JO JO MA", "JOJOMA", ' \
        +pswd+', False, False, "/home/jojoma", "'+grpid+'"]')
        
    def testTestUserAbsent(self):
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Absent", "", "", "", "", "", "", "" ) ==
                        [0],'Test("jojoma", "Absent", "", "", "", "", "", "", "" ) should return ==[0]')

    def testTestUserAbsentError(self):
        self.assertTrue(nxUser.Test_Marshall("root", "Absent", "", "", "", "", "", "", "" )==
                        [-1],'Test("root", "", "", "", "", "", "", "", "" ) should return ==[-1]')
        
    def testTestUserPresent(self):
        self.assertTrue(nxUser.Test_Marshall("root", "Present", "", "", "", "", "", "", "" )==
                        [0],'Test("root", "Present", "", "", "", "", "", "", "" ) should return ==[0]')

    def testTestUserPresentError(self):
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "", "", "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "", "", "", "", "", "", "" ) should return ==[-1]')

    def testTestUserFullName(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "JO JO MA", "", "", "", "", "", "" )==
                        [0],'Test("jojoma", "Present", "JO JO MA", "", "", "", "", "", "" ) should return ==[0]')

    def testTestUserDescription(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "JOJOMA", "", "", "", "", "" )==
                        [0],'Test("jojoma", "Present", "", "JOJOMA", "", "", "", "", "" ) should return ==[0]')

    def testTestUserHomeDirectory(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "", "", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "", "", False, False, "/home/jojoma", "" )==
                        [0],'Test("jojoma", "Present", "", "", "", False, False, "/home/jojoma", "" ) should return ==[0]')

    def testTestUserGroupID(self):
        pswd=self.pswd_hash('jojoma')
        grpid=str(grp.getgrnam('mail')[2])
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "", "", "", "", "", grpid )==
                        [0],'Test("jojoma", "Present", "", "", "", "", "", "", "'+ grpid+ '" ) should return ==[0]')
        
    def testTestUserPassword(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "", "", pswd, "", "", "" )==
                        [0],'Test("jojoma", "Present", "", "", "", '+pswd+', "", "", "" ) should return ==[0]')

    def testTestUserFullNameError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "JO JO MAMA", "", "", "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "JO JO MAMA", "", "", "", "", "", "" ) should return ==[-1]')

    def testTestUserDescriptionError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "NOTJOJOMA", "", "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "", "NOTJOJOMA", "", "", "", "", "" ) should return ==[-1]')

    def testTestUserHomeDirectoryError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "", "", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "", "", "", "", "/home/ojoma", "" )==
                        [-1],'Test("jojoma", "Present", "", "", "", "", "", "/home/ojoma", "" ) should return ==[-1]')

    def testTestUserGroupIDError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "", "", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "", "", "", "", "", '1200' )==
                        [-1],'Test("jojoma", "Present", "", "", "", "", "", "", 1200 ) should return ==[-1]')

    def testTestUserPasswordError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "", "", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "", "", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        pswd=self.pswd_hash('jojomama')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "", "", pswd , "", "", "", "" )==
                        [-1],'Test("jojoma", "Present", "", "", "'+pswd+'", "", "", "", "" ) should return ==[-1]')

    def testSetUserDisabled(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, True, False, "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', True, False, "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, True, False, "/home/jojoma", "" )==
                        [0],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, True, False, "/home/jojoma", "" ) should return ==[0]')
        

    def testSetUserDisabledError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, True, False, "/home/jojoma", "" )==
                        [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, True, False, "/home/jojoma", "" ) should return ==[-1]')

    def testSetUserExpired(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, True, "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, True, "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, True, "/home/jojoma", "" )==
                        [0],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, True, "/home/jojoma", "" ) should return ==[0]')

    def testSetUserExpiredError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, True, "/home/jojoma", "" )==
                        [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, True, "/home/jojoma", "" ) should return ==[-1]')

    def testSetUserNotExpiredError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, True, "/home/jojoma", "" )==
 [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, True, "/home/jojoma", "" ) should return == [0]')
        self.assertTrue(nxUser.Test_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "" )==
 [-1],'Test("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "" ) should return == [-1]')

    def testUserInventoryMarshal(self):
        d=nxUser.Inventory_Marshall("", "", "", "", "", False, False, "", "" )
        self.assertTrue(d[0] == 0,'Inventory_Marshall("", "", "", "", "", False, False, "", "" ) should return == [0]')
        print repr(d)

    def testInventoryMarshallUser(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        r=nxUser.Inventory_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", "", False, False, "", "" )
        self.assertTrue(self.CheckInventory("jojoma", "JO JO MA", "JOJOMA", r[1]) == True, \
                        'CheckInventory("jojoma", "JO JO MA", "JOJOMA", r[1]) should == True')

    def testInventoryMarshallUserFilterUserName(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        r=nxUser.Inventory_Marshall("joj*", "", "", "", "", False, False, "", "" )
        self.assertTrue(self.CheckInventory("joj*", None, None, r[1]) == True, \
                        'CheckInventory("joj*", None, None, r[1]) should == True')

    def testInventoryMarshallUserFilterFullName(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        r=nxUser.Inventory_Marshall("", "", "JO*", "", "", False, False, "", "" )
        self.assertTrue(self.CheckInventory("", "JO*", None, r[1]) == True, \
                        'CheckInventory("", "JO*", None, r[1]) should == True')

    def testInventoryMarshallUserFilterDescription(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        r=nxUser.Inventory_Marshall("", "", "", "JO*", "", False, False, "", "" )
        self.assertTrue(self.CheckInventory("", None, "JO*", r[1]) == True, \
                        'CheckInventory("", None, "JO*", r[1]) should == True')

    def testInventoryMarshallUserFilterUserNameError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        r=nxUser.Inventory_Marshall("yoj*", "", "", "", "", False, False, "", "" )
        self.assertTrue(self.CheckInventory("yoj*", None, None, r[1]) == False, \
                        'CheckInventory("yoj*", None, None, r[1]) should == False')

    def testInventoryMarshallUserFilterFullNameError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        r=nxUser.Inventory_Marshall("", "", "JO*", "", "", False, False, "", "" )
        self.assertTrue(self.CheckInventory("", "YO*", None, r[1]) == False, \
                        'CheckInventory("", "YO*", None, r[1]) should == False')

    def testInventoryMarshallUserFilterDescriptionError(self):
        pswd=self.pswd_hash('jojoma')
        self.assertTrue(nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", pswd, False, False, "/home/jojoma", "mail" )==
                        [0],'Set("jojoma", "Present", "JO JO MA", "JOJOMA", '+pswd+', False, False, "/home/jojoma", "mail" ) should return == [0]')
        r=nxUser.Inventory_Marshall("", "", "", "YO*", "", False, False, "", "" )
        self.assertTrue(self.CheckInventory("", None, "YO*", r[1]) == False, \
                        'CheckInventory("", None, "YO*", r[1]) should == False')

class nxGroupTestCases(unittest2.TestCase):
    """
    Test cases for nxGroup.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        if not os.system('grep jojomamas /etc/group &> /dev/null'):
            os.system('groupdel jojomamas &> /dev/null')
        if os.system('grep jojoma /etc/passwd'):
            os.system('useradd -m jojoma &> /dev/null')
        time.sleep(1)
        nxGroup.SetShowMof(False)
        print self.id() + '\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('userdel -r jojoma &> /dev/null')
        os.system('groupdel jojomamas &> /dev/null')
        time.sleep(1)
        nxGroup.SetShowMof(False)
        print self.id() + '\n'

    def pswd_hash(self,pswd):
        import subprocess,hashlib,base64
        salt=(subprocess.Popen("openssl rand -base64 3", shell=True, bufsize=100, stdout=subprocess.PIPE).stdout).readline().rstrip()
        m = hashlib.sha1()
        m.update(pswd+salt)
        return base64.b64encode(m.digest()+salt)

    def CheckInventory(self, GroupName, Inventory):
        if len(Inventory['__Inventory'].value) < 1:
            return False
        for i in Inventory['__Inventory'].value:
            if GroupName != None and len(GroupName) and not fnmatch.fnmatch(i['GroupName'].value,GroupName):
                print 'GroupName:' + GroupName + ' != ' + i['GroupName'].value
                return False
        print 'Inventory Matched: ' + repr(i)
        return True

    def make_MI(self,retval,GroupName, Ensure, Members, MembersToInclude, MembersToExclude, PreferredGroupID, GroupID):
        d=dict();
        if GroupName == None :
            d['GroupName'] = None
        else :
            d['GroupName'] = nxGroup.protocol.MI_String(GroupName)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxGroup.protocol.MI_String(Ensure)
        if Members == None :
            d['Members'] = None
        else :
            d['Members'] = nxGroup.protocol.MI_StringA(Members)
        if MembersToInclude == None :
            d['MembersToInclude'] = None
        else :
            d['MembersToInclude'] = nxGroup.protocol.MI_StringA(MembersToInclude)
        if MembersToExclude == None :
            d['MembersToExclude'] = None
        else :
            d['MembersToExclude'] = nxGroup.protocol.MI_StringA(MembersToExclude)
        if PreferredGroupID == None :
            d['PreferredGroupID'] = None
        else :
            d['PreferredGroupID'] = nxGroup.protocol.MI_String(PreferredGroupID)
        if GroupID == None :
            d['GroupID'] = None
        else :
            d['GroupID'] = nxGroup.protocol.MI_String(GroupID)
        return retval,d

    def testSetGroupPresent(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", ["jojoma"], "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", ["jojoma"], "", "", "1101" ) should return == [0]')

    def testSetGroupAbsent(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", ["jojoma"], "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", ["jojoma"], "", "", "1101" ) should return == [0]')
        time.sleep(1)
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Absent", ["jojoma"], "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Absent", ["jojoma"], "", "", "1101" ) should return == [0]')

    def testGetGroupAbsent(self):
        self.assertTrue(check_values(nxGroup.Get_Marshall \
        ("jojomamas", "Absent", "", "", "", ""),self.make_MI(0,"jojomamas","absent",None ,None ,None ,None ,None )), \
        'Get("jojomamas", "", "", "", "", "")[:3] should return ==[0,"jojomamas","absent"]')

    def testGetGroupPresent(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", ["jojoma"], "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", ["jojoma"], "", "", "1101" ) should return == [0]')
        
        self.assertTrue(check_values(nxGroup.Get_Marshall("jojomamas", "Present", ['jojoma'], "", "", "1101"), \
        self.make_MI(0,"jojomamas","present", ['jojoma'],None ,None , "1101" ,None )), \
                        'Get("jojomamas", "", "", "", "", "1101")[:6] should return ==[0,"jojomamas","present", "", "", "1101"]')

    def testTestGroupAbsent(self):
        self.assertTrue(nxGroup.Test_Marshall("jojomamas", "Absent", "", "", "", "") ==
                        [0],'Test("jojomamas", "Absent", "", "", "", "") should return ==[0]')

    def testTestGroupAbsentError(self):
        self.assertTrue(nxGroup.Test_Marshall("mail", "Absent", "", "", "", "")==
                        [-1],'Test("mail", "Absent", "", "", "", "") should return ==[-1]')

    def testTestGroupPresent(self):
        self.assertTrue(nxGroup.Test_Marshall("mail", "Present", "", "", "", "")==
                        [0],'Test("mail", "Present", "", "", "", "") should return ==[0]')

    def testTestGroupPresentError(self):
        self.assertTrue(nxGroup.Test_Marshall("jojomamas", "Present", "", "", "", "")==
                        [-1],'Test("jojomamas", "Present", "", "", "", "") should return ==[-1]')

    def testSetGroupPresentMembers(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", ("jojoma","root"), "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", ["jojoma","root"], "", "", "1101" ) should return == [0]')
        self.assertTrue(nxGroup.Test_Marshall("jojomamas", "Present", ("jojoma","root"), "", "", "1101")==
                        [0],'Test("jojomamas", "Present", ["jojoma","root"], "", "", "1101") should return ==[0]')

    def testSetGroupPresentMembersInclude(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", "", "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", "", "", "", "1101" ) should return == [0]')
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", "", ["jojoma"], "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", "", ["jojoma"], "", "1101" ) should return == [0]')
        self.assertTrue(nxGroup.Test_Marshall("jojomamas", "Present", ["jojoma"], "", "", "1101")==
                        [0],'Test("jojomamas", "Present", ["jojoma"], "", "", "1101") should return ==[0]')

    def testSetGroupPresentMembersExclude(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", ["jojoma","root"], "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", ("jojoma","root"), "", "", "1101" ) should return == [0]')
        # Below is a bug in nxGroup ?
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", "", "", ["jojoma"], "1101" ) ==
                        [0],'Set("jojomamas", "Present", "", "", ("jojoma"), "1101" ) should return == [0]')
        self.assertTrue(nxGroup.Test_Marshall("jojomamas", "Present", ["root"], "", "", "1101")==
                        [0],'Test("jojomamas", "Present", "root", "", "", "1101") should return ==[0]')

    def testSetGroupPresentPreferredGroupIDInUseError(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", "", "", "", "0" ) ==
                        [0],'Set("jojomamas", "Present", "", "", "", "0" ) should return == [0]')
        self.assertTrue(nxGroup.Test_Marshall("jojomamas", "Present", "", "", "", "0")==
                        [-1],'Test("jojomamas", "Present", , "", "", "0") should return ==[-1]')

    def testInventory_Marshall(self):
        d=nxGroup.Inventory_Marshall("*", "", "", "", "", "")
        print repr(d)

    def testSetInventory_MarshallFilterGroup(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", "", "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", "", "", "", "1101" ) should return == [0]')
        d=nxGroup.Inventory_Marshall("*mama*", "", "", "", "", "")
        self.assertTrue(self.CheckInventory("*mama*",d[1]) == True, 'self.CheckInventory("*mama*",d[1]) should == True')

    def testSetInventory_MarshallFilterGroupError(self):
        self.assertTrue(nxGroup.Set_Marshall("jojomamas", "Present", "", "", "", "1101" ) ==
                        [0],'Set("jojomamas", "Present", "", "", "", "1101" ) should return == [0]')
        d=nxGroup.Inventory_Marshall("*jama*", "", "", "", "", "")
        self.assertTrue(self.CheckInventory("*jama*",d[1]) == False, \
                        'self.CheckInventory("*mama*",d[1]) should == False')


class nxScriptTestCases(unittest2.TestCase):
    """
    Test cases for nxScript.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('useradd -m jojoma ')
        time.sleep(1)
        self.get_script='#!/bin/bash \ncat /tmp/testfile\n'
        self.test_script='#!/bin/bash \ngrep  "set script successfull" /tmp/testfile\n'
        self.set_script='#!/bin/bash \necho "set script successfull" > /tmp/testfile\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('userdel -r jojoma ')
        os.system('rm /tmp/testfile')
        time.sleep(1)
    
    def make_MI(self,retval,GetScript, SetScript, TestScript, User, Group, Result):
        d=dict();
        if GetScript == None :
            d['GetScript'] = None
        else :
            d['GetScript'] = nxScript.protocol.MI_String(GetScript)
        if SetScript == None :
            d['SetScript'] = None
        else :
            d['SetScript'] = nxScript.protocol.MI_String(SetScript)
        if TestScript == None :
            d['TestScript'] = None
        else :
            d['TestScript'] = nxScript.protocol.MI_String(TestScript)
        if User == None :
            d['User'] = None
        else :
            d['User'] = nxScript.protocol.MI_String(User)
        if Group == None :
            d['Group'] = None
        else :
            d['Group'] = nxScript.protocol.MI_String(Group)
        if Result == None :
            d['Result'] = None
        else :
            d['Result'] = nxScript.protocol.MI_String(Result)
        return retval,d

    def testGetScriptUser(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        r=nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        print 'GET='+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,self.get_script,self.set_script,self.test_script, "jojoma", "", "set script successfull\n" )) == True,'nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )[0] should return == 0')

    def testTestScriptUser(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        r=nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        print 'TEST='+repr(r)
        self.assertTrue(r == [0],'nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )[0] should return == 0')

    def testSetScriptUser(self):
        r=nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        print 'SET='+repr(r)
        self.assertTrue(r[0] == 0,'nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )[0] should return == 0')

    def testGetScriptGroup(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )
        r=nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )
        print 'GET='+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,self.get_script,self.set_script,self.test_script, "", "mail", "set script successfull\n" )) == True,'nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )[0] should return == 0')

    def testTestScriptGroup(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )
        r=nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )
        print 'TEST='+repr(r)
        self.assertTrue(r == [0],'nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )[0] should return == 0')

    def testSetScriptGroup(self):
        r=nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )
        print 'SET='+repr(r)
        self.assertTrue(r[0] == 0,'nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "mail" )[0] should return == 0')

    def testGetScriptUserError(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        r=nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "ojoma", "" )
        print 'GET='+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,self.get_script,self.set_script,self.test_script, "ojoma", "", "set script successfull\n") ) == False,'nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "ojoma", "" )[-1] should return == -1')

    def testTestScriptUserError(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "jojoma", "" )
        r=nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "ojoma", "" )
        print 'TEST='+repr(r)
        self.assertTrue(r == [-1],'nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "ojoma", "" )[-1] should return == -1')

    def testSetScriptUserError(self):
        r=nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "ojoma", "" )
        print 'SET='+repr(r)
        self.assertTrue(r[0] == -1,'nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "ojoma", "" )[-1] should return == -1')

    def testGetScriptGroupError(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        r=nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        print 'GET='+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,self.get_script,self.set_script,self.test_script, "", "ojoma" , "set script successfull\n")) == False,'nxScript.Get_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )[-1] should return == -1')

    def testTestScriptGroupError(self):
        nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        r=nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        print 'TEST='+repr(r)
        self.assertTrue(r == [-1],'nxScript.Test_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )[-1] should return == -1')

    def testSetScriptGroupError(self):
        r=nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )
        print 'SET='+repr(r)
        self.assertTrue(r[0] == -1,'nxScript.Set_Marshall(self.get_script,self.set_script,self.test_script, "", "ojoma" )[-1] should return == -1')


class nxPackageTestCases(unittest2.TestCase):
    """
    Test cases for nxPackage
    """
    def setUp(self):
        """
        Setup test resources
        """
        time.sleep(4)
        self.pkg = 'nano'
        if platform.dist()[0].lower() == 'suse':
            self.pkg = 'gvim'
        if os.system('which dpkg ') == 0 :
            os.system('dpkg -r ' + self.pkg + ' &> /dev/null')
            if os.path.exists('/usr/bin/dummy.sh'):
                os.system('dpkg -r dummy &> /dev/null')
            self.package_path='./Scripts/Tests/dummy-1.0.deb'
        else :
            os.system('rpm -e ' + self.pkg + ' &> /dev/null')
            if os.path.exists('/usr/bin/dummy.sh'):
                os.system('rpm -e dummy &> /dev/null')
            self.package_path='./Scripts/Tests/dummy-1.0-1.x86_64.rpm'
        time.sleep(3)
        print self.id() + '\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        time.sleep(4)
        if os.system('which dpkg ') == 0 :
            os.system('dpkg -r ' + self.pkg + ' &> /dev/null')
            if os.path.exists('/usr/bin/dummy.sh'):
                os.system('dpkg -r dummy &> /dev/null')
        else :
            os.system('rpm -e ' + self.pkg + ' &> /dev/null')
            if os.path.exists('/usr/bin/dummy.sh'):
                os.system('rpm -e dummy &> /dev/null')
        time.sleep(3)

    def CheckInventory(self, Name, Inventory):
        if len(Inventory['__Inventory'].value) < 1:
            return False
        for i in Inventory['__Inventory'].value:
            if Name != None and len(Name) and not fnmatch.fnmatch(i['Name'].value,Name):
                print 'Name:' + Name + ' != ' + i['Name'].value
                return False
            print 'Inventory Matched: ' + repr(i)
        return True

    def make_MI(self, retval, Ensure, PackageManager, Name, FilePath, PackageGroup, Arguments,
                ReturnCode,PackageDescription,Publisher,InstalledOn,Size,Version,Installed, Architecture):
        d=dict();
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxPackage.protocol.MI_String(Ensure)
        if PackageManager == None :
            d['PackageManager'] = None
        else :
            d['PackageManager'] = nxPackage.protocol.MI_String(PackageManager)
        if Name == None :
            d['Name'] = None
        else :
            d['Name'] = nxPackage.protocol.MI_String(Name)
        if FilePath == None :
            d['FilePath'] = None
        else :
            d['FilePath'] = nxPackage.protocol.MI_String(FilePath)
        if PackageGroup == None :
            d['PackageGroup'] = None
        else :
            d['PackageGroup'] = nxPackage.protocol.MI_Boolean(PackageGroup)
        if Arguments == None :
            d['Arguments'] = None
        else :
            d['Arguments'] = nxPackage.protocol.MI_String(Arguments)
        if ReturnCode == None :
            d['ReturnCode'] = None
        else :
            d['ReturnCode'] = nxPackage.protocol.MI_Uint32(ReturnCode)
        if PackageDescription == None :
            d['PackageDescription'] = None
        else:
            d['PackageDescription'] = nxPackage.protocol.MI_String(PackageDescription)
        if Publisher == None:
            d['Publisher'] = None
        else:
            d['Publisher'] = nxPackage.protocol.MI_String(Publisher)
        if InstalledOn == None:
            d['InstalledOn'] = None
        else:
            d['InstalledOn'] = nxPackage.protocol.MI_String(InstalledOn)
        if Size == None:
            d['Size'] = None
        else:
            d['Size'] = nxPackage.protocol.MI_Uint32(int(Size))
        if Version == None:
            d['Version'] = None
        else:
            d['Version'] = nxPackage.protocol.MI_String(Version)
        if Installed == None:
            d['Installed'] = None
        else:
            d['Installed'] = nxPackage.protocol.MI_Boolean(Installed)
        if Architecture == None:
            d['Architecture'] = None
        else:
            d['Architecture'] = nxPackage.protocol.MI_Boolean(Architecture)
        return retval,d
    
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
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,args,0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',True,0) should return ==[0]")
        
    def testSetEnablePathAndNameDefaultProvider(self):
        """
        Test that when Path and Name are set, Path is used.
        """
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,self.package_path,False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','dummy','','"+ self.package_path +"',False,'',0) should return ==[0]")

    def testSetEnableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")

    def testSetEnableNameExplicitProvider(self):
        pm=nxPackage.GetPackageManager()
        self.assertTrue(nxPackage.Set_Marshall('Present',pm,self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','"+pm+"','" + self.pkg + "','',False,'',0) should return ==[0]")
 
    def testSetEnableNameBadExplicitProviderError(self):
        pm=nxPackage.GetPackageManager()
        for b in ('zypper','yum','apt-get'):
            if b != pm:
                break
        self.assertTrue(nxPackage.Set_Marshall('Present',b,self.pkg,'',False,'',0)==
                        [-1],"nxPackage.Set_Marshall('Present','"+b+"','" + self.pkg + "','',False,'',0) should return ==[-1]")

    def testSetEnableNameDefaultProviderBadReturnCodeError(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',6)==
                        [-1],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[-1]")

    def testGetEnableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        r=nxPackage.Get_Marshall('Present','',self.pkg,'',False,'',0)
        print 'GET:'+repr(r)

        self.assertTrue(check_values(r,self.make_MI(0,'present', None,self.pkg,'',False,'',0,  None, None, None, None, None, None, None )) == True
                        ,"nxPackage.Get_Marshall('Present','','" + self.pkg + "','',False,'',0)[0] should return == 0")

    def testTestEnableNameDefaultProviderBadReturnCodeError(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        print 'TEST:'+repr(nxPackage.Test_Marshall('Present','',self.pkg,'',False,'',6))

        self.assertTrue(nxPackage.Test_Marshall('Present','',self.pkg,'',False,'',6)==
                        [-1],"nxPackage.Test_Marshall('Present','','" + self.pkg + "','',False,'',True,6) should return == [-1]")

    def testGetEnableNameDefaultProviderBadReturnCodeError(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        r=nxPackage.Get_Marshall('Present','',self.pkg,'',False,'',6)
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,'present', None,self.pkg,'',False,'',6,  None, None, None, None, None, None, None )) == True
                        ,"nxPackage.Get_Marshall('Present','','" + self.pkg + "','',False,'',True,6)[0] should return == 0")

    def testTestEnableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        print 'TEST:'+repr(nxPackage.Test_Marshall('Present','',self.pkg,'',False,'',0))

        self.assertTrue(nxPackage.Test_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Test_Marshall('Present','','" + self.pkg + "','',False,'',0) should return == [0]")

    @unittest2.skipUnless(os.system('which yum ') ==
                          0,'groupmode is not implemented.')
    def testSetEnableGroupDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','','Remote Desktop Clients','',True,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',True,'',0) should return ==[0]")
            
    def testSetEnablePathDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','','',self.package_path,False,'',0)==
        [0],"nxPackage.Set_Marshall('Present','','','"+ self.package_path +"',False,'',0) should return ==[0]")

    def testSetDisableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        time.sleep(4)
        self.assertTrue(nxPackage.Set_Marshall('Absent','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Absent','','" + self.pkg + "','',False,'',0) should return ==[0]")

    def testGetDisableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        time.sleep(4)
        self.assertTrue(nxPackage.Set_Marshall('Absent','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Absent','','" + self.pkg + "','',False,'',0) should return ==[0]")
        time.sleep(4)
        r=nxPackage.Get_Marshall('Absent','',self.pkg,'',False,'',0)
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,'absent', None,self.pkg,'',False,'',0, None, None, None, None, None, None, None )) == True
                        ,"nxPackage.Get_Marshall('Absent','','" + self.pkg + "','',False,'',0)[0] should return == 0")

    def testTestDisableNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        time.sleep(4)
        self.assertTrue(nxPackage.Set_Marshall('Absent','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Absent','','" + self.pkg + "','',False,'',0) should return ==[0]")
        time.sleep(4)
        print 'TEST:'+repr(nxPackage.Test_Marshall('Absent','',self.pkg,'',False,'',0))

        self.assertTrue(nxPackage.Test_Marshall('Absent','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Test_Marshall('Absent','','" + self.pkg + "','',False,'',0) should return == [0]")

    @unittest2.skipUnless(os.system('which yum ') ==
                          0,'groupmode is not implemented.')
    def testSetDisableGroupDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','','Remote Desktop Clients','',True,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',True,'',0) should return ==[0]")
        time.sleep(4)
        self.assertTrue(nxPackage.Set_Marshall('Absent','','Remote Desktop Clients','',True,'',0)==
                        [0],"nxPackage.Set_Marshall('Absent','','" + self.pkg + "','',True,'',0) should return ==[0]")
            
    def testSetDisablePathDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Absent','','',self.package_path,False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','','"+ self.package_path +"',False,'',0) should return == [0]")

    def testSetEnableBadNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','','nanoo','',False,'',0)==
                        [-1],"nxPackage.Set_Marshall('Present','','nanoo','',False,'',0) should return == [-1]")

    def testGetEnableBadNameDefaultProvider(self):
        r=nxPackage.Get_Marshall('Present','','nanoo','',False,'',0)
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,'present', None,'nanoo','',False,'',0, None, None, None, None, None, None, None )) == True
                        ,"nxPackage.Get_Marshall('Present','','nanoo','',False,'',0)[-1] should return == 0")

    def testTestEnableBadNameDefaultProvider(self):
        print 'TEST:'+repr(nxPackage.Test_Marshall('Present','','nanoo','',False,'',0))

        self.assertTrue(nxPackage.Test_Marshall('Present','','nanoo','',False,'',0)==
                        [-1],"nxPackage.Test_Marshall('Present','','nanoo','',False,'',0) should return == [-1]")

    def testSetEnableBadPathDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','','','BADPATH'+self.package_path,False,'',0)==
                        [-1],"nxPackage.Set_Marshall('Present','','','"+ 'BADPATH'+ self.package_path +"',False,'',0) should return ==[-1]")

    def testSetDisableBadNameDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Absent','','nanoo','',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Absent','','nanoo','',False,'',0) should return ==[0]")

    def testGetDisableBadNameDefaultProvider(self):
        r=nxPackage.Get_Marshall('Absent','','nanoo','',False,'',0)
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,'absent', None,'nanoo','',False,'',0, None, None, None, None, None, None, None )) == True
                        ,"nxPackage.Get_Marshall('Absent','','nanoo','',False,'',0)[0] should return == 0")

    def testTestDisableBadNameDefaultProvider(self):
        print 'TEST:'+repr(nxPackage.Test_Marshall('Absent','','nanoo','',False,'',0))

        self.assertTrue(nxPackage.Test_Marshall('Absent','','nanoo','',False,'',0)==
                        [0],"nxPackage.Test_Marshall('Absent','','nanoo','',False,'',0) should return == [0]")

    def testSetDisableBadPathDefaultProvider(self):
        self.assertTrue(nxPackage.Set_Marshall('Absent','','', 'BADPATH'+ self.package_path,False,'',0)==
                        [0],"nxPackage.Set_Marshall('Absent','','','"+  'BADPATH'+ self.package_path +"',False,'',0) should return == [0]")

    def testInventoryMarshall(self):
        r=nxPackage.Inventory_Marshall('','','*','',False,'',0)
        self.assertTrue(r[0] == 0,"Inventory_Marshall('','','*','',False,'',0)  should return == [0]")
        print repr(r[1])

    def testInventoryMarshallFilterName(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        r=nxPackage.Inventory_Marshall('', '', self.pkg, '', False, '', 0)
        self.assertTrue(self.CheckInventory(self.pkg, r[1]) == True, \
                        'CheckInventory(self.pkg, r[1]) should == True')
        pkg = self.pkg[:3]
        pkg += '*'
        r=nxPackage.Inventory_Marshall('', '',  pkg, '', False, '', 0)
        self.assertTrue(self.CheckInventory(pkg, r[1]) == True, \
                        'CheckInventory('+ pkg + ', r[1]) should == True')

    def testInventoryMarshallFilterNameError(self):
        self.assertTrue(nxPackage.Set_Marshall('Present','',self.pkg,'',False,'',0)==
                        [0],"nxPackage.Set_Marshall('Present','','" + self.pkg + "','',False,'',0) should return ==[0]")
        r=nxPackage.Inventory_Marshall('', '', self.pkg[2:], '', False, '', 0)
        self.assertTrue(self.CheckInventory(self.pkg[2:], r[1]) == False, \
                        'CheckInventory(self.pkg, r[1]) should == False')

    def testInventoryMarshallCmdlineError(self):
        os.system('cp  ./Scripts/nxPackage.py /tmp/nxPackageBroken.py')
        os.system(r'sed -i "s/\((f).*\)[0-9]/\120/" /tmp/nxPackageBroken.py')
        nxPackageBroken = imp.load_source('nxPackageBroken','/tmp/nxPackageBroken.py') 
        r=nxPackageBroken.Inventory_Marshall('','','*','',False,'',0)
        os.system('rm /tmp/nxPackageBroken.py')
        self.assertTrue(len(r[1]['__Inventory'].value) == 0,"nxPackageBroken.Inventory_Marshall('','','*','',False,'',0)  should return empty MI_INSTANCEA.")
        print repr(r[1])


class nxFileTestCases(unittest2.TestCase):
    """
    Test cases for nxFile
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('rm -rf /tmp/*pp*')
        os.system('rm -rf /tmp/Python-2.4.6.tgz')
        nxFile.SetShowMof(False)
        print self.id() + '\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('rm -rf /tmp/*pp*')
        os.system('rm -rf /tmp/Python-2.4.6.tgz')

    def make_MI(self,retval,DestinationPath, SourcePath, Ensure, Type, Force, Contents, Checksum, Recurse, Links, Owner, Group, Mode, ModifiedDate):
        d=dict();
        if DestinationPath == None :
            d['DestinationPath'] = None
        else :
            d['DestinationPath'] = nxFile.protocol.MI_String(DestinationPath)
        if SourcePath == None :
            d['SourcePath'] = None
        else :
            d['SourcePath'] = nxFile.protocol.MI_String(SourcePath)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxFile.protocol.MI_String(Ensure)
        if Type == None :
            d['Type'] = None
        else :
            d['Type'] = nxFile.protocol.MI_String(Type)
        if Force == None :
            d['Force'] = None
        else :
            d['Force'] = nxFile.protocol.MI_Boolean(Force)
        if Contents == None :
            d['Contents'] = None
        else :
            d['Contents'] = nxFile.protocol.MI_String(Contents)
        if Checksum == None :
            d['Checksum'] = None
        else :
            d['Checksum'] = nxFile.protocol.MI_String(Checksum)
        if Recurse == None :
            d['Recurse'] = None
        else :
            d['Recurse'] = nxFile.protocol.MI_Boolean(Recurse)
        if Links == None :
            d['Links'] = None
        else :
            d['Links'] = nxFile.protocol.MI_String(Links)
        if Owner == None :
            d['Owner'] = None
        else :
            d['Owner'] = nxFile.protocol.MI_String(Owner)
        if Group == None :
            d['Group'] = None
        else :
            d['Group'] = nxFile.protocol.MI_String(Group)
        if Mode == None :
            d['Mode'] = None
        else :
            d['Mode'] = nxFile.protocol.MI_String(Mode)
        if ModifiedDate == None :
            d['ModifiedDate'] = None
        else :
            d['ModifiedDate'] = nxFile.protocol.MI_Timestamp.from_time(ModifiedDate)
        return retval,d

    def testSetFileAbsent(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetFileAbsentError(self):
        self.assertTrue(nxFile.Set_Marshall("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetFileData(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/1.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)

    def testSetFileDataError(self):
        self.assertTrue(nxFile.Set_Marshall("/tp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Set_Marshall("/tp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [-1]')

    def testSetFileNoData(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/1.pp')
        self.assertTrue(len(d)==
                        0,"The contents of 1.pp should be empty.  File contents mismatch:"+d)

    def testTestCompareFilesMD5Same(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        
    def testTestCompareFilesMD5Different(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        
    def testTestCompareFilesMD5Error(self):
        self.assertTrue(nxFile.Test_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Test_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testSetFileCopy(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/12.pp", "/tmp/1.pp", "", "", "", "", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/12.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)

    def testSetDirectoryPresent(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        True,'Directory /tmp/pp is missing.')

    def testSetDirectoryAbsent(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        False,'Directory /tmp/pp is present.')

    def testSetDirectoryAbsentError(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Absent", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetCopyDirectoryToNew(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        True,'Directory /tmp/pp is missing.')
        self.assertTrue(nxFile.Set_Marshall("/tmp/ppp", "/tmp/pp", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/ppp') ==
                        True,'Directory /tmp/ppp is missing.')
        
    def testSetCopyDirectoryToExistingForce(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/pp') ==
                        True,'Directory /tmp/pp is missing.')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/pp/1.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)
        self.assertTrue(nxFile.Set_Marshall("/tmp/ppp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(os.path.isdir('/tmp/ppp') ==
                        True,'Directory /tmp/ppp is missing.')
        self.assertTrue(nxFile.Set_Marshall("/tmp/ppp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/ppp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        d,e=nxFile.ReadFile('/tmp/ppp/1.pp')
        self.assertTrue(d==
                        "These are the contents of 1.pp","File contents mismatch:"+d)
        self.assertTrue(nxFile.Set_Marshall("/tmp/ppp", "/tmp/pp", "Present", "Directory", "Force", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')

    def testSetModeRecursive(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", '755')==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", 755) should return [0]')
        self.assertTrue((nxFile.StatFile('/tmp/pp/1.pp').st_mode & 0755 ) ==
                        0755 and (nxFile.StatFile('/tmp/pp/12.pp').st_mode & 0755) == 0755,'Mode of /tmp/pp/1.pp and /tmp/pp/12.pp should be 755')

    def testSetOwnerRecursive(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp/1.pp", "", "Present", "File", "", "These are the contents of 1.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp/12.pp", "", "Present", "File", "", "These are the contents of 12.pp", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "mail", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.StatFile('/tmp/pp/1.pp').st_gid ==
                        grp.getgrnam('mail')[2]  and nxFile.StatFile('/tmp/pp/12.pp').st_gid == grp.getgrnam('mail')[2] ,'Group of /tmp/pp/1.pp and /tmp/pp/12.pp should be mail')

    def testTestNoDestPathError(self):
        self.assertTrue(nxFile.Test_Marshall("", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Test_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testTestFilePresentError(self):
        self.assertTrue(nxFile.Test_Marshall("/tp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [-1],'nxFile.Test_Marshall("/tp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testTestFilePresent(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestFileAbsentError(self):
        self.assertTrue(nxFile.Test_Marshall("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test_Marshall("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestFileAbsent(self):
        self.assertTrue(nxFile.Test_Marshall("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Test_Marshall("/tp/1.pp", "", "Absent", "File", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestDirectoryRecurseCheckOwnerError(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "udos", "", "")==
                        [-1],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "udos", "", "") should return [-1]')

    def testTestDirectoryRecurseCheckGroupError(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "mail", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "udos", "")==
                        [-1],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "udos", "") should return [-1]')

    def testTestDirectoryRecurseCheckModeError(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", '755')==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", 755) should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", '755')==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", 755) should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", '744')==
                        [-1],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", 744) should return [-1]')

    def testTestDirectoryRecurseCheckOwner(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        me =  pwd.getpwuid(os.getuid()).pw_name
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", me, "", "")==
                        [0],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryRecurseCheckGroup(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        me = grp.getgrgid(os.getgid()).gr_name
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", me, "")==
                        [0],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryRecurseCheckMode(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", '755')==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", 755) should return [0]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", '755')==
                        [0],'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", 755) should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", '755')==
                        [0],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", True, "", "", "", 755) should return [0]')

    def testGetNoDestPathError(self):
        r=nxFile.Get_Marshall("", "", "Present", "File", "", "", "md5", "", "", "", "", "")
        self.assertTrue(check_values(r,self.make_MI(0,"", "", "present", "file", False, None, "md5", False, "", "", "", "",None)) == False
                        ,'nxFile.Get_Marshall("", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [-1]')

    def testGetFilePresent(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "")[0]==
                        0,'nxFile.Set_Marshall("/tmp/1.pp", "", "Present", "File", "", "", "md5", "", "", "", "", "") should return [0]')
        r=nxFile.Get_Marshall("/tmp/1.pp", "", "present", "file", "", "", "md5", "", "", "", "", "")
        self.assertTrue(check_values(r,self.make_MI(0,"/tmp/1.pp", "", "present", "file", False, None, "md5", False, "", None, None, None, None)) == True
                        ,'nxFile.Get_Marshall("/tmp/1.pp", "", "present", "file", "", "", "md5", "", "", "", "", "") should return [0]')

    def testGetDirectoryPresent(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")[0]==
                        0,'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "","", "")==
                        [0],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        r=nxFile.Get_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")
        self.assertTrue(check_values(r,self.make_MI(0,"/tmp/pp", "", "present", "directory",  \
                        False, None, "md5", False, "", None, None, None, None)) == True
                        ,'nxFile.Get_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')

    def testTestDirectoryCheckOwnerError(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "udos", "", "")==
                        [-1],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "udos", "", "") should return [-1]')

    def testTestDirectoryCheckGroupError(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "mail", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "mail", "") should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "udos", "")==
                        [-1],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "udos", "") should return [-1]')

    def testTestDirectoryCheckOwner(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "") should return [0]')
        me =  pwd.getpwuid(os.getuid()).pw_name
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", me, "", "")==
                        [0],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryCheckGroup(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", "")==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "mail", "") should return [0]')
        me = grp.getgrgid(os.getgid()).gr_name
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", me, "")==
                        [0],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "'+me+'", "", "") should return [0]')

    def testTestDirectoryCheckMode(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", '776')==
                        [0],'nxFile.Set_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", 776) should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", '776')==
                        [0],'nxFile.Test_Marshall("/tmp/pp", "", "Present", "Directory", "", "", "md5", "", "", "", "", 776) should return [0]')

    def testRemoteFilePass(self):
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "ctime", "", "", "", "", '776') ==
               [-1],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "ctime", "", "", "", "", 776) should return [-1]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "ctime", "", "", "", "", '776') ==
               [0],'nxFile.Set(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "ctime", "", "", "", "", 776) should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "ctime", "", "", "", "", '776') ==
               [0],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "ctime", "", "", "", "", 776) should return [0]')
                                                                                             

    def testRemoteFileMtimePass(self):
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", '776') ==
               [-1],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", 776) should return [-1]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", '776') ==
               [0],'nxFile.Set(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", 776) should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", '776') ==
               [0],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", 776) should return [0]')


    def testRemoteFileMD5Pass(self):
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", '776') ==
               [-1],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", 776) should return [-1]')
        self.assertTrue(nxFile.Set_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", '776') ==
               [0],'nxFile.Set(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", 776) should return [0]')
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", '776') ==
               [0],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", 776) should return [0]')

    def testRemoteFileMtimeFail(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", '776') ==
               [0],'nxFile.Set(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", 776) should return [-1]')
        os.utime('/tmp/Python-2.4.6.tgz',(0,0))
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", '776') ==
               [-1],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "mtime", "", "", "", "", 776) should return [-1]')


    def testRemoteFileMD5Fail(self):
        self.assertTrue(nxFile.Set_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", '776') ==
                [0],'nxFile.Set(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", 776) should return [0]')
        os.system('ls >> /tmp/Python-2.4.6.tgz')
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", '776') ==
               [-1],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", 776) should return [-1]')

    def testRemoteFileBadUrl(self):
        self.assertTrue(nxFile.Test_Marshall("/tmp/Python-2.4.6.tgz",\
               "https://www.python.org/ftp/python/2.4.6/Python-2.4.6.nope", "Present", "File", "", "", "md5", "", "", "", "", '776') ==
               [-1],'nxFile.Test(_Marshall("/tmp/Python-2.4.6.tgz",'+\
               '"https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz", "Present", "File", "", "", "md5", "", "", "", "", 776) should return [-1]')


dummy_service_file=r"""#!/usr/bin/env python
from __future__ import with_statement

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
upstart_etc_default="""# To disable , set DUMMY_SERVICE_ENABLED=0
DUMMY_SERVICE_ENABLED=1
"""

upstart_init_conf="""description "dummy_service"
author "Eric Gable"
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
        pid=$( pidofproc -p $WAZD_PID $WAZD_BIN)
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
	status_of_proc -p $WAZD_PID $WAZD_BIN && exit 0 || exit $?
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

ubuntu_systemd_init_file="""
[Unit]
Description=Dummy Service
After=network.target
[Service]
Type=simple
PIDFile=/var/run/dummy_service.pid
ExecStart=/usr/bin/python /usr/sbin/dummy_service.py
ExecStop=rm -f /var/run/dummy_service.pid
KillMode=process
KillSignal=SIGKILL
TimeoutStartSec=10

[Install]
WantedBy=multi-user.target
"""


class nxServiceTestCases(unittest2.TestCase):
    """
    Test cases for nxService
    """
    def setUp(self):
        """
        Setup test resources
        """
        self.controller = None
        nxService.SetShowMof(True)
        print self.id() + '\n'
        dist=platform.dist()[0].lower()
        init_file=''
        if 'suse' in dist:
            init_file=suse_init_file
        elif 'ubuntu' in dist:
            if nxService.SystemdExists():
                init_file=ubuntu_systemd_init_file
        elif 'redhat' in dist:
            init_file=redhat_init_file
        elif 'cent' in dist:
            init_file=redhat_init_file
            if nxService.SystemdExists():
                init_file=ubuntu_systemd_init_file
        elif 'debian' in dist:
            init_file=debian_init_file
        if nxService.SystemdExists():
            self.controller='systemd'
            try:
                if 'ubuntu' in dist or 'cent' in dist:
                    nxService.WriteFile('/lib/systemd/system/dummy_service.service',init_file)
                    os.chmod('/lib/systemd/system/dummy_service.service',0744)
                else:
                    nxService.WriteFile('/etc/rc.d/dummy_service',init_file)
                    os.chmod('/etc/rc.d/dummy_service',0744)
                nxService.WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print repr(sys.exc_info())
            os.system('systemctl --system daemon-reload &> /dev/null')
        elif nxService.UpstartExists():
            self.controller='upstart'
            try:
                nxService.WriteFile('/etc/default/dummy_service',upstart_etc_default)
                os.chmod('/etc/default/dummy_service',0744)
                nxService.WriteFile('/etc/init/dummy_service.conf',upstart_init_conf)
                nxService.WriteFile('/etc/init.d/dummy_service',upstart_init_d_file)
                os.chmod('/etc/init.d/dummy_service',0744)
                nxService.WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print repr(sys.exc_info())

        elif nxService.InitExists():
            self.controller='init'
            try:
                nxService.WriteFile('/etc/init.d/dummy_service',init_file)
                os.chmod('/etc/init.d/dummy_service',0744)
                nxService.WriteFile('/usr/sbin/dummy_service.py',dummy_service_file)
                os.chmod('/usr/sbin/dummy_service.py',0744)
            except:
                print repr(sys.exc_info())
            

    def tearDown(self):
        """
        Remove test resources.
        """
        dist=platform.dist()[0].lower()
        if nxService.SystemdExists():
            os.system('systemctl disable dummy_service &> /dev/null')
            if 'ubuntu' in dist or 'debian' in dist  or 'cent' in dist:
                os.system('rm /usr/sbin/dummy_service.py /lib/systemd/system/dummy_service.' + \
                          'service /etc/systemd/system/multi-user.target.wants/dummy_service.service &> /dev/null')
            else:
                os.system('rm /usr/sbin/dummy_service.py /etc/rc.d/dummy_service &> /dev/null')
            os.system('systemctl --system daemon-reload &> /dev/null')
        elif nxService.UpstartExists():
            os.system('update-rc.d -f dummy_service remove &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/init/dummy_service.conf /etc/init.d/dummy_service /etc/default/dummy_service &> /dev/null')
        elif nxService.InitExists():
            os.system('chkconfig --del dummy_service &> /dev/null')
            os.system('rm /usr/sbin/dummy_service.py /etc/init.d/dummy_service &> /dev/null')
            
        time.sleep(1)
        os.system("ps -ef | grep -v grep | grep dummy_service | awk '{print $2}' | xargs -L1 kill &> /dev/null")

    def CheckInventory(self, Name, Controller, Enabled, State, Inventory):
        if len(Inventory['__Inventory'].value) < 1:
            return False
        for i in Inventory['__Inventory'].value:
            if Name != None and len(Name) and not fnmatch.fnmatch(i['Name'].value,Name):
                print 'Name:' + Name + ' != ' + i['Name'].value
                return False
            if Enabled is not None and Enabled != i['Enabled'].value.value:
                print 'Enabled:' + repr(Enabled) + ' != ' + repr(i['Enabled'].value.value)
                return False
            if State != None and len(State) and not fnmatch.fnmatch(i['State'].value,State):
                print 'State:' + State + ' != ' + i['State'].value
                return False
            print 'Inventory Matched: ' + repr(i)
        return True

    def make_MI(self,retval, Name, Controller, Enabled, State, Path, Description, Runlevels):
        d=dict();
        if Name == None :
            d['Name'] = None
        else :
            d['Name'] = nxService.protocol.MI_String(Name)
        if Controller == None :
            d['Controller'] = None
        else :
            d['Controller'] = nxService.protocol.MI_String(Controller)
        if Enabled == None :
            d['Enabled'] = None
        else :
            d['Enabled'] = nxService.protocol.MI_Boolean(Enabled)
        if State == None :
            d['State'] = None
        else :
            d['State'] = nxService.protocol.MI_String(State)
        if Path == None :
            d['Path'] = None
        else :
            d['Path'] = nxService.protocol.MI_String(Path)
        if Description == None :
            d['Description'] = None
        else :
            d['Description'] = nxService.protocol.MI_String(Description)
        if Runlevels == None :
            d['Runlevels'] = None
        else :
            d['Runlevels'] = nxService.protocol.MI_String(Runlevels)
        return retval,d

    def testSetEnable(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("dummy_service", controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+controller+'", True, "running") should return ==[0]')

    def testSetDisable(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("dummy_service", controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+controller+'", True, "running") should return ==[0]')
        self.assertTrue(nxService.Set_Marshall("dummy_service", controller, False, "stopped")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+controller+'", False, "stopped") should return ==[0]')

    def testSetEnableError(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("yummyservice", controller, True, "running")==
                        [-1],'nxService.Set_Marshall("yummyservice", "'+controller+'", True, "running") should return ==[-1]')

    def testSetDisableError(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("yummyservice", controller, False, "stopped")==
                        [-1],'nxService.Set_Marshall("yummyservice", "'+controller+'", False, "stopped") should return ==[-1]')

    def testGetEnable(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("dummy_service", controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+controller+'", True, "running") should return ==[0]')
        r=nxService.Get_Marshall("dummy_service", controller, True, "running")
        print repr(r[1])
        self.assertTrue(check_values(r,self.make_MI(0,"dummy_service", controller, True, "running",None,None,None)) == True
                        ,'nxService.Get_Marshall("dummy_service", "'+controller+'", True, "running") should return ==[0]')

    def testGetDisable(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("dummy_service", controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+controller+'", True, "running") should return ==[0]')
        self.assertTrue(nxService.Set_Marshall("dummy_service", controller, False, "stopped")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+controller+'", False, "stopped") should return ==[0]')
        r=nxService.Get_Marshall("dummy_service", controller, False, "stopped")
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,"dummy_service", controller, False, "stopped", None, None, None)) == True
                        ,'nxService.Get_Marshall("dummy_service", "'+controller+'", False, "stopped") should return ==[0,"dummy_service", controller, False, "stopped"]')

    def testGetEnableError(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("yummyservice", controller, True, "running")==
                        [-1],'nxService.Set_Marshall("yummyservice", "'+controller+'", True, "running") should return ==[-1]')
        r=nxService.Get_Marshall("yummyservice", controller, True, "running")
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,"yummyservice", controller, True, "running", None, None, None)) == False
                        ,'nxService.Get_Marshall("yummyservice", "'+controller+'", True, "running")[0:5] should return ==[-1,"yummyservice", controller, True, "running"]')

    def testGetDisableError(self):
        controller=self.controller
        self.assertTrue(nxService.Set_Marshall("yummyservice", controller, False, "stopped")==
                        [-1],'nxService.Set_Marshall("yummyservice", "'+controller+'", False, "stopped") should return ==[-1]')
        r=nxService.Get_Marshall("yummyservice", controller, False, "stopped")
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,"yummyservice", controller, False, "stopped", None, None, None)) == False
                        ,'nxService.Get_Marshall("yummyservice", "'+controller+'", False, "stopped")[0:5] should return ==[-1,"yummyservice", controller, False, "stopped"]')

    def testInventoryMarshall(self):
        r=nxService.Inventory_Marshall('*', self.controller, None,'')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('*', " + self.controller + ", None,'')  should return == 0")
        print repr(r[1])

    def testInventoryMarshallCmdlineError(self):
        os.system('cp  ./Scripts/nxService.py /tmp/nxServiceBroken.py')
        os.system('sed -i "s/cmd =  initd_service + \' --status-all \'/cmd =  initd_service + \' --atus-all \'/" /tmp/nxServiceBroken.py')
        os.system('sed -i "s/cmd = initd_chkconfig + \' --list \'/cmd = initd_chkconfig + \' --ist \'/" /tmp/nxServiceBroken.py')
        os.system('sed -i "s/cmd = \'initctl list\'/cmd = \'initctl ist\'/" /tmp/nxServiceBroken.py')
        os.system('sed -i "s/cmd = \'systemctl -a list-unit-files \'/cmd = \'systemctl -a ist-unit-files \'/" /tmp/nxServiceBroken.py')
        nxServiceBroken = imp.load_source('nxServiceBroken','/tmp/nxServiceBroken.py') 
        r=nxServiceBroken.Inventory_Marshall('*', self.controller, None,'')
        os.system('rm /tmp/nxServiceBroken.py')
        self.assertTrue(r[0] == -1,"nxServiceBroken.Inventory_Marshall('*', " + self.controller + ", None,'')  should return == -1")
        print repr(r[1])

    def testInventoryMarshallControllerWildcard(self):
        r=nxService.Inventory_Marshall('*', '*', None,'')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('*', '*', None,'')  should return == 0")
        print repr(r[1])

    def testInventoryMarshallControllerError(self):
        controllers = ['systemd', 'upstart', 'init']
        controllers.remove(self.controller)
        r=nxService.Inventory_Marshall('*', controllers[0], None,'')
        self.assertTrue(r[0] == -1,"Inventory_Marshall('*', " + self.controller + ", None,'')  should return == -1")
        print repr(r[1])

    def testInventoryMarshallDummyService(self):
        self.assertTrue(nxService.Set_Marshall("dummy_service", self.controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+self.controller+'", True, "running") should return ==[0]')
        r=nxService.Inventory_Marshall('dummy_service', self.controller, None,'')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('dummy_service', " + self.controller + ", None,'')  should return == 0")
        self.assertTrue(self.CheckInventory('dummy_service', self.controller, None, '', r[1]) == True, \
                        'CheckInventory("dummy_service", self.controller, None, "", r[1]) should == True')

    def testInventoryMarshallDummyServiceFilterName(self):
        self.assertTrue(nxService.Set_Marshall("dummy_service", self.controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+self.controller+'", True, "running") should return ==[0]')
        r=nxService.Inventory_Marshall('dummy?*ice', self.controller, None,'')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('dummy?*ice', " + self.controller + ", None,'')  should return == 0")
        self.assertTrue(self.CheckInventory('dummy?*ice', self.controller, None, '', r[1]) == True, \
                        'CheckInventory("dummy?*ice", ' + self.controller + ', None, "", r[1]) should == True')

    @unittest2.skipIf(nxService.UpstartExists() == True,'Not implemented in upstart')
    def testInventoryMarshallDummyServiceFilterEnabled(self):
        self.assertTrue(nxService.Set_Marshall("dummy_service", self.controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+self.controller+'", True, "running") should return ==[0]')
        r=nxService.Inventory_Marshall('dummy?*ice', self.controller, True,'')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('dummy?*ice', " + self.controller + ", True,'')  should return == 0")
        self.assertTrue(self.CheckInventory('dummy?*ice', self.controller, True, '', r[1]) == True, \
                        'CheckInventory("dummy?*ice", ' + self.controller + ', True, "", r[1]) should == True')

    def testInventoryMarshallDummyServiceFilterState(self):
        # This test inconsistantly fails on slower systems.  The sleep here reduces these failures.
        time.sleep(3)
        self.assertTrue(nxService.Set_Marshall("dummy_service", self.controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+self.controller+'", True, "running") should return ==[0]')
        r=nxService.Inventory_Marshall('dummy?*ice', self.controller, None,'running')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('dummy?*ice', " + self.controller + ", None,'running')  should return == 0")
        self.assertTrue(self.CheckInventory('dummy?*ice', self.controller, None, 'running', r[1]) == True, \
                        'CheckInventory("dummy?*ice", ' + self.controller + ', None, "running", r[1]) should == True')

    def testInventoryMarshallDummyServiceFilterNameError(self):
        # This test inconsistantly fails on slower systems.  The sleep here reduces these failures.
        time.sleep(3)
        self.assertTrue(nxService.Set_Marshall("dummy_service", self.controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+self.controller+'", True, "running") should return ==[0]')
        r=nxService.Inventory_Marshall('Gummy_service', self.controller, None,'')
        self.assertTrue(r[0] == 0, "Inventory_Marshall('Gummy_service', " + self.controller + ", None,'')  should return == 0")
        self.assertTrue(self.CheckInventory('Gummy_service', self.controller, None, '', r[1]) == False, \
                        'CheckInventory("Gummy_service", self.controller, None, "", r[1]) should == False')

    def testInventoryMarshallDummyServiceFilterEnabledError(self):
        # This test inconsistantly fails on slower systems.  The sleep here reduces these failures.
        time.sleep(3)
        self.assertTrue(nxService.Set_Marshall("dummy_service", self.controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+self.controller+'", True, "running") should return ==[0]')
        r=nxService.Inventory_Marshall('dummy?*ice', self.controller, False,'')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('dummy?*ice', " + self.controller + ", False,'')  should return == 0")
        self.assertTrue(self.CheckInventory('dummy?*ice', self.controller, False, '', r[1]) == False, \
                        'CheckInventory("dummy?*ice", ' + self.controller + ', False, "", r[1]) should == False')

    def testInventoryMarshallDummyServiceFilterStateError(self):
        # This test inconsistantly fails on slower systems.  The sleep here reduces these failures.
        time.sleep(3)
        self.assertTrue(nxService.Set_Marshall("dummy_service", self.controller, True, "running")==
                        [0],'nxService.Set_Marshall("dummy_service", "'+self.controller+'", True, "running") should return ==[0]')
        r=nxService.Inventory_Marshall('dummy?*ice', self.controller, None,'stopped')
        self.assertTrue(r[0] == 0,"Inventory_Marshall('dummy?*ice', " + self.controller + ", None,'stopped')  should return == 0")
        self.assertTrue(self.CheckInventory('dummy?*ice', self.controller, None, 'stopped', r[1]) == False, \
                        'CheckInventory("dummy?*ice", ' + self.controller + ', None, "stopped", r[1]) should == False')

    def testInventoryMarshallNoStderr(self):
        code, out = nxService.RunGetOutputNoStderr('ls -l /tmp/bad/path', False, True)
        self.assertTrue(code !=0 and len(out) == 0, "code, out = nxService.RunGetOutputNoStderr('ls -l /tmp/bad/path', False, True) \
        should be code !=0 and len(out) == 0")

 
class nxSshAuthorizedKeysTestCases(unittest2.TestCase):
    """
    Test cases for nxSshAuthorizedKeys.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        self.mykey='MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDLXp6PkCtbpV+P1gwFQWH6Ez0U83uEmS8IGnpeI8Fk8rY/vHOZzZZaxRCw+loyc342qCDIQheMOCNm5Fkevz06q757/oooiLR3yryYGKiKG1IZIiplmtsC95oKrzUSKk60wuI1mbgpMUP5LKi/Tvxes5PmkUtXfimz2qgkeUcPpQIDAQAB'
        if os.system('grep jojoma /etc/passwd'):
            nxUser.Set_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", 'badpass', False, False, "/home/jojoma", "mail" )    
        path='/home/jojoma/.ssh/authorized_keys'
        if not os.path.isfile(path):
            os.system('echo '+ self.mykey + ' > ' + path +' ; echo ' + self.mykey +' >> ' + path )
        os.system('cp -p ' + path + ' /tmp/')
        nxSshAuthorizedKeys.SetShowMof(True)
        print self.id() + '\n'

    def tearDown(self):
        """
        Remove test resources.
        """
        path='/home/jojoma/.ssh/authorized_keys'
        os.system('rm -rf ' + path)

    def make_MI(self,retval, KeyComment, Ensure, UserName, Key):
        d=dict();
        if KeyComment == None :
            d['KeyComment'] = None
        else :
            d['KeyComment'] = nxSshAuthorizedKeys.protocol.MI_String(KeyComment)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxSshAuthorizedKeys.protocol.MI_String(Ensure)
        if UserName == None :
            d['UserName'] = None
        else :
            d['UserName'] = nxSshAuthorizedKeys.protocol.MI_String(UserName)
        if Key == None :
            d['Key'] = None
        else :
            d['Key'] = nxSshAuthorizedKeys.protocol.MI_String(Key)
        return retval,d

    def testSetKeyPresentTwice(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',key) should be == [0]")
        # do this twice to prove there is no error if the same key already exists
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',key) should be == [0]")

    def testSetKeyAbsentTwice(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',key) should be == [0]")
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Absent','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Absent','jojoma',key) should be == [0]")
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Absent','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Absent','jojoma',key) should be == [0]")

    def testTestKeyPresent(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',key) should be == [0]")
        self.assertTrue(nxSshAuthorizedKeys.Test_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Test_Marshall('MyKey','Present','jojoma',key) should be == [0]")
        
    def testTestKeyPresentError(self):
        self.assertTrue(nxSshAuthorizedKeys.Test_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Test_Marshall('MyKey','Present','jojoma',key) should be == [-1]")
        
    def testGetKeyPresent(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma',key) should be == [0]")
        r=nxSshAuthorizedKeys.Get_Marshall('MyKey','Present','jojoma',self.mykey)
        self.assertTrue(check_values(r,self.make_MI(0,'MyKey','present','jojoma',self.mykey)) == True
                        ,"assert nxSshAuthorizedKeys.Get_Marshall('MyKey','Present','jojoma',key)[0] should be == 0")
        
    def testTestKeyPresentBadUser(self):
        self.assertTrue(nxSshAuthorizedKeys.Test_Marshall('MyKey','Present','jojoma',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Test_Marshall('MyKey','Present','jojoma',key) should be == [-1]")

    def testSetKeyPresentMissingKeyComment(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('','Present','jojoma',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Set_Marshall('','Present','jojoma',key) should be == [-1]")
        
    def testSetKeyPresentMissingEnsure(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','','jojoma',self.mykey) ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','','jojoma',key) should be == [0]")
        
    def testSetKeyPresentMissingUserName(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','',self.mykey) ==
                        [-1],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','',key) should be == [-1]")
        
    def testSetKeyPresentMissingKey(self):
        self.assertTrue(nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma','') ==
                        [0],"assert nxSshAuthorizedKeys.Set_Marshall('MyKey','Present','jojoma','') should be == [0]")


class nxEnvironmentTestCases(unittest2.TestCase):
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
        nxEnvironment.SetShowMof(True)
        print self.id() + '\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        print "TEARDOWN"
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
            
    def make_MI(self, retval, Name, Value, Ensure, Path):
        d=dict();
        if Name == None :
            d['Name'] = None
        else :
            d['Name'] = nxEnvironment.protocol.MI_String(Name)
        if Value == None :
            d['Value'] = None
        else :
            d['Value'] = nxEnvironment.protocol.MI_String(Value)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxEnvironment.protocol.MI_String(Ensure)
        if Path == None :
            d['Path'] = None
        else :
            d['Path'] = nxEnvironment.protocol.MI_Boolean(Path)
        return retval,d

    def testSetVarPresentTwice(self):
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) ==
                        [0],"self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [0]")
        # do this twice to prove there is no error if the same path already exists
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [0]")

    def testSetVarPresentTwoValues(self):
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) ==
                        [0],"self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [0]")
        # do this twice to prove there is no error if the same path already exists
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR2','/tmp','Present',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [0]")
        r=nxEnvironment.Get_Marshall('MYVAR','/tmp','Present',False)
        self.assertTrue(check_values(r,self.make_MI(0,'MYVAR','/tmp','present',False)) == True
                        ,"assert nxEnvironment.Get_Marshall('MYVAR','/tmp','Present',False)[0] should == [0]")
        r=nxEnvironment.Get_Marshall('MYVAR2','/tmp','Present',False)
        self.assertTrue(check_values(r,self.make_MI(0,'MYVAR2','/tmp','present',False)) == True
                        ,"assert nxEnvironment.Get_Marshall('MYVAR2','/tmp','Present',False)[0] should == [0]")

    def testSetVarAbsentTwice(self):
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [0]")
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Absent',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Absent',False) should == [0]")
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Absent',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Absent',False) should == [0]")

    def testTestVarPresent(self):
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [0]")
        self.assertTrue(nxEnvironment.Test_Marshall('MYVAR','/tmp','Present',False) ==
                        [0],"assert nxEnvironment.Test_Marshall('MYVAR','/tmp','Present',False) should == [0]")
        
    def testTestVarPresentError(self):
        self.assertTrue(nxEnvironment.Test_Marshall('MYVAR','/tp','Present',False) ==
                        [-1],"assert nxEnvironment.Test_Marshall('MYVAR','/tmp','Present',False) should == [-1]")

    def testGetVarPresent(self):
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [0]")
        r=nxEnvironment.Get_Marshall('MYVAR','/tmp','Present',False)
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,'MYVAR','/tmp','present',False)) == True
                        ,"assert nxEnvironment.Get_Marshall('MYVAR','/tmp','Present',False)[0] should == [0]")
        
    def testSetPathPresentTwice(self):
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Present',True) should == [0]")
        # do this twice to prove there is no error if the same path already exists
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Present',True) should == [0]")

    def testSetPathAbsentTwice(self):
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Present',True) should == [0]")
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Absent',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Absent',True) should == [0]")
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Absent',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Absent',True) should == [0]")

    def testTestPathPresent(self):
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Present',True) should == [0]")
        self.assertTrue(nxEnvironment.Test_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Test_Marshall('','/tmp','Present',True) should == [0]")

    def testTestPathPresentTwoValues(self):
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Present',True) should == [0]")
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp2','Present',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp2','Present',True) should == [0]")
        self.assertTrue(nxEnvironment.Test_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Test_Marshall('','/tmp','Present',True) should == [0]")
        self.assertTrue(nxEnvironment.Test_Marshall('','/tmp2','Present',True) ==
                        [0],"assert nxEnvironment.Test_Marshall('','/tmp2','Present',True) should == [0]")
        
    def testTestPathPresentError(self):
        self.assertTrue(nxEnvironment.Test_Marshall('','/tp','Present',True) ==
                        [-1],"assert nxEnvironment.Test_Marshall('','/tmp','Present',True) should == [-1]")

    def testGetPathPresent(self):
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Present',True) ==
                        [0],"assert nxEnvironment.Set_Marshall('','/tmp','Present',True) should == [0]")
        r=nxEnvironment.Get_Marshall('','/tmp','Present',True)
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,'','/tmp','present',True)) == True
                        ,"assert nxEnvironment.Get_Marshall('','/tmp','Present',True) should == [0]")
        
    def testGetPathPresentError(self):
        r=nxEnvironment.Get_Marshall('','/tp','Present',True)
        print 'GET:'+repr(r)
        self.assertTrue(check_values(r,self.make_MI(0,'','/tp','present',True)) == False
                        ,"assert nxEnvironment.Get_Marshall('','/tmp','Present',True)[0] should == [-1]")

        
    def testSetPathPresentMissingEnsure(self):
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','/tmp','',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [-1]")

        
    def testSetPathPresentMissingNamePathFalse(self):
        self.assertTrue(nxEnvironment.Set_Marshall('','/tmp','Present',False) ==
                        [-1],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [-1]")

    def testSetPathPresentMissingValue(self):
        self.assertTrue(nxEnvironment.Set_Marshall('MYVAR','','Present',False) ==
                        [0],"assert nxEnvironment.Set_Marshall('MYVAR','/tmp','Present',False) should == [-1]")


class tBag(object):
    def __init__(self,Name, FirewallType, Protocol, Ensure,
    AddressFamily, Access, State,  Direction, Position, SourceHost,
    SourcePort, DestinationHost, DestinationPort) :
        self.Name = Name
        self.FirewallType = FirewallType
        self.Protocol = Protocol
        self.Ensure = Ensure
        self.AddressFamily =AddressFamily 
        self.Access = Access
        self.State = State
        self.Direction = Direction
        self.Position = Position
        self.SourceHost = SourceHost
        self.SourcePort = SourcePort
        self.DestinationHost = DestinationHost
        self.DestinationPort = DestinationPort
 
def FirewallTypeIs():
    t=['ufw','SuSEfirewall2','firewalld','iptables']
    for f in t:
        if os.system('which ' + f) == 0:
            return f
    return 'nothing'

def IsFirewallRunning():
    if FirewallTypeIs() == 'iptables':
        return True
    cmd='ps -ef | grep -v grep | grep ' + FirewallTypeIs()
    if FirewallTypeIs() == 'SuSEfirewall2':
        cmd='rcSuSEfirewall2 status | grep running'
    return os.system(cmd)

def StartFirewall(firewall):
    if firewall == 'iptables':
        return
    t={}
    t['ufw']='yes | ufw enable '
    t['SuSEfirewall2']='SuSEfirewall2 start'
    t['firewalld']='service firewalld start'
    os.system(t[firewall])

def StopFirewall(firewall):
    if firewall == 'iptables':
        return
    t={}
    t['ufw']='ufw disable'
    t['SuSEfirewall2']='SuSEfirewall2 stop'
    t['firewalld']='service firewalld stop'
    os.system(t[firewall])


@unittest2.skipUnless(FirewallTypeIs() != 
                     'nothing','Skipping nxFirewallTestCases.  No supported firewall installed.')
class nxFirewallTestCases(unittest2.TestCase):
    """
    Test cases for nxFirewall.py
    """

    @classmethod    
    def setUpClass(cls):
        StartFirewall(FirewallTypeIs())

    @classmethod
    def tearDownClass(cls):
        StopFirewall(FirewallTypeIs())
    
    def setUp(self):
        """
        Setup test resources
        """
        print self.id() + '\n'
        self.FirewallType=FirewallTypeIs()
        self.min_rule={}
        self.min_rule['Name'] = "rule1"
        self.min_rule['InterfaceName'] = "eth1"
        self.min_rule['FirewallType'] = self.FirewallType
        self.min_rule['Protocol'] = ""
        self.min_rule['Ensure'] = "Present"
        self.min_rule['AddressFamily'] = ""
        self.min_rule['Access'] = "Allow"
        self.min_rule['State'] = ""
        self.min_rule['Direction'] = "INPUT"
        self.min_rule['Position'] = ""
        self.min_rule['SourceHost'] = ""
        self.min_rule['SourcePort'] = "22"
        self.min_rule['DestinationHost'] = ""
        self.min_rule['DestinationPort'] = ""
        self.max_rule={}
        self.max_rule['Name'] = "rule1"
        self.max_rule['InterfaceName'] = "eth1"
        self.max_rule['FirewallType'] = self.FirewallType
        self.max_rule['Protocol'] = "tcp"
        self.max_rule['Ensure'] = "Present"
        self.max_rule['AddressFamily'] = "IPv4"
        self.max_rule['Access'] = "Allow"
        self.max_rule['State'] = ["NEW" , "RELATED"]
        self.max_rule['Direction'] = "INPUT"
        self.max_rule['Position'] = "top"
        self.max_rule['SourceHost'] = "0.0.0.0"
        self.max_rule['SourcePort'] = "22"
        self.max_rule['DestinationHost'] = "0.0.0.1"
        self.max_rule['DestinationPort'] = "22"

    def tearDown(self):
        """
        Remove test resources.
        """
        self.max_rule['Ensure'] = "Absent"
        nxFirewall.Set_Marshall(**self.max_rule)
        self.min_rule['Ensure'] = "Absent"
        nxFirewall.Set_Marshall(**self.min_rule)
        
    def make_MI(self,retval,Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
                Access, State,  Direction, Position, SourceHost, SourcePort,
                DestinationHost, DestinationPort):
        d=dict();
        if Name == None :
            d['Name'] = None
        else :
            d['Name'] = nxFirewall.protocol.MI_String(Name)
        if InterfaceName == None :
            d['InterfaceName'] = None
        else :
            d['InterfaceName'] = nxFirewall.protocol.MI_String(InterfaceName)
        if FirewallType == None :
            d['FirewallType'] = None
        else :
            d['FirewallType'] = nxFirewall.protocol.MI_String(FirewallType)
        if Protocol == None :
            d['Protocol'] = None
        else :
            d['Protocol'] = nxFirewall.protocol.MI_String(Protocol)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxFirewall.protocol.MI_String(Ensure)
        if AddressFamily == None :
            d['AddressFamily'] = None
        else :
            d['AddressFamily'] = nxFirewall.protocol.MI_String(AddressFamily)
        if Access == None :
            d['Access'] = None
        else :
            d['Access'] = nxFirewall.protocol.MI_String(Access)
        if State == None :
            d['State'] = None
        else :
            d['State'] = nxFirewall.protocol.MI_StringA(State)
        if Direction == None :
            d['Direction'] = None
        else :
            d['Direction'] = nxFirewall.protocol.MI_String(Direction)
        if Position == None :
            d['Position'] = None
        else :
            d['Position'] = nxFirewall.protocol.MI_String(Position)
        if SourceHost == None :
            d['SourceHost'] = None
        else :
            d['SourceHost'] = nxFirewall.protocol.MI_String(SourceHost)
        if SourcePort == None :
            d['SourcePort'] = None
        else :
            d['SourcePort'] = nxFirewall.protocol.MI_String(SourcePort)
        if DestinationHost == None :
            d['DestinationHost'] = None
        else :
            d['DestinationHost'] = nxFirewall.protocol.MI_String(DestinationHost)
        if DestinationPort == None :
            d['DestinationPort'] = None
        else :
            d['DestinationPort'] = nxFirewall.protocol.MI_String(DestinationPort)
        return retval,d

    def testTestPassMaxArgs(self):
        nxFirewall.Set_Marshall(**self.max_rule)
        self.assertTrue(nxFirewall.Test_Marshall(**self.max_rule) ==
        [0],"self.assertTrue(nxFirewall.Test_Marshall(" + repr(self.max_rule) + ") should == [0]")
        
    def testTestFailMaxArgs(self):
        nxFirewall.Set_Marshall(**self.max_rule)
        self.bag=dict(self.max_rule)
        self.bag['Direction'] = 'output'
        self.assertTrue(nxFirewall.Test_Marshall(**self.bag) ==
        [-1],"self.assertTrue(nxFirewall.Test_Marshall(" + repr(self.bag) + ") should == [-1]")

    def testTestPassMinArgs(self):
        nxFirewall.Set_Marshall(**self.min_rule)
        self.bag=dict(self.min_rule)
        self.assertTrue(nxFirewall.Test_Marshall(**self.bag) ==
        [0],"self.assertTrue(nxFirewall.Test_Marshall(" + repr(self.bag) + ") should == [0]")

    def testTestFailMinArgs(self):
        nxFirewall.Set_Marshall(**self.min_rule)
        self.bag=dict(self.min_rule)
        self.bag['Direction'] = 'output'
        self.assertTrue(nxFirewall.Test_Marshall(**self.bag) ==
                        [-1],"self.assertTrue(nxFirewall.Test_Marshall(" + repr(self.bag) + ") should == [-1]")
        

class nxIPAddressTestCases(unittest2.TestCase):
    """
    Test cases for nxIPAddress.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        pass
    
    def tearDown(self):
        """
        Remove test resources.
        """
        pass
    
    def make_MI(self,retval,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        d=dict()
        d.clear()
        if IPAddress == None :
            d['IPAddress'] = None
        else :
            d['IPAddress'] = nxIPAddress.protocol.MI_String(IPAddress)
        if InterfaceName == None :
            d['InterfaceName'] = None
        else :
            d['InterfaceName'] = nxIPAddress.protocol.MI_String(InterfaceName)
        if BootProtocol == None :
            d['BootProtocol'] = None
        else :
            d['BootProtocol'] = nxIPAddress.protocol.MI_String(BootProtocol)
        if DefaultGateway == None :
            d['DefaultGateway'] = None
        else :
            d['DefaultGateway'] = nxIPAddress.protocol.MI_String(DefaultGateway)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxIPAddress.protocol.MI_String(Ensure)
        if PrefixLength == None :
            d['PrefixLength'] = None
        else :
            d['PrefixLength'] = nxIPAddress.protocol.MI_Uint32(PrefixLength)
        if AddressFamily == None :
            d['AddressFamily'] = None
        else :
            d['AddressFamily'] = nxIPAddress.protocol.MI_String(AddressFamily)
        return retval,d
    
    def testSetIPAddressV4Dynamic(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V4_dynamic.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetIPAddressV4Dynamic(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V4_dynamic.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxIPAddress.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    def testSetIPAddressV4Static(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V4_static.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetIPAddressV4Static(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V4_static.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxIPAddress.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    def testSetIPAddressV6Dynamic(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V6_dynamic.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetIPAddressV6Dynamic(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V6_dynamic.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxIPAddress.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    def testSetIPAddressV6Static(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V6_static.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetIPAddressV6Static(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxIPAddress_eth1_V6_static.mof')
        self.assertTrue(nxIPAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxIPAddress.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')


class nxComputerTestCases(unittest2.TestCase):
    """
    Test cases for nxComputer.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('cp /etc/localtime /etc/localtime.bak;'+
                  'date +%Z > /etc/lastdate;' +
                  'cp /etc/hostname /etc/hostname.bak;' +
                  'cp /etc/hosts /etc/hosts.bak')
        
    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('mv /etc/localtime.bak /etc/localtime')
        os.environ['TZ'] = open('/etc/lastdate').read()
        time.tzset()
        os.system('mv /etc/hostname.bak /etc/hostname;' +
                  'mv /etc/hosts.bak /etc/hosts')
        os.system('cat /etc/hostname | xargs hostname')
        time.sleep(1)
        
    def make_MI(self,retval,Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
        d=dict()
        d.clear()
        if Name == None :
            d['Name'] = None
        else :
            d['Name'] = nxComputer.protocol.MI_String(Name)
        if DNSDomainName == None :
            d['DNSDomainName'] = None
        else :
            d['DNSDomainName'] = nxComputer.protocol.MI_String(DNSDomainName)
        if TimeZoneName == None :
            d['TimeZoneName'] = None
        else :
            d['TimeZoneName'] = nxComputer.protocol.MI_String(TimeZoneName)
        if AlternateTimeZoneName == None :
            d['AlternateTimeZoneName'] = None
        else :
            d['AlternateTimeZoneName'] = nxComputer.protocol.MI_String(AlternateTimeZoneName)
        return retval,d
    
    def testSetComputerNameTimeZone(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxComputer.mof')
        self.assertTrue(nxComputer.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetComputerNameTimeZone(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxComputer.mof')
        self.assertTrue(nxComputer.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        d['AlternateTimeZoneName']=''
        self.assertTrue(check_values(nxComputer.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')


class nxDNSServerAddressTestCases(unittest2.TestCase):
    """
    Test cases for nxDNSServerAddress.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        print self.id() + '\n'
        dist=nxDNSServerAddress.GetMyDistro()
        os.system('cp ' + dist.file + ' ' + dist.file + '.bak')

    def tearDown(self):
        """
        Remove test resources.
        """
        dist=nxDNSServerAddress.GetMyDistro()
        os.system('mv ' + dist.file + '.bak' + ' ' + dist.file)

    def make_MI(self,retval,Address,Ensure,AddressFamily):
        d=dict();
        d.clear()
        if Address == None :
            d['Address'] = None
        else :
            d['Address'] = nxDNSServerAddress.protocol.MI_StringA(Address)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxDNSServerAddress.protocol.MI_String(Ensure)
        if AddressFamily == None :
            d['AddressFamily'] = None
        else :
            d['AddressFamily'] = nxDNSServerAddress.protocol.MI_String(AddressFamily)
        return retval,d
    
    def testSetDNSServerAddressPresent(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxDNSServerAddress_add.mof')
        self.assertTrue(nxDNSServerAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

    def testGetDNSServerAddressPresent(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxDNSServerAddress_add.mof')
        self.assertTrue(nxDNSServerAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        print "HERE "+repr(nxDNSServerAddress.Get_Marshall(**d))
        self.assertTrue(check_values(nxDNSServerAddress.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return [0,'+ repr(d) + ']')

    def testGetDNSServerAddressAbsent(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxDNSServerAddress_add.mof')
        self.assertTrue(nxDNSServerAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        d['Ensure']='Absent'
        self.assertTrue(nxDNSServerAddress.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxDNSServerAddress.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return [0,'+ repr(d) + ']')


class nxFileLineTestCases(unittest2.TestCase):
    """
    Test cases for nxFileLine.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('echo "joe is coolest" >  /tmp/joe.txt') 
        print self.id() + '\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        pass

    def make_MI(self,retval,FilePath, DoesNotContainPattern, ContainsLine):
        d=dict()
        d.clear()
        if FilePath == None :
            d['FilePath'] = None
        else :
            d['FilePath'] = nxFileLine.protocol.MI_String(FilePath)
        if DoesNotContainPattern == None :
            d['DoesNotContainPattern'] = None
        else :
            d['DoesNotContainPattern'] = nxFileLine.protocol.MI_String(DoesNotContainPattern)
        if ContainsLine == None :
            d['ContainsLine'] = None
        else :
            d['ContainsLine'] = nxFileLine.protocol.MI_String(ContainsLine)
        return retval,d
    
    def testSetFileLinePresent(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxFileLine_add.mof')
        self.assertTrue(nxFileLine.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

    def testGetFileLine(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxFileLine_add.mof')
        self.assertTrue(nxFileLine.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxFileLine.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return [0,'+ repr(d) + ']')


class nxArchiveTestCases(unittest2.TestCase):
    """
    Test cases for nxArchive.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        if not os.path.exists('/tmp/src.tar.gz') or not os.path.exists('/tmp/src.zip'):
            os.system('cp ./Scripts/Tests/test_mofs/src* /tmp/') 
        print self.id() + '\n'
        
    def tearDown(self):
        """
        Remove test resources.
        """
        pass

    def make_MI(self,retval,DestinationPath, SourcePath, Ensure, Force, Checksum):
        d=dict();
        
        if DestinationPath == None :
            d['DestinationPath'] = None
        else :
            d['DestinationPath'] = nxArchive.protocol.MI_String(DestinationPath)
        if SourcePath == None :
            d['SourcePath'] = None
        else :
            d['SourcePath'] = nxArchive.protocol.MI_String(SourcePath)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxArchive.protocol.MI_String(Ensure)
        if Force == None :
            d['Force'] = None
        else :
            d['Force'] = nxArchive.protocol.MI_Boolean(Force)
        if Checksum == None :
            d['Checksum'] = None
        else :
            d['Checksum'] = nxArchive.protocol.MI_String(Checksum)
        return retval,d

    def testSetTarArchivePresent(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxArchive_tar_ctime_test.mof')
        self.assertTrue(nxArchive.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

    def testSetZipArchivePresent(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxArchive_zip_ctime_test.mof')
        self.assertTrue(nxArchive.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')


@unittest2.skipUnless(os.system('ps -ef | grep -v grep | grep mysqld') ==
                      0,'Skipping nxMySqlUserTestCases.   mysqld is not running.')
class nxMySqlUserTestCases(unittest2.TestCase):
    """
    Test cases for nxMySqlUser.py
    """
    def drop(self):
        Name = 'jojoma'
        cmd = "DROP USER " + Name + ";"
        cmd='mysql -u root -e "' + cmd + ' FLUSH PRIVILEGES;"'
        os.environ['MYSQL_PWD'] = 'root'
        os.system(cmd)
        os.environ['MYSQL_PWD'] = ''

    def setUp(self):
        """
        Setup test resources
        """
        self.drop()
        
    def tearDown(self):
        """
        Remove test resources.
        """
        self.drop()

        
    def make_MI(self,retval,Name, Credential,  ConnectionCredential, Ensure):
        d=dict()
        d.clear()
        if Name == None :
            d['Name'] = None
        else :
            d['Name'] = nxMySqlUser.protocol.MI_String(Name)
        if Credential == None :
            d['Credential'] = None
        else :
            d['Credential'] = nxMySqlUser.protocol.MI_String(Credential)
        if ConnectionCredential == None :
            d['ConnectionCredential'] = None
        else :
            d['ConnectionCredential'] = nxMySqlUser.protocol.MI_String(ConnectionCredential)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxMySqlUser.protocol.MI_String(Ensure)
        return retval,d
    
    def testSetMySqlUser_add(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_add.mof')
        self.assertTrue(nxMySqlUser.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetMySqlUser_add(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_add.mof')
        self.assertTrue(nxMySqlUser.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxMySqlUser.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    def testSetMySqlUser_del(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_del.mof')
        self.assertTrue(nxMySqlUser.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetMySqlUser_del(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_del.mof')
        self.assertTrue(nxMySqlUser.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxMySqlUser.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    def testSetMySqlUser_upd(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_upd.mof')
        self.assertTrue(nxMySqlUser.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetMySqlUser_upd(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_upd.mof')
        self.assertTrue(nxMySqlUser.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxMySqlUser.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')


@unittest2.skipUnless(os.system('ps -ef | grep -v grep | grep mysqld') ==
                      0,'Skipping nxMySqlDatabaseTestCases.   mysqld is not running.')
class nxMySqlDatabaseTestCases(unittest2.TestCase):
    """
    Test cases for nxMySqlDatabase.py
    """

    def drop(self):
        Name = 'jojoma'
        cmd = "DROP DATABASE " + Name + ";"
        cmd='mysql -u root -e "' + cmd + '"'
        os.environ['MYSQL_PWD'] = 'root'
        os.system(cmd)
        os.environ['MYSQL_PWD'] = ''

    def setUp(self):
        """
        Setup test resources
        """
        self.drop()
        
    def tearDown(self):
        """
        Remove test resources.
        """
        self.drop()
        
    def make_MI(self,retval,Name, ConnectionCredential, Ensure):
        d=dict()
        d.clear()
        if Name == None :
            d['Name'] = None
        else :
            d['Name'] = nxMySqlDatabase.protocol.MI_String(Name)
        if ConnectionCredential == None :
            d['ConnectionCredential'] = None
        else :
            d['ConnectionCredential'] = nxMySqlDatabase.protocol.MI_String(ConnectionCredential)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxMySqlDatabase.protocol.MI_String(Ensure)
        return retval,d
    
    def testSetMySqlDatabase_add(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlDatabase_add.mof')
        self.assertTrue(nxMySqlDatabase.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetMySqlDatabase_add(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlDatabase_add.mof')
        self.assertTrue(nxMySqlDatabase.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxMySqlDatabase.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    def testSetMySqlDatabase_del(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlDatabase_del.mof')
        self.assertTrue(nxMySqlDatabase.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetMySqlDatabase_del(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlDatabase_del.mof')
        self.assertTrue(nxMySqlDatabase.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxMySqlDatabase.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')


@unittest2.skipUnless(os.system('ps -ef | grep -v grep | grep mysqld') ==
                      0,'Skipping nxMySqlGrantTestCases.   mysqld is not running.')
class nxMySqlGrantTestCases(unittest2.TestCase):
    """
    Test cases for nxMySqlGrant.py
    """
    def revoke(self):
        UserName="jojoma"
        Host="127.0.0.1"
        DatabaseName = "jojoma"
        PermissionType = "ALL PRIVILEGES"
        cmd = "REVOKE "+ PermissionType + " ON " + DatabaseName + ".* FROM '" + UserName+"'@'" + Host  + "';"
        cmd='mysql -u root -e "' + cmd + ' FLUSH PRIVILEGES;"'
        os.environ['MYSQL_PWD'] = 'root'
        os.system(cmd)
        os.environ['MYSQL_PWD'] = ''

    def setUp(self):
        """
        Setup test resources
        """
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlDatabase_add.mof')
        nxMySqlDatabase.Set_Marshall(**d)
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_add.mof')
        nxMySqlUser.Set_Marshall(**d)
        self.revoke()
        
    def tearDown(self):
        """
        Remove test resources.
        """
        self.revoke()
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlDatabase_del.mof')
        nxMySqlDatabase.Set_Marshall(**d)
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlUser_del.mof')
        nxMySqlUser.Set_Marshall(**d)
        
    def make_MI(self,retval,UserName, DatabaseName, ConnectionCredential, PermissionType, Ensure):
        d=dict()
        d.clear()
        if UserName == None :
            d['UserName'] = None
        else :
            d['UserName'] = nxMySqlGrant.protocol.MI_String(UserName)
        if UserName == None :
            d['DatabaseName'] = None
        else :
            d['DatabaseName'] = nxMySqlGrant.protocol.MI_String(DatabaseName)
        if ConnectionCredential == None :
            d['ConnectionCredential'] = None
        else :
            d['ConnectionCredential'] = nxMySqlGrant.protocol.MI_String(ConnectionCredential)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxMySqlGrant.protocol.MI_String(Ensure)
        if PermissionType == None :
            d['PermissionType'] = None
        else :
            d['PermissionType'] = nxMySqlGrant.protocol.MI_String(PermissionType)
        return retval,d
    
    def testSetMySqlGrant_add(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlGrant_add.mof')
        self.assertTrue(nxMySqlGrant.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetMySqlGrant_add(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlGrant_add.mof')
        self.assertTrue(nxMySqlGrant.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxMySqlGrant.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    def testSetMySqlGrant_del(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlGrant_del.mof')
        self.assertTrue(nxMySqlGrant.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetMySqlGrant_del(self):
        d=ParseMOF('./Scripts/Tests/test_mofs/nxMySqlGrant_del.mof')
        self.assertTrue(nxMySqlGrant.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(check_values(nxMySqlGrant.Get_Marshall(**d), \
        self.make_MI(0,**d))  ==  True, \
        'Get('+repr(d)+' should return ==['+repr(d)+']')

    
@unittest2.skipUnless(os.system('ps -ef | grep -v grep | grep omsagent') ==
                      0,'Skipping nxOMSSyslogTestCases.   omsagent is not running.')
class nxOMSSyslogTestCases(unittest2.TestCase):
    """
    Test cases for nxOMSSyslog.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        if os.path.exists('/etc/rsyslog.d/95-omsagent.conf'):
            os.system('cp /etc/rsyslog.d/95-omsagent.conf /etc/rsyslog.d/95-omsagent.conf.bak')
            os.system('cp /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf.bak')
        elif os.path.exists('/etc/rsyslog.conf'):
            os.system('cp /etc/rsyslog.conf /etc/rsyslog.conf.bak')
            os.system('cp /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf.bak')
        elif os.path.exists('/etc/syslog.conf'):
            os.system('cp /etc/syslog.conf /etc/syslog.conf.bak')
            os.system('cp /etc/opt/omi/conf/omsconfig/sysklog-oms.conf /etc/opt/omi/conf/omsconfig/sysklog-oms.conf.bak')
        elif os.path.exists('/etc/syslog-ng/syslog-ng.conf'):
            os.system('cp /etc/syslog-ng/syslog-ng.conf /etc/syslog-ng/syslog-ng.conf.bak')
            os.system('cp /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf.bak')            

    def tearDown(self):
        """
        Remove test resources.
        """
        if os.path.exists('/etc/rsyslog.d/95-omsagent.conf'):
            os.system('mv /etc/rsyslog.d/95-omsagent.conf.bak /etc/rsyslog.d/95-omsagent.conf')
            os.system('mv /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf.bak /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf')
        elif os.path.exists('/etc/rsyslog.conf'):
            os.system('mv /etc/rsyslog.conf.bak /etc/rsyslog.conf')
            os.system('mv /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf.bak /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf')
        elif os.path.exists('/etc/syslog.conf'):
            os.system('mv /etc/syslog.conf.bak /etc/syslog.conf')
            os.system('mv /etc/opt/omi/conf/omsconfig/sysklog-oms.conf.bak /etc/opt/omi/conf/omsconfig/sysklog-oms.conf')
        elif os.path.exists('/etc/syslog-ng/syslog-ng.conf'):
            os.system('mv /etc/syslog-ng/syslog-ng.conf.bak /etc/syslog-ng/syslog-ng.conf')
            os.system('mv /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf.bak /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf')            
        
    def make_MI(self,retval,SyslogSource):
        d=dict()
        d.clear()
        if SyslogSource == None :
            d['SyslogSource'] = None
        else :
            for source in SyslogSource:
                source['Severities'] = nxOMSSyslog.protocol.MI_StringA(source['Severities'])
                source['Facility']=nxOMSSyslog.protocol.MI_String(source['Facility'])
            d['SyslogSource'] = nxOMSSyslog.protocol.MI_InstanceA(SyslogSource)
        return retval,d
    
    def testSetOMSSyslog_add(self):
        d={'SyslogSource': [{'Facility': 'kern','Severities': ['emerg','crit','warning']},{'Facility': 'auth','Severities': ['emerg','crit','warning']}] }
        self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testTestSetOMSSyslog_add(self):
        d={'SyslogSource': [{'Facility': 'kern','Severities': ['emerg','crit','warning']},{'Facility': 'auth','Severities': ['emerg','crit','warning']}] }
        self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set_Marshall('+repr(d)+') should return == [0]') 
        self.assertTrue(nxOMSSyslog.Test_Marshall(**d) == [0],'Test_Marshall('+repr(d)+') should return == [0]') 

    def testGetOMSSyslog_add(self):
        d={'SyslogSource': [{'Facility': 'auth','Severities': ['crit','emerg','warning']},{'Facility': 'kern','Severities': ['crit','emerg','warning']}] }
        e=copy.deepcopy(d)
        t=copy.deepcopy(d)
        self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        m=self.make_MI(0,**e)
        g=nxOMSSyslog.Get_Marshall(**t)
        print 'GET '+ repr(g) 
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')

    def testSetOMSSyslog_del(self):
        d={'SyslogSource': [{'Facility': 'kern','Severities': None },{'Facility': 'auth','Severities': None }] }
        self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetOMSSyslog_del(self):
        d={'SyslogSource': [{'Facility': 'auth','Severities': None },{'Facility': 'kern','Severities': None }] }
        e=copy.deepcopy(d)
        t=copy.deepcopy(d)
        self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        m=self.make_MI(0,**t)
        g=nxOMSSyslog.Get_Marshall(**e)
        print 'GET '+ repr(g)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')

    def testTestSetOMSSyslog_addSysklogd(self):
        sysklogd_exists = False
        if not os.path.exists('/etc/syslog.conf'):
            os.system('touch /etc/syslog.conf')
        else:
            sysklogd_exists = True
        d={'SyslogSource': [{'Facility': 'kern','Severities': ['emerg','crit','warning']},{'Facility': 'auth','Severities': ['emerg','crit','warning']}] }
        self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set_Marshall('+repr(d)+') should return == [0]') 
        self.assertTrue(nxOMSSyslog.Test_Marshall(**d) == [0],'Test_Marshall('+repr(d)+') should return == [0]') 
        g=nxOMSSyslog.Get_Marshall(**d)
        print 'GET '+ repr(g) 
        self.assertTrue(g[0] == 0 and g[1]["SyslogSource"].value == [], \
       'Get('+repr(g)+' should return g[0] == 0 and g[1]["SyslogSource"].value == []')
        if sysklogd_exists == False:
            os.system('rm /etc/syslog.conf')


@unittest2.skipUnless(os.system('ps -ef | grep -v grep | grep omsagent') ==
                      0,'Skipping nxOMSPerfCounterTestCases.   omsagent is not running.')
class nxOMSPerfCounterTestCases(unittest2.TestCase):
    """
    Test cases for nxOMSPerfCounter.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        os.system('cp /etc/opt/microsoft/omsagent/conf/omsagent.conf /etc/opt/microsoft/omsagent/conf/omsagent.conf.bak')

    def tearDown(self):
        """
        Remove test resources.
        """
        os.system('mv /etc/opt/microsoft/omsagent/conf/omsagent.conf.bak /etc/opt/microsoft/omsagent/conf/omsagent.conf')            

        
    def make_MI(self, retval, Name, HeartbeatIntervalSeconds, PerfCounterObject):
        d=dict()
        d.clear()
        if PerfCounterObject == None :
            d['PerfCounterObject'] = None
        else :
            for perf in PerfCounterObject:
                perf['PerformanceCounter'] =  nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
                perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
                perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
                perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
                perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
            d['PerfCounterObject'] = nxOMSPerfCounter.protocol.MI_InstanceA(PerfCounterObject)
        d['HeartbeatIntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(HeartbeatIntervalSeconds)
        d['Name']=nxOMSPerfCounter.protocol.MI_String(Name)
        return retval,d
    
    def testSetOMSPerfCounter_add(self):
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        self.assertTrue(nxOMSPerfCounter.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetOMSPerfCounter_add(self):
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        e=copy.deepcopy(d)
        t={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        self.assertTrue(nxOMSPerfCounter.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        m=self.make_MI(0,**t)
        g=nxOMSPerfCounter.Get_Marshall(**e)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')

    def testSetOMSPerfCounter_del(self):
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        self.assertTrue(nxOMSPerfCounter.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetOMSPerfCounter_del(self):
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        self.assertTrue(nxOMSPerfCounter.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[]}
        m=self.make_MI(0,**t)
        g=nxOMSPerfCounter.Get_Marshall(**d)
        print 'GET '+ repr(g)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')

    def testSetOMSPerfCounter_add_missing_conf_file(self):
        os.system('rm /etc/opt/microsoft/omsagent/conf/omsagent.conf')
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        self.assertTrue(nxOMSPerfCounter.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testSetGetOMSPerfCounter_add_missing_conf_file(self):
        os.system('rm /etc/opt/microsoft/omsagent/conf/omsagent.conf')
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        e=copy.deepcopy(d)
        t={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        self.assertTrue(nxOMSPerfCounter.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        m=self.make_MI(0,**t)
        g=nxOMSPerfCounter.Get_Marshall(**e)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')

    def testGetOMSPerfCounter_add_missing_conf_file(self):
        os.system('rm /etc/opt/microsoft/omsagent/conf/omsagent.conf')
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        t={'Name':'testPerfCounter','HeartbeatIntervalSeconds':None,'PerfCounterObject':[]}
        m=self.make_MI(0,**t)
        g=nxOMSPerfCounter.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')

    def testTestOMSPerfCounter_add_missing_conf_file(self):
        os.system('rm /etc/opt/microsoft/omsagent/conf/omsagent.conf')
        d={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        for perf in d['PerfCounterObject']:
            perf['PerformanceCounter'] = nxOMSPerfCounter.protocol.MI_StringA(perf['PerformanceCounter'])
            perf['InstanceName']=nxOMSPerfCounter.protocol.MI_String(perf['InstanceName'])
            perf['AllInstances']=nxOMSPerfCounter.protocol.MI_Boolean(perf['AllInstances'])
            perf['IntervalSeconds']=nxOMSPerfCounter.protocol.MI_Uint16(perf['IntervalSeconds'])
            perf['ObjectName']=nxOMSPerfCounter.protocol.MI_String(perf['ObjectName'])
        e=copy.deepcopy(d)
        t={'Name':'testPerfCounter','HeartbeatIntervalSeconds':600,'PerfCounterObject':[{'InstanceName':'*', 'IntervalSeconds':600, 'AllInstances':True,
            'PerformanceCounter':['FreeMegabytes','PercentFreeSpace','PercentUsedSpace','PercentFreeInodes',
            'PercentUsedInodes','BytesPerSecond','ReadBytesPerSecond','WriteBytesPerSecond'],
            'ObjectName':'Logical Disk'},{'InstanceName':'*', 'IntervalSeconds':60, 'AllInstances':True,
            'PerformanceCounter':['% Processor Time','% DPC Time','% Idle Time','% Nice Time'],
            'ObjectName':'Processor'}]}
        self.assertTrue(nxOMSPerfCounter.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        m=self.make_MI(0,**t)
        g=nxOMSPerfCounter.Get_Marshall(**e)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')

@unittest2.skipUnless(os.system('ps -ef | grep -v grep | grep omsagent') ==
                      0,'Skipping nxOMSCustomLogTestCases.   omsagent is not running.')
class nxOMSCustomLogTestCases(unittest2.TestCase):
    """
    Test Case for nxOMSCustomLog.py
    """

    original_conf_path = None
    mock_conf_path = './ut_customlog.conf'

    def setUp(self):
        """
        Setup test resources
        """
        self.original_conf_path = nxOMSCustomLog.conf_path
        nxOMSCustomLog.conf_path = self.mock_conf_path
        os.system('rm -rf {0}'.format(self.mock_conf_path))

    def tearDown(self):
        """
        Remove test resources
        """
        nxOMSCustomLog.conf_path = self.original_conf_path

    def make_MI(self, retval, Name, EnableCustomLogConfiguration, CustomLogObjects):
        d = dict()
        d['Name'] = nxOMSCustomLog.protocol.MI_String(Name)
        d['EnableCustomLogConfiguration'] = nxOMSCustomLog.protocol.MI_Boolean(EnableCustomLogConfiguration)
        if CustomLogObjects is None:
            CustomLogObjects = []
        for customlog in CustomLogObjects:
            customlog['LogName'] = nxOMSCustomLog.protocol.MI_String(customlog['LogName'])
            if customlog['FilePath'] is not None and len(customlog['FilePath']):
                customlog['FilePath'] = nxOMSCustomLog.protocol.MI_StringA(customlog['FilePath'])
        d['CustomLogObjects'] = nxOMSCustomLog.protocol.MI_InstanceA(CustomLogObjects)
        return retval, d
    
    def testSetOMSCustomLog_add(self):
        d = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': [{ 'LogName': 'CUSTOM_LOG_BLOB.LinuxSampleCustomLog1', 'FilePath': [ '/tmp/test1.log', '/tmp/logs/*.log' ] }, { 'LogName': 'CUSTOM_LOG_BLOB.LinuxSampleCustomLog2', 'FilePath': [ '/tmp/test2.log' ] } ] }
        for customlog in d['CustomLogObjects']:
            customlog['LogName'] = nxOMSCustomLog.protocol.MI_String(customlog['LogName'])
            customlog['FilePath'] = nxOMSCustomLog.protocol.MI_StringA(customlog['FilePath'])

        self.assertTrue(nxOMSCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

    def testGetOMSCustomLog_add(self):
        d = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': [{ 'LogName': 'LinuxSampleCustomLog1', 'FilePath': [ '/tmp/test1.log', '/tmp/logs/*.log' ] }, { 'LogName': 'LinuxSampleCustomLog2', 'FilePath': [ '/tmp/test2.log' ] } ] }
        for customlog in d['CustomLogObjects']:
            customlog['LogName'] = nxOMSCustomLog.protocol.MI_String(customlog['LogName'])
            customlog['FilePath'] = nxOMSCustomLog.protocol.MI_StringA(customlog['FilePath'])

        e = copy.deepcopy(d)
        t = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': [{ 'LogName': 'LinuxSampleCustomLog1', 'FilePath': [ '/tmp/logs/*.log', '/tmp/test1.log' ] }, { 'LogName': 'LinuxSampleCustomLog2', 'FilePath': [ '/tmp/test2.log' ] } ] }

        self.assertTrue(nxOMSCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
         
        m = self.make_MI(0,**t)
        g = nxOMSCustomLog.Get_Marshall(**e)
        self.assertTrue(check_values(g, m)  ==  True, 'Get('+repr(g)+' should return ==['+repr(m)+']')

    def testSetOMSCustomLog_del(self):
        d = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
        self.assertTrue(nxOMSCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 

    def testGetOMSCustomLog_default(self):
        d = { 'Name': 'SimpleCustomLog' }
        self.assertTrue(nxOMSCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

        t = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': False, 'CustomLogObjects': None }
        m=self.make_MI(0,**t)
        g=nxOMSCustomLog.Get_Marshall(**d)
        print 'GET '+ repr(g)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')

    def testGetOMSCustomLog_del(self):
        d = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
        self.assertTrue(nxOMSCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
        m=self.make_MI(0,**t)
        g=nxOMSCustomLog.Get_Marshall(**d)
        print 'GET '+ repr(g)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')


@unittest2.skipUnless(os.system('ps -ef | grep -v grep | grep omsagent') ==
                      0,'Skipping nxOMSSudoCustomLogTestCases.   omsagent is not running.')
class nxOMSSudoCustomLogTestCases(unittest2.TestCase):
    """
    Test Case for nxOMSSudoCustomLog.py
    """

    original_conf_path = None
    mock_conf_path = './ut_sudocustomlog.conf'

    def setUp(self):
        """
        Setup test resources
        """
        self.original_conf_path = nxOMSSudoCustomLog.CONF_PATH
        nxOMSSudoCustomLog.CONF_PATH = self.mock_conf_path
        os.system('rm -rf {0}'.format(self.mock_conf_path))

        nxOMSSudoCustomLog.RESOURCE_DIR = '/var/tmp/omsconfig_CL/modules/nxOMSSudoCustomLog/'
        nxOMSSudoCustomLog.RESOURCE_PLUGIN_DIR = nxOMSSudoCustomLog.RESOURCE_DIR + 'Plugin/'
        nxOMSSudoCustomLog.PLUGIN = nxOMSSudoCustomLog.RESOURCE_PLUGIN_DIR + 'in_sudo_tail.rb'
        nxOMSSudoCustomLog.SCRIPT = nxOMSSudoCustomLog.RESOURCE_PLUGIN_DIR + 'tailfilereader.rb'
        nxOMSSudoCustomLog.AGENT_PLUGIN_DIR = '/var/tmp/omsagent_CL/plugin/'

        os.system('rm -rf /var/tmp/omsconfig_CL /var/tmp/omsagent_CL;')

        os.system('mkdir -p ' + nxOMSSudoCustomLog.RESOURCE_PLUGIN_DIR + ';'
              'mkdir -p ' + nxOMSSudoCustomLog.AGENT_PLUGIN_DIR + ';'
              'echo sudo_tail plugin >> ' + nxOMSSudoCustomLog.PLUGIN + ';'
              'echo tailfilereader script >> ' + nxOMSSudoCustomLog.SCRIPT + ';'
        )

    def tearDown(self):
        """
        Remove test resources
        """
        nxOMSSudoCustomLog.CONF_PATH = self.original_conf_path
        os.system('rm -rf /var/tmp/omsconfig_CL /var/tmp/omsagent_CL')

    def make_MI(self, retval, Name, Ensure, EnableCustomLogConfiguration, CustomLogObjects):
        d = dict()
        d['Name'] = nxOMSSudoCustomLog.protocol.MI_String(Name)
        d['Ensure'] = nxOMSSudoCustomLog.protocol.MI_String(Ensure)
        d['EnableCustomLogConfiguration'] = nxOMSSudoCustomLog.protocol.MI_Boolean(EnableCustomLogConfiguration)
        if CustomLogObjects is None:
            CustomLogObjects = []
        for customlog in CustomLogObjects:
            customlog['LogName'] = nxOMSSudoCustomLog.protocol.MI_String(customlog['LogName'])
            if customlog['FilePath'] is not None and len(customlog['FilePath']):
                customlog['FilePath'] = nxOMSSudoCustomLog.protocol.MI_StringA(customlog['FilePath'])
        d['CustomLogObjects'] = nxOMSSudoCustomLog.protocol.MI_InstanceA(CustomLogObjects)
        return retval, d

    def testSetOMSSudoCustomLog_add(self):
        d = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'Ensure': 'Present', 'CustomLogObjects': [{ 'LogName': 'CUSTOM_LOG_BLOB.LinuxSampleCustomLog1', 'FilePath': [ '/tmp/test1.log', '/tmp/logs/*.log' ] }, { 'LogName': 'CUSTOM_LOG_BLOB.LinuxSampleCustomLog2', 'FilePath': [ '/tmp/test2.log' ] } ] }
        for customlog in d['CustomLogObjects']:
            customlog['LogName'] = nxOMSSudoCustomLog.protocol.MI_String(customlog['LogName'])
            customlog['FilePath'] = nxOMSSudoCustomLog.protocol.MI_StringA(customlog['FilePath'])
        self.assertTrue(nxOMSSudoCustomLog.Set_Marshall(**d) == [0], 'Set('+repr(d)+') should return == [0]')

    def testGetOMSSudoCustomLog_add(self):
        d = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'Ensure': 'Present', 'CustomLogObjects': [{ 'LogName': 'LinuxSampleCustomLog1', 'FilePath': [ '/tmp/test1.log', '/tmp/logs/*.log' ] }, { 'LogName': 'LinuxSampleCustomLog2', 'FilePath': [ '/tmp/test2.log' ] } ] }
        for customlog in d['CustomLogObjects']:
            customlog['LogName'] = nxOMSSudoCustomLog.protocol.MI_String(customlog['LogName'])
            customlog['FilePath'] = nxOMSSudoCustomLog.protocol.MI_StringA(customlog['FilePath'])

        e = copy.deepcopy(d)
        t = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'Ensure': 'Present', 'CustomLogObjects': [{ 'LogName': 'LinuxSampleCustomLog1', 'FilePath': [ '/tmp/logs/*.log', '/tmp/test1.log' ] }, { 'LogName': 'LinuxSampleCustomLog2', 'FilePath': [ '/tmp/test2.log' ] } ] }

        self.assertTrue(nxOMSSudoCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

        m = self.make_MI(0,**t)
        g = nxOMSSudoCustomLog.Get_Marshall(**e)
        self.assertTrue(check_values(g, m)  ==  True, 'Get('+repr(g)+' should return ==['+repr(m)+']')

    def testSetOMSSudoCustomLog_del(self):
        d = { 'Name': 'SimpleCustomLog', 'Ensure': 'Present', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
        self.assertTrue(nxOMSSudoCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

    def testGetOMSSudoCustomLog_default(self):
        d = { 'Name': 'SimpleCustomLog', 'Ensure': 'Absent' }
        self.assertTrue(nxOMSSudoCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

        t = { 'Name': 'SimpleCustomLog', 'Ensure': 'Absent', 'EnableCustomLogConfiguration': False, 'CustomLogObjects': None }
        m=self.make_MI(0,**t)
        g=nxOMSSudoCustomLog.Get_Marshall(**d)
        print 'GET '+ repr(g)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')

    def testGetOMSSudoCustomLog_del(self):
        d = { 'Name': 'SimpleCustomLog', 'Ensure': 'Present', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
        self.assertTrue(nxOMSSudoCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t = { 'Name': 'SimpleCustomLog', 'Ensure': 'Present', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
        m=self.make_MI(0,**t)
        g=nxOMSSudoCustomLog.Get_Marshall(**d)
        print 'GET '+ repr(g)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')


class nxOMSGenerateInventoryMofTestCases(unittest2.TestCase):
    """
    Test Case for nxOMSGenerateInventoryMof.py
    """

    original_mof_path = None
    mock_mof_path = '/tmp/'

    def setUp(self):
        """
        Setup test resources
        """
        self.original_mof_path = nxOMSGenerateInventoryMof.inventoryMof_path
        nxOMSGenerateInventoryMof.inventoryMof_path = self.mock_mof_path
        os.system('rm -rf {0}'.format(self.mock_mof_path + 'generatedinventory.mof'))
        os.system('rm -rf {0}'.format(self.mock_mof_path + 'generatedinventory.conf'))

    def tearDown(self):
        """
        Remove test resources
        """
        nxOMSGenerateInventoryMof.inventoryMof_path = self.original_mof_path

    def make_MI(self, retval, FeatureName, Enable, Instances , RunIntervalInSeconds, Tag , Format , FilterType , Configuration):
        d = dict()
        d['FeatureName'] = nxOMSGenerateInventoryMof.protocol.MI_String(FeatureName)
        d['Enable'] = nxOMSGenerateInventoryMof.protocol.MI_Boolean(Enable)
        if Instances is None:
            Instances = []
        for instance in Instances:
            instance['InstanceName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['InstanceName'])
            instance['ClassName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['ClassName'])

            if instance['Properties'] is not None and len(instance['Properties']):
                instance['Properties'] = nxOMSGenerateInventoryMof.protocol.MI_StringA(instance['Properties'])
        d['Instances'] = nxOMSGenerateInventoryMof.protocol.MI_InstanceA(Instances)
        d['RunIntervalInSeconds'] =  nxOMSGenerateInventoryMof.protocol.MI_Uint64(RunIntervalInSeconds)
        d['Tag'] = nxOMSGenerateInventoryMof.protocol.MI_String(Tag)
        d['Format'] = nxOMSGenerateInventoryMof.protocol.MI_String(Format)
        d['FilterType'] = nxOMSGenerateInventoryMof.protocol.MI_String(FilterType)

        if Configuration is None:
            Configuration = []
        if Configuration is not None and len(Configuration):
            d['Configuration'] = nxOMSGenerateInventoryMof.protocol.MI_StringA(Configuration)

        return retval, d

    def testSetOMSGenerateInventoryMof_multipleinstances(self):
        d = { 'FeatureName': 'generatedinventory', 'Enable': True, 'Instances': [{ 'InstanceName': 'FileInventory', 'ClassName': 'MSFT_nxFileInventoryResource', 'Properties': [ 'DestinationPath = "/etc/*.conf";', 'Recurse=true;' ] }, { 'InstanceName': 'RegistryInventory', 'ClassName':'MSFT_nxRegistryInventoryResource', 'Properties': [ 'RegistryName=hkeylocal;' ] } ], 'RunIntervalInSeconds':300, 'Tag': 'Test', 'Format':'tsv', 'FilterType':'filter', 'Configuration':['testname = value'] }

        for instance in d['Instances']:
            instance['InstanceName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['InstanceName'])
            instance['ClassName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['ClassName'])
            instance['Properties'] = nxOMSGenerateInventoryMof.protocol.MI_StringA(instance['Properties'])

        self.assertTrue(nxOMSGenerateInventoryMof.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(os.path.isfile(self.mock_mof_path + 'generatedinventory' + '.mof'))


    def testSetOMSGenerateInventoryMof_noinstances(self):
        d = { 'FeatureName': 'generatedinventory', 'Enable': True, 'Instances': None }
        self.assertTrue(nxOMSGenerateInventoryMof.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(os.path.isfile(self.mock_mof_path + 'generatedinventory' + '.mof'))


    def testSetOMSGenerateInventoryMof_EnableisFalse(self):
        d = { 'FeatureName': 'generatedinventory', 'Enable': False, 'Instances': [{ 'InstanceName': 'FileInventory', 'ClassName': 'MSFT_nxFileInventoryResource', 'Properties': [ 'DestinationPath = "/etc/*.conf";', 'Recurse=true;' ] }, { 'InstanceName': 'RegistryInventory', 'ClassName':'MSFT_nxRegistryInventoryResource', 'Properties': [ 'RegistryName=hkeylocal;' ] } ], 'RunIntervalInSeconds':300, 'Tag': 'Test', 'Format':'tsv', 'FilterType':'filter', 'Configuration':['testname = value'] }
        for instance in d['Instances']:
            instance['InstanceName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['InstanceName'])
            instance['ClassName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['ClassName'])
            instance['Properties'] = nxOMSGenerateInventoryMof.protocol.MI_StringA(instance['Properties'])

        codecs.open(self.mock_mof_path + 'generatedinventory' + '.mof', 'w', 'utf8').write("dummy")
        codecs.open(self.mock_mof_path + 'generatedinventory' + '.conf', 'w', 'utf8').write("dummy")
        self.assertTrue(nxOMSGenerateInventoryMof.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertFalse(os.path.isfile(self.mock_mof_path + 'generatedinventory' + '.mof'))
        self.assertFalse(os.path.isfile(self.mock_mof_path + 'generatedinventory' + '.conf'))

    def testTestOMSGenerateInventoryMof(self):

        d = { 'FeatureName': 'generatedinventory', 'Enable': True, 'Instances': [{ 'InstanceName': 'FileInventory', 'ClassName': 'MSFT_nxFileInventoryResource', 'Properties': [ 'DestinationPath = "/etc/*.conf";', 'Recurse=true;' ] }, { 'InstanceName': 'RegistryInventory', 'ClassName':'MSFT_nxRegistryInventoryResource', 'Properties': [ 'RegistryName=hkeylocal;' ] } ], 'RunIntervalInSeconds':300, 'Tag': 'Test', 'Format':'tsv', 'FilterType':'filter', 'Configuration':['testname = value'] }

        for instance in d['Instances']:
            instance['InstanceName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['InstanceName'])
            instance['ClassName'] = nxOMSGenerateInventoryMof.protocol.MI_String(instance['ClassName'])
            instance['Properties'] = nxOMSGenerateInventoryMof.protocol.MI_StringA(instance['Properties'])

        e = copy.deepcopy(d)
        f = copy.deepcopy(d)

        self.assertTrue(nxOMSGenerateInventoryMof.Test_Marshall(**d) == [-1],'Test('+repr(d)+') should return == [-1]')
        self.assertFalse(os.path.isfile(self.mock_mof_path + 'generatedinventory' + '.mof'))

        self.assertTrue(nxOMSGenerateInventoryMof.Set_Marshall(**e) == [0],'Set('+repr(e)+') should return == [0]')
        self.assertTrue(nxOMSGenerateInventoryMof.Test_Marshall(**f) == [0],'Test('+repr(f)+') should return == [0]')
        self.assertTrue(os.path.isfile(self.mock_mof_path + 'generatedinventory' + '.mof'))


    def testGetOMSGenerateInventoryMof_default(self):
        d = { 'FeatureName': 'generatedinventory', 'Enable': True, 'Instances': [{ 'InstanceName': 'FileInventory', 'ClassName': 'MSFT_nxFileInventoryResource', 'Properties': [ 'DestinationPath = "/etc/*.conf";', 'Recurse=true;' ] }, { 'InstanceName': 'RegistryInventory', 'ClassName':'MSFT_nxRegistryInventoryResource', 'Properties': [ 'RegistryName=hkeylocal;' ] } ], 'RunIntervalInSeconds':300, 'Tag': 'Test', 'Format':'tsv', 'FilterType':'filter', 'Configuration':['testname = value'] }
        m=self.make_MI(0,**d)
        g=nxOMSGenerateInventoryMof.Get_Marshall(**d)
        print('GET '+ repr(g))
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get('+repr(g)+' should return ==['+repr(m)+']')
        self.assertFalse(os.path.isfile(self.mock_mof_path + 'generatedinventory' + '.mof'))


# omsagent is not required to  be running.
class nxOMSKeyMgmtTestCases(unittest2.TestCase):
    """
    Test cases for nxOMSSyslog.py
    """
    @classmethod    
    def setUpClass(cls):
        key_txt = (open('./Scripts/Tests/test_mofs/testdsckey.pub','r').read())
        sig_txt = (open('./Scripts/Tests/test_mofs/testdsckey.asc','r').read())
        cls.keymgmt = {'KeyContents': key_txt, \
                       'KeySignature': sig_txt, 'Ensure':'present'}
        cls.conf_dir = '/etc/opt/omi/conf/omsconfig'
        if not os.path.exists(cls.conf_dir):
            os.system('mkdir -p ' + cls.conf_dir + ' 2>&1 >/dev/null')
        os.system('cp ' + nxOMSKeyMgmt.signature_keyring_path + ' ' + \
                  nxOMSKeyMgmt.signature_keyring_path +  '.bak 2>&1 >/dev/null')
        os.system('cp ' + nxOMSKeyMgmt.dsc_keyring_path + ' ' + \
                  nxOMSKeyMgmt.dsc_keyring_path +  '.bak 2>&1 >/dev/null')

        

    @classmethod
    def tearDownClass(cls):
        os.system('cp ' + nxOMSKeyMgmt.signature_keyring_path + '.bak ' + \
                  nxOMSKeyMgmt.signature_keyring_path + '2>&1 >/dev/null')
        os.system('cp ' + nxOMSKeyMgmt.dsc_keyring_path + '.bak ' + \
                  nxOMSKeyMgmt.dsc_keyring_path +  ' 2>&1 >/dev/null')
        

    
    def setUp(self):
        """
        Setup test resources
        """
        os.system('cp ./Scripts/Tests/test_mofs/keymgmtring.gpg ' + \
                  nxOMSKeyMgmt.signature_keyring_path +  ' 2>&1 >/dev/null')
        os.system('cp ./Scripts/Tests/test_mofs/keyring.gpg ' + \
                  nxOMSKeyMgmt.dsc_keyring_path +  ' 2>&1 >/dev/null')
        

    def tearDown(self):
        """
        Remove test resources.
        """
        pass
    
    def testOMSKeyMgmtSetTestAbsent(self):
        self.keymgmt['Ensure'] = 'present'
        r = nxOMSKeyMgmt.Set_Marshall(**self.keymgmt)
        self.assertTrue(r == [0], 
                "nxOMSKeyMgmt.Set_Marshall(self.keymgmt['KeyContents'], self.keymgmt['KeySignature'], 'present') should == [0]")
        self.keymgmt['Ensure'] = 'absent'
        r = nxOMSKeyMgmt.Set_Marshall(**self.keymgmt)
        self.assertTrue(r == [0], 
                "nxOMSKeyMgmt.Set_Marshall(self.keymgmt['KeyContents'], self.keymgmt['KeySignature'], 'absent') should == [0]")
        r = nxOMSKeyMgmt.Test_Marshall(**self.keymgmt)
        self.assertTrue(r == [0], 
                "nxOMSKeyMgmt.Test_Marshall(self.keymgmt['KeyContents'], self.keymgmt['KeySignature'], 'absent') should == [0]")

    def testOMSKeyMgmtTestAbsent(self):
        self.keymgmt['Ensure'] = 'absent'
        r = nxOMSKeyMgmt.Test_Marshall(**self.keymgmt)
        self.assertTrue(r == [0], 
                "nxOMSKeyMgmt.Test_Marshall(self.keymgmt['KeyContents'], self.keymgmt['KeySignature'], 'absent') should == [0]")

    def testOMSKeyMgmtSetPresent(self):
        self.keymgmt['Ensure'] = 'present'
        r = nxOMSKeyMgmt.Set_Marshall(**self.keymgmt)
        self.assertTrue(r == [0], 
                "nxOMSKeyMgmt.Set_Marshall(self.keymgmt['KeyContents'], self.keymgmt['KeySignature'], 'present') should == [0]")
        r = nxOMSKeyMgmt.Test_Marshall(**self.keymgmt)
        self.assertTrue(r == [0], 
                "nxOMSKeyMgmt.Test_Marshall(self.keymgmt['KeyContents'], self.keymgmt['KeySignature'], 'present') should == [0]")

    def testOMSKeyMgmtSetPresentBadSig(self):
        bad = dict(self.keymgmt)
        bad['Ensure'] = 'present'
        bad['KeySignature'] = 'aaa'
        r = nxOMSKeyMgmt.Set_Marshall(**bad)
        self.assertTrue(r == [-1], 
                "nxOMSKeyMgmt.Set_Marshall(bad['KeyContents'], bad['KeySignature'], 'present') should == [-1]")
        r = nxOMSKeyMgmt.Test_Marshall(**bad)
        self.assertTrue(r == [-1], 
                "nxOMSKeyMgmt.Test_Marshall(bad['KeyContents'], bad['KeySignature'], 'present') should == [-1]")

    def testOMSKeyMgmtSetPresentBadCert(self):
        bad = dict(self.keymgmt)
        bad['Ensure'] = 'present'
        bad['KeyContents'] = 'aaa'
        r = nxOMSKeyMgmt.Set_Marshall(**bad)
        self.assertTrue(r == [-1], 
                "nxOMSKeyMgmt.Set_Marshall(bad['KeyContents'], bad['KeySignature'], 'present') should == [-1]")
        r = nxOMSKeyMgmt.Test_Marshall(**bad)
        self.assertTrue(r == [-1], 
                "nxOMSKeyMgmt.Test_Marshall(bad['KeyContents'], bad['KeySignature'], 'present') should == [-1]")


class nxFileInventoryTestCases(unittest2.TestCase):
    """
    Test cases for nxFileInventory.py
    """
    @classmethod    
    def setUpClass(cls):
        """
        You should set 'create_files' to True
        to re-create the picked files
        when Inventory_Marshall
        or the tests have changed.
        """
        cls.create_files = False
        cls.linkfarm = '/tmp/linkfarm/'
        os.system('rm -rf ' + cls.linkfarm)
        os.makedirs(cls.linkfarm+'joe')
        os.makedirs(cls.linkfarm+'bob')
        open(cls.linkfarm+'joe/linkfarmjoefile1.txt','w+').write(\
            'Contents of linkfarmjoefile1.txt\n')
        open(cls.linkfarm+'joe/linkfarmjoefile2.txt','w+').write(\
            'Contents of linkfarmjoefile2.txt\n')
        open(cls.linkfarm+'bob/linkfarmbobfile1.txt','w+').write(\
            'Contents of linkfarmbobfile1.txt\n')
        open(cls.linkfarm+'bob/linkfarmbobfile2.txt','w+').write(\
            'Contents of linkfarmbobfile2.txt\n')
        cls.basepath = '/tmp/FileInventory/'
        os.system('rm -rf ' + cls.basepath)
        os.makedirs(cls.basepath+'joedir0/joedir1/joedir2/')
        open(cls.basepath+'basedirfile1.txt','w+').write(\
            'Contents of basedirfile1.txt\n')
        open(cls.basepath+'basedirfile2.txt','w+').write(\
            'Contents of basedirfile2.txt\n')
        open(cls.basepath+'basedirfile3.bin','wb+').write(\
            '\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
        os.chown(cls.basepath+'basedirfile3.bin', 7777, 7777)
        open(cls.basepath+'joedir0/joedir0file1.txt','w+').write(\
            'Contents of joedir0file1.txt\n')
        open(cls.basepath+'joedir0/joedir0file2.txt','w+').write(\
            'Contents of joedir0file2.txt\n')
        open(cls.basepath+'joedir0/joedir0file3.bin','wb+').write(\
            '\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
        os.chown(cls.basepath+'joedir0/joedir0file3.bin', 7777, 7777)
        open(cls.basepath+'joedir0/joedir1/joedir1file1.txt','w+').write(\
            'Contents of joedir1file1.txt\n')
        open(cls.basepath+'joedir0/joedir1/joedir1file2.txt','w+').write(\
            'Contents of joedir1file2.txt\n')
        open(cls.basepath+'joedir0/joedir1/joedir1file3.bin','wb+').write(\
            '\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
        os.chown(cls.basepath+'joedir0/joedir1/joedir1file3.bin', 7777, 7777)
        open(cls.basepath+'joedir0/joedir1/joedir2/joedir2file1.txt','w+').write(\
            'Contents of joedir2file1.txt\n')
        open(cls.basepath+'joedir0/joedir1/joedir2/joedir2file2.txt','w+').write(\
            'Contents of joedir2file2.txt\n')
        open(cls.basepath+'joedir0/joedir1/joedir2/joedir2file3.bin','wb+').write(\
            '\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
        os.chown(cls.basepath+'joedir0/joedir1/joedir2/joedir2file3.bin', 7777, 7777)
        os.makedirs(cls.basepath+'bobdir0/bobdir1/bobdir2/')
        open(cls.basepath+'bobdir0/bobdir0file1.txt','w+').write(\
            'Contents of bobdir0file1.txt\n')
        open(cls.basepath+'bobdir0/bobdir0file2.txt','w+').write(\
            'Contents of bobdir0file2.txt\n')
        open(cls.basepath+'bobdir0/bobdir0file3.bin','wb+').write(\
            '\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
        os.chown(cls.basepath+'bobdir0/bobdir0file3.bin', 7777, 7777)
        open(cls.basepath+'bobdir0/bobdir1/bobdir1file1.txt','w+').write(\
            'Contents of bobdir1file1.txt\n')
        open(cls.basepath+'bobdir0/bobdir1/bobdir1file2.txt','w+').write(\
            'Contents of bobdir1file2.txt\n')
        open(cls.basepath+'bobdir0/bobdir1/bobdir1file3.bin','wb+').write(\
            '\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
        os.chown(cls.basepath+'bobdir0/bobdir1/bobdir1file3.bin', 7777, 7777)
        open(cls.basepath+'bobdir0/bobdir1/bobdir2/bobdir2file1.txt','w+').write(\
            'Contents of bobdir2file1.txt\n')
        open(cls.basepath+'bobdir0/bobdir1/bobdir2/bobdir2file2.txt','w+').write(\
            'Contents of bobdir2file2.txt\n')
        open(cls.basepath+'bobdir0/bobdir1/bobdir2/bobdir2file3.bin','wb+').write(\
            '\xff\xfe\x00\x00\xff\xfd\x00\x00\x00\x00')
        os.chown(cls.basepath+'bobdir0/bobdir1/bobdir2/bobdir2file3.bin', 7777, 7777)
        os.symlink(cls.basepath+'bobdir0/bobdir0file1.txt', cls.basepath+'basedirfilelink1.txt')
        os.symlink(cls.basepath+'bobdir0/bobdir1', cls.basepath+'basedirdirlink1')
        os.symlink(cls.basepath+'bobdir0/bobdir0file1.txt', cls.basepath+'joedir0/joedir0filelink1.txt')
        os.symlink(cls.linkfarm+'joe', cls.basepath+'joedir0/joedir0dirlink1')
        os.symlink(cls.basepath+'joedir0', cls.basepath+'joedir0/joedir1/joedir1dirlinktojoedir0') # infinite recursion
        os.symlink(cls.basepath+'joedir0/joedir0file1.txt', cls.basepath+'bobdir0/bobdir0filelink1.txt')
        os.symlink(cls.linkfarm+'bob', cls.basepath+'bobdir0/bobdir0dirlink1')
        os.symlink(cls.basepath+'bobdir0', cls.basepath+'bobdir0/bobdir1/bobdir1dirlinktobobdir0') # infinite recursion

    @classmethod    
    def tearDownClass(cls):
        os.system('rm -rf ' + cls.basepath)
    
    def setUp(self):
        """
        Setup test resources
        """
        pass

    
    def tearDown(self):
        """
        Remove test resources.
        """
        pass


    def SerializeInventoryObject(self, fname, ob):
        # Persist the results of correct results for future tests.
        # The pickled results are stored in test_mofs.
        # You should re-create these files if Inventory_Marshall
        # or the the tests have changed.
        l = []
        for d in ob[1]['__Inventory'].value:
            l.append(d['DestinationPath'].value)
        l.sort()
        with open('./Scripts/Tests/test_mofs/' + fname + '.pkl', 'wb') as F:
            pickle.dump(l, F, -1)

    def DeserializeInventoryObject(self, fname):
        with open('./Scripts/Tests/test_mofs/' + fname + '.pkl', 'rb') as F:
            r = pickle.load(F)
        return r
        
    def MakeList(self,ob):
        l = []
        for d in ob[1]['__Inventory'].value:
            l.append(d['DestinationPath'].value)
        l.sort()
        return l
    
    def testFileInventoryInventory_MarshallDir(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0')
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallDir',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallDir')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))

    
    def testFileInventoryInventory_MarshallFile(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0')
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallFile',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallFile')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallSingleFile(self):
        print('Using path:' + self.basepath + 'basedirfile1.txt') 
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath + 'basedirfile1.txt', 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0')
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallSingleFile',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallSingleFile')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallTypeWild(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallTypeWild',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallTypeWild')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallDirRecurse(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallDirRecurse',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallDirRecurse')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallFileRecurse(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallFileRecurse',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallFileRecurse')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallTypeWildRecurse(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallTypeWildRecurse',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallTypeWildRecurse')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildDir(self):
        print 'Using path:' + self.basepath +'*dir*'
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*dir*', 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildDir',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildDir')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildFile(self):
        print 'Using path:' + self.basepath +'*/*file*'
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*file*', 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildFile',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildFile')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildTypeWild(self):
        print 'Using path:' + self.basepath +'*/*'
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*', 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWild',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWild')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildDirRecurse(self):
        print 'Using path:' + self.basepath +'*/*dir*'
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*dir*', 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildDirRecurse',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildDirRecurse')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildFileRecurse(self):
        print 'Using path:' + self.basepath +'*/*file*'
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*file*', 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildFileRecurse',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildFileRecurse')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildTypeWildRecurse(self):
        print 'Using path:' + self.basepath +'*/*'
        d = {'Links': u'ignore', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*', 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildRecurse',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildRecurse')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallDirFollowLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallDirFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallDirFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallFileFollowLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallFileFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallFileFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallTypeWildFollowLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallTypeWildFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallTypeWildFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallDirRecurseFollowLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallDirRecurseFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallDirRecurseFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallFileRecurseFollowLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallFileRecurseFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallFileRecurseFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallTypeWildRecurseFollowLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallTypeWildRecurseFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallTypeWildRecurseFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildDirFollowLink(self):
        print 'Using path:' + self.basepath +'*dir*'
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*dir*', 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildDirFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildDirFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildFileFollowLink(self):
        print 'Using path:' + self.basepath +'*/*file*'
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*file*', 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildFileFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildFileFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildTypeWildFollowLink(self):
        print 'Using path:' + self.basepath +'*/*'
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*', 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildDirRecurseFollowLink(self):
        print 'Using path:' + self.basepath +'*/*dir*'
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*dir*', 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildDirRecurseFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildDirRecurseFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildFileRecurseFollowLink(self):
        print 'Using path:' + self.basepath +'*/*file*'
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*file*', 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildFileRecurseFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildFileRecurseFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildTypeWildRecurseFollowLink(self):
        print 'Using path:' + self.basepath +'*/*'
        d = {'Links': u'follow', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*', 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildRecurseFollowLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildRecurseFollowLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']


    def testFileInventoryInventory_MarshallDirManageLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallDirManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallDirManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallFileManageLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallFileManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallFileManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallTypeWildManageLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallTypeWildManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallTypeWildManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallDirRecurseManageLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallDirRecurseManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallDirRecurseManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallFileRecurseManageLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallFileRecurseManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallFileRecurseManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallTypeWildRecurseManageLink(self):
        print 'Using path:' + self.basepath 
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath, 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallTypeWildRecurseManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallTypeWildRecurseManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildDirManageLink(self):
        print 'Using path:' + self.basepath +'*dir*'
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*dir*', 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildDirManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildDirManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildFileManageLink(self):
        print 'Using path:' + self.basepath +'*/*file*'
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*file*', 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildFileManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildFileManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildTypeWildManageLink(self):
        print 'Using path:' + self.basepath +'*/*'
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': False, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*', 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildDirRecurseManageLink(self):
        print 'Using path:' + self.basepath +'*/*dir*'
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*dir*', 'UseSudo': True, 'Type': u'directory'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildDirRecurseManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildDirRecurseManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildFileRecurseManageLink(self):
        print 'Using path:' + self.basepath +'*/*file*'
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*file*', 'UseSudo': True, 'Type': u'file'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildFileRecurseManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildFileRecurseManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

    def testFileInventoryInventory_MarshallWildTypeWildRecurseManageLink(self):
        print 'Using path:' + self.basepath +'*/*'
        d = {'Links': u'manage', 'MaxOutputSize': None, \
             'Checksum': u'md5', 'Recurse': True, \
             'MaxContentsReturnable': None, \
             'DestinationPath': self.basepath+'*/*', 'UseSudo': True, 'Type': u'*'}
        r = nxFileInventory.Inventory_Marshall(**d)
        self.assertTrue(r[0] == 0,'Inventory_Marshall('+repr(d)+')[0] should return == 0') 
        if self.create_files:
            self.SerializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildRecurseManageLink',r)
        l = self.MakeList(r)
        g = self.DeserializeInventoryObject('testFileInventoryInventory_MarshallWildTypeWildRecurseManageLink')
        self.assertTrue(g == l, repr(g) + '\n should be == to \n' + repr(l))
        for d in r[1]['__Inventory'].value:
            print d['DestinationPath'], d['Contents']

class nxOMSAgentNPMConfigTestCases(unittest2.TestCase):
    """
    Test cases for nxOMSAgentNPMConfig.py
    """

    class TestOMSAgentUtil(nxNPMD.IOMSAgent):
        def restart_oms_agent(self):
            return True

    class TestNPMAgentUtil(nxNPMD.IOMSAgent):
        def binary_setcap(self, binaryPath):
            return True

    def setUp(self):
        """
        Setup test resources
        """
        #time.sleep(1)
        nxNPMD.CONFIG_PATH = '/var/tmp/etc/opt/microsoft/omsagent/conf/'
        nxNPMD.SERVER_ADDRESS = '/var/tmp/run/npmdagent.sock'
        nxNPMD.DSC_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/AGENTVERSION'
        nxNPMD.PLUGIN_PATH = '/var/tmp/opt/microsoft/omsagent/plugin/'
        nxNPMD.PLUGIN_CONF_PATH = '/var/tmp/etc/opt/microsoft/omsagent/conf/omsagent.d/'
        nxNPMD.AGENT_BINARY_PATH = '/var/tmp/opt/microsoft/omsagent/'
        nxNPMD.RESOURCE_MODULE_PATH = '/var/tmp/opt/microsoft/omsconfig/modules/NPM/'
        nxNPMD.AGENT_SCRIPT_PATH = '/var/tmp/etc/opt/microsoft/omsagent/scipt.sh'

        self.config_type = 'UpdatedAgentConfig'
        self.config_id = '12345'
        self.contents = base64.b64encode('<Configuration></Configuration>')
        self.content_checksum = hashlib.md5(self.contents).hexdigest().upper()
        self.ensure_present = 'Present'
        self.ensure_absent = 'Absent'
        self.out_file = nxNPMD.CONFIG_PATH.__add__(nxNPMD.DEST_FILE_NAME)
        self.server_address = nxNPMD.SERVER_ADDRESS

        x64binaryPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_X64_AGENT_PATH)
        x86binaryPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_X86_AGENT_PATH)
        dscPluginPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_PLUGIN_PATH)
        dscConfPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_PLUGIN_CONF_PATH)
        
        # remove files from directory
        os.system('rm -rf /var/tmp/run;' +
            'rm -rf /var/tmp/etc;'
            'rm -rf /var/tmp/opt;'
        )
        os.system('mkdir -p ' + nxNPMD.CONFIG_PATH + ';'
            'mkdir -p ' + '/var/tmp/run/' + ';'
            'mkdir -p ' + nxNPMD.PLUGIN_PATH + ';'
            'mkdir -p ' + nxNPMD.PLUGIN_CONF_PATH + ';'
            'mkdir -p ' + x64binaryPath + ';'
            'mkdir -p ' + x86binaryPath + ';'
            'mkdir -p ' + dscPluginPath + ';'
            'mkdir -p ' + dscConfPath + ';'
            'echo testfile >> ' + x64binaryPath + 'binary;'
            'echo testfile >> ' + x86binaryPath + 'binary;'
            'echo testfile >> ' + dscPluginPath + 'plugin;'
            'echo testfile >> ' + dscConfPath + 'config;'
            'echo testfile >> ' + nxNPMD.AGENT_SCRIPT_PATH + ';'
        )
        
        with open(nxNPMD.DSC_RESOURCE_VERSION_PATH, 'w+') as dFile:
            dFile.write('1.0')
        with open(nxNPMD.AGENT_RESOURCE_VERSION_PATH, 'w+') as dFile:
            dFile.write('1.0')

        nxNPMD.OMS_ACTION = nxOMSAgentNPMConfigTestCases.TestOMSAgentUtil()
        nxNPMD.NPM_ACTION = nxOMSAgentNPMConfigTestCases.TestNPMAgentUtil()

        thread.start_new_thread(self.createUDSServer, ())
    def tearDown(self):
        """
        Remove test resources.
        """
        # remove files from directory
        os.system('rm -rf /var/tmp/run;' +
            'rm -rf /var/tmp/etc;'
        )
        #time.sleep(1)

    
    def make_MI(self, retval, ConfigType, ConfigID, Contents, Ensure, ContentChecksum):
        d=dict();
        if ConfigType == None :
            d['ConfigType'] = None
        else :
            d['ConfigType'] = nxNPMD.protocol.MI_String(ConfigType)
        if ConfigID == None :
            d['ConfigID'] = None
        else :
            d['ConfigID'] = nxNPMD.protocol.MI_String(ConfigID)
        if Ensure == None :
            d['Ensure'] = None
        else :
            d['Ensure'] = nxNPMD.protocol.MI_String(Ensure)
        if Contents == None :
            d['Contents'] = None
        else :
            d['Contents'] = nxNPMD.protocol.MI_String(Contents)
        if ContentChecksum == None :
            d['ContentChecksum'] = None
        else :
            d['ContentChecksum'] = nxNPMD.protocol.MI_String(ContentChecksum)
        return retval,d

    def readFile(self, path):
        content = None
        try:
            with codecs.open (path, encoding = 'utf8', mode = "r") as dFile:
                content = dFile.read()
        except IOError, error:
            print "Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror
        return content

    def createUDSServer(self):
        # Make sure the socket does not already exist
        try:
            os.unlink(self.server_address)
        except OSError:
            if os.path.exists(self.server_address):
                raise

        # Create a UDS socket
        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

        # Bind the socket to the port
        sock.bind(self.server_address)

        # Listen for incoming connections
        sock.listen(1)

        while True:
            connection, client_address = sock.accept()
            try:
                # Receive the data in small chunks and retransmit it
                while True:
                    data = connection.recv(100)
                    if not data:
                        break
            finally:
                # Clean up the connection
                connection.close()

    def verifyFileContents(self, text):
        content = self.readFile(nxNPMD.AGENT_BINARY_PATH.__add__('binary'))
        print content, text
        self.assertTrue(content == text, 'Contents written to file do not match')
        content = self.readFile(nxNPMD.PLUGIN_PATH.__add__('plugin'))
        self.assertTrue(content == text, 'Contents written to file do not match')
        content = self.readFile(nxNPMD.PLUGIN_CONF_PATH.__add__('config'))
        self.assertTrue(content == text, 'Contents written to file do not match')

    def updateFileContents(self, text):
        with open(nxNPMD.AGENT_BINARY_PATH.__add__('binary'), 'w+') as dFile:
            dFile.write(text)
        with open(nxNPMD.PLUGIN_PATH.__add__('plugin'), 'w+') as dFile:
            dFile.write(text)
        with open(nxNPMD.PLUGIN_CONF_PATH.__add__('config'), 'w+') as dFile:
            dFile.write(text)

    def testGetUpdateAgentConfig(self):
        r=nxNPMD.Get_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        print r
        print self.make_MI([0], self.config_type, self.config_id, base64.b64decode(self.contents), self.ensure_present, self.content_checksum)
        self.assertTrue(check_values(r,self.make_MI([0], self.config_type, self.config_id, base64.b64decode(self.contents), self.ensure_present, self.content_checksum)) == True,'nxNPMD.Get_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)[0] should return == 0')


    def testTestNewAgentConfig(self):
        # disables check for binary update
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        print r
        self.assertTrue(r == [-1],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')

    def testTestUpdateConfigChecksumMismatch(self):
        # disables check for binary update
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, base64.b64encode('New config string'), self.ensure_present, self.content_checksum)
        print r
        self.assertTrue(r == [0],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')

    def testTestUpdateNewConfig(self):
        # disables check for binary update
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        newContent = 'New config string'
        newChecksum = hashlib.md5(base64.b64encode(newContent)).hexdigest().upper()
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, base64.b64encode(newContent), self.ensure_present, newChecksum)
        print r
        self.assertTrue(r == [-1],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')

    def testTestSolutionEnable(self):
        # disable config update
        with open(nxNPMD.CONFIG_PATH.__add__(nxNPMD.DEST_FILE_NAME), 'w+') as dFile:
            dFile.write(base64.b64decode(self.contents))
        # remove agent resource version file
        os.unlink(nxNPMD.AGENT_RESOURCE_VERSION_PATH)
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        self.assertTrue(r == [-1],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')

    def testTestBinaryUpdate(self):
        # disable config update
        with open(nxNPMD.CONFIG_PATH.__add__(nxNPMD.DEST_FILE_NAME), 'w+') as dFile:
            dFile.write(base64.b64decode(self.contents))
        # update dsc resource version file
        with open(nxNPMD.DSC_RESOURCE_VERSION_PATH, 'w+') as dFile:
            dFile.write('1.1')
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        self.assertTrue(r == [-1],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')

    def testTestNoChange(self):
        # disable config update
        with open(nxNPMD.CONFIG_PATH.__add__(nxNPMD.DEST_FILE_NAME), 'w+') as dFile:
            dFile.write(base64.b64decode(self.contents))
        # disables check for binary update
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        self.assertTrue(r == [0],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')

    def testTestEnsureAbsentNoAgent(self):
        # remove agent resource version file
        os.unlink(nxNPMD.AGENT_RESOURCE_VERSION_PATH)
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_absent, self.content_checksum)
        self.assertTrue(r == [0],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')

    def testTestEnsureAbsentSolutionPurge(self):
        r=nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_absent, self.content_checksum)
        self.assertTrue(r == [-1],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')


    def testSetNewAgentConfig(self):
        # disables check for binary update
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        r=nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        print r
        self.assertTrue(r == [0],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')
        content = self.readFile(self.out_file)
        self.assertTrue(content == base64.b64decode(self.contents), 'Contents written to file do not match')

    def testSetUpdateConfigChecksumMismatch(self):
        # disables check for binary update
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        newStr = 'New config string'
        r=nxNPMD.Set_Marshall(self.config_type, self.config_id, base64.b64encode(newStr), self.ensure_present, self.content_checksum)
        print r
        self.assertTrue(r == [-1],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')
        content = self.readFile(self.out_file)
        print content
        self.assertTrue(content != newStr, 'Contents written to file do not match')

    def testSetUpdateNewConfig(self):
        # disables check for binary update
        nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
        nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        newContent = 'New config string'
        newChecksum = hashlib.md5(base64.b64encode(newContent)).hexdigest().upper()
        r=nxNPMD.Set_Marshall(self.config_type, self.config_id, base64.b64encode(newContent), self.ensure_present, newChecksum)
        print r
        self.assertTrue(r == [0],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')
        content = self.readFile(self.out_file)
        self.assertTrue(newContent == content, 'Contents written to file do not match')

    def testSetSolutionEnable(self):
        # disable config update
        with open(nxNPMD.CONFIG_PATH.__add__(nxNPMD.DEST_FILE_NAME), 'w+') as dFile:
            dFile.write(base64.b64decode(self.contents))
        # remove agent resource version file
        os.unlink(nxNPMD.AGENT_RESOURCE_VERSION_PATH)
        r=nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
        self.assertTrue(r == [0],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')
        
        #verify file contents
        self.verifyFileContents('testfile\n')

    def testSetBinaryUpdate(self):
        # disable config update
        with open(nxNPMD.CONFIG_PATH.__add__(nxNPMD.DEST_FILE_NAME), 'w+') as dFile:
            dFile.write(base64.b64decode(self.contents))
        # update dsc resource version file
        with open(nxNPMD.DSC_RESOURCE_VERSION_PATH, 'w+') as dFile:
            dFile.write('1.1')
        r=nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)

        #change contents
        self.updateFileContents('newText')

        # making sure we are able to override files
        with open(nxNPMD.DSC_RESOURCE_VERSION_PATH, 'w+') as dFile:
            dFile.write('1.2')

        r=nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)        
        self.assertTrue(r == [0],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')

        #verify file contents
        self.verifyFileContents('testfile\n')

    def testSetEnsureAbsentSolutionPurge(self):
        r=nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_absent, self.content_checksum)
        self.assertTrue(r == [0],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')

        # make sure files are not present
        if os.path.exists(nxNPMD.PLUGIN_CONF_PATH.__add__('config')):
            self.assertTrue(False, 'binary file exists')
        if os.path.exists(nxNPMD.AGENT_RESOURCE_VERSION_PATH):
            self.assertTrue(False, 'agent resource version file exists')

class nxOMSAutomationWorkerTestCases(unittest2.TestCase):
    """
    Test Case for nxOMSAutomationWorker.py
    """
    workspace_id = 'cfd4ef08-4011-428a-8947-0c2f4605980f'
    agent_id = 'cfd4ef08-4011-428a-8947-0c2f4605980g'
    AzureDnsAgentSvcZone = 'agentsvc.azure-automation.net'
    temp_run_dir = os.path.join(os.getcwd(), 'Scripts/Tests/temp')
    dummyFileLocation = os.path.join(os.getcwd(), 'Scripts/Tests/dummy_nxOMSAutomationWorker_files')

    nxOMSAutomationWorker.WORKER_CONF_DIR = temp_run_dir
    nxOMSAutomationWorker.OMS_CONF_FILE_PATH = os.path.join(temp_run_dir, "oms.conf")
    nxOMSAutomationWorker.AUTO_REGISTERED_WORKER_CONF_PATH = os.path.join(temp_run_dir, "worker.conf")
    nxOMSAutomationWorker.WORKER_MANAGER_START_PATH = os.path.join(dummyFileLocation, 'main.py')
    nxOMSAutomationWorker.DSC_RESOURCE_VERSION_FILE = os.path.join(dummyFileLocation, 'VERSION')
    nxOMSAutomationWorker.LOCAL_LOG_LOCATION = os.path.join(temp_run_dir, 'nxOMSAutomationWorker.log')
    nxOMSAutomationWorker.LOG_LOCALLY = True
    nxOMSAutomationWorker.OMS_ADMIN_CONFIG_FILE = os.path.join(dummyFileLocation, 'omsadmin.conf')
    nxOMSAutomationWorker.DIY_WORKER_CONF_PATH = nxOMSAutomationWorker.AUTO_REGISTERED_WORKER_CONF_PATH

    automation_user = "nxautomation"

    def create_nxautomation_user_and_group(self):
        try:
            grp.getgrnam(self.automation_user)
        except KeyError:
            # group nxautomation not found, create one
            subprocess.call(["groupadd", "-r", self.automation_user])
        try:
            pwd.getpwnam(self.automation_user)
        except KeyError:
            # user nxautomation does not exist, create one
            if subprocess.call(["useradd", "-r", "-c", "nxOMSAutomation", "-d", "/var/opt/microsoft/omsagent/run", "-g",
                             self.automation_user, "-s", "/bin/bash", self.automation_user ]) != 0:
                raise OSError("could not create %s user" %self.automation_user)
            if subprocess.call(["/usr/sbin/usermod", "-g", self.automation_user, "-a", "-G", "omsagent", "-G", "omiusers",
                                self.automation_user]) != 0:
                raise OSError("could not add %s to groups omsaget and omiusers", self.automation_user)
            if subprocess.call(["chmod", "-R", "0777", self.dummyFileLocation]) !=0:
                raise OSError("could not change permissions for dummy file")

    def remove_nxautomation_user_and_group(self):
        subprocess.call(["userdel", self.automation_user])

    def setUp(self):
        """
        Setup Test resources
        """
        if not os.path.isdir(self.temp_run_dir):
            os.mkdir(self.temp_run_dir, 0o777)
        # create nxautomation user on the machine
        self.create_nxautomation_user_and_group()
        subprocess.call(["sudo", "pkill", "-u", self.automation_user])
        shutil.copyfile(os.path.join(self.dummyFileLocation, "worker.conf"),
                        nxOMSAutomationWorker.AUTO_REGISTERED_WORKER_CONF_PATH)

    def tearDown(self):
        """
        Remove test resoruces
        """
        subprocess.call(["sudo", "pkill", "-u", self.automation_user])
        shutil.rmtree(self.temp_run_dir, ignore_errors=True)
        self.remove_nxautomation_user_and_group()


    def test_can_start_verify_kill_worker_manager(self):
        shutil.copyfile(os.path.join(self.dummyFileLocation, "oms_conf_auto_manual.conf"), nxOMSAutomationWorker.OMS_CONF_FILE_PATH)
        nxOMSAutomationWorker.start_worker_manager_process(self.workspace_id)
        pid, version = nxOMSAutomationWorker.get_worker_manager_pid_and_version(self.workspace_id)
        self.assertTrue(nxOMSAutomationWorker.is_worker_manager_running_latest_version(self.workspace_id))
        self.assertTrue(pid > 0)
        self.assertTrue(version == "1.4")

        nxOMSAutomationWorker.kill_worker_manager(self.workspace_id)
        self.assertFalse(nxOMSAutomationWorker.is_worker_manager_running_latest_version(self.workspace_id))
        pid, version = nxOMSAutomationWorker.get_worker_manager_pid_and_version(self.workspace_id)
        self.assertTrue(pid == -1)
        os.remove(nxOMSAutomationWorker.OMS_CONF_FILE_PATH)

    def test_parsing_parameters_and_creation_of_omsconf(self):
        auto_enabled_manual_enabled = "[{\"WorksapceId\":\"%s\",\"AzureDnsAgentSvcZone\":\"df-agentsvc.azure-automation.net\",\"Solutions\":{\"Updates\":{\"Enabled\":true},\"AzureAutomation\":{\"Enabled\":true,\"Parameter1\":\"PARAM_11\",\"Parameter2\":\"PARAM_12\"}}}]" %self.workspace_id
        auto_disabled_manual_enabled = "[{\"WorksapceId\":\"%s\",\"AzureDnsAgentSvcZone\":\"df-agentsvc.azure-automation.net\",\"Solutions\":{\"Updates\":{\"Enabled\":false},\"AzureAutomation\":{\"Enabled\":true,\"Parameter1\":\"PARAM_11\",\"Parameter2\":\"PARAM_12\"}}}]" %self.workspace_id
        auto_enabled_manual_disabled = "[{\"WorksapceId\":\"%s\",\"AzureDnsAgentSvcZone\":\"df-agentsvc.azure-automation.net\",\"Solutions\":{\"Updates\":{\"Enabled\":true},\"AzureAutomation\":{\"Enabled\":false,\"Parameter1\":\"PARAM_11\",\"Parameter2\":\"PARAM_12\"}}}]" %self.workspace_id
        auto_disabled_manual_disabled = "[{\"WorksapceId\":\"%s\",\"AzureDnsAgentSvcZone\":\"df-agentsvc.azure-automation.net\",\"Solutions\":{\"Updates\":{\"Enabled\":false},\"AzureAutomation\":{\"Enabled\":false,\"Parameter1\":\"PARAM_11\",\"Parameter2\":\"PARAM_12\"}}}]" %self.workspace_id

        if os.path.isfile(nxOMSAutomationWorker.OMS_CONF_FILE_PATH):
            os.remove(nxOMSAutomationWorker.OMS_CONF_FILE_PATH)
        settings = nxOMSAutomationWorker.read_settings_from_mof_json(
            auto_enabled_manual_enabled)
        nxOMSAutomationWorker.write_omsconf_file(settings.workspace_id, settings.updates_enabled, settings.diy_enabled)
        self.assertTrue(filecmp.cmp(os.path.join(self.dummyFileLocation, "oms_conf_auto_manual.conf"),
                                    nxOMSAutomationWorker.OMS_CONF_FILE_PATH))

        if os.path.isfile(nxOMSAutomationWorker.OMS_CONF_FILE_PATH):
            os.remove(nxOMSAutomationWorker.OMS_CONF_FILE_PATH)
        settings = nxOMSAutomationWorker.read_settings_from_mof_json(
            auto_disabled_manual_enabled)
        nxOMSAutomationWorker.write_omsconf_file(settings.workspace_id, settings.updates_enabled, settings.diy_enabled)
        self.assertTrue(filecmp.cmp(os.path.join(self.dummyFileLocation, "oms_conf_manual.conf"),
                                    nxOMSAutomationWorker.OMS_CONF_FILE_PATH))

        if os.path.isfile(nxOMSAutomationWorker.OMS_CONF_FILE_PATH):
            os.remove(nxOMSAutomationWorker.OMS_CONF_FILE_PATH)
        settings = nxOMSAutomationWorker.read_settings_from_mof_json(
            auto_enabled_manual_disabled)
        nxOMSAutomationWorker.write_omsconf_file(settings.workspace_id, settings.updates_enabled, settings.diy_enabled)
        self.assertTrue(filecmp.cmp(os.path.join(self.dummyFileLocation, "oms_conf_auto.conf"),
                                    nxOMSAutomationWorker.OMS_CONF_FILE_PATH))

        if os.path.isfile(nxOMSAutomationWorker.OMS_CONF_FILE_PATH):
            os.remove(nxOMSAutomationWorker.OMS_CONF_FILE_PATH)
        settings = nxOMSAutomationWorker.read_settings_from_mof_json(
            auto_disabled_manual_disabled)
        nxOMSAutomationWorker.write_omsconf_file(settings.workspace_id, settings.updates_enabled, settings.diy_enabled)
        self.assertTrue(filecmp.cmp(os.path.join(self.dummyFileLocation, "oms_conf_none.conf"),
                                    nxOMSAutomationWorker.OMS_CONF_FILE_PATH))

    def test_is_oms_config_consistent_with_mof(self):
        dummy_oms_conf_filepaths = [os.path.join(self.dummyFileLocation, "oms_conf_auto_manual.conf"),
                                    os.path.join(self.dummyFileLocation, "oms_conf_manual.conf"),
                                    os.path.join(self.dummyFileLocation, "oms_conf_auto.conf"),
                                    os.path.join(self.dummyFileLocation, "oms_conf_none.conf")
                                    ]
        valid_results = {dummy_oms_conf_filepaths[0] : [True, True],
                       dummy_oms_conf_filepaths[1] : [False, True],
                       dummy_oms_conf_filepaths[2]: [True, False],
                       dummy_oms_conf_filepaths[3]: [False, False],
                       }
        for updates_enabled in [True, False]:
            for diy_enabled in [True, False]:
                for dummy_oms_conf_file_path in dummy_oms_conf_filepaths:
                    result = nxOMSAutomationWorker.is_oms_config_consistent_with_mof(updates_enabled, diy_enabled,
                                                                                     dummy_oms_conf_file_path)
                    updates_expected_value, diy_expected_value = valid_results[dummy_oms_conf_file_path]
                    if updates_enabled == updates_expected_value and diy_enabled == diy_expected_value:
                        self.assertTrue(result)
                    else:
                        self.assertFalse(result)

    def test_get_diy_account_id(self):
        self.assertTrue(nxOMSAutomationWorker.get_diy_account_id() == "cfd4ef08-4011-428a-8947-0c2f4605980h")
        os.remove(nxOMSAutomationWorker.AUTO_REGISTERED_WORKER_CONF_PATH)
        self.assertFalse(nxOMSAutomationWorker.get_diy_account_id())

    def test_get_stray_worker_and_manager_pids(self):
        processes = ['1000 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.4',
                     '1001 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:dfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.4',
                     '1002 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/main.py /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.4',
                     '1003 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/main.py /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:efd4ef08-4011-428a-8947-0c2f4605980f 1.4',
                     '']
        stray_processes = nxOMSAutomationWorker.get_stray_worker_and_manager_wsids(processes, self.workspace_id)
        self.assertTrue(stray_processes == set(['dfd4ef08-4011-428a-8947-0c2f4605980f', 'efd4ef08-4011-428a-8947-0c2f4605980f']))

        processes = ['1000 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.4',
                     '1001 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.4',
                     '1002 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/main.py /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.4',
                     '1003 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/main.py /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.4',
                     '']
        stray_processes = nxOMSAutomationWorker.get_stray_worker_and_manager_wsids(processes, self.workspace_id)
        self.assertFalse(stray_processes)

        processes = ['']
        stray_processes = nxOMSAutomationWorker.get_stray_worker_and_manager_wsids(processes, self.workspace_id)
        self.assertFalse(stray_processes)

    def test_is_any_1_3_process_running(self):
        processes = [
            '1002 python %s /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.3' % nxOMSAutomationWorker.WORKER_MANAGER_START_PATH,
            '1003 python %s /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.4' % nxOMSAutomationWorker.WORKER_MANAGER_START_PATH,
            '']
        self.assertTrue(nxOMSAutomationWorker.is_any_1_3_process_running(processes, self.workspace_id))

        processes = ['1000 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.4',
                     '1001 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.4',
                     '1002 python %s /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.4' % nxOMSAutomationWorker.WORKER_MANAGER_START_PATH,
                     '1003 python %s /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.4' % nxOMSAutomationWorker.WORKER_MANAGER_START_PATH,
                     '']
        self.assertFalse(nxOMSAutomationWorker.is_any_1_3_process_running(processes, self.workspace_id))

        processes = [
            '1000 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.4',
            '1001 python /opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker/hybridworker.py /var/opt/microsoft/omsagent/state/automationworker/worker.conf managed rworkspace:dfd4ef08-4011-428a-8947-0c2f4605980f rversion:1.3',
            '1002 python %s /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:dfd4ef08-4011-428a-8947-0c2f4605980f 1.3' % nxOMSAutomationWorker.WORKER_MANAGER_START_PATH,
            '1003 python %s /var/opt/microsoft/omsagent/state/automationworker/oms.conf rworkspace:cfd4ef08-4011-428a-8947-0c2f4605980f 1.4' % nxOMSAutomationWorker.WORKER_MANAGER_START_PATH,
            '']
        self.assertFalse(nxOMSAutomationWorker.is_any_1_3_process_running(processes, self.workspace_id))
######################################
if __name__ == '__main__':
    s1=unittest2.TestLoader().loadTestsFromTestCase(nxUserTestCases)
    s2=unittest2.TestLoader().loadTestsFromTestCase(nxGroupTestCases)
    s3=unittest2.TestLoader().loadTestsFromTestCase(nxFileTestCases)
    s4=unittest2.TestLoader().loadTestsFromTestCase(nxScriptTestCases)
    s5=unittest2.TestLoader().loadTestsFromTestCase(nxServiceTestCases)
    s6=unittest2.TestLoader().loadTestsFromTestCase(nxPackageTestCases)
    s7=unittest2.TestLoader().loadTestsFromTestCase(nxSshAuthorizedKeysTestCases)
    s8=unittest2.TestLoader().loadTestsFromTestCase(nxEnvironmentTestCases)
    s9=unittest2.TestLoader().loadTestsFromTestCase(nxFirewallTestCases)
    s10=unittest2.TestLoader().loadTestsFromTestCase(nxArchiveTestCases)
    s11=unittest2.TestLoader().loadTestsFromTestCase(nxFileLineTestCases)
    s12=unittest2.TestLoader().loadTestsFromTestCase(nxDNSServerAddressTestCases)
    s13=unittest2.TestLoader().loadTestsFromTestCase(nxComputerTestCases)
    s14=unittest2.TestLoader().loadTestsFromTestCase(nxIPAddressTestCases)
    s15=unittest2.TestLoader().loadTestsFromTestCase(nxMySqlDatabaseTestCases)
    s16=unittest2.TestLoader().loadTestsFromTestCase(nxMySqlUserTestCases)
    s17=unittest2.TestLoader().loadTestsFromTestCase(nxMySqlGrantTestCases)
    s18=unittest2.TestLoader().loadTestsFromTestCase(nxOMSSyslogTestCases)
    s19=unittest2.TestLoader().loadTestsFromTestCase(nxOMSPerfCounterTestCases)
    s20=unittest2.TestLoader().loadTestsFromTestCase(nxOMSCustomLogTestCases)
    s21=unittest2.TestLoader().loadTestsFromTestCase(nxOMSKeyMgmtTestCases)
    s22=unittest2.TestLoader().loadTestsFromTestCase(nxFileInventoryTestCases)
    s23=unittest2.TestLoader().loadTestsFromTestCase(nxOMSGenerateInventoryMofTestCases)
    s24=unittest2.TestLoader().loadTestsFromTestCase(nxOMSAgentNPMConfigTestCases)
    s25=unittest2.TestLoader().loadTestsFromTestCase(nxOMSAutomationWorkerTestCases)
    s26=unittest2.TestLoader().loadTestsFromTestCase(nxOMSSudoCustomLogTestCases)
    alltests = unittest2.TestSuite([s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s23,s24,s25,s26])
    unittest2.TextTestRunner(stream=sys.stdout,verbosity=3).run(alltests)

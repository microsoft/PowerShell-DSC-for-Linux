#!/usr/bin/env python3
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import os
import sys
import imp
import codecs
import ctypes
import re
import inspect
import copy
import fnmatch
import base64
import _thread as thread
import socket
import hashlib
import pickle
from contextlib import contextmanager
import time
import uuid

@contextmanager
def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, encoding='utf-8' , mode=mode)
    except IOError as err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()
try:
    import unittest2
except:
    import unittest as unittest2

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
                print(k+': '+str(sd[k].value.value)+' != '+str(dd[k].value.value)+'\n')
                return False
            continue
        if type(sd[k].value) == ctypes.c_uint or type(sd[k].value) == ctypes.c_ushort :
            if sd[k].value.value==None or dd[k].value.value==None:
                continue
            if sd[k].value.value != dd[k].value.value:
                print(k+': '+str(sd[k].value.value)+' != '+str(dd[k].value.value)+'\n')
                return False
            continue
        if not deep_compare(sd[k].value, dd[k].value):  
            print(k+': '+str(sd[k].value)+' != '+str(dd[k].value)+'\n')
            return False
    return True

def deep_compare(obj1, obj2):
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
nxUser = None
nxGroup = None
nxService = None
nxPackage = None
nxOMSSyslog = None
nxOMSAgentNPMConfig = None
nxOMSCustomLog = None
nxOMSKeyMgmt = None
nxFileInventory = None
nxAvailableUpdates = None
nxNPMD = None

if os.path.exists('./Scripts/nxUser.py'):
    nxUser=imp.load_source('nxUser','./Scripts/nxUser.py') 
if os.path.exists('./Scripts/nxGroup.py'):
    nxGroup=imp.load_source('nxGroup','./Scripts/nxGroup.py') 
if os.path.exists('./Scripts/nxService.py'):
    nxService=imp.load_source('nxService','./Scripts/nxService.py') 
if os.path.exists('./Scripts/nxPackage.py'):
    nxPackage=imp.load_source('nxPackage','./Scripts/nxPackage.py') 
if os.path.exists('./Scripts/nxOMSSyslog.py'):
    nxOMSSyslog=imp.load_source('nxOMSSyslog','./Scripts/nxOMSSyslog.py')
if os.path.exists('./Scripts/nxOMSCustomLog.py'):
    nxOMSCustomLog=imp.load_source('nxOMSCustomLog','./Scripts/nxOMSCustomLog.py')
if os.path.exists('./Scripts/nxOMSKeyMgmt.py'):
    nxOMSKeyMgmt=imp.load_source('nxOMSKeyMgmt','./Scripts/nxOMSKeyMgmt.py')
if os.path.exists( './Scripts/nxFileInventory.py'):
    nxFileInventory=imp.load_source('nxFileInventory', './Scripts/nxFileInventory.py')
if os.path.exists('./Scripts/nxAvailableUpdates.py'):
    nxAvailableUpdates=imp.load_source('nxAvailableUpdates','./Scripts/nxAvailableUpdates.py') 
if os.path.exists('./Scripts/nxOMSAgentNPMConfig.py'):
    nxNPMD=imp.load_source('nxNPMD','./Scripts/nxOMSAgentNPMConfig.py')
if os.path.exists('./Scripts/nxOMSWLI.py'):
    nxWLI=imp.load_source('nxWLI','./Scripts/nxOMSWLI.py')

nxUserTestCases = None
if nxUser != None:
    class nxUserTestCases(unittest2.TestCase):
        """
        Test cases for nxUser.py
        """
        def CheckInventory(self, UserName, FullName, Description, Inventory):
            if len(Inventory['__Inventory'].value) < 1:
                return False
            for i in Inventory['__Inventory'].value:
                if UserName != None and len(UserName) and not fnmatch.fnmatch(i['UserName'].value,UserName):
                    print('UserName:' + UserName + ' != ' + i['UserName'].value)
                    return False
                if FullName != None and len(FullName) and not fnmatch.fnmatch(i['FullName'].value,FullName):
                    print('FullName:' + FullName + ' != ' + i['FullName'].value)
                    return False
                if Description != None and len(Description) and not fnmatch.fnmatch(i['Description'].value,Description):
                    print('Description:' + Description + ' != ' + i['Description'].value)
                    return False
                print('Inventory Matched: ' + repr(i))
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
        
        def testInventoryMarshallUser(self):
            r=nxUser.Inventory_Marshall("jojoma", "Present", "JO JO MA", "JOJOMA", "", False, False, "", "" )
            self.assertTrue(self.CheckInventory("jojoma", "JO JO MA", "JOJOMA", r[1]) == True, \
                            'CheckInventory("jojoma", "JO JO MA", "JOJOMA", r[1]) should == True')
    
        def testInventoryMarshallUserFilterUserName(self):
            r=nxUser.Inventory_Marshall("joj*", "", "", "", "", False, False, "", "" )
            self.assertTrue(self.CheckInventory("joj*", None, None, r[1]) == True, \
                            'CheckInventory("joj*", None, None, r[1]) should == True')
    
        def testInventoryMarshallUserFilterFullName(self):
            r=nxUser.Inventory_Marshall("", "", "JO*", "", "", False, False, "", "" )
            self.assertTrue(self.CheckInventory("", "JO*", None, r[1]) == True, \
                            'CheckInventory("", "JO*", None, r[1]) should == True')
    
        def testInventoryMarshallUserFilterDescription(self):
            r=nxUser.Inventory_Marshall("", "", "", "JO*", "", False, False, "", "" )
            self.assertTrue(self.CheckInventory("", None, "JO*", r[1]) == True, \
                            'CheckInventory("", None, "JO*", r[1]) should == True')
    
        def testInventoryMarshallUserFilterUserNameError(self):
            r=nxUser.Inventory_Marshall("yoj*", "", "", "", "", False, False, "", "" )
            self.assertTrue(self.CheckInventory("yoj*", None, None, r[1]) == False, \
                            'CheckInventory("yoj*", None, None, r[1]) should == False')
    
        def testInventoryMarshallUserFilterFullNameError(self):
            r=nxUser.Inventory_Marshall("", "", "JO*", "", "", False, False, "", "" )
            self.assertTrue(self.CheckInventory("", "YO*", None, r[1]) == False, \
                            'CheckInventory("", "YO*", None, r[1]) should == False')
    
        def testInventoryMarshallUserFilterDescriptionError(self):
            r=nxUser.Inventory_Marshall("", "", "", "YO*", "", False, False, "", "" )
            self.assertTrue(self.CheckInventory("", None, "YO*", r[1]) == False, \
                            'CheckInventory("", None, "YO*", r[1]) should == False')
    
nxGroupTestCases = None
if nxGroup != None:
    class nxGroupTestCases(unittest2.TestCase):
        """
        Test cases for nxGroup.py
        """
        def CheckInventory(self, GroupName, Inventory):
            if len(Inventory['__Inventory'].value) < 1:
                return False
            for i in Inventory['__Inventory'].value:
                if GroupName != None and len(GroupName) and not fnmatch.fnmatch(i['GroupName'].value,GroupName):
                    print('GroupName:' + GroupName + ' != ' + i['GroupName'].value)
                    return False
            print('Inventory Matched: ' + repr(i))
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
    
        def testInventory_Marshall(self):
            d=nxGroup.Inventory_Marshall("*", "", "", "", "", "")
            print(repr(d))
    
        def testSetInventory_MarshallFilterGroup(self):
            d=nxGroup.Inventory_Marshall("*mama*", "", "", "", "", "")
            self.assertTrue(self.CheckInventory("*mama*",d[1]) == True, 'self.CheckInventory("*mama*",d[1]) should == True')
    
        def testSetInventory_MarshallFilterGroupError(self):
            d=nxGroup.Inventory_Marshall("*jama*", "", "", "", "", "")
            self.assertTrue(self.CheckInventory("*jama*",d[1]) == False, \
                            'self.CheckInventory("*mama*",d[1]) should == False')
    
    
    class nxPackageTestCases(unittest2.TestCase):
        """
        Test cases for nxPackage
        """
        def setUp(self):
            """
            Setup test resources
            """
            self.pkg = 'dummy'
    
        def CheckInventory(self, Name, Inventory):
            if len(Inventory['__Inventory'].value) < 1:
                return False
            for i in Inventory['__Inventory'].value:
                if Name != None and len(Name) and not fnmatch.fnmatch(i['Name'].value,Name):
                    print('Name:' + Name + ' != ' + i['Name'].value)
                    return False
                print('Inventory Matched: ' + repr(i))
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
        
    
        def testInventoryMarshall(self):
            r=nxPackage.Inventory_Marshall('','','*','',False,'',0)
            self.assertTrue(r[0] == 0,"Inventory_Marshall('','','*','',False,'',0)  should return == [0]")
    
        def testInventoryMarshallFilterName(self):
            r=nxPackage.Inventory_Marshall('', '', self.pkg, '', False, '', 0)
            self.assertTrue(self.CheckInventory(self.pkg, r[1]) == True, \
                            'CheckInventory(self.pkg, r[1]) should == True')
            pkg = self.pkg[:3]
            pkg += '*'
            r=nxPackage.Inventory_Marshall('', '',  pkg, '', False, '', 0)
            self.assertTrue(self.CheckInventory(pkg, r[1]) == True, \
                            'CheckInventory('+ pkg + ', r[1]) should == True')
    
        def testInventoryMarshallFilterNameError(self):
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
    
nxServiceTestCases = None
if nxService != None:

    @unittest2.skipUnless(nxService.Inventory_Marshall('*', '*', None,'')[0] == \
                          0,'Error.  Skipping nxService.Inventory_Marshall tests.')
    class nxServiceTestCases(unittest2.TestCase):
        """
        Test cases for nxService
        """
        @classmethod    
        def setUpClass(cls):
            cls.srv_names = {}
            r=nxService.Inventory_Marshall('*', '*', None,'')
            for srv in r[1]['__Inventory'].value:
                if srv['State'].value == 'Running' :
                    cls.srv_names['Running'] = srv['Name'].value
                if srv['State'].value == 'Stopped' :
                    cls.srv_names['Stopped'] = srv['Name'].value
                if srv['Enabled'].value.value == True :
                    cls.srv_names['Enabled'] = srv['Name'].value
                if srv['Enabled'].value.value == False :
                    cls.srv_names['Disabled'] = srv['Name'].value
                if len(cls.srv_names.keys()) == 4:
                    break
            if len(cls.srv_names.keys()) < 4:
                for k in ['Running', 'Stopped', 'Enabled', 'Disabled']:
                    if k not in cls.srv_names.keys():
                        cls.srv_names[k] = '*'
            cls.controller = nxService.GetController()
    
        def CheckInventory(self, Name, Controller, Enabled, State, Inventory):
            if len(Inventory['__Inventory'].value) < 1:
                return False
            for i in Inventory['__Inventory'].value:
                if Name != None and len(Name) and not fnmatch.fnmatch(i['Name'].value,Name):
                    print('Name:' + Name + ' != ' + i['Name'].value)
                    return False
                if Enabled is not None and Enabled != i['Enabled'].value.value:
                    print('Enabled:' + repr(Enabled) + ' != ' + repr(i['Enabled'].value.value))
                    return False
                if State != None and len(State) and not fnmatch.fnmatch(i['State'].value,State):
                    print('State:' + State + ' != ' + i['State'].value)
                    return False
                print('Inventory Matched: ' + repr(i))
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
    
        def testInventoryMarshall(self):
            r=nxService.Inventory_Marshall('*', '*', None,'')
            self.assertTrue(r[0] == 0,"Inventory_Marshall('*', " + self.controller + ", None,'')  should return == 0")
            print(repr(r[1]))
    
        def testInventoryMarshallCmdlineError(self):
            os.system('cp  ./Scripts/nxService.py /tmp/nxServiceBroken.py')
            os.system('sed -i "s/--status-all/--atus-all/" /opt/microsoft/omsconfig/Scripts/OMSServiceStatAll.sh')
            os.system('sed -i "s/cmd = initd_chkconfig + \' --list \'/cmd = initd_chkconfig + \' --ist \'/" /tmp/nxServiceBroken.py')
            os.system('sed -i "s/cmd = \'initctl list\'/cmd = \'initctl ist\'/" /tmp/nxServiceBroken.py')
            os.system('sed -i "s/cmd = \'systemctl -a list-unit-files \'/cmd = \'systemctl -a ist-unit-files \'/" /tmp/nxServiceBroken.py')
            nxServiceBroken = imp.load_source('nxServiceBroken','/tmp/nxServiceBroken.py') 
            r=nxServiceBroken.Inventory_Marshall('*', self.controller, None,'')
            os.system('rm /tmp/nxServiceBroken.py')
            os.system('sed -i "s/--atus-all/--status-all/" /opt/microsoft/omsconfig/Scripts/OMSServiceStatAll.sh')
            self.assertTrue(r[0] == -1,"nxServiceBroken.Inventory_Marshall('*', " + self.controller + ", None,'')  should return == -1")
            print(repr(r[1]))
    
        def testInventoryMarshallControllerWildcard(self):
            r=nxService.Inventory_Marshall('*', '*', None,'')
            self.assertTrue(r[0] == 0,"Inventory_Marshall('*', '*', None,'')  should return == 0")
            print(repr(r[1]))
    
        def testInventoryMarshallControllerError(self):
            controllers = ['systemd', 'upstart', 'init']
            controllers.remove(self.controller)
            r=nxService.Inventory_Marshall('*', controllers[0], None,'')
            self.assertTrue(r[0] == -1,"Inventory_Marshall('*', " + self.controller + ", None,'')  should return == -1")
            print(repr(r[1]))
    
        def testInventoryMarshallDummyServiceFilterName(self):
            name = self.srv_names['Running']
            name = name[:-1] + '*'
            r=nxService.Inventory_Marshall(name, self.controller, None,'')
            self.assertTrue(r[0] == 0,"Inventory_Marshall(name, " + self.controller + ", None,'')  should return == 0")
            self.assertTrue(self.CheckInventory(name, self.controller, None, '', r[1]) == True, \
                            'CheckInventory(' + name + ')' + self.controller + ', None, "", r[1]) should == True')
    
        @unittest2.skipIf(nxService.UpstartExists() == True,'Not implemented in upstart')
        def testInventoryMarshallDummyServiceFilterEnabled(self):
            name = self.srv_names['Enabled']
            name = name[:-1] + '*'
            r=nxService.Inventory_Marshall(name, self.controller, True,'')
            self.assertTrue(r[0] == 0,"Inventory_Marshall(name, " + self.controller + ", True,'')  should return == 0")
            self.assertTrue(self.CheckInventory(name, self.controller, True, '', r[1]) == True, \
                            'CheckInventory(' + name + ')' + self.controller + ', True, "", r[1]) should == True')
    
        def testInventoryMarshallDummyServiceFilterState(self):
            name = self.srv_names['Running']
            name = name[:-1] + '*'
            r=nxService.Inventory_Marshall(name, self.controller, None,'Running')
            self.assertTrue(r[0] == 0,"Inventory_Marshall(name, " + self.controller + ", None,'Running')  should return == 0")
            self.assertTrue(self.CheckInventory(name, self.controller, None, 'Running', r[1]) == True, \
                            'CheckInventory(' + name + ')' + self.controller + ', None, "Running", r[1]) should == True')
    
        def testInventoryMarshallDummyServiceFilterNameError(self):
            name = self.srv_names['Running']
            name = 'gummy' + name
            r=nxService.Inventory_Marshall(name, self.controller, None,'')
            self.assertTrue(r[0] == 0, "Inventory_Marshall(" + name + ", " + self.controller + ", None,'')  should return == 0")
    
        def testInventoryMarshallDummyServiceFilterEnabledError(self):
            name = self.srv_names['Enabled']
            name = name[:-1] + '*'
            r=nxService.Inventory_Marshall(name, self.controller, False,'')
            self.assertTrue(r[0] == 0,"Inventory_Marshall(name, " + self.controller + ", False,'')  should return == 0")
            self.assertTrue(self.CheckInventory(name, self.controller, False, '', r[1]) == False, \
                            'CheckInventory(' + name + ')' + self.controller + ', False, "", r[1]) should == False')
    
        def testInventoryMarshallDummyServiceFilterStateError(self):
            name = self.srv_names['Running']
            name = name[:-1] + '*'
            r=nxService.Inventory_Marshall(name, self.controller, None,'Stopped')
            self.assertTrue(r[0] == 0,"Inventory_Marshall(name, " + self.controller + ", None,'Stopped')  should return == 0")
            self.assertTrue(self.CheckInventory(name, self.controller, None, 'Stopped', r[1]) == False, \
                            'CheckInventory(' + name + ')' + self.controller + ', None, "Stopped", r[1]) should == False')
    
        def testInventoryMarshallNoStderr(self):
            code, out = nxService.RunGetOutputNoStderr('ls -l /tmp/bad/path', False, True)
            self.assertTrue(code !=0 and len(out) == 0, "code, out = nxService.RunGetOutputNoStderr('ls -l /tmp/bad/path', False, True) \
            should be code !=0 and len(out) == 0")
    
OMSSyslog_setup_txt = """import os,sys
if os.path.exists('/etc/rsyslog.d/'):
    if os.path.exists('/etc/rsyslog.d/95-omsagent.conf'):
        os.system('cp -a /etc/rsyslog.d/95-omsagent.conf /etc/rsyslog.d/95-omsagent.conf.bak')
        os.system('cp -a /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf.bak')
elif os.path.exists('/etc/rsyslog.conf'):
    os.system('cp -a /etc/rsyslog.conf /etc/rsyslog.conf.bak')
    os.system('cp -a /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf.bak')
elif os.path.exists('/etc/syslog.conf'):
    os.system('cp -a /etc/syslog.conf /etc/syslog.conf.bak')
    os.system('cp -a /etc/opt/omi/conf/omsconfig/sysklog-oms.conf /etc/opt/omi/conf/omsconfig/sysklog-oms.conf.bak')
elif os.path.exists('/etc/syslog-ng/syslog-ng.conf'):
    os.system('cp -a /etc/syslog-ng/syslog-ng.conf /etc/syslog-ng/syslog-ng.conf.bak')
    os.system('cp -a /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf.bak')            
"""
OMSSyslog_teardown_txt = """import os,sys
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
"""
    
nxOMSSyslogTestCases = None
if nxOMSSyslog != None:
    class nxOMSSyslogTestCases(unittest2.TestCase):
        """
        Test cases for nxOMSSyslog.py
        """
        def setUp(self):
            """
            Setup test resources
            """
            self.workspace_id = str(uuid.uuid4())
            os.system('/bin/echo -e "' + OMSSyslog_setup_txt + '" | sudo python3')
            
        def tearDown(self):
            """
            Remove test resources.
            """
            os.system('/bin/echo -e "' + OMSSyslog_teardown_txt + '" | sudo python3')
    
        def make_MI(self, retval, SyslogSource, WorkspaceID):
            d=dict()
            d.clear()
            if SyslogSource == None :
                d['SyslogSource'] = None
            else :
                for source in SyslogSource:
                    source['Severities'] = nxOMSSyslog.protocol.MI_StringA(source['Severities'])
                    source['Facility']=nxOMSSyslog.protocol.MI_String(source['Facility'])
                d['SyslogSource'] = nxOMSSyslog.protocol.MI_InstanceA(SyslogSource)
            d['WorkspaceID'] = nxOMSSyslog.protocol.MI_String(WorkspaceID)
            return retval, d
        
        def testSetOMSSyslog_add(self):
            d={'SyslogSource': [{'Facility': 'kern','Severities': ['emerg','crit','warning']},{'Facility': 'auth','Severities': ['emerg','crit','warning']}] }
            d['WorkspaceID'] = self.workspace_id
            self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 
    
        def testTestSetOMSSyslog_add(self):
            d={'SyslogSource': [{'Facility': 'kern','Severities': ['emerg','crit','warning']},{'Facility': 'auth','Severities': ['emerg','crit','warning']}] }
            d['WorkspaceID'] = self.workspace_id
            self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set_Marshall('+repr(d)+') should return == [0]') 
            self.assertTrue(nxOMSSyslog.Test_Marshall(**d) == [0],'Test_Marshall('+repr(d)+') should return == [0]') 
    
        def testGetOMSSyslog_add(self):
            d={'SyslogSource': [{'Facility': 'auth','Severities': ['crit','emerg','warning']},{'Facility': 'kern','Severities': ['crit','emerg','warning']}] }
            d['WorkspaceID'] = self.workspace_id
            e=copy.deepcopy(d)
            t=copy.deepcopy(d)
            self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
            m=self.make_MI(0,**e)
            g=nxOMSSyslog.Get_Marshall(**t)
            print('GET '+ repr(g) )
            self.assertTrue(check_values(g, m)  ==  True, 'Get('+repr(g)+' should return ==['+repr(m)+']')
    
        def testSetOMSSyslog_del(self):
            d={'SyslogSource': [{'Facility': 'kern','Severities': None },{'Facility': 'auth','Severities': None }] }
            d['WorkspaceID'] = self.workspace_id
            self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]') 
    
        def testGetOMSSyslog_del(self):
            d={'SyslogSource': [{'Facility': 'auth','Severities': None },{'Facility': 'kern','Severities': None }] }
            d['WorkspaceID'] = self.workspace_id
            e=copy.deepcopy(d)
            t=copy.deepcopy(d)
            self.assertTrue(nxOMSSyslog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
            m=self.make_MI(0,**t)
            g=nxOMSSyslog.Get_Marshall(**e)
            print('GET '+ repr(g))
            self.assertTrue(check_values(g, m)  ==  True, 'Get('+repr(g)+' should return ==['+repr(m)+']')

nxOMSCustomLog_setup_txt = """import os
os.system('rm -rf ./ut_customlog.conf')
"""
nxOMSCustomLogTestCases = None
if nxOMSCustomLog != None:
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
            os.system('/bin/echo -e "' + nxOMSCustomLog_setup_txt + '" | sudo python3')
    
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
            print('GET '+ repr(g))
            self.assertTrue(check_values(g, m)  ==  True, \
            'Get('+repr(g)+' should return ==['+repr(m)+']')
    
        def testGetOMSCustomLog_del(self):
            d = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
            self.assertTrue(nxOMSCustomLog.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
            t = { 'Name': 'SimpleCustomLog', 'EnableCustomLogConfiguration': True, 'CustomLogObjects': None }
            m=self.make_MI(0,**t)
            g=nxOMSCustomLog.Get_Marshall(**d)
            print('GET '+ repr(g))
            self.assertTrue(check_values(g, m)  ==  True, \
            'Get('+repr(g)+' should return ==['+repr(m)+']')
    
nxOMSKeyMgmt_cls_setup_txt = """import os
if not os.path.exists(cls.conf_dir):
    os.system('mkdir -p ' + cls.conf_dir + ' 2>&1 >/dev/null')
os.system('cp -a  /etc/opt/omi/conf/omsconfig/keymgmtring.gpg  \
          /etc/opt/omi/conf/omsconfig/keymgmtring.gpg.bak 2>&1 >/dev/null')
os.system('cp -a /etc/opt/omi/conf/omsconfig/keyring.gpg \
          /etc/opt/omi/conf/omsconfig/keyring.gpg.bak 2>&1 >/dev/null')
"""
nxOMSKeyMgmt_cls_teardown_txt = """import os
os.system('cp -a /etc/opt/omi/conf/omsconfig/keymgmtring.gpg.bak \
/etc/opt/omi/conf/omsconfig/keymgmtring.gpg 2>&1 >/dev/null')
os.system('cp -a /etc/opt/omi/conf/omsconfig/keyring.gpg.bak \
/etc/opt/omi/conf/omsconfig/keyring.gpg 2>&1 >/dev/null')
"""
nxOMSKeyMgmt_setup_txt = """import os
os.system('cp -a ./Scripts/Tests/test_mofs/keymgmtring.gpg \
/etc/opt/omi/conf/omsconfig/keymgmtring.gpg 2>&1 >/dev/null')
os.system('cp -a ./Scripts/Tests/test_mofs/keyring.gpg \
/etc/opt/omi/conf/omsconfig/keyring.gpg 2>&1 >/dev/null')
"""
    
nxOMSKeyMgmtTestCases = None
if nxOMSKeyMgmt != None:
    # omsagent is not required to  be running.
    class nxOMSKeyMgmtTestCases(unittest2.TestCase):
        """
        Test cases for nxOMSKeyMgmt.py
        """
        @classmethod    
        def setUpClass(cls):
            key_txt = (open('./Scripts/Tests/test_mofs/testdsckey.pub','r').read())
            sig_txt = (open('./Scripts/Tests/test_mofs/testdsckey.asc','r').read())
            os.system('/bin/echo -e "' + nxOMSKeyMgmt_cls_setup_txt + '" | sudo python3')
            cls.keymgmt = {'KeyContents': key_txt, \
                           'KeySignature': sig_txt, 'Ensure':'present'}
            cls.conf_dir = '/etc/opt/omi/conf/omsconfig'
    
        @classmethod
        def tearDownClass(cls):
            os.system('/bin/echo -e "' + nxOMSKeyMgmt_cls_teardown_txt + '" | sudo python3')
            
    
        
        def setUp(self):
            """
            Setup test resources
            """
            os.system('/bin/echo -e "' + nxOMSKeyMgmt_setup_txt + '" | sudo python3')
            
    
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

nxFileInventoryTestCases = None
if nxFileInventory != None:
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
                b'\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
            open(cls.basepath+'joedir0/joedir0file1.txt','w+').write(\
                'Contents of joedir0file1.txt\n')
            open(cls.basepath+'joedir0/joedir0file2.txt','w+').write(\
                'Contents of joedir0file2.txt\n')
            open(cls.basepath+'joedir0/joedir0file3.bin','wb+').write(\
                b'\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
            open(cls.basepath+'joedir0/joedir1/joedir1file1.txt','w+').write(\
                'Contents of joedir1file1.txt\n')
            open(cls.basepath+'joedir0/joedir1/joedir1file2.txt','w+').write(\
                'Contents of joedir1file2.txt\n')
            open(cls.basepath+'joedir0/joedir1/joedir1file3.bin','wb+').write(\
                b'\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
            open(cls.basepath+'joedir0/joedir1/joedir2/joedir2file1.txt','w+').write(\
                'Contents of joedir2file1.txt\n')
            open(cls.basepath+'joedir0/joedir1/joedir2/joedir2file2.txt','w+').write(\
                'Contents of joedir2file2.txt\n')
            open(cls.basepath+'joedir0/joedir1/joedir2/joedir2file3.bin','wb+').write(\
                b'\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
            os.makedirs(cls.basepath+'bobdir0/bobdir1/bobdir2/')
            open(cls.basepath+'bobdir0/bobdir0file1.txt','w+').write(\
                'Contents of bobdir0file1.txt\n')
            open(cls.basepath+'bobdir0/bobdir0file2.txt','w+').write(\
                'Contents of bobdir0file2.txt\n')
            open(cls.basepath+'bobdir0/bobdir0file3.bin','wb+').write(\
                b'\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
            open(cls.basepath+'bobdir0/bobdir1/bobdir1file1.txt','w+').write(\
                'Contents of bobdir1file1.txt\n')
            open(cls.basepath+'bobdir0/bobdir1/bobdir1file2.txt','w+').write(\
                'Contents of bobdir1file2.txt\n')
            open(cls.basepath+'bobdir0/bobdir1/bobdir1file3.bin','wb+').write(\
                b'\xff\xff\xfe\x00\xfe\x00\xff\x00\x00\x00')
            open(cls.basepath+'bobdir0/bobdir1/bobdir2/bobdir2file1.txt','w+').write(\
                'Contents of bobdir2file1.txt\n')
            open(cls.basepath+'bobdir0/bobdir1/bobdir2/bobdir2file2.txt','w+').write(\
                'Contents of bobdir2file2.txt\n')
            open(cls.basepath+'bobdir0/bobdir1/bobdir2/bobdir2file3.bin','wb+').write(\
                b'\xff\xfe\x00\x00\xff\xfd\x00\x00\x00\x00')
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
            print('Using path:' + self.basepath )
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
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallTypeWild(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallDirRecurse(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallFileRecurse(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallTypeWildRecurse(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildDir(self):
            print('Using path:' + self.basepath +'*dir*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildFile(self):
            print('Using path:' + self.basepath +'*/*file*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildTypeWild(self):
            print('Using path:' + self.basepath +'*/*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildDirRecurse(self):
            print('Using path:' + self.basepath +'*/*dir*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildFileRecurse(self):
            print('Using path:' + self.basepath +'*/*file*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildTypeWildRecurse(self):
            print('Using path:' + self.basepath +'*/*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallDirFollowLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallFileFollowLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallTypeWildFollowLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallDirRecurseFollowLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallFileRecurseFollowLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallTypeWildRecurseFollowLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildDirFollowLink(self):
            print('Using path:' + self.basepath +'*dir*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildFileFollowLink(self):
            print('Using path:' + self.basepath +'*/*file*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildTypeWildFollowLink(self):
            print('Using path:' + self.basepath +'*/*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildDirRecurseFollowLink(self):
            print('Using path:' + self.basepath +'*/*dir*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildFileRecurseFollowLink(self):
            print('Using path:' + self.basepath +'*/*file*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildTypeWildRecurseFollowLink(self):
            print('Using path:' + self.basepath +'*/*')
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
                print(d['DestinationPath'], d['Contents'])
    
    
        def testFileInventoryInventory_MarshallDirManageLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallFileManageLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallTypeWildManageLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallDirRecurseManageLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallFileRecurseManageLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallTypeWildRecurseManageLink(self):
            print('Using path:' + self.basepath )
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildDirManageLink(self):
            print('Using path:' + self.basepath +'*dir*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildFileManageLink(self):
            print('Using path:' + self.basepath +'*/*file*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildTypeWildManageLink(self):
            print('Using path:' + self.basepath +'*/*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildDirRecurseManageLink(self):
            print('Using path:' + self.basepath +'*/*dir*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildFileRecurseManageLink(self):
            print('Using path:' + self.basepath +'*/*file*')
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
                print(d['DestinationPath'], d['Contents'])
    
        def testFileInventoryInventory_MarshallWildTypeWildRecurseManageLink(self):
            print('Using path:' + self.basepath +'*/*')
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
                print(d['DestinationPath'], d['Contents'])

nxOMSAgentNPMConfigTestCases = None
if nxNPMD != None:
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
            nxNPMD.SERVER_ADDRESS = '/var/tmp/npm_state/npmdagent.sock'
            nxNPMD.DSC_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
            nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/AGENTVERSION'
            nxNPMD.PLUGIN_PATH = '/var/tmp/opt/microsoft/omsagent/plugin/'
            nxNPMD.PLUGIN_CONF_PATH = '/var/tmp/etc/opt/microsoft/omsagent/conf/omsagent.d/'
            nxNPMD.AGENT_BINARY_PATH = '/var/tmp/opt/microsoft/omsagent/'
            nxNPMD.RESOURCE_MODULE_PATH = '/var/tmp/opt/microsoft/omsconfig/modules/NPM/'
            nxNPMD.AGENT_SCRIPT_PATH = '/var/tmp/etc/opt/microsoft/omsagent/scipt.sh'
    
            self.config_type = 'UpdatedAgentConfig'
            self.config_id = '12345'
            self.contents = base64.b64encode(b'<Configuration></Configuration>')
            self.content_checksum = hashlib.md5(self.contents).hexdigest().upper()
            self.ensure_present = 'Present'
            self.ensure_absent = 'Absent'
            self.out_file = nxNPMD.CONFIG_PATH.__add__(nxNPMD.DEST_FILE_NAME)
            self.server_address = nxNPMD.SERVER_ADDRESS
            self.server_read_data = ''
            self.server_bound = False
            self.server_read_retries = 5
            self.server_bound_retries = 5
    
    
            x64binaryPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_X64_AGENT_PATH)
            x86binaryPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_X86_AGENT_PATH)
            dscPluginPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_PLUGIN_PATH)
            dscConfPath = nxNPMD.RESOURCE_MODULE_PATH.__add__(nxNPMD.DSC_PLUGIN_CONF_PATH)
            
            # remove files from directory
            os.system('rm -rf /var/tmp/npm_state;' +
                'rm -rf /var/tmp/etc;'
                'rm -rf /var/tmp/opt;'
            )
            os.system('mkdir -p ' + nxNPMD.CONFIG_PATH + ';'
                'mkdir -p ' + '/var/tmp/npm_state/' + ';'
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
            os.system('rm -rf /var/tmp/npm_state;' +
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
            except IOError as error:
                print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
            return content
    
        def createUDSServer(self):
            # Make sure the socket does not already exist
            try:
                if os.path.exists(self.server_address):
                    os.unlink(self.server_address)
            except OSError:
                if os.path.exists(self.server_address):
                    raise
    
            # Reset the socket read data
            self.server_read_data = ''
            # Create a UDS socket
            sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    
            # Bind the socket to the port
            sock.bind(self.server_address)
    
            # Listen for incoming connections
            sock.listen(socket.SOMAXCONN)
            self.server_bound = True
    
            while True:
                connection, client_address = sock.accept()
                try:
                    # Receive the data in small chunks and retransmit it
                    while True:
                        data = connection.recv(100)
                        if not data:
                            break
                        else:
                            self.server_read_data += data.decode('utf-8')
                finally:
                    # Clean up the connection
                    connection.close()
    
        def verifyFileContents(self, text):
            content = self.readFile(nxNPMD.AGENT_BINARY_PATH.__add__('binary'))
            print(content, text)
            self.assertTrue(content == text, 'Contents written to file do not match')
            content = self.readFile(nxNPMD.PLUGIN_PATH.__add__('plugin'))
            self.assertTrue(content == text, 'Contents written to file do not match')
            content = self.readFile(nxNPMD.PLUGIN_CONF_PATH.__add__('config'))
            self.assertTrue(content == text, 'Contents written to file do not match')
    
        def verifySocketRead(self, text):
            if text in self.server_read_data:
                return True
            return False
    
        def updateFileContents(self, text):
            with open(nxNPMD.AGENT_BINARY_PATH.__add__('binary'), 'w+') as dFile:
                dFile.write(text)
            with open(nxNPMD.PLUGIN_PATH.__add__('plugin'), 'w+') as dFile:
                dFile.write(text)
            with open(nxNPMD.PLUGIN_CONF_PATH.__add__('config'), 'w+') as dFile:
                dFile.write(text)
    
        def testSendDiagnosticLog(self):
            #check that the UDS server is bound
            retry = 0
            while not self.server_bound and retry < self.server_bound_retries:
                time.sleep(1)
                retry += 1
            self.assertTrue(retry <= self.server_bound_retries,
                    'Server at ' + self.server_address + ' should be bound')

            #create the diagnostic logging util object
            DLOG = nxNPMD.NPMDiagnosticLogUtil()
            testStr = 'This is a test log string'

            #emit the log
            DLOG.log(nxNPMD.LogType.Error, testStr)

            #check that some log has arrived
            retry = 0
            while len(self.server_read_data) == 0 and retry < self.server_read_retries:
                time.sleep(1)
                retry += 1
            self.assertTrue(retry <= self.server_read_retries,
                    'Some data should be emitted to the server')

            #check that test log is part of emit
            self.assertTrue(self.verifySocketRead(testStr),
                    'Given test string should have been emitted to UDS server')
   
        def testGetUpdateAgentConfig(self):
            r=nxNPMD.Get_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
            print(r)
            print(self.make_MI([0], self.config_type, self.config_id, base64.b64decode(self.contents), self.ensure_present, self.content_checksum))
            self.assertTrue(check_values(r,self.make_MI([0], self.config_type, self.config_id, base64.b64decode(self.contents), self.ensure_present, self.content_checksum)) == True,'nxNPMD.Get_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)[0] should return == 0')
    
    
        def testTestNewAgentConfig(self):
            # disables check for binary update
            nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
            r=nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
            print(r)
            self.assertTrue(r == [-1],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')
    
        def testTestUpdateConfigChecksumMismatch(self):
            # disables check for binary update
            nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
            nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
            r=nxNPMD.Test_Marshall(self.config_type, self.config_id, base64.b64encode('New config string'), self.ensure_present, self.content_checksum)
            print(r)
            self.assertTrue(r == [0],'nxNPMD.Test_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')
    
        def testTestUpdateNewConfig(self):
            # disables check for binary update
            nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
            nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
            newContent = 'New config string'
            newChecksum = hashlib.md5(base64.b64encode(newContent)).hexdigest().upper()
            r=nxNPMD.Test_Marshall(self.config_type, self.config_id, base64.b64encode(newContent), self.ensure_present, newChecksum)
            print(r)
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
            print(r)
            self.assertTrue(r == [0],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == 0')
            content = self.readFile(self.out_file)
            self.assertTrue(content == base64.b64decode(self.contents), 'Contents written to file do not match')
    
        def testSetUpdateConfigChecksumMismatch(self):
            # disables check for binary update
            nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
            newStr = 'New config string'
            r=nxNPMD.Set_Marshall(self.config_type, self.config_id, base64.b64encode(newStr), self.ensure_present, self.content_checksum)
            print(r)
            self.assertTrue(r == [-1],'nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum) should return == -1')
            content = self.readFile(self.out_file)
            print(content)
            self.assertTrue(content != newStr, 'Contents written to file do not match')
    
        def testSetUpdateNewConfig(self):
            # disables check for binary update
            nxNPMD.AGENT_RESOURCE_VERSION_PATH = '/var/tmp/etc/opt/microsoft/omsagent/VERSION'
            nxNPMD.Set_Marshall(self.config_type, self.config_id, self.contents, self.ensure_present, self.content_checksum)
            newContent = 'New config string'
            newChecksum = hashlib.md5(base64.b64encode(newContent)).hexdigest().upper()
            r=nxNPMD.Set_Marshall(self.config_type, self.config_id, base64.b64encode(newContent), self.ensure_present, newChecksum)
            print(r)
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
    
nxOMSWLITestCases = None
if nxWLI != None:
    class nxOMSWLITestCases(unittest2.TestCase):

        class TestOMSAgentUtil(nxWLI.IOMSAgent):
            def restart_oms_agent(self, workspaceId):
                return True

        class TestLOG(object):
            def Log(self, log_type, msg):
                pass

        def assignDirectories(self):
            self.dir_test_staging = 'tmp'

            nxWLI.RESOURCE_MODULE_PATH = os.path.join(self.dir_test_staging, 'dsc/WLI/')
            nxWLI.PLUGIN_RPATH = 'plugins/'
            nxWLI.CONF_RPATH = 'conf/'

            nxWLI.PLUGIN_DEST_PATH = os.path.join(self.dir_test_staging, 'plugin/')
            nxWLI.CONF_DEST_PATH_PREFIX = os.path.join(self.dir_test_staging, 'conf/')
            nxWLI.CONF_DEST_PATH_SUFFIX = '/omsagent.d/'

            common_plugin_rpath = nxWLI.PLUGIN_RPATH + 'common/'
            baseos_conf_rpath = nxWLI.CONF_RPATH + 'baseOS/'
            self.dsc_common_plugin_path = os.path.join(nxWLI.RESOURCE_MODULE_PATH, common_plugin_rpath)
            self.dsc_baseos_conf_path = os.path.join(nxWLI.RESOURCE_MODULE_PATH, baseos_conf_rpath)

            self.workspace_id_01 = str(uuid.uuid4())
            self.workspace_id_02 = str(uuid.uuid4())

        def removeDirectories(self):
            if os.path.exists(self.dir_test_staging):
                shutil.rmtree(self.dir_test_staging)

        def createDirectories(self):
            os.makedirs(nxWLI.PLUGIN_DEST_PATH)
            os.makedirs(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_01 + nxWLI.CONF_DEST_PATH_SUFFIX))
            os.makedirs(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_02 + nxWLI.CONF_DEST_PATH_SUFFIX))

            os.makedirs(self.dsc_common_plugin_path)
            os.makedirs(self.dsc_baseos_conf_path)

        def setupFiles(self):
            fake_plugin_path = os.path.join(self.dsc_common_plugin_path, 'fake_plugin.rb')
            self.writeFile(fake_plugin_path, 'This is a fake plugin')

            fake_conf_path = os.path.join(self.dsc_baseos_conf_path, 'fake_conf.conf')
            self.writeFile(fake_conf_path, 'This a fake config')

        def writeFile(self, path, content):
            f = open(path, 'w+')
            f.write(content)
            f.close()

        def make_MI(self, retval, WorkspaceId, Configuration):
            d=dict();
            if WorkspaceId == None :
                d['WorkspaceId'] = None
            else :
                d['WorkspaceId'] = nxNPMD.protocol.MI_String(WorkspaceId)
            if Configuration == None :
                d['Configuration'] = None
            else :
                d['Configuration'] = nxNPMD.protocol.MI_String(Configuration)
            return retval,d

        def setUp(self):
            try:
                self.assignDirectories()
                self.removeDirectories()
                self.createDirectories()
                self.setupFiles()
            except IOError as error:
                # raise error if setup itself failed
                self.assertTrue(False, "Setting filesystem for test cases failed!:" + error.message + ':' + error.strerror)

            nxWLI.OMS_ACTION = nxOMSAgentNPMConfigTestCases.TestOMSAgentUtil()
            nxWLI.LG = nxOMSWLITestCases.TestLOG

            self.enable_config = '{\"WLIConfiguration\":[{\"WorkloadName\":\"baseOS\",\"Ensure\":\"Present\",\"Plugin\":\"common\"}]}'
            self.disable_config = '{\"WLIConfiguration\":[{\"WorkloadName\":\"baseOS\",\"Ensure\":\"Absent\",\"Plugin\":\"common\"}]}'

        def tearDown(self):
            """
            Remove test resources.
            """
            try:
                self.removeDirectories()
            except IOError as error:
                self.assertTrue(False, "Cleanup of filesystem in tear down failed!" + error.message + ':' + error.strerror)

        def testTestMarshall(self):
            r = nxWLI.Test_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [-1], 'Test Failed')
            r = nxWLI.Test_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(r == [0], 'Test Failed')

        def testSetMarshall(self):
            r = nxWLI.Test_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [-1], 'Test Failed')
            r = nxWLI.Set_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [0], 'Set Failed')
            r = nxWLI.Test_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [0], 'Test Failed')

        def testFiles(self):
            r = nxWLI.Test_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [-1], 'Test Failed')
            r = nxWLI.Set_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [0], 'Set Failed')

            self.assertTrue(os.path.isfile(os.path.join(nxWLI.PLUGIN_DEST_PATH, 'fake_plugin.rb')), 'Plugin file should be present')
            self.assertTrue(os.path.isfile(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_01 + nxWLI.CONF_DEST_PATH_SUFFIX, 'fake_conf.conf')), 'Conf file should be present')

            r = nxWLI.Test_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [0], 'Test Failed')

            r = nxWLI.Set_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(r == [0], 'Set Failed')

            self.assertTrue(not os.path.isfile(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_01 + nxWLI.CONF_DEST_PATH_SUFFIX, 'fake_conf.conf')), 'Conf file should not be present')

            r = nxWLI.Test_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(r == [0], 'Test Failed')

        def testGetMarshall(self):
            enable_get_config = '[{\'WorkloadName\': \'baseOS\', \'Ensure\': \'Present\'}]'
            disable_get_config = '[{\'WorkloadName\': \'baseOS\', \'Ensure\': \'Absent\'}]'
            enable_get_config_rev = '[{\'Ensure\': \'Present\', \'WorkloadName\': \'baseOS\'}]'
            disable_get_config_rev = '[{\'Ensure\': \'Absent\', \'WorkloadName\': \'baseOS\'}]'

            r = nxWLI.Get_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(check_values(r, self.make_MI(0, self.workspace_id_01, disable_get_config)) or\
                            check_values(r, self.make_MI(0, self.workspace_id_01, disable_get_config_rev)))

            r = nxWLI.Set_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [0], 'Set Failed')

            r = nxWLI.Get_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(check_values(r, self.make_MI(0, self.workspace_id_01, enable_get_config)) or\
                            check_values(r, self.make_MI(0, self.workspace_id_01, enable_get_config_rev)))

            r = nxWLI.Set_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(r == [0], 'Set Failed')

            r = nxWLI.Get_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(check_values(r, self.make_MI(0, self.workspace_id_01, disable_get_config)) or\
                            check_values(r, self.make_MI(0, self.workspace_id_01, disable_get_config_rev)))

        def testMultipleWorkspaces(self):
            r = nxWLI.Test_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [-1], 'Test Failed')
            r = nxWLI.Set_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [0], 'Set Failed')

            r = nxWLI.Test_Marshall(self.workspace_id_02, self.enable_config)
            self.assertTrue(r == [-1], 'Test Failed')
            r = nxWLI.Set_Marshall(self.workspace_id_02, self.enable_config)
            self.assertTrue(r == [0], 'Set Failed')

            self.assertTrue(os.path.isfile(os.path.join(nxWLI.PLUGIN_DEST_PATH, 'fake_plugin.rb')), 'Plugin file should be present')
            self.assertTrue(os.path.isfile(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_01 + nxWLI.CONF_DEST_PATH_SUFFIX, 'fake_conf.conf')), 'Conf file should be present')

            self.assertTrue(os.path.isfile(os.path.join(nxWLI.PLUGIN_DEST_PATH, 'fake_plugin.rb')), 'Plugin file should be present')
            self.assertTrue(os.path.isfile(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_02 + nxWLI.CONF_DEST_PATH_SUFFIX, 'fake_conf.conf')), 'Conf file should be present')

            r = nxWLI.Test_Marshall(self.workspace_id_01, self.enable_config)
            self.assertTrue(r == [0], 'Test Failed')

            r = nxWLI.Test_Marshall(self.workspace_id_02, self.enable_config)
            self.assertTrue(r == [0], 'Test Failed')

            r = nxWLI.Set_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(r == [0], 'Set Failed')

            r = nxWLI.Set_Marshall(self.workspace_id_02, self.disable_config)
            self.assertTrue(r == [0], 'Set Failed')

            self.assertTrue(not os.path.isfile(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_01 + nxWLI.CONF_DEST_PATH_SUFFIX, 'fake_conf.conf')), 'Conf file should not be present')

            self.assertTrue(not os.path.isfile(os.path.join(nxWLI.CONF_DEST_PATH_PREFIX, self.workspace_id_02 + nxWLI.CONF_DEST_PATH_SUFFIX, 'fake_conf.conf')), 'Conf file should not be present')

            r = nxWLI.Test_Marshall(self.workspace_id_01, self.disable_config)
            self.assertTrue(r == [0], 'Test Failed')

            r = nxWLI.Test_Marshall(self.workspace_id_02, self.disable_config)
            self.assertTrue(r == [0], 'Test Failed')

######################################
if __name__ == '__main__':
    tests = []
    if nxUserTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxUserTestCases))
    if nxGroupTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxGroupTestCases))
    if nxServiceTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxServiceTestCases))
    if nxPackageTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxPackageTestCases))
    if nxOMSSyslogTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxOMSSyslogTestCases))
    if nxOMSAgentNPMConfigTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxOMSAgentNPMConfigTestCases))
    if nxOMSCustomLogTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxOMSCustomLogTestCases))
    if nxOMSKeyMgmtTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxOMSKeyMgmtTestCases))
    if nxFileInventoryTestCases != None :
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxFileInventoryTestCases))
    if nxOMSWLITestCases != None:
        tests.append(unittest2.TestLoader().loadTestsFromTestCase(nxOMSWLITestCases))
    alltests = unittest2.TestSuite(tests)
    unittest2.TextTestRunner(stream=sys.stdout,verbosity=3).run(alltests)

#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import os
import sys
import imp
import ctypes
import shutil

try:
    import unittest2
except:
    os.system('tar -zxvf ./unittest2-0.5.1.tar.gz')
    sys.path.append(os.path.realpath('./unittest2-0.5.1'))
    import unittest2

sys.path.append('.:'+os.path.realpath('./Scripts'))
os.chdir('../..')
nxOMSPlugin=imp.load_source('nxOMSPlugin', './Scripts/nxOMSPlugin.py')

class nxOMSPluginTestCases(unittest2.TestCase):
    """
    Test cases for nxOMSPlugin.py
    """
    def setUp(self):
        """
        Setup test resources
        """
        nxOMSPlugin.PLUGIN_MODULE_PATH = '/var/tmp/Plugins'
        nxOMSPlugin.PLUGIN_PATH = '/var/tmp/opt/microsoft/omsagent/plugin/'
        nxOMSPlugin.CONF_PATH = '/var/tmp/etc/opt/microsoft/omsagent/conf/omsagent.d/'
        nxOMSPlugin.CONF_PREFIX = '/var/tmp/etc/opt/microsoft/omsagent'
        nxOMSPlugin.CONF_ROOT = '/var/tmp/etc'
        nxOMSPlugin.STATE_ROOT = '/var/tmp/var'
        nxOMSPlugin.DIAG_PLUGINS = ['diag_plugin_placeholder.rb']
        nxOMSPlugin.OMS_ACTION = nxOMSPlugin.TestOMSAgent()
        nxOMSPlugin.DIAG_ACTION = nxOMSPlugin.TestDiagLog()
        nxOMSPlugin.ws_counter = 0
        nxOMSPlugin.ws_prefix = '1412ce08-ac39-4792-9b8c-'
        nxOMSPlugin.ws_suffix_list = ['e57c46a8b3b1', '0605a3267245', '02ecb4078542', '3e86f66b7625', 'b2ba2a13fc58', 'f2a99731a5c2', '0a8509df1488', '4c6f5542c6d4', 'f59efac90bc0', '1104891b4cb1', 'e4b400b33ef6', '3f218d77869b', 'ae2cb6dc6d41', '4997020e7a88']
        # remove files from directory
        os.system('rm -rf /var/tmp/Plugins;' +
            'rm -rf /var/tmp/etc;'
            'rm -rf /var/tmp/opt;'
        )
        
        os.system('rm -f -rf /var/tmp/Plugins;' +
            'mkdir -p ' + nxOMSPlugin.PLUGIN_PATH + ';'
            'mkdir -p ' + nxOMSPlugin.CONF_PATH + ';'
            'mkdir /var/tmp/Plugins;' +
            'mkdir /var/tmp/Plugins/Common;' +
            'mkdir /var/tmp/Plugins/Common/plugin;' +
            'echo out_ods plugin >> /var/tmp/Plugins/Common/plugin/out_oms.rb;' +
            'echo out_ods customlog plugin >> /var/tmp/Plugins/Common/plugin/out_oms_blob.rb;' +
            'mkdir /var/tmp/Plugins/BlueStripe;' +
            'mkdir /var/tmp/Plugins/BlueStripe/plugin;' +
            'echo bsplugin >> /var/tmp/Plugins/BlueStripe/plugin/in_bluestripe.rb;' +
            'mkdir /var/tmp/Plugins/BlueStripe/conf;' +
            'echo bsconf >> /var/tmp/Plugins/BlueStripe/conf/bluestripe.conf;' +
            'mkdir /var/tmp/Plugins/ChangeTracking;' +
            'mkdir /var/tmp/Plugins/ChangeTracking/plugin;' +
            'echo ctplugin >> /var/tmp/Plugins/ChangeTracking/plugin/in_changetracking.rb;' +
            'mkdir /var/tmp/Plugins/ChangeTracking/conf;' +
            'echo ctconf >> /var/tmp/Plugins/ChangeTracking/conf/changetracking.conf;' +
            'mkdir /var/tmp/Plugins/Security;' +
            'mkdir /var/tmp/Plugins/Security/plugin;' +
            'echo splugin >> /var/tmp/Plugins/Security/plugin/in_security.rb;' +
            'echo sfplugin >> /var/tmp/Plugins/Security/plugin/filter_security.rb;' +
            'mkdir /var/tmp/Plugins/Security/conf;' +
            'echo sconf >> /var/tmp/Plugins/Security/conf/security.conf;' +
            'mkdir /var/tmp/Plugins/StatsD;' +
            'mkdir /var/tmp/Plugins/StatsD/plugin;' +
            'echo statplugin >> /var/tmp/Plugins/StatsD/plugin/in_statd.rb;' +
            'mkdir /var/tmp/Plugins/StatsD/conf;' +
            'echo statconf >> /var/tmp/Plugins/StatsD/conf/statd.conf;' +
            'mkdir /var/tmp/Plugins/CustomLog;' +
            'mkdir /var/tmp/Plugins/CustomLog/conf;' +
            'echo custom log conf >> /var/tmp/Plugins/CustomLog/conf/customlog.conf;'
        )

		
    def tearDown(self):
        """
        Remove test all test plugins and conf file from
        """
        os.system('rm -rf /var/tmp/Plugins;' +
            'rm -rf /var/tmp/etc;'
            'rm -rf /var/tmp/opt;'
        )

    def make_MI(self,retval, Name, Plugins):
        d=dict()
        d.clear()
        d['Name'] = nxOMSPlugin.protocol.MI_String(Name)
        if Plugins == None :
            d['Plugins'] = None
        else :
            for plugin in Plugins:
                plugin['PluginName']=nxOMSPlugin.protocol.MI_String(plugin['PluginName'])
                plugin['Ensure']=nxOMSPlugin.protocol.MI_String(plugin['Ensure'])
            d['Plugins'] = nxOMSPlugin.protocol.MI_InstanceA(Plugins)
        return retval,d

    def testGetPlugin_default(self):
        d={'Name': 'testPlugin', 'Plugins': [] }
        t={'Name': 'testPlugin', 'Plugins': [] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')
        
    def testGetPlugin_add(self):
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}, {'PluginName': 'ChangeTracking','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}, {'PluginName': 'ChangeTracking','Ensure': 'Present'}] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')

        # add Common Plugin
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}, {'PluginName': 'ChangeTracking','Ensure': 'Present'}, {'PluginName': 'Common','Ensure': 'Present'}] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')
        
    def testGetPlugin_remove(self):
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Absent'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name': 'testPlugin', 'Plugins': [] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Absent'}, {'PluginName': 'ChangeTracking','Ensure': 'Absent'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name': 'testPlugin', 'Plugins': [] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')
        
        # remove Common plugin - no action
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Absent'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')
        
        # remove custom log conf test
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'CustomLog','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        t={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}, {'PluginName': 'CustomLog','Ensure': 'Present'}] }
        m=self.make_MI(0,**t)
        g=nxOMSPlugin.Get_Marshall(**d)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'CustomLog','Ensure': 'Absent'}] }
        t={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        g=nxOMSPlugin.Get_Marshall(**d)
        m=self.make_MI(0,**t)
        self.assertTrue(check_values(g, m)  ==  True, \
        'Get '+repr(g)+' should return == '+repr(m)+'')        
        
    def testSetPlugin_add(self):
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}, {'PluginName': 'ChangeTracking','Ensure': 'Absent'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

    def testTestPlugin_add(self):
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}, {'PluginName': 'ChangeTracking','Ensure': 'Present'}, {'PluginName': 'StatsD','Ensure': 'Present'}, {'PluginName': 'Security','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}, {'PluginName': 'ChangeTracking','Ensure': 'Absent'}, {'PluginName': 'StatsD','Ensure': 'Present'}, {'PluginName': 'Security','Ensure': 'Absent'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0],'Test('+repr(d)+') should return == [0]')
    
    def testTestPlugin_filesChanged(self):
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'BlueStripe','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0],'Test('+repr(d)+') should return == [0]')
        # modify the module plugin file on disk
        os.system('echo modified plugin >> /var/tmp/Plugins/BlueStripe/plugin/in_bluestripe.rb;')
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [-1],'Test('+repr(d)+') should return == [-1]')

        # update common Plugin - out_oms_blob
        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0],'Test('+repr(d)+') should return == [0]')
        # modify the module plugin file on disk
        os.system('echo updated output plugin >> /var/tmp/Plugins/Common/plugin/out_oms_blob.rb;')
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [-1],'Test('+repr(d)+') should return == [-1]')
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0],'Set('+repr(d)+') should return == [0]')
        # validate latest plugin applied
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0],'Test('+repr(d)+') should return == [0]')

        
    def testTestDiag_setup(self):
        nxOMSPlugin.DIAG_ACTION = nxOMSPlugin.DiagLogUtil()
        # setup
        # 1. copy required plugin files in plugin directory
        # 2. few workspace conf directories containing omsagent conf not having diag
        # 3. few workspace conf directories containing omsagent conf having diag
        # 4. few workspace conf directories not having omsagent.conf file itself
        # call test and check result
        copy_common_plugin_files()
        copy_diag_plugin_files()
        for x in range(1,5):
            setup_conf_directories_without_diag()
            setup_conf_directories_with_diag()
            setup_conf_directories_without_conf_file()

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [-1], 'Test('+repr(d)+') should return == [-1] for diag setup')

    def testTestDiag_nosetup(self):
        nxOMSPlugin.DIAG_ACTION = nxOMSPlugin.DiagLogUtil()
        # setup
        # 1. copy required plugin files in plugin directory
        # 2. few workspace conf directories containing omsagent conf having diag
        # 3. few workspace conf directories not having omsagent.conf file itself
        # call test and check result
        copy_common_plugin_files()
        copy_diag_plugin_files()
        for x in range(1,5):
            setup_conf_directories_with_diag()
            setup_conf_directories_without_conf_file()

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0], 'Test('+repr(d)+') should return == [0] as diag well setup')

    def testTestDiag_nofiles(self):
        nxOMSPlugin.DIAG_ACTION = nxOMSPlugin.DiagLogUtil()
        # setup
        # 1. miss plugin files that are checked in plugin directory
        # 2. few workspace conf directories containing omsagent conf having diag
        # 3. few workspace conf directories not having omsagent.conf file itself
        # call test and check result
        copy_common_plugin_files()
        for x in range(1,5):
            setup_conf_directories_with_diag()
            setup_conf_directories_without_conf_file()

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Test_Marshall(**d) == [0], 'Test('+repr(d)+') should return == [0] as diag plugin files not present')

    def testSetDiag_setup(self):
        # setup
        # 1. copy required plugin files in plugin directory
        # 2. few workspace conf directories containing omsagent conf not having diag
        # 3. few workspace conf directories containing omsagent conf having diag
        # 4. few workspace conf directories not having omsagent.conf file itself
        # call test and check result
        copy_common_plugin_files()
        copy_diag_plugin_files()
        for x in range(1,5):
            setup_conf_directories_without_diag()
            setup_conf_directories_with_diag()
            setup_conf_directories_without_conf_file()

        d={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'Common','Ensure': 'Present'}] }
        self.assertTrue(nxOMSPlugin.Set_Marshall(**d) == [0], 'Set('+repr(d)+') should return == [0] as diag correctly setup')

        # verify if setup updated files correctly
        self.assertTrue(nxOMSPlugin.DIAG_ACTION.is_diag_enabled() == True, 'Set should have setup diag config files correctly')

def copy_common_plugin_files():
    plugin_files = os.listdir(os.path.join(nxOMSPlugin.PLUGIN_MODULE_PATH, 'Common/plugin'))
    for f in plugin_files:
        file_path = os.path.join(nxOMSPlugin.PLUGIN_MODULE_PATH, 'Common/plugin', f)
        if os.path.isfile(file_path):
            shutil.copy(file_path, nxOMSPlugin.PLUGIN_PATH)

def copy_diag_plugin_files():
    for x in nxOMSPlugin.DIAG_PLUGINS:
        file_path = os.path.join(nxOMSPlugin.PLUGIN_PATH, x)
        contents = 'placeholder file'
        nxOMSPlugin.append_file(file_path, contents)

def setup_conf_directories_without_conf_file():
    # Setup conf directory and return ws_path
    ws_path = os.path.join(nxOMSPlugin.CONF_PREFIX, get_uuid())
    os.makedirs(os.path.join(ws_path, 'conf'))
    return ws_path

def setup_conf_directories_without_diag():
    ws_path = setup_conf_directories_without_conf_file()
    # Setup conf file with config for out_oms
    file_contents = nxOMSPlugin.DIAG_ACTION.generate_diag_conf_contents(ws_path)
    file_contents_without_diag = file_contents.replace('diag', '')
    nxOMSPlugin.append_file(os.path.join(ws_path, nxOMSPlugin.WS_OMSAGENT_CONF_SUFFIX), file_contents_without_diag)
    return ws_path

def setup_conf_directories_with_diag():
    ws_path = setup_conf_directories_without_diag()
    # Generate and append config for diag
    file_contents = nxOMSPlugin.DIAG_ACTION.generate_diag_conf_contents(ws_path)
    nxOMSPlugin.append_file(os.path.join(ws_path, nxOMSPlugin.WS_OMSAGENT_CONF_SUFFIX), file_contents)
    return ws_path

def get_uuid():
    suffix = nxOMSPlugin.ws_suffix_list[nxOMSPlugin.ws_counter]
    nxOMSPlugin.ws_counter += 1
    return nxOMSPlugin.ws_prefix + suffix

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
        if type(sd[k].value) == ctypes.c_uint:
            if sd[k].value.value==None or dd[k].value.value==None:
                continue
            if sd[k].value.value != dd[k].value.value:
                print k+': '+str(sd[k].value.value)+' != '+str(dd[k].value.value)+'\n'
                return False
            continue
        if type(sd[k].value) == ctypes.c_int or type(sd[k].value) == ctypes.c_ushort:
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
    
def decode_unicode(obj):
    if isinstance(obj, dict):
        d = {}
        for k, v in obj.iteritems():
            d[decode_unicode(k)] = decode_unicode(v)
        return d
    elif isinstance(obj, list):
        return [decode_unicode(i) for i in obj]
    elif isinstance(obj, unicode):
        return obj.decode('ascii', 'ignore')
    else:
        return obj
        
######################################
if __name__ == '__main__':
    s1=unittest2.TestLoader().loadTestsFromTestCase(nxOMSPluginTestCases)
    alltests = unittest2.TestSuite([s1])
    unittest2.TextTestRunner(stream=sys.stdout,verbosity=3).run(alltests)

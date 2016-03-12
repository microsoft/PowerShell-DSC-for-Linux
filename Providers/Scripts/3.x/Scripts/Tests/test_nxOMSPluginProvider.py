#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import os
import sys
import imp
import ctypes

try:
    import unittest2
except:
    import unittest as unittest2

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
        nxOMSPlugin.OMS_ACTION = nxOMSPlugin.TestOMSAgent()
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
        t={'Name': 'testPlugin', 'Plugins': [{'PluginName': 'CustomLog','Ensure': 'Present'}, {'PluginName': 'Common','Ensure': 'Present'}] }
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
                print(k+': '+str(sd[k].value.value)+' != '+str(dd[k].value.value)+'\n')
                return False
            continue
        if type(sd[k].value) == ctypes.c_int or type(sd[k].value) == ctypes.c_ushort:
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
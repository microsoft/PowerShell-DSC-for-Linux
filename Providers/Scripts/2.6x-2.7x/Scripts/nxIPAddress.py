#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
from __future__ import print_function
from __future__ import with_statement

import os
import sys
import tempfile
import re
import platform
import imp
import socket
protocol=imp.load_source('protocol','../protocol.py')

"""
MOF:

[ClassVersion("1.0.0"), FriendlyName("nxIPAddress")] 
class MSFT_nxIPAddress : OMI_BaseResource
{
	[write] string IPAddress;
	[Key] string InterfaceName;
	[write,ValueMap{"Automatic", "Static"},Values{"Automatic", "Static"}] string BootProtocol;
	[write] string DefaultGateway;
	[write,ValueMap{"Present", "Absent"}, Values{"Present", "Absent"}] string Ensure;
	[write] integer PrefixLength;
	[Key,write,ValueMap{"IPv4", "IPv6"},Values{"IPv4", "IPv6"}] string AddressFamily;
};
"""

def ValidateAddresses(IPAddress,AddressFamily):
    if 'IPv4' in AddressFamily:
        ptype=socket.AF_INET
    elif 'IPv6' in AddressFamily:
        ptype=socket.AF_INET6
    else:
        return False
    try:
        socket.inet_pton(ptype,IPAddress)
    except:
        return False
    return True

def bitNetmaskConversion(PrefixLength):
    N = int(PrefixLength)
    M =  N / 8    #number of 255 sections (full octets)
#    part = N % 8    #number of 1's in odd octet
    MASK = 255
   
    netmaskIP = ""
    count = 0
    while count < M:
        netmaskIP = netmaskIP + "255."
        count += 1
   
    if N % 8 != 0:
        netmaskIP += str((MASK << (8 - N%8)) & MASK) + "."
        count += 1
    while count < 4:
        netmaskIP = netmaskIP + "0."
        count += 1

    if netmaskIP[-1] == ".":
        netmaskIP = netmaskIP[:-1]
       
    return netmaskIP

def netmaskBitConversion(netmask):
    print( netmask, "netmask")
    arrTmp = netmask.strip("'")
    arr = arrTmp.split(".")
    
    sumT = 0
    for i in arr:
        i = int(i)
        if i == 255:
            sumT += 8
        else:
            j = 0
            while j < 8:
                sumT += (i >> j) & 1
                j+=1
    return sumT

def Set_Marshall(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
    if PrefixLength == None:
        PrefixLength=''
    if BootProtocol == None:
        BootProtocol=''
    if Ensure == None or len(Ensure)<1:
        Ensure='Present'
    if AddressFamily == None or len(AddressFamily)<1:
        AddressFamily='IPv4'
    if IPAddress == None:
        IPAddress=''
    if len(IPAddress)>0:
        if ValidateAddresses(IPAddress,AddressFamily) == False:
            return [-1]
    elif BootProtocol != 'Automatic' and Ensure == 'Present':
        print('ERROR: BootProtocol != Automatic.  IPAdress is required.',file=sys.stdout)
        return [-1]
    if DefaultGateway == None:
        DefaultGateway=''
    if len(DefaultGateway) > 0 and ValidateAddresses(DefaultGateway,AddressFamily) == False:
        return [-1]
    MyDistro=GetMyDistro()
    retval = MyDistro.Set(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily)
    return retval

def Test_Marshall(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
    if PrefixLength == None:
        PrefixLength=''
    if BootProtocol == None:
        BootProtocol=''
    if Ensure == None or len(Ensure)<1:
        Ensure='Present'
    if AddressFamily == None or len(AddressFamily)<1:
        AddressFamily='IPv4'
    if IPAddress == None:
        IPAddress=''
    if len(IPAddress)>0:
        if ValidateAddresses(IPAddress,AddressFamily) == False:
            return [-1]
    elif BootProtocol != 'Automatic' and Ensure == 'Present':
        print('ERROR: BootProtocol != Automatic.  IPAdress is required.',file=sys.stdout)
        return [-1]
    if DefaultGateway == None:
        DefaultGateway=''
    if len(DefaultGateway) > 0 and ValidateAddresses(DefaultGateway,AddressFamily) == False:
        return [-1]
    MyDistro=GetMyDistro()
    retval = MyDistro.Test(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily)
    return retval

def Get_Marshall(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
    arg_names=list(locals().keys())
    if PrefixLength == None:
        PrefixLength=''
    if BootProtocol == None:
        BootProtocol=''
    if Ensure == None or len(Ensure)<1:
        Ensure='Absent'
    if AddressFamily == None or len(AddressFamily)<1:
        AddressFamily='IPv4'
    if IPAddress == None:
        IPAddress=''
    if len(IPAddress)>0:
        if ValidateAddresses(IPAddress,AddressFamily) == False:
            return [-1,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily]
    elif BootProtocol != 'Automatic' and Ensure == 'Present':
        print('ERROR: BootProtocol != Automatic.  IPAdress is required.',file=sys.stdout)
        return [-1,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily]
    if DefaultGateway == None:
        DefaultGateway=''
    if len(DefaultGateway) > 0 and ValidateAddresses(DefaultGateway,AddressFamily) == False:
        return [-1,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily]
    retval = 0
    MyDistro=GetMyDistro()
    (retval, IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily) = MyDistro.Get(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily)
    Ensure = protocol.MI_String(Ensure.encode("utf-8"))
    IPAddress = protocol.MI_String(IPAddress.encode("utf-8"))
    AddressFamily= protocol.MI_String(AddressFamily.encode("utf-8"))
    InterfaceName = protocol.MI_String(InterfaceName.encode("utf-8"))
    BootProtocol = protocol.MI_String(BootProtocol.encode("utf-8"))
    DefaultGateway = protocol.MI_String(DefaultGateway.encode("utf-8"))
    if type(PrefixLength) == int:
        PrefixLength=protocol.MI_Uint32(PrefixLength)
    else:
        PrefixLength=protocol.MI_Uint32(int(PrefixLength))
    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k]     
    return retval, retd
    
def ReplaceFileContentsAtomic(filepath, contents):
    """
    Write 'contents' to 'filepath' by creating a temp file, and replacing original.
    """
    handle, temp = tempfile.mkstemp(dir = os.path.dirname(filepath))
    if type(contents) == str :
        contents=contents.encode('latin-1')
    try:
        os.write(handle, contents)
    except IOError, e:
        print('ReplaceFileContentsAtomic','Writing to file ' + filepath + ' Exception is ' + str(e),file=sys.stderr)
        return None
    finally:
        os.close(handle)
    try:
        os.rename(temp, filepath)
        return None
    except IOError, e:
        print('ReplaceFileContentsAtomic','Renaming ' + temp+ ' to ' + filepath + ' Exception is ' +str(e),file=sys.stderr)
    try:
        os.remove(filepath)
    except IOError, e:
        print('ReplaceFileContentsAtomic','Removing '+ filepath + ' Exception is ' +str(e),file=sys.stderr)
    try:
        os.rename(temp,filepath)
    except IOError, e:
        print('ReplaceFileContentsAtomic','Removing '+ filepath + ' Exception is ' +str(e),file=sys.stderr)
        return 1
    return 0

def GetMyDistro(dist_class_name=''):
    """
    Return MyDistro object.
    NOTE: Logging is not initialized at this point.
    """
    if dist_class_name == '':
        if 'Linux' in platform.system():
            Distro=platform.dist()[0]
        else : # I know this is not Linux!
            if 'FreeBSD' in platform.system():
                Distro=platform.system()
        Distro=Distro.strip('"')
        Distro=Distro.strip(' ')
        dist_class_name=Distro+'Distro'
    else:
        Distro=dist_class_name
    if not globals().has_key(dist_class_name):
        print(Distro+' is not a supported distribution.')
        return None
    return globals()[dist_class_name]() # the distro class inside this module.

class AbstractDistro(object):
    def __init__(self): 
        self.gateway_file='/etc/sysconfig/network'
        self.gateway_prefix=''
        self.ifcfg_prefix='/etc/sysconfig/network-scripts/ifcfg-'
        
    def init_re_dict(self,src_dict):
        re_dict=dict()
        for k in src_dict:
            re_dict[k]=re.compile(r'\s*'+k+'.*')
        return re_dict

    def init_src_dicts(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        self.gateway_dict=dict()
        self.ifcfg_v4_dict=dict()
        self.ifcfg_v4_dict['ONBOOT=']='yes'
        self.ifcfg_v4_dict['DEVICE=']=InterfaceName
        if BootProtocol.lower() == 'static':
            self.ifcfg_v4_dict['BOOTPROTO=']='none'
        else:
            self.ifcfg_v4_dict['BOOTPROTO=']='dhcp'
        self.ifcfg_v4_dict['DHCPCLASS=']=''
        self.ifcfg_v4_dict['IPADDR=']=IPAddress
        if PrefixLength != 0 and PrefixLength  != '':
            self.ifcfg_v4_dict['NETMASK=']=bitNetmaskConversion(PrefixLength)
        else:
            self.ifcfg_v4_dict['NETMASK=']=''            
        self.ifcfg_v6_dict=dict()
        self.ifcfg_v6_dict['ONBOOT=']='yes'
        self.ifcfg_v6_dict['DEVICE=']=InterfaceName
        if BootProtocol.lower() == 'static':
            self.ifcfg_v6_dict['BOOTPROTO=']='none'
        else:
            self.ifcfg_v6_dict['BOOTPROTO=']='dhcp'
        self.ifcfg_v6_dict['DHCPCLASS=']=''
        self.ifcfg_v6_dict['IPV6ADDR=']=IPAddress
        if BootProtocol.lower() == 'static':
            self.ifcfg_v6_dict['IPV6_INIT=']='yes'
            self.ifcfg_v6_dict['IPV6_AUTOCONF=']='no'
        else :
            self.ifcfg_v6_dict['IPV6_INIT=']='yes'
            self.ifcfg_v6_dict['IPV6_AUTOCONF=']='no'
        if PrefixLength != 0 and PrefixLength != '':
            self.ifcfg_v6_dict['NETMASK=']=bitNetmaskConversion(PrefixLength)
        else:
            self.ifcfg_v6_dict['NETMASK=']=''
        self.gateway_dict['GATEWAY=']=DefaultGateway
        if AddressFamily == 'IPv4':
            self.ifcfg_dict=self.ifcfg_v4_dict
            self.addr_key='IPADDR='
        else :
            self.ifcfg_dict=self.ifcfg_v6_dict
            self.addr_key='IPV6ADDR='

    def src_dicts_to_params(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        if len(self.ifcfg_dict['NETMASK=']) > 0:
            PrefixLength=netmaskBitConversion(self.ifcfg_dict['NETMASK='])
        else:
            PrefixLength=''
        if ':' in self.ifcfg_dict[self.addr_key]:
            AddressFamily='IPv6'
        else:
            AddressFamily='IPv4'
        if self.ifcfg_dict['BOOTPROTO='] == 'dhcp':
            bootproto='Automatic'
        else:
            bootproto='Static'
        gateway=''
        if len(self.gateway_dict['GATEWAY=']) >0:
            gateway=self.gateway_dict['GATEWAY=']
        return self.ifcfg_dict[self.addr_key],self.ifcfg_dict['DEVICE='],bootproto,gateway,Ensure,PrefixLength,AddressFamily
    
    def restart_network(self):
        os.system('service network restart')
        return [0]

    def interface_down(self,Interface):
        os.system('ifconfig ' + Interface + ' down')
        return [0]

    def UpdateValuesInFile(self,fname,src_dict,re_dict):
        updated=''
        if os.path.exists(fname) != True:
            # if this file is not here - we will create it
            with open(fname,'w+') as F:
                F.write('# Created by Microsoft DSC nxIPAddress Provider\n')
                F.close()
        try:
            with open(fname,'r') as F:
                for l in F.readlines():
                    if l[0]=='#':
                        updated+=l
                        continue
                    for k in re_dict:
                        if re_dict[k]!=None:
                            if re.match(re_dict[k],l): # re.match is anchored to the line start.
                                if len(src_dict[k])==0 :
                                    l=''
                                    re_dict[k]=None
                                    break
                                else:
                                    l=re.sub(re_dict[k],k+src_dict[k],l)
                                    re_dict[k]=None
                    if len(l)>2:
                        updated+=l
                for k in re_dict:
                    if re_dict[k] != None and len(src_dict[k]) > 0 :
                        l=k+src_dict[k]+'\n'
                        updated+=l
                
        except:
            raise
        ReplaceFileContentsAtomic(fname,updated)
        return [0]
    
    def GetValuesFromFile(self,fname,src_dict,re_dict):
        if os.path.exists(fname) != True:
            return
        try:
            with (open(fname,'r')) as F:  
                for l in F.readlines():
                    for k in re_dict:
                        if re_dict[k]!=None:
                            if re.match(re_dict[k],l): # re.match is anchored to the line start.
                                src_dict[k]=l.split(k[-1])[1].strip('\n')
                                re_dict[k]=None
        except:
            raise

    def Set(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        retval=[-1]
        if len(self.ifcfg_prefix)>0:
            self.ifcfg_file=self.ifcfg_prefix+InterfaceName
        if len(self.gateway_prefix)>0:
            self.gateway_file=self.gateway_prefix+InterfaceName
        self.init_src_dicts(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily)
        gateway_re_dict=self.init_re_dict(self.gateway_dict)
        ifcfg_re_dict=self.init_re_dict(self.ifcfg_dict)
        if Ensure == 'Absent':
            if len(self.ifcfg_prefix)>0:
                if os.path.exists(self.ifcfg_file):
                    os.remove(self.ifcfg_file)
                    retval=[0]
            else:
                retval=self.UpdateValuesInFile(self.ifcfg_file,self.ifcfg_dict,ifcfg_re_dict)
            if len(self.gateway_prefix)>0:
                if os.path.exists(self.gateway_file):
                    os.remove(self.gateway_file)
                    retval=[0]
            else:
                retval=self.UpdateValuesInFile(self.gateway_file,self.gateway_dict,gateway_re_dict)
            self.interface_down(InterfaceName)
        else:
            retval=self.UpdateValuesInFile(self.gateway_file,self.gateway_dict,gateway_re_dict)
            retval=self.UpdateValuesInFile(self.ifcfg_file,self.ifcfg_dict,ifcfg_re_dict)
        retval=self.restart_network()
        return retval
    
    def Test(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        if len(self.ifcfg_prefix)>0:
            self.ifcfg_file=self.ifcfg_prefix+InterfaceName
        if len(self.gateway_prefix)>0:
            self.gateway_file=self.gateway_prefix+InterfaceName
        self.init_src_dicts(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily)
        test_gateway=dict(self.gateway_dict)
        for k in test_gateway:
            test_gateway[k]=''
        test_gateway_re_dict=self.init_re_dict(self.gateway_dict)
        self.GetValuesFromFile(self.gateway_file,test_gateway,test_gateway_re_dict)
        for k in self.gateway_dict:
            if self.gateway_dict[k] != test_gateway[k]:
                return [-1]
        test_ifcfg=dict(self.ifcfg_dict)
        for k in test_ifcfg:
            if k != 'iface ':
                test_ifcfg[k]=''
        test_ifcfg_re_dict=self.init_re_dict(self.ifcfg_dict)
        self.GetValuesFromFile(self.ifcfg_file,test_ifcfg,test_ifcfg_re_dict)
        for k in self.ifcfg_dict:
            if self.ifcfg_dict[k] != test_ifcfg[k]:
                return [-1]
        return [0]
    
    def Get(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        # calling Test here will fill the dicts with values
        if self.Test(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily) == [0]:
            Ensure='Present'
            IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength, \
            AddressFamily = self.src_dicts_to_params(IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily)
        else:
            Ensure='Absent'
        if PrefixLength=='':
            PrefixLength=0
        return 0,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily

class SuSEDistro(AbstractDistro):
    def __init__(self):
        super(SuSEDistro,self).__init__()
        self.gateway_prefix='/etc/sysconfig/network/ifroute-'
        self.ifcfg_prefix='/etc/sysconfig/network/ifcfg-'

    def init_src_dicts(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        self.gateway_v4_dict=dict()
        self.gateway_v6_dict=dict()
        if BootProtocol.lower() != 'static':
            self.gateway_v4_dict['default ']=''
            self.gateway_v6_dict['default ']=''
        else:
            self.gateway_v4_dict['default ']=DefaultGateway+' '+bitNetmaskConversion(PrefixLength)+' '+InterfaceName
            self.gateway_v6_dict['default ']=DefaultGateway+'/'+str(PrefixLength)+' - - '+InterfaceName
        self.ifcfg_v4_dict=dict()
        if BootProtocol.lower() != 'static':
            self.ifcfg_v4_dict['BOOTPROTO=']='dhcp'
        else:
            self.ifcfg_v4_dict['BOOTPROTO=']='static'
        self.ifcfg_v4_dict['STARTMODE=']='auto'
        self.ifcfg_v4_dict['IPADDR=']=IPAddress
        self.ifcfg_v4_dict['PREFIXLEN=']=str(PrefixLength)
        self.ifcfg_v6_dict=dict()
        if BootProtocol.lower() != 'static':
            self.ifcfg_v6_dict['BOOTPROTO=']='autoip' 
        else:
            self.ifcfg_v6_dict['BOOTPROTO=']='static'
        self.ifcfg_v6_dict['STARTMODE=']='auto'
        self.ifcfg_v6_dict['IPADDR=']=IPAddress
        self.ifcfg_v6_dict['PREFIXLEN=']=str(PrefixLength)
        if AddressFamily == 'IPv4':
            self.ifcfg_dict=self.ifcfg_v4_dict
            self.addr_key='IPADDR='
            self.gateway_dict=self.gateway_v4_dict
        else :
            self.ifcfg_dict=self.ifcfg_v6_dict
            self.addr_key='IPADDR='
            self.gateway_dict=self.gateway_v6_dict

    def src_dicts_to_params(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        if len(self.ifcfg_dict['PREFIXLEN=']) > 0:
            PrefixLength=netmaskBitConversion(self.ifcfg_dict['PREFIXLEN='])
        else:
            PrefixLength=''
        if ':' in self.ifcfg_dict['IPADDR=']:
            AddressFamily='IPv6'
        else:
            AddressFamily='IPv4'
        if self.ifcfg_v4_dict['BOOTPROTO='] != 'static':
            bootproto='Automatic'
        else:
            bootproto='Static'
        gateway=''
        if len(self.gateway_dict['default ']) >0:
            gateway=self.gateway_dict['default '].split(' ')[1]
        return self.ifcfg_dict['IPADDR='],self.ifcfg_file.split('-')[-1],bootproto,gateway,Ensure,PrefixLength,AddressFamily
    
    def restart_network(self):
        os.system('/sbin/rcnetwork restart')
        return [0]

class debianDistro(AbstractDistro):
    def __init__(self):
        super(debianDistro,self).__init__()
        self.ifcfg_prefix=''
        self.gateway_prefix=''
        self.ifcfg_file='/etc/network/interfaces'
        self.gateway_file='/etc/network/interfaces'

    def init_re_dict(self,src_dict): 
        re_dict=dict()
        for k in src_dict:
            re_dict[k]=re.compile(r'\s*'+k+'.*')
        if 'iface ' in re_dict:
            re_dict['iface ']=re.compile(r'\s*iface '+src_dict['iface '])
        if 'inet ' in re_dict:
            re_dict['inet ']=re.compile(r'\s*iface '+src_dict['iface '] + ' inet .*')
        return re_dict

    def init_src_dicts(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        self.ifcfg_v4_dict={}
        self.ifcfg_v6_dict={}
        self.gateway_dict={}
        if BootProtocol.lower() == 'static' :
            self.ifcfg_v4_dict['inet '] = 'static'
        elif BootProtocol.lower() == 'automatic':
            self.ifcfg_v4_dict['inet '] = 'dhcp'
        else:
            self.ifcfg_v4_dict['inet '] = ''
        self.ifcfg_v4_dict['iface ']=InterfaceName
        self.ifcfg_v4_dict['autoconf ']=''
        self.ifcfg_v4_dict['network ']=''
        self.ifcfg_v4_dict['address ']=IPAddress
        if PrefixLength !=0 and PrefixLength != '':
            self.ifcfg_v4_dict['netmask ']=bitNetmaskConversion(PrefixLength)
        else:
            self.ifcfg_v4_dict['netmask ']=''
        self.ifcfg_v4_dict['gateway ']=DefaultGateway
        if len(BootProtocol) > 0:
            self.ifcfg_v6_dict['inet6 ']='static'  # static is used for autoconf as well
        else:
            self.ifcfg_v6_dict['inet6 ']='' 
        self.ifcfg_v6_dict['iface ']=InterfaceName
        addr=IPAddress
        if PrefixLength != '' and IPAddress !='' :
            addr+='/'+str(PrefixLength)
        self.ifcfg_v6_dict['address ']=addr
        if PrefixLength !=0 and PrefixLength != '':
            self.ifcfg_v6_dict['netmask ']=bitNetmaskConversion(PrefixLength)
        else:
            self.ifcfg_v6_dict['netmask ']=''
        self.ifcfg_v6_dict['gateway ']=DefaultGateway

        if AddressFamily == "IPv4":
            self.ifcfg_dict=self.ifcfg_v4_dict
            self.inet='inet '
        else:
            if BootProtocol.lower() != 'static':
                self.ifcfg_v6_dict['autoconf ']='1'
            else:
                self.ifcfg_v6_dict['autoconf ']='0'
            self.ifcfg_dict=self.ifcfg_v6_dict
            self.inet='inet6 '
        if Ensure == "Absent":
            auto='auto '+InterfaceName
            self.ifcfg_dict[auto]=''
            
    def src_dicts_to_params(self,IPAddress,InterfaceName,BootProtocol,DefaultGateway,Ensure,PrefixLength,AddressFamily):
        if len(self.ifcfg_dict['netmask ']) > 0:
            PrefixLength=netmaskBitConversion(self.ifcfg_dict['netmask '])
        else:
            PrefixLength=''
        if ':' in self.ifcfg_dict['address ']:
            AddressFamily='IPv6'
            if self.ifcfg_dict['autoconf '] == '1' :
                inet = 'Automatic'
            else:
                inet = 'Static'
        else:
            AddressFamily='IPv4'
            if self.ifcfg_dict[self.inet] == 'dhcp':
                inet = 'Automatic'
            else:
                inet = 'Static'
        gateway=''
        if len(self.ifcfg_dict['gateway ']) >0:
            gateway=self.ifcfg_dict['gateway ']
        return self.ifcfg_dict['address '],self.ifcfg_dict['iface '],inet,gateway,Ensure,PrefixLength,AddressFamily

    def restart_network(self):
        os.system('ifdown --exclude=lo -a ; ifup --exclude=lo -a')
        return [0]

    def UpdateValuesInFile(self,fname,src_dict,re_dict):
        if len(src_dict) == 0:
            return [0]
        removing=False
        if 'inet ' in src_dict.keys() and len(src_dict[self.inet])==0: # we are trying to remove
            removing=True
        if removing == False and os.path.exists(fname) != True:
            # if this file is not here - we will create it
            with open(fname,'w+') as F:
                F.write('# Created by nxIPAddress DSC PRovider\n')
                F.close()
        with open(fname,'r') as F:
            txt=F.read()
        if 'iface ' in src_dict.keys():
            srch=r'(^auto '+src_dict['iface ']+'$.*?^iface '+src_dict['iface ']+'.*?$|^iface '+src_dict['iface ']+'.*?$).*?((^auto )|(^iface )|(^$))'
        updated=''
        r=re.search(srch,txt,flags=re.S|re.M)
        if r == None:
            if removing:  #nothing to remove
                return [0]
            else : # append values to the end
                l='auto ' + src_dict['iface '] + '\niface '+src_dict['iface '] + ' ' + self.inet+src_dict[self.inet] + '\n'
                if len(updated) > 0 and updated[-1] != '\n':
                    updated+='\n'
                updated+=l
                re_dict['iface ']=None
                re_dict[self.inet]=None
                for k in re_dict:
                    if re_dict[k] != None and len(src_dict[k]) > 0 :
                        l=k+src_dict[k]+'\n'
                        updated+=l
                txt=txt+updated
        else:  #matched      
            if removing:
                tail=''
                txt=re.sub(r.group(0),tail,txt,flags=re.S|re.M)
                if txt[-2:] == '\n\n':
                    txt=txt[:-1]
            else : # replace tags - preserve unknown tags
                t=r.group(0)
                for l in t.splitlines():
                    if len(l)>1:
                        l+='\n'
                    else:
                        continue
                    if 'iface ' in re_dict.keys() and re_dict['iface '] != None :
                            if re.match(re_dict['iface '],l) :
                                l='iface '+src_dict['iface '] + ' ' + self.inet+src_dict[self.inet] + '\n'
                                re_dict['iface ']=None
                                re_dict[self.inet]=None
                                updated+=l
                                continue
                    for k in re_dict.keys():
                        if re_dict[k]!=None:
                            if re.match(re_dict[k],l): # re.match is anchored to the line start.
                                if len(src_dict[k])==0 :
                                    l=''
                                else:
                                    l=re.sub(re_dict[k],k+src_dict[k],l)
                                    if len(l)>0 and l[-1]!='\n':
                                        l+='\n'
                                re_dict[k]=None
                                break
                    if len(l)>2:
                        updated+=l

                for k in re_dict:
                    if re_dict[k] != None and len(src_dict[k]) > 0 :
                        l=k+src_dict[k]+'\n'
                        updated+=l
                tail=''
                if updated[-1] != '\n':
                    tail='\n'
                updated+=tail
                txt=re.sub(r.group(0),updated,txt,flags=re.S|re.M)
                if txt[-2:] == '\n\n':
                    txt=txt[:-1]
        ReplaceFileContentsAtomic(fname,txt)
        return [0]

    def GetValuesFromFile(self,fname,src_dict,re_dict):
        if os.path.exists(fname) != True:
            return
        try:
            with (open(fname,'r')) as F:  
                txt=F.read()
                if 'iface ' in src_dict.keys():
                    srch=r'(^auto '+src_dict['iface ']+'$.*?^iface '+src_dict['iface ']+'.*?$|^iface '+src_dict['iface ']+'.*?$).*?((^auto )|(^iface )|(^$))'
                    r=re.search(srch,txt,flags=re.S|re.M)
                    if r == None:
                        return
                    txt=r.group(0)
                for l in txt.splitlines():
                    for k in re_dict:
                        if re_dict[k]!=None:
                            if re.match(re_dict[k],l): # re.match is anchored to the line start.
                                if k == self.inet:
                                    src_dict[k]=l.split(k[-1])[3].strip('\n')
                                else:
                                    src_dict[k]=l.split(k[-1])[1].strip('\n')
                                re_dict[k]=None
        except:
            raise
    
class redhatDistro(AbstractDistro):
    def __init__(self):
        super(redhatDistro,self).__init__()

class centosDistro(redhatDistro):
    def __init__(self):
        super(centosDistro,self).__init__()

class UbuntuDistro(debianDistro):
    def __init__(self):
        super(UbuntuDistro,self).__init__()
        
class LinuxMintDistro(UbuntuDistro):
    def __init__(self):
        super(LinuxMintDistro,self).__init__()
        
class fedoraDistro(redhatDistro):
    def __init__(self):
        super(fedoraDistro,self).__init__()


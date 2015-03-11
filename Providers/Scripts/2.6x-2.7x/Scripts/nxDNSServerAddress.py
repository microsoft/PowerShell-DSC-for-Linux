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
Ubuntu/Debian: /etc/network/interfaces:dns-nameservers 8.8.8.8 8.8.4.4

REDHAT/CENTOS: /etc/resolv.conf 
    nameserver 192.168.1.254
    nameserver 8.8.8.8
    
SLES: /etc/sysconfig/network/config:NETCONFIG_DNS_STATIC_SEARCHLIST="<ipaddr1> <ipaddr2>"

[ClassVersion("1.0.0"), FriendlyName("nxDNSServerAddress")] 
class MSFT_nxDNSServerAddressResource : OMI_BaseResource
{
  [Key] string Address[];
  [Write,ValueMap{"Ensure"},Values{"Present", "Absent"}] string Ensure;
  [Write,ValueMap{"IPv4", "IPv6"},Values{"IPv4", "IPv6"}] string AddressFamily;
};
"""


def ValidateAddresses(Address,AddressFamily):
    if len(Address)>3:
        print("ERROR: Maximum of three entries for Address",sys.stderr)
        return False
    if 'IPv4' in AddressFamily:
        ptype=socket.AF_INET
    elif 'IPv6' in AddressFamily:
        ptype=socket.AF_INET6
    else:
        return False
    for a in Address:
        try:
            socket.inet_pton(ptype, a)
        except:
            return False
    return True

def Set_Marshall(Address,Ensure,AddressFamily):
    if Ensure == None or len(Ensure)<1:
        Ensure='Present'
    if AddressFamily == None or len(AddressFamily)<1:
        AddressFamily='IPv4'
    if ValidateAddresses(Address,AddressFamily) == False:
        return [-1]
    MyDistro=GetMyDistro()
    retval = MyDistro.Set(Address,Ensure,AddressFamily)
    return retval

def Test_Marshall(Address,Ensure,AddressFamily):
    if Ensure == None or len(Ensure)<1:
        Ensure='Present'
    if AddressFamily == None or len(AddressFamily)<1:
        AddressFamily='IPv4'
    if ValidateAddresses(Address,AddressFamily) == False:
        return [-1]
    MyDistro=GetMyDistro()
    retval= MyDistro.Test(Address,Ensure,AddressFamily)
    return retval

def Get_Marshall(Address,Ensure,AddressFamily):
    arg_names=list(locals().keys())

    if Ensure == None or len(Ensure)<1:
        Ensure='Present'
    if AddressFamily == None or len(AddressFamily)<1:
        AddressFamily='IPv4'
    if ValidateAddresses(Address,AddressFamily) == False:
        return [-1,Address,Ensure,AddressFamily]
    retval = 0
    MyDistro=GetMyDistro()
    (retval, Address) = MyDistro.Get(Address,Ensure,AddressFamily)
    Ensure = protocol.MI_String(Ensure.encode("utf-8"))
    Address = protocol.MI_StringA(Address)
    AddressFamily= protocol.MI_String(AddressFamily.encode("utf-8"))
    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k]     
    return retval, retd

def FindStringInFile(fname,matchs,multiline=False):
    """
    Single line: return match object if found in file.
    Multi line: return list of matches found in file.
    """
    print("%s %s %s"%(fname,matchs,multiline),file=sys.stderr)
    m=None
    try:
        if multiline:
            ms=re.compile(matchs,re.S|re.M)
            with (open(fname,'r')) as F:  
                l = F.read()
                m=re.findall(ms,l)
        else:
            ms=re.compile(matchs)
            with (open(fname,'r')) as F:  
                for l in F.readlines():
                    m=re.search(ms,l)
                    if m:
                        break
    except:
        raise
    return m

def ReplaceStringInFile(fname,src,repl):
    """
    Replace 'src' with 'repl' in file.
    """
    updated=''
    try:
        sr=re.compile(src)
        if FindStringInFile(fname,src):
            for l in (open(fname,'r')).readlines():
                n=re.sub(sr,repl,l)
                if len(n)>2:
                    updated+=n
            ReplaceFileContentsAtomic(fname,updated)
            return True
    except :
        raise
    return False

def AppendStringToFile(fname,s):
    with (open(fname,'a')) as F:
        F.write(s)
        if s[-1] != '\n' :
            F.write('\n')
        F.close()
    return True

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
        self.file='/etc/resolv.conf'
        self.dns_srch='nameserver '
        self.mode='single'
        
    def get_addrs(self,addrs,mode):
        lines=FindStringInFile(self.file,'('+self.dns_srch+'.*?$)',True) # use multiline
        naddrs=[]
        if len(addrs) == 0:
            for l in lines:
                l=l.replace(self.dns_srch,'')
                l = l.strip('"')
                l = l.strip("'")
                l = l.strip('\n')
                for a in l.split():
                    naddrs.append(a)
            return naddrs
        for a in addrs:
            if a in lines:
                naddrs.append(a)
        return naddrs
    
    def add_addrs(self,addrs,mode):
        # - TODO EXECPTION handlers
        delim=''
        if 'quoted' in mode:
                delim='"'
        if  'multi' in mode:
            ReplaceStringInFile(self.file,'('+self.dns_srch+'.*)','') 
            for a in addrs:
                AppendStringToFile(self.file,self.dns_srch+' '+a)
        elif 'single' in mode:
            ReplaceStringInFile(self.file,'('+self.dns_srch+'.*)',self.dns_srch+delim) 
            l=self.dns_srch
            for a in addrs:
                l+=a
                l+=' '
            if len(FindStringInFile(self.file,'('+self.dns_srch+'.*)',True)) == 0:
                AppendStringToFile(self.file,l)
            else:
                ReplaceStringInFile(self.file,self.dns_srch,l)
        return True

    def del_addrs(self,addrs,mode):
        delim=''
        cur_addrs = self.get_addrs('',self.mode)
        new_addrs = []
        for c in cur_addrs:
                if c not in addrs:
                    new_addrs.append(c)
        if mode == 'multi':
            ReplaceStringInFile(self.file,self.dns_srch+'.*','') 
            for a in new_addrs:
                AppendStringToFile(self.file,self.dns_srch+' '+a)
        elif 'single' in mode:
            if 'quoted' in mode:
                delim='"'
            l=self.dns_srch
            for a in new_addrs:
                l+=a
                l+=' '
            l+=delim
            ReplaceStringInFile(self.file,self.dns_srch+'.*',l)
        return True
            
    def Set(self,addrs,Ensure,AddressFamily):
        retval=[-1]
        r=False
        if Ensure=='Absent':
            r=self.del_addrs(addrs,self.mode)
        else:
            r=self.add_addrs(addrs,self.mode)
        if r:
            retval=[0]
        return retval
    
    def Test(self,addrs,Ensure,AddressFamily):
        if len(self.get_addrs(addrs,self.mode)) != len(addrs):
            return [-1]
        return [0]
    
    def Get(self,addrs,Ensure,AddressFamily):
        return 0,self.get_addrs(addrs,self.mode)

class SuSEDistro(AbstractDistro):
    def __init__(self):
        super(SuSEDistro,self).__init__()
        self.file='/etc/sysconfig/network/config'
        self.dns_srch='NETCONFIG_DNS_STATIC_SEARCHLIST="'
        self.mode='single-quoted'
    def Set(self,addrs,Ensure,AddressFamily):
        return super(SuSEDistro,self).Set(addrs,Ensure,AddressFamily)

class debianDistro(AbstractDistro):
    def __init__(self):
        super(debianDistro,self).__init__()
        self.file='/etc/network/interfaces'
        self.dns_srch='dns-nameservers '
        
class redhatDistro(AbstractDistro):
    def __init__(self):
        super(redhatDistro,self).__init__()
        self.mode='multi'
    def Set(self,addrs,Ensure,AddressFamily):
        return super(redhatDistro,self).Set(addrs,Ensure,AddressFamily)

class UbuntuDistro(debianDistro):
    def __init__(self):
        super(UbuntuDistro,self).__init__()
        
class LinuxMintDistro(UbuntuDistro):
    def __init__(self):
        super(LinuxMintDistro,self).__init__()
        
class fedoraDistro(redhatDistro):
    def __init__(self):
        super(fedoraDistro,self).__init__()

    def Set(self,addrs,Ensure,AddressFamily):
        return super(fedoraDistro,self).Set(addrs,Ensure,AddressFamily)

class centosDistro(redhatDistro):
    def __init__(self):
        super(centosDistro,self).__init__()

    def Set(self,addrs,Ensure,AddressFamily):
        return super(centosDistro,self).Set(addrs,Ensure,AddressFamily)

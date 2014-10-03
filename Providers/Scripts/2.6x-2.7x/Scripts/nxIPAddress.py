import pwd
import shutil
import grp
import time


import socket
import re
import csv
import os
import subprocess
import struct


BLOCK_SIZE = 8192

def Set_Marshall(InterfaceName, IPAddress, BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily):
    InterfaceName = InterfaceName.decode("utf-8")
    IPAddress = IPAddress.decode("utf-8")
    BootProtocol = BootProtocol.decode("utf-8")
    DefaultGateway = DefaultGateway.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    PrefixLength = PrefixLength.decode("utf-8")
    AddressFamily = AddressFamily.decode("utf-8")

    retval = Set(InterfaceName, IPAddress, BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily)
    return retval


def Test_Marshall(InterfaceName, IPAddress, BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily):
    InterfaceName = InterfaceName.decode("utf-8")
    IPAddress = IPAddress.decode("utf-8")
    BootProtocol = BootProtocol.decode("utf-8")
    DefaultGateway = DefaultGateway.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    PrefixLength = PrefixLength.decode("utf-8")
    AddressFamily = AddressFamily.decode("utf-8")

    retval = Test(InterfaceName, IPAddress, BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily)
    return retval


def Get_Marshall(InterfaceName, IPAddress, BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily):
    InterfaceName = InterfaceName.decode("utf-8")
    IPAddress = IPAddress.decode("utf-8")
    BootProtocol = BootProtocol.decode("utf-8")
    DefaultGateway = DefaultGateway.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    PrefixLength = PrefixLength.decode("utf-8")
    AddressFamily = AddressFamily.decode("utf-8")

    retval = 0

    (retval, InterfaceName, IPAddress, BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily) = Get(InterfaceName, IPAddress,  BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily)


    InterfaceName = InterfaceName.encode("utf-8")
    IPAddress = IPAddress.encode("utf-8")
    BootProtocol = BootProtocol.encode("utf-8")
    DefaultGateway = DefaultGateway.encode("utf-8")
    Ensure = Ensure.encode("utf-8")
    PrefixLength = str(PrefixLength).encode("utf-8")
    AddressFamily = AddressFamily.encode("utf-8")

    return [retval, InterfaceName, IPAddress, BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily]

############################################################
### Begin user defined DSC functions                     ###
############################################################

def Process(params):
    process = subprocess.Popen(params, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    (process_stdout, process_stderr) = process.communicate()
    return (process_stdout, process_stderr, process.returncode)


def validateIP(ipaddr):
    try:
        ip = ipaddr.strip("'")
        socket.inet_aton(ip)
        return True
    except socket.error:
        print "IP address is not valid."
        return False


def bitNetmaskConversion(PrefixLength):
    N = int(PrefixLength)
    M =  N / 8    #number of 255 sections (full octets)
    part = N % 8    #number of 1's in odd octet
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
    print netmask, "netmask"
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



   
"""                                                    IP ADDRESS                               """

##SLES

def readSlesIPAddr(configFile):
    return readDict(parseSles(configFile), 'IPADDR')

def openFile_witherror_grabIP(filename):
    try:
        readIPAddress()
    except IOError:
        print "Error: couldn't find IP address"


#parser only sufficient for config files with format: key=value

def parseSles(fileI):
    openR = open(fileI)
    md = {}
    data = openR.read()
    lines = data.split("\n")
    for line in lines:
        keyvals = line.split("=")

        if len(keyvals) == 2:
            keyvals[1] = keyvals[1].strip("'")
            md[keyvals[0]] = keyvals[1]

    openR.close()

    return md
   

def readDict(my_dict, key):
    try:
        if key in my_dict: 
            return my_dict[key]
    except KeyError:
        return [-1]
        
def write_StaticBootProto(fileI,md, ipAddr, netmaskIP):

    openW = open(fileI, 'w')
   
    if 'IPADDR' in md:
        md['IPADDR'] = ipAddr
    openW.write('IPADDR' + "=" + "'" + md['IPADDR'] + "'" "\n")
    
    if 'NETMASK' in md:
        md['NETMASK'] = str(netmaskIP)
    openW.write('NETMASK' + "=" + "'" + md['NETMASK'] + "'" + "\n")

    for key in md.keys():
        if key != 'IPADDR' and key != 'NETMASK':
            openW.write(key + "=" + "'" + md[key] + "'"  + "\n")
   
    openW.close()


def write_StaticIPv6BootProto(fileI,md, ip6Addr, netmaskLen):

    openW = open(fileI, 'w')

    if 'IPV6INIT' in md:
        md['IPV6INIT'] = "yes"
    openW.write("IPV6INIT=" + 'yes' + "\n")
   
    if 'IPV6ADDR' in md:
        md['IPV6ADDR'] = ip6Addr
    openW.write("IPV6ADDR=" + "'" +  ip6Addr + "'" + "\n")

    if 'PREFIXLEN' in md:
        md['PREFIXLEN'] = netmaskLen
    openW.write("PREFIXLEN=" + str(netmaskLen) + "\n")
   
    for key in md.keys():
        if key != 'IPV6ADDR' and key != 'IPV6INIT' and key != 'PREFIXLEN':
            openW.write(key + "=" + "'" + md[key] + "'" + "\n")
 
    openW.close()


def write_DhcpBootProto(fileI,md):  ##Lines with IPAddress and Netmask are simply deleted

    openW = open(fileI, 'w')

    if 'BOOTPROTO' in md:
        md['BOOTPROTO'] = "dhcp"
    else:
        openW.write('BOOTPROTO' + "=" + 'dhcp' + "\n")

    for key in md.keys():

        if key != 'IPADDR' and key != 'NETMASK':
            openW.write(key + "=" + "'" +  md[key] + "'" + "\n")
  
    openW.close()


def write_DhcpIPv6BootProto(fileI,md):

    openW = open(fileI, 'w')

    for key in md.keys():
        if key != 'IPV6ADDR' and key != 'IPV6_AUTOCONF' and key != 'IP6INIT':
            openW.write(key + "=" + "'" + md[key] + "'" + "\n")
        openW.write('IPV6INIT' + "=" + 'yes'+ "\n")
        openW.write('IPV6_AUTOCONF' + "=" + 'yes'+ "\n")
       
    openW.close()


def setIPv4Address(filePath, BootProtocol IPAddress, PrefixLength):

    if validateIP(IPAddress):
        if BootProtocol == "static":
            write_StaticBootProto(filePath, parseSles(filePath), IPAddress, bitNetmaskConversion(PrefixLength))
        elif BootProtocol == "automatic":
            write_DhcpBootProto(filePath, parseSles(filePath))


def setIPv6Address(filePath, BootProtocol, IPAddress, PrefixLength):

    if validateIP(IPAddress):
        if BootProtocol == "static":
            write_StaticIPv6BootProto(filePath, parseSles(filePath), IPAddress, PrefixLength)
        elif BootProtocol == "automatic":
            write_DhcpIPv6BootProto(filePath, parseSles(filePath))
         

def removeValSlesConfig(fileI, md, valuesToRemoveFromMD): #fileI, md, listVal):

    openW = open(fileI, 'w')
    for val in valuesToRemoveFromMD:
        if val in md:
            del md[val]
    for key in md:
        openW.write(key + "=" + "'" + md[key] + "'" + "\n")
    openW.close()
    return md

##RHEL/CENTOS/ORACLE

"""
really quite the same as defined by sles.
ip address/netmask will be located in the /etc/sysconfig/network-scripts/ifcfg-ethX files

"""


##DEBIAN/UBUNTU
#to see type of network configuration-- either static or dhcp
#i.e. if parseDeb_BootP("ifcfg-eth0","eth0") == "static", then call other function to set ip address etc
def findDebBootPStatus(fileI, deviceName):
    openR = open(fileI)
    Type = ""
    lines = openR.read().split("\n")
    line_arr = []
    for line in lines:
        line_arr = line.split()
        if len(line_arr) >= 4:
            if line_arr[0] == "iface" and line_arr[1] == deviceName:
                Type = line_arr[3]
        line_arr = []
    openR.close()
    return Type

def findDebIPStatus(fileI, InterfaceName):   
    openR = open(fileI)
    #Type=""
    lines = openR.read().split("\n")
    line_arr = []
    for line in lines:
       line_arr = line.split()
       if len(line_arr) >= 4:
           if line_arr[0] == "iface" and line_arr[1] == InterfaceName:
               Type = line_arr[3]
       line_arr = []
    openR.close()
    return Type


def parseDeb(fileI):
    openR = open(fileI)
    keyvals     = {}
    md          = {}
    keyvals_arr = []
    line_arr    = []
    val_dict    = {}
    lines = openR.read().split("\n")
    marker = ""
    for line in lines:
        keyLine = line
        keys = line.split()
        if len(keys) >= 2:
           if keys[0] == "iface" or  keys[0] == "#" or keys[0] == "auto" : #this will work for comments that have a space between the "#" and text
               keyvals_arr.append(keyLine)
               if keys[0] == "iface":
                   marker = keys[1]
           else:
               if len(keys) >= 2:
                   md[keys[0]] = keys[1] + "=" + marker

    for key in keyvals_arr:
        findDevice = key.split()
        if len(findDevice) >= 2:
            for k, v in md.iteritems():
                pairDevice = v.split("=")
                if len(pairDevice) >= 2:
                    if findDevice[1] == pairDevice[1]:
                        val_dict[k] = pairDevice[0]
                        if len(findDevice) >= 4:
                            keyvals[key] = val_dict
                        else:
                            keyvals[key] = {}
                    else:
                        keyvals[key] = {}

    openR.close()
    return keyvals

""" note, for debian and ubuntu files, can use the two functions below for either searching and setting ip addresses, or default gateways\
"""
#can either search for address, netmask or gateway, if they're defined per interface in the network config file
def readIP_or_GW_Deb(my_dict, InterfaceName, IP_or_GW, inet_or_inet6): 

    for key in my_dict:
        line = key.split()
        if len(line) >= 4 and line[0] == "iface" and line[1] == InterfaceName and line[2] == inet_or_inet6:
            return my_dict[key][IP_or_GW]


def set_IP_GW_Deb(fileI, my_dict, InterfaceName, IPAddress, PrefixLength, AddressFamily, DefaultGateway):
    fileO = open(fileI, 'w')
    if AddressFamily == "IPv4":
        inet = "inet"
    elif AddressFamily == "IPv6":
        inet = "inet6"
    for key in my_dict:

        line = key.split()
        if len(line) >= 4 and line[0] == "iface" and line[1] == InterfaceName and line[2] == inet:
            if IPAddress != '':
                my_dict[key]['address'] = IPAddress
            if PrefixLength != '':
                my_dict[key]['netmask'] = PrefixLength
            if DefaultGateway != '':
                my_dict[key]['gateway'] = DefaultGateway 

    #now to copy new values over to the actual config file

    for key, val in my_dict.iteritems():
        fileO.write(key + "\n" )
        for k,v in val.iteritems():
            fileO.write(str(k) + " " + str(v) + "\n")
        fileO.write("\n\n")
   
    fileO.close()   

def write_Deb(fileI, InterfaceName, IPAddress, BootProtocol, DefaultGateway, PrefixLength, AddressFamily):
    fileO = open(fileI, 'a')
    if AddressFamily == "IPv4":
        fileO.write("iface "+ InterfaceName + " inet " + BootProtocol + "\n")
    elif addressFamily == "IPv6":
        fileO.write("iface "+ InterfaceName + " inet6 " + BootProtocol + "\n")

    fileO.write('address ' + IPAddress)
    fileO.write('netmask ' + PrefixLength)
    fileO.write('gateway ' + DefaultGateway)

    fileO.close()


################ for the function removeValFrom_Deb-Ub() ###########################################################
##This function needs to be adjusted. For some reason, deletes everything but the values I'd like to delete
    ##for example, if I have a config file of the format:
    """
    auto eth0
    iface eth0 inet static
    address 1.1.1.1

    auto eth2
    iface eth2 inet static
    address 1.1.1.1
    netmask 2.2.2.2

    if I wish to delete address from eth0, will delete address and netmask  under eth2 and leave address.
    unfortunately I did not have enough time to fix this

    Also, if BootP == static and absent,in the case of the above config file, output should be:
    ...
    auto eth2
    iface eth2 inet static

    
    (no address or netmask here)


    if BootP == automtaic, output should be
    ...
    auto eth2
    iface eth2 inet static
    address
    netmask
    """
####################################################################################################################
    
def removeValFrom_Deb_Ub(fileI, my_dict, valuesToRemoveFromMD,AddressFamily, InterfaceName, BootProtocol, Ensure):
    fileO = open(fileI, 'w')
    if AddressFamily == "IPv4":
        inet = "inet"
    elif AddressFamily == "IPv6":
        inet = "inet6"

# in this case, want to remove the entire line of either address, gateway, and netmask (any one of those (including all) that are defined)
    if BootProtocol == "Static" and Ensure == "Absent":
        for val in valuesToRemoveFromMD:
            for key1 in my_dict:
                line = key1.strip()
                if len(line) >= 4 and line[0] == "iface" and line[1] == InterfaceName and line[2] == inet: 
                    for key2 in key1:
                        if  my_dict[key1][key2] == val:
                            del my_dict[key1][key2]

        for key, val in my_dict.iteritems():
            fileO.write(key + "\n" )
            for k,v in val.iteritems():
                fileO.write(str(k) + " " + str(v) + "\n")
            fileO.write("\n\n")

#in this case, only want to remove the values of address, netmask, or/and gateway
    elif BootProtocol == "Automatic":
        for val in valuesToRemoveFromMD:
            for key1 in my_dict:
                line = key1.strip()
                if len(line) >= 4 and line[0] == "iface" and line[1] == InterfaceName and line[2] == inet: 
                    for key2 in key1:
                        if  my_dict[key1][key2] == val:
                            del my_dict[key1][key2]

        for key, val in my_dict.iteritems():
            fileO.write(key + "\n" )
            for k,v in val.iteritems():
                fileO.write(str(k) + " " + str(v) + "\n")
            fileO.write("\n\n")        
   
    fileO.close()   



"""                                     DEFAULT GATEWAY                                      """

## SLES

def parse_gwSles(filePath):
    fOpen = open(filePath)
   
    md = []
    lines = fOpen.read().split("\n")
    for line in lines:
        tokens = line.split()
        md.append(tokens)
       
    fOpen.close()
    return md

def read_gwSles(md):
    return md[1][1]

def write_gwSles(Interfacename,def_gw,filePath): 
    md = parse_gwSles(filePath)
    fOpen = open(filePath, "w")
    md[1][0] = "default"
    md[1][1] = def_gw
    md[1][2] = "255.255.255.255"
    for cell in md:
        for val in cell:
            fOpen.write(val + " ")
        fOpen.write("\n")

    fOpen.close()


## RHEL/CENTOS/ORACLE                   

def read_gwRhel(md, addressType):  
    if addressType == "IPv4":
        readDict(md,'GATEWAY')
    elif addressType == "IPv6":
        readDict(md, 'IPV6_DEFAULTGW')

def write_gwRhel(filePath, md, gateway, addressType): 
    openW = open(filePath, 'w')
    if addressType == "IPv4":
        
        if md['GATEWAY'] in md:
            md['GATEWAY'] = gateway
        openW.write('GATEWAY' + "=" + md['GATEWAY'] + "\n")

        for key in md.keys():
            if key != 'GATEWAY':
                openW.write(key + "=" + md[key] + "\n")

    elif addressType == "IPV6":
        if md['IPV6_DEFAULTGW'] in md:
            md['IPV6_DEFAULTGW'] = gateway
        openW.write('IPV6_DEFAULTGW' + "=" + md['IPV6_DEFAULTGW'] + "\n")

        for key in md.keys():
            if key != 'IPV6_DEFAULTGW':
                openW.write(key + "=" + md[key] + "\n")

    openW.close()



"""                                         TEST/SET/GET FUNCTIONS                                       """
def Test(InterfaceName, IPAddress,  BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily):

    fileFiller= "/etc/sysconfig/network/ifcfg-%s" %InterfaceName
    rhelFileFiller = "/etc/sysconfig/network-scripts/ifcfg-%s" %InterfaceName
    debFileFiller = "/etc/network/interfaces"

        
    num = 0
##SLES:
    if os.path.isdir("/etc/sysconfig/network"):

        filler = parseDeb(fileFiller)
        print filler, "filler"

        if AddressFamily == "IPv4":
            if os.path.isfile(fileFiller):                 
                if readSlesIPAddr(fileFiller) == IPAddress:
                    num+=1
                if readDict(filler,'BOOTPROTO') == BootProtocol:
                    num+=1
                if read_gwSles(parse_gwSles("/etc/sysconfig/network/ifroute-%s" %InterfaceName)) == DefaultGateway:
                    num+=1
                if netmaskBitConversion(readDict(filler,'NETMASK')) == int(PrefixLength):
                    num+=1
                if num == 4:
                    return [0]
                else:
                    return [-1]
            else:
                print "File does not exist."
                return [-1]
        elif AddressFamily == "IPv6":
            num = 0
            if os.path.isfile(fileFiller):   
                if readSlesIPAddr(fileFiller) == IPAddress:
                    num +=1
                if readDict(filler, 'BOOTPROTO') == BootProtocol:
                    num += 1
                if read_gwSles(parse_gwSles("/etc/sysconfig/network/ifroute-%s" %InterfaceName)) == DefaultGateway:
                    num += 1
                if readDict(filler,'PREFIXLEN') == PrefixLength:
                    num += 1
                if num == 4:
                    return [0]
                else:
                    return [-1]
            else:
                print "File does not exist."
                return [-1]

##RHEL/CentOs/Oracle
#####################################
##### QUESTION
#######################################
#so i place default gateway in /etc/sysconfig/network, and ip/netmask in /etc/sysconfig/network-scripts/ifcfg-ethX
#does that mean I should also look in these respective files for gateway and ip/netmask respectively?

 
    elif os.path.isdir("/etc/sysconfig/network-scripts"):

        rhelFiller = parseSles(rhelFileFiller)
        
        if AddressFamily == "IPv4":
            num = 0
            if os.path.isfile(rhelFileFiller):
                if readSlesIPAddr(rhelFileFiller) == IPAddress:
                    num += 1
                if readDict(rhelFiller, 'BOOTPROTO') == BootProtocol:
                    num += 1
                if read_gwRhel("/etc/sysconfig/network", AddressFamily)== DefaultGateway:
                    num += 1
                if bitNetmaskConversion(readDict(rhelFiller,'NETMASK')) == PrefixLength:
                    num += 1
                if num == 4:
                    return [0]
                else:
                    return [-1]
            else:
                print "File does not exist"
                return [-1]
        elif AddressFamily == "IPv6":
            num = 0
            if os.path.isfile(rhelFileFiller):
                if readSlesIPAddr(rhelFileFiller) == IPAddress:
                    num += 1
                if readDict(rhelFiller, 'BOOTPROTO') == BootProtocol:
                    num += 1
                if read_gwRhel(rhelFileFiller, AddressFamily)== DefaultGateway:
                    num += 1
                if readDict(rhelFileFiller,'PREFIXLEN') == PrefixLength:
                    num += 1
                if num == 4:
                    return [0]
                else:
                    return [-1]
            else:
                print "File does not exist."
                return [-1]

    
    ##Debian/Ubuntu                         
    elif os.path.isdir("/etc/network"):
        if os.path.isfile(debFileFiller):

            debFiller = parseDeb(debFileFiller)

            if AddressFamily == "IPv4":
                num = 0
                if readIP_or_GW_Deb(debFiller,InterfaceName,'address', 'inet') == IPAddress:
                    num += 1
                if findDebBootPStatus(debFileFiller,InterfaceName) == BootProtocol:
                    num += 1
                if readIP_or_GW_Deb(debFiller,InterfaceName,'gateway', 'inet') == DefaultGateway:
                    num += 1
                if netmaskBitConversion(readIP_or_GW_Deb(debFiller, InterfaceName, 'netmask', 'inet')) == PrefixLength:
                    num += 1
                if num == 4:
                    return [0]
              
            elif AddressFamily == "IPv6":
                num = 0
                if readIP_or_GW_Deb(debFiller,InterfaceName,'address', 'inet6') == IPAddress:
                    num += 1
                if findDebBootPStatus(debFileFiller,InterfaceName) == BootProtocol:
                    num += 1
                if readIP_or_GW_Deb(debFiller,InterfaceName,'gateway', 'inet6') == DefaultGateway:
                    num += 1
                if readIP_or_GW_Deb(debFiller, InterfaceName, 'netmask', 'inet6') == PrefixLength:
                    num += 1
                if num == 4:
                    return [0]
        else:
            print "File does not exist"
            return [-1]
    else:
        print "ERROR: The network configuration directory could not be found."
  


def Get(InterfaceName, IPAddress,  BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily):
    return_arr = []
    fileFiller= "/etc/sysconfig/network/ifcfg-%s" %InterfaceName
    rhelFileFiller = "/etc/sysconfig/network-scripts/ifcfg-%s" %InterfaceName
    debFileFiller = "/etc/network/interfaces"

    
    if os.path.isdir("/etc/sysconfig/network/"):
        if os.path.isfile(fileFiller):
            filler = parseSles(fileFiller)
            if AddressFamily == "IPv4":
                if 'IPADDR' in filler and readDict(filler, 'IPADDR') != '':
                        IPAddress = readDict((filler), 'IPADDR')
                        Ensure = "Present"
                else:
                    IPAddress = ''
                    Ensure = "Absent"
                if 'NETMASK' in filler and readDict(filler, 'NETMASK') != '':
                    PrefixLength = netmaskBitConversion(readDict(filler, 'NETMASK'))
                else:
                    PrefixLength = ''

            elif AddressFamilly == "IPv6":
                if 'IPV6ADDR' in filler  and readDict(filler, 'IPV6ADDR')!= '':
                    IPAddress = readDict(filler, 'IPV6ADDR')
                    Ensure = "Present"
                else:
                    Ensure = "Absent"
                if 'PREFIXLEN' in filler and readDict(filler, 'PREFIXLEN') != '':
                    PrefixLength = readDict(filler, 'PREFIXLEN')
                else:
                    PrefixLength = ''
                
            BootProtocol = readDict(filler, 'BOOTPROTO')
            DefaultGateway = read_gwSles(parse_gwSles("/etc/sysconfig/network/ifroute-%s" %InterfaceName))

            return_arr = [0, InterfaceName, IPAddress,  BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily]
            
            return return_arr


 #set ensure to absent if ip address is not present, set ensure to present if it is for a given interface

    elif os.path.isdir("/etc/sysconfig/network-scripts"):
        if os.path.isfile(rhelFileFiller):
            rhelFiller = parseSles(rhelFileFiller)
            if AddressFamily == "IPv4":
                
                if 'IPADDR' in rhelFiller and readSlesIPAddr(rhelFileFiller) != '':
                    IPAddress = readSlesIPAddr(rhelFileFiller)
                    Ensure = "Present"
                else:
                    IPAddress = ''
                    Ensure = "Absent"
                if 'NETMASK' in rhelFiller and readDict(rhelFiller, 'NETMASK') != '':
                    PrefixLength = netmaskBitConversion(readDict(filler, 'NETMASK'))
                else:
                    PrefixLength = ''

            elif AddressFamily == "IPv6":
                if 'IPV6ADDR' in rhelFiller and readDict(filler, 'IPV6ADDR') != '':
                    IPAddress = readDict(filler, 'IPV6ADDR')
                    Ensure = "Present"
                else:
                    IPAddress = ''
                    Ensure = "Absent"
                
                if 'PREFIXLEN' in rhelFiller and readDict(rhelFiller, 'PREFIXLEN') != '':
                    PrefixLength = readDict(rhelFiller, 'PREFIXLEN')
                else:
                    PrefixLength = ''


            BootProtocol = readDict(rhelFiller, 'BOOTPROTO')
            D_gateway = read_gwRhel("/etc/sysconfig/network", AddressFamily)

            return_arr = [0, InterfaceName, IPAddress,  BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily]

            return return_arr

    elif os.path.isdir("/etc/network"):
        if os.path.isfile(debFileFiller):
            debFiller =  parseDeb(debFileFiller)

            if AddressFamily == "IPv4":
                if readIP_or_GW_Deb(debFiller,InterfaceName, "address", 'inet') != '':
                    IPAddress = readIP_or_GW_Deb(debFiller,InterfaceName, "address", 'inet')
                    Ensure = "Present"
                else:
                    IPAddress = ''
                    Ensure = "Absent"
                if readIP_or_GW_Deb(debFiller, InterfaceName, "netmask", "inet") != '':
                    PrefixLength = netmaskBitConversion(readIP_or_GW_Deb(debFiller, InterfaceName, "netmask", "inet"))
                else:
                    PrefixLength = ''
                    
            elif AddressFamily == "IPv6":
                if readIP_or_GW_Deb(debFiller,InterfaceName, "address", "inet6")!= '':
                    IPAddress = readIP_or_GW_Deb(debFiller,InterfaceName, "address", "inet6")
                    Ensure = "Present"
                else:
                    IPAddress = ''
                    Ensure = "Absent"
                if readIP_or_GW_Deb(debFiller, InterfaceName, "netmask", "inet6") != '':
                    PrefixLength = netmaskBitConversion(readIP_or_GW_Deb(debFiller, InterfaceName, "netmask", "inet6"))
                else:
                    PrefixLength = ''

            Netmask = readIP_or_GW_Deb(debFileFiller, InterfaceName, "netmask", "inet")
            BootProtocol = findDebBootPStatus(debFileFiller, InterfaceName)
            D_gateway = readIP_or_GW_Deb(debFiller,InterfaceName, "gateway", "inet")

            return_arr = [0, InterfaceName, IPAddress,  BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily]

            return return_arr

"""                SET FUNCTION                       """
                                     
def Set(InterfaceName, IPAddress,  BootProtocol, DefaultGateway, Ensure, PrefixLength, AddressFamily):

#SUSE
    if os.path.isdir("/etc/sysconfig/network"):
        if os.path.isfile("/etc/sysconfig/network/ifcfg-%s" %InterfaceName):
            fileFiller = "/etc/sysconfig/network/ifcfg-%s" %InterfaceName
            filler = parseSles(fileFiller)


#The process function was an attempt to create a config file for a respective linux distro if a device for a specified InterfaceName is set up,
#but no config file exists for it. Essentially, all I wanted to do here was navigate to the right network directory and touch a file with the right
#name. 


#            try: ##THIS WHOLE PROCESS THING DOESN"T WORK> WHY> I DON"T UNDERSTAND
#               (process_stdout, process_stderr, retval) = Process(["ip","link","show", InterfaceName])
#                print process_stderr, "PROCESS"
#                if process_stderr != '':
#                    (process_stdout, process_stderr, retval) = Process(["touch", "/etc/sysconfig/network/ifcfg-%s" %InterfaceName])
#            except OSError:
#                retval = 1
            
            
            if AddressFamily == "IPv4":
                if Ensure == "Present":
                    setIPv4Address(fileFiller, BootProtocol, IPAddress, PrefixLength)
                    write_gwSles(InterfaceName,DefaultGateway, "/etc/sysconfig/network/ifroute-%s" %InterfaceName)

                elif Ensure == "Absent":
                   if BootProtocol == "static" or BootProtocol == "automatic":
                       val_list = ['IPADDR','NETMASK','BOOTPROTO']
                       removeValSlesConfig(fileFiller, filler, val_list) 
                        

            if AddressFamily == "IPv6":
                if Ensure == "Present":
                    setIPv6Address(fileFiller, BootProtocol, IPAddress, PrefixLength)
            
                elif Ensure == "Absent":
                    if BootProtocol == "static" or BootProtocol == "automatic":
                        val_list = ['IPV6ADDR','PREFIXLEN','IPV6INIT','IPV6AUTOCONF','BOOTPROTO']
                        removeValSlesConfig(fileFiller, filler, val_list)
            return [0]


##RHEL/ORACLE/CENTOS

    
    if os.path.isdir("/etc/sysconfig/network-scripts/"):
        if os.path.isfile("/etc/sysconfig/network-scripts/ifcfg-%s" %InterfaceName):
            fileFiller = "/etc/sysconfig/network-scripts/ifcfg-%s" %InterfaceName
            filler = parseSles(fileFiller)

            
#            try:
                
#                (process_stdout3, process_stderr3, retval3) = Process(["ip","link","show", InterfaceName])
#                if process_stderr3 != '' :
#                    (process_stdout, process_stderr, retval) = Process(["cd","/etc/sysconfig/network"])
#                    pipe = subprocess.Popen(["cd","/etc/sysconfig/network-scripts"], stdout = subprocess.PIPE, close_fds=True, shell=True)
#                    (process_stdout2, process_stderr2, retval2) = Process(["touch", "ifcfg-%s" %InterfaceName])
#            except OSError:
#                retval = 1

            
            if AddressFamily == "IPv4":
                if Ensure == "Present":
                    if BootProtocol == "static":
                        write_StaticBootProto(fileFiller, filler, IPAddress, bitNetmaskConversion(PrefixLength))
                        write_gwRhel(fileFiller, DefaultGateway)
                    
                    elif BootProtocol == "automatic":
                        write_StaticDhcpBootProto(fileFiller, filler)

                        ##WAITING ON KB TO GIVE ME MATRIX FOR BOOTP AND DG

                elif Ensure == "Absent":
                    if BootProtocol == "static" or BootProtocol == "automatic":
                        val_list = ['IPADDR','NETMASK','BOOTPROTO']
                        removeValSlesConfig(fileFiller, filler,  val_list)
                  
            if AddressFamily == "IPv6":
                if Ensure == "Present":
                    if BootProtocol == "static":
                        write_StaticIPv6BootProto(fileFiller, filler, IPAddress, PrefixLength)
                        write_gwRhel(fileFiller, filler, DefaultGateway, AddressFamily)

                        ##NEED TO WRITE DEFAULT GATEWAY FOR IPV6
                    if BootProtocol == "automatic":
                        write_StaticIpv6BootProto(fileFiller, filler)

                elif Ensure == "Absent":
                    if BootProtocol == "static" or BootProtocol == "automatic":
                        val_list = ['IPV6ADDR','PREFIXLEN','IPV6INIT','IPV6AUTOCONF','BOOTPROTO']
                        removeValSlesConfig("/etc/sysconfig/network-scripts/ifcfg-%s" %InterfaceName, parseSles("/etc/sysconfig/network-scripts/ifcfg-%s" %InterfaceName), val_list)
            return [0]                        
 
##DEBIAN/UBUNTU

    if os.path.isdir("/etc/network"):

        if os.path.isfile("/etc/network/interfaces"):
            fileFiller = "/etc/network/interfaces"
            filler = parseDeb(fileFiller)

#            try:
               
#                (process_stdout3, process_stderr3, retval3) = Process(["ip","link","show", InterfaceName])
#                if process_stderr3 != '' :
#                    (process_stdout, process_stderr, retval) = Process(["cd","/etc/sysconfig/network"])
#                    pipe = subprocess.Popen(["cd","/etc/sysconfig/network-scripts"], stdout = subprocess.PIPE, close_fds=True, shell=True)
#                    (process_stdout2, process_stderr2, retval2) = Process(["touch", "ifcfg-%s" %InterfaceName])
#            except OSError:
#                retval = 1
#can do something here like write_Deb to configure the file after it has been touched

            if AddressFamily == "IPv4":
                if Ensure == "Present":
                    if BootProtocol == "static":
                        if readIP_or_GW_Deb(fileFiller, InterfaceName, "netmask", "inet") != '':
                            set_IP_GW_Deb(fileFiller, filler, InterfaceName, IPAddress, bitNetmaskConversion(PrefixLength), AddressFamily, DefaultGateway)
                        else:
                            write_Deb(fileI, InterfaceName, IPAddress, BootProtocol, DefaultGateway, bitNetmaskConversion(PrefixLength), AddressFamily)                            
                    elif BootProtocol == "automatic":
                        removeValFrom_Deb_Ub(fileFiller, filler, valuesToRemoveFromMD,AddressFamily, InterfaceName,BootProtocol, Ensure)

                elif Ensure == "Absent":
                    if BootProtocol == "static" or BootProtocol == "automatic":
                        valuesToRemoveFromMD=['address','netmask','gateway']
                        removeValFrom_Deb_Ub(fileFiller, filler, valuesToRemoveFromMD,AddressFamily, InterfaceName,BootProtocol, Ensure)
                            
                   

            if AddressFamily == "IPv6":
                if Ensure == "Present":
                    if BootProtocol == "static":
                        if readIP_or_GW_Deb(fileFiller, InterfaceName, "netmask", "inet6") != '':
                            set_IP_GW_Deb(fileFiller, filler, InterfaceName, IPAddress, PrefixLength, AddressFamily, DefaultGateway)
                        else:
                            write_Deb(fileI, InterfaceName, IPAddress, BootProtocol, DefaultGateway, PrefixLength, AddressFamily)
                            
                    elif BootProtocol == "automatic":
                        removeValFrom_Deb_Ub(fileFiller, filler, valuesToRemoveFromMD,AddressFamily, InterfaceName, BootProtocol, Ensure)

                elif Ensure == "Absent":
                    if BootProtocol == "static" or BootProtocol == "automatic":
                        removeValFrom_Deb_Ub(fileFiller, filler, valuesToRemoveFromMD,AddressFamily, InterfaceName,BootProtocol, Ensure)

            return [0]
        return [-1]
    return [-1]

    
    






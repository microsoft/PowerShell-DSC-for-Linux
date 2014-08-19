#from _future_ import print_function
#from _future_ import with_statement
#from contextlib import contextmanager

import os
import sys
import codecs
import socket
import fileinput
import re
import subprocess
def Set_Marshall(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
	Name = Name.decode("utf-8")
        DNSDomainName = DNSDomainName.decode("utf-8")
        TimeZoneName = TimeZoneName.decode("utf-8")
        AlternateTimeZoneName = AlternateTimeZoneName.decode("utf-8")

	retval = Set(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
	return retval

def Test_Marshall(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
	Name = Name.decode("utf-8")
        DNSDomainName = DNSDomainName.decode("utf-8")
        TimeZoneName = TimeZoneName.decode("utf-8")
        AlternateTimeZoneName = AlternateTimeZoneName.decode("utf-8")
	
	retval= Test(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
	return retval

def Get_Marshall(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
	Name = Name.decode("utf-8")
        DNSDomainName = DNSDomainName.decode("utf-8")
        TimeZoneName = TimeZoneName.decode("utf-8")
        AlternateTimeZoneName = AlternateTimeZoneName.decode("utf-8")
        
	retval = 0
	(retval, Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName) = Get(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)

	Name = Name.encode("utf-8")
        DNSDomainName = DNSDomainName.encode("utf-8")
        TimeZoneName = TimeZoneName.encode("utf-8")
        AlternateTimeZoneName = AlternateTimeZoneName.encode("utf-8")
	return [retval, Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName]

############################################################
### Begin user defined DSC functions
############################################################
global UNITTEST

#global Name
#global DNSDomainName
#global TimeZoneName
#global AlternateTimeZoneName 
#Name = "John's Computer"
#DNSDomainName = "jokes.com"
#TimeZoneName = "America/Los_Angeles"
#AlternateTimeZoneName = "Canada/Eastern"

UNITTEST = False 

def FilePaths(filePath):
    if os.path.islink("/etc/localtime"):
       os.unlink("/etc/localtime")
       os.symlink(filePath,"/etc/localtime")
    elif os.path.isfile("/etc/localtime"):
       os.remove("/etc/localtime")
       os.symlink(filePath, "/etc/localtime")
    elif os.path.islink("/etc/timezone"):
       os.unlink("/etc/timezone")
       os.symlink(filePath,"/etc/timezone")
    elif os.path.isfile("/etc/timezone"):
       os.remove("/etc/timezone")
       os.symlink(filePath, "/etc/timezone")
    else:
       os.symlink(filePath, "/etc/localtime")
    
def parseFile(fileName, num, propertyName, propertyDef):
    text = ""
    count = 0
    writeIn = propertyName + "= " + propertyDef + "\n"
    testFile = open(fileName, "r")
    for line in testFile:
       trimmedName = line.strip()
       if trimmedName[0:num] == propertyName:
          count = 1 
          text = text + writeIn
       else:
          text = text +  line + "\n"
    if count == 0:
       text = text + writeIn     
    testFile.close()
    testFile = open(fileName, "w")
    testFile.write(text)
    testFile.close()
       
       
def parseFileSmall(fileName, num, propertyName):
    testFile = open(fileName, "r")
    for line in testFile:
       trimmedName = line.strip()
       smallName = trimmedName[0:num]
       if smallName == propertyName:
          return trimmedName
   
def Set(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    DNSText = " "
    NameText = " "
    works = 0  
    if os.path.isfile(getNamePath2()):                   # Setting Name
       nameFile = open(getNamePath2(), "w")
       nameFile.write(Name)
    elif os.path.isfile(getNamePath()):
       nameFile = open(getNamePath(), 'w')
       nameFile.write(Name)
    else:
       works = -1
    if os.path.isfile(getDNSDomainNamePath()):
       parseFile(getDNSDomainNamePath(), 6, "domain", DNSDomainName)
    else:
       domainFile = open("/etc/resolv.conf", "w")
       domainText = "domain= " + DNSDomainName
       domainFile.write(domainText)
       domainFile.close()
    fullPath = "/usr/share/zoneinfo/" + TimeZoneName    #set TimeZoneName or AlternateTimeZoneName
    altFullPath = "/usr/share/zoneinfo/" + AlternateTimeZoneName
    if os.path.isfile(fullPath):
       FilePaths(fullPath)
    else:
       FilePaths(altFullPath)
    return [works]

def Get(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
   works = 0
   if os.path.isfile(getNamePath2()):
      nameFile = open(getNamePath2(), "r")           
      for line in nameFile:
         nameLine = line
   elif os.path.isfile(getNamePath()):
      nameFile = open(getNamePath(), "r")
      for line in nameFile:
         nameLine = line
   else:
      works = -1
      nameLine = ""
   DNSName = ""
   if os.path.isfile(getDNSDomainNamePath()):
      dnsName = parseFileSmall(getDNSDomainNamePath(), 6,"domain")
      if dnsName == None:
         works = -1
      else:
         print "I MADE IT"
         DNSName = dnsName.split("domain=", 1)
	 DNSName = DNSName[1].strip()
      
   if os.path.islink(getTimeZonePath()):                              
      timeZonePath = os.readlink(getTimeZonePath())
      timeZone = timeZonePath.split('/',4)
      
      timeZone2 = timeZone[4]
   elif os.path.islink(getTimeZonePath2()):
      timeZonePath = os.readlink(getTimeZonePath2())
      timeZone = timeZonePath.split('/', 4)
      timeZone2 = timeZone[4]                                                                                                                                                                                                                                             
   else:
      works = -1
   if works == 0:
      return [0, nameLine, DNSName , timeZone2, ""]
   else:
      return [-1, nameLine, DNSName, timeZone2, ""]
def Test(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    works = 0
    if os.path.isfile(getNamePath2()):
       nameFile = open(getNamePath2(), "r")
       for line in nameFile:
          nameStrip = line.strip()
          if nameStrip == Name:
	     print "\nName: " +nameStrip+ " = "+ Name
             break
       if nameStrip != Name:
          works = -1
    elif os.path.isfile(getNamePath()):
       nameFile = open(getNamePath(), "r")
       for line in nameFile:
          nameStrip = line.strip()
          if nameStrip == Name:
             break
       if nameStrip != Name:
          works = -1

    if os.path.isfile(getDNSDomainNamePath()):
       dnsName = parseFileSmall(getDNSDomainNamePath(), 6,"domain")
       if dnsName != None:
         DNSName = dnsName.split("domain=",1)
	 DNSName = DNSName[1].strip()
	 if DNSName != DNSDomainName:
	    works = -1
	 
    localfile = getTimeZonePath()
    timezone = getTimeZonePath2()
    if os.path.islink(localfile):
       timeZonePath = os.readlink(localfile)         #fix when get is fixed
       timeZone = timeZonePath.split('/',4)
       timeZone2 = timeZone[4]
    elif os.path.islink(timezone):
       timeZonePath = os.readlink(timezone)
       timeZone = timeZonePath.split('/',4)
       timeZone2 = timeZone[4]
    else:
        works = -1
    return [works]
       
def getNamePath():
    if UNITTEST == True:
        return nameString
    else:
        return "/etc/hostname"
    
def getNamePath2():
    if UNITTEST == True:
        return nameString
    else:
        return "/etc/HOSTNAME"
    
def getDNSDomainNamePath():
    if UNITTEST == True:
        return DNSDomainNameString
    else:
        return "/etc/resolv.conf"
#def getDNSDomainNamePath2():
#    if UNITTEST == True;
#       return DNSDomainNameString
#    else:
#        return "/etc/resolvconf"
    
def getTimeZonePath():
    if UNITTEST == True:
        return TimeZoneString
    else:
        return "/etc/localtime"
def getTimeZonePath2():
    if UNITTEST == True:
        return TimeZoneString
    else:
        return "/etc/timezone"

#Testing Name paths 
nameString = "sysconfig.txt"    #redhat,sles, cent os, oracle 
#UnitTest1()
nameString = "sysconfig2.txt"             # debian and ubuntu
#UnitTest2()
DNSDomainNameString = "resolv.txt"
#UnitTest3()
TimeZoneString = "localtime.txt"
#UnitTest4()
TimeZoneString = "localtime2.txt"
#UnitTest5()


#print Set(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
#print Get(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
#print Test(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)

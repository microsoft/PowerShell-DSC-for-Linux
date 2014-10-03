#from _future_ import print_function
#from _future_ import with_statement
#from contextlib import contextmanager

import os
import sys
import codecs
import socket
import fileinput
import re


def Set_Marshall(Address):
	Address = Address.decode("utf-8")

	retval = Set(Address)
	return retval

def Test_Marshall(Address):
	Address = Address.decode("utf-8")
	
	retval= Test(Address)
	return retval

def Get_Marshall(Address):
	Address = Address.decode("utf-8")

	retval = 0
	(retval, Address)

	Address = Address.encode("utf-8")
	
	return [retval, Address]
############################################################
### Begin user defined DSC functions
############################################################
#global Address
#Address = "10.231.248.89 54.54.54.54 32.32.123.32"      # Address given in the mof file that needs to be set

def Set(Address):
    times = -1
    bigBuffer = " "                                     # bigBuffer will over write testFile with the DNS Server Address's set (Up to 3)
    if os.path.isfile("/etc/resolv.conf") != True:
       testFile = open("/etc/resolv.conf", "w")
       testFile.close()
    testFile = open("/etc/resolv.conf", "r")            # open the file in read mode
    for line in testFile:                               # for each line in the file check for "dns-nameservers"     
       trimmed = line.strip()
       if trimmed[0:10] == "nameserver":           # if the first part of the trimmed line equals to "dns-nameservers" then add it to bigBuffer
          if times == -1:                                # delete any other dns-nameserver addresses found
             times = 0
             bigBuffer = bigBuffer + "nameserver " + Address + "\n"
       else:
          bigBuffer =  bigBuffer + line	  
    testFile.close()
    testFile = open("/etc/resolv.conf", "w")
    testFile.write(bigBuffer)
    testFile.close()
    return times

def Get(Address):
    DNS = ""
    works = -1
    testFile = open("/etc/resolv.conf", "r")            # open the file in read mode
    for line in testFile:
       trimmed = line.strip()
       if trimmed[0:10] == "nameserver":                    # change to nameserver and have it catch multiple lines ##
	  addr = trimmed.strip("nameserver")
	  addr = adrr.strip()
	  addr = addr.split(" ",2)
	  for addr in Array:
	     DNS += addr + "\n"
	  works = 0
    testFile.close()
    return [works, DNS]
       
def Test(Address):
   if os.path.isfile( "/etc/resolv.conf"):
      works = 0
   else:
      return -1
   testFile = open("/etc/resolv.conf", "r")            # open the file in read mode
   addr = Address.strip()                           # Split Address into 3 Addresses 
   splitAddress = addr.split(" ", 2)
   for line in testFile:
      trimmed = line.strip()
      if trimmed[0:10] == "nameserver":        # find the dns-nameservers line and split it according to spaces
         trimmed = trimmed.strip("nameserver")
         trimmed = strip()
         wordlist = trimmed.split(" ")              # test each DNS Server Address(up to 3) and see if it equals Address otherwise print out a message
	 if len(wordlist) > 1:
	    if wordlist[1] == splitAddress[0]: 
	       print "First DNSAddress is Correct"
            else:
	       return -1
	 if len(wordlist) > 2:
	    if wordlist[2] == splitAddress[1]:
	       print "Second DNSAddress is correct"
	    else:
	       return -1
	 if len(wordlist) > 3:
	    if wordlist[3] == splitAddress[2]:          
	       print "Third DNSAddress is correct"
	       return 0
	    else:
	       return -1
   
	 
	 	

Set(Address)
Get(Address)
print Test(Address)

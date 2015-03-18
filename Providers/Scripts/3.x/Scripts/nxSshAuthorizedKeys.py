#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

from __future__ import with_statement
from contextlib import contextmanager

import os
import sys
import pwd
import re
import time
import imp
protocol=imp.load_source('protocol','../protocol.py')

# [Key] string KeyComment;
# [write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
# [write] string UserName;
# [write] string Key;

global show_mof
show_mof=False

LogPath='/tmp/nxSshAuthorizedKeys.log'
def Set_Marshall(KeyComment,Ensure,UserName,Key):
    if Ensure == None:
        Ensure=''
    if KeyComment == None:
        KeyComment=''
    if UserName == None:
        UserName=''
    if Key == None:
        Key=''

    retval = Set(KeyComment,Ensure,UserName,Key)
    return retval

def Test_Marshall(KeyComment,Ensure,UserName,Key):
    if Ensure == None:
        Ensure=''
    if KeyComment == None:
        KeyComment=''
    if UserName == None:
        UserName=''
    if Key == None:
        Key=''

    retval = Test(KeyComment,Ensure,UserName,Key)
    return retval

def Get_Marshall(KeyComment,Ensure,UserName,Key):
    arg_names=list(locals().keys())
    if Ensure == None:
        Ensure=''
    if KeyComment == None:
        KeyComment=''
    if UserName == None:
        UserName=''
    if Key == None:
        Key=''

    retval = 0
    retval,KeyComment,Ensure,UserName,Key = Get(KeyComment,Ensure,UserName,Key)
    KeyComment = protocol.MI_String(KeyComment)
    Ensure = protocol.MI_String(Ensure)
    UserName = protocol.MI_String(UserName)
    Key = protocol.MI_String(Key)

    retd={}
    ld=locals()
    for k in arg_names :
        retd[k]=ld[k] 
    return retval, retd


############################################################
### Begin user defined DSC functions
############################################################

class Params:
    def __init__(self,KeyComment,Ensure,UserName,Key):

        if not ( "Present" in Ensure or "Absent" in Ensure ):
            Print('ERROR: Param Ensure must be Present or Absent.',file=sys.stderr)
            Log(LogPath,'ERROR: Param Ensure must be Present or Absent.')
            raise Exception('BadParameter')
        self.Ensure = Ensure

        if len(KeyComment)<1:
            Print('ERROR: Mandatory Param KeyComment missing.',file=sys.stderr)
            Log(LogPath,'ERROR: Mandatory Param KeyComment missing.')
            raise Exception('BadParameter')
        self.KeyComment = KeyComment

        if len(UserName)<1:
            Print('ERROR: Mandatory Param UserName missing.',file=sys.stderr)
            Log(LogPath,'ERROR: Mandatory Param UserName missing.')
            raise Exception('BadParameter')
        pw_st=None
        try:
             pw_st=pwd.getpwnam(UserName)
        except KeyError:
            Print('ERROR:  UserName:' + UserName + ' does not exist.',file=sys.stderr)
            Log(LogPath,'ERROR:  UserName:' + UserName + ' does not exist.')
            raise Exception('BadParameter')

        self.UserName = UserName
        self.UserHome=pw_st.pw_dir
        self.Key = Key # this can be empty for delete

def Set(KeyComment,Ensure,UserName,Key):
    retval=-1
    ShowMof('SET', KeyComment,Ensure,UserName,Key)
    try:
        p=Params(KeyComment,Ensure,UserName,Key)
    except Exception as e:
        Print('ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ',file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxSshAuthorizedKeysProvider. ')
        return [retval]
    if  p.Ensure == 'Present'  :
        if AddKey(p) == None:
            retval = 0
    if  p.Ensure == 'Absent' :
        if DelKey(p) == None:
            retval = 0
    return [retval]
   
def Test(KeyComment,Ensure,UserName,Key):
    retval=-1
    ShowMof('TEST', KeyComment,Ensure,UserName,Key)
    try:
        p=Params(KeyComment,Ensure,UserName,Key)
    except Exception as e:
        Print('ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ',file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxSshAuthorizedKeysProvider. ')
        return [retval]
    found,error=FindKey(p)
    if  found and p.Ensure == 'Present'  :
        retval = 0
    if not found and p.Ensure == 'Absent' :
        retval =0
    
    return [retval]

def Get(KeyComment,Ensure,UserName,Key):
    retval=0
    ShowMof('GET', KeyComment,Ensure,UserName,Key)
    try:
        p=Params(KeyComment,Ensure,UserName,Key)
    except Exception as e:
        Print('ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ',file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxSshAuthorizedKeysProvider. ')
        return [retval,KeyComment,Ensure,UserName,Key]
    found,error=FindKey(p)
    if found :
        p.Ensure == 'Present' 
    else:
        p.Ensure == 'Absent'
    return [retval,KeyComment,Ensure,UserName,Key]

def SetShowMof(a):
    global show_mof
    show_mof=a

def ShowMof(op, KeyComment,Ensure,UserName,Key):
    if not show_mof:
        return
    mof=''
    mof+= op + ' nxSshAuthorizedKeys MyKey \n'
    mof+='{\n'
    mof+='    KeyComment = "' + KeyComment + '"\n'
    mof+='    Ensure = "' + Ensure + '"\n'
    mof+='    UserName = "' + UserName + '"\n'
    mof+='    Key = "' + Key + '"\n'
    mof+='}\n'
    f=open('./test_mofs.log','a')
    Print(mof,file=f)
    f.close()


@contextmanager
def opened_w_error(filename, mode="a"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError as err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()


def Print(s,file=sys.stdout):
    file.write(s+'\n')
    
def Log(file_path,message):
    if len(file_path)<1 or len(message) < 1:
        return
    t = time.localtime()
    t = "%04u/%02u/%02u %02u:%02u:%02u " % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
    lines=re.sub(re.compile(r'^(.)',re.MULTILINE),t+r'\1',message)
    with opened_w_error(file_path,'a') as (F,error):
        if error:
            Print("Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: "  + error.strerror,file=sys.stderr)
            Log(LogPath,"Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: "  + error.strerror)
        else:
            F.write(lines + "\n")

def AddKey(p):
    d=p.UserHome+'/.ssh'
    path=d+'/authorized_keys'
    if os.path.isdir(d) == False:
        try:
            os.makedirs(d)
            os.chmod(d,0o700)
            os.chown(d,pwd.getpwnam(p.UserName).pw_uid,pwd.getpwnam(p.UserName).pw_gid)
        except IOError as error:
            Print("Exception creating directory " + d + " Error Code: " + str(error.errno) + " Error: "  + error.strerror,file=sys.stderr )
            Log(LogPath,"Exception creating directory " + d + " Error Code: " + str(error.errno) + " Error: "  + error.strerror)
            return error
        except OSError as error:
            Print("Exception opening directory " + d + " Error Code: " + str(error.errno) + " Error: " + error.strerror,file=sys.stderr )
            Log(LogPath,"Exception opening directory " + d + " Error Code: " + str(error.errno) + " Error: "  + error.strerror)
            return error
    if os.path.exists(path) == False:
        os.system('echo > '+path)

    error=None
    with opened_w_error(path,'r') as (F,error):
        if error:
            Print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror,file=sys.stderr )
            Log(LogPath,"Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
            return error
        flag='not found'
        n=''
        KC='#'+p.KeyComment
        for l in F.readlines():
            if flag=='found' :
                n+=p.Key+'\n'
                flag='done'
            elif KC == l[:len(l)-1]:
                flag='found'
                n+=l
            else :
                n+=l
        if flag=='not found':  
            n+=KC+'\n'+p.Key+'\n'
        F.close()
        with opened_w_error(path,'w+') as (F,error):
            F.write(n)
            F.close()
        os.chmod(path,0o700)
        os.chown(path,pwd.getpwnam(p.UserName).pw_uid,pwd.getpwnam(p.UserName).pw_gid)
    return error
    
def DelKey(p):
    path=p.UserHome+'/.ssh/authorized_keys'
    error=None
    found=False
    if not os.path.isfile(path):
        return error
    with opened_w_error(path,'r') as (F,error):
        if error:
            Print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror,file=sys.stderr )
            Log(LogPath,"Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror) 
            return error
        n=''
        KC='#'+p.KeyComment
        for l in F.readlines():
            if found==True:
                found=False #skip this line
                continue
            if KC == l[:len(l)-1]:
                found = True # set this true to skip the next line which is the key
                continue
            n+=l
        F.close()
        with opened_w_error(path,'w+') as (F,error):
            F.write(n)
            F.close()
    return error

def FindKey(p):
    path=p.UserHome+'/.ssh/authorized_keys'
    error=None
    found=False
    if not os.path.isfile(path):
        return found,error
    with opened_w_error(path,'r') as (F,error):
        if error:
            Print("Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror,file=sys.stderr )
            Log(LogPath,"Exception opening file " + path + " Error Code: " + str(error.errno) + " Error: " + error.strerror)
            return found,error
        KC='#'+p.KeyComment
        for l in F.readlines():
            if found == True :
                if len(p.Key) == 0 or p.Key == l[:len(l)-1]: # return true of the key is not provided
                    break
                else :
                    found = False
                    break
            if KC == l[:len(l)-1]:
                found = True
        F.close()
    return found,error

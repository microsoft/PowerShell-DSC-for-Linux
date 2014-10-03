#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================

from __future__ import print_function
from __future__ import with_statement
from contextlib import contextmanager

import os
import sys
import re
import time

#   [Key] string Name;
#   [write] string Value;
#   [Write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
#   [Write] boolean Path;
  
LogPath='/tmp/nxEnvironment.log'
def Set_Marshall(Name,Value,Ensure,Path):
    Name = Name.decode('utf-8')
    Value = Value.decode('utf-8')
    Ensure = Ensure.decode('utf-8')
    Path = Path.decode('utf-8')
    retval = Set(Name,Value,Ensure,Path)
    return retval

def Test_Marshall(Name,Value,Ensure,Path):
    Name = Name.decode('utf-8')
    Value = Value.decode('utf-8')
    Ensure = Ensure.decode('utf-8')
    Path = Path.decode('utf-8')
    retval = Test(Name,Value,Ensure,Path)
    return retval

def Get_Marshall(Name,Value,Ensure,Path):
    Name = Name.decode('utf-8')
    Value = Value.decode('utf-8')
    Ensure = Ensure.decode('utf-8')
    Path = Path.decode('utf-8')
    retval = 0
    retval,Name,Value,Ensure,Path = Get(Name,Value,Ensure,Path)

    return [retval,Name,Value,Ensure,Path]


############################################################
### Begin user defined DSC functions
############################################################

class Params:
    def __init__(self,Name,Value,Ensure,Path):

        if not ( "Present" in Ensure or "Absent" in Ensure ):
            print('ERROR: Param Ensure must be Present or Absent.',file=sys.stderr)
            Log(LogPath,'ERROR: Param Ensure must be Present or Absent.')
            raise Exception('BadParameter')
        self.Ensure = Ensure

        if len(Path)<1:
            print('ERROR: Mandatory Param Path missing.',file=sys.stderr)
            Log(LogPath,'ERROR: Mandatory Param Path missing.')
            raise Exception('BadParameter')
        elif not ( "True" in Path or "False" in Path ):
            print('ERROR: Param Path must be True or False.',file=sys.stderr)
            raise Exception('BadParameter')
        self.Path = Path

        if len(Name)<1 and 'True' not in Path:
            print('ERROR: Param Name must be set if Path <> True.',file=sys.stderr)
            Log(LogPath,'ERROR: Param Name must be set if Path <> True.')
            raise Exception('BadParameter')
        self.Name = Name

        if len(Value)<1:
            print('ERROR: Mandatory Param Value missing.',file=sys.stderr)
            Log(LogPath,'ERROR: Mandatory Param Value missing.')
            raise Exception('BadParameter')
        self.Value = Value


        self.file_path='/etc/environment'
        if 'True' in self.Path:
            self.file_path='/etc/profile.d/DSCEnvironment.sh'
            self.Name='PATH=$PATH:"'

        # check the configuration and create DSCEnvironment if needed.
        if not os.path.isfile('/etc/environment'):
            # create the /etc/environment file and source it from DSCEnvironment.sh
            os.system('echo > /etc/environment')
        if not os.path.isfile('/etc/profile.d/DSCEnvironment.sh'):
            os.system('echo ". /etc/environment" > /etc/profile.d/DSCEnvironment.sh')
        else: # file exists - add the sourceline if not already there
            found=False
            n=''
            with opened_w_error('/etc/profile.d/DSCEnvironment.sh','r+') as (F,error):
                if error:
                    raise Exception('BadParameter')
                for l in F.readlines():
                    if l.startswith('. /etc/environment'):
                        found=True
                    n+=l+'\n'
                if not found:
                    F.seek(0,0)
                    F.write('. /etc/environment\n'+n)
                F.close()
            
            
            
def Set(Name,Value,Ensure,Path):
    retval=-1
    try:
        p=Params(Name,Value,Ensure,Path)
    except Exception,e:
        print('ERROR - Unable to initialize nxEnvironmentProvider.  '+e.message,file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxEnvironmentProvider. '+ e.message)
        return [retval]
    if AddOrDelVar(p) == None:
            retval = 0
    return [retval]
   
def Test(Name,Value,Ensure,Path):
    retval=-1
    try:
        p=Params(Name,Value,Ensure,Path)
    except Exception,e:
        print('ERROR - Unable to initialize nxEnvironmentProvider.  '+e.message,file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxEnvironmentProvider. '+ e.message)
        return [retval]
    found,error=FindVar(p)
    if  found and p.Ensure == 'Present'  :
        retval = 0
    if not found and p.Ensure == 'Absent' :
        retval =0
    
    return [retval]

def Get(Name,Value,Ensure,Path):
#    import pdb; pdb.set_trace()
    retval=-1
    try:
        p=Params(Name,Value,Ensure,Path)
    except Exception,e:
        print('ERROR - Unable to initialize nxEnvironmentProvider.  '+e.message,file=sys.stderr)
        Log(LogPath,'ERROR - Unable to initialize nxEnvironmentProvider. '+ e.message)
        return [retval]
    found,error=FindVar(p)
    if  found and p.Ensure == 'Present'  :
        retval = 0
    if not found and p.Ensure == 'Absent' :
        retval =0
    return [retval,Name,Value,Ensure,Path]

@contextmanager
def opened_w_error(filename, mode="a"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError, err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()

def Log(file_path,message):
    if len(file_path)<1 or len(message) < 1:
        return
    t = time.localtime()
    t = "%04u/%02u/%02u %02u:%02u:%02u " % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
    lines=re.sub(re.compile(r'^(.)',re.MULTILINE),t+r'\1',message)
    with opened_w_error(file_path,'a') as (F,error):
        if error:
            print("Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr)
            Log(LogPath,"Exception opening logfile " + file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
        else:
            F.write(lines + "\n")

def AddOrDelVar(p):
    #preserve the ownership of this file
    found=False
    error=None
    st=None
    n=''
    if os.path.isfile(p.file_path):
        st=os.stat(p.file_path)
    with opened_w_error(p.file_path,'r+') as (F,error):
        if error:
            print("Exception opening file " + p.file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr )
            Log(LogPath,"Exception opening file " + p.file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
            return found,error
        for l in F.readlines():
            if p.Path == 'True' : 
                if l.startswith(p.Name+p.Value) and p.Ensure == 'Present': # is is already there - keep it if present requested otherwise skip
                            found=True
                            n+=l
                else: # not a match
                    n+=l
            else:
                if l.startswith(p.Name+'=') and p.Ensure == 'Present': # is is already there - keep it if present requested otherwise skip
                    found = True
                    l=p.Name+'="'+p.Value+'"\n' # set the variable to the new values
                    n+=l
                else:
                    n+=l
        if not found and p.Ensure == 'Present': # not found - present requested so add it.
            if p.Path == 'True':
                n+=p.Name+p.Value+'"\n'
            else:
                n+=p.Name+'="'+p.Value+'"\n'
        F.seek(0,0)
        F.write(n)
        F.close()
    if st !=None :
        os.chown(p.file_path,st.st_uid,st.st_gid)
    return error

def FindVar(p):
    found=False
    error=None
    if not os.path.isfile(p.file_path):
        return found
    with opened_w_error(p.file_path,'rb') as (F,error):
        if error:
            print("Exception opening file " + p.file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror,file=sys.stderr )
            Log(LogPath,"Exception opening file " + p.file_path + " Error Code: " + str(error.errno) + " Error: " + error.message + error.strerror)
            return found,error
        for l in F.readlines():
            if p.Path == 'True':
                if p.Name+p.Value in l:
                    found = True
            elif p.Name+ '="' +p.Value+'"' in l:
                    found = True
        F.close()
    return found,error

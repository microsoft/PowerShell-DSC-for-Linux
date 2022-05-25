#!/usr/bin/env python2
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================

from __future__ import print_function
from __future__ import with_statement

import os
import sys
import subprocess
import imp

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog



# [ClassVersion("1.0.0"),FriendlyName("nxMySqlGrant")] 
# class MSFT_nxMySqlGrantResource : OMI_BaseResource
# { 
#   [Key, Description("Name of MySQL user.")] String UserName;
#   [Key, Description("MySql database name to grant permissions.")] String DatabaseName;
#   [Write, Description("MySql connection credential used for the root.")] String ConnectionCredential;
#   [Write, Description("MySql user permission type."), ValueMap{"ALL PRIVILEGES", "CREATE", "DROP", "DELETE", "INSERT", "SELECT", "UPDATE", "EXECUTE"}, Values{"ALL PRIVILEGES", "CREATE", "DROP", "DELETE", "INSERT", "SELECT", "UPDATE", "EXECUTE"}] String PermissionType;
#   [Write, Description("Ensure given grant to mySql database present or absent."), ValueMap{"Present","Absent"}, Values{"Present","Absent"}] String Ensure;
# };

def init_vars(UserName, DatabaseName, ConnectionCredential, PermissionType, Ensure):
    if Ensure is None or len(Ensure) is 0:
        Ensure = 'Present'
    if UserName is None or len(UserName) is 0:
        print("Error: 'UserName' must be specified.\n", file=sys.stderr)
        LG().Log('ERROR', "Error: 'UserName' must be specified.\n")
        raise Exception("'UserName' must be specified")
    if DatabaseName is None or len(DatabaseName) is 0:
        DatabaseName='*'
    if ConnectionCredential is None or len(ConnectionCredential) is 0:
        ConnectionCredential=''
        print("WARNING: No ConnectionCredential specified.\n", file=sys.stderr)
        LG().Log('WARNING', "WARNING: No ConnectionCredential specified.\n")
    if PermissionType is None or len(PermissionType) is 0:
        PermissionType = 'ALL PRIVILEGES'
    return UserName, DatabaseName, ConnectionCredential, PermissionType, Ensure


def Set_Marshall(UserName, DatabaseName, ConnectionCredential, PermissionType, Ensure): 
    (UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure) =  init_vars(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure)
    retval = Set(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure)
    return retval


def Test_Marshall(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure):
    (UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure) =  init_vars(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure)
    if Test(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure):
        retval=[0]
    else :
        retval=[-1]
    return retval


def Get_Marshall(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure):
    arg_names = list(locals().keys())
    (UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure) = init_vars(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure)
    retval = 0
    (UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure) = Get(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure)   
    UserName = protocol.MI_String(UserName)
    DatabaseName = protocol.MI_String(DatabaseName)
    PermissionType = protocol.MI_String(PermissionType)
    ConnectionCredential = protocol.MI_String(ConnectionCredential)
    Ensure = protocol.MI_String(Ensure)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


def Set(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure):
    retval = [0]
    if AddRemovePermission(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure) == False:
        retval = [-1]
    return retval


def Test(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure):
    found = IsPermissionPresent(UserName, DatabaseName, ConnectionCredential, PermissionType)
    if (found and Ensure == 'Present') or ( not found and Ensure == 'Absent'):
        return True
    return False


def Get(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure):
    found = IsPermissionPresent(UserName, DatabaseName, ConnectionCredential, PermissionType)
    if found:
        Ensure = 'Present'
    else :
        Ensure = 'Absent'
    return UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure


def IsPermissionPresent(UserName, DatabaseName, ConnectionCredential, PermissionType):
    Host='%'
    if '@' in UserName:
        myName=UserName.split('@')[0].strip("'")
        Host=UserName.split('@')[1].strip("'")
    else:
        myName=UserName.strip("'")
    cmd='mysql -u root -e "SHOW GRANTS FOR ' +"'" + myName+"'@'" + Host + "';"+'"'
    os.environ['MYSQL_PWD'] = ConnectionCredential
    code, out=RunGetOutput(cmd,False)
    os.environ['MYSQL_PWD'] = ''
    perm="GRANT " + PermissionType + " ON `" + DatabaseName + "`.* TO '" + myName+"'@'" + Host + "'"
    if perm in out:
        return True
    return False

def AddRemovePermission(UserName, DatabaseName,  ConnectionCredential, PermissionType, Ensure):
    cmd=''
    out=''
    code=0
    if '@' in UserName:
        myName=UserName.split('@')[0].strip("'")
        Host=UserName.split('@')[1].strip("'")
    else:
        myName=UserName.strip("'")
    present=IsPermissionPresent(UserName, DatabaseName, ConnectionCredential, PermissionType)
    if Ensure == 'Present':
        if present:
            return True
        else :
            cmd="GRANT " + PermissionType + " ON " + DatabaseName + ".* TO '" + myName+"'@'" + Host  + "';"
    elif present:
        cmd = "REVOKE "+ PermissionType + " ON " + DatabaseName + ".* FROM '" + myName+"'@'" + Host  + "';"
    if len(cmd) > 0 :
        cmd='mysql -u root -e "' + cmd + ' FLUSH PRIVILEGES;"'
        os.environ['MYSQL_PWD'] = ConnectionCredential
        code, out=RunGetOutput(cmd,False)
        os.environ['MYSQL_PWD'] = ''
    return code == 0

def RunGetOutput(cmd, no_output, chk_err=True):
    """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT,
    trapping expected exceptions.
    Reports exceptions to Error if chk_err parameter is True
    """
    def check_output(no_output, *popenargs, **kwargs):
        r"""Backport from subprocess module from python 2.7"""
        if 'stdout' in kwargs:
            raise ValueError(
                'stdout argument not allowed, it will be overridden.')
        if no_output:
            out_file = None
        else:
            out_file = subprocess.PIPE
        process = subprocess.Popen(stdout=out_file, *popenargs, **kwargs)
        output, unused_err = process.communicate()
        retcode = process.poll()
        if retcode:
            cmd = kwargs.get("args")
            if cmd is None:
                cmd = popenargs[0]
            raise CalledProcessError(retcode, cmd, output=output)
        return output

    # Exception classes used by this module.
    class CalledProcessError(Exception):

        def __init__(self, returncode, cmd, output=None):
            self.returncode = returncode
            self.cmd = cmd
            self.output = output

        def __str__(self):
            return "Command '%s' returned non-zero exit status %d" \
                   % (self.cmd, self.returncode)

    try:
        output = check_output(no_output, cmd, stderr=subprocess.STDOUT, shell=True)
    except CalledProcessError, e:
        if chk_err:
            print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stdout)
            LG().Log('ERROR', 'CalledProcessError.  Error Code is ' + str(e.returncode))
            print(
                'CalledProcessError.  Command string was ' + e.cmd, file=sys.stdout)
            LG().Log('ERROR', 
                'CalledProcessError.  Command string was ' + e.cmd)
            print('CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'), file=sys.stdout)
            LG().Log('ERROR', 'CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'))
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, e.output.decode('utf-8').encode('ascii', 'ignore')

    if no_output:
        return 0, None
    else:
        return 0, output.decode('utf-8').encode('ascii', 'ignore')

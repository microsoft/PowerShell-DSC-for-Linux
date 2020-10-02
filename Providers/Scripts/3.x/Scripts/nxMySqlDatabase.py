#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================

import os
import sys
import subprocess
import imp

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

# mysqladmin -u root password 'new-password'
# mysqladmin -h localhost -u root -ppassword create bedrock
# mysql -e "use mysql; show databases; quit"

# [ClassVersion("1.0.0"),FriendlyName("nxMySqlDatabase")] 
# class MSFT_nxMySqlDatabaseResource : OMI_BaseResource
# {
#     [Key, Description("Name of the database.")] String Name;
#     [Write, Description("Should the database be present or absent."), \
#     ValueMap{"Present","Absent"}, Values{"Present","Absent"}] String Ensure;
#     [Write, Description("The root credential that is used to install MySql server.")] \
#     String ConnectionCredential;
# };

def Set_Marshall(Name, ConnectionCredential, Ensure): 
    (Name, ConnectionCredential, Ensure) = init_vars(Name, ConnectionCredential, Ensure)
    retval = Set(Name, ConnectionCredential, Ensure)
    return retval


def Test_Marshall(Name, ConnectionCredential, Ensure):
    (Name, ConnectionCredential, Ensure) = init_vars(Name, ConnectionCredential, Ensure)
    if Test(Name, ConnectionCredential, Ensure):
        retval=[0]
    else :
        retval=[-1]
    return retval


def Get_Marshall(Name, ConnectionCredential, Ensure):
    arg_names = list(locals().keys())
    retval = 0
    (Name, ConnectionCredential, Ensure) = init_vars(Name, ConnectionCredential, Ensure)
    (Name, ConnectionCredential, Ensure) = Get(Name, ConnectionCredential, Ensure)
    Name = protocol.MI_String(Name)
    ConnectionCredential = protocol.MI_String(ConnectionCredential)
    Ensure = protocol.MI_String(Ensure)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

def init_vars(Name, ConnectionCredential, Ensure):
    if Ensure is None or len(Ensure) is 0:
        Ensure = 'Present'
    if ConnectionCredential is None or len(ConnectionCredential) is 0:
        ConnectionCredential=''
        print("WARNING: No ConnectionCredential specified.\n", file=sys.stderr)
        LG().Log('WARNING', "WARNING: No ConnectionCredential specified.\n")
    if Name is None or len(Name) is 0:
        print("Error: 'Name' must be specified.\n", file=sys.stderr)
        LG().Log('ERROR', "Error: 'Name' must be specified.\n")
        raise Exception("Error: 'Name' must be specified")
    return Name, ConnectionCredential, Ensure

def Set(Name, ConnectionCredential, Ensure):
    retval = [0]
    if AddRemoveDatabase(Name, ConnectionCredential, Ensure) == False:
        retval = [-1]
    return retval


def Test(Name, ConnectionCredential, Ensure):
    found = IsDatabasePresent(Name, ConnectionCredential)
    if (found and Ensure == 'Present') or ( not found and Ensure == 'Absent'):
        return True
    return False


def Get(Name, ConnectionCredential, Ensure):
    found = IsDatabasePresent(Name, ConnectionCredential)
    if found:
        Ensure = 'Present'
    else :
        Ensure = 'Absent'
    return Name, ConnectionCredential, Ensure


def IsDatabasePresent(Name, ConnectionCredential):
    cmd='mysql -u root -e "SHOW DATABASES WHERE \`Database\` = ' + "'" + Name+"';"+'"'
    os.environ['MYSQL_PWD'] = ConnectionCredential
    code, out=RunGetOutput(cmd,False)
    os.environ['MYSQL_PWD'] = ''
    if '\n'+Name+'\n' in out:
        return True
    return False

def AddRemoveDatabase(Name, ConnectionCredential, Ensure):
    cmd=''
    out=''
    code=0
    present=IsDatabasePresent(Name, ConnectionCredential)
    if Ensure == 'Present':
        if present:
            return True
        else :
            cmd="CREATE DATABASE " + Name +  ";"
    elif present:
        cmd = "DROP DATABASE " + Name + ";"
    if len(cmd) > 0 :
        cmd='mysql -u root -e "' + cmd + '"'
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

    output=b''
    try:
        output = check_output(no_output, cmd, stderr=subprocess.STDOUT, shell=True)
        if output is None:
            output=b''
    except CalledProcessError as e:
        if chk_err:
            print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stdout)
            LG().Log(
                'ERROR', 'CalledProcessError.  Error Code is '
                + str(e.returncode))
            print(
                'CalledProcessError.  Command string was '
                + e.cmd, file=sys.stdout)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command string was ' + e.cmd)
            print('CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('ascii','ignore'), file=sys.stdout)
            LG().Log(
                'ERROR', 'CalledProcessError.  Command result was '
                + (e.output[:-1]).decode('ascii','ignore'))
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, e.output.decode('ascii','ignore')

    if no_output:
        return 0, None
    else:
        return 0, output.decode('ascii','ignore')

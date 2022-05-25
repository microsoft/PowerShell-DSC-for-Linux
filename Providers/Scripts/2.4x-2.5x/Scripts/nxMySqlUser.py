#!/usr/bin/env python2
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

# [ClassVersion("1.0.0"),FriendlyName("nxMySqlUser")] 
# class MSFT_nxMySqlUserResource : OMI_BaseResource
# { 
#   [Key, Description("Name of MySQL user to create or remove.")] String Name;
#   [Write, Description("Credential for MySql user."), EmbeddedInstance("MSFT_Credential")] String Credential;
#   [Write, Description("MySql connection credential used to create a user."), EmbeddedInstance("MSFT_Credential")] String ConnectionCredential;
#   [Write, Description("Ensure mysql user is present or absent."), ValueMap{"Present","Absent"}, Values{"Present","Absent"}] String Ensure;
# };

def Set_Marshall(Name, Credential, ConnectionCredential, Ensure): 
    (Name, Credential,  ConnectionCredential, Ensure) = init_vars(Name, Credential,  ConnectionCredential, Ensure)
    retval = Set(Name, Credential,  ConnectionCredential, Ensure)
    return retval


def Test_Marshall(Name, Credential,  ConnectionCredential, Ensure):
    (Name, Credential,  ConnectionCredential, Ensure) = init_vars(Name, Credential,  ConnectionCredential, Ensure)
    if Test(Name, Credential,  ConnectionCredential, Ensure):
        retval=[0]
    else :
        retval=[-1]
    return retval


def Get_Marshall(Name, Credential,  ConnectionCredential, Ensure):
    arg_names = list(locals().keys())
    (Name, Credential,  ConnectionCredential, Ensure) = init_vars(Name, Credential,  ConnectionCredential, Ensure)
    retval = 0
    (Name, Credential,  ConnectionCredential, Ensure) = Get(Name, Credential,  ConnectionCredential, Ensure)
    Name = protocol.MI_String(Name)
    Credential = protocol.MI_String(Credential)
    ConnectionCredential = protocol.MI_String(ConnectionCredential)
    Ensure = protocol.MI_String(Ensure)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

def init_vars(Name, Credential,  ConnectionCredential, Ensure):
    if Ensure is None or len(Ensure) is 0:
        Ensure = 'Present'
    if ConnectionCredential is None or len(ConnectionCredential) is 0:
        ConnectionCredential=''
        Print("WARNING: No ConnectionCredential specified.\n", file=sys.stderr)
        LG().Log('WARNING', "WARNING: No ConnectionCredential specified.\n")
    if Credential is None or len(Credential) is 0:
        Credential=''
        Print("WARNING: No User Credential specified.\n", file=sys.stderr)
        LG().Log('WARNING', "WARNING: No User Credential specified.\n")
    if Name is None or len(Name) is 0:
        Print("Error: 'Name' must be specified.\n", file=sys.stderr)
        LG().Log('ERROR', "Error: 'Name' must be specified.\n")
        raise Exception("Error: 'Name' must be specified")
    Name=Name.strip("`")
    Name=Name.strip("'")
    return Name, Credential,  ConnectionCredential, Ensure

def Set(Name, Credential,  ConnectionCredential, Ensure):
    retval = [0]
    if AddRemoveUser(Name, Credential,  ConnectionCredential, Ensure) == False:
        retval = [-1]
    return retval


def Test(Name, Credential,  ConnectionCredential, Ensure):
    found = IsUserPresent(Name, ConnectionCredential)
    if (found and Ensure == 'Present') or ( not found and Ensure == 'Absent'):
        return True
    return False


def Get(Name, Credential,  ConnectionCredential, Ensure):
    found = IsUserPresent(Name, ConnectionCredential)
    if found:
        Ensure = 'Present'
    else :
        Ensure = 'Absent'
    return Name, Credential,  ConnectionCredential, Ensure


def IsUserPresent(Name, ConnectionCredential):
    Host='%'
    if '@' in Name:
        myName=Name.split('@')[0]
        Host=Name.split('@')[1]
    else:
        myName=Name
    cmd='mysql -u root -e "use mysql; select user from user where user=' \
    + "'" + myName + "'" + " and host='" + Host +  "';" + '"'
    os.environ['MYSQL_PWD'] = ConnectionCredential
    code, out=RunGetOutput(cmd,False)
    os.environ['MYSQL_PWD'] = ''
    Print(repr(out))
    if '\n'+myName+'\n' in out:
        return True
    return False

def AddRemoveUser(Name, Credential,  ConnectionCredential, Ensure):
    cmd=''
    out=''
    code=0
    present=IsUserPresent(Name, ConnectionCredential)
    if Ensure == 'Present':
        if present:
            cmd="SET PASSWORD FOR " + Name + " = PASSWORD('"+ Credential + "');"
        else :
            cmd="CREATE USER " + Name + " IDENTIFIED BY '" + Credential + "';"
    elif present:
        cmd = "DROP USER " + Name + ";"
    if len(cmd) > 0 :
        cmd='mysql -u root -e "' + cmd + ' FLUSH PRIVILEGES;"'
        os.environ['MYSQL_PWD'] = ConnectionCredential
        Print(cmd)
        code, out=RunGetOutput(cmd,False)
        os.environ['MYSQL_PWD'] = ''
    return code == 0


def Print(s, file=sys.stdout):
    file.write(s + '\n')


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
            Print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stdout)
            LG().Log('ERROR', 'CalledProcessError.  Error Code is ' + str(e.returncode))
            Print(
                'CalledProcessError.  Command string was ' + e.cmd, file=sys.stdout)
            LG().Log('ERROR', 
                'CalledProcessError.  Command string was ' + e.cmd)
            Print('CalledProcessError.  Command result was ' +
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

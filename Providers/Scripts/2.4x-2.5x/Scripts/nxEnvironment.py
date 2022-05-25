#!/usr/bin/env python2
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================

import os
import sys
import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

global show_mof
show_mof = False


#   [Key] string Name;
#   [write] string Value;
#   [Write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
#   [Write] boolean Path;


def init_vars(Name, Value, Ensure, Path):
    if Name is not None:
        Name = Name.encode('ascii', 'ignore')
    else:
        Name = ''
    if Value is not None:
        Value = Value.encode('ascii', 'ignore')
    else:
        Value = ''
    if Ensure is not None and Ensure != '':
        Ensure = Ensure.encode('ascii', 'ignore')
    else:
        Ensure = 'present'
    if Path is None:
        Path = False
    Path = ( Path == True )
    return Name, Value, Ensure.lower(), Path


def Set_Marshall(Name, Value, Ensure, Path):
    (Name, Value, Ensure, Path) = init_vars(Name, Value, Ensure, Path)
    retval = Set(Name, Value, Ensure, Path)
    return retval


def Test_Marshall(Name, Value, Ensure, Path):
    (Name, Value, Ensure, Path) = init_vars(Name, Value, Ensure, Path)
    retval = Test(Name, Value, Ensure, Path)
    return retval


def Get_Marshall(Name, Value, Ensure, Path):
    arg_names = list(locals().keys())
    (Name, Value, Ensure, Path) = init_vars(Name, Value, Ensure, Path)
    retval = 0
    retval, Name, Value, Ensure, Path = Get(Name, Value, Ensure, Path)
    Name = protocol.MI_String(Name)
    Value = protocol.MI_String(Value)
    Ensure = protocol.MI_String(Ensure)
    Path = protocol.MI_Boolean(Path)

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


############################################################
# Begin user defined DSC functions
############################################################

def SetShowMof(a):
    global show_mof
    show_mof = a


def ShowMof(op, Name, Value, Ensure, Path):
    if not show_mof:
        return
    mof = ''
    mof += op + ' nxEnvironment MyEnv \n'
    mof += '{\n'
    mof += '    Name = "' + Name + '"\n'
    mof += '    Value = "' + Value + '"\n'
    mof += '    Ensure = "' + Ensure + '"\n'
    mof += '    Path = "' + str(Path) + '"\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    Print(mof, file=f)
    f.close()


class Params:

    def __init__(self, Name, Value, Ensure, Path):

        if not ("present" in Ensure or "absent" in Ensure):
            Print(
                'ERROR: Param Ensure must be "Present" or "Absent".', file=sys.stderr)
            LG().Log(
                'ERROR', 'ERROR: Param Ensure must be "Present" or "Absent".')
            raise Exception('BadParameter')
        self.Ensure = Ensure

        if Path is not True and Path is not False:
            Print('ERROR: Param Path must be True or False.', file=sys.stderr)
            LG().Log('ERROR', 'ERROR: Param Path must be True or False.')
            raise Exception('BadParameter')
        self.Path = Path

        if len(Name) < 1 and True is not Path:
            Print(
                'ERROR: Param Name must be set if Path <> True.', file=sys.stderr)
            LG().Log('ERROR', 'ERROR: Param Name must be set if Path <> True.')
            raise Exception('BadParameter')

        self.Name = Name
        self.Value = Value

        self.file_path = '/etc/environment'
        if True is self.Path:
            self.file_path = '/etc/profile.d/DSCEnvironment.sh'
            self.Name = 'PATH=$PATH:"'

        # check the configuration and create DSCEnvironment if needed.
        if not os.path.isfile('/etc/environment'):
            # create the /etc/environment file and source it from
            # DSCEnvironment.sh
            os.system('echo > /etc/environment')
        if not os.path.exists('/etc/profile.d'):
            os.system('mkdir /etc/profile.d/')
        if not os.path.isfile('/etc/profile.d/DSCEnvironment.sh'):
            os.system(
                'echo ". /etc/environment" > /etc/profile.d/DSCEnvironment.sh')
        else:  # file exists - add the sourceline if not already there
            found = False
            n = ''
            F, error = opened_w_error('/etc/profile.d/DSCEnvironment.sh', 'r+')
            if error:
                raise Exception('BadParameter')
            for l in F.readlines():
                if l.startswith('. /etc/environment'):
                    found = True
                n += l
            if not found:
                F.seek(0, 0)
                F.write('. /etc/environment\n' + n)
            F.close()


def Set(Name, Value, Ensure, Path):
    retval = -1
    try:
        p = Params(Name, Value, Ensure, Path)
    except Exception, e:
        Print(
            'ERROR - Unable to initialize nxEnvironmentProvider.  ' +
            str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxEnvironmentProvider. ' + str(e))
        return [retval]
    ShowMof('SET', Name, Value, Ensure, Path)
    if AddOrDelVar(p) is None:
        retval = 0
    return [retval]


def Test(Name, Value, Ensure, Path):
    retval = -1
    try:
        p = Params(Name, Value, Ensure, Path)
    except Exception, e:
        Print(
            'ERROR - Unable to initialize nxEnvironmentProvider.  ' +
            str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxEnvironmentProvider. ' + str(e))
        return [retval]
    ShowMof('TEST', Name, Value, Ensure, Path)

    found, error = FindVar(p)
    if found and p.Ensure == 'present':
        retval = 0
    if not found and p.Ensure == 'absent':
        retval = 0

    return [retval]


def Get(Name, Value, Ensure, Path):
    retval = -1
    try:
        p = Params(Name, Value, Ensure, Path)
    except Exception, e:
        Print(
            'ERROR - Unable to initialize nxEnvironmentProvider.  ' +
            str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxEnvironmentProvider. ' + str(e))
        return [retval, Name, Value, Ensure, Path]
    ShowMof('GET', Name, Value, Ensure, Path)
    found, error = FindVar(p)
    if found and p.Ensure == 'present':
        retval = 0
    if not found and p.Ensure == 'absent':
        retval = 0
    return [retval, Name, Value, Ensure, Path]


def opened_w_error(filename, mode="a"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode=mode)
    except IOError, err:
        return None, err
    return f, None


def Print(s, file=sys.stdout):
    file.write(s + '\n')


def AddOrDelVar(p):
    # preserve the ownership of this file
    found = False
    error = None
    st = None
    n = ''
    if os.path.isfile(p.file_path):
        st = os.stat(p.file_path)
    F, error = opened_w_error(p.file_path, 'r')
    if error:
        Print("Exception opening file " + p.file_path + ' Error: ' + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + p.file_path + ' Error: ' + str(error))
        return found, error
    for l in F.readlines():
        if p.Path is True:
            if l.startswith('PATH=$PATH:"' + p.Value):
                # is is already there - keep it if present requested otherwise
                # skip
                if p.Ensure == 'present':
                    found = True
                    n += l
                else:
                    found = True
            else:  # not a match
                n += l
        else:
            if l.startswith(p.Name + '='):
                found = True
                if p.Ensure == 'present':
                    # set the variable to the new values
                    l = p.Name + '=' + p.Value + '\n'
                    n += l
            else:
                n += l
    # not found - present requested so add it.
    if not found and p.Ensure == 'present':
        if p.Path is True:
            n += p.Name + p.Value + '"\n'
        else:
            n +=  p.Name + '=' + p.Value + '\n'
            
    F.close()

    F, error = opened_w_error(p.file_path, 'w')
    F.write(n)
    F.close()
    if st is not None:
        os.chown(p.file_path, st.st_uid, st.st_gid)
    return error


def FindVar(p):
    found = False
    error = None
    if not os.path.isfile(p.file_path):
        return found, error
    F, error = opened_w_error(p.file_path, 'rb')
    if error:
        Print("Exception opening file " + p.file_path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + p.file_path + " Error: " + str(error))
        return found, error
    for l in F.readlines():
        if p.Path is True:
            if p.Value in l:
                found = True
        elif p.Name + '=' + p.Value in l:
            found = True
    F.close()
    return found, error

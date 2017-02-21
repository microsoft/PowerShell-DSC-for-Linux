#!/usr/bin/env python
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

# [Key] string Name;
#
# [Write, ValueMap{"Pass", "Fail"}, Values{"Pass", "Fail"}] 
# string Value;
#
# [Write, ValueMap{"Present", "Absent"}, Values{"Present", "Absent"}] 
# string Ensure;

def init_vars(Name, Value, Ensure):
    if Name is not None and Name != '':
        Name = Name.encode('ascii', 'ignore')
    else:
        Name = ''

    if Value is not None and Value != '':
        Value = Value.encode('ascii', 'ignore').lower()
    else:
        Value = 'pass'

    if Ensure is not None and Ensure != '':
        Ensure = Ensure.encode('ascii', 'ignore').lower()
    else:
        Ensure = 'present'

    return Name, Value, Ensure

def Set_Marshall(Name, Value, Ensure):
    (Name, Value, Ensure) = init_vars(Name, Value, Ensure)
    retval = Set(Name, Value, Ensure)
    return retval

def Test_Marshall(Name, Value, Ensure):
    (Name, Value, Ensure) = init_vars(Name, Value, Ensure)
    retval = Test(Name, Value, Ensure)
    return retval    

def Get_Marshall(Name, Value, Ensure):
    arg_names = list(locals().keys())
    (Name, Value, Ensure) = init_vars(Name, Value, Ensure)
    retval = 0
    retval, Name, Value, Ensure = Get(Name, Value, Ensure)
    Name = protocol.MI_String(Name)
    Value = protocol.MI_String(Value)
    Ensure = protocol.MI_String(Ensure)
    
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


class Params:

    def __init__(self, Name, Value, Ensure):

        if not ("present" in Ensure or "absent" in Ensure):
            Print(
                'ERROR: Param Ensure must be "Present" or "Absent".', file=sys.stderr)
            LG().Log(
                'ERROR', 'ERROR: Param Ensure must be "Present" or "Absent".')
            raise Exception('BadParameter')

        self.Ensure = Ensure

        if len(Name) < 1:
            Print(
                'ERROR: Param Name must be set.', file=sys.stderr)
            LG().Log('ERROR', 'ERROR: Param Name must be set if Path <> True.')
            raise Exception('BadParameter')

        self.Name = Name

        if not ("pass" in Ensure or "fail" in Ensure):
            Print(
                'ERROR: Param Ensure must be "Pass" or "Fail".', file=sys.stderr)
            LG().Log(
                'ERROR', 'ERROR: Param Ensure must be "Pass" or "Fail".')
            raise Exception('BadParameter')

        self.Value = Value.lower

############################################################
# DSC functions
############################################################
def SetShowMof(a):
    global show_mof
    show_mof = a

def ShowMof(op, Name, Value, Ensure):
    if not show_mof:
        return
    mof = ''
    mof += op + ' nxNop MyNop \n'
    mof += '{\n'
    mof += '    Name = "' + Name + '"\n'
    mof += '    Value = "' + Value + '"\n'
    mof += '    Ensure = "' + Ensure + '"\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    Print(mof, file=f)
    f.close()

def Set(Name, Value, Ensure):
    retval = -1
    try:
        p = Params(Name, Value, Ensure)
    except Exception, e:
        Print(
            'ERROR - Unable to initialize nxNopProvider. ' +
            str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxNopProvider. ' + str(e))
        return [retval]

    ShowMof('Set', Name, Value, Ensure)

    if p.Ensure == 'present':
        if p.Value == 'fail':
            Print(
                'ERROR - Failing Set(present) due to Value = "fail". ' + str(e), file=sys.stderr)
            LG().Log(
                'ERROR', 'ERROR - Failing Set(present) due to Value = "fail".' + str(e))
        else:
            retval = 0
    else:
        if p.Value == 'fail':
            Print(
                'ERROR - Failing Set(absent) due to Value = "fail" ' + str(e), file=sys.stderr)
            LG().Log(
                'ERROR', 'ERROR - Failing Set(absent) due to Value = "fail". ' + str(e))
        else:
            retval = 0

    return [retval]

def Test(Name, Value, Ensure):
    retval = -1
    try:
        p = Params(Name, Value, Ensure, Path)
    except Exception, e:
        Print(
            'ERROR - Unable to initialize nxNopProvider. ' +
            str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxNopProvider. ' + str(e))
        return [retval]

    ShowMof('Test', Name, Value, Ensure)

    if p.Value == 'pass':
        retval = 0

    return [retval]

def Get(Name, Value, Ensure, Path):
    retval = -1
    try:
        p = Params(Name, Value, Ensure)
    except Exception, e:
        Print(
            'ERROR - Unable to initialize nxNopProvider. ' +
            str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxNopProvider. ' + str(e))
        return [retval, Name, Value, Ensure]

    ShowMof('Get', Name, Value, Ensure)

    return [retval, Name, Value, Ensure]
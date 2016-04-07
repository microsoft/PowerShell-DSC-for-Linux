#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved. 
#============================================================================
import os
import sys
import imp
import codecs
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

# [ClassVersion("1.0.0"), Description("The configuration provider for inventory collection."), FriendlyName("nxInventoryMOF")]
# class MSFT_nxInventoryMOFResource:OMI_BaseResource
# {
#   [Key] string DestinationPath;
#   [Write] string MOFContents;

# };

def init_vars(DestinationPath, MOFContents):
    if DestinationPath is not None and len(DestinationPath) > 0:
        DestinationPath = DestinationPath.encode('ascii','ignore')
    else:
        #should not happen - complain to log and return False
        return False
    if MOFContents is not None and len(MOFContents) > 0:
        MOFContents = MOFContents.encode('ascii','ignore')
    return True

def Set_Marshall(DestinationPath, MOFContents):
    if not init_vars(DestinationPath, MOFContents):
        return [-1]
    return Set(DestinationPath, MOFContents)

def Test_Marshall(DestinationPath, MOFContents):
    if not init_vars(DestinationPath, MOFContents):
        return [-1]
    return Test(DestinationPath, MOFContents)

def Get_Marshall(DestinationPath, MOFContents):
    arg_names = list(locals().keys())
    init_vars(DestinationPath, MOFContents)
    MOFContents = Get(DestinationPath, MOFContents)
    MOFContents = protocol.MI_String(MOFContents)
    DestinationPath = protocol.MI_String(DestinationPath)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return 0, retd
            
def Set(DestinationPath, MOFContents):
    if Test(DestinationPath, MOFContents) == [0]:
        return [0]
    return UpdateInventoryMOF(DestinationPath, MOFContents)

def Test(DestinationPath, MOFContents):
    oldmof=ReadInventoryMOF(DestinationPath)
    same = [-1]
    if MOFContents == oldmof:
        same = [0]
    return same

def Get(DestinationPath, MOFContents):
    MOFContents = ReadInventoryMOF(DestinationPath)
    return MOFContents

def ReadInventoryMOF(DestinationPath):
    mof=''
    fname = os.path.join(DestinationPath,'Inventory.mof')
    F, error = opened_w_error(fname, 'r')
    if error:
        Print("Exception opening file " + fname + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + fname + " Error: " + str(error))
    else:
        mof=F.read()
        F.close()
    return mof.encode('ascii','ignore')

def UpdateInventoryMOF(DestinationPath, MOFContents):
    fname = os.path.join(DestinationPath,'Inventory.mof')
    F, error = opened_w_error(fname, 'w')
    if error:
        Print("Exception opening file " + fname + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + fname + " Error: " + str(error))
        return [-1]
    F.write(MOFContents)
    F.close()
    return [0]

def opened_w_error(filename, mode="r"):
    """
    This context ensures the file is closed.
    """
    try:
        f = codecs.open(filename, encoding='utf8', mode=mode)
    except IOError, err:
        return None, err
    return f, None

def Print(s, file=sys.stdout):
    file.write(s + '\n')

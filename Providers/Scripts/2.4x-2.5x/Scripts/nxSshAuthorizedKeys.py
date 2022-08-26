#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python
# ===================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ===================================

import os
import sys
import pwd
import re
import time
import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

# [Key] string KeyComment;
# [write,ValueMap{"Present", "Absent"},Values{"Present", "Absent"}] string Ensure;
# [write] string UserName;
# [write] string Key;

global show_mof
show_mof = False


def init_vars(KeyComment, Ensure, UserName, Key):
    if Ensure is not None and Ensure != '':
        Ensure = Ensure.encode('ascii', 'ignore').lower()
    else:
        Ensure = 'present'
    if KeyComment is not None:
        KeyComment = KeyComment.encode('ascii', 'ignore')
    else:
        KeyComment = ''
    if UserName is not None:
        UserName = UserName.encode('ascii', 'ignore')
    else:
        UserName = ''
    if Key is not None:
        Key = Key
    else:
        Key = ''
    return KeyComment, Ensure, UserName, Key


def Set_Marshall(KeyComment, Ensure, UserName, Key):
    (KeyComment, Ensure, UserName, Key) = init_vars(
        KeyComment, Ensure, UserName, Key)
    retval = Set(KeyComment, Ensure, UserName, Key)
    return retval


def Test_Marshall(KeyComment, Ensure, UserName, Key):
    (KeyComment, Ensure, UserName, Key) = init_vars(
        KeyComment, Ensure, UserName, Key)
    retval = Test(KeyComment, Ensure, UserName, Key)
    return retval


def Get_Marshall(KeyComment, Ensure, UserName, Key):
    arg_names = list(locals().keys())
    (KeyComment, Ensure, UserName, Key) = init_vars(
        KeyComment, Ensure, UserName, Key)
    retval = 0
    retval, KeyComment, Ensure, UserName, Key = Get(
        KeyComment, Ensure, UserName, Key)
    KeyComment = protocol.MI_String(KeyComment)
    Ensure = protocol.MI_String(Ensure)
    UserName = protocol.MI_String(UserName)
    Key = protocol.MI_String(Key)

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd


############################################################
# Begin user defined DSC functions
############################################################

class Params:

    def __init__(self, KeyComment, Ensure, UserName, Key):

        if not ("present" in Ensure or "absent" in Ensure):
            Print(
                'ERROR: Param Ensure must be "Present" or "Absent".', file=sys.stderr)
            LG().Log(
                'ERROR', 'ERROR: Param Ensure must be "Present" or "Absent".')
            raise Exception('BadParameter')
        self.Ensure = Ensure

        if len(KeyComment) < 1:
            Print(
                'ERROR: Mandatory Param KeyComment missing.', file=sys.stderr)
            LG().Log('ERROR', 'ERROR: Mandatory Param KeyComment missing.')
            raise Exception('BadParameter')
        self.KeyComment = KeyComment

        if len(UserName) < 1:
            Print('ERROR: Mandatory Param UserName missing.', file=sys.stderr)
            LG().Log('ERROR', 'ERROR: Mandatory Param UserName missing.')
            raise Exception('BadParameter')
        pw_st = None
        try:
            pw_st = pwd.getpwnam(UserName)
        except KeyError:
            Print('ERROR:  UserName:' + UserName +
                  ' does not exist.', file=sys.stderr)
            LG().Log(
                'ERROR', 'ERROR:  UserName:' + UserName + ' does not exist.')
            raise Exception('BadParameter')

        self.UserName = UserName
        self.UserHome = pw_st.pw_dir
        self.Key = Key  # this can be empty for delete


def Set(KeyComment, Ensure, UserName, Key):
    retval = -1
    ShowMof('SET', KeyComment, Ensure, UserName, Key)
    try:
        p = Params(KeyComment, Ensure, UserName, Key)
    except Exception, e:
        Print('ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ' +
              str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ' + str(e))
        return [retval]
    if p.Ensure == 'present':
        if AddKey(p) is None:
            retval = 0
    if p.Ensure == 'absent':
        if DelKey(p) is None:
            retval = 0
    return [retval]


def Test(KeyComment, Ensure, UserName, Key):
    retval = -1
    ShowMof('TEST', KeyComment, Ensure, UserName, Key)
    try:
        p = Params(KeyComment, Ensure, UserName, Key)
    except Exception, e:
        Print('ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ' +
              str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ' + str(e))
        return [retval]
    found, error = FindKey(p)
    if found and p.Ensure == 'present':
        retval = 0
    if not found and p.Ensure == 'absent':
        retval = 0

    return [retval]


def Get(KeyComment, Ensure, UserName, Key):
    retval = 0
    ShowMof('GET', KeyComment, Ensure, UserName, Key)
    try:
        p = Params(KeyComment, Ensure, UserName, Key)
    except Exception, e:
        Print('ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ' +
              str(e), file=sys.stderr)
        LG().Log(
            'ERROR', 'ERROR - Unable to initialize nxSshAuthorizedKeysProvider.  ' + str(e))
        return [retval, KeyComment, Ensure, UserName, Key]
    found, error = FindKey(p)
    if found:
        p.Ensure == 'present'
    else:
        p.Ensure == 'absent'
    return [retval, KeyComment, Ensure, UserName, Key]


def SetShowMof(a):
    global show_mof
    show_mof = a


def ShowMof(op, KeyComment, Ensure, UserName, Key):
    if not show_mof:
        return
    mof = ''
    mof += op + ' nxSshAuthorizedKeys MyKey \n'
    mof += '{\n'
    mof += '    KeyComment = "' + KeyComment + '"\n'
    mof += '    Ensure = "' + Ensure + '"\n'
    mof += '    UserName = "' + UserName + '"\n'
    mof += '    Key = "' + Key + '"\n'
    mof += '}\n'
    f = open('./test_mofs.log', 'a')
    Print(mof, file=f)
    LG().Log('INFO', mof)
    f.close()


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


def Log(file_path, message):
    if len(file_path) < 1 or len(message) < 1:
        return
    t = time.localtime()
    t = "%04u/%02u/%02u %02u:%02u:%02u " % (
        t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
    lines = re.sub(re.compile(r'^(.)', re.MULTILINE), t + r'\1', message)
    F, error = opened_w_error(file_path, 'a')
    if error:
        Print("Exception opening logfile " + file_path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening logfile " + file_path + " Error: " + str(error))
    else:
        F.write(lines + "\n")
    F.close()


def AddKey(p):
    d = p.UserHome + '/.ssh'
    path = d + '/authorized_keys'
    if os.path.isdir(d) is False:
        try:
            os.makedirs(d)
            os.chmod(d, 0700)
            os.chown(
                d, pwd.getpwnam(p.UserName).pw_uid, pwd.getpwnam(p.UserName).pw_gid)
        except IOError, error:
            Print("Exception creating directory " + d + " Error: " + str(error), file=sys.stderr)
            LG().Log('ERROR', "Exception creating directory " + d + " Error: " + str(error))
            return error
        except OSError, error:
            Print("Exception opening directory " + d + " Error: " + str(error), file=sys.stderr)
            LG().Log('ERROR', "Exception opening directory " + d + " Error: " + str(error))
            return error
    if os.path.exists(path) is False:
        os.system('echo > ' + path)

    error = None
    F, error = opened_w_error(path, 'rb+')
    if error:
        Print("Exception opening file " + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + path + " Error: " + str(error))

        return error
    flag = 'not found'
    n = ''
    KC = '#' + p.KeyComment
    for l in F.readlines():
        if flag == 'found':
            n += p.Key + '\n'
            flag = 'done'
        elif KC == l[:len(l) - 1]:
            flag = 'found'
            n += l
        else:
            n += l
    if flag == 'not found':
        n += KC + '\n' + p.Key + '\n'
    F.close()
    F, error = opened_w_error(path, 'wb+')
    F.write(n)
    F.close()
    os.chmod(path, 0700)
    os.chown(path, pwd.getpwnam(p.UserName).pw_uid,
             pwd.getpwnam(p.UserName).pw_gid)
    return error


def DelKey(p):
    path = p.UserHome + '/.ssh/authorized_keys'
    error = None
    found = False
    if not os.path.isfile(path):
        return error
    F, error = opened_w_error(path, 'rb+')
    if error:
        Print("Exception opening file " + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + path + " Error: " + str(error))
        return error
    n = ''
    KC = '#' + p.KeyComment
    for l in F.readlines():
        if found is True:
            found = False  # skip this line
            continue
        if KC == l[:len(l) - 1]:
            # set this true to skip the next line which is the key
            found = True
            continue
        n += l
    F.close()
    F, error = opened_w_error(path, 'wb+')
    F.write(n)
    F.close()
    return error


def FindKey(p):
    path = p.UserHome + '/.ssh/authorized_keys'
    error = None
    found = False
    if not os.path.isfile(path):
        return found, error
    F, error = opened_w_error(path, 'rb')
    if error:
        Print("Exception opening file " + path + " Error: " + str(error), file=sys.stderr)
        LG().Log('ERROR', "Exception opening file " + path + " Error: " + str(error))
        return found, error
    KC = '#' + p.KeyComment
    for l in F.readlines():
        if found is True:
            # return true of the key is not provided
            if len(p.Key) is 0 or p.Key == l[:len(l) - 1]:
                break
            else:
                found = False
                break
        if KC == l[:len(l) - 1]:
            found = True
    F.close()
    return found, error

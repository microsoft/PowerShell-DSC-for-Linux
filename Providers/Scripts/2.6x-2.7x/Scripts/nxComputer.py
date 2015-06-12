# !/usr/bin/env python
# ==================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# See license.txt for license information.
# ==================================

from __future__ import print_function
from __future__ import with_statement
from contextlib import contextmanager

import os
import sys
import time
import subprocess
import re
import imp
protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog
try:
    import hashlib
    md5const = hashlib.md5
except ImportError:
    import md5
    md5const = md5.md5

# [ClassVersion("1.0.0"), FriendlyName("nxComputer")]
# class MSFT_nxComputerResource : OMI_BaseResource
# {
#     [key] string Name;
#     [Write] string DNSDomainName;
#     [Write] string TimeZoneName;
#     [Write] string AlternateTimeZoneName;
# };


def init_vars(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    if Name is None:
        Name = ''
    if DNSDomainName is None:
        DNSDomainName = ''
    if TimeZoneName is None:
        TimeZoneName = ''
    if AlternateTimeZoneName is None:
        AlternateTimeZoneName = ''
    return Name.encode('ascii', 'ignore'), DNSDomainName.encode('ascii', 'ignore'), \
        TimeZoneName.encode('ascii', 'ignore'), AlternateTimeZoneName.encode('ascii', 'ignore')


def Set_Marshall(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    (Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName) = init_vars(
        Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
    retval = Set(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
    if retval is False:
        retval = [-1]
    else:
        retval = [0]
    return retval


def Test_Marshall(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    (Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName) = init_vars(
        Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
    retval = Test(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
    if retval is False:
        retval = [-1]
    else:
        retval = [0]
    return retval


def Get_Marshall(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    arg_names = list(locals().keys())
    (Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName) = init_vars(
        Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
    retval = 0
    (Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName) = Get(
        Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName)
    Name = protocol.MI_String(Name)
    DNSDomainName = protocol.MI_String(DNSDomainName)
    TimeZoneName = protocol.MI_String(TimeZoneName)
    AlternateTimeZoneName = protocol.MI_String(AlternateTimeZoneName)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

############################################################
# Begin user defined DSC functions
############################################################


def RunGetOutput(cmd, no_output, chk_err=True):
    """
    Wrapper for subprocess.check_output.
    Execute 'cmd'.  Returns return code and STDOUT, trapping expected exceptions.
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
            raise subprocess.CalledProcessError(retcode, cmd, output=output)
        return output

    # Exception classes used by this module.
    class CalledProcessError(Exception):

        def __init__(self, returncode, cmd, output=None):
            self.returncode = returncode
            self.cmd = cmd
            self.output = output

        def __str__(self):
            return "Command '%s' returned non-zero exit status %d" % (self.cmd, self.returncode)

    subprocess.check_output = check_output
    subprocess.CalledProcessError = CalledProcessError
    try:
        output = subprocess.check_output(
            no_output, cmd, stderr=subprocess.STDOUT, shell=True)
    except subprocess.CalledProcessError, e:
        if chk_err:
            print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stdout)
            LG().Log('ERROR', 'CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stdout)
            print(
                'CalledProcessError.  Command string was ' + e.cmd, file=sys.stdout)
            LG().Log('ERROR', 
                'CalledProcessError.  Command string was ' + e.cmd, file=sys.stdout)
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


@contextmanager
def opened_w_error(filename, mode="rb"):
    """
    This context ensures the file is closed.
    """
    try:
        f = open(filename, mode)
    except IOError, err:
        yield None, err
    else:
        try:
            yield f, None
        finally:
            f.close()


def Set(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    if len(Name) > 0 :
        if len(DNSDomainName) > 0 :
            if GetHostname() != Name + '.' + DNSDomainName and SetHostname(Name, DNSDomainName) is False:
                return False
        else :
            if '.' in GetHostname() and GetHostname().split('.')[0] != Name and SetHostname(Name, DNSDomainName) is False:
                return False
            else :
                if GetHostname() != Name and SetHostname(Name, DNSDomainName) is False:
                    return False
    if len(TimeZoneName) > 0:
        if SetTimezone(TimeZoneName) is True:
            return True
        elif len(AlternateTimeZoneName) is 0:
            return False
    if len(AlternateTimeZoneName) > 0 and SetTimezone(AlternateTimeZoneName) is False:
        return False
    return True


def Test(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    if len(Name) > 0 :
        if len(DNSDomainName) > 0 :
            if GetHostname() != Name + '.' + DNSDomainName:
                return False
        else :
            if '.' in GetHostname() and GetHostname().split('.')[0] != Name:
                return False
            else :
                if GetHostname() != Name:
                    return False
    if len(TimeZoneName) > 0:
        if TestTimezone(TimeZoneName) is True:
            return True
        elif len(AlternateTimeZoneName) is 0:
            return False
    if len(AlternateTimeZoneName) > 0 and TestTimezone(AlternateTimeZoneName) is False:
        return False
    return True


def Get(Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName):
    fqdn = GetHostname()
    if '.' in fqdn:
        Name = fqdn.split('.')[0]
        DNSDomainName = fqdn.replace(Name + '.', '')
    else:
        Name = fqdn
        DNSDomainName = ''
    
    if not TestTimezone(TimeZoneName):
        TimeZoneName = ''
    if len(AlternateTimeZoneName) > 0 and not TestTimezone(AlternateTimeZoneName):
        AlternateTimeZoneName = ''
    return Name, DNSDomainName, TimeZoneName, AlternateTimeZoneName


def BuildTZList():
    tzlist = list()
    for top, dirs, files in os.walk('/usr/share/zoneinfo'):
        for f in files:
            h = md5const()
            n = top + '/' + f
            with opened_w_error(n, 'r') as (F, error):
                if error:
                    print("Exception opening file " + n + " Error Code: " + str(error.errno) +
                          " Error: " + error.message + error.strerror, file=sys.stderr)
                    LG().Log('ERROR', "Exception opening file " + n + " Error Code: " + str(error.errno) +
                          " Error: " + error.message + error.strerror)
                    continue
                t = F.read()
            h.update(t)
            tzlist.append((n[20:], h.hexdigest()))
    return tzlist

# Example TZ 'AEST-10:55:01AEDT-11:55:10,M10.5.0/11:55:01,M3.5.0/11:55:10'

timezone_regex = r"""
(?P<std_name>.*?ST)                                  # std name is required
(?P<std_hours>[-,+]?[0-1][0-9]|[-,+]?[2][0-4])       # std offset hours is required 
(?P<std_minutes>:[0-5][0-9])?                        # std offset minutes is optional 
(?P<std_seconds>:[0-5][0-9])?                        # std offset seconds is optional 
(?P<dst_name>.*?DT)?                                 # dst name is optional
(?P<dst_hours>[-,+]?[0-1][0-9]|[-,+]?[2][0-4])?      # dst offset hours is optional
(?P<dst_minutes>:[0-5][0-9])?                        # dst offset minutes is optional
(?P<dst_seconds>:[0-5][0-9])?                        # dst offset seconds is optional

(?P<dst_start_day_of_jullian_year>,J[1-2][0-9][0-9]|
,J[3][0-5][0-9]|,J[3][6][0-5]|,J[1-9][0-9]|,J[0-9])? # dst offset start_day_of_year is optional
(?P<dst_start_day_of_year>,[1-2][0-9][0-9]|
,[3][0-5][0-9]|,[3][6][0-5]|,[1-9][0-9]|,[0-9])?     # dst offset start_day_of_year is optional
(?P<dst_start_month>,M[1][0-2]|M[1-9])?              # dst offset start_month is optional
(?P<dst_start_week>[.][1-5])?                        # dst offset start_week is optional
(?P<dst_start_day>[.][0-6])?                         # dst offset start_day is optional
(?P<dst_start_hours>[/][0-1][0-9]|[/][2][0-4])?      # dst offset hours is optional
(?P<dst_start_minutes>:[0-5][0-9])?                  # dst offset minutes is optional
(?P<dst_start_seconds>:[0-5][0-9])?                  # dst offset seconds is optional

(?P<dst_end_day_of_jullian_year>,J[1-2][0-9][0-9]|
,J[3][0-5][0-9]|,J[3][6][0-5]|,J[1-9][0-9]|,J[0-9])? # dst offset end_day_of_year is optional
(?P<dst_end_day_of_year>,[1-2][0-9][0-9]|
,[3][0-5][0-9]|,[3][6][0-5]|,[1-9][0-9]|,[0-9])?     # dst offset end_day_of_year is optional
(?P<dst_end_month>,M[1][0-2]|,M[1-9])?               # dst offset end_month is optional
(?P<dst_end_week>[.][1-5])?                          # dst offset end_week is optional
(?P<dst_end_day>[.][0-6])?                           # dst offset end_day is optional
(?P<dst_end_hours>[/][0-1][0-9]|[/][2][0-4])?        # dst offset hours is optional
(?P<dst_end_minutes>:[0-5][0-9])?                    # dst offset minutes is optional
(?P<dst_end_seconds>:[0-5][0-9])?                    # dst offset seconds is optional
"""
# Use re to filter out invalid syntax and number ranges.
# Keep the delimiters.


def ValidateTimeZoneString(TimeZone):
    safe_tz = ''
    tzstring = TimeZone.strip()
    m = re.search(timezone_regex, tzstring, re.VERBOSE)
    if m is None:
        print('Unable to validate TimeZone', file=sys.stderr)
        LG().Log('ERROR', 'Unable to validate TimeZone')
        return safe_tz
    if m.group('std_name') is None or m.group('std_hours') is None:
        return safe_tz
    # return only what matched
    for g in m.groups():
        if g is not None:
            safe_tz += g
    return safe_tz


def ExtractSimpleNameFromTimeZoneString(TimeZone):
    simple_tz = ''
    tzstring = TimeZone.strip()
    m = re.search(timezone_regex, tzstring, re.VERBOSE)
    if m is None:
        print('Unable to parse TimeZone', file=sys.stderr)
        LG().Log('ERROR', 'Unable to parse TimeZone')
        return simple_tz
    if m.group('std_name') is None or m.group('std_hours') is None:
        return simple_tz
    simple_tz += m.group('std_name')
    simple_tz += m.group('std_hours')
    if m.group('dst_name') is not None:
        simple_tz += m.group('dst_name')
    return simple_tz


def ValidateTimezone(TimeZone):
    # Is it a region file path?
    l = BuildTZList()
    for n, h in l:
        if TimeZone == n:
            return TimeZone,TimeZone
    # Is it a TZ string?
    safe_tz = ValidateTimeZoneString(TimeZone)
    tzfile = ExtractSimpleNameFromTimeZoneString(TimeZone)
    return safe_tz, tzfile


def SetTimezone(TimeZone):
    zone, tzfile_name = ValidateTimezone(TimeZone)
    if len(zone) < 1:
        return False
    os.environ['TZ'] = zone
    time.tzset()
    SetLocaltimeTZFile(tzfile_name)
    print('Time is now ' + time.strftime('%X %x %Z') +
        ' time zone is ' + repr(time.tzname), file=sys.stderr)
    LG().Log('INFO', 'Time is now ' + time.strftime('%X %x %Z') +
        ' time zone is ' + repr(time.tzname))
    return True

def SetLocaltimeTZFile(tzfile):
    l = BuildTZList()
    for n, h in l:
        if tzfile == n:
            code=os.system('cp /usr/share/zoneinfo/' + n + ' /etc/localtime')
            if code:
                print('Error: cp /usr/share/zoneinfo/' + n + ' /etc/localtime Failed', file=sys.stderr)
            return
    print('Error: No match for ' + tzfile + ' under /usr/share/zoneinfo.', file=sys.stderr)
    return
                      
def SetHostname(Name, DNSDomainName):
    fqdn = Name + '.' + DNSDomainName
    with opened_w_error('/etc/hosts', 'r') as (F, error):
        if error:
            print("Exception opening file /etc/hosts Error Code: " + str(error.errno) +
                  " Error: " + error.message + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file /etc/hosts Error Code: " + str(error.errno) +
                  " Error: " + error.message + error.strerror)
            return False
        text=F.read()

    # we must ensure that our line is the first in the list or 'hostname --fqdn' may fail
    # remove ::1 and 127.0.0.1
    srch=r'(^(/s)?((.*?:)|(.*?\.)).*?\n)'
    srch=re.compile(r'(^(/s)?((::1)|(127\.0\.0\.1)).*?\n)',re.M|re.S)
    text=srch.sub('',text)
    # if other entries are here - put our line in front of the first of that type
    # otherwise put the ipv4 at the top and ipv6 at the bottom.
    srch=re.compile(r'(^([0-9]+.*?\.).*?\n)',re.M)
    if len(srch.findall(text)) > 0:
        sub=r'127.0.0.1     ' + fqdn + '    ' + Name + r'\n\1'
        text=srch.sub(sub,text,1)
    else :
        text='127.0.0.1     ' + fqdn + '    ' + Name + '\n' + text
    srch=re.compile(r'(^([0-9,a-f,:]+.*?:).*?\n)',re.M)
    if len(srch.findall(text)) > 0:
        sub=r'::1     ' + fqdn + '    ' + Name + r'\n\1'
        text=srch.sub(sub,text,1)
    else:
        text+='::1     ' + fqdn + '    ' + Name + '\n'
    with opened_w_error('/etc/hosts', 'w') as (F, error):
        if error:
            print("Exception opening file /etc/hosts Error Code: " + str(error.errno) +
                  " Error: " + error.message + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file /etc/hosts Error Code: " + str(error.errno) +
                  " Error: " + error.message + error.strerror)
            return False
        F.write(text)
    with opened_w_error('/etc/hostname', 'w') as (F, error):
        if error:
            print("Exception opening file /etc/hostname Error Code: " + str(error.errno) +
                  " Error: " + error.message + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file /etc/hostname Error Code: " + str(error.errno) +
                  " Error: " + error.message + error.strerror)
            return False
        F.write(Name + '\n')
    os.system('hostname ' + Name)
    return True


def GetHostname():
    out = ''
    code, out = RunGetOutput('hostname --fqdn', False, False)
    return out.strip('\n')


def GetCurrentTimezones():
    zones = list()
    hash = md5const()
    with opened_w_error('/etc/localtime', 'r') as (F, error):
        if error:
            print("Exception opening file /etc/localtime Error Code: " +
                  str(error.errno) + " Error: " + error.message + error.strerror, file=sys.stderr)
            LG().Log('ERROR', "Exception opening file /etc/localtime Error Code: " +
                  str(error.errno) + " Error: " + error.message + error.strerror)
            return zones
        t = F.read()
    hash.update(t)
    md = hash.hexdigest()
    l = BuildTZList()
    for n, h in l:
        if md == h:
            zones.append((n, h))
    return zones


def TestTimezone(TimeZone):
    zones = GetCurrentTimezones()
    for n, h in zones:
        if TimeZone == n:
            return True
    tz = ValidateTimeZoneString(TimeZone)
    tz = ExtractSimpleNameFromTimeZoneString(tz)
    for n, h in zones:
        if tz == n:
            return True
    return False

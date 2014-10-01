#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import time
import socket
import sys
import nxFile
import struct
######################################

#class Datetime:
#    def __init__ (self, tm):
#        self.tm = tm
    
def write_uchar (fd, val):
    buf = struct.pack ('B', val)
    fd.send (buf)

    
def write_int (fd, val):
    #print '<write_int>'
    #print '  val: {0}'.format (val)
    buf = struct.pack ('@i', val)
    fd.send (buf)
    #print '</write_val>'


def write_string (fd, st):
    #print '<write_string>'
    #print '  st: \"{0}\"'.format (st)
    buf = struct.pack ('@i', len (st)) + st
    #if 0 < len (st):
    #    buf += st
    fd.send (buf)
    #print '</write_string>'


def write_bool (fd, val):
    #print '<write_bool> {0}'.format (val)
    if val:
        write_uchar (fd, 1)
    else:
        write_uchar (fd, 0)
    #print '</write_bool>'
                               
        
def read_uchar (s):
    #print '<read_uchar>'
    buf = s.recv (1)
    val = struct.unpack ('B',buf)[0]
    #print '  val: {0}'.format (int (val))
    #print '</read_uchar>'
    return val


def read_bool (s):
    #print '<read_bool>'
    val = False
    temp = read_uchar (s)
    if 0 != temp:
        val = True
        #print '  val: True'
    #else:
    #    print '  val: False'
    #print '</read_bool>'
    return val


def read_int (s):
    #print '<read_int>'
    buf = s.recv (4)
    val = struct.unpack ('@i',buf)[0]
    #print '  val: {0}'.format (val)
    #print '</read_int>'
    return val


def read_string (s):
    #print '<read_string>'
    len = read_int (s)
    #print '  len: {0}'.format (len)
    str = ''
    if 0 < len:
        buf = s.recv (len)
        str = buf.decode ('utf8')
    #print '  str: "{0}"'.format (str)
    #print '</read_string>'
    return str


def read_value (s):
    print '<read_value>'
    arg_name = read_string (s)
    print '  arg_name: "{0}"'.format (arg_name)
    arg_type = read_uchar (s)
    print '  arg_type: {0}'.format (int (arg_type))
    argv =''
    if 0 == (64 & arg_type): # MI_NULL_FLAG = 64
        if 0 == arg_type: # MI_Boolean = 0
            argv = read_bool (s)
            print '  argv: {0}'.format (argv)
        elif 13 == arg_type: # MI_String = 13
            argv = read_string (s)
            print '  argv: "{0}"'.format (argv)
        else:
            print '  unhandled arg type!'
    else: # MI_NULL_FLAG = 64
        argv = None
        print '  argv: None'
    print '</read_value>'
    return (arg_name, argv)


def read_values (s):
    print '<read_values>'
    d = dict ()
    argc = read_int (s)
    print '  argc: {0}'.format (argc)
    for i in range (argc):
        #print 'val #{0}'.format (i)
        arg = read_value (s)
        d[arg[0]] = arg[1]
    print '</read_values>'
    return d


def read_request (s):
    #print '<read_request>'
    op_type = read_uchar (s)
    #print '  op_type: {0}'.format (int (op_type))
    op_name = read_string (s)
    #print '  op_name: "{0}"'.format (op_name)
    d = read_values (s)
    #print '</read_request>'
    return (op_type, op_name, d)


def write_arg (s, arg):
    #print '<write_arg>'
    if type (arg) is bool:
        write_uchar (s, 0) # MI_Boolean = 0
        write_bool (s, arg)
    #elif type (arg) is class:
    #    write_uchar (s, 12) # MI_Datetime = 12
    #    write_int (s, arg.tm)
    elif type (arg) is str:
        write_uchar (s, 13) # MI_String = 13
        write_string (s, arg)
    else:
        print 'write_arg called for undefined type!'
    #print '</write_arg>'


def write_dict (s, d):
    #print '<write_dict>'
    write_int (s, len (d))
    for key, value in d.iteritems():
        write_string (s, key)
        write_arg (s, value)
    #print '</write_dict>'


def write_args (s, args):
    #print '<write_args>'
    if type (args) is dict:
        write_dict (s, args)
    else:
        print 'write_args - was expecting dictionary for args!'
    #print '</write_args>'


def write_success (s, args=None):
    print '<write_success>'
    write_int (s, 0)
    if args is not None:
        write_args (s, args)
    print '</write_success>'


def write_failed (s, fail_code, text=''):
    print '<write_failed>'
    write_int (s, fail_code)
    write_string (s, text)
    print '</write_failed>'
    

def handle_request (s, req):
    print '<handle_request>'
    op = ''
    if 0 == req[0]:
        op = 'Test'
    elif 1 == req[0]:
        op = 'Set'
    elif 2 == req[0]:
        op = 'Get'
    print '  {0} : {1}'.format (op, req[1])
    error_text = ''
    ret = []
    rval = 0
    if 0 <= req[0] and 2 >= req[0]:
        if 'nxFile' == req[1]:
            if 2 == req[0]:
                # Get
                ret = nxFile.Get_Marshall (
                    req[2]['DestinationPath'] if req[2]['DestinationPath'] is not None else '',
                    req[2]['SourcePath'] if req[2]['SourcePath'] is not None else '',
                    req[2]['Ensure'] if req[2]['Ensure'] is not None else '',
                    req[2]['Type'] if req[2]['Type'] is not None else '',
                    str (req[2]['Force']) if req[2]['Force'] is not None else '',
                    req[2]['Contents'] if req[2]['Contents'] is not None else '',
                    req[2]['Checksum'] if req[2]['Checksum'] is not None else '',
                    str (req[2]['Recurse']) if req[2]['Recurse'] is not None else '',
                    req[2]['Links'] if req[2]['Links'] is not None else '',
                    req[2]['Owner'] if req[2]['Owner'] is not None else '',
                    req[2]['Group'] if req[2]['Group'] is not None else '',
                    req[2]['Mode'] if req[2]['Mode'] is not None else '')
                rval = ret[0]
                if 0 == rval:
                    args = dict ()
                    args['DestinationPath'] = ret[1]
                    args['SourcePath'] = ret[2]
                    args['Ensure'] = ret[3]
                    args['Type']= ret[4]
                    if ret[5] == 'True':
                        args['Force'] = True
                    else:
                        args['Force'] = False
                    args['Contents'] = ret[6]
                    args['Checksum'] = ret[7]
                    if ret[8] == 'True':
                        args['Recurse'] = True
                    else:
                        args['Recurse'] = False
                    args['Links'] = ret[9]
                    args['Owner'] = ret[10]
                    args['Group'] = ret[11]
                    args['Mode'] = ret[12]
#                    print 'ModifiedDate: {0}'.format (ret[13])
#                    args['ModifiedDate'] = Datetime (int (ret[13]))
                    write_success (s, args)
                else:
                    # Fail
                    error_text = 'Test failed'
            else:
                if 0 == req[0]:
                    # Test
                    ret = nxFile.Test_Marshall (
                        req[2]['DestinationPath'] if req[2]['DestinationPath'] is not None else '',
                        req[2]['SourcePath'] if req[2]['SourcePath'] is not None else '',
                        req[2]['Ensure'] if req[2]['Ensure'] is not None else '',
                        req[2]['Type'] if req[2]['Type'] is not None else '',
                        str (req[2]['Force']) if req[2]['Force'] is not None else '',
                        req[2]['Contents'] if req[2]['Contents'] is not None else '',
                        req[2]['Checksum'] if req[2]['Checksum'] is not None else '',
                        str (req[2]['Recurse']) if req[2]['Recurse'] is not None else '',
                        req[2]['Links'] if req[2]['Links'] is not None else '',
                        req[2]['Owner'] if req[2]['Owner'] is not None else '',
                        req[2]['Group'] if req[2]['Group'] is not None else '',
                        req[2]['Mode'] if req[2]['Mode'] is not None else '')
                else:
                    # Set
                    ret = nxFile.Set_Marshall (
                        req[2]['DestinationPath'] if req[2]['DestinationPath'] is not None else '',
                        req[2]['SourcePath'] if req[2]['SourcePath'] is not None else '',
                        req[2]['Ensure'] if req[2]['Ensure'] is not None else '',
                        req[2]['Type'] if req[2]['Type'] is not None else '',
                        str (req[2]['Force']) if req[2]['Force'] is not None else '',
                        req[2]['Contents'] if req[2]['Contents'] is not None else '',
                        req[2]['Checksum'] if req[2]['Checksum'] is not None else '',
                        str (req[2]['Recurse']) if req[2]['Recurse'] is not None else '',
                        req[2]['Links'] if req[2]['Links'] is not None else '',
                        req[2]['Owner'] if req[2]['Owner'] is not None else '',
                        req[2]['Group'] if req[2]['Group'] is not None else '',
                        req[2]['Mode'] if req[2]['Mode'] is not None else '')
                rval = ret[0]
                if 0 == rval:
                    write_success (s)
        else:
            # Error
            error_text = 'Received a request for an unexpected operation!'
    else:
        # fail
        error_text = 'Received a request for an invalid operation type!'
    if 0 != rval:
        if 0 < len (error_text):
            print error_text
        write_failed (s, rval, error_text)
    print '</handle_request>'


def main (argv=sys.argv):
    print 'socket: {0}'.format (argv[1])
    s = socket.fromfd (int (argv[1]), socket.AF_UNIX, socket.SOCK_STREAM)
    read = 1
    out = ''
    while 0 < read:
        try:
            req = read_request (s)
            handle_request (s, req)
        except socket.error:
            read = -1;
            print 'exception encountered'


if __name__ == '__main__':
    main ()


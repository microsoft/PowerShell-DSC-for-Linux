#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import time
import os
import sys
import socket
import struct


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
    #print '<read_value>'
    arg_name = read_string (s)
    #print '  arg_name: "{0}"'.format (arg_name)
    arg_type = read_uchar (s)
    #print '  arg_type: {0}'.format (int (arg_type))
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
    #print '<read_values>'
    d = dict ()
    argc = read_int (s)
    #print '  argc: {0}'.format (argc)
    for i in range (argc):
        #print 'val #{0}'.format (i)
        arg = read_value (s)
        d[arg[0]] = arg[1]
    #print '</read_values>'
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
    


def callMOF(m):
    sys.stderr.write('MOF='+repr(m))
    op=('Test','Set','Get')
    if not globals().has_key(m[1]):
        sys.stderr.write('Unable to find module: ' + md)
        return None
    the_module=globals()[m[1]]
    method_name=op[m[0]]+'_Marshall'
    if not the_module.__dict__.has_key(method_name):
        sys.stderr.write('Unable to find method: ' + method_name)
        return None
    sys.stderr.write('calling '+m[1]+'.'+method_name+repr(m[2]))
    ret = the_module.__dict__[method_name](**m[2])
    sys.stderr.write(repr(ret))
    return ret
    
def handle_request (s, req):
    sys.stderr.write('<handle_request>')
    #import pdb; pdb.set_trace()
    r = callMOF(req)
    if len(r) < 2 :
        ret=None
        rval=r[0]
    else:
        rval=r[0]
        ret=r[1]
        
    if rval != 0:
        write_failed(s,rval,'Error occurred processing '+repr(req))
        return
    else:
        write_success (s,ret)
    sys.stderr.write('</handle_request>')

def main (argv):
    s = socket.fromfd (int (argv[1]), socket.AF_UNIX, socket.SOCK_STREAM)
    read = 1
    out = ''
    while 0 < read:
        try:
            req = read_request (s)
            handle_request (s, req)
        except socket.error:
            read = -1;
            sys.stderr.write('exception encountered')

##############################
try:

    sys.stderr.write('socket: {0}'.format (sys.argv[1]))
    
    if 'OMI_HOME' in os.environ and len(os.environ['OMI_HOME']):
        omi_home=os.environ['OMI_HOME']
    else:
        omi_home='/opt/omi-1.0.8'
    if not os.path.isdir(omi_home):
        sys.stderr.write("omi home not found.  Please set OMI_HOME")
        sys.exit(1)
    pid_path=omi_home+'/var/run/python/'+repr(os.getuid())
    
    if not os.path.isdir(pid_path):
        os.system('mkdir -p ' + pid_path)
    pid_file=pid_path+'/dsc_python_client.pid'
    
    with open(pid_file,'w') as F: 
            F.write(str(os.getpid()) + "\n")
            F.flush()
            F.close()
    sys.stderr.write('using python version '+ sys.version) 
    sys.path.insert(0,'') # put the cwd in the path so we can find our module
    if sys.version < '2.6':
        sys.stderr.write('/lib/Scripts/2.4x-2.5x')
        os.chdir(omi_home+'/lib/Scripts/2.4x-2.5x')
    elif sys.version < '3':
        sys.stderr.write('/lib/Scripts/2.6x-2.7x')
        os.chdir(omi_home+'/lib/Scripts/2.6x-2.7x')
    else:
        sys.stderr.write('/lib/Scripts/3.x')
        os.chdir(omi_home+'/lib/Scripts/3.x')
    from Scripts import *
    
        
        
    if __name__ == '__main__':
            main (sys.argv)


except Exception, e:
    sys.stderr.write('Uncaught exception'+repr(e))
finally:
    sys.stderr.write('Exiting - closing socket' )
    (socket.fromfd(int (sys.argv[1]), socket.AF_UNIX, socket.SOCK_STREAM)).close()

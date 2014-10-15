#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import time
import os
import sys
import socket
import struct
import traceback
            


#class Datetime:
#    def __init__ (self, tm):
#        self.tm = tm
    
def write_uchar (fd, val):
    buf = struct.pack ('B', val)
    fd.send (buf)

    
def write_int (fd, val):
    #sys.stderr.write('<write_int>')
    #sys.stderr.write('  val: '+str(val))
    buf = struct.pack ('@i', val)
    fd.send (buf)
    #sys.stderr.write('</write_val>')


def write_string (fd, st):
    sys.stderr.write('<write_string>')
    #sys.stderr.write('  st: \"\"'+str(st))
    sys.stderr.write(repr(st))
    buf = struct.pack('@i', len (st))
    if type(buf) != str:
        buf+=bytes(st,'utf8')
    else:
        buf += st
    fd.send (buf)
    sys.stderr.write('</write_string>')


def write_bool (fd, val):
    #sys.stderr.write('<write_bool> '+str(val))
    if val:
        write_uchar (fd, 1)
    else:
        write_uchar (fd, 0)
    #sys.stderr.write('</write_bool>')
                               
        
def read_uchar (s):
    sys.stderr.write('<read_uchar>\n')
    buf = s.recv (1)
    if len(buf)<1:
        return None
    val = struct.unpack ('B',buf)[0]
    sys.stderr.write('  val: '+str(int (val)))
    sys.stderr.write('</read_uchar>\n')
    return val


def read_bool (s):
    #sys.stderr.write('<read_bool>')
    val = False
    temp = read_uchar (s)
    if temp == None:
        return None
    if 0 != temp:
        val = True
        #sys.stderr.write('  val: True')
    #else:
    #    sys.stderr.write('  val: False')
    #sys.stderr.write('</read_bool>')
    return val


def read_int (s):
    #sys.stderr.write('<read_int>')
    buf = s.recv (4)
    val = struct.unpack ('@i',buf)[0]
    #sys.stderr.write('  val: '+str(val))
    #sys.stderr.write('</read_int>')
    return val


def read_string (s):
    #sys.stderr.write('<read_string>')
    len = read_int (s)
    #sys.stderr.write('  len: '+str(len))
    str = ''
    if 0 < len:
        buf = s.recv (len)
        str = buf.decode ('utf8')
    #sys.stderr.write('  str: ""'+str(str))
    #sys.stderr.write('</read_string>')
    return str


def read_value (s):
    #sys.stderr.write('<read_value>')
    arg_n = read_string (s)
    # for python2.4x-2.5x unicode strings are illegal for **kwargs
    if sys.version < '2.6':
        arg_name=arg_n.encode('ascii','ignore')
    else:
        arg_name=arg_n
    #sys.stderr.write('  arg_name: ""'+str(arg_name))
    arg_type = read_uchar (s)
    if arg_type == None:
        return None
    #sys.stderr.write('  arg_type: '+str(int (arg_type)))
    argv =''
    if 0 == (64 & arg_type): # MI_NULL_FLAG = 64
        if 0 == arg_type: # MI_Boolean = 0
            argv = read_bool (s)
            sys.stderr.write('  argv: '+str(argv))
        elif 13 == arg_type: # MI_String = 13
            argv = read_string (s)
            sys.stderr.write('  argv: '+str(argv))
        else:
            sys.stderr.write('  unhandled arg type!')
    else: # MI_NULL_FLAG = 64
        argv = None
        sys.stderr.write('  argv: None')
    sys.stderr.write('</read_value>')
    return (arg_name, argv)


def read_values (s):
    #sys.stderr.write('<read_values>')
    d = dict ()
    argc = read_int (s)
    #sys.stderr.write('  argc: '+str(argc))
    for i in range (argc):
        #sys.stderr.write('val #'+str(i))
        arg = read_value (s)
        d[arg[0]] = arg[1]
    #sys.stderr.write('</read_values>')
    return d


def read_request (s):
    sys.stderr.write('<read_request>')
    op_type = read_uchar (s)
    if op_type == None:
        return None
    sys.stderr.write('  op_type: '+str(int (op_type)))
    op_name = read_string (s)
    sys.stderr.write('  op_name: ""'+str(op_name))
    d = read_values (s)
    sys.stderr.write('</read_request>')
    return (op_type, op_name, d)


def write_arg (s, arg):
    sys.stderr.write('<write_arg>')
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
        sys.stderr.write('write_arg called for undefined type!')
    sys.stderr.write('</write_arg>')


def write_dict (s, d):
    #sys.stderr.write('<write_dict>')
    write_int (s, len (d))
    if sys.version > '2':
        for key, value in d.items():
            write_string (s, key)
            write_arg (s, value)
    else:
        for key, value in d.iteritems():
            write_string (s, key)
            write_arg (s, value)
    #sys.stderr.write('</write_dict>')


def write_args (s, args):
    #sys.stderr.write('<write_args>')
    if type (args) is dict:
        write_dict (s, args)
    else:
        sys.stderr.write('write_args - was expecting dictionary for args!')
    #sys.stderr.write('</write_args>')


def write_success (s, args=None):
    sys.stderr.write('<write_success>')
    write_int (s, 0)
    if args is not None:
        write_args (s, args)
    sys.stderr.write('</write_success>')


def write_failed (s, fail_code, text=''):
    sys.stderr.write('<write_failed>')
    write_int (s, fail_code)
    write_string (s, text)
    sys.stderr.write('</write_failed>')
    


def callMOF(m):
    sys.stderr.write('MOF='+repr(m))
    op=('Test','Set','Get')
    if m[1] not in globals().keys():
        sys.stderr.write('Unable to find module: ' + md)
        return None
    the_module=globals()[m[1]]
    method_name=op[m[0]]+'_Marshall'
    if not method_name in the_module.__dict__.keys():
        sys.stderr.write('Unable to find method: ' + method_name)
        return None
    sys.stderr.write('calling '+m[1]+'.'+method_name+repr(m[2]))
    ret = the_module.__dict__[method_name](**m[2])
    sys.stderr.write(repr(ret))
    return ret
    
def handle_request (s, req):
    sys.stderr.write('<handle_request>')
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
            if req == None:
                read = -1
            else:
                sys.stderr.write('Main: request len is'+str(len(req)))
                handle_request (s, req)
        except socket.error:
            read = -1;
            sys.stderr.write('exception encountered')

##############################
try:
    try:
        sys.stderr.write('socket: '+str(sys.argv[1]))
        
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
        try:        
            F = open(pid_file,'w')
            F.write(str(os.getpid()) + "\n")
            F.flush()
            F.close()
        except:
             sys.stderr.write('Unable to create '+pid_file)
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
    
    
    except:
        sys.stderr.write('\nException: ')
        sys.stderr.write(repr(sys.exc_info())+'\n')
        traceback.print_tb(sys.exc_info()[2])
        sys.stderr.write('\n')

finally:
    sys.stderr.write('Exiting - closing socket\n' )
    (socket.fromfd(int (sys.argv[1]), socket.AF_UNIX, socket.SOCK_STREAM)).close()

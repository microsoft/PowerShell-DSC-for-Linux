#!/bin/env python
# =======================
# Copyright (c) Microsoft Corporation.
# All rights reserved.
# See license.txt for license information.
# =======================
from __future__ import print_function
from __future__ import with_statement
import subprocess
import imp
import os
import sys
import socket
import re

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')
LG = nxDSCLog.DSCLog

# [ClassVersion("1.0.0"), FriendlyName("nxFirewallResource")]
# class MSFT_nxFirewallResource:OMI_BaseResource
# {
#   [Key] string Name;
#   [Write] string InterfaceName;
#   [Write] string FirewallType; # Iptables, Ip6tables, yast, \
#   ufw, susefirewall2
#   [Write ValueMap{"tcp", "udp", "icmp"}] string Protocol;
#   [Write, {"Present", "Absent"},Values{"Present", "Absent"}] \
#   string Ensure;
#   [Write, ValueMap{"IPv4", "IPv6"},Values{"IPv4", "IPv6}] \
#   string AddressFamily;
#   [Write, ValueMap{"allow, block"},Values{"allow, block}] \
#   string Access;
#   [Write, ValueMap{"new, related, established"}] string State;
#   [Write, ValueMap{"input, output, forward"},Values{"input, \
#   output, forward}] string Direction;
#   [Write, ValueMap{"top", "after-top", "before-end", "end"},\
#   Values{"top", \
#   "after-top", "before-end", "end"} string Position;
#   [Write] string SourceHost;
#   [Write] string SourcePort;
#   [Write] string DestinationHost;
#   [Write] string DestinationPort;
# };

def init_vars(Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
    Access, State, Direction, Position, SourceHost, SourcePort,
    DestinationHost, DestinationPort):

    if Name is None or Name == '':
        print('Error: "Name" must be specified.', file=sys.stderr)
        LG().Log('ERROR', 'Error: "Name" must be specified.')
        raise Exception('Name must be specified.')
    Name = Name.encode('ascii', 'ignore')

    if InterfaceName is None or InterfaceName == '':
        InterfaceName = 'eth0'
    else:
        InterfaceName = InterfaceName.encode('ascii', 'ignore')

    if FirewallType is None or FirewallType == '':
        print('Error: "FirewallType" must be specified.', file=sys.stderr)
        LG().Log('ERROR', 'Error: "FirewallType" must be specified.')
        raise Exception('FirewallType must be specified.')
    FirewallType = FirewallType.encode('ascii', 'ignore').lower()

    if Protocol is None or Protocol == '':
        Protocol = 'tcp'
    Protocol = Protocol.encode('ascii', 'ignore')

    if Ensure is None or Ensure == '':
        Ensure = 'present'
    Ensure = Ensure.encode('ascii', 'ignore').lower()

    if AddressFamily is None or AddressFamily == '':
        AddressFamily = 'ipv4'
    AddressFamily = AddressFamily.encode('ascii', 'ignore').lower()

    if Access is None or Access == '':
        print(
            'Error: "Access" must be specified.', \
            file=sys.stderr)
        LG().Log(
            'ERROR', 'Error: "Access" must be specified.')
        raise Exception('Access must be specified.')
    Access = Access.encode('ascii', 'ignore').lower()

    if State is None:
        State = ''
        
    if Position is None or Position == '':
        Position = 'top'
    Position = Position.encode('ascii', 'ignore')

    if SourceHost is None:
        SourceHost = ''
    else :
        SourceHost = SourceHost.encode('ascii', 'ignore')
        if ValidateAddress(SourceHost, AddressFamily) is False:
            print(
            'Error: Invalid address for "SourceHost".', file=sys.stderr)
            LG().Log('ERROR', 'Error: Invalid address for "SourceHost".')
            raise Exception('Error: Invalid address for "SourceHost".')
        if AddressFamily == 'ipv6': # ip6tables only looks upto the first ':'
            if '/' in SourceHost:
                pfx=SourceHost.split('/')[1]
                SourceHost = SourceHost.split(':')[0]+'::/'+pfx
            else:
                SourceHost = SourceHost.split(':')[0]+'::'
    if SourcePort is None:
       SourcePort = '' 
    else :
        SourcePort = SourcePort.encode('ascii', 'ignore')
        if ValidatePort(SourcePort) is False:
            print(
            'Error: Invalid address for "SourcePort".', file=sys.stderr)
            LG().Log('ERROR', 'Error: Invalid address for "SourcePort".')
            raise Exception('Error: Invalid address for "SourcePort".')

    if DestinationHost is None:
        DestinationHost = ''
    else :
        DestinationHost = DestinationHost.encode('ascii', 'ignore')
        if ValidateAddress(DestinationHost, AddressFamily) is False:
            print(
            'Error: Invalid address for "DestinationHost".', file=sys.stderr)
            LG().Log('ERROR', 'Error: Invalid address for "DestinationHost".')
            raise Exception('Error: Invalid address for "DestinationHost".')
        if AddressFamily == 'ipv6': # ip6tables only looks upto the first ':'
            if '/' in DestinationHost:
                pfx=DestinationHost.split('/')[1]
                DestinationHost = DestinationHost.split(':')[0]+'::/'+pfx
            else:
                DestinationHost = DestinationHost.split(':')[0]+'::'
    if DestinationPort is None:
       DestinationPort = '' 
    else :
        DestinationPort = DestinationPort.encode('ascii', 'ignore')
        if ValidatePort(DestinationPort) is False:
            print(
            'Error: Invalid address for "DestinationPort".', file=sys.stderr)
            LG().Log('ERROR', 'Error: Invalid address for "DestinationPort".')
            raise Exception('Error: Invalid address for "DestinationPort".')
    
    if Direction is None or Direction == '':
        Direction = 'input'
    Direction = Direction.encode('ascii', 'ignore')

    return Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily, \
    Access, State, Direction, Position, SourceHost, SourcePort, \
    DestinationHost, DestinationPort


def Set_Marshall(Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
                 Access, State,  Direction, Position, SourceHost, SourcePort,
                 DestinationHost, DestinationPort):
    (Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
     Access, State,  Direction, Position, SourceHost, SourcePort,
     DestinationHost, DestinationPort) = init_vars(Name, InterfaceName, FirewallType, Protocol, Ensure,
    AddressFamily, Access, State, Direction, Position, SourceHost, SourcePort,
    DestinationHost, DestinationPort)
    Rule = RuleBag(Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
                   Access, State, Direction, Position, SourceHost, SourcePort,
                   DestinationHost, DestinationPort)
    retval = Set(Rule)
    return retval


def Test_Marshall(Name, InterfaceName, FirewallType, Protocol, Ensure,
    AddressFamily, Access, State,  Direction, Position, SourceHost,
                  SourcePort, DestinationHost, DestinationPort):
    (Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily, Access,
     State,  Direction, Position, SourceHost, SourcePort, DestinationHost,
     DestinationPort) = init_vars(Name, InterfaceName, FirewallType, Protocol, Ensure,
    AddressFamily, Access, State, Direction, Position, SourceHost,
                                  SourcePort, DestinationHost, DestinationPort)
    Rule = RuleBag(Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
                   Access, State, Direction, Position, SourceHost, SourcePort,
                   DestinationHost, DestinationPort)
    
    if Ensure == 'present':
        if Test(Rule)  == 0:
            return [0]
        else:
            return [-1]
    else:
        if Test(Rule)  == 0:
            return [-1]
        else:
            return [0]


def Get_Marshall(Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
    Access, State,  Direction, Position, SourceHost, SourcePort,
                 DestinationHost, DestinationPort):
    arg_names = list(locals().keys())
    (Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily, Access, State,
     Direction, Position, SourceHost, SourcePort, DestinationHost,
     DestinationPort) = init_vars(Name, InterfaceName, FirewallType, Protocol, Ensure,
    AddressFamily, Access, State, Direction, Position, SourceHost,
    SourcePort, DestinationHost, DestinationPort)
    Rule = RuleBag(Name, InterfaceName, FirewallType, Protocol, Ensure,
    AddressFamily, Access, State, Direction, Position, SourceHost, SourcePort,
    DestinationHost, DestinationPort)

    (Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
    Access, Direction, Position, SourceHost, SourcePort,
    DestinationHost, DestinationPort) = Get(Rule)
    Name = protocol.MI_String(Name)
    InterfaceName = protocol.MI_String(InterfaceName)
    FirewallType = protocol.MI_String(FirewallType)
    Protocol = protocol.MI_String(Protocol)
    Ensure = protocol.MI_String(Ensure)
    AddressFamily = protocol.MI_String(AddressFamily)
    Access = protocol.MI_String(Access)
    State = protocol.MI_StringA(State)
    Direction = protocol.MI_String(Direction)
    Position = protocol.MI_String(Position)
    SourceHost = protocol.MI_String(SourceHost)
    SourcePort = protocol.MI_String(SourcePort)
    DestinationHost = protocol.MI_String(DestinationHost)
    DestinationPort = protocol.MI_String(DestinationPort)
    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return 0, retd


# ############################
# ## Begin user defined DSC functions
# ############################

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
            raise subprocess.CalledProcessError(retcode, cmd, output=output)
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

    subprocess.check_output = check_output
    subprocess.CalledProcessError = CalledProcessError
    output = ''
    try:
        output = subprocess.check_output(
            no_output, cmd, stderr=subprocess.STDOUT, shell=True)
    except subprocess.CalledProcessError, e:
        if chk_err:
            print('CalledProcessError.  Error Code is ' +
                  str(e.returncode), file=sys.stdout)
            LG().Log('ERROR', 'CalledProcessError.  Error Code is ' +
                     str(e.returncode))
            print(
                'CalledProcessError.  Command string was ' + e.cmd, \
                file=sys.stdout)
            LG().Log('ERROR',
                     'CalledProcessError.  Command string was ' + e.cmd, \
                     )
            print('CalledProcessError.  Command result was ' +
                  (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'), \
                  file=sys.stdout)
            LG().Log('ERROR', 'CalledProcessError.  Command result was ' +
                     (e.output[:-1]).decode('utf-8').encode('ascii', 'ignore'))
        if no_output:
            return e.returncode, None
        else:
            return e.returncode, e.output.decode('utf-8').encode('ascii', \
            'ignore')

    if no_output:
        return 0, None
    else:
        return 0, output.decode('utf-8').encode('ascii', 'ignore')


def ValidateAddress(IPAddress, AddressFamily):
    if IPAddress == None or len(IPAddress) == 0: # allow empty or None.
        return True
    if ':' not in IPAddress and IPAddress[1].isalpha() == True: # dont try to validate a hostname.
        return True
    if '/' in IPAddress:
        IPAddress=IPAddress.split('/')[0]
    if 'ipv4' in AddressFamily:
        ptype = socket.AF_INET
    elif 'ipv6' in AddressFamily:
        ptype = socket.AF_INET6
    else:
        return False
    try:
        socket.inet_pton(ptype, IPAddress)
    except:
        return False
    return True


def ValidatePort(Port):
    try:
        socket.getaddrinfo(None, Port, 0, 0, socket.IPPROTO_TCP)
    except:
        return False
    return True


def IsFirewallRunning(rule):
    if rule.FirewallType == 'iptables':
        code, out = RunGetOutput('iptables -L',False)
        if code == 0:
            return True
    if rule.FirewallType == 'ip6tables':
        code, out = RunGetOutput('ip6tables -L',False)
        if code == 0:
            return True
    elif rule.FirewallType == 'firewalld':
        code, out = RunGetOutput('ps -ef | grep -v grep | grep firewalld',False)
        if code == 0:
            return True
    elif rule.FirewallType == 'ufw':
        code, out = RunGetOutput(
            'iptables -L | grep -v grep | grep ufw-before-input',False)
        if code == 0:
            return True
    elif rule.FirewallType == 'yast' or rule.FirewallType == 'susefirewall2':
        code, out = RunGetOutput('iptables -L | grep -v grep | grep SFW2',False)
        if code == 0:
            return True
    return False


def RuleExists(rule):
    if 'instancemethod' in repr(type(rule.cmds[rule.FirewallType]['check'])) :
        return rule.cmds[rule.FirewallType]['check']()
    cmd = rule.fmt(rule.cmds[rule.FirewallType]['check'])
    code, out = RunGetOutput(cmd,False)
    print('Check rule exists: ' + cmd + ' result code is: ' + str(code))
    LG().Log('INFO', 'Check rule exists: ' +
             cmd + ' result code is: ' + str(code))
    return code


def GetRuleCountInChain(rule):
    rule.cmds[rule.FirewallType]['chain']()
    cmd = rule.iptbls+' -L ' + rule.Direction
    code, out = RunGetOutput(cmd,False)
    if code != 0:
        return 0
    if out is not None and len(out) > 0:
        Val = None
        try:
            Val = len(out.splitlines())-2
        except:
            print('ERROR: Rule count is not numeric in Check rule exists: ' +
                  cmd + ' result code is: ' + str(code))
            LG().Log('ERROR', 'Rule count is not numeric in Check rule exists: ' +
                     cmd + ' result code is: ' + str(code))
    print('Count Rules in chain: ' + cmd + ' result code is: ' + str(code))
    LG().Log('INFO', 'Count Rules in chain: ' +
             cmd + ' result code is: ' + str(code))
    if Val is not None:
        return Val
    else:
        return 0


def DoAddRemove(rule):
    count = GetRuleCountInChain(rule)
    rule.Index = 0
    p = rule.Position
    if p != 'end':
        p = 'ind'
        if rule.Position == 'top':
            rule.Index = 1
        elif rule.Position == 'after-top':
            if count > 1:
                rule.Index = 2
            else:
                rule.Index = 1
        elif rule.Position == 'before-end':
            if count > 1:
                rule.Index = count
            else:
                p = 'end'
    cmd = rule.fmt(rule.cmds[rule.FirewallType][rule.Ensure][p])
    code, out = RunGetOutput(cmd,False)
    print('Set rule ' + rule.Ensure + ': ' +
          cmd + ' result code is: ' + str(code))
    LG().Log('INFO', 'Set rule ' + rule.Ensure +
             ': ' + cmd + ' result code is: ' + str(code))
    if code == 0:
        rule.cmds[rule.FirewallType]['post']()
    return code


def Test(rule):
    if IsFirewallRunning(rule) is False:
        print('Error ' + rule.FirewallType + ' is not running.')
        LG().Log('ERROR','Error ' + rule.FirewallType + ' is not running.')
        return -1
    if RuleExists(rule) == 0:
        return 0
    return -1


def Set(rule):
    if IsFirewallRunning(rule) is False:
        print('Error ' + rule.FirewallType + ' is not running.')
        LG().Log('ERROR','Error ' + rule.FirewallType + ' is not running.')
        return [-1]
    ret = DoAddRemove(rule)
    if ret == 0:
        return [0]
    return [-1]


def Get(rule):
    if Test(rule) == 0:
        Ensure = 'Present'
    else:
        Ensure = 'Absent'
    return rule.Name, rule.OrigInterfaceName, rule.FirewallType, rule.Protocol, Ensure, \
    rule.AddressFamily, rule.Access, rule.OrigDirection, \
    rule.Position, rule.SourceHost, rule.SourcePort, \
    rule.DestinationHost, rule.DestinationPort

iptables_regex=r"""
^-A[ ]+(?P<Direction>.*?)[ ]+
((?:-s[ ]+)(?P<SourceHost>.*?)
(((?:/)(?P<Spfx>.*?)(?:[ ]+))|(?:[ ]+)))?
((?:-d[ ]+)(?P<DestinationHost>.*?)
(((?:/)(?P<Dpfx>.*?)(?:[ ]+))|(?:[ ]+)))?
((?:-i[ ]+)(?P<InterfaceName>.*?)(?:[ ]+))?
((?:-p[ ]+)(?P<proto>.*?)(?:[ ]+))?
((?:-m[ ]+)(?P<matchport>.*?)(?:[ ]+))?
((?:--sport[ ]+)(?P<SourcePort>.*?)(?:[ ]+))?
((?:--dport[ ]+)(?P<DestinationPort>.*?)(?:[ ]+))?
((?:-m[ ]+)(?P<matchstate>.*?)(?:[ ]+))?
((?:--state[ ]+)(?P<State>.*?)(?:[ ]+))?
((?:-j[ ]+)(?P<Access>.*?)((?:[ ]+)|(?:$)))?
"""

class RuleBag(object):
    def __init__(self, Name, InterfaceName, FirewallType, Protocol, Ensure, AddressFamily,
                 Access, State, Direction, Position, SourceHost, SourcePort,
                 DestinationHost, DestinationPort):
        self.Name = Name
        self.FirewallType = FirewallType
        self.Protocol = Protocol
        self.Ensure = Ensure
        self.AddressFamily = AddressFamily
        self.iptbls='iptables'
        if self.AddressFamily == 'ipv6' :
            self.iptbls = 'ip6tables'
        if 'allow' == Access :
            self.Access = 'ACCEPT'
        else:
            self.Access = 'DROP'
        if len(State)>0:
            self.State=reduce(lambda x, y: x.encode('ascii','ignore') + ',' + y.encode('ascii','ignore') , State)
        else:
            self.State=''
        self.Direction = Direction
        self.Position = Position
        self.SourceHost = SourceHost
        self.SourcePort = SourcePort
        self.DestinationHost = DestinationHost
        self.DestinationPort = DestinationPort
        self.Index = 0
        self.InterfaceName = InterfaceName
        self.OrigInterfaceName = InterfaceName
        if self.Direction.lower() == 'output':
            self.InterfaceName = ''
        self.OrigDirection = Direction
        self.cmds = {}

        
        # iptables
        self.cmds['iptables'] = {}
        self.cmds['iptables']['present'] = {}
        self.cmds['iptables']['present']['end'] = self.iptbls + ' -A {Direction} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['iptables']['present']['ind'] = self.iptbls + ' -I {Direction} {Index} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['iptables']['absent'] = {}
        self.cmds['iptables']['absent']['end'] = self.iptbls + ' -D {Direction} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['iptables']['absent']['ind'] = self.iptbls + ' -D {Direction} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['iptables']['check'] = self.iptables_check
        self.cmds['iptables']['post'] = self.iptables_post
        self.cmds['iptables']['chain'] = self.iptables_chain_translate

        # ip6tables
        self.cmds['ip6tables'] = self.cmds['iptables']
        
        # firewalld firewall-cmd [--permanent] --direct --add-rule { ipv4 | ipv6 | eb } <table> <chain> <priority> <args>
        self.cmds['firewalld'] = {}
        self.cmds['firewalld']['present'] = {}
        self.cmds['firewalld']['present']['ind'] = 'firewall-cmd --direct --add-rule ' + ' {AddressFamily} filter {Direction} {Index} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['firewalld']['present']['end'] = 'firewall-cmd --direct --add-rule ' + ' {AddressFamily} filter {Direction} {Index} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['firewalld']['absent'] = {}
        self.cmds['firewalld']['absent']['ind'] = 'firewall-cmd --direct --remove-rule ' + ' {AddressFamily} filter {Direction} {Index} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['firewalld']['absent']['end'] = 'firewall-cmd --direct --remove-rule ' + ' {AddressFamily} filter {Direction} {Index} -i {InterfaceName} -p {Protocol} -s {SourceHost} --sport {SourcePort} -d {DestinationHost} --dport {DestinationPort} -m state --state {State} -j {Access}'
        self.cmds['firewalld']['check'] = self.iptables_check
        self.cmds['firewalld']['post'] = self.firewalld_post
        self.cmds['firewalld']['chain'] = self.firewalld_chain_translate

        # SuSEfirewall2
        self.cmds['susefirewall2'] = {}
        self.cmds['susefirewall2']['present'] = self.cmds['iptables']['present']
        self.cmds['susefirewall2']['absent'] = self.cmds['iptables']['absent']
        self.cmds['susefirewall2']['check'] = self.cmds['iptables']['check']
        self.cmds['susefirewall2']['post'] = self.susefirewall2_post
        self.cmds['susefirewall2']['chain'] = self.susefirewall2_chain_translate

        # SuSEfirewall2 - yast
        self.cmds['yast']=self.cmds['susefirewall2']

        # ufw
        self.cmds['ufw'] = {}
        self.cmds['ufw']['present'] = self.cmds['iptables']['present']
        self.cmds['ufw']['absent'] = self.cmds['iptables']['absent']
        self.cmds['ufw']['check'] = self.iptables_check
        self.cmds['ufw']['post'] = self.ufw_post
        self.cmds['ufw']['chain'] = self.ufw_chain_translate

    def iptables_check(self):
        self.cmds[self.FirewallType]['chain']()
        r=re.compile(iptables_regex,re.VERBOSE)
        code,out = RunGetOutput(self.iptbls + '-save ', False)
        mykeys=self.__dict__.keys()
        for line in out.splitlines():
            m=r.search(line)
            if m == None:
                continue
            found=True
            groupd=dict(m.groupdict())
            for k in groupd.keys():
                if k in mykeys:
                    if groupd[k] == None :
                        groupd[k] = ''
                    if k[-4:] == 'Host':
                        if self.__dict__[k] != None and '/' in self.__dict__[k]:
                            groupd[k]+= '/' + m.group(k[0:1]+'pfx')
                        if groupd[k] == '::':
                            groupd[k] = '' 
                    if groupd[k] != self.__dict__[k]:
                        found=False
                        break
            if found == True:
                return 0
        return 1

    def iptables_chain_translate(self):
        self.Direction = self.OrigDirection.upper()

    def iptables_post(self):
        self.update_iptables_rules()

    def update_iptables_rules(self):
        rules_file = '/etc/sysconfig/' + self.iptbls
        code =  os.system(self.iptbls + '-save > ' + rules_file)
        if code != 0 :
            print('Error: '+ self.iptbls +'-save > ' + rules_file + ' failed.', file=sys.stderr)
            LG().Log('ERROR', 'Error: '+ self.iptbls +'-save > ' + rules_file + ' failed.')
        return

    def firewalld_chain_translate(self):
        self.Direction = self.OrigDirection.upper() + '_direct'

    def firewalld_post(self):
        self.update_firewalld_rules()

    def update_firewalld_rules(self):
        p = self.Position
        if p != 'end':
            p = 'ind'
        rule = self.fmt(self.cmds[self.FirewallType][self.Ensure][p])
        cmd = rule.replace(
            'firewall-cmd', 'firewall-cmd --permanent ')
        code, out = RunGetOutput(cmd,False)
        print('Set permanent rule ' + self.Ensure +
              ': ' + cmd + ' result code is: ' + str(code))
        LG().Log('INFO', 'Set permanent rule ' + self.Ensure +
                 ': ' + cmd + ' result code is: ' + str(code))
        return

    def ufw_chain_translate(self):
        if self.Position == 'top':
            p = 'before'
        elif self.Position == 'after-top' or self.Position == 'before-end':
            p = 'user'
        else:
            p = 'after'
        ufw = 'ufw-'
        if self.AddressFamily == 'ipv6':
            ufw = 'ufw6-'
        self.Direction = ufw + p + '-' + self.OrigDirection.lower()

    def ufw_post(self):
        self.update_ufw_rules()

    def update_ufw_rules(self):
        rules_file = {}
        p=''
        if self.iptbls == 'ip6tables':
            p='6'
        rules_file['top'] = '/etc/ufw/before'+p+'.rules'
        rules_file['after-top'] = '/lib/ufw/user'+p+'.rules'
        rules_file['before-end'] = '/lib/ufw/user'+p+'.rules'
        rules_file['end'] = '/etc/ufw/after'+p+'.rules'
        p='end'
        if self.Position != 'end':
            p = 'ind'
        search_str = \
        r'^(.filter)(.*)((:.*?\n\n)|(:.*?\n#.*?\n\n))'
        rule = self.fmt(self.cmds[self.FirewallType]['present'][p])
        rule=re.sub(self.iptbls+r'.*? ','',rule)
        rplace_str = r'\1\2\3' + rule + '\n\n'
        text = ''
        with open(rules_file[self.Position], 'r') as F:
            text = F.read()
        text=text.replace(rule+'\n','') # remove rule
        if self.Ensure == 'present':
            srch = re.compile(search_str, re.M | re.S)
            text = srch.sub(rplace_str, text)
        with open(rules_file[self.Position], 'w') as F:
            F.write(text)

    def susefirewall2_chain_translate(self):
        self.Direction = self.OrigDirection.upper()

    def susefirewall2_post(self):
        self.update_susefirewall2_rules()

    def update_susefirewall2_rules(self):
        rules_file = '/etc/sysconfig/scripts/SuSEfirewall2-custom'
        pos = {}
        pos['top'] = 'fw_custom_before_antispoofing'
        pos['after-top'] = 'fw_custom_after_antispoofing'
        pos['before-end'] = 'fw_custom_before_masq'
        pos['end'] = 'fw_custom_before_denyall'
        pos['anchor'] = 'true\n'
        search_str = r'^.*(fw_custom_before_antispoofing)(.*?[{].*?)(\n[ ]+true\n}\n)'
        rule = self.fmt(self.cmds[self.FirewallType]['present']['end'])
        rplace_str = r'\1\2' + rule + r'\n\3'
        text = ''
        with open(rules_file, 'r') as F:
            text = F.read()
        text=text.replace(rule+'\n','') # remove rule
        if self.Ensure == 'present':
            srch = re.compile(search_str, re.M| re.S)
            text = srch.sub(rplace_str, text)
        with open(rules_file, 'w') as F:
            F.write(text)

    def fmt(self, st):
        for k in self.__dict__.keys():
            if 'cmds' in k:
                continue
            if k == 'Direction':
                self.cmds[self.FirewallType]['chain']()
            if type(self.__dict__[k]) == int :
                st = st.replace('{' + k + '}', str(self.__dict__[k])) 
            elif self.__dict__[k]==None or (type(self.__dict__[k]) == str and len(self.__dict__[k]) == 0) :
                st = re.sub(r'}'+k[::-1]+'{.*?[-]+', '', st[::-1])[::-1]
                if k == 'State':
                    st = st.replace('-m state ','')
            else :
                st = st.replace('{' + k + '}', self.__dict__[k])
        return st


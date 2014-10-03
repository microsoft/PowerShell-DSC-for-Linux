#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================

import subprocess
import os
import pwd
import shutil
import grp
import time

def Set_Marshall( Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):
    Name = Name.decode("utf-8")
    Protocol = Protocol.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    AddressFamily = AddressFamily.decode("utf-8")
    Access = Access.decode("utf-8")
    State = State.decode("utf-8")
    State2 = State2.decode("utf-8")
    State3 = State3.decode("utf-8")
    Direction = Direction.decode("utf-8")
    SourceHost = SourceHost.decode("utf-8")
    SourcePort = SourcePort.decode("utf-8")
    DestinationHost = DestinationHost.decode("utf-8")
    DestinationPort = DestinationPort.decode("utf-8")
    

    retval = Set( Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)
    return retval

def Test_Marshall( Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):
    Name = Name.decode("utf-8")
    Protocol = Protocol.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    AddressFamily = AddressFamily.decode("utf-8")
    Access = Access.decode("utf-8")
    State = State.decode("utf-8")
    State2 = State2.decode("utf-8")
    State3 = State3.decode("utf-8")
    Direction = Direction.decode("utf-8")
    SourceHost = SourceHost.decode("utf-8")
    SourcePort = SourcePort.decode("utf-8")
    DestinationHost = DestinationHost.decode("utf-8")
    DestinationPort = DestinationPort.decode("utf-8")

    retval = Test(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)
    return retval


def Get_Marshall(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):
    Name = Name.decode("utf-8")
    Protocol = Protocol.decode("utf-8")
    Ensure = Ensure.decode("utf-8")
    AddressFamily = AddressFamily.decode("utf-8")
    Access = Access.decode("utf-8")
    State = State.decode("utf-8")
    State2 = State2.decode("utf-8")
    State3 = State3.decode("utf-8")
    Direction = Direction.decode("utf-8")
    SourceHost = SourceHost.decode("utf-8")
    SourcePort = SourcePort.decode("utf-8")
    DestinationHost = DestinationHost.decode("utf-8")
    DestinationPort = DestinationPort.decode("utf-8")

    retval = 0
    (retval, Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort) = Get(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)

    Name = Name.encode("utf-8")
    Protocol = Protocol.encode("utf-8")
    Ensure = Ensure.encode("utf-8")
    AddressFamily = AddressFamily.encode("utf-8")
    Access = Access.encode("utf-8")
    State = State.encode("utf-8")
    State2 = State2.encode("utf-8")
    State3 = State3.encode("utf-8")
    Direction = Direction.encode("utf-8")
    SourceHost = SourceHost.encode("utf-8")
    SourcePort = SourcePort.encode("utf-8")
    DestinationHost = DestinationHost.encode("utf-8")
    DestinationPort = DestinationPort.encode("utf-8")

    return [retval, Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort]

############################################################
### Begin user defined DSC functions
############################################################



def Test(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):

    SetString = BuildRuleString(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)

    if Ensure == "Present":

        ReadFileReturn = ReadFile(SetString, Ensure, AddressFamily)

        if ReadFileReturn == -1:

            return -1
        
        elif ReadFileReturn == 0:

            return 0

    elif Ensure == "Absent":

        x = 1

        RulesDeleted = ReadFileEnsureAbsent(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)

        if RulesDeleted == [-1]:

            return [0]

        else:
        
            return [-1]

 


def Set(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):
    
    if Ensure == "Present":

        SetString = BuildRuleString(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)
    
        ProcessSetStringTest(SetString)

    elif Ensure == "Absent":

        RulesDeleted = ReadFileEnsureAbsent(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)

        RuleString = '\n'.join(RulesDeleted)

        ProcessIPRestore(AddressFamily, RuleString)

    return [0]



               

def Get(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):

    if Ensure == "Present":

        SetString = BuildRuleString(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)

        ReadFileReturn = ReadFile(SetString, Ensure, AddressFamily)

        if ReadFileReturn == -1:

            return [0, Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort]

        elif ReadFileReturn == 0:

            return [0, "", "", "", "", "", "", "", "", "", "", "", "", ""]

    elif Ensure == "Absent":

        if AddressFamily == "IPv4":

            (process_stdout, process_stderr, retval) = Process("iptables-save")

        elif AddressFamily == "IPv6":

            (process_stdout, process_stderr, retval) = Process("ip6tables-save")

        Infile = process_stdout

        InfileLines = Infile.split("\n")

        NumLines = InfileLines.__len__()

        i = 0

        while i < NumLines:

            CurrentRule = InfileLines[i]

            RuleMatch = -1

            # Check each parameter 

            if Protocol:

                ParamExist = CurrentRule.find(Protocol)
                
                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            if AddressFamily:

                if AddressFamily == "IPv4":

                    ParamExist = CurrentRule.find("iptables")

                elif AddressFamily == "IPv6":

                    ParamExist = CurrentRule.find("ip6tables")

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            if Access:

                if Access == "Allow":

                    ParamExist = CurrentRule.find("ACCEPT")

                elif Access == "Block":

                    ParamExist = CurrentRule.find("DROP")

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            if State:

                ParamExist = CurrentRule.find(State)

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0 

                    if State2:

                        ParamExist = CurrentRule.find(State2)

                        if ParamExist == -1:

                            break

                        else:

                            RuleMatch = 0

                            if State3:

                                ParamExist = CurrentRule.find(State3)

                                if ParamExist == -1:

                                    break

                                else:

                                    RuleMatch = 0 
                    
            if Direction:

                ParamExist = CurrentRule.find(Direction)

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            if SourceHost:

                ParamExist = CurrentRule.find(SourceHost)

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            if SourcePort:

                ParamExist = CurrentRule.find(SourcePort)

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            if DestinationHost:

                ParamExist = CurrentRule.find(DestinationHost)

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            if DestinationPort:

                ParamExist = CurrentRule.find(DestinationPort)

                if ParamExist == -1:

                    break

                else:

                    RuleMatch = 0

            # Once all parameters have been checked

            if RuleMatch == 0:

                Name = ""
                Protocol = ""
                Access = ""
                State = ""
                State2 = ""
                State3 = ""
                Direction = ""
                SourceHost = ""
                SourcePort = ""
                DestinationHost = ""
                DestinationPort = ""

                CurrentRuleTable = CurrentRule.split(" ")

                j = 0

                TableNumLines = len(CurrentRuleTable)

                while j < TableNumLines - 1:  #Last position in the table does not need to be read

                    Rule = CurrentRuleTable[j]

                    k = j + 1

                    j = j + 1

                    if Rule.find("-s") != -1:

                        SourceHost = CurrentRuleTable[k]

                        j = j + 1

                        break

                    if Rule.find("-d") != -1:

                        DestinationHost = CurrentRuleTable[k]

                        j = j + 1

                        break

                    if Rule.find("-p") != -1:

                        Protocol = CurrentRuleTable[k]

                        j = j + 1

                        break

                    if Rule.find("--sport") != -1:

                        SourcePort = CurrentRuleTable[k]

                        j = j + 1

                        break

                    if Rule.find("--dport") != -1:

                        DestinationPort = CurrentRuleTable[k]

                        j = j + 1

                        break

                    if Rule.find("--state") != -1:

                        StateRule = Rule.split(",")

                        StateNumLine = len(StateRule)

                        State = StateRule[0]

                        if StateNumLine == 2:

                            State2 = StateRule[1]

                        if StateNumLine == 3:

                            State2 = StateRule[1]

                            State3 = StateRule[2]

                        j = j + 1

                        break

                    if Rule.find("-j") != -1:

                        Access = CurrentRuleTable[k]

                        j = j + 1

                        break

                return [0, Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort]

            i = i + 1

        return [0, "", "", "", "", "", "", "", "", "", "", "", "", ""]





def ReadFileEnsureAbsent(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):

    if AddressFamily == "IPv4":

        (process_stdout, process_stderr, retval) = Process("iptables-save")

    elif AddressFamily == "IPv6":

        (process_stdout, process_stderr, retval) = Process("ip6tables-save")

    Infile = process_stdout

    RulesDeletedBefore = Infile.split("\n")

    NumLines = len(RulesDeletedBefore)

    i = 0
    
    while i < NumLines - 1:  #Line "*filter" is not read, the "-1" accounts for this

        CurrentRule = RulesDeletedBefore[i]

        RuleMatch = -1

        ParamExist = 0

        # Check each parameter 

        if Protocol and  ParamExist != -1:

            ParamExist = CurrentRule.find(Protocol)
                
            if ParamExist != -1:

                RuleMatch = 0

        if Access and ParamExist != -1:

            if Access == "Allow":

                ParamExist = CurrentRule.find("ACCEPT")

            elif Access == "Block":

                ParamExist = CurrentRule.find("DROP")

            if ParamExist != -1:

                RuleMatch = 0

        if State and ParamExist != -1:

            ParamExist = CurrentRule.find(State)

            if ParamExist != -1:

                RuleMatch = 0 

                if State2:

                    ParamExist = CurrentRule.find(State2)

                    if ParamExist != -1:

                        RuleMatch = 0

                        if State3:

                            ParamExist = CurrentRule.find(State3)

                            if ParamExist != -1:

                                RuleMatch = 0

        if Direction and ParamExist != -1:

            ParamExist = CurrentRule.find(Direction)

            if ParamExist != -1:

                RuleMatch = 0

        if SourceHost and ParamExist != -1:

            ParamExist = CurrentRule.find(SourceHost)

            if ParamExist != -1:

                RuleMatch = 0

        if SourcePort and ParamExist != -1:

            ParamExist = CurrentRule.find(SourcePort)

            if ParamExist != -1:

                RuleMatch = 0

        if DestinationHost and ParamExist != -1:

            ParamExist = CurrentRule.find(DestinationHost)

            if ParamExist != -1:

                RuleMatch = 0

        if DestinationPort and ParamExist != -1:

            ParamExist = CurrentRule.find(DestinationPort)

            if ParamExist != -1:

                RuleMatch = 0

        # Once all parameters have been checked

        if RuleMatch == 0 and ParamExist != -1:

            RulesDeleted = RulesDeletedBefore.remove(CurrentRule)

            i = i - 1

            NumLines = len(RulesDeletedBefore)

        i = i + 1

    return RulesDeletedBefore



def ReadFile(SetString, Ensure, AddressFamily):

    if AddressFamily == "IPv4":

        (process_stdout, process_stderr, retval) = Process("iptables-save")

        RulePrefix = "iptables "

    elif AddressFamily == "IPv6":

        (process_stdout, process_stderr, retval) = Process("ip6tables-save")

        RulePrefix = "ip6tables "

    Infile = process_stdout

    InfileLines = Infile.split("\n")

    i = 0

    NumLines = len(InfileLines)

    while i < NumLines:

        CurrentRule = InfileLines[i]

        CurrentRule = RulePrefix + CurrentRule

        CurrentRule = CurrentRule.strip()

        j = 0

        while j < 2:

            IndexNum = CurrentRule.find("/")

            if IndexNum != -1:

                if CurrentRule[IndexNum + 3] == " ":

                    CurrentRule = CurrentRule[:IndexNum] + CurrentRule[IndexNum + 3:]

                elif CurrentRule[IndexNum + 2] == " ":

                    CurrentRule = CurrentRule[:IndexNum] + CurrentRule[IndexNum + 2]

                CurrentRule = CurrentRule[:IndexNum] + CurrentRule[IndexNum + NumDelete:]

            j = j + 1            

        if Ensure == "Absent":

            CurrentRule = CurrentRule.replace("-A ","-D ")

        if SetString == CurrentRule:
                
            return 0

        i = i + 1


    return -1    



def Process(params):
    process = subprocess.Popen(params, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    (process_stdout, process_stderr) = process.communicate()

    return (process_stdout, process_stderr, process.returncode)




def ProcessIPRestore(AddressFamily, RuleString):

    if AddressFamily == "IPv4":
    
        process = subprocess.Popen(["iptables-restore"], stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)     # Removed the "/usr/sbin"

    elif AddressFamily == "IPv6":

        process = subprocess.Popen(["ip6tables-restore"], stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)

    (stdout, stderr) = process.communicate(RuleString)



                           
def BuildRuleString(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort):

    SetString = ""

    if AddressFamily:

        if AddressFamily == "IPv4":

            SetString += "iptables"

        elif AddressFamily == "IPv6":

            SetString += "ip6tables"

    if Ensure:

        if Ensure == "Present":

            SetString += " -A "

        elif Ensure == "Absent":

            SetString += " -D "
                    

    if Direction:

        SetString += Direction


    if Protocol:
        
        SetString += " -p " + Protocol


    if SourceHost:

        SetString += " -s " + SourceHost
        

    if SourcePort:

        SetString += " --sport " + SourcePort


    if DestinationHost:

        SetString += " -d " + DestinationHost
        

    if DestinationPort:

        SetString += " --dport " + DestinationPort
 

    if State:

        if State == State2:

            State2 = ""

        if State == State3:

            State3 = ""

        if State2 == State3:

            State3 = ""

        if State2:

            if State2 == "NEW":

                StateTemp = State

                State = State2

                State2 = StateTemp

            if State == "ESTABLISHED":

                StateTemp = State2

                State2 = State

                State = StateTemp

            if State3:

                State = "NEW"

                State2 = "RELATED"

                State3 = "ESTABLISHED"        

        SetString += " -m state --state " + State

        if State2:

            SetString += "," + State2

            if State3:

                SetString += "," + State3

    if Access:

        if Access == "Allow":

            SetString += " -j ACCEPT"

        elif Access == "Block":

            SetString += " -j DROP"
    
    return SetString





def ProcessSetStringTest(SetString):
    
    (process_stdout, process_stderr, retval) = Process(SetString.split())





'''

######################################
#######  Below is for testing purposes
######################################

Name = "scxfirewallrule  "
    
Protocol = ""  #{tcp, udp}

Ensure = "Absent"  #{Present, Absent}

AddressFamily = "IPv4"  #{IPv4, IPv6}

Access = ""  #{Allow, Block}   ACCEPT or DROP

State = ""  #{ESTABLISHED, RELATED, NEW}

State2 = ""  #{ESTABLISHED, RELATED, NEW}

State3 = ""  #{ESTABLISHED, RELATED, NEW}

Direction = ""  #{INPUT, OUTPUT, FORWARD}

SourceHost = ""

SourcePort = ""

DestinationHost = ""

DestinationPort = ""


 
GetOrTest = "Test"   #{Get, Test}



if GetOrTest == "Test":

    Setvar = 0

    Setvar = Test(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)

    if Setvar == -1:

        Set(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)

elif GetOrTest == "Get":

    Get(Name, Protocol, Ensure, AddressFamily, Access, State, State2, State3, Direction, SourceHost, SourcePort, DestinationHost, DestinationPort)
'''


'''


(process_stdout, process_stderr, retval) = Process("/usr/sbin/iptables-restore")

print process_stdout
'''

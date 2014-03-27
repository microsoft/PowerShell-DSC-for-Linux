import subprocess
import shutil
import pwd
import grp
import os
import stat
import time
import datetime

def Set_Marshall(Name, Controller, Enabled, State):
    Name = Name.decode("utf-8")
    Controller = Controller.decode("utf-8")
    Enabled = Enabled.decode("utf-8")
    State = State.decode("utf-8")

    retval = Set(Name, Controller, Enabled, State)
    return retval

def Test_Marshall(Name, Controller, Enabled, State):
    Name = Name.decode("utf-8")
    Controller = Controller.decode("utf-8")
    Enabled = Enabled.decode("utf-8")
    State = State.decode("utf-8")

    retval = Test(Name, Controller, Enabled, State)
    return retval

def Get_Marshall(Name, Controller, Enabled, State):
    Name = Name.decode("utf-8")
    Controller = Controller.decode("utf-8")
    Enabled = Enabled.decode("utf-8")
    State = State.decode("utf-8")

    retval = 0
    (retval, Name, Controller, Enabled, State, IsEnabled, Status, Path) = Get(Name, Controller, Enabled, State)

    Name = Name.encode("utf-8")
    Controller = Controller.encode("utf-8")
    Enabled = Enabled.encode("utf-8")
    State = State.encode("utf-8")
    IsEnabled = IsEnabled.encode("utf-8")
    Status = Status.encode("utf-8")
    Path = Path.encode("utf-8")

    return [retval, Name, Controller, Enabled, State, IsEnabled, Status, Path]


############################################################
### Begin user defined DSC functions
############################################################
def Set(Name, Controller, Enabled, State):
    return [0]

def Test(Name, Controller, Enabled, State):
    return [-1]

def Get(Name, Controller, Enabled, State):
    IsEnabled = Status = Path = ""
    exit_code = 0
    return [exit_code, Name, Controller, Enabled, State, IsEnabled, Status, Path]



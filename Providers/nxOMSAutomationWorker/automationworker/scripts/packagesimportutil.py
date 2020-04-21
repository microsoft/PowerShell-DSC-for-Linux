#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import sys, os

AUTOMATIONWORKER = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker"
HYBRIDWORKER = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/worker"

def add_directories_under_to_sys_path(directory_path, list_of_directories):
    if directory_path == None:
        print("Directory path provided is null")
        return
    if list_of_directories == None:
        print("No list of directories found to add")
        return 
    for dire in list_of_directories:
        imm_direc = str(directory_path + "/" + dire)
        sys.path.append(imm_direc)

def add_all_packages_under_automationworker_to_sys_path():
    if(os.path.isdir(AUTOMATIONWORKER)):
        list_of_directories_under_automation_worker = next(os.walk(AUTOMATIONWORKER))[1]
    else:
        print("Automation Worker for python3 is not present")
    if(os.path.isdir(HYBRIDWORKER)):
        list_of_directories_under_worker = next(os.walk(HYBRIDWORKER))[1]
    else:
        print("Hybrid Worker for python3 is not present")
    add_directories_under_to_sys_path(AUTOMATIONWORKER, list_of_directories_under_automation_worker)
    add_directories_under_to_sys_path(HYBRIDWORKER, list_of_directories_under_worker)    

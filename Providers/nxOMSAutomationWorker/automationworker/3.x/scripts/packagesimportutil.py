import sys, os

AUTOMATIONWORKER_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x"
WORKER_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x/worker"

def add_directories_under_to_sys_path(list_of_directories, directory_path):
    for dire in list_of_directories:
        imm_direc = str(directory_path + "/" + dire)
        sys.path.append(imm_direc)

def add_all_packages_under_automationworker_to_sys_path():
    if(os.path.isdir(AUTOMATIONWORKER_PATH)):
        list_of_directories_under_automation_worker = next(os.walk(AUTOMATIONWORKER_PATH))[1]
    else:
        print("Automation Worker path is incorrect")
    if(os.path.isdir(WORKER_PATH)):
        list_of_directories_under_worker = next(os.walk(WORKER_PATH))[1]
    else:
        print("Worker Path is incorrect")
    add_directories_under_to_sys_path(list_of_directories_under_automation_worker, AUTOMATIONWORKER_PATH)
    add_directories_under_to_sys_path(list_of_directories_under_worker, WORKER_PATH)    

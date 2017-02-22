#!/usr/bin/python
import sys
import os
import subprocess
import shutil
import platform

def usage():
    print("Usage:")
    print("  RemoveModule.py NAME")
    sys.exit(1)


def RemoveMirroredDirectory(moduleDir, omiDir):
    if len(moduleDir) < 15 or len(omiDir) < 10:
        print("Error: The parameters to RemoveMirroredDirectory are too short.  This function can do dangerous things, so this is a sanity check.")
        sys.exit(1)

    for curFile in os.listdir(moduleDir):
        if os.path.islink(moduleDir + "/" + curFile):
            os.path.unlink(moduleDir + "/" + curFile)
        elif os.path.isfile(moduleDir + "/" + curFile):
            os.remove(moduleDir + "/" + curFile)
        elif os.path.isdir(moduleDir + "/" + curFile):
            RemoveMirroredDirectory(moduleDir + "/" + curFile, omiDir + "/" + curFile)
            os.rmdir(moduleDir + "/" + curFile)
            if len(os.listdir(omiDir + "/" + curFile)) == 0:
                os.rmdir(omiDir + "/" + curFile)

        if os.path.islink(omiDir + "/" + curFile):
            os.path.unlink(omiDir + "/" + curFile)
        elif os.path.isfile(omiDir + "/" + curFile):
            os.remove(omiDir + "/" + curFile)

if len(sys.argv) != 2:
    usage()

moduleName = sys.argv[1]
omi_bindir = "<CONFIG_BINDIR>"
omi_libdir = "<CONFIG_LIBDIR>"
omi_sysconfdir = "<CONFIG_SYSCONFDIR>"
baseModulePath = "<DSC_MODULES_PATH>"
baseScriptPath = "<DSC_SCRIPT_PATH>"
modulePath = baseModulePath + "/" + moduleName
omiregister_dir = "/etc/opt/omi/conf/omiregister"

if not os.path.isdir(modulePath):
    print("Error: unable to find installed module " + moduleName + " at " + modulePath)
    sys.exit(1)

print("Removing module " + moduleName)

# special section for nxOMSAutomationWorker module
# the Linux Hybrid worker needs to be killed before the module is removed
# also a good idea to remove the state.conf file
# manually invoking RemoveModule.py will preserve worker.conf file in case the user wants to keep their settings
# an uninstall or purge operation of the OMS agent installer will get rid of worker.conf file
if moduleName == "nxOMSAutomationWorker":
    registration_file_path = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/scripts/register_oms.py"
    state_conf_location = "/var/opt/microsoft/omsagent/state/automationworker/state.conf"
    config_state_section = "state"
    config_pid_key = "pid"
    workspace_id_key = "workspace_id"
    automation_user = "nxautomation"
    import signal
    try:
        import ConfigParser
    except ImportError:
        # ConfigParser is named configparser in python 3x
        import configparser as ConfigParser

    # invoke deregister when it becomes available

    if os.path.isfile(state_conf_location):
        state_conf = ConfigParser.ConfigParser()
        try:
            # try to read the PID of the worker and make a best effort attempt to kill it
            # don't fail uninstall if it cannot be killed
            state_conf.read(state_conf_location)
            worker_process_id = state_conf.get(config_state_section, config_pid_key)
            workspace_id = state_conf.get(config_state_section, workspace_id_key)
            os.kill(int(worker_process_id), signal.SIGTERM)
            # Typicallly the above kill should be sufficient becasue we should never reach as state where there are more
            # than 1 workers. Since we introduced a new user to exclusively for worker, we can safely kill all processes
            # that user which were started with the workspace id for additional safety
            subprocess.call(["sudo", "pkill", "-u", automation_user, "--full", workspace_id])
        except ConfigParser.NoSectionError:
            pass
        except ConfigParser.NoOptionError:
            pass
        except OSError:
            pass
        try:
            os.remove(state_conf_location)
        except:
            pass

resourcelist = os.listdir(modulePath + "/DSCResources")
for resource in resourcelist:
    print("Removing resource " + resource)
    # Remove omi registration for each class
    namespace_dir = "<DSC_NAMESPACE>".replace("/","-")
    os.remove(omiregister_dir + "/" + namespace_dir + "/" + resource + ".reg")
    
    # Remove schema/registration for each class
    schemadir = omi_sysconfdir + "/<CONFIG_SYSCONFDIR_DSC>/configuration/schema"
    regdir = omi_sysconfdir + "/<CONFIG_SYSCONFDIR_DSC>/configuration/registration"
    if os.path.isdir(schemadir + "/" + resource):
        shutil.rmtree(schemadir + "/" + resource)
    if os.path.isdir(regdir + "/" + resource):
        shutil.rmtree(regdir + "/" + resource)

    if os.path.isfile(modulePath + "/DSCResources/" + resource + "/" + resource + ".schema.mof"):
        os.remove(modulePath + "/DSCResources/" + resource + "/" + resource + ".schema.mof")

    # Remove all files in libdir (lib for x86, lib64 for x64) for each class
    libdir = "x86"
    arch = platform.architecture()
    if len(arch) != 2:
        print("Error: The python function platform.architecture() failed to return a valid tuple. Cannot detect if this system has x64 or x86 architecture.")
        sys.exit(1)
    if (arch[0] == "64bit"):
        libdir = "x64"
        
    libdirPath = modulePath + "/DSCResources/" + resource + "/" + libdir
    if not os.path.isdir(libdirPath):
        print("Error: Unable to find directory in module at " + libdirPath + ", unable to remove module.")
        sys.exit(1)

    # In libdirPath, there's .so file(s) and a Script directory.  We want to remove the .so from its omi lib path, and the Scripts inside the Script directory
    filelist = os.listdir(libdirPath)
    for f in filelist:
        if not os.path.isdir(libdirPath + "/" + f):
            os.remove(omi_libdir + "/" + f)
            os.remove(libdirPath + "/" + f)
    
    # Now remove the scripts from their installed location
    RemoveMirroredDirectory(libdirPath + "/Scripts", baseScriptPath)
    if os.path.isdir(modulePath + "/DSCResources/" + resource + "/x86"):
        shutil.rmtree(modulePath + "/DSCResources/" + resource + "/x86")
    if os.path.isdir(modulePath + "/DSCResources/" + resource + "/x64"):
        shutil.rmtree(modulePath + "/DSCResources/" + resource + "/x64")

shutil.rmtree(modulePath)

retval = subprocess.call([baseScriptPath + "/RegenerateInitFiles.py"])
if retval != 0:
    print("Error: failed to regenerate init files.")
sys.exit(0)




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
        print("Removing " + moduleDir + "/" + curFile + " and " + omiDir + "/" + curFile)
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
modulePath = "/opt/microsoft/dsc/modules/" + moduleName

if not os.path.isdir(modulePath):
    print("Error: unable to find installed module " + moduleName + " at " + modulePath)
    sys.exit(1)

print("Removing module " + moduleName)


resourcelist = os.listdir(modulePath + "/DSCResources")
for resource in resourcelist:
    print("Removing resource " + resource)
    # Remove schema/registration for each class
    schemadir = "/opt/omi/etc/dsc/configuration/schema"
    regdir = "/opt/omi/etc/dsc/configuration/registration"
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

    RemoveMirroredDirectory(libdirPath, "/opt/omi/lib")
    if os.path.isdir(modulePath + "/DSCResources/" + resource + "/x86"):
        shutil.rmtree(modulePath + "/DSCResources/" + resource + "/x86")
    if os.path.isdir(modulePath + "/DSCResources/" + resource + "/x64"):
        shutil.rmtree(modulePath + "/DSCResources/" + resource + "/x64")

shutil.rmtree(modulePath)

retval = subprocess.call(["/opt/microsoft/dsc/Scripts/RegenerateInitFiles.py"])
if retval != 0:
    print("Error: failed to regenerate init files.")
sys.exit(0)




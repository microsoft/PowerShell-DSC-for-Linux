#!/usr/bin/python
import sys
import os
import subprocess
import shutil
import platform

def usage():
    print("Usage:")
    print("  InstallModule.py NAME_VERSION.zip")
    sys.exit(1)

def registration_text(resource):
    return '''
Instance of MSFT_CimConfigurationProviderRegistration
{
  className = "''' + resource + '''";
  DSCEngineCompatVersion = "1.0.0";
  DSCModuleVersion = "1.0.0";
  Namespace = "root/Microsoft/DesiredStateConfiguration";
};
'''

if len(sys.argv) != 2:
    usage()

filepath = sys.argv[1]

if not os.path.isfile(filepath):
    print("Error: " + filepath + " is not a file.")
    sys.exit(1)

basename = os.path.basename(filepath)
last_underscore = basename.rfind("_")

if last_underscore == -1:
    print("Error: Invalid name for zipfile.  Must be NAME_VERSION.zip")
    sys.exit(1)

token1 = basename[0:last_underscore]
token2 = basename[last_underscore+1:]

zip_loc = token2.rfind(".zip")

moduleVersion = token2[0:zip_loc]
moduleName = token1

if "." not in moduleVersion:
    print("Error: Version does not contain a dot and is thus improperly formed.")
    sys.exit(1)

omi_bindir = "<CONFIG_BINDIR>"
omi_libdir = "<CONFIG_LIBDIR>"
omi_sysconfdir = "<CONFIG_SYSCONFDIR>"
dsc_path = "<DSC_PATH>"
baseModulePath = dsc_path + "/modules"
modulePath = baseModulePath + "/" + moduleName

retval = subprocess.call(["unzip","-o","-d", baseModulePath, filepath])
if retval != 0:
    print("Error: Failed to unzip " + filepath)
    sys.exit(1)

if not os.path.isdir(modulePath):
    print("Error: After extracting module, unable to find module directory in " + baseModulePath)
    sys.exit(1)

if not os.path.isdir(modulePath + "/DSCResources"):
    print("Error: After extracting module, unable to find DSCResources directory in " + modulePath)
    sys.exit(1)

f = open(modulePath+ "/VERSION", "w")
f.write(moduleVersion)
f.close()

# Install each resource
resourcelist = os.listdir(modulePath + "/DSCResources")
for resource in resourcelist:
    print("Installing resource " + resource)
    if not os.path.isdir(modulePath + "/DSCResources/" + resource):
        # skip non-directories
        continue
    
    # Install schema/registration files
    if not os.path.isdir(omi_sysconfdir + "/dsc/configuration/registration/" + resource):
        os.mkdir(omi_sysconfdir + "/dsc/configuration/registration/" + resource)
    if not os.path.isdir(omi_sysconfdir + "/dsc/configuration/schema/" + resource):
        os.mkdir(omi_sysconfdir + "/dsc/configuration/schema/" + resource)

    if not os.path.isfile(modulePath + "/DSCResources/" + resource + "/" + resource + ".schema.mof"):
        print("Error: Unable to find schema mof for resource " + resource)
        sys.exit(1)

    shutil.copy(modulePath + "/DSCResources/" + resource + "/" + resource + ".schema.mof", omi_sysconfdir + "/dsc/configuration/schema/" + resource + "/")
    shutil.copy(modulePath + "/DSCResources/" + resource + "/" + resource + ".reg", omi_sysconfdir + "/omiregister/root-Microsoft-DesiredStateConfiguration/")
    f = open(omi_sysconfdir + "/dsc/configuration/registration/" + resource + "/" + resource + ".registration.mof", "w")
    f.write(registration_text(resource))
    f.close()

    # Install lib files (lib for x86, lib64 for x64)
    libdir = "x86"
    arch = platform.architecture()
    if len(arch) != 2:
        print("Error: The python function platform.architecture() failed to return a valid tuple. Cannot detect if this system has x64 or x86 architecture.")
        sys.exit(1)
    if (arch[0] == "64bit"):
        libdir = "x64"
        
    libdirPath = modulePath + "/DSCResources/" + resource + "/" + libdir
    if not os.path.isdir(libdirPath):
        print("Error: Unable to find directory in module at " + libdirPath + ", unable to install module.")
        sys.exit(1)

    os.rename(libdirPath, modulePath + "/DSCResources/" + resource + "/lib")
    retval = subprocess.call(["cp", "-R", modulePath + "/DSCResources/" + resource + "/lib/", omi_libdir + "/.."])
    os.rename(modulePath + "/DSCResources/" + resource + "/lib", libdirPath)
    if retval != 0:
        print("Error: Failed to install module " + moduleName + " on resource " + resource)
        sys.exit(1)

retval = subprocess.call([omi_libdir + "/Scripts/RegenerateInitFiles.py"])
if retval != 0:
    print("Error: failed to regenerate init files.")
    sys.exit(1)
sys.exit(0)


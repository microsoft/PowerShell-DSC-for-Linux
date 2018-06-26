#!/usr/bin/python
from sys import argv, stdout, version_info
from subprocess import Popen, PIPE
import os
import fcntl
import shutil
import stat
from imp import load_source
from xml.dom.minidom import parse
from os.path import basename, dirname, join, realpath, split

import datetime

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

operationStatusUtilityPath = join(pathToCommonScriptsFolder, 'OperationStatusUtility.py')
operationStatusUtility = load_source('operationStatusUtility', operationStatusUtilityPath)

operation = 'PerformInventory'

# Redirect output to our log file
fullPathDSCLogger = join(pathToCommonScriptsFolder, 'nxDSCLog.py')
nxDSCLog = load_source('nxDSCLog', fullPathDSCLogger)
logger = nxDSCLog.ConsoleAndFileLogger()
stdout = logger

def usage():
    operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Incorrect parameters to PerformInventory.py: ' + str(argv))
    print("""Usage: PerformInventory.py [OPTIONS]
OPTIONS (case insensitive):
 --InMOF PATH_TO_INVENTORY.MOF
 --OutXML PATH_TO_OUTPUT_REPORT.XML
 --help
""")

def get_current_timestamp():
    currentDateTime = datetime.datetime.now()
    currentDateTimeFormattedString = datetime.datetime.strftime(currentDateTime, "%Y/%m/%d %H:%M:%S")
    return currentDateTimeFormattedString

def exitWithError(message, errorCode = 1):
    timestamp = get_current_timestamp()
    errorMessage = timestamp + ": ERROR from PerformInventory.py: " + message
    print(errorMessage)
    exit(errorCode)

def printVerboseMessage(message):
    timestamp = get_current_timestamp()
    verboseMessage = timestamp + ": VERBOSE from PerformInventory.py: " + message
    print(verboseMessage)

def main(args):
    # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions
    if version_info >= (2, 6):
        main_py26to3(args)
    else:
        main_py24to27(args)

def main_py24to27(args):
    try:
        perform_inventory(args)
    except Exception, errorInstance:
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Python exception raised from PerformInventory.py: ' + str(errorInstance))
        raise errorInstance

def main_py26to3(args):
    try:
        perform_inventory(args)
    except Exception as errorInstance:
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Python exception raised from PerformInventory.py: ' + str(errorInstance))
        raise errorInstance

def perform_inventory(args):
    Variables = dict()

    # Parse command line arguments
    args = []
    optlist = []

    command_line_length = len(args)
    i = 0
    inArgument = False
    currentArgument = ""
    arg = ""
    while i < command_line_length:
        arg = args[i]
        if i == 0:
            # skip the program name
            i += 1
            continue

        if inArgument:
            Variables[currentArgument] = arg
            inArgument = False
        else:
            if arg[0:2] == "--":
                inArgument = True
                currentArgument = arg[2:].lower()
            else:
                # The rest are not options
                args = args[i:]
                break
        i += 1

    if inArgument:
        Variables[currentArgument] = arg

    AcceptableOptions = ["inmof", "outxml", "help"]

    if "help" in Variables:
        usage()
        exit(0)

    optionsValid = True
    for arg in Variables.keys():
        if arg.lower() not in AcceptableOptions:
            optionsValid = False
            exitWithError("Error: %s is not a valid option" % arg)

    if optionsValid == False:
        usage()
        exit(1)

    dsc_sysconfdir = join(helperlib.CONFIG_SYSCONFDIR, helperlib.CONFIG_SYSCONFDIR_DSC)
    dsc_reportdir = join(dsc_sysconfdir, 'InventoryReports')
    omicli_path = join(helperlib.CONFIG_BINDIR, 'omicli')
    dsc_configuration_path = join(dsc_sysconfdir, 'configuration')
    temp_report_path = join(dsc_configuration_path, 'Inventory.xml.temp')
    report_path = join(dsc_configuration_path, 'Inventory.xml')
    inventorylock_path = join(dsc_sysconfdir, 'inventory_lock')

    if "outxml" in Variables:
        report_path = Variables["outxml"]

    parameters = []
    parameters.append(omicli_path)
    parameters.append("iv")
    parameters.append(helperlib.DSC_NAMESPACE)
    parameters.append("{")
    parameters.append("MSFT_DSCLocalConfigurationManager")
    parameters.append("}")

    if "inmof" in Variables:
        parameters.append("PerformInventoryOOB")
        parameters.append("{")
        parameters.append("InventoryMOFPath")
        parameters.append(Variables["inmof"])
        parameters.append("}")
    else:
        parameters.append("PerformInventory")

    if len(dsc_sysconfdir) < 10:
        # something has gone wrong with the directory paths. error out before we attempt to remove the entire file system
        exitWithError("Error: Something has gone wrong with the directory paths. Exiting PerformInventory.")

    # If inventory lock files already exists update its permissions.
    if os.path.isfile(inventorylock_path):
        os.chmod(inventorylock_path , stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
        printVerboseMessage("Updated permissions of file: " + inventorylock_path + " to 0644")

    # open the inventory lock file, this also creates a file if it does not exist so we are using 644 permissions
    filehandle = os.open(inventorylock_path, os.O_WRONLY | os.O_CREAT , 0o644)
    printVerboseMessage("Opened file: " + inventorylock_path + " with permissions set to 0644")
    inventory_lock = os.fdopen(filehandle, 'w')

    # Acquire inventory file lock
    fcntl.flock(inventory_lock, fcntl.LOCK_EX)

    os.system("rm -f " + dsc_reportdir + "/*")

    # Save the starting timestamp
    startDateTime = datetime.datetime.now()
    startDateTimeStringNoMs = datetime.datetime.strftime(startDateTime, "%Y/%m/%d %H:%M:%S")
    startDateTimeNoMs = datetime.datetime.strptime(startDateTimeStringNoMs, '%Y/%m/%d %H:%M:%S')

    process = Popen(parameters, stdout = PIPE, stderr = PIPE)
    stdout, stderr = process.communicate()
    retval = process.returncode

    printVerboseMessage(stdout)

    if stderr == '':
        operationStatusUtility.write_success_to_status_file(operation)
    else:
        operationStatusUtility.write_failure_to_status_file(operation, startDateTimeNoMs, stderr)
        printVerboseMessage(stderr)

    # combine reports together
    reportFiles = os.listdir(dsc_reportdir)

    final_xml_report = '<INSTANCE CLASSNAME="Inventory"><PROPERTY.ARRAY NAME="Instances" TYPE="string" EmbeddedObject="object"><VALUE.ARRAY>'
    values = []
    for f in reportFiles:
        if not os.path.isfile(dsc_reportdir + "/" + f):
            continue
        d = parse(dsc_reportdir + "/" + f)
        for valueNode in d.getElementsByTagName('VALUE'):
            values.append(valueNode.toxml())

    final_xml_report = final_xml_report + "".join(values) + "</VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"

    with os.fdopen(os.open(temp_report_path, os.O_WRONLY | os.O_CREAT, 0o644), 'w') as filehandle:
        filehandle.write(final_xml_report)

    os.system("rm -f " + dsc_reportdir + "/*")
    shutil.move(temp_report_path, report_path)

    # Release inventory file lock
    fcntl.flock(inventory_lock, fcntl.LOCK_UN)
    inventory_lock.close()

    exit(retval)

if __name__ == "__main__":
    main(argv)

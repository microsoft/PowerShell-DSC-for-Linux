#!/usr/bin/python
from datetime   import datetime, timedelta
from imp        import load_source
from os         import chmod, mkdir, stat
from os.path    import dirname, join, isdir, isfile, realpath
from sys        import version_info

import re

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

def get_permission_in_oct(threeDigitString):
    # Python 2.4 and 3 recognize different formats for octal
    if version_info >= (3, 0):
        strMode = "0o" + threeDigitString
    else:
        strMode = "0" + threeDigitString

    octMode = int(strMode, base = 8)
    return octMode

def get_log_since_datetime(startDateTime):
    logSinceDateTime = ''
    foundStartDateTime = False

    logFileName = 'omsconfig.log'
    logFilePath = join(helperlib.PYTHON_PID_DIR, logFileName)

    print("Retrieving log with start datetime set to " + str(startDateTime))

    logFileHandle = open(logFilePath)
    try:
        for logFileLine in logFileHandle:
            if foundStartDateTime:
                print("Adding next line to message...")
                logFileLine = logFileLine.replace('"', '')
                logSinceDateTime += logFileLine
            else:
                # Find the timestamp in the line if present
                regexResult = re.search('\d{4}\/\d{2}\/\d{2}\s*\d{2}:\d{2}:\d{2}', logFileLine)
                if regexResult is not None:
                    lineTimestamp = regexResult.group(0)
                    print("Found a timestamp: " +  str(lineTimestamp))

                    # Parse the timestamp
                    lineDateTime = datetime.strptime(lineTimestamp, '%Y/%m/%d %H:%M:%S')

                    # Compare the parsed date to the desired date
                    if lineDateTime >= startDateTime:
                        print("Found a valid timestamp: " +  str(lineTimestamp))
                        foundStartDateTime = True
                        logFileLine = logFileLine.replace('"', '')
                        logSinceDateTime += logFileLine
    finally:
        logFileHandle.close()

    return logSinceDateTime

def get_status_file_content(operation, success, message = ''):
    return '''
{
    "operation": "Dsc''' + str(operation) + '''",
    "success": "''' + str(success) + '''",
    "message": "''' + str(message) + '''"
}
'''

def write_to_status_file(operation, success, message = ''):
    statusFolderName = 'status'
    statusFolderPath = join(helperlib.PYTHON_PID_DIR, statusFolderName)
    statusFolderDesiredPermission = get_permission_in_oct('755')

    # Ensure that the status folder exists
    if (not isdir(statusFolderPath)):
        mkdir(statusFolderPath, statusFolderDesiredPermission)

    # Ensure that the status folder has the correct permissions (755)
    statusFolderPermission = oct(stat(statusFolderPath).st_mode & statusFolderDesiredPermission)
    if (not (statusFolderPermission == "0755" or statusFolderPermission == "0o755")):
        chmod(statusFolderPath, statusFolderDesiredPermission)

    statusFileName = 'dsc' + operation.lower()
    statusFilePath = join(statusFolderPath, statusFileName)
    statusFileDesiredPermission = get_permission_in_oct('644')

    # Ensure that the status file has the correct permissions (644) if it exists before writing status
    if (isfile(statusFilePath)):
        statusFilePermission = oct(stat(statusFilePath).st_mode & statusFileDesiredPermission)
        if (not (statusFilePermission == "0644" or statusFilePermission == "0o644")):
            chmod(statusFilePath , statusFileDesiredPermission)

    statusFileContent = get_status_file_content(operation, success, message)

    statusFileHandle = open(statusFilePath, 'w')
    try:
        statusFileHandle.write(statusFileContent)
    finally:
        statusFileHandle.close()

    # Ensure that the status file has the correct permissions (644) if it exists after writing status
    if (isfile(statusFilePath)):
        statusFilePermission = oct(stat(statusFilePath).st_mode & statusFileDesiredPermission)
        if (not (statusFilePermission == "0644" or statusFilePermission == "0o644")):
            chmod(statusFilePath , statusFileDesiredPermission)

def write_success_to_status_file(operation):
    write_to_status_file(operation, True)

def write_failure_to_status_file_no_log(operation, errorMessage):
    write_to_status_file(operation, False, errorMessage)

def write_failure_to_status_file(operation, startDateTime, errorMessage):
    logSinceDateTime = get_log_since_datetime(startDateTime)
    errorMessageWithLog = errorMessage + '\n---LOG---\n' + logSinceDateTime
    write_to_status_file(operation, False, errorMessageWithLog)

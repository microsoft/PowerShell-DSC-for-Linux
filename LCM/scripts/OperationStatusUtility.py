#!/usr/bin/python
from datetime   import datetime
from imp        import load_source
from os         import chmod, mkdir, stat
from os.path    import dirname, join, isdir, isfile, realpath
from re         import search
from sys        import version_info

if hasattr(datetime, 'strptime'):
    # Only available in this module in Python 2.5+
    strptime = datetime.strptime
else:
    # Only for Python 2.4
    import time
    strptime = lambda date_string, format: datetime(*(time.strptime(date_string, format)[0:6]))

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

def get_current_time_no_ms():
    currentTimestamp = get_current_timestamp()
    currentTimeNoMS = strptime(currentTimestamp, '%Y/%m/%d %H:%M:%S')
    return currentTimeNoMS

def get_current_timestamp():
    currentDateTime = datetime.now()
    currentDateTimeFormattedString = datetime.strftime(currentDateTime, "%Y/%m/%d %H:%M:%S")
    return currentDateTimeFormattedString

def get_permission_in_oct(threeDigitString):
    # Python 2.4 and 3 recognize different formats for octal
    if version_info >= (3, 0):
        strMode = "0o" + threeDigitString
    else:
        strMode = "0" + threeDigitString

    octMode = int(strMode, base = 8)
    return octMode

def ensure_file_permissions(filePath, permissionString):
    desiredPermission = get_permission_in_oct(permissionString)

    # Ensure that the file has the desired permissions if it exists
    if (isfile(filePath)):
        filePermission = oct(stat(filePath).st_mode & desiredPermission)
        if (not (filePermission == desiredPermission)):
            chmod(filePath, desiredPermission)

def ensure_directory_permissions(directoryPath, permissionString):
    desiredPermission = get_permission_in_oct(permissionString)

    # Ensure that the file has the desired permissions if it exists
    if (isdir(directoryPath)):
        directoryPermission = oct(stat(directoryPath).st_mode & desiredPermission)
        if (not (directoryPermission == desiredPermission)):
            chmod(directoryPath, desiredPermission)

def get_log_since_datetime(startDateTime):
    logSinceDateTime = ''
    foundStartDateTime = False

    logFileName = 'omsconfig.log'
    logFilePath = join(helperlib.PYTHON_PID_DIR, logFileName)

    logFileHandle = open(logFilePath)
    try:
        for logFileLine in logFileHandle:
            if foundStartDateTime:
                logFileLine = logFileLine.replace('"', '')
                logSinceDateTime += logFileLine
            else:
                # Find the timestamp in the line if present
                regexResult = search('\d{4}\/\d{2}\/\d{2}\s*\d{2}:\d{2}:\d{2}', logFileLine)
                if regexResult is not None:
                    lineTimestamp = regexResult.group(0)

                    # Parse the timestamp
                    lineDateTime = strptime(lineTimestamp, '%Y/%m/%d %H:%M:%S')

                    # Compare the parsed date to the desired date
                    if lineDateTime >= startDateTime:
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

    # Ensure that the status folder exists
    if (not isdir(statusFolderPath)):
        mkdir(statusFolderPath)

    # Ensure that the status folder has the correct permissions (755)
    ensure_directory_permissions(statusFolderPath, '755')

    statusFileName = 'dsc' + operation.lower()
    statusFilePath = join(statusFolderPath, statusFileName)

    # Ensure that the status file has the correct permissions (644) if it exists before writing status
    ensure_file_permissions(statusFilePath, '644')

    statusFileContent = get_status_file_content(operation, success, message)

    statusFileHandle = open(statusFilePath, 'w')
    try:
        statusFileHandle.write(statusFileContent)
    finally:
        statusFileHandle.close()

    # Ensure that the status file has the correct permissions (644) if it exists after writing status
    ensure_file_permissions(statusFilePath, '644')

def write_success_to_status_file(operation):
    write_to_status_file(operation, True)

def write_failure_to_status_file_no_log(operation, errorMessage):
    write_to_status_file(operation, False, errorMessage)

def write_failure_to_status_file(operation, startDateTime, errorMessage):
    logSinceDateTime = get_log_since_datetime(startDateTime)
    errorMessageWithLog = errorMessage + '\n---LOG---\n' + logSinceDateTime
    write_to_status_file(operation, False, errorMessageWithLog)

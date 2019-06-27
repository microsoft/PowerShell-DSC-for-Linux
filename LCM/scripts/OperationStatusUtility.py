#!/usr/bin/python
from datetime   import datetime
from errno      import EINVAL
from imp        import load_source
from json       import dump
from os         import chmod, mkdir, stat
from os.path    import dirname, join, isdir, isfile, realpath
from re         import search
from sys        import exc_info, version_info

if hasattr(datetime, 'strptime'):
    # Only available in this module in Python 2.5+
    strptime = datetime.strptime
else:
    # Only for Python 2.4
    import time
    strptime = lambda date_string, format: datetime(*(time.strptime(date_string, format)[0:6]))

# Only for Python 2.4, otherwise you can import these from the os module
SEEK_SET = 0
SEEK_CUR = 1
SEEK_END = 2

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
    return str(currentDateTimeFormattedString)

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

def get_file_newline_char_in_bytes(filePath):
    newlineChar = ''

    # Get the newline character
    fileHandle = open(filePath, 'rU')
    try:
        firstLine = fileHandle.readline()
        if not firstLine:
            # File is empty
            return  
        
        newlineChar = fileHandle.newlines
    finally:
        fileHandle.close()

    if (version_info >= (3, 0)):
        newlineChar = newlineChar.encode()
    
    return newlineChar

def get_file_end_position(filePath):
    endFilePosition = None

    fileHandle = open(filePath, 'rb')
    try:
        fileHandle.seek(0, SEEK_END)
        endFilePosition = fileHandle.tell()
    finally:
        fileHandle.close()

    return endFilePosition

def get_file_position_and_num_lines_reading_file_up(filePath, newlineChar, startPosition = SEEK_END, minNumLinesToRead = 10, numBytesToRead = 32):
    fileHandle = open(filePath, 'rb')
    try:
        fileHandle.seek(startPosition, SEEK_SET)
        lineCount = 0
        filePosition = startPosition

        while lineCount <= minNumLinesToRead + 1:
            try:
                fileHandle.seek(-numBytesToRead, SEEK_CUR)
                lineCount += fileHandle.read(numBytesToRead).count(newlineChar)
                fileHandle.seek(-numBytesToRead, SEEK_CUR)
            except IOError:
                error = exc_info()[1]
                if error.errno == EINVAL:
                    # Attempted to seek past the start
                    numBytesToRead = fileHandle.tell()
                    fileHandle.seek(0, SEEK_SET)
                    lineCount += fileHandle.read(numBytesToRead).count(newlineChar)
                    filePosition = 0
                    break
                else:
                    raise
            filePosition = fileHandle.tell()
    finally:
        fileHandle.close()

    return filePosition, lineCount

def get_timestamp_file_position(filePath, startFilePosition, numLinesToRead, startDateTime):
    filePosition = None

    fileHandle = open(filePath, 'r')
    try:
        fileHandle.seek(startFilePosition, SEEK_SET)
        currentFilePosition = startFilePosition
        lineCount = 0

        while lineCount <= numLinesToRead:
            line = fileHandle.readline()
            if (test_line_timestamp_before_start(line, startDateTime)):
                filePosition = currentFilePosition
                
            lineCount += 1
            currentFilePosition = fileHandle.tell()
    finally:
        fileHandle.close()

    return filePosition

def test_line_timestamp_before_start(line, startDateTime):
    if not line:
        return False

    foundTimestampBeforeGiven = False

    regexResult = search('\d{4}\/\d{2}\/\d{2}\s*\d{2}:\d{2}:\d{2}', line)
    if regexResult is not None:
        lineTimestamp = regexResult.group(0)

        # Parse the timestamp
        lineDateTime = strptime(lineTimestamp, '%Y/%m/%d %H:%M:%S')

        # Compare the parsed date to the desired date
        if lineDateTime < startDateTime:
            foundTimestampBeforeGiven = True

    return foundTimestampBeforeGiven

def get_file_content_from_position(filePath, filePosition):
    fileContent = ''

    fileHandle = open(filePath, 'r')
    try:
        fileHandle.seek(filePosition, SEEK_SET)
        
        for line in fileHandle:
            fileContent += line
    finally:
        fileHandle.close()

    return fileContent

def get_log_since_datetime(startDateTime):
    logSinceDateTime = ''
    foundStartDateTime = False
    reachedTopOfFile = False

    logFileName = 'omsconfig.log'
    logFilePath = join(helperlib.PYTHON_PID_DIR, logFileName)

    if isfile(logFilePath):
        newlineChar = get_file_newline_char_in_bytes(logFilePath)
        filePosition = get_file_end_position(logFilePath)
        timeStampFilePosition = None

        while (filePosition != 0 and timeStampFilePosition is None):
            filePosition, numLinesRead = get_file_position_and_num_lines_reading_file_up(logFilePath, newlineChar, filePosition)
            timeStampFilePosition = get_timestamp_file_position(logFilePath, filePosition, numLinesRead, startDateTime)

        if (timeStampFilePosition is not None):
            logSinceDateTime = get_file_content_from_position(logFilePath, timeStampFilePosition)
        
    return logSinceDateTime

def get_status_file_content(operation, success, message = ''):
    escaped_message = message.replace('"', '\\"')
    status_file_content = {
        "operation": "Dsc" + str(operation),
        "success": str(success),
        "message": str(escaped_message)
    }

    return status_file_content

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
        dump(statusFileContent, statusFileHandle)
    finally:
        statusFileHandle.close()

    # Ensure that the status file has the correct permissions (644) if it exists after writing status
    ensure_file_permissions(statusFilePath, '644')

def write_to_status_to_log_file(operation, message = ''):
    logFilePath = join(helperlib.PYTHON_PID_DIR, 'omsconfig.log')

    # Ensure that the omsconfig.log file has the correct permissions (644) if it exists before writing log
    ensure_file_permissions(logFilePath, '644')

    timestamp = get_current_timestamp()
    logMessage = timestamp + ": operation: " + operation + ", message: " + message + "\n"

    logFileHandle = open(logFilePath, 'a')
    try:
        logFileHandle.write(logMessage)
    finally:
        logFileHandle.close()

    # Ensure that the status file has the correct permissions (644) if it exists after writing status
    ensure_file_permissions(logFilePath, '644')

def write_success_to_status_file(operation):
    write_to_status_file(operation, 'true', 'Succeeded')
    write_to_status_to_log_file(operation, 'Succeeded')

def write_failure_to_status_file_no_log(operation, errorMessage):
    write_to_status_file(operation, 'false', errorMessage)
    write_to_status_to_log_file(operation, errorMessage)

def write_failure_to_status_file(operation, startDateTime, errorMessage):
    logSinceDateTime = get_log_since_datetime(startDateTime)
    errorMessageWithLog = str(errorMessage) + '\n---LOG---\n' + str(logSinceDateTime)
    write_to_status_file(operation, False, errorMessageWithLog)

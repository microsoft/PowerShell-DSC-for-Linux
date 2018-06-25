#!/usr/bin/python
from imp            import load_source
from os.path        import dirname, join, realpath
from subprocess     import Popen
from sys            import version_info

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = imp.load_source('helperlib', helperLibPath)

def main():
    # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions
    if sys.version_info >= (2, 6):
        main_py26to3()
    else:
        main_py24to27()

def main_py24to27():
    try:
        run_perform_required_configuration_checks()
    except Exception, errorInstance:
        write_failure_to_status_file(errorInstance)
        raise errorInstance

def main_py26to3():
    try:
        run_perform_required_configuration_checks()
    except Exception as errorInstance:
        write_failure_to_status_file(errorInstance)
        raise errorInstance

def run_perform_required_configuration_checks():
    omicli_path = join(helperlib.CONFIG_BINDIR, 'omicli')

    parameters = []
    parameters.append(omicli_path)
    parameters.append("iv")
    parameters.append(helperlib.DSC_NAMESPACE)
    parameters.append("{")
    parameters.append("MSFT_DSCLocalConfigurationManager")
    parameters.append("}")
    parameters.append("PerformRequiredConfigurationChecks")
    parameters.append("{")
    parameters.append("Flags")
    parameters.append("1")
    parameters.append("}")

    p = subprocess.Popen(parameters, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = p.communicate()

    if stderr == '':
        write_success_to_status_file()
    else:
        write_failure_to_status_file(stderr)

    print(stdout)
    print(stderr)

def write_success_to_status_file():
    write_to_status_file('DscPerformRequiredConfigurationChecks', True, '')

def write_failure_to_status_file(errorMessage):
    write_to_status_file('DscPerformRequiredConfigurationChecks', False, errorMessage)

def write_to_status_file(operation, success, message):
    fileContent = get_status_file_content(operation, success, message)

    statusFileName = 'dsc' + operation.lower()
    statusFilePath = join(helperlib.PYTHON_PID_DIR, statusFileName)

    statusFileHandle = open(statusFilePath, 'w')
    try:
        statusFileHandle.write(fileContent)
    finally:
        statusFileHandle.close()

def get_status_file_content(operation, success, message):
    return '''
{
    "operation": "''' + str(operation) + '''",
    "success": "''' + str(success) + '''",
    "message": "''' + str(message) + '''"
}
'''

if __name__ == "__main__":
    main()

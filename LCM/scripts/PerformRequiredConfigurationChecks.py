#!/usr/bin/python
from imp            import load_source
from os.path        import dirname, join, realpath
from subprocess     import PIPE, Popen
from sys            import version_info

import datetime

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

operationStatusUtilityPath = join(pathToCommonScriptsFolder, 'OperationStatusUtility.py')
operationStatusUtility = load_source('operationStatusUtility', operationStatusUtilityPath)

operation = 'PerformRequiredConfigurationChecks'

def main():
    # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions
    if version_info >= (2, 6):
        main_py26to3()
    else:
        main_py24to27()

def main_py24to27():
    try:
        run_perform_required_configuration_checks()
    except Exception, errorInstance:
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Python exception raised from PerformRequiredConfigurationChecks.py: ' + str(errorInstance))
        raise errorInstance

def main_py26to3():
    try:
        run_perform_required_configuration_checks()
    except Exception as errorInstance:
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Python exception raised from PerformRequiredConfigurationChecks.py: ' + str(errorInstance))
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

    # Save the starting timestamp
    startDateTime = datetime.datetime.now()
    startDateTimeStringNoMs = datetime.datetime.strftime(startDateTime, "%Y/%m/%d %H:%M:%S")
    startDateTimeNoMs = datetime.datetime.strptime(startDateTimeStringNoMs, '%Y/%m/%d %H:%M:%S')

    process = Popen(parameters, stdout = PIPE, stderr = PIPE)
    stdout, stderr = process.communicate()

    print(stdout)

    if stderr == '':
        operationStatusUtility.write_success_to_status_file(operation)
    else:
        operationStatusUtility.write_failure_to_status_file(operation, startDateTimeNoMs, stderr)
        print(stderr)

if __name__ == "__main__":
    main()

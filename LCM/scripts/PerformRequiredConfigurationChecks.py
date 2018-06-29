#!/usr/bin/python
from imp            import load_source
from os.path        import dirname, join, realpath
from subprocess     import PIPE, Popen
from sys            import exc_info, version_info

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

operationStatusUtilityPath = join(pathToCommonScriptsFolder, 'OperationStatusUtility.py')
operationStatusUtility = load_source('operationStatusUtility', operationStatusUtilityPath)

operation = 'PerformRequiredConfigurationChecks'

def main():
    try:
        run_perform_required_configuration_checks()
    except Exception:
        # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions. This methods works in all versions.
        errorInstance = exc_info()
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Python exception raised from PerformRequiredConfigurationChecks.py: ' + str(errorInstance[1]))
        raise errorInstance[0], errorInstance[1], errorInstance[2]

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

    # Save the starting timestamp without milliseconds
    startDateTime = operationStatusUtility.get_current_time_no_ms()

    process = Popen(parameters, stdout = PIPE, stderr = PIPE)
    stdout, stderr = process.communicate()

    print(stdout)

    if stderr == '':
        operationStatusUtility.write_success_to_status_file(operation)
    else:
        operationStatusUtility.write_failure_to_status_file(operation, startDateTime, stderr)
        print(stderr)

if __name__ == "__main__":
    main()

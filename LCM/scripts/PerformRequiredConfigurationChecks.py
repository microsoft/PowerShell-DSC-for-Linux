#!/usr/bin/python
from imp        import load_source
from os.path    import dirname, join, realpath
from subprocess import PIPE, Popen
from sys        import exc_info, exit, version_info
from traceback  import format_exc

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

operationStatusUtilityPath = join(pathToCommonScriptsFolder, 'OperationStatusUtility.py')
operationStatusUtility = load_source('operationStatusUtility', operationStatusUtilityPath)

operation = 'PerformConsistency'

def main():
    try:
        run_perform_required_configuration_checks()
    except SystemExit:
        exit(exc_info()[1])
    except Exception:
        # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions. This methods works in all versions.
        formattedExceptionMessage = format_exc()
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Python exception raised from PerformRequiredConfigurationChecks.py: ' + formattedExceptionMessage)
        raise

def run_perform_required_configuration_checks():
    dsc_sysconfdir = join(helperlib.CONFIG_SYSCONFDIR, helperlib.CONFIG_SYSCONFDIR_DSC)
    # omicli_path = join(helperlib.CONFIG_BINDIR, 'omicli')
    dsc_host_path = join(helperlib.CONFIG_BINDIR, 'dsc_host')
    dsc_configuration_path = join(dsc_sysconfdir, 'configuration')

    parameters = []
    parameters.append(dsc_host_path)
    parameters.append(dsc_configuration_path) # output folder for dsc_host (not used yet)
    # parameters.append(omicli_path)
    # parameters.append("iv")
    # parameters.append(helperlib.DSC_NAMESPACE)
    # parameters.append("{")
    # parameters.append("MSFT_DSCLocalConfigurationManager")
    # parameters.append("}")
    parameters.append("PerformRequiredConfigurationChecks")
    # parameters.append("{")
    # parameters.append("Flags")
    parameters.append("1")
    # parameters.append("}")

    # Save the starting timestamp without milliseconds
    startDateTime = operationStatusUtility.get_current_time_no_ms()

    process = Popen(parameters, stdout = PIPE, stderr = PIPE)
    stdout, stderr = process.communicate()

    print(stdout)

    # Python 3 returns an empty byte array into stderr on success
    if stderr == '' or (version_info >= (3, 0) and stderr.decode(encoding = 'UTF-8') == ''):
        operationStatusUtility.write_success_to_status_file(operation)
    else:
        operationStatusUtility.write_failure_to_status_file(operation, startDateTime, stderr)
        print(stderr)

if __name__ == "__main__":
    main()

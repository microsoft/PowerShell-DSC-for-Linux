#!/usr/bin/python
from imp                  import load_source
from os.path              import dirname, isfile, join, realpath
from subprocess           import PIPE, Popen
from sys                  import argv, exc_info, exit, version_info
from traceback            import format_exc
from fcntl                import flock, LOCK_EX, LOCK_UN, LOCK_NB
from OmsConfigHostHelpers import write_omsconfig_host_telemetry, write_omsconfig_host_event, write_omsconfig_host_log
from time                 import sleep

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

operationStatusUtilityPath = join(pathToCommonScriptsFolder, 'OperationStatusUtility.py')
operationStatusUtility = load_source('operationStatusUtility', operationStatusUtilityPath)

operation = 'SetLCM'

def usage():
    print("Usage:")
    print("    " + argv[0] + " -configurationmof FILE")
    operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Incorrect parameters to SetDscLocalConfigurationManager.py: ' + str(argv))
    exit(1)

def main(args):
    try:
        apply_meta_config(args)
    except SystemExit:
        exit(exc_info()[1])
    except Exception:
        # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions. This methods works in all versions.
        formattedExceptionMessage = format_exc()
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Python exception raised from SetDscLocalConfigurationManager.py: ' + formattedExceptionMessage)
        raise

def apply_meta_config(args):
    if len(args) != 3:
        usage()

    if args[1].lower() != '-configurationmof':
        usage()

    if (not isfile(args[2])):
        errorMessage = 'The provided configurationmof file does not exist: ' + str(args[2])
        print(errorMessage)
        operationStatusUtility.write_failure_to_status_file_no_log(operation, 'Incorrect parameters to SetDscLocalConfigurationManager.py: ' + errorMessage)
        exit(1)

    fileHandle = open(args[2], 'r')
    try:
        fileContent = fileHandle.read()
        outtokens = []
        for char in fileContent:
            outtokens.append(str(ord(char)))

        omicli_path = join(helperlib.CONFIG_BINDIR, 'omicli')
        dsc_host_base_path = helperlib.DSC_HOST_BASE_PATH
        dsc_host_path = join(dsc_host_base_path, 'bin/dsc_host')
        dsc_host_output_path = join(dsc_host_base_path, 'output')
        dsc_host_lock_path = join(dsc_host_base_path, 'dsc_host_lock')
        dsc_host_switch_path = join(dsc_host_base_path, 'dsc_host_ready')

        if ("omsconfig" in helperlib.DSC_SCRIPT_PATH):
            write_omsconfig_host_event(pathToCurrentScript, isfile(dsc_host_switch_path))

        if ("omsconfig" in helperlib.DSC_SCRIPT_PATH) and (isfile(dsc_host_switch_path)):
            use_omsconfig_host = True
        else:
            use_omsconfig_host = False

        parameters = []

        if use_omsconfig_host:
            parameters.append(dsc_host_path)
            parameters.append(dsc_host_output_path)
            parameters.append("SendMetaConfigurationApply")
            parameters.append(args[2])
        else:
            parameters.append(omicli_path)
            parameters.append("iv")
            parameters.append(helperlib.DSC_NAMESPACE)
            parameters.append("{")
            parameters.append("MSFT_DSCLocalConfigurationManager")
            parameters.append("}")
            parameters.append("SendMetaConfigurationApply")
            parameters.append("{")
            parameters.append("ConfigurationData")
            parameters.append("[")
            # Insert configurationmof data here
            for token in outtokens:
                parameters.append(token)
            parameters.append("]")
            parameters.append("}")

        exit_code = 0

        # Save the starting timestamp without milliseconds
        startDateTime = operationStatusUtility.get_current_time_no_ms()

        # Apply the metaconfig
        if use_omsconfig_host:
            try:
                # Open the dsc host lock file. This also creates a file if it does not exist
                dschostlock_filehandle = open(dsc_host_lock_path, 'w')
                print("Opened the dsc host lock file at the path '" + dsc_host_lock_path + "'")
                
                dschostlock_acquired = False

                # Acquire dsc host file lock
                for retry in range(10):
                    try:
                        flock(dschostlock_filehandle, LOCK_EX | LOCK_NB)
                        dschostlock_acquired = True
                        break
                    except IOError:
                        write_omsconfig_host_log(pathToCurrentScript, 'dsc_host lock file not acquired. retry (#' + str(retry) + ') after 60 seconds...')
                        sleep(60)

                if dschostlock_acquired:
                    p = Popen(parameters, stdout=PIPE, stderr=PIPE)
                    exit_code = p.wait()
                    stdout, stderr = p.communicate()
                    print(stdout)
                else:
                    print("dsc host lock already acuired by a different process")
                    stdout = ''
                    stderr = ''
            finally:
                # Release dsc host file lock
                flock(dschostlock_filehandle, LOCK_UN)

                # Close dsc host lock file handle
                dschostlock_filehandle.close()
        else:
            p = Popen(parameters, stdout=PIPE, stderr=PIPE)
            exit_code = p.wait()
            stdout, stderr = p.communicate()

        print(stdout)

        if ((exit_code != 0) or (stderr)):
            exit(1)

        # Python 3 returns an empty byte array into stderr on success
        if stderr == '' or (version_info >= (3, 0) and stderr.decode(encoding = 'UTF-8') == ''):
            operationStatusUtility.write_success_to_status_file(operation)
            print("Successfully applied metaconfig.")
        else:
            operationStatusUtility.write_failure_to_status_file(operation, startDateTime, stderr)
            print(stderr)
    finally:
        fileHandle.close()

if __name__ == "__main__":
    main(argv)

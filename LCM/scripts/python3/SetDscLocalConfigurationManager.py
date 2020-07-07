#!/usr/bin/env python3
from imp                  import load_source
from os.path              import dirname, isfile, join, realpath
from subprocess           import PIPE, Popen
from sys                  import argv, exc_info, exit, version_info
from traceback            import format_exc
from fcntl                import flock, LOCK_EX, LOCK_UN, LOCK_NB
from OmsConfigHostHelpers import write_omsconfig_host_telemetry, write_omsconfig_host_switch_event, write_omsconfig_host_log, stop_old_host_instances
from time                 import sleep
import codecs 

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
    write_omsconfig_host_log('Incorrect parameters to SetDscLocalConfigurationManager.py: ' + str(argv), pathToCurrentScript, 'WARNING')
    exit(1)

def main(args):
    try:
        apply_meta_config(args)
    except SystemExit:
        exit(exc_info()[1])
    except Exception:
        # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions. This methods works in all versions.
        formattedExceptionMessage = format_exc()
        write_omsconfig_host_log('Python exception raised from SetDscLocalConfigurationManager.py: ' + formattedExceptionMessage, pathToCurrentScript, 'ERROR')
        raise

def apply_meta_config(args):
    if len(args) != 3:
        usage()



    if args[1].lower() != '-configurationmof':
        usage()

    if (not isfile(args[2])):
        errorMessage = 'The provided configurationmof file does not exist: ' + str(args[2])
        print(errorMessage)
        write_omsconfig_host_log('Incorrect parameters to SetDscLocalConfigurationManager.py: ' + errorMessage, pathToCurrentScript, 'ERROR')
        exit(1)

    fileHandle = open(args[2], 'rb')
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
            write_omsconfig_host_switch_event(pathToCurrentScript, isfile(dsc_host_switch_path))

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
        stdout = ''
        stderr = ''

        # Apply the metaconfig
        if use_omsconfig_host:
            try:
                dschostlock_filehandle = None
                stop_old_host_instances(dsc_host_lock_path)

                # Open the dsc host lock file. This also creates a file if it does not exist
                dschostlock_filehandle = open(dsc_host_lock_path, 'w')
                print("Opened the dsc host lock file at the path '" + dsc_host_lock_path + "'")
                
                dschostlock_acquired = False

                # Acquire dsc host file lock
                for retry in range(10):
                    try:
                        flock(dschostlock_filehandle, LOCK_EX | LOCK_NB)
                        write_omsconfig_host_log('dsc_host lock file is acquired by : SendMetaConfigurationApply', pathToCurrentScript)
                        dschostlock_acquired = True
                        break
                    except IOError:
                        write_omsconfig_host_log('dsc_host lock file not acquired. retry (#' + str(retry) + ') after 60 seconds...', pathToCurrentScript)
                        sleep(60)

                if dschostlock_acquired:
                    p = Popen(parameters, stdout=PIPE, stderr=PIPE)
                    exit_code = p.wait()
                    stdout, stderr = p.communicate()
                    stdout = stdout.decode() if isinstance(stdout, bytes) else stdout
                    print(stdout)
                else:
                    print("dsc host lock already acuired by a different process")
            finally:
                if dschostlock_filehandle:
                    # Release dsc host file lock
                    flock(dschostlock_filehandle, LOCK_UN)

                    # Close dsc host lock file handle
                    dschostlock_filehandle.close()
        else:
            p = Popen(parameters, stdout=PIPE, stderr=PIPE)
            exit_code = p.wait()
            stdout, stderr = p.communicate()

        stdout = stdout.decode() if isinstance(stdout, bytes) else stdout
        print(stdout)

        if ((exit_code != 0) or (stderr)):
            exit(1)

    finally:
        fileHandle.close()

if __name__ == "__main__":
    main(argv)

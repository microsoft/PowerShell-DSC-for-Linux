#!/usr/bin/python
from imp            import load_source
from os.path        import dirname, join, realpath
from subprocess     import PIPE, Popen
from sys            import argv, version_info

pathToCurrentScript = realpath(__file__)
pathToCommonScriptsFolder = dirname(pathToCurrentScript)

helperLibPath = join(pathToCommonScriptsFolder, 'helperlib.py')
helperlib = load_source('helperlib', helperLibPath)

operationStatusUtilityPath = join(pathToCommonScriptsFolder, 'OperationStatusUtility.py')
operationStatusUtility = load_source('operationStatusUtility', operationStatusUtilityPath)

operation = 'SetDscLocalConfigurationManager'

def usage():
    print("Usage:")
    print("    " + argv[0] + " -configurationmof FILE")
    operationStatusUtility.write_failure_to_status_file(operation, 'Incorrect parameters: ' + str(argv))
    exit(1)

def main(args):
    # Python 2.4-2.7 and 2.6-3 recognize different formats for exceptions
    if version_info >= (2, 6):
        main_py26to3(args)
    else:
        main_py24to27(args)

def main_py24to27(args):
    try:
        apply_meta_config(args)
    except Exception, errorInstance:
        operationStatusUtility.write_failure_to_status_file(operation, errorInstance)
        raise errorInstance

def main_py26to3(args):
    try:
        apply_meta_config(args)
    except Exception as errorInstance:
        operationStatusUtility.write_failure_to_status_file(operation, errorInstance)
        raise errorInstance

def apply_meta_config(args):
    if len(args) != 3:
        usage()

    if args[1].lower() != "-configurationmof":
        usage()

    try:
        filedata = open(args[2], "r").read()
    except:
        filedata = open(args[2], "r", encoding = "utf-16").read()

    outtokens = []
    for char in filedata:
        outtokens.append(str(ord(char)))

    omicli_path = join(helperlib.CONFIG_BINDIR, 'omicli')

    parameters = []
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


    # Apply the metaconfig
    process = Popen(parameters, stdout = PIPE, stderr = PIPE, close_fds = True)
    exit_code = process.wait()
    stdout, stderr = process.communicate()

    print(stdout)

    if stderr == '':
        operationStatusUtility.write_success_to_status_file(operation)
        print("Successfully applied metaconfig.")
    else:
        operationStatusUtility.write_failure_to_status_file(operation, stderr)
        print(stderr)

    if ((exit_code != 0) or (stderr)):
        exit(1)

if __name__ == "__main__":
    main(argv)

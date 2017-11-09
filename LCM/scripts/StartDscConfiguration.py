#!/usr/bin/python

# Standard library imports
from subprocess import Popen, PIPE
from sys import argv

try:
    # Used by Python 2.7+
    from argparse import ArgumentParser
    useArgParse = True
except:
    # Used by Python 2.4-2.6
    from optparse import OptionParser
    useArgParse = False

def main(argv):
    """StartDscConfiguration"""

    # Define method arguments and description
    description = 'Starts the specified DSC configuration.'

    parameters = {
        'configurationmof' : {
            'shortForm' : 'c',
            'helpText' : 'The path to the configuration mof to start.',
            'required' : True,
            'action' : 'store'
        },
        'force' : {
            'shortForm' : 'f',
            'helpText' : 'Specifies that any current pending configuration should be forcibly removed before starting the new configuration.',
            'required' : False,
            'action' : 'store_true'
        }
    }

    # Parse -configurationmof on its own for backwards compatibility
    configmofArgument = None
    if '-configurationmof' in argv:
        configmofIndex = argv.index('-configurationmof')

        try:
            configmofArgument = argv[configmofIndex + 1]
        except:
            print 'StartDscConfiguration.py: error: Please provide a valid path argument for -configurationmof'
            exit(1)

        # Set the configuration mof parameter to no longer be required so it doesn't error in the arugment parser
        parameters['configurationmof']['required'] = False 

        # Remove -configurationmof and its argument from the list so it doesn't error in the arugment parser
        argv.pop(configmofIndex)
        argv.pop(configmofIndex)

    # Parse arguments
    if (useArgParse):
        # Used by Python 2.7+
        parser = ArgumentParser(description = description)

        for parameter in parameters.keys():
            parameterInfo = parameters[parameter]
            parser.add_argument('-' + parameterInfo['shortForm'], '--' + parameter, required = parameterInfo['required'], help = parameterInfo['helpText'], action = parameterInfo['action'])

        parsedArguments = parser.parse_args(argv)
    else:
        # Used by Python 2.4-2.6
        parser = OptionParser(description = description)

        for parameter in parameters.keys():
            parameterInfo = parameters[parameter]
            parser.add_option('-' + parameterInfo['shortForm'], '--' + parameter, help = parameterInfo['helpText'], action = parameterInfo['action'])

        (parsedArguments, extraArguments) = parser.parse_args(argv)

        for parameter in parameters.keys():
            if parameters[parameter]['required']:
                if not getattr(parsedArguments, parameter):
                    print 'StartDscConfiguration.py: error: argument -' + parameters[parameter]['shortForm'] + '/--' + parameter + ' is required.'
                    exit(1)

    # Check that we don't have two configuration mofs defined
    if configmofArgument and parsedArguments.configurationmof:
        print 'StartDscConfiguration.py: error: Two configuration mof arguments were found. Please provide only one.'
        exit(1)
    
    if configmofArgument:
        parsedArguments.configurationmof = configmofArgument

    # Read the configuration mof
    try:
        configurationFile = open(parsedArguments.configurationmof, 'r')
    except:
        configurationFile = open(parsedArguments.configurationmof, 'r', encoding = 'utf-16')

    try:
        configurationFileContent = configurationFile.read()
    finally:
        configurationFile.close()

    # Convert the file content to strings of integers representing unicode
    configurationData = []
    for char in configurationFileContent:
        configurationData.append(str(ord(char)))

    # OMI CLI location
    omiBinDir = "<CONFIG_BINDIR>"
    omiCliPath = omiBinDir + "/omicli"

    # Assemble parameters to pass to OMI CLI
    omiCliParameters = []
    omiCliParameters.append(omiCliPath)
    omiCliParameters.append("iv")
    omiCliParameters.append("<DSC_NAMESPACE>")
    omiCliParameters.append("{")
    omiCliParameters.append("MSFT_DSCLocalConfigurationManager")
    omiCliParameters.append("}")
    omiCliParameters.append("SendConfigurationApply")
    omiCliParameters.append("{")
    omiCliParameters.append("ConfigurationData")
    omiCliParameters.append("[")

    # Insert configurationmof data here
    for token in configurationData:
        omiCliParameters.append(token)
    
    omiCliParameters.append("]")

    # Insert force if specified
    if parsedArguments.force:
        omiCliParameters.append("force")
        omiCliParameters.append("true")

    omiCliParameters.append("}")

    # Call OMI CLI in subprocess
    omiCliProcess = Popen(omiCliParameters, stdout = PIPE, stderr = PIPE)

    # Retrieve stdout and stderr from OMI CLI call
    stdout, stderr = omiCliProcess.communicate()

    # Print output from OMI CLI call
    print(stdout)
    print(stderr)

main(argv[1:])

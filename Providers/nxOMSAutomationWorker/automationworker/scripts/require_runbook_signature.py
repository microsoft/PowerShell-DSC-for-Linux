from optparse import OptionParser
import os
import sys
import ConfigParser
# append worker binary source path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# since we are using the worker httpclient, some configuration values are expected
from worker import configuration

WORKSPACE_ID_PLACEHOLDER = "<workspace_id>"
DIY_WORKER_CONFIG_FILE_LOCATION_PATTERN = "/var/opt/microsoft/omsagent/" + WORKSPACE_ID_PLACEHOLDER + "/state/automationworker/diy/worker.conf"


def get_config_file_path(workspace_id):
    return DIY_WORKER_CONFIG_FILE_LOCATION_PATTERN.replace(WORKSPACE_ID_PLACEHOLDER, workspace_id)

def set_signature_enforcement_policy(config_file_path, node_locked):
    if os.path.isfile(config_file_path) is False:
        sys.stderr.write("Could not find DIY automation worker configuration file\nPlease check if the DIY automation worker is registered for the specified workspace\n")
        sys.exit(1)

    worker_optional_section = configuration.WORKER_OPTIONAL_CONFIG_SECTION
    enforce_runbook_signature_validation = configuration.ENFORCE_RUNBOOK_SIGNATURE_VALIDATION

    config = ConfigParser.ConfigParser()
    config.read(config_file_path)
    config.set(worker_optional_section, enforce_runbook_signature_validation, node_locked)
    config_file_handle = open(config_file_path, 'wb')
    config.write(config_file_handle)
    config_file_handle.close()

    # Verify that the entry was made
    config.read(config_file_path)
    assert config.get(worker_optional_section, enforce_runbook_signature_validation).__eq__(node_locked)


def main():
    if os.getuid() != 0:
        raise Exception("You need to run this script as root.")
    parser = OptionParser(usage="usage: %prog ( --true | --false ) workspace_id")
    parser.add_option("-t", "--true", dest="t", action="store_true", default=False, help="Require runbooks to be signed for execution on this host")
    parser.add_option("-f", "--false", dest="f", action="store_true", default=False, help="Do not require runbooks to be signed for execution on this host")
    (options, args) = parser.parse_args()
    if options.f is True and options.t is True:
        # Both options should not be true at the same time
        parser.print_help(sys.stderr)
        sys.stderr.write("Both \"--true\" and \"--false\" options cannot be selected at the same time.\n")
        sys.exit(1)
    if options.f is False and options.t is False:
        parser.print_help(sys.stderr)
        sys.stderr.write("Please select at least one of \"--true\" or \"--false\" options.\n")
        sys.exit(1)
    if len(args) != 1:
        parser.print_help(sys.stderr)
        sys.stderr.write("Please specify only one and only one workspace id.\n")
        sys.exit(1)
    workspace_id = args[0]
    config_file_path = get_config_file_path(workspace_id)
    if options.f is True:
        set_signature_enforcement_policy(config_file_path, False)
        print "Successfully configured this host to execute both signed and unsigned runbooks."
    elif options.t is True:
        set_signature_enforcement_policy(config_file_path, True)
        print "Successfully configured this host to execute signed runbook exclusively."


if __name__ == "__main__":
    main()


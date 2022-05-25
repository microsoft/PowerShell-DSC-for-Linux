#!/usr/bin/env python3
# ====================================
# Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================
import sys
import os
import configuration
import ConfigParser
import time

def exit_on_error(message, exit_code=1):
    print str(message)
    try:
        os.chdir(os.path.expanduser("~"))
        open("automation_worker_crash.log", "w").write(message)
    except:
        pass
    sys.exit(exit_code)

def generate_state_file():
    state_file_name = "state.conf"
    if configuration.get_state_directory_path() == configuration.DEFAULT_STATE_DIRECTORY_PATH:
        state_file_path = os.path.join(configuration.get_working_directory_path(), state_file_name)
    else:
        state_file_path = os.path.join(configuration.get_state_directory_path(), state_file_name)

    if os.path.isfile(state_file_path):
        os.remove(state_file_path)

    section = "state"
    conf_file = open(state_file_path, 'wb')
    config = ConfigParser.ConfigParser()
    config.add_section(section)
    config.set(section, configuration.STATE_PID, str(os.getpid()))
    config.set(section, configuration.WORKER_VERSION, str(configuration.get_worker_version()))

    # for OMS scenarios, optional for DIY
    if len(sys.argv) >= 3:
        config.set(section, configuration.STATE_WORKSPACE_ID, str(sys.argv[2]))

    if len(sys.argv) >= 4:
        config.set(section, configuration.STATE_RESOURCE_VERSION, str(sys.argv[3]))

    config.write(conf_file)
    conf_file.close()

def main():
    if len(sys.argv) < 2:
        exit_on_error("Invalid configuration file path (absolute path is required).")
    configuration_path = sys.argv[1]

    if not os.path.isfile(configuration_path):
        exit_on_error("Invalid configuration file path (absolute path is required).")

    # configuration has to be read first thing
    try:
        # remove the test_mode env_var value (mainly for Windows)
        # this value is set in test
        del os.environ["test_mode"]
    except KeyError:
        pass
    worker_dir = os.path.dirname(os.path.realpath(__file__))
    config_path = os.path.join(worker_dir, configuration_path)
    configuration.read_and_set_configuration(config_path)
    configuration.set_config({configuration.COMPONENT: "worker"})
    # do not trace anything before this point

    generate_state_file()

    # start a non terminating job
    while (True):
        time.sleep(60)


if __name__ == "__main__":
    main()

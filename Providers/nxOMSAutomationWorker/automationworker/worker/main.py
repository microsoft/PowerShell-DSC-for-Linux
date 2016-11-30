#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import ConfigParser
import os
import subprocess
import sys
import threading
import time
import traceback

import configuration
import iohelper
import subprocessfactory
import tracer
from httpclientfactory import HttpClientFactory
from jrdsclient import JRDSClient


def safe_loop(func):
    def decorated_func(*args, **kwargs):
        while True:
            try:
                func(*args, **kwargs)
            except Exception:
                tracer.log_exception_trace(traceback.format_exc())
            time.sleep(configuration.get_jrds_get_sandbox_actions_polling_freq())

    return decorated_func


def background_thread(func):
    def decorated_func(*args, **kwargs):
        t = threading.Thread(target=func, args=args)
        t.start()

    return decorated_func


def exit_on_error(message, exit_code=1):
    print str(message)
    try:
        os.chdir(os.path.expanduser("~"))
        open("automation_worker_crash.log", "w").write(message)
    except:
        pass
    sys.exit(exit_code)


def test_file_creation(path):
    try:
        iohelper.write_to_file(path, path)
        os.remove(path)
        return True
    except IOError:
        return False


def validate_and_setup_path():
    # default to user dir for exception logs to be writen to disk
    test_file_name = "test_file"

    # test certificate and key path
    if not os.path.isfile(configuration.get_jrds_cert_path()) or not os.path.isfile(configuration.get_jrds_key_path()):
        exit_on_error("Invalid certificate of key file path (absolute path is required).")

    # test working dirextory for existance and permissions
    if not os.path.exists(configuration.get_working_directory_path()):
        exit_on_error("Invalid working directory path (absolute path is required).")
    file_creation = test_file_creation(os.path.join(configuration.get_working_directory_path(), test_file_name))
    if file_creation is False:
        exit_on_error("Invalid working directory permission (read/write permissions are required).")

    # test keyring paths
    keyring_path = configuration.get_gpg_public_keyring_path()
    if keyring_path != configuration.DEFAULT_GPG_PUBLIC_KEYRING_PATH and not os.path.isfile(keyring_path):
        exit_on_error("Invalid gpg public keyring path (absolute path is required).")

    # test state file path
    if configuration.get_state_directory_path() != configuration.DEFAULT_STATE_DIRECTORY_PATH:
        if not os.path.exists(configuration.get_state_directory_path()):
            exit_on_error("Invalid state directory path (absolute path is required).")

        file_creation = test_file_creation(os.path.join(configuration.get_state_directory_path(), test_file_name))
        if file_creation is False:
            exit_on_error("Invalid state directory permission (read/write permissions are required).")


def generate_state_file():
    state_file_name = "state.conf"
    if configuration.get_state_directory_path() == configuration.DEFAULT_STATE_DIRECTORY_PATH:
        state_file_path = os.path.join(configuration.get_working_directory_path(), state_file_name)
    else:
        state_file_path = os.path.join(configuration.get_state_directory_path(), state_file_name)

    tracer.log_debug_trace("State file path : " + str(state_file_path))

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


class Worker:
    def __init__(self):
        tracer.log_worker_starting(configuration.get_worker_version())
        http_client_factory = HttpClientFactory(configuration.get_jrds_cert_path(), configuration.get_jrds_key_path(),
                                                configuration.get_verify_certificates())
        http_client = http_client_factory.create_http_client(sys.version_info)
        self.jrds_client = JRDSClient(http_client)
        self.running_sandboxes = {}

    @safe_loop
    def routine(self):
        self.stop_tracking_terminated_sandbox()

        sandbox_actions = self.jrds_client.get_sandbox_actions()
        tracer.log_debug_trace("Get sandbox action. Found " + str(len(sandbox_actions)) + " action(s).")

        for action in sandbox_actions:
            tracer.log_worker_sandbox_action_found(len(sandbox_actions))
            sandbox_id = str(action["SandboxId"])

            # prevent duplicate sandbox from running
            if sandbox_id in self.running_sandboxes:
                return

            # create sandboxes folder if needed
            sandboxes_base_path = "sandboxes"
            sandbox_working_dir = os.path.join(configuration.get_working_directory_path(), sandboxes_base_path,
                                               sandbox_id)

            try:
                iohelper.assert_or_create_path(sandbox_working_dir)
            except OSError:
                tracer.log_debug_trace("Failed to create sandbox folder.")
                pass

            # copy current process env variable (contains configuration) and add the sanbox_id key
            process_env_variables = os.environ.copy()
            process_env_variables["sandbox_id"] = sandbox_id

            cmd = ["python", os.path.join(configuration.get_source_directory_path(), "sandbox.py")]
            sandbox_process = subprocessfactory.create_subprocess(cmd=cmd,
                                                                  env=process_env_variables,
                                                                  stdout=subprocess.PIPE,
                                                                  stderr=subprocess.PIPE,
                                                                  cwd=sandbox_working_dir)
            self.running_sandboxes[sandbox_id] = sandbox_process
            self.monitor_sandbox_process_outputs(sandbox_id, sandbox_process)
            tracer.log_worker_starting_sandbox(sandbox_id, str(sandbox_process.pid))

    @background_thread
    def monitor_sandbox_process_outputs(self, sandbox_id, process):
        while process.poll() is None:
            output = process.stdout.readline().replace("\n", "")
            if output == '':
                continue
            if output != '':
                tracer.log_sandbox_stdout(output)

        if process.poll() != 0:
            full_error_output = ""
            while True:
                error_output = process.stderr.readline()
                if error_output is None or error_output == '':
                    break
                full_error_output += error_output
            tracer.log_debug_trace("Sandbox crashed : " + str(full_error_output))

        tracer.log_worker_sandbox_process_exited(sandbox_id, str(process.pid), process.poll())

    def stop_tracking_terminated_sandbox(self):
        terminated_sandbox_ids = []

        # detect terminated sandboxes
        for sandbox_id, sandbox_process in self.running_sandboxes.items():
            if sandbox_process.poll() is not None:
                terminated_sandbox_ids.append(sandbox_id)

        # clean-up terminated sandboxes
        for sandbox_id in terminated_sandbox_ids:
            removal = self.running_sandboxes.pop(sandbox_id, None)
            if removal is not None:
                tracer.log_debug_trace("Worker stopped tracking sandbox : " + str(sandbox_id))


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
    validate_and_setup_path()
    # do not trace anything before this point

    generate_state_file()
    worker = Worker()
    worker.routine()


if __name__ == "__main__":
    main()

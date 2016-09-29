#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Tracer module."""

import inspect
import logging
import logging.handlers
import os
import random
import sys
import threading
import time
import traceback

import configuration
from httpclientfactory import HttpClientFactory
from jrdsclient import JRDSClient

jrds_client = None
jrds_cert_path = None
jrds_key_path = None
jrds_base_uri = None
subscription_id = None
account_id = None
machine_id = None
hybrid_worker_group_name = None
worker_version = None
activity_id = None

default_logger = None
sandbox_stdout = None


def safe_trace(func):
    def decorated_func(*args, **kwargs):
        try:
            func(*args, **kwargs)
        except Exception:
            if default_logger is None:
                print traceback.format_exc()
                print "Logger not defined."
            else:
                default_logger.critical(traceback.format_exc())
    return decorated_func


def background_thread(func):
    def decorated_func(*args, **kwargs):
        t = threading.Thread(target=func, args=args)
        t.start()
    return decorated_func


def init():
    """Initializes all required variable for the tracer."""
    global default_logger, sandbox_stdout, jrds_client, jrds_cert_path, jrds_key_path, jrds_base_uri, subscription_id,\
        account_id, machine_id, hybrid_worker_group_name, worker_version, activity_id

    # Create the http client
    http_client_factory = HttpClientFactory(configuration.get_jrds_cert_path(), configuration.get_jrds_key_path())
    http_client = http_client_factory.create_http_client(sys.version_info, configuration.get_verify_certificates())
    jrds_client = JRDSClient(http_client)

    # Populate global configuration values
    jrds_cert_path = configuration.get_jrds_cert_path()
    jrds_key_path = configuration.get_jrds_key_path()
    jrds_base_uri = configuration.get_jrds_base_uri()
    subscription_id = "00000000-0000-0000-0000-000000000000" # temporary place holder
    account_id = configuration.get_account_id()
    machine_id = configuration.get_machine_id()
    hybrid_worker_group_name = configuration.get_hybrid_worker_name()
    worker_version = configuration.get_worker_version()
    activity_id = generate_activity_id()

    sandbox_id = None
    try:
        sandbox_id = os.environ["sandbox_id"]
    except KeyError:
        pass

    if sandbox_id is not None:
        log_file_name = configuration.get_component() + sandbox_id
    else:
        log_file_name = configuration.get_component()

    file_name = os.path.join(configuration.get_working_directory_path(), log_file_name + '.log')
    logging.Formatter.converter = time.gmtime

    # Default logger
    default_logger = logging.getLogger("default_logger")
    default_logger.setLevel(logging.INFO)

    # Logger for the sandbox traces coming back to worker
    sandbox_stdout = logging.getLogger("sandbox_stdout_logger")
    sandbox_stdout.setLevel(logging.INFO)

    # Default rotating file handler write traces with the specified format to disk.
    default_rf_handler = logging.handlers.RotatingFileHandler(file_name, maxBytes=10485760, backupCount=5)
    formatter = logging.Formatter('%(asctime)s (' + str(os.getpid()) + ')' + configuration.get_component() +
                                  ' : %(message)s', datefmt="%Y-%m-%d %H:%M:%S")
    default_rf_handler.setFormatter(formatter)
    default_logger.addHandler(default_rf_handler)

    # Traces coming from sandbox child process and collected by the worker are already formatted, hence no formatter
    # needed.
    worker_sandbox_rf_handler = logging.handlers.RotatingFileHandler(file_name, maxBytes=10485760, backupCount=5)
    sandbox_stdout.addHandler(worker_sandbox_rf_handler)

    # Stdout handler (Worker traces have to be formatted).
    log_stream = logging.StreamHandler(sys.stdout)
    log_stream.setFormatter(formatter)
    default_logger.addHandler(log_stream)

    # Stdout handler (traces coming from child process are already formatted).
    sandbox_log_stream = logging.StreamHandler(sys.stdout)
    sandbox_stdout.addHandler(sandbox_log_stream)


@background_thread
@safe_trace
def trace(event_id, task_name, message, t_id, keyword, debug=False):
    """Write the trace to STDOUT / log file (on disk) / to MDS (in the cloud).

    Note:
        This method run in a background thread.

    Args:
        event_id    : int   , the event id. This event id doesn't have to map to an ETW event id in the cloud.
        task_name   : string, the task name.
        message     : string, the message.
        t_id        : int   , the thread id.
        keyword     : string, the keyword.
    """
    # # # # # # # # # # # # # # # # # # # #
    # for tests, disregard tracer
    if os.getenv('test_mode', None) is not None:
        return
    # # # # # # # # # # # # # # # # # # # #

    if jrds_client is None or default_logger is None:
        init()

    if debug and not configuration.get_debug_traces():
        return

    if task_name.startswith("log"):
        task_name = "_".join(task_name.split("_")[1:])
    task_name = task_name.title().replace("_", "")

    if isinstance(message, dict):
        message = dict_to_str(message)

    # local trace
    default_logger.info(message)

    # MDS
    if not debug:
        issue_jrds_trace(event_id, task_name, message, t_id, keyword)


def issue_jrds_trace(event_id, task_name, message, t_id, keyword):
    """Send the trace to MDS (in the cloud) using the JRDS api.

    Args:
        event_id    : int   , the event id. This event id doesn't have to map to an ETW event id in the cloud.
        task_name   : string, the task name.
        message     : string, the message.
        t_id        : int   , the thread id.
        keyword     : string, the keyword.
    """
    u_activity_id = generate_activity_id()

    # The local trace is converted into the "GenericHybridWorker" trace in the cloud (eventId: 16000).
    # For this reason, this trace has to follow the JRDS TraceEventSource.cs event's signature contract
    # for eventId 16000.
    cloud_trace_format = [account_id,
                          subscription_id,
                          hybrid_worker_group_name,
                          machine_id,
                          configuration.get_component(),
                          event_id,
                          task_name,
                          keyword,
                          t_id,
                          os.getpid(),
                          u_activity_id,
                          worker_version,
                          message]
    jrds_client.set_log(16000, u_activity_id, 0, map(str, cloud_trace_format))


def dict_to_str(input_dict):
    output_str = ""
    for key, value in input_dict.iteritems():
        output_str = output_str + "[" + str(key) + "=" + str(value) + "]"
    return output_str


def generate_activity_id():
    """ UUID module isn't available in python 2.4. Since activity id are only required for tracing this is enough.

    Returns: string, an activity id which has a GUID format
    """
    uuid = [random.randint(10000000, 99999999),
            random.randint(1000, 9999),
            random.randint(1000, 9999),
            random.randint(1000, 9999),
            random.randint(100000000000, 999999999999)]
    return '-'.join(map(str, uuid))


COMPONENT_SANDBOX = "Sandbox"
COMPONENT_WORKER = "Worker"

KEYWORD_DEBUG = "Debug"
KEYWORD_INFO = "Info"
KEYWORD_ERROR = "Error"
KEYWORD_STARTUP = "Startup"
KEYWORD_ROUTINE = "Routine"
KEYWORD_CONFIGURATION = "Configuration"


# general traces
# traces in this section may be used in all worker components (worker, sandbox, etc)
def log_debug_trace(message):
    message = "[DEBUG] " + message
    trace(1, inspect.stack()[0][3], message, 1, KEYWORD_DEBUG, True)


def log_informational_trace(message):
    trace(2, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_exception_trace(stacktrace):
    message = "Exception encountered. \n" + stacktrace
    trace(3, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


# worker specific traces
# traces in this section are mainly for the worker component
def log_sandbox_stdout(trace_content):
    sandbox_stdout.info(trace_content)


def log_worker_starting(version):
    message = "Worker starting. [WorkerVersion=" + str(version) + "]"
    trace(4, inspect.stack()[0][3], message, 1, KEYWORD_STARTUP)


def log_worker_sandbox_action_found(sandbox_actions):
    message = "Get sandbox actions found " + str(sandbox_actions) + " new action(s)."
    trace(5, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


def log_worker_starting_sandbox(sandbox_id, pid):
    message = "Starting sandbox process. [SandboxId=" + str(sandbox_id) + "][PID=" + str(pid) + "]"
    trace(6, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


def log_worker_sandbox_process_exited(sandbox_id, pid, exit_code):
    message = "Sandbox process exited. [SandboxId=" + str(sandbox_id) + "][PID=" + str(pid) + "][ExitCode=" + \
              str(exit_code) + "]"
    trace(7, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


# sandbox specific traces
# traces in this section are mainly for the sandbox component
def log_sandbox_starting(sandbox_id, pid):
    message = "Starting sandbox process. [SandboxId=" + str(sandbox_id) + "][PID=" + str(pid) + "]"
    trace(8, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


def log_sandbox_get_job_actions(job_actions):
    message = "Get job actions. Found " + str(job_actions) + " new action(s)."
    trace(9, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)

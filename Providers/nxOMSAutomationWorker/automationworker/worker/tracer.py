#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Tracer module."""

import inspect
import logging
import logging.handlers
import os
import sys
import threading
import time
import traceback

import configuration
from httpclientfactory import HttpClientFactory
from jrdsclient import JRDSClient
import util

jrds_client = None
jrds_cert_path = None
jrds_key_path = None
jrds_base_uri = None
subscription_id = None
account_id = None
machine_id = None
hybrid_worker_group_name = None
worker_version = None
sandbox_id = None

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
        t.daemon = True
        t.start()

    return decorated_func


def init():
    """Initializes all required variable for the tracer."""
    global default_logger, sandbox_stdout, jrds_client, jrds_cert_path, jrds_key_path, jrds_base_uri, subscription_id, \
        account_id, machine_id, hybrid_worker_group_name, worker_version, activity_id, sandbox_id

    # Create the http client
    http_client_factory = HttpClientFactory(configuration.get_jrds_cert_path(), configuration.get_jrds_key_path(),
                                            configuration.get_verify_certificates())
    http_client = http_client_factory.create_http_client(sys.version_info)
    jrds_client = JRDSClient(http_client)

    # Populate global configuration values
    jrds_cert_path = configuration.get_jrds_cert_path()
    jrds_key_path = configuration.get_jrds_key_path()
    jrds_base_uri = configuration.get_jrds_base_uri()
    subscription_id = "00000000-0000-0000-0000-000000000000"  # temporary place holder
    account_id = configuration.get_account_id()
    machine_id = configuration.get_machine_id()
    hybrid_worker_group_name = configuration.get_hybrid_worker_name()
    worker_version = configuration.get_worker_version()

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
def trace_generic_hybrid_worker_event(event_id, task_name, message, t_id, keyword, debug=False):
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
    # we prioritize cloud traces, do not raise exception if local tracing raises an exception
    try:
        default_logger.info(message)
    except Exception, e:
        print str(e)
        pass

    # MDS
    if not debug:
        format_and_issue_generic_hybrid_worker_trace(event_id, task_name, message, t_id, keyword)


@background_thread
@safe_trace
def trace_etw_event(event_id, message, activity_id, log_type, arg_array):
    """Write the trace to STDOUT / log file (on disk) / to MDS (in the cloud).

    Note:
        This method run in a background thread.

    Args:
        event_id    : int   , the event id. This event id doesn't have to map to an ETW event id in the cloud.
        message     : string, the message.
        activity_id : string, the activiti id.
        log_type    : int   , the log type.
        arg_array   : string, the argument array.
    """
    # # # # # # # # # # # # # # # # # # # #
    # for tests, disregard tracer
    if os.getenv('test_mode', None) is not None:
        return
    # # # # # # # # # # # # # # # # # # # #

    if jrds_client is None or default_logger is None:
        init()

    if isinstance(message, dict):
        message = dict_to_str(message)

    # local trace
    # we prioritize cloud traces, do not raise exception if local tracing raises an exception
    try:
        default_logger.info(message)
    except Exception, e:
        print str(e)
        pass

    # MDS
    issue_jrds_trace(event_id, activity_id, log_type, arg_array)


def format_and_issue_generic_hybrid_worker_trace(event_id, task_name, message, t_id, keyword):
    """Send the trace to MDS (in the cloud) using the JRDS api.

    Args:
        event_id    : int   , the event id. This event id doesn't have to map to an ETW event id in the cloud.
        task_name   : string, the task name.
        message     : string, the message.
        t_id        : int   , the thread id.
        keyword     : string, the keyword.
    """
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
    issue_jrds_trace(16000, u_activity_id, 0, cloud_trace_format)


def issue_jrds_trace(event_id, activity_id, log_type, arg_array):
    jrds_client.set_log(event_id, activity_id, log_type, map(str, arg_array))


def dict_to_str(input_dict):
    output_str = ""
    for key, value in input_dict.iteritems():
        output_str = output_str + "[" + str(key) + "=" + str(value) + "]"
    return output_str


u_activity_id = util.generate_uuid()

COMPONENT_SANDBOX = "Sandbox"
COMPONENT_WORKER = "Worker"

KEYWORD_DEBUG = "Debug"
KEYWORD_INFO = "Info"
KEYWORD_ERROR = "Error"
KEYWORD_WARNING = "Warning"
KEYWORD_STARTUP = "Startup"
KEYWORD_ROUTINE = "Routine"
KEYWORD_JOB = "Job"
KEYWORD_RUNTIME = "Runtime"
KEYWORD_CONFIGURATION = "Configuration"
KEYWORD_TELEMETRY = "Telemetry"


# general traces
# traces in this section may be used in all worker components (worker, sandbox, etc)
def log_debug_trace(message):
    message = "[DEBUG] " + message
    trace_generic_hybrid_worker_event(1, inspect.stack()[0][3], message, 1, KEYWORD_DEBUG, True)


def log_informational_trace(message):
    trace_generic_hybrid_worker_event(2, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_exception_trace(stacktrace):
    message = "Exception encountered. \n" + stacktrace
    trace_generic_hybrid_worker_event(3, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


# worker specific traces
# traces in this section are mainly for the worker component
def log_sandbox_stdout(trace_content):
    sandbox_stdout.info(trace_content)


def log_worker_starting(version):
    message = "Worker starting. [workerVersion=" + str(version) + "]"
    trace_generic_hybrid_worker_event(5000, inspect.stack()[0][3], message, 1, KEYWORD_STARTUP)


def log_worker_general_telemetry(worker_version):
    message = "Worker general telemetry. [workerVersion=" + str(worker_version) + "]"
    trace_generic_hybrid_worker_event(5001, inspect.stack()[0][3], message, 1, KEYWORD_TELEMETRY)


def log_worker_python_telemetry(version, build, compiler):
    message = "Worker python telemetry. [version=" + str(version) + "][build=" + str(' '.join(map(str, build))) + \
              "][compiler=" + str(compiler) + "]"
    trace_generic_hybrid_worker_event(5002, inspect.stack()[0][3], message, 1, KEYWORD_TELEMETRY)


def log_worker_system_telemetry(system, node, version, machine, processor):
    message = "Worker system telemetry. [system=" + str(system) + "][node=" + str(node) + \
              "][version=" + str(version) + "][machine=" + str(machine) + "][processor=" + str(processor) + "]"
    trace_generic_hybrid_worker_event(5003, inspect.stack()[0][3], message, 1, KEYWORD_TELEMETRY)


def log_worker_user_telemetry(username):
    message = "Worker user context telemetry. [username=" + str(username) + "]"
    trace_generic_hybrid_worker_event(5004, inspect.stack()[0][3], message, 1, KEYWORD_TELEMETRY)


def log_worker_lsb_release_telemetry(distributor_id, description, release, codename):
    message = "Worker lsb_release telemetry. [distributor_id=" + str(distributor_id) + "][description=" + \
              str(description) + "][release=" + str(release) + "][codename=" + str(codename) + "]"
    trace_generic_hybrid_worker_event(5005, inspect.stack()[0][3], message, 1, KEYWORD_TELEMETRY)


def log_worker_sandbox_action_found(sandbox_actions):
    message = "Get sandbox actions found " + str(sandbox_actions) + " new action(s)."
    trace_generic_hybrid_worker_event(5100, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


def log_worker_starting_sandbox(sandbox_id):
    message = "Starting sandbox process. [sandboxId=" + str(sandbox_id) + "]"
    trace_generic_hybrid_worker_event(5101, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


def log_worker_sandbox_process_started(sandbox_id, pid):
    message = "Sandbox process started. [sandboxId=" + str(sandbox_id) + "][pId=" + str(pid) + "]"
    trace_generic_hybrid_worker_event(5102, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


def log_worker_sandbox_process_exited(sandbox_id, pid, exit_code):
    message = "Sandbox process exited. [sandboxId=" + str(sandbox_id) + "][pId=" + str(pid) + "][exitCode=" + \
              str(exit_code) + "]"
    trace_generic_hybrid_worker_event(5103, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_worker_sandbox_process_crashed(sandbox_id, pid, exit_code, exception):
    message = "Sandbox process crashed. [sandboxId=" + str(sandbox_id) + "][pId=" + str(pid) + "][exitCode=" + \
              str(exit_code) + "][exception=" + str(exception) + "]"
    trace_generic_hybrid_worker_event(5104, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


def log_worker_failed_to_create_sandbox_root_folder(sandbox_id, exception):
    message = "Failed to create sandbox root folder. [sandboxId=" + str(sandbox_id) + "][exception=" + \
              str(exception) + "]"
    trace_generic_hybrid_worker_event(5105, inspect.stack()[0][3], message, 1, KEYWORD_WARNING)


def log_worker_started_tracking_sandbox(sandbox_id):
    message = "Worker started tracking sandbox. [sandboxId=" + str(sandbox_id) + "]"
    trace_generic_hybrid_worker_event(5106, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_worker_stopped_tracking_sandbox(sandbox_id):
    message = "Worker stopped tracking sandbox. [sandboxId=" + str(sandbox_id) + "]"
    trace_generic_hybrid_worker_event(5107, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


# sandbox specific traces
# traces in this section are mainly for the sandbox component
#
# ** these trace rely on the sandbox_id env variable to be set **
def log_sandbox_starting(pid):
    message = "Sandbox process starting. [sandboxId=" + str(sandbox_id) + "][pId=" + str(pid) + "]"
    trace_generic_hybrid_worker_event(10000, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_get_job_actions(job_actions):
    message = "Get job actions. Found " + str(job_actions) + " new action(s)."
    trace_generic_hybrid_worker_event(10001, inspect.stack()[0][3], message, 1, KEYWORD_ROUTINE)


def log_sandbox_stopped_tracking_job(job_id):
    message = "Sandbox stopped tracking job. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "]"
    trace_generic_hybrid_worker_event(10002, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_started_tracking_job(job_id):
    message = "Sandbox started tracking job. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "]"
    trace_generic_hybrid_worker_event(10003, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_jrds_closure_request():
    message = "Sandbox closure request received from JRDS. [sandboxId=" + str(sandbox_id) + "]"
    trace_generic_hybrid_worker_event(10004, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_pending_action_activate_detected(job_id, job_status, pending_action):
    message = "Sandbox pending action activate detected. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
              "][jobStatus=" + str(job_status) + "][pendingAction=" + str(pending_action) + "]"
    trace_generic_hybrid_worker_event(10005, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_pending_action_stop_detected(job_id, job_status, pending_action):
    message = "Sandbox pending action stop detected. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
              "][jobStatus=" + str(job_status) + "][pendingAction=" + str(pending_action) + "]"
    trace_generic_hybrid_worker_event(10006, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_no_pending_action_detected(job_id, job_status):
    message = "Sandbox no pending action detected. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
              "][jobStatus=" + str(job_status) + "]"
    trace_generic_hybrid_worker_event(10007, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_unsupported_pending_action_detected(job_id, job_status, pending_action):
    message = "Sandbox unsupported pending action detected. [sandboxId=" + str(sandbox_id) + "][jobId=" + \
              str(job_id) + "][jobStatus=" + str(job_status) + "][pendingAction=" + str(pending_action) + "]"
    trace_generic_hybrid_worker_event(10008, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


def log_sandbox_job_created(job_id):
    message = "Job created. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "]"
    trace_generic_hybrid_worker_event(10009, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_job_loaded(job_id):
    message = "Job loaded. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "]"
    trace_generic_hybrid_worker_event(10010, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_job_started(job_id, runbook_definition_kind, runbook_name, runbook_version_id):
    message = "Job started. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "][runbookDefinitionKind=" +\
              str(runbook_definition_kind) + "][runbookName=" + str(runbook_name) + "][runbookVersionId=" +\
              str(runbook_version_id) + "]"
    trace_generic_hybrid_worker_event(10011, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_job_pending_action_detected(job_id, pending_action):
    message = "Job pending action detected. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
              "][pendingAction=" + str(pending_action) + "]"
    trace_generic_hybrid_worker_event(10012, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_job_unloaded(job_id):
    message = "Job unloaded. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "]"
    trace_generic_hybrid_worker_event(10013, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_job_unsupported_runbook_type(job_id, exception):
    message = "Unsupported runbook type. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
              "][exception=" + str(exception) + "]"
    trace_generic_hybrid_worker_event(10014, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


def log_sandbox_job_invalid_signature(job_id):
    message = "Invalid runbook signature. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "]"
    trace_generic_hybrid_worker_event(10015, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


def log_sandbox_job_unhandled_exception(job_id, stacktrace):
    message = "Job unhandled exception. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
              "][stacktrace=" + str(stacktrace) + "]"
    trace_generic_hybrid_worker_event(10016, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


def log_sandbox_job_streamhandler_unhandled_exception(job_id, exception):
    message = "Job stream handler unhandled exception. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
              "][stacktrace=" + str(exception) + "]"
    trace_generic_hybrid_worker_event(10017, inspect.stack()[0][3], message, 1, KEYWORD_ERROR)


def log_sandbox_job_streamhandler_processing_complete(job_id):
    message = "Job stream handler processing complete. [sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "]"
    trace_generic_hybrid_worker_event(10018, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


def log_sandbox_job_runbook_signature_validation_failed(keyring_path, exception):
    message = "Runbook signature validation failed. [sandboxId=" + str(sandbox_id) + "][gpgException=" + \
              str(exception) + "]" + "[keyring_path=" + str(keyring_path) + "]"
    trace_generic_hybrid_worker_event(10019, inspect.stack()[0][3], message, 1, KEYWORD_WARNING)


def log_sandbox_job_runbook_signature_validation_succeeded(keyring_path):
    message = "Runbook signature validation succeeded. [sandboxId=" + str(sandbox_id) + "]" + \
              "[keyring_path=" + str(keyring_path) + "]"
    trace_generic_hybrid_worker_event(10020, inspect.stack()[0][3], message, 1, KEYWORD_WARNING)


def log_sandbox_job_runbook_signature_invalid():
    message = "Runbook signature validation is invalid. [sandboxId=" + str(sandbox_id) + "]"
    trace_generic_hybrid_worker_event(10021, inspect.stack()[0][3], message, 1, KEYWORD_WARNING)


def log_sandbox_configuration(sandbox_id, enforce_runbook_signature_validation, gpg_public_keyring_paths,
                              working_directory):
    message = "Sandbox configuration. [sandboxId=" + str(sandbox_id) + "][enforceRunbookSignatureValidation=" +\
              str(enforce_runbook_signature_validation) + "][gpgPublicKeyringPaths=" + str(gpg_public_keyring_paths) +\
              "][workingDirectory=" + str(working_directory) + "]"
    trace_generic_hybrid_worker_event(10022, inspect.stack()[0][3], message, 1, KEYWORD_INFO)


# etw specific traces
# traces in the following block
def log_etw_job_status_changed_completed(subscription_id, account_id, account_name, sandbox_id, job_id,
                                         runbook_definition_kind, runbook_name):
    cloud_trace_format = [subscription_id,
                          account_id,
                          account_name,
                          sandbox_id,
                          job_id,
                          runbook_definition_kind,
                          runbook_name]
    local_message = "Job state changed to completed. [subscriptionId=" + str(subscription_id) + \
                    "][accountId=" + str(account_id) + "][accountName=" + str(account_name) + "][sandboxId=" + \
                    str(sandbox_id) + "][jobId=" + str(job_id) + "][runbookDefinitionKind=" + \
                    str(runbook_definition_kind) + "][runbookName=" + str(runbook_name) + "]"
    trace_etw_event(3181, local_message, u_activity_id, 0, cloud_trace_format)


def log_etw_job_status_changed_failed(subscription_id, account_id, account_name, sandbox_id, job_id,
                                      runbook_definition_kind, runbook_name, runbook_version_id, exception):
    cloud_trace_format = [subscription_id,
                          account_id,
                          account_name,
                          sandbox_id,
                          job_id,
                          runbook_definition_kind,
                          runbook_name,
                          runbook_version_id,
                          exception]
    local_message = "Job state changed to failed. [subscriptionId=" + str(subscription_id) + "][accountId=" + \
                    str(account_id) + "][accountName=" + str(account_name) + "][sandboxId=" + str(sandbox_id) + \
                    "][jobId=" + str(job_id) + "][runbookDefinitionKind=" + str(runbook_definition_kind) + \
                    "][runbookName=" + str(runbook_name) + "][runbookVersionId=" + str(runbook_version_id) + \
                    "][exception=" + str(exception) + "]"
    trace_etw_event(3182, local_message, u_activity_id, 0, cloud_trace_format)


def log_etw_job_status_changed_running(subscription_id, account_id, account_name, sandbox_id, job_id,
                                       runbook_definition_kind, runbook_name, time_taken_to_start_running_in_seconds):
    cloud_trace_format = [subscription_id,
                          account_id,
                          account_name,
                          sandbox_id,
                          job_id,
                          runbook_definition_kind,
                          runbook_name,
                          time_taken_to_start_running_in_seconds]
    local_message = "Job state changed to running. [subscriptionId=" + str(subscription_id) + "][accountId=" + \
                    str(account_id) + "][accountName=" + str(account_name) + "][sandboxId=" + str(sandbox_id) + \
                    "][jobId=" + str(job_id) + "][runbookDefinitionKind=" + str(runbook_definition_kind) + \
                    "][runbookName=" + str(runbook_name) + "][timeTakenToStartRunningInSeconds=" + \
                    str(time_taken_to_start_running_in_seconds) + "]"
    trace_etw_event(3183, local_message, u_activity_id, 0, cloud_trace_format)


def log_etw_job_status_changed_stopped(subscription_id, account_id, account_name, sandbox_id, job_id,
                                       runbook_definition_kind, runbook_name):
    cloud_trace_format = [subscription_id,
                          account_id,
                          account_name,
                          sandbox_id,
                          job_id,
                          runbook_definition_kind,
                          runbook_name]
    local_message = "Job state changed to stopped. [subscriptionId=" + str(subscription_id) + "][accountId=" + \
                    str(account_id) + "][accountName=" + str(account_name) + "][sandboxId=" + str(sandbox_id) + \
                    "][jobId=" + str(job_id) + "][runbookDefinitionKind=" + str(runbook_definition_kind) + \
                    "][runbookName=" + str(runbook_name) + "]"
    trace_etw_event(3184, local_message, u_activity_id, 0, cloud_trace_format)


def log_etw_job_status_changed_suspended_by_user(account_id, sandbox_id, job_id, runbook_name, runbook_definition_kind,
                                                 account_name):
    cloud_trace_format = [account_id,
                          sandbox_id,
                          job_id,
                          runbook_name,
                          runbook_definition_kind,
                          account_name]
    local_message = "Job state changed to suspended. [accountId=" + str(account_id) + "][sandboxId=" + \
                    str(sandbox_id) + "][jobId=" + str(job_id) + "][runbookName=" + str(runbook_name) + \
                    "][runbookDefinitionKind=" + str(runbook_definition_kind) + "][accountName=" + str(account_name) + \
                    "]"
    trace_etw_event(3185, local_message, u_activity_id, 0, cloud_trace_format)


def log_etw_job_status_changed_suspended_by_exception(account_id, sandbox_id, job_id, runbook_name, exception,
                                                      account_name):
    cloud_trace_format = [account_id,
                          sandbox_id,
                          job_id,
                          runbook_name,
                          exception,
                          account_name]
    local_message = "Job state changed to suspended after an exception was encountered. [accountId=" + \
                    str(account_id) + "][sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "][runbookName=" + \
                    str(runbook_name) + "][exception=" + str(exception) + "]"
    trace_etw_event(3186, local_message, u_activity_id, 0, cloud_trace_format)


def log_etw_user_requested_start_or_resume(account_id, sandbox_id, job_id, runbook_name, account_name,
                                           time_taken_to_start_running_in_seconds, runbook_definition_kind):
    cloud_trace_format = [account_id,
                          sandbox_id,
                          job_id,
                          runbook_name,
                          account_name,
                          time_taken_to_start_running_in_seconds,
                          runbook_definition_kind]
    local_message = "The user requested job state has changed to running. [accountId=" + str(account_id) + \
                    "][sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + "][runbookName=" + \
                    str(runbook_name) + "][timeTakenToStartRunningInSeconds=" + \
                    str(time_taken_to_start_running_in_seconds) + "][runbookType=" + str(runbook_definition_kind) + "]"
    trace_etw_event(3732, local_message, u_activity_id, 0, cloud_trace_format)


def log_etw_job_duration(subscription_id, account_id, sandbox_id, job_id, duration, duration_in_seconds, tier_name,
                         account_name, job_trigger_source, runbook_source, runbook_type, runbook_name,
                         job_run_destination):
    cloud_trace_format = [subscription_id,
                          account_id,
                          sandbox_id,
                          job_id,
                          duration,
                          duration_in_seconds,
                          tier_name,
                          account_name,
                          job_trigger_source,
                          runbook_source,
                          runbook_type,
                          runbook_name,
                          job_run_destination]
    local_message = "Job execution time recorded. [subscriptionId=" + str(subscription_id) + "][accountId=" + \
                    str(account_id) + "][sandboxId=" + str(sandbox_id) + "][jobId=" + str(job_id) + \
                    "][jobTriggerSource=" + str(job_trigger_source) + "][runbookSource=" + str(runbook_source) + \
                    "][runbookType=" + str(runbook_type) + "][runbookName=" + str(runbook_name) + \
                    "][jobRunDestination=" + str(job_run_destination) + "]"
    trace_etw_event(3453, local_message, u_activity_id, 0, cloud_trace_format)

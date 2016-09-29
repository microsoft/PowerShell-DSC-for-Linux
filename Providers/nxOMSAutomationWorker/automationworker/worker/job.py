#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Job module. Contains a class representation of an "automation" job."""

import Queue
import sys
import time
import traceback
from datetime import datetime
from threading import Thread

import configuration
import runtimefactory
import tracer
from automationconstants import pendingactions, jobstatus
from streamhandler import StreamHandler
from workerexception import *

EXIT_SUCCESS = 0


class Job(Thread):
    """Job class."""

    def __init__(self, sandbox_id, job_id, msg_queue, jrds_client, job_thread_exception_queue):
        Thread.__init__(self)
        self.daemon = True

        self.sandbox_id = sandbox_id
        self.job_id = job_id
        self.msg_queue = msg_queue
        self.jrds_client = jrds_client
        self.job_thread_exception_queue = job_thread_exception_queue

        # values populated in load_job()
        self.runtime = None
        self.runbook = None
        self.job_data = None
        self.job_updatable_data = None
        self.runbook_data = None

    def load_job(self):
        """Load all required artifact for the job to be executed."""
        self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.ACTIVATING, False)
        self.job_data = self.jrds_client.get_job_data(self.job_id)
        self.job_updatable_data = self.jrds_client.get_job_updatable_data(self.job_id)
        self.runbook_data = self.jrds_client.get_runbook_data(self.job_data["runbookVersionId"])

    def initialize_runtime(self):
        """Initializes the runtime component for the job. The runtime component is language specific."""
        self.runbook, self.runtime = runtimefactory.create_runtime(self.job_data, self.runbook_data)

    def run(self):
        """Main job execution logic. This methods returns when the job execution is completed.

        Throws:
            WorkerUnsupportedRunbookType  : If the language isn't supported by by the worker.
            OSUnsupportedRunbookType      : If the language isn't supported by by the host.
            Exception                     : Any unhandled exception.
        """
        try:
            self.load_job()
            self.initialize_runtime()
            self.execute_runbook()
            self.unload_job()
        except (WorkerUnsupportedRunbookType, OSUnsupportedRunbookType), e:
            tracer.log_debug_trace("Runbook type not supported.")
            self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.FAILED, True, exception=e.message)
            self.unload_job()
        except InvalidRunbookSignature, e:
            tracer.log_debug_trace("Runbook signature is invalid.")
            self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.FAILED, True, exception=e.message)
            self.unload_job()
        except Exception:
            tracer.log_debug_trace("Job runtime unhandled exception.")
            tracer.log_exception_trace(traceback.format_exc())
            self.job_thread_exception_queue.put(sys.exc_info())

    def execute_runbook(self):
        """Executes the job runtime and performs runtime operation (stream upload / status change)."""
        # set status to running
        tracer.log_debug_trace("Starting runbook.")
        self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.RUNNING, False)

        # create runbook subprocess
        self.runtime.start_runbook_subprocess()

        # monitor runbook output for streams
        stream_handler = StreamHandler(self.job_data, self.runtime.runbook_subprocess, self.jrds_client)
        stream_handler.daemon = True
        stream_handler.start()

        # wait for runbook execution to complete
        pending_action = None
        while stream_handler.isAlive() or self.runtime.runbook_subprocess.poll() is None:
            try:
                pending_action = self.msg_queue.get(block=False)
                tracer.log_debug_trace("Pending action detected. " + str(pending_action))
                if pending_action == pendingactions.STOP_ENUM_INDEX:
                    self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.STOPPING, False)
                    self.runtime.kill_runbook_subprocess()
                    break
            except Queue.Empty:
                pass
            time.sleep(0.2)

        # handle terminal state changes
        if pending_action == pendingactions.STOP_ENUM_INDEX:
            self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.STOPPED, True)
            tracer.log_debug_trace("Completed - Stopped")
        elif self.runtime.runbook_subprocess.poll() is not None and self.runtime.runbook_subprocess.poll() == EXIT_SUCCESS:
            self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.COMPLETED, True)
            tracer.log_debug_trace("Completed - Without error")
        else:
            full_error_output = self.get_full_stderr_content(self.runtime.runbook_subprocess.stderr)
            self.jrds_client.set_job_status(self.sandbox_id, self.job_id, jobstatus.FAILED, True,
                                            exception=full_error_output)
            tracer.log_debug_trace("Completed - With error")

    def unload_job(self):
        """Unloads the job."""
        self.jrds_client.unload_job(self.job_data["subscriptionId"], self.sandbox_id, self.job_id,
                                    self.job_updatable_data["isDraft"], datetime.now(), 2)
        tracer.log_debug_trace("Unloading job.")

    @staticmethod
    def get_full_stderr_content(stderr):
        full_error_output = ""
        while True:
            error_output = stderr.readline()
            if error_output is None or error_output == '':
                break
            full_error_output = "\n".join([full_error_output, error_output])
        return full_error_output

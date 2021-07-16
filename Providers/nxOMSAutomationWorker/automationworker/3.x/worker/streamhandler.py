#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

"""Stream handler module. Is used to process output from stdout and stderr"""

import codecs
import traceback
from threading import Thread

import jrdsclient
import tracer

PREFIX_DEBUG = "DEBUG:"
PREFIX_ERROR = "ERROR:"
PREFIX_VERBOSE = "VERBOSE:"
PREFIX_WARNING = "WARNING:"

STREAM_TYPE_DEBUG = "Debug"
STREAM_TYPE_ERROR = "Error"
STREAM_TYPE_OUTPUT = "Output"
STREAM_TYPE_VERBOSE = "Verbose"
STREAM_TYPE_WARNING = "Warning"


class StreamHandler(Thread):
    """Stream handler class."""

    def __init__(self, job_data, runtime_process, jrds_client):
        """
        :type job_data: jrdsclient.JobData
        :type runtime_process :
        :type jrds_client : jrdsclient.JRDSClient
        """
        Thread.__init__(self)
        self.daemon = True
        self.job_data = job_data
        self.runtime_process = runtime_process
        self.jrds_client = jrds_client

    def get_job_extended_properties(self):
        return {
            'accountid': str(self.job_data.account_id),
            'accountname': str(self.job_data.account_name),
            'trackingid': str(self.job_data.tracking_id),
            'jobid': str(self.job_data.job_id),
            'resourcegroup': str(self.job_data.resource_group_name),
            'runbookname': str(self.job_data.runbook_name),
            'subscriptionid': str(self.job_data.subscription_id),
            'runon': str(self.job_data.run_on)
        }

    def run(self):
        """Monitor the job's subprocess for output (which will be uploaded as streams).

        Notes:
        PowerShell stdout : http://stackoverflow.com/questions/22349139/utf-8-output-from-powershell

        IMPORTANT: Do not log streams to cloud.
        """
        stream_count = 0
        while True:
            try:
                output = codecs.getwriter('utf8')(self.runtime_process.stdout).readline().decode()
                error_output = codecs.getwriter('utf8')(self.runtime_process.stderr).readline().decode()
                if output == '' and error_output == '' and self.runtime_process.poll() is not None:
                    break
                if output:
                    if output.startswith(PREFIX_DEBUG.lower()) or \
                            output.startswith(PREFIX_DEBUG.upper()) or \
                            output.startswith(PREFIX_DEBUG.capitalize()):
                        self.process_debug_stream(stream_count, output)
                    elif output.startswith(PREFIX_ERROR.lower()) or \
                            output.startswith(PREFIX_ERROR.upper()) or \
                            output.startswith(PREFIX_ERROR.capitalize()):
                        self.process_error_stream(stream_count, output)
                    elif output.startswith(PREFIX_VERBOSE.lower()) or \
                            output.startswith(PREFIX_VERBOSE.upper()) or \
                            output.startswith(PREFIX_VERBOSE.capitalize()):
                        self.process_verbose_stream(stream_count, output)
                    elif output.startswith(PREFIX_WARNING.lower()) or \
                            output.startswith(PREFIX_WARNING.upper()) or \
                            output.startswith(PREFIX_WARNING.capitalize()):
                        self.process_warning_stream(stream_count, output)
                    else:
                        self.process_output_stream(stream_count, output)
                    stream_count += 1

                    # leave trace at the end to prevent encoding issue from pushing streams to cloud
                    # leave this as debug trace to prevent logging customer streams to automation logs
                    tracer.log_debug_trace("STDOUT : " + str(output.strip()))
                if error_output:
                    self.process_error_stream(stream_count, error_output)
                    stream_count += 1
                    tracer.log_debug_trace("STDERR : " + str(error_output.strip()))
            except:
                tracer.log_sandbox_job_streamhandler_unhandled_exception(self.job_data.job_id, traceback.format_exc())
                continue
        tracer.log_sandbox_job_streamhandler_processing_complete(self.job_data.job_id)

    def process_debug_stream(self, stream_count, output):
        self.set_stream(stream_count, STREAM_TYPE_DEBUG, output)
        pass

    def process_error_stream(self, stream_count, output):
        self.set_stream(stream_count, STREAM_TYPE_ERROR, output)
        pass

    def process_output_stream(self, stream_count, output):
        self.set_stream(stream_count, STREAM_TYPE_OUTPUT, output)
        pass

    def process_verbose_stream(self, stream_count, output):
        self.set_stream(stream_count, STREAM_TYPE_VERBOSE, output)
        pass

    def process_warning_stream(self, stream_count, output):
        self.set_stream(stream_count, STREAM_TYPE_WARNING, output)
        pass

    def set_stream(self, stream_count, stream_type, output):
        self.jrds_client.set_stream(self.job_data.job_id, self.job_data.runbook_version_id, output.strip(),
                                    stream_type, stream_count, self.get_job_extended_properties())

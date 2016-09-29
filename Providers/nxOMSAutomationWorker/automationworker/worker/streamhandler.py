#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""Stream handler module. Is used to process output from stdout and stderr"""

import codecs
import traceback
from threading import Thread

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
        Thread.__init__(self)
        self.job_data = job_data
        self.runtime_process = runtime_process
        self.jrds_client = jrds_client

    def run(self):
        """Monitor the job's subprocess for output (which will be uploaded as streams).

        Notes:
        PowerShell stdout : http://stackoverflow.com/questions/22349139/utf-8-output-from-powershell

        IMPORTANT: Do not log streams to cloud.
        """
        stream_count = 0
        while True:
            try:
                output = codecs.getwriter('utf8')(self.runtime_process.stdout).readline()
                if output == '' and self.runtime_process.poll() is not None:
                    break
                elif output:
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
            except:
                tracer.log_exception_trace(traceback.format_exc())
                continue
        tracer.log_debug_trace("Stream processing complete.")

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
        self.jrds_client.set_stream(self.job_data["jobId"], self.job_data["runbookVersionId"], output.strip(),
                                    stream_type, stream_count)

#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

"""Curl CLI wrapper."""

import base64
import os.path
import random
import subprocess
import time
import traceback

import iohelper
import subprocessfactory
from httpclient import *

json = serializerfactory.get_serializer(sys.version_info)

CURL_ALIAS = "curl"
CURL_HTTP_CODE_SPECIAL_VAR = "%{http_code}"
OPTION_LOCATION = "--location"
OPTION_SILENT = "--silent"
OPTION_CERT = "--cert"
OPTION_KEY = "--key"
OPTION_WRITE_OUT = "--write-out"
OPTION_HEADER = "--header"
OPTION_REQUEST = "--request"
OPTION_INSECURE = "--insecure"
OPTION_DATA = "--data"
OPTION_PROXY = "--proxy"

OPTION_CONNECT_TIMEOUT = "--connect-timeout"
OPTION_MAX_TIME = "--max-time"
OPTION_RETRY = "--retry"
OPTION_RETRY_DELAY = "--retry-delay"
OPTION_RETRY_MAX_TIME = "--retry-max-time"

# maximum  time  in seconds that you allow the whole operation to take
VALUE_MAX_TIME = "30"

# this only limits the connection phase, it has no impact once it has connected
VALUE_CONNECT_TIMEOUT = "15"

# if  a  transient  error is returned when curl tries to perform a transfer, it will retry this number of times
# before giving up
VALUE_RETRY = "3"

# make  curl  sleep  this amount of time before each retry when a transfer has failed with a transient
VALUE_RETRY_DELAY = "3"

# retries will be done as usual as long as the timer hasn't reached this given limit
VALUE_RETRY_MAX_TIME = "60"

# curl status delimiter
STATUS_CODE_DELIMITER = "\n\nstatus_code:"

# curl success exit code
EXIT_SUCCESS = 0


class CurlHttpClient(HttpClient):
    """Curl CLI wrapper. Inherits from HttpClient.

    Targets :
        [2.4.0 - 2.7.9[

    Implements the following method common to all classes inheriting HttpClient.
        get     (url, headers)
        post    (url, headers, data)

    Curl documentation :
    CLI         : https://curl.haxx.se/docs/manpage.html
    Error code  : https://curl.haxx.se/libcurl/c/libcurl-errors.html
    """

    @staticmethod
    def parse_raw_output(output):
        """Parses stdout from Curl to extract response_body and status_code.

        Args:
            output : string, raw stdout from curl subprocess.

        The format of the raw output should be of the following format (example request to www.microsoft.com):
            <html><head><title>Microsoft Corporation</title><meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7">
            </meta><meta http-equiv="Content-Type" content="text/html; chaset=utf-8"></meta><meta name="SearchTitle"
            content="Microsoft.com" scheme=""></meta><meta name="Description" content="Get product information, support,
            and news from Microsoft." scheme=""></meta><meta name="Title" content="Microsoft.com Home Page" scheme="">
            </meta><meta name="Keywords" content="Microsoft, product, support, help, training Office, Windows,
            software, download, trial, preview, demo,  business, security, update, free, computer, PC, server, search,
            download, install, news" scheme=""></meta><mta name="SearchDescription" content="Microsoft.com Homepage"
            scheme=""></meta></head><body><p>Your current User-Agent string appears to be from an automated process,
            if his is incorrect, please click this link:<a href="http://www.microsoft.com/en/us/default.aspx?redir=
            true">United States English Microsoft Homepage</a></p></body></html>


            status_code:200

        Returns:
            A RequestResponse
        """
        start_index = output.index(STATUS_CODE_DELIMITER)
        response_body = output[:start_index]
        status_code = output[start_index:].strip("\n").split(":")[1]
        return RequestResponse(status_code, response_body)

    def get_base_cmd(self):
        """Creates the base cmd array to invoke the Curl CLI.

        Adds the following arguments for all request:
            --location : Retry the request if the requested page has moved to a different location
            --silent   : Silent or quiet mode

        Adds the following optional arguments
            --cert     : Tells curl to use the specified client certificate file when getting a file with HTTPS
            --key      : Private key file name

        Returns:
            An array containing all required arguments to invoke curl, example:
            ["curl", "--location", "--silent", "--cert", "my_cert_file.crt", "--key", "my_key_file.key"]
        """
        # basic options
        cmd = [CURL_ALIAS, OPTION_LOCATION, OPTION_SILENT]

        # retry and timeout options
        cmd += [OPTION_CONNECT_TIMEOUT, VALUE_CONNECT_TIMEOUT, OPTION_MAX_TIME, VALUE_MAX_TIME, OPTION_RETRY,
                VALUE_RETRY, OPTION_RETRY_DELAY, VALUE_RETRY_DELAY, OPTION_RETRY_MAX_TIME, VALUE_RETRY_MAX_TIME]

        if self.cert_path is not None:
            cmd.extend([OPTION_CERT, self.cert_path, OPTION_KEY, self.key_path])

        if self.proxy_configuration is not None:
            cmd.extend([OPTION_PROXY, self.proxy_configuration])
        return cmd

    def build_request_cmd(self, url, headers, method=None, data_file_path=None):
        """Formats the final cmd array to invoke Curl. The final cmd is created from the based command and additional
        optional parameters.

        Args:
            url             : string    , the URL.
            headers         : dictionary, contains the required headers.
            method          : string    , specifies the http method to use.
            data_file_path  : string    , data file path.

        Adds the following arguments to the base cmd when required:
            --write-out : Makes curl display information on stdout after a completed transfer (i.e status_code).
            --header    : Extra headers to include in the request when sending the request.
            --request   : Specifies a custom request method to use for the request.
            --insecure  : Explicitly allows curl to perform "insecure" SSL connections and transfers.

        Returns:
            An array containing the base cmd concatenated with any required extra argument, example:
            ["curl", "--location", "--silent", "--cert", "my_cert_file.crt", "--key", "my_key_file.key", "--insecure",
                "https://www.microsoft.com"]
        """
        cmd = self.get_base_cmd()
        cmd.append(OPTION_WRITE_OUT)
        cmd.append(STATUS_CODE_DELIMITER + CURL_HTTP_CODE_SPECIAL_VAR + "\n")

        if headers is not None:
            for key, value in headers.items():
                cmd.append(OPTION_HEADER)
                cmd.append(key + ": " + value)

        if method is not None:
            cmd.append(OPTION_REQUEST)
            cmd.append(method)
            if data_file_path is not None:
                cmd.append(OPTION_DATA)
                cmd.append("@" + data_file_path)

        if self.insecure:
            cmd.append(OPTION_INSECURE)

        cmd.append(url)
        return cmd

    def os_is_redhat(self):
        return os.path.exists("/etc/redhat-release")

    def issue_request(self, url, headers, method, data):
        data_file_path = None
        headers = self.merge_headers(self.default_headers, headers)

        # if a body is included, write it to a temporary file (prevent body from leaking in ps/top)
        if method != self.GET and data is not None:
            serialized_data = self.json.dumps(data)

            # write data to disk
            data_file_name = base64.standard_b64encode(str(time.time()) +
                                                       str(random.randint(0, sys.maxsize)) +
                                                       str(random.randint(0, sys.maxsize)) +
                                                       str(random.randint(0, sys.maxsize)) +
                                                       str(random.randint(0, sys.maxsize)))
            data_file_path = os.path.join(configuration.get_temporary_request_directory_path(), data_file_name)
            iohelper.write_to_file(data_file_path, serialized_data)

            # insert Content-Type header
            headers.update({self.CONTENT_TYPE_HEADER_KEY: self.APP_JSON_HEADER_VALUE})

        # ** nesting of try statement is required since try/except/finally isn't supported prior to 2.5 **
        try:
            try:
                cmd = self.build_request_cmd(url, headers, method=method, data_file_path=data_file_path)
                env = os.environ.copy()
                if self.os_is_redhat():
                    env["NSS_SDB_USE_CACHE"] = "no"
                p = subprocessfactory.create_subprocess(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                out, err = p.communicate()
                
                out = out.decode if isinstance(out, bytes) else out
                err = err.decode() if isinstance(err, bytes) else err 
                if p.returncode != EXIT_SUCCESS:
                    raise Exception("Http request failed due to curl error. [returncode=" + str(p.returncode) + "]" +
                                    "[stderr=" + str(err) + "]")

                return self.parse_raw_output(out)
            except Exception as e:
                raise Exception("Unknown exception while issuing request. [exception=" + str(e) + "]" +
                                "[stacktrace=" + str(traceback.format_exc()) + "]")
        finally:
            if data_file_path is not None:
                os.remove(data_file_path)

    def get(self, url, headers=None, data=None):
        """Issues a GET request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).
            data    : dictionary, contains the non-serialized request body (defaults to None).

        Returns:
            A RequestResponse
        """
        return self.issue_request(url, headers, self.GET, data)

    def post(self, url, headers=None, data=None):
        """Issues a POST request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).
            data    : dictionary, contains the non-serialized request body (defaults to None).

        Returns:
            A RequestResponse
        """
        return self.issue_request(url, headers, self.POST, data)

    def put(self, url, headers=None, data=None):
        """Issues a PUT request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).
            data    : dictionary, contains the non-serialized request body (defaults to None).

        Returns:
            A RequestResponse
        """
        return self.issue_request(url, headers, self.PUT, data)

    def delete(self, url, headers=None, data=None):
        """Issues a DELETE request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).
            data    : dictionary, contains the non-serialized request body (defaults to None).

        Returns:
            A RequestResponse
        """
        return self.issue_request(url, headers, self.DELETE, data)

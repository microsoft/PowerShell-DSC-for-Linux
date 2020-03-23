#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""HttpClient base class."""

import os
import sys

import configuration
import serializerfactory
import locallogger
import re as regex

class HttpClient:
    """Base class to provide common attributes and functionality to all HttpClient implementation."""
    ACCEPT_HEADER_KEY = "Accept"
    CONTENT_TYPE_HEADER_KEY = "Content-Type"
    CONNECTION_HEADER_KEY = "Connection"
    USER_AGENT_HEADER_KEY = "User-Agent"

    APP_JSON_HEADER_VALUE = "application/json"
    KEEP_ALIVE_HEADER_VALUE = "keep-alive"

    GET = "GET"
    POST = "POST"
    PUT = "PUT"
    DELETE = "DELETE"

    def __init__(self, cert_path, key_path, insecure=False, proxy_configuration=None):
        self.cert_path = cert_path
        self.key_path = key_path
        self.insecure = insecure
        self.proxy_configuration = proxy_configuration

        # validate presence of cert/key in case they were removed after process creation
        if (cert_path is not None and not os.path.isfile(self.cert_path)) or \
                (key_path is not None and not os.path.isfile(self.key_path)):
            print cert_path
            raise Exception("Invalid certificate or key file path.")

        self.default_headers = {self.ACCEPT_HEADER_KEY: self.APP_JSON_HEADER_VALUE,
                                self.CONNECTION_HEADER_KEY: self.KEEP_ALIVE_HEADER_VALUE,
                                self.USER_AGENT_HEADER_KEY: "AzureAutomationHybridWorker/" +
                                                            configuration.get_worker_version()}
        self.json = serializerfactory.get_serializer(sys.version_info)

    @staticmethod
    def merge_headers(client_headers, request_headers):
        """Merges client_headers and request_headers into a single dictionary. If a request_header key is also present
        in the client_headers, the request_header value will override the client_header one.

        Args:
            client_headers  : dictionary, the default client's headers.
            request_headers : dictionary, request specific headers.

        Returns:
            A dictionary containing a set of both the client_headers and the request_headers
        """
        if request_headers is not None:
            client_headers.update(request_headers.copy())
        else:
            request_headers = client_headers.copy()
        return request_headers

    def get(self, url, headers=None):
        """Issues a GET request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).

        Returns:
            A RequestResponse
        """
        pass

    def post(self, url, headers=None, data=None):
        """Issues a POST request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).
            data    : dictionary, contains the non-serialized request body (defaults to None).

        Returns:
            A RequestResponse
        """
        pass

    def put(self, url, headers=None, data=None):
        """Issues a PUT request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).
            data    : dictionary, contains the non-serialized request body (defaults to None).

        Returns:
            A RequestResponse
        """
        pass

    def delete(self, url, headers=None, data=None):
        """Issues a DELETE request to the provided url using the provided headers.

        Args:
            url     : string    , the URl.
            headers : dictionary, contains the headers key value pair (defaults to None).
            data    : dictionary, contains the non-serialized request body (defaults to None).

        Returns:
            A RequestResponse
        """
        pass

class RequestResponse:
    """Encapsulates all request response for http clients. Will also deserialize the response when the raw response
    data is deserializable.
    """

    @staticmethod
    def check_if_service_unavailable_response_is_received(response_body):
        SERVICE_UNAVAILABLE_STR = 'Service Unavailable'
        HTML_HEADER_TAG_REGEX = '<h[0-9]+>(.*?)</h[0-9]+>'
        HTML_BODY_TAG_REGEX = '<BODY>(.*?)</BODY>'
        HTML_PARAGRAPH_TAG_REGEX = '<p>(.*?)</p>'
        response_body = regex.compile(HTML_BODY_TAG_REGEX).findall(response_body)

        if len(response_body) >= 1:
            response_body = response_body[0]
            headers = regex.compile(HTML_HEADER_TAG_REGEX).findall(response_body)
            # explicit check of service unavailable
            if len(headers) >= 1 and headers.__contains__(SERVICE_UNAVAILABLE_STR):
                detailed_response = regex.compile(HTML_PARAGRAPH_TAG_REGEX).findall(response_body)
                resultant_response = ""
                if detailed_response is not None:
                    for response in detailed_response:
                        resultant_response = resultant_response + response + "\n"
                return resultant_response
        return None


    def __init__(self, status_code, raw_response_data=None):
        self.status_code = int(status_code)
        self.raw_data = raw_response_data
        self.json = serializerfactory.get_serializer(sys.version_info)
        if raw_response_data is not None:
            try:
                self.deserialized_data = self.json.loads(self.raw_data)
            except ValueError:
                import tracer
                self.deserialized_data = None
                service_unavailable_check_result = self.check_if_service_unavailable_response_is_received(self.raw_data)
                if service_unavailable_check_result is not None:
                    tracer.log_warning_trace("Request to service failed because the service was unavailable. Detailed response is %s" %(service_unavailable_check_result))

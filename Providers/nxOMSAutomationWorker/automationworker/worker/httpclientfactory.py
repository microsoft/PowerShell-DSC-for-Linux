#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

from curlhttpclient import CurlHttpClient
from urllib2httpclient import Urllib2HttpClient

PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 1
PY_MICRO_VERSION = 2


class HttpClientFactory:
    """Factory which returns the appropriate HttpClient based on the provided python version.

    Targets :
        [2.4.0 - 2.7.9[ : CurlHttpclient
        [2.7.9 - 2.7.9+ : Urllib2Httpclient

        This is due to the lack of built-in strict certificate verification prior to 2.7.9.
        The ssl module was also unavailable for [2.4.0 - 2.6.0[.
    """

    def __init__(self, cert, key):
        self.cert = cert
        self.key = key

    def create_http_client(self, version_info, insecure=False):
        """Create a new instance of the appropriate HttpClient.

        Args:
            version_info    : array, the build-in python version_info array.
            insecure        : bool, when set to True, httpclient wil bypass certificate verification.

        Returns:
            An instance of CurlHttpClient if the installed Python version is below 2.7.9
            An instance of Urllib2 if the installed Python version is or is above 2.7.9
        """
        if version_info[PY_MAJOR_VERSION] == 2 and version_info[PY_MINOR_VERSION] < 7:
            return CurlHttpClient(self.cert, self.key, insecure)
        elif version_info[PY_MAJOR_VERSION] == 2 and version_info[PY_MINOR_VERSION] <= 7 and version_info[
                PY_MICRO_VERSION] < 9:
            return CurlHttpClient(self.cert, self.key, insecure)
        else:
            return Urllib2HttpClient(self.cert, self.key, insecure)
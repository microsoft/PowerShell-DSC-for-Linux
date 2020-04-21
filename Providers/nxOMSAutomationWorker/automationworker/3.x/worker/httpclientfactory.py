#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

import os

import configuration3 as configuration
import util
from workerexception import *

PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 1
PY_MICRO_VERSION = 2


class HttpClientFactory(object):
    """Factory which returns the appropriate HttpClient based on the provided python version.

    Targets :
        [2.4.0 - 2.7.9[ : CurlHttpclient
        [2.7.9 - 2.7.9+ : Urllib2Httpclient

        This is due to the lack of built-in strict certificate verification prior to 2.7.9.
        The ssl module was also unavailable for [2.4.0 - 2.6.0[.
    """

    def __init__(self, cert, key, insecure=False, force_no_proxy=False):
        self.cert = cert
        self.key = key
        self.insecure = insecure
        self.proxy_configuration = None

        # set proxy if valid proxy_configuration path is detected
        if not force_no_proxy:
            proxy_conf_path = configuration.get_proxy_configuration_path()
            if proxy_conf_path != configuration.DEFAULT_PROXY_CONFIGURATION_PATH \
                    and os.path.isfile(proxy_conf_path):
                if util.assert_file_read_permission(configuration.get_proxy_configuration_path()) is False:
                    raise InvalidFilePermissionException(configuration.get_proxy_configuration_path())
                else:
                    proxy_conf_file = open(configuration.get_proxy_configuration_path(), "r")
                    proxy_configuration = proxy_conf_file.readline().strip()
                    if proxy_configuration != "":
                        self.proxy_configuration = proxy_configuration
                    proxy_conf_file.close()

    def create_http_client(self, version_info):
        """Create a new instance of the appropriate HttpClient.

        Args:
            version_info    : array, the build-in python version_info array.
            insecure        : bool, when set to True, httpclient wil bypass certificate verification.

        Returns:
            An instance of CurlHttpClient if the installed Python version is below 2.7.9
            An instance of Urllib2 if the installed Python version is or is above 2.7.9
        """
        if version_info[PY_MAJOR_VERSION] == 3:
            from urllib3HttpClient import Urllib3HttpClient
            return Urllib3HttpClient(self.cert, self.key, self.insecure, self.proxy_configuration)
        if version_info[PY_MAJOR_VERSION] == 2 and version_info[PY_MINOR_VERSION] < 7:
            from curlhttpclient import CurlHttpClient
            return CurlHttpClient(self.cert, self.key, self.insecure, self.proxy_configuration)
        elif version_info[PY_MAJOR_VERSION] == 2 and version_info[PY_MINOR_VERSION] <= 7 and version_info[
            PY_MICRO_VERSION] < 9:
            from urllib2httpclient import Urllib2HttpClient
            return CurlHttpClient(self.cert, self.key, self.insecure, self.proxy_configuration)
        else:
            from urllib2httpclient import Urllib2HttpClient
            return Urllib2HttpClient(self.cert, self.key, self.insecure, self.proxy_configuration)

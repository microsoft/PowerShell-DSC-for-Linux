#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import sys

import configuration
import serializerfactory
from httpclientfactory import HttpClientFactory
from jrdsclient import JRDSClient

# do not remove, allows clients to use the exceptions types
from workerexception import AutomationAssetException, AutomationAssetNotFound

KEY_VALUE = "value"
KEY_USERNAME = "userName"
KEY_CONNECTION_FIELDS = "connectionFields"


def test_client_override(mock_jrds_client):
    global jrds_client
    jrds_client = mock_jrds_client


def get_automation_variable(name):
    variable = jrds_client.get_variable_asset(name)
    return json.loads(variable[KEY_VALUE])


def set_automation_variable(name, value):
    jrds_client.set_variable_asset(name, json.dumps(value), False)


def get_automation_credential(name):
    credential = jrds_client.get_credential_asset(name)
    return CredentialModelV1(credential[KEY_USERNAME], credential[KEY_VALUE])


def get_automation_connection(name):
    connection = jrds_client.get_connection_asset(name)
    return connection[KEY_CONNECTION_FIELDS]


class CredentialModelV1:
    def __init__(self, username, password):
        self.username = username
        self.password = password


configuration.set_config({configuration.COMPONENT: "assets"})
json = serializerfactory.get_serializer(sys.version_info)
http_client_factory = HttpClientFactory(configuration.get_jrds_cert_path(), configuration.get_jrds_key_path(),
                                        configuration.get_verify_certificates())
http_client = http_client_factory.create_http_client(sys.version_info)
jrds_client = JRDSClient(http_client)

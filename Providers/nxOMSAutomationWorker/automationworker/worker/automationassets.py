#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import sys
import time 

# for python 3 runbook execution in a python2 runtime of Sandbox we need to use httpclient and jrdsclient of python3 automation worker
if sys.version_info[0] == 3:
    AUTOMATIONWORKER_PATH = "/opt/microsoft/omsconfig/modules/nxOMSAutomationWorker/DSCResources/MSFT_nxOMSAutomationWorkerResource/automationworker/3.x/worker"
    sys.path.insert(1,AUTOMATIONWORKER_PATH)
    import configuration3 as configuration
else:
    import configuration


import binascii
import serializerfactory
from httpclientfactory import HttpClientFactory
from jrdsclient import JRDSClient

# do not remove, allows clients to use the exceptions types
from workerexception import AutomationAssetException, AutomationAssetNotFound

KEY_VALUE = "value"
KEY_USERNAME = "userName"
KEY_CONNECTION_FIELDS = "connectionFields"

def log_warning(message):
    print("WARNING: " + str(message))

def log_error(message):
    print("ERROR: " + str(message))

def test_client_override(mock_jrds_client):
    global jrds_client
    jrds_client = mock_jrds_client

def get_automation_variable_with_retry(name, retry_count=2):
    tries = 1
    while tries <= retry_count:
        log_warning("Retrieval of automation variable failed for " + str(name) +". Retrying ..")
        variable = jrds_client.get_variable_asset(name)
        if variable is not None:
            return json.loads(variable[KEY_VALUE])
        time_to_wait = 3 * (2 ** tries)
        if time_to_wait > 60:
            time_to_wait = 60
        time.sleep(time_to_wait)
        tries = tries + 1
    # log not able to retrieve data
    log_error("Retrieval of automation variable failed for " + str(name) +".")

def get_automation_variable(name):
    variable = jrds_client.get_variable_asset(name)
    if variable is None:
        return get_automation_variable_with_retry(name, 2)    
    else:
        return json.loads(variable[KEY_VALUE])

def set_automation_variable(name, value):
    jrds_client.set_variable_asset(name, json.dumps(value), False)

def get_automation_credential_with_retry(name, retry_count=2):
    tries = 1
    while tries <= retry_count:
        log_warning("Retrieval of automation credential failed for " + str(name) +". Retrying ..")
        credential = jrds_client.get_credential_asset(name)
        if credential is not None:
            return {"username": credential[KEY_USERNAME], "password": credential[KEY_VALUE]}
        time_to_wait = 3 * (2 ** tries)
        if time_to_wait > 60:
            time_to_wait = 60
        time.sleep(time_to_wait)
        tries = tries + 1
    # log not able to retrieve data
    log_error("Retrieval of automation credential failed for " + str(name) +".")

def get_automation_credential(name):
    credential = jrds_client.get_credential_asset(name)
    if credential is None:
        return get_automation_credential_with_retry(name, 2)
    else:
        return {"username": credential[KEY_USERNAME], "password": credential[KEY_VALUE]}

def get_automation_connection_with_retry(name, retry_count=2):
    tries = 1
    while tries <= retry_count:
        log_warning("Retrieval of automation connection failed for " + str(name) +". Retrying ..")
        connection = jrds_client.get_connection_asset(name)
        if connection is not None:
            return connection[KEY_CONNECTION_FIELDS]
        time_to_wait = 3 * (2 ** tries)
        if time_to_wait > 60:
            time_to_wait = 60
        time.sleep(time_to_wait)
        tries = tries + 1
    # log not able to retrieve data
    log_error("Retrieval of automation connection failed for " + str(name) +".")

def get_automation_connection(name):
    connection = jrds_client.get_connection_asset(name)
    if connection is None:
        return get_automation_connection_with_retry(name, 2)
    else:
        return connection[KEY_CONNECTION_FIELDS]
        

def get_automation_certificate_with_retry(name, retry_count = 2):
    tries = 1
    while tries <= retry_count:
        log_warning("Retrieval of automation certificate failed for " + str(name) +". Retrying ..")
        certificate = jrds_client.get_certificate_asset(name)
        if certificate is not None:
            return binascii.a2b_base64(certificate[KEY_VALUE])
        time_to_wait = 3 * (2 ** tries)
        if time_to_wait > 60:
            time_to_wait = 60
        time.sleep(time_to_wait)
        tries = tries + 1
    # log not able to retrieve data
    log_error("Retrieval of automation certificate failed for " + str(name) +".")
        
def get_automation_certificate(name):
    certificate = jrds_client.get_certificate_asset(name)
    if certificate is None:
        return get_automation_certificate_with_retry(name, 2)
    else:
        return binascii.a2b_base64(certificate[KEY_VALUE])
 
configuration.set_config({configuration.COMPONENT: "assets"})
json = serializerfactory.get_serializer(sys.version_info)
http_client_factory = HttpClientFactory(configuration.get_jrds_cert_path(), configuration.get_jrds_key_path(),
                                        configuration.get_verify_certificates())
http_client = http_client_factory.create_http_client(sys.version_info)
jrds_client = JRDSClient(http_client)

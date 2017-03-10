#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import ConfigParser
import datetime
import getopt
import os
import socket
import sys

# append worker binary source path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# since we are using the worker httpclient, some configuration values are expected
from worker import configuration

from worker import httpclientfactory
from worker import simplejson as json
from worker import linuxutil

REGISTER = "register"
DEREGISTER = "deregister"

CONFIGURATION_SECTION_WORKER_REQUIRED = "worker-required"
CONFIGURATION_SECTION_WORKER_OPTIONAL = "worker-optional"
CONFIGURATION_SECTION_OMS_METADATA = "oms-metadata"


def get_headers_and_payload(worker_group_name, certificate_path):
    """Formats the required headers and payload for the registration and deregitration requests.

    Returns:
        A tuple containing a dictionary for the request headers and a dictionary for the payload (request body).
    """
    issuer, subject, thumbprint = linuxutil.get_cert_info(certificate_path)
    headers = {'ProtocolVersion': "2.0",
               'x-ms-date': datetime.datetime.utcnow().isoformat() + "0-00:00",
               "Content-Type": "application/json"}

    payload = {'RunbookWorkerGroup': worker_group_name,
               "MachineName": socket.gethostname(),
               "IpAddress": socket.gethostbyname(socket.gethostname()),
               "Thumbprint": thumbprint,
               "Issuer": issuer,
               "Subject": subject}

    return headers, payload


def register(registration_endpoint, worker_group_name, machine_id, cert_path, key_path, test_mode):
    """Registers the worker through the automation linked account with the Agent Service.

    Returns:
        The deserialized response from the Agent Service.
    """
    headers, payload = get_headers_and_payload(worker_group_name, cert_path)
    url = registration_endpoint + "/HybridV2(MachineId='" + machine_id + "')"

    http_client_factory = httpclientfactory.HttpClientFactory(cert_path, key_path, test_mode)
    http_client = http_client_factory.create_http_client(sys.version_info)
    response = http_client.put(url, headers=headers, data=payload)

    if response.status_code != 200:
        raise Exception("Unable to register [status_code=" + str(response.status_code) + "]")

    return json.loads(response.raw_data)


def deregister(registration_endpoint, worker_group_name, machine_id, cert_path, key_path, test_mode):
    """Deregisters the worker through the automation linked account with the Agent Service.

    Note:
        This method is only present for testing purposes for now. Linked account deregistration is not yet implemented
        and deregistration need to be made through using the automation account information.

    Returns:

    """
    headers, payload = get_headers_and_payload(worker_group_name, cert_path)
    url = registration_endpoint + "/Hybrid(MachineId='" + machine_id + "')"

    http_client_factory = httpclientfactory.HttpClientFactory(cert_path, key_path, test_mode)
    http_client = http_client_factory.create_http_client(sys.version_info)
    response = http_client.delete(url, headers=headers, data=payload)

    if response.status_code != 200:
        raise Exception("Unable to deregister [status_code=" + str(response.status_code) + "]")


def create_worker_configuration_file(working_directory, jrds_uri, registration_endpoint, workspace_id,
                                     automation_account_id, worker_group_name, machine_id, oms_cert_path, oms_key_path,
                                     state_directory, gpg_keyring_path, proxy_configuration_path, test_mode,
                                     cert_info):
    """Creates the automation hybrid worker configuration file.

    Note:
        The generated file has to match the latest worker.conf template.
    """
    issuer, subject, thumbprint = cert_info

    worker_conf_path = os.path.join(state_directory, "worker.conf")

    config = ConfigParser.ConfigParser()
    if os.path.isfile(worker_conf_path):
        config.read(worker_conf_path)
    conf_file = open(worker_conf_path, 'wb')

    if not config.has_section(CONFIGURATION_SECTION_WORKER_REQUIRED):
        config.add_section(CONFIGURATION_SECTION_WORKER_REQUIRED)
    config.set(CONFIGURATION_SECTION_WORKER_REQUIRED, "jrds_cert_path", oms_cert_path)
    config.set(CONFIGURATION_SECTION_WORKER_REQUIRED, "jrds_key_path", oms_key_path)
    config.set(CONFIGURATION_SECTION_WORKER_REQUIRED, "jrds_base_uri", jrds_uri)
    config.set(CONFIGURATION_SECTION_WORKER_REQUIRED, "account_id", automation_account_id)
    config.set(CONFIGURATION_SECTION_WORKER_REQUIRED, "machine_id", machine_id)
    config.set(CONFIGURATION_SECTION_WORKER_REQUIRED, "hybrid_worker_group_name", worker_group_name)
    config.set(CONFIGURATION_SECTION_WORKER_REQUIRED, "working_directory_path", working_directory)

    if not config.has_section(CONFIGURATION_SECTION_WORKER_OPTIONAL):
        config.add_section(CONFIGURATION_SECTION_WORKER_OPTIONAL)
    config.set(CONFIGURATION_SECTION_WORKER_OPTIONAL, "gpg_public_keyring_path", gpg_keyring_path)
    config.set(CONFIGURATION_SECTION_WORKER_OPTIONAL, "proxy_configuration_path", proxy_configuration_path)
    config.set(CONFIGURATION_SECTION_WORKER_OPTIONAL, "state_directory_path", state_directory)
    if test_mode is True:
        config.set(CONFIGURATION_SECTION_WORKER_OPTIONAL, "bypass_certificate_verification", True)

    if not config.has_section(CONFIGURATION_SECTION_OMS_METADATA):
        config.add_section(CONFIGURATION_SECTION_OMS_METADATA)
    config.set(CONFIGURATION_SECTION_OMS_METADATA, "agent_id", machine_id)
    config.set(CONFIGURATION_SECTION_OMS_METADATA, "workspace_id", workspace_id)
    config.set(CONFIGURATION_SECTION_OMS_METADATA, "registration_endpoint", registration_endpoint)
    config.set(CONFIGURATION_SECTION_OMS_METADATA, "oms_cert_thumbprint", thumbprint)

    config.write(conf_file)
    conf_file.close()


def main(argv):
    agent_id = None
    oms_cert_path = None
    oms_key_path = None
    endpoint = None
    gpg_keyring_path = None
    operation = None
    proxy_configuration_path = None
    test_mode = False
    state_directory = None
    working_directory = None
    workspace_id = None
    mock_powershelldsc_test = False
    diy_account_id = None

    # parse cmd line args
    try:
        opts, args = getopt.getopt(argv, "hrdw:a:c:k:e:f:s:p:g:y:t",
                                   ["help", "register", "deregister", "workspaceid=", "agentid=", "certpath=",
                                    "keypath=", "endpoint=", "workingdirpath=", "statepath=", "proxyconfpath=",
                                    "gpgkeyringpath=", "diyaccountid=", "mock_powershelldsc_test="])
    except getopt.GetoptError:
        print __file__ + "[--register, --deregister] -w <workspaceid> -a <agentid> -c <certhpath> -k <keypath> " \
                         "-e <endpoint> -f <workingdirpath> -s <statepath> -p <proxyconfpath> -g <gpgkeyringpath>" \
                         "-y <diyaccountid>"
        sys.exit(2)
    for opt, arg in opts:
        if opt == ("-h", "--help"):
            print __file__ + "[--register, --deregister] -w <workspaceid> -a <agentid> -c <certhpath> -k <keypath> " \
                             "-e <endpoint> -f <workingdirpath> -s <statepath> -p <proxyconfpath> -g <gpgkeyringpath>" \
                             "-y <diyaccountid>"
            sys.exit()
        elif opt in ("-r", "--register"):
            operation = REGISTER
        elif opt in ("-d", "--deregister"):
            operation = DEREGISTER
        elif opt in ("-w", "--workspaceid"):
            workspace_id = arg.strip()
        elif opt in ("-a", "--agentid"):
            agent_id = arg.strip()
        elif opt in ("-c", "--certpath"):
            oms_cert_path = arg.strip()
        elif opt in ("-k", "--keypath"):
            oms_key_path = arg.strip()
        elif opt in ("-e", "--endpoint"):
            endpoint = arg.strip()
        elif opt in ("-f", "--workingdirpath"):
            working_directory = arg.strip()
        elif opt in ("-p", "--proxyconfpath"):
            proxy_configuration_path = arg.strip()
        elif opt in ("-s", "--statepath"):
            state_directory = arg.strip()
        elif opt in ("-g", "--gpgkeyringpath"):
            gpg_keyring_path = arg.strip()
        elif opt in ("-y", "--diyaccountid"):
            diy_account_id = arg.strip()
        elif opt in ("-t", "--test"):
            test_mode = True
        elif opt == "--mock_powershelldsc_test":
            # generate a dummy configuration file
            # does not do actual registration, just creates the resulting config file
            mock_powershelldsc_test = True

    if workspace_id is None or agent_id is None or oms_cert_path is None or oms_key_path is None \
            or endpoint is None or gpg_keyring_path is None or proxy_configuration_path is None \
            or working_directory is None or state_directory is None:
        print "Missing mandatory arguments."
        print "Use -h or --help for usage."
        sys.exit(1)
    else:
        if mock_powershelldsc_test is True:
            # Don't validate paths if we want to generate a dummy config file
            pass
        else:
            # validate that the cert and key exists
            if os.path.isfile(oms_cert_path) is False or os.path.isfile(oms_key_path) is False:
                raise Exception("Certificate or key file doesn't exist. Are you using absolute path?")

        configuration.clear_config()
        configuration.set_config(
            {configuration.PROXY_CONFIGURATION_PATH: proxy_configuration_path,
             configuration.WORKER_VERSION: "LinuxAutoRegister",
             configuration.WORKING_DIRECTORY_PATH: "/var/opt/microsoft/omsagent/tmp"})

        # build registration endpoint
        # example endpoint : agentsvc.azure-automation.net
        registration_endpoint = "https://" + workspace_id + "." + endpoint + "/accounts/" + workspace_id
        if "df-agentsvc" in registration_endpoint:
            registration_endpoint = "https://oaasagentsvcdf.test.azure-automation.net/accounts/" + workspace_id
            test_mode = True

        # rename to match oms concepts to automation
        machine_id = agent_id
        worker_group_name = socket.gethostname() + "_" + agent_id

        # action
        if operation == REGISTER:
            if mock_powershelldsc_test is True:
                # Don't do the actual registration in case we want only a dummy registration file
                # create a dummy response instead
                registration_response = \
                    {'jobRuntimeDataServiceUri': 'https://we-jobruntimedata-prod-su1.azure-automation.net',
                     'AccountId': '23216587-8f56-428c-9006-4c2f28c036f5'}
                cert_info = ['', '', '959GG850526XC5JT35E269CZ69A55E1C7E1256JH']
            else:
                registration_response = register(registration_endpoint, worker_group_name, machine_id, oms_cert_path,
                                                 oms_key_path, test_mode)
                cert_info = linuxutil.get_cert_info(oms_cert_path)
                account_id = registration_response["AccountId"]

                if test_mode is False and diy_account_id is not None and diy_account_id != account_id:
                    sys.stderr.write("Unable to create worker configuration. DIY Automation account differs from "
                                     "linked account.")
                    sys.exit(-5)

                create_worker_configuration_file(working_directory, registration_response["jobRuntimeDataServiceUri"],
                                                 registration_endpoint, workspace_id, account_id,
                                                 worker_group_name, machine_id, oms_cert_path, oms_key_path,
                                                 state_directory, gpg_keyring_path, proxy_configuration_path, test_mode,
                                                 cert_info)
        elif operation == DEREGISTER:
            deregister(registration_endpoint, worker_group_name, machine_id, oms_cert_path, oms_key_path, test_mode)
        else:
            raise Exception("No option specified, specify --register, --deregister or --help.")


if __name__ == "__main__":
    main(sys.argv[1:])

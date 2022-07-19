#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

import ConfigParser
import datetime
import getopt
import os
import socket
import sys
import re


PY_MAJOR_VERSION = 0
PY_MINOR_VERSION = 1

# append worker binary source path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# since we are using the worker httpclient, some configuration values are expected
from worker import configuration

from worker import httpclientfactory
from worker import linuxutil

''''An instance of simplejson module if the installed Python version is below 2.6
An instance of json module if the installed Python version is or is above 2.6'''
if sys.version_info[PY_MAJOR_VERSION] == 2 and sys.version_info[PY_MINOR_VERSION] < 6:
    import simplejson as json
else:
    import json

REGISTER = "register"
DEREGISTER = "deregister"


def is_ipv4(hostname):
    match = re.match('^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3}).(\\d{1,3})$', hostname)
    if not match:
        return False
    for i in range(1, 5):
        num = int(match.group(i))
        if num < 0 or num > 255:
            return False
    return True


def get_hostname():
    oms_agent_hostname_command = ['/opt/microsoft/omsagent/ruby/bin/ruby', '-r',
                                  '/opt/microsoft/omsagent/plugin/oms_common.rb', '-e', 'puts OMS::Common.get_hostname']
    # Use the ruby util OMS agent uses to get hostname
    try:
        process, output, error = linuxutil.popen_communicate(oms_agent_hostname_command)
        if process.returncode == 0 and not error:
            return output.strip()
    except OSError:
        pass
    # Unable to use ruby util, falling back on socket to get hostname
    hostname = socket.gethostname()
    if is_ipv4(hostname):
        return hostname
    else:
        return hostname.split(".")[0]


def get_hybrid_worker_group_name(agent_id):
    """Generates the hybrid worker group name.

    Notes:
        The format as to match the OMSAgent computer_agentid format.
        The OMSAgent doesn't use FQDN for the computer name.

        See : https://github.com/Microsoft/OMS-Agent-for-Linux/blob/master/source/code/plugins/oms_common.rb#L600

    Returns:
        String, hybrid worker group name
    """
    # following same format as OMSAgent (get_hostname())
    # see : https://github.com/Microsoft/OMS-Agent-for-Linux/blob/master/source/code/plugins/oms_common.rb#L600
    return get_hostname() + "_" + agent_id


def get_ip_address():
    """Gets the host ip address.

    Notes:
        Defaulting to 127.0.01 for host that are not configured properly. This field is only informational
        for AgentService.

    Returns:
        String, IpAddress
    """
    try:
        return socket.gethostbyname(socket.gethostname())
    except:
        return "127.0.0.1"


def get_metadata_from_imds(http_client):
    """
    Tries to get azurevm metadata from IMDS
    :return: a dictionary of the following format
    {
        "compute": {
            "location": "some-location",
            "name": "some-computer",
            "offer": "some-offer",
            "osType": "Linux",
            "placementGroupId": "",
            "platformFaultDomain": "0",
            "platformUpdateDomain": "0",
            "publisher": "some-publisher",
            "resourceGroupName": "rome-resourceGroup",
            "sku": "some-sku",
            "subscriptionId": "aaaa0000-aa00-aa00-aa00-aaaaaa000000",
            "tags": "",
            "version": "1.1.10",
            "vmId": "bbbb0000-bb00-bb00-bb00-bbbbbb000000",
            "vmSize": "Standard_D1"
        },
        "network": {
            "interface": [
                {
                    "ipv4": {
                        "ipAddress": [
                            {
                                "privateIpAddress": "0.0.0.0",
                                "publicIpAddress": "0.0.0.0"
                            }
                        ],
                        "subnet": [
                            {
                                "address": "10.0.0.0",
                                "prefix": "24"
                            }
                        ]
                    },
                    "ipv6": {
                        "ipAddress": []
                    },
                    "macAddress": "000AAABBB11"
                }
            ]
        }
    }
    """
    try:
        mdUrl = "http://169.254.169.254/metadata/instance?api-version=2017-08-01"
        header = {'Metadata': 'True'}
        response = http_client.get(mdUrl, headers=header)
        jsonObj = json.loads(response.raw_data)
        return jsonObj

    except:
        return None


def get_headers_and_payload(worker_group_name, is_azure_vm, vm_id, azure_resource_id, certificate_path, http_client):
    """Formats the required headers and payload for the registration and deregitration requests.

    Returns:
        A tuple containing a dictionary for the request headers and a dictionary for the payload (request body).
    """
    issuer, subject, thumbprint = linuxutil.get_cert_info(certificate_path)
    headers = {"ProtocolVersion": "2.0",
               "x-ms-date": datetime.datetime.utcnow().isoformat() + "0-00:00",
               "Content-Type": "application/json"}

    asset_tag = "Unknown"
    platform_update_domain = ""
    tags = {}
    if is_azure_vm:
        asset_tag = linuxutil.get_azure_vm_asset_tag()
        try:
            metadata = get_metadata_from_imds(http_client)
            if metadata is not None:
                try:
                    vm_id = metadata["compute"]["vmId"]
                    sub_id = metadata["compute"]["subscriptionId"]
                    resource_group = metadata["compute"]["resourceGroupName"]
                    vm_name = metadata["compute"]["name"]
                    azure_resource_id = "/subscriptions/{0}/resourceGroups/{1}/providers/Microsoft.Compute/virtualMachines/{2}".format(sub_id, resource_group, vm_name)
                    platform_update_domain = metadata["compute"]["platformUpdateDomain"]
                    tags = metadata["compute"]["tags"]

                except KeyError:
                    pass
        except:
            pass

    payload = {"RunbookWorkerGroup": worker_group_name,
               "MachineName": get_hostname(),
               "IpAddress": get_ip_address(),
               "Thumbprint": thumbprint,
               "Issuer": issuer,
               "OperatingSystem": 2,
               "SMBIOSAssetTag": asset_tag,
               "VirtualMachineId": vm_id,
               "Subject": subject,
               "platformUpdateDomain": platform_update_domain,
               "tags": tags}

    if azure_resource_id is not None:
        payload["AzureResourceId"] = azure_resource_id

    return headers, payload


# TODO: add test-register code to test changes in payload, change cadence to increase polling time period

def register(registration_endpoint, worker_group_name, machine_id, cert_path, key_path, is_azure_vm, vm_id,
             azure_resource_id, test_mode):
    """Registers the worker through the automation linked account with the Agent Service.

    Returns:
        The deserialized response from the Agent Service.
    """
    http_client_factory = httpclientfactory.HttpClientFactory(cert_path, key_path, test_mode)
    http_client = http_client_factory.create_http_client(sys.version_info)

    no_proxy_http_client_factory = httpclientfactory.HttpClientFactory(cert_path, key_path, test_mode, force_no_proxy=True)
    no_proxy_http_client = no_proxy_http_client_factory.create_http_client(sys.version_info)

    headers, payload = get_headers_and_payload(worker_group_name, is_azure_vm, vm_id, azure_resource_id, cert_path,
                                               no_proxy_http_client)
    url = registration_endpoint + "/HybridV2(MachineId='" + machine_id + "')"

    response = http_client.put(url, headers=headers, data=payload)

    if response.status_code != 200:
        raise Exception("Unable to register [status_code=" + str(response.status_code) + "]")

    return json.loads(response.raw_data), payload


def deregister(registration_endpoint, worker_group_name, machine_id, cert_path, key_path, test_mode):
    """Deregisters the worker through the automation linked account with the Agent Service.

    Note:
        This method is only present for testing purposes for now. Linked account deregistration is not yet implemented
        and deregistration need to be made through using the automation account information.

    Returns:

    """
    headers, payload = get_headers_and_payload(worker_group_name, certificate_path=cert_path)
    url = registration_endpoint + "/Hybrid(MachineId='" + machine_id + "')"

    http_client_factory = httpclientfactory.HttpClientFactory(cert_path, key_path, test_mode)
    http_client = http_client_factory.create_http_client(sys.version_info)
    response = http_client.delete(url, headers=headers, data=payload)

    if response.status_code != 200:
        raise Exception("Unable to deregister [status_code=" + str(response.status_code) + "]")


def create_worker_configuration_file(working_directory, jrds_uri, registration_endpoint, workspace_id,
                                     automation_account_id, worker_group_name, machine_id, oms_cert_path, oms_key_path,
                                     state_directory, gpg_keyring_path, proxy_configuration_path, test_mode,
                                     cert_info, is_azure_vm, vm_id):
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

    worker_required_section = configuration.WORKER_REQUIRED_CONFIG_SECTION
    if not config.has_section(worker_required_section):
        config.add_section(worker_required_section)
    config.set(worker_required_section, configuration.CERT_PATH, oms_cert_path)
    config.set(worker_required_section, configuration.KEY_PATH, oms_key_path)
    config.set(worker_required_section, configuration.BASE_URI, jrds_uri)
    config.set(worker_required_section, configuration.ACCOUNT_ID, automation_account_id)
    config.set(worker_required_section, configuration.MACHINE_ID, machine_id)
    config.set(worker_required_section, configuration.HYBRID_WORKER_GROUP_NAME, worker_group_name)
    config.set(worker_required_section, configuration.WORKING_DIRECTORY_PATH, working_directory)

    worker_optional_section = configuration.WORKER_OPTIONAL_CONFIG_SECTION
    if not config.has_section(worker_optional_section):
        config.add_section(worker_optional_section)
    config.set(worker_optional_section, configuration.GPG_PUBLIC_KEYRING_PATH, gpg_keyring_path)
    config.set(worker_optional_section, configuration.PROXY_CONFIGURATION_PATH, proxy_configuration_path)
    config.set(worker_optional_section, configuration.STATE_DIRECTORY_PATH, state_directory)
    if test_mode is True:
        config.set(worker_optional_section, configuration.BYPASS_CERTIFICATE_VERIFICATION, True)

    metadata_section = configuration.METADATA_CONFIG_SECTION
    if not config.has_section(metadata_section):
        config.add_section(metadata_section)
    config.set(metadata_section, configuration.IS_AZURE_VM, str(is_azure_vm))
    config.set(metadata_section, configuration.VM_ID, vm_id)
    config.set(metadata_section, configuration.WORKER_TYPE, "auto-registered")

    oms_metadata_section = "oms-metadata"
    if not config.has_section(oms_metadata_section):
        config.add_section(oms_metadata_section)
    config.set(oms_metadata_section, configuration.AGENT_ID, machine_id)
    config.set(oms_metadata_section, configuration.WORKSPACE_ID, workspace_id)
    config.set(oms_metadata_section, configuration.REGISTRATION_ENDPOINT, registration_endpoint)
    config.set(oms_metadata_section, configuration.CERTIFICATE_THUMBPRINT, thumbprint)

    config.write(conf_file)
    conf_file.close()


def main(argv):
    agent_id = None
    is_azure_vm = False
    vm_id = None
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
    azure_resource_id = None

    # parse cmd line args
    try:
        opts, args = getopt.getopt(argv, "hrdw:a:c:k:e:f:s:p:g:y:i:v:zt",
                                   ["help", "register", "deregister", "workspaceid=", "agentid=", "certpath=",
                                    "keypath=", "endpoint=", "workingdirpath=", "statepath=", "proxyconfpath=",
                                    "gpgkeyringpath=", "diyaccountid=", "mock_powershelldsc_test=", "vmid=",
                                    "azureresourceid="])
    except getopt.GetoptError:
        print __file__ + "[--register, --deregister] -w <workspaceid> -a <agentid> -c <certhpath> -k <keypath> " \
                         "-e <endpoint> -f <workingdirpath> -s <statepath> -p <proxyconfpath> -g <gpgkeyringpath>" \
                         "-y <diyaccountid> -i <vmid>"
        sys.exit(2)
    for opt, arg in opts:
        if opt == ("-h", "--help"):
            print __file__ + "[--register, --deregister] -w <workspaceid> -a <agentid> -c <certhpath> -k <keypath> " \
                             "-e <endpoint> -f <workingdirpath> -s <statepath> -p <proxyconfpath> -g <gpgkeyringpath>" \
                             "-y <diyaccountid> -i <vmid>"
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
        elif opt in ("-z", "--azurevm"):
            is_azure_vm = True
        elif opt in ("-v", "--azureresourceid"):
            azure_resource_id = arg.strip()  # Use the Resource ID from DSC resource as a backup. Overwrite it with metadata from IMDS when available
        elif opt in ("-i", "--vmid"):
            vm_id = arg.strip()  # Use the VM ID from DSC resource as a backup. Overwrite it with metadata from IMDS when available
        elif opt in ("-t", "--test"):
            test_mode = True
        elif opt == "--mock_powershelldsc_test":
            # generate a dummy configuration file
            # does not do actual registration, just creates the resulting config file
            mock_powershelldsc_test = True

    if workspace_id is None or agent_id is None or oms_cert_path is None or oms_key_path is None \
            or endpoint is None or gpg_keyring_path is None or proxy_configuration_path is None \
            or working_directory is None or state_directory is None or vm_id is None:
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
        worker_group_name = get_hybrid_worker_group_name(agent_id=agent_id)

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
                registration_response, payload = register(registration_endpoint, worker_group_name, machine_id, oms_cert_path,
                                                 oms_key_path, is_azure_vm, vm_id, azure_resource_id, test_mode)
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
                                                 cert_info, is_azure_vm,
                                                 payload["VirtualMachineId"])
        elif operation == DEREGISTER:
            deregister(registration_endpoint, worker_group_name, machine_id, oms_cert_path, oms_key_path, test_mode)
        else:
            raise Exception("No option specified, specify --register, --deregister or --help.")


if __name__ == "__main__":
    main(sys.argv[1:])

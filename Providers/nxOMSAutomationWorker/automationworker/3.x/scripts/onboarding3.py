#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

import configparser
import base64
import datetime
import os
import re
import shutil
import socket
import subprocess
import sys
from optparse import OptionParser
import packagesimportutil

# append worker binary source path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
packagesimportutil.add_all_packages_under_automationworker_to_sys_path()


from worker import configuration3
from worker import httpclientfactory
from worker import linuxutil
from worker import serializerfactory
from worker import util
from worker import diydirs

json = serializerfactory.get_serializer(sys.version_info)
configuration3.clear_config()
configuration3.set_config({configuration3.PROXY_CONFIGURATION_PATH: "/etc/opt/microsoft/omsagent/proxy.conf",
                          configuration3.WORKER_VERSION: "LinuxDIYRegister",
                          configuration3.WORKING_DIRECTORY_PATH: "/tmp"})

def get_ip_address():
    try:
        return socket.gethostbyname(socket.gethostname())
    except:
        return "127.0.0.1"


DIY_STATE_PATH = diydirs.DIY_STATE_PATH
DIY_WORKING_DIR = diydirs.DIY_WORKING_DIR

def generate_self_signed_certificate(certificate_path, key_path):
    """Creates a self-signed x509 certificate and key pair in the spcified path.

    Args:
        certificate_path    : string, the output path of the certificate
        key_path            : string, the output path of the key
    """
    cmd = ["openssl", "req", "-subj",
           "/C=US/ST=Washington/L=Redmond/O=Microsoft Corporation/OU=Azure Automation/CN=Hybrid Runbook Worker",
           "-new", "-newkey", "rsa:2048", "-days", "365", "-nodes", "-x509", "-keyout", key_path, "-out",
           certificate_path]
    process, certificate_creation_output, error = linuxutil.popen_communicate(cmd)
    error = error.decode() if isinstance(error, bytes) else error
    if process.returncode != 0:
        raise Exception("Unable to create certificate/key. " + str(error))
    print ("Certificate/Key created.")


def sha256_digest(payload):
    """Sha256 digest of the specified payload.

    Args:
        payload : string, the payload to digest

    Returns:
        payload_hash : string, the sha256 hash of the payload
    """
    cmd = ['echo -n "' + str(json.dumps(json.dumps(payload))) + '" | openssl dgst -sha256 -binary']
    process, payload_hash, error = linuxutil.popen_communicate(cmd, shell=True)

    error = error.decode() if isinstance(error, bytes) else error
    if process.returncode != 0:
        raise Exception("Unable to generate payload hash. " + str(error))

    return payload_hash


def generate_hmac(str_to_sign, secret):
    """Signs the specified string using the specified secret.

    Args:
        str_to_sign : string, the string to sign
        secret      : string, the secret used to sign

    Returns:
        signed_message : string, the signed str_to_sign
    """
    message = str_to_sign.encode('utf-8')
    secret = secret.encode('utf-8')
    cmd = ['echo -n "' + str(message.decode("utf-8")) + '" | openssl dgst -sha256 -binary -hmac "' + str(secret.decode("utf-8")) + '"']
    process, signed_message, error = linuxutil.popen_communicate(cmd, shell=True)
    
    error = error.decode() if isinstance(error, bytes) else error
    if process.returncode != 0:
        raise Exception("Unable to generate signature. " + str(error))

    return signed_message


def create_worker_configuration_file(jrds_uri, automation_account_id, worker_group_name, machine_id,
                                     working_directory_path, state_directory_path, cert_path, key_path,
                                     registration_endpoint, workspace_id, thumbprint, vm_id, is_azure_vm,
                                     gpg_keyring_path, test_mode):
    """Creates the automation hybrid worker configuration3 file.

    Args:
        jrds_uri                : string, the jrds endpoint
        automation_account_id   : string, the automation account id
        worker_group_name       : string, the hybrid worker group name
        machine_id              : string, the machine id
        working_directory_path  : string, the hybrid worker working directory path
        state_directory_path    : string, the state directory path
        cert_path               : string, the the certificate path
        key_path                : string, the key path
        registration_endpoint   : string, the registration endpoint
        workspace_id            : string, the workspace id
        thumbprint              : string, the certificate thumbprint
        is_azure_vm             : bool,   whether the VM is hosted in Azure
        gpg_keyring_path        : string, path to the gpg keyring for verifying runbook signatures
        test_mode               : bool,   test mode

    Note:
        The generated file has to match the latest worker.conf template.
    """
    worker_conf_path = os.path.join(state_directory_path, "worker.conf")

    config = configparser.ConfigParser()
    if os.path.isfile(worker_conf_path):
        config.read(worker_conf_path)
    conf_file = open(worker_conf_path, 'w')

    worker_required_section = configuration3.WORKER_REQUIRED_CONFIG_SECTION
    if not config.has_section(worker_required_section):
        config.add_section(worker_required_section)
    config.set(worker_required_section, configuration3.CERT_PATH, cert_path)
    config.set(worker_required_section, configuration3.KEY_PATH, key_path)
    config.set(worker_required_section, configuration3.BASE_URI, jrds_uri)
    config.set(worker_required_section, configuration3.ACCOUNT_ID, automation_account_id)
    config.set(worker_required_section, configuration3.MACHINE_ID, machine_id)
    config.set(worker_required_section, configuration3.HYBRID_WORKER_GROUP_NAME, worker_group_name)
    config.set(worker_required_section, configuration3.WORKING_DIRECTORY_PATH, working_directory_path)

    worker_optional_section = configuration3.WORKER_OPTIONAL_CONFIG_SECTION
    if not config.has_section(worker_optional_section):
        config.add_section(worker_optional_section)
    config.set(worker_optional_section, configuration3.PROXY_CONFIGURATION_PATH,
               "/etc/opt/microsoft/omsagent/proxy.conf")
    config.set(worker_optional_section, configuration3.STATE_DIRECTORY_PATH, state_directory_path)
    if gpg_keyring_path is not None:
        config.set(worker_optional_section, configuration3.GPG_PUBLIC_KEYRING_PATH, gpg_keyring_path)
    if test_mode is True:
        config.set(worker_optional_section, configuration3.BYPASS_CERTIFICATE_VERIFICATION, True)
        config.set(worker_optional_section, configuration3.DEBUG_TRACES, True)

    metadata_section = configuration3.METADATA_CONFIG_SECTION
    if not config.has_section(metadata_section):
        config.add_section(metadata_section)
    config.set(metadata_section, configuration3.WORKER_TYPE, "diy")
    config.set(metadata_section, configuration3.IS_AZURE_VM, str(is_azure_vm))
    config.set(metadata_section, configuration3.VM_ID, vm_id)

    registration_metadata_section = "registration-metadata"
    if not config.has_section(registration_metadata_section):
        config.add_section(registration_metadata_section)
    config.set(registration_metadata_section, configuration3.REGISTRATION_ENDPOINT, registration_endpoint)
    config.set(registration_metadata_section, configuration3.WORKSPACE_ID, workspace_id)
    config.set(registration_metadata_section, configuration3.CERTIFICATE_THUMBPRINT, thumbprint)

    config.write(conf_file)
    conf_file.close()


def get_autoregistered_worker_account_id():
    autoregistered_worker_conf_path = "/var/opt/microsoft/omsagent/state/automationworker/worker.conf"
    config = configparser.ConfigParser()
    if os.path.isfile(autoregistered_worker_conf_path) is False:
        print ("No diy worker found. Account validation skipped.")
        return None

    config.read(autoregistered_worker_conf_path)
    account_id = config.get("worker-required", "account_id")
    print ("Found existing worker for account id : " + str(account_id))
    return account_id


def extract_account_id_from_registration_endpoint(registration_endpoint):
    account_id = re.findall("[a-z0-9]{8}-[a-z0-9]{4}-[a-z0-9]{4}-[a-z0-9]{4}-[a-z0-9]{12}",
                            registration_endpoint.lower())
    if len(account_id) != 1:
        raise Exception("Invalid registration endpoint format.")
    return account_id[0]


def invoke_dmidecode():
    """Gets the dmidecode output from the host."""
    proc = subprocess.Popen(["su", "-", "root", "-c", "dmidecode"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    dmidecode, error = proc.communicate()
    if proc.poll() != 0:
        raise Exception("Unable to get dmidecode output : " + str(error))
    return dmidecode.decode()


def register(options):
    environment_prerequisite_validation()
    """Registers the machine against the automation agent service.

    Args:
        options : dict, the options dictionary
    """
    registration_endpoint = options.registration_endpoint
    automation_account_key = options.automation_account_key
    hybrid_worker_group_name = options.hybrid_worker_group_name
    workspace_id = options.workspace_id

    # assert workspace exists on the box
    state_base_path = "/var/opt/microsoft/omsagent/" + workspace_id + "/state/"
    working_directory_base_path = "/var/opt/microsoft/omsagent/" + workspace_id + "/run/"
    if os.path.exists(state_base_path) is False or os.path.exists(working_directory_base_path) is False:
        raise Exception("Invalid workspace id. Is the specified workspace id registered as the OMSAgent "
                        "primary worksapce?")

    diy_account_id = extract_account_id_from_registration_endpoint(registration_endpoint)
    auto_registered_account_id = get_autoregistered_worker_account_id()
    if auto_registered_account_id != None and auto_registered_account_id != diy_account_id:
        raise Exception("Cannot register, conflicting worker already registered.")


    worker_conf_path = os.path.join(DIY_STATE_PATH, "worker.conf")

    if os.path.isfile(worker_conf_path) is True:
        raise Exception("Unable to register, an existing worker was found. Please deregister any existing worker and "
                        "try again.")

    certificate_path = os.path.join(DIY_STATE_PATH, "worker_diy.crt")
    key_path = os.path.join(DIY_STATE_PATH, "worker_diy.key")
    machine_id = util.generate_uuid()

    # generate state path (certs/conf will be dropped in this path)
    if os.path.isdir(DIY_STATE_PATH) is False:
        os.makedirs(DIY_STATE_PATH)
    generate_self_signed_certificate(certificate_path=certificate_path, key_path=key_path)
    issuer, subject, thumbprint = linuxutil.get_cert_info(certificate_path)

    # try to extract optional metadata
    unknown = "Unknown"
    asset_tag = unknown
    vm_id = unknown
    is_azure_vm = False
    try:
        dmidecode = invoke_dmidecode()
        is_azure_vm = linuxutil.is_azure_vm(dmidecode)
        if is_azure_vm:
            asset_tag = linuxutil.get_azure_vm_asset_tag()
        else:
            asset_tag = False
        vm_id = linuxutil.get_vm_unique_id_from_dmidecode(sys.byteorder, dmidecode)
    except Exception as e:
        print (str(e))
        pass
    
    # generate payload for registration request
    date = datetime.datetime.utcnow().isoformat() + "0-00:00"
    payload = {'RunbookWorkerGroup': hybrid_worker_group_name,
               "MachineName": socket.gethostname().split(".")[0],
               "IpAddress": get_ip_address(),
               "Thumbprint": thumbprint,
               "Issuer": issuer,
               "OperatingSystem": 2,
               "SMBIOSAssetTag": asset_tag,
               "VirtualMachineId": vm_id,
               "Subject": subject}

    # the signature generation is based on agent service contract
    payload_hash = sha256_digest(payload)
    b64encoded_payload_hash = base64.b64encode(payload_hash)
    signature = generate_hmac(b64encoded_payload_hash.decode("utf-8") + "\n" + date, automation_account_key)
    b64encoded_signature = base64.b64encode(signature)

    headers = {'Authorization': 'Shared ' + b64encoded_signature.decode("utf-8"),
               'ProtocolVersion': "2.0",
               'x-ms-date': date,
               "Content-Type": "application/json"}

    # agent service registration request
    http_client_factory = httpclientfactory.HttpClientFactory(certificate_path, key_path, options.test)
    http_client = http_client_factory.create_http_client(sys.version_info)
    url = registration_endpoint + "/HybridV2(MachineId='" + machine_id + "')"
    response = http_client.put(url, headers=headers, data=payload)
    if response.status_code != 200:
        raise Exception("Failed to register worker. [response_status=" + str(response.status_code) + "]")

    registration_response = json.loads(response.raw_data)
    account_id = registration_response["AccountId"]
    create_worker_configuration_file(registration_response["jobRuntimeDataServiceUri"], account_id,
                                     hybrid_worker_group_name, machine_id, DIY_WORKING_DIR,
                                     DIY_STATE_PATH, certificate_path, key_path, registration_endpoint,
                                     workspace_id, thumbprint, vm_id, is_azure_vm, options.gpg_keyring, options.test)

    # generate working directory path
    diydirs.create_persistent_diy_dirs()

    print ("Registration successful!")


def deregister(options):
    environment_prerequisite_validation()
    registration_endpoint = options.registration_endpoint
    automation_account_key = options.automation_account_key
    workspace_id = options.workspace_id

    # assert workspace exists on the box
    state_base_path = "/var/opt/microsoft/omsagent/" + workspace_id + "/state/"
    working_directory_base_path = "/var/opt/microsoft/omsagent/" + workspace_id + "/run/"
    if os.path.exists(state_base_path) is False or os.path.exists(working_directory_base_path) is False:
        raise Exception("Invalid workspace id. Is the specified workspace id registered as the OMSAgent "
                        "primary worksapce?")

    worker_conf_path = os.path.join(DIY_STATE_PATH, "worker.conf")
    certificate_path = os.path.join(DIY_STATE_PATH, "worker_diy.crt")
    key_path = os.path.join(DIY_STATE_PATH, "worker_diy.key")

    if os.path.exists(worker_conf_path) is False:
        raise Exception("Unable to deregister, no worker configuration found on disk.")

    if os.path.exists(certificate_path) is False or os.path.exists(key_path) is False:
        raise Exception("Unable to deregister, no worker certificate/key found on disk.")

    issuer, subject, thumbprint = linuxutil.get_cert_info(certificate_path)

    if os.path.exists(worker_conf_path) is False:
        raise Exception("Missing worker configuration.")

    if os.path.exists(certificate_path) is False:
        raise Exception("Missing worker certificate.")

    if os.path.exists(key_path) is False:
        raise Exception("Missing worker key.")

    config = configparser.ConfigParser()
    config.read(worker_conf_path)
    machine_id = config.get("worker-required", "machine_id")

    # generate payload for registration request
    date = datetime.datetime.utcnow().isoformat() + "0-00:00"
    payload = {"Thumbprint": thumbprint,
               "Issuer": issuer,
               "Subject": subject}

    # the signature generation is based on agent service contract
    payload_hash = sha256_digest(payload)
    b64encoded_payload_hash = base64.b64encode(payload_hash)
    signature = generate_hmac(b64encoded_payload_hash.decode() + '\n' + date, automation_account_key)
    b64encoded_signature = base64.b64encode(signature)

    headers = {'Authorization': 'Shared ' + b64encoded_signature.decode(),
               'ProtocolVersion': "2.0",
               'x-ms-date': date,
               "Content-Type": "application/json"}

    # agent service registration request
    http_client_factory = httpclientfactory.HttpClientFactory(certificate_path, key_path, options.test)
    http_client = http_client_factory.create_http_client(sys.version_info)
    url = registration_endpoint + "/Hybrid(MachineId='" + machine_id + "')"
    response = http_client.delete(url, headers=headers, data=payload)

    if response.status_code != 200:
        raise Exception("Failed to deregister worker. [response_status=" + str(response.status_code) + "]")
    if response.status_code == 404:
        raise Exception("Unable to deregister. Worker not found.")
    print ("Successfuly deregistered worker.")

    print ("Cleaning up left over directories.")

    try:
        shutil.rmtree(DIY_STATE_PATH)
        print ("Removed state directory.")
    except:
        raise Exception("Unable to remove state directory base path.")

    try:
        shutil.rmtree(DIY_WORKING_DIR)
        print ("Removed working directory.")
    except:
        raise Exception("Unable to remove working directory base path.")


def environment_prerequisite_validation():
    """Validates that basic environment requirements are met for the onboarding operations."""
    nxautomation_username = "nxautomation"
    if linuxutil.is_existing_user(nxautomation_username) is False:
        raise Exception("Missing user : " + nxautomation_username + ". Are you running the lastest OMSAgent version?")

    omsagent_username = "omsagent"
    if linuxutil.is_existing_user(omsagent_username) is False:
        raise Exception("Missing user : " + omsagent_username + ".")

    omiusers_group_name = "omiusers"
    if linuxutil.is_existing_group(omiusers_group_name) is False:
        raise Exception("Missing group : " + omiusers_group_name + ".")

    nxautomation_group_name = "nxautomation"
    if linuxutil.is_existing_group(omiusers_group_name) is False:
        raise Exception("Missing group : " + nxautomation_group_name + ".")


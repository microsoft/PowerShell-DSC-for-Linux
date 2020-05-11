#!/usr/bin/env python3
# ====================================
#  Copyright (c) Microsoft Corporation. All rights reserved.
# ====================================

from optparse import OptionParser
import os
import sys
import configparser
import packagesimportutil

# append worker binary source path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
packagesimportutil.add_all_packages_under_automationworker_to_sys_path()

# since we are using the worker httpclient, some configuration values are expected
from worker import configuration3 as configuration
from worker import diydirs


def get_config_file_path():
    return os.path.join(diydirs.DIY_STATE_PATH, "worker.conf")

def set_signature_enforcement_policy(node_locked):
    config_file_path = get_config_file_path()
    if os.path.isfile(config_file_path) is False:
        sys.stderr.write("Could not find DIY automation worker configuration file\nPlease check if the DIY automation worker is registered for the specified workspace\n")
        sys.exit(1)

    worker_optional_section = configuration.WORKER_OPTIONAL_CONFIG_SECTION
    enforce_runbook_signature_validation = configuration.ENFORCE_RUNBOOK_SIGNATURE_VALIDATION

    config = configparser.ConfigParser()
    config.read(config_file_path)
    config.set(worker_optional_section, enforce_runbook_signature_validation, str(node_locked))
    config_file_handle = open(config_file_path, 'w')
    config.write(config_file_handle)
    config_file_handle.close()

    # Verify that the entry was made
    config.read(config_file_path)
    assert config.get(worker_optional_section, enforce_runbook_signature_validation).__eq__(node_locked)




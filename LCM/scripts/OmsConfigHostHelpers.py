#!/usr/bin/python
import json
import time
import datetime
import os

def write_omsconfig_host_telemetry(message):
    omsagent_telemetry_path = '/var/opt/microsoft/omsconfig/status'
    dsc_host_telemetry_path = os.path.join(omsagent_telemetry_path, 'omsconfighost')

    if os.path.isfile(dsc_host_telemetry_path):
        with open(dsc_host_telemetry_path) as host_telemetry_file:
            host_telemetry_json = json.load(host_telemetry_file)
    else:
        if not os.path.exists(omsagent_telemetry_path):
            os.makedirs(omsagent_telemetry_path)
        os.mknod(dsc_host_telemetry_path)
        host_telemetry_json = {}
        host_telemetry_json['operation'] = 'omsconfighost'
        host_telemetry_json['message'] = ''
        host_telemetry_json['success'] = 1

    host_telemetry_json['message'] += message

    with open(dsc_host_telemetry_path, 'a+') as host_telemetry_file:
        json.dump(host_telemetry_json, host_telemetry_file)

def write_omsconfig_host_event(pathToCurrentScript, dsc_host_switch_exists):
    msg_template = '<OMSCONFIGLOG>[{}] [{}] [{}] [{}] [{}:{}] {}</OMSCONFIGLOG>'
    timestamp = datetime.datetime.fromtimestamp(time.time()).strftime('%Y/%m/%d %H:%M:%S')
    if dsc_host_switch_exists:
        msg_buffer = 'Using dsc_host'
    else:
        msg_buffer = 'Falling back to OMI'
    message = msg_template.format(timestamp, os.getpid(), 'INFO', 0, pathToCurrentScript, 0, msg_buffer)
    write_omsconfig_host_telemetry(message)

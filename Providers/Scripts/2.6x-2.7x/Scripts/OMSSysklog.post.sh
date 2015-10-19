#!/bin/bash
cp /etc/opt/microsoft/omsagent/conf/sysklog-oms.conf /etc/syslog.conf
service syslog reload

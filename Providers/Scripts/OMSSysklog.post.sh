#!/bin/bash
cp --force /etc/opt/omi/conf/omsconfig/sysklog-oms.conf /etc/syslog.conf
service syslog restart

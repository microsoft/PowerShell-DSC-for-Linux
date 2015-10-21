#!/bin/bash
cp --force /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/rsyslog.d/95-omsagent.conf
service rsyslog restart


#!/bin/bash
if [ $1="1" ]; then
    cp --force /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/rsyslog.conf
else
    cp --force /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/rsyslog.d/95-omsagent.conf
fi
service rsyslog restart


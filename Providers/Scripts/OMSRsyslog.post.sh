#!/bin/bash
if [ "$1" = "1" ]; then
    if [ ! -d /etc/rsyslog.d ]; then 
        cp --force /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/rsyslog.conf
    fi
else
    cp --force /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/rsyslog.d/95-omsagent.conf
fi
service rsyslog restart


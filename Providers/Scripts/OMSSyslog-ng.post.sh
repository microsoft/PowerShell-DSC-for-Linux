#!/bin/bash
cp --force /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf /etc/syslog-ng/syslog-ng.conf
ps -A | grep syslog-ng
if [ $? -eq 0 ]; then
    service syslog-ng restart
else
    service syslog restart
fi

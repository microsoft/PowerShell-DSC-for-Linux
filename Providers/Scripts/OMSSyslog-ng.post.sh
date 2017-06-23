#!/bin/bash
cp --force /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf /etc/syslog-ng/syslog-ng.conf
service syslog restart

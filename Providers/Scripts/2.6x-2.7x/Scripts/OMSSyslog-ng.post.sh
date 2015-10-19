#!/bin/bash
cp /etc/opt/microsoft/omsagent/conf/syslog-ng-oms.conf /etc/syslog-ng/syslog-ng.conf
service syslog reload

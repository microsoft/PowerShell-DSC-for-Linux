#!/bin/bash
cp /opt/microsoft/omsagent/conf/syslog-ng-oms.conf /etc/syslog-ng/syslog-ng.conf
service syslog reload

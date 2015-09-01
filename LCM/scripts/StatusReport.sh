#!/bin/sh

# $0 JobId (StartTime|EndTime) [ErrorMessage]

curDate=`date +%Y-%m-%dT%T.%N%:z`

if [ "$2" = "EndTime" ]; then
    if [ -n "$3" ]; then
	ErrorMessage="\"{\\\"ErrorMessage\\\":\\\"$3\\\"}\""
	Errors=",\\\"Error\\\":\\\"$3\\\""
    else
	ErrorMessage=""
	Errors=""
    fi
    output="{\"JobId\":\"$1\",\"ConfigurationVersion\":\"2.0.0\",\"EndTime\":\"$curDate\",\"Errors\":[$ErrorMessage],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\"$Errors}\"]}"
else
    IPAddress=`ip addr | grep 'inet' | awk '{print $2}' | sed 's/\/.*//' | tr "\n" ";"`
    NodeName=`hostname`
    output="{\"JobId\":\"$1\",\"OperationType\":\"Consistency\",\"NodeName\":\"$NodeName\",\"IpAddress\":\"$IPAddress\",\"LCMVersion\":\"2.0\",\"ReportFormatVersion\":\"1.0\",\"StartTime\":\"$curDate\",\"Errors\":[],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\"}\"]}"

fi

echo $output
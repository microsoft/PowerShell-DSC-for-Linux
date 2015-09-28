#!/bin/sh

# $0 JobId (StartTime|EndTime) [ErrorMessage [SourceInfo ModuleName DurationInSeconds InstanceName StartDate ResourceName ModuleVersion RebootRequested ResourceId ConfigurationName InDesiredState]]

curDate=`date +%Y-%m-%dT%T.%N%:z`
ErrorMessage=""
Errors=""
RNIDS=""

if [ "$2" = "EndTime" ]; then
    if [ -n "$3" ]; then
	ErrorMessage="\"{\\\"ErrorMessage\\\":\\\"$3\\\"}\""
	Errors=",\\\"Error\\\":\\\"$3\\\""
	if [ -n "${14}" ]; then
	    RNIDS="{\\\"SourceInfo\\\":\\\"$4\\\",\\\"ModuleName\\\":\\\"$5\\\",\\\"DurationInSeconds\\\":\\\"0\\\",\\\"InstanceName\\\":\\\"$7\\\",\\\"StartDate\\\":\\\"$curDate\\\",\\\"ResourceName\\\":\\\"$9\\\",\\\"ModuleVersion\\\":\\\"${10}\\\",\\\"RebootRequested\\\":\\\"${11}\\\",\\\"ResourceId\\\":\\\"${12}\\\",\\\"ConfigurationName\\\":\\\"${13}\\\",\\\"InDesiredState\\\":\\\"${14}\\\"}"
	else
	    ErrorMessage="\"{\\\"Locale\\\":\\\"en-US\\\",\\\"ErrorCode\\\":\\\"1\\\",\\\"ErrorMessage\\\":\\\"$3\\\",\\\"ResourceId\\\":\\\"DSCEngine\\\",\\\"ErrorSource\\\":\\\"DSCEngine\\\"}\""
	fi
	output="{\"JobId\":\"$1\",\"ConfigurationVersion\":\"2.0.0\",\"ReportFormatVersion\":\"2.0\",\"LCMVersion\":\"2.0\",\"EndTime\":\"$curDate\",\"Errors\":[$ErrorMessage],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\",\\\"ResourcesNotInDesiredState\\\":[$RNIDS]$Errors}\"]}"
    else
	output="{\"JobId\":\"$1\",\"ConfigurationVersion\":\"2.0.0\",\"ReportFormatVersion\":\"2.0\",\"LCMVersion\":\"2.0\",\"EndTime\":\"$curDate\",\"Errors\":[$ErrorMessage],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\"}\"]}"
    fi
else
    IPAddress=`ip addr | grep 'inet' | awk '{print $2}' | sed 's/\/.*//' | tr "\n" ";" | cut -c 1-254`
    NodeName=`hostname`
    output="{\"JobId\":\"$1\",\"OperationType\":\"Consistency\",\"NodeName\":\"$NodeName\",\"IpAddress\":\"$IPAddress\",\"ReportFormatVersion\":\"2.0\",\"LCMVersion\":\"2.0\",\"StartTime\":\"$curDate\",\"Errors\":[],\"StatusData\":[\"{\\\"Locale\\\":\\\"en-US\\\"}\"]}"

fi

echo $output > /etc/opt/omi/conf/dsc/last_statusreport
echo $output
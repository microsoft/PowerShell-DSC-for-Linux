#!/bin/sh
NodeName=`hostname`

IPAddress=`ip addr | grep 'inet' | awk '{print $2}' | sed 's/\/.*//' | tr "\n" ";" | cut -c 1-254`;

RegistrationKey="$3"

if [ -n "$4" ]; then
    ConfigurationName="\"ConfigurationNames\":[\"$4\"],"
else
    ConfigurationName=""
fi

FriendlyName="DSC-OaaS Client Authentication"
Issuer=`openssl x509 -text -in <OAAS_CERTPATH> | grep Issuer: | head -n 1 | awk '{print $2}'`
NotAfter_pre=`openssl x509 -dates -in <OAAS_CERTPATH> | grep notAfter | sed 's/^.*=//'`
NotAfter=`date --date="${NotAfter_pre}" +%Y-%m-%dT%T.%7N%:z`
NotBefore_pre=`openssl x509 -dates -in <OAAS_CERTPATH> | grep notBefore | sed 's/^.*=//'`
NotBefore=`date --date="${NotBefore_pre}" +%Y-%m-%dT%T.%7N%:z`
Subject=`openssl x509 -text -in <OAAS_CERTPATH> | grep Subject: | head -n 1 | awk '{print $2}'`
PublicKey=`openssl x509 -in <OAAS_CERTPATH> -pubkey -noout | awk 'NR>2 { print line } { line=$0 }' | tr -d "\n"`
Thumbprint=`openssl x509 -noout -in <OAAS_CERTPATH> -fingerprint | sed 's/^.*=//' | tr -d :`

if [ -n "$2" ]; then
    RegistrationMessageType="$2"
else
    RegistrationMessageType="ConfigurationRepository"
fi

x_ms_date=`date --utc +%Y-%m-%dT%T.%7NZ | tr -d "\n"`

requestBody="{\"AgentInformation\":{\"LCMVersion\":\"2.0\",\"NodeName\":\"$NodeName\",\"IPAddress\":\"$IPAddress\"},$ConfigurationName\"RegistrationInformation\":{\"CertificateInformation\":{\"FriendlyName\":\"$FriendlyName\",\"Issuer\":\"$Issuer\",\"NotAfter\":\"$NotAfter\",\"NotBefore\":\"$NotBefore\",\"Subject\":\"$Subject\",\"PublicKey\":\"$PublicKey\",\"Thumbprint\":\"$Thumbprint\",\"Version\":3},\"RegistrationMessageType\":\"$RegistrationMessageType\"}}"

contentHash=`echo -n "$requestBody" | openssl dgst -binary -sha256 | openssl enc -base64 | tr -d "\n"`

stringToSign=`printf "${contentHash}\n${x_ms_date}"`

signature=`echo -n "$stringToSign" | openssl dgst -binary -sha256 -hmac "$RegistrationKey" | openssl enc -base64 | tr -d "\n"`

if [ "$1" = "body" ]; then
    printf "$requestBody"
elif [ "$1" = "header" ]; then
    echo "x-ms-date: $x_ms_date"
    echo "Authorization: Shared $signature"
else
    echo "x-ms-date: $x_ms_date"
    echo "Authorization: Shared $signature"
    printf "$requestBody"
fi


#!/bin/sh
NodeName=`hostname`

IPAddress=`ip addr | grep 'inet' | awk '{print $2}' | sed 's/\/.*//' | tr "\n" ";"`;

RegistrationKey="$3"

if [ -n "$4" ]; then
    ConfigurationName="\"ConfigurationNames\":[\"$4\"],"
else
    ConfigurationName=""
fi

#TODO: change?
FriendlyName="DSC-OaaS Client Authentication"
Issuer=`openssl x509 -text -in /etc/opt/omi/ssl/oaas.crt | grep Issuer: | head -n 1 | awk '{print $2}'`
NotAfter_pre=`openssl x509 -dates -in /etc/opt/omi/ssl/oaas.crt | grep notAfter | sed 's/^.*=//'`
NotAfter=`date --date="${NotAfter_pre}" +%Y-%m-%dT%T.%7N%:z`
NotBefore_pre=`openssl x509 -dates -in /etc/opt/omi/ssl/oaas.crt | grep notBefore | sed 's/^.*=//'`
NotBefore=`date --date="${NotBefore_pre}" +%Y-%m-%dT%T.%7N%:z`
Subject=`openssl x509 -text -in /etc/opt/omi/ssl/oaas.crt | grep Subject: | head -n 1 | awk '{print $2}'`
PublicKey=`openssl x509 -in /etc/opt/omi/ssl/oaas.crt -pubkey -noout | awk 'NR>2 { print line } { line=$0 }' | tr -d "\n"`
Thumbprint=`openssl x509 -noout -in /etc/opt/omi/ssl/oaas.crt -fingerprint | sed 's/^.*=//' | tr -d :`

if [ -n "$2" ]; then
    RegistrationMessageType="$2"
else
    RegistrationMessageType="ConfigurationRepository"
fi

x_ms_date=`date --utc +%Y-%m-%dT%T.%7NZ | tr -d "\n"`

requestBody="{\"AgentInformation\":{\"LCMVersion\":\"2.0\",\"NodeName\":\"$NodeName\",\"IPAddress\":\"$IPAddress\"},$ConfigurationName\"RegistrationInformation\":{\"CertificateInformation\":{\"FriendlyName\":\"$FriendlyName\",\"Issuer\":\"$Issuer\",\"NotAfter\":\"$NotAfter\",\"NotBefore\":\"$NotBefore\",\"Subject\":\"$Subject\",\"PublicKey\":\"$PublicKey\",\"Thumbprint\":\"$Thumbprint\",\"Version\":3},\"RegistrationMessageType\":\"$RegistrationMessageType\"}}"

# BEGIN TEST CODE
#testBody='{"AgentInformation":{"LCMVersion":"2.0","NodeName":"DESKTOP-GDU6CNU","IPAddress":"10.30.69.164;127.0.0.1;2001:4898:200:8:4529:f306:651a:d488;2001:4898:200:8:3520:e3f2:542c:cf95;fe80::4529:f306:651a:d488%2;::2000:0:0:0;::1;::2000:0:0:0"},"ConfigurationNames":["FileConfig"],"RegistrationInformation":{"CertificateInformation":{"FriendlyName":"DSC-OaaS Client Authentication","Issuer":"CN=DSC-OaaS","NotAfter":"2016-07-20T08:20:33.0000000-07:00","NotBefore":"2015-07-20T15:10:34.0000000-07:00","Subject":"CN=DSC-OaaS","PublicKey":"U3lzdGVtLlNlY3VyaXR5LkNyeXB0b2dyYXBoeS5YNTA5Q2VydGlmaWNhdGVzLlB1YmxpY0tleQ==","Thumbprint":"9A30D1E57B44DB0D5DE265619278FC67A7FAA3D6","Version":3},"RegistrationMessageType":"ConfigurationRepository"}}'

#requestBody=$testBody
#x_ms_date="2015-07-20T22:20:38.3739827Z"
# END TEST CODE

contentHash=`echo -n "$requestBody" | openssl dgst -binary -sha256 | openssl enc -base64 | tr -d "\n"`

stringToSign=`printf "${contentHash}\n${x_ms_date}"`

# TODO: replace testkey with actual registration key
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


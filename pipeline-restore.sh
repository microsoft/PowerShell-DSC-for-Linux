#!/bin/bash

sudo apt-get update

sudo apt-get install make -y
sudo apt-get install bison -y
sudo apt-get install g++ -y
sudo apt-get install rpm -y
sudo apt-get install librpm-dev -y
sudo apt-get install libpam0g-dev -y
sudo apt-get install libssl-dev -y
#sudo apt-get install libmysqlclient-dev -y
sudo apt-get install curl -y
sudo apt-get install libcurl4-gnutls-dev -y
sudo apt-get install zlib1g -y
sudo apt-get install zlib1g-dev -y
sudo apt-get install openssl -y
sudo apt-get install pkg-config -y
sudo apt-get install libkrb5-dev -y

cd /tmp
wget -q https://www.python.org/ftp/python/2.4.6/Python-2.4.6.tgz
wget -q https://sourceforge.net/projects/ctypes/files/ctypes/1.0.2/ctypes-1.0.2.tar.gz

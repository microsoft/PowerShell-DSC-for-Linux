#!/usr/bin/env python
#

import os
import os.path
import re
import subprocess
import platform

class DistroCategory:
    debian = 1
    redhat = 2
    suse = 3

def run_cmd(cmd):
    proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    proc.wait()
    output = proc.stdout.read()
    code = proc.returncode
    return code, output

def get_openssl_version():
    code, cmd_result = run_cmd("openssl version")
    openssl_version = cmd_result.split()[1]
    if code == 0:
        if re.match('^1.0.*', openssl_version):
            return '100'
        if re.match('^1.1.*', openssl_version):
            return '110'
        elif re.match('^0.9.8*', openssl_version):
            return '098'
        else:
            raise Exception('This system does not have a supported version of OpenSSL installed. Supported version: 0.9.8*, 1.0.*')

def get_distro_category():
    distro_info = platform.dist()
    distro_name = distro_info[0].lower()
    distro_version = distro_info[1]
    if distro_name == 'ubuntu' or (distro_name == 'debian'):
        return DistroCategory.debian
    elif distro_name == 'centos' or distro_name == 'redhat' or distro_name == 'oracle':
        return DistroCategory.redhat
    elif distro_name == 'suse':
        return DistroCategory.suse

    raise Exception("Unsupported distro :" + distro_name + "; distro_version: " + distro_version)

def install_dsc_packages():
    openssl_version = get_openssl_version()
    distro_category = get_distro_category()

    if distro_category == DistroCategory.debian:
        if openssl_version == '098':
            dsc_package_path = 'https://github.com/Microsoft/PowerShell-DSC-for-Linux/releases/download/v1.1.1-926/dsc-1.1.1-926.ssl_098.x64.deb'
            dsc_package_file_name = './dsc-1.1.1-926.ssl_098.x64.deb'
        elif openssl_version == '100':
            dsc_package_path = 'https://github.com/Microsoft/PowerShell-DSC-for-Linux/releases/download/v1.1.1-926/dsc-1.1.1-926.ssl_100.x64.deb'
            dsc_package_file_name = './dsc-1.1.1-926.ssl_100.x64.deb'
        elif openssl_version == '110':
            dsc_package_path = 'https://github.com/Microsoft/PowerShell-DSC-for-Linux/releases/download/v1.1.1-926/dsc-1.1.1-926.ssl_110.x64.deb'
            dsc_package_file_name = './dsc-1.1.1-926.ssl_110.x64.deb'
        else:
            raise Exception('This system does not have a supported version of OpenSSL installed. Supported version: 0.9.8*, 1.0.*')

        code, cmd_result = run_cmd("wget " + dsc_package_path)
        if code != 0:
            raise Exception('dsc package download failed : ' + cmd_result)
        run_cmd("dpkg -i " + dsc_package_file_name)
    elif distro_category == DistroCategory.redhat or distro_category == DistroCategory.suse:
        if openssl_version == '098':
            dsc_package_path = 'https://github.com/Microsoft/PowerShell-DSC-for-Linux/releases/download/v1.1.1-926/dsc-1.1.1-926.ssl_098.x64.rpm'
            dsc_package_file_name = './dsc-1.1.1-926.ssl_098.x64.rpm'
        elif openssl_version == '100':
            dsc_package_path = 'https://github.com/Microsoft/PowerShell-DSC-for-Linux/releases/download/v1.1.1-926/dsc-1.1.1-926.ssl_100.x64.rpm'
            dsc_package_file_name = './dsc-1.1.1-926.ssl_100.x64.rpm'
        elif openssl_version == '110':
            dsc_package_path = 'https://github.com/Microsoft/PowerShell-DSC-for-Linux/releases/download/v1.1.1-926/dsc-1.1.1-926.ssl_110.x64.rpm'
            dsc_package_file_name = './dsc-1.1.1-926.ssl_110.x64.rpm'
        else:
            raise Exception('This system does not have a supported version of OpenSSL installed. Supported version: 0.9.8*, 1.0.*')

        code, cmd_result = run_cmd("wget " + dsc_package_path)
        if code != 0:
            raise Exception('dsc package download failed : ' + cmd_result)
        run_cmd("rpm -Uvh  " + dsc_package_file_name)

install_dsc_packages()
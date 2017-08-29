## Table of Contents
- [Setup DSC and OMI Repo](#setup-dsc-and-omi-repo)
- [Build OMI](#build-omi)
- [Build DSC](#build-dsc)
- [Run OMI Server](#run-omi-server)
- [Test DSC basic functionality](#test-dsc-basic-functionality)
- [Update DSC and rebuild](#update-dsc-and-rebuild)


## Setup DSC and OMI Repo

1. Clone the repo. 
   - git clone https://github.com/Microsoft/PowerShell-DSC-for-Linux.git 
   - cd PowerShell-DSC-for-Linux
2. mkdir omi-1.3.0-2 
3. mkdir omi-1.0.8 
4. Download the source code for this release - https://github.com/Microsoft/omi/releases/tag/v1.3.0-2 
5. Unzip it under omi-1.3.0-2
6. Copy over everything from under omi-1.3.0-2/Unix to omi-1.0.8
7. Set up the dependent packages for OMI from https://github.com/Microsoft/Build-omi 
   - On Ubuntu 14.04 and 16.04
        - sudo apt-get install git pkg-config make g++ rpm librpm-dev libpam0g-dev libssl-dev libkrb5-dev gawk
8. Set up dependent packages for DSC 
   - sudo apt-get install libcurl4-gnutls-dev

## Build OMI

1. cd omi-1.3.0-2/Unix
2. ./configure -–dev –-enable-debug
3. make -j
4. Copy everything from omi-1.3.0-2/Unix/Output to omi-1.0.8/ (This is a temporary workaround and needs to be fixed)

## Build DSC

1. cd PowerShell-DSC-for-Linux
2. ./configure --no-rpm --no-dpkg –local –-enable-debug
3. make -j
4. Open LCM/GNUmakefile. There will be 3 occurrences of the word ‘ConsistencyInvoker’. comment out the last 2 occurrences that mention ‘ConsistencyInvoker’
5. make reg

## Run OMI Server

1. cd omi-1.3.0-2/Unix/Output/bin
2. sudo omiserver -d

## Test DSC basic functionality

1. cd PowerShell-DSC-for-Linux/intermediate/Scripts
2. sudo ./GetDscLocalConfigurationManager.py

## Update DSC and rebuild 
As part of developer workflow, anytime we make changes to DSC code, these are the steps we need to follow
1. Sudo killall omiserver           # Kill OMI Server before building OMI
2. Delete output folder from under
   - DSC-Linux/omi-1.0.8
   - DSC-Linux/omi-1.3.0-2/Unix
3. Perform all the steps under Build OMI section
4. Make your DSC changes
4. Perform all steps under Build DSC section


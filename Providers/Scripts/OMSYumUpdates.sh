#!/bin/bash

if [ "$1" = "" ]; then
    yum -q check-update
else
    yum info available $1
fi

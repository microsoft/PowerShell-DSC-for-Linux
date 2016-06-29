#!/bin/bash

if [ "$1" = "" ]; then
    yum check-update
else
    yum info available $1
fi

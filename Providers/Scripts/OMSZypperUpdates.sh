#!/bin/bash

# The first time the arg is 'lu'.
if [ "$1" = "lu" ]; then
    zypper -qn refresh
fi
zypper -q $1 



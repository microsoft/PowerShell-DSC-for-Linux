#!/bin/bash

# The first time the arg is 'lu'.
if [ "$1" = "lu" ]; then
    zypper -qn refresh &> /dev/null
fi
zypper -q $1 



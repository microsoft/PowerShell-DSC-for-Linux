#!/bin/bash

if [ "$1" = "" ]; then
    yum check-update
else
    if [ -e "/usr/bin/repoquery" ]; then
	repoquery --queryformat "Name : %{NAME}\nArch : %{ARCH}\nVersion :  %{EPOCH}:%{VERSION}\nRelease : %{RELEASE}\nRepo : %{REPO}\nBuildtime : %{BUILDTIME}" $1
    else
	yum info available $1
    fi
fi

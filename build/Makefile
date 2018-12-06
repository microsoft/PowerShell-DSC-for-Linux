# -*- mode: Makefile; -*- 
#--------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation.  All rights reserved.
#--------------------------------------------------------------------------------
# 2014-01-17
#--------------------------------------------------------------------------------

all:
	cd ../; \
	./configure; \
	ln -s ../omi/Unix ./omi-1.0.8; \
	ln -s ./release ./target
	make -C ..
local:
	cd ../; \
	./configure --local; \
	ln -s ../omi/Unix ./omi-1.0.8; \
	ln -s ./release ./target
	make -C ..

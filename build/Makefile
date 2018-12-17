# -*- mode: Makefile; -*- 
#--------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation.  All rights reserved.
#--------------------------------------------------------------------------------
# 2014-01-17
#--------------------------------------------------------------------------------

all:
	cd ../; \
	./configure; \
	ln -fs ../omi/Unix ./omi-1.0.8; \
	ln -fs ./release ./target
	make -C ..
local:
	cd ../; \
	./configure --local; \
	ln -fs ../omi/Unix ./omi-1.0.8; \
	ln -fs ./release ./target
	make -C ..

all:
	make -C OMI
	make -C LCM
	make -C Providers

reg:
	make -C Providers reg
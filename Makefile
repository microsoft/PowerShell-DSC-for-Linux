all:
	make -C omi-1.0.8
	make -C LCM
	make -C Providers

reg:
	make -C LCM deploydsc
	make -C Providers reg

all: lcm providers

reg: lcmreg providersreg

lcm:
	make -C omi-1.0.8
	make -C LCM

lcmreg:
	make -C LCM deploydsc

providers:
	make -C Providers

providersreg:
	make -C Providers reg

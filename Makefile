all: lcm providers

reg: lcmreg

lcm:
	make -C omi-1.0.8
	make -C LCM

lcmreg:
	make -C LCM deploydsc

providers:
	make -C Providers

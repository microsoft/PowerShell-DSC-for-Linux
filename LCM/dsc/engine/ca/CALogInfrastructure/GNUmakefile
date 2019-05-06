DSCTOP = ../../..
TOP = ../../../..
include $(TOP)/config.mak

LIBRARY = CALogInfrastructure

SOURCES = \
	CALog.c 

INCLUDES = \
	$(OMI) \
	$(OMI)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(TOP)/codec/common \
	$(OMI)/nits/base \
	$(TOP)/json_parson

DEFINES = MI_CONST= HOOK_BUILD $(BUILD_OMS)

include $(OMI)/mak/rules.mak

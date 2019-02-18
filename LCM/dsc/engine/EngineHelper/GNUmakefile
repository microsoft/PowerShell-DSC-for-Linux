DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

LIBRARY = EngineHelper

SOURCES = \
	EngineHelper.c \
	EventWrapper.c \
	PAL_Extension.c \
	plog_wrapper.cpp

INCLUDES = $(OMI) $(OMI)/common $(DSCTOP)/common/inc $(TOP)/codec/common $(OMI)/nits/base $(DSCTOP)/engine $(TOP)/json_parson $(TOP)/plog/include 

DEFINES = MI_CONST= HOOK_BUILD $(BUILD_OMS)

include $(OMI)/mak/rules.mak


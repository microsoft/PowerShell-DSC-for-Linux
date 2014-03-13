DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

LIBRARY = EngineHelper

SOURCES = \
	EngineHelper.c \
	EventWrapper.c \
	PAL_Extension.c

INCLUDES = $(TOP) $(TOP)/common $(DSCTOP)/common/inc $(TOP)/codec/common $(TOP)/nits/base $(DSCTOP)/engine

DEFINES = MI_CONST= HOOK_BUILD

include $(TOP)/mak/rules.mak


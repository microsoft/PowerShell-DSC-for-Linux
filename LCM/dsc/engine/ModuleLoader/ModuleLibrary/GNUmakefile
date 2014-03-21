DSCTOP = ../../..
TOP = ../../../..
include $(TOP)/config.mak

LIBRARY = ModuleHandler

SOURCES = \
	ModuleHandler.c \
	ModuleValidator.c 

INCLUDES = $(OMI) $(OMI)/common $(DSCTOP)/common/inc $(DSCTOP)/engine/EngineHelper $(DSCTOP)/engine $(TOP)/codec/common $(OMI)/nits/base

DEFINES = MI_CONST= HOOK_BUILD

include $(OMI)/mak/rules.mak


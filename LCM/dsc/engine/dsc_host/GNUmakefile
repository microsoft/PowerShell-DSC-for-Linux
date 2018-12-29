DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

LIBRARY = dsc_host

SOURCES = \
        dsc_host.c

INCLUDES = \
        $(OMI) \
        $(OMI)/common \
        $(DSCTOP)/common/inc \
        $(DSCTOP)/engine/EngineHelper \
        $(DSCTOP)/engine \
        $(DSCTOP)/engine/ca/CAInfrastructure \
        $(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
        $(TOP)/codec/common \
        $(OMI)/nits/base

DEFINES = MI_CONST= HOOK_BUILD $(BUILD_OMS)

include $(OMI)/mak/rules.mak


DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

ifeq ($(BUILD_OMS),BUILD_OMS)
CPROGRAM = OMSConsistencyInvoker
else
CPROGRAM = ConsistencyInvoker
endif
SOURCES = ConsistencyInvoker.c

INCLUDES = $(OMI) $(OMI)/common $(TOP)/codec/common $(OMI)/nits/base $(DSCTOP)/common/inc $(DSCTOP)/engine/EngineHelper

DEFINES = $(BUILD_OMS) DSC_SCRIPT_PATH=\"$(DSC_SCRIPT_PATH)\"

LIBRARIES = mi $(PALLIBS)

include $(OMI)/mak/rules.mak

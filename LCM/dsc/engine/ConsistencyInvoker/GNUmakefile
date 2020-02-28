DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

ifeq ($(BUILD_OMS),BUILD_OMS)
CPROGRAM = OMSConsistencyInvoker
else
CPROGRAM = ConsistencyInvoker
endif
SOURCES = ConsistencyInvoker.c

INCLUDES = $(OMI) $(OMI)/common $(TOP)/codec/common $(OMI)/nits/base $(DSCTOP)/common/inc $(DSCTOP)/engine/EngineHelper $(TOP)/json_parson

DEFINES = $(BUILD_OMS) DSC_SCRIPT_PATH=\"$(DSC_SCRIPT_PATH)\" DSC_HOST_BASE_PATH=\"$(DSC_HOST_BASE_PATH)\"

LIBRARIES = mi $(PALLIBS)

include $(OMI)/mak/rules.mak

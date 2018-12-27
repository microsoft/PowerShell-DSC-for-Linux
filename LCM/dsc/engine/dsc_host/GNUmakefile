DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

ifeq ($(BUILD_OMS),BUILD_OMS)
CPROGRAM = oms_dsc_host
else
CPROGRAM = dsc_host
endif
SOURCES = dsc_host.c \
		  dsc_host_response_handler.c \
          dummy_lcm_interface.c

INCLUDES = $(OMI) $(OMI)/common $(TOP)/codec/common $(OMI)/nits/base $(DSCTOP)/common/inc $(DSCTOP)/engine/EngineHelper

DEFINES = $(BUILD_OMS) DSC_SCRIPT_PATH=\"$(DSC_SCRIPT_PATH)\"

LIBRARIES = mi $(PALLIBS)

include $(OMI)/mak/rules.mak

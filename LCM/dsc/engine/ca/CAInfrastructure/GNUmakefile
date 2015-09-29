DSCTOP = ../../..
TOP = ../../../..
include $(TOP)/config.mak

LIBRARY = CAEngine

SOURCES = \
	CAEngine.c \
	CAValidate.c \
	WebPullClient.c

INCLUDES = \
	$(TOP)/../ext/curl/current_platform/include \
	$(OMI) \
	$(OMI)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine \
	$(DSCTOP)/engine/ConfigurationManager \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(OMI)/nits/base

ifeq ($(BUILD_LOCAL),1)
DEFINES = MI_CONST= HOOK_BUILD
else
DEFINES = MI_CONST= HOOK_BUILD DSC_PACKAGE_BUILD
endif

include $(OMI)/mak/rules.mak

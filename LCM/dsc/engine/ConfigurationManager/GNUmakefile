DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

LIBRARY = ConfigurationManager

SOURCES = \
	BeginEndLcmOperation.c \
	hashmap.c \
	LocalConfigManagerHelper.c \
	LocalConfigurationManager.c \
        MSFT_DSCLocalConfigurationManager.c \
	OMI_LocalConfigManagerHelper.c \
        omi_schema.c 

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

DEFINES = MI_CONST= HOOK_BUILD

include $(OMI)/mak/rules.mak


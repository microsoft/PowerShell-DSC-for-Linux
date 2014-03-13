DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

LIBRARY = ConfigurationManager

SOURCES = \
	BeginEndLcmOperation.c \
	LocalConfigManagerHelper.c \
	LocalConfigurationManager.c \
        MSFT_DSCLocalConfigurationManager.c \
		OMI_LocalConfigManagerHelper.c \
        omi_schema.c 

INCLUDES = \
	$(TOP) \
	$(TOP)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine \
	$(DSCTOP)/engine/ca/CAInfrastructure \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(TOP)/nits/base

DEFINES = MI_CONST= HOOK_BUILD

include $(TOP)/mak/rules.mak


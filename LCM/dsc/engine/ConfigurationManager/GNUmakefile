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
	RegistrationManager.c \
	RegistrationManagerHelper.c \
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
	$(OMI)/nits/base \
	$(TOP)/json_parson

DEFINES = MI_CONST= HOOK_BUILD $(BUILD_OMS)

include $(OMI)/mak/rules.mak


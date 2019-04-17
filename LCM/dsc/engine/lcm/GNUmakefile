DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

ifeq ($(BUILD_OMS),BUILD_OMS)
CXXSHLIBRARY = omsconfig
else
CXXSHLIBRARY = dsccore
endif

SOURCES = \
	module.c \
	lcm.traps.c 

INCLUDES = \
	$(TOP)/../ext/curl/current_platform/include \
	$(OMI) \
	$(OMI)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine/ConfigurationManager \
	$(DSCTOP)/engine/ca/CAInfrastructure \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(OMI)/nits/base \
	$(TOP)/json_parson

DEFINES = MI_CONST= HOOK_BUILD $(BUILD_OMS)

LIBRARIES =  ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure mi pal omi_error  micodec mofparser base pal curl xmlserializer

include $(OMI)/mak/rules.mak


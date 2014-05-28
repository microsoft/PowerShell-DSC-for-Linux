DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = dsccore

SOURCES = \
	module.c \
	lcm.traps.c 

INCLUDES = \
	$(OMI) \
	$(OMI)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine/ConfigurationManager \
	$(DSCTOP)/engine/ca/CAInfrastructure \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(OMI)/nits/base

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES =  ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure mi base pal omi_error  micodec mofparser

include $(OMI)/mak/rules.mak

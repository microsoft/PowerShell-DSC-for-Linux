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

LIBRARIES =  ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure mi pal omi_error  micodec mofparser http base pal

include $(OMI)/mak/rules.mak

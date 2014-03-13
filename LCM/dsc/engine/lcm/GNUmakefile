DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = dsccore

SOURCES = \
	module.c \
	lcm.traps.c 

INCLUDES = \
	$(TOP) \
	$((TOP)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine/ConfigurationManager \
	$(DSCTOP)/engine/ca/CAInfrastructure \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(TOP)/nits/base

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES =  ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure mi base pal omi_error  micodec mofparser

include $(TOP)/mak/rules.mak

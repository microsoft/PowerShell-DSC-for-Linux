DSCTOP = ../../..
TOP = ../../../..
include $(TOP)/config.mak

LIBRARY = CAEngine

SOURCES = \
	CAEngine.c \
	CAValidate.c \
	CACrypto.c

INCLUDES = \
	$(OMI) \
	$(OMI)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine \
	$(DSCTOP)/engine/ConfigurationManager \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(OMI)/nits/base

DEFINES = MI_CONST= HOOK_BUILD

include $(OMI)/mak/rules.mak

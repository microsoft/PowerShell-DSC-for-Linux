DSCTOP = ../../..
TOP = ../../../..
include $(TOP)/config.mak

LIBRARY = CAEngine

SOURCES = \
	CAEngine.c \
	CAValidate.c \
	CACrypto.c

INCLUDES = \
	 $(TOP) \
	$(TOP)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine \
	$(DSCTOP)/engine/ConfigurationManager \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(TOP)/nits/base

DEFINES = MI_CONST= HOOK_BUILD

include $(TOP)/mak/rules.mak

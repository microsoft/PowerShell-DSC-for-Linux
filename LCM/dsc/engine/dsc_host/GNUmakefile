DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

CPROGRAM = dsc_host

SOURCES = \
        dsc_host.c 

INCLUDES = \
        $(OMI) \
        $(OMI)/common \
        $(DSCTOP)/common/inc \
        $(DSCTOP)/engine/EngineHelper \
        $(DSCTOP)/engine \
        $(DSCTOP)/engine/ca/CAInfrastructure \
        $(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
        $(DSCTOP)/engine/dsc_library \
        $(TOP)/codec/common \
        $(OMI)/nits/base \
        $(TOP)/json_parson 

DEFINES = MI_CONST= HOOK_BUILD $(BUILD_OMS)

LIBRARIES = dsc_library mi $(PALLIBS) ssl ConfigurationManager CAEngine EngineHelper ModuleHandler curl micodec mofparser base pal stdc++

include $(OMI)/mak/rules.mak



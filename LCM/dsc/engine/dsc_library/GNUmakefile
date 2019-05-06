DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

LIBRARY = dsc_library

SOURCES = \
        dsc_library.c 

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
        $(TOP)/json_parson \
        $(DSCTOP)/engine/ConfigurationManager 

DEFINES = MI_CONST= HOOK_BUILD $(BUILD_OMS)

# LIBRARIES =  ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure mi pal omi_error  micodec mofparser base pal curl xmlserializerLIBRARIES =  ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure mi pal omi_error  micodec mofparser base pal curl xmlserializer


include $(OMI)/mak/rules.mak


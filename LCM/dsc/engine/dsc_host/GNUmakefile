DSCTOP = ../..
TOP = ../../..
include $(TOP)/config.mak

#LIBRARY = dsc_host
# ifeq ($(BUILD_OMS),BUILD_OMS)
# CPROGRAM = dsc_host
# else
CPROGRAM = dsc_host
# endif

SOURCES = \
        dsc_host.c 
        # dsc_host.rc 
        # dsc_operations.c

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


##LIBRARIES = dsc_library mi pal ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure
#LIBRARIES = ConfigurationManager CAEngine ModuleHandler EngineHelper CALogInfrastructure mi pal omi_error  micodec mofparser base pal curl xmlserializer dsccore dsc_library mi $(PALLIBS)
LIBRARIES = dsc_library mi $(PALLIBS) ssl ConfigurationManager CAEngine EngineHelper ModuleHandler curl micodec mofparser base pal

include $(OMI)/mak/rules.mak



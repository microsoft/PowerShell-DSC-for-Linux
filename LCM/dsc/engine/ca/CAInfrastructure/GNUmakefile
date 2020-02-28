DSCTOP = ../../..
TOP = ../../../..
include $(TOP)/config.mak

LIBRARY = CAEngine

SOURCES = \
	CAEngine.c \
	CAValidate.c \
	WebPullClient.c \
	ProviderCallbacks.c \
	NativeResourceProviderMiModule.c \
	NativeResourceHostMiContext.c \
	NativeResourceManager.c

INCLUDES = \
	$(TOP)/../ext/curl/current_platform/include \
	$(OMI) \
	$(OMI)/common \
	$(DSCTOP)/common/inc \
	$(DSCTOP)/engine/EngineHelper \
	$(DSCTOP)/engine \
	$(DSCTOP)/engine/ConfigurationManager \
	$(DSCTOP)/engine/ModuleLoader/ModuleLibrary \
	$(TOP)/codec/common \
	$(OMI)/nits/base \
	$(TOP)/json_parson

DEFINES = MI_CONST= HOOK_BUILD DSC_MODULES_PATH=\"$(DSC_MODULES_PATH)\" DSC_SCRIPT_PATH=\"$(DSC_SCRIPT_PATH)\" DSC_HOST_BASE_PATH=\"$(DSC_HOST_BASE_PATH)\" $(BUILD_OMS)

include $(OMI)/mak/rules.mak

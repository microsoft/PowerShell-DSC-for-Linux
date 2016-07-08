############################################################################
#
#   Copyright (C) 1999, Microsoft Corporation.
#
#   All rights reserved.
#
############################################################################
USE_NATIVE_EH=ASYNC

USE_ATL=1
ATL_VER=70
USE_VCCOM=1
BUILD_FOR_CORESYSTEM=1
CONFIGMANAGER_LIB = $(PROJECT_OBJ_ROOT)\DSC\Engine\configurationmanager\$(O)\ConfigurationManager.lib
CALOGINFRA_LIB = $(PROJECT_OBJ_ROOT)\dsc\engine\ca\caloginfrastructure\$O\caloginfrastructure.lib
MOFCONVERTER_LIB = $(PROJECT_OBJ_ROOT)\dsc\engine\mofconverter\$O\mofconverter.lib

_DEFINES=$(C_DEFINES) /DOPTIMIZE /DUNICODE /D_UNICODE /DREGISTER_PROXY_DLL /D__REMOVE_TRACING /DHOOK_BUILD

!include $(PROJECT_ROOT)\dsc\makefile.cmn

TARGETNAME=dsccore
TARGETTYPE=DYNLINK
TARGET_DESTINATION=DSC

_NT_TARGET_VERSION=$(_NT_TARGET_VERSION_LATEST)
UPLEVEL=1

USE_DEFAULT_WIN32_LIBS=0
BUILD_MINCORE=1

TARGETLIBS= \
  $(MINCORE_PRIV_SDK_LIB_VPATH)\ext-ms-win-advapi32-shutdown-l1.lib \
  $(MINCORE_PRIV_SDK_LIB_VPATH)\ext-ms-win-ntuser-message-l1.lib \
  $(MINCORE_PRIV_SDK_LIB_VPATH)\api-ms-win-downlevel-kernel32-l2.lib \
  $(MINCORE_PRIV_SDK_LIB_VPATH)\api-ms-win-downlevel-ole32-l1.lib \
  $(CONFIGMANAGER_LIB) \
  $(MOFCONVERTER_LIB) \
  $(OBJECT_ROOT)\admin\dsc\engine\moduleloader\modulelibrary\$O\modulehandler.lib \
  $(OBJECT_ROOT)\admin\wmi\winomi\http\$O\http.lib \
  $(OBJECT_ROOT)\admin\wmi\winomi\sock\$O\sock.lib \
  $(OBJECT_ROOT)\admin\dsc\engine\EngineHelper\$O\EngineHelper.lib \
  $(OBJECT_ROOT)\admin\dsc\engine\ca\cainfrastructure\$O\CAEngine.lib \
  $(ADMIN_LIB_PATH)\pal.lib \
  $(ADMIN_LIB_PATH)\nitsstub.lib \
  $(SDK_LIB_PATH)\mi.lib \
  $(SDK_LIB_PATH)\winhttp.lib \
  $(OBJECT_ROOT)\admin\wmi\wmiv2\common\$(OGRP)\$(O)\miutils.lib \
  $(SDK_LIB_PATH)\oleaut32.lib \
  $(SDK_LIB_PATH)\uuid.lib \
  $(SDK_LIB_PATH)\shell32.lib \
  $(SDK_LIB_PATH)\wmiutils.lib \
  $(SDK_LIB_PATH)\wbemuuid.lib \
  $(SDK_LIB_PATH)\rpcrt4.lib \
  $(ADMIN_LIB_PATH)\mimofcodec.lib \
  $(MINWIN_PRIV_SDK_LIB_PATH)\rsa32.lib \
  $(SDK_LIB_PATH)\ntdll.lib                                        \
              
DLOAD_ERROR_HANDLER=kernelbase

INCLUDES=$(INCLUDES); \
    $(ADMIN_INC_PATH)\DSC; \
    $(MINWIN_PRIV_SDK_INC_PATH); \
    $(DSC_ENGINE_INC); \
    $(CONFIGMANAGER_LIB_INC); \
    $(ENGINEHELPER_INC); \
    $(MODULELIBRARY_INC); \
    $(ADMIN_INC_PATH)\codec; \
    $(NITS_INC); \
    $(CAINFRASRTUCTURE_INC); \
    $(CALOGINFRASTRUCTURE_LIB_INC); \
    $(WINDOWS_INC_PATH); \
    
SOURCES= \
  ..\module.c \
  ..\WMIAdapter.c \
  ..\lcm.traps.c \
  ..\DscCore.rc \

DLLDEF_OBJECTS= \
    $(ADMIN_LIB_PATH)\nitsstub.obj \


DLLENTRY=_DllMainCRTStartup

DLLDEF=..\Provider.DEF

WMI_VERSION=2.0

WMI_MOF_MFL_PATH=..\..\..\mof\


/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

#if defined(_MSC_VER)

#pragma prefast(push)
#pragma prefast(disable:26071 26036 26061) //oacr warnings in sdk header files.
#endif

#include "EngineHelper.h"
#include "Resources_LCM.h"
#include "strings.h"
#include "LocalConfigManagerHelper.h"
#include "CAEngine.h"
#include "ModuleHandlerInternal.h"
#include "ModuleValidator.h"
#include "lcm.traps.h"

#if defined(_MSC_VER)
#pragma prefast(pop)
#endif

MI_Result NITS_CALL LCMTest_ExpandPath(_In_z_ const MI_Char * pathIn,
                     _Outptr_result_maybenull_z_ MI_Char **expandedPath, 
                     _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return ExpandPath( pathIn, expandedPath, cimErrorDetails);

}

MI_Result NITS_CALL LCMTest_GetMetaConfig(_Outptr_ MSFT_DSCMetaConfiguration **metaConfigInstance)
{
    return GetMetaConfig( metaConfigInstance);
}

MI_Result NITS_CALL LCMTest_InitHandler(_In_z_ const MI_Char* methodName, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return InitHandler(methodName, cimErrorDetails);
}

MI_Result NITS_CALL LCMTest_UnInitHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return UnInitHandler(cimErrorDetails);
}

MI_Result NITS_CALL  LCMTEST_LCM_Pull_GetConfiguration(
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if( cimErrorDetails )
        *cimErrorDetails = NULL;
    return MI_RESULT_OK;
    //return LCM_Pull_GetConfiguration(cimErrorDetails);
}

MI_Result NITS_CALL LCMTEST_LCM_Pull_Execute()
{
#if defined(_MSC_VER)
    MI_Instance *cimErrorDetails;    
    return LCM_Pull_Execute(&cimErrorDetails);
#else
    return MI_RESULT_OK;
#endif
}

MI_Result LCMTest_CallSetConfiguration(_In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
                               MI_Uint32 dataSize,
                               MI_Uint32 dwFlags,
                                MI_Boolean force,
                               _In_ MI_Context* context,
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return CallSetConfiguration(ConfigData, dataSize, dwFlags, force, context, cimErrorDetails);
}

MI_Result LCMTest_CallConsistencyEngine(_In_ MI_Context* context,
                                _In_ MI_Uint32 invokeMode,
                                _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return CallConsistencyEngine(context, invokeMode, cimErrorDetails);
}

MI_Result LCMTest_TaskHelper(_In_z_ MI_Char* taskPath,
        _In_z_ MI_Char* taskName,
        _In_z_ const MI_Char* methodName,
        _In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return TaskHelper(taskPath, taskName, methodName, moduleManager, cimErrorDetails);
}
MI_Result LCMTest_SerializeMetaConfig(_In_ const MSFT_DSCMetaConfiguration *metaConfig,
                                _In_ ModuleManager *moduleManager,
                              _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return SerializeMetaConfig(metaConfig, moduleManager, cimErrorDetails);
}

MI_Result LCMTest_DeseralizeMetaConfig(_Outptr_result_maybenull_ MSFT_DSCMetaConfiguration **metaConfig,
                                _In_ ModuleManager *moduleManager,
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return DeseralizeMetaConfig( metaConfig, moduleManager, cimErrorDetails);
}

MI_Result NITS_CALL LCMTEST_GetLCMStatusCodeHistory(
	_Outptr_result_maybenull_z_ MI_Char **lcmStatusCodeHistory,
	_Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
	return GetLCMStatusCodeHistory(lcmStatusCodeHistory, cimErrorDetails);
}

MI_Result NITS_CALL LCMTEST_RegisterTask(
	_In_ MI_Instance * currentMetaConfigInstance,
	_In_z_ const MI_Char * propName,
	_In_z_ const MI_Char * taskName,
	_In_ MI_Uint32 defaultValue,
	_Outptr_result_maybenull_ MI_Instance ** cimErrorDetails)
{
    return RegisterTask(currentMetaConfigInstance, propName, taskName, defaultValue, cimErrorDetails);
}

MI_Result NITS_CALL CATest_InitCAHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return InitCAHandler(cimErrorDetails);
}

MI_Result NITS_CALL CATest_UnInitCAHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return UnInitCAHandler(cimErrorDetails);
}


MI_Result NITS_CALL CATest_SendConfigurationApply( _In_ LCMProviderContext *lcmContext,   
                                  _In_ MI_Uint32 flags,
                                  _In_ MI_InstanceA *instanceA,
                                  _In_ ModuleManager *moduleManager,
                                  _In_ MI_Instance *documentIns,
                                  _Inout_ MI_Uint32 *resultStatus,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return SendConfigurationApply(lcmContext, flags, instanceA, moduleManager, documentIns, 
        resultStatus, extendedError);
}

MI_Result NITS_CALL CATest_GetConfiguration(_In_ LCMProviderContext *lcmContext,   
                                    _In_ MI_Uint32 flags,
                                    _In_ MI_InstanceA *instanceA,
                                    _In_ ModuleManager *moduleManager,
                                    _In_ MI_Instance *documentIns,
                                    _Out_ MI_InstanceA *outInstances,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return GetConfiguration(lcmContext, flags, instanceA, moduleManager, documentIns, outInstances, extendedError);
}

MI_Result NITS_CALL CATest_ResolveDependency( _In_ MI_InstanceA *instanceA, 
                                  _Inout_ ExecutionOrderContainer *container,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return ResolveDependency(instanceA, container, extendedError);
}

void NITS_CALL CATest_FreeExecutionOrderContainer(_Inout_ ExecutionOrderContainer *container)
{
    FreeExecutionOrderContainer(container);
}

MI_Result NITS_CALL CATest_InitializeModuleManager(MI_Uint32 flags, 
                                _Outptr_result_maybenull_ MI_Instance **extendedError, 
                                _Outptr_result_maybenull_ ModuleManager **moduleManager)
{
    return InitializeModuleManager(flags, extendedError, moduleManager);
}

MI_Result NITS_CALL CATEST_LoadInstanceDocumentFromLocation( _In_ ModuleManager *moduleManager,
        MI_Uint32 flags,
        _In_ const MI_Char *documentLocation,
        _Outptr_result_maybenull_ MI_Instance **extendedError,
        _Out_ MI_InstanceA *resources,
        _Outptr_result_maybenull_ MI_Instance **documentInstance)
{
    return moduleManager->ft->LoadInstanceDocumentFromLocation( moduleManager, flags, documentLocation, extendedError, resources, documentInstance);
}

MI_Result NITS_CALL CATEST_LoadInstanceDocument (
        _In_ ModuleManager *moduleManager,
        MI_Uint32 flags,
        _In_count_(documentSize) MI_Uint8 *document,
        _In_ MI_Uint32 documentSize,
        _Outptr_result_maybenull_ MI_Instance **extendedError,
        _Out_ MI_InstanceA *resources,
        _Outptr_result_maybenull_ MI_Instance **documentInstance)
{
    return moduleManager->ft->LoadInstanceDocument( moduleManager, flags, document, documentSize, extendedError, resources, documentInstance);
}

MI_Result  NITS_CALL CATest_Close( _Inout_ ModuleManager *moduleManager,
                        _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return moduleManager->ft->Close(moduleManager, extendedError);
}

MI_Result  NITS_CALL CATest_GetRegistrationInstance (
        _In_ ModuleManager *moduleManager,
        _In_z_ const MI_Char *className,
        _Outptr_result_maybenull_ const MI_Instance **registrationInstance,
        _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return moduleManager->ft->GetRegistrationInstance( moduleManager, className, registrationInstance, extendedError);
}

MI_Result NITS_CALL CATest_GetProviderCompatibleInstance (
        _In_ ModuleManager *moduleManager,
        _In_ MI_Instance *inInstance,
        _Outptr_result_maybenull_ MI_Instance **outInstance,
        _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return moduleManager->ft->GetProviderCompatibleInstance(moduleManager, inInstance, outInstance, extendedError);
}

MI_Result NITS_CALL  CATest_Update (
        _In_ ModuleManager *moduleManager,
         _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return moduleManager->ft->Update(moduleManager, extendedError);
}
MI_Result  NITS_CALL  CATest_GetCoreSchema (_In_ MI_Application *miApp,                           
                    _In_ MI_Deserializer *deserializer,
                    _In_ MI_OperationOptions * options,
                    _Inout_ MI_ClassA *miClassArray, 
                    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return GetCoreSchema(miApp, deserializer, options, miClassArray, extendedError);
}

MI_Result NITS_CALL CATest_ValidateInfrastructureSchema (_In_ MI_ClassA *miClassArray, 
                                   _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    return ValidateInfrastructureSchema(miClassArray, extendedError);
}

NitsTrapValue(LCMTraps)
    LCMTest_ExpandPath,
    LCMTest_GetMetaConfig,
    LCMTest_InitHandler,
    LCMTest_UnInitHandler,
    LCMTest_CallSetConfiguration,
    LCMTest_CallConsistencyEngine,
    LCMTest_TaskHelper,
    LCMTest_SerializeMetaConfig,
    LCMTest_DeseralizeMetaConfig,
    LCMTEST_LCM_Pull_GetConfiguration,
    LCMTEST_LCM_Pull_Execute,
    LCMTEST_GetLCMStatusCodeHistory,
    LCMTEST_RegisterTask,

NitsEndTrapValue

NitsTrapValue(CATraps)
    CATest_InitCAHandler,
    CATest_UnInitCAHandler,
    CATest_SendConfigurationApply,
    CATest_GetConfiguration,
    CATest_ResolveDependency,
    CATest_FreeExecutionOrderContainer,
    CATest_InitializeModuleManager,
    CATEST_LoadInstanceDocumentFromLocation,
    CATEST_LoadInstanceDocument,
    CATest_Close,
    CATest_GetRegistrationInstance,
    CATest_GetProviderCompatibleInstance,
    CATest_Update,
    CATest_GetCoreSchema,
    CATest_ValidateInfrastructureSchema,

NitsEndTrapValue





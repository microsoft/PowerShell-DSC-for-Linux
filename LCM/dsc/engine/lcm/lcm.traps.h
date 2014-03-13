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

#ifndef __LCM_TRAPS_H_
#define __LCM_TRAPS_H_
    
#include <nits.h>
#include <MSFT_DSCMetaConfiguration.h>
#include "MI.h"
    
NitsTrapTable(LCMTraps, 0)
    MI_Result ( NITS_CALL * _LCMTest_ExpandPath)(_In_z_ const MI_Char * pathIn,
                     _Outptr_result_maybenull_z_ MI_Char **expandedPath, 
                     _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ( NITS_CALL * _LCMTest_GetMetaConfig)(_Outptr_ MSFT_DSCMetaConfiguration **metaConfigInstance);
    
    MI_Result ( NITS_CALL * _LCMTest_InitHandler)(_In_z_ const MI_Char* methodName, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ( NITS_CALL * _LCMTest_UnInitHandler)(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ( NITS_CALL * _LCMTest_CallSetConfiguration)(_In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
                               MI_Uint32 dataSize,
                               MI_Uint32 dwFlags,
							   MI_Boolean force,
                               _In_ MI_Context* context,
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ( NITS_CALL * _LCMTest_CallConsistencyEngine)(_In_ MI_Context* context,
                                _In_ MI_Uint32 invokeMode,
                                _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ( NITS_CALL * _LCMTest_TaskHelper)(_In_z_ MI_Char* taskPath,
        _In_z_ MI_Char* taskName,
        _In_z_ const MI_Char* methodName,
        _In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result (NITS_CALL * _LCMTest_SerializeMetaConfig)(_In_ const MSFT_DSCMetaConfiguration *metaConfig,
                              _In_ ModuleManager *moduleManager,
                              _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result (NITS_CALL * _LCMTest_DeseralizeMetaConfig)(_Outptr_result_maybenull_ MSFT_DSCMetaConfiguration **metaConfig,
                               _In_ ModuleManager *moduleManager,
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);


MI_Result (NITS_CALL * _LCMTEST_LCM_Pull_GetConfiguration)(
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result (NITS_CALL * _LCMTEST_LCM_Pull_Execute)();

MI_Result (NITS_CALL * _LCMTEST_GetLCMStatusCodeHistory)(
		_Outptr_result_maybenull_z_ MI_Char **lcmStatusCodeHistory,
		_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result (NITS_CALL * _LCMTEST_RegisterTask)(
	_In_ MI_Instance * currentMetaConfigInstance,
	_In_z_ const MI_Char * propName,
	_In_z_ const MI_Char * taskName,
	_In_ MI_Uint32 defaultValue,
	_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

NitsEndTrapTable

NitsTrapTable(CATraps, 0)
    MI_Result (NITS_CALL *_CATest_InitCAHandler)(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result (NITS_CALL *_CATest_UnInitCAHandler)(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ( NITS_CALL * _CATest_SendConfigurationApply)( _In_ LCMProviderContext *lcmContext,   
                                  _In_ MI_Uint32 flags,
                                  _In_ MI_InstanceA *instanceA,
                                  _In_ ModuleManager *moduleManager,
                                  _In_ MI_Instance *documentIns,
                                  _Inout_ MI_Uint32 *resultStatus,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result ( NITS_CALL * _CATest_GetConfiguration)(_In_ LCMProviderContext *lcmContext,   
                                    _In_ MI_Uint32 flags,
                                    _In_ MI_InstanceA *instanceA,
                                    _In_ ModuleManager *moduleManager,
                                    _In_ MI_Instance *documentIns,
                                    _Out_ MI_InstanceA *outInstances,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result ( NITS_CALL * _CATest_ResolveDependency)( _In_ MI_InstanceA *instanceA, 
                                  _Inout_ ExecutionOrderContainer *container,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError); 

    void ( NITS_CALL * _CATest_FreeExecutionOrderContainer)(_Inout_ ExecutionOrderContainer *container);

    MI_Result ( NITS_CALL * _CATest_InitializeModuleManager)( MI_Uint32 flags, 
                                _Outptr_result_maybenull_ MI_Instance **extendedError, 
                                _Outptr_result_maybenull_ ModuleManager **moduleManager);

    MI_Result (NITS_CALL * _CATEST_LoadInstanceDocumentFromLocation) (
        _In_ ModuleManager *moduleManager,
        MI_Uint32 flags,
        _In_ const MI_Char *documentLocation,
        _Outptr_result_maybenull_ MI_Instance **extendedError,
        _Out_ MI_InstanceA *resources,
        _Outptr_result_maybenull_ MI_Instance **documentInstance);    

    MI_Result (NITS_CALL * _CATEST_LoadInstanceDocument) (
        _In_ ModuleManager *moduleManager,
        MI_Uint32 flags,
        _In_count_(documentSize) MI_Uint8 *document,
        _In_ MI_Uint32 documentSize,
        _Outptr_result_maybenull_ MI_Instance **extendedError,
        _Out_ MI_InstanceA *resources,
        _Outptr_result_maybenull_ MI_Instance **documentInstance);   

    MI_Result ( NITS_CALL * _CATest_Close)( _Inout_ ModuleManager *moduleManager,
                        _Outptr_result_maybenull_ MI_Instance **extendedError);  

    MI_Result  ( NITS_CALL * _CATest_GetRegistrationInstance) (
        _In_ ModuleManager *moduleManager,
        _In_z_ const MI_Char *className,
        _Outptr_result_maybenull_ const MI_Instance **registrationInstance,
        _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result ( NITS_CALL * _CATest_GetProviderCompatibleInstance) (
        _In_ ModuleManager *moduleManager,
        _In_ MI_Instance *inInstance,
        _Outptr_result_maybenull_ MI_Instance **outInstance,
        _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result ( NITS_CALL * _CATest_Update) (
        _In_ ModuleManager *moduleManager,
         _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result ( NITS_CALL * _CATest_GetCoreSchema) (_In_ MI_Application *miApp,                           
                        _In_ MI_Deserializer *deserializer,
                        _In_ MI_OperationOptions * options,
                        _Inout_ MI_ClassA *miClassArray, 
                        _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result ( NITS_CALL * _CATest_ValidateInfrastructureSchema) (_In_ MI_ClassA *miClassArray, 
                                       _Outptr_result_maybenull_ MI_Instance **extendedError );    

NitsEndTrapTable

NitsTrapExport(CATraps);

NitsTrapExport(LCMTraps);

#endif //__LCM_TRAPS_H_

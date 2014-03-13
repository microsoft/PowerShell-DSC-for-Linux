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

#ifndef _CAENGINEINTERNAL_H
#define _CAENGINEINTERNAL_H
#include "MI.h"






#define INITIAL_CONTAINER_SIZE 10
#define CONTAINER_DEFAULT_EXECUTION 0
#define CONTAINER_REMAINING_EXECUTION 1
#define NODE_VISITED 1
#define NODE_RESOLVED 1


#define LOGRESOURCE_CLASSNAME MI_T("MSFT_LogResource")
#define LOGRESOURCE_MESSAGEPROPERTYNAME MI_T("Message")
#define STOP_CONFIGURATIONT_TIMEOUT 60000


MI_Result DependentResourceProcessed (_In_ MI_Uint32 resourceIndex,
                                    _In_ ExecutionOrderContainer *container,
                                    _Inout_ MI_Boolean *bDependentFailed,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result DependentResourceFailed( _In_ MI_Uint32 index,
                            _In_ ExecutionOrderContainer *container,
                            _In_ MI_InstanceA *instanceA,
                            _Out_ MI_Boolean *bDependentFailed,
                            _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result ResolveDependencyInternal( _In_ MI_Uint32 index,
                                   _In_ MI_InstanceA *instanceA, 
                                  _Inout_ ExecutionOrderContainer *container,
                                  _Inout_count_(instanceA->size) MI_Sint32 *visitedNodes,
                                  _Inout_count_(instanceA->size) MI_Sint32 *resolvedNodes,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetInstanceIndex(_In_ MI_InstanceA *instanceA, 
                              _In_z_ MI_Char *resourceId, 
                              int currentInstanceIndex,
                              _Out_ MI_Uint32 *resourceIndex, 
                              _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result AddToList(_Inout_ ExecutionOrderContainer *container, 
                            _In_ MI_Uint32 objectIndex,
                            _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result SetResourcesInOrder(_In_ LCMProviderContext *lcmContext,  
                                  _In_ ModuleManager *moduleManager,
                                  _In_ MI_InstanceA * instanceA,
                                  _In_ MI_Session *miSession,
                                  _In_ ExecutionOrderContainer *executionOrder,
                                  _In_ MI_Uint32 flags,
                                  _In_ MI_Instance *documentIns,
                                   _Inout_ MI_Uint32 *resultStatus,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MoveToDesiredState(_In_ ProviderCallbackContext *provContext,   
                             _In_ MI_Application *miApp,
                             _In_ MI_Session *miSession,
                             _In_ MI_Instance *instance,
                             _In_ const MI_Instance *regInstance,
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
                             _Inout_ MI_Boolean *canceled,
                             _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetCurrentState(_In_ ProviderCallbackContext *provContext,  
                           _In_ MI_Application *miApp,
                           _In_ MI_Session *miSession,
                           _In_ MI_Instance *instance,
                           _In_ const MI_Instance *regInstance,
                           _Outptr_result_maybenull_ MI_Instance **outputInstance,
                           _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result Exec_WMIv2Provider(_In_ ProviderCallbackContext *provContext,   
                             _In_ MI_Application *miApp,
                             _In_ MI_Session *miSession,
                             _In_ MI_Instance *instance,
                             _In_ const MI_Instance *regInstance,
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
                             _Inout_ MI_Boolean* canceled,
                             _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result Exec_PSProvider(_In_ ProviderCallbackContext *provContext, 
                          _In_ MI_Application *miApp,
                          _In_ MI_Instance *instance,
                          _In_ const MI_Instance *regInstance,
                          _In_ MI_Uint32 flags,
                          _Inout_ MI_Uint32 *resultStatus,
                          _Inout_ MI_Boolean *canceled,
                          _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result Get_WMIv2Provider(_In_ ProviderCallbackContext *provContext,  
                                _In_ MI_Application *miApp,
                               _In_ MI_Session *miSession,
                               _In_ MI_Instance *instance,
                               _In_ const MI_Instance *regInstance,
                               _Outptr_result_maybenull_ MI_Instance **outputInstance,
                                _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result Get_PSProvider(_In_ ProviderCallbackContext *provContext, 
                                 _In_ MI_Application *miApp,
                                 _In_ MI_Instance *instance,
                                 _In_ const MI_Instance *regInstance,
                                 _Outptr_result_maybenull_ MI_Instance **outputInstance,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result StopCurrentPSProviderConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError);



MI_Result GetTestMethodResult(_In_ MI_Operation *operation,
                              _Out_opt_ MI_Boolean *bTestResult,
                              _Out_opt_ MI_Uint64 *outProviderContext,
                              _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetSetMethodResult(_In_ MI_Operation *operation,
                            _Out_opt_ MI_Uint32 *returnValue,
                            _In_z_ const MI_Char * resourceId,
                            _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetGetMethodResult(_In_ MI_Operation *operation,
                              _Outptr_result_maybenull_ MI_Instance **outputInstance,
                              _Outptr_result_maybenull_ MI_Instance **extendedError);

void LogCAMessage(_In_ LCMProviderContext *lcmContext,
                  _In_ MI_Uint32 messageIndex,
                  _In_z_ const MI_Char *resourceId
                  );
void LogCAMessageTime(_In_ LCMProviderContext *lcmContext,
                  _In_ MI_Uint32 messageIndex,
                  _In_ const MI_Real64 duration,
                  _In_z_ const MI_Char *resourceId
                  );

void LogCAProgress( _In_ LCMProviderContext *lcmContext, 
                       _In_z_ const MI_Char * currentOperation,
                       _In_z_ const MI_Char * statusDescription,
                       _In_ MI_Uint32 currentResourceIndex,
                       _In_ MI_Uint32 totalResource);


/*MP Features supported Methods*/


MI_Result Pull_GetModules(_In_ LCMProviderContext *lcmContext,
                                _In_ MI_Instance *metaConfig,
                                _In_z_ const MI_Char *downloadedLocation,
                                _In_ MI_InstanceA *modulesToDownload,
                                _Inout_ MI_StringA *downloadedModules,
                                _Outptr_result_maybenull_ MI_Instance **extendedError);



#endif //_CAENGINEINTERNAL_H

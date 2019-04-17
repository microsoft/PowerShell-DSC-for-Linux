/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _CAENGINE_H
#define _CAENGINE_H
#include <nits.h>

#include "MI.h"
#include <ModuleHandler.h>

#if defined(BUILD_OMS)
#include <signal.h>
#endif

typedef enum _ResourceStatus
{
    ResourceNotProcessed = -1,
    ResourceProcessedAndSucceeded = 1,
    ResourceProcessedAndFailed = 2
} ResourceStatus;

typedef struct _ResourceExecutionDetails
{
    MI_Uint32 resourceIndex;       //Contain ID referencing original list in instance document..
    ResourceStatus resourceStatus;        // Status of the resource
} ResourceExecutionDetails;

typedef struct _ExecutionOrderContainer
{
    // Sorted list of resources that need to be executed in the order specified in this list.
    ResourceExecutionDetails *ExecutionList;    
    MI_Uint32 executionListCapacity;          // capacity of items in execution list
    MI_Uint32 executionListSize;              // Active size of ExecutionList.
} ExecutionOrderContainer;


#ifdef __cplusplus
extern "C"
{
#endif

MI_Result InitCAHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result UnInitCAHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result MI_CALL SendConfigurationApply( _In_ LCMProviderContext *lcmContext,   
                                  _In_ MI_Uint32 flags,
                                  _In_ MI_InstanceA *instanceA,
                                  _In_ ModuleManager *moduleManager,
                                  _In_ MI_Instance *documentIns,
                                  _Inout_ MI_Uint32 *resultStatus,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MI_CALL GetConfiguration(_In_ LCMProviderContext *lcmContext,   
                                    _In_ MI_Uint32 flags,
                                    _In_ MI_InstanceA *instanceA,
                                    _In_ ModuleManager *moduleManager,
                                    _In_ MI_Instance *documentIns,
                                    _Out_ MI_InstanceA *outInstances,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result MI_CALL ResolveDependency( _In_ MI_InstanceA *instanceA, 
                                  _Inout_ ExecutionOrderContainer *container,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError);  

void MI_CALL FreeExecutionOrderContainer(_Inout_ ExecutionOrderContainer *container);

MI_Result MI_CALL Pull_GetConfiguration(_In_ LCMProviderContext *lcmContext,
                                        _In_ MI_Instance *metaConfig,
                                        _In_opt_z_ MI_Char *partialConfigName,
                                        _In_opt_z_ MI_Char *assignedConfiguration,
                                        _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                        _Outptr_result_maybenull_z_  MI_Char** result,
                                        _Out_ MI_Uint32* getActionStatusCode,
                                        _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MI_CALL Pull_GetAction(_In_ LCMProviderContext *lcmContext,
                                 _In_ MI_Instance *metaConfig,
                                 _In_opt_z_ MI_Char *partialConfigName,
                                 _In_z_ const MI_Char *checkSum,
                                 _In_ MI_Boolean complianceStatus,
                                 _In_ MI_Uint32 lastGetActionStatusCode,
                                 _Outptr_result_maybenull_z_  MI_Char** result,
                                 _Out_ MI_Uint32* getActionStatusCode,
                                 _Outptr_result_maybenull_ OverAllGetActionResponse** serverAssignedConfigurations,
                                 _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MI_CALL Pull_GetConfigurationWebDownloadManager(_In_ LCMProviderContext *lcmContext,
                                                          _In_ MI_Instance *metaConfig,
                                                          _In_opt_z_ MI_Char *partialConfigName,
                                                          _In_opt_z_ MI_Char *assignedConfiguration,
                                                          _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                                          _Outptr_result_maybenull_z_  MI_Char** directoryName,
                                                          _Out_ MI_Uint32 * numModulesInstalled,
                                                          _Outptr_result_maybenull_z_  MI_Char** result,
                                                          _Out_ MI_Uint32* getActionStatusCode,
                                                          _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MI_CALL Pull_GetActionWebDownloadManager(_In_ LCMProviderContext *lcmContext,
                                                   _In_ MI_Instance *metaConfig,
                                                   _In_opt_z_ MI_Char *partialConfigName,
                                                   _In_z_ const MI_Char *checkSum,
                                                   _In_ MI_Boolean complianceStatus,
                                                   _In_ MI_Uint32 lastGetActionStatusCode,
                                                   _Outptr_result_maybenull_z_  MI_Char** result,
                                                   _Out_ MI_Uint32* getActionStatusCode,
                                                   _Outptr_result_maybenull_ OverAllGetActionResponse** serverAssignedConfigurations,
                                                   _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result MI_CALL Do_Register(
    _In_ MI_Instance *metaConfig,
    _In_ MI_Instance *managerInstance,
    _In_z_ MI_Char *agentId,
    _In_z_ MI_Char *thumbprint,
    _In_ MI_Instance *registrationPayload,
    _In_ MI_StringA *configurationNames,
    _In_ MI_Uint32 typeOfManagerInstance,
    _Outptr_result_maybenull_z_  MI_Char** result,
    _Out_ MI_Uint32* getActionStatusCode,
    _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MI_CALL Pull_SendStatusReport(_In_ LCMProviderContext *lcmContext, 
                                                      _In_ MI_Instance *metaConfig,
                                                      _In_ MI_Instance *statusReport,
                                                      _In_ MI_Uint32 isStatusReport,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError);

void SetMessageInContext(MI_Uint32 msgOperation,MI_Uint32 msgItem,LCMProviderContext *lcmContext);



MI_Result  MI_CALL StopCurrentConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError, BOOL force);

#if defined(BUILD_OMS)
void handleSIGCHLDSignal(int sig);
#endif


#ifdef __cplusplus
                                  
}
                                  
#endif

#endif //_CAENGINE_H

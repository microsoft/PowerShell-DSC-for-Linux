/*============================================================================
 * Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *============================================================================
 */
#ifndef _CAENGINE_H
#include <nits.h>

#include "MI.h"
#include <ModuleHandler.h>

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
                                _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MI_CALL Pull_GetAction(_In_ LCMProviderContext *lcmContext,
                                _In_ MI_Instance *metaConfig,
                                _In_z_ const MI_Char *checkSum,
                                _In_ MI_Boolean complianceStatus,
                                _In_ MI_Uint32 lastGetActionStatusCode,
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _Outptr_result_maybenull_ MI_Instance **extendedError);

void SetMessageInContext(MI_Uint32 msgOperation,MI_Uint32 msgItem,LCMProviderContext *lcmContext);



MI_Result  MI_CALL StopCurrentConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError, BOOL force);



#ifdef __cplusplus
                                  
}
                                  
#endif

#endif //_CAENGINE_H

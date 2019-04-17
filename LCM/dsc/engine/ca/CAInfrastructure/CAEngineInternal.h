/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

/*
  This is a data structure for a single linked list that contains a front pointer and a back pointer, and we'll be using it to keep track of all resources that have failed to apply, and at the end we construct a string based on entries in this data structure and free the memory allocated by it.

  Example output in the CIM_Error instance that is returned is:

    Failed to apply the configuration.  These resources produced errors: [nxSshAuthorizedKeys]rootKey, [nxFile]MyFile1.
*/

typedef struct _ResourceError ResourceError;
typedef struct _ResourceErrorList ResourceErrorList;

struct _ResourceError
{
    ResourceError * next;
    char * resourceID;
};

struct _ResourceErrorList
{
    ResourceError * first;
    ResourceError * last;
};

MI_Result InitResourceErrorList(ResourceErrorList * resourceErrorList);
MI_Result AddToResourceErrorList(ResourceErrorList * resourceErrorList, const char * resourceID);
char *    BuildStringResourceErrorList(ResourceErrorList * resourceErrorList);
MI_Result CleanupResourceErrorList(ResourceErrorList * resourceErrorList);

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
                              _Outptr_result_maybenull_ ResourceErrorList *resourceErrorList,
                              _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MoveToDesiredState(_In_ ProviderCallbackContext *provContext,   
                             _In_ MI_Application *miApp,
                             _In_ MI_Session *miSession,
                             _In_ MI_Instance *instance,
                             _In_ const MI_Instance *regInstance,
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
                             _Inout_ MI_Boolean *canceled,
                             _Outptr_result_maybenull_ ResourceErrorList *resourceErrorList,
                             _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetCurrentState(_In_ ProviderCallbackContext *provContext,  
                           _In_ MI_Application *miApp,
                           _In_ MI_Session *miSession,
                           _In_ MI_Instance *instance,
                           _In_ const MI_Instance *regInstance,
                           _Outptr_result_maybenull_ MI_Instance *outputInstance,
                        //    _Outptr_result_maybenull_ MI_InstanceA *outputInstance,
                           _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result PerformInventoryState(_In_ ProviderCallbackContext *provContext,  
                           _In_ MI_Application *miApp,
                           _In_ MI_Session *miSession,
                           _In_ MI_Instance *instance,
                           _In_ const MI_Instance *regInstance,
                           _Outptr_result_maybenull_ MI_InstanceA *outputInstances,
                           _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result Exec_WMIv2Provider(_In_ ProviderCallbackContext *provContext,   
                             _In_ MI_Application *miApp,
                             _In_ MI_Session *miSession,
                             _In_ MI_Instance *instance,
                             _In_ const MI_Instance *regInstance,
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
                             _Inout_ MI_Boolean* canceled,
                             _Outptr_result_maybenull_ ResourceErrorList *resourceErrorList,
                             _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result Exec_NativeProvider(_In_ ProviderCallbackContext *provContext,   
                             _In_ MI_Application *miApp,
                             _In_ MI_Session *miSession,
                             _In_ MI_Instance *instance,
                             _In_ const MI_Instance *regInstance,
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
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

MI_Result Inventory_WMIv2Provider(_In_ ProviderCallbackContext *provContext,  
                                _In_ MI_Application *miApp,
                               _In_ MI_Session *miSession,
                               _In_ MI_Instance *instance,
                               _In_ const MI_Instance *regInstance,
                               _Outptr_result_maybenull_ MI_InstanceA *outputInstances,
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

MI_Result PerformInventoryMethodResult(_In_ MI_Operation *operation,
                              _Outptr_result_maybenull_ MI_InstanceA *outputInstances,
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

#endif //_CAENGINEINTERNAL_H

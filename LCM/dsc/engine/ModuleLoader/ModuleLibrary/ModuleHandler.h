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


#ifndef __MODULEHANDLER_H_
#define __MODULEHANDLER_H_
#include <MI.h>


typedef struct _ModuleManager ModuleManager;
typedef struct _ModuleManagerFT ModuleManagerFT;

struct _ModuleManagerFT
{
    MI_Result (MI_CALL *Close) (
        _Inout_ ModuleManager *moduleManager,
        _Outptr_opt_result_maybenull_ MI_Instance **extendedError);

    MI_Result (*LoadInstanceDocument) (
        _In_ ModuleManager *moduleManager,
        MI_Uint32 flags,
        _In_count_(documentSize) MI_Uint8 *document,
        _In_ MI_Uint32 documentSize,
        _Outptr_result_maybenull_ MI_Instance **extendedError,
        _Out_ MI_InstanceA *resources,
        _Outptr_result_maybenull_ MI_Instance **documentInstance);

    MI_Result (*LoadInstanceDocumentFromLocation) (
        _In_ ModuleManager *moduleManager,
        MI_Uint32 flags,
        _In_ const MI_Char *documentLocation,
        _Outptr_result_maybenull_ MI_Instance **extendedError,
        _Out_ MI_InstanceA *resources,
        _Outptr_result_maybenull_ MI_Instance **documentInstance);


    MI_Result  (*GetRegistrationInstance) (
        _In_ ModuleManager *moduleManager,
        _In_z_ const MI_Char *className,
        _Outptr_result_maybenull_ const MI_Instance **registrationInstance,
        _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result (*GetProviderCompatibleInstance) (
        _In_ ModuleManager *moduleManager,
        _In_ MI_Instance *inInstance,
        _Outptr_result_maybenull_ MI_Instance **outInstance,
        _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result (*Update) (
        _In_ ModuleManager *moduleManager,
         _Outptr_result_maybenull_ MI_Instance **extendedError);

   /* MI_Result (*GetSchemaDetails) (
        _In_ ModuleManager *moduleManager,
        MI_Uint32 flags,
        _In_ MI_Char *className,
        _Outptr_result_maybenull_ MI_Instance **extendedError,
        _Out_ MI_Class **classList, //Referenced class + all embedded classes
        _Out_ MI_Uint32 *classCount,
        _Out_ MI_Instance **registrationInstance);

    MI_Result(*UpdateCache) (
        _In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MI_Instance **extendedError );
        */
            
} ;


 struct _ModuleManager
{
    MI_Uint64 reserved1;
    ptrdiff_t reserved2;
    const ModuleManagerFT *ft;
} ;
#ifdef __cplusplus
extern "C"
{
#endif
MI_Result MI_CALL InitializeModuleManager( MI_Uint32 flags, _Outptr_result_maybenull_ MI_Instance **extendedError, _Outptr_result_maybenull_ ModuleManager **moduleManager);
MI_Result MI_CALL LoadModuleManager(_Inout_ ModuleManager *moduleManager,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError);


#ifdef __cplusplus

}

#endif

#endif //__MODULEHANDLER_H_

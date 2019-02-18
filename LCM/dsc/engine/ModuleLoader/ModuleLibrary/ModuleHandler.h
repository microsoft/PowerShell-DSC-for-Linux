/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef __MODULEHANDLER_H_
#define __MODULEHANDLER_H_
#include <MI.h>
#include <EngineHelperInternal.h>


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

MI_Result GetArrayInstancesFromSingleMof(_In_ ModuleManager *moduleManager,
                                         MI_Uint32 flags,
                                         _In_z_  const MI_Char *documentLocation,
                                         MI_InstanceA * miInstanceArray,
                                         MI_Instance **extendedError,
                                         MI_Boolean shouldUseStrictOptions);

#ifdef __cplusplus

}

#endif

#endif //__MODULEHANDLER_H_

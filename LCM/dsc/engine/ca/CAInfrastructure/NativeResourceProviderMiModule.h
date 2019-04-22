/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**************************************************************************************************/
/*                                                                                                */
/* NativeResourceProviderMiModule provides utilities to retrieve and invoke the methods in the    */
/* MI_Module implemented by a native resource provider.                                           */
/*                                                                                                */
/**************************************************************************************************/

#ifndef _NATIVE_RESOURCE_PROVIDER_MI_MODULE_H
#define _NATIVE_RESOURCE_PROVIDER_MI_MODULE_H

#include <MI.h>

//
// NativeResourceProviderMiModule wraps an MI_Module* and adds some private data needed to cleanup
// the module.
//
typedef struct {
    MI_Module* miModule;
    #if defined(_MSC_VER)
    struct {
        HMODULE moduleHandle;
    } _private;
    #else
    struct {
        void *moduleHandle;
    } _private;
    #endif 
} NativeResourceProviderMiModule;

//
// Creates a NativeResourceProviderMiModule using the path to the binary file (e.g. a Windows DLL) that implements the MI_Module
//
MI_Result NativeResourceProviderMiModule_New(const _In_z_ MI_Char *nativeResourceProviderPath, 
                                             _Outptr_ NativeResourceProviderMiModule** module);

//
// Destroys the NativeResourceProviderMiModule created by NativeResourceProviderMiModule_New
//
MI_Result NativeResourceProviderMiModule_Delete(_In_ NativeResourceProviderMiModule* module);

//
// Retrieves the declaration of a class within the given MI_Module
//
MI_Result NativeResourceProviderMiModule_GetClassDecl(const _In_ NativeResourceProviderMiModule* module, 
                                                                const _In_z_ MI_Char *className,
                                                                _Outptr_ const MI_ClassDecl** classDecl);

//
// Find the declaration of a class within the given MI_Module
//
MI_Result NativeResourceProviderMiModule_HasClassDecl(const _In_ NativeResourceProviderMiModule* module, 
                                                                 const _In_z_ MI_Char *className);


//
// Retrieves the declaration of all classes within the given MI_Module
//
MI_Result NativeResourceProviderMiModule_GetSchemaDecls(const _In_ NativeResourceProviderMiModule* module, 
                                                                    const _In_z_ MI_Char *className, 
                                                                    _Outptr_ const MI_SchemaDecl** schema);


//
// Retrieves the declaration of a method within the given class
//
MI_Result NativeResourceProviderMiModule_GetMethodDecl(const _In_ MI_ClassDecl* classDecl, 
                                                                  const _In_z_ MI_Char *methodName, 
                                                                  _Outptr_  const MI_MethodDecl** methodDecl);


#endif // _NATIVE_RESOURCE_PROVIDER_MI_MODULE_H

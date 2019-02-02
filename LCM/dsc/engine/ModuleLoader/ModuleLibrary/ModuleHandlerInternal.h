/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef __MODULEHANDLERINTERNAL_H_
#define __MODULEHANDLERINTERNAL_H_

MI_Result GetMappingTable(_In_ MI_Application *miApp, 
                          _In_ MI_ClassA *miClassArray,
                          _In_ MI_InstanceA *miInstanceArray,
                          _Out_ ModuleLoaderObject **moduleLoader,
                          _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result GetModuleLoader( _In_ MI_Application *miApp,
                          _Out_ ModuleLoaderObject **moduleLoader,
                          _Outptr_result_maybenull_ MI_Instance **extendedError);

/* Class methods*/
MI_Result GetSchemaFromMOFs(_In_ MI_Application *miApp,                           
                            _In_ MI_Deserializer *deserializer,
                            _In_ MI_OperationOptions * options,
                            _Inout_ MI_ClassA *miClassArray,
                            _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetSystemSchema(_In_ MI_Application *miApp,                           
                          _In_ MI_Deserializer *deserializer,
                          _In_ MI_OperationOptions * options,
                          _In_z_ const MI_Char* schemaName, 
                          _In_opt_ MI_ClassA *inputClasses,
                          _Inout_ MI_ClassA *miClassArray, 
                          _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result UpdateClassCacheWithSchemasMofs(_In_ MI_Application *miApp,
                            _In_ MI_Deserializer *deserializer,
                            _In_ MI_OperationOptions * options,
                            _Inout_ MI_ClassA *miClassArray, 
                            _Outptr_result_maybenull_ MI_Instance **extendedError,
                            _In_z_ const MI_Char * schemaPath);

#ifdef __cplusplus
extern "C"
{
#endif

    MI_Result GetCoreSchema(_In_ MI_Application *miApp,                           
        _In_ MI_Deserializer *deserializer,
        _In_ MI_OperationOptions * options,
        _Inout_ MI_ClassA *miClassArray, 
        _Outptr_result_maybenull_ MI_Instance **extendedError);

    MI_Result GetMetaConfigSchema(_In_ MI_Application *miApp,                           
        _In_ MI_Deserializer *deserializer,
        _In_ MI_OperationOptions * options,
        _Inout_ MI_ClassA *miClassArray, 
        _Outptr_result_maybenull_ MI_Instance **extendedError);

#ifdef __cplusplus
}
#endif

MI_Result UpdateClassCache(_In_ MI_Application *miApp,
                           _In_ MI_Deserializer *deserializer,
                           _In_ MI_OperationOptions * options,
                           _In_z_ MI_Char *rootPath, 
                           _In_z_ MI_Char *directoryPath, 
                           _Inout_ MI_ClassA *miClassArray,
                           _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetSchemaFromSingleMOF(_In_ MI_Application *miApp,
                                 _In_ MI_Deserializer *deserializer,
                                 _In_ MI_OperationOptions * options,
                                 _In_z_ MI_Char *mofModulePath, 
                                 _In_z_ MI_Char *schemaFileName, 
                                 _Inout_ MI_ClassA *miClassArray,
                                 _In_opt_ MI_ClassA *miDiscoverdSchema,
                                 _Outptr_result_maybenull_ MI_Instance **extendedError);


/* Instance methods*/

MI_Result GetRegistrationInstanceFromMOFs(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,    
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray, 
                                          _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetRegistrationInstanceFromSharedObjects(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,    
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray, 
                                          _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result GetEachRegistrationInfo(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,       
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray, 
                                          _Outptr_result_maybenull_ MI_Instance **extendedError,
                                          _In_z_ const MI_Char * registrationPath);


MI_Result UpdateRegistrationInstanceCache(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _In_z_ MI_Char *rootPath, 
                                          _In_z_ MI_Char *directoryPath, 
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result FilterForConfigurationResource(_Inout_ MI_InstanceA *inputInstanceArray,
                                         _Inout_ MI_InstanceA *outputInstanceArray,
                                         _Outptr_result_maybenull_ MI_Instance **documentInstance, 
                                         _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result UpdateAndReloadInMemoryCache(_In_ ModuleManager *moduleManager,
                            _In_ MI_StringA *classNameA, 
                            _In_ MI_StringA *moduleNameA, 
                            _In_ MI_StringA *moduleVersionA, 
                            _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result GetInstanceFromSingleMOF(_In_opt_ ModuleManager *moduleManager,
                                   _In_ MI_Uint32 flags,
                                   _In_ MI_Application *miApp,
                                   _In_ MI_Deserializer *deserializer,
                                   _In_ MI_OperationOptions * options,
                                   _In_ MI_OperationOptions * strictOptions,
                                   _In_ MI_ClassA *classArray,
                                   _In_z_ const MI_Char *mofModuleFilePath, 
                                   _Inout_ MI_InstanceA *miInstanceArray,
                                   _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result InstallSchemaWithWMI(_In_ ModuleLoaderObject *moduleLoader,
                                   _In_z_ MI_Char *providerName,
                                   _In_z_ MI_Char *mofFilePath,  
                                   _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result GetInstanceFromBuffer(_In_opt_ ModuleManager *moduleManager,
                                _In_ MI_Application *miApp,
                                _In_ MI_Deserializer *deserializer,
                                _In_ MI_OperationOptions * options,
                                _In_ MI_ClassA *classArray,
                                _In_count_(instanceBufferSize) MI_Uint8 *instanceBuffer, 
                                _In_ MI_Uint32 instanceBufferSize,
                                _Inout_ MI_InstanceA *miInstanceArray,
                                _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result GetFilteredResource( _In_ MI_Application *miApp, 
                              _In_ MI_Instance *inInstance,
                              _Outptr_result_maybenull_ MI_Instance **outInstance,
                              _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result MI_CALL SchemaCallback(_In_opt_ void *context, 
                                 _In_opt_z_ const MI_Char *serverName, 
                                 _In_opt_z_ const MI_Char *namespaceName, 
                                 _In_z_ const MI_Char *className, 
                                 _Outptr_ MI_Class **requestedClassObject);


MI_Result GetMofDeserializer(_In_ MI_Application *miApp,
                             _Outptr_result_maybenull_ MI_Deserializer **deserializer,
                             _Outptr_result_maybenull_ MI_OperationOptions **operationOptions,
                             _Outptr_result_maybenull_ MI_OperationOptions **strictOperationOptions,
                             _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result CreateWMIv1CompatibleMof(_In_ ModuleLoaderObject* moduleLoader,
                                _In_z_ MI_Char *mofFilePath, 
                                _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result GetMIClass(_In_ MI_ClassDecl* classDecl,
                    _Outptr_  MI_Class ** miClass,
                    MI_Instance ** extendedErro);

#endif //__MODULEHANDLERINTERNAL_H_

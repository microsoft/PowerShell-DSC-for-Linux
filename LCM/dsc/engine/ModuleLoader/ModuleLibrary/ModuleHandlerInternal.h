/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
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
MI_Result UpdateClassCacheWithSchemas(_In_ MI_Application *miApp,
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


#endif //__MODULEHANDLERINTERNAL_H_

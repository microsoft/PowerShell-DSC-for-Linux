
/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef __MODULEVALIDATOR_H_
#define __MODULEVALIDATOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

    MI_Result ValidateInfrastructureSchema(_In_ MI_ClassA *miClassArray, 
        _Outptr_result_maybenull_ MI_Instance **extendedError );

#ifdef __cplusplus
}
#endif

MI_Result ValidateProviderRegistrationAgainstSchema(_In_ MI_ClassA *miClassArray,
                                                    _In_ MI_InstanceA *miRegistrationArray,
                                                    _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result ValidateSchema(_In_ MI_ClassA *miClassArray, 
                         _In_ MI_Uint32 classIndex, 
                         _Inout_updates_(resSize) MI_Boolean *bResourceVisited, 
                         _In_ MI_Uint32 resSize,
                         _In_ MI_Boolean bConfigurationResource,
                         _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result ValidateDSCProviderMapping(_In_ MI_Instance *regInstance, 
                                     _In_ MI_Class *regClass,
                                     _In_ MI_Session *miSession,
                                     _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result ValidateDSCProviderMappingForWMIV2Provider( _In_z_ const MI_Char *namespaceName,
                                                     _In_ MI_Class *regClass,
                                                     _In_ MI_Session *miSession,
                                                     _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result ValidateDSCProviderSchema(_In_ MI_ClassA *miClassArray, 
                                    _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateDSCProviderRegistrationInstance(_In_ MI_InstanceA *miInstanceArray, 
                                                  _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateDSCDocumentInstance(_In_ MI_InstanceA *miInstanceArray, 
                                      _In_ MI_Uint32 flags,
                                                  _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateClassProperties(_In_ MI_Class *classInfo, 
                                  _In_ BaseResourceConfiguration *properties,
                                  _In_ MI_Uint32 basePropertyCount,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateBaseResourceConfigurationClass(_In_ MI_Class *baseResourceClass, 
                                                 _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateBaseResourceRegistrationClass(_In_ MI_Class *baseRegistrationClass, 
                                                _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateCimResourceRegistrationClass(_In_ MI_Class *cimRegistrationClass, 
                                               _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidatePSResourceRegistrationClass(_In_ MI_Class *psRegistrationClass, 
                                              _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateConfigurationDocumentClass(_In_ MI_Class *configDocumentClass, 
                                             _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateMetaConfigurationClass(_In_ MI_Class *configDocumentClass, 
                                         _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateBaseCredClass(_In_ MI_Class *configDocumentClass, 
                                _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateWindowsCredClass(_In_ MI_Class *configDocumentClass, 
                                   _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateKeyValuePairClass(_In_ MI_Class *configDocumentClass, 
                                   _Outptr_result_maybenull_ MI_Instance **extendedError );

MI_Result ValidateDocumentInstance(_In_ MI_Instance *docInstance,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError );

//Validation function for all those classes that inherit directly or indirectly from the metaconfigurationresource base class
MI_Result ValidateClassPropertiesForMetaConfResourceChildren(_In_ MI_Class *configDocumentClass,
                                                             _Outptr_result_maybenull_ MI_Instance **extendedError);

/*Function to check if the configurationsource exists as a defined download manatger
varifyConfigSource = MI_TRUE to verify ConfigurationSource and MI_FALSE to verify ResourceModuleSource
*/
MI_Result ValidatePartialMeta_ConfigDownloadMgr(_In_ MI_Boolean verifyConfigSource,
                                                _In_ MI_Instance* partialInstance,                                               
                                                _In_ MI_Instance* metaConfInstance,
                                                _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result ValidatePartialMeta_ExclusiveResources(_In_ MI_Instance* partialInstance,
                                                 _Inout_ MI_StringA* arrayOutput,
                                                 _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result ValidatePartialConfigMetaConfDefinition(_In_ MI_Instance* metaConfigInstance,
                                                  _Outptr_result_maybenull_ MI_Instance** cimErrorDetails);

MI_Result ValidateResourceObeysExclusiveResourcesRule(_In_z_ MI_Char* exclusiveResourceString,
                                                      _In_ MI_Instance* resourceInstance,
                                                      _Inout_ MI_Boolean * obeysExclusiveResources,
                                                      _Outptr_result_maybenull_ MI_Instance** cimErrorDetails);

MI_Result ValidateConfigurationDownloadManagerProperties(_In_ MI_Class *configDocumentClass, 
                                                         _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result ValidateMetaConfResourceProperties(_In_ MI_Class *configDocumentClass, 
                                             _Outptr_result_maybenull_ MI_Instance **extendedError);

MI_Result ValidateWebDownloadManagerProperties(_In_ MI_Class *configDocumentClass, 
                                             _Outptr_result_maybenull_ MI_Instance **extendedError);



typedef struct _InfraSchemaValidator
{
    const MI_Char *wszClassName;
    MI_Result (*Validator) (_In_ MI_Class *configDocumentClass, 
        _Outptr_result_maybenull_ MI_Instance **extendedError );
} InfraSchemaValidator;


#endif //__MODULEVALIDATOR_H_

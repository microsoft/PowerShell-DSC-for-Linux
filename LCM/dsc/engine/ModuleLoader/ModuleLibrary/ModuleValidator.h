
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

typedef struct _InfraSchemaValidator
{
    const MI_Char *wszClassName;
    MI_Result (*Validator) (_In_ MI_Class *configDocumentClass, 
        _Outptr_result_maybenull_ MI_Instance **extendedError );
} InfraSchemaValidator;


#endif //__MODULEVALIDATOR_H_

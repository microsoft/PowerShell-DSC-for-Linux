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


#include "DSC_Systemcalls.h"
#include "micodec.h"
#include "EngineHelper.h"
#include "ModuleHandler.h"
#include "ModuleHandlerInternal.h"
#include "ModuleValidator.h"
#include "EventWrapper.h"
#include "Resources_LCM.h"



#define OMI_BaseResource_GetMethodCount 4
#define OMI_BaseResource_TestMethodCount 5
#define OMI_BaseResource_SetMethodCount 4



InfraSchemaValidator g_InfraSchemaValidators[] = 
{
    {BASE_RESOURCE_CLASSNAME, ValidateBaseResourceConfigurationClass},
    {BASE_DOCUMENT_CLASSNAME, ValidateConfigurationDocumentClass},
    {BASE_REGISTRATION, ValidateBaseResourceRegistrationClass},
    {BASE_REGISTRATION_WMIV2PROVIDER, ValidateCimResourceRegistrationClass},
    {BASE_REGISTRATION_PSPROVIDER, ValidatePSResourceRegistrationClass},
    {METACONFIG_CLASSNAME, ValidateMetaConfigurationClass},
    {MSFT_BASECREDENTIAL_CLASSNAME, ValidateBaseCredClass},
    {MSFT_KEYVALUEPAIR_CLASSNAME, ValidateKeyValuePairClass},        
    {NULL, NULL}
};

BaseResourceConfiguration g_ConfigurationDocumentProperties[] =
{
    {OMI_ConfigurationDocument_Version,        MI_STRING},
    {OMI_ConfigurationDocument_Author,         MI_STRING},
    {OMI_ConfigurationDocument_Copyright,      MI_STRING},
    {OMI_ConfigurationDocument_HelpInfoUri,    MI_STRING},
    {OMI_ConfigurationDocument_ContentType,    MI_STRING},
    {OMI_ConfigurationDocument_GenerationDate, MI_STRING},
    {OMI_ConfigurationDocument_GenerationHost, MI_STRING},
    {NULL,                                      0}
};    

BaseResourceConfiguration g_PSResourceProperties[] =
{
    {MSFT_PSConfigurationProviderRegistration_ModuleName,         MI_STRING},
    {NULL,                                                        0}
};    

BaseResourceConfiguration g_CimResourceProperties[] =
{
    {MSFT_CimConfigurationProviderRegistration_Namespace,         MI_STRING},
    {NULL,                                                        0}
};    

BaseResourceConfiguration g_BaseRegistrationProperties[] =
{
    {MSFT_BaseConfigurationProviderRegistration_ClassName,                  MI_STRING},
    {MSFT_BaseConfigurationProviderRegistration_DSCEngineCompatVersion,     MI_STRING},
    {MSFT_BaseConfigurationProviderRegistration_DSCModuleVersion,           MI_STRING},
    {NULL,                  0}
};    

BaseResourceConfiguration g_BaseResourceProperties[] =
{
    {OMI_BaseResource_ResourceId,         MI_STRING},
    {OMI_BaseResource_SourceInfo,         MI_STRING},
    {OMI_BaseResource_DependsOn,           MI_STRINGA},
    {OMI_BaseResource_ModuleName,         MI_STRING},
    {OMI_BaseResource_ModuleVersion,      MI_STRING},        
    {NULL,                                              0}
};    

PropertyQualifier g_BaseResourceQualifiers[] =
{
    {OMI_BaseResource_ResourceId,         QUALIFIER_REQUIRED},
    {OMI_BaseResource_SourceInfo,         QUALIFIER_WRITE},
    {OMI_BaseResource_DependsOn,           QUALIFIER_WRITE},
    {OMI_BaseResource_ModuleName,         QUALIFIER_REQUIRED},
    {OMI_BaseResource_ModuleVersion,      QUALIFIER_REQUIRED}, 
    {NULL,                                              NULL}
};

BaseResourceConfiguration g_MetaConfigProperties[] =
{
    { MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins,             MI_UINT32},
    { MSFT_DSCMetaConfiguration_RebootNodeIfNeeded,                         MI_BOOLEAN},        
    { MSFT_DSCMetaConfiguration_Credential,                                 MI_INSTANCE},
    { MSFT_DSCMetaConfiguration_ConfigurationMode,                          MI_STRING},
    { MSFT_DSCMetaConfiguration_RefreshMode,                                MI_STRING},
    { MSFT_DSCMetaConfiguration_CertificateID,                              MI_STRING},           
    { MSFT_DSCMetaConfiguration_ConfigurationID,                            MI_STRING},             
    { MSFT_DSCMetaConfiguration_DownloadManagerName,                        MI_STRING},
    { MSFT_DSCMetaConfiguration_DownloadManagerCustomData,                  MI_INSTANCEA},   
    { MSFT_DSCMetaConfiguration_RefreshFrequencyMins,                       MI_UINT32},
    { MSFT_DSCMetaConfiguration_AllowModuleOverwrite,                       MI_BOOLEAN},
	{ MSFT_DSCMetaConfiguration_LocalConfigurationManagerState,				MI_STRING},
    {NULL,                                                                  0}
};    

BaseResourceConfiguration g_BaseCredProperties[] =
{
    {MSFT_Credential_UserName, MI_STRING},
    {MSFT_Credential_Password, MI_STRING},
    {NULL,                                 0}
};

BaseResourceConfiguration g_KeyValuePairProperties[] =
{
    {MSFT_KeyValuePair_Key, MI_STRING},
    {MSFT_KeyValuePair_Value, MI_STRING},
    {NULL,                                  0}
};


MI_Result ValidateInfrastructureSchema(_In_ MI_ClassA *miClassArray, 
                                       _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0, yCount = 0;
    if( extendedError )
        *extendedError = NULL;
    SetJobId();
    DSC_EventWriteValidatingInfrastructureSchema(miClassArray->size);
    //Validate various infrastructure classes
    for( xCount = 0 ; xCount < miClassArray->size ; xCount++)
    {
        for (yCount = 0; g_InfraSchemaValidators[yCount].wszClassName != NULL; yCount++)
        {
            if( Tcscasecmp(miClassArray->data[xCount]->classDecl->name, g_InfraSchemaValidators[yCount].wszClassName) == 0 )
            {
                break;
            }
        }

        if( g_InfraSchemaValidators[yCount].wszClassName == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
        {
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_INFRASCHEMA); 
        }

        r = g_InfraSchemaValidators[yCount].Validator(miClassArray->data[xCount], extendedError);
        if( r != MI_RESULT_OK)
        {
            return r; 
        }
    }
    return r;
}


/*Validate Provider registration against schema*/

MI_Result ValidateProviderRegistrationAgainstSchema(_In_ MI_ClassA *miClassArray,
                                                    _In_ MI_InstanceA *miRegistrationArray,
                                                    _Outptr_result_maybenull_ MI_Instance **extendedError)

{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount=0 , yCount = 0;
    MI_Uint32 registrationFoundCount = 0, schemaFoundCount = 0;
    MI_Value value;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    DSC_EventWriteValidatingProviderRegistration(miClassArray->size,miRegistrationArray->size);

    //Test1 : only 1 registration per class
    //Test2 : no class left out without registration(except for meta config), also validates that registration not targeting more than 1 class.
    //Test3: no registration instance left out without class
    //Test4 : no two classes with same name    

    for (xCount = 0 ; xCount < miClassArray->size ; xCount++)
    {
        if (miClassArray->data[xCount]->classDecl->superClass &&
            Tcscasecmp(miClassArray->data[xCount]->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0)
        {
            schemaFoundCount++;
        }

        //Test4
        for (yCount = xCount + 1 ; yCount <  miClassArray->size ; yCount++)
        {
            if (Tcscasecmp(miClassArray->data[yCount]->classDecl->name, miClassArray->data[xCount]->classDecl->name) == 0  || NitsShouldFault(NitsHere(), NitsAutomatic))
            {
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVREG_MULTI);  
            }
        }
    }

    for (xCount = 0 ; xCount < miRegistrationArray->size ; xCount++)
    {
        for (yCount = 0 ; yCount < miClassArray->size ; yCount++)
        {
            if ((miClassArray->data[yCount]->classDecl->superClass &&
                 Tcscasecmp(miClassArray->data[yCount]->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0) ||
                 Tcscasecmp(miClassArray->data[xCount]->classDecl->name, METACONFIG_CLASSNAME) == 0)
            {
                r = DSC_MI_Instance_GetElement(miRegistrationArray->data[xCount], MSFT_BaseConfigurationProviderRegistration_ClassName, 
                    &value, NULL, NULL, NULL); 
                if (r != MI_RESULT_OK )
                {
                    return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREG_MANDATORY);
                }

                if (Tcscasecmp(value.string, miClassArray->data[yCount]->classDecl->name) == 0 )
                {
                    // Test1
                    registrationFoundCount++;
                    break;
                }
            }
        }

        // Test3
        if (yCount == miClassArray->size  || NitsShouldFault(NitsHere(), NitsAutomatic))
        {
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVREG_NOCLASS);    
        }
    }

    // Test2
    if (registrationFoundCount != schemaFoundCount  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVREG_NOREG);
    }

    return r;
}


MI_Result ValidateSchema(_In_ MI_ClassA *miClassArray, 
                         _In_ MI_Uint32 classIndex, 
                         _Inout_updates_(resSize) MI_Boolean *bResourceVisited, 
                         _In_ MI_Uint32 resSize,
                         _In_ MI_Boolean bConfigurationResource,
                         _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0, yCount = 0;    
    const MI_ClassDecl *classToCheck = NULL; 
    MI_Uint32 keyPropertyCount = 0;
    MI_Uint32 propertyBitMask = 0; // 1 = Read, 2 = Write, 4 = Key, 8 = Required
     if( extendedError )
        *extendedError = NULL;

    //PrintClass(miClassArray->data[classIndex]);

    if( classIndex >= miClassArray->size || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_SCHEMA_INVPARAM);        
    }

    classToCheck = miClassArray->data[classIndex]->classDecl;
    DSC_EventWriteValidatingSchema(classToCheck->name,classIndex,miClassArray->size);
   
    /*Test7*/
    if( classToCheck->numMethods != 0  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_SCHEMA_NOMETHOD);
    }

    /*Test 4*/
    // validate class qualifiers
    for( xCount = 0 ; xCount < classToCheck->numQualifiers; xCount++)
    {
        if( Tcscasecmp(QUALIFIER_VERSION, classToCheck->qualifiers[xCount]->name) == 0 )
        {
            break;
        }
    }
    if( xCount == classToCheck->numQualifiers || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_NOT_FOUND, extendedError, ID_MODMAN_VALIDATE_SCHEMA_VERSIONQUAL);
    }

    /*Test 2*/
    /*Rule1: Read and (Key or Required or Write) can't coexist*/
    /*Rule2: Write and (Read) can't coexist*/    
    /*Rule3: Key and (Read) can't coexist*/    
    /*Rule4: Required and (Read) can't coexist*/        
    for( xCount = 0 ; xCount < classToCheck->numProperties; xCount++)
    {
        propertyBitMask = 0;
        /*Test5: Reference types are not supported.*/
        if( classToCheck->properties[xCount]->type == MI_REFERENCE ||
            classToCheck->properties[xCount]->type == MI_REFERENCEA  || NitsShouldFault(NitsHere(), NitsAutomatic))
        {
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_SCHEMA_NOSUPP_REF);
        }
        if( classToCheck->properties[xCount]->flags & MI_FLAG_READONLY )
        {
            propertyBitMask |= PROPERTY_BITMASK_READ;
        }
        if( classToCheck->properties[xCount]->flags & MI_FLAG_KEY )
        {
            propertyBitMask |= PROPERTY_BITMASK_KEY;
            keyPropertyCount++;
        }
        if( classToCheck->properties[xCount]->flags & MI_FLAG_REQUIRED )
        {
            propertyBitMask |= PROPERTY_BITMASK_REQUIRED;
        }

        for( yCount = 0 ; yCount < classToCheck->properties[xCount]->numQualifiers; yCount++)
        {
            const MI_Qualifier *classQual = classToCheck->properties[xCount]->qualifiers[yCount];
            if( Tcscasecmp(classQual->name, QUALIFIER_WRITE) == 0 )
            {
                propertyBitMask |= PROPERTY_BITMASK_WRITE;
                break;
            }
        }

        // Do actual validation
        if( ((propertyBitMask & PROPERTY_BITMASK_READ) && ( (propertyBitMask & PROPERTY_BITMASK_ALL) & ~(PROPERTY_BITMASK_READ)))  || (NitsShouldFault(NitsHere(), NitsAutomatic)))
        {
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_SCHEMA_NOMANDATORY_QUALIFIER);
        }

        /*Test6: Embedded object type support*/
        if( classToCheck->properties[xCount]->className != NULL)
        {
            // check for class in existing classes
            for( yCount = 0 ; yCount < miClassArray->size && yCount < resSize; yCount++)
            {
                if( Tcscasecmp(miClassArray->data[yCount]->classDecl->name, classToCheck->properties[xCount]->className) == 0 )
                {
                    if( bResourceVisited[yCount] == MI_TRUE) // Already processed
                    {
                        break;
                    }
                    else
                    {
                        bResourceVisited[yCount] = MI_TRUE;
                        r = ValidateSchema(miClassArray, yCount, bResourceVisited, resSize, MI_FALSE,extendedError);
                        if( r != MI_RESULT_OK)
                        {
                            return r;
                        }
                    }
                }
            }

        }
    }
    if( bConfigurationResource && 
        Tcscasecmp(miClassArray->data[classIndex]->classDecl->name, METACONFIG_CLASSNAME) != 0 &&
        Tcscasecmp(miClassArray->data[classIndex]->classDecl->name, MSFT_LOGRESOURCENAME) != 0)
    {
        if( keyPropertyCount < 1  || NitsShouldFault(NitsHere(), NitsAutomatic))
        {
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_SCHEMA_NOKEY);
        }
    }

    return r;

}

MI_Result ValidateDSCProviderSchema(_In_ MI_ClassA *miClassArray, 
                                    _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0;
    MI_Uint32 configurationResourceCount = 0; 
    MI_Boolean *bResourceVisited = NULL; 
    // Test1: Exactly 1 resource per MOF file
    // Test2: All properties should contain qualifiers read, write, required or write and at least 1 key property.
    // Test3: Embedded object and its associated property validation
    // Test4: Version qualifier should be present
    // Test5: Only supported data type is available.
    // Test6: No reduntant class ( all classes should refered from resource class).
    // Test7: Class shouldn't contain any method.

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    if (miClassArray == NULL || miClassArray->size == 0  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVSCHEMA_NORES);
    }

    DSC_EventWriteValidatingDSCProviderSchema(miClassArray->size);
    
    bResourceVisited = (MI_Boolean*)DSC_malloc(sizeof(MI_Boolean) * miClassArray->size, NitsHere());
    if (bResourceVisited == NULL )
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }

    memset(bResourceVisited, MI_FALSE, sizeof(MI_Boolean) * miClassArray->size );

    /*Start Test*/
    for (xCount = 0 ; xCount < miClassArray->size ; xCount++)
    {
        if ((miClassArray->data[xCount]->classDecl->superClass &&
             Tcscasecmp(BASE_RESOURCE_CLASSNAME, miClassArray->data[xCount]->classDecl->superClass) == 0) ||
             Tcscasecmp(METACONFIG_CLASSNAME, miClassArray->data[xCount]->classDecl->name) == 0)
        {
            bResourceVisited[xCount] = MI_TRUE;
            configurationResourceCount++;
            r = ValidateSchema(miClassArray, xCount, bResourceVisited, miClassArray->size, MI_TRUE, extendedError);
            if (r != MI_RESULT_OK)
            {
                DSC_free(bResourceVisited);
                return r;
            }
        }
    }

    /*Test6*/
    for (xCount = 0 ; xCount < miClassArray->size ; xCount++)
    {
        if(bResourceVisited[xCount] == MI_FALSE || NitsShouldFault(NitsHere(), NitsAutomatic))
        {
            DSC_free(bResourceVisited);
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVSCHEMA_NOTREFERRED);
        }
    }

    DSC_free(bResourceVisited);
    
    /*Test1*/
    if (configurationResourceCount != 1  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVSCHEMA_ONERES);
    }

    return r;
}

MI_Result ValidateDSCDocumentInstance(_In_ MI_InstanceA *miInstanceArray, 
                                      _In_ MI_Uint32 flags,
                                      _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0, yCount = 0;
    MI_Instance *instanceToCheck = NULL;
    MI_Uint32 instanceFlags;
    const MI_Char* resourceID;
    MI_Boolean hasMetaConfig = MI_FALSE;
    
    // Test1 : should contain all key and required properties.
    if( extendedError )
        *extendedError = NULL;    

    if( miInstanceArray == NULL || miInstanceArray->size == 0  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVSCHEMA_NORES);
    }      
    DSC_EventWriteValidatingDSCDocInstance(miInstanceArray->size,flags);
    for( xCount = 0; xCount < miInstanceArray->size; xCount++)
    {
        instanceToCheck = miInstanceArray->data[xCount];
        if(Tcscasecmp(instanceToCheck->classDecl->name, METACONFIG_CLASSNAME) == 0 )
        {
            hasMetaConfig = MI_TRUE;
        }
        for( yCount = 0; yCount < instanceToCheck->classDecl->numProperties ; yCount++)
        {
            if( (instanceToCheck->classDecl->properties[yCount]->flags & (MI_FLAG_KEY | MI_FLAG_REQUIRED) ) != 0 )
            {
                //The property must be specified.
                r = DSC_MI_Instance_GetElement(instanceToCheck, instanceToCheck->classDecl->properties[yCount]->name, NULL, NULL, &instanceFlags, NULL);
                if( r != MI_RESULT_OK || (instanceFlags & MI_FLAG_NULL) != 0 )
                {
                    r = MI_RESULT_NOT_FOUND;
                    return GetCimMIError1Param(r, extendedError, ID_MODMAN_VALIDATE_PROVSCHEMA_NOMANDATORY, instanceToCheck->classDecl->properties[yCount]->name);
                }
            }
        }
        
    }

    //check meta configuration, which should not be merged with other configurations (> 2 because we always have the OMI_ConfigurationDocument)
    if(flags & VALIDATE_METACONFIG_INSTANCE)
    {
        if(hasMetaConfig == MI_FALSE || miInstanceArray->size > 2)
        {
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_METACONFIG_NOTFOUND_OR_MORE);
        }
    }
    else
    {
        if(hasMetaConfig == MI_TRUE)
        {
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_METACONFIG_MERGED_WITH_OTHERCONFIG);
        }
    }
    //check duplicate resourceid
    for( xCount = 0; xCount < miInstanceArray->size; xCount++)
    {
        instanceToCheck = miInstanceArray->data[xCount];
        resourceID = GetResourceId(instanceToCheck);
        for( yCount = xCount+1; yCount < miInstanceArray->size; yCount++)
        {
            const MI_Char *resourceID2 = GetResourceId(miInstanceArray->data[yCount]);
            if(resourceID && resourceID2 && Tcscasecmp(resourceID, resourceID2) == 0)
            {
                return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_MODMAN_DUPLICATE_RESOURCEID, resourceID);
            }
        }
        
    }
    return r;
}


MI_Result ValidateDSCProviderRegistrationInstance(_In_ MI_InstanceA *miInstanceArray, 
                                                  _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r = MI_RESULT_OK;
    MI_Instance *instanceToCheck = NULL;
    const MI_Char *className = NULL;
    MI_Boolean bWMIv2ProviderRegistration = MI_FALSE;
    // Test1: Exactly 1 registration per MOF file
    // Test2: Should be either PS registration or WMIv2 provider registration
    // Test3: Validate base properties.
    // Test3: WMIv2 provider registration and properties
    // Test4: PS Provider registration and properties.

    if( extendedError )
        *extendedError = NULL;

    /*Start Test*/
    /*Test1*/
    if( miInstanceArray == NULL || miInstanceArray->size != 1  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVSCHEMA_ONERES);
    }    
    instanceToCheck = miInstanceArray->data[0];
    
    /*Test2*/
    r = DSC_MI_Instance_GetClassName(instanceToCheck, &className);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_CLASSNAME);
    }
    DSC_EventWriteValidatingDSCProviderRegistrationInstance(className);
    if( Tcscasecmp(className, BASE_REGISTRATION_WMIV2PROVIDER) == 0 )
    {
        bWMIv2ProviderRegistration = MI_TRUE;
    }
    else if( Tcscasecmp(className, BASE_REGISTRATION_PSPROVIDER) == 0 )
    {
        bWMIv2ProviderRegistration = MI_FALSE;
    }
    else 
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_TYPE);
    }

    /*Test3 All Base properties MUST be specified*/
    r = DSC_MI_Instance_GetElement(instanceToCheck, MSFT_BaseConfigurationProviderRegistration_ClassName, NULL, NULL, NULL, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_PROP_CLASSNAME);
    }
    r = DSC_MI_Instance_GetElement(instanceToCheck, MSFT_BaseConfigurationProviderRegistration_DSCEngineCompatVersion, NULL, NULL, NULL, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_PROP_COMPATVERSION);
    }
    r = DSC_MI_Instance_GetElement(instanceToCheck, MSFT_BaseConfigurationProviderRegistration_DSCModuleVersion, NULL, NULL, NULL, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_PROP_MODULEVERSION);
    }    

    if( bWMIv2ProviderRegistration)
    {
        /*Test4 All DSC_MI_Instance_GetElement properties*/
        r = DSC_MI_Instance_GetElement(instanceToCheck, MSFT_CimConfigurationProviderRegistration_Namespace, NULL, NULL, NULL, NULL);
        if( r != MI_RESULT_OK)
        {
            return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_PROP_NAMESPACE);
        }
    }
    else
    {
        /*Test5 All MSFT_PSConfigurationProviderRegistrationn properties*/
        r = DSC_MI_Instance_GetElement(instanceToCheck, MSFT_PSConfigurationProviderRegistration_ModuleName, NULL, NULL, NULL, NULL);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_PROP_MODULENAME);
        }    
    }

    return r;
}

MI_Result ValidateClassProperties(_In_ MI_Class *classInfo, 
                                  _In_ BaseResourceConfiguration *properties,
                                  _In_ MI_Uint32 basePropertyCount,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r = MI_RESULT_OK;
    MI_Type type;
    MI_Uint32 count = 0;
    MI_Uint32 proCount = 0;
    if( extendedError )
        *extendedError = NULL;

    
    /*Start Test*/
    for (count = 0; properties[count].wszPropName != NULL; count++)
    {
        DSC_EventWriteValidatingClassProperty(properties[count].wszPropName,classInfo->classDecl->name);
        r = DSC_MI_Class_GetElement(classInfo, properties[count].wszPropName, NULL, NULL, &type, NULL, NULL, NULL, NULL);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_CLASSPROP_MAND_NAME);
        }

        if(type != properties[count].propType || NitsShouldFault(NitsHere(), NitsAutomatic))
        {
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_CLASSPROP_MAND_TYPE);
        }
    }

    /*validate property counts*/
    r = DSC_MI_Class_GetElementCount(classInfo, &proCount);
    if(r != MI_RESULT_OK)
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_CLASSPROP_MAND_GETCLASS);
    }

    if((count + basePropertyCount) != proCount || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_CLASSPROP_MAND_NOMATCH);
    }

    return r;
}

MI_Result ValidateBaseResourceConfigurationClass(_In_ MI_Class *baseResourceClass, 
                                                 _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;
    MI_QualifierSet qualifierSet;
    MI_Uint32 xCount = 0;
    MI_Type qualifierType;
    MI_Uint32 qualifierFlags;
    MI_Value qualifierValue;
    MI_Uint32 index;

    r = ValidateClassProperties(baseResourceClass, g_BaseResourceProperties, 0, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }

    /* validate qualifier */ 
    for (xCount = 0; g_BaseResourceQualifiers[xCount].wszPropName != NULL; xCount++)
    {
        r = DSC_MI_Class_GetElement(baseResourceClass, g_BaseResourceQualifiers[xCount].wszPropName, NULL, NULL, NULL, NULL, &qualifierSet, NULL, NULL);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_CLASSPROP_MAND_NAME );
        }

        r = DSC_MI_QualifierSet_GetQualifier(&qualifierSet, g_BaseResourceQualifiers[xCount].wszQualifierName, &qualifierType, &qualifierFlags, &qualifierValue, &index);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_BASERES_NOQUAL);
        }
    }

    return r;
}

MI_Result ValidateBaseResourceRegistrationClass(_In_ MI_Class *baseRegistrationClass, 
                                                _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;
    MI_Uint32 flags;

    r = ValidateClassProperties(baseRegistrationClass, g_BaseRegistrationProperties, 0, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }

    /* Validate key for className */
    r = DSC_MI_Class_GetElement(baseRegistrationClass, MSFT_BaseConfigurationProviderRegistration_ClassName, NULL, NULL, NULL, NULL, NULL, &flags, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_CLASSPROP_MAND_NAME );
    }

    if( !(flags & MI_FLAG_KEY) || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_BASERES_NOQUAL);
    }

    return r;
}

MI_Result ValidateCimResourceRegistrationClass(_In_ MI_Class *cimRegistrationClass, 
                                               _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;

    r = ValidateClassProperties(cimRegistrationClass, g_CimResourceProperties, MSFT_CimConfigurationProviderRegistration_BaseProperty_Count, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }

    /* validate parent class */
    if(Tcscasecmp(cimRegistrationClass->classDecl->superClass, BASE_REGISTRATION) != 0 || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_BASERES_V2DERIVATEION);
    }

    return r;
}

MI_Result ValidatePSResourceRegistrationClass(_In_ MI_Class *psRegistrationClass, 
                                              _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;

    r = ValidateClassProperties(psRegistrationClass, g_PSResourceProperties, MSFT_PSConfigurationProviderRegistration_BaseProperty_Count, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }

    /* validate parent */
    if(Tcscasecmp(psRegistrationClass->classDecl->superClass, BASE_REGISTRATION) != 0 || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_BASERES_PSDERIVATEION);
    }

    return r;
}

MI_Result ValidateConfigurationDocumentClass(_In_ MI_Class *configDocumentClass, 
                                             _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;
    r = ValidateClassProperties(configDocumentClass, g_ConfigurationDocumentProperties, 0, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }
    return r;
}

MI_Result ValidateMetaConfigurationClass(_In_ MI_Class *configDocumentClass, 
                                         _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;
    r = ValidateClassProperties(configDocumentClass, g_MetaConfigProperties, MSFT_DSCMetaConfiguration_BaseProperty_Count, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }
    return r;
}

MI_Result ValidateBaseCredClass(_In_ MI_Class *configDocumentClass, 
                                _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;
    r = ValidateClassProperties(configDocumentClass, g_BaseCredProperties, 0, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }
    return r;
}

MI_Result ValidateKeyValuePairClass(_In_ MI_Class *configDocumentClass, 
                                   _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    MI_Result r;
    r = ValidateClassProperties(configDocumentClass, g_KeyValuePairProperties, 0, extendedError);
    if( r!= MI_RESULT_OK)
    {
        return r;
    }
    return r;    
}


MI_Result ValidateDSCProviderMapping(_In_ MI_Instance *regInstance, 
                                     _In_ MI_Class *regClass,
                                     _In_ MI_Session *miSession,
                                     _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Value namespaceName;
    
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    /*Validation only for configuration classes which are registered as wmiv2 provider.
           MSFT_LogResource is a special class.*/
    if ( (Tcscasecmp(regClass->classDecl->name, MSFT_LOGRESOURCENAME) != 0) &&
        ((regClass->classDecl->superClass &&
         Tcscasecmp(regClass->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0) ||
         Tcscasecmp(regClass->classDecl->name, METACONFIG_CLASSNAME) == 0))
    {
        r = DSC_MI_Instance_GetElement(regInstance, MI_T("Namespace"), &namespaceName, NULL, NULL, NULL);
        if (r == MI_RESULT_OK )
        {
            r = ValidateDSCProviderMappingForWMIV2Provider(namespaceName.string, regClass, miSession, extendedError);
        }
        else if (r == MI_RESULT_NOT_FOUND || r == MI_RESULT_NO_SUCH_PROPERTY)
        {
            // It is not wmiv2 provider registration, PS provider validation should happen here
            return MI_RESULT_OK;
        }
        else
        {
            return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_MAPPING_NAMESPACE );
        }
    }

    return r;
}

MI_Result ValidateDSCProviderMappingForWMIV2Provider( _In_z_ const MI_Char *namespaceName,
                                                     _In_ MI_Class *regClass,
                                                     _In_ MI_Session *miSession,
                                                     _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Result innerR = MI_RESULT_OK;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails = NULL;     
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Uint32 xCount, usefulMethodCount =0 ;
    const MI_Class *resultClass;
    const MI_MethodDecl *methodDecl = NULL;
    if( extendedError )
        *extendedError = NULL;

    MI_Session_GetClass(miSession, 0, 0, namespaceName, regClass->classDecl->name, NULL, &operation);

    r = MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
    if( result != MI_RESULT_OK)
    {
        r = result;
    }     
    if( r != MI_RESULT_OK)
    {
        if( completionDetails != NULL)
        {
            innerR = DSC_MI_Instance_Clone( completionDetails, extendedError);
        }
        if( innerR != MI_RESULT_OK || completionDetails == NULL)
        {
            r = GetCimMIError(r, extendedError,ID_CAINFRA_GETINSTANCE_FAILED);
        }
        MI_Operation_Close(&operation);
        return r;
    }
    // check class methods and its name
    for( xCount = 0 ; xCount < resultClass->classDecl->numMethods; xCount++)
    {
        methodDecl = resultClass->classDecl->methods[xCount];

        if( Tcscasecmp(methodDecl->name, OMI_BaseResource_GetMethodName) == 0 )
        {
            if( methodDecl->numParameters != OMI_BaseResource_GetMethodCount  || NitsShouldFault(NitsHere(), NitsAutomatic))
            {
                MI_Operation_Close(&operation);
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_VALIDATE_MAPPING_PARAM_GET);
            }
            usefulMethodCount++;
        }
        else if(Tcscasecmp(methodDecl->name, OMI_BaseResource_TestMethodName) == 0 )
        {
            if( methodDecl->numParameters != OMI_BaseResource_TestMethodCount  || NitsShouldFault(NitsHere(), NitsAutomatic))
            {
                MI_Operation_Close(&operation);
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_VALIDATE_MAPPING_PARAM_TEST);                
            }
            usefulMethodCount++;
        }
        else if (Tcscasecmp(methodDecl->name, OMI_BaseResource_SetMethodName) == 0)
        {
            if( methodDecl->numParameters != OMI_BaseResource_SetMethodCount  || NitsShouldFault(NitsHere(), NitsAutomatic) )
            {
                MI_Operation_Close(&operation);
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_VALIDATE_MAPPING_PARAM_SET);                
            }
            usefulMethodCount++;
        }
    }

    MI_Operation_Close(&operation);

    if( usefulMethodCount != 3  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        // at least one method is missing
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_VALIDATE_MAPPING_PARAM_ALLFAILED );
    }
    return MI_RESULT_OK;
}

MI_Boolean ValidateABCFormatVersion(_In_z_ const MI_Char *str)
{
    MI_Boolean bValidFormat = MI_TRUE;
    MI_Uint32 dwDots = 0;
    while( *str != '\0')
    {
        if( !(*str >= MI_T('0') && *str <= MI_T('9') ) )
        {
            if( *str == '.' )
            {
                dwDots++;
                if( dwDots > 2 )
                {
                    break;
                }
            }
            else
            {
                bValidFormat = MI_FALSE;
                break;
            }
        }
        str++;
    }
    if( bValidFormat && dwDots == 2 )
    {
        return MI_TRUE;
    }
    return MI_FALSE;
}

MI_Result ValidateDocumentInstance(_In_ MI_Instance *docInstance,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError )
{
    
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 yCount = 0;
    MI_Uint32 Flags;
    MI_Value value;
    DSC_EventWriteValidatingDocInstance();
    
    // Test1 : should have 'Version' property with correct format.
    if( extendedError )
        *extendedError = NULL;    
    
    for( yCount = 0; yCount < docInstance->classDecl->numProperties ; yCount++)
    {
        r = DSC_MI_Instance_GetElement(docInstance, OMI_ConfigurationDocument_Version, &value, NULL, &Flags, NULL);
        if( r != MI_RESULT_OK || (Flags & MI_FLAG_NULL) != 0 )
        {
            r = MI_RESULT_NOT_FOUND;
            return GetCimMIError1Param(r, extendedError, ID_MODMAN_VALIDATE_PROVSCHEMA_NOMANDATORY, OMI_ConfigurationDocument_Version);
        }
        if( !ValidateABCFormatVersion(value.string))
        {
            return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError, ID_MODMAN_VALIDATE_DOCINS_VERSION);
        }
    }
    return r;    
}






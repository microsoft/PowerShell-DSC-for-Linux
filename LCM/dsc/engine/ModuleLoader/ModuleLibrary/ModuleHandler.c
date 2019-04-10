/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <MI.h>
#include "EngineHelper.h"
#include "micodec.h"
#include "ModuleHandler.h"
#include "ModuleHandlerInternal.h"
#include "DSC_Systemcalls.h"
#include "ModuleValidator.h"
#include "EventWrapper.h"

#include "Resources_LCM.h"

#include "NativeResourceProviderMiModule.h"

extern const ModuleManagerFT g_ModuleManagerFT;

#if defined(BUILD_OMS)
extern MI_Boolean g_DscHost;
#endif

MI_Result MI_CALL InitializeModuleManager( MI_Uint32 flags,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError,
                                          _Outptr_result_maybenull_ ModuleManager **moduleManager)
{
    MI_Result r = MI_RESULT_OK;
    ModuleManager *tempModuleManager = NULL;
    if( moduleManager == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_MODMAN_NULLPARAM);
    }
    SetJobId();

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *moduleManager = NULL;

    tempModuleManager = (ModuleManager *) DSC_malloc( sizeof(ModuleManager), NitsHere());
    if( tempModuleManager == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    tempModuleManager->reserved2 = (ptrdiff_t) NULL;
    tempModuleManager->reserved1 = MODULEHANDLER_NOTLOADED;
    tempModuleManager->ft = &g_ModuleManagerFT;
    *moduleManager = tempModuleManager;

    return r;
}

MI_Result MI_CALL LoadModuleManager(_Inout_ ModuleManager *moduleManager,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    if( moduleManager->reserved1 == MODULEHANDLER_LOADED)
    {
        return MI_RESULT_OK;
    }
    else
    {
        MI_Application *miApp = NULL;
        ModuleLoaderObject *moduleLoader = NULL;
        MI_Result r = MI_RESULT_OK;
        /*Create MI_Application object*/
        miApp = (MI_Application *) DSC_malloc( sizeof(MI_Application), NitsHere());
        if( miApp == NULL)
        {
            return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
        }
        memset(miApp,  0, sizeof(MI_Application));
        r = DSC_MI_Application_Initialize(0, NULL, NULL, miApp);
        if( r != MI_RESULT_OK)
        {
            DSC_free(miApp);
            return GetCimMIError(r, extendedError,ID_MODMAN_APPINIT_FAILED);
        }
        r = GetModuleLoader(miApp, &moduleLoader, extendedError);
        if( r != MI_RESULT_OK)
        {
            MI_Application_Close(miApp);
            DSC_free(miApp);
            return r;
        }
        moduleManager->reserved2 = (ptrdiff_t) moduleLoader;
        moduleManager->reserved1 = MODULEHANDLER_LOADED;
        return MI_RESULT_OK;
    }
}


MI_Result MI_CALL ModuleManager_Close(_Inout_ ModuleManager *moduleManager,
                                      _Outptr_opt_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    ModuleLoaderObject *moduleLoader = NULL;

    if (extendedError)
    {
        *extendedError = NULL;
    }

    if( moduleManager == NULL ||
        moduleManager->ft == NULL)
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_PARAM_INVALID);
    }

    //Cleanup stuff
    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    if( moduleLoader)
    {
        for( xCount = 0 ; xCount< moduleLoader->schemaCount ; xCount++)
        {
            MI_Class_Delete(moduleLoader->providerSchema[xCount]);
        }
        DSC_free(moduleLoader->providerSchema);

        for( xCount = 0 ; xCount< moduleLoader->regisrationCount; xCount++)
        {
            MI_Instance_Delete(moduleLoader->registrationSchema[xCount]);
        }
        DSC_free(moduleLoader->registrationSchema);
        DSC_free(moduleLoader->schemaToRegistrationMapping);
        MI_OperationOptions_Delete(moduleLoader->options);
        MI_OperationOptions_Delete(moduleLoader->strictOptions);
        MI_Deserializer_Close(moduleLoader->deserializer);
        MI_Application_Close(moduleLoader->application);
        DSC_free(moduleLoader->application);
        DSC_free(moduleLoader->deserializer);
        DSC_free(moduleLoader->options);
        DSC_free(moduleLoader->strictOptions);
        DSC_free(moduleLoader);
    }

    DSC_free(moduleManager);
    return MI_RESULT_OK;
}



MI_Result ModuleManager_LoadInstanceDocument (
    _In_ ModuleManager *moduleManager,
    MI_Uint32 flags,
    _In_count_(documentSize) MI_Uint8 *document,
    _In_ MI_Uint32 documentSize,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_InstanceA *resources,
    _Outptr_result_maybenull_ MI_Instance **documentInstance)
{
    MI_Result r = MI_RESULT_OK;
    MI_InstanceA miInstanceArray = {0};
    MI_ClassA miClassArray = {0};
    ModuleLoaderObject *moduleLoader = NULL;


    if( moduleManager == NULL || document == NULL || resources == NULL || documentInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_LOADDOC_NULLPARAM);
    }

    memset(resources, 0, sizeof(MI_InstanceA));
    *documentInstance = NULL;

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    miClassArray.size = moduleLoader->schemaCount;
    miClassArray.data = moduleLoader->providerSchema;

    r = GetInstanceFromBuffer( moduleManager, moduleLoader->application, moduleLoader->deserializer, moduleLoader->options, &miClassArray, document, documentSize, &miInstanceArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }
    /*FilterForConfigurationResource will cleanup as needed.*/
    r = FilterForConfigurationResource(&miInstanceArray, resources, documentInstance, extendedError);
    return r;
}

MI_Result ModuleManager_LoadInstanceDocumentFromLocation (
    _In_ ModuleManager *moduleManager,
    MI_Uint32 flags,
    _In_z_  const MI_Char *documentLocation,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_InstanceA *resources,
    _Outptr_result_maybenull_ MI_Instance **documentInstance)
{
    MI_Result r = MI_RESULT_OK;
    MI_InstanceA miInstanceArray = {0};
    MI_ClassA miClassArray = {0};
    ModuleLoaderObject *moduleLoader = NULL;
    DSC_EventWriteMessageLoadingInstance(documentLocation);

    if( moduleManager == NULL || documentLocation == NULL || documentInstance == NULL || resources == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_LOADDOC_NULLPARAM);
    }
    memset(resources, 0, sizeof(MI_InstanceA));

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }


    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    miClassArray.size = moduleLoader->schemaCount;
    miClassArray.data = moduleLoader->providerSchema;

    r = GetInstanceFromSingleMOF( moduleManager, flags | VALIDATE_DOCUMENT_INSTANCE,
                moduleLoader->application, moduleLoader->deserializer,
                moduleLoader->options, moduleLoader->strictOptions, &miClassArray,
                documentLocation, &miInstanceArray, extendedError);

    if( r != MI_RESULT_OK)
    {
        return r;
    }
    r = FilterForConfigurationResource(&miInstanceArray, resources, documentInstance,extendedError);

    return r;
}


MI_Result  ModuleManager_GetRegistrationInstance (
    _In_ ModuleManager *moduleManager,
    _In_z_ const MI_Char *className,
    _Outptr_result_maybenull_ const MI_Instance **registrationInstance,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    MI_Result r = MI_RESULT_OK;
    ModuleLoaderObject *moduleLoader = NULL;
    if( moduleManager == NULL || className == NULL || registrationInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_GETREG_NULLPARAM);
    }

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *registrationInstance = NULL;
    //special case for meta configuration where we don't need the registration
    if(Tcscasecmp(className, METACONFIG_CLASSNAME) == 0)
    {
        return r;
    }

    for( xCount = 0 ; xCount < moduleLoader->schemaCount; xCount++)
    {
        if( Tcscasecmp(className, moduleLoader->providerSchema[xCount]->classDecl->name) == 0 )
        {
            if( moduleLoader->schemaToRegistrationMapping[xCount] == (MI_Uint32)-1 ||
                moduleLoader->schemaToRegistrationMapping[xCount] > moduleLoader->regisrationCount)
            {
                return GetCimMIError(MI_RESULT_NOT_FOUND, extendedError,ID_MODMAN_REGINS_NOTFOUND);
            }
            *registrationInstance = moduleLoader->registrationSchema[ moduleLoader->schemaToRegistrationMapping[xCount] ] ;
            return MI_RESULT_OK;
        }
    }
    /*If here we didn't find the registration*/
    return GetCimMIError(MI_RESULT_NOT_FOUND, extendedError,ID_MODMAN_CONFIGCLASS_NOTREG);

}

/*Callers responsibility to fill Namespace if needed.*/

_Return_type_success_(return == MI_RESULT_OK)
    MI_Result ModuleManager_GetProviderCompatibleInstance (
    _In_ ModuleManager *moduleManager,
    _In_ MI_Instance *inInstance,
    _Outptr_result_maybenull_ MI_Instance **outInstance,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    ModuleLoaderObject *moduleLoader = NULL;
    MI_Instance * filteredInstance = NULL;

    if( moduleManager == NULL || inInstance == NULL || outInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_GETCOMPAT_NULLPARAM);
    }

    *outInstance = NULL;

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }
    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    // Remove non-provider properties.
    r = GetFilteredResource(moduleLoader->application ,inInstance, &filteredInstance, extendedError);
    if( r != MI_RESULT_OK)
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_GETFILTERED_FAILED);
    }
    *outInstance = filteredInstance;
    return r;
}

MI_Result ModuleManager_Update (
    _In_ ModuleManager *moduleManager,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0;
    MI_Application *miApp = NULL;
    ModuleLoaderObject *inModuleLoader = NULL;
    ModuleLoaderObject *outModuleLoader = NULL;

    if( moduleManager == NULL ||
        moduleManager->ft == NULL  || NitsShouldFault(NitsHere(), NitsAutomatic) )
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_PARAM_INVALID);
    }
    inModuleLoader = (ModuleLoaderObject*) moduleManager->reserved2;
    if( inModuleLoader == NULL)
    {
        // create application object.
        miApp = (MI_Application *) DSC_malloc( sizeof(MI_Application), NitsHere());
        if( miApp == NULL)
        {
            return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
        }
        memset(miApp,  0, sizeof(MI_Application));
        r = DSC_MI_Application_Initialize(0, NULL, NULL, miApp );
        if( r != MI_RESULT_OK)
        {
            DSC_free(miApp);
            return GetCimMIError(r, extendedError,ID_MODMAN_APPINIT_FAILED);
        }
    }
    else
    {
        miApp = inModuleLoader->application;
    }
    /*First get new registration information. If we fail, user can still use old data.*/
    r = GetModuleLoader(miApp, &outModuleLoader, extendedError);
    if( r != MI_RESULT_OK)
    {
        if( inModuleLoader == NULL)
        {
            MI_Application_Close(miApp);
            DSC_free(miApp);
        }
        return r;
    }

    if(inModuleLoader)
    {
        //Cleanup stuff
        for( xCount = 0 ; xCount< inModuleLoader->schemaCount ; xCount++)
        {
            MI_Class_Delete(inModuleLoader->providerSchema[xCount]);
        }
        DSC_free(inModuleLoader->providerSchema);

        for( xCount = 0 ; xCount< inModuleLoader->regisrationCount; xCount++)
        {
            MI_Instance_Delete(inModuleLoader->registrationSchema[xCount]);
        }
        DSC_free(inModuleLoader->registrationSchema);
        DSC_free(inModuleLoader->schemaToRegistrationMapping);
        DSC_free(inModuleLoader);
    }

    moduleManager->reserved2 = (ptrdiff_t) outModuleLoader;

    return MI_RESULT_OK;

}


MI_Result GetModuleLoader( _In_ MI_Application *miApp,
                          _Out_ ModuleLoaderObject **moduleLoader,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_ClassA miClassArray = {0};
    MI_InstanceA miInstanceArray = {0};
    MI_Deserializer *de;
    MI_OperationOptions *options;
    MI_OperationOptions *strictOptions;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    r = GetMofDeserializer(miApp, &de, &options, &strictOptions, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    /*Get the schema from MOFs*/
    r = GetSchemaFromMOFs(miApp, de, options, &miClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        MI_Deserializer_Close(de);
        MI_OperationOptions_Delete(options);
        DSC_free(de);
        DSC_free(options);
        CleanUpClassCache(&miClassArray);
        return r;
    }

    // No need to do this after removing OMI since we will discover resources directly from shared objects (except for DIY DSC)
    // Get the Registration information from MOFs
    r = GetRegistrationInstanceFromMOFs(NULL, miApp, de, options, strictOptions, &miClassArray, &miInstanceArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        MI_Deserializer_Close(de);
        MI_OperationOptions_Delete(options);
        DSC_free(de);
        DSC_free(options);
        CleanUpClassCache(&miClassArray);
        CleanUpInstanceCache(&miInstanceArray);
        return r;
    }

#if defined(BUILD_OMS)
    if (g_DscHost == MI_FALSE)
    {
#endif
        // Get the Registration information from shared objects
        r = GetRegistrationInstanceFromSharedObjects(NULL, miApp, de, options, strictOptions, &miClassArray, &miInstanceArray, extendedError);
        if( r != MI_RESULT_OK)
        {
            MI_Deserializer_Close(de);
            MI_OperationOptions_Delete(options);
            DSC_free(de);
            DSC_free(options);
            CleanUpClassCache(&miClassArray);
            CleanUpInstanceCache(&miInstanceArray);
            return r;
        }

        // No need to do this after removing OMI since we will discover resources directly from shared objects (except for DIY DSC)
        /*Perform registration against schema validation*/
        r = ValidateProviderRegistrationAgainstSchema(&miClassArray, &miInstanceArray, extendedError);
        if( r != MI_RESULT_OK)
        {
            MI_Deserializer_Close(de);
            MI_OperationOptions_Delete(options);
            DSC_free(de);
            DSC_free(options);
            CleanUpClassCache(&miClassArray);
            CleanUpInstanceCache(&miInstanceArray);
            return r;
        }
#if defined(BUILD_OMS)
    }
#endif

    /*Form mapping tables*/

    r = GetMappingTable(miApp, &miClassArray, &miInstanceArray, moduleLoader, extendedError);
    if( r != MI_RESULT_OK)
    {
        MI_Deserializer_Close(de);
        MI_OperationOptions_Delete(options);
        DSC_free(de);
        DSC_free(options);
        CleanUpClassCache(&miClassArray);
        CleanUpInstanceCache(&miInstanceArray);
        return r;
    }

    (*moduleLoader)->deserializer = de;
    (*moduleLoader)->options = options;
    (*moduleLoader)->strictOptions = strictOptions;
    return r;
}

/*caller will cleanup miClassArray*/
MI_Result GetCoreSchema(_In_ MI_Application *miApp,
                        _In_ MI_Deserializer *deserializer,
                        _In_ MI_OperationOptions * options,
                        _Inout_ MI_ClassA *miClassArray,
                        _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return GetSystemSchema(miApp, deserializer, options, BASESCHEMA_FILENAME, NULL, miClassArray, extendedError);
}

MI_Result GetMetaConfigSchema(_In_ MI_Application *miApp,
                              _In_ MI_Deserializer *deserializer,
                              _In_ MI_OperationOptions * options,
                              _Inout_ MI_ClassA *miClassArray,
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    r = GetCoreSchema(miApp, deserializer, options, miClassArray, extendedError);
    if(r != MI_RESULT_OK)
    {
        return r;
    }
    return GetSystemSchema(miApp, deserializer, options, METACONFIGSCHEMA_FILENAME, miClassArray, miClassArray, extendedError);
}

MI_Result GetMappingTable(_In_ MI_Application *miApp,
                          _In_ MI_ClassA *miClassArray,
                          _In_ MI_InstanceA *miInstanceArray,
                          _Out_ ModuleLoaderObject **moduleLoader,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0, yCount = 0;
    MI_Result r = MI_RESULT_OK;
    MI_Value className;
    MI_Session miSession = MI_SESSION_NULL;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    /*Allocate structures*/
    *moduleLoader = (ModuleLoaderObject *)DSC_malloc(sizeof(ModuleLoaderObject), NitsHere());
    if( *moduleLoader == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
    (*moduleLoader)->schemaToRegistrationMapping = (MI_Uint32 *) DSC_malloc(sizeof(MI_Uint32) * miClassArray->size, NitsHere());
    if( (*moduleLoader)->schemaToRegistrationMapping == NULL)
    {
        DSC_free(*moduleLoader);
        *moduleLoader = NULL;
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    memset((*moduleLoader)->schemaToRegistrationMapping, -1, sizeof(MI_Uint32) * miClassArray->size );

    r = DSC_MI_Application_NewSession(miApp, NULL, NULL, NULL, NULL, NULL, &miSession);
    if( r != MI_RESULT_OK )
    {
        DSC_free(*moduleLoader);
        *moduleLoader = NULL;
        return GetCimMIError(r, extendedError, ID_CAINFRA_NEWSESSION_FAILED);
    }

    /* Create Mapping*/
    for( xCount = 0; xCount < miClassArray->size ; xCount++)
    {
        for( yCount = 0; yCount < miInstanceArray->size ; yCount++)
        {
            r = DSC_MI_Instance_GetElement(miInstanceArray->data[yCount], MI_T("className"), &className, NULL, NULL, NULL);
            if( r != MI_RESULT_OK )
            {
                DSC_free(*moduleLoader);
                *moduleLoader = NULL;
                MI_Session_Close(&miSession, NULL, NULL);
                return GetCimMIError(r, extendedError, ID_MODMAN_MAPPING_CLASSNAME_NOTFOUND);
            }
            if( Tcscasecmp( miClassArray->data[xCount]->classDecl->name , className.string) == 0 )
            {
                ((*moduleLoader)->schemaToRegistrationMapping)[xCount] = yCount;
                break;
            }
        }
    }

    MI_Session_Close(&miSession, NULL, NULL);

    /*Fill structures*/
    (*moduleLoader)->application = miApp;
    (*moduleLoader)->providerSchema = miClassArray->data;
    (*moduleLoader)->schemaCount = miClassArray->size;
    (*moduleLoader)->registrationSchema = miInstanceArray->data;
    (*moduleLoader)->regisrationCount = miInstanceArray->size;
    return MI_RESULT_OK;
}

MI_Result GetFilteredResource( _In_ MI_Application *miApp,
                              _In_ MI_Instance *inInstance,
                              _Outptr_result_maybenull_ MI_Instance **outInstance,
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0, yCount = 0;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;

    if( miApp == NULL || inInstance == NULL || outInstance == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_ARGNULL);
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *outInstance = NULL;

    r = DSC_MI_Application_NewInstance(miApp, inInstance->classDecl->name, NULL, outInstance);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NEWAPPLICATIONINSTANCE_FAILED);
    }

    /*Filter properties*/
    for( xCount = 0 ; xCount < inInstance->classDecl->numProperties ; xCount++)
    {
        for (yCount = 0; g_BaseResourceConfiguration[yCount].wszPropName != NULL; yCount++)
        {
            if( Tcscasecmp(inInstance->classDecl->properties[xCount]->name, g_BaseResourceConfiguration[yCount].wszPropName) == 0 )
            {
                break;
            }
        }
        if( g_BaseResourceConfiguration[yCount].wszPropName == NULL)
        {
            r = DSC_MI_Instance_GetElement(inInstance, inInstance->classDecl->properties[xCount]->name,
                &value, &type, &flags, NULL);
            if( r != MI_RESULT_OK )
            {
                MI_Instance_Delete(*outInstance);
                *outInstance = NULL;
                return GetCimMIError(r, extendedError,ID_MODMAN_GETELEMENT_FAILED);
            }
            // Not base resource property, add it
            r = DSC_MI_Instance_AddElement(*outInstance, inInstance->classDecl->properties[xCount]->name,
                &value, type, flags);
            if( r != MI_RESULT_OK)
            {
                *outInstance = NULL;
                return GetCimMIError(r, extendedError,ID_MODMAN_GETELEMENT_FAILED);
            }

        }
    }
    return r;

}

MI_Result GetInstanceFromBuffer(_In_opt_ ModuleManager *moduleManager,
                                _In_ MI_Application *miApp,
                                _In_ MI_Deserializer *deserializer,
                                _In_ MI_OperationOptions * options,
                                _In_ MI_ClassA *classArray,
                                _In_count_(instanceBufferSize) MI_Uint8 *instanceBuffer,
                                _In_ MI_Uint32 instanceBufferSize,
                                _Inout_ MI_InstanceA *miInstanceArray,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_InstanceA *miTempInstanceArray = NULL;
    MI_Uint32 readBytes;
    // MI_Uint32 xCount = 0, classCount = 0, yCount = 0;
    // ClassNameCacheA classNameCache = { 0 };

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.


    r = MI_Deserializer_DeserializeInstanceArray(deserializer, 0, options, 0, instanceBuffer, instanceBufferSize, classArray, &readBytes, &miTempInstanceArray, extendedError);
    if( r != MI_RESULT_OK || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        CleanUpDeserializerInstanceCache(miTempInstanceArray);
        return r;
    }

    // Update cache with discovered native resources(not through OMI) 
    r = UpdateInstanceArray(miTempInstanceArray, miInstanceArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerInstanceCache(miTempInstanceArray);
    }

    return r;
}

MI_Result GetInstanceFromSingleMOF(_In_opt_ ModuleManager *moduleManager,
                                   _In_ MI_Uint32 flags,
                                   _In_ MI_Application *miApp,
                                   _In_ MI_Deserializer *deserializer,
                                   _In_ MI_OperationOptions * options,
                                   _In_ MI_OperationOptions * strictOptions,
                                   _In_ MI_ClassA *classArray,
                                   _In_z_ const MI_Char *mofModuleFilePath,
                                   _Inout_ MI_InstanceA *miInstanceArray,
                                   _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    /*Form full path to mof file*/
    MI_InstanceA *miTempInstanceArray = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 contentSize;
    MI_Uint32 readBytes;
    MI_ClassA miClassArray = {0};

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    r = ReadFileContent(mofModuleFilePath, &pbuffer, &contentSize, extendedError);
    if(r != MI_RESULT_OK)
    {
        return r;
    }
    miClassArray.size = classArray->size;
    miClassArray.data = classArray->data;
    
    // We will discover PS schema only if we are running in windows.
    // So nothing here for Linux.

    miTempInstanceArray = NULL;

    r = MI_Deserializer_DeserializeInstanceArray(deserializer, 0, strictOptions, 0, pbuffer, contentSize, &miClassArray, &readBytes, &miTempInstanceArray, extendedError);
    
    if( r != MI_RESULT_OK )
    {
        Print_MI_Instance(*extendedError);
        DSC_free(pbuffer);
        return r;
    }

    if(pbuffer)
    {
        DSC_free(pbuffer);
        pbuffer = NULL;
    }

    if( flags & VALIDATE_REGISTRATION_INSTANCE)
    {
        /*Validate Registration Instance*/
        r = ValidateDSCProviderRegistrationInstance(miTempInstanceArray, extendedError);
        if( r != MI_RESULT_OK)
        {
            CleanUpDeserializerInstanceCache(miTempInstanceArray);
            return r;
        }
    }
    else if( flags & VALIDATE_DOCUMENT_INSTANCE )
    {
        /*Validate mof instance*/
        r = ValidateDSCDocumentInstance(miTempInstanceArray, flags, extendedError);
        if( r != MI_RESULT_OK)
        {
            CleanUpDeserializerInstanceCache(miTempInstanceArray);
            return r;
        }
    }

    // Here we should discover resources and update our resource cache
    /*Update actual cache*/
    r = UpdateInstanceArray(miTempInstanceArray, miInstanceArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerInstanceCache(miTempInstanceArray);
    }

    return r;
}

MI_Result MI_CALL SchemaCallback(_In_opt_ void *context,
                                 _In_opt_z_ const MI_Char *serverName,
                                 _In_opt_z_ const MI_Char *namespaceName,
                                 _In_z_ const MI_Char *className,
                                 _Outptr_ MI_Class **requestedClassObject)
{
    MI_ClassA *classContainer = NULL;
    MI_Uint32 iCount = 0;
    if( context == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    classContainer = (MI_ClassA*)context;
    for( iCount = 0 ; iCount < classContainer->size; iCount++)
    {
        if(Tcscasecmp(className , classContainer->data[iCount]->classDecl->name) == 0 )
        {
            return MI_Class_Clone(classContainer->data[iCount], requestedClassObject);
        }
    }
    return MI_RESULT_NOT_FOUND;
}

/*Cleanup is done by this method. Caller should not cleanup in success or failure case*/
MI_Result FilterForConfigurationResource(_Inout_ MI_InstanceA *inputInstanceArray,
                                         _Inout_ MI_InstanceA *outputInstanceArray,
                                         _Outptr_result_maybenull_ MI_Instance **documentInstance,
                                         _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0, yCount = 0;
    MI_Uint32 flags = 0;
    MI_Uint32 resourceCount = 0;
    MI_Uint8 *embeddedResourceMap = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Instance **tempOutput = NULL;
    MI_Boolean bDocumentInstance = MI_FALSE;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *documentInstance = NULL;

    //if there are embedded resource we won't copy them to inputInstanceArray so need to release them ourselves
    embeddedResourceMap = (MI_Uint8 *)DSC_malloc( inputInstanceArray->size * sizeof(MI_Uint8), NitsHere());
    if( embeddedResourceMap == NULL)
    {
        CleanUpInstanceCache(inputInstanceArray);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    for(xCount = 0 ; xCount < inputInstanceArray->size ; xCount++)
    {
        embeddedResourceMap[xCount] = 0;

        if( Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->name, BASE_DOCUMENT_CLASSNAME) == 0 )
        {
            if( bDocumentInstance )
            {
                //Error multiple instances specified, only 1 allowed
                CleanUpInstanceCache(inputInstanceArray);
                DSC_free(embeddedResourceMap);
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_MULTIPLEINS);
            }
            else
            {
                *documentInstance = inputInstanceArray->data[xCount];
                bDocumentInstance = MI_TRUE;
                embeddedResourceMap[xCount] = 2;
            }
        }
        //we don't check resourceid if it's other embeded instances
        else if ((inputInstanceArray->data[xCount]->classDecl->superClass != NULL && Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0) ||
                 Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->name, METACONFIG_CLASSNAME) == 0)
        {
            resourceCount++;

            // Resource must contain resourceID as mandatory parameter.
            if(inputInstanceArray->data[xCount]->classDecl->superClass != NULL && Tcscasecmp(inputInstanceArray->data[xCount]->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0 )
            {
                r = DSC_MI_Instance_GetElement(inputInstanceArray->data[xCount], OMI_BaseResource_ResourceId, NULL, NULL, &flags, NULL);
                if( r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
                {
                    CleanUpInstanceCache(inputInstanceArray);
                    DSC_free(embeddedResourceMap);
                    return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_RESOURCEID);
                }
            }
            embeddedResourceMap[xCount] = 1;
        }
    }

    if( bDocumentInstance == MI_FALSE || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        //mandatory Document instance not specified.
        CleanUpInstanceCache(inputInstanceArray);
        DSC_free(embeddedResourceMap);
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_FILTER_NOINSTANCE);

    }
    tempOutput = (MI_Instance **)DSC_malloc( resourceCount * sizeof(MI_Instance*), NitsHere());
    if( tempOutput == NULL)
    {
        CleanUpInstanceCache(inputInstanceArray);
        DSC_free(embeddedResourceMap);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }

    for(xCount = 0 ; xCount < inputInstanceArray->size ; xCount++)
    {
        if(embeddedResourceMap[xCount] == 1)
        {
            tempOutput[yCount++] = inputInstanceArray->data[xCount];
        }
        else if (embeddedResourceMap[xCount] == 0)
        {
            MI_Instance_Delete(inputInstanceArray->data[xCount]);
        }
    }
    outputInstanceArray->size = resourceCount;
    outputInstanceArray->data = tempOutput;
    DSC_free(inputInstanceArray->data);
    DSC_free(embeddedResourceMap);
    return r;
}

MI_Result GetMofDeserializer(_In_ MI_Application *miApp,
                             _Outptr_result_maybenull_ MI_Deserializer **deserializer,
                             _Outptr_result_maybenull_ MI_OperationOptions **operationOptions,
                             _Outptr_result_maybenull_ MI_OperationOptions **strictOperationOptions,
                             _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    *operationOptions = NULL;

    *deserializer = (MI_Deserializer*) DSC_malloc(sizeof(MI_Deserializer), NitsHere());
    if(*deserializer == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memset(*deserializer, 0, sizeof(MI_Deserializer));

    *operationOptions = (MI_OperationOptions*) DSC_malloc(sizeof(MI_OperationOptions), NitsHere());
    if(*operationOptions == NULL)
    {
        DSC_free(*deserializer);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memset(*operationOptions, 0, sizeof(MI_OperationOptions));

    r = DSC_MI_Application_NewOperationOptions(miApp, MI_FALSE, *operationOptions);
    if (r!=MI_RESULT_OK)
    {
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        return GetCimMIError(r, extendedError, ID_MODMAN_NEWOO_FAILED);
    }

    r = DSC_MI_OperationOptions_SetString(*operationOptions, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, MOFCODEC_SCHEMA_VALIDATION_IGNORE, 0);
    if (r!=MI_RESULT_OK )
    {
        MI_OperationOptions_Delete(*operationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
       return GetCimMIError(r, extendedError, ID_MODMAN_OOSET_FAILED);
    }

    *strictOperationOptions = (MI_OperationOptions*) DSC_malloc(sizeof(MI_OperationOptions), NitsHere());
    if(*strictOperationOptions == NULL)
    {
        MI_OperationOptions_Delete(*operationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memset(*strictOperationOptions, 0, sizeof(MI_OperationOptions));

    r = DSC_MI_Application_NewOperationOptions(miApp, MI_FALSE, *strictOperationOptions);
    if (r!=MI_RESULT_OK)
    {
        MI_OperationOptions_Delete(*operationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        DSC_free(*strictOperationOptions);
        return GetCimMIError(r, extendedError, ID_MODMAN_NEWOO_FAILED);
    }

    r = DSC_MI_OperationOptions_SetString(*strictOperationOptions, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, MOFCODEC_SCHEMA_VALIDATION_STRICT, 0);
    if (r!=MI_RESULT_OK )
    {
        MI_OperationOptions_Delete(*operationOptions);
        MI_OperationOptions_Delete(*strictOperationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        DSC_free(*strictOperationOptions);
       return GetCimMIError(r, extendedError, ID_MODMAN_OOSET_FAILED);
    }

    r = DSC_MI_Application_NewDeserializer_Mof(miApp, 0, MOFCODEC_FORMAT, *deserializer);
    if (r!=MI_RESULT_OK)
    {
        MI_OperationOptions_Delete(*operationOptions);
        MI_OperationOptions_Delete(*strictOperationOptions);
        DSC_free(*deserializer);
        DSC_free(*operationOptions);
        DSC_free(*strictOperationOptions);
        return GetCimMIError(r, extendedError, ID_LCMHELPER_DESERIALIZER_CREATE_FAILED);
    }

    return MI_RESULT_OK;
}

/*caller will cleanup miClassArray*/
MI_Result GetSystemSchema(_In_ MI_Application *miApp,
                          _In_ MI_Deserializer *deserializer,
                          _In_ MI_OperationOptions * options,
                          _In_z_ const MI_Char* schemaName,
                          _In_opt_ MI_ClassA *inputClasses,
                          _Inout_ MI_ClassA *miClassArray,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Char *envResolvedPath = NULL;
    MI_Char *filePath = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_ClassA * miTempClassArray = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 contentSize;
    MI_Uint32 readBytes;

    if( miClassArray == NULL || miApp == NULL  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_SYSTEMCACHE_INVALIDPARAM);
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    /* Resolve schema search path*/
    r = ResolvePath(&envResolvedPath, &filePath, GetCoreSchemaPath(), schemaName, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    if( envResolvedPath)
    {
        DSC_free(envResolvedPath);
    }

    r = ReadFileContent(filePath, &pbuffer, &contentSize, extendedError);
    if(r != MI_RESULT_OK )
    {
        return r;
    }

    r = MI_Deserializer_DeserializeClassArray(deserializer, 0, options, 0, pbuffer, contentSize, inputClasses, NULL, NULL, &readBytes, &miTempClassArray, extendedError);

    if( filePath)
    {
        DSC_free(filePath);
    }

    if(pbuffer)
    {
        DSC_free(pbuffer);
    }

    if( r != MI_RESULT_OK || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        if( r == MI_RESULT_OK)
        {
            r = MI_RESULT_FAILED;
        }
        return r;
    }

    /*Validate Schema*/
    r = ValidateInfrastructureSchema(miTempClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        return r;
    }

    /*Update actual cache*/
    r = UpdateClassArray(miTempClassArray, miClassArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerClassCache(miTempClassArray);
    }
    return r;
}

MI_Result GetSchemaFromSingleMOF(_In_ MI_Application *miApp,
                                 _In_ MI_Deserializer *deserializer,
                                 _In_ MI_OperationOptions * options,
                                 _In_z_ MI_Char *mofModulePath,
                                 _In_z_ MI_Char *schemaFileName,
                                 _Inout_ MI_ClassA *miClassArray,
                                 _In_opt_ MI_ClassA *miDiscoverdSchema,
                                 _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    int result = 0;
    /*Form full path to mof file*/
    MI_Char *fullPath = NULL;
    MI_ClassA *miTempClassArray = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 contentSize;
    MI_Uint32 readBytes;
    size_t fullPathLength = Tcslen(mofModulePath) + 1 + Tcslen(schemaFileName) + 1; // mofModulePath\schemaFileName
    MI_DeserializerCallbacks cb;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    fullPath = (MI_Char*)DSC_malloc(fullPathLength* sizeof(MI_Char), NitsHere());
    if( fullPath == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
    result = Stprintf(fullPath, fullPathLength, MI_T("%T/%T"), mofModulePath, schemaFileName);

    if( result <= 0|| NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }

    r = ReadFileContent(fullPath, &pbuffer, &contentSize, extendedError);
    if(r != MI_RESULT_OK)
    {
        return r;
    }

    memset(&cb, 0, sizeof(cb));
    if(miDiscoverdSchema)
    {
        cb.classObjectNeededContext = miDiscoverdSchema;
    }
    else
    {
        cb.classObjectNeededContext = miClassArray;
    }

    cb.classObjectNeeded = SchemaCallback;
    r = MI_Deserializer_DeserializeClassArray(deserializer, 0, options, &cb, pbuffer, contentSize, NULL, NULL, NULL, &readBytes, &miTempClassArray, extendedError);
    DSC_free(fullPath);
    DSC_free(pbuffer);
    if( r != MI_RESULT_OK || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        if(r == MI_RESULT_OK)           //nits faulted; return MI_RESULT_FAILED
        {
            r = MI_RESULT_FAILED;
        }
        return r;
    }

    /*Validate Schema*/

    r = ValidateDSCProviderSchema(miTempClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        CleanUpDeserializerClassCache(miTempClassArray);
        return r;
    }


    /*Update actual cache*/
    r = UpdateClassArray(miTempClassArray, miClassArray, extendedError, MI_TRUE);
    if( r != MI_RESULT_OK )
    {
        CleanUpDeserializerClassCache(miTempClassArray);
    }
    return r;

}

/*Caller will free up miInstanceArray*/
MI_Result GetRegistrationInstanceFromMOFs(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char **pathsForRegistration;
    MI_Uint32 count=0;
    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.
    pathsForRegistration = (MI_Char**)DSC_malloc(NUM_PATHS_TO_LOOK_FOR_PROVIDERS * sizeof(MI_Char*), NitsHere());
    if( pathsForRegistration == NULL)
    {
        return MI_RESULT_FAILED;
    }
    pathsForRegistration[0] = (MI_Char*)GetRegistrationInstanceSearchPath();
    pathsForRegistration[1] = (MI_Char*)GetRegistrationInstanceSearchPathProgFiles();
    for (count = 0; count < NUM_PATHS_TO_LOOK_FOR_PROVIDERS; count++)
    {
        r= GetEachRegistrationInfo(moduleManager,miApp,deserializer,options,strictOptions,classArray,miInstanceArray, extendedError,pathsForRegistration[count]);
        if(r != MI_RESULT_OK)
        {
            DSC_free(pathsForRegistration);
            return r;
        }
    }
    DSC_free(pathsForRegistration);
    return r;
}

/*Caller will free up miInstanceArray*/
MI_Result GetRegistrationInstanceFromSharedObjects(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result result = MI_RESULT_OK;
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;
    MI_Char *envResolvedPath = NULL;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    /* Resolve schema search path*/
    result = ResolvePath(&envResolvedPath, NULL, DSC_LIB_PATH, NULL, extendedError);
    if( result != MI_RESULT_OK )
    {
        goto clean_up;
    }

    dirHandle = Internal_Dir_Open(envResolvedPath, NitsHere() );
    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        result = GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
        goto clean_up;
    }

    dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    while( dirEntry != NULL )
    {
    //     /* Only process directories as modules are expected to have a directory per module.*/
        if( dirEntry->isDir &&
            (Tcscasecmp(MI_T(".."), dirEntry->name)!=0) &&
            (Tcscasecmp(MI_T("."), dirEntry->name)!=0))
        {
            // Assumption here is that classname matches both directory and file name

            // Get provider .so path for class
            MI_Char resources_so_path[MAX_PATH];
            int ret = Stprintf(resources_so_path, MAX_PATH, MI_T("%T/%T/lib%T.so"), DSC_LIB_PATH, dirEntry->name, dirEntry->name);
            DSC_LOG_INFO("Looking into shared object file under '%s'\n", resources_so_path);
            if (ret == -1)
            {
                result = GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_PRINTF_ERROR);
                goto clean_up;
            }

            //call MI_Module
            NativeResourceProviderMiModule* nativeResourceProviderModule = NULL;
            result = NativeResourceProviderMiModule_New(/*g_ConfigurationDetails.jobGuidString, */resources_so_path, &nativeResourceProviderModule);
            if( result != MI_RESULT_OK )
            {
                goto clean_up;
            }
            if( nativeResourceProviderModule == NULL )
            {
                goto clean_up;
            }

            // Find if class exists in this module
            result = NativeResourceProviderMiModule_HasClassDecl(nativeResourceProviderModule, dirEntry->name);
            if( result != MI_RESULT_OK )
            {
                goto in_loop_clean_up;
            }

            MI_SchemaDecl *schema = NULL;
            MI_Uint32 i, j;
            MI_ClassA newClass = { 0 };

            result = NativeResourceProviderMiModule_GetSchemaDecls(nativeResourceProviderModule, dirEntry->name, (const MI_SchemaDecl**) &schema);
            if( result != MI_RESULT_OK )
            {
                goto in_loop_clean_up;
            }

            // Get all classes and ignore the system classes.
            for( i = 0; i < schema->numClassDecls; i++ )
            {
                MI_Boolean class_already_found = MI_FALSE;
                for( j = 0; j < classArray->size; j++ )
                {
                    if ( Tcscasecmp(classArray->data[j]->classDecl->name, dirEntry->name) == 0 ) 
                    {
                        class_already_found = MI_TRUE;
                        break;
                    }
                }

                if (class_already_found == MI_TRUE)
                {
                    continue;
                }

                MI_Class * so_MIClass = NULL;
                
                // We will always submit one class at a time.
                newClass.data = (MI_Class**)DSC_malloc(sizeof(MI_Class*), NitsHere());
                if (newClass.data == NULL)
                {
                    result = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
                    goto in_loop_clean_up;
                }
                
                newClass.size = 1;
                // get MI_Class object for the classDecl
                result = GetMIClass((MI_ClassDecl *)schema->classDecls[i], &so_MIClass, extendedError);
                if( result != MI_RESULT_OK )
                {
                    goto in_loop_clean_up;
                }
                newClass.data[0] = so_MIClass;

                // // Memory for newClass will be freed by UpdateClassArray
                result = UpdateClassArray(&newClass, classArray, extendedError, MI_FALSE);
                //result = UpdateClassArray(miTempClassArray, miClassArray, extendedError, MI_TRUE);
                if( result != MI_RESULT_OK )
                {
                    goto in_loop_clean_up;
                }
            }

in_loop_clean_up:
    
            if (nativeResourceProviderModule)
            {
                DSC_free(nativeResourceProviderModule);
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    }

clean_up:

    if (dirHandle)
    {
        Internal_Dir_Close(dirHandle);
    }
    
    if (envResolvedPath)
    {
        DSC_free(envResolvedPath);
    }

    return result;
}

MI_Result GetEachRegistrationInfo(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError,
                                          _In_z_ const MI_Char * registrationPath)
{
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Char *envResolvedPath = NULL;

    /* Resolve schema search path*/
    r = ResolvePath(&envResolvedPath, NULL, registrationPath, NULL, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    /*Do actual search using search path*/

    dirHandle = Internal_Dir_Open(envResolvedPath, NitsHere() );
    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(envResolvedPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    while( dirEntry != NULL )
    {
        /* Only process directories as modules are expected to have a directory per module.*/
        if( dirEntry->isDir &&
            (Tcscasecmp(MI_T(".."), dirEntry->name)!=0) &&
            (Tcscasecmp(MI_T("."), dirEntry->name)!=0))
        {
            r = UpdateRegistrationInstanceCache(moduleManager, miApp, deserializer, options, strictOptions, classArray, envResolvedPath, dirEntry->name, miInstanceArray, extendedError);
            if( r != MI_RESULT_OK)
            {
                DSC_free(envResolvedPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    }

    /*Cleanup*/
    Internal_Dir_Close( dirHandle);
    DSC_free(envResolvedPath);
    return MI_RESULT_OK;
}

/*caller will cleanup miClassArray*/
MI_Result GetSchemaFromMOFs(_In_ MI_Application *miApp,
                            _In_ MI_Deserializer *deserializer,
                            _In_ MI_OperationOptions * options,
                            _Inout_ MI_ClassA *miClassArray,
                            _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 count=0;
    MI_Char *envResolvedPath = NULL;
    MI_Char **pathsForSchemas = NULL;

    if( miClassArray == NULL || miApp == NULL  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_MODMAN_SCHEMAFROMMOF_INVALIDPARAM);
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    /*Get DSC core schema first*/
    r = GetCoreSchema(miApp, deserializer, options, miClassArray, extendedError);
    if( r != MI_RESULT_OK)
    {
        goto clean_up;
    }

    /* Resolve meta schema search path*/
    r = ResolvePath(&envResolvedPath, NULL, GetCoreSchemaPath(), SEARCH_PATTERN_DIRECTORY, extendedError);
    if( r != MI_RESULT_OK)
    {
        goto clean_up;
    }

    //Update the cache with meta schema
    r = GetSchemaFromSingleMOF(miApp, deserializer, options, envResolvedPath, METACONFIGSCHEMA_FILENAME, miClassArray, NULL, extendedError);
    DSC_free(envResolvedPath);
    if( r != MI_RESULT_OK)
    {
        goto clean_up;
    }

    // TODO: This only belongs to OMS after removing OMI, DIY DSC still needs it: TURN OFF looking for resource MOFs
    pathsForSchemas = (MI_Char**)DSC_malloc(NUM_PATHS_TO_LOOK_FOR_PROVIDERS * sizeof(MI_Char*), NitsHere());
    if( pathsForSchemas == NULL)
    {
        return MI_RESULT_FAILED;
    }
    pathsForSchemas[0] = (MI_Char*)GetSchemaSearchPath();
    pathsForSchemas[1] = (MI_Char*)GetSchemaSearchPathProgFiles();
    for (count = 0; count < NUM_PATHS_TO_LOOK_FOR_PROVIDERS; count++)
    {
        r= UpdateClassCacheWithSchemasMofs(miApp,deserializer,options,miClassArray,extendedError,pathsForSchemas[count]);
        if( r != MI_RESULT_OK)
        {
            goto clean_up;
        }
    }

clean_up:
    if (pathsForSchemas)
    {
        DSC_free(pathsForSchemas);
    }

    return r;
}

MI_Result UpdateClassCacheWithSchemasMofs(_In_ MI_Application *miApp,
                            _In_ MI_Deserializer *deserializer,
                            _In_ MI_OperationOptions * options,
                            _Inout_ MI_ClassA *miClassArray,
                            _Outptr_result_maybenull_ MI_Instance **extendedError,
                            _In_z_ const MI_Char * schemaPath)
{
    MI_Char *envResolvedPath = NULL;
    Internal_Dir *dirHandle = NULL;
    MI_Result r = MI_RESULT_OK;
    Internal_DirEnt *dirEntry = NULL;

    /* Resolve schema search path*/
    r = ResolvePath(&envResolvedPath, NULL, schemaPath, NULL, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    /*Do actual search using search path*/

    dirHandle = Internal_Dir_Open(envResolvedPath, NitsHere() );
    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(envResolvedPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    while( dirEntry != NULL )
    {
        /* Only process directories as modules are expected to have a directory per module.*/
        if( (dirEntry->isDir) &&
            (Tcscasecmp(MI_T(".."), dirEntry->name)!=0) &&
            (Tcscasecmp(MI_T("."), dirEntry->name)!=0))
        {
            r = UpdateClassCache(miApp, deserializer, options, envResolvedPath, dirEntry->name, miClassArray, extendedError);
            if( r != MI_RESULT_OK)
            {
                DSC_free(envResolvedPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, NULL);
    }

    /*Cleanup*/
    Internal_Dir_Close( dirHandle);
    DSC_free(envResolvedPath);
    return MI_RESULT_OK;
}

/* Caller will clean up miClassArray*/
MI_Result UpdateClassCache(_In_ MI_Application *miApp,
                           _In_ MI_Deserializer *deserializer,
                           _In_ MI_OperationOptions * options,
                           _In_z_ MI_Char *rootPath,
                           _In_z_ MI_Char *directoryPath,
                           _Inout_ MI_ClassA *miClassArray,
                           _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    int result = 0;
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;

    /*Form full path to schema module*/
    MI_Char *fullPath = NULL;
    MI_Uint32 fullPathLength = (MI_Uint32) (Tcslen(rootPath) + 1 + Tcslen(directoryPath) + 1) ; // rootpath\directorypath

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    fullPath = (MI_Char*)DSC_malloc(fullPathLength* sizeof(MI_Char), NitsHere());
    if( fullPath == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
    result = Stprintf(fullPath, fullPathLength, MI_T("%T/%T"), rootPath, directoryPath);

    if( result <= 0 || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        return GetCimMIError(result, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }
    /*Find schema files*/
    dirHandle = Internal_Dir_Open(fullPath, NitsHere() );

    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_SCHEMA);
    while(dirEntry != NULL)
    {
        /* Only process files*/
        if( !dirEntry->isDir)
        {
            r = GetSchemaFromSingleMOF(miApp, deserializer, options, fullPath, dirEntry->name, miClassArray, NULL, extendedError);
            if( r != MI_RESULT_OK)
            {
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_SCHEMA);
    }

    /*Update Cache*/
    DSC_free(fullPath);
    Internal_Dir_Close( dirHandle);

    return MI_RESULT_OK;
}

MI_Result UpdateRegistrationInstanceCache(_In_opt_ ModuleManager *moduleManager,
                                          _In_ MI_Application *miApp,
                                          _In_ MI_Deserializer *deserializer,
                                          _In_ MI_OperationOptions * options,
                                          _In_ MI_OperationOptions * strictOptions,
                                          _In_ MI_ClassA *classArray,
                                          _In_z_ MI_Char *rootPath,
                                          _In_z_ MI_Char *directoryPath,
                                          _Inout_ MI_InstanceA *miInstanceArray,
                                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    int result = 0;
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;
    MI_InstanceA miTempInstanceArray = {0};

    /*Form full path to schema module*/
    MI_Char *fullPath = NULL;
    MI_Uint32 fullPathLength = (MI_Uint32)(Tcslen(rootPath) + 1 + Tcslen(directoryPath) + 1) ; // rootpath\directorypath
    MI_Uint32 fullFilePathLength = 0;
    MI_Char *fullFilePath = NULL;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    fullPath = (MI_Char*)DSC_malloc(fullPathLength* sizeof(MI_Char), NitsHere());
    if( fullPath == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
    }
    result = Stprintf(fullPath, fullPathLength, MI_T("%T/%T"), rootPath, directoryPath);

    if( result <=0 || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }

    /*Find schema files*/
    dirHandle = Internal_Dir_Open(fullPath, NitsHere() );

    if(dirHandle == NULL || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        DSC_free(fullPath);
        if( dirHandle != NULL )
            Internal_Dir_Close( dirHandle);

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_MODMAN_FINDFIRST_FAILED);
    }
    dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_REGISTRATIONINSTANCE);
    while( dirEntry != NULL)
    {
        /* Only process files*/
        if( !dirEntry->isDir)
        {
            fullFilePathLength = (MI_Uint32)(Tcslen(fullPath) + 1 + Tcslen(dirEntry->name) + 1) ; // mofModulePath\schemaFileName
            fullFilePath = (MI_Char*)DSC_malloc(fullFilePathLength* sizeof(MI_Char), NitsHere());
            if( fullFilePath == NULL)
            {
                CleanUpInstanceCache(&miTempInstanceArray);
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_LCMHELPER_MEMORY_ERROR);
            }
            result = Stprintf(fullFilePath, fullFilePathLength, MI_T("%T/%T"), fullPath, dirEntry->name);

            if( result <=0 || NitsShouldFault(NitsHere(), NitsAutomatic))
            {
                DSC_free(fullFilePath);
                CleanUpInstanceCache(&miTempInstanceArray);
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_PRINTF_ERROR);
            }
            r = GetInstanceFromSingleMOF(moduleManager, VALIDATE_REGISTRATION_INSTANCE, miApp, deserializer, options, strictOptions, classArray, fullFilePath, &miTempInstanceArray, extendedError);
            DSC_free(fullFilePath);
            if( r != MI_RESULT_OK)
            {
                CleanUpInstanceCache(&miTempInstanceArray);
                DSC_free(fullPath);
                Internal_Dir_Close( dirHandle);
                return r;
            }
        }
        dirEntry =  Internal_Dir_Read(dirHandle, SEARCH_PATTERN_REGISTRATIONINSTANCE);
    }

    /*Update Cache*/
    DSC_free(fullPath);
    Internal_Dir_Close( dirHandle);

    if( r == MI_RESULT_OK)
    {
        r = UpdateInstanceArray(&miTempInstanceArray, miInstanceArray, extendedError, MI_FALSE);
    }
    if( r != MI_RESULT_OK)
    {
        CleanUpInstanceCache(&miTempInstanceArray);
        return r;
    }

    return MI_RESULT_OK;
}

const ModuleManagerFT g_ModuleManagerFT = {
    ModuleManager_Close,
    ModuleManager_LoadInstanceDocument,
    ModuleManager_LoadInstanceDocumentFromLocation,
    ModuleManager_GetRegistrationInstance,
    ModuleManager_GetProviderCompatibleInstance,
    ModuleManager_Update
};

/*Function to get all the instances in a single array from a file*/
MI_Result GetArrayInstancesFromSingleMof(_In_ ModuleManager *moduleManager,
    MI_Uint32 flags,
    _In_z_  const MI_Char *documentLocation,
    MI_InstanceA * miInstanceArray,
    MI_Instance **extendedError,
    MI_Boolean shouldUseStrictOptions)
{
    MI_Result r = MI_RESULT_OK;
    MI_ClassA miClassArray = { 0 };
    ModuleLoaderObject *moduleLoader = NULL;
    DSC_EventWriteMessageLoadingInstance(documentLocation);

    /*Load the manager*/
    r = LoadModuleManager(moduleManager, extendedError);
    if (r != MI_RESULT_OK)
    {
        return r;
    }

    moduleLoader = (ModuleLoaderObject*)moduleManager->reserved2;
    miClassArray.size = moduleLoader->schemaCount;
    miClassArray.data = moduleLoader->providerSchema;
    if (shouldUseStrictOptions == MI_TRUE)
    {
        r = GetInstanceFromSingleMOF(moduleManager, flags | VALIDATE_DOCUMENT_INSTANCE,
            moduleLoader->application, moduleLoader->deserializer,
            moduleLoader->options, moduleLoader->strictOptions, &miClassArray,
            documentLocation, miInstanceArray, extendedError);
    }
    else
    {
        r = GetInstanceFromSingleMOF(NULL, flags | VALIDATE_DOCUMENT_INSTANCE,
            moduleLoader->application, moduleLoader->deserializer,
            moduleLoader->options, moduleLoader->options, &miClassArray,
            documentLocation, miInstanceArray, extendedError);
    }
    return r;
}

// TODO: Add error message if creating MI_class failed.
MI_Result GetMIClass(_In_ MI_ClassDecl * classDecl, _Outptr_  MI_Class ** miClass, MI_Instance ** extendedError)
{
    // Hard coded NameSpace
    MI_Char* nativeNameSpace = MI_T("root/Microsoft/DesiredStateConfiguration");
    MI_Result r = Class_New(classDecl, nativeNameSpace, 0, miClass);
    return r;
}
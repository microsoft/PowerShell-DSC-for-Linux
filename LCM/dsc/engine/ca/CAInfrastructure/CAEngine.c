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
#include "EngineHelper.h"
#include "ModuleHandler.h"
#include "ModuleHandlerInternal.h"
#include "ModuleValidator.h"
#include "EngineHelper.h"
#include "LocalConfigManagerHelperForCA.h"
#include "MI.h"
#include "CAEngine.h"
#include "CAEngineInternal.h"
#include "CACrypto.h"
#include "CAValidate.h"

#define _CA_IMPORT_ 1

#include "Resources_LCM.h"
#include "EventWrapper.h"

volatile MI_Operation *g_CurrentWmiv2Operation = NULL;

MI_Result GetDocumentEncryptionSetting( _In_ MI_Instance *documentIns, 
                                        _Inout_ MI_Boolean *bEncryptionEnabled,
                                        _Outptr_result_maybenull_z_ MI_Char **certificateid,
                                        _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Value passwordEncryption;
    MI_Value certificateID;

    MI_Result r = MI_RESULT_OK;
    MI_Instance *currentMetaConfigInstance = NULL;
    
    if (documentIns == NULL || extendedError == NULL || bEncryptionEnabled == NULL || certificateid == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }

    *extendedError = NULL;     
    *bEncryptionEnabled = MI_FALSE;
    *certificateid = NULL;

    certificateID.string = NULL;

    r = MI_Instance_GetElement(documentIns, OMI_ConfigurationDocument_ContentType, 
        &passwordEncryption, NULL, NULL, NULL);
    if (r == MI_RESULT_OK && passwordEncryption.string != NULL && 
        Tcscasecmp(passwordEncryption.string, OMI_ConfigurationDocument_ContentType_PasswordEncrypted) == 0)
    {
        r = GetMetaConfig((MSFT_DSCMetaConfiguration **)&currentMetaConfigInstance);
        if (r != MI_RESULT_OK)
        {
            return GetCimMIError(r, extendedError, ID_CA_FAILED_TO_GET_METACONFIGURATION);
        }

        r = MI_Instance_GetElement(currentMetaConfigInstance,MSFT_DSCPULL_CertificateID, 
            &certificateID, NULL, NULL, NULL);
        if (r == MI_RESULT_OK && certificateID.string != NULL && documentIns != NULL)
        {
            size_t length = Tcslen(certificateID.string)+1;
            *certificateid = (MI_Char*)DSC_malloc(length * sizeof(MI_Char), NitsHere()); 
            if (*certificateid == NULL)
            {
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
            }

            memcpy(*certificateid, certificateID.string, length * sizeof(MI_Char));

            *bEncryptionEnabled = MI_TRUE;
        }

        MI_Instance_Delete(currentMetaConfigInstance);
    }

    // Lack of a value in the document or an invalid setting doesn't stop processing.
    return MI_RESULT_OK;
}

MI_Result DecryptPasswords( _In_z_ MI_Char *certificateid,
                            _In_ MI_Instance* instance,
                            _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 yCount = 0;

    if (instance == NULL || certificateid == NULL || extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }

    *extendedError = NULL;     

    for (yCount = 0 ; yCount < instance->classDecl->numProperties; yCount++)            
    {
        const MI_PropertyDecl * miProp = instance->classDecl->properties[yCount];
        if( miProp->className != NULL && Tcscasecmp(miProp->className, MSFT_BASECREDENTIAL_CLASSNAME) == 0)
        {
            MI_Value credentialInstance;
            MI_Type type;
            MI_Uint32 flags;
            r = MI_Instance_GetElement(instance,  miProp->name, &credentialInstance, &type, &flags, NULL);
            if (r != MI_RESULT_OK)
            {                        
                return GetCimMIError(r, extendedError, ID_MODMAN_GETELEMENT_FAILED);
            }   
            if( (type == MI_INSTANCE ) && !( flags & MI_FLAG_NULL) && credentialInstance.instance != NULL)
            {
                const MI_Char *password = NULL;
                        
                MI_Value value;
                MI_Value result;

                r = MI_Instance_GetElement(credentialInstance.instance,  MSFT_Credential_Password, &value, NULL, &flags, NULL);
                if (r != MI_RESULT_OK)
                {
                    return GetCimMIError(r, extendedError, ID_MODMAN_GETELEMENT_FAILED);
                }
                if( !(flags & MI_FLAG_NULL))
                {
                    password = value.string;
                    r = Decrypt(certificateid, password, &result.string, extendedError);
                    if (r != MI_RESULT_OK)
                    {
                        return r;
                    }

                    r = MI_Instance_SetElement(credentialInstance.instance,  MSFT_Credential_Password, &result, MI_STRING, 0);
                    if (r != MI_RESULT_OK)
                    {
                        DSC_free(result.string);
                        return GetCimMIError(r, extendedError, ID_CA_CRYPTO_DECRYPTION_FAILED);
                    }

                    r = MI_Instance_SetElement(instance,  miProp->name, &credentialInstance, MI_INSTANCE, 0);
                    if (r != MI_RESULT_OK)
                    {                        
                        return GetCimMIError(r, extendedError, ID_MODMAN_GETELEMENT_FAILED);
                    }   

                    DSC_free(result.string);
                }
            }
        }
    }

    return r;
}

MI_Result InitCAHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if (cimErrorDetails == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *cimErrorDetails = NULL;    // Explicitly set *cimErrorDetails to NULL as _Outptr_ requires setting this at least once. 

    RecursiveLock_Init(&g_cs_CurrentWmiv2Operation);

    if(Sem_Init_Injected(&g_h_ConfigurationStoppedEvent, SEM_USER_ACCESS_DEFAULT, 1, NitsHere()) == -1)
    {
        return GetCimWin32Error(MI_RESULT_FAILED, cimErrorDetails, ID_LCMHELPER_INIT_FILECRITSEC_FAILED);
    }

    return MI_RESULT_OK;
}

MI_Result UnInitCAHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if (cimErrorDetails == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *cimErrorDetails = NULL;    // Explicitly set *cimErrorDetails to NULL as _Outptr_ requires setting this at least once. 

    RecursiveLock_Release(&g_cs_CurrentWmiv2Operation);
    Sem_Destroy(&g_h_ConfigurationStoppedEvent);
    
    return MI_RESULT_OK;
}

void MI_CALL FreeExecutionOrderContainer(_Inout_ ExecutionOrderContainer *container)
{
    //Free default execution list
    if( container->ExecutionList)
    {
        DSC_free(container->ExecutionList);
    }
    container->ExecutionList = NULL;
    container->executionListSize = 0;
    container->executionListCapacity = 0;
}


/* Dependency resolver will create independent trees. Individual tree is 
    sorted and the sort order define the sequence in which the instances need to be executed.
    Exception is resources which do not define any dependency. They all become part of a 
    default tree and put in the order they were defined in original document.*/
    
MI_Result MI_CALL ResolveDependency( _In_ MI_InstanceA *instanceA,
                                  _Inout_ ExecutionOrderContainer *container,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 xCount = 0;
    MI_Sint32 *visitedNodes;
    MI_Sint32 *resolvedNodes;
    DSC_EventWriteMessageResolvingDependency();
    if( container == NULL || instanceA == NULL || instanceA->size == 0 || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_NULLPARAM);
    }

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.     

    /*Algo to find cycles and create trees.
          Create two lists. First one contain information about the nodes that have been visited.
          Second one contain information about the nodes that have been resolved.*/
    visitedNodes = (MI_Sint32*) DSC_malloc(sizeof(MI_Sint32) * instanceA->size, NitsHere());
    if( visitedNodes == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }

    resolvedNodes = (MI_Sint32*) DSC_malloc(sizeof(MI_Sint32) * instanceA->size, NitsHere());
    if( resolvedNodes == NULL)
    {
        DSC_free(visitedNodes);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }    

    container->ExecutionList = (ResourceExecutionDetails*) DSC_malloc(sizeof(ResourceExecutionDetails) * instanceA->size, NitsHere());
    if( container->ExecutionList == NULL )
    {
        DSC_free(resolvedNodes);
        DSC_free(visitedNodes);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);        
    }
    container->executionListCapacity = instanceA->size;

    
    memset(resolvedNodes, -1 , sizeof(MI_Sint32) * instanceA->size);  
    memset( container->ExecutionList, -1, sizeof(ResourceExecutionDetails) * instanceA->size);

    for( xCount = 0 ; xCount < instanceA->size; xCount++)
    {
        /*Check if node is already resolved. If yes return success.*/
        if( resolvedNodes[xCount] == NODE_RESOLVED )
        {
            continue;
        }

        memset(visitedNodes, -1 , sizeof(MI_Sint32) * instanceA->size);
        r = ResolveDependencyInternal(xCount, instanceA, container, visitedNodes, resolvedNodes, extendedError);
        if( r != MI_RESULT_OK)
        {
            DSC_free(visitedNodes);
            DSC_free(resolvedNodes);
            FreeExecutionOrderContainer(container);
            return r;
        }
    }
    // All nodes should be visited here by now, if now we have some undefined error.
    for( xCount = 0 ; xCount < instanceA->size; xCount++ )
    {
        if( resolvedNodes[xCount] != NODE_RESOLVED )
        {
            GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CAINFRA_DEPENDCYRESOLVER_OUTOFBOUNDS);
        }
    }

    DSC_free(visitedNodes);
    DSC_free(resolvedNodes);    
    return r;
}

/*This method assumes that all the parameters are valid and within range as appropriate. Like index is < instanceA->size etc.
    Also memory for container is freed by the caller.*/
MI_Result ResolveDependencyInternal( _In_ MI_Uint32 index,
                                   _In_ MI_InstanceA *instanceA, 
                                  _Inout_ ExecutionOrderContainer *container,
                                  _Inout_count_(instanceA->size) MI_Sint32 *visitedNodes,
                                  _Inout_count_(instanceA->size) MI_Sint32 *resolvedNodes,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Instance *currentInstance = NULL;
    MI_Uint32 xCount = 0;
    MI_Uint32 dwIndex = 0;
    MI_Value value;
    const MI_Char *className = NULL;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    if( index >= instanceA->size || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_OUTOFBOUNDS);
    }    
    
    // find dependencies
    currentInstance = instanceA->data[index];
    r = MI_Instance_GetClassName(currentInstance, &className);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_VALIDATE_PROVREGINS_CLASSNAME);
    }    
    visitedNodes[index] = NODE_VISITED;
    
    r = MI_Instance_GetElement(currentInstance, OMI_BaseResource_DependsOn, &value, NULL, NULL, NULL);
    if( r == MI_RESULT_NOT_FOUND || r == MI_RESULT_NO_SUCH_PROPERTY || value.string == NULL)
    {
        // no dependency specified add it to the list.
        resolvedNodes[index] = NODE_RESOLVED;
        r = AddToList(container, index, extendedError);
        return r;
    }
    else
    {
        for( xCount = 0 ; xCount < value.stringa.size; xCount++)
        {
            r = GetInstanceIndex(instanceA, value.stringa.data[xCount], index, &dwIndex, extendedError);
            if( r != MI_RESULT_OK)
            {
                return r;
            }
            if( dwIndex >= instanceA->size || NitsShouldFault(NitsHere(), NitsAutomatic))
            {
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_OUTOFBOUNDS);
            }            
            /*Check if node is already resolved. If yes return success.*/
            if( resolvedNodes[dwIndex] == NODE_RESOLVED)
            {
                continue;
            }

            /*If the node is visited but not resolved there is a cycle in the graph*/
            if( visitedNodes[dwIndex] == NODE_VISITED || NitsShouldFault(NitsHere(), NitsAutomatic))
            {
                const MI_Char* resourceID;
                const MI_Char* sourceInfo;
                resourceID = GetResourceId(instanceA->data[dwIndex]);
                sourceInfo = GetSourceInfo(instanceA->data[dwIndex]);
                if(sourceInfo == NULL)
                {
                    return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_CAINFRA_DEPENDCY_CYCLE, resourceID);
                }
                else
                {
                    return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_CAINFRA_DEPENDCY_CYCLE2, resourceID, sourceInfo);
                }
            }     
            
            r = ResolveDependencyInternal(dwIndex, instanceA, container, visitedNodes, resolvedNodes, extendedError);
            if( r != MI_RESULT_OK)
            {
                return r;
            }             
        }
        //Add it to resolved List.
        resolvedNodes[index] = NODE_RESOLVED;
        r = AddToList(container, index, extendedError); 
        if( r != MI_RESULT_OK)
        {
            return r;
        }        
       
    }
    return MI_RESULT_OK;
}

MI_Result GetInstanceIndex(_In_ MI_InstanceA *instanceA, 
                              _In_z_ MI_Char *resourceId, 
                              int currentInstanceIndex,
                              _Out_ MI_Uint32 *resourceIndex, 
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    const MI_Char* currentResourceID;
    const MI_Char* currentSourceInfo;
    
    *resourceIndex = 0;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    for( xCount = 0 ; xCount < instanceA->size; xCount++)
    {
        r = DSC_MI_Instance_GetElement(instanceA->data[xCount], OMI_BaseResource_ResourceId, &value, NULL, NULL, NULL);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError, ID_CAINFRA_INSTANCE_RESOURCEID);
        }
        if( Tcscasecmp(value.string, resourceId) == 0 )
        {
            *resourceIndex = xCount;
            return MI_RESULT_OK;
        }
    }
    // If here resource was not found. Throw an error.
    currentResourceID = GetResourceId(instanceA->data[currentInstanceIndex]);
    currentSourceInfo = GetSourceInfo(instanceA->data[currentInstanceIndex]);
    if(currentSourceInfo == NULL)
    {
        return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_CAINFRA_INSTANCE_RESOURCEID_NOTFOUND, resourceId, currentResourceID);
    }
    else
    {
        return GetCimMIError3Params(MI_RESULT_FAILED, extendedError, ID_CAINFRA_INSTANCE_RESOURCEID_NOTFOUND2, resourceId, currentResourceID, currentSourceInfo);
    }
}

MI_Result DependentResourceFailed( _In_ MI_Uint32 index,
                            _In_ ExecutionOrderContainer *container,
                            _In_ MI_InstanceA *instanceA,
                            _Out_ MI_Boolean *bDependentFailed,
                            _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    MI_Uint32 xCount = 0;
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;	// Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.	
    *bDependentFailed = MI_FALSE;
    if( index >= instanceA->size || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_OUTOFBOUNDS);
    }     
    /* Step1: get the resources on which resource with location index depends on.*/

    r = MI_Instance_GetElement(instanceA->data[index], OMI_BaseResource_DependsOn, &value, NULL, NULL, NULL);
    if( r == MI_RESULT_NOT_FOUND || r == MI_RESULT_NO_SUCH_PROPERTY || value.string == NULL)
    {
        // no dependencies we are good.
        return MI_RESULT_OK;
    }
    else if ( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError, ID_MODMAN_GETELEMENT_FAILED );
    }

    /* Step2: For each of dependent resources they should have already been processed. */
    for ( xCount = 0 ; xCount < value.stringa.size && *bDependentFailed == MI_FALSE; xCount++)
    {
        MI_Uint32 resourceIndex = 0;
        r = GetInstanceIndex(instanceA, value.stringa.data[xCount], 
            index, &resourceIndex, extendedError);

        if( r != MI_RESULT_OK )
        {
            return r;
        }
        r = DependentResourceProcessed(resourceIndex, container, bDependentFailed, extendedError);
        if( r != MI_RESULT_OK )
        {
            return r;
        }
    }
    return MI_RESULT_OK;
}

MI_Result DependentResourceProcessed (_In_ MI_Uint32 resourceIndex,
                                    _In_ ExecutionOrderContainer *container,
                                    _Inout_ MI_Boolean *bDependentFailed,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;

    for( xCount = 0 ; xCount < container->executionListSize ; xCount++)
    {
        if( container->ExecutionList[xCount].resourceIndex == resourceIndex )
        {
            // status should be processed.
            if( container->ExecutionList[xCount].resourceStatus == ResourceNotProcessed )
            {
                // We have some internal error.
                return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_OUTOFBOUNDS);
            }
            else if( container->ExecutionList[xCount].resourceStatus == ResourceProcessedAndFailed )
            {
                *bDependentFailed = MI_TRUE;
            }
            return MI_RESULT_OK;
        }
    }
    // Here is impossible, something is messed up which we don't understant.
    return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_OUTOFBOUNDS);
}


/*Caller will clean up the memory*/
MI_Result AddToList(_Inout_ ExecutionOrderContainer *container, 
                            _In_ MI_Uint32 objectIndex,
                            _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;	// Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.	
        
    for( xCount = 0; xCount < container->executionListSize; xCount++)
    {
        if( objectIndex == container->ExecutionList[xCount].resourceIndex)
        {
            // Resource is already in the list, we are good.
            return MI_RESULT_OK;
        }
    }
    if( container->executionListSize == container->executionListCapacity )
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);            
    }    
    // Add it to the list at the end.
    container->ExecutionList[ container->executionListSize ].resourceIndex = objectIndex;
    container->ExecutionList[ container->executionListSize ].resourceStatus = ResourceNotProcessed;
    container->executionListSize++;
    
    return MI_RESULT_OK;
}


MI_Result SetResourcesInOrder(_In_ LCMProviderContext *lcmContext,  
                                  _In_ ModuleManager *moduleManager,
                                  _In_ MI_InstanceA * instanceA,
                                  _In_ MI_Session *miSession,
                                  _In_ ExecutionOrderContainer *executionOrder,
                                  _In_ MI_Uint32 flags,
                                  _In_ MI_Instance *documentIns,                                  
                                  _Inout_ MI_Uint32 *resultStatus,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    MI_Uint32 index = 0;
    MI_Instance *filteredInstance = NULL;
    MI_Instance *regInstance = NULL;
    ModuleLoaderObject *moduleLoader = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Result finalr = MI_RESULT_OK;
    ProviderCallbackContext providerContext = {0};
    MI_Char *certificateid = NULL;
    MI_Boolean bEncryptionEnabled = MI_FALSE;
    MI_Boolean canceled;
    DSC_EventWriteMessageSettingResourcesOrder(executionOrder->executionListSize);
    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   
 
    providerContext.lcmProviderContext = lcmContext;

    r = GetDocumentEncryptionSetting(documentIns, &bEncryptionEnabled, &certificateid, extendedError);
    if( r != MI_RESULT_OK )
    {
        return r;
    }

    /*Assuming the dependencies is implicit (the order in which instances are specified in the list). */
    /*Get the instance compatible with the provider.*/
    for (xCount = 0 ; xCount < executionOrder->executionListSize ; xCount++)
    {
        MI_Boolean bDependentFailed = MI_FALSE;
        if (g_CancelConfiguration == TRUE)
        {
            if(certificateid != NULL)
            {
                DSC_free(certificateid);
                certificateid = NULL;
            }
            DSC_EventWriteConfigurationCancelledInTheMiddle(executionOrder->executionListSize, executionOrder->executionListSize - xCount);
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CANCEL_CONFIGURATION);
        }
        
        index = executionOrder->ExecutionList[xCount].resourceIndex;
        r = DependentResourceFailed(index, executionOrder, instanceA, &bDependentFailed, extendedError);
        if( r != MI_RESULT_OK )
        {
            return r;
        }
        if( bDependentFailed == MI_TRUE )
        {
            // mark it as failed and continue;
            executionOrder->ExecutionList[xCount].resourceStatus = ResourceProcessedAndFailed;
            continue;
            
        }
        providerContext.resourceId = GetResourceId(instanceA->data[index]);
        
        //metaconfig doesn't have resourceID
        if(providerContext.resourceId == NULL &&
            Tcscasecmp(instanceA->data[index]->classDecl->name, METACONFIG_CLASSNAME) == 0)
        {
            providerContext.resourceId = METACONFIG_CLASSNAME;
        }

        if ( flags & LCM_EXECUTE_TESTONLY )
        {
            LogCAProgress(lcmContext,MI_T("Test"),MI_T("Testing Configuration"), xCount, instanceA->size);
        }
        else
        {
            LogCAProgress(lcmContext,MI_T("Set"),MI_T("Applying Configuration"), xCount, instanceA->size);
        }
        SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_RESOURCE,lcmContext);
        LogCAMessage(lcmContext, ID_OUTPUT_EMPTYSTRING, providerContext.resourceId);

        if (index >= instanceA->size || NitsShouldFault(NitsHere(), NitsAutomatic))
        {
            if(certificateid != NULL)
            {
                DSC_free(certificateid);
                certificateid = NULL;
            }

            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CAINFRA_DEPENDCYRESOLVER_OUTOFBOUNDS);
        }

        DSC_EventWriteMessageRegisteringModule(instanceA->data[index]->classDecl->name);
            
        /* Get Registration Instance to find registration information.*/
        r = moduleManager->ft->GetRegistrationInstance(moduleManager, instanceA->data[index]->classDecl->name, (const MI_Instance **)&regInstance, extendedError);
        if (r != MI_RESULT_OK)
        {
            if(certificateid != NULL)
            {
                DSC_free(certificateid);
                certificateid = NULL;
            }
            return r;
        }        

        if (bEncryptionEnabled == MI_TRUE && certificateid != NULL)
        {
            /*Decrypt passwords if necessary */
            r = DecryptPasswords(certificateid, instanceA->data[index], extendedError);
            if (r != MI_RESULT_OK)
            {                        
                if(certificateid != NULL)
                {
                    DSC_free(certificateid);
                    certificateid = NULL;
                }
                MI_Instance_Delete(filteredInstance);
                return r;
            }
        }

        /*Get provider compatible instance*/
        r = moduleManager->ft->GetProviderCompatibleInstance(moduleManager, instanceA->data[index], &filteredInstance, extendedError);
        if (r != MI_RESULT_OK)
        {         
            if(certificateid != NULL)
            {
                DSC_free(certificateid);
                certificateid = NULL;
            }
            return r;
        }

        /* Move the resource to desired state.*/
        canceled = MI_FALSE;
        r = MoveToDesiredState(&providerContext, moduleLoader->application, miSession, filteredInstance, regInstance, flags, resultStatus, &canceled, extendedError);
        MI_Instance_Delete(filteredInstance);
        filteredInstance = NULL;
        
        if (r != MI_RESULT_OK)
        {        
            // Failure case, update the resource status
            Intlstr intlstr = Intlstr_Null;
            executionOrder->ExecutionList[xCount].resourceStatus = ResourceProcessedAndFailed;
            if (canceled)
            {
                if(certificateid != NULL)
                {
                    DSC_free(certificateid);
                    certificateid = NULL;
                }

                DSC_EventWriteConfigurationCancelledInTheMiddle(executionOrder->executionListSize, executionOrder->executionListSize - xCount);
                return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CANCEL_CONFIGURATION);
            }            
            if( flags & LCM_EXECUTE_TESTONLY)
            {
                if(certificateid != NULL)
                {
                    DSC_free(certificateid);
                    certificateid = NULL;
                }

                return r;
            }                           

            GetResourceString(ID_LCMHELPER_SENDCONFIGAPPLY_ERROR, &intlstr);

                DSC_EventWriteLCMSendConfigurationError(CA_ACTIVITY_NAME, 
                    r, 
                    intlstr.str, 
                    providerContext.resourceId, 
                    GetSourceInfo(instanceA->data[index]), 
                    (MI_Char*)GetErrorDetail(*extendedError));

               if( intlstr.str)
                   Intlstr_Free(intlstr);


            //send the error to WriteError stream.
            LCM_WriteError( lcmContext, *extendedError);

            // we need to continue moving other resources to their desired state.
            finalr = r;
            if(extendedError)
            {
                if(certificateid != NULL)
                {
                    DSC_free(certificateid);
                    certificateid = NULL;
                }

                MI_Instance_Delete(*extendedError);
                *extendedError = NULL;
            }
            continue;
        }
        // Success Case
        executionOrder->ExecutionList[xCount].resourceStatus = ResourceProcessedAndSucceeded;
        r = finalr;
        SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_RESOURCE,lcmContext);
        LogCAMessage(lcmContext, ID_OUTPUT_EMPTYSTRING, providerContext.resourceId);

        // if resultStatus is 1 then they are in their current state otherwise not.
        if (flags & LCM_EXECUTE_TESTONLY)
        {
            if (*resultStatus == MI_FALSE)
            {
                if(certificateid != NULL)
                {
                    DSC_free(certificateid);
                    certificateid = NULL;
                }

                return r;
            }
        }
        else if (DSC_RESTART_SYSTEM_FLAG & *resultStatus && r == MI_RESULT_OK)
        {
            if(certificateid != NULL)
            {
                DSC_free(certificateid);
                certificateid = NULL;
            }

            return MI_RESULT_OK;
        }
    }

    if(certificateid != NULL)
    {
        DSC_free(certificateid);
        certificateid = NULL;
    }

    return finalr;
}

/*WriteMessage callbacks from providers*/

void MI_CALL DoWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
             MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *) callbackContext;
    LCM_WriteMessageFromProvider(providerContext->lcmProviderContext, providerContext->resourceId, channel, message);
}

void MI_CALL DoWriteProgress(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
    _In_z_   const MI_Char *activity,
    _In_z_   const MI_Char *currentOperation,
    _In_z_   const MI_Char *statusDescription,
             MI_Uint32 percentageComplete,
             MI_Uint32 secondsRemaining)
{
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *) callbackContext;
    LCM_WriteProgress(providerContext->lcmProviderContext, activity, currentOperation,
                      statusDescription, percentageComplete, secondsRemaining);
}

void MI_CALL DoPromptUser(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
    _In_z_   const MI_Char *message,
             MI_PromptType promptType,
    _In_     MI_Result (MI_CALL * promptUserResult)(_In_ MI_Operation *operation, 
                                                      MI_OperationCallback_ResponseType response))
{
    MI_Boolean bPromptUserResultStatus;
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *) callbackContext;
    LCM_PromptUserFromProvider(providerContext->lcmProviderContext, providerContext->resourceId, message, promptType, &bPromptUserResultStatus);    
    if(promptUserResult)
    {
        promptUserResult(operation, bPromptUserResultStatus);
    }
}



/*Get the current configuration for the desired state objects*/
MI_Result MI_CALL GetConfiguration( _In_ LCMProviderContext *lcmContext,   
                                    _In_ MI_Uint32 flags,
                                    _In_ MI_InstanceA *instanceA,
                                    _In_ ModuleManager *moduleManager,
                                    _In_ MI_Instance *documentIns,
                                    _Out_ MI_InstanceA *outInstances,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Instance *filteredInstance = NULL;
    MI_Instance *regInstance = NULL;
    ModuleLoaderObject *moduleLoader = NULL;
    MI_Instance *getInstanceResult = NULL;
    MI_Session miSession = MI_SESSION_NULL;
    ProviderCallbackContext providerContext = {0};

    MI_Char *certificateid = NULL;
    MI_Boolean bEncryptionEnabled = MI_FALSE;
    MI_Uint32 xCount = 0;
    MI_Uint32 index = 0;
   
    if( outInstances == NULL  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_GET_NULLPARAM);
    }

    memset(outInstances, 0, sizeof(MI_InstanceA));
    if( instanceA == 0 || moduleManager == 0 || instanceA->size == 0  || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_NULLPARAM);
    }
    
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.      

    providerContext.lcmProviderContext = lcmContext;

    r = GetDocumentEncryptionSetting(documentIns, &bEncryptionEnabled, &certificateid, extendedError);
    if( r != MI_RESULT_OK )
    {
        return r;
    }

    outInstances->data = (MI_Instance **)DSC_malloc( instanceA->size * sizeof(MI_Instance*), NitsHere());
    outInstances->size = 0;    

    if( outInstances->data == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);        
                    
    }

    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;

    /*Create MI session*/
    r = DSC_MI_Application_NewSession(moduleLoader->application, NULL, NULL, NULL, NULL, NULL, &miSession);
    if( r != MI_RESULT_OK)
    {
        CleanUpGetCache(outInstances);
        return GetCimMIError(r, extendedError,ID_CAINFRA_NEWSESSION_FAILED);
    }


    /*Assuming the dependencies is implicit (the order in which instances are specified in instance document). */
    /*Get the instance compatible with the provider.*/
    for (xCount = 0 ; xCount < instanceA->size ; xCount++)
    {
        /* Get Registration Instance to find registration information.*/
        r = moduleManager->ft->GetRegistrationInstance(moduleManager, instanceA->data[xCount]->classDecl->name, (const MI_Instance **)&regInstance, extendedError);
        if( r != MI_RESULT_OK)
        {
            CleanUpGetCache(outInstances);
            MI_Session_Close(&miSession, NULL, NULL);
            return r;
        }        

        if (bEncryptionEnabled == MI_TRUE && certificateid != NULL)
        {
            /*Decrypt passwords if necessary */
            r = DecryptPasswords(certificateid, instanceA->data[index], extendedError);
            if (r != MI_RESULT_OK)
            {                        
                if(certificateid != NULL)
                {
                    DSC_free(certificateid);
                    certificateid = NULL;
                }
                MI_Instance_Delete(filteredInstance);
                return r;
            }
        }

        /*Get provider compatible instance*/
        r = moduleManager->ft->GetProviderCompatibleInstance(moduleManager, instanceA->data[xCount], &filteredInstance, extendedError);
        if( r != MI_RESULT_OK)
        {
            CleanUpGetCache(outInstances);           
            MI_Session_Close(&miSession, NULL, NULL);            
            return r;
        }
        providerContext.resourceId = GetResourceId(instanceA->data[xCount]);    
        
        /* Get the resource.*/
        r = GetCurrentState(&providerContext, moduleLoader->application, &miSession, filteredInstance, regInstance, &getInstanceResult, extendedError);
        MI_Instance_Delete(filteredInstance);
        filteredInstance = NULL;
        
        if( r != MI_RESULT_OK)
        {
            Intlstr intlstr = Intlstr_Null;
            GetResourceString(ID_LCMHELPER_SENDCONFIGAPPLY_ERROR, &intlstr);

            DSC_EventWriteLCMSendConfigurationError(CA_ACTIVITY_NAME, 
                r, 
                (MI_Char*)intlstr.str, 
                providerContext.resourceId, 
                GetSourceInfo(instanceA->data[xCount]), 
                (MI_Char*)GetErrorDetail(*extendedError));

            if( intlstr.str)
                Intlstr_Free(intlstr);   

            CleanUpGetCache(outInstances);           
            MI_Session_Close(&miSession, NULL, NULL);            
            return r;
        }
        outInstances->data[xCount] = getInstanceResult;
        outInstances->size += 1;
    }

    MI_Session_Close(&miSession, NULL, NULL);    
    return r;
}

/*Apply the configuration for instances whose current state is different than desired state.*/
MI_Result MI_CALL SendConfigurationApply( _In_ LCMProviderContext *lcmContext,  
                                  _In_ MI_Uint32 flags,
                                  _In_ MI_InstanceA *instanceA,
                                  _In_ ModuleManager *moduleManager,
                                  _In_ MI_Instance *documentIns,
                                  _Inout_ MI_Uint32 *resultStatus,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    ModuleLoaderObject *moduleLoader = NULL;
    MI_Session miSession = MI_SESSION_NULL;
    ExecutionOrderContainer executionContainer = {0};
    DSC_EventWriteMessageParsingConfiguration();
    DSC_EventWriteEngineMethodParameters(__WFUNCTION__,documentIns->classDecl->name,_STRINGEMPTY_,flags,lcmContext->executionMode,documentIns->nameSpace);
    
    if( instanceA == 0 || moduleManager == 0 || instanceA->size == 0 || NitsShouldFault(NitsHere(), NitsAutomatic) )
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_DEPENDCY_NULLPARAM);
    }

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    moduleLoader = (ModuleLoaderObject*) moduleManager->reserved2;

    r = ValidateIfDuplicatedInstances(instanceA, extendedError);
    if( r != MI_RESULT_OK)
    {
        FreeExecutionOrderContainer(&executionContainer);
        return r;
    }    

    /*Resolving dependencies*/
    r = ResolveDependency(instanceA, &executionContainer, extendedError);
    if( r != MI_RESULT_OK)
    {
        FreeExecutionOrderContainer(&executionContainer);
        return r;
    }    

    /*Create MI session*/
    r = DSC_MI_Application_NewSession(moduleLoader->application, NULL, NULL, NULL, NULL, NULL, &miSession);
    if( r != MI_RESULT_OK)
    {
        FreeExecutionOrderContainer(&executionContainer);      
        return GetCimMIError(r, extendedError,ID_CAINFRA_NEWSESSION_FAILED);
    }


    /*execute the list in sequence.*/
    r = SetResourcesInOrder(lcmContext, moduleManager, instanceA, &miSession, & executionContainer, 
                            flags, documentIns, resultStatus, extendedError);

    if( r != MI_RESULT_OK )
    {
        FreeExecutionOrderContainer(&executionContainer);            
        MI_Session_Close(&miSession, NULL, NULL);            
        return r;          
    }

    FreeExecutionOrderContainer(&executionContainer);    
    MI_Session_Close(&miSession, NULL, NULL);   
    return r;
}


MI_Result GetCurrentState(_In_ ProviderCallbackContext *provContext,  
                           _In_ MI_Application *miApp,
                           _In_ MI_Session *miSession,
                           _In_ MI_Instance *instance,
                           _In_ const MI_Instance *regInstance,
                           _Outptr_result_maybenull_ MI_Instance **outputInstance,
                           _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    *outputInstance = NULL;

    if( Tcscasecmp(regInstance->classDecl->name, BASE_REGISTRATION_WMIV2PROVIDER) == 0 ||
        Tcscasecmp(MSFT_LOGRESOURCENAME, instance->classDecl->name) == 0)
    {
        return Get_WMIv2Provider(provContext, miApp, miSession, instance, regInstance, outputInstance, extendedError);
    }    
#if defined(_MSC_VER)
#ifndef BUILD_FOR_CORESYSTEM
    else if( Tcscasecmp(regInstance->classDecl->name, BASE_REGISTRATION_PSPROVIDER) == 0 )
    {
        return Get_PSProvider(provContext, miApp, instance, regInstance, outputInstance, extendedError);        
    }
#endif
#endif
    else
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_UNKNOWN_REGISTRATION);
    }    
    
}

MI_Result MoveToDesiredState(_In_ ProviderCallbackContext *provContext,  
                             _In_ MI_Application *miApp,
                             _In_ MI_Session *miSession,
                             _In_ MI_Instance *instance,
                             _In_ const MI_Instance *regInstance,
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
                             _Inout_ MI_Boolean *canceled,
                             _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    DSC_EventWriteMessageMoveResourceToDesired(provContext->resourceId,instance->classDecl->name);
       
    if( Tcscasecmp(instance->classDecl->name, METACONFIG_CLASSNAME) == 0 || // put special cases to wmiv2 code
        Tcscasecmp(regInstance->classDecl->name, BASE_REGISTRATION_WMIV2PROVIDER) == 0 ||
        Tcscasecmp(MSFT_LOGRESOURCENAME, instance->classDecl->name) == 0)
    {
        if(instance->classDecl!=NULL)
        {
            SQMLogResourceCountData(instance->classDecl->name,1);
        }

        return Exec_WMIv2Provider(provContext, miApp, miSession, instance, regInstance, flags, resultStatus, canceled, extendedError);
    }
    
#if defined(_MSC_VER)
#ifndef BUILD_FOR_CORESYSTEM
    else if(Tcscasecmp(regInstance->classDecl->name, BASE_REGISTRATION_PSPROVIDER) == 0 )
    {
        if(instance->classDecl!=NULL)
        {
            SQMLogResourceCountData(instance->classDecl->name,1);
        }
        return Exec_PSProvider(provContext, miApp, instance, regInstance, flags, resultStatus, canceled, extendedError);        
    }
#endif
#endif   
    else
    {
        return GetCimMIError(MI_RESULT_INVALID_PARAMETER, extendedError,ID_CAINFRA_UNKNOWN_REGISTRATION);
    }
}

MI_Result Exec_WMIv2Provider(_In_ ProviderCallbackContext *provContext,   
                             _In_ MI_Application *miApp,
                             _In_ MI_Session *miSession,
                             _In_ MI_Instance *instance,
                             _In_ const MI_Instance *regInstance,
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
                             _Inout_ MI_Boolean* canceled,
                             _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;  
    MI_Result result = MI_RESULT_OK;
    const MI_Char *provNamespace = NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *params = NULL;
    MI_Value value;
    MI_Value valueOperationOptions;
    MI_Boolean bTestResult = MI_TRUE;
    MI_Uint64 outProviderContext = 0;
    MI_Uint32 returnValue = 0;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_Real64 duration;
    MI_OperationOptions sessionOptions;
    const MI_Char * instanceNamespace;    
   
    ptrdiff_t start,finish;

    //we don't have reginstance for meta configuration
    if (Tcscasecmp(instance->classDecl->name, METACONFIG_CLASSNAME) == 0)
    {
        instanceNamespace = MI_T("");
    }
    else
    {
        instanceNamespace = regInstance->nameSpace;
    }    
    //Debug Log 
    DSC_EventWriteEngineMethodParameters(__WFUNCTION__,
                                        instance->classDecl->name,
                                        provContext->resourceId,
                                        flags,
                                        provContext->lcmProviderContext->executionMode,
                                        instanceNamespace);
    DSC_EventWriteMessageExecutingWMI(instance->classDecl->name,provContext->resourceId);
    
    
    callbacks.writeMessage = DoWriteMessage;
    /* Sign up for progress only if we are in online mode*/
    if ((LCM_EXECUTIONMODE_ONLINE & provContext->lcmProviderContext->executionMode) == LCM_EXECUTIONMODE_ONLINE)
    {
        callbacks.writeProgress = DoWriteProgress;
    }

    /* Sign up for promptuser only if we are asked to do so.*/
    if ((LCM_SETFLAGS_ENABLEWHATIF & flags) == LCM_SETFLAGS_ENABLEWHATIF)
    {
        callbacks.promptUser = DoPromptUser;
    }

    callbacks.callbackContext = (void *)(provContext);    

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    *canceled = MI_FALSE;
    if (g_CancelConfiguration)
    {
        *canceled = MI_TRUE;
        return MI_RESULT_FAILED;
    
    }
    // If the input MI_Instance is a MSFT_LogResource then directly log the message using LCM log API's
    if (Tcscasecmp(instance->classDecl->name, LOGRESOURCE_CLASSNAME) == 0)
    {
        MI_Value value;
        const MI_Char *message = NULL;
        //Start timer for Set
        start=CPU_GetTimeStamp();
        
        //Starting Test
        SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_TEST,provContext->lcmProviderContext);
        LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
        
        r = MI_Instance_GetElement(instance, LOGRESOURCE_MESSAGEPROPERTYNAME, &value, NULL, NULL, NULL);
        if (r != MI_RESULT_OK)
        {
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_LOGRESOURCE_FAILED);
        }

        message = value.string;
        //Stop the timer for test
        finish=CPU_GetTimeStamp();
        duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
        SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_TEST,provContext->lcmProviderContext);
        LogCAMessageTime(provContext->lcmProviderContext, ID_CA_TEST_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);

        if (!(flags & LCM_EXECUTE_TESTONLY))
        {
            //Start timer for Set
            start=CPU_GetTimeStamp();   
            SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
            LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
        
            LCM_WriteMessageFromProvider(provContext->lcmProviderContext, provContext->resourceId, MI_WRITEMESSAGE_CHANNEL_VERBOSE, message);
            //Stop the timer for set
            finish=CPU_GetTimeStamp();
            duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
            SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
            LogCAMessageTime(provContext->lcmProviderContext, ID_CA_SET_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);
        }
    }
    // If the input is a meta configuration then invoke LCM's API directly
    else if (Tcscasecmp(instance->classDecl->name, METACONFIG_CLASSNAME) == 0 && !( flags & LCM_EXECUTE_TESTONLY ))
    {
        //Start timer for Set
        start=CPU_GetTimeStamp();
        //meta configuration is always explicitly get invoked so no need to test before set.
        SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
        LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
        r = SetMetaConfig(instance, extendedError);
         //Stop the timer for set
        finish=CPU_GetTimeStamp();
        duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
        SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
        LogCAMessageTime(provContext->lcmProviderContext, ID_CA_SET_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);

        if(r == MI_RESULT_OK)
        {
            result = RegisterStandardTasks(extendedError);
        }
    }  
    else
    {

        /*Get target namespace*/
        r = DSC_MI_Instance_GetElement(regInstance, MSFT_CimConfigurationProviderRegistration_Namespace, &value, NULL, NULL, NULL);
        if (r != MI_RESULT_OK)
        {
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NAMESPACE_FAILED);
        }

        provNamespace = value.string;

        /*Set input parameters*/
        r = DSC_MI_Application_NewInstance(miApp, MI_T("__Parameters"), NULL, &params);
        if (r != MI_RESULT_OK)
        {
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NEWAPPLICATIONINSTANCE_FAILED);
        }

        value.instance = instance;
        r = DSC_MI_Instance_AddElement(params, OMI_BaseResource_Method_InputResource, &value, MI_INSTANCE, 0 );
        if (r != MI_RESULT_OK)
        {
            MI_Instance_Delete(params);
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_ADDELEM_FAILED);
        }
        r = MI_Application_NewOperationOptions(miApp, MI_FALSE, &sessionOptions);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NEWOPERATIONOPTIONS_FAILED);
        }
        valueOperationOptions.string=g_ConfigurationDetails.jobGuidString;
        r =MI_OperationOptions_SetCustomOption(&sessionOptions,DSC_JOBIDSTRING,MI_STRING,&valueOperationOptions,MI_FALSE);
        if( r != MI_RESULT_OK)
        {
            MI_OperationOptions_Delete(&sessionOptions);
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_SETCUSTOMOPTION_FAILED);
        }
        if(r!=MI_RESULT_OK)
        {
            //INCHTODO: Say setcustomoptionfailed
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_ADDELEM_FAILED);
        }
        /* Perform Test*/
        //Start timer for test
        start=CPU_GetTimeStamp();
        DSC_EventWriteMessageInvokingSession(provNamespace,instance->classDecl->name,OMI_BaseResource_TestMethodName);
        SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_TEST,provContext->lcmProviderContext);
        LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);

        RecursiveLock_Acquire(&g_cs_CurrentWmiv2Operation);
        MI_Session_Invoke(miSession, 0, &sessionOptions, provNamespace, 
                             instance->classDecl->name, OMI_BaseResource_TestMethodName,
                             NULL, params, &callbacks,&operation);  
        g_CurrentWmiv2Operation = &operation;
        RecursiveLock_Release(&g_cs_CurrentWmiv2Operation);

        r = GetTestMethodResult(&operation, &bTestResult, &outProviderContext, extendedError);

        RecursiveLock_Acquire(&g_cs_CurrentWmiv2Operation);
        g_CurrentWmiv2Operation = NULL;
        MI_Operation_Close(&operation);
        RecursiveLock_Release(&g_cs_CurrentWmiv2Operation);
        if (r != MI_RESULT_OK)
        {
            MI_Instance_Delete(params);            
            MI_OperationOptions_Delete(&sessionOptions);
            return r;
        }

        //Stop the timer for test
        finish=CPU_GetTimeStamp();
        duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
        SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_TEST,provContext->lcmProviderContext);
        LogCAMessageTime(provContext->lcmProviderContext, ID_CA_TEST_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);
           
        /* Skip rest of the operation if we were asked just to test.*/
        if (flags & LCM_EXECUTE_TESTONLY)
        {
            if(bTestResult == MI_TRUE)
                *resultStatus = 1;
            else
                *resultStatus = 0;
            
            MI_Instance_Delete(params);
            MI_OperationOptions_Delete(&sessionOptions);
            return MI_RESULT_OK;
        }

        /* Perform Set if value returned is FALSE*/
        if( bTestResult == MI_TRUE)
        {
            SetMessageInContext(ID_OUTPUT_OPERATION_SKIP,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
            LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
            MI_Instance_Delete(params);        
            MI_OperationOptions_Delete(&sessionOptions);
            return MI_RESULT_OK;
        }

        if (g_CancelConfiguration)
        {
            *canceled = MI_TRUE;
            MI_Instance_Delete(params);
            MI_OperationOptions_Delete(&sessionOptions);
            return MI_RESULT_FAILED;
        }

        /* Add outProviderContext to the params*/
        value.uint64 = outProviderContext;
        r = DSC_MI_Instance_AddElement(params, OMI_BaseResource_Method_ProviderContext, &value, MI_UINT64, 0 );
        if (r != MI_RESULT_OK)
        {
            MI_Instance_Delete(params);        
            MI_OperationOptions_Delete(&sessionOptions);
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_ADDELEM_FAILED);
        }    

        /* Perform Set*/
        //Start timer for set
        start=CPU_GetTimeStamp();
        SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
        LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
        DSC_EventWriteMessageInvokingSession(provNamespace,instance->classDecl->name,OMI_BaseResource_SetMethodName);
        
        RecursiveLock_Acquire(&g_cs_CurrentWmiv2Operation);
        memset(&operation, 0, sizeof(MI_Operation));
        MI_Session_Invoke(miSession, 0, &sessionOptions, provNamespace, 
                             instance->classDecl->name, OMI_BaseResource_SetMethodName,
                             NULL, params, &callbacks,&operation);       
        
        g_CurrentWmiv2Operation = &operation;
        RecursiveLock_Release(&g_cs_CurrentWmiv2Operation);

        r = GetSetMethodResult(&operation, &returnValue, provContext->resourceId, extendedError); 
        MI_Instance_Delete(params);         
        
        RecursiveLock_Acquire(&g_cs_CurrentWmiv2Operation);
        g_CurrentWmiv2Operation = NULL;
        MI_Operation_Close(&operation);
        RecursiveLock_Release(&g_cs_CurrentWmiv2Operation);
        
        if (r != MI_RESULT_OK)
        {
            MI_OperationOptions_Delete(&sessionOptions);
            return r;
        }

        *resultStatus = returnValue;
        //Stop the timer for set
        finish=CPU_GetTimeStamp();
        duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
        SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
        LogCAMessageTime(provContext->lcmProviderContext, ID_CA_SET_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);
        MI_OperationOptions_Delete(&sessionOptions);        
    }
      
    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    return r;
}



MI_Result GetSetMethodResult(_In_ MI_Operation *operation,
                              _Out_opt_ MI_Uint32 *returnValue,
                             _In_z_ const MI_Char * resourceId,
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Result innerR = MI_RESULT_OK;
    const MI_Instance* outInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails = NULL;  
    MI_Value value;

    *returnValue = 0;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   
    
    /*Get the operation result*/
    r = MI_Operation_GetInstance(operation, &outInstance, &moreResults, &result, &errorMessage, &completionDetails);
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
        /* append resourceid to error message*/
        else
        {
            AppendWMIErrorWithResourceID(*extendedError, resourceId);
        }
        return r;
    }

    /*Get ReturnValue*/
    r = DSC_MI_Instance_GetElement(outInstance, OMI_BaseResource_Method_ReturnValue, &value, NULL, NULL, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError,ID_CAINFRA_GET_RETURNVALUE_FAILED);
    }
    *returnValue = value.uint32;

    return r;
                                
}


MI_Result GetTestMethodResult(_In_ MI_Operation *operation,
                              _Out_opt_ MI_Boolean *bTestResult,
                              _Out_opt_ MI_Uint64 *outProviderContext,
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Result innerR = MI_RESULT_OK;
    const MI_Instance* outInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails = NULL;  
    MI_Value value;

    *bTestResult = MI_TRUE;
    *outProviderContext = 0;
    
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.     
    
    /*Get the operation result*/
    r = MI_Operation_GetInstance(operation, &outInstance, &moreResults, &result, &errorMessage, &completionDetails);
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
        return r;
    }

    /*Get Result  property*/
    r = DSC_MI_Instance_GetElement(outInstance, OMI_BaseResource_Method_Result, &value, NULL, NULL, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError,ID_CAINFRA_GET_RESULT_FAILED);
    }
    *bTestResult = value.boolean;

    /*Get ProviderContext  property*/    
    r = DSC_MI_Instance_GetElement(outInstance, OMI_BaseResource_Method_ProviderContext, &value, NULL, NULL, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError,ID_CAINFRA_GET_PROVCONTEXT_FAILED);
    }   
    *outProviderContext = value.uint64;

    return r;
                                
}

MI_Result GetGetMethodResult(_In_ MI_Operation *operation,
                              _Outptr_result_maybenull_ MI_Instance **outputInstance,
                              _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Result innerR = MI_RESULT_OK;
    const MI_Instance* outInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails = NULL;  
    MI_Value value;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   
    
    *outputInstance = NULL;
    
    /*Get the operation result*/
    r = MI_Operation_GetInstance(operation, &outInstance, &moreResults, &result, &errorMessage, &completionDetails);
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
        return r;
    }

    /*Get configurations  property*/
    r = DSC_MI_Instance_GetElement(outInstance, OMI_BaseResource_Method_OutputResource, &value, NULL, NULL, NULL);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError,ID_CAINFRA_GET_OUTPUTRES_FAILED);
    }
    /*Clone the object*/

    r = DSC_MI_Instance_Clone(value.instance, outputInstance);
    if( r != MI_RESULT_OK )
    {
        return GetCimMIError(r, extendedError,ID_CAINFRA_CLONE_FAILED);
    }    
    return r;
                                
}
MI_Result Get_WMIv2Provider(_In_ ProviderCallbackContext *provContext,   
                               _In_ MI_Application *miApp,
                               _In_ MI_Session *miSession,
                               _In_ MI_Instance *instance,
                               _In_ const MI_Instance *regInstance,
                               _Outptr_result_maybenull_ MI_Instance **outputInstance,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;  
    const MI_Char *provNamespace = NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *params = NULL;
    MI_Value value;
    MI_Value valueOperationOptions;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_Real64 duration;
    MI_OperationOptions sessionOptions ;
    
    ptrdiff_t finish,start;
    //Debug Log 
    DSC_EventWriteEngineMethodParameters(__WFUNCTION__,
                                        instance->classDecl->name,
                                        provContext->resourceId,
                                        0,
                                        provContext->lcmProviderContext->executionMode,
                                        regInstance->nameSpace);
    DSC_EventWriteMessageWmiGet(instance->classDecl->name,provContext->resourceId);
    
    callbacks.writeMessage = DoWriteMessage;
    /* Sign up for progress only if we are in online mode*/
    if( (LCM_EXECUTIONMODE_ONLINE & provContext->lcmProviderContext->executionMode) == LCM_EXECUTIONMODE_ONLINE)
    {
        callbacks.writeProgress = DoWriteProgress;
    }   

    callbacks.callbackContext = (void *)(provContext);
    
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.      

    *outputInstance = NULL;

    start=CPU_GetTimeStamp();
    SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_GET,provContext->lcmProviderContext);
    LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
    DSC_EventWriteMessageInvokingSession(provNamespace,instance->classDecl->name,OMI_BaseResource_GetMethodName);

    if( Tcscasecmp(MSFT_LOGRESOURCENAME, instance->classDecl->name) == 0 )
    {
        r = DSC_MI_Instance_Clone(instance, outputInstance);
        if( r != MI_RESULT_OK)
        {
            return GetCimMIError(r, extendedError, ID_CAINFRA_CLONE_FAILED);
        }
    }
    else
    {
    

        /*Get target namespace*/
        r = DSC_MI_Instance_GetElement(regInstance, MSFT_CimConfigurationProviderRegistration_Namespace, &value, NULL, NULL, NULL);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NAMESPACE_FAILED);
        }
        provNamespace = value.string;

        /*Set input parameters*/
        r = DSC_MI_Application_NewInstance(miApp, MI_T("__Parameters"), NULL, &params);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NEWAPPLICATIONINSTANCE_FAILED);
        }
        value.instance = instance;
        r = DSC_MI_Instance_AddElement(params, OMI_BaseResource_Method_InputResource, &value, MI_INSTANCE, 0 );
        if( r != MI_RESULT_OK)
        {
            MI_Instance_Delete(params);        
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_ADDELEM_FAILED);
        }
        r = MI_Application_NewOperationOptions(miApp, MI_FALSE, &sessionOptions);
        if( r != MI_RESULT_OK )
        {
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_NEWOPERATIONOPTIONS_FAILED);
        }
        valueOperationOptions.string=g_ConfigurationDetails.jobGuidString;
        r =MI_OperationOptions_SetCustomOption(&sessionOptions,DSC_JOBIDSTRING,MI_STRING,&valueOperationOptions,MI_FALSE);
        if( r != MI_RESULT_OK)
        {
            MI_OperationOptions_Delete(&sessionOptions);
            return GetCimMIError(r, extendedError,ID_CAINFRA_GET_SETCUSTOMOPTION_FAILED);
        }
        
        /* Perform Get*/
        
        MI_Session_Invoke(miSession, 0, &sessionOptions, provNamespace, 
                             instance->classDecl->name, OMI_BaseResource_GetMethodName,
                             NULL, params, &callbacks,&operation);  

        r = GetGetMethodResult(&operation, outputInstance , extendedError);
        MI_Instance_Delete(params);
        MI_OperationOptions_Delete(&sessionOptions);
        MI_Operation_Close(&operation);
        if( r != MI_RESULT_OK)
        {           
            return r;
        }
    }
    //Stop timer for get
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_GET,provContext->lcmProviderContext);    
    LogCAMessageTime(provContext->lcmProviderContext, ID_CA_GET_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);
    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    return r;   
}

const MI_Char * GetResourceId( _In_ MI_Instance *inst)
{
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    r = MI_Instance_GetElement(inst, OMI_BaseResource_ResourceId, &value, NULL, NULL, NULL);
    if( r != MI_RESULT_OK)
    {
        return NULL;
    }
    return (const MI_Char*)value.string;
}

const MI_Char * GetSourceInfo( _In_ MI_Instance *inst)
{
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    // Not using DSC version as caller handles the failures as success.
    r = MI_Instance_GetElement(inst, OMI_BaseResource_SourceInfo, &value, NULL, NULL, NULL);
    if( r != MI_RESULT_OK)
    {
        return NULL;
    }
    return (const MI_Char*)value.string;
}

void LogCAMessage(_In_ LCMProviderContext *lcmContext,
                  _In_ MI_Uint32 messageIndex,
                  _In_z_ const MI_Char *resourceId
                  )
{
    MI_Uint32 lcmChannel = MI_WRITEMESSAGE_CHANNEL_VERBOSE;
    MI_Char wcMessage[MAX_PATH] ;
    Intlstr intlstr = Intlstr_Null;
    GetResourceString(messageIndex, &intlstr);
    //merge message and resourceId.
    if( intlstr.str && Stprintf(wcMessage, MAX_PATH, MI_T("%T"), intlstr.str) > 0 )
    {
        LCM_WriteMessage(lcmContext, resourceId, lcmChannel, wcMessage);
    }
    
    if( intlstr.str)
        Intlstr_Free(intlstr);   
}

void LogCAMessageTime(_In_ LCMProviderContext *lcmContext,
                  _In_ MI_Uint32 messageIndex,
                  _In_ const MI_Real64 duration,
                  _In_z_ const MI_Char *resourceId
                  )
{
    MI_Uint32 lcmChannel = MI_WRITEMESSAGE_CHANNEL_VERBOSE;
    MI_Char wcTime[DURATION_SIZE] ; 
    Intlstr intlstr = Intlstr_Null;
    //merge message and resourceId.Stprintf(durationMessage, durationMsgLen, msgStr, resourceId, duration)
    if( Stprintf(wcTime, DURATION_SIZE, MI_T("%0.4f"), duration) > 0 )
    {
        GetResourceString1Param(messageIndex, wcTime, &intlstr);
        if( intlstr.str )
        {
            LCM_WriteMessage(lcmContext, resourceId, lcmChannel, intlstr.str);
            Intlstr_Free(intlstr);
        }
    }   
}

void LogCAProgress( _In_ LCMProviderContext *lcmContext, 
                         _In_z_ const MI_Char * currentOperation,
                         _In_z_ const MI_Char * statusDescription,
                         _In_ MI_Uint32 currentResourceIndex,
                         _In_ MI_Uint32 totalResource)
{
    MI_Uint32 percentComplete = 100;
    MI_Uint32 secondsRemaining = totalResource - currentResourceIndex;

    if( currentResourceIndex+1 != totalResource)
    {
        percentComplete = (MI_Uint32) (100/totalResource) *( currentResourceIndex+1);    
    }
    LCM_WriteProgress(lcmContext, CA_ACTIVITY_NAME, currentOperation, statusDescription, percentComplete, secondsRemaining);
}

void SetMessageInContext(MI_Uint32 msgOperation,MI_Uint32 msgItem,LCMProviderContext *lcmContext)
{
    if(lcmContext!=NULL)
    {
        lcmContext->messageItem=msgItem;
        lcmContext->messageOperation=msgOperation;
    }
}

//Stop the current configuration
//if force is specified then we try to stop the current operation
//otherwise we will wait until the current operation finishes, and then cancel the remaining
MI_Result  MI_CALL StopCurrentConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError, BOOL force)
{
    MI_Result r = MI_RESULT_OK;
    DWORD dwWaitResult;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   
    
    g_CancelConfiguration = TRUE;
    if (force == TRUE)
    {
        DSC_EventWriteMessageWaitCurrentConfig();
        RecursiveLock_Acquire(&g_cs_CurrentWmiv2Operation);

        if (g_CurrentWmiv2Operation != NULL)
        {
            r = MI_Operation_Cancel((MI_Operation*)g_CurrentWmiv2Operation, MI_REASON_NONE);
            if( r == MI_RESULT_OK)
            {
                DSC_EventWriteConfigurationForcelyStopped();
            }
        }

        RecursiveLock_Release(&g_cs_CurrentWmiv2Operation);

        if (r != MI_RESULT_OK)
        {
            g_CancelConfiguration = FALSE;
            return GetCimMIError(r, extendedError,ID_CA_CANCELWMIV2_FAILED);
        }
// Stop ps providers on windows        
#if defined(_MSC_VER)  
#ifndef BUILD_FOR_CORESYSTEM
        r = StopCurrentPSProviderConfiguration(extendedError);
        if (r != MI_RESULT_OK)
        {
            return r;
        }
#endif  
#endif      
    }

    dwWaitResult = Sem_TimedWait(&g_h_ConfigurationStoppedEvent, STOP_CONFIGURATIONT_TIMEOUT);
    g_CancelConfiguration = FALSE;
    if (dwWaitResult != 0)
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_FAILED_TO_WAIT_EVENT);
    }
    
    return MI_RESULT_OK;
}


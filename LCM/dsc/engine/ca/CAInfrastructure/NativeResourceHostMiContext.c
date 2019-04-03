#include "DSC_Systemcalls.h"
#include "pal/strings.h"
#include "CAEngine.h"
#include "EngineHelper.h"
#include "CAEngineInternal.h"
#include "ModuleHandlerInternal.h"
#include "EventWrapper.h"
#include "Resources_LCM.h"
#include "ProviderCallbacks.h"
#include "base/instance.h"
#include "NativeResourceHostMiContext.h"

/**************************************************************************************************/
/*                                                                                                */
/* Implementation of the MI_Context interface                                                     */
/*                                                                                                */
/**************************************************************************************************/

static MI_Result PostResult(_In_ MI_Context* context, MI_Result result)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    nativeResourceProvider->_private.result = result;
    return MI_RESULT_OK;
}

static MI_Result PostInstance(_In_ MI_Context* context, _In_ const MI_Instance * instance)
{
    if (instance == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;

    if (!nativeResourceProvider->_private.resourceProviderClassLoaded) {
        DSC_EventUnSupportedHostMethodCalled(MI_T("PostIndication"));
        return MI_RESULT_NOT_SUPPORTED;
    }

    return MI_Instance_Clone(instance, &nativeResourceProvider->_private.outputResource);
}

static MI_Result WriteMessage(_In_ MI_Context* context, MI_Uint32 channel, const MI_Char* message)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;

    DoWriteMessage(NULL, nativeResourceProvider->_private.callbackContext, channel, message);
	
	return MI_RESULT_OK;
}

static MI_Result WriteProgress(_In_ MI_Context* context, const MI_Char* activity, const MI_Char* currentOperation, const MI_Char* statusDescription, MI_Uint32 percentComplete, MI_Uint32 secondsRemaining)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;

    DoWriteProgress(NULL, nativeResourceProvider->_private.callbackContext, activity, currentOperation, statusDescription, percentComplete, secondsRemaining);

    return MI_RESULT_OK;
}

static MI_Result WriteStreamParameter(_In_ MI_Context* context, const MI_Char* name, _In_ const MI_Value* value, _In_ MI_Type type, _In_ MI_Uint32 flags)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;

    if (!nativeResourceProvider->_private.resourceProviderClassLoaded) {
        DSC_EventUnSupportedHostMethodCalled(MI_T("PostIndication"));
        return MI_RESULT_NOT_SUPPORTED;
    }

    LCM_WriteStreamParameter(nativeResourceProvider->_private.callbackContext->lcmProviderContext, name, value, type, flags);

    return MI_RESULT_OK;
}

static MI_Result WriteError(_In_ MI_Context* context, MI_Uint32 resultCode, _In_z_ const MI_Char* resultType, _In_z_ const MI_Char* errorMessage, _Out_ MI_Boolean *flag)
{
    MI_Result returnValue = MI_RESULT_OK;
    MI_Instance* extendedError = NULL;

    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;

    if (!nativeResourceProvider->_private.resourceProviderClassLoaded) {
        DSC_EventUnSupportedHostMethodCalled(MI_T("PostIndication"));
        return MI_RESULT_NOT_SUPPORTED;
    }

    *flag = MI_TRUE; // TRUE indicates the provider can continue (this is a non-terminating error)

    returnValue = MI_Utilities_CimErrorFromErrorCode(resultCode, resultType, errorMessage, &extendedError);
    EH_CheckResult(returnValue);

    DoWriteError(NULL, nativeResourceProvider->_private.callbackContext, extendedError, NULL);

EH_UNWIND;
    if (extendedError != NULL)
        MI_Instance_Delete(extendedError);

    return returnValue;
}

static MI_Result PostError(_In_ MI_Context* context, MI_Uint32 resultCode, _In_z_ const MI_Char* resultType, _In_z_ const MI_Char* errorMessage)
{
    // After PostError, the resource provider should not invoke any other API in the MI_Context it is given. The NativeResourceManager could do
    // some cleanup here, but currently none is needed so we simply pass the call thru to WriteError.
    MI_Boolean flag;

    return WriteError(context, resultCode, resultType, errorMessage, &flag);
}

static MI_Result WriteCimError(_In_ MI_Context* context, _In_ const MI_Instance *error, _Out_ MI_Boolean*flag)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;

    if (!nativeResourceProvider->_private.resourceProviderClassLoaded) {
        DSC_EventUnSupportedHostMethodCalled(MI_T("PostIndication"));
        return MI_RESULT_NOT_SUPPORTED;
    }

    *flag = MI_TRUE; // TRUE indicates the provider can continue (this is a non-terminating error)

    DoWriteError(NULL, nativeResourceProvider->_private.callbackContext, /* const cast */ (MI_Instance *) error, NULL);

    return MI_RESULT_OK;
}

static MI_Result PostCimError(_In_ MI_Context* context, _In_ const MI_Instance* error)
{
    // After PostCimError, the resource provider should not invoke any other API in the MI_Context it is given. The NativeResourceManager could do
    // some cleanup here, but currently none is needed so we simply pass the call thru to WriteCimError.
    MI_Boolean flag;

    return WriteCimError(context, error, &flag);
}

static MI_Result ConstructInstance(_In_ MI_Context* context, _In_ const MI_ClassDecl *classDecl, _Out_ MI_Instance *instance)
{
#if defined(_MSC_VER)
   return Instance_Construct(classDecl, instance);
#else
   return Instance_Construct(instance, classDecl, NULL);
#endif
}

static MI_Result ConstructParameters(_In_ MI_Context* context, _In_ const MI_MethodDecl *methodDecl, _Out_ MI_Instance *instance)
{
#if defined(_MSC_VER)
    return Instance_Construct((MI_ClassDecl*)methodDecl, instance);
#else
    return Instance_Construct(instance, (MI_ClassDecl*)methodDecl, NULL);
#endif   
}

static MI_Result NewInstance(_In_ MI_Context* context, _In_ const MI_ClassDecl* classDecl, MI_Instance** instance)
{
    #if defined(_MSC_VER)
    return Instance_New(classDecl, instance);
    #else
    return Instance_New(instance, classDecl, NULL);
    #endif
}

static MI_Result NewDynamicInstance(_In_ MI_Context* context, _In_ const MI_Char* className, MI_Uint32 flags, _Outptr_ MI_Instance** instance)
{
    #if defined(_MSC_VER)
    return Instance_InitDynamic(instance, className, flags);
    #else
    return Instance_NewDynamic(instance, className, flags, NULL);
    #endif
}

static MI_Result NewParameters(_In_ MI_Context* context, _In_ const MI_MethodDecl* methodDecl, MI_Instance** instance)
{
    #if defined(_MSC_VER)
    return Instance_New((MI_ClassDecl*)methodDecl, instance);
    #else
    return Instance_New(instance, (MI_ClassDecl*)methodDecl, NULL);
    #endif
}

/**************************************************************************************************/
/*                                                                                                */
/* The rest of the methods are not supported.                                                     */
/*                                                                                                */
/**************************************************************************************************/


static MI_Result PostIndication(_In_ MI_Context* context, _In_ const MI_Instance* indication, MI_Uint32 subscriptionIDCount, const MI_Char* bookmark)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
     DSC_EventUnSupportedHostMethodCalled(MI_T("PostIndication"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result Canceled(_In_ const MI_Context* context, _Out_ MI_Boolean* flag)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
     DSC_EventUnSupportedHostMethodCalled(MI_T("Canceled"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result RegisterCancel(_In_ MI_Context* context, _In_ MI_CancelCallback callback, void* callbackData)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("RegisterCancel"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result RequestUnload(_In_ MI_Context* context)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("RequestUnload"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result RefuseUnload(_In_ MI_Context* context)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("RefuseUnload"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result GetLocalSession(_In_ const MI_Context* context, _Out_ MI_Session* session)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("GetLocalSession"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result GetLocale(_In_ const MI_Context* context, MI_LocaleType localeType, _Out_writes_z_(MI_MAX_LOCALE_SIZE) MI_Char locale[MI_MAX_LOCALE_SIZE])
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("GetLocale"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result GetCustomOption(_In_ MI_Context* context, _In_z_ const MI_Char* name, _Out_opt_  MI_Type* valueType, _Out_opt_  MI_Value* value)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("GetCustomOption"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result SetStringOption(_In_ MI_Context* context, _In_z_ const MI_Char* name, _In_z_ const MI_Char* value)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("SetStringOption"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result GetStringOption(_In_ MI_Context* context, _In_z_ const MI_Char* name, _Outptr_opt_result_maybenull_z_  const MI_Char** value)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("GetStringOption"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result GetNumberOption(_In_ MI_Context* context, _In_z_ const MI_Char *name, _Out_opt_  MI_Uint32* value)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("GetNumberOption"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result GetCustomOptionCount(_In_ MI_Context* context, _Out_opt_ MI_Uint32* count)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("GetCustomOptionCount"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result GetCustomOptionAt(_In_ MI_Context* context, _In_ MI_Uint32 index, _Outptr_opt_result_maybenull_z_  const MI_Char** name, _Out_opt_  MI_Type* valueType, _Out_opt_  MI_Value* value)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    DSC_EventUnSupportedHostMethodCalled(MI_T("GetCustomOptionAt"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result ShouldProcess(_In_ MI_Context* context, const MI_Char* target, const MI_Char* action, _Out_ MI_Boolean* flag)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    *flag = MI_FALSE;
    DSC_EventUnSupportedHostMethodCalled(MI_T("ShouldProcess"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result ShouldContinue(_In_ MI_Context* context, const MI_Char* message, _Out_ MI_Boolean* flag)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    *flag = MI_TRUE;
    DSC_EventUnSupportedHostMethodCalled(MI_T("ShouldContinue"));
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result PromptUser(_In_ MI_Context* context, const MI_Char* message, MI_PromptType promptType, _Out_ MI_Boolean*flag)
{
    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;
    *flag = MI_FALSE;
    DSC_EventUnSupportedHostMethodCalled(MI_T("PromptUser"));
    return MI_RESULT_NOT_SUPPORTED;
}

/**************************************************************************************************/
/*                                                                                                */
/* Creates an instance of NativeResourceProvider                                                  */
/*                                                                                                */
/**************************************************************************************************/

MI_Result NativeResourceProvider_New(const _In_z_ MI_Char* resourceProviderPath, 
                                            const _In_z_ MI_Char* resourceProviderClassName, 
                                            _In_opt_ void *callbackContext, 
                                            _Outptr_ NativeResourceProvider** nativeResourceProvider)
{
    MI_Result returnValue = MI_RESULT_OK;

    *nativeResourceProvider = NULL;

    NativeResourceProvider* nativeResourceProviderLocal = DSC_malloc(sizeof(NativeResourceProvider), NitsHere());
    EH_Check_(nativeResourceProviderLocal != NULL, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);
    memset(nativeResourceProviderLocal, 0, sizeof(NativeResourceProvider));

    //
    // Initialize the MI_Context (base class) of the NativeResourceProvider
    //
    // We use ft as an alias for MI_Context.ft to reduce the number of const casts in the 
    // code below (MI_Context.ft is a const pointer and we do many assigments below).
    //
    MI_ContextFT* ft = NULL;

    nativeResourceProviderLocal->_base.ft = ft = (MI_ContextFT*)DSC_malloc(sizeof(MI_ContextFT), NitsHere());
    EH_Check_(nativeResourceProviderLocal->_base.ft != NULL, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);
    memset(ft, 0, sizeof(MI_ContextFT));

    // Post Methods
    ft->PostResult = PostResult;
    ft->PostInstance = PostInstance;
    ft->PostIndication = PostIndication;
    ft->PostCimError = PostCimError;
    ft->PostError = PostError;

    // Factory Methods
    ft->ConstructInstance = ConstructInstance;
    ft->ConstructParameters = ConstructParameters;
    ft->NewInstance = NewInstance;
    ft->NewDynamicInstance = NewDynamicInstance;
    ft->NewParameters = NewParameters;

    // Misc. Methods
    ft->Canceled = Canceled;
    ft->GetLocale = GetLocale;
    ft->RegisterCancel = RegisterCancel;
    ft->RequestUnload = RequestUnload;
    ft->RefuseUnload = RefuseUnload;
    ft->GetLocalSession = GetLocalSession;
    ft->SetStringOption = SetStringOption;
    ft->GetStringOption = GetStringOption;
    ft->GetNumberOption = GetNumberOption;
    ft->GetCustomOption = GetCustomOption;
    ft->GetCustomOptionCount = GetCustomOptionCount;
    ft->GetCustomOptionAt = GetCustomOptionAt;

    // PowerShell Methods
    ft->WriteMessage = WriteMessage;
    ft->WriteProgress = WriteProgress;
    ft->WriteStreamParameter = WriteStreamParameter;
    ft->WriteCimError = WriteCimError;
    ft->WriteError = WriteError;

    //PowerShell Helper methods
    ft->ShouldProcess = ShouldProcess;
    ft->ShouldContinue = ShouldContinue;
    ft->PromptUser = PromptUser;

    //
    // Initialize the members specific to NativeResourceProvider
    //
    nativeResourceProviderLocal->_private.callbackContext = callbackContext;
    nativeResourceProviderLocal->_private.outputResource = NULL;
    nativeResourceProviderLocal->_private.result = MI_RESULT_OK;

    size_t resourceProviderPathSize = Tcslen(resourceProviderPath) + 1;
    nativeResourceProviderLocal->resourceProviderPath = (MI_Char*)DSC_malloc(sizeof(MI_Char) * resourceProviderPathSize, NitsHere());
    EH_Check_(nativeResourceProviderLocal->resourceProviderPath != NULL, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);
    Tcslcpy(nativeResourceProviderLocal->resourceProviderPath, resourceProviderPath, resourceProviderPathSize);

    //
    // Load the implementation of the resource provider and invoke Load on the MI_Module
    //
    returnValue = NativeResourceProviderMiModule_New(resourceProviderPath, &nativeResourceProviderLocal->_private.resourceProviderMiModule);
    EH_CheckResult(returnValue);

    nativeResourceProviderLocal->_private.resourceProviderMiModule->miModule->Load(&nativeResourceProviderLocal->_private.resourceProviderMiModuleSelf, 
                                                        (MI_Context*) nativeResourceProviderLocal);
    EH_CheckResult(nativeResourceProviderLocal->_private.result);

    nativeResourceProviderLocal->_private.resourceProviderMiModuleLoaded = TRUE;
    
    //
    // Get the class declaration for the the provider and invoke the Load method on the class
    //
    DSC_LOG_INFO("NativeResourceProviderMiModule_GetClassDecl(%s)", resourceProviderClassName);
    returnValue = NativeResourceProviderMiModule_GetClassDecl(nativeResourceProviderLocal->_private.resourceProviderMiModule, 
                                                    resourceProviderClassName, 
                                                     (const MI_ClassDecl **) &nativeResourceProviderLocal->_private.resourceClassDecl);
    EH_CheckResult(returnValue);

    nativeResourceProviderLocal->_private.resourceClassDecl->providerFT->Load(&nativeResourceProviderLocal->_private.resourceClassDeclSelf, 
                                                    nativeResourceProviderLocal->_private.resourceProviderMiModuleSelf, 
                                                    (MI_Context*) nativeResourceProviderLocal);
    EH_CheckResult(nativeResourceProviderLocal->_private.result);

    nativeResourceProviderLocal->_private.resourceProviderClassLoaded = TRUE;

    //
    // Return the local object we just created
    //
    *nativeResourceProvider = nativeResourceProviderLocal;

    DSC_EventCreateHostContextSucceeded();

EH_UNWIND;
    if (returnValue != MI_RESULT_OK) 
    {
        DSC_EventCreateHostContextFailed();

        if (nativeResourceProviderLocal != NULL) 
            NativeResourceProvider_Delete(nativeResourceProviderLocal);
    }
        

    return returnValue;
}

/**************************************************************************************************/
/*                                                                                                */
/* Deletes the given NativeResourceProvider                                                       */
/*                                                                                                */
/**************************************************************************************************/
MI_Result NativeResourceProvider_Delete(_In_ NativeResourceProvider* nativeResourceProvider)
{
    if (nativeResourceProvider != NULL)
    {
        if (nativeResourceProvider->_private.resourceProviderClassLoaded)
            nativeResourceProvider->_private.resourceClassDecl->providerFT->Unload(nativeResourceProvider->_private.resourceClassDeclSelf, (MI_Context*) nativeResourceProvider);

        if (nativeResourceProvider->_private.resourceProviderMiModuleLoaded)
            nativeResourceProvider->_private.resourceProviderMiModule->miModule->Unload(nativeResourceProvider->_private.resourceProviderMiModuleSelf, (MI_Context*) nativeResourceProvider);

        if (nativeResourceProvider->_private.resourceProviderMiModule != NULL)
            NativeResourceProviderMiModule_Delete(nativeResourceProvider->_private.resourceProviderMiModule);

        if (nativeResourceProvider->_private.outputResource != NULL)
            MI_Instance_Delete(nativeResourceProvider->_private.outputResource);

        if (nativeResourceProvider->resourceProviderPath != NULL)
            DSC_free(nativeResourceProvider->resourceProviderPath);

        MI_ContextFT* ft = (MI_ContextFT*)((MI_Context*)nativeResourceProvider)->ft;

        if (ft != NULL)
            DSC_free(ft);

        DSC_free(nativeResourceProvider);
    }

    return MI_RESULT_OK;
}

/**************************************************************************************************/
/*                                                                                                */
/* InvokeMethod                                                                                   */
/*                                                                                                */
/**************************************************************************************************/

static MI_Result InvokeMethod(_In_ NativeResourceProvider* resourceProvider, const _In_z_ MI_Char* methodName, const _In_ MI_Instance* inputResource, _Outptr_result_maybenull_ MI_Instance** outputResource, _Outptr_result_maybenull_ MI_Instance** extendedError) {
    if (outputResource == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *outputResource = NULL;

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;

    MI_Result returnValue = MI_RESULT_OK;
    MI_Instance *methodInputResourceCopy = NULL;
    MI_Instance *inputResourceInstance = NULL;

    MI_Context* resourceProviderMiContext = (MI_Context*)resourceProvider;

    DSC_EventInvokingNativeResourceMethod(methodName, inputResource->classDecl->name, resourceProvider->resourceProviderPath);

    //
    // Create a copy of the arguments that will be passed to the method - this copy is needed because the value of 'inputResource'
    // is created dynamically without type information; we create all its properties explicitly below.
    //
    resourceProviderMiContext->ft->NewInstance(resourceProviderMiContext, resourceProvider->_private.resourceClassDecl, &methodInputResourceCopy);
    EH_CheckResult(returnValue);

    MI_Uint32 elementCount;
    returnValue = MI_Instance_GetElementCount(inputResource, &elementCount);
    EH_CheckResult(returnValue);

    MI_Uint32 i;
    for (i = 0; i < elementCount; i++) {
        const MI_Char* propertyName;
        MI_Value propertyValue;
        MI_Type propertyType;

        returnValue = MI_Instance_GetElementAt(inputResource, i, &propertyName, &propertyValue, &propertyType, 0);
        EH_CheckResult(returnValue);

        returnValue = MI_Instance_SetElement(methodInputResourceCopy, propertyName, &propertyValue, propertyType, 0);
        EH_CheckResult(returnValue);
    }

    // Get the method that will be invoked
    // NOTE: the method declarations is managed by the provider's implementation of MI_Module and should not be deallocated
    const MI_MethodDecl* methodDecl = NULL;
    returnValue = NativeResourceProviderMiModule_GetMethodDecl(resourceProvider->_private.resourceClassDecl, methodName, &methodDecl);
    EH_CheckResult(returnValue);

    // Invoke the method
    returnValue = resourceProviderMiContext->ft->NewParameters(resourceProviderMiContext, methodDecl, &inputResourceInstance);
    EH_CheckResult(returnValue);
    
    // Check if provider needs an array or single element
    MI_Type type;
    returnValue = MI_Instance_GetElement(inputResourceInstance, OMI_BaseResource_Method_InputResource, NULL, &type, NULL,NULL);

    MI_Value value;
    EH_CheckResult(returnValue);
    if( type & MI_ARRAY)
    {
        value.instancea.size = 1;
        value.instancea.data = &methodInputResourceCopy;
    }
    else
    {
        value.instance = methodInputResourceCopy;
    }
    
    returnValue = MI_Instance_SetElement(inputResourceInstance, OMI_BaseResource_Method_InputResource, &value, type, 0);
    EH_CheckResult(returnValue);

    size_t length = Tcslen(inputResource->classDecl->name)+1;
    MI_Char* str = (MI_Char*)DSC_malloc(length * sizeof(MI_Char), NitsHere()); 
    memcpy(str, inputResource->classDecl->name, length * sizeof(MI_Char));

    methodDecl->function(resourceProvider->_private.resourceClassDeclSelf, resourceProviderMiContext, NULL, str, methodName, NULL, inputResourceInstance);

    // Set the output resource to the instance posted by the provider, but only if the result is MI_RESULT_OK. 
    // If no instance has been posted, return MI_RESULT_NOT_FOUND.
    if (resourceProvider->_private.result != MI_RESULT_OK) {
        EH_Fail_(returnValue = resourceProvider->_private.result);
    }

    if (resourceProvider->_private.outputResource == NULL) {
        EH_Fail_(returnValue = MI_RESULT_NOT_FOUND);
    }
    
    *outputResource = resourceProvider->_private.outputResource;
    
    resourceProvider->_private.outputResource = NULL;

    returnValue = MI_RESULT_OK;

EH_UNWIND;

    if (inputResourceInstance != NULL)
        MI_Instance_Delete(inputResourceInstance);

    if (methodInputResourceCopy != NULL)
        MI_Instance_Delete(methodInputResourceCopy);

    return returnValue;
}

/**************************************************************************************************/
/*                                                                                                */
/*  NativeResourceProvider_GetTargetResource                                                      */
/*                                                                                                */
/**************************************************************************************************/

MI_Result NativeResourceProvider_GetTargetResource(
    _In_ NativeResourceProvider* resourceProvider,
    _In_ MI_Application *miApplication,
    _In_ MI_Session *miSession,
    _In_ MI_Instance *nativeResource,
    _In_ const MI_Instance *resourceProviderRegistration,
    // _Inout_ MI_InstanceA *outputInstance,
    _Inout_ MI_Instance *outputInstance,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    if (outputInstance == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;

    ptrdiff_t start,finish;
    MI_Real64 duration;

    MI_Result returnValue = MI_RESULT_OK;
    MI_Instance *outputResourceSystemProperties = NULL;

    ProviderCallbackContext* providerCallbackContext = resourceProvider->_private.callbackContext;

    LCMProviderContext* lcmProviderContext = providerCallbackContext->lcmProviderContext;

    DSC_EventWriteEngineMethodParameters(
        __WFUNCTION__,
        nativeResource->classDecl->name,
        providerCallbackContext->resourceId,
        0,
        lcmProviderContext->executionMode,
        resourceProviderRegistration->nameSpace);
    //TODO: DSC_EventWriteMessageWmiGet(provContext->lcmProviderContext->configurationDetails.jobGuidString, instance->classDecl->name, provContext->resourceId);

    start = CPU_GetTimeStamp();
    SetMessageInContext(ID_OUTPUT_OPERATION_START, ID_OUTPUT_ITEM_GET, lcmProviderContext);
    LogCAMessage(lcmProviderContext, ID_OUTPUT_EMPTYSTRING, providerCallbackContext->resourceId);
    // TODO: DSC_EventWriteMessageInvokingSession(provContext->lcmProviderContext->configurationDetails.jobGuidString, provNamespace, instance->classDecl->name, OMI_BaseResource_GetMethodName);

    // Invoke GetTargetResource
    MI_Instance* outputResource = NULL;
    returnValue = InvokeMethod(resourceProvider, OMI_BaseResource_GetMethodName, nativeResource, &outputResource, extendedError);
    EH_CheckResult(returnValue);

    // Get the output resource returned by GetTargetResource and remove (filter) the system properties (resource properties from base classes)
    MI_Value outputResourceValue;
    returnValue = DSC_MI_Instance_GetElement(outputResource, OMI_BaseResource_Method_OutputResource, &outputResourceValue, NULL, NULL, NULL);
    EH_CheckResult(returnValue);

    MI_Instance *outputResourceFiltered = NULL;
    returnValue = GetFilteredResource(miApplication, outputResourceValue.instance, &outputResourceFiltered, extendedError);
    EH_CheckResult(returnValue);

    // Return the output resource
    MI_Instance_Clone(outputResourceFiltered, outputInstance);
    
EH_UNWIND;// Empty statement needed for not-C99-standard compiler on Linux

    // Log the duration of the operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    SetMessageInContext(ID_OUTPUT_OPERATION_END, ID_OUTPUT_ITEM_GET, lcmProviderContext);
    LogCAMessageTime(lcmProviderContext, ID_CA_GET_TIMEMESSAGE, (const MI_Real64)duration, providerCallbackContext->resourceId);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

    if (outputResourceSystemProperties)
        MI_Instance_Delete(outputResourceSystemProperties);

    return returnValue;
}

/**************************************************************************************************/
/*                                                                                                */
/*  NativeResourceProvider_TestTargetResource                                                      */
/*                                                                                                */
/**************************************************************************************************/

MI_Result NativeResourceProvider_TestTargetResource(
    _In_ NativeResourceProvider* resourceProvider,
    _In_ MI_Application *miApplication,
    _In_ MI_Session *miSession,
    _In_ MI_Instance *nativeResource,
    _In_ const MI_Instance *resourceProviderRegistration,
    _Outptr_ MI_Uint32 *testOperationResult,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;

    ptrdiff_t start,finish;
    MI_Real64 duration;

    MI_Result returnValue = MI_RESULT_OK;

    ProviderCallbackContext* providerCallbackContext = resourceProvider->_private.callbackContext;
    LCMProviderContext*lcmProviderContext = providerCallbackContext->lcmProviderContext;

    DSC_EventWriteEngineMethodParameters(
        __WFUNCTION__,
        nativeResource->classDecl->name,
        providerCallbackContext->resourceId,
        0,
        lcmProviderContext->executionMode,
        resourceProviderRegistration->nameSpace);

    start = CPU_GetTimeStamp();
    SetMessageInContext(ID_OUTPUT_OPERATION_START, ID_OUTPUT_ITEM_TEST, lcmProviderContext);
    LogCAMessage(lcmProviderContext, ID_OUTPUT_EMPTYSTRING, providerCallbackContext->resourceId);

    // Invoke TestTargetResource
    MI_Instance* outputResource = NULL;
    returnValue = InvokeMethod(resourceProvider, OMI_BaseResource_TestMethodName, nativeResource, &outputResource, extendedError);
    EH_CheckResult(returnValue);


    // Get the output resource returned by TestTargetResource
    MI_Value outputResourceValue;
    returnValue = DSC_MI_Instance_GetElement(outputResource, OMI_BaseResource_Method_Result, &outputResourceValue, NULL, NULL, NULL);
    EH_CheckResult(returnValue);

    *testOperationResult = (MI_Uint32)outputResourceValue.boolean;

EH_UNWIND;// Empty statement needed for not-C99-standard compiler on Linux

    // Log the duration of the operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    SetMessageInContext(ID_OUTPUT_OPERATION_END, ID_OUTPUT_ITEM_TEST, lcmProviderContext);
    LogCAMessageTime(lcmProviderContext, ID_CA_GET_TIMEMESSAGE, (const MI_Real64)duration, providerCallbackContext->resourceId);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

    return returnValue;
}

/**************************************************************************************************/
/*                                                                                                */
/*  NativeResourceProvider_GetInventory                                                      */
/*                                                                                                */
/**************************************************************************************************/

MI_Result NativeResourceProvider_GetInventory(
    _In_ NativeResourceProvider* resourceProvider,
    _In_ MI_Application *miApplication,
    _In_ MI_Session *miSession,
    _In_ MI_Instance *nativeResource,
    _In_ const MI_Instance *resourceProviderRegistration,
    _Inout_ MI_InstanceA *outputInstance,
    _Outptr_result_maybenull_ MI_Instance **extendedError
)
{
    if (outputInstance == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;

    ptrdiff_t start,finish;
    MI_Real64 duration;

    MI_Result returnValue = MI_RESULT_OK;

    ProviderCallbackContext* providerCallbackContext = resourceProvider->_private.callbackContext;
    LCMProviderContext*lcmProviderContext = providerCallbackContext->lcmProviderContext;

    DSC_EventWriteEngineMethodParameters(
        __WFUNCTION__,
        nativeResource->classDecl->name,
        providerCallbackContext->resourceId,
        0,
        lcmProviderContext->executionMode,
        resourceProviderRegistration->nameSpace);

    start = CPU_GetTimeStamp();
    SetMessageInContext(ID_OUTPUT_OPERATION_START, ID_OUTPUT_ITEM_GET, lcmProviderContext);
    LogCAMessage(lcmProviderContext, ID_OUTPUT_EMPTYSTRING, providerCallbackContext->resourceId);

    // Invoke GetTargetResource
    MI_Instance* outputResource = NULL;
    returnValue = InvokeMethod(resourceProvider, OMI_BaseResource_InventoryMethodName, nativeResource, &outputResource, extendedError);
    EH_CheckResult(returnValue);
    // For Inventory output is send via streaming

EH_UNWIND;// Empty statement needed for not-C99-standard compiler on Linux

    // Log the duration of the operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    SetMessageInContext(ID_OUTPUT_OPERATION_END, ID_OUTPUT_ITEM_GET, lcmProviderContext);
    LogCAMessageTime(lcmProviderContext, ID_CA_GET_TIMEMESSAGE, (const MI_Real64)duration, providerCallbackContext->resourceId);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

    return returnValue;
}

/**************************************************************************************************/
/*                                                                                                */
/*  NativeResourceProvider_SetTargetResource                                                      */
/*                                                                                                */
/**************************************************************************************************/

MI_Result NativeResourceProvider_SetTargetResource(
    _In_ NativeResourceProvider* resourceProvider,
    _In_ MI_Application *miApplication,
    _In_ MI_Session *miSession,
    _In_ MI_Instance *nativeResource,
    _In_ const MI_Instance *resourceProviderRegistration,
    _Outptr_ MI_Uint32 *p_operation_result,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    if (extendedError == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;

    ptrdiff_t start,finish;
    MI_Real64 duration;

    MI_Result returnValue = MI_RESULT_OK;

    ProviderCallbackContext* providerCallbackContext = resourceProvider->_private.callbackContext;
    LCMProviderContext*lcmProviderContext = providerCallbackContext->lcmProviderContext;

    DSC_EventWriteEngineMethodParameters(
        __WFUNCTION__,
        nativeResource->classDecl->name,
        providerCallbackContext->resourceId,
        0,
        lcmProviderContext->executionMode,
        resourceProviderRegistration->nameSpace);

    start = CPU_GetTimeStamp();
    SetMessageInContext(ID_OUTPUT_OPERATION_START, ID_OUTPUT_ITEM_SET, lcmProviderContext);
    LogCAMessage(lcmProviderContext, ID_OUTPUT_EMPTYSTRING, providerCallbackContext->resourceId);

    // Invoke SetTargetResource
    MI_Instance* outputResource = NULL;
    returnValue = InvokeMethod(resourceProvider, OMI_BaseResource_SetMethodName, nativeResource, &outputResource, extendedError);
    EH_CheckResult(returnValue);

    // Get the output resource returned by SetTargetResource
    MI_Value outputResourceValue;
    returnValue = DSC_MI_Instance_GetElement(outputResource, OMI_BaseResource_Method_MIReturn, &outputResourceValue, NULL, NULL, NULL);

    EH_CheckResult(returnValue);
    
    *p_operation_result = outputResourceValue.uint32;

EH_UNWIND;// Empty statement needed for not-C99-standard compiler on Linux

    // Log the duration of the operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    SetMessageInContext(ID_OUTPUT_OPERATION_END, ID_OUTPUT_ITEM_SET, lcmProviderContext);
    LogCAMessageTime(lcmProviderContext, ID_CA_GET_TIMEMESSAGE, (const MI_Real64)duration, providerCallbackContext->resourceId);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

    return returnValue;
}

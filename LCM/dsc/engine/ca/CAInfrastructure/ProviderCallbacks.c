#include "ProviderCallbacks.h"
#include "EventWrapper.h"
#include "DSC_Systemcalls.h"

void MI_CALL DoWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *)callbackContext;
    LCM_WriteMessageFromProvider(providerContext->lcmProviderContext, providerContext->resourceId, channel, message);
    DSC_LOG(DSC_LOG_VERBOSE_LEVEL, 0, "", 0, "[%s] %s", providerContext->resourceId, message);
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
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *)callbackContext;
    LCM_WriteProgress(providerContext->lcmProviderContext, activity, currentOperation,
        statusDescription, percentageComplete, secondsRemaining);
}

void MI_CALL DoPromptUser(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_z_   const MI_Char *message,
    MI_PromptType promptType,
    _In_     MI_Result(MI_CALL * promptUserResult)(_In_ MI_Operation *operation,
        MI_OperationCallback_ResponseType response))
{
    MI_Boolean bPromptUserResultStatus;
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *)callbackContext;
    LCM_PromptUserFromProvider(providerContext->lcmProviderContext, providerContext->resourceId, message, promptType, &bPromptUserResultStatus);
    if (promptUserResult)
    {
        promptUserResult(operation, bPromptUserResultStatus);
    }
}

/*This function will be called whenever a native resource writes a non-terminating error.*/
void MI_CALL DoWriteError(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_     MI_Instance* instance,
    _In_     MI_Result(MI_CALL* writeErrorResult)(_In_ MI_Operation* operation,
        MI_OperationCallback_ResponseType response))
{
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *)callbackContext;
    LCM_WriteError(providerContext->lcmProviderContext, instance);

    MI_Result error_code = MI_RESULT_OK;
    MI_ConstStringPtr error_message;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;
    MI_Result result;

    result = DSC_MI_Instance_GetElement(instance, MI_T("CIMStatusCode"), &value, &type, &flags, NULL);
    if (result == MI_RESULT_OK &&
        type == MI_UINT16 &&
        (flags & MI_FLAG_NULL) == 0)
    {
        error_code = value.uint16;
    }

    result = DSC_MI_Instance_GetElement(instance, MI_T("Message"), &value, &type, &flags, NULL);
    if (result == MI_RESULT_OK &&
        type == MI_STRING &&
        (flags & MI_FLAG_NULL) == 0)
    {
        error_message = value.string;
    }

    DSC_LOG(DSC_LOG_ERROR_LEVEL, 0, "", 0, "[%s] error code = %d, error message: '%s'", providerContext->resourceId, error_code, error_message);
}

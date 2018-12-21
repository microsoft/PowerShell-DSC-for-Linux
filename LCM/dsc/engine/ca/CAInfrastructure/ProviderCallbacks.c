#include "ProviderCallbacks.h"

void MI_CALL DoWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *)callbackContext;
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
    //providerContext->lcmProviderContext->initVariables->nonTerminatingErrorFromNativeProvider = TRUE;
    //LCM_WriteError(providerContext->lcmProviderContext, providerContext->resourceId, REPORTING_TYPE_PSWMIRESOURCE, instance);
    LCM_WriteError(providerContext->lcmProviderContext, instance);
}

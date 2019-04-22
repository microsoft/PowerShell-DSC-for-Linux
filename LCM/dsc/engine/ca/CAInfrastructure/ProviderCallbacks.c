/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

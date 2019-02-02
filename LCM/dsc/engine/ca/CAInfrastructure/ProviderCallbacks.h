#ifndef _PROVIDER_CALLBACKS_H
#define _PROVIDER_CALLBACKS_H

/**************************************************************************************************/
/*                                                                                                */
/* These callbacks are used by resource providers to produce verbose output and report progress   */
/* and non-terminating errors.                                                                                     */
/*                                                                                                */
/**************************************************************************************************/

#include "CAEngine.h"
#include "LocalConfigManagerHelperForCA.h"

void MI_CALL DoWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    MI_Uint32 channel,
    _In_z_   const MI_Char *message);

void MI_CALL DoWriteProgress(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_z_   const MI_Char *activity,
    _In_z_   const MI_Char *currentOperation,
    _In_z_   const MI_Char *statusDescription,
    MI_Uint32 percentageComplete,
    MI_Uint32 secondsRemaining);

void MI_CALL DoPromptUser(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_z_   const MI_Char *message,
    MI_PromptType promptType,
    _In_     MI_Result(MI_CALL * promptUserResult)(_In_ MI_Operation *operation,
        MI_OperationCallback_ResponseType response));

void MI_CALL DoWriteError(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_     MI_Instance* instance,
    _In_     MI_Result(MI_CALL* writeErrorResult)(_In_ MI_Operation* operation,
        MI_OperationCallback_ResponseType response));

#endif // _PROVIDER_CALLBACKS_H

/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

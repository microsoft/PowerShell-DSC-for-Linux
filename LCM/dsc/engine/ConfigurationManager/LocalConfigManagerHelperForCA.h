/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _LOCALCONFIGMANAGERHELPERFORCA_H_
#define _LOCALCONFIGMANAGERHELPERFORCA_H_

#include "pal/lock.h"
#include "pal/sem.h"

RecursiveLock g_cs_CurrentWmiv2Operation;
Sem g_h_ConfigurationStoppedEvent;
volatile BOOL g_CancelConfiguration;


#ifdef __cplusplus
extern "C"
{
#endif

// These methods are used by CA to communicate back to LCM.
    void LCM_WriteMessage( _In_ LCMProviderContext *lcmContext,
                                _In_z_ const MI_Char *resourceId,
                                _In_ MI_Uint32 channel,
                                _In_z_ const MI_Char *message
                                );

    void LCM_WriteMessageNoParamWithoutContext(
        _In_z_ const MI_Char *resourceId,
        _In_ MI_Uint32 errorStringId,
        _In_ MI_Uint32 channel
        );

    void LCM_WriteMessage1ParamWithoutContext(
        _In_z_ const MI_Char *resourceId,
        _In_ MI_Uint32 errorStringId,
        _In_z_ const MI_Char * param1,
        _In_ MI_Uint32 channel
        );
    //Method to display the time taken in the specified channel
   
    void LCM_WriteMessage_Internal_TimeTaken(
        _In_ MI_Context *context,
        _In_z_ const MI_Char *resourceId,
        _In_ MI_Uint32 messageID,
        _In_ MI_Uint32 tokenItem,
        _In_ const MI_Real64 duration,
        _In_ MI_Uint32 channel);
   

    void LCM_WriteMessageFromProvider( _In_ LCMProviderContext *lcmContext,
                                _In_z_ const MI_Char *resourceId,
                                _In_ MI_Uint32 channel,
                                _In_z_ const MI_Char *message
                                );

    void LCM_WriteProgress( _In_ LCMProviderContext *lcmContext,
                                 _In_z_ const MI_Char *activity,
                                 _In_z_ const MI_Char * currentOperation,
                                 _In_z_ const MI_Char * statusDescroption,
                                 _In_ MI_Uint32 percentComplete,
                                 _In_ MI_Uint32 secondsRemaining);

    void LCM_WriteError( _In_ LCMProviderContext *lcmContext,
                            _In_ MI_Instance* instanceMIError);
    

    void LCM_PromptUserFromProvider( _In_ LCMProviderContext *lcmContext,
                       _In_z_ const MI_Char *resourceId,
                       _In_z_   const MI_Char *message,
                       _In_ MI_PromptType promptType,
                       _Out_ MI_Boolean *flag);

    void LCM_WriteStreamParameter(_In_ LCMProviderContext* lcmContext,
        _In_z_ const MI_Char* name,
        _In_ const MI_Value* value,
        _In_ MI_Type type,
        _In_ MI_Uint32 flags);

    MI_Result SetMetaConfig(_In_ const MI_Instance* metaConfig,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    //the caller should call MSFT_DSCMetaConfiguration_Delete to delete the instance
    MI_Result GetMetaConfig(_Outptr_ MSFT_DSCMetaConfiguration ** metaConfigInstance);

    MI_Result RegisterStandardTasks(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

#ifdef __cplusplus

}

#endif
#endif //_LOCALCONFIGMANAGERHELPERFORCA_H_

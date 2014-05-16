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

#ifndef _LOCALCONFIGMANAGERHELPERFORCA_H_
#define _LOCALCONFIGMANAGERHELPERFORCA_H_

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

    MI_Result SetMetaConfig(_In_ const MI_Instance* metaConfig, 
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    //the caller should call MSFT_DSCMetaConfiguration_Delete to delete the instance
    MI_Result GetMetaConfig(_Outptr_ MSFT_DSCMetaConfiguration ** metaConfigInstance);

    MI_Result RegisterStandardTasks(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

#ifdef __cplusplus

}

#endif
#endif //_LOCALCONFIGMANAGERHELPERFORCA_H_

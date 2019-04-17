/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved.

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* @migen@ */

#include "MI.h"
#include "MSFT_DSCLocalConfigurationManager.h"
#include "LocalConfigurationManager.h"
#include "EngineHelper.h"
#include "EventWrapper.h"
#include "Resources_LCM.h"

#if defined(BUILD_OMS)
#include <signal.h>
// Variable to store old Signal for SIGCHLD
static struct sigaction oldAction ;
#endif

void MI_CALL MSFT_DSCLocalConfigurationManager_Load(
    _Outptr_result_maybenull_ MSFT_DSCLocalConfigurationManager_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
#if defined(BUILD_OMS)
    memset(&oldAction, 0, sizeof(struct sigaction));
    sigaction(SIGCHLD, NULL, &oldAction);
#endif
    //load will not be called by multiple threads
    miResult = InitHandler(MI_T("MSFT_DSCLocalConfigurationManager_Load"), &cimErrorDetails);

    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    DSC_EventWriteMessageLoadingDscEngineProvider();
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Unload(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context)
{
    DSC_EventWriteMessageUnLoadingDscEngineProvider();
    UnloadFromProvider(self, context);

#if defined(BUILD_OMS)
        // Set the SIGCHLD signal to default
        // This is to ensure that if any provider has overriden this specific signal
        // provider DSC reset it back to the previous signal.
    sigaction(SIGCHLD, &oldAction, NULL);
    memset(&oldAction, 0, sizeof(struct sigaction));
#endif
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    if (!in || !in->ConfigurationData.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        ResetJobId();
        return;
    }
    Invoke_SendConfiguration(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    if (!in || !in->ConfigurationData.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        ResetJobId();
        return;
    }
    Invoke_SendConfigurationApply(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    Invoke_GetConfiguration(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_ApplyConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    Invoke_ApplyConfiguration(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendMetaConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* in)
{
    SetJobId();
    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);

    if (!in || !in->ConfigurationData.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        ResetJobId();
        return;
    }
    Invoke_SendMetaConfigurationApply(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_GetMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    Invoke_GetMetaConfiguration(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_RollBack(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_RollBack* in)
{
    MI_Instance *cimErrorDetails = NULL;
    SetJobId();
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    if (in && in->configurationNumber.exists)
    {
        GetCimMIError(MI_RESULT_INVALID_PARAMETER, &cimErrorDetails, ID_LCM_CONF_NUMBEREXIST);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }
    //Show up an error if confirm is used. Whatif is supported but not confirm
    if (IsConfirmUsed(context))
    {
        GetCimMIError(MI_RESULT_INVALID_PARAMETER, &cimErrorDetails, ID_LCM_CONFIRM_NOT_SUPPORTED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }
    Invoke_RollBack(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_TestConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* in)
{
    MI_Instance *cimErrorDetails = NULL;
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    // If configuration data exists, output error mentioning this is reserved for future use
    if (in && in->configurationData.exists)
    {
        GetCimMIError(MI_RESULT_INVALID_PARAMETER, &cimErrorDetails, ID_LCM_CONF_DATAEXIST);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }
    Invoke_TestConfiguration(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformRequiredConfigurationChecks(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    if (!in->Flags.exists || !(in->Flags.value == TASK_REGULAR || in->Flags.value == TASK_REBOOT || in->Flags.value == TASK_BOOTSTRAP ))
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        ResetJobId();
        return;
    }
    Invoke_PerformRequiredConfigurationChecks(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_StopConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    Invoke_StopConfiguration(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformInventory(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventory* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    Invoke_PerformInventory(self, context, nameSpace, className, methodName, instanceName, in);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformInventoryOOB(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* in)
{
    SetJobId();

    // Debug Log
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    Invoke_PerformInventoryOOB(self, context, nameSpace, className, methodName, instanceName, in);
}

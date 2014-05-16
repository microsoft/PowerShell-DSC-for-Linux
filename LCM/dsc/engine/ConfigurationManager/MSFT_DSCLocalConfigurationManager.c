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

/* @migen@ */

#include "MI.h"
#if defined(_MSC_VER)
#include "MSFT_DSCLocalConfigurationManager.h"
#else
#include "omi_msft_dsclocalconfigurationmanager.h"
#endif
#include "LocalConfigurationManager.h"
#include "EngineHelper.h"
#include "EventWrapper.h"
#include "Resources_LCM.h"


void MI_CALL MSFT_DSCLocalConfigurationManager_Load(
    _Outptr_result_maybenull_ MSFT_DSCLocalConfigurationManager_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCLocalConfigurationManager_Unload(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context)
{
    UnloadFromProvider(self, context);
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
    if (in->configurationNumber.exists)
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


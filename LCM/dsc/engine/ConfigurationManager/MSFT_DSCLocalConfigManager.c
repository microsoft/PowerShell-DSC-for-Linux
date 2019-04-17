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
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26061 26071  26036) //public strsafe.h is giving errors about some of the methods hence disabling it
#endif /* _PREFAST_ */

#include <strsafe.h>
#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

#include <MI.h>
#include "MSFT_DSCLocalConfigManager.h"

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26061 26071  26036) //public strsafe.h is giving errors about some of the methods hence disabling it
#endif /* _PREFAST_ */

#include <strsafe.h>
#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

#include <EngineHelper.h>
#include "LocalConfigManagerHelper.h"
#include "ModuleHandlerInternal.h"
#include "common\SystemCalls.h"
#include "Resources_LCM.h"


void MI_CALL MSFT_DSCLocalConfigManager_Load(
    _Outptr_result_maybenull_ MSFT_DSCLocalConfigManager_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;

    //load will not be called by multiple threads
    miResult = InitHandler(&cimErrorDetails);

    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);        
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCLocalConfigManager_Unload(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_UNREFERENCED_PARAMETER(self);

    miResult = UnInitHandler(&cimErrorDetails);
    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);        
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 bufferIndex = 0;
    HANDLE m_clientThreadToken;
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    if(!in->ConfigurationData.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;        
    }

    if(!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    GetRealBufferIndex( &(in->ConfigurationData.value), &bufferIndex);

    miResult = CallSetConfiguration(in->ConfigurationData.value.data + bufferIndex, 
                            in->ConfigurationData.value.size - bufferIndex, LCM_SETFLAGS_SAVETOPENDINGONLY, context, &cimErrorDetails); 

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails,ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    CloseHandle(m_clientThreadToken);
    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);

}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfigurationApply* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 bufferIndex = 0;
    HANDLE m_clientThreadToken;
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    if(!in->ConfigurationData.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;        
    }

    if(!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    GetRealBufferIndex( &(in->ConfigurationData.value), &bufferIndex);

    miResult = CallSetConfiguration(in->ConfigurationData.value.data + bufferIndex, 
                            in->ConfigurationData.value.size - bufferIndex, LCM_SETFLAGS_DEFAULT, context, &cimErrorDetails); 

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    CloseHandle(m_clientThreadToken);

    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfigurationWhatIf(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfigurationApplyQuick(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_GetConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_InstanceA outInstances = {0};
    MI_Value val;
    MI_Uint32 bufferIndex = 0;    
    MSFT_DSCLocalConfigManager_GetConfiguration outputObject;
    HANDLE m_clientThreadToken;
    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

            
    if(!in->configurationData.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;        
    }

    if(!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_GetConfiguration_Construct(&outputObject, context);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }   

    GetRealBufferIndex( &(in->configurationData.value), &bufferIndex);
    miResult = CallGetConfiguration(in->configurationData.value.data + bufferIndex, 
                                in->configurationData.value.size - bufferIndex, &outInstances, 
                                context, &cimErrorDetails);
    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }
   
    val.instancea.data = outInstances.data;
    val.instancea.size = outInstances.size;
    miResult = MI_Context_WriteStreamParameter(context, L"configurations", &val, MI_INSTANCEA, 0);
    CleanUpInstanceCache(&outInstances);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_WRITEGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_GetConfiguration_Set_MIReturn(&outputObject, 0);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_GetConfiguration_Post(&outputObject, context);
    MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    CloseHandle(m_clientThreadToken);

    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_GetConfigurationHistory(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_GetConfigurationHistory* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_ApplyConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_ApplyConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MSFT_DSCLocalConfigManager_ApplyConfiguration outputObject;
    HANDLE m_clientThreadToken;
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    if(!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_ApplyConfiguration_Construct(&outputObject, context);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTAPPLY_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }       


    miResult = CallConsistencyEngine(context, &cimErrorDetails); 

    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_ApplyConfiguration_Set_MIReturn(&outputObject, 0);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETAPPLY_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_ApplyConfiguration_Post(&outputObject, context);
    MSFT_DSCLocalConfigManager_ApplyConfiguration_Destruct(&outputObject);

    
    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    CloseHandle(m_clientThreadToken);

    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTAPPLY_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }    

    MI_Context_PostResult(context, MI_RESULT_OK);

}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_PullConfigurationNow(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_PullConfigurationNow* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendMetaConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    HANDLE m_clientThreadToken;
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    if(!in->MetaConfiguration.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;        
    }

    if(!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = SetMetaConfig(in->MetaConfiguration.value, &cimErrorDetails);

    
    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    CloseHandle(m_clientThreadToken);

    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_GetMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_GetMetaConfiguration* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_RollBack(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_RollBack* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_Cancel(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_Cancel* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_Suspend(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_Suspend* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DSCLocalConfigManager_Invoke_Resume(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_Resume* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}


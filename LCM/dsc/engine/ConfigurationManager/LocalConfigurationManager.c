/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MI.h"

#include "MSFT_DSCLocalConfigurationManager.h"

#include <EngineHelper.h>
#include "LocalConfigManagerHelper.h"
#include "ModuleHandlerInternal.h"

#include "DSC_Systemcalls.h"
#include "Resources_LCM.h"
#include "EventWrapper.h"
#include "CAEngine.h"

#include <xmlserializer/xmlserializer.h>

#if defined(_MSC_VER)

#include <io.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include "Win32_LocalConfigManagerHelper.h"
#pragma warning(disable:6031) /*systemcalls.h for nits has this warning*/

/* These are needed to load PS infrastructure at runtime on need basis. Once loaded it won't be unloaded until provider is loaded again.*/
HMODULE g_hPSInfraModuleHandle;
MI_Boolean g_hPSInfraModuleHandleInitialized;


#endif


#include "BeginEndLcmOperation.h"

#include "LocalConfigurationManager.h"

typedef struct _LCMTaskNode LCMTaskNode;

struct _LCMTaskNode
{
    ThreadProc task;
    void* params;
    LCMTaskNode * next;
};

static LCMTaskNode * g_TaskHead = NULL;
static pthread_mutex_t g_TaskQueueMutex;
static int g_TaskQueueShutdown = 0;
static int g_TaskQueueExists = 0;

void AddToTaskQueue(LCMTaskNode * node)
{
    LCMTaskNode* current;
    pthread_mutex_lock(&g_TaskQueueMutex);
    if (g_TaskHead == NULL)
    {
	g_TaskHead = node;
    }
    else
    {
	current = g_TaskHead;
	while (current != NULL)
	{
	    if (current->next == NULL)
	    {
		current->next = node;
		break;
	    }
	    else
	    {
		current = current->next;
	    }
	}
    }
    pthread_mutex_unlock(&g_TaskQueueMutex);
}

void TaskQueueLoop()
{
    int shouldShutdown;
    LCMTaskNode * currentTask = NULL;
    
    pthread_mutex_lock(&g_TaskQueueMutex);
    shouldShutdown = g_TaskQueueShutdown;
    pthread_mutex_unlock(&g_TaskQueueMutex);
    
    while (shouldShutdown == 0)
    {
	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskHead != NULL)
	{
	    Thread t;
	    PAL_Uint32 ret;

	    currentTask = g_TaskHead;
	    g_TaskHead = currentTask->next;
	    pthread_mutex_unlock(&g_TaskQueueMutex);

	    Thread_CreateJoinable(&t, currentTask->task, NULL, currentTask->params);
	    Thread_Join(&t, &ret);
	    Thread_Destroy(&t);
	    DSC_free(currentTask);
	}
	else
	{
	    currentTask = NULL;
	    pthread_mutex_unlock(&g_TaskQueueMutex);
	}

	usleep(10000);

	pthread_mutex_lock(&g_TaskQueueMutex);
	shouldShutdown = g_TaskQueueShutdown;
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }

    pthread_mutex_lock(&g_TaskQueueMutex);
    g_TaskQueueShutdown = 0;
    g_TaskHead = NULL;
    g_TaskQueueExists = 0;
    pthread_mutex_unlock(&g_TaskQueueMutex);
}

void ReloadOMI()
{
    system(OMI_RELOAD_COMMAND);
}

MI_Boolean RunningAsRoot()
{
    if (getuid() == 0)
    {
	return MI_TRUE;
    }
    else
    {
	return MI_FALSE;
    }
}

void UnloadFromProvider(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    int taskQueueExists;
    MI_UNREFERENCED_PARAMETER(self);

#if defined(_MSC_VER)
    g_hPSInfraModuleHandleInitialized = MI_FALSE;
    if( g_hPSInfraModuleHandle != NULL)
    {
        FreeLibrary(g_hPSInfraModuleHandle);
        g_hPSInfraModuleHandle = NULL;
    }
#endif    
    
    miResult = UnInitHandler(&cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, miResult);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    pthread_mutex_lock(&g_TaskQueueMutex);
    g_TaskQueueShutdown = 1;
    pthread_mutex_unlock(&g_TaskQueueMutex);

    // Wait until the TaskQueue is complete before allowing unload
    do 
    {
	usleep(10000);

	pthread_mutex_lock(&g_TaskQueueMutex);
	taskQueueExists = g_TaskQueueExists;
	pthread_mutex_unlock(&g_TaskQueueMutex);
    } while (taskQueueExists != 0);

    MI_Context_PostResult(context, MI_RESULT_OK);
}


#if defined(_MSC_VER)

void Invoke_SendConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 bufferIndex = 0;
    HANDLE m_clientThreadToken;
    MI_Boolean force = MI_FALSE;

    if (in->force.exists && in->force.value == MI_TRUE)
    {
        force = MI_TRUE;
    }    
    
    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    GetRealBufferIndex( &(in->ConfigurationData.value), &bufferIndex);

    miResult = CallSetConfiguration(in->ConfigurationData.value.data + bufferIndex, 
        in->ConfigurationData.value.size - bufferIndex, LCM_SETFLAGS_SAVETOPENDINGONLY, force, context, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);

    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    // Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    return;

ExitWithError:
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();    
}

void Invoke_SendConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 bufferIndex = 0;
    HANDLE m_clientThreadToken;
    MI_Boolean force = MI_FALSE;
    // Declarations for measuring time
    MI_Real64 duration;
    ptrdiff_t start, finish;        

    if (in->force.exists && in->force.value == MI_TRUE)
    {      
        force = MI_TRUE;
    }

    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    GetRealBufferIndex( &(in->ConfigurationData.value), &bufferIndex);

    start=CPU_GetTimeStamp();
    miResult = CallSetConfiguration(in->ConfigurationData.value.data + bufferIndex, 
        in->ConfigurationData.value.size - bufferIndex, GetCallSetConfigurationFlags(context), 
        force, context, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);

    // Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context,EMPTY_STRING, ID_LCM_TIMEMESSAGE,  ID_OUTPUT_ITEM_SET,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    // Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    return;

ExitWithError:
    ResetJobId();
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);    
}

void Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* in)
{
    MI_Result miResult = MI_RESULT_OK;
    MI_Instance *cimErrorDetails = NULL;
    MI_InstanceA outInstances = {0};
    MI_Value val;
    MI_Uint32 bufferIndex = 0;    
    MSFT_DSCLocalConfigurationManager_GetConfiguration outputObject;
    HANDLE m_clientThreadToken;
    MI_Uint8A dataValue = {0};
    //Declarations for measuring time
    MI_Real64 duration;
    ptrdiff_t start, finish;
       

    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);    
        ResetJobId();
        return;
    }

    // If the configuration file has not been passed in the parameters        
    if (!in || !in->configurationData.exists)
    {
        // If the current configuration file does not exist, output a corresponding error message and return
        if (File_ExistT(GetCurrentConfigFileName())== -1)
        {
            GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_LCMHELPER_CURRENT_NOTFOUND);
            SetThreadToken(NULL, m_clientThreadToken);
            CloseHandle(m_clientThreadToken);
            goto ExitWithError;
        }
        
        // Read file contents from the current configuration file into dataValue
        miResult = ReadFileContent(GetCurrentConfigFileName(), &dataValue.data, &dataValue.size, &cimErrorDetails);
        if (miResult != MI_RESULT_OK)
        {
            SetThreadToken(NULL, m_clientThreadToken);
            CloseHandle(m_clientThreadToken);
            goto ExitWithError;
        }
    }
    else
    {
        // If a configuration file name is passed in the parameters, read from the passed configuration file.
        GetRealBufferIndex(&(in->configurationData.value), &bufferIndex);  
        dataValue.data = (MI_Uint8*)(in->configurationData.value.data + bufferIndex);
        dataValue.size = in->configurationData.value.size - bufferIndex;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_GetConfiguration_Construct(&outputObject, context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }   

    start=CPU_GetTimeStamp();
    miResult = CallGetConfiguration(dataValue.data, 
        dataValue.size, &outInstances, 
        context, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    val.instancea.data = outInstances.data;
    val.instancea.size = outInstances.size;
    miResult = MI_Context_WriteStreamParameter(context, MI_T("configurations"), &val, MI_INSTANCEA, 0);
    CleanUpInstanceCache(&outInstances);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_WRITEGET_FAILED);
        MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_GetConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_GetConfiguration_Post(&outputObject, context);
    MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTGET_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);
    // Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context,EMPTY_STRING, ID_LCM_TIMEMESSAGE,  ID_OUTPUT_ITEM_GET,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    if ( in && !in->configurationData.exists)
    {
       DSC_free(dataValue.data);
    }

    ResetJobId();

    return;

ExitWithError:
    ResetJobId();
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    if (in && !in->configurationData.exists)
    {
       DSC_free(dataValue.data);
    }
}

void Invoke_ApplyConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration outputObject;
    HANDLE m_clientThreadToken;
    MI_Uint32 taskMode = TASK_AUTO;
    MI_Value value;
    MI_Uint32 flags = 0;
    MI_Instance *metaConfigInstance = NULL;
    MI_Boolean restartOMI = MI_FALSE;

    if (in->force.exists && in->force.value == MI_TRUE)
    {      
        taskMode = TASK_FORCE;
    }

    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = GetMetaConfig((MSFT_DSCMetaConfiguration **)&metaConfigInstance);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_Context_PostResult(context, miResult);
        goto ExitWithError;
    }

    miResult = MI_Instance_GetElement((MI_Instance*)metaConfigInstance, MSFT_DSCMetaConfiguration_RefreshMode, &value, NULL, &flags, NULL);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostResult(context, miResult);
        goto ExitWithError;
    }

    if (flags & MI_FLAG_NULL)
    {
        value.string = METADATA_REFRESHMODE_PUSH;
    }

        // if pending configuration exists
        if (File_ExistT(GetPendingConfigFileName()) != -1)
        {
                if (taskMode == TASK_AUTO)
                {
                        GetCimMIError(MI_RESULT_ALREADY_EXISTS, &cimErrorDetails, ID_LCMHELPER_OLDCONFPENDING_ERROR);
                        goto ExitWithError;
                }
        }
        else
        {
                // no current configuration exists
                if (File_ExistT(GetCurrentConfigFileName()) == -1)
                {
                        if (Tcscasecmp(value.string , METADATA_REFRESHMODE_PUSH) == 0)
                        {
                                GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_LCMHELPER_CURRENT_NOTFOUND);
                                goto ExitWithError;
                        }
                }
        }

    if (Tcscasecmp(value.string , METADATA_REFRESHMODE_PULL) == 0)
    {
                miResult = DoPullServerRefresh(metaConfigInstance, &cimErrorDetails);
                if (miResult != MI_RESULT_OK)
                {
                    SetThreadToken(NULL, m_clientThreadToken);
                    CloseHandle(m_clientThreadToken);
                    MI_Instance_Delete((MI_Instance *)metaConfigInstance);
                    MI_Context_PostCimError(context, cimErrorDetails);
                    MI_Instance_Delete(cimErrorDetails);
                    goto ExitWithError;
                }
    }
    miResult = CallConsistencyEngine(context, TASK_REGULAR, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_ENGINEHELPER_MANUAL_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Construct(&outputObject, context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTAPPLY_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETAPPLY_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Post(&outputObject, context);
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTAPPLY_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }    

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);

    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    // Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    return;

ExitWithError:
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();
}

void Invoke_SendMetaConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 bufferIndex = 0;
    HANDLE m_clientThreadToken;
    MI_Uint32 flags=0;      
    // Declarations for measuring time
    MI_Real64 duration;
    ptrdiff_t start, finish; 


    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    GetRealBufferIndex( &(in->ConfigurationData.value), &bufferIndex);
    flags=GetCallSetConfigurationFlags(context) | LCM_SET_METACONFIG;
    
    start=CPU_GetTimeStamp();
    miResult = CallSetConfiguration(in->ConfigurationData.value.data + bufferIndex, 
        in->ConfigurationData.value.size - bufferIndex, flags, MI_TRUE, context, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);
    // Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context,EMPTY_STRING, ID_LCM_TIMEMESSAGE,  ID_OUTPUT_ITEM_SET,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    // Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    return;

ExitWithError:
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();    
}


void Invoke_GetMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* in)
{
    MI_Result miResult;
        MSFT_DSCMetaConfiguration * metaConfigInstance;
    MI_Instance *cimErrorDetails = NULL;
    HANDLE m_clientThreadToken;
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration outputObject;       
    
    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = GetMetaConfig(&metaConfigInstance);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(MI_RESULT_INVALID_PARAMETER, &cimErrorDetails, ID_LCMHELPER_METASCHEMA_CLONE_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Construct(&outputObject, context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }   

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_SetPtr_MetaConfiguration(&outputObject, (MSFT_DSCMetaConfiguration*)metaConfigInstance);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_WRITEGET_FAILED);
        MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
        MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }   

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
        MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }   

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Post(&outputObject, context);
    MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        EndLcmOperation();
        MI_Context_PostResult(context, miResult);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);
        if (MetaMofCorrupted == MI_TRUE)
        {
                Intlstr pTempStr = Intlstr_Null;
                GetResourceString(ID_LCMHELPER_METAMOFCORRUPTED, &pTempStr);
                MI_Context_WriteWarning(context, pTempStr.str);
                if (pTempStr.str)
                {
                        Intlstr_Free(pTempStr);
                }
                MetaMofCorrupted = MI_FALSE;
        }
    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    return;

ExitWithError:
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();
}

void Invoke_RollBack(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_RollBack* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    HANDLE m_clientThreadToken;
     
    //Declarations for measuring time
    MI_Real64 duration;
    ptrdiff_t start=CPU_GetTimeStamp();
    ptrdiff_t finish;  
    
    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    //Log operational event for restoring configuration
    DSC_EventWriteRestoringConfiguration();
    miResult = CallRestoreConfiguration(GetCallSetConfigurationFlags(context), context, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);

    //Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context,EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_ROLLBACK,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    return;

ExitWithError:
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();
}

void Invoke_TestConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 xCount = 0;    
    MI_Boolean testStatus = MI_FALSE;
    MSFT_DSCLocalConfigurationManager_TestConfiguration outputObject;
    MI_StringA resourceId = {0};
    HANDLE m_clientThreadToken;
    // Declarations for measuring time 
    MI_Real64 duration;
    ptrdiff_t start=CPU_GetTimeStamp();
    ptrdiff_t finish;
    
    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Construct(&outputObject, context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTTEST_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }   

    miResult = CallTestConfiguration(&testStatus, &resourceId, context, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_ResourceId(&outputObject, resourceId.data, resourceId.size);
    for (xCount = 0; xCount < resourceId.size; xCount++)
    {
        DSC_free(resourceId.data[xCount]);
    }

    DSC_free(resourceId.data);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETTEST_FAILED);
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_InDesiredState(&outputObject, testStatus);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETTEST_FAILED);
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETTEST_FAILED);
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Post(&outputObject, context);
    MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTTEST_FAILED);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        CloseHandle(m_clientThreadToken);
        goto ExitWithError;
    }

    CloseHandle(m_clientThreadToken);

    //Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context,EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_TEST, (const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    MI_Context_PostResult(context, MI_RESULT_OK);

    // Debug log
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    return;

ExitWithError:
    EndLcmOperation();
    MI_PostCimError(context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();
}


void Invoke_PerformRequiredConfigurationChecks(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* in)
{
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks outputObject;
    MI_Result miResult = MI_RESULT_OK;
    HANDLE m_clientThreadToken;
    MI_Instance *cimErrorDetails = NULL;
    MSFT_DSCMetaConfiguration *metaConfigInstance = NULL;
    MI_Value value;
    MI_Uint32 flags = 0;

    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = TryBeginLcmOperation(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        goto ExitSimple;
    }

    miResult = GetMetaConfig((MSFT_DSCMetaConfiguration **)&metaConfigInstance);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_Context_PostResult(context, miResult);
        goto ExitSimple;
    }

    if (in->Flags.value == TASK_BOOTSTRAP)
    {
        miResult = RegisterStandardTasks(&cimErrorDetails);
        if (miResult != MI_RESULT_OK)
        {
            SetThreadToken(NULL, m_clientThreadToken);
            CloseHandle(m_clientThreadToken);
            MI_Instance_Delete((MI_Instance *)metaConfigInstance);
            MI_PostCimError(context, cimErrorDetails);
            MI_Instance_Delete(cimErrorDetails);
            goto ExitSimple;
        }
    }

    miResult = MI_Instance_GetElement((MI_Instance*)metaConfigInstance, MSFT_DSCMetaConfiguration_RefreshMode, &value, NULL, &flags, NULL);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostResult(context, miResult);
        goto ExitSimple;
    }

    if (flags & MI_FLAG_NULL)
    {
        value.string = METADATA_REFRESHMODE_PUSH;
    }

    if (Tcscasecmp(value.string , METADATA_REFRESHMODE_PULL) == 0)
    {
        miResult = DoPullServerRefresh(metaConfigInstance, &cimErrorDetails);
        if (miResult != MI_RESULT_OK)
        {
            SetThreadToken(NULL, m_clientThreadToken);
            CloseHandle(m_clientThreadToken);
            MI_Instance_Delete((MI_Instance *)metaConfigInstance);
            MI_Context_PostCimError(context, cimErrorDetails);
            MI_Instance_Delete(cimErrorDetails);
            goto ExitSimple;
        }
    }    

    miResult = RunConsistencyEngine(context, in->Flags.value, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        goto ExitSimple;
    }

    miResult = MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Construct(&outputObject, context);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostResult(context, miResult);
        goto ExitSimple;
    }

    miResult = MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        CloseHandle(m_clientThreadToken);
        MI_Context_PostResult(context, miResult);
        goto ExitSimple;
    }

    miResult = MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Post(&outputObject, context);
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Destruct(&outputObject);
    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        goto ExitSimple;
    }

    CloseHandle(m_clientThreadToken);
    MI_Instance_Delete((MI_Instance *)metaConfigInstance);
    MI_Context_PostResult(context, miResult);

ExitSimple:
    EndLcmOperation();

    // Debug log
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();    
}

void Invoke_StopConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* in)
{
    MSFT_DSCLocalConfigurationManager_StopConfiguration outputObject;
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    HANDLE m_clientThreadToken;  

    if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    miResult = InitHandler(methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        return;
    }

    miResult = RepudicationHelper(context, m_clientThreadToken, __WFUNCTION__, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    if (in->force.exists && in->force.value == MI_TRUE)
    {
        miResult = StopCurrentConfiguration(&cimErrorDetails, TRUE);
    }
    else
    {
        miResult = StopCurrentConfiguration(&cimErrorDetails, FALSE);
    }

    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        ResetJobId();
        return;
    }

    CloseHandle(m_clientThreadToken);

    miResult = MSFT_DSCLocalConfigurationManager_StopConfiguration_Construct(&outputObject, context);
    if (miResult != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, miResult);
        ResetJobId();
        return;
    }

    miResult = MSFT_DSCLocalConfigurationManager_StopConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_StopConfiguration_Destruct(&outputObject);
        MI_Context_PostResult(context, miResult);
        ResetJobId();
        return;
    }

    miResult = MSFT_DSCLocalConfigurationManager_StopConfiguration_Post(&outputObject, context);
    MSFT_DSCLocalConfigurationManager_StopConfiguration_Destruct(&outputObject);
    MI_Context_PostResult(context, miResult);

    // Debug log
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
}


#else



MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_SendConfigurationApply_Internal(void *param)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 bufferIndex = 0;
    // Declarations for measuring time
    MI_Real64 duration;
    ptrdiff_t start, finish; 
    MSFT_DSCLocalConfigurationManager_SendConfigurationApply outputObject;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)param;
    if( args == NULL )
    {
        return 0;
    }
    if( args->data.data == NULL || args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args->data.data);
        PAL_Free(args);
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args->data.data);
        PAL_Free(args);        
        return 0;
    }

    GetRealBufferIndex( &args->data, &bufferIndex);

    start=CPU_GetTimeStamp();
    SetLCMStatusBusy();
    miResult = CallSetConfiguration(args->data.data + bufferIndex, 
        args->data.size - bufferIndex, args->flag, 
        args->force, args->context, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        goto ExitWithError;
    }
    
    miResult = MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        goto ExitWithError;
    } 
    miResult = MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Destruct(&outputObject);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Post(&outputObject, args->context);
    MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Destruct(&outputObject);    

    // Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(args->context,EMPTY_STRING, ID_LCM_TIMEMESSAGE,  ID_OUTPUT_ITEM_SET,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    SetLCMStatusReady();
    MI_Context_PostResult(args->context, MI_RESULT_OK);

    // Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    PAL_Free(args->data.data);
    PAL_Free(args);    
    return 0;

ExitWithError:
    ResetJobId();
    EndLcmOperation();
    SetLCMStatusReady();
    MI_PostCimError(args->context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails); 
    PAL_Free(args->data.data);
    PAL_Free(args);    
    return 0;
}

MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_GetConfiguration_Internal(void *param)
{
    MI_Result miResult = MI_RESULT_OK;
    MI_Instance *cimErrorDetails = NULL;
    MI_InstanceA outInstances = {0};
    MI_Value val;
    MI_Uint32 bufferIndex = 0;    
    MSFT_DSCLocalConfigurationManager_GetConfiguration outputObject;
    MI_Uint8A dataValue = {0};
    //Declarations for measuring time
    MI_Real64 duration;
    ptrdiff_t start, finish;   

    Context_Invoke_Basic *args = (Context_Invoke_Basic*)param;

    if( args == NULL )
    {
        return 0;
    }
    if( (args->dataExist && args->data.data == NULL) || args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }    


    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        if (args->dataExist)
        {
            PAL_Free(args->data.data);
        }

        PAL_Free(args);        
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        if (args->dataExist)
        {
            PAL_Free(args->data.data);
        }

        PAL_Free(args);        
        return 0;
    }

    // If the configuration file has not been passed in the parameters        
    if (!args->dataExist)
    {
        // If the current configuration file does not exist, output a corresponding error message and return
        if (File_ExistT(GetCurrentConfigFileName())== -1)
        {
            GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_LCMHELPER_CURRENT_NOTFOUND);
            goto ExitWithError;
        }
        
        // Read file contents from the current configuration file into dataValue
        miResult = ReadFileContent(GetCurrentConfigFileName(), &dataValue.data, &dataValue.size, &cimErrorDetails);
        if (miResult != MI_RESULT_OK)
        {
            goto ExitWithError;
        }
    }
    else
    {
        // If a configuration file name is passed in the parameters, read from the passed configuration file.
        GetRealBufferIndex((MI_ConstUint8A*)&(args->data.data), &bufferIndex);  
        dataValue.data = (MI_Uint8*)(args->data.data + bufferIndex);
        dataValue.size = args->data.size - bufferIndex;
    }

    miResult = MSFT_DSCLocalConfigurationManager_GetConfiguration_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        goto ExitWithError;
    }   

    start=CPU_GetTimeStamp();
    SetLCMStatusBusy();
    miResult = CallGetConfiguration(dataValue.data, 
        dataValue.size, &outInstances, 
        args->context, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }

    val.instancea.data = outInstances.data;
    val.instancea.size = outInstances.size;
    miResult = MI_Instance_SetElement(&outputObject.__instance, MI_T("configurations"), &val, MI_INSTANCEA, 0);
    CleanUpInstanceCache(&outInstances);    
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }
    miResult = MSFT_DSCLocalConfigurationManager_GetConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }    

    miResult = MSFT_DSCLocalConfigurationManager_GetConfiguration_Post(&outputObject, args->context);
    MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTGET_FAILED);
        goto ExitWithError;
    }
    // Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(args->context,EMPTY_STRING, ID_LCM_TIMEMESSAGE,  ID_OUTPUT_ITEM_GET,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    SetLCMStatusReady();
    MI_Context_PostResult(args->context, MI_RESULT_OK);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    if (!args->dataExist)
    {
       DSC_free(dataValue.data);
    }

    ResetJobId();
    if (args->dataExist)
    {
        PAL_Free(args->data.data);
    }
    PAL_Free(args);    

    return 0;

ExitWithError:
    ResetJobId();
    EndLcmOperation();
    SetLCMStatusReady();
    MI_PostCimError(args->context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    if (!args->dataExist)
    {
       DSC_free(dataValue.data);
    }    
    if (args->dataExist)
    {
        PAL_Free(args->data.data);
    }

    PAL_Free(args);    
    return 0;
}

MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_ApplyConfiguration_Internal(void *param)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration outputObject;    
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)param;

    if( args == NULL )
    {
        return 0;
    }
    if( args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }       

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args); 
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args); 
        return 0;
    }

    miResult = MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTAPPLY_FAILED);
        goto ExitWithError;
    }       

    SetLCMStatusBusy();
    miResult = CallConsistencyEngine(args->context, TASK_REGULAR, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETAPPLY_FAILED);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Post(&outputObject, args->context);
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTAPPLY_FAILED);
        goto ExitWithError;
    }    

    EndLcmOperation();
    SetLCMStatusReady();
    MI_Context_PostResult(args->context, MI_RESULT_OK);

    // Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    PAL_Free(args); 
    return 0;

ExitWithError:
    EndLcmOperation();
    SetLCMStatusReady();
    MI_PostCimError(args->context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();      
    PAL_Free(args); 
    return 0;
}

MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_GetMetaConfiguration_Internal(void *param)
{
    MI_Result miResult;
    MSFT_DSCMetaConfiguration * metaConfigInstance;
    MI_Instance *cimErrorDetails = NULL;
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration outputObject;  
    Context_Invoke_Basic *args = (Context_Invoke_Basic*) param;

    if( args == NULL )
    {
        return 0;
    }
    if( args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }       

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args); 
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args); 
        return 0;
    }

    SetLCMStatusBusy();
    miResult = GetMetaConfig(&metaConfigInstance);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(MI_RESULT_INVALID_PARAMETER, &cimErrorDetails, ID_LCMHELPER_METASCHEMA_CLONE_FAILED);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
        goto ExitWithError;
    }   

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_SetPtr_MetaConfiguration(&outputObject, (MSFT_DSCMetaConfiguration*)metaConfigInstance);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_WRITEGET_FAILED);
        MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
        MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }   

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
        MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }   

    miResult = MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Post(&outputObject, args->context);
    MSFT_DSCMetaConfiguration_Delete(metaConfigInstance);
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        EndLcmOperation();
        MI_Context_PostResult(args->context, miResult);
        ResetJobId();
        PAL_Free(args); 
        return 0;
    }

    EndLcmOperation();
    SetLCMStatusReady();
    MI_Context_PostResult(args->context, MI_RESULT_OK);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    PAL_Free(args); 
    return 0;

ExitWithError:
    EndLcmOperation();
    SetLCMStatusReady();
    MI_PostCimError(args->context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();  
    PAL_Free(args); 
    return 0;
}

MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_RollBack_Internal(void *param)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
     
    //Declarations for measuring time
    MI_Real64 duration;
    ptrdiff_t start=CPU_GetTimeStamp();
    ptrdiff_t finish; 
    Context_Invoke_Basic *args = (Context_Invoke_Basic*) param;

    if( args == NULL )
    {
        return 0;
    }
    if(args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }       

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    //Log operational event for restoring configuration
    DSC_EventWriteRestoringConfiguration();
    SetLCMStatusBusy();
    miResult = CallRestoreConfiguration(args->flag, args->context, &cimErrorDetails); 
    if (miResult != MI_RESULT_OK)
    {
        goto ExitWithError;
    }

    //Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(args->context,EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_ROLLBACK,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    SetLCMStatusReady();
    MI_Context_PostResult(args->context, MI_RESULT_OK);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    PAL_Free(args);
    return 0;

ExitWithError:
    EndLcmOperation();
    SetLCMStatusReady();
    MI_PostCimError(args->context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();
    PAL_Free(args);
    return 0;
          
}

MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_TestConfiguration_Internal(void *param)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 xCount = 0;    
    MI_Boolean testStatus = MI_FALSE;
    MSFT_DSCLocalConfigurationManager_TestConfiguration outputObject;
    MI_StringA resourceId = {0};
    // Declarations for measuring time 
    MI_Real64 duration;
    ptrdiff_t start=CPU_GetTimeStamp();
    ptrdiff_t finish;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*) param;

    if( args == NULL )
    {
        return 0;
    }
    if( args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }       

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTTEST_FAILED);
        goto ExitWithError;
    }   

    SetLCMStatusBusy();
    miResult = CallTestConfiguration(&testStatus, &resourceId, args->context, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_ResourceId(&outputObject, (const MI_Char**)resourceId.data, resourceId.size);
    for (xCount = 0; xCount < resourceId.size; xCount++)
    {
        DSC_free(resourceId.data[xCount]);
    }

    DSC_free(resourceId.data);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETTEST_FAILED);
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_InDesiredState(&outputObject, testStatus);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETTEST_FAILED);
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETTEST_FAILED);
        MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
        goto ExitWithError;
    }

    miResult = MSFT_DSCLocalConfigurationManager_TestConfiguration_Post(&outputObject, args->context);
    MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTTEST_FAILED);
        goto ExitWithError;
    }

    //Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(args->context,EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_TEST, (const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    SetLCMStatusReady();
    MI_Context_PostResult(args->context, MI_RESULT_OK);

    // Debug log
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    PAL_Free(args);
    return 0;

ExitWithError:
    EndLcmOperation();
    SetLCMStatusReady();
    MI_PostCimError(args->context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    ResetJobId();  
    PAL_Free(args);
    return 0;
}

MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_PerformRequiredConfigurationChecks_Internal(void *param)
{
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks outputObject;
    MI_Result miResult = MI_RESULT_OK;
    MI_Instance *cimErrorDetails = NULL;
    MSFT_DSCMetaConfiguration *metaConfigInstance = NULL;
    MI_Value value;
    MI_Uint32 flags = 0;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*) param;

    if( args == NULL )
    {
        return 0;
    }
    if(  args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }       

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    SetLCMStatusBusy();
    miResult = GetMetaConfig((MSFT_DSCMetaConfiguration **)&metaConfigInstance);
    if (miResult != MI_RESULT_OK)
    {
        MI_Context_PostResult(args->context, miResult);
        goto ExitSimple;
    }

    if (args->flag== TASK_BOOTSTRAP)
    {
        miResult = RegisterStandardTasks(&cimErrorDetails);
        if (miResult != MI_RESULT_OK)
        {
            MI_Instance_Delete((MI_Instance *)metaConfigInstance);
            MI_PostCimError(args->context, cimErrorDetails);
            MI_Instance_Delete(cimErrorDetails);
            goto ExitSimple;
        }
    }

    miResult = MI_Instance_GetElement((MI_Instance*)metaConfigInstance, MSFT_DSCMetaConfiguration_RefreshMode, &value, NULL, &flags, NULL);
    if (miResult != MI_RESULT_OK)
    {
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostResult(args->context, miResult);
        goto ExitSimple;
    }

    if (flags & MI_FLAG_NULL)
    {
        value.string = METADATA_REFRESHMODE_PUSH;
    }

    if (Tcscasecmp(value.string , METADATA_REFRESHMODE_PULL) == 0)
    {
        miResult = DoPullServerRefresh(metaConfigInstance, &cimErrorDetails);
        if (miResult != MI_RESULT_OK)
        {
            MI_Instance_Delete((MI_Instance *)metaConfigInstance);
            MI_Context_PostCimError(args->context, cimErrorDetails);
            MI_Instance_Delete(cimErrorDetails);
            goto ExitSimple;
        }
    }    

    miResult = RunConsistencyEngine(args->context, args->flag, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        goto ExitSimple;
    }

    miResult = MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostResult(args->context, miResult);
        goto ExitSimple;
    }

    miResult = MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Destruct(&outputObject);
        MI_Instance_Delete((MI_Instance *)metaConfigInstance);
        MI_Context_PostResult(args->context, miResult);
        goto ExitSimple;
    }

    miResult = MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Post(&outputObject, args->context);
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Destruct(&outputObject);
    MI_Instance_Delete((MI_Instance *)metaConfigInstance);
    MI_Context_PostResult(args->context, miResult);

ExitSimple:
    EndLcmOperation();
    SetLCMStatusReady();
    // Debug log
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();     
    PAL_Free(args);
    return 0;
}

MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_StopConfiguration_Internal(void *param)
{
    MSFT_DSCLocalConfigurationManager_StopConfiguration outputObject;
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*) param;

    if( args == NULL )
    {
        return 0;
    }
    if( args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }       

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    if (args->force== MI_TRUE)
    {
        miResult = StopCurrentConfiguration(&cimErrorDetails, TRUE);
    }
    else
    {
        miResult = StopCurrentConfiguration(&cimErrorDetails, FALSE);
    }

    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    miResult = MSFT_DSCLocalConfigurationManager_StopConfiguration_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        MI_Context_PostResult(args->context, miResult);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    miResult = MSFT_DSCLocalConfigurationManager_StopConfiguration_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_StopConfiguration_Destruct(&outputObject);
        MI_Context_PostResult(args->context, miResult);
        ResetJobId();
        PAL_Free(args);
        return 0;
    }

    SetLCMStatusBusy();
    miResult = MSFT_DSCLocalConfigurationManager_StopConfiguration_Post(&outputObject, args->context);
    MSFT_DSCLocalConfigurationManager_StopConfiguration_Destruct(&outputObject);
    MI_Context_PostResult(args->context, miResult);

    SetLCMStatusReady();
    // Debug log
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    ResetJobId();
    PAL_Free(args);
    return 0;
}


void Invoke_SendConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif

    
    MI_Uint8 *dataValue = NULL;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }
    dataValue = (MI_Uint8*)DSC_malloc( sizeof(MI_Uint8) * in->ConfigurationData.value.size, NitsHere());
    if( args == NULL)
    {
        PAL_Free(args);
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }    
    memcpy(dataValue, in->ConfigurationData.value.data, in->ConfigurationData.value.size);
    args->context = context;
    args->methodName = methodName;
    args->force = MI_FALSE;
    args->data.data = dataValue;
    args->data.size = in->ConfigurationData.value.size;
    args->flag = LCM_SETFLAGS_SAVETOPENDINGONLY;
    if (in->force.exists && in->force.value == MI_TRUE)
    {      
        args->force = MI_TRUE;
    }    

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_SendConfigurationApply_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}


void Invoke_SendConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    MI_Uint8 *dataValue = NULL;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }
    dataValue = (MI_Uint8*)DSC_malloc( sizeof(MI_Uint8) * in->ConfigurationData.value.size, NitsHere());
    if( args == NULL)
    {
        PAL_Free(args);
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }    
    memcpy(dataValue, in->ConfigurationData.value.data, in->ConfigurationData.value.size);
    args->context = context;
    args->methodName = methodName;
    args->force = MI_FALSE;
    args->data.data = dataValue;
    args->data.size = in->ConfigurationData.value.size;
    args->flag = GetCallSetConfigurationFlags(context);
    if (in->force.exists && in->force.value == MI_TRUE)
    {      
        args->force = MI_TRUE;
    }    

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_SendConfigurationApply_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}



void Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    MI_Uint8 *dataValue = NULL;
    MI_Uint32 dataSize = 0;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }
    args->dataExist = MI_TRUE;

    // If the configuration file has not been passed in the parameters        
    if (!in || !in->configurationData.exists)
    {
        args->dataExist = MI_FALSE;
    }  
    else
    {
        dataValue = (MI_Uint8*)DSC_malloc( sizeof(MI_Uint8) * in->configurationData.value.size, NitsHere());
        if( args == NULL)
        {
            PAL_Free(args);
            miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
            MI_PostCimError(context, cimErrorDetails);
            MI_Instance_Delete(cimErrorDetails);
            return;
        }    
        memcpy(dataValue, in->configurationData.value.data, in->configurationData.value.size);
        dataSize = in->configurationData.value.size;
    }
    args->context = context;
    args->methodName = methodName;
    args->data.data = dataValue;
    args->data.size = dataSize; 

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_GetConfiguration_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}


void Invoke_ApplyConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }  
    args->context = context;
    args->methodName = methodName;   

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_ApplyConfiguration_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}


void Invoke_SendMetaConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    MI_Uint8 *dataValue = NULL;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }
    dataValue = (MI_Uint8*)DSC_malloc( sizeof(MI_Uint8) * in->ConfigurationData.value.size, NitsHere());
    if( args == NULL)
    {
        PAL_Free(args);
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }    
    memcpy(dataValue, in->ConfigurationData.value.data, in->ConfigurationData.value.size);
    args->context = context;
    args->methodName = methodName;
    args->force = MI_TRUE;
    args->data.data = dataValue;
    args->data.size = in->ConfigurationData.value.size;
    args->flag = GetCallSetConfigurationFlags(context) | LCM_SET_METACONFIG;  

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_SendConfigurationApply_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}


void Invoke_GetMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }  
    args->context = context;
    args->methodName = methodName;   

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_GetMetaConfiguration_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}

void Invoke_RollBack(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_RollBack* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }  
    args->context = context;
    args->methodName = methodName;  
    args->flag = GetCallSetConfigurationFlags(context);

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_RollBack_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}

void Invoke_TestConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }  
    args->context = context;
    args->methodName = methodName;

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_TestConfiguration_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}


void Invoke_PerformRequiredConfigurationChecks(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }  
    args->context = context;
    args->methodName = methodName; 
    args->flag = TASK_REGULAR;
    if( in && in->Flags.exists)
        args->flag = in->Flags.value;

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_PerformRequiredConfigurationChecks_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}

void Invoke_StopConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }  
    args->context = context;
    args->methodName = methodName;   
    args->force = MI_FALSE;
    if( in )
        args->force = in->force.exists ? in->force.value : MI_FALSE;

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_StopConfiguration_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}


MI_EXTERN_C PAL_Uint32 THREAD_API Invoke_PerformInventory_Internal(void *param)
{
    MI_Result miResult = MI_RESULT_OK;
    MI_Instance *cimErrorDetails = NULL;
    MI_InstanceA outInstances;
    MI_Value val;
    MI_Uint32 bufferIndex = 0;    
    MSFT_DSCLocalConfigurationManager_PerformInventory outputObject;
    MI_Uint8A dataValue = {0};
    MI_Real64 duration;
    ptrdiff_t start, finish;   
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)param;
    MI_Char * InMOF;

    if( args == NULL )
    {
        return 0;
    }
    if( args->methodName == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }   
    if (args->stringdata == NULL)
    {
        MI_Context_PostResult(args->context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }

    miResult = InitHandler(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();

        PAL_Free(args);        
        return 0;
    }

    miResult = TryBeginLcmOperation(args->methodName, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MI_PostCimError(args->context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        ResetJobId();
        PAL_Free(args);        
        return 0;
    }

    miResult = MSFT_DSCLocalConfigurationManager_PerformInventory_Construct(&outputObject, args->context);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        goto ExitWithError;
    }

    start=CPU_GetTimeStamp();
    SetLCMStatusBusy();

    InMOF = (MI_Char*) args->stringdata;

    miResult = CallPerformInventory(InMOF, &outInstances, 
        args->context, &cimErrorDetails);
    if (miResult != MI_RESULT_OK)
    {
        MSFT_DSCLocalConfigurationManager_PerformInventory_Destruct(&outputObject);
        goto ExitWithError;
    }

    CleanUpInstanceCache(&outInstances);    
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_INVENTORY_FAILED);
        MSFT_DSCLocalConfigurationManager_PerformInventory_Destruct(&outputObject);
        goto ExitWithError;
    }
    miResult = MSFT_DSCLocalConfigurationManager_PerformInventory_Set_MIReturn(&outputObject, 0);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_INVENTORY_FAILED);
        MSFT_DSCLocalConfigurationManager_PerformInventory_Destruct(&outputObject);
        goto ExitWithError;
    }    

    miResult = MSFT_DSCLocalConfigurationManager_PerformInventory_Post(&outputObject, args->context);
    MSFT_DSCLocalConfigurationManager_PerformInventory_Destruct(&outputObject);
    if (miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTINVENTORY_FAILED);
        goto ExitWithError;
    }
    // Stop the clock and measure time taken for this operation
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(args->context,EMPTY_STRING, ID_LCM_TIMEMESSAGE,  ID_OUTPUT_ITEM_INVENTORY,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    EndLcmOperation();
    SetLCMStatusReady();
    MI_Context_PostResult(args->context, MI_RESULT_OK);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);

    ResetJobId();
    PAL_Free(args->stringdata);
    PAL_Free(args);    

    return 0;

ExitWithError:
    ResetJobId();
    EndLcmOperation();
    SetLCMStatusReady();
    MI_PostCimError(args->context, cimErrorDetails);
    MI_Instance_Delete(cimErrorDetails);
    PAL_Free(args->stringdata);
    PAL_Free(args);    
    return 0;
}


void Invoke_PerformInventory(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventory* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;
    MI_Char * InMOF;

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    MI_Uint8 *dataValue = NULL;
    MI_Uint32 dataSize = 0;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    InMOF = (MI_Char*) DSC_malloc ( sizeof(MI_Char) * 1, NitsHere());

    InMOF[0] = '\0';

    args->dataExist = MI_TRUE;
    args->stringdata = InMOF;
    args->context = context;
    args->methodName = methodName;

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_PerformInventory_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);

	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}

void Invoke_PerformInventoryOOB(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* in)
{
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult;
    MI_Char * InMOF;
    size_t length;

    if (in->InventoryMOFPath.exists == MI_FALSE || in->InventoryMOFPath.value == NULL)
    {
	MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return 0;
    }

#if defined(BUILD_OMS)
    if (RunningAsRoot() == MI_TRUE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#else
    if (RunningAsRoot() == MI_FALSE)
    {
	miResult = GetCimMIError(MI_RESULT_FAILED, &cimErrorDetails, ID_CANNOT_RUN_DSC_AS_NONROOT);
	MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
	return;
    }
#endif
    
    MI_Uint8 *dataValue = NULL;
    MI_Uint32 dataSize = 0;
    Context_Invoke_Basic *args = (Context_Invoke_Basic*)DSC_malloc( sizeof(Context_Invoke_Basic), NitsHere());
    if( args == NULL)
    {
        miResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    length = strlen(in->InventoryMOFPath.value);
    InMOF = (MI_Char*) DSC_malloc ( sizeof(MI_Char) * (length + 1), NitsHere());

    memcpy(InMOF, in->InventoryMOFPath.value, length);
    InMOF[length] = '\0';

    args->dataExist = MI_TRUE;
    args->stringdata = InMOF;
    args->context = context;
    args->methodName = methodName;

    {
	LCMTaskNode * newNode = (LCMTaskNode*)DSC_malloc(sizeof(LCMTaskNode), NitsHere());
	newNode->task = Invoke_PerformInventory_Internal;
	newNode->params = args;
	newNode->next = NULL;
	AddToTaskQueue(newNode);
	
	pthread_mutex_lock(&g_TaskQueueMutex);
	if (g_TaskQueueExists == 0)
	{
	    Thread_CreateDetached(TaskQueueLoop, NULL, NULL);
	    g_TaskQueueExists = 1;
	}
	pthread_mutex_unlock(&g_TaskQueueMutex);
    }
}

#endif


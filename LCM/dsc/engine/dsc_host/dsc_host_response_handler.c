#include "dsc_system_calls.h"
#include "EngineHelper.h"
#include "Resources_LCM.h"
#include "LocalConfigManagerHelper.h"
#include "ComposableUnitWrapper.h"
#include "pal/lock.h"
#include "Win32_EngineHelper.h"
#include "Arbiter.h"
#include "ArbiterHelper.h"
#include "instance.h"
#include "EngineHelperInternal.h"
#include "pal/strings.h"
#include "JsonSerializer.h"
#include "DscWorkerResponseHandler.h"
#include "MIInstanceArrayHelper.h"
#include "DscHostOutputUtility.h"
#include "DSCHostCommon.h"
#include "DSCLibrary.h"
#include "DscWorkerHelper.h"
#include "DscLibraryUtility.h"

#define TOKENIZED_MESSAGE_PADDING 50

MI_Result MI_CALL DscWorker_PostResult(
    _In_ void* context,
    MI_Result result,
    _In_opt_ const MI_Instance *error)
{
    DSCHostCallbackData *data = (DSCHostCallbackData*)context;
    MI_Instance *cimErrorDetails = NULL;
    if( error)
    {
        MI_Char *serializedString = NULL;
        MI_Uint32 serializedStringLength  = 0;  
        MI_Result r = AddMIInstance((MI_Instance*)error, &(data->errors), &(data->errorsCapacity));
        if( r != MI_RESULT_OK)
        {
            data->opertionResult = r;
        }
        else
        {
            if(SerializeDscInstances(&data->errors, &serializedString, &serializedStringLength, MI_FALSE, MI_FALSE) == MI_RESULT_OK)
            {
                SaveDataOnDiskWithNewLine(data->errFilePath, serializedString, &cimErrorDetails);
                DSC_free(serializedString);
            }   
            else
            {
                data->opertionResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            } 
        }
    }
    else if( result != MI_RESULT_OK)
    {
        data->opertionResult = result;
    }
    else
    {
        MI_Char *serializedString = NULL;
        MI_Uint32 serializedStringLength  = 0; 
        if(SerializeDscInstances(&data->streamedInstances, &serializedString, &serializedStringLength, MI_FALSE, MI_FALSE) == MI_RESULT_OK)
        {
            SaveDataOnDiskWithNewLine(data->jsonOutFilePath, serializedString, &cimErrorDetails);
            DSC_free(serializedString);
        }
    }
    return MI_RESULT_OK;
}

MI_Result MI_CALL DscWorker_PostInstance(
    _In_ void* context,
    _In_ const MI_Instance* instance)
{
	DSCHostCallbackData *data = (DSCHostCallbackData*)context;
	MI_Result result = MI_RESULT_OK;
	if (instance)
	{
		MI_Instance* instanceLocal = (MI_Instance*)instance;
		result = AddMIInstance(instanceLocal, &(data->streamedInstances), &(data->streamedInstancesCapacity));
		if (result != MI_RESULT_OK)
		{
			data->opertionResult = result;
			return result;
		}
	}

    return MI_RESULT_OK;
}

MI_Result MI_CALL DscWorker_WriteMessage(
    _In_ void* context,
    MI_Uint32 channel,
    _In_z_ const MI_Char* message)
{
    // No need to handle stream messages, they are already being written in log file by LCM engine.
    return MI_RESULT_OK;
}

MI_Result MI_CALL DscWorker_WriteProgress(
    _In_ void* context,
    _In_z_ const MI_Char* activity,
    _In_z_ const MI_Char* currentOperation,
    _In_z_ const MI_Char* statusDescription,
    MI_Uint32 percentComplete,
    MI_Uint32 secondsRemaining)
{
    return MI_RESULT_OK;
}


MI_Result MI_CALL DscWorker_WriteStreamParameter(
    _In_ void* context,
    _In_z_ const MI_Char* name,
    _In_ const MI_Value* value,
    _In_ MI_Type type,
    _In_ MI_Uint32 flags)
{
    DSCHostCallbackData *data = (DSCHostCallbackData*)context;
    MI_Result result = MI_RESULT_OK;
    if(type == MI_INSTANCE)
    {
        MI_Instance *instance = value->instance;
        if( result != MI_RESULT_OK)
        {
            return result;
        }
        result = AddMIInstance(instance, &(data->streamedInstances), &(data->streamedInstancesCapacity));
        if( result != MI_RESULT_OK)
        {
            data->opertionResult = result;
            return result;
        }
    }
    else if(type == MI_INSTANCEA)
    {
        MI_Uint32 xCount = 0;
        MI_InstanceA instanceA = value->instancea;
        for(xCount = 0; xCount < instanceA.size; xCount++)
        {
            if( result != MI_RESULT_OK)
            {
                return result;
            }    
            result = AddMIInstance((MI_Instance*)instanceA.data[xCount], &(data->streamedInstances), &(data->streamedInstancesCapacity));
            if( result != MI_RESULT_OK)
            {
                data->opertionResult = result;
                return result;
            }            
        }
    }
    return MI_RESULT_OK;
}

MI_Result MI_CALL DscWorker_WriteError(
    _In_ void* context,
    _In_ const MI_Instance *error,
    _Out_ MI_Boolean *shouldContinue)
{
    MI_Result result = MI_RESULT_OK;
    DSCHostCallbackData *data = (DSCHostCallbackData*)context;
    *shouldContinue = MI_FALSE;  
    if( error)
    {
        result = AddMIInstance((MI_Instance*)error, &(data->errors), &(data->errorsCapacity));
        if( result != MI_RESULT_OK)
        {
            data->opertionResult = result;
            return result;
        }        
        
    }    
    return result;
}

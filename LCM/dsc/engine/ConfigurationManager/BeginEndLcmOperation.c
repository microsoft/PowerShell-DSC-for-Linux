
/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
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

#include "BeginEndLcmOperation.h"
extern Sem g_h_ConfigurationStoppedEvent;

//
// global variable used by TryBeginLcaOperation and EndLcaOperation
//
 volatile ptrdiff_t g_activeOperationMethodName = 0;

/// <summary>
/// Try begin general method if another method is not running currently. General methods don't include StopConfiguration
/// </summary>
MI_Result TryBeginLcmOperation(
    _In_z_ const MI_Char* methodName,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Char* originalMethodName;
    int waitResult = 0;

    *cimErrorDetails = NULL;
    originalMethodName = (MI_Char*)Atomic_CompareAndSwap(&g_activeOperationMethodName, (ptrdiff_t) NULL, (ptrdiff_t)methodName);

    if (originalMethodName != NULL)
	{
		// We silently let GetMetaConfiguration to go if the active operation is not SetMetaConfiguration
		if (Tcscasecmp(originalMethodName, MSFT_DSCLocalConfigManager_SendMetaConfigurationApply) == 0
			|| Tcscasecmp(methodName, MSFT_DSCLocalConfigManager_GetMetaConfiguration) != 0)
		{
			return GetCimMIError3Params(MI_RESULT_FAILED, cimErrorDetails, ID_LCM_MULTIPLE_METHOD_REQUEST, methodName, originalMethodName, methodName);
		}
	}
    waitResult = Sem_TimedWait(&g_h_ConfigurationStoppedEvent, (int)0); //Ignore the result
    return MI_RESULT_OK;
}

/// <summary>
/// End the operation of the method.
/// </summar>
void EndLcmOperation()
{
    int waitResult = 0;
    Atomic_Swap(&g_activeOperationMethodName, (ptrdiff_t)NULL);
    waitResult = Sem_Post(&g_h_ConfigurationStoppedEvent, 1); //Ignore the result
}


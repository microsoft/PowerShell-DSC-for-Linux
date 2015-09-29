
/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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


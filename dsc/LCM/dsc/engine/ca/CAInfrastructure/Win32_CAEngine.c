/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "DSC_Systemcalls.h"
#include "EngineHelper.h"
#include "ModuleHandler.h"
#include "ModuleHandlerInternal.h"
#include "ModuleValidator.h"
#include "EngineHelper.h"
#include "LocalConfigManagerHelperForCA.h"
#include "mi.h"
#include "CAEngine.h"
#include "CAEngineInternal.h"
#include "CACrypto.h"
#include "CAValidate.h"
#include "..\CALogInfrastructure\CALog.h"

#include "Resources_LCM.h"
#include "EventWrapper.h"

#include "Win32_EngineHelper.h"

MI_Result Exec_PSProvider(_In_ ProviderCallbackContext *provContext,
                          _In_ MI_Application *miApp,
                          _In_ MI_Instance *instance,
                          _In_ const MI_Instance *regInstance,
                          _In_ MI_Uint32 flags,
                          _Inout_ MI_Uint32 *resultStatus,
                          _Inout_ MI_Boolean* canceled,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Boolean testMIResult = MI_FALSE;
    MI_Real64 duration;
    ptrdiff_t start,finish;

    DSC_EventWriteMessageExecutingPS(instance->classDecl->name,provContext->resourceId);

    //Debug Log 
    DSC_EventWriteEngineMethodParameters(__WFUNCTION__,
                                        instance->classDecl->name,
                                        provContext->resourceId,
                                        flags,
                                        provContext->lcmProviderContext->executionMode,
                                        regInstance->nameSpace);

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    *canceled = MI_FALSE;
    if (g_CancelConfiguration)
    {
        *canceled = MI_TRUE;
        return MI_RESULT_FAILED;
    }

    //Start timer for test
    start=CPU_GetTimeStamp();
    
    //Output a message to start test
    SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_TEST,provContext->lcmProviderContext);        
    LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);   

    r = PS_Test(provContext, instance, regInstance, resultStatus, &testMIResult, extendedError);
    //Stop the timer for test
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_TEST,provContext->lcmProviderContext);
    LogCAMessageTime(provContext->lcmProviderContext, ID_CA_TEST_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);
       
    if (r != MI_RESULT_OK)
    {
        return r;
    }

    /* Skip rest of the operation if we were asked just to test.*/
    if (flags & LCM_EXECUTE_TESTONLY )
    {
        if (testMIResult == MI_TRUE)
            *resultStatus = 1;
        else
            *resultStatus = 0;
        return r;
    }

    if (testMIResult == MI_TRUE)
    {
        SetMessageInContext(ID_OUTPUT_OPERATION_SKIP,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
        LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
        return MI_RESULT_OK;
    }

    if (g_CancelConfiguration)
    {
        *canceled = MI_TRUE;
        return MI_RESULT_FAILED;
    }

    //Start timer for set
    start=CPU_GetTimeStamp();
    SetMessageInContext(ID_OUTPUT_OPERATION_START,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
    LogCAMessage(provContext->lcmProviderContext, ID_OUTPUT_EMPTYSTRING, provContext->resourceId);
    r = PS_Set(provContext, instance, regInstance, resultStatus, extendedError);
    //Stop timer for set
    finish=CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_SET,provContext->lcmProviderContext);
    LogCAMessageTime(provContext->lcmProviderContext, ID_CA_SET_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);

    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    return r;
}


MI_Result Get_PSProvider(_In_ ProviderCallbackContext *provContext,
                         _In_ MI_Application *miApp,
                         _In_ MI_Instance *instance,
                         _In_ const MI_Instance *regInstance,
                         _Outptr_result_maybenull_ MI_Instance **outputInstance,
                         _Outptr_result_maybenull_ MI_Instance **extendedError)

{
    MI_Result r = MI_RESULT_OK;
    MI_Real64 duration;
    ptrdiff_t start,finish;
    DSC_EventWriteMessagePsGet(instance->classDecl->name,provContext->resourceId);
     //Debug Log 
        DSC_EventWriteEngineMethodParameters(__WFUNCTION__,
                                        instance->classDecl->name,
                                        provContext->resourceId,
                                        0,//Flags are not present
                                        provContext->lcmProviderContext->executionMode,
                                        regInstance->nameSpace);
    
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    // If the input MI_Instance is a MSFT_LogResource then return the instance as a result of Get.
    if(Tcscasecmp(instance->classDecl->name, LOGRESOURCE_CLASSNAME) == 0 )
    {       
        MI_Instance *clonedInstance =NULL; 

        r = DSC_MI_Instance_Clone(instance, &clonedInstance);

        *outputInstance = clonedInstance;
    }
    else
    {
        //Start timer for get
        start=CPU_GetTimeStamp();
        r = PS_Get(provContext, instance, regInstance, outputInstance, extendedError);
        if( r != MI_RESULT_OK)
        {
            return r;
        }
        //Stop the clock and calculate time taken
        finish=CPU_GetTimeStamp();
        duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
        SetMessageInContext(ID_OUTPUT_OPERATION_END,ID_OUTPUT_ITEM_GET,provContext->lcmProviderContext);
        LogCAMessageTime(provContext->lcmProviderContext, ID_CA_GET_TIMEMESSAGE, (const MI_Real64)duration,provContext->resourceId);
    }
    //Debug Log 
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    return r;
}

MI_Result MI_CALL Pull_GetConfiguration(_In_ LCMProviderContext *lcmContext,
                                _In_ MI_Instance *metaConfig,
                                _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    r = PS_Pull_GetConfiguration_ManagedPlugin((void*)lcmContext, metaConfig, mofFileName, result, getActionStatusCode, extendedError,g_ConfigurationDetails.jobGuidString);
    return r;
}

MI_Result MI_CALL Pull_GetAction(_In_ LCMProviderContext *lcmContext,
                                _In_ MI_Instance *metaConfig,
                                _In_z_ const MI_Char *checkSum,
                                _In_ MI_Boolean complianceStatus,
                                _In_ MI_Uint32 lastGetActionStatusCode,
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    r = PS_Pull_GetAction_ManagedPlugin((void*)lcmContext, metaConfig, checkSum, complianceStatus, lastGetActionStatusCode, result, getActionStatusCode, extendedError,
        g_ConfigurationDetails.jobGuidString);
    return r;    
}
MI_Result StopCurrentPSProviderConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError)
{
    return PS_StopCurrentPSConfiguration(extendedError);
}

MI_Result MI_CALL Pull_GetModules(_In_ LCMProviderContext *lcmContext,
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_  MI_Char* downloadLocation,
                                                      _In_z_  MI_Char* mofFileName,
                                                      _In_ MI_Boolean allowModuleOverwrite,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    r = PS_Pull_GetModules_ManagedPlugin((void*)lcmContext, metaConfig, downloadLocation, mofFileName, allowModuleOverwrite, getActionStatusCode, extendedError,g_ConfigurationDetails.jobGuidString);
    return r;
}



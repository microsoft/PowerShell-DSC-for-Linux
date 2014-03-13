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

#include <MI.h>
#include <stdlib.h>
#include "DSC_Systemcalls.h"
#include "EngineHelperInternal.h"

#define PerformRequiredConfigurationChecks_PARAMETER_NAME MI_T("Flags")
#define MSFT_DSCLocalConfigManager_CLASSNAME MI_T("MSFT_DSCLocalConfigurationManager")
#if defined(_MSC_VER)
#define DSCENGINE_NAMESPACE MI_T("root\\microsoft\\windows\\desiredstateconfiguration")
#else
#define DSCENGINE_NAMESPACE MI_T("/dsc")
#endif

int main(int argc, char *argv[])
{
    MI_Application miApp = MI_APPLICATION_NULL;
    MI_Session miSess = MI_SESSION_NULL;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    const MI_Instance *result;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint32 argValue = TASK_REGULAR; //

    if( argc >= 2 )
    {
        // the argument is the value of the parameter passed to function PerformRequiredConfigurationChecks
        argValue = atoi(argv[1]);
        if( argValue == 0 || !(argValue == TASK_REGULAR || argValue== TASK_REBOOT || argValue == TASK_BOOTSTRAP))
            argValue = TASK_REGULAR;
    }
    
    r = DSC_MI_Application_Initialize(0, NULL, NULL, &miApp);   
    if( r != MI_RESULT_OK)
    { 
        return r;
    }     

    r = DSC_MI_Application_NewSession(&miApp, NULL, NULL, NULL, NULL, NULL, &miSess);
    if (r != MI_RESULT_OK)
    {
        MI_Application_Close(&miApp);
        return r;
    }    
    r = DSC_MI_Application_NewInstance(&miApp, MI_T("__Parameter"), NULL, &parameter);
    if (r != MI_RESULT_OK)
    {
        MI_Session_Close(&miSess, NULL, NULL);
        MI_Application_Close(&miApp);
        return r;
    }     
    value.uint32 = TASK_REGULAR;
    r = DSC_MI_Instance_AddElement(parameter, PerformRequiredConfigurationChecks_PARAMETER_NAME, &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
    {
        MI_Instance_Delete(parameter);
        MI_Session_Close(&miSess, NULL, NULL);
        MI_Application_Close(&miApp);
        return r;
    }    

    MI_Session_Invoke(&miSess, 0, 0, DSCENGINE_NAMESPACE, MSFT_DSCLocalConfigManager_CLASSNAME, MSFT_DSCLocalConfigManager_PerformRequiredConfigurationChecks, 
                    NULL, parameter, NULL, &miOperation);
    r = MI_Operation_GetInstance(&miOperation, &result, &moreResults, &resultCode, &errorMessage, (const MI_Instance **)&cimErrorDetails);
    if (resultCode != MI_RESULT_OK)
    {
        //write error message
        r = MI_RESULT_FAILED;
    }   
    // Free resources
    MI_Instance_Delete(parameter);
    MI_Operation_Close(&miOperation);
    MI_Session_Close(&miSess, NULL, NULL);
    MI_Application_Close(&miApp);    
    return r;
}

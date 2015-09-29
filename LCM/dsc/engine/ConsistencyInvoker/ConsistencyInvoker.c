/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
#define DSCENGINE_NAMESPACE MI_T("root/Microsoft/Windows/DesiredStateConfiguration")
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
        argValue = strtoul(argv[1], NULL, 10);
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

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "dsc_sal.h"
//#include <common/linux/sal.h>
#include "DSC_Systemcalls.h"
#include "Resources_LCM.h"
#include "EngineHelper.h"
#include "dsc_host.h"
#include "dsc_operations.h"
#include "dsc_library.h"
#include "lcm/strings.h"
// #include "dsc_operation_context.h"


MI_Result GetDSCHostVersion(_In_z_ MI_Char* version, _In_ size_t length)
{
    if(Stprintf(version, length, MI_T("Version : %d.%d.%04d"), MajorVersion, MinorVersion, BuildVersion) < 0)
        return MI_RESULT_FAILED;
    else
        return MI_RESULT_OK;
}

void PrintVersion()
{
    MI_Char versionInfo[DSCHOST_VERSION_BUFF_SIZE];
    GetDSCHostVersion(versionInfo, DSCHOST_VERSION_BUFF_SIZE);
    Tprintf(versionInfo);
}

void PrintHelp()
{
    Tprintf(MI_T("Usage:\n"));
    Tprintf(MI_T("dsc_host [--help] [--version]\n"));
    Tprintf(MI_T("dsc_host <Output Folder Path> <Operation> [Operation Arguments] \n"));
    Tprintf(MI_T("\n"));
    Tprintf(MI_T("Supported Operation values are:\n"));
    Tprintf(MI_T("  GetConfiguration [Configuration Document Path]\n"));
    Tprintf(MI_T("  TestConfiguration\n"));
    Tprintf(MI_T("\n"));
    Tprintf(MI_T("Example:\n"));
    Tprintf(MI_T("dsc_host /tmp/GetAuditPolicy GetConfiguration ./GetAuditPolicy.mof \n"));
    Tprintf(MI_T("dsc_host /tmp/GetAuditPolicy TestConfiguration\n"));
    Tprintf(MI_T("\n"));
}

int main(int argc, char *argv[])
{
    MI_Instance *extended_error = NULL;
    MI_Result result = MI_RESULT_OK;
    DscSupportedOperation current_operation = DscSupportedOperation_NOP;
    // DSC_Operation_Context *context = NULL;
    JSON_Value *operation_result_root_value = NULL;

    // Check the user that has invoked the operation: root for DIY and omsagent for OMS

    if(argc < 3)
    {
        if(argc > 1 && 0 == Tcscasecmp(argv[1], MI_T("--version")))
        {
            PrintVersion();
        }
        else
        {
            PrintHelp();
        }
        return result;
    }

    // Checking for operation
    if(Tcscasecmp(argv[2], MI_T("GetConfiguration")) == 0 )
    {
        current_operation = DscSupportedOperation_GetConfiguration;
    } 
    else
    if(Tcscasecmp(argv[2], MI_T("TestConfiguration")) == 0 )
    {
        current_operation = DscSupportedOperation_TestConfiguration;
    } 
    else
    {
        result = GetCimMIError1Param(MI_RESULT_FAILED, &extended_error, ID_DSC_HOST_INVALID_OPERATION, argv[2]);
        Tprintf(MI_T("Operation %T is not supported\n"), argv[2]);
        goto CleanUp;
    }

    // result = Dsc_Operation_Context_Initialize(context, &extended_error);
    // if( result != MI_RESULT_OK)
    // {
    //     Tprintf(MI_T("Unable to initialize DSC operation context\n"), argv[1]);
    //     goto CleanUp;
    // }

    switch(current_operation)
    {
        case DscSupportedOperation_GetConfiguration:
            {
                result = DscLib_GetConfiguration (&operation_result_root_value, argv[3]);
                if(result == MI_RESULT_OK)
                {
                    Tprintf(MI_T("Operation %T completed successfully.\n"), MI_T("GetConfiguration"));
                    Print_JSON_Value(&operation_result_root_value);
                }
                else
                {
                    Tprintf(MI_T("Error occured during operation %T. r = %d\n"), MI_T("GetConfiguration"), result);
                }
                break;
            }
        case DscSupportedOperation_TestConfiguration:
            {
                result = DscLib_TestConfiguration (&operation_result_root_value);
                if(result == MI_RESULT_OK)
                {
                    Tprintf(MI_T("Operation %T completed successfully.\n"), MI_T("TestConfiguration"));
                    Print_JSON_Value(&operation_result_root_value);
                }
                else
                {
                    Tprintf(MI_T("Error occured during operation %T. r = %d\n"), MI_T("TestConfiguration"), result);
                }
                break;
            }
        default:
            result = GetCimMIError1Param( MI_RESULT_FAILED, &extended_error, ID_DSC_HOST_INVALID_OPERATION, argv[2]);
            Tprintf(MI_T("Current operation %d is not supported yet.\n"), current_operation);
    }

CleanUp:

    // Dsc_Operation_Context_Uninitialize(context, &extendedError);
    if (operation_result_root_value)
    {
        json_value_free(operation_result_root_value);
    }

    if (result == MI_RESULT_OK)
    {
        Tprintf(MI_T("Operation was successful.\n"));
    }
    else
    {
        Tprintf(MI_T("Operation failed.\n"));
    }

    return result;
}

MI_Result  Print_JSON_Value (
        JSON_Value** p_root_value
    )
{
    MI_Result result = MI_RESULT_OK;

    char *serialized_string = NULL;
    serialized_string = json_serialize_to_string_pretty(*p_root_value);
    puts(serialized_string);
    json_free_serialized_string(serialized_string);

    return result;
}

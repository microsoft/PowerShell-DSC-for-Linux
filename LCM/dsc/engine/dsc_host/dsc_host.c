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
    Tprintf(MI_T("dsc_host <Operation> <Configuration Document Path> [Output Folder Path]\n"));
    Tprintf(MI_T("\n. Supported Operation values are: 'GetConfiguration'"));
    Tprintf(MI_T(", e.g.: \n"));
    Tprintf(MI_T("dsc_host GetConfiguration ./GetAuditPolicy.mof /tmp/GetAuditPolicy\n"));
}

int main(int argc, char *argv[])
{
    MI_Instance *extended_error = NULL;
    MI_Result result = MI_RESULT_OK;
    DscSupportedOperation current_operation = DscSupportedOperation_NOP;
    // DSC_Operation_Context *context = NULL;

    if(argc != 4)
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
    if(Tcscasecmp(argv[1], MI_T("GetConfiguration")) == 0 )
    {
        current_operation = DscSupportedOperation_GetConfiguration;
    } 
    else
    {
        result = GetCimMIError1Param(MI_RESULT_FAILED, &extended_error, ID_DSC_HOST_INVALID_OPERATION, argv[1]);
        Tprintf(MI_T("Operation %T is not supported\n"), argv[1]);
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
                // result = Invoke_DscOperation_GetConfiguration(
                //         context,
                //         &dscLibraryCallbacks,
                //         jobId,
                //         inputFilePath,
                //         &extendedError
                //     );
                JSON_Value *root_value;
                result = DscLib_GetConfiguration (&root_value, argv[2]);
                if(result == MI_RESULT_OK)
                {
                    Tprintf(MI_T("Operation %T completed successfully.\n"), MI_T("GetConfiguration"));
                }
                else
                {
                    Tprintf(MI_T("Error occured during operation %T. r = %d\n"), MI_T("GetConfiguration"), result);
                }
                char *serialized_string = NULL;
                serialized_string = json_serialize_to_string_pretty(root_value);
                puts(serialized_string);
                json_free_serialized_string(serialized_string);
                json_value_free(root_value);
                break;
            }
        default:
            result = GetCimMIError1Param( MI_RESULT_FAILED, &extended_error, ID_DSC_HOST_INVALID_OPERATION, argv[1]);
            Tprintf(MI_T("Current operation %d is not supported yet.\n"), current_operation);
    }

CleanUp:

    // Dsc_Operation_Context_Uninitialize(context, &extendedError);

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


// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_GetConfiguration(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* in)
// {
//     SetJobId();

//     // Debug Log
//     DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
//     Invoke_GetConfiguration(self, context, nameSpace, className, methodName, instanceName, in);
// }

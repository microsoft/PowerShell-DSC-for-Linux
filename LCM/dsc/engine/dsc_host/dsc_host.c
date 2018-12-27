/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#include<stdio.h>
#include <locale.h>
#include <MI.h>

#if defined(_MSC_VER)
#include <sal.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>
#include <strsafe.h>
#pragma prefast(push)
#pragma prefast(disable:26071 26036 26061) //oacr warnings in sdk header files.
#endif

#include "dsc_system_calls.h"
#include "EngineHelper.h"
#include "Resources_LCM.h"
#if defined(_MSC_VER)
#include "DSCStrings.h"
#endif
#include "LocalConfigManagerHelper.h"
#include "CAEngine.h"
#include "ModuleHandlerInternal.h"
#include "ModuleValidator.h"
#include "ComposableUnitWrapper.h"
#include "pal/lock.h"
#include "Win32_EngineHelper.h"

#include "Arbiter.h"
#include "ArbiterHelper.h"
#include "MSFT_DSCMethodInvoked.h"
#include "DscWorkerResponseHandler.h"
#include "DSCLibrary.h"
#include "DscLibraryUtility.h"
#include "MIInstanceArrayHelper.h"
#include "DscHostOutputUtility.h"
#include "HostProcessConstraints.h"
#include "DSCHostCommon.h"
#include "DscWorkerHelper.h"
#include "Logger.h"
#include "dsc_logger_c.h" // Used for tests only

#if defined(_MSC_VER)
#pragma prefast(pop)
#endif

// Currently log and error file names are hardcoaded.
// Later, filename can be based on operation-name/GUID supplied
#define OUTPUT_FILE_NAME         MI_T("dscworker.json")
#define ERROR_FILE_NAME       MI_T("dscworker.err")

#if defined(_MSC_VER)
#define OUTPUT_FILE_SEPARATOR MI_T("%T\\%T")
#define JSON_FILE_SEPARATOR MI_T("%T\\%T.json")
#else
#define OUTPUT_FILE_SEPARATOR MI_T("%T/%T")
#define OUTPUT_FILE_AND_FOLDER_SEPARATOR MI_T("%T/%T/%T")
#define JSON_FILE_SEPARATOR MI_T("%T/%T.json") 
#endif 

#define HOST_INFO_BUFF_SIZE           1024
#define DSCWORKER_VERSION_BUFF_SIZE   512

// Custom data structure used in the listener thread. This is passed by void pointer so it can be any data type that can be passed using a single void pointer (LPVOID).
typedef struct _StopListenerThreadData {
    DSCLibraryContext **context;
    DSCHostCallbackData *hostCallbackData;
    MI_Instance **extendedError;
    HANDLE terminateEventHandle;
} StopListenerThreadData;

// DscWorker Version Information
const MI_Uint32 MajorVersion = 1;
const MI_Uint32 MinorVersion = 0;
const MI_Uint32 BuildVersion = 0000;

MI_Result GetDscWorkerVersion(_In_z_ MI_Char* version, _In_ size_t length)
{
    if ( Stprintf( version, length, MI_T( "Version : %d.%d.%04d" ), MajorVersion, MinorVersion, BuildVersion ) < 0 )
        return MI_RESULT_FAILED;
    else
        return MI_RESULT_OK;
}

void PrintVersion()
{
    MI_Char versionInfo[DSCWORKER_VERSION_BUFF_SIZE];
    GetDscWorkerVersion( versionInfo, DSCWORKER_VERSION_BUFF_SIZE );
    Tprintf( versionInfo );
}

void PrintHelp()
{
    Tprintf( MI_T( "Usage:\n" ) );
    Tprintf( MI_T( "DscWorker.exe [--help] [--version] \n" ) );
    Tprintf( MI_T( "DscWorker.exe <Operation> <Job ID> [Log Path]\n" ) );
    Tprintf( MI_T( "LogPath is used for testing only.\n" ) );
    Tprintf( MI_T( "\n. Supported Operation values are: 'GetLCMSettings', 'RunConsistency', 'UpdateDscConfiguration', 'SendReport'" ) );
    Tprintf( MI_T( ", e.g.: \n" ) );
    Tprintf( MI_T( "DscWorker.exe GetLCMSettings \"{7920CB26-CB11-11E7-8ED6-C4346B7C918B}\" \n" ) );
    Tprintf( MI_T( "DscWorker.exe GetLCMSettings \"{7920CB26-CB11-11E7-8ED6-C4346B7C918B}\" dsc_worker.log\n" ) );
}

MI_Result CreateOutputPaths(_In_z_ MI_Char *outputFolder,
                            _Inout_ DSCHostCallbackData *callbackData,
                            _Outptr_result_maybenull_ MI_Instance **extendedError,
                            _In_ MI_Char *log_file_name)
{
    *extendedError = NULL;
  
    // Error file
    if ( Stprintf( (MI_Char*)callbackData->errFilePath, MAX_PATH, OUTPUT_FILE_SEPARATOR, outputFolder, ERROR_FILE_NAME ) == -1 )
    {
        return GetCimMIError1Param( NULL, MI_RESULT_FAILED, extendedError, ID_DSC_HOST_PRINTF_FILE_CREATION_ERROR, outputFolder);
    }

    // Log file
    if (log_file_name)
    {
        if (Stprintf((MI_Char*)callbackData->logFilePath, MAX_PATH, OUTPUT_FILE_SEPARATOR, outputFolder, log_file_name) == -1)
        {
            return GetCimMIError1Param(NULL, MI_RESULT_FAILED, extendedError, ID_DSC_HOST_PRINTF_FILE_CREATION_ERROR, outputFolder);
        }
    }
    else
    {
        if (Stprintf((MI_Char*)callbackData->logFilePath, MAX_PATH, OUTPUT_FILE_SEPARATOR, outputFolder) == -1)
        {
            return GetCimMIError1Param(NULL, MI_RESULT_FAILED, extendedError, ID_DSC_HOST_PRINTF_FILE_CREATION_ERROR, outputFolder);
        }
    }

    // Output file
    if (Stprintf((MI_Char*)callbackData->jsonOutFilePath, MAX_PATH, OUTPUT_FILE_SEPARATOR, outputFolder, OUTPUT_FILE_NAME) == -1)
    {
        return GetCimMIError1Param(NULL, MI_RESULT_FAILED, extendedError, ID_DSC_HOST_PRINTF_FILE_CREATION_ERROR, outputFolder);
    }

    //Create Directory if one doesn't exists
    if ( Directory_ExistT( outputFolder ) != 0 )
    {        
        Create_Directory( outputFolder );
    }

    // Delete old files if any exists
    if ( File_ExistT( (const TChar*) callbackData->errFilePath ) != -1 )
    {
        DSC_WORKER_DEBUG(Tprintf( MI_T( "output file '%T' exists, deleting it\n" ), callbackData->errFilePath ));
       File_RemoveT( callbackData->errFilePath );
    }

    if ( File_ExistT( (const TChar*) callbackData->jsonOutFilePath) != -1 )
    {
        DSC_WORKER_DEBUG(Tprintf( MI_T( "output file '%T' exists, deleting it\n" ), callbackData->jsonOutFilePath ));
       File_RemoveT( callbackData->jsonOutFilePath );
    }    

    callbackData->streamedInstances.data = DSC_malloc( DEFAULT_STREAMCAPACITY*sizeof(MI_Instance), NitsHere() );
    if ( callbackData->streamedInstances.data == NULL )
    {
        return GetCimMIError( NULL, MI_RESULT_FAILED, extendedError, ID_LCMHELPER_MEMORY_ERROR );
    }     
    callbackData->errors.data = DSC_malloc( DEFAULT_STREAMCAPACITY*sizeof(MI_Instance), NitsHere() );
    if ( callbackData->errors.data == NULL )
    {
        return GetCimMIError( NULL, MI_RESULT_FAILED, extendedError, ID_LCMHELPER_MEMORY_ERROR );
    }

    callbackData->streamedInstances.size = 0;
    callbackData->streamedInstancesCapacity = DEFAULT_STREAMCAPACITY;
    callbackData->errors.size = 0;
    callbackData->errorsCapacity = DEFAULT_STREAMCAPACITY ;
    return MI_RESULT_OK;
}

MI_Result WriteDscWorkerInfoOnDisk(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Result result = MI_RESULT_OK;
    MI_Char* separator = MI_T("=========================================");
    MI_Char hostInfo[HOST_INFO_BUFF_SIZE];
    MI_Char versionInfo[DSCWORKER_VERSION_BUFF_SIZE];

    // If this method fails to get the operating system information, it writes the error message in hostInfo buffer.
    // It isn't a terminating error. So we can ignore the return value from this method.
    result = GetHostOSInformation( hostInfo, HOST_INFO_BUFF_SIZE, cimErrorDetails );
    if (result != MI_RESULT_OK)
    {
        DSC_WORKER_DEBUG(Tprintf(MI_T("Could not get the host OS information.")));
        return result;
    }

    // Write OS Information in log file.
    LogDiagnosticsMessageInternal(DSCWORKER_COMPONENTNAME, 0, MSG_INFO, hostInfo);

    // Write DscWorker Version Information in log file.
    result = GetDscWorkerVersion(versionInfo, DSCWORKER_VERSION_BUFF_SIZE);
    if (result != MI_RESULT_OK)
    {
        DSC_WORKER_DEBUG(Tprintf(MI_T("Could not get the host version information.")));
        return result;
    }

    LogDiagnosticsMessageInternal(DSCWORKER_COMPONENTNAME, 0, MSG_INFO, separator);
    LogDiagnosticsMessageInternal(DSCWORKER_COMPONENTNAME, 0, MSG_INFO, versionInfo);
    LogDiagnosticsMessageInternal(DSCWORKER_COMPONENTNAME, 0, MSG_INFO, separator);

    return result;
}

MI_Result ExtractAndPrintTimerValues(_In_ const MI_Instance* instance,
                                     _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result result = MI_RESULT_OK;
    MI_Value value;
    MI_Type type;
    MI_Instance* metaConfigInstance;

    result = MI_Instance_GetElement(instance, MSFT_DSCConfigurationStatus_MetaConfiguration, &value, &type, NULL, NULL);
    EH_CheckResult(result);
    metaConfigInstance = (MI_Instance*)value.instance;

    result = MI_Instance_GetElement(metaConfigInstance, MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins, &value, &type, NULL, NULL);
    EH_CheckResult(result);
    MI_Uint32 configurationModeFrequencyMins = value.uint32;

    result = MI_Instance_GetElement(metaConfigInstance, MSFT_DSCMetaConfiguration_RefreshFrequencyMins, &value, &type, NULL, NULL);
    EH_CheckResult(result);
    MI_Uint32 refreshModeFrequencyMins = value.uint32;

	Tprintf(MI_T("ConfigurationModeFrequencyMins=%d\n"), configurationModeFrequencyMins);
	Tprintf(MI_T("RefreshModeFrequencyMins=%d\n"), refreshModeFrequencyMins);

EH_UNWIND
    if (result != MI_RESULT_OK)
    {
        DSC_WORKER_DEBUG(Tprintf(MI_T("Could not extract timer values from MetaConfiguration")));
        return GetCimMIError(NULL, MI_RESULT_FAILED, extendedError, ID_DSC_HOST_UNABLE_TO_EXTRACT_TIMER_VALUES);
    }
        
    return result;
}

DWORD  WINAPI StopListenerMain(LPVOID lpStopListenerThreadParam)
{
    DWORD r = 0;
    MI_Result result = MI_RESULT_OK;
    StopListenerThreadData *pThreadData;
    MI_Char* jobId = NULL;

    // Cast the input parameter to the correct data type. The pointer is known to be valid because it was checked for NULL before the thread was created.
    pThreadData = (StopListenerThreadData*)lpStopListenerThreadParam;

    DSCLibraryContext **context = pThreadData->context;
    DSCHostCallbackData *hostCallbackData = pThreadData->hostCallbackData;
    DSCLibraryCallbacks dscLibraryCallbacks = { 0 };
    dscLibraryCallbacks.postResult = DscWorker_PostResult;
    dscLibraryCallbacks.postInstance = DscWorker_PostInstance;
    dscLibraryCallbacks.writeMessage = DscWorker_WriteMessage;
    dscLibraryCallbacks.writeError = DscWorker_WriteError;
    dscLibraryCallbacks.writeProgress = DscWorker_WriteProgress;
    dscLibraryCallbacks.writeStreamParameter = DscWorker_WriteStreamParameter;
    dscLibraryCallbacks.pHostData = (ptrdiff_t) hostCallbackData;
    dscLibraryCallbacks.reserved1 = (ptrdiff_t) context;
    
    MI_Instance **extendedError = pThreadData->extendedError;
    HANDLE hTerminateEvent = pThreadData->terminateEventHandle;
    HANDLE hStopEvent;
    HANDLE allEvents[2];
    DWORD dwEvent;

    // Create a manual-reset event object. The main thread sets this object to the signaled state when it finishes the DSC operation.
    // Then the second thread waiting for a potential STOP operation will terminate and we can shutdown gracefully.
    hStopEvent = CreateEvent(
        NULL,               // default security attributes
        TRUE,               // manual-reset event
        FALSE,              // initial state is nonsignaled
        MI_T("Global\\StopDscWorker")  // object name
    );

    if (hStopEvent == NULL)
    {
        r = (DWORD) GetCimMIError(NULL, MI_RESULT_FAILED, extendedError, ID_DSC_HOST_FAILED_TO_CREATE_STOP_EVENT);
        WriteErrorOnDisk(hostCallbackData->errFilePath, *extendedError);
        goto clean_up;
    }

    DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] Start \n")));

    DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] Waiting for TERMINATE or STOP event \n")));

    allEvents[0] = hTerminateEvent;
    allEvents[1] = hStopEvent;

    dwEvent = WaitForMultipleObjects(
        2,           // number of objects in array
        allEvents,   // array of objects
        FALSE,       // wait for any object
        INFINITE);   // five-second wait

    // The return value indicates which event is signaled
    switch (dwEvent)
    {
        // allEvents[0] was signaled, aka hTerminateEvent
        case WAIT_OBJECT_0 + 0:
            DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] TERMINATE event was received.\n")));
            break;

        // allEvents[1] was signaled, aka hStopEvent
        case WAIT_OBJECT_0 + 1:
            DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] STOP event was received.\n")));
            jobId = Generate_UUID(NitsMakeCallSite(-3, NULL, NULL, 0));
            result = DSCLib_StopDscConfiguration(*context, &dscLibraryCallbacks, jobId, MI_TRUE, extendedError);
            if (result == MI_RESULT_OK)
            {
                DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] DSCLib_StopDscConfiguration completed successfully.\n")));
            }
            else
            {
                WriteErrorOnDisk(hostCallbackData->errFilePath, *extendedError);
                DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] DSCLib_StopDscConfiguration Failed.\n")));
            }
            break;

        // Return value is invalid.
        default:
            DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] Unexpected event was received/Failurein WaitForMultipleObjects.\n")));
            r = (DWORD)GetCimMIError(NULL, MI_RESULT_FAILED, extendedError, ID_DSC_HOST_FAILED_TO_WAIT_FOR_EVENT);
            WriteErrorOnDisk(hostCallbackData->errFilePath, *extendedError);
            goto clean_up;
    }

clean_up:

    DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] Clean up \n")));
    if (!hStopEvent)
    {
        CloseHandle(hStopEvent);
    }
    if (jobId)
    {
        DSC_free(jobId);
    }

    DSC_WORKER_DEBUG(Tprintf(MI_T("[ StopListenerMain ] End \n")));

    return r;
}

#if defined(_MSC_VER)
int MI_MAIN_CALL wmain (_In_ int argc, _In_reads_(argc) wchar_t** argv)
#else
int MI_MAIN_CALL main(_In_ int argc, _In_reads_(argc) char** argv)
#endif
{
    MI_Instance *extendedError = NULL;
    MI_Result result = MI_RESULT_OK;
    StopListenerThreadData stopListenerThreadData;
    DWORD stopListenerThreadId;
    HANDLE hStopListenerThread = NULL;
    DWORD lpStopListenerThreadExitCode = 0;
    HANDLE hTerminateEvent = NULL;
    DSCLibraryContext *context = NULL;
    DSCLibraryEnvironmentPath envPath = {0};
    MI_Char *log_file_name = NULL;

    // Verify input arguments through command line
    if (argc == 2 && 0 == Tcscasecmp(argv[1], MI_T("--version")))
    {
        PrintVersion();
        return result;
    }
    else if ((argc < 3) || (argc > 4))
    {
        PrintHelp();
        result = MI_RESULT_INVALID_PARAMETER;
        return result;
    }


#if defined(_MSC_VER)
    // Sets the thread preferred UI languages for the current thread
    SetThreadPreferredUILanguages(MUI_CONSOLE_FILTER, NULL, NULL);
#endif
    // Set locale so that strings are correctly processed.
    setlocale(LC_ALL, "");

    DSCHostCallbackData hostCallbackData = {0};
    DSCLibraryCallbacks dscLibraryCallbacks = {0};
    dscLibraryCallbacks.postResult = DscWorker_PostResult;
    dscLibraryCallbacks.postInstance = DscWorker_PostInstance;
    dscLibraryCallbacks.writeMessage = DscWorker_WriteMessage;
    dscLibraryCallbacks.writeError = DscWorker_WriteError;
    dscLibraryCallbacks.writeProgress = DscWorker_WriteProgress;
    dscLibraryCallbacks.writeStreamParameter = DscWorker_WriteStreamParameter;
    dscLibraryCallbacks.pHostData = (ptrdiff_t) &hostCallbackData;
    dscLibraryCallbacks.reserved1 = (ptrdiff_t) context;

    if (argc == 4)
    {
        log_file_name = argv[3];
    }

    memset(&envPath, 0, sizeof(DSCLibraryEnvironmentPath));
    envPath.DscLibraryDirectoryBasePath = (MI_Char*)DSC_malloc(sizeof(MI_Char)*MAX_PATH, NitsHere());
    envPath.UserConfigPath = (MI_Char*)DSC_malloc(sizeof(MI_Char)*MAX_PATH, NitsHere());
    envPath.DotNetFrameworkPath = (MI_Char*)DSC_malloc(sizeof(MI_Char)*MAX_PATH, NitsHere());
    envPath.EventLogPath = (MI_Char*)DSC_malloc(sizeof(MI_Char)*MAX_PATH, NitsHere());

    if ( envPath.DscLibraryDirectoryBasePath == NULL || 
         envPath.UserConfigPath == NULL || 
         envPath.DotNetFrameworkPath == NULL || 
         envPath.EventLogPath == NULL )
    {
        result = GetCimMIError( NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED, &extendedError, ID_LCMHELPER_MEMORY_ERROR );
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }

    // Get the installation path of current DSC Worker
    result = GetDSCInstallationPath( envPath.DscLibraryDirectoryBasePath, MAX_PATH, &extendedError );
    if ( result != MI_RESULT_OK )
    {
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }

    FormatPath( envPath.UserConfigPath, MAX_PATH, USERCONFIG_PATH_FORMAT, envPath.DscLibraryDirectoryBasePath );
    FormatPath( envPath.DotNetFrameworkPath, MAX_PATH, DSC_PATH_FORMAT, envPath.DscLibraryDirectoryBasePath );

    // Check for the presence of the folder
    MI_Char *outputFolder = envPath.UserConfigPath;
    result = CreateOutputPaths(outputFolder, &hostCallbackData, &extendedError, log_file_name);
    if( result != MI_RESULT_OK)
    {
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }

    if ( Directory_ExistT( outputFolder ) == -1 )
    {
        // Can't write this error on disk since output dir is not created.
        result = GetCimMIError( NULL, MI_RESULT_FAILED, &extendedError, ID_LCMHELPER_CREATE_CONFDIR_FAILED );
        goto clean_up;
    }

    if (argc == 4) // User for testing only
    {
        // Initialize DSC settings and update log path
        set_dsc_logger_log_path(hostCallbackData.logFilePath);
    }

    // Initialize logger APIs
    if (dsc_logger_register_component(DSCWORKER_COMPONENTNAME))
    {
        result = GetCimMIError1Param(NULL, MI_RESULT_FAILED, &extendedError, ID_DSC_HOST_INVALID_OPERATION, argv[1]);
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }

    // Write host operating system and version information in the log file.
    // This method also verifies Access permission of output folder or log file.
    // So this should always be the the first attempt to write data into log file.
    result = WriteDscWorkerInfoOnDisk(&extendedError);
    EH_CheckResult(result);

    //Set log info
    if ( Stprintf( envPath.EventLogPath, MAX_PATH, MI_T("%T"), hostCallbackData.logFilePath ) == -1 )
    {
        result = GetCimWin32Error1Param( NULL, MI_RESULT_FAILED, &extendedError, ID_DSC_HOST_PRINTF_FILE_CREATION_ERROR,hostCallbackData.logFilePath );
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        return result;
    }
    
    // Initialize DSC Library
    result = DSCLib_InitializeDSCLibrary( &envPath, &context, &extendedError );
    if ( result != MI_RESULT_OK)
    {
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        return result;
    }
    
    dscLibraryCallbacks.reserved1 = (ptrdiff_t) context;

    // Create a manual-reset event object. The main thread sets this object to the signaled state when it finishes the DSC operation.
    // Then the second thread waiting for a potential STOP operation will terminate and we can shutdown gracefully.
    hTerminateEvent = CreateEvent(
        NULL,               // default security attributes
        TRUE,               // manual-reset event
        FALSE,              // initial state is nonsignaled
        MI_T("Local\\TerminateStopListenerThread")  // object name
    );

    if (hTerminateEvent == NULL)
    {
        result = GetCimMIError(NULL, MI_RESULT_FAILED, &extendedError, ID_DSC_HOST_FAILED_TO_CREATE_TERMINATE_EVENT);
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }

    // Create the data structure that's going to be passed to the new thread listening for Stop signal from DscService
    stopListenerThreadData.context = &context;
    stopListenerThreadData.hostCallbackData = &hostCallbackData;
    stopListenerThreadData.extendedError = &extendedError;
    stopListenerThreadData.terminateEventHandle = hTerminateEvent;

    // Create a new thread to listen for Stop signal from DscService
    hStopListenerThread = CreateThread(
        NULL,                     // default security attributes
        0,                        // use default stack size  
        StopListenerMain,         // thread function name
        &stopListenerThreadData, // argument to thread function 
        0,                        // use default creation flags 
        &stopListenerThreadId);   // returns the thread identifier

    // Check the return value for success. If CreateThread fails, DscWorker terminates execution. This will automatically clean up threads and memory. 
    if (hStopListenerThread == NULL)
    {
        result = GetCimMIError(NULL, MI_RESULT_FAILED, &extendedError, ID_DSC_HOST_FAILED_TO_CREATE_STOPLISTENER_THREAD);
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }
    
    MI_Char* jobId = argv[2];
    if (Tcscasecmp(argv[1], MI_T("GetLCMSettings")) == 0)
    {
        result = DSCLib_GetDscLocalConfigurationManager(context, &dscLibraryCallbacks, jobId, &extendedError);
        if (result == MI_RESULT_OK)
        {
            // We expect a single MI instance for GetLCMSettings
            if ((&hostCallbackData.streamedInstances)->size == 1)
            {
                result = ExtractAndPrintTimerValues((&hostCallbackData.streamedInstances)->data[0], &extendedError);
                if (result != MI_RESULT_OK)
                {
                    WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
                }
                else
                {
                    DSC_WORKER_DEBUG(Tprintf(MI_T("Operation completed successfully. Output is captured in %T and logs are captured in %T.\n"), hostCallbackData.jsonOutFilePath, hostCallbackData.logFilePath));
                }
            }
            else
            {
                result = GetCimMIError(NULL, MI_RESULT_FAILED, &extendedError, ID_DSC_HOST_FAILED_GETLCM_OPERATION);
            }
        }
        else
        {
            WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
            DSC_WORKER_DEBUG(Tprintf(MI_T("Error occured during operation. Error details are logged in %T and logs are captured in %T.\n"), hostCallbackData.errFilePath, hostCallbackData.logFilePath));
        }
    }
    else if (Tcscasecmp(argv[1], MI_T("RunConsistency")) == 0)
    {
        result = DSCLib_PerformRequiredConsistencyCheck(context, &dscLibraryCallbacks, jobId, &extendedError);
        if (result == MI_RESULT_OK)
        {
            DSC_WORKER_DEBUG(Tprintf(MI_T("Operation completed successfully. Output is captured in %T and logs are captured in %T.\n"), hostCallbackData.jsonOutFilePath, hostCallbackData.logFilePath));
        }
        else
        {
            DSC_WORKER_DEBUG(Tprintf(MI_T("Error occured during operation. Error details are logged in %T and logs are captured in %T.\n"), hostCallbackData.errFilePath, hostCallbackData.logFilePath));
            WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        }
    }
    else if (Tcscasecmp(argv[1], MI_T("UpdateDscConfiguration")) == 0)
    {
        result = DSCLib_UpdateDscConfiguration(context, &dscLibraryCallbacks, jobId, &extendedError);
        if (result == MI_RESULT_OK)
        {
            DSC_WORKER_DEBUG(Tprintf(MI_T("Operation completed successfully. Output is captured in %T and logs are captured in %T.\n"), hostCallbackData.jsonOutFilePath, hostCallbackData.logFilePath));
        }
        else
        {
            WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
            DSC_WORKER_DEBUG(Tprintf(MI_T("Error occured during operation. Error details are logged in %T and logs are captured in %T.\n"), hostCallbackData.errFilePath, hostCallbackData.logFilePath));
        }
    }
    else
    {
        result = GetCimMIError1Param(NULL, MI_RESULT_FAILED, &extendedError, ID_DSC_HOST_INVALID_OPERATION, argv[1]);
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        DSC_WORKER_DEBUG(Tprintf(MI_T("Operation %T is not supported\n"), argv[1]));
    }

    DSC_WORKER_DEBUG(Tprintf(MI_T("Sending a TERMINATE signal to StopListener thread.\n")));
    if (!SetEvent(hTerminateEvent))
    {
        result = GetCimMIError(NULL, MI_RESULT_FAILED, &extendedError, ID_DSC_HOST_FAILED_TO_SIGNAL_TERMINATE_EVENT);
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }

    DSC_WORKER_DEBUG(Tprintf(MI_T("Waiting for Stop thread to finish.\n")));
    // Wait until StopListener Thread have terminated.
    WaitForSingleObject(hStopListenerThread, INFINITE);
    DSC_WORKER_DEBUG(Tprintf(MI_T("StopListener thread done.\n")));

    if (GetExitCodeThread(hStopListenerThread, &lpStopListenerThreadExitCode) == 0)
    {
        result = GetCimMIError(NULL, GetLastError(), &extendedError, ID_DSC_HOST_FAILED_TO_GET_THREAD_EXIT_CODE);
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up;
    }

    if (lpStopListenerThreadExitCode != MI_RESULT_OK)
    {
        result = GetCimMIError(NULL, lpStopListenerThreadExitCode, &extendedError, ID_DSC_HOST_STOPLISTENER_THREAD_FAILED);
        WriteErrorOnDisk(hostCallbackData.errFilePath, extendedError);
        goto clean_up; 
    }

clean_up:
    if (!hStopListenerThread)
    {
        CloseHandle(hStopListenerThread);
    }

    if (!hTerminateEvent)
    {
        CloseHandle(hTerminateEvent);
    }

    // Uninitialize DSC Library
    DSCLib_UnInitializeDSCLibrary( &context );

    UnRegisterLogDiagnostics(DSCWORKER_COMPONENTNAME);

    // Cleanup data streams
    MI_Uint32 xCount;
    for ( xCount = 0 ; xCount < hostCallbackData.streamedInstancesCapacity ; xCount++ )
    {
        MI_Instance_Delete( hostCallbackData.streamedInstances.data[xCount] );
    }
    for ( xCount = 0 ; xCount < hostCallbackData.errorsCapacity ; xCount++ )
    {
        MI_Instance_Delete( hostCallbackData.errors.data[xCount] );
    }  
    if ( hostCallbackData.streamedInstances.data )
    {
        DSC_free( hostCallbackData.streamedInstances.data );
    }
    if ( hostCallbackData.errors.data )
    {
        DSC_free( hostCallbackData.errors.data );
    }
    if ( envPath.DscLibraryDirectoryBasePath )
    {
        DSC_free( envPath.DscLibraryDirectoryBasePath );
    }
    if ( envPath.UserConfigPath )
    {
        DSC_free( envPath.UserConfigPath );
    }
    if ( envPath.DotNetFrameworkPath )
    {
        DSC_free( envPath.DotNetFrameworkPath );
    }
    if( envPath.EventLogPath )
    {
        DSC_free( envPath.EventLogPath );
    }
 
	EH_UNWIND
	
	if(result != MI_RESULT_OK)
    {
		Tprintf(MI_T("Operation Failed.\n"));
		return result;
    }
    return result;
}

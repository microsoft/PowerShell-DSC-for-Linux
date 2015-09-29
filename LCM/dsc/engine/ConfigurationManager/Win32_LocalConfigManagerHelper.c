/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "EngineHelper.h"
#include "ModuleHandler.h"
#include "Win32_LocalConfigManagerHelper.h"
#include "LocalConfigManagerTaskStrings.h"
#include "LocalConfigManagerHelper.h"
#include "Resources_LCM.h"
#include "DSC_SystemCalls.h"
#include <Sddl.h>
#include <errno.h>
#include "EventWrapper.h"
#include <PAL/sleep.h>

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201)

// #include <sha2.h>
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

MI_Result UpdateTask(
    _In_z_ MI_Char* taskName,
    _In_z_ MI_Char* taskTime,
    _In_ MI_Uint32 refreshFrequencyInSeconds,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    PROCESS_INFORMATION ProcInfo;
    STARTUPINFO si;
    HRESULT hr = S_OK;
    MI_Uint32 dwExitCode = 0;
    BOOL bRes = MI_TRUE;
    UINT retVal = 0;
    HANDLE hXmlFileHandle = NULL;
    BOOL bHandleUsageSuccess = FALSE;
    const char BOM [] = {0xFF, 0xFE};
    MI_Uint32 dwWmiMethodArg = 0;
    size_t sFormattedXMLFileLength = 0;

    // The task scheduler filename
    // This will double as the buffer for GetTempPath and for the command
    wchar_t wSchedTaskPath[MAX_PATH];
    wchar_t wTmpFilePath[MAX_PATH];
    wchar_t wSchedTaskFile[(sizeof(LocalConfigManagerTaskXMLFormatString)+sizeof(L"2013-04-11T18:10:48")+sizeof("2678400"))/sizeof(wchar_t)];
    wchar_t wSchedTaskParam[LCM_MAX_PATH];
    MI_Uint32 len = 0;

    LPWSTR wCommandFormat = NULL;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    wSchedTaskPath[0] = L'\0';
    wTmpFilePath[0] = L'\0';
    wSchedTaskFile[0] = L'\0';
    wSchedTaskParam[0] = L'\0';
    memset(&si,0,sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_FORCEOFFFEEDBACK;

    if (refreshFrequencyInSeconds > THIRTY_ONE_DAYS_IN_SECONDS)
    {
        refreshFrequencyInSeconds = THIRTY_ONE_DAYS_IN_SECONDS;
    }
    if (refreshFrequencyInSeconds < FIFTEEN_MINUTES_IN_SECONDS)
    {
        refreshFrequencyInSeconds = THIRTY_ONE_DAYS_IN_SECONDS;
    }



    wCommandFormat = LocalConfigManagerTaskConsistencyCommand;
    dwWmiMethodArg = 1;

    retVal = GetTempPath(MAX_PATH, wSchedTaskPath);
    if (!retVal)
    {
        hr = E_FAIL;
        return GetCimError(hr, extendedError, ID_LCMHELPER_GETTEMPPATH_ERROR);
    }

    // 0 here signifies our willingness to let the system create and close the file for us
    // This means we cannot specify FILE_ATTRIBUTE_TEMPORARY to CreateFile
    // but in return we can be sure that nobody will take our filename in the microsecond before we use it
    retVal = GetTempFileName(wSchedTaskPath, L"LCM", 0u, wTmpFilePath);
    if (!retVal)
    {
        hr = E_FAIL;
        return GetCimError(hr, extendedError, ID_LCMHELPER_GETTEMPFILENAME_ERROR);
    }

    hr = StringCchPrintf(wSchedTaskParam, sizeof(wSchedTaskParam)/sizeof(wchar_t), wCommandFormat, wTmpFilePath);
    if (FAILED(hr) || NitsShouldFault(NitsHere(), NitsAutomatic))
    {   
        if (SUCCEEDED(hr)) hr = E_FAIL;        
        return GetCimError(hr, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }

    if (GetEnvironmentVariable(L"windir", wSchedTaskPath, MAX_PATH) ==0 )
    {
        return  GetCimWin32Error(GetLastError(), extendedError, ID_MODMAN_WINDIRENV_FAILED);
    }

    hr = StringCchCatW(wSchedTaskPath, MAX_PATH, L"\\system32\\schtasks.exe");
    if (FAILED(hr))
    {
        return GetCimError(hr, extendedError, ID_ENGINEHELPER_CAT_ERROR);
    }

    hr = StringCchPrintf(wSchedTaskFile, sizeof(wSchedTaskFile)/sizeof(wchar_t), LocalConfigManagerTaskXMLFormatString, refreshFrequencyInSeconds, taskTime, dwWmiMethodArg);
    if (FAILED(hr) || NitsShouldFault(NitsHere(), NitsAutomatic))
    {   
        if( SUCCEEDED(hr)) hr = E_FAIL;        
        return GetCimError(hr, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }

    hr = StringCchLength(wSchedTaskFile, STRSAFE_MAX_CCH, &sFormattedXMLFileLength);
    if (FAILED(hr) || NitsShouldFault(NitsHere(), NitsAutomatic))
    {   
        if( SUCCEEDED(hr)) hr = E_FAIL;        
        return GetCimError(hr, extendedError, ID_LCMHELPER_STRLEN_ERROR);
    }

    // We've done everything we can do ahead of time. Now we actually start changing the system

    hXmlFileHandle = CreateFile(wTmpFilePath, GENERIC_WRITE, 0 /* Prevent sharing */, NULL /* Children don't inherit */, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL /* No template */);
    if (hXmlFileHandle == INVALID_HANDLE_VALUE)
    {
        return GetCimWin32Error(GetLastError(), extendedError, ID_ENGINEHELPER_OPENFILE_ERROR);
    }

    bHandleUsageSuccess = WriteFile(hXmlFileHandle, BOM, sizeof(BOM), (LPDWORD)&len, NULL);
    if (!bHandleUsageSuccess)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        CloseHandle(hXmlFileHandle);
        DeleteFile(wTmpFilePath);
        return GetCimError(hr, extendedError, ID_LCMHELPER_WRITEFILE_ERROR);
    }

    bHandleUsageSuccess = WriteFile(hXmlFileHandle, wSchedTaskFile, (DWORD)(sFormattedXMLFileLength*sizeof(wchar_t)), (LPDWORD)&len, NULL);
    if (!bHandleUsageSuccess)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        CloseHandle(hXmlFileHandle);
        DeleteFile(wTmpFilePath);
        return GetCimError(hr, extendedError, ID_LCMHELPER_WRITEFILE_ERROR);
    }

    bHandleUsageSuccess = CloseHandle(hXmlFileHandle);
    if (!bHandleUsageSuccess)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        DeleteFile(wTmpFilePath);
        return GetCimError(hr, extendedError, ID_LCMHELPER_CLOSEHANDLE_ERROR);
    }

    bRes = CreateProcess(wSchedTaskPath, wSchedTaskParam, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &ProcInfo);
    if (!bRes)
    {
        CloseHandle(hXmlFileHandle);
        DeleteFile(wTmpFilePath);
        return GetCimWin32Error(GetLastError(), extendedError, ID_ENGINEHELPER_CREATEPROCESS_ERROR);
    }

    WaitForSingleObject(ProcInfo.hProcess, INFINITE);
    if (GetExitCodeProcess(ProcInfo.hProcess,(LPDWORD)&dwExitCode) && dwExitCode != 0)
    {
        r = GetCimMIError(MI_RESULT_FAILED, extendedError, ID_ENGINEHELPER_CREATEPROCESS_ERROR);
    }

    bHandleUsageSuccess = DeleteFile(wTmpFilePath);
    if (!bHandleUsageSuccess && r == MI_RESULT_OK)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        return GetCimError(hr, extendedError, ID_LCMHELPER_DELETEFILE_ERROR);
    }

    CloseHandle(ProcInfo.hThread);
    CloseHandle(ProcInfo.hProcess);

    return r;
}


MI_Result RepudicationHelper(
    _In_opt_ MI_Context* context,
    _In_ HANDLE token,
    _In_z_ const MI_Char* methodName,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Type type;
    MI_Value value;
    MI_Result result;
    size_t computerLength;
    DWORD sidLength;
    MI_Char* pComputerName=NULL;
    BOOL success = FALSE;
    PWSTR pstrUserSid = NULL;
    PTOKEN_USER userInformation = NULL;
    LCMProviderContext lcmContext = {0};

    if (context)
    {
        result = MI_Context_GetCustomOption(context,DSCCOMPUTERNAME, &type, &value);
        if (result == MI_RESULT_OK && type == MI_STRING)
        {
            computerLength = Tcslen(value.string)+1;
            pComputerName = (MI_Char*)DSC_malloc(computerLength* sizeof(wchar_t), NitsHere()); 
            if (pComputerName == NULL)
            {
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
            }

            memcpy(pComputerName, value.string, computerLength * sizeof(wchar_t));
        }
    }        

    GetTokenInformation(token, TokenUser, userInformation, 0, &sidLength);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }

        return GetCimMIError(MI_RESULT_FAILED, cimErrorDetails, ID_LCMHELPER_COMPUTERNAMECONTEXT_ERROR);
    }

    userInformation = (PTOKEN_USER)DSC_malloc(sidLength, NitsHere());
    if (userInformation == NULL)
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }

        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
    }

    success = GetTokenInformation(token, TokenUser, userInformation, sidLength, &sidLength);
    if (!success || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }

        DSC_free(userInformation);

        if (success)
        {
            // Pass through a bogus error if we've faulted in an error otherwise success will be returned.
            SetLastError(ERROR_ACCESS_DENIED);
        }
        return GetCimWin32Error(MI_RESULT_FAILED, cimErrorDetails, GetLastError());
    }

    success = ConvertSidToStringSidW(userInformation->User.Sid, &pstrUserSid);
    DSC_free(userInformation);
    if (!success || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }
        if (pstrUserSid != NULL)
        {
            LocalFree(pstrUserSid);
        }

        if (success)
        {
            // Pass through a bogus error if we've faulted in an error otherwise success will be returned.
            SetLastError(ERROR_ACCESS_DENIED);
        }
        return GetCimWin32Error(MI_RESULT_FAILED, cimErrorDetails, GetLastError());
    }

    lcmContext.executionMode = (LCM_EXECUTIONMODE_OFFLINE | LCM_EXECUTIONMODE_ONLINE);
    lcmContext.context = (void*)context;
    LCM_WriteMessageInfo(&lcmContext, pComputerName, MI_WRITEMESSAGE_CHANNEL_VERBOSE, pstrUserSid);
    LocalFree(pstrUserSid);
    if (pComputerName != NULL)
    {
        DSC_free(pComputerName);
    }

    return MI_RESULT_OK;
}

MI_Result RegisterRebootTaskIfNeeded(
    _In_ MI_Instance *metaConfigInstance, 
    _In_ ModuleManager *moduleManager,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Uint32 flags;
    MI_Value value;
    MI_Result result = MI_RESULT_OK;
    MI_Instance* tempErrorDetail = NULL;

    if (cimErrorDetails == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }

    *cimErrorDetails = NULL;    // Explicitly set *cimErrorDetails to NULL as _Outptr_ requires setting this at least once.   
    result = MI_Instance_GetElement(metaConfigInstance, MSFT_DSCMetaConfiguration_RebootNodeIfNeeded, &value, NULL, &flags, NULL);
    if (result == MI_RESULT_OK)
    {
        if (flags & MI_FLAG_NULL)
        {
            value.boolean = DEFAULT_RebootNodeIfNeeded;
        }
    }

    result = RegisterStartAtBootTask(MI_TRUE, cimErrorDetails);
    if (result == MI_RESULT_OK && value.boolean == MI_TRUE)
    {
        result = ScheduleRestart(cimErrorDetails);
        if (result != MI_RESULT_OK)
        {
            // Deregister the task
            RegisterStartAtBootTask(MI_FALSE, &tempErrorDetail);
            if (tempErrorDetail)
            {
                MI_Instance_Delete(tempErrorDetail);
            }
        }
    }

    return result;
}

MI_Result RegisterStartAtBootTask(
    _In_ MI_Boolean bregisterTask,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    PROCESS_INFORMATION ProcInfo;
    STARTUPINFO si;
    HRESULT hr = S_OK;
    MI_Uint32 dwExitCode = 0;
    BOOL bRes = MI_TRUE;
    wchar_t param[LCM_MAX_PATH] ;
    wchar_t wExe[LCM_MAX_PATH];
    DSC_EventWriteMessageScheduleTaskAfterReboot();

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;  // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.   

    wExe[0] = L'\0';
    param[0] = L'\0';    
    memset(&si,0,sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_FORCEOFFFEEDBACK;  

    if (bregisterTask)
    {
        hr = StringCchPrintf(param, LCM_MAX_PATH, L" /Create /SC ONSTART /TN \"%s\" /RU System /F /TR \"PowerShell.exe -NonInt -Window Hidden -Command \'Invoke-CimMethod -Namespace root/Microsoft/Windows/DesiredStateConfiguration -ClassName MSFT_DSCLocalConfigurationManager -MethodName PerformRequiredConfigurationChecks -Arg @{Flags = [System.UInt32]2 }\'\"", 
            DSC_RESTART_BOOTUP_TASK);
    }
    else
    {
        hr = StringCchPrintf(param, LCM_MAX_PATH, L" /Delete /F /TN \"%s\" ", DSC_RESTART_BOOTUP_TASK);        
    }


    if (FAILED(hr) || NitsShouldFault(NitsHere(), NitsAutomatic))
    {   
        if (SUCCEEDED(hr)) hr = E_FAIL;        
        return GetCimError(hr, extendedError, ID_LCMHELPER_PRINTF_ERROR);
    }  
    if(GetEnvironmentVariable(L"windir", wExe, LCM_MAX_PATH) ==0 )
    {
        return  GetCimWin32Error(GetLastError(), extendedError, ID_MODMAN_WINDIRENV_FAILED);
    }    
    hr = StringCchCatW(wExe, LCM_MAX_PATH, L"\\system32\\schtasks.exe");
    if( FAILED(hr))
    {
        return GetCimError(hr, extendedError, ID_ENGINEHELPER_CAT_ERROR);
    }

    bRes = CreateProcess(wExe, param,
        NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &ProcInfo);
    if (!bRes)
    {
        return  GetCimWin32Error(GetLastError(), extendedError, ID_ENGINEHELPER_CREATEPROCESS_ERROR);
    }

    WaitForSingleObject( ProcInfo.hProcess, INFINITE);
    if (GetExitCodeProcess(ProcInfo.hProcess,(LPDWORD)&dwExitCode) && dwExitCode != 0)
    {
        r = GetCimMIError(MI_RESULT_FAILED, extendedError, ID_ENGINEHELPER_CREATEPROCESS_ERROR);
    }

    CloseHandle(ProcInfo.hThread);
    CloseHandle(ProcInfo.hProcess);    

    return r;
}

MI_Result ScheduleRestart(
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Uint32 dwError = ERROR_SUCCESS;
    HANDLE hToken;
    MI_Boolean bRevertToSelf = MI_FALSE;
    Intlstr intlstr = Intlstr_Null;
    MI_Result result = MI_RESULT_OK;

    if (cimErrorDetails == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *cimErrorDetails = NULL;    // Explicitly set *cimErrorDetails to NULL as _Outptr_ requires setting this at least once. 

    DSC_EventWriteMessageScheduleReboot();

    GetResourceString(ID_LCMHELPER_SHUTDOWN_MESSAGE, &intlstr);
    if (!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &hToken))
    {
        if (GetLastError() == ERROR_NO_TOKEN)
        {
            SetLastError(ERROR_SUCCESS);
            if (!ImpersonateSelf(SecurityImpersonation))
            {
                return GetCimWin32Error(GetLastError(), cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
            }

            if (!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &hToken))
            {
                RevertToSelf();
                return GetCimWin32Error(GetLastError(), cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
            }

            bRevertToSelf = MI_TRUE;
        }
        else
        {
            return GetCimWin32Error(GetLastError(), cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        }
    }    

    result = EnableShutdownPrivilege(hToken, cimErrorDetails);
    if (result != MI_RESULT_OK)
    {
        if (bRevertToSelf)
        {
            RevertToSelf();
        }
        return result;
    }

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28159) //This is needed to reconfigure windows server to finish configuring the system by DSC.
#endif /* _PREFAST_ */

    dwError = InitiateSystemShutdownEx(NULL, 
        (MI_Char*)intlstr.str, 
        DSC_REBOOT_GRACEPERIOD, 
        TRUE,
        TRUE, 
        SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_MAINTENANCE | SHTDN_REASON_FLAG_PLANNED);

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

    if (bRevertToSelf)
    {
        RevertToSelf();
    }

    if (intlstr.str )
    {
        Intlstr_Free(intlstr);
    }

    if (!dwError)
    {
        return GetCimWin32Error(GetLastError(), cimErrorDetails, ID_LCMHELPER_SHUTDOWN_FAILED);
    }

    return MI_RESULT_OK;
}





MI_Result EnableShutdownPrivilege(
    _In_ HANDLE hToken,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Uint32 dwLen = 0;
    BOOL res = TRUE;
    BYTE *pBuffer;
    TOKEN_USER tu;
    TOKEN_PRIVILEGES * pPrivs = NULL;
    MI_Uint32 xCount = 0;

    if (cimErrorDetails == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *cimErrorDetails = NULL;    // Explicitly set *cimErrorDetails to NULL as _Outptr_ requires setting this at least once. 

    memset(&tu, 0, sizeof(TOKEN_USER));
    res = GetTokenInformation(hToken, TokenPrivileges, &tu, sizeof(TOKEN_USER), (PDWORD)&dwLen);    
    if (!res && ERROR_INSUFFICIENT_BUFFER !=  GetLastError())
    {

        return GetCimWin32Error(GetLastError(), cimErrorDetails, ID_LCMHELPER_COMPUTERNAMECONTEXT_ERROR);
    }

    pBuffer = (BYTE*)DSC_malloc(dwLen, NitsHere());
    if (pBuffer == NULL)
    {       
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
    }

    res = GetTokenInformation(hToken, TokenPrivileges, pBuffer, dwLen, (PDWORD)&dwLen);    
    if (!res && ERROR_INSUFFICIENT_BUFFER !=  GetLastError())
    {
        DSC_free(pBuffer);
        return GetCimWin32Error(GetLastError(), cimErrorDetails, ID_LCMHELPER_COMPUTERNAMECONTEXT_ERROR);
    }    

    pPrivs = (TOKEN_PRIVILEGES*)(BYTE*)pBuffer;
    for (xCount = 0; xCount < pPrivs->PrivilegeCount; xCount++)
    {
        pPrivs->Privileges[xCount].Attributes |= SE_PRIVILEGE_ENABLED;
    }   

    if (!AdjustTokenPrivileges(hToken, FALSE, pPrivs, 0, NULL, NULL))
    {
        DSC_free(pBuffer);      
        return GetCimMIError(MI_RESULT_FAILED, cimErrorDetails, ID_LCMHELPER_COMPUTERNAMECONTEXT_ERROR);
    }

    DSC_free(pBuffer);
    return MI_RESULT_OK;
}


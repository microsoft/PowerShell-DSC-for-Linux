/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26018 28301 26006) //this is unit test code don't worry about the warnings.
#endif /* _PREFAST_ */

#include <stdio.h>
#include <windows.h>
#include <nits.h>
#include "..\..\common\NitsPriority.h"
//#include "DscCoreREvents.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <mi.h>
#include <EngineHelperInternal.h>

#include <ModuleHandler.h>
#include <CAEngine.h>
#include <MSFT_DSCMetaConfiguration.h>

#include <lcm.traps.h>
#include <evntrace.h>

#include <Evntprov.h>
#include <winevt.h>



using namespace std;

#pragma comment(lib, "wevtapi.lib")
DWORD WINAPI SubscriptionCallback(EVT_SUBSCRIBE_NOTIFY_ACTION action, PVOID pContext, EVT_HANDLE hEvent);
LPCWSTR SetErrorBuffer(__out_ecount(bufLen) LPWSTR bufout, DWORD bufLen,  LPCWSTR bufin, HRESULT hr);


#define TEST_CONFIG_FILE L"testLCM.mof"
#define TEST_META_CONFIG_MOF L"testMetaConfig.mof"
#define CONFIGURATION_CURRENT L"%windir%\\System32\\Configuration\\Current.mof"
#define DSCENGINECACHE_LOCATION_MOF L"%windir%\\System32\\Configuration\\DSCEngineCache.mof"
#define METACONFIG_LOCATION_MOF L"%windir%\\system32\\configuration\\MetaConfig.mof"
#define TEST_MODULELOCATION L"%programfiles%\\WindowsPowershell\\Modules\\PsModuleForTestModuleForPull"
#define TEST_MODULE_DSCRESOURCES_LOCATION L"%programfiles%\\WindowsPowershell\\Modules\\PsModuleForTestModuleForPull\\DSCResources"
#define TEST_MODULE_RESOURCE_LOCATION L"%programfiles%\\WindowsPowershell\\Modules\\PsModuleForTestModuleForPull\\DSCResources\\TestModuleForPull"
#define DOWNLOADMANAGER_LOCATION L"%windir%\\System32\\WindowsPowershell\\v1.0\\Modules\\psdesiredstateconfiguration\\DownloadManager\\DSCFileDownloadManager"
#define DOWNLOADMANAGER_TEMPLOCATION L"%windir%\\System32\\WindowsPowershell\\v1.0\\Modules\\psdesiredstateconfiguration\\DownloadManager\\DSCFileDownloadManagerTEMP"
#define TEST_MODULELOCATION_PSD1 L"%programfiles%\\WindowsPowershell\\Modules\\PsModuleForTestModuleForPull\\PsModuleForTestModuleForPull.psd1"
#define TEST_MODULELOCATION_PSM1 L"%programfiles%\\WindowsPowershell\\Modules\\PsModuleForTestModuleForPull\\DSCResources\\TestModuleForPull\\TestModuleForPull.psm1"
#define TEST_MODULELOCATION_MOF L"%programfiles%\\WindowsPowershell\\Modules\\PsModuleForTestModuleForPull\\DSCResources\\TestModuleForPull\\TestModuleForPull.schema.mof"
//#define META_CONFIG_PULL L"instance of MSFT_KeyValuePair as $keyvaluepair1\n{\n      key=\"ServerUrl\";\n      value = \"http://localhost:8080/PSDSCPullServer/PSDSCPullServer.svc\";\n};\n   instance of MSFT_DSCMetaConfiguration\n{\n    ConfigurationID=\"d564b612-5436-43aa-a355-1aa8bdea22b6\";\n    DownloadManagerName=\"WebDownloadManager\";\n  ConfigurationModeFrequencyMins = 5;\n  DownloadManagerCustomData = {$keyvaluepair1};\n};\n"
#define META_CONFIG_PULL L"instance of MSFT_KeyValuePair as $keyvaluepair1\n{\n      key=\"SourcePath\";\n      value = \"C:\\\\ProgramData\\\\DSCFileRepository\";\n};\n instance of MSFT_KeyValuePair as $keyvaluepair2\n{\n      key=\"DestinationPath\";\n      value = \"C:\\\\ProgramData\\\\DSCFileDownloadLocation\";\n};\n     instance of MSFT_DSCMetaConfiguration\n{\n    ConfigurationID=\"d564b612-5436-43aa-a355-1aa8bdea22b6\";\n    DownloadManagerName=\"DSCFileDownloadManager\";\n  ConfigurationModeFrequencyMins = 5;\n  DownloadManagerCustomData = {$keyvaluepair1,$keyvaluepair2};\n};\n"

HANDLE g_PresentHandle = NULL;

#define ID_EVENT_PULL_ERROR             (1<<0)
#define ID_EVENT_PULL_GETCONFTRY        (1<<1)
#define ID_EVENT_PULL_GETMODULETRY      (1<<3)
#define ID_EVENT_PULL_GETACTIONTRY      (1<<4)
#define ID_EVENT_PULL_GETCONFSTATUS     (1<<5)
#define ID_EVENT_PULL_GETMODULSTATUS    (1<<6)
#define ID_EVENT_PULL_GETACTIONSTATUS   (1<<7)

DWORD gdwTotalFlags = 0;

struct Ptr
{
    void *ptr;
};

Ptr PtrVal = {NULL};



template<class T>
class CDeleteUs
{
protected:
    T *m_p;
public:
    CDeleteUs(_In_ T *p) : m_p(p) {}
    ~CDeleteUs() { delete [] m_p; }
};

LPCWSTR SetErrorBuffer(__out_ecount(bufLen) LPWSTR bufout, DWORD bufLen,  LPCWSTR bufin, HRESULT hr)
{
    StringCchPrintf(bufout, bufLen, L"%s\t Error = %x", bufin, hr);
    return bufout;
}


MI_Result DeleteConfig(_In_ LPCWSTR pwszFileName, NitsTrapHandle h)
{
    MI_Result result;
    wchar_t *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(pwszFileName, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(!DeleteFile(fileFull))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

void DeleteModuleDirectory( NitsTrapHandle h)
{
    MI_Result result;
    wchar_t *fileFull = NULL;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULELOCATION_PSD1, &fileFull, &cimError);

    if( fileFull )
    {
        DeleteFile(fileFull);
        free(fileFull);
        fileFull = NULL;
    }

    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULELOCATION_PSM1, &fileFull, &cimError);

    if( fileFull )
    {
        DeleteFile(fileFull);
        free(fileFull);
        fileFull = NULL;
    }

    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULELOCATION_MOF, &fileFull, &cimError);

    if( fileFull )
    {
        DeleteFile(fileFull);
        free(fileFull);
        fileFull = NULL;
    }


    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULE_RESOURCE_LOCATION, &fileFull, &cimError);

    if( fileFull )
    {
        RemoveDirectory(fileFull);
        free(fileFull);
        fileFull = NULL;
    }    

    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULE_DSCRESOURCES_LOCATION, &fileFull, &cimError);

    if( fileFull )
    {
        RemoveDirectory(fileFull);
        free(fileFull);
        fileFull = NULL;
    } 


    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULELOCATION, &fileFull, &cimError);

    if( fileFull )
    {
        RemoveDirectory(fileFull);
        free(fileFull);
        fileFull = NULL;
    } 


    //The error might be caused by nits fault injection
    NitsIgnoringError();

}

void MoveDirectory(_In_z_ MI_Char *from , _In_z_ MI_Char *to, NitsTrapHandle h)
{
    MI_Result result;
    wchar_t *fileFullFrom;
    wchar_t *fileFullTo;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(from, &fileFullFrom, &cimError);   
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(to, &fileFullTo, &cimError);   
    MoveFile(fileFullFrom, fileFullTo);
    free(fileFullFrom);
    free(fileFullTo);    
    //The error might be caused by nits fault injection
    NitsIgnoringError();    
}
DWORD GetEventID(EVT_HANDLE hEvent, LPWSTR *ActivityID,  
                                      LPWSTR *RelatedActivityID)
{
    if(ActivityID)
        *ActivityID = NULL;
    if(RelatedActivityID)
        *RelatedActivityID = NULL;
    DWORD status = ERROR_SUCCESS;
    EVT_HANDLE hContext = NULL;
    DWORD dwBufferSize = 0;
    DWORD dwBufferUsed = 0;
    DWORD dwPropertyCount = 0;
    PEVT_VARIANT pRenderedValues = NULL;
    WCHAR wsGuid[50];
    LPWSTR pwsSid = NULL;
    ULONGLONG ullTimeStamp = 0;
    ULONGLONG ullNanoseconds = 0;
    SYSTEMTIME st;
    FILETIME ft;
    DWORD dwReturnValue = 0;
    wchar_t ErrorBuffer[MAX_PATH];    

    // Identify the components of the event that you want to render. In this case,
    // render the system section of the event.
    hContext = EvtCreateRenderContext(0, NULL, EvtRenderContextSystem);
    if (NULL == hContext)
    {
        TSASSERT(false, SetErrorBuffer(ErrorBuffer, MAX_PATH ,L"EvtCreateRenderContext failed with %lu\n", status = GetLastError()), TLINE);
        goto cleanup;
    }

    // When you render the user data or system section of the event, you must specify
    // the EvtRenderEventValues flag. The function returns an array of variant values 
    // for each element in the user data or system section of the event. For user data
    // or event data, the values are returned in the same order as the elements are 
    // defined in the event. For system data, the values are returned in the order defined
    // in the EVT_SYSTEM_PROPERTY_ID enumeration.
    if (!EvtRender(hContext, hEvent, EvtRenderEventValues, dwBufferSize, pRenderedValues, &dwBufferUsed, &dwPropertyCount))
    {
        if (ERROR_INSUFFICIENT_BUFFER == (status = GetLastError()))
        {
            dwBufferSize = dwBufferUsed;
            pRenderedValues = (PEVT_VARIANT)malloc(dwBufferSize);
            if (pRenderedValues)
            {
                EvtRender(hContext, hEvent, EvtRenderEventValues, dwBufferSize, pRenderedValues, &dwBufferUsed, &dwPropertyCount);
            }
            else
            {
                TSASSERT(false,L"malloc failed\n", TLINE);
                dwReturnValue = ERROR_OUTOFMEMORY;
                goto cleanup;
            }
        }

        if (ERROR_SUCCESS != (status = GetLastError()))
        {
            TSASSERT(false, SetErrorBuffer(ErrorBuffer, MAX_PATH ,L"EvtRender failed with %d\n", GetLastError()),TLINE);
            goto cleanup;
        }
    }
    
    dwReturnValue = pRenderedValues[EvtSystemEventID].UInt16Val;
    /*GUID *gui = pRenderedValues[EvtSystemActivityID].GuidVal;
    if( gui != NULL  && ActivityID)
    {
        StringFromCLSID(*gui, (LPOLESTR *)ActivityID);
    }
    gui = pRenderedValues[EvtSystemRelatedActivityID].GuidVal;
    if( gui != NULL  && RelatedActivityID)
    {
        StringFromCLSID(*gui, (LPOLESTR *)RelatedActivityID);
    }    */
    cleanup:
    
        if (hContext)
            EvtClose(hContext);
    
        if (pRenderedValues)
            free(pRenderedValues);
    
        return dwReturnValue;
    
    
}

void ProcessEvent(EVT_HANDLE hEvent)
{
    DWORD status = ERROR_SUCCESS;
    EVT_HANDLE hContext = NULL;
    DWORD dwBufferSize = 0;
    DWORD dwBufferUsed = 0;
    DWORD dwPropertyCount = 0;
    PEVT_VARIANT pRenderedValues = NULL;
    WCHAR wsGuid[50];
    LPWSTR pwsSid = NULL;
    ULONGLONG ullTimeStamp = 0;
    ULONGLONG ullNanoseconds = 0;
    SYSTEMTIME st;
    FILETIME ft;
    wchar_t ErrorBuffer[MAX_PATH*2];
    
    hContext = EvtCreateRenderContext(0, NULL, EvtRenderContextUser);
    
    NitsAssert(hContext != NULL, SetErrorBuffer(ErrorBuffer, MAX_PATH , L"Unable to EvtCreateRenderContext.", GetLastError()));
    if(hContext)
    {
        
        if (!EvtRender(hContext, hEvent, EvtRenderEventValues, dwBufferSize, pRenderedValues, &dwBufferUsed, &dwPropertyCount))
        {
            if (ERROR_INSUFFICIENT_BUFFER == (status = GetLastError()))
            {
                dwBufferSize = dwBufferUsed;
                pRenderedValues = (PEVT_VARIANT)malloc(dwBufferSize);
                if (pRenderedValues)
                {
                    EvtRender(hContext, hEvent, EvtRenderEventValues, dwBufferSize, pRenderedValues, &dwBufferUsed, &dwPropertyCount);
                }
                else
                {
                    NitsAssert(false, SetErrorBuffer(ErrorBuffer, MAX_PATH, L"unable to allocate memory for EvtRender.", ERROR_OUTOFMEMORY));
                    goto cleanup;
                }
            }
    
            if (ERROR_SUCCESS != (status = GetLastError()))
            {
                NitsAssert(false, SetErrorBuffer(ErrorBuffer, MAX_PATH, L"EvtRender failed with error.", GetLastError()));
                goto cleanup;
            }
        }
        switch(GetEventID(hEvent, NULL, NULL))
        {
            case 4104:
                StringCchPrintf(ErrorBuffer, MAX_PATH*2,L"Event 4104 generated. ComponentName = %s, DownloadManagerName = %s", 
                                            pRenderedValues[1].StringVal, pRenderedValues[2].StringVal);

                TTRACE(ErrorBuffer);
                if( wcscmp(pRenderedValues[2].StringVal, L"DSCFileDownloadManager") == 0)
                {
                    gdwTotalFlags |= ID_EVENT_PULL_ERROR;
                }
                break;                
            case 4105:
                StringCchPrintf(ErrorBuffer, MAX_PATH*2,L"Event 4105 generated. DownloadManagerName = %s , ConfigurationId = %d\n", 
                                            pRenderedValues[1].StringVal, pRenderedValues[2].StringVal);
                TTRACE(ErrorBuffer);
                if( wcscmp(pRenderedValues[1].StringVal, L"DSCFileDownloadManager") == 0)
                {
                    gdwTotalFlags |= ID_EVENT_PULL_GETCONFTRY;
                }
                break;      
            case 4106:
                StringCchPrintf(ErrorBuffer, MAX_PATH*2,L"Event 4106 generated. DownloadManagerName = %s , ConfigurationId = %d\n, Modules = %s", 
                                            pRenderedValues[1].StringVal, pRenderedValues[2].StringVal, pRenderedValues[3].StringVal);
                TTRACE(ErrorBuffer);
                if( wcscmp(pRenderedValues[1].StringVal, L"DSCFileDownloadManager") == 0)
                {
                    gdwTotalFlags |= ID_EVENT_PULL_GETMODULETRY;
                }
                break;       
            case 4107:
                StringCchPrintf(ErrorBuffer, MAX_PATH*2,L"Event 4107 generated. DownloadManagerName = %s , ConfigurationId = %d\n, Checksum = %s, ComplianceStatus = %d", 
                                            pRenderedValues[1].StringVal, pRenderedValues[2].StringVal, pRenderedValues[3].StringVal, pRenderedValues[2].BooleanVal);
                TTRACE(ErrorBuffer);
                if( wcscmp(pRenderedValues[1].StringVal, L"DSCFileDownloadManager") == 0)
                {
                    gdwTotalFlags |= ID_EVENT_PULL_GETACTIONTRY;
                }
                break;       
            case 4108:
                StringCchPrintf(ErrorBuffer, MAX_PATH*2,L"Event 4108 generated. DownloadManagerName = %s", 
                                            pRenderedValues[1].StringVal);
                TTRACE(ErrorBuffer);
                if( wcscmp(pRenderedValues[1].StringVal, L"DSCFileDownloadManager") == 0)
                {
                    gdwTotalFlags |= ID_EVENT_PULL_GETCONFSTATUS;
                }
                break;   
            case 4109:
                StringCchPrintf(ErrorBuffer, MAX_PATH*2,L"Event 4109 generated. DownloadManagerName = %s", 
                                            pRenderedValues[1].StringVal);
                TTRACE(ErrorBuffer);
                if( wcscmp(pRenderedValues[1].StringVal, L"DSCFileDownloadManager") == 0)
                {
                    gdwTotalFlags |= ID_EVENT_PULL_GETMODULSTATUS;
                }
                break; 
            case 4110:
                StringCchPrintf(ErrorBuffer, MAX_PATH*2,L"Event 4110 generated. Status = %s, DownloadManagerName = %s", 
                                            pRenderedValues[1].StringVal, pRenderedValues[2].StringVal);
                TTRACE(ErrorBuffer);
                if( wcscmp(pRenderedValues[2].StringVal, L"DSCFileDownloadManager") == 0)
                {
                    gdwTotalFlags |= ID_EVENT_PULL_GETACTIONSTATUS;
                }
                break;                 
            default:
                NitsAssert(false, L"Unexpected event");
        }
        if((gdwTotalFlags &ID_EVENT_PULL_GETCONFTRY) &&
            (gdwTotalFlags & ID_EVENT_PULL_GETCONFSTATUS)  &&
            (gdwTotalFlags & ID_EVENT_PULL_GETMODULETRY)  &&
            (gdwTotalFlags & ID_EVENT_PULL_GETMODULSTATUS)  &&
            (gdwTotalFlags & ID_EVENT_PULL_GETACTIONTRY)  &&
            (gdwTotalFlags & ID_EVENT_PULL_GETACTIONSTATUS) &&
            (gdwTotalFlags & ID_EVENT_PULL_ERROR))

        {
            TTRACE(L"All the flags set properly");
            SetEvent(g_PresentHandle);
        }
    }
    cleanup:
        if(hContext)
            EvtClose(hContext); 
        if (pRenderedValues)
                free(pRenderedValues);
                
}


DWORD WINAPI SubscriptionCallback(EVT_SUBSCRIBE_NOTIFY_ACTION action, PVOID pContext, EVT_HANDLE hEvent)
{
    
    DWORD status = ERROR_SUCCESS;
    if((gdwTotalFlags &ID_EVENT_PULL_GETCONFTRY) &&
        (gdwTotalFlags & ID_EVENT_PULL_GETCONFSTATUS)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETMODULETRY)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETMODULSTATUS)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETACTIONTRY)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETACTIONSTATUS)&&
        (gdwTotalFlags & ID_EVENT_PULL_ERROR))
    {
        SetEvent(g_PresentHandle);
        return ERROR_SUCCESS;
    }    
    
    switch(action)
    {
        case EvtSubscribeActionError:
            NitsAssert(false, L"EvtSubscribeActionError not expected");
            SetEvent(g_PresentHandle);
            break;
        case EvtSubscribeActionDeliver:
            ProcessEvent(hEvent);
            break;
        default:
            NitsAssert(false, L"Unexpected flag");
            
    }
    return status;
}

MI_Result  RegisterForPullEvents(_Inout_ EVT_HANDLE *hSubscription)
{
    DWORD status = ERROR_SUCCESS;
    wchar_t ErrorBuffer[MAX_PATH];
    LPWSTR pwsPath = L"Application";
    LPWSTR pwsQuery = L"<QueryList><Query Id=\"0\" Path=\"Microsoft-Windows-DSC/Operational\"><Select Path=\"Microsoft-Windows-DSC/Operational\">*[System[(EventID=4104 or EventID=4105 or EventID=4106 or EventID=4107 or EventID=4108 or EventID=4109 or EventID=4110)]]</Select></Query></QueryList>";
    
    *hSubscription = EvtSubscribe(NULL, NULL, pwsPath, pwsQuery, NULL, NULL, 
                                     (EVT_SUBSCRIBE_CALLBACK)SubscriptionCallback, EvtSubscribeToFutureEvents);
    if( NitsAssert(hSubscription != NULL, SetErrorBuffer(ErrorBuffer, MAX_PATH , L"Unable to Subscribe for events.", GetLastError())))
    {
        return MI_RESULT_OK;
    }
    return MI_RESULT_FAILED;
    
}
MI_Result CopyConfig(_In_ LPCWSTR pwszFileName, NitsTrapHandle h)
{
    MI_Result result;
    wchar_t *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(pwszFileName, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(!CopyFile(TEST_CONFIG_FILE, fileFull, false))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

MI_Result CopyMetaConfigLocally(NitsTrapHandle h)
{
    MI_Result result;
    wchar_t *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(!CopyFile(fileFull, TEST_META_CONFIG_MOF,false))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

MI_Result SaveFile(_In_z_ const wchar_t* filePath,
                   _In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
                   MI_Uint32 dataSize)
{
    HANDLE fHandle = NULL;
    DWORD writeError = 0;
    BOOL fResult;
    MI_Uint32 len = 0;


    fHandle = CreateFile(filePath,
        GENERIC_WRITE,
        0 ,
        0,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if( fHandle == INVALID_HANDLE_VALUE )
    {
        return MI_RESULT_FAILED;
    }

    fResult = WriteFile(fHandle, ConfigData, dataSize, (LPDWORD)&len, NULL);
    if(!fResult )
    {
        if(fResult)
        {
            // Pass through a bogus error if we've faulted in an error otherwise success will be returned.
            SetLastError(ERROR_ACCESS_DENIED);
        }

        writeError = GetLastError();
        CloseHandle(fHandle);
        return MI_RESULT_FAILED;
    }

    CloseHandle(fHandle);
    return MI_RESULT_OK;
}

MI_Result UpdateMetaConfigForPull(NitsTrapHandle h)
{
    wchar_t *fileFull;
    MI_Result result;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);
    const MI_Uint8 *configData =    (const MI_Uint8 *) META_CONFIG_PULL;
    MI_Uint32 bufferSize = wcslen(META_CONFIG_PULL) * sizeof(wchar_t);
    return SaveFile(fileFull, configData, bufferSize);
}

MI_Result CopyMetaConfig(NitsTrapHandle h)
{
    MI_Result result;
    wchar_t *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(!CopyFile(TEST_META_CONFIG_MOF, fileFull, false))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}




NitsSetup0(InitPull, Ptr)

    MI_Instance *cimErrorDetails = NULL;
        NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", LCMTraps);
    NitsAssert(h != NULL, L"Failed to load LCMTraps!");
    NitsContext()->_Ptr->ptr = h;
    MI_Result miResult  = CopyMetaConfigLocally(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(L"Failed to take backup of metaConfig!");
    }

    miResult = UpdateMetaConfigForPull(h);
    NitsCompare(miResult, MI_RESULT_OK, L"Unable to update the meta configuration for certificate.");        
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_InitHandler)(L"MyMethod", &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, L"Failed to initialize LCM!");
    //Delete current configuration
    DeleteConfig(CONFIGURATION_CURRENT, h);
    //Delete DSCEngineCache.mof
    DeleteConfig(DSCENGINECACHE_LOCATION_MOF, h);    
    // Delete TestModuleForPull Module
    DeleteModuleDirectory(h);

    if(NULL == g_PresentHandle)
    {
        g_PresentHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
        if(!g_PresentHandle)
            NitsAssert(FALSE, L"Failed to create event");
    }


NitsEndSetup

NitsCleanup(InitPull)
    MI_Instance *cimErrorDetails = NULL;
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;
    MI_Result miResult  = CopyMetaConfig(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(L"Failed to copy back original meta config!");
    }        
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_UnInitHandler)(&cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, L"Failed to uninitialize LCM!");

    if (h != NULL)
        NitsCloseTrap(h);
    
    if(NULL != g_PresentHandle)
    {
        CloseHandle(g_PresentHandle);
        g_PresentHandle = NULL;
    }    

NitsEndCleanup


NitsIDXTest1(TestLCM_Pull_ValidateEvents, InitPull, PtrVal)

    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult = MI_RESULT_OK;
    NitsTrapHandle h = NitsContext()->_InitPull->_Ptr->ptr;
    EVT_HANDLE hSubscription = NULL;
    if(NitsCompare(RegisterForPullEvents(&hSubscription), MI_RESULT_OK, L"RegisterForPullEvents returned error"))
    {
        // Check event 4104
        //Execute to get configuration and modules.
        MoveDirectory(DOWNLOADMANAGER_LOCATION, DOWNLOADMANAGER_TEMPLOCATION, h);
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );
        MoveDirectory(DOWNLOADMANAGER_TEMPLOCATION, DOWNLOADMANAGER_LOCATION, h );

                //getchar();

        //Check rest of the events.
        //Execute to get configuration and modules.
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

        if( NitsCompare(miResult, MI_RESULT_OK, L"Call pull Execute failed"))
        {
            //Execute for Get-Action
            miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

            if( NitsCompare(miResult, MI_RESULT_OK, L"Call pull Execute failed"))
            {
                //Validate event.
                DWORD returnCode = ::WaitForSingleObject(g_PresentHandle,10000);
                if( WAIT_OBJECT_0 != returnCode) //Something went wrong, let us wait for 2 seconds
                {
                    NitsAssert(false, L"Events were not retreived within 10 seconds.");
                }
            }
        }
        EvtClose(hSubscription);
    }
    if( !((gdwTotalFlags &ID_EVENT_PULL_GETCONFTRY) &&
        (gdwTotalFlags & ID_EVENT_PULL_GETCONFSTATUS)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETMODULETRY)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETMODULSTATUS)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETACTIONTRY)  &&
        (gdwTotalFlags & ID_EVENT_PULL_GETACTIONSTATUS) &&
        (gdwTotalFlags & ID_EVENT_PULL_ERROR)))
    {
        NitsAssert(false, L"Not all events signaled as expected");
    }     
NitsEndTest





#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */


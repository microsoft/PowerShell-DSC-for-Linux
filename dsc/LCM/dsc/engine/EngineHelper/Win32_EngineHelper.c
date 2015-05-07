#include <windows.h>
#include "EngineHelper.h"
#include "Win32_EngineHelper.h"
#include "EventWrapper.h"
#include "DSC_SystemCalls.h"
#include "Resources_LCM.h"
#include <wbemcli.h>

extern HINSTANCE g_hModule;

extern HMODULE g_hPSInfraModuleHandle;
extern MI_Boolean g_hPSInfraModuleHandleInitialized;

struct _PSMethodAccessor g_PSMethodAccessor = {0};


/*For debugging purposes only.*/

void  MyDbgPrintfW(ULONG_PTR pBuff, const wchar_t * fmt, ...)
{
    wchar_t pBuff_[128];
    va_list argptr;

    UNREFERENCED_PARAMETER(pBuff);

    va_start(argptr, fmt);
    StringCchVPrintfW(pBuff_,128,fmt,argptr);
    OutputDebugStringW(pBuff_);
    va_end(argptr);
};

/* This method loads PSInfrastructure in the process. It assumes single caller at any given point of time (actually for the first time).
     If use case is multithreaded then variables g_hPSInfraModuleHandleInitialized and g_hPSInfraModuleHandle must be preserved.*/
HMODULE GetPSInfrastructureModuleHandle()
{
    MI_Char *envResolvedPath = NULL;
    MI_Instance *extendedError = NULL;
    if( g_hPSInfraModuleHandleInitialized )
    {
        return g_hPSInfraModuleHandle;
    }
    /* Resolve schema search path*/
    if( ResolvePath(&envResolvedPath, NULL, DSC_PLUGINWKR_PATH, NULL, &extendedError))
    {
        MI_Instance_Delete(extendedError);
        return NULL;
    }
    memset(&g_PSMethodAccessor, 0, sizeof(PSMethodAccessor));
    g_hPSInfraModuleHandle = LoadLibraryEx(envResolvedPath, NULL, 0);
    DSC_free(envResolvedPath);       
    g_hPSInfraModuleHandleInitialized = MI_TRUE;
    if( g_hPSInfraModuleHandle != NULL )
    {
        g_PSMethodAccessor.fn_StopCurrentPSConfiguration = (_StopCurrentPSConfiguration) GetProcAddress(g_hPSInfraModuleHandle, "StopCurrentPSConfiguration");
        g_PSMethodAccessor.fn_Get = (_Get) GetProcAddress(g_hPSInfraModuleHandle, "Get");
        g_PSMethodAccessor.fn_Set = (_Set) GetProcAddress(g_hPSInfraModuleHandle, "Set");
        g_PSMethodAccessor.fn_Test = (_Test) GetProcAddress(g_hPSInfraModuleHandle, "Test");
        g_PSMethodAccessor.fn_Pull_GetConfiguration_ManagedPlugin = (_Pull_GetConfiguration_ManagedPlugin) GetProcAddress(g_hPSInfraModuleHandle, "Pull_GetConfiguration_ManagedPlugin");
        g_PSMethodAccessor.fn_Pull_GetAction_ManagedPlugin = (_Pull_GetAction_ManagedPlugin) GetProcAddress(g_hPSInfraModuleHandle, "Pull_GetAction_ManagedPlugin");        
        g_PSMethodAccessor.fn_Pull_GetModules_ManagedPlugin = (_Pull_GetModules_ManagedPlugin) GetProcAddress(g_hPSInfraModuleHandle, "Pull_GetModules_ManagedPlugin");       
        g_PSMethodAccessor.fn_GetResourceProvider = (_GetResourceProvider) GetProcAddress(g_hPSInfraModuleHandle, "GetResourceProvider");                
    }
    return g_hPSInfraModuleHandle;
}

MI_Result  PS_StopCurrentPSConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError) 
{
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError);
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    }
    return g_PSMethodAccessor.fn_StopCurrentPSConfiguration(extendedError);
}

MI_Result  PS_Get(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Outptr_result_maybenull_ MI_Instance **outputInstance, _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError);   
    *outputInstance = NULL; 
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    }    
    return g_PSMethodAccessor.fn_Get( provContext, instance, regInstance, outputInstance, extendedError);
}

MI_Result  PS_Set(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError);    
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    }  
    return g_PSMethodAccessor.fn_Set(provContext, instance, regInstance, resultStatus, extendedError);
}

MI_Result  PS_Test(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Out_ MI_Boolean *testResult, _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError); 
    *testResult = MI_FALSE;
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    }  
    return g_PSMethodAccessor.fn_Test(provContext, instance, regInstance, resultStatus, testResult, extendedError);
}

MI_Result  PS_Pull_GetConfiguration_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig,                                                       
                                                      _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                                      _Outptr_result_maybenull_z_  MI_Char** result,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative)
{
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError);  
    *mofFileName = NULL;    
    *result = NULL; 
    *getActionStatusCode = 0;
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    } 
    return g_PSMethodAccessor.fn_Pull_GetConfiguration_ManagedPlugin(provContext, metaConfig, mofFileName, result, getActionStatusCode, extendedError, jobIdNative);
}

MI_Result  PS_Pull_GetAction_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_ const MI_Char *checkSum,
                                                      _In_ MI_Boolean complianceStatus,
                                                      _In_ MI_Uint32 lastGetActionStatusCode,
                                                      _Outptr_result_maybenull_z_  MI_Char** result, 
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative)
{
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError);    
    *result = NULL;     
    *getActionStatusCode = 0;
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    }    
    return g_PSMethodAccessor.fn_Pull_GetAction_ManagedPlugin(provContext, metaConfig, checkSum, complianceStatus, lastGetActionStatusCode, result, getActionStatusCode, extendedError,jobIdNative);
}

MI_Result  PS_Pull_GetModules_ManagedPlugin(_In_  void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_  MI_Char* downloadLocation,
                                                      _In_z_  MI_Char* mofFileName,
                                                      _In_ MI_Boolean allowModuleOverwrite,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative)
{
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError);       
    *getActionStatusCode = 0;
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    }    
    return g_PSMethodAccessor.fn_Pull_GetModules_ManagedPlugin(provContext, metaConfig, downloadLocation, mofFileName, allowModuleOverwrite,  getActionStatusCode, extendedError,jobIdNative);    
}


MI_Result  PS_GetResourceProvider(_In_ MI_StringA *classNameA, 
                                      _In_ MI_StringA *moduleNameA,
                                      _In_ MI_StringA *moduleVersionA,
                                      _Inout_ MI_StringA *providerNames,
                                      _Inout_ MI_StringA *mofPaths, 
                                      _Inout_ MI_ClassA *miClassArray,  
                                      _Inout_ MI_InstanceA *registrationInstances, 
                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                      _In_z_ MI_Char* jobId)
 {
    HMODULE mod = GetPSInfrastructureModuleHandle();
    MI_UNREFERENCED_PARAMETER(extendedError);    
    if( mod == NULL )
    {
        return GetCimError(MI_RESULT_NOT_SUPPORTED, extendedError, ID_ENGINEHELPER_PSINFRA_LOADERROR);
    }    
    return g_PSMethodAccessor.fn_GetResourceProvider(classNameA, moduleNameA, moduleVersionA, providerNames, mofPaths, miClassArray, registrationInstances, extendedError, jobId);
 }


void PrintClass(__in MI_Class *miClass)
{
    MI_Uint32 jCount = 0;

    MyDbgPrintfW(0, L"ClassName %S\n", miClass->classDecl->name);
    for(jCount = 0 ; jCount < miClass->classDecl->numProperties; jCount++)
    {
        MyDbgPrintfW(0, L"Name: %s , Flags: %x\n", miClass->classDecl->properties[jCount]->name, miClass->classDecl->properties[jCount]->flags);
    }
    MyDbgPrintfW(0, L"********************************\n");
        
}

/*Mapping copied from WMIV2 error codes conversion*/
 MI_Result MIResultFromHRESULT(HRESULT hr)
 {
     MI_Result r = MI_RESULT_OK;
     
     switch (hr)
     {
     case S_OK:
         r = MI_RESULT_OK;
         break;
     case WBEM_E_FAILED:
         r =  MI_RESULT_FAILED;
         break;
     case WBEM_E_ACCESS_DENIED:
         r = MI_RESULT_ACCESS_DENIED;
         break;
     case WBEM_E_INVALID_NAMESPACE:
         r = MI_RESULT_INVALID_NAMESPACE;
         break;
     case WBEM_E_INVALID_PARAMETER:
         r = MI_RESULT_INVALID_PARAMETER;
         break;
     case WBEM_E_INVALID_CLASS:
         r = MI_RESULT_INVALID_CLASS;
         break;
     case WBEM_E_NOT_FOUND:
         r = MI_RESULT_NOT_FOUND;
         break;
     case WBEM_E_NOT_SUPPORTED:
         r = MI_RESULT_NOT_SUPPORTED;
         break;
     case WBEM_E_CLASS_HAS_CHILDREN:
         r = MI_RESULT_CLASS_HAS_CHILDREN;
         break;  
     case WBEM_E_CLASS_HAS_INSTANCES:
         r = MI_RESULT_CLASS_HAS_INSTANCES;
         break;          
     case WBEM_E_INVALID_SUPERCLASS:
         r = MI_RESULT_INVALID_SUPERCLASS;
         break;          
     case WBEM_E_ALREADY_EXISTS:
         r = MI_RESULT_ALREADY_EXISTS;
         break;
     case WBEM_E_INVALID_PROPERTY:
         r = MI_RESULT_NO_SUCH_PROPERTY;
         break;
     case WBEM_E_TYPE_MISMATCH:
         r = MI_RESULT_TYPE_MISMATCH;
         break;
     case WBEM_E_INVALID_QUERY_TYPE:
         r = MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED;
         break; 
     case WBEM_E_INVALID_QUERY:
         r = MI_RESULT_INVALID_QUERY;
         break;  
     case WBEM_E_METHOD_NOT_IMPLEMENTED:
         r = MI_RESULT_METHOD_NOT_AVAILABLE;
         break;
     case WBEM_E_INVALID_METHOD:
         r = MI_RESULT_METHOD_NOT_FOUND;
         break;  
     case WBEM_E_INVALID_CONTEXT:
         r = MI_RESULT_INVALID_ENUMERATION_CONTEXT;
         break;        
     case WBEM_E_QUERY_NOT_IMPLEMENTED:
         r = MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED;  
         break;
     case WBEM_E_OUT_OF_MEMORY:
         r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
         break;
     case WBEM_E_SHUTTING_DOWN:
         r = MI_RESULT_SERVER_IS_SHUTTING_DOWN;
         break;
     case WBEM_S_TIMEDOUT:
         r = MI_RESULT_FAILED;
         break;
     default:
         if(SUCCEEDED(hr))
             r = MI_RESULT_OK;
         else
             r = MI_RESULT_FAILED;
         break;
     }
     return r;
 }

 

 MI_Result GetCimError(MI_Uint32 hr ,
                                _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                                _In_ MI_Uint32 errorStringId)
{
    Intlstr intlstr = Intlstr_Null;
    GetResourceString(errorStringId, &intlstr);

    MI_Utilities_CimErrorFromErrorCode( hr, MI_RESULT_TYPE_HRESULT, intlstr.str, cimErrorDetails);
    
    DSC_EventWriteCIMError(intlstr.str,hr);
    if( intlstr.str)
        Intlstr_Free(intlstr);
    
    return MIResultFromHRESULT(hr);
}


#pragma once


typedef MI_Result (MI_CALL *_StopCurrentPSConfiguration)(_Outptr_result_maybenull_ MI_Instance **extendedError) ;

typedef MI_Result (MI_CALL *_Get)(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Outptr_result_maybenull_ MI_Instance **outputInstance, _Outptr_result_maybenull_ MI_Instance **extendedError);
typedef MI_Result (MI_CALL *_Set)(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Outptr_result_maybenull_ MI_Instance **extendedError);
typedef MI_Result (MI_CALL *_Test)(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Out_ MI_Boolean *testResult, _Outptr_result_maybenull_ MI_Instance **extendedError);
typedef MI_Result (MI_CALL *_Pull_GetConfiguration_ManagedPlugin)(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig,                                                       
                                                      _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                                      _Outptr_result_maybenull_z_  MI_Char** result,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);

typedef MI_Result (MI_CALL *_Pull_GetAction_ManagedPlugin)(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_ const MI_Char *checkSum,
                                                      _In_ MI_Boolean complianceStatus,
                                                      _In_ MI_Uint32 lastGetActionStatusCode,
                                                      _Outptr_result_maybenull_z_  MI_Char** result, 
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);

typedef MI_Result (MI_CALL * _Pull_GetModules_ManagedPlugin)(_In_  void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_  MI_Char* downloadLocation,
                                                      _In_z_  MI_Char* mofFileName,
                                                      _In_ MI_Boolean allowModuleOverwrite,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);


typedef MI_Result (MI_CALL *_GetResourceProvider)(_In_ MI_StringA *classNameA, 
                                      _In_ MI_StringA *moduleNameA,
                                      _In_ MI_StringA *moduleVersionA,
                                      _Inout_ MI_StringA *providerNames,
                                      _Inout_ MI_StringA *mofPaths, 
                                      _Inout_ MI_ClassA *miClassArray,  
                                      _Inout_ MI_InstanceA *registrationInstances, 
                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                      _In_z_ MI_Char* jobId);


struct _PSMethodAccessor
{
    _StopCurrentPSConfiguration fn_StopCurrentPSConfiguration;
    _Get fn_Get;
    _Set fn_Set;
    _Test fn_Test;
    _Pull_GetConfiguration_ManagedPlugin fn_Pull_GetConfiguration_ManagedPlugin;
    _Pull_GetAction_ManagedPlugin fn_Pull_GetAction_ManagedPlugin;
    _Pull_GetModules_ManagedPlugin fn_Pull_GetModules_ManagedPlugin;
    _GetResourceProvider fn_GetResourceProvider;
} PSMethodAccessor;



MI_Result  PS_StopCurrentPSConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError) ;

MI_Result  PS_Get(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Outptr_result_maybenull_ MI_Instance **outputInstance, _Outptr_result_maybenull_ MI_Instance **extendedError);
MI_Result  PS_Set(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Outptr_result_maybenull_ MI_Instance **extendedError);
MI_Result  PS_Test(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Out_ MI_Boolean *testResult, _Outptr_result_maybenull_ MI_Instance **extendedError);
MI_Result  PS_Pull_GetConfiguration_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig,                                                       
                                                      _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                                      _Outptr_result_maybenull_z_  MI_Char** result,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);

MI_Result  PS_Pull_GetAction_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_ const MI_Char *checkSum,
                                                      _In_ MI_Boolean complianceStatus,
                                                      _In_ MI_Uint32 lastGetActionStatusCode,
                                                      _Outptr_result_maybenull_z_  MI_Char** result, 
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);

 MI_Result  PS_Pull_GetModules_ManagedPlugin(_In_  void *provContext, 
                                                       _In_ MI_Instance *metaConfig, 
                                                       _In_z_  MI_Char* downloadLocation,
                                                       _In_z_  MI_Char* mofFileName,
                                                       _In_ MI_Boolean allowModuleOverwrite,
                                                       _Out_ MI_Uint32* getActionStatusCode,
                                                       _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                       _In_ MI_Char* jobIdNative);


 MI_Result  PS_GetResourceProvider(_In_ MI_StringA *classNameA, 
                                      _In_ MI_StringA *moduleNameA,
                                      _In_ MI_StringA *moduleVersionA,
                                      _Inout_ MI_StringA *providerNames,
                                      _Inout_ MI_StringA *mofPaths, 
                                      _Inout_ MI_ClassA *miClassArray,  
                                      _Inout_ MI_InstanceA *registrationInstances, 
                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                      _In_z_ MI_Char* jobId);


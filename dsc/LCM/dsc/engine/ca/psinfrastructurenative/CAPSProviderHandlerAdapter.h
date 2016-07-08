/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#pragma once

// #include <windows.h>
// #include <stdio.h>
// #include <stdlib.h>

#if defined(__cplusplus)
# define EXTERNC extern "C"
# define BEGIN_EXTERNC extern "C" {
# define END_EXTERNC }
#else
# define EXTERNC /* empty */
# define BEGIN_EXTERNC /* empty */
# define END_EXTERNC /* empty */
#endif

BEGIN_EXTERNC

#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL Get(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Outptr_result_maybenull_ MI_Instance **outputInstance, _Outptr_result_maybenull_ MI_Instance **extendedError);
#else
MI_Result MI_CALL Get(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Outptr_result_maybenull_ MI_Instance **outputInstance, _Outptr_result_maybenull_ MI_Instance **extendedError);
#endif

#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL Set(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Outptr_result_maybenull_ MI_Instance **extendedError);
#else
MI_Result MI_CALL Set(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Outptr_result_maybenull_ MI_Instance **extendedError);
#endif

#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL Test(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Out_ MI_Boolean *testResult, _Outptr_result_maybenull_ MI_Instance **extendedError);
#else
MI_Result MI_CALL Test(_In_ void *provContext, _In_ MI_Instance *instance, _In_ const MI_Instance *regInstance, _Inout_ MI_Uint32 *resultStatus, _Out_ MI_Boolean *testResult, _Outptr_result_maybenull_ MI_Instance **extendedError);
#endif

#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL StopCurrentPSConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError);
#else
MI_Result MI_CALL StopCurrentPSConfiguration(_Outptr_result_maybenull_ MI_Instance **extendedError);
#endif

#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL GetResourceProvider(_In_ MI_StringA *classNameA, 
                                                            _In_ MI_StringA *moduleNameA,
                                                            _In_ MI_StringA *moduleVersionA,
                                                                                                                        _Inout_ MI_StringA *providerNames, 
                                                            _Inout_ MI_StringA *mofPaths, 
                                                            _Inout_ MI_ClassA *miClassArray,  
                                                            _Inout_ MI_InstanceA *registrationInstances, 
                                                            _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                            _In_z_ MI_Char* jobId);
#else
MI_Result MI_CALL GetResourceProvider(_In_ MI_StringA *classNameA, 
                                                                          _In_ MI_StringA *moduleNameA,
                                                                          _In_ MI_StringA *moduleVersionA,
                                                                          _Inout_ MI_StringA *providerNames,
                                                                          _Inout_ MI_StringA *mofPaths, 
                                                                          _Inout_ MI_ClassA *miClassArray,  
                                                                          _Inout_ MI_InstanceA *registrationInstances, 
                                                                          _Outptr_result_maybenull_ MI_Instance **extendedError,
                                      _In_z_ MI_Char* jobId);
#endif


#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL Pull_GetConfiguration_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                                      _Outptr_result_maybenull_z_  MI_Char** result,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);
#else
MI_Result MI_CALL Pull_GetConfiguration_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig,                                                       
                                                      _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                                      _Outptr_result_maybenull_z_  MI_Char** result,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);
#endif

#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL Pull_GetAction_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_ const MI_Char *checkSum,
                                                      _In_ MI_Boolean complianceStatus,
                                                      _In_ MI_Uint32 lastGetActionStatusCode,
                                                      _Outptr_result_maybenull_z_  MI_Char** result, 
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);
#else
MI_Result MI_CALL Pull_GetAction_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_ const MI_Char *checkSum,
                                                      _In_ MI_Boolean complianceStatus,
                                                      _In_ MI_Uint32 lastGetActionStatusCode,
                                                      _Outptr_result_maybenull_z_  MI_Char** result, 
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);


#endif

#if defined (_CA_IMPORT_)
__declspec(dllimport) MI_Result MI_CALL Pull_GetModules_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_  MI_Char* downloadLocation,
                                                      _In_z_  MI_Char* mofFileName,
                                                      _In_ MI_Boolean allowModuleOverwrite,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);
#else
MI_Result MI_CALL Pull_GetModules_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_  MI_Char* downloadLocation,
                                                      _In_z_  MI_Char* mofFileName,
                                                      _In_ MI_Boolean allowModuleOverwrite,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative);
#endif


END_EXTERNC

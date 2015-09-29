#ifndef _REGISTRATIONMANAGER_H
#define _REGISTRATIONMANAGER_H

#include <MI.h>
#include <EngineHelperInternal.h>

/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

typedef struct _RegistrationRequest
{
    // This is an instance of either OMI_ConfigurationDownloadManager, OMI_ResourceModuleManager or OMI_ReportManager
    MI_Instance* registrationData;

    // The set of configuration names that an agent can register for
    MI_StringA configurationNames;

    // This denotes whether we are regsitering to a ConfigurationDownloadManager, ResourceModuleManager or ReportManager. In the managed layer, we use this information to extract details from metaconfig
    // 1 -> ConfigurationDownloadManager
    // 2 -> ResourceModuleManager
    // 3 -> ReportManager
    MI_Uint32 typeOfManagerInstance;

} RegistrationRequest;

typedef struct _RegistrationManager
{
    MI_Char* agentId;

    // This is a list of Server URLs for which registration has succeeded
    MI_Char** serverURLs;

    // Once a server URL has registered, there will be a thumbprint for the certificate
    MI_Char** serverCertificateThumbprints;

    MI_Uint32 numberOfServerURLs;
    
} RegistrationManager;

extern void * g_registrationManager;

MI_Result MI_CALL RegistrationManager_New(
    _Outptr_ RegistrationManager** out,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

void MI_CALL RegistrationManager_Destroy(
    _Inout_ RegistrationManager* self);

MI_Result MI_CALL RegistrationManager_RunRequest(
                                    _In_ RegistrationManager* self,
                                     _In_ RegistrationRequest *item,
                                     _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

/*These are private methods*/

MI_Result RegistrationManager_HandleRequest(
    _In_ RegistrationManager* self,
    _In_ RegistrationRequest *item,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

#endif

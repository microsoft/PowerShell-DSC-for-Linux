/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef __REGISTRATIONMANAGER_HELPER_H_
#define __REGISTRATIONMANAGER_HELPER_H_

#include <MI.h>

// Total Number of Server URLs that we want to maintain in our Registration Manager
#define NUMBEROFSERVERURLS 100

#define DSC_AGENTID_KEY L"Software\\Microsoft\\DesiredStateConfiguration"

// This method tells you whether we need to do registration for a particular ServerURL
MI_Boolean ShouldDoRegistration(
    _In_ RegistrationManager* self,
    _In_ RegistrationRequest* request,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);


MI_Result GetAgentIdFromRegistry(
    _Outptr_result_maybenull_z_ MI_Char** agentId, 
    _Inout_ MI_Boolean *shouldGenerateAgentId);

MI_Result WriteAgentIdToRegistry(
    _In_z_ MI_Char* agentId,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result Register(
    _In_ RegistrationManager* self,
    _In_ RegistrationRequest* request,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

// Once registration succeeds, this method is called.
// This caches the serverURL from registration request to RegistrationManager's cache
MI_Result CacheServerURL(
    _In_ RegistrationManager* self,
    _In_ MI_Instance* registrationData,
    _In_z_ MI_Char* thumbprint,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

// Helper method to write the server URL to RegistrationManager's cache
MI_Result WriteServerURLToCache(
    _In_ RegistrationManager* self,
    _In_z_ MI_Char* serverURL,
    _In_z_ MI_Char* thumbprint,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

// This is called when creating an instance of RegistrationManager
// This populates ServerURLs in RegistrationManager's cache from DSC Engine Cache
MI_Result PopulateServerURLs(
    _In_ RegistrationManager* self,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);


// Helper method to read the ServerURLs from DSC Engine Cache
MI_Result GetRegisteredServerURLsFromCache(
    _Outptr_result_maybenull_z_ MI_Char** registeredServerURLs,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

// This is called after registration succeeds to write ServerURL to DSC Engine Cache
MI_Result UpdateServerURLsToDSCCache(
    _In_ RegistrationManager *self,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

// Helper method to format the server URLs in RegistrationManager cache in the format expected by DSC Engine Cache
MI_Result FormatServerURLsForDscCache(
    _In_ RegistrationManager *self,
    _Outptr_result_maybenull_z_ MI_Char** registeredServerURLs,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result InitializeServerURLs(
    _In_ RegistrationManager *self,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

// Check the cache for a given serverUrl
MI_Result GetThumbprintForRegisteredServerURL(
    _In_ RegistrationManager* self,
    _In_ MI_Instance* registrationData,
    _Outptr_result_maybenull_z_ MI_Char** thumbprint,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

#endif

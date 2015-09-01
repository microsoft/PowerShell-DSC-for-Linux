#ifndef _REGISTRATIONMANAGER_H
#define _REGISTRATIONMANAGER_H

#include <MI.h>
#include <EngineHelperInternal.h>

/*
        Registration Manager handles the following tasks for LCM
        1) Register the LCM with the Pull or Reporting Servers
        2) Keeps track of the AgentId
        3) Keeps track of which serverURLs have registered successfully.
    
    Debugging tips:
    

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

/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

#ifndef _LOCALCONFIGMANAGERHELPER_H_
#define _LOCALCONFIGMANAGERHELPER_H_
#include "MI.h"

#include "ModuleHandler.h"
#if defined(_MSC_VER)
#include "MSFT_DSCMetaConfiguration.h"
#else
#include "omi_msft_dsclocalconfigurationmanager.h"
#endif

#include "LocalConfigManagerHelperForCA.h"

#define LCM_MAX_PATH MAX_PATH*4
#define THIRTY_ONE_DAYS_IN_SECONDS 2678400
#define FIFTEEN_MINUTES_IN_SECONDS 900
#define GET_ACTION_STATUS_CODE_SUCCESS 0

// Constants used only for API tests
#define LCM_STATUSCODE_HISTORY_STR_SIZE 3	// 1 for code, 1 for comma seperator, 1 for tailing null
#define MAX_LCM_STATUSCODE_HISTORY_SIZE 50

typedef struct _RichErrorInformation
{
    const wchar_t *error_type;
    int error_code;
    wchar_t *error_message;
} RichErrorInformation;

RichErrorInformation g_richResult;
MI_Char *g_PendingConfigFileName;
MI_Char *g_GetConfigFileName;
MI_Char *g_CurrentConfigFileName;
MI_Char *g_PreviousConfigFileName;
MI_Char *g_MetaConfigFileName;
MI_Char *g_MetaConfigTmpFileName;
MI_Char *g_ConfigChecksumFileName;
MI_Char *g_PullRunLogFileName;
MI_Char *g_LCMStatusCodeHistory;
MI_Boolean g_LCMPendingReboot;
MSFT_DSCMetaConfiguration *g_metaConfig;
MI_Instance *g_DSCInternalCache;

extern MI_Char* overWroteUserSpecifiedRefreshFreqMins;
extern MI_Boolean MetaMofCorrupted;

typedef struct _ExpandedSystemPath
{ 
    const MI_Char *dscSystemFile; 
    MI_Char **expandedPath;
} ExpandedSystemPath;

#ifdef __cplusplus
extern "C"
{
#endif

    MI_Result InitHandler(_In_z_ const MI_Char* methodName, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result UnInitHandler(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ApplyConfig(_In_ LCMProviderContext *lcmContext,
                             _In_z_ const MI_Char *configFileLocation,
                             _In_ ModuleManager *moduleManager, 
                             _In_ MI_Uint32 flags,
                             _Inout_ MI_Uint32 *resultStatus,
                            _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ApplyPendingConfig(_In_ LCMProviderContext *lcmContext,
                         _In_ ModuleManager *moduleManager,
                         _In_ MI_Uint32 flags,
                         _Inout_ MI_Uint32 *resultStatus,
                         _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ApplyCurrentConfig(_In_ LCMProviderContext *lcmContext,
                         _In_ ModuleManager *moduleManager, 
                         _In_ MI_Uint32 flags,
                         _Inout_ MI_Uint32 *resultStatus,
                         _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ApplyMetaConfig(_In_ LCMProviderContext *lcmContext,
        _In_ ModuleManager *moduleManager, 
        _In_ MI_Uint32 flags,
        _Inout_ MI_Uint32 *resultStatus,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result DoPullServerRefresh(_In_ MI_Context *context, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

	MI_Result UpdateMetaConfigWithLCMState(_In_z_ MI_Uint32 *lcmStatusCode, _Inout_ MI_Instance *metaConfigInstance);

    MI_Result UpdateMetaConfigWithCertificateThumbprint(_In_z_ MI_Char *certificateThumbprint, _Inout_ MI_Instance *metaConfigInstance,
                                            _Out_ MI_Boolean *bMetaConfigUpdated, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result UpdateMetaConfigForWebDownloadManager(_In_z_ MI_Char *certificateThumbprint, _Inout_ MI_Instance *metaConfigInstance, 
                            _Inout_ MI_InstanceA *customData, _Inout_ MI_Boolean *bMetaConfigUpdated,
                            _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);    

    MI_Result RegisterTask(_In_ MI_Instance *currentMetaConfigInstance, _In_z_ const MI_Char *propName, _In_z_ const MI_Char *taskName,
                            _In_ MI_Uint32 defaultValue, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);    

    MI_Result IsRegisterdForPull(_In_ MI_Instance *currentMetaConfigInstance, _Out_ MI_Boolean *isPullEnabled, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);    

    MI_Result SaveFile(_In_z_ const MI_Char* filePath,
        _In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
        MI_Uint32 dataSize,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ClearBuiltinProvCache(
    _In_z_ const MI_Char* cachePath,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result LoadFromPullRunLogFile(_Out_ MI_Uint32 *lastRun, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);
    
    MI_Result SavePullRunLogFile(_In_ MI_Uint32 maxRun, _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result RetryDeleteFile(_In_z_ const MI_Char* filePath);

    MI_Result SaveMetaConfig(_In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
        MI_Uint32 dataSize,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result CallSetConfiguration(_In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
        MI_Uint32 dataSize,
        MI_Uint32 dwFlags,
        MI_Boolean force,
        _In_ MI_Context* context,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);
    
    MI_Result CallRestoreConfiguration(MI_Uint32 dwFlags,
                               _In_ MI_Context* context,
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result CallGetConfiguration(_In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
        MI_Uint32 dataSize,
        _Inout_ MI_InstanceA *outInstances,
        _In_ MI_Context* context,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result CallTestConfiguration(_Out_ MI_Boolean *testStatus, 
        _Inout_ MI_StringA *resourceId,
        _In_ MI_Context* context,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);    

    MI_Result CallConsistencyEngine(_In_ MI_Context* context,
        _In_ MI_Uint32 invokeMode,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);
    
    MI_Result RunConsistencyEngine(_In_ MI_Context* context,
        _In_ MI_Uint32 flags,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);    
    
    MI_Result SetConfiguration(_In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
        MI_Uint32 dataSize,
        MI_Boolean force,
        _In_ LCMProviderContext *lcmContext,
        MI_Uint32 dwFlags,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ExpandPath(_In_z_ const MI_Char * pathIn,
        _Outptr_result_maybenull_z_ MI_Char **expandedPath,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result CopyConfigurationFile(_In_z_ const MI_Char *locationFrom,
        _In_z_ const MI_Char *locationTo,
        MI_Boolean backUpNeeded,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result MoveConfigurationFiles(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result GetFullPath(_In_z_ const MI_Char *fileName,
        _Outptr_result_maybenull_z_ MI_Char **fullPath,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ValidateConfigurationDirectory(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    void GetRealBufferIndex(_In_ const MI_ConstUint8A *buffer, 
        _Out_ MI_Uint32 *bufferIndex);

    void LCM_WriteMessageInfo(
    _In_ LCMProviderContext *lcmContext,  
    _In_opt_z_ const MI_Char *computerName, 
    _In_ MI_Uint32 channel,
    _In_z_ const MI_Char *userSid);
   
    void LCM_WriteMessage_Internal_Tokenized(
        _In_ LCMProviderContext *lcmContext,  
        _In_z_ const MI_Char *resourceId, 
        _In_ MI_Uint32 channel, 
        _In_z_ const MI_Char *message,
        _In_ MI_Boolean bRunWhatIf);

    void LCM_WriteMessage_EngineInternal( _In_ LCMProviderContext *lcmContext,  
        _In_z_ const MI_Char *resourceId, 
        _In_ MI_Uint32 channel, 
        _In_z_ const MI_Char *message
        );    

    void LCM_WriteMessage_ProviderInternal( _In_ LCMProviderContext *lcmContext,  
        _In_z_ const MI_Char *resourceId, 
        _In_ MI_Uint32 channel, 
        _In_z_ const MI_Char *message
        );     
    
    void LCM_WriteMessageInfo_Internal( _In_ LCMProviderContext *lcmContext,  
        _In_opt_z_ const MI_Char *computerName, 
        _In_ MI_Uint32 channel, 
        _In_z_ const MI_Char *userSid
        );

    void LCM_BuildMessage(_In_ LCMProviderContext *lcmContext,  
        _In_ MI_Uint32 errorStringId,
        _In_z_ const MI_Char *resourceId, 
        _In_ MI_Uint32 channel); 
    

    MI_Uint32 GetCallSetConfigurationFlags(_In_opt_ MI_Context* context);

    MI_Result UpdateCurrentStatus(
        _In_opt_ MI_Boolean *complianceStatus,
        _In_opt_ MI_Uint32 *getActionStatusCode,
		_In_opt_ MI_Uint32 *lcmStatusCode,
        _Outptr_result_maybenull_ MI_Instance **extendedError);

    void GetLatestStatus(
        _Out_ MI_Boolean *complianceStatus,
        _Out_ MI_Uint32 *getActionStatusCode,
		_Out_ MI_Uint32 *lcmStatusCode);

    MI_Result InitCacheAndMetaConfig(_Outptr_result_maybenull_ MSFT_DSCMetaConfiguration **metaConfig,
                         _Outptr_result_maybenull_ MI_Instance **DSCInternalCache,
                         _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);    

    MI_Result InitMetaConfig(_In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MSFT_DSCMetaConfiguration **metaConfig,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result UpdateDefaultValueForMetaConfig(
        _Inout_ MI_Instance* self);

    MI_Result InitDSCInternalCache(_In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MI_Instance **DSCInternalCache,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);    

    MI_Result UpdateDSCCacheInstance(
        _In_ MI_Application *miApp,
        _Inout_ MI_Instance **dscCacheInstance, 
        _In_opt_ MI_Boolean* complianceStatus,
        _In_opt_ MI_Uint32* getActionStatusCode,
		_In_opt_ MI_Uint32* lcmStatusCode,
        _Outptr_result_maybenull_ MI_Instance **extendedError);

	MI_Result UpdateLCMStatusCodeHistory(
		_In_ MI_Instance **dscInternalCache,
		_Outptr_result_maybenull_z_ MI_Char **lcmStatusCodeHistory);

	MI_Result GetLCMStatusCodeHistory(
		_Outptr_result_maybenull_z_ MI_Char **lcmStatusCodeHistory,
		_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result SerializeMetaConfig(_In_ const MSFT_DSCMetaConfiguration *metaConfig,
        _In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result DeseralizeMetaConfig(_Outptr_result_maybenull_ MSFT_DSCMetaConfiguration **metaConfig,
        _In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result TaskHelper(_In_z_ MI_Char* taskPath,
        _In_z_ MI_Char* taskName,
        _In_z_ const MI_Char* methodName,
        _In_ ModuleManager *moduleManager,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);


    MI_Result InitPath(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    const MI_Char *GetPendingConfigFileName();

    const MI_Char * GetGetConfigFileName();

    const MI_Char * GetConfigChecksumFileName();

    const MI_Char *GetCurrentConfigFileName();

    const MI_Char *GetPreviousConfigFileName();

    const MI_Char *GetMetaConfigTmpFileName();

    const MI_Char *GetPullRunLogFileName();

    const MI_Char *GetConfigPath();

	const MI_Char *GetCurrentLCMStatusCodeHistory();

	MI_Result SetLCMStatusBusy();
	
	MI_Result SetLCMStatusReady();
	
	MI_Result SetLCMStatusReboot();

#if defined(_MSC_VER)

    
    MI_Result LCM_Pull_GetConfiguration(_In_ LCMProviderContext *lcmContext,
                               _In_ ModuleManager *moduleManager,
                               _In_ MI_Instance *metaConfigInstance,                               
                               _Outptr_result_maybenull_z_  MI_Char** resultStatus,
                               _Inout_ MI_Uint32 *resultExecutionStatus,
                               _Out_ MI_Uint32 *getActionStatusCode,
                               _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result LCM_Pull_GetAction(_In_ LCMProviderContext *lcmContext,
                          _In_ MI_Instance *metaConfigInstance,
                          _In_z_ MI_Char *checkSum,
                          _In_ MI_Boolean bIsCompliant,
                          _In_ MI_Uint32 lastGetActionStatusCode,
                          _Outptr_result_maybenull_z_  MI_Char** resultStatus,
                          _Out_  MI_Uint32* getActionStatusCode,
                          _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

     MI_Result MI_CALL LCM_Pull_Execute(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

#endif     


     void ConcatStrings(_Outptr_result_z_ MI_Char** target,_In_ MI_Uint32 padding,_In_z_ MI_Char* source1, _In_z_ MI_Char* source2);
    MI_Result TimeToRunConsistencyCheck(_Out_ MI_Boolean *bRunConsistencyCheck, 
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result TimeToRunConsistencyCheck(_Out_ MI_Boolean *bRunConsistencyCheck, 
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result RegisterConsistencyTask( _In_ MI_Instance *currentMetaConfigInstance, 
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result RegisterStartAtBootTask(_In_ MI_Boolean bregisterTask, 
                                           _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Boolean ShouldAutoCorrect(_In_z_ MI_Char* configurationMode);

    MI_Boolean ShouldMonitor(_In_z_ MI_Char* configurationMode);

    void GetFullMessageWithTokens(_In_z_ const MI_Char * deviceName, _In_z_ const MI_Char * resourceId,
                     _In_z_ const MI_Char * message, _In_ LCMProviderContext *lcmContext, Intlstr *intlstr);

#ifdef __cplusplus

}

#endif


#endif //_LOCALCONFIGMANAGERHELPER_H_

/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved.

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _LOCALCONFIGMANAGERHELPER_H_
#define _LOCALCONFIGMANAGERHELPER_H_
#include "MI.h"

#include "ModuleHandler.h"
#include "MSFT_DSCMetaConfiguration.h"

#include "LocalConfigManagerHelperForCA.h"
#include "hashmap.h"

#define LCM_MAX_PATH MAX_PATH*4
#define THIRTY_ONE_DAYS_IN_SECONDS 2678400
#define FIFTEEN_MINUTES_IN_SECONDS 900
#define REFRESH_MINIMUM_IN_SECONDS 60
#define GET_ACTION_STATUS_CODE_SUCCESS 0

// Constants used only for API tests
#define LCM_STATUSCODE_HISTORY_STR_SIZE 3       // 1 for code, 1 for comma seperator, 1 for tailing null
#define MAX_LCM_STATUSCODE_HISTORY_SIZE 50

typedef struct _RichErrorInformation
{
    const wchar_t *error_type;
    int error_code;
    wchar_t *error_message;
} RichErrorInformation;

RichErrorInformation g_richResult;
MI_Char *g_PendingConfigFileName;
MI_Char *g_PendingConfigTmpFileName;
MI_Char *g_GetConfigFileName;
MI_Char *g_InventoryFileName;
MI_Char *g_InventoryReportFileName;
MI_Char *g_CurrentConfigFileName;
MI_Char *g_PreviousConfigFileName;
MI_Char *g_MetaConfigFileName;
MI_Char *g_MetaConfigTmpFileName;
MI_Char *g_ConfigChecksumFileName;
MI_Char *g_PullRunLogFileName;
MI_Char *g_LCMStatusCodeHistory;
MI_Char* g_PartialConfigDataStoreName;
MI_Char *g_PartialConfigBaseDocumentInstanceFileName;
MI_Char *g_PartialConfigBaseDocumentInstanceTmpFileName;
MI_Boolean g_LCMPendingReboot;
MSFT_DSCMetaConfiguration *g_metaConfig;
MI_Instance *g_DSCInternalCache;

RecursiveLock gExecutionLock;

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

    MI_Result DoPullServerRefresh(
        _In_ MI_Instance *metaConfigInstance,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

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

    MI_Result CallPerformInventory(
        _In_ MI_Char * InMOF,
        _Inout_ MI_InstanceA *outInstances,
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

    MI_Result CopyConfigAndRemoveSource(_In_z_ const MI_Char *sourceConfigFileName,
        _In_z_ const MI_Char *destinationConfigFileName,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result GetFullPath(_In_z_ const MI_Char* directoryName,
        _In_z_ const MI_Char *fileName,
        _Outptr_result_maybenull_z_ MI_Char **fullPath,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ValidateConfigurationDirectory(_Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ProcessPartialConfigurations(
        _In_ LCMProviderContext *lcmContext,
        _In_ ModuleManager *moduleManager,
        _In_ MI_Uint32 flags,
        _Inout_ MI_Uint32 *resultStatus,
        _In_ MI_Result(*ConfigurationProcessor)
        (
            _In_ LCMProviderContext *lcmContext,
            _In_ ModuleManager *moduleManager,
            _In_ MI_Uint32 flags,
            _In_ MI_Instance * documentIns,
            _In_ MI_InstanceA *resourceInstances,
            _In_ MI_Instance *metaConfigInstance,
            _Inout_ MI_Uint32 *resultStatus,
            _Outptr_result_maybenull_ MI_Instance **cimErrorDetails
            ),
        _In_ MI_Instance *metaConfigInstance,
        _In_ MI_InstanceA* resourceInstances,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result DependPartialConfigExist(_In_ MI_Instance *partialConfig,
                                       _In_ HashMap* self,
                                       _Out_ MI_Boolean *dependsOnExist,
                                       _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    /*Function to merge N partial configurations.*/
    MI_Result MergePartialConfigurations(_In_ LCMProviderContext *lcmContext,
        _In_ ModuleManager* moduleManager,
        _In_z_ const MI_Char* targetMofFile,
        _In_z_ const MI_Char* targetBaseDocumentMergedFile,
        _Outptr_result_maybenull_ MI_Instance** cimErrorDetails);

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
        _In_opt_ MI_Char *registeredServerURLs,
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
        _In_opt_ MI_Char* registeredServerURLs,
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

    const MI_Char * GetPendingConfigTmpFileName();

    const MI_Char * GetGetConfigFileName();

    const MI_Char * GetInventoryFileName();

    const MI_Char * GetInventoryReportFileName();

    const MI_Char * GetConfigChecksumFileName();

    const MI_Char *GetCurrentConfigFileName();

    const MI_Char *GetPreviousConfigFileName();

    const MI_Char *GetMetaConfigTmpFileName();

    const MI_Char *GetPullRunLogFileName();

    const MI_Char *GetConfigPath();

    const MI_Char *GetCurrentLCMStatusCodeHistory();

    /*This will return the extension for partial Configuration files*/
    const MI_Char*GetMofExtension();

    /*This will return the checksum extension for partial Configuration files*/

    const MI_Char * GetMofChecksumExtension()    ;

    /*This will point to the unique partial configuration name*/
    const MI_Char*GetPartialConfigDataStore();

    /*This will point to the unique partial configuration name*/
    const MI_Char*GetPartialConfigSuffix();

    const MI_Char * GetPartialConfigBaseDocumentInstanceFileName();

    const MI_Char * GetPartialConfigBaseDocumentInstanceTmpFileName();

    /*Function to obtain the partial configuration file name*/
    MI_Result GetPartialConfigStoreLocation(_In_ ModuleManager * moduleManager,
        _In_count_(documentSize) const MI_Uint8* configData,
        _In_ MI_Uint32 documentSize,
        _Outptr_result_maybenull_ MI_Instance** cimErrorDetails,
        _Outptr_result_maybenull_z_  MI_Char** configFileName);
    /*Function to add instances into the destination file.*/
    MI_Result SerializeInstanceArrayToFile(_In_ MI_InstanceA *miInstanceArray,
        _In_z_ const MI_Char* filePath,
        _Outptr_result_maybenull_ MI_Instance** cimErrorDetails,
        _In_z_ const MI_Char* fileOpenMode,
        _In_ MI_Boolean isLockSensitive,
        _Inout_ MI_Serializer *pSerializer);

    /*method to get partial configuration name*/
    MI_Result GetPartialConfigurationName(_In_ MI_Instance *partialConfiguration,
                                      _Outptr_result_maybenull_z_ const MI_Char** name,
                                      _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    /*Returns constant memory for partialconfigurations held by meta config instance*/
    MI_Result GetPartialConfigurations(_In_ MI_Instance *metaInstance, _Inout_ MI_InstanceA *partialConfigurations,
                                            _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result ValidateConfigurationDirectory(
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    /*Function to add a single instance to a destination file*/
    MI_Result SerializeSingleInstanceToFile(_In_ MI_Instance *miInstance,
        _In_z_ const MI_Char* filePath,
        _Outptr_result_maybenull_ MI_Instance** cimErrorDetails,
        _In_z_ const MI_Char* fileOpenMode,
        _In_ MI_Boolean isLockSensitive,
        _Inout_ MI_Serializer *pSerializer);

        MI_Result SetLCMStatusBusy();

        MI_Result SetLCMStatusReady();

        MI_Result SetLCMStatusReboot();

    MI_Result DeleteRegistrationKeyFromManagerInstance(
        _In_ LCMProviderContext *lcmContext,
        _Inout_ MI_Instance **managerInstance,
        MI_Uint32 typeOfDownloadManagerInstance,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result RegisterWithServers(_In_ LCMProviderContext *lcmContext,
        _In_ MI_Instance *metaConfigInstance,
        _In_ MI_Uint32 isPull,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result RegisterWithPullServers(_In_ LCMProviderContext *lcmContext,
        _In_ MI_Instance *metaConfigInstance,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result RegisterWithReportingServers(_In_ LCMProviderContext *lcmContext,
        _In_ MI_Instance *metaConfigInstance,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result DoRegistration(
        _In_ LCMProviderContext* lcmContext,
        _Inout_ MI_InstanceA *managerInstances,
        _In_ MI_Uint32 typeOfDownloadManagerInstance,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result SetDownloadManagerInstancesInMetaConfig(
        _In_ LCMProviderContext* lcmContext,
        _In_ MI_InstanceA downloadManagerInstances,
        _In_ MI_Uint32 typeOfDownloadManagerInstance,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);


    MI_Result LCM_Pull_GetConfiguration(
        _In_ LCMProviderContext *lcmContext,
        _In_ ModuleManager *moduleManager,
        _In_ MI_Instance *metaConfigInstance,
        _In_opt_z_ MI_Char *partialConfigName,
        _Out_ MI_Uint32 * numModulesInstalled,
        _In_opt_z_ MI_Char *assignedConfiguration,
        _Inout_ MI_Uint32 *resultExecutionStatus,
        _Out_ MI_Uint32 *getActionStatusCode,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result LCM_Pull_GetAction(_In_ LCMProviderContext *lcmContext,
                                 _In_ MI_Instance *metaConfigInstance,
                                 _In_opt_z_ MI_Char *partialConfigName,
                                 _In_z_ MI_Char *checkSum,
                                 _In_ MI_Boolean bIsCompliant,
                                 _In_ MI_Uint32 lastGetActionStatusCode,
                                 _Outptr_result_maybenull_z_  MI_Char** resultStatus,
                                 _Out_  MI_Uint32* getActionStatusCode,
                                 _Outptr_result_maybenull_ OverAllGetActionResponse** serverAssignedConfigurations,
                                 _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

     MI_Result LCM_Do_Register(
         _In_ MI_Instance *metaConfigInstance,
         _In_ MI_Instance *managerInstance,
         _In_z_ MI_Char *agentId,
         _In_z_ MI_Char *thumbprint,
         _In_ MI_Instance *registrationPayload,
         _In_ MI_StringA *configurationNames,
         _In_ MI_Uint32 typeOfManagerInstance,
         _Outptr_result_maybenull_z_  MI_Char** result,
         _Out_ MI_Uint32* getActionStatusCode,
         _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

    MI_Result MI_CALL LCM_Pull_Execute(
        _In_ LCMProviderContext *lcmContext,
        _In_ MI_Instance *metaConfigInstance,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

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

    MI_Boolean ShouldMonitorOnly(_In_z_ MI_Char* configurationMode);

    void GetFullMessageWithTokens(_In_z_ const MI_Char * deviceName, _In_z_ const MI_Char * resourceId,
                     _In_z_ const MI_Char * message, _In_ LCMProviderContext *lcmContext, Intlstr *intlstr);

#ifdef __cplusplus

}

#endif

#endif //_LOCALCONFIGMANAGERHELPER_H_

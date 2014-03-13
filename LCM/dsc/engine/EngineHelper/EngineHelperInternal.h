/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
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

#ifndef _ENGINE_HELPERINTERNAL_H_
#define _ENGINE_HELPERINTERNAL_H_

#include <MI.h>
#include <pal/intlstr.h>
#if !defined(_MSC_VER)
#include <common/linux/sal.h>
#endif
#include <micodec.h>

#define SEARCH_PATTERN_DIRECTORY            MI_T("*")
#define SEARCH_PATTERN_SCHEMA               MI_T(".schema.mof")
#define CHECKSUM_EXTENSION                  MI_T(".checksum")
#define SEARCH_PATTERN_REGISTRATIONINSTANCE MI_T(".registration.mof")
#define BASESCHEMA_FILENAME                 MI_T("baseresource.schema.mof")
#define METACONFIGSCHEMA_FILENAME           MI_T("MSFT_DSCMetaConfiguration.mof")
#define BASE_RESOURCE_CLASSNAME             MI_T("OMI_BaseResource")
#define BASE_DOCUMENT_CLASSNAME             MI_T("OMI_ConfigurationDocument")
#define BASE_REGISTRATION                   MI_T("MSFT_BaseConfigurationProviderRegistration")
#define BASE_REGISTRATION_WMIV2PROVIDER     MI_T("MSFT_CimConfigurationProviderRegistration")
#define BASE_REGISTRATION_PSPROVIDER        MI_T("MSFT_PSConfigurationProviderRegistration")
#define METACONFIG_CLASSNAME                MI_T("MSFT_DSCMetaConfiguration")
#define MSFT_BASECREDENTIAL_CLASSNAME       MI_T("MSFT_Credential")
#define MSFT_KEYVALUEPAIR_CLASSNAME         MI_T("MSFT_KeyValuePair")
#define MSFT_KEYVALUEPAIR_CLASS_KEY         MI_T("key")
#define MSFT_KEYVALUEPAIR_CLASS_VALUE       MI_T("value")
#define QUALIFIER_VERSION                   MI_T("ClassVersion")
#define QUALIFIER_READ                      MI_T("Read")
#define QUALIFIER_WRITE                     MI_T("Write")
#define QUALIFIER_KEY                       MI_T("Key")
#define QUALIFIER_REQUIRED                  MI_T("Required")


#define OMI_BaseResource_GetMethodName                        MI_T("GetTargetResource")
#define OMI_BaseResource_TestMethodName                       MI_T("TestTargetResource")
#define OMI_BaseResource_SetMethodName                        MI_T("SetTargetResource")

#define OMI_BaseResource_Method_InputResource                 MI_T("InputResource")
#define OMI_BaseResource_Method_Result                        MI_T("Result")
#define OMI_BaseResource_Method_ProviderContext               MI_T("ProviderContext")
#define OMI_BaseResource_Method_ReturnValue                   MI_T("ReturnValue")
#define OMI_BaseResource_Method_Configurations                MI_T("Configurations")
#define OMI_BaseResource_Method_OutputResource                MI_T("OutputResource")


/*OMI_BaseResource*/
#define OMI_BaseResource_ResourceId           MI_T("ResourceId")
#define OMI_BaseResource_SourceInfo           MI_T("SourceInfo")
#define OMI_BaseResource_DependsOn            MI_T("DependsOn")
#define OMI_BaseResource_Force                MI_T("Force")
#define OMI_BaseResource_ModuleName           MI_T("ModuleName")
#define OMI_BaseResource_ModuleVersion        MI_T("ModuleVersion")

/*MSFT_ConfigurationDocumen*/
#define OMI_ConfigurationDocument_Version                  MI_T("Version")
#define OMI_ConfigurationDocument_Author                   MI_T("Author")
#define OMI_ConfigurationDocument_Copyright                MI_T("Copyright")
#define OMI_ConfigurationDocument_HelpInfoUri              MI_T("HelpInfoUri")
#define OMI_ConfigurationDocument_ContentType              MI_T("ContentType")
#define OMI_ConfigurationDocument_GenerationDate           MI_T("GenerationDate")
#define OMI_ConfigurationDocument_GenerationHost           MI_T("GenerationHost")

#define OMI_ConfigurationDocument_ContentType_PasswordEncrypted   MI_T("PasswordEncrypted")
#define OMI_ConfigurationDocument_ContentType_NotEncrypted   MI_T("NotEncrypted")

/* MSFT_BaseConfigurationProviderRegistration*/
#define MSFT_BaseConfigurationProviderRegistration_ClassName                MI_T("ClassName")
#define MSFT_BaseConfigurationProviderRegistration_DSCEngineCompatVersion   MI_T("DSCEngineCompatVersion")
#define MSFT_BaseConfigurationProviderRegistration_DSCModuleVersion         MI_T("DSCModuleVersion")

/* MSFT_CimConfigurationProviderRegistration*/
#define MSFT_CimConfigurationProviderRegistration_Namespace                MI_T("Namespace")
#define MSFT_CimConfigurationProviderRegistration_BaseProperty_Count    3

/* MSFT_PSConfigurationProviderRegistration*/
#define MSFT_PSConfigurationProviderRegistration_ModuleName                 MI_T("ModuleName")
#define MSFT_PSConfigurationProviderRegistration_BaseProperty_Count    3

/* MSFT_DSCMetaConfiguration*/
#define MSFT_DSCMetaConfiguration_LocalConfigurationManagerState			MI_T("LocalConfigurationManagerState")
#define MSFT_DSCMetaConfiguration_ResourceId                                MI_T("ResourceId")
#define MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins            MI_T("ConfigurationModeFrequencyMins")
#define MSFT_DSCMetaConfiguration_RebootNodeIfNeeded                        MI_T("RebootNodeIfNeeded")
#define MSFT_DSCMetaConfiguration_Credential                                MI_T("Credential")
#define MSFT_DSCMetaConfiguration_RefreshMode                               MI_T("RefreshMode")
#define MSFT_DSCMetaConfiguration_ConfigurationMode                         MI_T("ConfigurationMode")
#define MSFT_DSCMetaConfiguration_CertificateInstallLocation                MI_T("CertificateInstallLocation")
#define MSFT_DSCMetaConfiguration_CertificateID                             MI_T("CertificateID")
#define MSFT_DSCMetaConfiguration_InventoryUrl                              MI_T("InventoryUrl")
#define MSFT_DSCMetaConfiguration_ConfigurationID                           MI_T("ConfigurationID")
#define MSFT_DSCMetaConfiguration_DeleteCertificateOnInstallation           MI_T("DeleteCertificateOnInstallation")
#define MSFT_DSCMetaConfiguration_DownloadManagerName                       MI_T("DownloadManagerName")
#define MSFT_DSCMetaConfiguration_DownloadManagerCustomData                 MI_T("DownloadManagerCustomData")
#define MSFT_DSCMetaConfiguration_RefreshFrequencyMins						MI_T("RefreshFrequencyMins")
#define MSFT_DSCMetaConfiguration_AllowModuleOverwrite						MI_T("AllowModuleOverwrite")

#define MSFT_DSCMetaConfiguration_BaseProperty_Count    0

/* MSFT_DSCLocalConfigManager */
#define MSFT_DSCLocalConfigManager_SendConfiguration					MI_T("SendConfiguration")
#define MSFT_DSCLocalConfigManager_SendConfigurationApply				MI_T("SendConfigurationApply")
#define MSFT_DSCLocalConfigManager_GetConfiguration						MI_T("GetConfiguration")
#define MSFT_DSCLocalConfigManager_ApplyConfiguration					MI_T("ApplyConfiguration")
#define MSFT_DSCLocalConfigManager_SendMetaConfigurationApply			MI_T("SendMetaConfigurationApply")
#define MSFT_DSCLocalConfigManager_GetMetaConfiguration					MI_T("GetMetaConfiguration")
#define MSFT_DSCLocalConfigManager_RollBack								MI_T("RollBack")
#define MSFT_DSCLocalConfigManager_PerformRequiredConfigurationChecks	MI_T("PerformRequiredConfigurationChecks")
#define MSFT_DSCLocalConfigManager_StopConfiguration					MI_T("StopConfiguration")

/* MSFT_Credential */
#define MSFT_Credential_UserName                    MI_T("UserName")
#define MSFT_Credential_Password                    MI_T("Password")

/* MSFT_KeyValuePair */
#define MSFT_KeyValuePair_Key                   MI_T("Key")
#define MSFT_KeyValuePair_Value                 MI_T("Value")



/*MSFT_ConfigurationDocumen*/
#define MSFT_WMIERROR_MESSAGE                  MI_T("Message")

/*DSC_InternalStateCache*/
#define DSC_InternalStateCache_ComplianceStatus     MI_T("ComplianceStatus")
#define DSC_InternalStateCache_GetActionStatusCode  MI_T("GetActionStatusCode")
#define DSC_InternalStateCache_LCMStatusCode		MI_T("LCMStatusCode")

#define DSC_RESOURCENAME                MI_T("LCM")
#define CA_ACTIVITY_NAME                MI_T("LCM")
#define METADATA_REFRESHMODE_PULL       MI_T("PULL")
#define METADATA_REFRESHMODE_PUSH       MI_T("PUSH")
#define EMPTY_STRING                        MI_T("")
#define DEVICE_NAME_SIZE                MAX_COMPUTERNAME_LENGTH+1 //Maximum computer name length possible is 15
#define TOKENIZED_OUTPUT_PADDING        50 //Padding required when outputs are tokenized


#define DSC_RESTART_SYSTEM_FLAG         1

#define LCM_SETFLAGS_DEFAULT            0
#define LCM_SETFLAGS_SAVETOPENDINGONLY  (1 << 0 )
#define LCM_SET_METACONFIG              (1 << 1)
#define LCM_SETFLAGS_ENABLEWHATIF       (1 << 2)
#define VALIDATE_REGISTRATION_INSTANCE  (1 << 3 )
#define VALIDATE_DOCUMENT_INSTANCE      (1 << 4)
#define VALIDATE_METACONFIG_INSTANCE    (1 << 5)
#define LCM_EXECUTIONMODE_OFFLINE       (1 << 6)
#define LCM_EXECUTIONMODE_ONLINE        (1 << 7)
#define LCM_EXECUTE_TESTONLY            (1 << 8)

#define MODULEHANDLER_NOTLOADED     0
#define MODULEHANDLER_LOADED     1

#define MAX_MOFSIZE         (10*1024*1024) // Setting the Max Mof Size as 10 MB as per Bug # 298792

#define TIME_PER_SECONND 1000000 // 1 MicroSecond

/*Consistency Engine variables*/
#define TASK_AUTO 1
#define TASK_FORCE 2


/*PerformRequiredConfigurationChecks variables*/
#define TASK_REGULAR 1
#define TASK_REBOOT 2
#define TASK_BOOTSTRAP 3
#define DSC_CONFIGURATIONMODE_APPLYONLY MI_T("ApplyOnly")
#define DSC_CONFIGURATIONMODE_APPLYANDMONITOR MI_T("ApplyAndMonitor")
#define DSC_CONFIGURATIONMODE_APPLYANDAUTOCORRECT MI_T("ApplyAndAutoCorrect")
#define DEFAULT_RebootNodeIfNeeded MI_FALSE
#define DEFAULT_AllowModuleOverwrite MI_FALSE
#define DEFAULT_RefreshMode MI_T("PUSH")
#define DEFAULT_MinRefreshFrequencyMins 15
#define DEFAULT_MinRefreshFrequencyMinsString MI_T("15")
#define DEFAULT_MaxRefreshFrequencyMins 44640
#define DEFAULT_MaxRefreshFrequencyMinsString MI_T("44640")
#define DEFAULT_ConfigurationModeFrequencyMins 30
#define DEFAULT_ConfigurationModueFrequencyMinsString MI_T("a multiple of RefreshFrequencyMins")


#define DURATION_SIZE 11
// This is a mapping table between resourceId for resource and the function generated by the PAL layer.
// Some of the macro may appear irrlevant but they are not. It is needed to expand first and then concatinate.
// ## does not expand, hence expansion must happen before expanding ##. Extra redirection makes sure that
// expansion happens first.
#define GEN_CAT( locId) Intlstr_ ## locId
#define GEN_XCAT(locId) GEN_CAT( locId)
#define GEN_HASH_EXPAND(locId) locId
#define GEN_HASH(locId)  GEN_HASH_EXPAND(locId)
#define GEN_SUF(locId) GEN_XCAT(  GEN_HASH(locId)  )
#if defined(_MSC_VER)
#define GEN_FPTR(x)    & ## x
#else
#define GEN_FPTR(x)    (void*)x
#endif
#define GEN_XFPTR(x)  GEN_FPTR(x)

// This is used by PAL to find strings in dsccore.dll
#define INTLSTR_DOMAIN "dsccore"


#define Intlstr_Name(resourceId)    Intlstr_ ## resourceId

#define DEFAULT_ConfigurationMode DSC_CONFIGURATIONMODE_APPLYANDMONITOR
#define DEFAULT_DeleteCertificateOnInstallation MI_TRUE
#define DSC_PULL_DOWNLOADMANAGER_WEB MI_T("PsDesiredStateConfiguration")
#define MSFT_DSCPULL_CertificateID   MI_T("CertificateID")
#define MSFT_DSCPULL_SERVERURL   MI_T("ServerURL")
#define DSC_GETCONFIGURATION_FIRSTTIME 1
#define DSC_GETCONFIGURATION_REPEAT    2
#define DSC_REBOOT_GRACEPERIOD      5 
#define DSC_RESTART_BOOTUP_TASK MI_T("\\Microsoft\\Windows\\Desired State Configuration\\DSCRestartBootTask")
#define DSC_INDEX_OPTION_SHOULDPROCESS 3
#define DSC_INDEX_OPTION_CONFIRM 2    //This index in the context gets set to 1 if -confirm is used, set to 0 if whatif is used, and set to 2 if none of them is used.
#define DSC_CONFIRMOPTION_SET_VALUE 1    //This is the value at the confirm index, if the confirm option is set.

/*SQM DATA*/
#define SQM_MACHINEGLOBAL_SESSIONID 13238784	//Session ID for all machine global sessions, present in sqmteam documentation online
#define SQM_RESOURCECOUNT_DATAPOINTID 12401		//Datapoint ID for PSDSCResourceCount, newly created for DSC , as present in sqmteam documentation online.
#define SQM_INDEX_PROVIDERNAME 1				//Provider name is the second column in the PSDSCResoururceCount stream datapoint, hence it is indexed as 1
#define SQM_INDEX_RESOURCECOUNT 0				//The resource count is the first column in the datapoint, indexed as 0.
#define SQM_PARAMETER_SIZE 2					//Total number of columns in the stream datapoint


typedef MI_Instance* MI_InstancePtr;
typedef MI_InstancePtr* MI_InstancePtrPtr;


#define NUM_PATHS_TO_LOOK_FOR_PROVIDERS   2 //Look for native providers in both the configuration directory inside systemdir , and inside c:\programfiles (as defined below)

#if defined(_MSC_VER)
#define CONFIGURATION_SYSTEMDIR         MI_T("%windir%\\System32\\Configuration")
#define CONFIGURATION_PROGFILES         MI_T("%programFiles%\\WindowsPowerShell\\Configuration")
#define PATH_SEPARATOR                  MI_T("\\")
#define DSC_PLUGINWKR_PATH MI_T("%windir%\\System32\\wbem\\Dscpspluginwkr.dll")


#define CONFIGURATION_SCHEMA_SEARCH_PATH                CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("Schema")
#define CONFIGURATION_BASESCHEMA_MOF_PATH               CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("BaseRegistration")
#define CONFIGURATION_REGINSTANCE_SEARCH_PATH           CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("Registration")
#define CONFIGURATION_LOCATION                          CONFIGURATION_SYSTEMDIR
#define CONFIGURATION_MODULE_SEARCH_PATH                CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("Registration")
#define CONFIGURATION_LOCATION_BACKUP                   CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("backup.mof")
#define CONFIGURATION_LOCATION_CHECKSUM                 CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("current.mof.checksum")
#define CONFIGURATION_LOCATION_INTERNALSTATECACHE       CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("DSCEngineCache.mof")
#define BUILTIN_PROVIDER_CACHE                          CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("BuiltinProvCache")
#define PACKAGE_PROVIDER_CACHE                          MI_T("%ProgramData%\\Microsoft\\Windows\\PowerShell\\Configuration\\BuiltinProvCache")
#define CONFIGURATION_PROGFILES_SCHEMA_SEARCH_PATH      CONFIGURATION_PROGFILES PATH_SEPARATOR MI_T("Schema")
#define CONFIGURATION_PROGFILES_REGINSTANCE_SEARCH_PATH CONFIGURATION_PROGFILES PATH_SEPARATOR MI_T("Registration")

#else
//Non-Windows
#define MAX_COMPUTERNAME_LENGTH 15 
#define CONFIGURATION_SYSTEMDIR CONFIG_SYSCONFDIR   MI_T("/dsc/configuration")
#define CONFIGURATION_PROGFILES CONFIG_DATADIR      MI_T("/dsc/configuration")
#define PATH_SEPARATOR                              MI_T("/")

#define CONFIGURATION_SCHEMA_SEARCH_PATH                  CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("schema")
#define CONFIGURATION_BASESCHEMA_MOF_PATH                 CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("baseregistration")
#define CONFIGURATION_REGINSTANCE_SEARCH_PATH             CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("registration") 
#define CONFIGURATION_LOCATION                            CONFIGURATION_SYSTEMDIR
#define CONFIGURATION_MODULE_SEARCH_PATH                  CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("registration") 
#define CONFIGURATION_LOCATION_BACKUP                     CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("backup.mof")  
#define CONFIGURATION_LOCATION_CHECKSUM                   CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("current.mof.checksum") 
#define CONFIGURATION_LOCATION_INTERNALSTATECACHE         CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("DSCEngineCache.mof")  
#define BUILTIN_PROVIDER_CACHE                            CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("BuiltinProvCache")  
#define PACKAGE_PROVIDER_CACHE                            CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("BuiltinProvCache")  
#define CONFIGURATION_PROGFILES_SCHEMA_SEARCH_PATH        CONFIGURATION_PROGFILES PATH_SEPARATOR MI_T("schema")
#define CONFIGURATION_PROGFILES_REGINSTANCE_SEARCH_PATH   CONFIGURATION_PROGFILES PATH_SEPARATOR MI_T("registration")



#endif


/**************************************
    constants used by LCM
    ******************************** ***/

    

#define CONFIGURATION_LOCATION_PENDING MI_T("Pending.mof")
#define CONFIGURATION_LOCATION_GET MI_T("Get.mof")
#define CONFIGURATION_LOCATION_CURRENT MI_T("Current.mof")
#define CONFIGURATION_LOCATION_CURRENTCHECKSUM MI_T("Current.mof.checksum")
#define CONFIGURATION_LOCATION_PREVIOUS MI_T("Previous.mof")
#define CONFIGURATION_LOCATION_METACONFIG MI_T("MetaConfig.mof")
#define CONFIGURATION_LOCATION_METACONFIG_TMP MI_T("MetaConfig.tmp.mof")
#define CONFIGURATION_LOCATION_METACONFIG_BACKUP MI_T("MetaConfig.backup.mof")
#define CONFIGURATION_LOCATION_PULLRUNLOGFILE MI_T("PullRunLog.txt")
#define INTERNALSTATECACHE_CLASSNAME MI_T("DSC_InternalStateCache")
#define METACONFIG_CLASSNAME MI_T("MSFT_DSCMetaConfiguration")
#define MSFT_LOGRESOURCENAME MI_T("MSFT_LogResource")
#define CONFIG_AGENT_APPLY_WAIT_SPIN_COUNT 5000
#define METACONFIG_MAX_BUFFER_SIZE 8192
#define TASKSCHEDULE_PROVDER_NAMESPACE MI_T("Root/Microsoft/Windows/TaskScheduler")
#define TASKSCHEDULE_PROVDER_NAME MI_T("PS_ScheduledTask")
#define TASKSCHEDULE_PROVDER_ENABLEMETHOD_NAME MI_T("EnableByName")
#define TASKSCHEDULE_PROVDER_DISABLEMETHOD_NAME MI_T("DisableByName")
#define TASKSCHEDULE_PROVDER_GETINFOBYNMAEMETHOD_NAME MI_T("GetInfoByName")
#define TASKSCHEDULE_PROVDER_PATH_NAME MI_T("TaskPath")
#define TASKSCHEDULE_PROVDER_NAME_NAME MI_T("TaskName")
#define DSC_TASKSCHEDULE_PATH MI_T("\\Microsoft\\Windows\\Desired State Configuration")
#define BOOT_TASKSCHEDULE_NAME MI_T("Boot")
#if defined(_MSC_VER)
#define CONSISTENCY_TASKSCHEDULE_NAME_BASE MI_T("\\Microsoft\\Windows\\Desired State Configuration\\")
#define CONSISTENCY_TASKSCHEDULE_NAME CONSISTENCY_TASKSCHEDULE_NAME_BASE MI_T("Consistency")
#else
// note this task name should not contain space
#define OMI_CONSISTENCY_TASKSCHEDULE_NAME CONFIG_BINDIR PATH_SEPARATOR MI_T("ConsistencyInvoker")
#endif
#define TASK_PARAMETER_SC_DAILY MI_T("DAILY")
#define TASK_PARAMETER_DU_DAILY MI_T("24:00")
#define DSCCOMPUTERNAME MI_T("DSC_REMOTE_COMPUTERNAME")
#define DSCWHATIFENABLED MI_T("DSC_WHATIF_ENABLED")
#define DSC_JOBIDSTRING MI_T("DSC_JOBID_STRING")


#define RETRY_LOOP_COUNT        10
#define RETRY_LOOP_SLEEP        500
#define CHECKSUM_SIZE 64
#define DEVICENAMESIZE MAX_COMPUTERNAME_LENGTH+1

#define LCM_STATUSCODE_READY 0
#define LCM_STATUSCODE_BUSY 1
#define LCM_STATUSCODE_REBOOT 2

#define LCM_STATUS_READY	MI_T("Ready")
#define LCM_STATUS_BUSY		MI_T("Busy")
#define LCM_STATUS_REBOOT	MI_T("PendingReboot")


/**************************************
    constants used by Pull Functionality
***************************************/

#define DEFAULT_PULL_REFRESH_FREQUENCY 60 //SECONDS    
#define PULL_STATUSCODE_OK           MI_T("OK")
#define PULL_STATUSCODE_RETRY        MI_T("RETRY")
#define PULL_STATUSCODE_GETCONFIG    MI_T("GETConfiguration")


/*OMI_BaseResource */

typedef struct _BaseResourceConfiguration
{
    const MI_Char *wszPropName;
    MI_Type propType ;
} BaseResourceConfiguration;

typedef struct _PropertyQualifier
{
    const MI_Char *wszPropName;
    const MI_Char *wszQualifierName;
} PropertyQualifier;

typedef struct _LCMProviderContext
{
    MI_Uint32 executionMode;
    void *context;
    MI_Uint32 messageOperation;//Start, failed, end
    MI_Uint32 messageItem;//test,get,resource
} LCMProviderContext;

typedef struct _ProviderCallbackContext
{
    LCMProviderContext *lcmProviderContext;
    const MI_Char *resourceId;
} ProviderCallbackContext;

typedef struct _WriteMessageResource
{
    MI_Uint32 resId;
    const MI_Char *wszMessage;
} WriteMessageResource;


#define PROPERTY_BITMASK_READ           (1 << 0)
#define PROPERTY_BITMASK_WRITE          (1 << 1)
#define PROPERTY_BITMASK_KEY            (1 << 2)
#define PROPERTY_BITMASK_REQUIRED       (1 << 3)
#define PROPERTY_BITMASK_ALL            (1|2|4|8)


typedef struct _ModuleLoaderObject
{
    MI_Application *application;
    MI_Class **providerSchema;
    MI_Uint32 schemaCount;
    MI_Instance **registrationSchema;
    MI_Uint32 regisrationCount;
    MI_Uint32 *schemaToRegistrationMapping; // size is equal to schemaCount. If registration found value is index into registrationSchema otherwise -1.
    MI_Deserializer *deserializer;
    MI_OperationOptions *options;
    MI_OperationOptions *strictOptions;
} ModuleLoaderObject;

typedef struct _ClassContainer
{
    MI_Class **MiClasses;
    MI_Uint32 miClassCount;
} ClassContainer;

typedef struct _JobInformation
{
     MI_Char deviceName[DEVICE_NAME_SIZE];

}JobInformation;
void SetJobId();

void ResetJobId();

MI_Boolean IsConfirmUsed(_In_opt_ MI_Context* context);

void SetJobDeviceName();
const MI_Char * GetSchemaSearchPath();

const MI_Char * GetRegistrationInstanceSearchPath();

const MI_Char * GetSchemaSearchPathProgFiles();

const MI_Char * GetRegistrationInstanceSearchPathProgFiles();

const MI_Char * GetCoreSchemaPath();

void CleanUpClassCache(_Inout_ MI_ClassA *miClassArray);


MI_Result UpdateClassArray(_In_ MI_ClassA *inputClassArray,
                           _Inout_ MI_ClassA *outputClassArray,
                           _Outptr_result_maybenull_ MI_Instance **extendedError,
                           _In_ MI_Boolean bInputUsingSerializedAPI
                           );

MI_Result UpdateInstanceArray(_In_ MI_InstanceA *inputInstanceArray,
                              _Inout_ MI_InstanceA *outputInstanceArray,
                              _Outptr_result_maybenull_ MI_Instance **extendedError,
                              _In_ MI_Boolean bInputUsingSerializedAPI);

MI_Result UpdateInstanceArray(_In_ MI_InstanceA *inputInstanceArray,
                              _Inout_ MI_InstanceA *outputInstanceArray,
                              _Outptr_result_maybenull_ MI_Instance **extendedError,
                              _In_ MI_Boolean bInputUsingSerializedAPI);

void CleanUpInstanceCache(_Inout_ MI_InstanceA *instanceArray);

void CleanUpDeserializerClassCache(_Inout_ MI_ClassA *miClassArray);

void CleanUpDeserializerInstanceCache(_Inout_ MI_InstanceA *instanceArray);

void CleanUpGetCache(_Inout_ MI_InstanceA *instanceArray);

/*For Debugging purposes onlys*/
void PrintClass(_In_ MI_Class *miClass);

void SQMLogResourceCountData(_In_z_ const MI_Char* providerName,_In_ MI_Uint32 resourceCount);

MI_Result ReadFileContent(_In_z_ const MI_Char *pFileName,
        _Outptr_result_buffer_maybenull_(*pBufferSize) MI_Uint8 ** pBuffer, 
        _Out_ MI_Uint32 *pBufferSize,
        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

const MI_Char * GetResourceId( _In_ MI_Instance *inst);

const MI_Char * GetSourceInfo( _In_ MI_Instance *inst);

const MI_Char * GetDownloadManagerName( _In_ MI_Instance *inst);

const MI_Char * GetErrorDetail( _In_ MI_Instance *inst);

void CleanupTempDirectory(_In_z_ MI_Char *mofFileName);

void GetResourceString( _In_ MI_Uint32 errorStringId, _Inout_ Intlstr *resStr);

MI_Result  GetCimError(MI_Uint32 hr , 
                                _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                                _In_ MI_Uint32 errorStringId
                                );

_Always_(_Ret_range_(==, result))
MI_Result  GetCimMIError(MI_Result result ,
                                  _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                                  _In_ MI_Uint32 errorStringId
                                  );

_Always_(_Ret_range_(==, result))
MI_Result GetCimMIError1Param(MI_Result result ,
                        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                        _In_ MI_Uint32 errorStringId,
                        _In_z_ const MI_Char * param1);

_Always_(_Ret_range_(==, result))
MI_Result GetCimMIError2Params(MI_Result result ,
                        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                        _In_ MI_Uint32 errorStringId,
                        _In_z_ const MI_Char * param1,
                        _In_z_ const MI_Char * param2);

_Always_(_Ret_range_(==, result))
MI_Result GetCimMIError3Params(MI_Result result ,
                        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                        _In_ MI_Uint32 errorStringId,
                        _In_z_ const MI_Char * param1,
                        _In_z_ const MI_Char * param2,
                        _In_z_ const MI_Char * param3
                        );

_Always_(_Ret_range_(==, result))
MI_Result GetCimMIError4Params(MI_Result result ,
                        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                        _In_ MI_Uint32 errorStringId,
                        _In_z_ const MI_Char * param1,
                        _In_z_ const MI_Char * param2,
                        _In_z_ const MI_Char * param3,
                        _In_z_ const MI_Char * param4
                        );

MI_Result  GetCimWin32Error(MI_Uint32 result ,
                      _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                      _In_ MI_Uint32 errorStringId );

MI_Result AppendWMIErrorWithResourceID(
                      _Inout_ MI_Instance *cimErrorDetails,
                      _In_z_ const MI_Char * resourceId
                      );

MI_Result AppendWMIError1ParamID(
                      _Inout_ MI_Instance *cimErrorDetails,
                      _In_ MI_Uint32 errorStringId
                      );

void RecursivelyDeleteDirectory(_In_z_ MI_Char *directoryPath);

MI_Result ResolvePath(_Outptr_opt_result_maybenull_z_ MI_Char **envResolvedPath, 
                      _Outptr_opt_result_maybenull_z_ MI_Char **searchPath, 
                      _In_z_ const MI_Char *envPath,
                      _In_z_ const MI_Char *searchPattern,
                      _Outptr_result_maybenull_ MI_Instance **extendedError);

void InitLocTable();


#ifndef g_ConfigurationDetails

#define JOB_UUID_LENGTH 40*sizeof(MI_Char)
    typedef struct _ConfigurationDetails
        { 
            MI_Char jobGuidString[JOB_UUID_LENGTH]; 
            MI_Boolean hasSetDetail;
        } ConfigurationDetails;

    extern ConfigurationDetails g_ConfigurationDetails;
#endif

#if defined(_MSC_VER)
     MI_Result MIResultFromHRESULT(HRESULT hr);
#endif

#endif

/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _ENGINE_HELPERINTERNAL_H_
#define _ENGINE_HELPERINTERNAL_H_

#include <MI.h>
#include <pal/intlstr.h>
#include <common/linux/sal.h>
#include <micodec.h>
#include "MSFT_DSCMetaConfiguration.h"

/*Macro functions to return on an error*/
#define RETURN_RESULT_IF_FAILED(resultCode)                                                             if(resultCode!=MI_RESULT_OK) return resultCode;
#define GOTO_CLEANUP_IF_FAILED(resultCode,cleanUpLabel)                                                 if(resultCode!=MI_RESULT_OK) {goto cleanUpLabel;}
//Macro to throw cimerror on a failure
#define GOTO_CLEANUP_AND_THROW_ERROR_IF_FAILED(resultCode,errorIntCode, errorStringID,cimErrorDetails,cleanUpLabel)     \
        { \
                if (resultCode != MI_RESULT_OK) \
                { \
                        resultCode = GetCimMIError(errorIntCode, cimErrorDetails, errorStringID); \
                        goto cleanUpLabel; \
                } \
        }
#define GOTO_CLEANUP_AND_THROW_ERROR1PARAM_IF_FAILED(resultCode,errorID,cimErrorDetails,param1,cleanUpLabel)   \
                        { \
                                if (resultCode != MI_RESULT_OK) \
                                { \
                                return resultCode = GetCimMIError1Param(resultCode, cimErrorDetails, errorID, param1); \
                                goto cleanUpLabel; \
                                }\
                        }
#define GOTO_CLEANUP_AND_THROW_ERROR2PARAMS_IF_FAILED(resultCode,errorID,cimErrorDetails,param1,param2,cleanUpLabel)   \
                        { \
                                if (resultCode != MI_RESULT_OK) \
                                { \
                                return resultCode = GetCimMIError2Params(resultCode, cimErrorDetails, errorID, param1, param2); \
                                goto cleanUpLabel; \
                                }\
                        }

#define CHECK_AND_RETURN_WITH_CIMERROR(resultCode,errorCode,cimErrorDetails,IDstring)                   if(resultCode!=MI_RESULT_OK) {return GetCimMIError(errorCode, cimErrorDetails, IDstring);}
#define DSCFREE_IF_NOT_NULL(pointer)                                                                    if(pointer!=NULL) { DSC_free(pointer); pointer=NULL;}
#define INSTANCE_DELETE_IF_NOT_NULL(pointer)                                                            if(pointer) { MI_Instance_Delete(pointer); pointer=NULL;}

#define VALIDATE_AND_RESET_OUTPUT_POINTERPOINTER(pp) \
    if (pp == NULL)                                 \
    {                                               \
        return MI_RESULT_INVALID_PARAMETER;         \
    }                                               \
    *pp = NULL;

/* unconditional fail */
#define EH_Fail() { goto _eh_unwind; }

#define EH_Fail_(immediate_cleanup) { immediate_cleanup; EH_Fail() }

/* checks if expression is true */
#define EH_Check(expression) \
  EH_Check_(expression, {})

#define EH_Check_(expression, immediateCleanup) \
  { if (!(expression)) { immediateCleanup; goto _eh_unwind; } }



#define EH_CheckResult_(miResultExpression, immediateCleanup) \
  EH_Check_(MI_RESULT_OK == (miResultExpression), immediateCleanup)

  /* checks if MI_Result indicates success */
#define EH_CheckResult(miResultExpression) \
    EH_Check(MI_RESULT_OK == (miResultExpression))

/* unwind block */
#define EH_UNWIND _eh_unwind:


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
#define BASE_REGISTRATION_NATIVEPROVIDER    MI_T("MSFT_NativeConfigurationProviderRegistration")
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
#define METACONF_RESOURCE_CLASSNAME         MI_T("OMI_MetaConfigurationResource")

#define DSC_LIB_PATH MI_T("/opt/dsc/lib")

#define MSFT_ServerURL_Name MI_T("ServerURL")

#define OMI_BaseResource_GetMethodName                        MI_T("GetTargetResource")
#define OMI_BaseResource_TestMethodName                       MI_T("TestTargetResource")
#define OMI_BaseResource_SetMethodName                        MI_T("SetTargetResource")
#define OMI_BaseResource_InventoryMethodName                  MI_T("InventoryTargetResource")


#define OMI_BaseResource_Method_InputResource                 MI_T("InputResource")
#define OMI_BaseResource_Method_Result                        MI_T("Result")
#define OMI_BaseResource_Method_MIReturn                      MI_T("MIReturn")
#define OMI_BaseResource_Method_ProviderContext               MI_T("ProviderContext")
#define OMI_BaseResource_Method_ReturnValue                   MI_T("ReturnValue")
#define OMI_BaseResource_Method_Configurations                MI_T("Configurations")
#define OMI_BaseResource_Method_OutputResource                MI_T("OutputResource")


#define OMI_RESOURCEMODULEMANAGER_CLASSNAME                         MI_T("OMI_ResourceModuleManager")
#define OMI_CONFIGURATIONDOWNLOADMANAGER_CLASSNAME                  MI_T("OMI_ConfigurationDownloadManager")
#define OMI_REPORTMANAGER_CLASSNAME                                 MI_T("OMI_ReportManager")
#define MSFT_PARTIALCONFIGURATION_CLASSNAME                         MI_T("MSFT_PartialConfiguration")
/*derived manager names*/
#define MSFT_WEBRESOURCEMODULEMANAGER_CLASSNAME                     MI_T("MSFT_WebResourceManager")
#define MSFT_FILERESOURCEMODULEMANAGER_CLASSNAME                    MI_T("MSFT_FileResourceManager")
#define MSFT_WEBCONFIGURATIONDOWNLOADMANAGER_CLASSNAME              MI_T("MSFT_WebDownloadManager")
#define MSFT_FILECONFIGURATIONDOWNLOADMANAGER_CLASSNAME             MI_T("MSFT_FileDownloadManager")
#define MSFT_OAASREPORTMANAGER_CLASSNAME                            MI_T("MSFT_OaaSReportManager")
#define MSFT_WEBREPORTMANAGER_CLASSNAME                             MI_T("MSFT_WebReportManager")

/*OMI_BaseResource*/
#define OMI_BaseResource_ResourceId           MI_T("ResourceId")
#define OMI_BaseResource_SourceInfo           MI_T("SourceInfo")
#define OMI_BaseResource_DependsOn            MI_T("DependsOn")
#define OMI_BaseResource_Force                MI_T("Force")
#define OMI_BaseResource_ModuleName           MI_T("ModuleName")
#define OMI_BaseResource_ModuleVersion        MI_T("ModuleVersion")
#define OMI_BaseResource_ConfigurationName    MI_T("ConfigurationName")

/* OMI_ConfigurationDownloadManager */
#define OMI_CONFIGURATIONDOWNLOADMANAGER_CLASSNAME                  MI_T("OMI_ConfigurationDownloadManager")
#define OMI_ConfigurationDownloadManager_Name                             MI_T("Name")

/*MSFT_ConfigurationDocumen*/
#define OMI_ConfigurationDocument_Version                  MI_T("Version")
#define OMI_ConfigurationDocument_Author                   MI_T("Author")
#define OMI_ConfigurationDocument_Copyright                MI_T("Copyright")
#define OMI_ConfigurationDocument_HelpInfoUri              MI_T("HelpInfoUri")
#define OMI_ConfigurationDocument_ContentType              MI_T("ContentType")
#define OMI_ConfigurationDocument_GenerationDate           MI_T("GenerationDate")
#define OMI_ConfigurationDocument_GenerationHost           MI_T("GenerationHost")
#define OMI_ConfigurationDocument_Name                     MI_T("Name")
#define OMI_ConfigurationDocument_DocumentType             MI_T("DocumentType")
#define OMI_ConfigurationDocument_MinimumCompatibleVersion               MI_T("MinimumCompatibleVersion")
#define OMI_ConfigurationDocument_CompatibleVersionAdditionalProperties  MI_T("CompatibleVersionAdditionalProperties")

#define OMI_ConfigurationDocument_ContentType_PasswordEncrypted   MI_T("PasswordEncrypted")
#define OMI_ConfigurationDocument_ContentType_NotEncrypted   MI_T("NotEncrypted")

#define OMI_ConfigurationDocument_VersionV1           MI_T("1.0.0")
#define OMI_ConfigurationDocument_VersionV2           MI_T("2.0.0")


#define OMI_ConfigurationDocument_PartialConfigAuthor MI_T("MSFT_DSCLocalConfigurationManager")
#define OMI_ConfigurationDocument_PartialConfigName   MI_T("MSFT_DSCLocalConfigurationManager")

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

/* MSFT_NativeConfigurationProviderRegistration*/
#define MSFT_NativeConfigurationProviderRegistration_Path                  MI_T("Path")

/* MSFT_DSCMetaConfiguration*/
#define MSFT_DSCMetaConfiguration_LCMState                                                                      MI_T("LCMState")
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
#define MSFT_DSCMetaConfiguration_RefreshFrequencyMins                                          MI_T("RefreshFrequencyMins")
#define MSFT_DSCMetaConfiguration_AllowModuleOverwrite                                          MI_T("AllowModuleOverwrite")
#define MSFT_DSCMetaConfiguration_DebugMode                                                                     MI_T("DebugMode")
#define MSFT_DSCMetaConfiguration_LCMVersion                                                            MI_T("LCMVersion")
#define MSFT_DSCMetaConfiguration_LCMCompatibleVersions                                         MI_T("LCMCompatibleVersions")
#define MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers                         MI_T("ConfigurationDownloadManagers")
#define MSFT_DSCMetaConfiguration_ResourceModuleManagers                                        MI_T("ResourceModuleManagers")
#define MSFT_DSCMetaConfiguration_ReportManagers                                                    MI_T("ReportManagers")
#define MSFT_DSCMetaConfiguration_PartialConfigurations                                     MI_T("PartialConfigurations")
#define MSFT_DSCMetaConfiguration_AgentId                                                                       MI_T("AgentId")
#define MSFT_DSCMetaConfiguration_LCMUpdateName                                                 MI_T("LcmUpdateName")
#define MSFT_DSCMetaConfiguration_MaxPendingConfigRetryCount                MI_T("MaxPendingConfigRetryCount")
#define MSFT_DSCMetaConfiguration_LocalConfigurationManagerState            MI_T("LocalConfigurationManagerState")
#define MSFT_DSCMetaConfiguration_LCMStateDetail                            MI_T("LCMStateDetail")
#define MSFT_DSCMetaConfiguration_ActionAfterReboot                                             MI_T("ActionAfterReboot")
#define MSFT_DSCMetaConfiguration_StatusRetentionTimeInDays                                     MI_T("StatusRetentionTimeInDays")

#define MSFT_DSCMetaConfiguration_EnableSignatureValidation                                     MI_T("EnableSignatureValidation")
#define MSFT_DSCMetaConfiguration_DisableModuleSignatureValidation                              MI_T("DisableModuleSignatureValidation")

#define MSFT_DSCMetaConfiguration_BaseProperty_Count    0


/* MSFT_DSCConfigurationStatus */
#define MAX_NUM_DSC_CONFIGURATION_STATUS_IN_HISTORY                             10      // this should be removed when MSFT workitem 216985 is finished.
#define MSFT_DSCConfigurationStatus_Status                                              MI_T("Status")
#define MSFT_DSCConfigurationStatus_Status_Success                              MI_T("Success")
#define MSFT_DSCConfigurationStatus_Status_Failure                              MI_T("Failure")
#define MSFT_DSCConfigurationStatus_Status_Aborted                              MI_T("Aborted")
#define MSFT_DSCConfigurationStatus_Status_InProgress                   MI_T("InProgress")
#define MSFT_DSCConfigurationStatus_Error                                               MI_T("Error")
#define MSFT_DSCConfigurationStatus_StartDate                                   MI_T("StartDate")
#define MSFT_DSCConfigurationStatus_StartDate_Format                    MI_T("%04d/%02d/%02d %02d:%02d:%02d")
#define MSFT_DSCConfigurationStatus_StartDate_Size                              20
#define MSFT_DSCConfigurationStatus_DurationInSeconds                   MI_T("DurationInSeconds")
#define MSFT_DSCConfigurationStatus_RebootRequested                             MI_T("RebootRequested")
#define MSFT_DSCConfigurationStatus_Type                                                MI_T("Type")
#define MSFT_DSCConfigurationStatus_Type_Initial                                MI_T("Initial")
#define MSFT_DSCConfigurationStatus_Type_Consistency                    MI_T("Consistency")
#define MSFT_DSCConfigurationStatus_Type_Reboot                                 MI_T("Reboot")
#define MSFT_DSCConfigurationStatus_Type_ReadOnly                               MI_T("ReadOnly")
#define MSFT_DSCConfigurationStatus_JobID                                               MI_T("JobID")
#define MSFT_DSCConfigurationStatus_MetaData                                    MI_T("MetaData")
#define MSFT_DSCConfigurationStatus_NumberOfResources                   MI_T("NumberOfResources")
#define MSFT_DSCConfigurationStatus_Mode                                                MI_T("Mode")
#define MSFT_DSCConfigurationStatus_LCMVersion                                  MI_T("LCMVersion")
#define MSFT_DSCConfigurationStatus_HostName                                    MI_T("HostName")
#define MSFT_DSCConfigurationStatus_IPV4Addresses                               MI_T("IPV4Addresses")
#define MSFT_DSCConfigurationStatus_IPV6Addresses                               MI_T("IPV6Addresses")
#define MSFT_DSCConfigurationStatus_MACAddresses                                MI_T("MACAddresses")
#define MSFT_DSCConfigurationStatus_MetaConfiguration                   MI_T("MetaConfiguration")
#define MSFT_DSCConfigurationStatus_ResourcesInDesiredState             MI_T("ResourcesInDesiredState")
#define MSFT_DSCConfigurationStatus_ResourcesNotInDesiredState  MI_T("ResourcesNotInDesiredState")

/*OMI_MetaConfigurationResource*/
#define OMI_MetaConfigurationResource_ResourceId           OMI_BaseResource_ResourceId
#define OMI_MetaConfigurationResource_SourceInfo           OMI_BaseResource_SourceInfo
#define OMI_MetaConfigurationResource_ModuleName           OMI_BaseResource_ModuleName
#define OMI_MetaConfigurationResource_ModuleVersion        OMI_BaseResource_ModuleVersion
#define OMI_MetaConfigurationResource_Property_Count       2

#define MSFT_DSCMetaConfiguration_PartialConfigurations                                     MI_T("PartialConfigurations")

#define MSFT_DSCMetaConfiguration_BaseProperty_Count    0

/* MSFT_DSCLocalConfigManager */
#define MSFT_DSCLocalConfigManager_SendConfiguration                                    MI_T("SendConfiguration")
#define MSFT_DSCLocalConfigManager_SendConfigurationApply                               MI_T("SendConfigurationApply")
#define MSFT_DSCLocalConfigManager_GetConfiguration                                             MI_T("GetConfiguration")
#define MSFT_DSCLocalConfigManager_ApplyConfiguration                                   MI_T("ApplyConfiguration")
#define MSFT_DSCLocalConfigManager_SendMetaConfigurationApply                   MI_T("SendMetaConfigurationApply")
#define MSFT_DSCLocalConfigManager_GetMetaConfiguration                                 MI_T("GetMetaConfiguration")
#define MSFT_DSCLocalConfigManager_RollBack                                                             MI_T("RollBack")
#define MSFT_DSCLocalConfigManager_PerformRequiredConfigurationChecks   MI_T("PerformRequiredConfigurationChecks")
#define MSFT_DSCLocalConfigManager_StopConfiguration                                    MI_T("StopConfiguration")

/* MSFT_Credential */
#define MSFT_Credential_UserName                    MI_T("UserName")
#define MSFT_Credential_Password                    MI_T("Password")

/* MSFT_KeyValuePair */
#define MSFT_KeyValuePair_Key                   MI_T("Key")
#define MSFT_KeyValuePair_Value                 MI_T("Value")


/* MSFT_PartialConfiguration */
#define MSFT_PartialConfiguration_Description                       MI_T("Description")
#define MSFT_PartialConfiguration_ExclusiveResources                MI_T("ExclusiveResources")
#define MSFT_PartialConfiguration_ConfigurationSource               MI_T("ConfigurationSource")
#define MSFT_PartialConfiguration_ResourceModuleSource              MI_T("ResourceModuleSource")
#define MSFT_PartialConfiguration_DependsOn                         MI_T("DependsOn")
#define MSFT_PartialConfiguration_RefreshMode                       MI_T("RefreshMode")


#define MSFT_PartialConfiguration_FriendlyName          MI_T("PartialConfiguration")


#define MSFT_RegistrationKey_Name MI_T("RegistrationKey")
#define MSFT_ConfigurationNames_Name MI_T("ConfigurationNames")
#define DSC_InternalStateCache_RegisteredServerURLs     MI_T("RegisteredServerURLs")
#define AGENT_REGISTRATION_CLASS MI_T("MSFT_PSDSCAgentRegistration")
#define PULL_STATUSCODE_UPDATEMETACONFIG    MI_T("UpdateMetaConfiguration")
#define REGISTER_STATUSCODE_CREATED           MI_T("CREATED")
#define DSC_OAAS_CERTIFICATE_SUBJECT_CN       MI_T("CN=DSC-OaaS")
#define DSC_OAAS_CERTIFICATE_SUBJECT          MI_T("DSC-OaaS")
#define DSC_OAAS_CERTIFICATE_FRIENDLYNAME     MI_T("DSC-OaaS Client Authentication")
#define DSC_OAAS_CERTIFICATE_LIFETIME_YEARS   1
#define DSC_OAAS_SYSTEM_STORE_PATH            MI_T("My")


/*MSFT_ConfigurationDocumen*/
#define MSFT_WMIERROR_MESSAGE                  MI_T("Message")

/*DSC_InternalStateCache*/
#define DSC_InternalStateCache_ComplianceStatus     MI_T("ComplianceStatus")
#define DSC_InternalStateCache_GetActionStatusCode  MI_T("GetActionStatusCode")
#define DSC_InternalStateCache_LCMStatusCode            MI_T("LCMStatusCode")

#define DSC_RESOURCENAME                MI_T("LCM")
#define CA_ACTIVITY_NAME                MI_T("LCM")
#define METADATA_REFRESHMODE_PULL       MI_T("PULL")
#define METADATA_REFRESHMODE_PUSH       MI_T("PUSH")
#define EMPTY_STRING                        MI_T("")
#define DEVICE_NAME_SIZE                MAX_COMPUTERNAME_LENGTH+1 //Maximum computer name length possible is 15
#define TOKENIZED_OUTPUT_PADDING        50 //Padding required when outputs are tokenized

#define DEFAULT_DOWNLOADMANAGER MI_T("WebDownloadManager")
#define DSC_RESTART_SYSTEM_FLAG         1

#define LCM_SETFLAGS_DEFAULT            0
#define LCM_EXECUTE_SETONLY             (1 << 15)
#define LCM_SETFLAGS_SAVETOPENDINGONLY  (1 << 0)
#define LCM_SET_METACONFIG              (1 << 1)
#define LCM_SETFLAGS_ENABLEWHATIF       (1 << 2)
#define VALIDATE_REGISTRATION_INSTANCE  (1 << 3)
#define VALIDATE_DOCUMENT_INSTANCE      (1 << 4)
#define VALIDATE_METACONFIG_INSTANCE    (1 << 5)
#define LCM_EXECUTIONMODE_OFFLINE       (1 << 6)
#define LCM_EXECUTIONMODE_ONLINE        (1 << 7)
#define LCM_EXECUTE_TESTONLY            (1 << 8)
#define LCM_EXECUTE_APPLYNEWCONFIG      (1 << 27)

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
#define DSC_CONFIGURATIONMODE_MONITORONLY MI_T("MonitorOnly")
#define DEFAULT_RebootNodeIfNeeded MI_FALSE
#define DEFAULT_AllowModuleOverwrite MI_FALSE
#define DEFAULT_RefreshMode MI_T("PUSH")
#define DEFAULT_MinRefreshFrequencyMins 1
#define DEFAULT_MinRefreshFrequencyMinsString MI_T("1")
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
#define GEN_FPTR(x)    (void*)x
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
#define SQM_MACHINEGLOBAL_SESSIONID 13238784    //Session ID for all machine global sessions, present in sqmteam documentation online
#define SQM_RESOURCECOUNT_DATAPOINTID 12401             //Datapoint ID for PSDSCResourceCount, newly created for DSC , as present in sqmteam documentation online.
#define SQM_INDEX_PROVIDERNAME 1                                //Provider name is the second column in the PSDSCResoururceCount stream datapoint, hence it is indexed as 1
#define SQM_INDEX_RESOURCECOUNT 0                               //The resource count is the first column in the datapoint, indexed as 0.
#define SQM_PARAMETER_SIZE 2                                    //Total number of columns in the stream datapoint


typedef MI_Instance* MI_InstancePtr;
typedef MI_InstancePtr* MI_InstancePtrPtr;


#define NUM_PATHS_TO_LOOK_FOR_PROVIDERS   2 //Look for native providers in both the configuration directory inside systemdir , and inside c:\programfiles (as defined below)

#define MAX_COMPUTERNAME_LENGTH 15
#define PATH_SEPARATOR                              MI_T("/")

#if defined(BUILD_OMS)
#define OAAS_KEY MI_T("oms.key")
#define OAAS_CERT MI_T("oms.crt")
#define OAAS_THUMBPRINT MI_T("oms.thumbprint")

#define DSC_CONFIG_DIRNAME MI_T("omsconfig")
#define CONFIGURATION_SYSTEMDIR_BASE CONFIG_SYSCONFDIR PATH_SEPARATOR DSC_CONFIG_DIRNAME
#define OMI_CONSISTENCY_TASKSCHEDULE_NAME CONFIG_BINDIR PATH_SEPARATOR MI_T("OMSConsistencyInvoker")
#define OAAS_KEYPATH MI_T("/etc/opt/microsoft/omsagent/certs/") OAAS_KEY
#define OAAS_CERTPATH MI_T("/etc/opt/microsoft/omsagent/certs/") OAAS_CERT
#define OAAS_THUMBPRINTPATH MI_T("/etc/opt/microsoft/omsagent/certs/") OAAS_THUMBPRINT
#else
#define OAAS_KEY MI_T("oaas.key")
#define OAAS_CERT MI_T("oaas.crt")
#define OAAS_THUMBPRINT MI_T("oaas.thumbprint")

#define DSC_CONFIG_DIRNAME MI_T("dsc")
#define CONFIGURATION_SYSTEMDIR_BASE CONFIG_SYSCONFDIR PATH_SEPARATOR DSC_CONFIG_DIRNAME
#define OMI_CONSISTENCY_TASKSCHEDULE_NAME CONFIG_BINDIR PATH_SEPARATOR MI_T("ConsistencyInvoker")
#define OAAS_KEYPATH CONFIG_CERTSDIR MI_T("/") OAAS_KEY
#define OAAS_CERTPATH CONFIG_CERTSDIR MI_T("/") OAAS_CERT
#define OAAS_THUMBPRINTPATH CONFIG_CERTSDIR MI_T("/") OAAS_THUMBPRINT
#endif

#define OMI_RELOAD_COMMAND MI_T("touch /var/opt/omi/omiusers/reload_dispatcher; sleep 5")
#define CONFIGURATION_SYSTEMDIR CONFIG_SYSCONFDIR PATH_SEPARATOR DSC_CONFIG_DIRNAME  MI_T("/configuration")
#define CONFIGURATION_PROGFILES CONFIG_DATADIR PATH_SEPARATOR DSC_CONFIG_DIRNAME MI_T("/configuration")
#define AGENTID_FILE_PATH CONFIG_SYSCONFDIR PATH_SEPARATOR DSC_CONFIG_DIRNAME "/agentid"
#define OMI_CONF_FILE_PATH CONFIG_SYSCONFDIR PATH_SEPARATOR DSC_CONFIG_DIRNAME PATH_SEPARATOR MI_T("dsc.conf")

#define CONFIGURATION_SCHEMA_SEARCH_PATH                  CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("schema")
#define CONFIGURATION_PARTIALCONFIG_STORE               CONFIGURATION_SYSTEMDIR PATH_SEPARATOR MI_T("PartialConfigurations")

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

/**************************************
    constants used by LCM
    ******************************** ***/

#define CONFIGURATION_LOCATION_TEMPFILE_PREFIX MI_T("tmp")    
#define CONFIGURATION_LOCATION_PENDINGTMP MI_T("Pending.mof.tmp")
#define CONFIGURATION_LOCATION_PENDING MI_T("Pending.mof")
#define CONFIGURATION_LOCATION_PARTIALBASEDOCUMENT MI_T("PartialConfigBaseDocumentInstances.mof")
#define CONFIGURATION_LOCATION_PARTIALBASEDOCUMENTTMP MI_T("PartialConfigBaseDocumentInstances.mof.tmp")
#define CONFIGURATION_LOCATION_PARTIALCONFIGURATIONS_STORE MI_T("PartialConfigurations")
#define CONFIGURATION_LOCATION_GET MI_T("Get.mof")
#define CONFIGURATION_LOCATION_INVENTORY MI_T("Inventory.mof")
#define CONFIGURATION_LOCATION_INVENTORY_REPORT MI_T("Inventory.xml")
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

#define MOF_EXTENSION MI_T(".mof")
#define MOFCHECKSUM_EXTENSION MI_T(".mof.checksum")
#define PARTIALCONFIG_SUFFIX MI_T("PartialConfiguration")

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

#define OMI_RESOURCEMODULEMANAGER_CLASSNAME                         MI_T("OMI_ResourceModuleManager")
#define OMI_REPORTMANAGER_CLASSNAME                                 MI_T("OMI_ReportManager")
/* Error/Status Reporting */
#define REPORTING_SERIALIZEDERROR MI_T("CIMStatusCodeDescription")
#define REPORTING_ERRORSOURCE MI_T("ErrorSource")
#define REPORTING_RESOURCEID MI_T("ResourceId")
#define REPORTING_ERRORCODE MI_T("ErrorCode")
#define REPORTING_ERRORMESSAGE MI_T("ErrorMessage")
#define REPORTING_LOCALE MI_T("Locale")
#define REPORTING_ERRORCLASSNAME MI_T("MSFT_PSDSCError")
#define REPORTING_STATUSCLASSNAME MI_T("MSFT_PSDSCStatus")
#define REPORTING_CLASS MI_T("MSFT_PSDSCStatusReporting")
#define REPORTING_ERRORREPORTNAME   MI_T("ErrorReport")
#define REPORTING_STATUSREPORTNAME   MI_T("StatusReport")
#define REPORTING_JOBID MI_T("JobId")
#define REPORTING_STARTTIME MI_T("StartTime")
#define REPORTING_OPERATIONTYPE MI_T("OperationType")
#define REPORTING_CONFIGURATIONVERSION MI_T("ConfigurationVersion")
#define REPORTING_ENDTIME MI_T("EndTime")
#define REPORTING_NODENAME MI_T("NodeName")
#define REPORTING_IPADDRESS MI_T("IpAddress")
#define REPORTING_NUMBEROFRESOURCES MI_T("NumberOfResources")
#define REPORTING_RESOURCESINDESIREDSTATE MI_T("ResourcesInDesiredState")
#define REPORTING_RESOURCESNOTINDESIREDSTATE MI_T("ResourcesNotInDesiredState")
#define REPORTING_REPORTFORMATVERSION MI_T("ReportFormatVersion")

#define REPORTING_LCMVERSION MI_T("LcmVersion")
#define REPORTING_INTERNALERRORS MI_T("Errors")
/* Constants*/
#define REPORTING_DEFAULT_MESSAGE MI_T("Unknown")
#define REPORTING_TYPE_PSDSCRESOURCE MI_T("DSCPowershellResource")
#define REPORTING_TYPE_PSWMIRESOURCE MI_T("DSCWMIResource")
#define REPORTING_TYPE_DSCENGINERESOURCE MI_T("DSCEngine")

/* Agent Registration Payload */
#define AGENT_REGISTRATION_CLASS MI_T("MSFT_PSDSCAgentRegistration")

#define OMI_SERVER_PATH CONFIG_BINDIR PATH_SEPARATOR MI_T("omiserver")

#define TASK_PARAMETER_SC_DAILY MI_T("DAILY")
#define TASK_PARAMETER_DU_DAILY MI_T("24:00")
#define DSCCOMPUTERNAME MI_T("DSC_REMOTE_COMPUTERNAME")
#define DSCWHATIFENABLED MI_T("DSC_WHATIF_ENABLED")
#define DSC_JOBIDSTRING MI_T("DSC_JOBID_STRING")

#define REPORTFORMAT_VERSION_1_0                                                MI_T("1.0")
#define RETRY_LOOP_COUNT        10
#define RETRY_LOOP_SLEEP        500
#define CHECKSUM_SIZE 64
#define DEVICENAMESIZE MAX_COMPUTERNAME_LENGTH+1

#define LCM_STATUSCODE_READY 0
#define LCM_STATUSCODE_BUSY 1
#define LCM_STATUSCODE_REBOOT 2

#define LCM_STATUS_READY        MI_T("Ready")
#define LCM_STATUS_BUSY         MI_T("Busy")
#define LCM_STATUS_REBOOT       MI_T("PendingReboot")


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
    MI_Boolean bReportErrorsToServer;
    MI_Uint32 executionMode;
    void *context;
    MI_Uint32 messageOperation;//Start, failed, end
    MI_Uint32 messageItem;//test,get,resource
    const MI_Instance *metaConfig; //Read only meta Config.
    MI_Boolean bNotFirstTimeReport; //signifies if this is the first time report is being sent.
    MI_Serializer *serializer;
    void * registrationManager;
} LCMProviderContext;

MI_Char* DSC_strdup(MI_Char* s);

typedef struct _StatusReport_ResourceNotInDesiredState
{
    char * SourceInfo;
    char * ModuleName;
    char * DurationInSeconds;
    char * InstanceName;
    char * StartDate;
    char * ResourceName;
    char * ModuleVersion;
    char * RebootRequested;
    char * ResourceId;
    char * ConfigurationName;
    char * InDesiredState;

} StatusReport_ResourceNotInDesiredState;

StatusReport_ResourceNotInDesiredState * Construct_StatusReport_RNIDS(
    char* SourceInfo,
    char* ModuleName,
    char* DurationInSeconds,
    char* InstanceName,
    char* StartDate,
    char* ResourceName,
    char* ModuleVersion,
    char* RebootRequested,
    char* ResourceId,
    char* ConfigurationName,
    char* InDesiredState
    );

void Destroy_StatusReport_RNIDS(StatusReport_ResourceNotInDesiredState* ptr);

// Structres to represent the V2 pullserver response for GetAction
typedef struct GetActionConfigurationStatus
{
    MI_Char *ConfigurationName;
    MI_Char *Status;
}ConfigurationStatus;

typedef struct OverAllGetActionResponse
{
    MI_Char *NodeOverAllStatus;
    MI_Uint32 NumberOfConfiguration;
    ConfigurationStatus *Details;
}OverAllGetActionResponse;


/* TODO: remove
typedef struct _LCMProviderContext
{
    MI_Uint32 executionMode;
    void *context;
    MI_Uint32 messageOperation;//Start, failed, end
    MI_Uint32 messageItem;//test,get,resource
} LCMProviderContext;
*/

typedef struct _NativeResourceManager NativeResourceManager;

typedef struct _ProviderCallbackContext
{
    LCMProviderContext *lcmProviderContext;
    NativeResourceManager* nativeResourceManager;
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
MI_Result  CreateMiInstanceErrorObject(
        _Outptr_result_maybenull_ MI_Instance **p_cim_error_details,
        _In_z_ const MI_Char *p_format,
        ...
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

MI_Result GetCimWin32Error1Param(MI_Uint32 result ,
                        _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                        _In_ MI_Uint32 errorStringId,
                        _In_z_ const MI_Char * param1);


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

/*Function to return true if we should use partial configurations instead of full. If shouldCheckPartialConfigDirectoryForFiles is set to true, then it will also check for non empty directory status before returning*/
MI_Boolean ShouldUsePartialConfigurations(_In_ MI_Instance*  metaConfigInstance,
        _In_ MI_Boolean shouldCheckPartialConfigDirectoryForFiles);

void InitLocTable();

MI_Result GetAgentInformation(
    _Inout_ MI_Instance** registrationPayload);

MI_Result UpdateMetaConfigWithAgentId(_In_z_ MI_Char *agentId, _Inout_ MI_Instance *metaConfigInstance);

MI_Result ShouldUseV1Protocol(
    _Inout_ MI_Boolean* isV1MetaConfig);

MI_Result StripBracesFromGuid(
    _In_z_ MI_Char* inputGuid,
    _Outptr_result_maybenull_z_ MI_Char** resultGuid,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Datetime PalDatetimeToMiDatetime(_In_ PAL_Datetime inDatetime);

extern char g_currentError[5001];
extern StatusReport_ResourceNotInDesiredState * g_rnids;
extern MSFT_DSCMetaConfiguration *g_metaConfig;


#ifndef g_ConfigurationDetails

#define JOB_UUID_LENGTH 41*sizeof(MI_Char)
    typedef struct _ConfigurationDetails
    {
	MI_Char jobGuidString[JOB_UUID_LENGTH];
	MI_Boolean hasSetDetail;
    } ConfigurationDetails;

    extern ConfigurationDetails g_ConfigurationDetails;
#endif


MI_Boolean IsDSCResource(_In_ MI_Instance *instance);

#endif

/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <oi/oi_file.h>

#if defined(CONFIG_ENABLE_DEBUG)
#define CUMethodWarning(a0, a1) CUMethodWarning_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define CUMethodWarning(a0, a1) CUMethodWarning_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4253, CUMethodWarning_Impl, LOG_WARNING, PAL_T("Job %1 : \nWarningMessage %2"), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMAboutToMergePartial(a0) LCMAboutToMergePartial_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMAboutToMergePartial(a0) LCMAboutToMergePartial_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4277, LCMAboutToMergePartial_Impl, LOG_INFO, PAL_T("Job %s : \nLooking into the partial configuration store to merge any present partial configurations."), const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define LCMApplyingPartial(a0, a1) LCMApplyingPartial_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMApplyingPartial(a0, a1) LCMApplyingPartial_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4275, LCMApplyingPartial_Impl, LOG_INFO, PAL_T("Job %s : \nStarting to apply partial configuration %s."), const TChar*, const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define LCMIdentifiedModePartial(a0) LCMIdentifiedModePartial_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMIdentifiedModePartial(a0) LCMIdentifiedModePartial_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4276, LCMIdentifiedModePartial_Impl, LOG_INFO, PAL_T("Job %s : \nHandling application of configurations in partial configuration mode based on the meta configuration definition."), const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define LCMMergingPartialConfiguration(a0, a1) LCMMergingPartialConfiguration_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMMergingPartialConfiguration(a0, a1) LCMMergingPartialConfiguration_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4278, LCMMergingPartialConfiguration_Impl, LOG_INFO, PAL_T("Job %s : \nMerging partial configuration %s into pending.mof"), const TChar*, const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullingPartial(a0, a1) LCMPullingPartial_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullingPartial(a0, a1) LCMPullingPartial_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4274, LCMPullingPartial_Impl, LOG_INFO, PAL_T("Job %s : \nPulling partial configuration %s from the server."), const TChar*, const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define PartialConfigurationNotAvailable(a0, a1) PartialConfigurationNotAvailable_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define PartialConfigurationNotAvailable(a0, a1) PartialConfigurationNotAvailable_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4267, PartialConfigurationNotAvailable_Impl, LOG_WARNING, PAL_T("Job %s : \nPartial Configuration %s not available on configuration server."), const TChar*, const TChar*)


#if defined(CONFIG_ENABLE_DEBUG)
#define LCMValidatingMergedPartial(a0) LCMValidatingMergedPartial_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMValidatingMergedPartial(a0) LCMValidatingMergedPartial_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4280, LCMValidatingMergedPartial_Impl, LOG_INFO, PAL_T("Job %s : \nValidating the document got from merging all partial configurations"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMValidatingMetaConfPartial(a0) LCMValidatingMetaConfPartial_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMValidatingMetaConfPartial(a0) LCMValidatingMetaConfPartial_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4281, LCMValidatingMetaConfPartial_Impl, LOG_INFO, PAL_T("Job %s : \nValidating the partial configuration definition blocks inside the meta configuration."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMValidatingPartialConfigName(a0, a1) LCMValidatingPartialConfigName_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMValidatingPartialConfigName(a0, a1) LCMValidatingPartialConfigName_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4282, LCMValidatingPartialConfigName_Impl, LOG_INFO, PAL_T("Job %s : \nValidating that the name of the partial configuration %s is consistent across the partial configuration ."), const TChar*, const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define LCMValidatingPartialConfigMetaConfDownloadMgr(a0) LCMValidatingPartialConfigMetaConfDownloadMgr_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMValidatingPartialConfigMetaConfDownloadMgr(a0) LCMValidatingPartialConfigMetaConfDownloadMgr_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4283, LCMValidatingPartialConfigMetaConfDownloadMgr_Impl, LOG_INFO, PAL_T("Job %s : \nValidating that the configuration source defined in each partial configuration inside the meta configuration are defined as configuration download managers as well ."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMValidatingPartialConfigMetaConfExclusiveResources(a0) LCMValidatingPartialConfigMetaConfExclusiveResources_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMValidatingPartialConfigMetaConfExclusiveResources(a0) LCMValidatingPartialConfigMetaConfExclusiveResources_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4284, LCMValidatingPartialConfigMetaConfExclusiveResources_Impl, LOG_INFO, PAL_T("Job %s : \nValidating that the exclusive resources are not conflicting in the meta configuration definition ."), const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define LCMValidatingPartialConfiguration(a0, a1) LCMValidatingPartialConfiguration_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMValidatingPartialConfiguration(a0, a1) LCMValidatingPartialConfiguration_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4279, LCMValidatingPartialConfiguration_Impl, LOG_INFO, PAL_T("Job %s : \nValidating the partial configuration %s for consistency in configuration Name and exclusive resources"), const TChar*, const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define LCMValidatingPartialExclusiveResourceStringDefintion(a0, a1) LCMValidatingPartialExclusiveResourceStringDefintion_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMValidatingPartialExclusiveResourceStringDefintion(a0, a1) LCMValidatingPartialExclusiveResourceStringDefintion_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4285, LCMValidatingPartialExclusiveResourceStringDefintion_Impl, LOG_INFO, PAL_T("Job %s : \nValidating if the exclusive resource %s is written in the correct format"), const TChar*, const TChar*)


#if defined(CONFIG_ENABLE_DEBUG)
#define LCMSendConfigurationError(a0, a1, a2, a3, a4, a5, a6) LCMSendConfigurationError_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2, tcs(a3), tcs(a4), tcs(a5), tcs(a6))
#else
#define LCMSendConfigurationError(a0, a1, a2, a3, a4, a5, a6) LCMSendConfigurationError_Impl(0, 0, tcs(a0), tcs(a1), a2, tcs(a3), tcs(a4), tcs(a5), tcs(a6))
#endif
FILE_EVENT7(4097, LCMSendConfigurationError_Impl, LOG_ERR, PAL_T("Job %s : \nThis event indicates that failure happens when %s is processing the configuration. ErrorId is %x. ErrorDetail is %s. ResourceId is %s and SourceInfo is %s. ErrorMessage is %s."), const TChar*, const TChar*, Hex_Int32, const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define DumpMessageFromBuiltinProvider(a0, a1, a2, a3) DumpMessageFromBuiltinProvider_Impl(__FILE__, __LINE__, tcs(a0), a1, tcs(a2), tcs(a3))
#else
#define DumpMessageFromBuiltinProvider(a0, a1, a2, a3) DumpMessageFromBuiltinProvider_Impl(0, 0, tcs(a0), a1, tcs(a2), tcs(a3))
#endif
FILE_EVENT4(4098, DumpMessageFromBuiltinProvider_Impl, LOG_WARNING, PAL_T("Job %s : \nDisplaying messages from built-in DSC resources:\n\t WMI channel %d \n\t ResourceID: %s \n\t Message : %s"), const TChar*, MI_Uint32, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MethodStart(a0, a1) MethodStart_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MethodStart(a0, a1) MethodStart_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4099, MethodStart_Impl, LOG_INFO, PAL_T("Job %s : \nMethod %s started."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageFromEngine(a0, a1, a2, a3) MessageFromEngine_Impl(__FILE__, __LINE__, tcs(a0), a1, tcs(a2), tcs(a3))
#else
#define MessageFromEngine(a0, a1, a2, a3) MessageFromEngine_Impl(0, 0, tcs(a0), a1, tcs(a2), tcs(a3))
#endif
FILE_EVENT4(4100, MessageFromEngine_Impl, LOG_INFO, PAL_T("Job %s : \nDisplaying messages from the engine:\n\t WMI channel %d \n\t ResourceID: %s \n\t Message : %s"), const TChar*, MI_Uint32, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define GenericMessageFromBuiltinProvider(a0, a1, a2) GenericMessageFromBuiltinProvider_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define GenericMessageFromBuiltinProvider(a0, a1, a2) GenericMessageFromBuiltinProvider_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4101, GenericMessageFromBuiltinProvider_Impl, LOG_INFO, PAL_T("Job %s : \nFrom %s, message is %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMRepudiationInfomation(a0, a1, a2) LCMRepudiationInfomation_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMRepudiationInfomation(a0, a1, a2) LCMRepudiationInfomation_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4102, LCMRepudiationInfomation_Impl, LOG_INFO, PAL_T("Job %s : \nConfiguration is sent from computer %s by user sid %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define PsProviderNonTerminatingError(a0, a1, a2, a3, a4, a5) PsProviderNonTerminatingError_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3), tcs(a4), tcs(a5))
#else
#define PsProviderNonTerminatingError(a0, a1, a2, a3, a4, a5) PsProviderNonTerminatingError_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3), tcs(a4), tcs(a5))
#endif
FILE_EVENT6(4103, PsProviderNonTerminatingError_Impl, LOG_ERR, PAL_T("Job %s : \nThis event indicates that a non-terminating error was thrown when %s was executing %s on %s DSC resource. FullyQualifiedErrorId is %s. ErrorMessage is %s."), const TChar*, const TChar*, const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullEngineError(a0, a1, a2, a3, a4) LCMPullEngineError_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), a3, tcs(a4))
#else
#define LCMPullEngineError(a0, a1, a2, a3, a4) LCMPullEngineError_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), a3, tcs(a4))
#endif
FILE_EVENT5(4104, LCMPullEngineError_Impl, LOG_ERR, PAL_T("Job %s : \nThis event indicates that failure happens when %s is trying to get the configuration from pull server using download manager %s. ErrorId is %d. ErrorDetail is %s"), const TChar*, const TChar*, const TChar*, Hex_Int32, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullGetConfigAttempt(a0, a1, a2) LCMPullGetConfigAttempt_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullGetConfigAttempt(a0, a1, a2) LCMPullGetConfigAttempt_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4105, LCMPullGetConfigAttempt_Impl, LOG_INFO, PAL_T("Job %3 : \nAttempting to get the configuration from pull server using Download Manager %s.Configuration Id is %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullGetModuleAttempt(a0, a1, a2, a3) LCMPullGetModuleAttempt_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#else
#define LCMPullGetModuleAttempt(a0, a1, a2, a3) LCMPullGetModuleAttempt_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#endif
FILE_EVENT4(4106, LCMPullGetModuleAttempt_Impl, LOG_INFO, PAL_T("Job %s : \nAttempting to get the modules from pull server using Download Manager %s. Configuration Id is %s. Modules are %s."), const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullGetActionAttempt(a0, a1, a2, a3, a4) LCMPullGetActionAttempt_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3), a4)
#else
#define LCMPullGetActionAttempt(a0, a1, a2, a3, a4) LCMPullGetActionAttempt_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3), a4)
#endif
FILE_EVENT5(4107, LCMPullGetActionAttempt_Impl, LOG_INFO, PAL_T("Job %s : \nAttempting to get the action from pull server using Download Manager %s. Configuration Id is %s. Checksum is %s. Compliance status is %d."), const TChar*, const TChar*, const TChar*, const TChar*, BOOL)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullGetConfigSuccess(a0, a1) LCMPullGetConfigSuccess_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullGetConfigSuccess(a0, a1) LCMPullGetConfigSuccess_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4108, LCMPullGetConfigSuccess_Impl, LOG_INFO, PAL_T("Job %s : \nSuccessfully got the configuration from pull server using Download Manager %s."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullGetModuleSuccess(a0, a1) LCMPullGetModuleSuccess_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullGetModuleSuccess(a0, a1) LCMPullGetModuleSuccess_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4109, LCMPullGetModuleSuccess_Impl, LOG_INFO, PAL_T("Job %s : \nSuccessfully got the modules from pull server using Download Manager %s."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullGetActionSuccess(a0, a1, a2) LCMPullGetActionSuccess_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullGetActionSuccess(a0, a1, a2) LCMPullGetActionSuccess_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4110, LCMPullGetActionSuccess_Impl, LOG_INFO, PAL_T("Job %s : \nSuccessfully got the action %s from pull server using Download Manager %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullCertificateInstall(a0, a1, a2) LCMPullCertificateInstall_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullCertificateInstall(a0, a1, a2) LCMPullCertificateInstall_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4111, LCMPullCertificateInstall_Impl, LOG_INFO, PAL_T("Job %s : \nSuccessfully installed the certificate %s from %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullCertificateSkip(a0, a1) LCMPullCertificateSkip_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullCertificateSkip(a0, a1) LCMPullCertificateSkip_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4112, LCMPullCertificateSkip_Impl, LOG_INFO, PAL_T("Job %s : \nSkipping installing certificate %s as it is already installed."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullCertificateFileDeleted(a0, a1) LCMPullCertificateFileDeleted_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullCertificateFileDeleted(a0, a1) LCMPullCertificateFileDeleted_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4113, LCMPullCertificateFileDeleted_Impl, LOG_INFO, PAL_T("Job %s : \nSuccessfully deleted certificate file %s."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMConsistencyEngineRunAttempt(a0) LCMConsistencyEngineRunAttempt_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMConsistencyEngineRunAttempt(a0) LCMConsistencyEngineRunAttempt_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4114, LCMConsistencyEngineRunAttempt_Impl, LOG_INFO, PAL_T("Job %s : \nRunning consistency engine."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMConsistencyEngineRunSuccess(a0) LCMConsistencyEngineRunSuccess_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMConsistencyEngineRunSuccess(a0) LCMConsistencyEngineRunSuccess_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4115, LCMConsistencyEngineRunSuccess_Impl, LOG_INFO, PAL_T("Job %s : \nConsistency engine was run successfully."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMConsistencyEngineError(a0, a1, a2) LCMConsistencyEngineError_Impl(__FILE__, __LINE__, tcs(a0), a1, tcs(a2))
#else
#define LCMConsistencyEngineError(a0, a1, a2) LCMConsistencyEngineError_Impl(0, 0, tcs(a0), a1, tcs(a2))
#endif
FILE_EVENT3(4116, LCMConsistencyEngineError_Impl, LOG_ERR, PAL_T("Job %s : \nThis event indicates that failure happened while trying to run consistency engine. ErrorId is %d. ErrorDetail is %s"), const TChar*, MI_Uint32, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define VerboseMessageFromPsProvider(a0, a1, a2) VerboseMessageFromPsProvider_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define VerboseMessageFromPsProvider(a0, a1, a2) VerboseMessageFromPsProvider_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4117, VerboseMessageFromPsProvider_Impl, LOG_INFO, PAL_T("Job %s : \nDisplaying verbose messages from Powershell DSC resource:\n\t ResourceID : %s \n\t Message : %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define DebugMessageFromPsProvider(a0, a1, a2) DebugMessageFromPsProvider_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define DebugMessageFromPsProvider(a0, a1, a2) DebugMessageFromPsProvider_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4118, DebugMessageFromPsProvider_Impl, LOG_INFO, PAL_T("Job %s : \nDisplaying debug messages from Powershell DSC resource:\n\t ResourceID : %s \n\t Message : %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define EngineMethodParameters(a0, a1, a2, a3, a4, a5, a6) EngineMethodParameters_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3), a4, a5, tcs(a6))
#else
#define EngineMethodParameters(a0, a1, a2, a3, a4, a5, a6) EngineMethodParameters_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3), a4, a5, tcs(a6))
#endif
FILE_EVENT7(4119, EngineMethodParameters_Impl, LOG_INFO, PAL_T("Job %s : \nMethod %s started with parameters \n \t Class name: %s \n \t Resource ID: %s \n \t Flags: %d \n \t Execution Mode: %d \n \t DSC resource Namespace: %s "), const TChar*, const TChar*, const TChar*, const TChar*, MI_Uint32, MI_Uint32, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MethodEnd(a0, a1) MethodEnd_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MethodEnd(a0, a1) MethodEnd_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4120, MethodEnd_Impl, LOG_INFO, PAL_T("Job %s : \nMethod %s ended successfully"), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define ConfigurationCancelledInTheMiddle(a0, a1, a2) ConfigurationCancelledInTheMiddle_Impl(__FILE__, __LINE__, tcs(a0), a1, a2)
#else
#define ConfigurationCancelledInTheMiddle(a0, a1, a2) ConfigurationCancelledInTheMiddle_Impl(0, 0, tcs(a0), a1, a2)
#endif
FILE_EVENT3(4121, ConfigurationCancelledInTheMiddle_Impl, LOG_WARNING, PAL_T("Job %s : \nCurrent configuration is cancelled. %d out of %d resources are not configured."), const TChar*, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define PsConfigurationStopped(a0) PsConfigurationStopped_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define PsConfigurationStopped(a0) PsConfigurationStopped_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4128, PsConfigurationStopped_Impl, LOG_WARNING, PAL_T("Job %s : \nConfiguration is stopped when Powershell DSC resource is executing."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define NativeProviderWriteProgressError(a0, a1) NativeProviderWriteProgressError_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define NativeProviderWriteProgressError(a0, a1) NativeProviderWriteProgressError_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENT2(4129, NativeProviderWriteProgressError_Impl, LOG_ERR, PAL_T("Job %s : \nWrite progress failed with error code %d. The current configuration will be stopped."), const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define ConfigurationForcelyStopped(a0) ConfigurationForcelyStopped_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define ConfigurationForcelyStopped(a0) ConfigurationForcelyStopped_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4130, ConfigurationForcelyStopped_Impl, LOG_WARNING, PAL_T("Job %s : \nCurrent configuration is forcely stopped."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define CimError(a0, a1, a2) CimError_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2)
#else
#define CimError(a0, a1, a2) CimError_Impl(0, 0, tcs(a0), tcs(a1), a2)
#endif
FILE_EVENT3(4131, CimError_Impl, LOG_ERR, PAL_T("Job %s : \nDSC Engine Error : \n\t Error Message %s \n\tError Code : %d "), const TChar*, const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageRegisteringModule(a0, a1) MessageRegisteringModule_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageRegisteringModule(a0, a1) MessageRegisteringModule_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4132, MessageRegisteringModule_Impl, LOG_INFO, PAL_T("Job %s : \nGetting a registration instance for %s"), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageLoadingInstance(a0, a1) MessageLoadingInstance_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageLoadingInstance(a0, a1) MessageLoadingInstance_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4133, MessageLoadingInstance_Impl, LOG_INFO, PAL_T("Job %s : \nModule manager is loading instance document from location %s"), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingDocInstance(a0) ValidatingDocInstance_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define ValidatingDocInstance(a0) ValidatingDocInstance_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4134, ValidatingDocInstance_Impl, LOG_INFO, PAL_T("Job %s : \nValidating instance document."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDeletingInstance(a0, a1) MessageDeletingInstance_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageDeletingInstance(a0, a1) MessageDeletingInstance_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4135, MessageDeletingInstance_Impl, LOG_INFO, PAL_T("Job %s : \nDeleting instance document from location %s since it is invalid."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageParsingConfiguration(a0) MessageParsingConfiguration_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageParsingConfiguration(a0) MessageParsingConfiguration_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4136, MessageParsingConfiguration_Impl, LOG_INFO, PAL_T("Job %s : \nParsing the configuration to apply."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageResolvingDependency(a0) MessageResolvingDependency_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageResolvingDependency(a0) MessageResolvingDependency_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4137, MessageResolvingDependency_Impl, LOG_INFO, PAL_T("Job %s : \nResolving Dependencies inside the configuration document."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageSettingResourcesOrder(a0, a1) MessageSettingResourcesOrder_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define MessageSettingResourcesOrder(a0, a1) MessageSettingResourcesOrder_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENT2(4144, MessageSettingResourcesOrder_Impl, LOG_INFO, PAL_T("Job %s : \nSetting resources in order. Number of resources: %d"), const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageProcessingResource(a0, a1, a2) MessageProcessingResource_Impl(__FILE__, __LINE__, tcs(a0), a1, tcs(a2))
#else
#define MessageProcessingResource(a0, a1, a2) MessageProcessingResource_Impl(0, 0, tcs(a0), a1, tcs(a2))
#endif
FILE_EVENT3(4145, MessageProcessingResource_Impl, LOG_INFO, PAL_T("Job %s : \nProcessing resource index %d, name %s"), const TChar*, MI_Uint32, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageGettingMetaConfig(a0) MessageGettingMetaConfig_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageGettingMetaConfig(a0) MessageGettingMetaConfig_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4146, MessageGettingMetaConfig_Impl, LOG_INFO, PAL_T("Job %s : \nGetting Metaconfiguration details."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageMoveResourceToDesired(a0, a1, a2) MessageMoveResourceToDesired_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessageMoveResourceToDesired(a0, a1, a2) MessageMoveResourceToDesired_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4147, MessageMoveResourceToDesired_Impl, LOG_INFO, PAL_T("Job %s : \nMoving the resource %s of class %s to desired state."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageSettingMetaConfig(a0) MessageSettingMetaConfig_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageSettingMetaConfig(a0) MessageSettingMetaConfig_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4148, MessageSettingMetaConfig_Impl, LOG_INFO, PAL_T("Job %s : \nSetting Metaconfiguration instance."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageSavingConfig(a0, a1) MessageSavingConfig_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageSavingConfig(a0, a1) MessageSavingConfig_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4149, MessageSavingConfig_Impl, LOG_INFO, PAL_T("Job %s : \nSaving configuration instance into %s."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageCopyingConfig(a0, a1, a2) MessageCopyingConfig_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessageCopyingConfig(a0, a1, a2) MessageCopyingConfig_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4150, MessageCopyingConfig_Impl, LOG_INFO, PAL_T("Job %s : \nCopying configuration file from %s to %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageApplyingConfig(a0, a1) MessageApplyingConfig_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageApplyingConfig(a0, a1) MessageApplyingConfig_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4151, MessageApplyingConfig_Impl, LOG_INFO, PAL_T("Job %s : \nApplying configuration from %s."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageWaitCurrentConfig(a0) MessageWaitCurrentConfig_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageWaitCurrentConfig(a0) MessageWaitCurrentConfig_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4152, MessageWaitCurrentConfig_Impl, LOG_INFO, PAL_T("Job %s : \nWaiting for the current configuration to stop"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDeletingFile(a0, a1) MessageDeletingFile_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageDeletingFile(a0, a1) MessageDeletingFile_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4153, MessageDeletingFile_Impl, LOG_INFO, PAL_T("Job %s : \nDeleting file from %s"), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageScheduleTaskAfterReboot(a0) MessageScheduleTaskAfterReboot_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageScheduleTaskAfterReboot(a0) MessageScheduleTaskAfterReboot_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4160, MessageScheduleTaskAfterReboot_Impl, LOG_INFO, PAL_T("Job %s : \nRegistering the task with task scheduler after rebooting the machine"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageScheduleReboot(a0) MessageScheduleReboot_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageScheduleReboot(a0) MessageScheduleReboot_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4161, MessageScheduleReboot_Impl, LOG_INFO, PAL_T("Job %s : \nScheduling a restart of the machine"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageExecutingPS(a0, a1, a2) MessageExecutingPS_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessageExecutingPS(a0, a1, a2) MessageExecutingPS_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4162, MessageExecutingPS_Impl, LOG_INFO, PAL_T("Job %s : \nExecuting operations for PS DSC resource %s with resource name %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageExecutingWMI(a0, a1, a2) MessageExecutingWMI_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessageExecutingWMI(a0, a1, a2) MessageExecutingWMI_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4163, MessageExecutingWMI_Impl, LOG_INFO, PAL_T("Job %s : \nExecuting operations for WMIv2 DSC resource %2s with resource name %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessagePsGet(a0, a1, a2) MessagePsGet_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessagePsGet(a0, a1, a2) MessagePsGet_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4164, MessagePsGet_Impl, LOG_INFO, PAL_T("Job %s : \nExecuting GET for PS DSC resource %s with resource name %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageWmiGet(a0, a1, a2) MessageWmiGet_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessageWmiGet(a0, a1, a2) MessageWmiGet_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4165, MessageWmiGet_Impl, LOG_INFO, PAL_T("Job %s : \nExecuting GET for WMIv2 DSC resource %s with resource name %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageInvokingSession(a0, a1, a2, a3) MessageInvokingSession_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#else
#define MessageInvokingSession(a0, a1, a2, a3) MessageInvokingSession_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#endif
FILE_EVENT4(4166, MessageInvokingSession_Impl, LOG_INFO, PAL_T("Job %s : \nInvoking session and getting result for namespace %s, classname %s for method %s"), const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageGetSchemaPath(a0) MessageGetSchemaPath_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageGetSchemaPath(a0) MessageGetSchemaPath_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4167, MessageGetSchemaPath_Impl, LOG_INFO, PAL_T("Job %s : \nGetting PS DSC resource schema path and registration information"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MSFTMethodParameters(a0, a1, a2, a3, a4) MSFTMethodParameters_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3), tcs(a4))
#else
#define MSFTMethodParameters(a0, a1, a2, a3, a4) MSFTMethodParameters_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3), tcs(a4))
#endif
FILE_EVENT5(4168, MSFTMethodParameters_Impl, LOG_INFO, PAL_T("Job %s : \nFunction %s started with parameters \n \t Class name: %s \n \t Method Name: %s \n \t Namespace: %s "), const TChar*, const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LocalConfigMethodParameters(a0, a1, a2, a3, a4) LocalConfigMethodParameters_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2, a3, a4)
#else
#define LocalConfigMethodParameters(a0, a1, a2, a3, a4) LocalConfigMethodParameters_Impl(0, 0, tcs(a0), tcs(a1), a2, a3, a4)
#endif
FILE_EVENT5(4169, LocalConfigMethodParameters_Impl, LOG_INFO, PAL_T("Job %s : \nFunction %s started with parameters \n \t DataSize: %d \n \t Flags: %d \n \t Execution Mode: %d "), const TChar*, const TChar*, MI_Uint32, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingInfrastructureSchema(a0, a1) ValidatingInfrastructureSchema_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define ValidatingInfrastructureSchema(a0, a1) ValidatingInfrastructureSchema_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENT2(4176, ValidatingInfrastructureSchema_Impl, LOG_INFO, PAL_T("Job %s : \nValidating infrastructure schema"), const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingProviderRegistration(a0, a1, a2) ValidatingProviderRegistration_Impl(__FILE__, __LINE__, tcs(a0), a1, a2)
#else
#define ValidatingProviderRegistration(a0, a1, a2) ValidatingProviderRegistration_Impl(0, 0, tcs(a0), a1, a2)
#endif
FILE_EVENT3(4177, ValidatingProviderRegistration_Impl, LOG_INFO, PAL_T("Job %s : \nValidating DSC resource registration against schema \n\t Number of classes: %d \n\t Number of Registrations: %d "), const TChar*, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingDSCProviderSchema(a0, a1) ValidatingDSCProviderSchema_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define ValidatingDSCProviderSchema(a0, a1) ValidatingDSCProviderSchema_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENT2(4178, ValidatingDSCProviderSchema_Impl, LOG_INFO, PAL_T("Job %s : \nValidating DSC resource schema against a class array of size %d"), const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingSchema(a0, a1, a2, a3) ValidatingSchema_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2, a3)
#else
#define ValidatingSchema(a0, a1, a2, a3) ValidatingSchema_Impl(0, 0, tcs(a0), tcs(a1), a2, a3)
#endif
FILE_EVENT4(4179, ValidatingSchema_Impl, LOG_INFO, PAL_T("Job %s : \nValidating Schema of class %s which is class index %d in an array of classes of size %d"), const TChar*, const TChar*, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingDSCDocInstance(a0, a1, a2) ValidatingDSCDocInstance_Impl(__FILE__, __LINE__, tcs(a0), a1, a2)
#else
#define ValidatingDSCDocInstance(a0, a1, a2) ValidatingDSCDocInstance_Impl(0, 0, tcs(a0), a1, a2)
#endif
FILE_EVENT3(4180, ValidatingDSCDocInstance_Impl, LOG_INFO, PAL_T("Job %s : \nValidating DSC Document instance with instance array size of %d and flags %d"), const TChar*, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingDSCProviderRegistrationInstance(a0, a1) ValidatingDSCProviderRegistrationInstance_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define ValidatingDSCProviderRegistrationInstance(a0, a1) ValidatingDSCProviderRegistrationInstance_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4181, ValidatingDSCProviderRegistrationInstance_Impl, LOG_INFO, PAL_T("Job %s : \nValidating DSC resource registration instance for class : %s"), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define ValidatingClassProperty(a0, a1, a2) ValidatingClassProperty_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define ValidatingClassProperty(a0, a1, a2) ValidatingClassProperty_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4182, ValidatingClassProperty_Impl, LOG_INFO, PAL_T("Job %s : \nValidating Class property %s for class %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define DeleteFileFailed(a0, a1, a2, a3, a4) DeleteFileFailed_Impl(__FILE__, __LINE__, tcs(a0), a1, tcs(a2), a3, tcs(a4))
#else
#define DeleteFileFailed(a0, a1, a2, a3, a4) DeleteFileFailed_Impl(0, 0, tcs(a0), a1, tcs(a2), a3, tcs(a4))
#endif
FILE_EVENT5(4183, DeleteFileFailed_Impl, LOG_ERR, PAL_T("Job %s : Failed attempt number %d : Couldn&apos;t delete file  %s . The error code is %d. The error message is: %s"), const TChar*, MI_Uint32, const TChar*, MI_Uint32, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define NotRegisteredForPull(a0) NotRegisteredForPull_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define NotRegisteredForPull(a0) NotRegisteredForPull_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4184, NotRegisteredForPull_Impl, LOG_INFO, PAL_T("Job %s : \nThe current metaconfiguration is not registered for Pull configuration mode"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define FailedToRegisterPullServerTask(a0) FailedToRegisterPullServerTask_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define FailedToRegisterPullServerTask(a0) FailedToRegisterPullServerTask_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4185, FailedToRegisterPullServerTask_Impl, LOG_ERR, PAL_T("Job %s : \nFailed to register the Pull Server Task for the current metaconfiguration"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define FailedToRegisterConsistencyTask(a0) FailedToRegisterConsistencyTask_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define FailedToRegisterConsistencyTask(a0) FailedToRegisterConsistencyTask_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4192, FailedToRegisterConsistencyTask_Impl, LOG_ERR, PAL_T("Job %s : \nFailed to register the Consistency Task for the current metaconfiguration"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define CopyConfigurationFailed(a0, a1, a2) CopyConfigurationFailed_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define CopyConfigurationFailed(a0, a1, a2) CopyConfigurationFailed_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4193, CopyConfigurationFailed_Impl, LOG_ERR, PAL_T("Job %s : \nFailed to copy the configuration from location %s to location %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define DeleteCurrentConfigFailed(a0) DeleteCurrentConfigFailed_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define DeleteCurrentConfigFailed(a0) DeleteCurrentConfigFailed_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4194, DeleteCurrentConfigFailed_Impl, LOG_ERR, PAL_T("Job %s : \nFailed to delete the current configuration file"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define RestartedMachine(a0) RestartedMachine_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define RestartedMachine(a0) RestartedMachine_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4195, RestartedMachine_Impl, LOG_INFO, PAL_T("Job %s : \nMachine was restarted as needed by one or more DSC resources."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define RestoringConfiguration(a0) RestoringConfiguration_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define RestoringConfiguration(a0) RestoringConfiguration_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4196, RestoringConfiguration_Impl, LOG_INFO, PAL_T("Job %s : \nRestoring the configuration to previous configuration"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define ReadingMOFFile(a0, a1) ReadingMOFFile_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define ReadingMOFFile(a0, a1) ReadingMOFFile_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4197, ReadingMOFFile_Impl, LOG_INFO, PAL_T("Job %s : \nReading the file content from %s"), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMConsistencyEngineNoCurrentPending(a0) LCMConsistencyEngineNoCurrentPending_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMConsistencyEngineNoCurrentPending(a0) LCMConsistencyEngineNoCurrentPending_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4198, LCMConsistencyEngineNoCurrentPending_Impl, LOG_INFO, PAL_T("Job %s : \nConsistency Engine did not find a current or pending configuration to apply"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleChecksumValidationResult(a0, a1, a2) LCMPullModuleChecksumValidationResult_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2)
#else
#define LCMPullModuleChecksumValidationResult(a0, a1, a2) LCMPullModuleChecksumValidationResult_Impl(0, 0, tcs(a0), tcs(a1), a2)
#endif
FILE_EVENT3(4199, LCMPullModuleChecksumValidationResult_Impl, LOG_INFO, PAL_T("Job %s : \nThe checksum validation for module %s completed with status code %d."), const TChar*, const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleContentValidationResult(a0, a1, a2) LCMPullModuleContentValidationResult_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2)
#else
#define LCMPullModuleContentValidationResult(a0, a1, a2) LCMPullModuleContentValidationResult_Impl(0, 0, tcs(a0), tcs(a1), a2)
#endif
FILE_EVENT3(4200, LCMPullModuleContentValidationResult_Impl, LOG_INFO, PAL_T("Job %s : \nThe content validation for module %s completed with status code %d."), const TChar*, const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleDownloadLocation(a0, a1, a2) LCMPullModuleDownloadLocation_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullModuleDownloadLocation(a0, a1, a2) LCMPullModuleDownloadLocation_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4201, LCMPullModuleDownloadLocation_Impl, LOG_INFO, PAL_T("Job %s : \nThe modules %s were downloaded to the location %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleInstallLocation(a0, a1, a2) LCMPullModuleInstallLocation_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullModuleInstallLocation(a0, a1, a2) LCMPullModuleInstallLocation_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4208, LCMPullModuleInstallLocation_Impl, LOG_INFO, PAL_T("Job %s : \nThe modules %s were installed at the location %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define GetDscModuleWebDownloadManagerServerUrl(a0, a1, a2) GetDscModuleWebDownloadManagerServerUrl_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define GetDscModuleWebDownloadManagerServerUrl(a0, a1, a2) GetDscModuleWebDownloadManagerServerUrl_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4209, GetDscModuleWebDownloadManagerServerUrl_Impl, LOG_INFO, PAL_T("Job %s : \nAttempting to get the modules %s from pull server with Server Url %s using Web Download Manager."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define GetDscDocumentWebDownloadManagerServerUrl(a0, a1, a2) GetDscDocumentWebDownloadManagerServerUrl_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define GetDscDocumentWebDownloadManagerServerUrl(a0, a1, a2) GetDscDocumentWebDownloadManagerServerUrl_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4210, GetDscDocumentWebDownloadManagerServerUrl_Impl, LOG_INFO, PAL_T("Job %s : \nAttempting to get the configuration %s from pull server with Server Url %s using Web Download Manager."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullConfigurationChecksumValidationResult(a0, a1, a2) LCMPullConfigurationChecksumValidationResult_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2)
#else
#define LCMPullConfigurationChecksumValidationResult(a0, a1, a2) LCMPullConfigurationChecksumValidationResult_Impl(0, 0, tcs(a0), tcs(a1), a2)
#endif
FILE_EVENT3(4211, LCMPullConfigurationChecksumValidationResult_Impl, LOG_INFO, PAL_T("Job %s : \nThe checksum validation for configuration %s completed with status code %d."), const TChar*, const TChar*, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullConfigurationInvalidConfigurationFormat(a0, a1) LCMPullConfigurationInvalidConfigurationFormat_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullConfigurationInvalidConfigurationFormat(a0, a1) LCMPullConfigurationInvalidConfigurationFormat_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4212, LCMPullConfigurationInvalidConfigurationFormat_Impl, LOG_INFO, PAL_T("Job %s : \nThe configuration %s has an invalid format. The configuration name should be a UUID."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleInvalidVersionFormat(a0, a1, a2) LCMPullModuleInvalidVersionFormat_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullModuleInvalidVersionFormat(a0, a1, a2) LCMPullModuleInvalidVersionFormat_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4213, LCMPullModuleInvalidVersionFormat_Impl, LOG_INFO, PAL_T("Job %s : \nThe module %s has an invalid version format %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleSkippedAsModuleIsAvailable(a0, a1, a2, a3) LCMPullModuleSkippedAsModuleIsAvailable_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#else
#define LCMPullModuleSkippedAsModuleIsAvailable(a0, a1, a2, a3) LCMPullModuleSkippedAsModuleIsAvailable_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#endif
FILE_EVENT4(4214, LCMPullModuleSkippedAsModuleIsAvailable_Impl, LOG_INFO, PAL_T("Job %s : \nSkipping pulling module %s with version %s as it already exists in this location %s."), const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleDirectoryAlreadyExists(a0, a1, a2) LCMPullModuleDirectoryAlreadyExists_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullModuleDirectoryAlreadyExists(a0, a1, a2) LCMPullModuleDirectoryAlreadyExists_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4215, LCMPullModuleDirectoryAlreadyExists_Impl, LOG_INFO, PAL_T("Job %s : \nExtraction for module %s failed since module path %s already exists."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleSkippedAsAllModulesAreAvailable(a0, a1) LCMPullModuleSkippedAsAllModulesAreAvailable_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullModuleSkippedAsAllModulesAreAvailable(a0, a1) LCMPullModuleSkippedAsAllModulesAreAvailable_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4216, LCMPullModuleSkippedAsAllModulesAreAvailable_Impl, LOG_INFO, PAL_T("Job %s : \nSkipping pulling of modules since all modules specified in configuration %s are available."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetDocCertId(a0, a1, a2) WebDownloadManagerGetDocCertId_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetDocCertId(a0, a1, a2) WebDownloadManagerGetDocCertId_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4217, WebDownloadManagerGetDocCertId_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Get-DscDocument command using certificate id: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerCertProcessed(a0, a1, a2) WebDownloadManagerCertProcessed_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerCertProcessed(a0, a1, a2) WebDownloadManagerCertProcessed_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4224, WebDownloadManagerCertProcessed_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager processed certificate: %s %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetDocHttpClient(a0, a1, a2) WebDownloadManagerGetDocHttpClient_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetDocHttpClient(a0, a1, a2) WebDownloadManagerGetDocHttpClient_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4225, WebDownloadManagerGetDocHttpClient_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration s Get-DscDocument command, Http Client failed: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetDocGetUrl(a0, a1, a2) WebDownloadManagerGetDocGetUrl_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetDocGetUrl(a0, a1, a2) WebDownloadManagerGetDocGetUrl_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4226, WebDownloadManagerGetDocGetUrl_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Get-DscDocument command, GET Url: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetDocGetCall(a0, a1, a2) WebDownloadManagerGetDocGetCall_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetDocGetCall(a0, a1, a2) WebDownloadManagerGetDocGetCall_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4227, WebDownloadManagerGetDocGetCall_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Get-DscDocument command, GET call result: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetDocChecksumValidation(a0, a1, a2) WebDownloadManagerGetDocChecksumValidation_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetDocChecksumValidation(a0, a1, a2) WebDownloadManagerGetDocChecksumValidation_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4228, WebDownloadManagerGetDocChecksumValidation_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Get-DscDocument command, Checksum validation failed: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetDocFileSave(a0, a1, a2) WebDownloadManagerGetDocFileSave_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetDocFileSave(a0, a1, a2) WebDownloadManagerGetDocFileSave_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4229, WebDownloadManagerGetDocFileSave_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Get-DscDocument command, File save result: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetModCertId(a0, a1, a2) WebDownloadManagerGetModCertId_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetModCertId(a0, a1, a2) WebDownloadManagerGetModCertId_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4230, WebDownloadManagerGetModCertId_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager Get-DscModule command, module %s using certificate id: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetModHttpClient(a0, a1, a2) WebDownloadManagerGetModHttpClient_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetModHttpClient(a0, a1, a2) WebDownloadManagerGetModHttpClient_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4231, WebDownloadManagerGetModHttpClient_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager Get-DscModule command, module %s, Http Client failed: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetModGetUrl(a0, a1, a2) WebDownloadManagerGetModGetUrl_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetModGetUrl(a0, a1, a2) WebDownloadManagerGetModGetUrl_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4232, WebDownloadManagerGetModGetUrl_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager Get-DscModule command, module %s, GET Url: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetModGetCall(a0, a1, a2) WebDownloadManagerGetModGetCall_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetModGetCall(a0, a1, a2) WebDownloadManagerGetModGetCall_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4233, WebDownloadManagerGetModGetCall_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager Get-DscModule command, module %s, GET call result: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetModChecksumValidation(a0, a1, a2) WebDownloadManagerGetModChecksumValidation_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetModChecksumValidation(a0, a1, a2) WebDownloadManagerGetModChecksumValidation_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4240, WebDownloadManagerGetModChecksumValidation_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager Get-DscModule command, module %s, Checksum validation failed: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerGetModFileSave(a0, a1, a2) WebDownloadManagerGetModFileSave_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerGetModFileSave(a0, a1, a2) WebDownloadManagerGetModFileSave_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4241, WebDownloadManagerGetModFileSave_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager Get-DscModule command, module %s, File save result: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionServerUrl(a0, a1, a2) WebDownloadManagerDoActionServerUrl_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionServerUrl(a0, a1, a2) WebDownloadManagerDoActionServerUrl_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4242, WebDownloadManagerDoActionServerUrl_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Do-DscAction command with server url: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionCertId(a0, a1, a2) WebDownloadManagerDoActionCertId_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionCertId(a0, a1, a2) WebDownloadManagerDoActionCertId_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4243, WebDownloadManagerDoActionCertId_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Do-DscAction command using certificate id: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionHttpClient(a0, a1, a2) WebDownloadManagerDoActionHttpClient_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionHttpClient(a0, a1, a2) WebDownloadManagerDoActionHttpClient_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4244, WebDownloadManagerDoActionHttpClient_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Do-DscAction command, Http Client failed: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionGetUrl(a0, a1, a2) WebDownloadManagerDoActionGetUrl_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionGetUrl(a0, a1, a2) WebDownloadManagerDoActionGetUrl_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4245, WebDownloadManagerDoActionGetUrl_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Do-DscAction command, GET Url: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionGetCall(a0, a1, a2) WebDownloadManagerDoActionGetCall_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionGetCall(a0, a1, a2) WebDownloadManagerDoActionGetCall_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4246, WebDownloadManagerDoActionGetCall_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for configuration %s Do-DscAction command, GET call result: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullModuleDirectoryOverwrite(a0, a1, a2) LCMPullModuleDirectoryOverwrite_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMPullModuleDirectoryOverwrite(a0, a1, a2) LCMPullModuleDirectoryOverwrite_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4247, LCMPullModuleDirectoryOverwrite_Impl, LOG_INFO, PAL_T("Job %s : \nModule %s is over written with the downloaded module %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMPullUnsecureConnectionNotAllowed(a0, a1) LCMPullUnsecureConnectionNotAllowed_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMPullUnsecureConnectionNotAllowed(a0, a1) LCMPullUnsecureConnectionNotAllowed_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4248, LCMPullUnsecureConnectionNotAllowed_Impl, LOG_INFO, PAL_T("Job %s : \nCannot download configuration from %s. Downloading over HTTP is not allowed."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageFromEngineConsistency(a0, a1, a2) MessageFromEngineConsistency_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessageFromEngineConsistency(a0, a1, a2) MessageFromEngineConsistency_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4249, MessageFromEngineConsistency_Impl, LOG_WARNING, PAL_T("Job %s : \nFrom %s, message is %s"), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define ExceptionMessage(a0, a1, a2, a3) ExceptionMessage_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), a2, tcs(a3))
#else
#define ExceptionMessage(a0, a1, a2, a3) ExceptionMessage_Impl(0, 0, tcs(a0), tcs(a1), a2, tcs(a3))
#endif
FILE_EVENT4(4250, ExceptionMessage_Impl, LOG_INFO, PAL_T("Job %1 : \nMessage %2 \nHResult %3 \nStackTrack %4"), const TChar*, const TChar*, MI_Uint32, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMRegisterAgentAttempt(a0, a1, a2, a3) LCMRegisterAgentAttempt_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#else
#define LCMRegisterAgentAttempt(a0, a1, a2, a3) LCMRegisterAgentAttempt_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#endif
FILE_EVENT4(4401, LCMRegisterAgentAttempt_Impl, LOG_INFO, PAL_T("Job %1 : \nAttempting to register the Dsc agent with AgentId %2 with the server %3 using Download Manager %4."), const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMRegisterAgentSuccess(a0, a1, a2, a3) LCMRegisterAgentSuccess_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#else
#define LCMRegisterAgentSuccess(a0, a1, a2, a3) LCMRegisterAgentSuccess_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2), tcs(a3))
#endif
FILE_EVENT4(4402, LCMRegisterAgentSuccess_Impl, LOG_INFO, PAL_T("Job %1 : \nSuccessfully registered the Dsc agent with AgentId %2 with the server %3 using Download Manager %4."), const TChar*, const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define RegisterAgentUrl(a0, a1, a2) RegisterAgentUrl_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define RegisterAgentUrl(a0, a1, a2) RegisterAgentUrl_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4403, RegisterAgentUrl_Impl, LOG_INFO, PAL_T("Job %1 : \nRegistering Dsc Agent with Agent Id %2. Register-DscAgent command, PUT Url: %3."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define RegisterAgentHttpClient(a0, a1, a2) RegisterAgentHttpClient_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define RegisterAgentHttpClient(a0, a1, a2) RegisterAgentHttpClient_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4404, RegisterAgentHttpClient_Impl, LOG_ERR, PAL_T("Job %1 : \nHttp Client %2 failed to register Dsc Agent: %3."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define RegisterAgentPostCall(a0, a1) RegisterAgentPostCall_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define RegisterAgentPostCall(a0, a1) RegisterAgentPostCall_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4405, RegisterAgentPostCall_Impl, LOG_INFO, PAL_T("Job %1 : \nRegister-DscAgent command for AgentId %2 succeeded."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define RegisterAgentCertId(a0, a1, a2) RegisterAgentCertId_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define RegisterAgentCertId(a0, a1, a2) RegisterAgentCertId_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4406, RegisterAgentCertId_Impl, LOG_INFO, PAL_T("Job %1 : \nRegister-DscAgent command for AgentId %2 using certificate id: %3."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMAgentNotRegistered(a0) LCMAgentNotRegistered_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMAgentNotRegistered(a0) LCMAgentNotRegistered_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4407, LCMAgentNotRegistered_Impl, LOG_INFO, PAL_T("Job %1 : \nThe Dsc Agent has not been registered. Registration will be attempted."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WriteAgentIdToRegistryFailure(a0, a1) WriteAgentIdToRegistryFailure_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define WriteAgentIdToRegistryFailure(a0, a1) WriteAgentIdToRegistryFailure_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4408, WriteAgentIdToRegistryFailure_Impl, LOG_ERR, PAL_T("Job %1 : \nUnable to write AgentId %2 to registry."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMServerURLRegistered(a0, a1, a2) LCMServerURLRegistered_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMServerURLRegistered(a0, a1, a2) LCMServerURLRegistered_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4409, LCMServerURLRegistered_Impl, LOG_INFO, PAL_T("Job %1 : \nThe Dsc Agent with AgentId %2 has already been registered for the Server URL %3. Registration will be skipped for this Server URL."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMProtocolVersion1InUse(a0) LCMProtocolVersion1InUse_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define LCMProtocolVersion1InUse(a0) LCMProtocolVersion1InUse_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4410, LCMProtocolVersion1InUse_Impl, LOG_INFO, PAL_T("Job %s : \nUsing Version 1 protocol of Dsc PULL."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMAgentAttemptRegistration(a0, a1, a2) LCMAgentAttemptRegistration_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define LCMAgentAttemptRegistration(a0, a1, a2) LCMAgentAttemptRegistration_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4411, LCMAgentAttemptRegistration_Impl, LOG_INFO, PAL_T("Job %1 : \nAttempt to register the Dsc Agent AgentId %2 with Server URL %3 since RegistrationKey was specified."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMServerRegCertGenFailed(a0, a1) LCMServerRegCertGenFailed_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMServerRegCertGenFailed(a0, a1) LCMServerRegCertGenFailed_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4331, LCMServerRegCertGenFailed_Impl, LOG_INFO, PAL_T("Job %1 : \nThe Dsc Agent with AgentId %2 failed to create a self-signed certificate."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMRunAsUser(a0, a1) LCMRunAsUser_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMRunAsUser(a0, a1) LCMRunAsUser_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4321, LCMRunAsUser_Impl, LOG_INFO, PAL_T("Job %1 : \n PsDscRunAsCredential has been specified. The user name is %2."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMImpersonationSuccessful(a0, a1) LCMImpersonationSuccessful_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMImpersonationSuccessful(a0, a1) LCMImpersonationSuccessful_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4322, LCMImpersonationSuccessful_Impl, LOG_INFO, PAL_T("Job %1 : \n Impersonation successful. Thread is running under the context of %2."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define LCMImpersonationReverted(a0, a1) LCMImpersonationReverted_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define LCMImpersonationReverted(a0, a1) LCMImpersonationReverted_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4323, LCMImpersonationReverted_Impl, LOG_INFO, PAL_T("Job %1 : \n Impersonation reverted. Thread is running under the context of %2."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionServerUrlVersion2(a0, a1, a2) WebDownloadManagerDoActionServerUrlVersion2_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionServerUrlVersion2(a0, a1, a2) WebDownloadManagerDoActionServerUrlVersion2_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4324, WebDownloadManagerDoActionServerUrlVersion2_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for AgentId %s Do-DscAction command with server url: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionCertIdVersion2(a0, a1, a2) WebDownloadManagerDoActionCertIdVersion2_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionCertIdVersion2(a0, a1, a2) WebDownloadManagerDoActionCertIdVersion2_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4325, WebDownloadManagerDoActionCertIdVersion2_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for AgentId %s Do-DscAction command using certificate id: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionHttpClientVersion2(a0, a1, a2) WebDownloadManagerDoActionHttpClientVersion2_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionHttpClientVersion2(a0, a1, a2) WebDownloadManagerDoActionHttpClientVersion2_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4326, WebDownloadManagerDoActionHttpClientVersion2_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for AgentId %s Do-DscAction command, Http Client failed: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionGetUrlVersion2(a0, a1, a2) WebDownloadManagerDoActionGetUrlVersion2_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionGetUrlVersion2(a0, a1, a2) WebDownloadManagerDoActionGetUrlVersion2_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4327, WebDownloadManagerDoActionGetUrlVersion2_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for AgentId %s Do-DscAction command, GET Url: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define WebDownloadManagerDoActionGetCallVersion2(a0, a1, a2) WebDownloadManagerDoActionGetCallVersion2_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define WebDownloadManagerDoActionGetCallVersion2(a0, a1, a2) WebDownloadManagerDoActionGetCallVersion2_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4328, WebDownloadManagerDoActionGetCallVersion2_Impl, LOG_INFO, PAL_T("Job %s : \nWebDownloadManager for AgentId %s Do-DscAction command, GET call result: %s."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDscOperationAlreadyQueued(a0, a1) MessageDscOperationAlreadyQueued_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageDscOperationAlreadyQueued(a0, a1) MessageDscOperationAlreadyQueued_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4329, MessageDscOperationAlreadyQueued_Impl, LOG_WARNING, PAL_T("Job %s : DSC Operation %s is already queued, ignoring the request."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDscOperationAlreadyRunning(a0, a1) MessageDscOperationAlreadyRunning_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageDscOperationAlreadyRunning(a0, a1) MessageDscOperationAlreadyRunning_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4330, MessageDscOperationAlreadyRunning_Impl, LOG_WARNING, PAL_T("Job %s : DSC Operation %s is already running, ignoring the request."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageStartingDscOperation(a0, a1) MessageStartingDscOperation_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define MessageStartingDscOperation(a0, a1) MessageStartingDscOperation_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(4331, MessageStartingDscOperation_Impl, LOG_WARNING, PAL_T("Job %s : Starting %s DSC operation."), const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDscOperationCompleted(a0, a1, a2) MessageDscOperationCompleted_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define MessageDscOperationCompleted(a0, a1, a2) MessageDscOperationCompleted_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4332, MessageDscOperationCompleted_Impl, LOG_WARNING, PAL_T("Job %s : %s DSC operation completed in %s seconds."), const TChar*, const TChar*, const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDscEngineProviderLoaded(a0) MessageDscEngineProviderLoaded_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageDscEngineProviderLoaded(a0) MessageDscEngineProviderLoaded_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4333, MessageDscEngineProviderLoaded_Impl,LOG_INFO, PAL_T("Job %s : \nLoading DSC Engine Provider"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDscEngineProviderUnLoaded(a0) MessageDscEngineProviderUnLoaded_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageDscEngineProviderUnLoaded(a0) MessageDscEngineProviderUnLoaded_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4334, MessageDscEngineProviderUnLoaded_Impl, LOG_INFO, PAL_T("Job %s : \nUnLoading DSC Engine Provider"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDscEngineRegisteringSignalHandler(a0) MessageDscEngineRegisteringSignalHandler_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageDscEngineRegisteringSignalHandler(a0) MessageDscEngineRegisteringSignalHandler_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4335, MessageDscEngineRegisteringSignalHandler_Impl, LOG_DEBUG, PAL_T("Job %s : \nRegistered Process Signal Handler for SIGCHLD Event"), const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define MessageDscEngineSignalHandlerWaitingForPorcess(a0) MessageDscEngineSignalHandlerWaitingForPorcess_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define MessageDscEngineSignalHandlerWaitingForPorcess(a0) MessageDscEngineSignalHandlerWaitingForPorcess_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4336, MessageDscEngineSignalHandlerWaitingForPorcess_Impl, LOG_DEBUG, PAL_T("Job %s : \nDsc Engine waiting for Child Process to Terminate"), const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define GettingTheClassDeclFailed(a0) GettingTheClassDeclFailed_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define GettingTheClassDeclFailed(a0) GettingTheClassDeclFailed_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4614, GettingTheClassDeclFailed_Impl, LOG_ERR, PAL_T("Getting the MI_ClassDecl for class name &apos;%s&apos; Failed."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define GettingTheMethodDeclSucceeded(a0) GettingTheMethodDeclSucceeded_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define GettingTheMethodDeclSucceeded(a0) GettingTheMethodDeclSucceeded_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4615, GettingTheMethodDeclSucceeded_Impl, LOG_INFO, PAL_T("Getting the MI_MethodDecl for method name &apos;%s&apos; succeeded."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define GettingTheMethodDeclFailed(a0) GettingTheMethodDeclFailed_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define GettingTheMethodDeclFailed(a0) GettingTheMethodDeclFailed_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4616, GettingTheMethodDeclFailed_Impl, LOG_ERR, PAL_T("Getting the MI_MethodDecl for method name &apos;%s&apos; failed."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define GettingTheHostNameFailed(a0) GettingTheHostNameFailed_Impl(__FILE__, __LINE__, a0)
#else
#define GettingTheHostNameFailed(a0) GettingTheHostNameFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(4617, GettingTheHostNameFailed_Impl, LOG_ERR, PAL_T("Getting the hostname failed with error code &apos;%s&apos;."), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define UnSupportedHostMethodCalled(a0) UnSupportedHostMethodCalled_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define UnSupportedHostMethodCalled(a0) UnSupportedHostMethodCalled_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(4618, UnSupportedHostMethodCalled_Impl, LOG_ERR, PAL_T("Unsupported host method &apos;%s&apos; called."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define InvokingNativeResourceMethod(a0, a1, a2) InvokingNativeResourceMethod_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define InvokingNativeResourceMethod(a0, a1, a2) InvokingNativeResourceMethod_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(4619, InvokingNativeResourceMethod_Impl, LOG_INFO, PAL_T("Invoking resource method &apos;%s&apos; with class name &apos;%s&apos; from prodvider path  &apos;%s&apos;."), const TChar*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define CreateHostContextSucceeded() CreateHostContextSucceeded_Impl(__FILE__, __LINE__)
#else
#define CreateHostContextSucceeded() CreateHostContextSucceeded_Impl(0, 0)
#endif
FILE_EVENT0(4620, CreateHostContextSucceeded_Impl, LOG_INFO, PAL_T("Creating host context succeeded."))
#if defined(CONFIG_ENABLE_DEBUG)
#define MIModuleVersionMisMatch(a0, a1) MIModuleVersionMisMatch_Impl(__FILE__, __LINE__, a0, a1)
#else
#define MIModuleVersionMisMatch(a0, a1) MIModuleVersionMisMatch_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(4621, MIModuleVersionMisMatch_Impl, LOG_ERR, PAL_T("Version mismatch between the current MI_Module version (&apos;%s&apos;) and the provider module version (&apos;%s&apos;)."), MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define CreateHostContextFailed() CreateHostContextFailed_Impl(__FILE__, __LINE__)
#else
#define CreateHostContextFailed() CreateHostContextFailed_Impl(0, 0)
#endif
FILE_EVENT0(4622, CreateHostContextFailed_Impl, LOG_ERR, PAL_T("Creating host context failed."))

#if defined(CONFIG_ENABLE_DEBUG)
#define LoadingDLLSucceeded(a0) LoadingDLLSucceeded_Impl(__FILE__, __LINE__, a0)
#else
#define LoadingDLLSucceeded(a0) LoadingDLLSucceeded_Impl(0, 0, a0)
#endif
FILE_EVENT1(4623, LoadingDLLSucceeded_Impl, LOG_INFO, PAL_T("Loading the native provider .so from &apos;%s&apos; succeeded."), const TChar*)

#if defined(CONFIG_ENABLE_DEBUG)
#define GettingTheSchemaSucceeded(a0) GettingTheSchemaSucceeded_Impl(__FILE__, __LINE__, a0)
#else
#define GettingTheSchemaSucceeded(a0) GettingTheSchemaSucceeded_Impl(0, 0, a0)
#endif
FILE_EVENT1(4624, GettingTheSchemaSucceeded_Impl, LOG_INFO, PAL_T("Getting the schema class for &apos;%s&apos; succeeded."), const TChar*)


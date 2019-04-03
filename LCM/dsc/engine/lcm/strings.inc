/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_MEMORY_ERROR, ID_ENGINEHELPER_MEMORY_ERROR, "Memory allocation failed.")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_FILESIZE_ERROR, ID_ENGINEHELPER_FILESIZE_ERROR, "MOF file size exceeded max size limit.")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_OPENFILE_ERROR, ID_ENGINEHELPER_OPENFILE_ERROR, "Error opening file.")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_READFILE_ERROR, ID_ENGINEHELPER_READFILE_ERROR, "Reading file content failed")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_GETFILESIZE_ERROR, ID_ENGINEHELPER_GETFILESIZE_ERROR, "Error getting file size.")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_CAT_ERROR, ID_ENGINEHELPER_CAT_ERROR, "StringCchCatW failed.")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_CREATEPROCESS_ERROR, ID_ENGINEHELPER_CREATEPROCESS_ERROR, "CreateProcess failed for mofcomp.exe")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_CHECKSUMGEN_ERROR, ID_ENGINEHELPER_CHECKSUMGEN_ERROR, "Unable to generate checksum for current configuration.")
    INTERNAL_Intlstr_Define2( ID_ENGINEHELPER_REGISTERCIMPROV_ERROR ,
                 ID_ENGINEHELPER_REGISTERCIMPROV_ERROR ,
                 _In_z_ const PAL_Char*, firstString,
                 _In_z_ const PAL_Char*, secondString,
                 "PowerShell Desired State Configuration failed to register MOF file" Intlstr_tstr(1) " using Mofcomp.exe during discovery of "  Intlstr_tstr(2) " resource . Check the MOF file and try again.")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_FAILEDTO_DESIREDSTATE, ID_ENGINEHELPER_FAILEDTO_DESIREDSTATE, "LCM failed to move one or more resources to their desired state.")
    INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_PSINFRA_LOADERROR, ID_ENGINEHELPER_PSINFRA_LOADERROR, "LCM failed to load PowerShell module loader.")
	INTERNAL_Intlstr_Define0( ID_ENGINEHELPER_MANUAL_FAILED, ID_ENGINEHELPER_MANUAL_FAILED, "LCM failed to start desired state configuration manually.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_ETWREGISTREATION_FAILED ,ID_LCMHELPER_ETWREGISTREATION_FAILED ,"The registration of Event Tracing for Windows (ETW) failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_INIT_AGENTCRITSEC_FAILED , ID_LCMHELPER_INIT_AGENTCRITSEC_FAILED ,"Could not initialize the agent critical section.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_INIT_FILECRITSEC_FAILED , ID_LCMHELPER_INIT_FILECRITSEC_FAILED ,"Could not initialize the file critical section.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_INIT_EXAPANDENV_FAILED , ID_LCMHELPER_INIT_EXAPANDENV_FAILED ,"Could not expand the environment path.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_ETWUNREGISTREATION_FAILED , ID_LCMHELPER_ETWUNREGISTREATION_FAILED ,"ETW unregistration failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_VALIDATE_CONFGDIR_FAILED , ID_LCMHELPER_VALIDATE_CONFGDIR_FAILED ,"The validation of the Configuration directory did not succeed. Ensure that the directory exists and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_DEL_GETFILEBEFORE_FAILED , ID_LCMHELPER_DEL_GETFILEBEFORE_FAILED ,"Could not delete the old file Get.mof before the get operation.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SAVE_GETCONF_FAILED , ID_LCMHELPER_SAVE_GETCONF_FAILED ,"Could not save the Get.mof file. Delete Get.mof in the Configuration directory and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_LOAD_GETFILE_FAILED , ID_LCMHELPER_LOAD_GETFILE_FAILED ,"Could not load the instance document from the specified location. Ensure that the instance document exists and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_GET_CONF_FAILED , ID_LCMHELPER_GET_CONF_FAILED ,"GetConfiguration did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_DEL_GETFILEAFTER_FAILED , ID_LCMHELPER_DEL_GETFILEAFTER_FAILED ,"Could not delete the file Get.mof after the get operation. Check the properties of the location of the file and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CREATE_CONFDIR_FAILED , ID_LCMHELPER_CREATE_CONFDIR_FAILED ,"The creation of the configuration directory failed. Verify the directory permissions and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_MEMORY_ERROR , ID_LCMHELPER_MEMORY_ERROR ,"Memory allocation failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_PRINTF_ERROR , ID_LCMHELPER_PRINTF_ERROR ,"Stprintf failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_OLDCONFPENDING_ERROR , ID_LCMHELPER_OLDCONFPENDING_ERROR ,"An old configuration is still pending. Please wait for the pending configuration to finish. If the problem persists, execute Start-DSCConfiguration command with -Force parameter.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SAVE_PENDING_ERROR , ID_LCMHELPER_SAVE_PENDING_ERROR ,"Could not save the pending configuration MOF file. Check the properties of the destination location and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_LOAD_PENDING_ERROR , ID_LCMHELPER_LOAD_PENDING_ERROR ,"Loading the instance document from the pending location did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SENDCONFIGAPPLY_ERROR , ID_LCMHELPER_SENDCONFIGAPPLY_ERROR ,"The SendConfigurationApply function did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_DEL_PENDINGFILEAFTER_FAILED , ID_LCMHELPER_DEL_PENDINGFILEAFTER_FAILED ,"Deleting the pending file after moving it did not succeed.")
    INTERNAL_Intlstr_Define2( ID_LCMHELPER_COPY_FAILED , ID_LCMHELPER_COPY_FAILED ,
                 _In_z_ const PAL_Char*, firstString,
                 _In_z_ const PAL_Char*, secondString,
                 "File copy from '" Intlstr_tstr(1) "' to '" Intlstr_tstr(2) "' failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CONVERT_SECDESC_FAILED , ID_LCMHELPER_CONVERT_SECDESC_FAILED ,"Unable to create configuration MOF file because converting security descriptor for administrators failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CREATE_CONF_FAILED , ID_LCMHELPER_CREATE_CONF_FAILED ,"Could not create the configuration MOF file. Check the Analytic event log to investigate why the MOF file could not be created at this path.")
    INTERNAL_Intlstr_Define0( ID_LCM_CREATE_PULL_RUN_LOG_FILE , ID_LCM_CREATE_PULL_RUN_LOG_FILE ,"Could not create the pull run log file. Check the Analytic event log to investigate why the file could not be created at this path.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_META_MOF_FAILED , ID_LCMHELPER_META_MOF_FAILED ,"Could not construct MSFT_DSCMetaConfiguration using Mof_Instance_New.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_MODLOADNULL_FAILED , ID_LCMHELPER_MODLOADNULL_FAILED ,"ModuleLoader is null.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_METASCHEMA_LOADNULL_FAILED , ID_LCMHELPER_METASCHEMA_LOADNULL_FAILED ,"Loading the Local Configuration Manager settings schema did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_METASCHEMA_NAMEMISMATCH_FAILED , ID_LCMHELPER_METASCHEMA_NAMEMISMATCH_FAILED ,"Metaschema loading returned null.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_METASCHEMA_CREATESERIALIZE_FAILED , ID_LCMHELPER_METASCHEMA_CREATESERIALIZE_FAILED ,"Could not create the serializer.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_METASCHEMA_SERIALIZE_FAILED , ID_LCMHELPER_METASCHEMA_SERIALIZE_FAILED ,"Could not serialize the Local Configuration Manager settings schema.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_METASCHEMA_DELETE_FAILED , ID_LCMHELPER_METASCHEMA_DELETE_FAILED ,"Could not delete the Local Configuration Manager settings file.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_DESERIALIZER_CREATE_FAILED , ID_LCMHELPER_DESERIALIZER_CREATE_FAILED ,"Creating deserializer failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_METASCHEMA_CLONE_FAILED , ID_LCMHELPER_METASCHEMA_CLONE_FAILED ,"Cloning the typed Local Configuration Manager settings did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_TASK_CREATEPARAM_FAILED , ID_LCMHELPER_TASK_CREATEPARAM_FAILED ,"Could not create the parameters required for invoking the Task API.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_TASK_ADDPARAM_FAILED , ID_LCMHELPER_TASK_ADDPARAM_FAILED ,"Adding task path parameters to call the task API did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_TASK_CREATESESSION_FAILED , ID_LCMHELPER_TASK_CREATESESSION_FAILED ,"Creating a session to call the task API did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_EXPANDENV_FAILED , ID_LCMHELPER_EXPANDENV_FAILED ,"The ExpandEnvironmentStrings function did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_THREADIMPERSONATION_FAILED , ID_LCMHELPER_THREADIMPERSONATION_FAILED ,"Getting the current thread impersonation token did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_REVERTSELF_FAILED , ID_LCMHELPER_REVERTSELF_FAILED ,"Could not revert to self.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_RESUMEIMPERSONATION_FAILED , ID_LCMHELPER_RESUMEIMPERSONATION_FAILED ,"Could not resume impersonation.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CONSTRUCTGET_FAILED , ID_LCMHELPER_CONSTRUCTGET_FAILED ,"Could not construct the output object for the GetConfiguration function.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_WRITEGET_FAILED , ID_LCMHELPER_WRITEGET_FAILED ,"Writing the output parameter for GetConfiguration did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SETGET_FAILED , ID_LCMHELPER_SETGET_FAILED ,"ApplyConfiguration could not get the current Local Configuration Manager settings for the system.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_POSTGET_FAILED , ID_LCMHELPER_POSTGET_FAILED ,"Posting output for GetConfiguration did not succeed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CONSTRUCTAPPLY_FAILED , ID_LCMHELPER_CONSTRUCTAPPLY_FAILED ,"Could not construct the output object for the ApplyConfiguration function. Check the configuration and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SETAPPLY_FAILED , ID_LCMHELPER_SETAPPLY_FAILED ,"The Set function in ApplyConfiguration returned an error.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_POSTAPPLY_FAILED , ID_LCMHELPER_POSTAPPLY_FAILED ,"Could not post the output in the ApplyConfiguration function.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_REBOOT , ID_LCM_WRITEMESSAGE_REBOOT ,"A reboot is scheduled to progress further. Configuration will be continued after the reboot.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_REBOOTMANUALLY , ID_LCM_WRITEMESSAGE_REBOOTMANUALLY ,"A reboot is required to progress further. Please reboot the system.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_STARTCONSISTENCY , ID_LCM_WRITEMESSAGE_STARTCONSISTENCY ,"Starting consistency engine.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_ENDCONSISTENCY , ID_LCM_WRITEMESSAGE_ENDCONSISTENCY ,"Consistency check completed.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_CONSISTENCY_PENDINGEXIST , ID_LCM_WRITEMESSAGE_CONSISTENCY_PENDINGEXIST ,"A pending configuration exists. DSC will process a set request on the pending configuration.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_CONSISTENCY_CURRENTEXIST , ID_LCM_WRITEMESSAGE_CONSISTENCY_CURRENTEXIST ,"Checking consistency for current configuration.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_SAVETOPENDING , ID_LCM_WRITEMESSAGE_SAVETOPENDING ,"Document successfully saved to pending state.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_NORESOURCESPECIFIED , ID_LCMHELPER_NORESOURCESPECIFIED ,"The instance document does not specify any resource. Add at least one resource to the document and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SAVE_METATMP_ERROR , ID_LCMHELPER_SAVE_METATMP_ERROR ,"Could not save the temporary Local Configuration Manager settings file. Check the properties of the destination location and try again.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_DEL_METATMPFILEAFTER_FAILED , ID_LCMHELPER_DEL_METATMPFILEAFTER_FAILED ,"Could not delete the temporary metadata file.")
    INTERNAL_Intlstr_Define0( ID_LCM_PULL_GETACTION_NORESULTSTATUS , ID_LCM_PULL_GETACTION_NORESULTSTATUS ,"Executing Get-Action returned success but didn't return any status.")   
    INTERNAL_Intlstr_Define0( ID_LCM_PULL_GETACTION_UNEXPECTEDRESULTSTATUS , ID_LCM_PULL_GETACTION_UNEXPECTEDRESULTSTATUS ,"Get-DSCAction returned success but did not return the expected status.")  
    INTERNAL_Intlstr_Define0( ID_LCM_PULL_GETCONF_UNEXPECTEDRESULTSTATUS , ID_LCM_PULL_GETCONF_UNEXPECTEDRESULTSTATUS ,"GetConfiguration ran successfully, but did not return the expected status.") 
    INTERNAL_Intlstr_Define0( ID_LCM_PULL_GETCONF_NORESULTSTATUS , ID_LCM_PULL_GETCONF_NORESULTSTATUS ,"GetConfiguration ran successfully, but did not return any status.")
    INTERNAL_Intlstr_Define0( ID_LCM_CONF_DATAEXIST , ID_LCM_CONF_DATAEXIST ,"The configurationData parameter is reserved for future use. The current configuration is used by default.")
    INTERNAL_Intlstr_Define0( ID_LCM_CONF_NUMBEREXIST , ID_LCM_CONF_NUMBEREXIST ,"The ConfigurationNumber parameter is reserved for future use. The previous configuration is used by default.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CONSTRUCTTEST_FAILED , ID_LCMHELPER_CONSTRUCTTEST_FAILED ,"Could not construct the test configuration output object.")   
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SETTEST_FAILED , ID_LCMHELPER_SETTEST_FAILED ,"Could not set the resource ID in TestConfiguration. Try running the operation again.")    
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_POSTTEST_FAILED , ID_LCMHELPER_POSTTEST_FAILED ,"Could not post the output for the test configuration.")  
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CURRENT_NOTFOUND , ID_LCMHELPER_CURRENT_NOTFOUND ,"Current configuration does not exist. Execute Start-DscConfiguration command with -Path parameter to specify a configuration file and create a current configuration first.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_PREVIOUS_NOTFOUND , ID_LCMHELPER_PREVIOUS_NOTFOUND ,"A previous configuration does not exist. DSC can rollback only when there is a previous configuration.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_ENDTESTPROCESSING_TRUE , ID_LCM_WRITEMESSAGE_ENDTESTPROCESSING_TRUE ,"Completed processing test operation. The operation returned True.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_ENDTESTPROCESSING_FALSE , ID_LCM_WRITEMESSAGE_ENDTESTPROCESSING_FALSE ,"Completed processing test operation. The operation returned False.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_ENDTESTPROCESSING_FAIL , ID_LCM_WRITEMESSAGE_ENDTESTPROCESSING_FAIL ,"Completed processing test operation. The operation failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_METAMOFCORRUPTED , ID_LCMHELPER_METAMOFCORRUPTED ,"Falling back to system defaults because the meta configuration mof has either been corrupted or an invalid mof property has been set.")
    INTERNAL_Intlstr_Define1(ID_LCMHELPER_OVERWROTE_USER_SPECIFIED_REFRESH_FREQUENCY ,
                     ID_LCMHELPER_OVERWROTE_USER_SPECIFIED_REFRESH_FREQUENCY ,
                     _In_z_ const PAL_Char*, firstString,
                     "The specified RefreshFrequencyMins was over-written to " Intlstr_tstr(1) " since it was outside the range of acceptable values (15-44640)")
	INTERNAL_Intlstr_Define1(ID_LCMHELPER_OVERWROTE_USER_SPECIFIED_CONFMODE_FREQUENCY ,
                     ID_LCMHELPER_OVERWROTE_USER_SPECIFIED_CONFMODE_FREQUENCY ,
                     _In_z_ const PAL_Char*, firstString,
                     "The specified ConfigurationModeFrequencyMins was over-written to " Intlstr_tstr(1) "")  
    INTERNAL_Intlstr_Define1( ID_LCMHELPER_DEL_FAILED ,
                     ID_LCMHELPER_DEL_FAILED ,
                     _In_z_ const PAL_Char*, firstString,
                     "Deletion of file" Intlstr_tstr(1) "failed.")    
    INTERNAL_Intlstr_Define4( ID_LCM_TIMEMESSAGE ,
                     ID_LCM_TIMEMESSAGE ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     _In_z_ const PAL_Char*, thirdString,
                     _In_z_ const PAL_Char*, fourthString,
                     "[" Intlstr_tstr(1) "]: LCM:  [ " Intlstr_tstrfull(2, "-", 16) "]   " Intlstr_tstr(3) " in  "  Intlstr_tstr(4) " seconds.")   
    INTERNAL_Intlstr_Define0( ID_LCM_FORCE_PARAMETER_INVALIDVALUE , ID_LCM_FORCE_PARAMETER_INVALIDVALUE ,"The Force parameter accepts only boolean values True or False.")
    INTERNAL_Intlstr_Define0( ID_LCM_FAILED_TO_GET_METACONFIGURATION , ID_LCM_FAILED_TO_GET_METACONFIGURATION ,"Could not retrieve the Local Configuration Manager settings.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SHUTDOWN_FAILED , ID_LCMHELPER_SHUTDOWN_FAILED ,"Machine reboot failed. Please reboot it manually to finish processing the request.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_SHUTDOWN_MESSAGE , ID_LCMHELPER_SHUTDOWN_MESSAGE ,"DSC is restarting the computer.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_GETTEMPPATH_ERROR , ID_LCMHELPER_GETTEMPPATH_ERROR ,"GetTempPath failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_GETTEMPFILENAME_ERROR , ID_LCMHELPER_GETTEMPFILENAME_ERROR ,"GetTempFileName failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CREATEFILE_ERROR , ID_LCMHELPER_CREATEFILE_ERROR ,"CreateFile failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_WRITEFILE_ERROR , ID_LCMHELPER_WRITEFILE_ERROR ,"WriteFile failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_CLOSEHANDLE_ERROR , ID_LCMHELPER_CLOSEHANDLE_ERROR ,"CloseHandle failed.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_STRLEN_ERROR , ID_LCMHELPER_STRLEN_ERROR ,"Error attempting to get the length of a string.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_UNEXPECTED_TASKNAME_ERROR , ID_LCMHELPER_UNEXPECTED_TASKNAME_ERROR ,"Unexpected task name received.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_INVALID_INTERVAL_ERROR , ID_LCMHELPER_INVALID_INTERVAL_ERROR ,"An interval was specified outside of the acceptable range (maximum of 31 days).")
    
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_DELETEFILE_ERROR , ID_LCMHELPER_DELETEFILE_ERROR ,"An error was encountered while deleting the temporary file.")
    INTERNAL_Intlstr_Define0( ID_LCM_PUSH_REQUESTED_ON_PULL_WO_FORCE , ID_LCM_PUSH_REQUESTED_ON_PULL_WO_FORCE ,"A PUSH operation was requested without -Force while configured for PULL processing.")
    INTERNAL_Intlstr_Define3( ID_LCM_MULTIPLE_METHOD_REQUEST ,
                     ID_LCM_MULTIPLE_METHOD_REQUEST ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     _In_z_ const PAL_Char*, thirdString,
                     "Cannot invoke the" Intlstr_tstr(1) "method. The " Intlstr_tstr(2) " method is in progress and must return before " Intlstr_tstr(3) " can be invoked.")
    INTERNAL_Intlstr_Define0( ID_LCM_CLEAR_PROVIDER_CACHE ,ID_LCM_CLEAR_PROVIDER_CACHE ,"Clear the cache of built-in DSC resources.")
    INTERNAL_Intlstr_Define0( ID_LCM_CLEAR_PROVIDER_CACHE_FAILED , ID_LCM_CLEAR_PROVIDER_CACHE_FAILED ,"Failed to clear the cache of built-in DSC resources.")
    INTERNAL_Intlstr_Define0( ID_LCM_CONFIRM_NOT_SUPPORTED , ID_LCM_CONFIRM_NOT_SUPPORTED ,"The Confirm option is not supported in Restore-DscConfiguration. Please try again without using -Confirm.")
    INTERNAL_Intlstr_Define0( ID_CONSISTENCY_TASK_FAILURE , ID_CONSISTENCY_TASK_FAILURE ,"Update consistency task failed.")  
    INTERNAL_Intlstr_Define4( ID_OUTPUT_FORMATPROVIDER ,
                     ID_OUTPUT_FORMATPROVIDER ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     _In_z_ const PAL_Char*, thirdString,
                     _In_z_ const PAL_Char*, fourthString,
                     "[" Intlstr_tstr(1) "]:         " Intlstr_tstrfull(2, "-", 16) "   [" Intlstr_tstr(3) "] "  Intlstr_tstr(4))                   
    INTERNAL_Intlstr_Define4( ID_OUTPUT_FORMATOUTPUT ,
                     ID_OUTPUT_FORMATOUTPUT ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     _In_z_ const PAL_Char*, thirdString,
                     _In_z_ const PAL_Char*, fourthString,
                     "[" Intlstr_tstr(1) "]: LCM:  [ " Intlstr_tstrfull(2, "-", 16) "]  [" Intlstr_tstr(3) "] "  Intlstr_tstr(4))
     
    INTERNAL_Intlstr_Define4( ID_OUTPUT_FORMATNORESOURCE ,
                     ID_OUTPUT_FORMATNORESOURCE ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     _In_z_ const PAL_Char*, thirdString,
                     _In_z_ const PAL_Char*, fourthString,
                     "[" Intlstr_tstr(1) "]: LCM:  [ " Intlstr_tstrfull(2, "-", 16) "]   " Intlstr_tstr(3) "  "  Intlstr_tstr(4))    
    INTERNAL_Intlstr_Define0( ID_OUTPUT_OPERATION_START, ID_OUTPUT_OPERATION_START, "Start")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_OPERATION_END, ID_OUTPUT_OPERATION_END, "End")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_OPERATION_FAILED, ID_OUTPUT_OPERATION_FAILED, "*FAILED*")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_OPERATION_SKIP, ID_OUTPUT_OPERATION_SKIP, "Skip")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_ITEM_TEST, ID_OUTPUT_ITEM_TEST, "Test")   
    INTERNAL_Intlstr_Define0( ID_OUTPUT_ITEM_GET, ID_OUTPUT_ITEM_GET, "Get")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_ITEM_SET, ID_OUTPUT_ITEM_SET, "Set")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_ITEM_ROLLBACK, ID_OUTPUT_ITEM_ROLLBACK, "Rollback")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_ITEM_RESOURCE, ID_OUTPUT_ITEM_RESOURCE, "Resource")
    INTERNAL_Intlstr_Define0( ID_OUTPUT_EMPTYSTRING, ID_OUTPUT_EMPTYSTRING, " ")   
    INTERNAL_Intlstr_Define0( ID_CAINFRA_DEPENDCY_NULLPARAM, ID_CAINFRA_DEPENDCY_NULLPARAM, "Dependency cannot be resolved with null instance parameters. Verify that the instances are not null.")
    INTERNAL_Intlstr_Define1( ID_CAINFRA_DEPENDCY_CYCLE ,
                 ID_CAINFRA_DEPENDCY_CYCLE ,
                 _In_z_ const PAL_Char*, firstString,
                 "A circular dependency was found in the resources specified in the instance document. Check and correct the Requires property of instance " Intlstr_tstr(1) ", then try again.")
    INTERNAL_Intlstr_Define2( ID_CAINFRA_DEPENDCY_CYCLE2 ,
                     ID_CAINFRA_DEPENDCY_CYCLE2 ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     "A circular dependency was found in the resources specified in instance document. Check and correct the Requires property of instance " Intlstr_tstr(1) " defined in " Intlstr_tstr(2) ", then try again.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_DEPENDCY_OUTOFBOUNDS, ID_CAINFRA_DEPENDCY_OUTOFBOUNDS, "Index is out of bounds.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_INSTANCE_RESOURCEID, ID_CAINFRA_INSTANCE_RESOURCEID, "MI_Instance_GetElement failed to get ResourceId.")
    INTERNAL_Intlstr_Define2( ID_CAINFRA_INSTANCE_RESOURCEID_NOTFOUND ,
                     ID_CAINFRA_INSTANCE_RESOURCEID_NOTFOUND ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     "ResourceId " Intlstr_tstr(1) " could not be found in any of the resources specified in the instance document. The ResourceId specified in the Requires property may be incorrect. Correct the instance " Intlstr_tstr(2) ", then try again.")
    INTERNAL_Intlstr_Define3( ID_CAINFRA_INSTANCE_RESOURCEID_NOTFOUND2 ,
                     ID_CAINFRA_INSTANCE_RESOURCEID_NOTFOUND2 ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     _In_z_ const PAL_Char*, thirdString,                   
                     "ResourceId " Intlstr_tstr(1) " could not be found in any of the resources specified in the instance document. The ResourceId specified in the Requires property may be incorrect. Correct the instance " Intlstr_tstr(2) " defined in " Intlstr_tstr(3)", then try again.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_DEPENDCYRESOLVER_OUTOFBOUNDS, ID_CAINFRA_DEPENDCYRESOLVER_OUTOFBOUNDS, "Index out of range for dependency resolver.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_NULLPARAM, ID_CAINFRA_GET_NULLPARAM, "OutInstances cannot be null.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_NEWSESSION_FAILED, ID_CAINFRA_NEWSESSION_FAILED, "MI_Application_NewSession failed.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_UNKNOWN_REGISTRATION, ID_CAINFRA_UNKNOWN_REGISTRATION, "Unknown registration type.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_NAMESPACE_FAILED, ID_CAINFRA_GET_NAMESPACE_FAILED, "MI_Instance_GetElement failed to get Namespace for WMIv2 DSC resource.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_NEWAPPLICATIONINSTANCE_FAILED, ID_CAINFRA_GET_NEWAPPLICATIONINSTANCE_FAILED, "MI_Application_NewInstance failed.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_ADDELEM_FAILED, ID_CAINFRA_GET_ADDELEM_FAILED, "MI_Instance_AddElement returned an error on the inputResource parameter.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GETINSTANCE_FAILED, ID_CAINFRA_GETINSTANCE_FAILED, "MI_Operation_GetInstance failed.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_RETURNVALUE_FAILED, ID_CAINFRA_GET_RETURNVALUE_FAILED, "MI_Instance_GetElement failed for ReturnValue.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_RESULT_FAILED, ID_CAINFRA_GET_RESULT_FAILED, "MI_Instance_GetElement returned an error on the Result parameter.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_PROVCONTEXT_FAILED, ID_CAINFRA_GET_PROVCONTEXT_FAILED, "MI_Instance_GetElement failed for ProviderContext method parameter.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_OUTPUTRES_FAILED, ID_CAINFRA_GET_OUTPUTRES_FAILED, "MI_Instance_GetElement did not succeed for the Method parameter of the configuration.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_CLONE_FAILED, ID_CAINFRA_CLONE_FAILED, "MI_Instance_Clone failed.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GETEXECUTION_FAILED, ID_CAINFRA_GETEXECUTION_FAILED, "Could not process the get request.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_LOGRESOURCE_FAILED, ID_CAINFRA_GET_LOGRESOURCE_FAILED, "MI_Instance_GetElement failed to get Message from MSFT_LogResource.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_TESTEXECUTION_FAILED, ID_CAINFRA_TESTEXECUTION_FAILED, "Test did not succeed.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_NEWOPERATIONOPTIONS_FAILED, ID_CAINFRA_GET_NEWOPERATIONOPTIONS_FAILED, "Could not initialize a new operation option.")
    INTERNAL_Intlstr_Define0( ID_CAINFRA_GET_SETCUSTOMOPTION_FAILED, ID_CAINFRA_GET_SETCUSTOMOPTION_FAILED, "MI_OperationOptions_SetCustomOptions returned an error.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_COMPUTERNAMECONTEXT_ERROR, ID_LCMHELPER_COMPUTERNAMECONTEXT_ERROR, "The Local Configuration Manager could not read the ComputerName property context information.")
    INTERNAL_Intlstr_Define0( ID_LCMHELPER_GETTOKENINFOSIZE_ERROR, ID_LCMHELPER_GETTOKENINFOSIZE_ERROR, "Local Configuration Manager could not get token info size.")
    INTERNAL_Intlstr_Define2( ID_LCM_REPUDIATIONMSG ,
                     ID_LCM_REPUDIATIONMSG ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     "An LCM method call arrived from computer " Intlstr_tstr(1) " with user sid " Intlstr_tstr(2) ".")      
    INTERNAL_Intlstr_Define2( ID_CA_MOVETODESIREDSTATE_FAILED_APPEND_RESOURCEID ,
                     ID_CA_MOVETODESIREDSTATE_FAILED_APPEND_RESOURCEID ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     Intlstr_tstr(1) ". The related ResourceID is " Intlstr_tstr(2) ".")   
    INTERNAL_Intlstr_Define1( ID_CA_SET_TIMEMESSAGE ,
                 ID_CA_SET_TIMEMESSAGE ,
                 _In_z_ const PAL_Char*, firstString,
                 " in " Intlstr_tstr(1) " seconds.")  
    INTERNAL_Intlstr_Define1( ID_CA_TEST_TIMEMESSAGE ,
                 ID_CA_TEST_TIMEMESSAGE ,
                 _In_z_ const PAL_Char*, firstString,
                 " in " Intlstr_tstr(1) " seconds.")                
    INTERNAL_Intlstr_Define1( ID_CA_GET_TIMEMESSAGE ,
                 ID_CA_GET_TIMEMESSAGE ,
                 _In_z_ const PAL_Char*, firstString,
                 " in " Intlstr_tstr(1) " seconds.")                  
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_STORE_UNOPENED, ID_CA_CRYPTO_STORE_UNOPENED, "The local machine certificate store could not be opened.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_CERT_NOTFOUND, ID_CA_CRYPTO_CERT_NOTFOUND, "The certificate cannot be found in the local machine certificate store.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_KEY_CONTEXT_FAILED, ID_CA_CRYPTO_KEY_CONTEXT_FAILED, "Could not acquire a handle to the key context for the CSP.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_GET_PUBLIC_KEY_FAILED, ID_CA_CRYPTO_GET_PUBLIC_KEY_FAILED, "The public key could not be acquired.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_GET_PRIVATE_KEY_FAILED, ID_CA_CRYPTO_GET_PRIVATE_KEY_FAILED, "The private key could not be acquired.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_ENCRYPTED_MALLOC_FAILED, ID_CA_CRYPTO_ENCRYPTED_MALLOC_FAILED, "Memory could not be allocated for the encrypted data.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_ENCRYPTION_FAILED, ID_CA_CRYPTO_ENCRYPTION_FAILED, "Encryption did not succeed.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_DECRYPTED_MALLOC_FAILED, ID_CA_CRYPTO_DECRYPTED_MALLOC_FAILED, "Could not allocate memory for the decrypted data.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_DECRYPTION_FAILED, ID_CA_CRYPTO_DECRYPTION_FAILED, "Decryption failed.")
    INTERNAL_Intlstr_Define0( ID_CA_CRYPTO_UPDATE_PWD_FAILED, ID_CA_CRYPTO_UPDATE_PWD_FAILED, "Updating the password element after decription failed.")
    INTERNAL_Intlstr_Define0( ID_CA_FAILED_TO_GET_METACONFIGURATION, ID_CA_FAILED_TO_GET_METACONFIGURATION, "Could not retrieve the current Local Configuration Manager settings. Apply Local Configuration Manager settings and try again.")
    INTERNAL_Intlstr_Define0( ID_CA_CANCEL_CONFIGURATION, ID_CA_CANCEL_CONFIGURATION, "The current configuration was cancelled.")
    INTERNAL_Intlstr_Define0( ID_CA_FAILED_TO_WAIT_EVENT, ID_CA_FAILED_TO_WAIT_EVENT, "Could not wait for the stopping event.")
    INTERNAL_Intlstr_Define0( ID_CA_CANCELWMIV2_FAILED, ID_CA_CANCELWMIV2_FAILED, "Could not cancel the current operation.")
    INTERNAL_Intlstr_Define4( ID_CA_DUPLICATE_KEYS ,
                     ID_CA_DUPLICATE_KEYS ,
                     _In_z_ const PAL_Char*, firstString,
                     _In_z_ const PAL_Char*, secondString,
                     _In_z_ const PAL_Char*, thirdString,
                     _In_z_ const PAL_Char*, fourthString,
                     "The following resources '" Intlstr_tstr(1) "' ('" Intlstr_tstr(2) "' and '" Intlstr_tstr(3) "') have the same key property '"  Intlstr_tstr(4) "'. Ensure that key property combinations are unique for each resource.")
    INTERNAL_Intlstr_Define0( ID_CA_COMMA_SEPARATOR, ID_CA_COMMA_SEPARATOR, ", ")
    INTERNAL_Intlstr_Define0( ID_MODMAN_MODMAN_NULLPARAM, ID_MODMAN_MODMAN_NULLPARAM, "The moduleManager parameter cannot be null.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_APPINIT_FAILED, ID_MODMAN_APPINIT_FAILED, "MI_Application_Initialize failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_PARAM_INVALID, ID_MODMAN_PARAM_INVALID, "The moduleManager parameter is not valid.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_LOADDOC_NULLPARAM, ID_MODMAN_LOADDOC_NULLPARAM, "The moduleManager parameter is not valid.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_GETREG_NULLPARAM, ID_MODMAN_GETREG_NULLPARAM, "The moduleManager, className, and registrationInstance parameters cannot be null.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_REGINS_NOTFOUND, ID_MODMAN_REGINS_NOTFOUND, "Registration instance not found. Class is not a DSC configuration class.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_CONFIGCLASS_NOTREG, ID_MODMAN_CONFIGCLASS_NOTREG, "The class is not registered as a configuration class.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_GETCOMPAT_NULLPARAM, ID_MODMAN_GETCOMPAT_NULLPARAM, "The moduleManager, inInstance, and outInstance parameters cannot be null.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_GETFILTERED_FAILED, ID_MODMAN_GETFILTERED_FAILED, "GetFilteredResource failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_NEWOO_FAILED, ID_MODMAN_NEWOO_FAILED, "Could not create a new object to store the operation options while initializing the deserializer.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_OOSET_FAILED, ID_MODMAN_OOSET_FAILED, "Setting the Operation option while initializing the deserializer did not succeed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_FINDFIRST_FAILED, ID_MODMAN_FINDFIRST_FAILED, "FindFirstFile Failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_FINDNEXT_FAILED, ID_MODMAN_FINDNEXT_FAILED, "FindNextFile Failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_SYSTEMCACHE_INVALIDPARAM, ID_MODMAN_SYSTEMCACHE_INVALIDPARAM, "The paramter for GetSystemSchema is not valid.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_SCHEMAFROMMOF_INVALIDPARAM, ID_MODMAN_SCHEMAFROMMOF_INVALIDPARAM, "The paramter for GetSchemaFromMOFs is not valid.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_FILTER_RESOURCEID, ID_MODMAN_FILTER_RESOURCEID, "Not all instances within the instance document contain ResourceId.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_FILTER_MULTIPLEINS, ID_MODMAN_FILTER_MULTIPLEINS, "The instance document contains multiple OMI_ConfigurationDocument instances.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_FILTER_NOINSTANCE, ID_MODMAN_FILTER_NOINSTANCE, "Instance document must contain exactly one OMI_ConfigurationDocument instance.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_MAPPING_CLASSNAME_NOTFOUND, ID_MODMAN_MAPPING_CLASSNAME_NOTFOUND, "ClassName property not found for registration instance.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_FILTER_ARGNULL, ID_MODMAN_FILTER_ARGNULL, "The miApp, inInstance, and outInstance parameters cannot be null.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_GETELEMENT_FAILED, ID_MODMAN_GETELEMENT_FAILED, "MI_Instance_GetElement failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_INFRASCHEMA, ID_MODMAN_VALIDATE_INFRASCHEMA, "An unexpected infrastructure class was found.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREG_MULTI, ID_MODMAN_VALIDATE_PROVREG_MULTI, "Found multiple classes registered with the same name.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREG_MANDATORY, ID_MODMAN_VALIDATE_PROVREG_MANDATORY, "The mandatory ClassName property was not found in the registration. Use a registered classname and try again.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREG_NOCLASS, ID_MODMAN_VALIDATE_PROVREG_NOCLASS, "Found a registration instance without a class.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREG_NOREG, ID_MODMAN_VALIDATE_PROVREG_NOREG, "A schema was found that does not contain registration. Check the Registration and Schema directories to find the registered schemas.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_SCHEMA_INVPARAM, ID_MODMAN_VALIDATE_SCHEMA_INVPARAM, "The class reference does not exist.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_SCHEMA_NOMETHOD, ID_MODMAN_VALIDATE_SCHEMA_NOMETHOD, "Class should not contain any method.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_SCHEMA_VERSIONQUAL, ID_MODMAN_VALIDATE_SCHEMA_VERSIONQUAL, "ClassVersion Qualifier not found.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_SCHEMA_NOSUPP_REF, ID_MODMAN_VALIDATE_SCHEMA_NOSUPP_REF, "A property or array of type reference is not supported.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_SCHEMA_NOMANDATORY_QUALIFIER, ID_MODMAN_VALIDATE_SCHEMA_NOMANDATORY_QUALIFIER, "Cannot have the Read property with any of the following qualifiers: Write, Key, Required.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_SCHEMA_NOKEY, ID_MODMAN_VALIDATE_SCHEMA_NOKEY, "At least one key property must be defined in the instance document. Update the instance document and try again.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVSCHEMA_NORES, ID_MODMAN_VALIDATE_PROVSCHEMA_NORES, "You must specify at least one configuration resource per MOF file.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVSCHEMA_NOTREFERRED, ID_MODMAN_VALIDATE_PROVSCHEMA_NOTREFERRED, "All classes must have a reference to ConfigurationResource.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVSCHEMA_ONERES, ID_MODMAN_VALIDATE_PROVSCHEMA_ONERES, "There must be exactly one configuration resource per MOF file.")
    INTERNAL_Intlstr_Define1( ID_MODMAN_VALIDATE_PROVSCHEMA_NOMANDATORY ,
                 ID_MODMAN_VALIDATE_PROVSCHEMA_NOMANDATORY ,
                 _In_z_ const PAL_Char*, firstString,
                 "Could not find mandatory property " Intlstr_tstr(1) ". Add this property and try again.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREGINS_CLASSNAME, ID_MODMAN_VALIDATE_PROVREGINS_CLASSNAME, "MI_Instance_GetClassName failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREGINS_TYPE, ID_MODMAN_VALIDATE_PROVREGINS_TYPE, "Instance should be of type MSFT_CimConfigurationProviderRegistration or MSFT_PSConfigurationProviderRegistration.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREGINS_PROP_CLASSNAME, ID_MODMAN_VALIDATE_PROVREGINS_PROP_CLASSNAME, "Mandatory property ClassName not found.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREGINS_PROP_COMPATVERSION, ID_MODMAN_VALIDATE_PROVREGINS_PROP_COMPATVERSION, "Mandatory property DSCEngineCompatVersion not found.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREGINS_PROP_MODULEVERSION, ID_MODMAN_VALIDATE_PROVREGINS_PROP_MODULEVERSION, "Mandatory property DscModuleVersion not found.")
   
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREGINS_PROP_NAMESPACE, ID_MODMAN_VALIDATE_PROVREGINS_PROP_NAMESPACE, "Mandatory property Namespace not found.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVREGINS_PROP_MODULENAME, ID_MODMAN_VALIDATE_PROVREGINS_PROP_MODULENAME, "Mandatory property ModuleName not found.")
    INTERNAL_Intlstr_Define2( ID_MODMAN_VALIDATE_CLASSPROP_MAND_NAME, 
        ID_MODMAN_VALIDATE_CLASSPROP_MAND_NAME, 
        _In_z_ const PAL_Char*, className,
        _In_z_ const PAL_Char*, propertyName,
        "Mandatory property  " Intlstr_tstr(1) " not found for class " Intlstr_tstr(2))
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_CLASSPROP_MAND_TYPE, ID_MODMAN_VALIDATE_CLASSPROP_MAND_TYPE, "Mandatory property type does not match.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_CLASSPROP_MAND_GETCLASS, ID_MODMAN_VALIDATE_CLASSPROP_MAND_GETCLASS, "MGet class property count failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_CLASSPROP_MAND_NOMATCH, ID_MODMAN_VALIDATE_CLASSPROP_MAND_NOMATCH, "The number of properties does not match the expected number.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_BASERES_NOQUAL, ID_MODMAN_VALIDATE_BASERES_NOQUAL, "Mandatory property qualifer type is missing.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_BASERES_V2DERIVATEION, ID_MODMAN_VALIDATE_BASERES_V2DERIVATEION, "MSFT_CimConfigurationProviderRegistration must derive from MSFT_BaseConfigurationProviderRegistration.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_BASERES_PSDERIVATEION, ID_MODMAN_VALIDATE_BASERES_PSDERIVATEION, "MSFT_PSConfigurationProviderRegistration must derive from MSFT_BaseConfigurationProviderRegistration.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_MAPPING_NAMESPACE, ID_MODMAN_VALIDATE_MAPPING_NAMESPACE, "The registration instance does not contain a namespace. A namespace is required.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_MAPPING_PARAM_GET, ID_MODMAN_VALIDATE_MAPPING_PARAM_GET, "GetTargetResource requires three parameters.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_MAPPING_PARAM_TEST, ID_MODMAN_VALIDATE_MAPPING_PARAM_TEST, "TestTargetResource doesn't have 4 parameters.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_MAPPING_PARAM_SET, ID_MODMAN_VALIDATE_MAPPING_PARAM_SET, "SetTargetResource doesn't have 3 parameters.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_MAPPING_PARAM_ALLFAILED, ID_MODMAN_VALIDATE_MAPPING_PARAM_ALLFAILED, "ValidateDSCProviderMappingForWMIV2Provider did not succeed. One of the following was not found: Get, Test, or Set.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_WINDIRENV_FAILED, ID_MODMAN_WINDIRENV_FAILED, "GetEnvironmentVariable for %windir% failed.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_DOCINS_VERSION, ID_MODMAN_VALIDATE_DOCINS_VERSION, "The Version property of the OMI_ConfigurationDocument class is not properly formatted. Check the formatting and try again.")
    INTERNAL_Intlstr_Define1( ID_MODMAN_DUPLICATE_RESOURCEID ,
                 ID_MODMAN_DUPLICATE_RESOURCEID ,
                 _In_z_ const PAL_Char*, firstString,
                 "Found more than one instance with the same ResourceId " Intlstr_tstr(1) ". Correct that and try again.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_METACONFIG_MERGED_WITH_OTHERCONFIG, ID_MODMAN_METACONFIG_MERGED_WITH_OTHERCONFIG, "The current document contains Local Configuration Manager settings, which is not supported. Send Local Configuration Manager settings seperately.")
    INTERNAL_Intlstr_Define0( ID_MODMAN_METACONFIG_NOTFOUND_OR_MORE, ID_MODMAN_METACONFIG_NOTFOUND_OR_MORE, "Local Configuration Manager settings were not found, or the current document contains other configurations. Correct that and try again.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_STARTPROCESSREBOOT, ID_LCM_WRITEMESSAGE_STARTPROCESSREBOOT, "Starting reboot processing.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_REBOOT_PENDINGEXIST, ID_LCM_WRITEMESSAGE_REBOOT_PENDINGEXIST, "A pending configuration exists after reboot. DSC will process a set request on the pending configuration.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_REBOOT_CURRENTEXIST, ID_LCM_WRITEMESSAGE_REBOOT_CURRENTEXIST, "Checking consistency for current configuration after reboot.")
    INTERNAL_Intlstr_Define0( ID_LCM_WRITEMESSAGE_ENDPROCESSREBOOT, ID_LCM_WRITEMESSAGE_ENDPROCESSREBOOT, "Reboot processing completed.")
    INTERNAL_Intlstr_Define0( ID_PULL_CONFIGURATIONIDNOTSPECIFIED,ID_PULL_CONFIGURATIONIDNOTSPECIFIED,"The configuration ID is not in a valid format. Please supply the value in Guid format or specify 'UseSystemUUID' to automatically detect and use the target node's UUID.")
    INTERNAL_Intlstr_Define1( ID_PULL_INVALIDCONFIGURATIONIDFORMAT ,
                 ID_PULL_INVALIDCONFIGURATIONIDFORMAT ,
                 _In_z_ const PAL_Char*, firstString,
                 "The configuration ID  " Intlstr_tstr(1) " is not in a valid format. Please use a configuration with name in a Guid format.")
    INTERNAL_Intlstr_Define0( ID_PULL_INVALIDURLINCUSTOMDATA,ID_PULL_INVALIDURLINCUSTOMDATA, "Invalid URL specified in Local Configuration Manager settings.")
    INTERNAL_Intlstr_Define1( ID_PULL_GETACTIONFAILED ,
                 ID_PULL_GETACTIONFAILED ,
                 _In_z_ const PAL_Char*, firstString,
                 "A generic exception occured during while trying to get the action by Download Manager " Intlstr_tstr(1) ".")    
    INTERNAL_Intlstr_Define2( ID_PULL_GETACTIONUNEXPECTEDRESULT ,
                 ID_PULL_GETACTIONUNEXPECTEDRESULT ,
                 _In_z_ const PAL_Char*, firstString,
                 _In_z_ const PAL_Char*, secondString,
                 "Unexpected result " Intlstr_tstr(1) " while trying to get the action from server "  Intlstr_tstr(2) ".")
    INTERNAL_Intlstr_Define1( ID_PULL_UNSECURECONNECTIONNOTALLOWED ,
                 ID_PULL_UNSECURECONNECTIONNOTALLOWED ,
                 _In_z_ const PAL_Char*, firstString,
                 "Cannot download configuration from " Intlstr_tstr(1) ". Downloading over HTTP is not allowed. To ensure security while downloading configurations use an HTTPS address for the ServerUrl in the DownloadMangerCustomData of the LocalConfigurationManager resource for this device. If you understand the security implications of using HTTP and want to allow its use on this device, set AllowUnsecureConnection property to true in the DownloadMangerCustomData of the LocalConfigurationManager resource for this device.")                    
    INTERNAL_Intlstr_Define1( ID_PULLGETCONFIGURATIONFAILED ,
                 ID_PULLGETCONFIGURATIONFAILED ,
                 _In_z_ const PAL_Char*, firstString,
                 "A generic exception occured during while trying to get the configuration by Download Manager " Intlstr_tstr(1) ".")       
    INTERNAL_Intlstr_Define1( ID_PULLGETCONFIGURATION_NULLCHECKSUMALGORITHM ,
                 ID_PULLGETCONFIGURATION_NULLCHECKSUMALGORITHM ,
                 _In_z_ const PAL_Char*, firstString,
                 "Server " Intlstr_tstr(1) " returned an empty checksum algorithm.")   
    INTERNAL_Intlstr_Define1( ID_PULLGETCONFIGURATION_NULLCHECKSUM ,
                 ID_PULLGETCONFIGURATION_NULLCHECKSUM ,
                 _In_z_ const PAL_Char*, firstString,
                 "Server " Intlstr_tstr(1) " returned an empty checksum.")         
    INTERNAL_Intlstr_Define2( ID_PULLGETCONFIGURATION_INVALIDCHECKSUMALGORITHM ,
                 ID_PULLGETCONFIGURATION_INVALIDCHECKSUMALGORITHM ,
                 _In_z_ const PAL_Char*, firstString,
                 _In_z_ const PAL_Char*, secondString,
                 "Server " Intlstr_tstr(1) " returned an unsupported "  Intlstr_tstr(2) " checksum algorithm.")       
    INTERNAL_Intlstr_Define1( ID_PULLGETCONFIGURATION_CHECKSUMSAVEFAILED ,
                 ID_PULLGETCONFIGURATION_CHECKSUMSAVEFAILED ,
                 _In_z_ const PAL_Char*, firstString,
                 "Failed to save the configuration checksum in file " Intlstr_tstr(1) ".")     
    INTERNAL_Intlstr_Define2( ID_PULLGETCONFIGURATION_BADRESPONSE ,
                 ID_PULLGETCONFIGURATION_BADRESPONSE ,
                 _In_z_ const PAL_Char*, firstString,
                 _In_z_ const PAL_Char*, secondString,
                 "The attempt to get the configuration from server " Intlstr_tstr(1) " returned unexpected response code "  Intlstr_tstr(2) ".")                 
    INTERNAL_Intlstr_Define2( ID_PULLGETACTION_BADRESPONSE ,
                 ID_PULLGETACTION_BADRESPONSE ,
                 _In_z_ const PAL_Char*, firstString,
                 _In_z_ const PAL_Char*, secondString,
                 "The attempt to get the action from server " Intlstr_tstr(1) " returned unexpected response code "  Intlstr_tstr(2) ".")  
    INTERNAL_Intlstr_Define1( ID_PULL_CONFIGURATIONSAVEFAILED ,
                 ID_PULL_CONFIGURATIONSAVEFAILED ,
                 _In_z_ const PAL_Char*, firstString,
                 "Failed to save the configuration in file " Intlstr_tstr(1) ".")  
    INTERNAL_Intlstr_Define0( ID_PULL_CHECKSUMMISMATCH,ID_PULL_CHECKSUMMISMATCH,"Checksum for configuration does not match.")                 
    INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_DOCINS , ID_MODMAN_VALIDATE_DOCINS ,"There is no document instance inside the metaconfiguration. Please create the configuration with an instance of OMI_ConfigurationDocument and try again.")
    INTERNAL_Intlstr_Define1( ID_LCMHELPER_INVALID_PARTIALCONFIG_NOTINMETACONF ,
                 ID_LCMHELPER_INVALID_PARTIALCONFIG_NOTINMETACONF ,
                 _In_z_ const PAL_Char*, firstString,
                 "The partial configuration name " Intlstr_tstr(1) " present in the configuration document is invalid. Define a partial configuration inside the metaconfiguration with this partial configuration name in order to use it.")
    INTERNAL_Intlstr_Define0( ID_LCM_CANNOTUSE_PARTIALCONFIG_PUSHMODE_WITHOUTPUBLISH , ID_LCM_CANNOTUSE_PARTIALCONFIG_PUSHMODE_WITHOUTPUBLISH ,"The only way DSC Partial Configurations can be used in Push mode is if the Publish-DscConfiguration Cmdlet is used. No other push cmdlet is supported. To avoid this error, either set a metaconfiguration without partial configurations, or use the Publish-DscConfiguration cmdlet to deploy your partial configuration.")

INTERNAL_Intlstr_Define0( ID_PULL_DSCCONF_NOTOPENABLE,
			  ID_PULL_DSCCONF_NOTOPENABLE,
                 	  "Unable to open file at " CONFIG_SYSCONFDIR "/dsc/dsc.conf")

INTERNAL_Intlstr_Define1( ID_PULL_DSCCONF_NOTREADABLE,
			  ID_PULL_DSCCONF_NOTREADABLE,
      			  _In_z_ const PAL_Char*, firstString,
                 	  "Unable to read file at " CONFIG_SYSCONFDIR "/dsc/dsc.conf. "  Intlstr_tstr(1) ".")

INTERNAL_Intlstr_Define2( ID_PULL_DSCCONF_INVALIDVALUE,
			  ID_PULL_DSCCONF_INVALIDVALUE,
      			  _In_z_ const PAL_Char*, firstString,
                          _In_z_ const PAL_Char*, secondString,
                 	  "Key " Intlstr_tstr(1) " in file " CONFIG_SYSCONFDIR "/dsc/dsc.conf has invalid value "  Intlstr_tstr(2) ".")

INTERNAL_Intlstr_Define0( ID_PULL_SSLCIPHERLISTTOOLONG,
			  ID_PULL_SSLCIPHERLISTTOOLONG,
                 	  "sslcipherlist is too long in " CONFIG_SYSCONFDIR "/dsc/dsc.conf. It must be 4096 characters or less.")


INTERNAL_Intlstr_Define0( ID_PULL_CABUNDLETOOLONG,
			  ID_PULL_CABUNDLETOOLONG,
                 	  "CURL_CA_BUNDLE is too long in " CONFIG_SYSCONFDIR "/dsc/dsc.conf. It must be 4096 characters or less.")

INTERNAL_Intlstr_Define0( ID_PULL_CABUNDLENOTSUPPORTED,
			  ID_PULL_CABUNDLENOTSUPPORTED,
                 	  "The CURL_CA_BUNDLE option is not supported by the version of cURL installed to this system. Please either install a more recent version of libcurl, or disable the CURL_CA_BUNDLE option in " CONFIG_SYSCONFDIR "/dsc/dsc.conf.")

INTERNAL_Intlstr_Define0( ID_PULL_NOCONFIGDOWNLOADMANAGERS,
			  ID_PULL_NOCONFIGDOWNLOADMANAGERS,
                 	  "There are no ConfigurationDownloadManagers specified in the MetaConfiguration")

INTERNAL_Intlstr_Define0( ID_PULL_TOOMANYCONFIGDOWNLOADMANAGERS,
			  ID_PULL_TOOMANYCONFIGDOWNLOADMANAGERS,
                 	  "There is more than one ConfigurationDownloadManager specified. You must use PartialConfigurations to have more than one ConfigurationDownloadManager.")

INTERNAL_Intlstr_Define1( ID_PULL_NOSERVERURL,
			  ID_PULL_NOSERVERURL,
      			  _In_z_ const PAL_Char*, firstString,
                 	  "There is no ServerURL specified for the WebDownloadManager with ResourceID: "  Intlstr_tstr(1) ".")

INTERNAL_Intlstr_Define0( ID_PULL_CURLFAILEDTOINITIALIZE,
			  ID_PULL_CURLFAILEDTOINITIALIZE,
                 	  "cURL failed to initialize.")

INTERNAL_Intlstr_Define0( ID_PULL_CURLFAILEDTOSETCIPHERLIST,
			  ID_PULL_CURLFAILEDTOSETCIPHERLIST,
                 	  "cURL failed to set the specified cipher list.")

INTERNAL_Intlstr_Define0( ID_PULL_CURLFAILEDTOSETNOSSLV3,
			  ID_PULL_CURLFAILEDTOSETNOSSLV3,
                 	  "cURL failed to disable SSLv3 communication.")

INTERNAL_Intlstr_Define2( ID_PULL_CURLPERFORMFAILED,
			  ID_PULL_CURLPERFORMFAILED,
      			  _In_z_ const PAL_Char*, firstString,
                          _In_z_ const PAL_Char*, secondString,
                 	  "cURL failed to perform on this base url: " Intlstr_tstr(1)  " with this error message: "  Intlstr_tstr(2) ". Make sure cURL and SSL libraries are up to date.")

INTERNAL_Intlstr_Define0( ID_PULL_INVALIDRESPONSEFROMSERVER,
			  ID_PULL_INVALIDRESPONSEFROMSERVER,
                 	  "Receieved an invalid response from server.")

INTERNAL_Intlstr_Define0( ID_PULL_INVALIDCHECKSUMALGORITHM,
			  ID_PULL_INVALIDCHECKSUMALGORITHM,
                 	  "Receieved an invalid checksum algorithm from server.")

INTERNAL_Intlstr_Define1( ID_MODMAN_INVALID_PARTIALCONFIG_CONFIGSOURCE,
			  ID_MODMAN_INVALID_PARTIALCONFIG_CONFIGSOURCE,
  			  _In_z_ const PAL_Char*, firstString,
              "The download manager " Intlstr_tstr(1) " mentioned in the partial configuration is undefined in the meta configuration or assigned incorrectly. Check the download manager and assign ResourceRepositoryWeb or ResourceReporistoryShare to ResourceModuleSource and ConfigurationRepositoryWeb or ConfigurationRepositoryShare to ConfigurationSource")

              
INTERNAL_Intlstr_Define1( ID_MODMAN_PARTIALCONFIG_CONFIGSOURCE_MUSTBEONE,
			  ID_MODMAN_PARTIALCONFIG_CONFIGSOURCE_MUSTBEONE,
  			  _In_z_ const PAL_Char*, firstString,
              "The download manager " Intlstr_tstr(1) " mentioned in the partial configuration is not allowed. ConfigurationSource must have a single value.")

INTERNAL_Intlstr_Define0( ID_MODMAN_PARTIALCONFIG_RESOURCEMODULESOURCE_NOTSUPPORTED,
			  ID_MODMAN_PARTIALCONFIG_RESOURCEMODULESOURCE_NOTSUPPORTED,
              "ResourceModuleSource is not supported for partial configurations on this system.")

INTERNAL_Intlstr_Define0(ID_PARTIALCONFIG_NOPARTIALCONFIGPRESENT,
              ID_PARTIALCONFIG_NOPARTIALCONFIGPRESENT,
"None of the partial configurations defined in the mataconfiguraiton was found in the store. Either the configuraitons have not been pulled from the pull server (in the case of pull refres mode), or they have not been published ot the store (in the case of push refresh mode). ")

INTERNAL_Intlstr_Define0(ID_PARTIALCONFIG_FAILEDPARTIALCONFIGS,
              ID_PARTIALCONFIG_FAILEDPARTIALCONFIGS,
              "One or more partial configurations failed to apply. No configuration could be created.")

INTERNAL_Intlstr_Define1( ID_PULL_NOCONFIGURATIONSOURCE,
			  ID_PULL_NOCONFIGURATIONSOURCE,
      			  _In_z_ const PAL_Char*, firstString,
                 	  "No ConfigurationSource is specified for the PartialConfiguration: "  Intlstr_tstr(1) ".")


INTERNAL_Intlstr_Define2( ID_PULL_SERVERHTTPERRORCODE,
			  ID_PULL_SERVERHTTPERRORCODE,
      			  _In_z_ const PAL_Char*, firstString,
                          _In_z_ const PAL_Char*, secondString,
                 	  "Pull server with url: " Intlstr_tstr(1) " responded with error code: "  Intlstr_tstr(2) ".")


INTERNAL_Intlstr_Define4( ID_PULL_SERVERHTTPERRORCODEMODULE,
			    ID_PULL_SERVERHTTPERRORCODEMODULE,
      			_In_z_ const PAL_Char*, firstString,
                _In_z_ const PAL_Char*, secondString,
                _In_z_ const PAL_Char*, thirdString,
                _In_z_ const PAL_Char*, fourthString,
                "Pull server with url: " Intlstr_tstr(1) " responded with error code: "  Intlstr_tstr(2) " for module '"  Intlstr_tstr(3) "' version '"  Intlstr_tstr(4) "'.")

INTERNAL_Intlstr_Define2( ID_PULL_INSTALLMODULEFAILED,
 			  ID_PULL_INSTALLMODULEFAILED,
      			  _In_z_ const PAL_Char*, firstString,
                          _In_z_ const PAL_Char*, secondString,
                 	  "Failed to install module: " Intlstr_tstr(1) " with version: "  Intlstr_tstr(2) ". Removed module.")

INTERNAL_Intlstr_Define2( ID_PULL_INSTALLMODULEANDREMOVEMODULEFAILED,
 			  ID_PULL_INSTALLMODULEANDREMOVEMODULEFAILED,
      			  _In_z_ const PAL_Char*, firstString,
                          _In_z_ const PAL_Char*, secondString,
                 	  "Failed to install module: " Intlstr_tstr(1) " with version: "  Intlstr_tstr(2) ". Also failed to remove module.")

INTERNAL_Intlstr_Define1( ID_PULL_INITIALIZEMODULETABLEFAILED,
			  ID_PULL_INITIALIZEMODULETABLEFAILED,
      			  _In_z_ const PAL_Char*, firstString,
                 	  "Failed to initialize the ModuleVersion table: "  Intlstr_tstr(1) ".")

INTERNAL_Intlstr_Define2( ID_PULL_INVALIDMODULEVERSION,
     			  ID_PULL_INVALIDMODULEVERSION,
      			  _In_z_ const PAL_Char*, firstString,
                          _In_z_ const PAL_Char*, secondString,
                 	  "Invalid module version: "  Intlstr_tstr(1) " for module: " Intlstr_tstr(2)  ".")


INTERNAL_Intlstr_Define0( ID_PULL_RESTARTINGSERVER,
			  ID_PULL_RESTARTINGSERVER,
                 	  "Due to a required resource module installation, DSC will be restarted. The configuration operation will resume after the restart")


INTERNAL_Intlstr_Define1( ID_APPLYCONFIG_RESOURCEERRORLIST,
			  ID_APPLYCONFIG_RESOURCEERRORLIST,
      			  _In_z_ const PAL_Char*, firstString,
                 	  "Failed to apply the configuration.  These resources produced errors: "  Intlstr_tstr(1))

INTERNAL_Intlstr_Define1( ID_PULL_REPORTINGFAILED,
			  ID_PULL_REPORTINGFAILED,
      			  _In_z_ const PAL_Char*, firstString,
                 	  "Failed to report to all reporting servers.  Last server failed with HTTP response code: "  Intlstr_tstr(1) ".")

INTERNAL_Intlstr_Define2( ID_PULL_SERVERHTTPERRORCODEREGISTER,
			  ID_PULL_SERVERHTTPERRORCODEREGISTER,
      			  _In_z_ const PAL_Char*, firstString,
                          _In_z_ const PAL_Char*, secondString,
                 	  "Failed to register with a pull server at url: " Intlstr_tstr(1) ". It responded with error code: "  Intlstr_tstr(2) " for a module.")

INTERNAL_Intlstr_Define0( ID_PULL_CERTOPTS_NOT_SUPPORTED,ID_PULL_CERTOPTS_NOT_SUPPORTED,"cURL does not support setting certificate options on this system.")


INTERNAL_Intlstr_Define0( ID_PULL_FAILEDTOGENERATECERT, ID_PULL_FAILEDTOGENERATECERT,"Failed to generate certificate and private key for pull server communication.")

INTERNAL_Intlstr_Define0( ID_CANNOT_RUN_OMSCONFIG_AS_ROOT, ID_CANNOT_RUN_OMSCONFIG_AS_ROOT,"Unable to run omsconfig configurations as root.  Please use omsagent credentials.")


INTERNAL_Intlstr_Define0( ID_PULL_PROXYTOOLONG,
			  ID_PULL_PROXYTOOLONG,
                 	  "PROXY is too long in " CONFIG_SYSCONFDIR "/dsc/dsc.conf. It must be 4096 characters or less.")

INTERNAL_Intlstr_Define0( ID_PULL_PROXYNOTSUPPORTED,
			  ID_PULL_PROXYNOTSUPPORTED,
                 	  "The PROXY option is not supported by the version of cURL installed to this system. Please either install a more recent version of libcurl, or disable the PROXY option in " CONFIG_SYSCONFDIR "/dsc/dsc.conf.")


INTERNAL_Intlstr_Define0( ID_OUTPUT_ITEM_INVENTORY, ID_OUTPUT_ITEM_INVENTORY, "Inventory")
INTERNAL_Intlstr_Define0( ID_CAINFRA_INVENTORY_NAMESPACE_FAILED, ID_CAINFRA_INVENTORY_NAMESPACE_FAILED, "MI_Instance_GetElement failed to get Namespace for WMIv2 DSC resource.")
INTERNAL_Intlstr_Define0( ID_CAINFRA_INVENTORY_NEWAPPLICATIONINSTANCE_FAILED, ID_CAINFRA_INVENTORY_NEWAPPLICATIONINSTANCE_FAILED, "MI_Application_NewInstance failed.")
INTERNAL_Intlstr_Define0( ID_CAINFRA_INVENTORY_ADDELEM_FAILED, ID_CAINFRA_INVENTORY_ADDELEM_FAILED, "MI_Instance_AddElement returned an error on the inputResource parameter.")
INTERNAL_Intlstr_Define0( ID_CAINFRA_INVENTORY_NEWOPERATIONOPTIONS_FAILED, ID_CAINFRA_INVENTORY_NEWOPERATIONOPTIONS_FAILED, "Could not initialize a new operation option.")
INTERNAL_Intlstr_Define0( ID_CAINFRA_INVENTORY_SETCUSTOMOPTION_FAILED, ID_CAINFRA_INVENTORY_SETCUSTOMOPTION_FAILED, "MI_OperationOptions_SetCustomOptions returned an error.")
INTERNAL_Intlstr_Define1( ID_CA_INVENTORY_TIMEMESSAGE, ID_CA_INVENTORY_TIMEMESSAGE , _In_z_ const PAL_Char*, firstString, " in " Intlstr_tstr(1) " seconds.")   
INTERNAL_Intlstr_Define0( ID_CAINFRA_INVENTORY_NULLPARAM, ID_CAINFRA_INVENTORY_NULLPARAM, "OutInstances cannot be null.")
INTERNAL_Intlstr_Define0( ID_LCMHELPER_GETINVENTORY_ERROR , ID_LCMHELPER_GETINVENTORY_ERROR ,"The Inventory function did not succeed.")
INTERNAL_Intlstr_Define0( ID_LCMHELPER_INVENTORY_MOF_DOESNT_EXIST, ID_LCMHELPER_INVENTORY_MOF_DOESNT_EXIST, "Inventory mof does not exist.")
INTERNAL_Intlstr_Define0( ID_LCMHELPER_LOAD_INVENTORY_FAILED , ID_LCMHELPER_LOAD_INVENTORY_FAILED, "Could not load the inventory document from the specified location. Ensure that the inventory document exists and try again.")
INTERNAL_Intlstr_Define0( ID_LCMHELPER_INVENTORY_CONF_FAILED , ID_LCMHELPER_INVENTORY_CONF_FAILED ,"PerformInventory did not succeed.")
INTERNAL_Intlstr_Define0( ID_CANNOT_RUN_DSC_AS_NONROOT, ID_CANNOT_RUN_DSC_AS_NONROOT,"Unable to run dsc configurations as non-root.  Please use root credentials.")
INTERNAL_Intlstr_Define0( ID_LCMHELPER_INVENTORY_FAILED , ID_LCMHELPER_INVENTORY_FAILED ,"Posting output for PerformInventory did not succeed.")
INTERNAL_Intlstr_Define0( ID_LCMHELPER_POSTINVENTORY_FAILED , ID_LCMHELPER_POSTINVENTORY_FAILED ,"PerformInventory could not get the current Local Configuration Manager settings for the system.")

INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVSCHEMA_SHOULD_NOT_BE_INVENTORY, ID_MODMAN_VALIDATE_PROVSCHEMA_SHOULD_NOT_BE_INVENTORY, "Configuration mof contains the DocumentType = 'inventory' in the OMI_ConfigurationDocument instance, which is not allowed for configuration mofs.")
INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVSCHEMA_SHOULD_BE_INVENTORY_1, ID_MODMAN_VALIDATE_PROVSCHEMA_SHOULD_BE_INVENTORY_1, "Inventory mof does not contain the DocumentType field in the OMI_ConfigurationDocument instance.")
INTERNAL_Intlstr_Define0( ID_MODMAN_VALIDATE_PROVSCHEMA_SHOULD_BE_INVENTORY_2, ID_MODMAN_VALIDATE_PROVSCHEMA_SHOULD_BE_INVENTORY_2, "Inventory mof contains the DocumentType field in the OMI_ConfigurationDocument instance, but it is not equal to 'inventory'.")

INTERNAL_Intlstr_Define0( ID_LCMHELPER_ERROR_CREATING_DYNAMIC_INSTANCE_INVENTORY, ID_LCMHELPER_ERROR_CREATING_DYNAMIC_INSTANCE_INVENTORY , "Error creating serializedInstance using MI_NewDynamicInstance")
INTERNAL_Intlstr_Define0( ID_LCMHELPER_ERROR_ADDING_DYNAMIC_INSTANCE_INVENTORY , ID_LCMHELPER_ERROR_ADDING_DYNAMIC_INSTANCE_INVENTORY , "Error adding instance array to serializedInstance")

INTERNAL_Intlstr_Define0(ID_LCM_MONITORONLY_CONFIGURATIONMODE , ID_LCM_MONITORONLY_CONFIGURATIONMODE , "LCM is running in MonitorOnly mode and will only test the configuration.")
INTERNAL_Intlstr_Define0(ID_LCMHELPER_GET_OPERATION_AGAINST_PENDING ,
                         ID_LCMHELPER_GET_OPERATION_AGAINST_PENDING ,
                         "The GET operation will be carried against a pending configuration since the latest configuration has not converged yet.")
INTERNAL_Intlstr_Define0(ID_LCMHELPER_TEST_OPERATION_AGAINST_PENDING ,
                         ID_LCMHELPER_TEST_OPERATION_AGAINST_PENDING ,
                         "The TEST operation will be carried against a pending configuration since the latest configuration has not converged yet.")
 
INTERNAL_Intlstr_Define0( ID_NATIVE_PROVIDER_MANAGER_SET_OPERATION_FAILED , ID_NATIVE_PROVIDER_MANAGER_SET_OPERATION_FAILED , "Native provider failed to run SET operation.")
INTERNAL_Intlstr_Define0( ID_DSC_HOST_INVALID_OPERATION , ID_DSC_HOST_INVALID_OPERATION , "Invalid value for DSC Operation")

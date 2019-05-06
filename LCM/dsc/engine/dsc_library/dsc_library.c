/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MI.h"
#include "dsc_library.h"
#include "Resources_LCM.h"
#include "EventWrapper.h"
#include "EngineHelper.h"
#include "LocalConfigManagerHelper.h"
#include "MSFT_DSCLocalConfigurationManager.h"
#include "parson.h"
#include "DSC_Systemcalls.h"

#include <stdio.h>

MI_Result  DscLib_GetConfiguration (
        _In_ JSON_Value** p_result_root_value,
        _In_ MI_Char* p_configuration_filename,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_InstanceA output_instances = {0};
    MI_Uint8A configuration_mof_data = {0};
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("GetConfiguration");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    // If the configuration file has been passed in the parameters, try to read that file
    if (p_configuration_filename != NULL)
    {
        // If a configuration file name is passed in the parameters, read from the passed configuration file.
        // Read file contents from the pending configuration file into configuration_mof_data
        result = ReadFileContent(p_configuration_filename, &configuration_mof_data.data, &configuration_mof_data.size, &extended_errors);
    }
    else if (File_ExistT(GetCurrentConfigFileName()) != -1)
    {
        // Read file contents from the current configuration file (Current.mof) into configuration_mof_data
        result = ReadFileContent(GetCurrentConfigFileName(), &configuration_mof_data.data, &configuration_mof_data.size, &extended_errors);
    }
    else if (File_ExistT(GetPendingConfigFileName()) != -1)
    {
        // Read file contents from the pending configuration file (Pending.mof) into configuration_mof_data
        result = ReadFileContent(GetPendingConfigFileName(), &configuration_mof_data.data, &configuration_mof_data.size, &extended_errors);
    }
    else
    {
        GetCimMIError(MI_RESULT_FAILED, &extended_errors, ID_LCMHELPER_CURRENT_NOTFOUND);
        goto Cleanup;
    }

    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    result = CallGetConfiguration(
        configuration_mof_data.data,
        configuration_mof_data.size,
        &output_instances,
        context,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // Extract the output values
    *p_result_root_value = json_value_init_object();
    JSON_Object *result_root_object = json_value_get_object(*p_result_root_value);
    json_object_set_value(result_root_object, "configurations", json_value_init_array());
    JSON_Array *configurations_result_arr = json_object_get_array(result_root_object, "configurations");

    MI_Uint32 i = 0;
    for(i = 0 ; i < output_instances.size; i++)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(output_instances.data[i], &value);
        json_array_append_value(configurations_result_arr, value);
    }

    CleanUpInstanceCache(&output_instances);

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context, EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_GET, (const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_TestConfiguration (
        _In_ JSON_Value** p_result_root_value,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_Boolean testStatus = MI_FALSE;
    MI_StringA resourceId = {0};
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("TestConfiguration");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    result = CallTestConfiguration(
        &testStatus,
        &resourceId,    // Nothing is actually populated here.
        context,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // Create the output object
    *p_result_root_value = json_value_init_object();
    JSON_Object *result_root_object = json_value_get_object(*p_result_root_value);

    // Extract InDesiredState field from MI instance result and update the output object
    json_object_set_boolean(result_root_object, "InDesiredState", testStatus);

    // Extract ResourceId field from MI instance result and update the output object
    json_object_set_value(result_root_object, "ResourceId", json_value_init_array());
    JSON_Array *resource_id_arr = json_object_get_array(result_root_object, "ResourceId");

    MI_Uint32 i = 0;
    for(i = 0 ; i < resourceId.size; i++)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(resourceId.data[i], &value);
        json_array_append_value(resource_id_arr, value);
    }

    // Release allocated memory for test results
    for(i = 0 ; i < resourceId.size; i++)
    {
        DSC_free(resourceId.data[i]);
    }
    DSC_free(resourceId.data);

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context, EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_TEST, (const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_PerformInventory (
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_InstanceA output_instances = {0};
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("PerformInventory");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    MI_Char * InMOF;
    InMOF = (MI_Char*) DSC_malloc ( sizeof(MI_Char) * 1, NitsHere());
    InMOF[0] = '\0';

    result = CallPerformInventory(
        InMOF,
        &output_instances,
        context,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    CleanUpInstanceCache(&output_instances);

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context, EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_INVENTORY,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_PerformInventoryOOB (
        _In_ MI_Char* p_mof_filename,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_InstanceA output_instances = {0};
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("PerformInventoryOOB");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        //CreateMiInstanceErrorObject(&extended_errors, MI_T("method: %T, InitHandler failed: %T\n"), method_name, result);
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    result = CallPerformInventory(
        p_mof_filename,
        &output_instances,
        context,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        // CreateMiInstanceErrorObject(&extended_errors, MI_T("method: %T, CallPerformInventory failed: %T\n"), method_name, result);
        goto Cleanup_LCMStatus;
    }

    CleanUpInstanceCache(&output_instances);

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context, EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_INVENTORY,(const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_SetConfiguration (
        _In_ MI_Char* p_configuration_filename,
        _In_ MI_Uint32 p_flags,
        _In_ MI_Boolean p_force,
        _In_ MI_Char* p_method_name,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_Uint8A configuration_mof_data = {0};
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(p_method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    // If the configuration file has been passed in the parameters, try to read that file
    if (p_configuration_filename != NULL)
    {
        // If a configuration file name is passed in the parameters, read from the passed configuration file.
        // Read file contents from the pending configuration file into configuration_mof_data
        result = ReadFileContent(p_configuration_filename, &configuration_mof_data.data, &configuration_mof_data.size, &extended_errors);
    }
    else
    {
        GetCimMIError(MI_RESULT_FAILED, &extended_errors, ID_LCMHELPER_CURRENT_NOTFOUND);
        goto Cleanup;
    }

    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    result = CallSetConfiguration(
        configuration_mof_data.data,
        configuration_mof_data.size,
        p_flags,
        p_force,
        context,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context, EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_SET, (const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_SendConfiguration (
        _In_ MI_Char* p_configuration_filename,
        _In_ MI_Boolean p_force,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Uint32 flags = LCM_SETFLAGS_SAVETOPENDINGONLY;
    MI_Char* method_name = MI_T("SendConfiguration");
    return DscLib_SetConfiguration(
            p_configuration_filename,
            flags,
            p_force,
            method_name,
            p_error_root_value
        );
}

MI_Result  DscLib_SendConfigurationApply (
        _In_ MI_Char* p_configuration_filename,
        _In_ MI_Boolean p_force,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Uint32 flags = LCM_SETFLAGS_DEFAULT;
    MI_Char* method_name = MI_T("SendConfigurationApply");
    return DscLib_SetConfiguration(
            p_configuration_filename,
            flags,
            p_force,
            method_name,
            p_error_root_value
        );
}

MI_Result  DscLib_SendMetaConfigurationApply (
        _In_ MI_Char* p_metaconfiguration_filename,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Uint32 flags = LCM_SETFLAGS_DEFAULT | LCM_SET_METACONFIG;
    MI_Char* method_name = MI_T("SendMetaConfigurationApply");
    MI_Boolean force = MI_TRUE;
    return DscLib_SetConfiguration(
            p_metaconfiguration_filename,
            flags,
            force,
            method_name,
            p_error_root_value
        );
}

MI_Result  DscLib_GetMetaConfiguration (
        _In_ JSON_Value** p_result_root_value,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MSFT_DSCMetaConfiguration * metaconfiguration_instance;
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("GetMetaConfiguration");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    result = GetMetaConfig(&metaconfiguration_instance);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // // Extract the output values
    Convert_MIInstance_JSON(metaconfiguration_instance, p_result_root_value);

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_ApplyConfiguration (
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("ApplyConfiguration");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    result = CallConsistencyEngine(
        context,
        TASK_REGULAR,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_RollBack (
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("RollBack");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    SetLCMStatusBusy();

    start = CPU_GetTimeStamp();

    result = CallRestoreConfiguration(
        LCM_SETFLAGS_DEFAULT,
        context,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;
    LCM_WriteMessage_Internal_TimeTaken(context, EMPTY_STRING, ID_LCM_TIMEMESSAGE, ID_OUTPUT_ITEM_ROLLBACK, (const MI_Real64)duration, MI_WRITEMESSAGE_CHANNEL_VERBOSE);

    DSC_EventWriteMethodEnd(__WFUNCTION__);

Cleanup_LCMStatus:
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_PerformRequiredConfigurationChecks (
        _In_ MI_Uint32 p_flags,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    // MI_Uint8A configuration_mof_data = {0};
    MSFT_DSCMetaConfiguration * metaconfiguration_instance;
    MI_Value value;
    MI_Uint32 flags = 0;
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("PerformRequiredConfigurationChecks");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    start = CPU_GetTimeStamp();
    SetLCMStatusBusy();

    result = GetMetaConfig(&metaconfiguration_instance);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    if (p_flags == TASK_BOOTSTRAP)
    {
        result = RegisterStandardTasks(&extended_errors);
        if (result != MI_RESULT_OK)
        {
            goto Cleanup_LCMStatus;
        }
    }

    result = MI_Instance_GetElement((MI_Instance*)metaconfiguration_instance, MSFT_DSCMetaConfiguration_RefreshMode, &value, NULL, &flags, NULL);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    if (flags & MI_FLAG_NULL)
    {
        value.string = METADATA_REFRESHMODE_PUSH;
    }

    if (Tcscasecmp(value.string , METADATA_REFRESHMODE_PULL) == 0)
    {
        result = DoPullServerRefresh(metaconfiguration_instance, &extended_errors);
        if (result != MI_RESULT_OK)
        {
            goto Cleanup_LCMStatus;
        }
    }

    result = RunConsistencyEngine(
        p_flags,
        context,
        &extended_errors
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;

Cleanup_LCMStatus:
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    SetLCMStatusReady();

Cleanup:
    ResetJobId();
    MI_Instance_Delete((MI_Instance *)metaconfiguration_instance);

    if (result != MI_RESULT_OK)
    {
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

MI_Result  DscLib_StopConfiguration (
        _In_ MI_Boolean p_force,
        _In_ JSON_Value** p_error_root_value
    )
{
    MI_Result result = MI_RESULT_OK;
    MI_Instance *extended_errors = NULL;
    MI_Real64 duration;
    ptrdiff_t start, finish;

    MI_Char* method_name = MI_T("StopConfiguration");

    MI_Context* context = (MI_Context*)DSC_malloc(sizeof(MI_Context), NitsHere()); 

    result = InitHandler(method_name, &extended_errors);
    if (result != MI_RESULT_OK)
    {
        goto Cleanup;
    }

    start = CPU_GetTimeStamp();
    SetLCMStatusBusy();

    result = StopCurrentConfiguration(
        &extended_errors,
        p_force
    );
    if (result != MI_RESULT_OK)
    {
        goto Cleanup_LCMStatus;
    }

    // Stop the clock and measure time taken for this operation
    finish = CPU_GetTimeStamp();
    duration = (MI_Real64)(finish- start) / TIME_PER_SECONND;

Cleanup_LCMStatus:
    DSC_EventWriteMethodEnd(__WFUNCTION__);
    SetLCMStatusReady();

Cleanup:
    ResetJobId();

    if (result != MI_RESULT_OK)
    {
        JSON_Value *value;
        Convert_MIInstance_JSON(extended_errors, p_error_root_value);
        MI_Instance_Delete(extended_errors);
    }

    DSC_free(context);

    return result;
}

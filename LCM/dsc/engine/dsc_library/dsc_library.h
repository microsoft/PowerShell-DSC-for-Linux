#ifndef _DSC_LIBRARY_H
#define _DSC_LIBRARY_H

#include "MI.h"
#include "EngineHelper.h"
#include "parson.h"

MI_Result  DscLib_GetConfiguration (
        _In_ JSON_Value** p_result_root_value,
        _In_ MI_Char* p_configuration_filename,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_TestConfiguration (
        _In_ JSON_Value** p_result_root_value,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_PerformInventory (
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_PerformInventoryOOB (
        _In_ MI_Char* p_mof_filename,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_SetConfiguration (
        _In_ MI_Char* p_configuration_filename,
        _In_ MI_Uint32 p_flags,
        _In_ MI_Boolean p_force,
        _In_ MI_Char* p_method_name,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_SendConfiguration (
        _In_ MI_Char* p_configuration_filename,
        _In_ MI_Boolean p_force,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_SendConfigurationApply (
        _In_ MI_Char* p_configuration_filename,
        _In_ MI_Boolean p_force,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_SendMetaConfigurationApply (
        _In_ MI_Char* p_metaconfiguration_filename,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_GetMetaConfiguration (
        _In_ JSON_Value** p_result_root_value,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_ApplyConfiguration (
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_RollBack (
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_PerformRequiredConfigurationChecks (
        _In_ MI_Uint32 p_flags,
        _In_ JSON_Value** p_error_root_value
    );

MI_Result  DscLib_StopConfiguration (
        _In_ MI_Boolean p_force,
        _In_ JSON_Value** p_error_root_value
    );

#endif // _DSC_LIBRARY_H

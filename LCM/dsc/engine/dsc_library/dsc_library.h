#ifndef _DSC_LIBRARY_H
#define _DSC_LIBRARY_H

#include "MI.h"
#include "EngineHelper.h"
#include "parson.h"

MI_Result  DscLib_GetConfiguration (
        _In_ JSON_Value** p_result_root_value,
        _In_ MI_Char* p_configuration_filename
    );

MI_Result  DscLib_TestConfiguration (
        _In_ JSON_Value** p_result_root_value
    );

MI_Result  DscLib_PerformInventory ();

MI_Result  DscLib_PerformInventoryOOB (
        _In_ MI_Char* p_mof_filename
    );

MI_Result  Convert_MIInstance_JSON (
        const MI_Instance* p_instance,
        JSON_Value** p_result_root_value
    );

#endif // _DSC_LIBRARY_H

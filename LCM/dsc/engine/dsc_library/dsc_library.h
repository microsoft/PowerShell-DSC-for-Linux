#ifndef _DSC_LIBRARY_H
#define _DSC_LIBRARY_H

#include "MI.h"
#include "EngineHelper.h"
#include "parson.h"

MI_Result  DscLib_GetConfiguration (
        // _In_ MI_Context* p_context,
        _In_ JSON_Value* p_result_root_value,
        _In_ MI_Char* p_configuration_filename
    );

MI_Result  Convert_MIInstance_JSON (
        const MI_Instance* p_instance,
        JSON_Value* p_result_root_value
    );

#endif // _DSC_LIBRARY_H

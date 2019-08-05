/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

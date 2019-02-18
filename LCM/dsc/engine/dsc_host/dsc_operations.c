///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// This file is implementing a separate version of what we have in MSFT_DSCLocalConfigurationManager.c
// The new implementation assumes there is no OMI server and is the code is expected to be used by dsc_host.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MI.h"
#include "dsc_operations.h"

void MI_CALL Invoke_DscOperation_GetConfiguration(
    _In_ MI_Context* context,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* instance,
    _Outptr_result_maybenull_ MI_Instance **p_extended_error)
{
    MI_UNREFERENCED_PARAMETER(in);
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);

    MSFT_DSCLocalConfigurationManager_Self *self = NULL;
    const MI_String class_name = MI_T("HOST");
    const MI_String method_name = MI_T("GetConfiguration");
    const MI_String name_space = MI_T("DSC");

    SetJobId();

    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__, &className, &method_name, &name_space);
    Invoke_GetConfiguration(self, context, &name_space, &class_name, &method_name, NULL, instance);
}

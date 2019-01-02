#include "MI.h"
#include "dsc_operations_context.h"

MI_Result Dsc_Operation_Context_Initialize(
        _In_ DSC_Operation_Context *p_context,
        _Outptr_result_maybenull_ MI_Instance **p_extended_error
    )
{
    MI_Result result = MI_RESULT_OK;
    DSC_Operation_Context *context = NULL;

    *p_extended_error = NULL;

    context = DSC_malloc(sizeof(DSC_Operation_Context), NitsHere());
    p_context = context;
    if (context == NULL)
    {
        GetCimMIError(MI_RESULT_INVALID_PARAMETER, p_extended_error, ID_DSC_OPERATION_CONTEXT_INVALID_OPERATION);
        return MI_RESULT_INVALID_PARAMETER;
    }

    context->job_id = NULL;

    return result;
}

MI_Result Dsc_Operation_Context_Uniitialize(
        _In_ DSC_Operation_Context *p_context,
        _Outptr_result_maybenull_ MI_Instance **p_extended_error
    )
{
    MI_Result result = MI_RESULT_OK;

    if (p_context)
    {
        DSC_free(p_context);
    }
    
    *p_extended_error = NULL;

    return result;
}
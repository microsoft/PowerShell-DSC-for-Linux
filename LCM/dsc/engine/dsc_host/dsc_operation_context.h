///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// This file is implementing a separate version of what we have in MSFT_DSCLocalConfigurationManager.c
// The new implementation assumes there is no OMI server and is the code is expected to be used by dsc_host.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DSC_OPERAION_CONTEXT_H
#define _DSC_OPERAION_CONTEXT_H

#include "MI.h"

typedef struct _DSC_Operation_Context
{
    MI_Char *job_id;
} DSC_Operation_Context;

MI_Result Dsc_Operation_Context_Initialize(
        _In_ DSC_Operation_Context *context,
        _Outptr_result_maybenull_ MI_Instance **extended_error
    );

MI_Result Dsc_Operation_Context_Uninitialize(
        _In_ DSC_Operation_Context *context,
        _Outptr_result_maybenull_ MI_Instance **extended_error
    );

#endif

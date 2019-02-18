#ifndef __DscWorkerResponseHandler_H_
#define __DscWorkerResponseHandler_H_
#endif

#include <MI.h>

#define DSCWORKER_COMPONENTNAME   MI_T("DSCWORKER")

MI_Result MI_CALL DscWorker_PostResult(
    _In_ void* context,
	MI_Result result,
    _In_opt_ const MI_Instance *error);

MI_Result MI_CALL DscWorker_PostInstance(
    _In_ void* context,
    _In_ const MI_Instance* instance);    

MI_Result MI_CALL DscWorker_WriteMessage(
    _In_ void* context,
    MI_Uint32 channel,
    _In_z_ const MI_Char* message);

MI_Result MI_CALL DscWorker_WriteProgress(
    _In_ void* context,
    _In_z_ const MI_Char* activity,
    _In_z_ const MI_Char* currentOperation,
    _In_z_ const MI_Char* statusDescription,
    MI_Uint32 percentComplete,
    MI_Uint32 secondsRemaining);

MI_Result MI_CALL DscWorker_WriteStreamParameter(
    _In_ void* context,
    _In_z_ const MI_Char* name,
    _In_ const MI_Value* value,
    _In_ MI_Type type,
    _In_ MI_Uint32 flags);

MI_Result MI_CALL DscWorker_WriteError(
    _In_ void* context,
    _In_ const MI_Instance *error,
    _Out_ MI_Boolean *shouldContinue);

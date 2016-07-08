/* @migen@ */
#include <MI.h>
#include "MSFT_DSCWebPullClient.h"
#include "WebPullClientInvoker.h"

void MI_CALL MSFT_DSCWebPullClient_Load(
    _Outptr_result_maybenull_ MSFT_DSCWebPullClient_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCWebPullClient_Unload(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DSCWebPullClient_Invoke_GetDSCAction(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCWebPullClient* instanceName,
    _In_opt_ const MSFT_DSCWebPullClient_GetDSCAction* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    GetDSCAction(context, in);
}

void MI_CALL MSFT_DSCWebPullClient_Invoke_GetDSCDocument(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCWebPullClient* instanceName,
    _In_opt_ const MSFT_DSCWebPullClient_GetDSCDocument* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    GetDSCDocument(context, in);
}

void MI_CALL MSFT_DSCWebPullClient_Invoke_GetDSCModule(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCWebPullClient* instanceName,
    _In_opt_ const MSFT_DSCWebPullClient_GetDSCModule* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    GetDSCModule(context, in);
}


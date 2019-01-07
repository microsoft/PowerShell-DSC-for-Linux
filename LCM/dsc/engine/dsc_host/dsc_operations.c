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

// void MI_CALL MSFT_DSCLocalConfigurationManager_Load(
//     _Outptr_result_maybenull_ MSFT_DSCLocalConfigurationManager_Self** self,
//     _In_opt_ MI_Module_Self* selfModule,
//     _In_ MI_Context* context)
// {
//     *self = NULL;
//     MI_UNREFERENCED_PARAMETER(selfModule);
//     MI_Context_PostResult(context, MI_RESULT_OK);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Unload(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_Context_PostResult(context, MI_RESULT_OK);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendConfiguration(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendConfigurationApply(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_GetConfiguration(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_ApplyConfiguration(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendMetaConfigurationApply(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_GetMetaConfiguration(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_RollBack(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_RollBack* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_TestConfiguration(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformRequiredConfigurationChecks(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_StopConfiguration(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformInventory(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventory* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

// void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformInventoryOOB(
//     _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
//     _In_ MI_Context* context,
//     _In_opt_z_ const MI_Char* nameSpace,
//     _In_opt_z_ const MI_Char* className,
//     _In_opt_z_ const MI_Char* methodName,
//     _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
//     _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* in)
// {
//     MI_UNREFERENCED_PARAMETER(self);
//     MI_UNREFERENCED_PARAMETER(nameSpace);
//     MI_UNREFERENCED_PARAMETER(className);
//     MI_UNREFERENCED_PARAMETER(methodName);
//     MI_UNREFERENCED_PARAMETER(instanceName);
//     MI_UNREFERENCED_PARAMETER(in);
//     MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
// }

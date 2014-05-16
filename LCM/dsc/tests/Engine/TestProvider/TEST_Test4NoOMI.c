/*============================================================================
 * Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *============================================================================
 */

/* @migen@ */
#include <MI.h>
#include "TEST_Test4NoOMI.h"

void MI_CALL TEST_Test4NoOMI_Load(
    _Outptr_result_maybenull_ TEST_Test4NoOMI_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Test4NoOMI_Unload(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Test4NoOMI_EnumerateInstances(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test4NoOMI_GetInstance(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test4NoOMI* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test4NoOMI_CreateInstance(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test4NoOMI* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test4NoOMI_ModifyInstance(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test4NoOMI* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test4NoOMI_DeleteInstance(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test4NoOMI* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test4NoOMI_Invoke_GetTargetResource(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test4NoOMI* instanceName,
    _In_opt_ const TEST_Test4NoOMI_GetTargetResource* in)
{
    TEST_Test4NoOMI_GetTargetResource out; 
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    TEST_Test4NoOMI_GetTargetResource_Construct(&out, context);
    TEST_Test4NoOMI_GetTargetResource_Set_OutputResource(&out,in->InputResource.value);
    TEST_Test4NoOMI_GetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Test4NoOMI_GetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);

}

void MI_CALL TEST_Test4NoOMI_Invoke_TestTargetResource(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test4NoOMI* instanceName,
    _In_opt_ const TEST_Test4NoOMI_TestTargetResource* in)
{
    TEST_Test4NoOMI_TestTargetResource out; 
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);
    TEST_Test4NoOMI_TestTargetResource_Construct(&out, context);
    TEST_Test4NoOMI_TestTargetResource_Set_Result(&out,MI_FALSE);
    TEST_Test4NoOMI_TestTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Test4NoOMI_TestTargetResource_Destruct(&out);

    MI_Context_PostResult(context, MI_RESULT_OK);

}

void MI_CALL TEST_Test4NoOMI_Invoke_SetTargetResource(
    _In_opt_ TEST_Test4NoOMI_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test4NoOMI* instanceName,
    _In_opt_ const TEST_Test4NoOMI_SetTargetResource* in)
{
    TEST_Test4NoOMI_SetTargetResource out;  
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    TEST_Test4NoOMI_SetTargetResource_Construct(&out, context);
    TEST_Test4NoOMI_SetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Test4NoOMI_SetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);

}



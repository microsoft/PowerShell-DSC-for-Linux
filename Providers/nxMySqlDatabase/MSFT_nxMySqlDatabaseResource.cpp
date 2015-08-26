/* @migen@ */
#include "MSFT_nxMySqlDatabaseResource.h"

#include "debug_tags.hpp"
#include "MI.h"
#include "PythonProvider.hpp"


#include <cstdlib>


typedef struct _MSFT_nxMySqlDatabaseResource_Self : public scx::PythonProvider
{
    /*ctor*/ _MSFT_nxMySqlDatabaseResource_Self ()
        : scx::PythonProvider ("nxMySqlDatabase")
    {
        // empty
    }
} MSFT_nxMySqlDatabaseResource_Self;


void MI_CALL MSFT_nxMySqlDatabaseResource_Load(
    _Outptr_result_maybenull_ MSFT_nxMySqlDatabaseResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxMySqlDatabase\"");
    MI_UNREFERENCED_PARAMETER(selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self)
    {
        if (0 == *self)
        {
            *self = new MSFT_nxMySqlDatabaseResource_Self;
            if (EXIT_SUCCESS != (*self)->init ())
            {
                delete *self;
                *self = 0;
                res = MI_RESULT_FAILED;
            }
        }
    }
    else
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult(context, res);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_Unload(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxMySqlDatabase\"");
    if (self)
    {
        delete self;
    }
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_EnumerateInstances(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
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

void MI_CALL MSFT_nxMySqlDatabaseResource_GetInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_CreateInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_ModifyInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_DeleteInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MSFT_nxMySqlDatabaseResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxMySqlDatabase\"");
    MI_Result result = MI_RESULT_FAILED;
    if (self)
    {
        MI_Instance* retInstance;
        MI_Instance_Clone (&in->InputResource.value->__instance, &retInstance);
        result = self->get (in->InputResource.value->__instance, context,
                            retInstance);
        if (MI_RESULT_OK == result)
        {
            SCX_BOOKEND_PRINT ("packing succeeded!");
            MSFT_nxMySqlDatabaseResource_GetTargetResource out;
            MSFT_nxMySqlDatabaseResource_GetTargetResource_Construct (&out, context);
            MSFT_nxMySqlDatabaseResource_GetTargetResource_Set_MIReturn (&out, 0);
            MI_Value value;
            value.instance = retInstance;
            MI_Instance_SetElement (&out.__instance, "OutputResource", &value,
                                    MI_INSTANCE, 0);
            result = MSFT_nxMySqlDatabaseResource_GetTargetResource_Post (&out, context);
            if (MI_RESULT_OK != result)
            {
                SCX_BOOKEND_PRINT ("post Failed");
            }
            MSFT_nxMySqlDatabaseResource_GetTargetResource_Destruct (&out);
        }
        else
        {
            SCX_BOOKEND_PRINT ("get FAILED");
        }
        MI_Instance_Delete (retInstance);
    }
    MI_Context_PostResult (context, result);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MSFT_nxMySqlDatabaseResource_TestTargetResource* in)
{
    MI_Result result = MI_RESULT_FAILED;
    if (self)
    {
        MI_Boolean testResult = MI_FALSE;
        result = self->test (in->InputResource.value->__instance, &testResult);
        if (MI_RESULT_OK == result)
        {
            MSFT_nxMySqlDatabaseResource_TestTargetResource out;
            MSFT_nxMySqlDatabaseResource_TestTargetResource_Construct (&out, context);
            MSFT_nxMySqlDatabaseResource_TestTargetResource_Set_Result (
                &out, testResult);
            MSFT_nxMySqlDatabaseResource_TestTargetResource_Set_MIReturn (&out, 0);
            MSFT_nxMySqlDatabaseResource_TestTargetResource_Post (&out, context);
            MSFT_nxMySqlDatabaseResource_TestTargetResource_Destruct (&out);
        }
    }
    MI_Context_PostResult (context, result);
}

void MI_CALL MSFT_nxMySqlDatabaseResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MSFT_nxMySqlDatabaseResource_SetTargetResource* in)
{
    MI_Result result = MI_RESULT_FAILED;
    if (self)
    {
        MI_Result setResult = MI_RESULT_FAILED;
        result = self->set (in->InputResource.value->__instance, &setResult);
        if (MI_RESULT_OK == result)
        {
            result = setResult;
            MSFT_nxMySqlDatabaseResource_SetTargetResource out;
            MSFT_nxMySqlDatabaseResource_SetTargetResource_Construct (&out, context);
            MSFT_nxMySqlDatabaseResource_SetTargetResource_Set_MIReturn (
                &out, setResult);
            MSFT_nxMySqlDatabaseResource_SetTargetResource_Post (&out, context);
            MSFT_nxMySqlDatabaseResource_SetTargetResource_Destruct (&out);
        }
    }
    MI_Context_PostResult (context, result);
}

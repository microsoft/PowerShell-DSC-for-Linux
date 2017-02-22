/* @migen@ */
#include "MSFT_nxNopResource.h"


#include "debug_tags.hpp"
#include "MI.h"
#include "PythonProvider.hpp"

typedef struct _MSFT_nxNopResource_Self : public scx::PythonProvider
{
    /*ctor*/ _MSFT_nxNopResource_Self ()
        : scx::PythonProvider ("nxNop")
    {
        // empty
    }
} MSFT_nxNopResource_Self;


void MI_CALL MSFT_nxNopResource_Load(
    _Outptr_result_maybenull_ MSFT_nxNopResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxNop\"");
    MI_UNREFERENCED_PARAMETER(selfModule);   
    MI_Result res = MI_RESULT_OK;
    if (0 != self)
    {
        if (0 == *self)
        {
            *self = new MSFT_nxNopResource_Self;
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

void MI_CALL MSFT_nxNopResource_Unload(
    _In_opt_ MSFT_nxNopResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxNop\"");
    if (self)
    {
        delete self;
    }   
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxNopResource_EnumerateInstances(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxNopResource_GetInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxNopResource_CreateInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxNopResource_ModifyInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxNopResource_DeleteInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxNopResource_Invoke_GetTargetResource(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_nxNopResource* instanceName,
    const MSFT_nxNopResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxEnvironment\"");
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
            MSFT_nxNopResource_GetTargetResource out;
            MSFT_nxNopResource_GetTargetResource_Construct (&out, context);
            MSFT_nxNopResource_GetTargetResource_Set_MIReturn (&out, 0);
            MI_Value value;
            value.instance = retInstance;
            MI_Instance_SetElement (&out.__instance, "OutputResource", &value,
                                    MI_INSTANCE, 0);
            result = MSFT_nxNopResource_GetTargetResource_Post (&out, context);
            if (MI_RESULT_OK != result)
            {
                SCX_BOOKEND_PRINT ("post Failed");
            }
            MSFT_nxNopResource_GetTargetResource_Destruct (&out);
        }
        else
        {
            SCX_BOOKEND_PRINT ("get FAILED");
        }
        MI_Instance_Delete (retInstance);
    }
    MI_Context_PostResult (context, result);
}

void MI_CALL MSFT_nxNopResource_Invoke_TestTargetResource(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_nxNopResource* instanceName,
    const MSFT_nxNopResource_TestTargetResource* in)
{
    MI_Result result = MI_RESULT_FAILED;
    if (self)
    {
        MI_Boolean testResult = MI_FALSE;
        result = self->test (in->InputResource.value->__instance, &testResult);
        if (MI_RESULT_OK == result)
        {
            MSFT_nxNopResource_TestTargetResource out;
            MSFT_nxNopResource_TestTargetResource_Construct (&out, context);
            MSFT_nxNopResource_TestTargetResource_Set_Result (
                &out, testResult);
            MSFT_nxNopResource_TestTargetResource_Set_MIReturn (&out, 0);
            MSFT_nxNopResource_TestTargetResource_Post (&out, context);
            MSFT_nxNopResource_TestTargetResource_Destruct (&out);
        }
    }
    MI_Context_PostResult (context, result);
}

void MI_CALL MSFT_nxNopResource_Invoke_SetTargetResource(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_nxNopResource* instanceName,
    const MSFT_nxNopResource_SetTargetResource* in)
{
    MI_Result result = MI_RESULT_FAILED;
    if (self)
    {
        MI_Result setResult = MI_RESULT_FAILED;
        result = self->set (in->InputResource.value->__instance, &setResult);
        if (MI_RESULT_OK == result)
        {
            result = setResult;
            MSFT_nxNopResource_SetTargetResource out;
            MSFT_nxNopResource_SetTargetResource_Construct (&out, context);
            MSFT_nxNopResource_SetTargetResource_Set_MIReturn (
                &out, setResult);
            MSFT_nxNopResource_SetTargetResource_Post (&out, context);
            MSFT_nxNopResource_SetTargetResource_Destruct (&out);
        }
    }
    MI_Context_PostResult (context, result);
}

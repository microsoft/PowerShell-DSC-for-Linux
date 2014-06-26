/* @migen@ */
#include "python_file_resource.hpp"
#include "python_helper.hpp"
#include "python_scoped_context.hpp"
#include <MI.h>
#include "MSFT_nxUserResource.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <stdlib.h>
#include <stdarg.h>
#include <ctime>
#include <iostream>


typedef struct _MSFT_nxUserResource_Self : public scx::PythonFileResource
{
    /*ctor*/ _MSFT_nxUserResource_Self (scx::PythonFileResource& base)
      : scx::PythonFileResource (base) {}
} MSFT_nxUserResource_Self;


void MI_CALL MSFT_nxUserResource_Load (
    _Outptr_result_maybenull_ MSFT_nxUserResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxUser\"");
    MI_UNREFERENCED_PARAMETER (selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self &&
        EXIT_SUCCESS != scx::PythonFileResource::create (self, "nxUser"))
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult (context, res);
}

void MI_CALL MSFT_nxUserResource_Unload (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxUser\"");
    if (self)
    {
        delete self;
    }
    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxUserResource_EnumerateInstances (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (propertySet);
    MI_UNREFERENCED_PARAMETER (keysOnly);
    MI_UNREFERENCED_PARAMETER (filter);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxUserResource_GetInstance (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (instanceName);
    MI_UNREFERENCED_PARAMETER (propertySet);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxUserResource_CreateInstance (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (newInstance);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxUserResource_ModifyInstance (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (modifiedInstance);
    MI_UNREFERENCED_PARAMETER (propertySet);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxUserResource_DeleteInstance (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (instanceName);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxUserResource_Invoke_GetTargetResource (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MSFT_nxUserResource_GetTargetResource* in)
{
    scx::PythonScopedContext lock (self->getThreadState ());
    SCX_BOOKEND_EX ("Get", " name=\"nxUser\"");
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxUserResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxUserResource_GetTargetResource_Construct (&out, context);
    r = MSFT_nxUserResource_GetTargetResource_Set_MIReturn (&out, 0);

    const MSFT_nxUserResource * user = in->InputResource.value;
    r = MI_Instance_Clone (&user->__instance, &newInstance);

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getGetFn (),
        scx::get_mi_value (user->UserName),
        scx::get_mi_value (user->Ensure),
        scx::get_mi_value (user->FullName),
        scx::get_mi_value (user->Description),
        scx::get_mi_value (user->Password),
        scx::get_mi_value (user->Disabled),
        scx::get_mi_value (user->PasswordChangeRequired),
        scx::get_mi_value (user->HomeDirectory),
        scx::get_mi_value (user->GroupID));
    
    // Expecting 1 + 9 parameters in return
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals) &&
        (1 + 9) == boost::python::len (retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    if (EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "UserName", retVals[1]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Ensure", retVals[2]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "FullName", retVals[3]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Description", retVals[4]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Password", retVals[5]) ||
        EXIT_SUCCESS != scx::set_mi_bool (
            newInstance, "Disabled", retVals[6]) ||
        EXIT_SUCCESS != scx::set_mi_bool (
            newInstance, "PasswordChangeRequired", retVals[7]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "HomeDirectory", retVals[8]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "GroupID", retVals[9]))
    {
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    value.instance = newInstance;
    r = MI_Instance_SetElement (
        &out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if (r != MI_RESULT_OK)
    {
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Instance_Delete (newInstance);
    r = MSFT_nxUserResource_GetTargetResource_Post (&out, context);
    if (r != MI_RESULT_OK)
    {
        MI_Context_PostResult (context, r);
        return;
    }

    r = MSFT_nxUserResource_GetTargetResource_Destruct (&out);
    if (r != MI_RESULT_OK)
    {
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxUserResource_Invoke_TestTargetResource (
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MSFT_nxUserResource_TestTargetResource* in)
{
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }
    SCX_BOOKEND_EX ("Test", " name=\"nxUser\"");
    scx::PythonScopedContext lock (self->getThreadState ());

    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxUserResource_TestTargetResource out;
    const MSFT_nxUserResource * user = in->InputResource.value;

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getTestFn (),
        scx::get_mi_value (user->UserName),
        scx::get_mi_value (user->Ensure),
        scx::get_mi_value (user->FullName),
        scx::get_mi_value (user->Description),
        scx::get_mi_value (user->Password),
        scx::get_mi_value (user->Disabled),
        scx::get_mi_value (user->PasswordChangeRequired),
        scx::get_mi_value (user->HomeDirectory),
        scx::get_mi_value (user->GroupID));
    
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        res = MI_FALSE;
    }

    r = MSFT_nxUserResource_TestTargetResource_Construct(&out, context);
    r = MSFT_nxUserResource_TestTargetResource_Set_Result(&out, res);
    r = MSFT_nxUserResource_TestTargetResource_Set_MIReturn(&out, 0);
    r = MSFT_nxUserResource_TestTargetResource_Post(&out, context);
    r = MSFT_nxUserResource_TestTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxUserResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MSFT_nxUserResource_SetTargetResource* in)
{
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }
    SCX_BOOKEND_EX ("Set", " name=\"nxUser\"");
    scx::PythonScopedContext lock (self->getThreadState ());

    MI_Result r = MI_RESULT_OK;
    MSFT_nxUserResource_SetTargetResource out;
    const MSFT_nxUserResource * user = in->InputResource.value;
    MI_Result res = MI_RESULT_OK;

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getSetFn (),
        scx::get_mi_value (user->UserName),
        scx::get_mi_value (user->Ensure),
        scx::get_mi_value (user->FullName),
        scx::get_mi_value (user->Description),
        scx::get_mi_value (user->Password),
        scx::get_mi_value (user->Disabled),
        scx::get_mi_value (user->PasswordChangeRequired),
        scx::get_mi_value (user->HomeDirectory),
        scx::get_mi_value (user->GroupID));

    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_RESULT_OK;
    }
    else
    {
        res = MI_RESULT_FAILED;
    }

    r = MSFT_nxUserResource_SetTargetResource_Construct(&out, context);
    r = MSFT_nxUserResource_SetTargetResource_Set_MIReturn(&out, res);
    r = MSFT_nxUserResource_SetTargetResource_Post(&out, context);
    r = MSFT_nxUserResource_SetTargetResource_Destruct(&out);
    MI_Context_PostResult(context, res);
}

/* @migen@ */
#include "python_file_resource.hpp"
#include "python_helper.hpp"
#include "python_scoped_context.hpp"
#include <MI.h>
#include "MSFT_nxServiceResource.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <stdlib.h>
#include <stdarg.h>
#include <ctime>
#include <iostream>


typedef struct _MSFT_nxServiceResource_Self : public scx::PythonFileResource
{
    /*ctor*/ _MSFT_nxServiceResource_Self (scx::PythonFileResource& base)
      : scx::PythonFileResource (base) {}
} MSFT_nxServerResource_Self;


void MI_CALL MSFT_nxServiceResource_Load(
    _Outptr_result_maybenull_ MSFT_nxServiceResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxService\"");
    MI_UNREFERENCED_PARAMETER(selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self &&
        EXIT_SUCCESS != scx::PythonFileResource::create (self, "nxService"))
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult(context, res);
}

void MI_CALL MSFT_nxServiceResource_Unload(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxService\"");
    if (self)
    {
        delete self;
    }
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxServiceResource_EnumerateInstances(
    _In_opt_ MSFT_nxServiceResource_Self* self,
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

void MI_CALL MSFT_nxServiceResource_GetInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxServiceResource_CreateInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxServiceResource_ModifyInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxServiceResource_DeleteInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxServiceResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MSFT_nxServiceResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxService\"");
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxServiceResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxServiceResource_GetTargetResource_Construct(&out, context);
    r = MSFT_nxServiceResource_GetTargetResource_Set_MIReturn(&out, 0);

    const MSFT_nxServiceResource * service = in->InputResource.value;
    r = MI_Instance_Clone(&service->__instance, &newInstance);

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getGetFn (),
        scx::get_mi_value (service->Name),
        scx::get_mi_value (service->Controller),
        scx::get_mi_value (service->Enabled),
        scx::get_mi_value (service->State));
    
    // Expecting 1 + 4 + 3 parameters in return
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals) &&
        (1 + 4 + 3) == boost::python::len (retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    if (EXIT_SUCCESS != scx::set_mi_string (newInstance, "Name", retVals[1]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Controller", retVals[2]) ||
        EXIT_SUCCESS != scx::set_mi_bool (
            newInstance, "Enabled", retVals[3]) ||
        EXIT_SUCCESS != scx::set_mi_string (newInstance, "State", retVals[4]) ||
        EXIT_SUCCESS != scx::set_mi_bool (
            newInstance, "IsEnabled", retVals[5]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Status", retVals[6]) ||
        EXIT_SUCCESS != scx::set_mi_string (newInstance, "Path", retVals[7]))
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }

    value.instance = newInstance;
    r = MI_Instance_SetElement(
        &out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    MI_Instance_Delete(newInstance);
    r = MSFT_nxServiceResource_GetTargetResource_Post(&out, context);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    r = MSFT_nxServiceResource_GetTargetResource_Destruct(&out);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxServiceResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MSFT_nxServiceResource_TestTargetResource* in)
{ 
    SCX_BOOKEND_EX ("Test", " name=\"nxService\"");
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxServiceResource_TestTargetResource out;
    const MSFT_nxServiceResource * service = in->InputResource.value;

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getTestFn (),
        scx::get_mi_value (service->Name),
        scx::get_mi_value (service->Controller),
        scx::get_mi_value (service->Enabled),
        scx::get_mi_value (service->State));
    
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        res = MI_FALSE;
    }

    r = MSFT_nxServiceResource_TestTargetResource_Construct(&out, context);
    r = MSFT_nxServiceResource_TestTargetResource_Set_Result(&out, res);
    r = MSFT_nxServiceResource_TestTargetResource_Set_MIReturn(&out, 0);
    r = MSFT_nxServiceResource_TestTargetResource_Post(&out, context);
    r = MSFT_nxServiceResource_TestTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxServiceResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MSFT_nxServiceResource_SetTargetResource* in)
{
    SCX_BOOKEND_EX ("Set", " name=\"nxService\"");
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxServiceResource_SetTargetResource out;
    const MSFT_nxServiceResource * service = in->InputResource.value;
    MI_Result res = MI_RESULT_OK;

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getSetFn (),
        scx::get_mi_value (service->Name),
        scx::get_mi_value (service->Controller),
        scx::get_mi_value (service->Enabled),
        scx::get_mi_value (service->State));

    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_RESULT_OK;
    }
    else
    {
        res = MI_RESULT_FAILED;
    }

    r = MSFT_nxServiceResource_SetTargetResource_Construct(&out, context);
    r = MSFT_nxServiceResource_SetTargetResource_Set_MIReturn(&out, res);
    r = MSFT_nxServiceResource_SetTargetResource_Post(&out, context);
    r = MSFT_nxServiceResource_SetTargetResource_Destruct(&out);
    MI_Context_PostResult(context, res);
}

/* @migen@ */
#include "python_file_resource.hpp"
#include "python_helper.hpp"
#include "python_scoped_context.hpp"
#include <MI.h>
#include "MSFT_nxGroupResource.h"


#include <boost/python.hpp>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <stdlib.h>
#include <stdarg.h>
#include <ctime>
#include <iostream>


typedef struct _MSFT_nxGroupResource_Self : public scx::PythonFileResource
{
    /*ctor*/ _MSFT_nxGroupResource_Self (scx::PythonFileResource& base)
      : scx::PythonFileResource (base) {}
} MSFT_nxGroupResource_Self;


void MI_CALL MSFT_nxGroupResource_Load (
    _Outptr_result_maybenull_ MSFT_nxGroupResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxGroup\"");
    MI_UNREFERENCED_PARAMETER (selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self &&
        EXIT_SUCCESS != scx::PythonFileResource::create (self, "nxGroup"))
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult (context, res);
}

void MI_CALL MSFT_nxGroupResource_Unload (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxGroup\"");
    if (self)
    {
        delete self;
    }
    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxGroupResource_EnumerateInstances (
    _In_opt_ MSFT_nxGroupResource_Self* self,
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

void MI_CALL MSFT_nxGroupResource_GetInstance (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (instanceName);
    MI_UNREFERENCED_PARAMETER (propertySet);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxGroupResource_CreateInstance (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (newInstance);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxGroupResource_ModifyInstance (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (modifiedInstance);
    MI_UNREFERENCED_PARAMETER (propertySet);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxGroupResource_DeleteInstance (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER (self);
    MI_UNREFERENCED_PARAMETER (nameSpace);
    MI_UNREFERENCED_PARAMETER (className);
    MI_UNREFERENCED_PARAMETER (instanceName);

    MI_Context_PostResult (context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxGroupResource_Invoke_GetTargetResource (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MSFT_nxGroupResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxGroup\"");
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxGroupResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxGroupResource_GetTargetResource_Construct (&out, context);
    r = MSFT_nxGroupResource_GetTargetResource_Set_MIReturn (&out, 0);

    const MSFT_nxGroupResource * group = in->InputResource.value;
    r = MI_Instance_Clone (&group->__instance, &newInstance);

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getGetFn (),
        scx::get_mi_value (group->GroupName),
        scx::get_mi_value (group->Ensure),
        scx::get_mi_value (group->Members),
        scx::get_mi_value (group->MembersToInclude),
        scx::get_mi_value (group->MembersToExclude),
        scx::get_mi_value (group->PreferredGroupID));
    
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals) &&
        (1 + 6) == boost::python::len (retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    if (EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "GroupName", retVals[1]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Ensure", retVals[2]) ||
        EXIT_SUCCESS != scx::set_mi_string_array (
            newInstance, "Members", retVals[3]) ||
        EXIT_SUCCESS != scx::set_mi_string_array (
            newInstance, "MembersToInclude", retVals[4]) ||
        EXIT_SUCCESS != scx::set_mi_string_array (
            newInstance, "MembersToExclude", retVals[5]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "PreferredGroupID", retVals[6]))
    {
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    value.instance = newInstance;
    r = MI_Instance_SetElement (
        &out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Instance_Delete (newInstance);
    r = MSFT_nxGroupResource_GetTargetResource_Post (&out, context);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult (context, r);
        return;
    }

    r = MSFT_nxGroupResource_GetTargetResource_Destruct (&out);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxGroupResource_Invoke_TestTargetResource (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MSFT_nxGroupResource_TestTargetResource* in)
{
    SCX_BOOKEND_EX ("Test", " name=\"nxGroup\"");
    if (!self)
    {
        MI_Context_PostResult (context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxGroupResource_TestTargetResource out;
    const MSFT_nxGroupResource * group = in->InputResource.value;

    boost::python::object retVals;

    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getTestFn (),
        scx::get_mi_value (group->GroupName),
        scx::get_mi_value (group->Ensure),
        scx::get_mi_value (group->Members).c_str (),
        scx::get_mi_value (group->MembersToInclude).c_str (),
        scx::get_mi_value (group->MembersToExclude).c_str (),
        scx::get_mi_value (group->PreferredGroupID));

    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        SCX_BOOKEND_PRINT ("Succeeded");
        res = MI_TRUE;
    }
    else
    {
        SCX_BOOKEND_PRINT ("Failed - 1");
        res = MI_FALSE;
    }

    r = MSFT_nxGroupResource_TestTargetResource_Construct (&out, context);
    r = MSFT_nxGroupResource_TestTargetResource_Set_Result (&out, res);
    r = MSFT_nxGroupResource_TestTargetResource_Set_MIReturn (&out, 0);
    r = MSFT_nxGroupResource_TestTargetResource_Post (&out, context);
    r = MSFT_nxGroupResource_TestTargetResource_Destruct (&out);
    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxGroupResource_Invoke_SetTargetResource (
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MSFT_nxGroupResource_SetTargetResource* in)
{
    SCX_BOOKEND_EX ("Set", " name=\"nxGroup\"");
    if (!self)
    {
        MI_Context_PostResult (context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxGroupResource_SetTargetResource out;
    const MSFT_nxGroupResource * group = in->InputResource.value;
    MI_Result res = MI_RESULT_OK;

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getSetFn (),
        scx::get_mi_value (group->GroupName),
        scx::get_mi_value (group->Ensure),
        scx::get_mi_value (group->Members),
        scx::get_mi_value (group->MembersToInclude),
        scx::get_mi_value (group->MembersToExclude),
        scx::get_mi_value (group->PreferredGroupID));

    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_RESULT_OK;
    }
    else
    {
        SCX_BOOKEND_PRINT ("Failed - 1");
        res = MI_RESULT_FAILED;
    }

    r = MSFT_nxGroupResource_SetTargetResource_Construct (&out, context);
    r = MSFT_nxGroupResource_SetTargetResource_Set_MIReturn (&out, res);
    r = MSFT_nxGroupResource_SetTargetResource_Post (&out, context);
    r = MSFT_nxGroupResource_SetTargetResource_Destruct (&out);
    MI_Context_PostResult (context, res);
}

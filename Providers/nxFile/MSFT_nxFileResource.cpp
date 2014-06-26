/* @migen@ */
#include <boost/python.hpp>
#include "debug_tags.hpp"
#include "python_file_resource.hpp"
#include "python_helper.hpp"
#include "python_scoped_context.hpp"
#include <MI.h>
#include "MSFT_nxFileResource.h"


#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <stdlib.h>
#include <stdarg.h>
#include <ctime>
#include <iostream>


typedef struct _MSFT_nxFileResource_Self : public scx::PythonFileResource
{
    /*ctor*/ _MSFT_nxFileResource_Self (scx::PythonFileResource& base)
      : scx::PythonFileResource (base) {}
} MSFT_nxFileResource_Self;


void MI_CALL MSFT_nxFileResource_Load(
    _Outptr_result_maybenull_ MSFT_nxFileResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxFile\"");
    MI_UNREFERENCED_PARAMETER(selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self &&
        EXIT_SUCCESS != scx::PythonFileResource::create (self, "nxFile"))
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult(context, res);
}

void MI_CALL MSFT_nxFileResource_Unload(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxFile\"");
    if (self)
    {
        delete self;
    }
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxFileResource_EnumerateInstances(
    _In_opt_ MSFT_nxFileResource_Self* self,
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

void MI_CALL MSFT_nxFileResource_GetInstance(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFileResource_CreateInstance(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFileResource_ModifyInstance(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFileResource_DeleteInstance(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFileResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFileResource* instanceName,
    _In_opt_ const MSFT_nxFileResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxFile\"");
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxFileResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxFileResource_GetTargetResource_Construct (&out, context);
    r = MSFT_nxFileResource_GetTargetResource_Set_MIReturn (&out, 0);

    const MSFT_nxFileResource* file = in->InputResource.value;
    r = MI_Instance_Clone (&file->__instance, &newInstance);

    MI_Boolean res = MI_TRUE;
    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getGetFn (),
        scx::get_mi_value (file->DestinationPath),
        scx::get_mi_value (file->SourcePath),
        scx::get_mi_value (file->Ensure),
        scx::get_mi_value (file->Type),
        scx::get_mi_value (file->Force),
        scx::get_mi_value (file->Contents),
        scx::get_mi_value (file->Checksum),
        scx::get_mi_value (file->Recurse),
        scx::get_mi_value (file->Links),
        scx::get_mi_value (file->Owner),
        scx::get_mi_value (file->Group),
        scx::get_mi_value (file->Mode));

    // 1 + 12 + 1 represents: result, 11 normal fields, 1 'read' fields
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals) &&
        (1 + 12 + 1) == boost::python::len (retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        SCX_BOOKEND_PRINT ("Failed - 1");
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }
    
    if (EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "DestinationPath", retVals[1]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "SourcePath", retVals[2]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Ensure", retVals[3]) ||
        EXIT_SUCCESS != scx::set_mi_string (newInstance, "Type", retVals[4]) ||
        EXIT_SUCCESS != scx::set_mi_bool (newInstance, "Force", retVals[5]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Contents", retVals[6]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Checksum", retVals[7]) ||
        EXIT_SUCCESS != scx::set_mi_bool (newInstance, "Recurse", retVals[8]) ||
        EXIT_SUCCESS != scx::set_mi_string (newInstance, "Links", retVals[9]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Owner", retVals[10]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Group", retVals[11]) ||
        EXIT_SUCCESS != scx::set_mi_string (newInstance, "Mode", retVals[12]))
    {
        SCX_BOOKEND_PRINT ("Failed - 2");
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }
    value.instance = newInstance;
    r = MI_Instance_SetElement (
        &out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if (MI_RESULT_OK != r)
    {
        SCX_BOOKEND_PRINT ("Failed - 3");
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Instance_Delete (newInstance);
    r = MSFT_nxFileResource_GetTargetResource_Post (&out, context);
    if (MI_RESULT_OK != r)
    {
        SCX_BOOKEND_PRINT ("Failed - 4");
        MI_Context_PostResult (context, r);
        return;
    }

    r = MSFT_nxFileResource_GetTargetResource_Destruct (&out);
    if (MI_RESULT_OK != r)
    {
        SCX_BOOKEND_PRINT ("Failed - 5");
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxFileResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFileResource* instanceName,
    _In_opt_ const MSFT_nxFileResource_TestTargetResource* in)
{
    SCX_BOOKEND_EX ("Test", " name=\"nxFile\"");
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxFileResource_TestTargetResource out;

    MSFT_nxFileResource const* file = in->InputResource.value;
    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getTestFn (),
        scx::get_mi_value (file->DestinationPath),
        scx::get_mi_value (file->SourcePath),
        scx::get_mi_value (file->Ensure),
        scx::get_mi_value (file->Type),
        scx::get_mi_value (file->Force),
        scx::get_mi_value (file->Contents),
        scx::get_mi_value (file->Checksum),
        scx::get_mi_value (file->Recurse),
        scx::get_mi_value (file->Links),
        scx::get_mi_value (file->Owner),
        scx::get_mi_value (file->Group),
        scx::get_mi_value (file->Mode));
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        res = MI_FALSE;
    }

    // Why are the results (r) of these functions being captured but not used?
    r = MSFT_nxFileResource_TestTargetResource_Construct(&out, context);
    r = MSFT_nxFileResource_TestTargetResource_Set_Result(&out, res);
    r = MSFT_nxFileResource_TestTargetResource_Set_MIReturn(&out, 0);
    r = MSFT_nxFileResource_TestTargetResource_Post(&out, context);
    r = MSFT_nxFileResource_TestTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxFileResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxFileResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFileResource* instanceName,
    _In_opt_ const MSFT_nxFileResource_SetTargetResource* in)
{
    SCX_BOOKEND_EX ("Set", " name=\"nxFile\"");
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxFileResource_SetTargetResource out;
    MI_Result res = MI_RESULT_OK;

    MSFT_nxFileResource const* file = in->InputResource.value;
    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getSetFn (),
        scx::get_mi_value (file->DestinationPath),
        scx::get_mi_value (file->SourcePath),
        scx::get_mi_value (file->Ensure),
        scx::get_mi_value (file->Type),
        scx::get_mi_value (file->Force),
        scx::get_mi_value (file->Contents),
        scx::get_mi_value (file->Checksum),
        scx::get_mi_value (file->Recurse),
        scx::get_mi_value (file->Links),
        scx::get_mi_value (file->Owner),
        scx::get_mi_value (file->Group),
        scx::get_mi_value (file->Mode));
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_RESULT_OK;
    }
    else
    {
        res = MI_RESULT_FAILED;
    }

    // Why are the results (r) of these functions being captured but not used?
    r = MSFT_nxFileResource_SetTargetResource_Construct(&out, context);
    r = MSFT_nxFileResource_SetTargetResource_Set_MIReturn(&out, res);
    r = MSFT_nxFileResource_SetTargetResource_Post(&out, context);
    r = MSFT_nxFileResource_SetTargetResource_Destruct(&out);
    MI_Context_PostResult(context, res);
}

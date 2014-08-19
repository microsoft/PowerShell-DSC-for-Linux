/* @migen@ */
#include <boost/python.hpp>
#include "debug_tags.hpp"
#include "python_file_resource.hpp"
#include "python_helper.hpp"
#include "python_scoped_context.hpp"
#include <MI.h>
#include "MSFT_nxIPAddressResource.h"


#include <cstdlib>


typedef struct _MSFT_nxIPAddressResource_Self : public scx::PythonFileResource
{
    /*ctor*/ _MSFT_nxIPAddressResource_Self (scx::PythonFileResource& base)
      : scx::PythonFileResource (base) {}
} MSFT_nxIPAddressResource_Self;


void MI_CALL MSFT_nxIPAddressResource_Load(
    _Outptr_result_maybenull_ MSFT_nxIPAddressResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxIPAddress\"");
    MI_UNREFERENCED_PARAMETER(selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self &&
        EXIT_SUCCESS != scx::PythonFileResource::create (self, "nxIPAddress"))
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult(context, res);
}

void MI_CALL MSFT_nxIPAddressResource_Unload(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxIPAddress\"");
    if (self)
    {
        delete self;
    }
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxIPAddressResource_EnumerateInstances(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
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

void MI_CALL MSFT_nxIPAddressResource_GetInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxIPAddressResource_CreateInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxIPAddressResource_ModifyInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxIPAddressResource_DeleteInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxIPAddressResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MSFT_nxIPAddressResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxIPAddress\"");
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxIPAddressResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxIPAddressResource_GetTargetResource_Construct (&out, context);
    r = MSFT_nxIPAddressResource_GetTargetResource_Set_MIReturn (&out, 0);

    const MSFT_nxIPAddressResource* ipAddress = in->InputResource.value;
    r = MI_Instance_Clone (&ipAddress->__instance, &newInstance);

    MI_Boolean res = MI_TRUE;
    boost::python::object retVals;
std::cerr << "invoking GET" << std::endl;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getGetFn (),
        scx::get_mi_value (ipAddress->InterfaceName),
        scx::get_mi_value (ipAddress->IPAddress),
        scx::get_mi_value (ipAddress->BootProtocol),
        scx::get_mi_value (ipAddress->DefaultGateway),
        scx::get_mi_value (ipAddress->Ensure),
        scx::get_mi_value (ipAddress->PrefixLength),
        scx::get_mi_value (ipAddress->AddressFamily));
std::cerr << "GET function returns" << std::endl;

    // 1 + 7 represents: result, 7 normal fields, 1 'read' fields
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals) &&
        (1 + 7) == boost::python::len (retVals))
    {
std::cerr << "good number of parameters and function succeeded" << std::endl;
        res = MI_TRUE;
    }
    else
    {
std::cerr << "parameters failed" << std::endl;
        SCX_BOOKEND_PRINT ("Failed - 1");
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }
    
    if (EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "InterfaceName", retVals[1]))
    {
std::cerr << "error parsing retVals[1]" << std::endl;
        SCX_BOOKEND_PRINT ("Failed - 2");
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;

     }
     if(   EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "IPAddress", retVals[2]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "BootProtocol", retVals[3]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "DefaultGateway", retVals[4]) ||
        EXIT_SUCCESS != scx::set_mi_string (newInstance, "Ensure", retVals[5]) ||
        EXIT_SUCCESS != scx::set_mi_uint32 (
            newInstance, "PrefixLength", retVals[6]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "AddressFamily", retVals[7]))
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
    r = MSFT_nxIPAddressResource_GetTargetResource_Post (&out, context);
    if (MI_RESULT_OK != r)
    {
        SCX_BOOKEND_PRINT ("Failed - 4");
        MI_Context_PostResult (context, r);
        return;
    }

    r = MSFT_nxIPAddressResource_GetTargetResource_Destruct (&out);
    if (MI_RESULT_OK != r)
    {
        SCX_BOOKEND_PRINT ("Failed - 5");
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxIPAddressResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MSFT_nxIPAddressResource_TestTargetResource* in)
{
    SCX_BOOKEND_EX ("Test", " name=\"nxIPAddress\"");
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxIPAddressResource_TestTargetResource out;

    MSFT_nxIPAddressResource const* ipAddress = in->InputResource.value;
    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getTestFn (),
        scx::get_mi_value (ipAddress->InterfaceName),
        scx::get_mi_value (ipAddress->IPAddress),
        scx::get_mi_value (ipAddress->BootProtocol),
        scx::get_mi_value (ipAddress->DefaultGateway),
        scx::get_mi_value (ipAddress->Ensure),
        scx::get_mi_value (ipAddress->PrefixLength),
        scx::get_mi_value (ipAddress->AddressFamily));
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_TRUE;
    }
    else
    {
        res = MI_FALSE;
    }

    // Why are the results (r) of these functions being captured but not used?
    r = MSFT_nxIPAddressResource_TestTargetResource_Construct(&out, context);
    r = MSFT_nxIPAddressResource_TestTargetResource_Set_Result(&out, res);
    r = MSFT_nxIPAddressResource_TestTargetResource_Set_MIReturn(&out, 0);
    r = MSFT_nxIPAddressResource_TestTargetResource_Post(&out, context);
    r = MSFT_nxIPAddressResource_TestTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxIPAddressResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MSFT_nxIPAddressResource_SetTargetResource* in)
{
    SCX_BOOKEND_EX ("Set", " name=\"nxIPAddress\"");
    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxIPAddressResource_SetTargetResource out;
    MI_Result res = MI_RESULT_OK;

    MSFT_nxIPAddressResource const* ipAddress = in->InputResource.value;
    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getSetFn (),
        scx::get_mi_value (ipAddress->InterfaceName),
        scx::get_mi_value (ipAddress->IPAddress),
        scx::get_mi_value (ipAddress->BootProtocol),
        scx::get_mi_value (ipAddress->DefaultGateway),
        scx::get_mi_value (ipAddress->Ensure),
        scx::get_mi_value (ipAddress->PrefixLength),
        scx::get_mi_value (ipAddress->AddressFamily));
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_RESULT_OK;
    }
    else
    {
        res = MI_RESULT_FAILED;
    }

    // Why are the results (r) of these functions being captured but not used?
    r = MSFT_nxIPAddressResource_SetTargetResource_Construct(&out, context);
    r = MSFT_nxIPAddressResource_SetTargetResource_Set_MIReturn(&out, res);
    r = MSFT_nxIPAddressResource_SetTargetResource_Post(&out, context);
    r = MSFT_nxIPAddressResource_SetTargetResource_Destruct(&out);
    MI_Context_PostResult(context, res);
}


/* @migen@ */
#include "python_file_resource.hpp"
#include "python_helper.hpp"
#include "python_scoped_context.hpp"
#include <MI.h>
#include "MSFT_nxFirewallResource.h"

#include <boost/python.hpp>
#include <cstdlib>


typedef struct _MSFT_nxFirewallResource_Self : public scx::PythonFileResource
{
    /*ctor*/ _MSFT_nxFirewallResource_Self (scx::PythonFileResource& base)
      : scx::PythonFileResource (base) {}
} MSFT_nxFirewallResource_Self;


void MI_CALL MSFT_nxFirewallResource_Load(
    _Outptr_result_maybenull_ MSFT_nxFirewallResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);
    SCX_BOOKEND_EX ("Load", " name=\"nxFirewall\"");
    MI_UNREFERENCED_PARAMETER (selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self &&
        EXIT_SUCCESS != scx::PythonFileResource::create (self, "nxFirewall"))
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult (context, res);
}

void MI_CALL MSFT_nxFirewallResource_Unload(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxFirewall\"");
    if (self)
    {
        delete self;
    }
}

void MI_CALL MSFT_nxFirewallResource_EnumerateInstances(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
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

void MI_CALL MSFT_nxFirewallResource_GetInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFirewallResource_CreateInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFirewallResource_ModifyInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFirewallResource_DeleteInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxFirewallResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MSFT_nxFirewallResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxFirewall\"");
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxFirewallResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxFirewallResource_GetTargetResource_Construct (&out, context);
    r = MSFT_nxFirewallResource_GetTargetResource_Set_MIReturn (&out, 0);

    const MSFT_nxFirewallResource* firewall = in->InputResource.value;
    r = MI_Instance_Clone (&firewall->__instance, &newInstance);

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getGetFn (),
        scx::get_mi_value (firewall->Name),
        scx::get_mi_value (firewall->Protocol),
        scx::get_mi_value (firewall->Ensure),
        scx::get_mi_value (firewall->AddressFamily),
        scx::get_mi_value (firewall->Access),
        scx::get_mi_value (firewall->State),
        scx::get_mi_value (firewall->State2),
        scx::get_mi_value (firewall->State3),
        scx::get_mi_value (firewall->Direction),
        scx::get_mi_value (firewall->SourceHost),
        scx::get_mi_value (firewall->SourcePort),
        scx::get_mi_value (firewall->DestinationHost),
        scx::get_mi_value (firewall->DestinationPort));


std::cerr << "GET function returned" << std::endl;
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals) &&
        (1 + 13) == boost::python::len (retVals))
    {
std::cerr << "proper number of values returned" << std::endl;
        res = MI_TRUE;
    }
    else
    {
std::cerr << "ERROR: invalid number of values returned" << std::endl;
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    if (EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Name", retVals[1]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Protocol", retVals[2]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Ensure", retVals[3]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "AddressFamily", retVals[4]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Access", retVals[5]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "State", retVals[6]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "State2", retVals[7]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "State3", retVals[8]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Direction", retVals[9]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "SourceHost", retVals[10]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "SourcePort", retVals[11]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "DestinationHost", retVals[12]) ||
        EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "DestinationPort", retVals[13]))
    {
std::cerr << "ERROR: having trouble parsing string" << std::endl;
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
    r = MSFT_nxFirewallResource_GetTargetResource_Post (&out, context);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult (context, r);
        return;
    }

    r = MSFT_nxFirewallResource_GetTargetResource_Destruct (&out);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxFirewallResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MSFT_nxFirewallResource_TestTargetResource* in)
{
    SCX_BOOKEND_EX ("Test", " name=\"nxFirewall\"");
    if (!self)
    {
        MI_Context_PostResult (context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxFirewallResource_TestTargetResource out;
    const MSFT_nxFirewallResource * firewall = in->InputResource.value;

    boost::python::object retVals;

    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getTestFn (),
        scx::get_mi_value (firewall->Name),
        scx::get_mi_value (firewall->Protocol),
        scx::get_mi_value (firewall->Ensure),
        scx::get_mi_value (firewall->AddressFamily),
        scx::get_mi_value (firewall->Access),
        scx::get_mi_value (firewall->State),
        scx::get_mi_value (firewall->State2),
        scx::get_mi_value (firewall->State3),
        scx::get_mi_value (firewall->Direction),
        scx::get_mi_value (firewall->SourceHost),
        scx::get_mi_value (firewall->SourcePort),
        scx::get_mi_value (firewall->DestinationHost),
        scx::get_mi_value (firewall->DestinationPort));

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

    r = MSFT_nxFirewallResource_TestTargetResource_Construct (&out, context);
    r = MSFT_nxFirewallResource_TestTargetResource_Set_Result (&out, res);
    r = MSFT_nxFirewallResource_TestTargetResource_Set_MIReturn (&out, 0);
    r = MSFT_nxFirewallResource_TestTargetResource_Post (&out, context);
    r = MSFT_nxFirewallResource_TestTargetResource_Destruct (&out);
    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxFirewallResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MSFT_nxFirewallResource_SetTargetResource* in)
{
    SCX_BOOKEND_EX ("Set", " name=\"nxFirewall\"");
    if (!self)
    {
        MI_Context_PostResult (context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxFirewallResource_SetTargetResource out;
    const MSFT_nxFirewallResource * firewall = in->InputResource.value;
    MI_Result res = MI_RESULT_OK;

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getSetFn (),
        scx::get_mi_value (firewall->Name),
        scx::get_mi_value (firewall->Protocol),
        scx::get_mi_value (firewall->Ensure),
        scx::get_mi_value (firewall->AddressFamily),
        scx::get_mi_value (firewall->Access),
        scx::get_mi_value (firewall->State),
        scx::get_mi_value (firewall->State2),
        scx::get_mi_value (firewall->State3),
        scx::get_mi_value (firewall->Direction),
        scx::get_mi_value (firewall->SourceHost),
        scx::get_mi_value (firewall->SourcePort),
        scx::get_mi_value (firewall->DestinationHost),
        scx::get_mi_value (firewall->DestinationPort));

    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_RESULT_OK;
    }
    else
    {
        SCX_BOOKEND_PRINT ("Failed - 1");
        res = MI_RESULT_FAILED;
    }

    r = MSFT_nxFirewallResource_SetTargetResource_Construct (&out, context);
    r = MSFT_nxFirewallResource_SetTargetResource_Set_MIReturn (&out, res);
    r = MSFT_nxFirewallResource_SetTargetResource_Post (&out, context);
    r = MSFT_nxFirewallResource_SetTargetResource_Destruct (&out);
    MI_Context_PostResult (context, res);
}


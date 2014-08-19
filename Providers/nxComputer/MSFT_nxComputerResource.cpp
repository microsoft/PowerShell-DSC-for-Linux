/* @migen@ */
#include "python_file_resource.hpp"
#include "python_helper.hpp"
#include "python_scoped_context.hpp"
#include <MI.h>


#include <boost/python.hpp>
#include <cstdlib>
#include "MSFT_nxComputerResource.h"


typedef struct _MSFT_nxComputerResource_Self : public scx::PythonFileResource
{
    /*ctor*/ _MSFT_nxComputerResource_Self (scx::PythonFileResource& base)
      : scx::PythonFileResource (base) {}
} MSFT_nxComputerResource_Self;


void MI_CALL MSFT_nxComputerResource_Load(
    _Outptr_result_maybenull_ MSFT_nxComputerResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Load", " name=\"nxComputer\"");
    MI_UNREFERENCED_PARAMETER (selfModule);
    MI_Result res = MI_RESULT_OK;
    if (0 != self &&
        EXIT_SUCCESS != scx::PythonFileResource::create (self, "nxComputer"))
    {
        res = MI_RESULT_FAILED;
    }
    MI_Context_PostResult (context, res);
}

void MI_CALL MSFT_nxComputerResource_Unload(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context)
{
    SCX_BOOKEND_EX ("Unload", " name=\"nxComputer\"");
    if (self)
    {
        delete self;
    }
    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxComputerResource_EnumerateInstances(
    _In_opt_ MSFT_nxComputerResource_Self* self,
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

void MI_CALL MSFT_nxComputerResource_GetInstance(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxComputerResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxComputerResource_CreateInstance(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxComputerResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxComputerResource_ModifyInstance(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxComputerResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxComputerResource_DeleteInstance(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxComputerResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_nxComputerResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxComputerResource* instanceName,
    _In_opt_ const MSFT_nxComputerResource_GetTargetResource* in)
{
    SCX_BOOKEND_EX ("Get", " name=\"nxComputer\"");
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxComputerResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxComputerResource_GetTargetResource_Construct (&out, context);
    r = MSFT_nxComputerResource_GetTargetResource_Set_MIReturn (&out, 0);

    const MSFT_nxComputerResource * computer = in->InputResource.value;
    r = MI_Instance_Clone (&computer->__instance, &newInstance);

    boost::python::object retVals;

	std::cerr << "Invoking GET" << std::endl;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getGetFn (),
        scx::get_mi_value (computer->Name),
        scx::get_mi_value (computer->DNSDomainName),
        scx::get_mi_value (computer->TimeZoneName),
        scx::get_mi_value (computer->AlternateTimeZoneName));
    std::cerr << "GET completed" << std::endl;
    
    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals) &&
        (1 + 4) == boost::python::len (retVals))
    {
         std::cerr << "Proper number of values returned" << std::endl;
        res = MI_TRUE;
    }
    else
    {
         std::cerr << "ERROR: Improper number of values returned" << std::endl;
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    if (EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "Name", retVals[1]))
    {
         std::cerr << "ERROR: trying to parse string 1, NAME, on return failed" << std::endl;
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }
 
    if (    EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "DNSDomainName", retVals[2]))

    {
         std::cerr << "ERROR: trying to parse string 2, DNSDomainName, on return failed" << std::endl;
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    if (    EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "TimeZoneName", retVals[3]))
    {
         std::cerr << "ERROR: trying to parse string 3, TimeZoneName, on return failed" << std::endl;
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    if (    EXIT_SUCCESS != scx::set_mi_string (
            newInstance, "AlternateTimeZoneName", retVals[4]))
    {
         std::cerr << "ERROR: trying to parse string 4, AlternateTimeZoneName, on return failed" << std::endl;
        MI_Context_PostResult (context, MI_RESULT_FAILED);
        return;
    }

    value.instance = newInstance;
    r = MI_Instance_SetElement (
        &out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if ( r != MI_RESULT_OK )
    {
         std::cerr << "ERROR: SetElement failed" << std::endl;
        MI_Context_PostResult (context, r);
        return;
    }

    MI_Instance_Delete (newInstance);
    r = MSFT_nxComputerResource_GetTargetResource_Post (&out, context);
    if ( r != MI_RESULT_OK )
    {
         std::cerr << "ERROR: Post failed" << std::endl;
        MI_Context_PostResult (context, r);
        return;
    }

    r = MSFT_nxComputerResource_GetTargetResource_Destruct (&out);
    if ( r != MI_RESULT_OK )
    {
         std::cerr << "ERROR: Destruct failed" << std::endl;
        MI_Context_PostResult (context, r);
        return;
    }

         std::cerr << "GET Posting MI_RESULT_OK" << std::endl;
    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxComputerResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxComputerResource* instanceName,
    _In_opt_ const MSFT_nxComputerResource_TestTargetResource* in)
{
    SCX_BOOKEND_EX ("Test", " name=\"nxComputer\"");
    if (!self)
    {
        MI_Context_PostResult (context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxComputerResource_TestTargetResource out;
    const MSFT_nxComputerResource * computer = in->InputResource.value;

    boost::python::object retVals;

    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getTestFn (),
        scx::get_mi_value (computer->Name),
        scx::get_mi_value (computer->DNSDomainName),
        scx::get_mi_value (computer->TimeZoneName),
        scx::get_mi_value (computer->AlternateTimeZoneName));

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

    r = MSFT_nxComputerResource_TestTargetResource_Construct (&out, context);
    r = MSFT_nxComputerResource_TestTargetResource_Set_Result (&out, res);
    r = MSFT_nxComputerResource_TestTargetResource_Set_MIReturn (&out, 0);
    r = MSFT_nxComputerResource_TestTargetResource_Post (&out, context);
    r = MSFT_nxComputerResource_TestTargetResource_Destruct (&out);
    MI_Context_PostResult (context, MI_RESULT_OK);
}

void MI_CALL MSFT_nxComputerResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxComputerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxComputerResource* instanceName,
    _In_opt_ const MSFT_nxComputerResource_SetTargetResource* in)
{
    SCX_BOOKEND_EX ("Set", " name=\"nxComputer\"");
    if (!self)
    {
        MI_Context_PostResult (context, MI_RESULT_OK);
        return;
    }
    scx::PythonScopedContext lock (self->getThreadState ());
    MI_Result r = MI_RESULT_OK;
    MSFT_nxComputerResource_SetTargetResource out;
    const MSFT_nxComputerResource * computer = in->InputResource.value;
    MI_Result res = MI_RESULT_OK;

    boost::python::object retVals;
    int exitCode = scx::invoke_python_function (
        &retVals,
        self->getSetFn (),
        scx::get_mi_value (computer->Name),
        scx::get_mi_value (computer->DNSDomainName),
        scx::get_mi_value (computer->TimeZoneName),
        scx::get_mi_value (computer->AlternateTimeZoneName));

    if (EXIT_SUCCESS == scx::did_function_succeed (exitCode, retVals))
    {
        res = MI_RESULT_OK;
    }
    else
    {
        SCX_BOOKEND_PRINT ("Failed - 1");
        res = MI_RESULT_FAILED;
    }

    r = MSFT_nxComputerResource_SetTargetResource_Construct (&out, context);
    r = MSFT_nxComputerResource_SetTargetResource_Set_MIReturn (&out, res);
    r = MSFT_nxComputerResource_SetTargetResource_Post (&out, context);
    r = MSFT_nxComputerResource_SetTargetResource_Destruct (&out);
    MI_Context_PostResult (context, res);
}


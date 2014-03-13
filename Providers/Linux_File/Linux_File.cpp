/* @migen@ */
#include <MI.h>
#include "Linux_File.h"
#include "PythonHelper.hpp"

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <stdlib.h>
#include <stdarg.h>
#include <ctime>
#include <iostream>


struct _Linux_File_Self
{
public:
    PyObjPtr pModule;
    PyObjPtr pSetFn;
    PyObjPtr pTestFn;
    PyObjPtr pGetFn;

    static int create (_Linux_File_Self** const ppInstance);

private:
    /*ctor*/ _Linux_File_Self (
        PyObjPtr const& _pModule,
        PyObjPtr const& _pSetFn,
        PyObjPtr const& _pTestFn,
        PyObjPtr const& _pGetFn)
      : pModule (_pModule)
      , pSetFn (_pSetFn)
      , pTestFn (_pTestFn)
      , pGetFn (_pGetFn)
    {
        // empty
    }

};

typedef _Linux_File_Self Linux_File_Self;



/*static*/
int
_Linux_File_Self::create (
    _Linux_File_Self** const ppInstance)
{
    int rval = EXIT_SUCCESS;
    PyObjPtr pModule;
    PyObjPtr pSetFn;
    PyObjPtr pTestFn;
    PyObjPtr pGetFn;
    if (ppInstance &&
        !*ppInstance)
    {
        if (EXIT_SUCCESS == (rval = initPython ("do'h", "/home/johnkord/dev/sandbox/dsc_providers/Linux_File")))
        {
            pModule = loadModule ("File");
            if (pModule)
            {
                pSetFn = loadFunctionFromModule (pModule, "Set_Marshall");
                pTestFn = loadFunctionFromModule (pModule, "Test_Marshall");
                pGetFn = loadFunctionFromModule (pModule, "Get_Marshall");
                if (pSetFn && pTestFn && pGetFn)
                {
                    *ppInstance = new _Linux_File_Self (
                        pModule, pSetFn, pTestFn, pGetFn);
                }
                else
                {
                    rval = EXIT_FAILURE;
                }
            }
            else
            {
                rval = EXIT_FAILURE;
            }
        }
        else
        {
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}

static const MI_Char* PassString(const MI_ConstStringField& field)
{
    if (field.exists == MI_TRUE)
    {
        return field.value;
    }
    else
    {
        return (const MI_Char*)"";
    }
}

void MI_CALL Linux_File_Load(
    _Outptr_result_maybenull_ Linux_File_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);
    MI_Result res = MI_RESULT_OK;
    if (EXIT_SUCCESS != Linux_File_Self::create (self))
    {
        res = MI_RESULT_FAILED;
    
    }


    MI_Context_PostResult(context, res);
}

void MI_CALL Linux_File_Unload(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context)
{
    if (self)
    {
        delete self;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Linux_File_EnumerateInstances(
    _In_opt_ Linux_File_Self* self,
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

void MI_CALL Linux_File_GetInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Linux_File_CreateInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Linux_File_ModifyInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Linux_File_DeleteInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

int SetElement(
    MI_Instance* newInstance, 
    char const * field,
    std::string& newFieldVal,
    MI_Type type)
{
    MI_Value value;
    MI_Result r;

    if (type == MI_STRING)
    {
        value.string = (MI_Char*)newFieldVal.c_str();
        r = MI_Instance_SetElement(newInstance, field, &value, MI_STRING, 0);
        if ( r != MI_RESULT_OK )
        {
            return -1;
        }
    }
    else if (type == MI_DATETIME)
    {
        time_t time_in_seconds = atol(newFieldVal.c_str());
        struct tm* time_in_tm = localtime(&time_in_seconds);
        value.datetime.u.timestamp.year = time_in_tm->tm_year+1900;
        value.datetime.u.timestamp.month = time_in_tm->tm_mon+1;
        value.datetime.u.timestamp.day = time_in_tm->tm_mday;
        value.datetime.u.timestamp.hour = time_in_tm->tm_hour;
        value.datetime.u.timestamp.minute = time_in_tm->tm_min;
        value.datetime.u.timestamp.second = time_in_tm->tm_sec;
        value.datetime.u.timestamp.utc = -8*60;
        r = MI_Instance_SetElement(newInstance, field, &value, MI_DATETIME, 0);
        if ( r != MI_RESULT_OK )
        {
            return -1;
        }
    }
    return 0;
}

void MI_CALL Linux_File_Invoke_GetTargetResource(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Linux_File* instanceName,
    _In_opt_ const Linux_File_GetTargetResource* in)
{

    std::cout << "Get" << std::endl;

    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    Linux_File_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = Linux_File_GetTargetResource_Construct(&out, context);
    r = Linux_File_GetTargetResource_Set_MIReturn(&out, 0);

    const Linux_File * file = in->InputResource.value;
    r = MI_Instance_Clone(&file->__instance, &newInstance);


    std::vector<std::string> ret_strings;
    long exit_code = callPythonFunction(
        ret_strings,
        self->pGetFn,
        12,
        PassString(file->DestinationPath),
        PassString(file->SourcePath),
        PassString(file->Ensure),
        PassString(file->Type),
        PassString(file->Force),
        PassString(file->Contents),
        PassString(file->Checksum),
        PassString(file->Recurse),
        PassString(file->Links),
        PassString(file->Owner),
        PassString(file->Group),
        PassString(file->Mode));
    
    // 12+2 represents: the 12 normal fields, the 2 'read' fields
    if (ret_strings.size() == (12+2) && exit_code == 0)
    {
        res = MI_TRUE;
    }
    else
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }

    if (SetElement(newInstance, "DestinationPath", ret_strings[0], MI_STRING)  != 0 ||
        SetElement(newInstance, "SourcePath", ret_strings[1], MI_STRING)       != 0 ||
        SetElement(newInstance, "Ensure", ret_strings[2], MI_STRING)           != 0 ||
        SetElement(newInstance, "Type", ret_strings[3], MI_STRING)             != 0 ||
        SetElement(newInstance, "Force", ret_strings[4], MI_STRING)            != 0 ||
        SetElement(newInstance, "Contents", ret_strings[5], MI_STRING)         != 0 ||
        SetElement(newInstance, "Checksum", ret_strings[6], MI_STRING)         != 0 ||
        SetElement(newInstance, "Recurse", ret_strings[7], MI_STRING)          != 0 ||
        SetElement(newInstance, "Links", ret_strings[8], MI_STRING)            != 0 ||
        SetElement(newInstance, "Owner", ret_strings[9], MI_STRING)            != 0 ||
        SetElement(newInstance, "Group", ret_strings[10], MI_STRING)           != 0 ||
        SetElement(newInstance, "Mode", ret_strings[11], MI_STRING)            != 0 ||
        SetElement(newInstance, "CreatedDate", ret_strings[12], MI_DATETIME)   != 0 ||
        SetElement(newInstance, "ModifiedDate", ret_strings[13], MI_DATETIME)  != 0)
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }

    value.instance = newInstance;
    r = MI_Instance_SetElement(&out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    MI_Instance_Delete(newInstance);
    r = Linux_File_GetTargetResource_Post(&out, context);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    r = Linux_File_GetTargetResource_Destruct(&out);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Linux_File_Invoke_TestTargetResource(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Linux_File* instanceName,
    _In_opt_ const Linux_File_TestTargetResource* in)
{
    std::cout << "Test" << std::endl;

    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }

    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    Linux_File_TestTargetResource out;
    const Linux_File * file = in->InputResource.value;

    std::vector<std::string> ret_strings;
    long exit_code = callPythonFunction(
        ret_strings,
        self->pTestFn,
        12,
        PassString(file->DestinationPath),
        PassString(file->SourcePath),
        PassString(file->Ensure),
        PassString(file->Type),
        PassString(file->Force),
        PassString(file->Contents),
        PassString(file->Checksum),
        PassString(file->Recurse),
        PassString(file->Links),
        PassString(file->Owner),
        PassString(file->Group),
        PassString(file->Mode));

    if (ret_strings.size() == 0 && exit_code == 0)
    {
        res = MI_TRUE;
    }
    else
    {
        res = MI_FALSE;
    }

    r = Linux_File_TestTargetResource_Construct(&out, context);
    r = Linux_File_TestTargetResource_Set_Result(&out, res);
    r = Linux_File_TestTargetResource_Set_MIReturn(&out, 0);
    r = Linux_File_TestTargetResource_Post(&out, context);
    r = Linux_File_TestTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Linux_File_Invoke_SetTargetResource(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Linux_File* instanceName,
    _In_opt_ const Linux_File_SetTargetResource* in)
{
    std::cout << "Set" << std::endl;

    if (!self)
    {
        MI_Context_PostResult(context, MI_RESULT_OK);
        return;
    }

    MI_Result r = MI_RESULT_OK;
    Linux_File_SetTargetResource out;
    const Linux_File * file = in->InputResource.value;
    MI_Result res = MI_RESULT_OK;

    std::vector<std::string> ret_strings;
    long exit_code = callPythonFunction(
        ret_strings,
        self->pSetFn,
        12,
        PassString(file->DestinationPath),
        PassString(file->SourcePath),
        PassString(file->Ensure),
        PassString(file->Type),
        PassString(file->Force),
        PassString(file->Contents),
        PassString(file->Checksum),
        PassString(file->Recurse),
        PassString(file->Links),
        PassString(file->Owner),
        PassString(file->Group),
        PassString(file->Mode));

    if (ret_strings.size() == 0 && exit_code == 0)
    {
        res = MI_RESULT_OK;
    }
    else
    {
        res = MI_RESULT_FAILED;
    }

    r = Linux_File_SetTargetResource_Construct(&out, context);
    r = Linux_File_SetTargetResource_Set_MIReturn(&out, res);
    r = Linux_File_SetTargetResource_Post(&out, context);
    r = Linux_File_SetTargetResource_Destruct(&out);
    MI_Context_PostResult(context, res);
}


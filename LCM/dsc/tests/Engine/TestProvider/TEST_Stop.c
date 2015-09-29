/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/* @migen@ */
#include <MI.h>
#if defined(_MSC_VER)
#include <windows.h>
#endif
#include "TEST_Stop.h"
//#include "winnt.h"
//#include "synchapi.h"

void MI_CALL TEST_Stop_Load(
    _Outptr_result_maybenull_ TEST_Stop_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Stop_Unload(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Stop_EnumerateInstances(
    _In_opt_ TEST_Stop_Self* self,
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

void MI_CALL TEST_Stop_GetInstance(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Stop* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Stop_CreateInstance(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Stop* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Stop_ModifyInstance(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Stop* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Stop_DeleteInstance(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Stop* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Stop_Invoke_GetTargetResource(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Stop* instanceName,
    _In_opt_ const TEST_Stop_GetTargetResource* in)
{
        TEST_Stop_GetTargetResource out;
        MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    TEST_Stop_GetTargetResource_Construct(&out, context);
    MI_Context_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Executing Get for Class TEST_Stop"));
    TEST_Stop_GetTargetResource_Set_OutputResource(&out,in->InputResource.value);
    TEST_Stop_GetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Stop_GetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Stop_Invoke_TestTargetResource(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Stop* instanceName,
    _In_opt_ const TEST_Stop_TestTargetResource* in)
{
    TEST_Stop_TestTargetResource out;    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);
    TEST_Stop_TestTargetResource_Construct(&out, context);
    TEST_Stop_TestTargetResource_Set_Result(&out,MI_FALSE);
    TEST_Stop_TestTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Stop_TestTargetResource_Destruct(&out);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Stop_Invoke_SetTargetResource(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Stop* instanceName,
    _In_opt_ const TEST_Stop_SetTargetResource* in)
{
    TEST_Stop_SetTargetResource out; 

    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    TEST_Stop_SetTargetResource_Construct(&out, context);    
    MI_Context_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Executing Set for Class TEST_Stop"));    
    TEST_Stop_SetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Stop_SetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);
}


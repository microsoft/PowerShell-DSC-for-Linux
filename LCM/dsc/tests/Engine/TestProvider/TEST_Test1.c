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
#include "TEST_Test1.h"

void MI_CALL TEST_Test1_Load(
    _Outptr_result_maybenull_ TEST_Test1_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Test1_Unload(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Test1_EnumerateInstances(
    _In_opt_ TEST_Test1_Self* self,
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

void MI_CALL TEST_Test1_GetInstance(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test1* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test1_CreateInstance(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test1* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test1_ModifyInstance(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test1* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test1_DeleteInstance(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test1* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TEST_Test1_Invoke_GetTargetResource(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test1* instanceName,
    _In_opt_ const TEST_Test1_GetTargetResource* in)
{
    TEST_Test1_GetTargetResource out;    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);
    TEST_Test1_GetTargetResource_Construct(&out, context);
    MI_Context_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Executing Get for Class TEST_Test1"));
    TEST_Test1_GetTargetResource_Set_OutputResource(&out,in->InputResource.value);
    TEST_Test1_GetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Test1_GetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Test1_Invoke_TestTargetResource(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test1* instanceName,
    _In_opt_ const TEST_Test1_TestTargetResource* in)
{
    TEST_Test1_TestTargetResource out;    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);
    TEST_Test1_TestTargetResource_Construct(&out, context);
    MI_Context_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Executing Testt for Class TEST_Test1"));    
    TEST_Test1_TestTargetResource_Set_Result(&out,MI_FALSE);
    TEST_Test1_TestTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Test1_TestTargetResource_Destruct(&out);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TEST_Test1_Invoke_SetTargetResource(
    _In_opt_ TEST_Test1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test1* instanceName,
    _In_opt_ const TEST_Test1_SetTargetResource* in)
{
    TEST_Test1_SetTargetResource out;    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);
    TEST_Test1_SetTargetResource_Construct(&out, context);
    MI_Context_WriteProgress(context, MI_T("Test_Test1"), MI_T("Set"), MI_T("Performing Set"), 50, 1);
    MI_Context_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Executing Set for Class TEST_Test1"));    
    MI_Context_WriteProgress(context, MI_T("Test_Test1"), MI_T("Set"), MI_T("Performing Set"), 100, 0);    
    TEST_Test1_SetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Test1_SetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);
}



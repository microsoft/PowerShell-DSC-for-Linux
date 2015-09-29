/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "MSFT_FileDirectoryConfiguration.h"
#include "FileImp.h"
#include "pal/file.h"
#include "nits.h"

int FileExist(_In_z_ const char *path)
{
    FILE *fp = fopen(path, "r");
    if( !fp )
        return -1;
     fclose(fp);
     return 0;
}
void Invoke_GetTargetResource(_In_ MI_Context* context,_In_opt_ MI_CONST MSFT_FileDirectoryConfiguration* in )
{
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    MSFT_FileDirectoryConfiguration_GetTargetResource out;
    MI_Instance *newInstance;
    const char *ensure_Present = "Present";
    const char *ensure_Absent = "Absent";
    if( !in->DestinationPath.exists || in->DestinationPath.value == NULL)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
    r = MSFT_FileDirectoryConfiguration_GetTargetResource_Construct(&out, context);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    r = MSFT_FileDirectoryConfiguration_GetTargetResource_Set_MIReturn(&out , 0);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    r = MI_Instance_Clone(&in->__instance, &newInstance);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }       
    if(FileExist(in->DestinationPath.value) == 0 )
    {
        value.string = (char*) ensure_Present;
    }
    else
    {
        value.string = (char*) ensure_Absent;
    }
    r = MI_Instance_SetElement(newInstance, "Ensure", &value, MI_STRING, 0);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    value.instance = newInstance;
    r = MI_Instance_SetElement(&out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    MI_Instance_Delete(newInstance);
    r = MSFT_FileDirectoryConfiguration_GetTargetResource_Post(&out,context);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    MSFT_FileDirectoryConfiguration_GetTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);
}
void Invoke_SetTargetResource(_In_ MI_Context* context,_In_opt_ MI_CONST MSFT_FileDirectoryConfiguration* in )
{
    FILE *fp;
    MI_Result r = MI_RESULT_OK;
    size_t result;
    MSFT_FileDirectoryConfiguration_SetTargetResource out;
    if( !in->DestinationPath.exists || !in->Contents.exists || in->DestinationPath.value == NULL)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }    
    fp = File_Open(in->DestinationPath.value, "w");
    result = fwrite(in->Contents.value,1, strlen(in->Contents.value), fp);
    File_Close(fp);    
    if( result != strlen(in->Contents.value))
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }
    r = MSFT_FileDirectoryConfiguration_SetTargetResource_Construct(&out, context);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    r = MSFT_FileDirectoryConfiguration_SetTargetResource_Set_MIReturn(&out, 0);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    r = MSFT_FileDirectoryConfiguration_SetTargetResource_Post(&out, context);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    MSFT_FileDirectoryConfiguration_SetTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);

}
void Invoke_TestTargetResource(_In_ MI_Context* context,_In_opt_ MI_CONST MSFT_FileDirectoryConfiguration* in )
{
    MI_Result r = MI_RESULT_OK;
    MI_Boolean testResult = MI_FALSE;
    MSFT_FileDirectoryConfiguration_TestTargetResource out;
    if( !in->DestinationPath.exists || !in->Contents.exists ||in->DestinationPath.value == NULL)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }    
    r = MSFT_FileDirectoryConfiguration_TestTargetResource_Construct(&out, context);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }
    if(FileExist(in->DestinationPath.value) == 0 )
    {
        // TODO: check its contents
        testResult = MI_TRUE;
    }
    r = MSFT_FileDirectoryConfiguration_TestTargetResource_Set_Result(&out, testResult);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    r = MSFT_FileDirectoryConfiguration_TestTargetResource_Set_MIReturn(&out, 0);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    r = MSFT_FileDirectoryConfiguration_TestTargetResource_Post(&out, context);
    if( r != MI_RESULT_OK)
    {
        MI_Context_PostResult(context, r);
        return;
    }    
    MSFT_FileDirectoryConfiguration_TestTargetResource_Destruct(&out);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

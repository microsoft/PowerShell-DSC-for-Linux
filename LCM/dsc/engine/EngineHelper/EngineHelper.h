/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __ENGINEHELPER_H_
#define __ENGINEHELPER_H_

#include <pal/strings.h>
#include <pal/sem.h>
#include <pal/thread.h>
#include <pal/lock.h>
#include <pal/memory.h>
#include <pal/math.h>
#include <pal/file.h>
#include <pal/atomic.h>
#include <pal/format.h>
#include <pal/cpu.h>
#include <pal/sleep.h>
#include <pal/intlstr.h>
#include <pal/alloc.h>

#include "EngineHelperInternal.h"
#include "PAL_Extension.h"

#include "parson.h"

typedef struct _Loc_Mapping
{
    MI_Uint32 locId;
    Intlstr (*LocFunctionZeroArgs)() ;
    Intlstr (*LocFunctionOneArgs)(MI_Char *) ;
    Intlstr (*LocFunctionTwoArgs)(MI_Char *, MI_Char *) ;
    Intlstr (*LocFunctionThreeArgs)(MI_Char *, MI_Char *, MI_Char *) ;
    Intlstr (*LocFunctionFourArgs)(MI_Char *, MI_Char *, MI_Char *, MI_Char *) ;    

} Loc_Mapping;

void GetResourceString1Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1, _Inout_ Intlstr *resStr);
void GetResourceString2Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1,
                               _In_z_ const MI_Char * param2,_Inout_ Intlstr *resStr);
void GetResourceString3Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1,
              _In_z_ const MI_Char * param2, _In_z_ const MI_Char * param3,_Inout_ Intlstr *resStr);

void GetResourceString4Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1, 
               _In_z_ const MI_Char * param2, _In_z_ const MI_Char * param3,  _In_z_ const MI_Char * param4, _Inout_ Intlstr *resStr);

// Helper method for warnings
void DSC_WriteWarningHelper(
	_In_ LCMProviderContext* lcmContext,
	_In_ Intlstr);

//Function to write a warning with message id that requires no parameter
void DSC_WriteWarning(
	_In_ LCMProviderContext* lcmContext,
	_In_ MI_Uint32 messageID);

//Function to write a warning with message iD that requires 1 parameter of type string
void DSC_WriteWarning1Param(_In_ MI_Context* context,
    _In_ MI_Uint32 messageID,
    _In_z_ MI_Char* param1);


void DSC_WriteWarning2Param(_In_ MI_Context* context,
    _In_ MI_Uint32 messageID,
    _In_z_ MI_Char* param1,
    _In_z_ MI_Char* param2);

//Function to write a warning from the message trapped in an error.
void DSC_WriteWarningFromError1Param(_In_ MI_Context* context,
    _In_ MI_Instance ** cimErrorDetails,
    _In_ MI_Uint32 messageID,
    _In_z_ MI_Char* param1);

MI_Result  Convert_MIInstance_JSON (
        const MI_Instance* p_instance,
        JSON_Value** p_result_root_value
    );

MI_Result  Convert_MiClass_JSON (
        const MI_Class* p_instance,
        JSON_Value** p_result_root_value
    );

MI_Result  Print_JSON_Value (
        JSON_Value** p_root_value
    );

MI_Result  Save_JSON_Value (
        const char* p_file_path,
        JSON_Value** p_root_value
    );

MI_Result  Print_MI_Instance (
        const MI_Instance* p_instance
    );

MI_Result  Print_MI_InstanceA (
        const MI_InstanceA* p_instanceA
    );

MI_Result  Print_MI_Class (
        const MI_Class* p_class
    );

extern BaseResourceConfiguration g_BaseResourceConfiguration[];
extern JobInformation g_JobInformation;

#endif //__ENGINEHELPER_H_

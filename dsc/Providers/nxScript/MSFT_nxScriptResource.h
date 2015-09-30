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
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxScriptResource_h
#define _MSFT_nxScriptResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxScriptResource.h"

/*
**==============================================================================
**
** MSFT_nxScriptResource [MSFT_nxScriptResource]
**
** Keys:
**    GetScript
**    SetScript
**    TestScript
**
**==============================================================================
*/

typedef struct _MSFT_nxScriptResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxScriptResource properties */
    /*KEY*/ MI_ConstStringField GetScript;
    /*KEY*/ MI_ConstStringField SetScript;
    /*KEY*/ MI_ConstStringField TestScript;
    MI_ConstStringField User;
    MI_ConstStringField Group;
    MI_ConstStringField Result;
}
MSFT_nxScriptResource;

typedef struct _MSFT_nxScriptResource_Ref
{
    MSFT_nxScriptResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxScriptResource_Ref;

typedef struct _MSFT_nxScriptResource_ConstRef
{
    MI_CONST MSFT_nxScriptResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxScriptResource_ConstRef;

typedef struct _MSFT_nxScriptResource_Array
{
    struct _MSFT_nxScriptResource** data;
    MI_Uint32 size;
}
MSFT_nxScriptResource_Array;

typedef struct _MSFT_nxScriptResource_ConstArray
{
    struct _MSFT_nxScriptResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxScriptResource_ConstArray;

typedef struct _MSFT_nxScriptResource_ArrayRef
{
    MSFT_nxScriptResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxScriptResource_ArrayRef;

typedef struct _MSFT_nxScriptResource_ConstArrayRef
{
    MSFT_nxScriptResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxScriptResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxScriptResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Construct(
    _Out_ MSFT_nxScriptResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxScriptResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Clone(
    _In_ const MSFT_nxScriptResource* self,
    _Outptr_ MSFT_nxScriptResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxScriptResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxScriptResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Destruct(_Inout_ MSFT_nxScriptResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Delete(_Inout_ MSFT_nxScriptResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Post(
    _In_ const MSFT_nxScriptResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Set_GetScript(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetPtr_GetScript(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Clear_GetScript(
    _Inout_ MSFT_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Set_SetScript(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetPtr_SetScript(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Clear_SetScript(
    _Inout_ MSFT_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Set_TestScript(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetPtr_TestScript(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Clear_TestScript(
    _Inout_ MSFT_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Set_User(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetPtr_User(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Clear_User(
    _Inout_ MSFT_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Set_Group(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetPtr_Group(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Clear_Group(
    _Inout_ MSFT_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Set_Result(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetPtr_Result(
    _Inout_ MSFT_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_Clear_Result(
    _Inout_ MSFT_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** MSFT_nxScriptResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxScriptResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxScriptResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxScriptResource_ConstRef OutputResource;
}
MSFT_nxScriptResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxScriptResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Construct(
    _Out_ MSFT_nxScriptResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxScriptResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Clone(
    _In_ const MSFT_nxScriptResource_GetTargetResource* self,
    _Outptr_ MSFT_nxScriptResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Post(
    _In_ const MSFT_nxScriptResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxScriptResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxScriptResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxScriptResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxScriptResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxScriptResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxScriptResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Construct(
    _Out_ MSFT_nxScriptResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxScriptResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Clone(
    _In_ const MSFT_nxScriptResource_TestTargetResource* self,
    _Outptr_ MSFT_nxScriptResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Post(
    _In_ const MSFT_nxScriptResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxScriptResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxScriptResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxScriptResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxScriptResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxScriptResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Construct(
    _Out_ MSFT_nxScriptResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxScriptResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Clone(
    _In_ const MSFT_nxScriptResource_SetTargetResource* self,
    _Outptr_ MSFT_nxScriptResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Post(
    _In_ const MSFT_nxScriptResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self,
    _In_ const MSFT_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxScriptResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxScriptResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxScriptResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxScriptResource_Self MSFT_nxScriptResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_Load(
    _Outptr_result_maybenull_ MSFT_nxScriptResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_Unload(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_EnumerateInstances(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_GetInstance(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxScriptResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_CreateInstance(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxScriptResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_ModifyInstance(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxScriptResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_DeleteInstance(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxScriptResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxScriptResource* instanceName,
    _In_opt_ const MSFT_nxScriptResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxScriptResource* instanceName,
    _In_opt_ const MSFT_nxScriptResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxScriptResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxScriptResource* instanceName,
    _In_opt_ const MSFT_nxScriptResource_SetTargetResource* in);


#endif /* _MSFT_nxScriptResource_h */

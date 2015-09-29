/* @migen@ */
/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _MSFT_nxMySqlUserResource_h
#define _MSFT_nxMySqlUserResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxMySqlUserResource.h"

/*
**==============================================================================
**
** MSFT_nxMySqlUserResource [MSFT_nxMySqlUserResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlUserResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxMySqlUserResource properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Credential;
    MI_ConstStringField ConnectionCredential;
    MI_ConstStringField Ensure;
}
MSFT_nxMySqlUserResource;

typedef struct _MSFT_nxMySqlUserResource_Ref
{
    MSFT_nxMySqlUserResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlUserResource_Ref;

typedef struct _MSFT_nxMySqlUserResource_ConstRef
{
    MI_CONST MSFT_nxMySqlUserResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlUserResource_ConstRef;

typedef struct _MSFT_nxMySqlUserResource_Array
{
    struct _MSFT_nxMySqlUserResource** data;
    MI_Uint32 size;
}
MSFT_nxMySqlUserResource_Array;

typedef struct _MSFT_nxMySqlUserResource_ConstArray
{
    struct _MSFT_nxMySqlUserResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxMySqlUserResource_ConstArray;

typedef struct _MSFT_nxMySqlUserResource_ArrayRef
{
    MSFT_nxMySqlUserResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlUserResource_ArrayRef;

typedef struct _MSFT_nxMySqlUserResource_ConstArrayRef
{
    MSFT_nxMySqlUserResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlUserResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxMySqlUserResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Construct(
    _Out_ MSFT_nxMySqlUserResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxMySqlUserResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Clone(
    _In_ const MSFT_nxMySqlUserResource* self,
    _Outptr_ MSFT_nxMySqlUserResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxMySqlUserResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxMySqlUserResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Destruct(_Inout_ MSFT_nxMySqlUserResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Delete(_Inout_ MSFT_nxMySqlUserResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Post(
    _In_ const MSFT_nxMySqlUserResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Set_Name(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetPtr_Name(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Clear_Name(
    _Inout_ MSFT_nxMySqlUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Set_Credential(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetPtr_Credential(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Clear_Credential(
    _Inout_ MSFT_nxMySqlUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Set_ConnectionCredential(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetPtr_ConnectionCredential(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Clear_ConnectionCredential(
    _Inout_ MSFT_nxMySqlUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Set_Ensure(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetPtr_Ensure(
    _Inout_ MSFT_nxMySqlUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_Clear_Ensure(
    _Inout_ MSFT_nxMySqlUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxMySqlUserResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlUserResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlUserResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxMySqlUserResource_ConstRef OutputResource;
}
MSFT_nxMySqlUserResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlUserResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Construct(
    _Out_ MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlUserResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Clone(
    _In_ const MSFT_nxMySqlUserResource_GetTargetResource* self,
    _Outptr_ MSFT_nxMySqlUserResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Post(
    _In_ const MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxMySqlUserResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxMySqlUserResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlUserResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlUserResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxMySqlUserResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlUserResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Construct(
    _Out_ MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlUserResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Clone(
    _In_ const MSFT_nxMySqlUserResource_TestTargetResource* self,
    _Outptr_ MSFT_nxMySqlUserResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Post(
    _In_ const MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxMySqlUserResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxMySqlUserResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlUserResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlUserResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxMySqlUserResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlUserResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Construct(
    _Out_ MSFT_nxMySqlUserResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlUserResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Clone(
    _In_ const MSFT_nxMySqlUserResource_SetTargetResource* self,
    _Outptr_ MSFT_nxMySqlUserResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Post(
    _In_ const MSFT_nxMySqlUserResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self,
    _In_ const MSFT_nxMySqlUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlUserResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlUserResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxMySqlUserResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxMySqlUserResource_Self MSFT_nxMySqlUserResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_Load(
    _Outptr_result_maybenull_ MSFT_nxMySqlUserResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_Unload(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_EnumerateInstances(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_GetInstance(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlUserResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_CreateInstance(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlUserResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_ModifyInstance(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlUserResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_DeleteInstance(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlUserResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlUserResource* instanceName,
    _In_opt_ const MSFT_nxMySqlUserResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlUserResource* instanceName,
    _In_opt_ const MSFT_nxMySqlUserResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlUserResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxMySqlUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlUserResource* instanceName,
    _In_opt_ const MSFT_nxMySqlUserResource_SetTargetResource* in);


#endif /* _MSFT_nxMySqlUserResource_h */

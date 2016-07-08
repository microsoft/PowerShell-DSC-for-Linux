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
#ifndef _MSFT_nxSshAuthorizedKeysResource_h
#define _MSFT_nxSshAuthorizedKeysResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxSshAuthorizedKeysResource.h"

/*
**==============================================================================
**
** MSFT_nxSshAuthorizedKeysResource [MSFT_nxSshAuthorizedKeysResource]
**
** Keys:
**    KeyComment
**
**==============================================================================
*/

typedef struct _MSFT_nxSshAuthorizedKeysResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxSshAuthorizedKeysResource properties */
    /*KEY*/ MI_ConstStringField KeyComment;
    MI_ConstStringField Ensure;
    MI_ConstStringField UserName;
    MI_ConstStringField Key;
}
MSFT_nxSshAuthorizedKeysResource;

typedef struct _MSFT_nxSshAuthorizedKeysResource_Ref
{
    MSFT_nxSshAuthorizedKeysResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxSshAuthorizedKeysResource_Ref;

typedef struct _MSFT_nxSshAuthorizedKeysResource_ConstRef
{
    MI_CONST MSFT_nxSshAuthorizedKeysResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxSshAuthorizedKeysResource_ConstRef;

typedef struct _MSFT_nxSshAuthorizedKeysResource_Array
{
    struct _MSFT_nxSshAuthorizedKeysResource** data;
    MI_Uint32 size;
}
MSFT_nxSshAuthorizedKeysResource_Array;

typedef struct _MSFT_nxSshAuthorizedKeysResource_ConstArray
{
    struct _MSFT_nxSshAuthorizedKeysResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxSshAuthorizedKeysResource_ConstArray;

typedef struct _MSFT_nxSshAuthorizedKeysResource_ArrayRef
{
    MSFT_nxSshAuthorizedKeysResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxSshAuthorizedKeysResource_ArrayRef;

typedef struct _MSFT_nxSshAuthorizedKeysResource_ConstArrayRef
{
    MSFT_nxSshAuthorizedKeysResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxSshAuthorizedKeysResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxSshAuthorizedKeysResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Construct(
    _Out_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxSshAuthorizedKeysResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Clone(
    _In_ const MSFT_nxSshAuthorizedKeysResource* self,
    _Outptr_ MSFT_nxSshAuthorizedKeysResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxSshAuthorizedKeysResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxSshAuthorizedKeysResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Destruct(_Inout_ MSFT_nxSshAuthorizedKeysResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Delete(_Inout_ MSFT_nxSshAuthorizedKeysResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Post(
    _In_ const MSFT_nxSshAuthorizedKeysResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Set_KeyComment(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetPtr_KeyComment(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Clear_KeyComment(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Set_Ensure(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetPtr_Ensure(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Clear_Ensure(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Set_UserName(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetPtr_UserName(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Clear_UserName(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Set_Key(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetPtr_Key(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_Clear_Key(
    _Inout_ MSFT_nxSshAuthorizedKeysResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxSshAuthorizedKeysResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxSshAuthorizedKeysResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxSshAuthorizedKeysResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxSshAuthorizedKeysResource_ConstRef OutputResource;
}
MSFT_nxSshAuthorizedKeysResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxSshAuthorizedKeysResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Construct(
    _Out_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxSshAuthorizedKeysResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Clone(
    _In_ const MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _Outptr_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Post(
    _In_ const MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxSshAuthorizedKeysResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxSshAuthorizedKeysResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxSshAuthorizedKeysResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxSshAuthorizedKeysResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxSshAuthorizedKeysResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Construct(
    _Out_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxSshAuthorizedKeysResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Clone(
    _In_ const MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _Outptr_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Post(
    _In_ const MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxSshAuthorizedKeysResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxSshAuthorizedKeysResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxSshAuthorizedKeysResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxSshAuthorizedKeysResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxSshAuthorizedKeysResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Construct(
    _Out_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxSshAuthorizedKeysResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Clone(
    _In_ const MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _Outptr_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Post(
    _In_ const MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _In_ const MSFT_nxSshAuthorizedKeysResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxSshAuthorizedKeysResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxSshAuthorizedKeysResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxSshAuthorizedKeysResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxSshAuthorizedKeysResource_Self MSFT_nxSshAuthorizedKeysResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_Load(
    _Outptr_result_maybenull_ MSFT_nxSshAuthorizedKeysResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_Unload(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_EnumerateInstances(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_GetInstance(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxSshAuthorizedKeysResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_CreateInstance(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxSshAuthorizedKeysResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_ModifyInstance(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxSshAuthorizedKeysResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_DeleteInstance(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxSshAuthorizedKeysResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxSshAuthorizedKeysResource* instanceName,
    _In_opt_ const MSFT_nxSshAuthorizedKeysResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxSshAuthorizedKeysResource* instanceName,
    _In_opt_ const MSFT_nxSshAuthorizedKeysResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxSshAuthorizedKeysResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxSshAuthorizedKeysResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxSshAuthorizedKeysResource* instanceName,
    _In_opt_ const MSFT_nxSshAuthorizedKeysResource_SetTargetResource* in);


#endif /* _MSFT_nxSshAuthorizedKeysResource_h */

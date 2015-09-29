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
#ifndef _MSFT_nxMySqlGrantResource_h
#define _MSFT_nxMySqlGrantResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxMySqlGrantResource.h"

/*
**==============================================================================
**
** MSFT_nxMySqlGrantResource [MSFT_nxMySqlGrantResource]
**
** Keys:
**    UserName
**    DatabaseName
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlGrantResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxMySqlGrantResource properties */
    /*KEY*/ MI_ConstStringField UserName;
    /*KEY*/ MI_ConstStringField DatabaseName;
    MI_ConstStringField ConnectionCredential;
    MI_ConstStringField PermissionType;
    MI_ConstStringField Ensure;
}
MSFT_nxMySqlGrantResource;

typedef struct _MSFT_nxMySqlGrantResource_Ref
{
    MSFT_nxMySqlGrantResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlGrantResource_Ref;

typedef struct _MSFT_nxMySqlGrantResource_ConstRef
{
    MI_CONST MSFT_nxMySqlGrantResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlGrantResource_ConstRef;

typedef struct _MSFT_nxMySqlGrantResource_Array
{
    struct _MSFT_nxMySqlGrantResource** data;
    MI_Uint32 size;
}
MSFT_nxMySqlGrantResource_Array;

typedef struct _MSFT_nxMySqlGrantResource_ConstArray
{
    struct _MSFT_nxMySqlGrantResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxMySqlGrantResource_ConstArray;

typedef struct _MSFT_nxMySqlGrantResource_ArrayRef
{
    MSFT_nxMySqlGrantResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlGrantResource_ArrayRef;

typedef struct _MSFT_nxMySqlGrantResource_ConstArrayRef
{
    MSFT_nxMySqlGrantResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlGrantResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxMySqlGrantResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Construct(
    _Out_ MSFT_nxMySqlGrantResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxMySqlGrantResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Clone(
    _In_ const MSFT_nxMySqlGrantResource* self,
    _Outptr_ MSFT_nxMySqlGrantResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxMySqlGrantResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxMySqlGrantResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Destruct(_Inout_ MSFT_nxMySqlGrantResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Delete(_Inout_ MSFT_nxMySqlGrantResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Post(
    _In_ const MSFT_nxMySqlGrantResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Set_UserName(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetPtr_UserName(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Clear_UserName(
    _Inout_ MSFT_nxMySqlGrantResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Set_DatabaseName(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetPtr_DatabaseName(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Clear_DatabaseName(
    _Inout_ MSFT_nxMySqlGrantResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Set_ConnectionCredential(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetPtr_ConnectionCredential(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Clear_ConnectionCredential(
    _Inout_ MSFT_nxMySqlGrantResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Set_PermissionType(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetPtr_PermissionType(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Clear_PermissionType(
    _Inout_ MSFT_nxMySqlGrantResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Set_Ensure(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetPtr_Ensure(
    _Inout_ MSFT_nxMySqlGrantResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_Clear_Ensure(
    _Inout_ MSFT_nxMySqlGrantResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MSFT_nxMySqlGrantResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlGrantResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlGrantResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxMySqlGrantResource_ConstRef OutputResource;
}
MSFT_nxMySqlGrantResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlGrantResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Construct(
    _Out_ MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlGrantResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Clone(
    _In_ const MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _Outptr_ MSFT_nxMySqlGrantResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Post(
    _In_ const MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxMySqlGrantResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxMySqlGrantResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlGrantResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlGrantResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxMySqlGrantResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlGrantResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Construct(
    _Out_ MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlGrantResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Clone(
    _In_ const MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _Outptr_ MSFT_nxMySqlGrantResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Post(
    _In_ const MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxMySqlGrantResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxMySqlGrantResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlGrantResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlGrantResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxMySqlGrantResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlGrantResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Construct(
    _Out_ MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlGrantResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Clone(
    _In_ const MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _Outptr_ MSFT_nxMySqlGrantResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Post(
    _In_ const MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _In_ const MSFT_nxMySqlGrantResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlGrantResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlGrantResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxMySqlGrantResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxMySqlGrantResource_Self MSFT_nxMySqlGrantResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_Load(
    _Outptr_result_maybenull_ MSFT_nxMySqlGrantResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_Unload(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_EnumerateInstances(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_GetInstance(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlGrantResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_CreateInstance(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlGrantResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_ModifyInstance(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlGrantResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_DeleteInstance(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlGrantResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlGrantResource* instanceName,
    _In_opt_ const MSFT_nxMySqlGrantResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlGrantResource* instanceName,
    _In_opt_ const MSFT_nxMySqlGrantResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlGrantResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxMySqlGrantResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlGrantResource* instanceName,
    _In_opt_ const MSFT_nxMySqlGrantResource_SetTargetResource* in);


#endif /* _MSFT_nxMySqlGrantResource_h */

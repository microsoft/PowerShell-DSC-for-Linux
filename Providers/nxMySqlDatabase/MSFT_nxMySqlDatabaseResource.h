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
#ifndef _MSFT_nxMySqlDatabaseResource_h
#define _MSFT_nxMySqlDatabaseResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxMySqlDatabaseResource.h"

/*
**==============================================================================
**
** MSFT_nxMySqlDatabaseResource [MSFT_nxMySqlDatabaseResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlDatabaseResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxMySqlDatabaseResource properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Ensure;
    MI_ConstStringField ConnectionCredential;
}
MSFT_nxMySqlDatabaseResource;

typedef struct _MSFT_nxMySqlDatabaseResource_Ref
{
    MSFT_nxMySqlDatabaseResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlDatabaseResource_Ref;

typedef struct _MSFT_nxMySqlDatabaseResource_ConstRef
{
    MI_CONST MSFT_nxMySqlDatabaseResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlDatabaseResource_ConstRef;

typedef struct _MSFT_nxMySqlDatabaseResource_Array
{
    struct _MSFT_nxMySqlDatabaseResource** data;
    MI_Uint32 size;
}
MSFT_nxMySqlDatabaseResource_Array;

typedef struct _MSFT_nxMySqlDatabaseResource_ConstArray
{
    struct _MSFT_nxMySqlDatabaseResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxMySqlDatabaseResource_ConstArray;

typedef struct _MSFT_nxMySqlDatabaseResource_ArrayRef
{
    MSFT_nxMySqlDatabaseResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlDatabaseResource_ArrayRef;

typedef struct _MSFT_nxMySqlDatabaseResource_ConstArrayRef
{
    MSFT_nxMySqlDatabaseResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxMySqlDatabaseResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxMySqlDatabaseResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Construct(
    _Out_ MSFT_nxMySqlDatabaseResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxMySqlDatabaseResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Clone(
    _In_ const MSFT_nxMySqlDatabaseResource* self,
    _Outptr_ MSFT_nxMySqlDatabaseResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxMySqlDatabaseResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxMySqlDatabaseResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Destruct(_Inout_ MSFT_nxMySqlDatabaseResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Delete(_Inout_ MSFT_nxMySqlDatabaseResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Post(
    _In_ const MSFT_nxMySqlDatabaseResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Set_Name(
    _Inout_ MSFT_nxMySqlDatabaseResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetPtr_Name(
    _Inout_ MSFT_nxMySqlDatabaseResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Clear_Name(
    _Inout_ MSFT_nxMySqlDatabaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Set_Ensure(
    _Inout_ MSFT_nxMySqlDatabaseResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetPtr_Ensure(
    _Inout_ MSFT_nxMySqlDatabaseResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Clear_Ensure(
    _Inout_ MSFT_nxMySqlDatabaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Set_ConnectionCredential(
    _Inout_ MSFT_nxMySqlDatabaseResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetPtr_ConnectionCredential(
    _Inout_ MSFT_nxMySqlDatabaseResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_Clear_ConnectionCredential(
    _Inout_ MSFT_nxMySqlDatabaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_nxMySqlDatabaseResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlDatabaseResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlDatabaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxMySqlDatabaseResource_ConstRef OutputResource;
}
MSFT_nxMySqlDatabaseResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlDatabaseResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Construct(
    _Out_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlDatabaseResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Clone(
    _In_ const MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _Outptr_ MSFT_nxMySqlDatabaseResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Post(
    _In_ const MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxMySqlDatabaseResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlDatabaseResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlDatabaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxMySqlDatabaseResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlDatabaseResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Construct(
    _Out_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlDatabaseResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Clone(
    _In_ const MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _Outptr_ MSFT_nxMySqlDatabaseResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Post(
    _In_ const MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxMySqlDatabaseResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxMySqlDatabaseResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxMySqlDatabaseResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxMySqlDatabaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxMySqlDatabaseResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxMySqlDatabaseResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Construct(
    _Out_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxMySqlDatabaseResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Clone(
    _In_ const MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _Outptr_ MSFT_nxMySqlDatabaseResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Post(
    _In_ const MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _In_ const MSFT_nxMySqlDatabaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxMySqlDatabaseResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxMySqlDatabaseResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxMySqlDatabaseResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxMySqlDatabaseResource_Self MSFT_nxMySqlDatabaseResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_Load(
    _Outptr_result_maybenull_ MSFT_nxMySqlDatabaseResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_Unload(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_EnumerateInstances(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_GetInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_CreateInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_ModifyInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_DeleteInstance(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MSFT_nxMySqlDatabaseResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MSFT_nxMySqlDatabaseResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxMySqlDatabaseResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxMySqlDatabaseResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxMySqlDatabaseResource* instanceName,
    _In_opt_ const MSFT_nxMySqlDatabaseResource_SetTargetResource* in);


#endif /* _MSFT_nxMySqlDatabaseResource_h */

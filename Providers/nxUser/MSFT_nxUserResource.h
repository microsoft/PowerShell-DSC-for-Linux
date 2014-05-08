/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxUserResource_h
#define _MSFT_nxUserResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxUserResource.h"

/*
**==============================================================================
**
** MSFT_nxUserResource [MSFT_nxUserResource]
**
** Keys:
**    UserName
**
**==============================================================================
*/

typedef struct _MSFT_nxUserResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxUserResource properties */
    /*KEY*/ MI_ConstStringField UserName;
    MI_ConstStringField Ensure;
    MI_ConstStringField FullName;
    MI_ConstStringField Description;
    MI_ConstStringField Password;
    MI_ConstBooleanField Disabled;
    MI_ConstBooleanField PasswordChangeRequired;
    MI_ConstStringField HomeDirectory;
    MI_ConstStringField GroupID;
}
MSFT_nxUserResource;

typedef struct _MSFT_nxUserResource_Ref
{
    MSFT_nxUserResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxUserResource_Ref;

typedef struct _MSFT_nxUserResource_ConstRef
{
    MI_CONST MSFT_nxUserResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxUserResource_ConstRef;

typedef struct _MSFT_nxUserResource_Array
{
    struct _MSFT_nxUserResource** data;
    MI_Uint32 size;
}
MSFT_nxUserResource_Array;

typedef struct _MSFT_nxUserResource_ConstArray
{
    struct _MSFT_nxUserResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxUserResource_ConstArray;

typedef struct _MSFT_nxUserResource_ArrayRef
{
    MSFT_nxUserResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxUserResource_ArrayRef;

typedef struct _MSFT_nxUserResource_ConstArrayRef
{
    MSFT_nxUserResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxUserResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxUserResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Construct(
    _Out_ MSFT_nxUserResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxUserResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clone(
    _In_ const MSFT_nxUserResource* self,
    _Outptr_ MSFT_nxUserResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxUserResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxUserResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Destruct(_Inout_ MSFT_nxUserResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Delete(_Inout_ MSFT_nxUserResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Post(
    _In_ const MSFT_nxUserResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_UserName(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetPtr_UserName(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_UserName(
    _Inout_ MSFT_nxUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_Ensure(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetPtr_Ensure(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_Ensure(
    _Inout_ MSFT_nxUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_FullName(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetPtr_FullName(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_FullName(
    _Inout_ MSFT_nxUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_Description(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetPtr_Description(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_Description(
    _Inout_ MSFT_nxUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_Password(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetPtr_Password(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_Password(
    _Inout_ MSFT_nxUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_Disabled(
    _Inout_ MSFT_nxUserResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Disabled)->value = x;
    ((MI_BooleanField*)&self->Disabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_Disabled(
    _Inout_ MSFT_nxUserResource* self)
{
    memset((void*)&self->Disabled, 0, sizeof(self->Disabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_PasswordChangeRequired(
    _Inout_ MSFT_nxUserResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->PasswordChangeRequired)->value = x;
    ((MI_BooleanField*)&self->PasswordChangeRequired)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_PasswordChangeRequired(
    _Inout_ MSFT_nxUserResource* self)
{
    memset((void*)&self->PasswordChangeRequired, 0, sizeof(self->PasswordChangeRequired));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_HomeDirectory(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetPtr_HomeDirectory(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_HomeDirectory(
    _Inout_ MSFT_nxUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Set_GroupID(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetPtr_GroupID(
    _Inout_ MSFT_nxUserResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_Clear_GroupID(
    _Inout_ MSFT_nxUserResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** MSFT_nxUserResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxUserResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxUserResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxUserResource_ConstRef OutputResource;
}
MSFT_nxUserResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxUserResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Construct(
    _Out_ MSFT_nxUserResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxUserResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Clone(
    _In_ const MSFT_nxUserResource_GetTargetResource* self,
    _Outptr_ MSFT_nxUserResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Post(
    _In_ const MSFT_nxUserResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxUserResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxUserResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxUserResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxUserResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxUserResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxUserResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Construct(
    _Out_ MSFT_nxUserResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxUserResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Clone(
    _In_ const MSFT_nxUserResource_TestTargetResource* self,
    _Outptr_ MSFT_nxUserResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Post(
    _In_ const MSFT_nxUserResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxUserResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxUserResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxUserResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxUserResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxUserResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxUserResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Construct(
    _Out_ MSFT_nxUserResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxUserResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Clone(
    _In_ const MSFT_nxUserResource_SetTargetResource* self,
    _Outptr_ MSFT_nxUserResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Post(
    _In_ const MSFT_nxUserResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self,
    _In_ const MSFT_nxUserResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxUserResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxUserResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxUserResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxUserResource_Self MSFT_nxUserResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_Load(
    _Outptr_result_maybenull_ MSFT_nxUserResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_Unload(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_EnumerateInstances(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_GetInstance(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_CreateInstance(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_ModifyInstance(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_DeleteInstance(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxUserResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MSFT_nxUserResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MSFT_nxUserResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxUserResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxUserResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxUserResource* instanceName,
    _In_opt_ const MSFT_nxUserResource_SetTargetResource* in);


#endif /* _MSFT_nxUserResource_h */

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxGroupResource_h
#define _MSFT_nxGroupResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxGroupResource.h"

/*
**==============================================================================
**
** MSFT_nxGroupResource [MSFT_nxGroupResource]
**
** Keys:
**    GroupName
**
**==============================================================================
*/

typedef struct _MSFT_nxGroupResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxGroupResource properties */
    /*KEY*/ MI_ConstStringField GroupName;
    MI_ConstStringField Ensure;
    MI_ConstStringAField Members;
    MI_ConstStringAField MembersToInclude;
    MI_ConstStringAField MembersToExclude;
    MI_ConstStringField PreferredGroupID;
}
MSFT_nxGroupResource;

typedef struct _MSFT_nxGroupResource_Ref
{
    MSFT_nxGroupResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxGroupResource_Ref;

typedef struct _MSFT_nxGroupResource_ConstRef
{
    MI_CONST MSFT_nxGroupResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxGroupResource_ConstRef;

typedef struct _MSFT_nxGroupResource_Array
{
    struct _MSFT_nxGroupResource** data;
    MI_Uint32 size;
}
MSFT_nxGroupResource_Array;

typedef struct _MSFT_nxGroupResource_ConstArray
{
    struct _MSFT_nxGroupResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxGroupResource_ConstArray;

typedef struct _MSFT_nxGroupResource_ArrayRef
{
    MSFT_nxGroupResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxGroupResource_ArrayRef;

typedef struct _MSFT_nxGroupResource_ConstArrayRef
{
    MSFT_nxGroupResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxGroupResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxGroupResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Construct(
    _Out_ MSFT_nxGroupResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxGroupResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Clone(
    _In_ const MSFT_nxGroupResource* self,
    _Outptr_ MSFT_nxGroupResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxGroupResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxGroupResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Destruct(_Inout_ MSFT_nxGroupResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Delete(_Inout_ MSFT_nxGroupResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Post(
    _In_ const MSFT_nxGroupResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Set_GroupName(
    _Inout_ MSFT_nxGroupResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetPtr_GroupName(
    _Inout_ MSFT_nxGroupResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Clear_GroupName(
    _Inout_ MSFT_nxGroupResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Set_Ensure(
    _Inout_ MSFT_nxGroupResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetPtr_Ensure(
    _Inout_ MSFT_nxGroupResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Clear_Ensure(
    _Inout_ MSFT_nxGroupResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Set_Members(
    _Inout_ MSFT_nxGroupResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetPtr_Members(
    _Inout_ MSFT_nxGroupResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Clear_Members(
    _Inout_ MSFT_nxGroupResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Set_MembersToInclude(
    _Inout_ MSFT_nxGroupResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetPtr_MembersToInclude(
    _Inout_ MSFT_nxGroupResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Clear_MembersToInclude(
    _Inout_ MSFT_nxGroupResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Set_MembersToExclude(
    _Inout_ MSFT_nxGroupResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetPtr_MembersToExclude(
    _Inout_ MSFT_nxGroupResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Clear_MembersToExclude(
    _Inout_ MSFT_nxGroupResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Set_PreferredGroupID(
    _Inout_ MSFT_nxGroupResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetPtr_PreferredGroupID(
    _Inout_ MSFT_nxGroupResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_Clear_PreferredGroupID(
    _Inout_ MSFT_nxGroupResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** MSFT_nxGroupResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxGroupResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxGroupResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxGroupResource_ConstRef OutputResource;
}
MSFT_nxGroupResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxGroupResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Construct(
    _Out_ MSFT_nxGroupResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxGroupResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Clone(
    _In_ const MSFT_nxGroupResource_GetTargetResource* self,
    _Outptr_ MSFT_nxGroupResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Post(
    _In_ const MSFT_nxGroupResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxGroupResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxGroupResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxGroupResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxGroupResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxGroupResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxGroupResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Construct(
    _Out_ MSFT_nxGroupResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxGroupResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Clone(
    _In_ const MSFT_nxGroupResource_TestTargetResource* self,
    _Outptr_ MSFT_nxGroupResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Post(
    _In_ const MSFT_nxGroupResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxGroupResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxGroupResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxGroupResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxGroupResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxGroupResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxGroupResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Construct(
    _Out_ MSFT_nxGroupResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxGroupResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Clone(
    _In_ const MSFT_nxGroupResource_SetTargetResource* self,
    _Outptr_ MSFT_nxGroupResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Post(
    _In_ const MSFT_nxGroupResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self,
    _In_ const MSFT_nxGroupResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxGroupResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxGroupResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxGroupResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxGroupResource_Self MSFT_nxGroupResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_Load(
    _Outptr_result_maybenull_ MSFT_nxGroupResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_Unload(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_EnumerateInstances(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_GetInstance(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_CreateInstance(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_ModifyInstance(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_DeleteInstance(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxGroupResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MSFT_nxGroupResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MSFT_nxGroupResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxGroupResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxGroupResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxGroupResource* instanceName,
    _In_opt_ const MSFT_nxGroupResource_SetTargetResource* in);


#endif /* _MSFT_nxGroupResource_h */

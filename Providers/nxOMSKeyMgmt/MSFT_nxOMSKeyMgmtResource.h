/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSKeyMgmtResource_h
#define _MSFT_nxOMSKeyMgmtResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxOMSKeyMgmtResource.h"

/*
**==============================================================================
**
** MSFT_nxOMSKeyMgmtResource [MSFT_nxOMSKeyMgmtResource]
**
** Keys:
**    KeyContents
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSKeyMgmtResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxOMSKeyMgmtResource properties */
    /*KEY*/ MI_ConstStringField KeyContents;
    MI_ConstStringField KeySignature;
    MI_ConstStringField Ensure;
}
MSFT_nxOMSKeyMgmtResource;

typedef struct _MSFT_nxOMSKeyMgmtResource_Ref
{
    MSFT_nxOMSKeyMgmtResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSKeyMgmtResource_Ref;

typedef struct _MSFT_nxOMSKeyMgmtResource_ConstRef
{
    MI_CONST MSFT_nxOMSKeyMgmtResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSKeyMgmtResource_ConstRef;

typedef struct _MSFT_nxOMSKeyMgmtResource_Array
{
    struct _MSFT_nxOMSKeyMgmtResource** data;
    MI_Uint32 size;
}
MSFT_nxOMSKeyMgmtResource_Array;

typedef struct _MSFT_nxOMSKeyMgmtResource_ConstArray
{
    struct _MSFT_nxOMSKeyMgmtResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSKeyMgmtResource_ConstArray;

typedef struct _MSFT_nxOMSKeyMgmtResource_ArrayRef
{
    MSFT_nxOMSKeyMgmtResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSKeyMgmtResource_ArrayRef;

typedef struct _MSFT_nxOMSKeyMgmtResource_ConstArrayRef
{
    MSFT_nxOMSKeyMgmtResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSKeyMgmtResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSKeyMgmtResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Construct(
    _Out_ MSFT_nxOMSKeyMgmtResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSKeyMgmtResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Clone(
    _In_ const MSFT_nxOMSKeyMgmtResource* self,
    _Outptr_ MSFT_nxOMSKeyMgmtResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSKeyMgmtResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSKeyMgmtResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Destruct(_Inout_ MSFT_nxOMSKeyMgmtResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Delete(_Inout_ MSFT_nxOMSKeyMgmtResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Post(
    _In_ const MSFT_nxOMSKeyMgmtResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Set_KeyContents(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetPtr_KeyContents(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Clear_KeyContents(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Set_KeySignature(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetPtr_KeySignature(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Clear_KeySignature(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Set_Ensure(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetPtr_Ensure(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_Clear_Ensure(
    _Inout_ MSFT_nxOMSKeyMgmtResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_nxOMSKeyMgmtResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSKeyMgmtResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSKeyMgmtResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxOMSKeyMgmtResource_ConstRef OutputResource;
}
MSFT_nxOMSKeyMgmtResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSKeyMgmtResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Construct(
    _Out_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSKeyMgmtResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Clone(
    _In_ const MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _Outptr_ MSFT_nxOMSKeyMgmtResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Post(
    _In_ const MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSKeyMgmtResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSKeyMgmtResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSKeyMgmtResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxOMSKeyMgmtResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSKeyMgmtResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Construct(
    _Out_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSKeyMgmtResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Clone(
    _In_ const MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _Outptr_ MSFT_nxOMSKeyMgmtResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Post(
    _In_ const MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSKeyMgmtResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSKeyMgmtResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSKeyMgmtResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSKeyMgmtResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxOMSKeyMgmtResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSKeyMgmtResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Construct(
    _Out_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSKeyMgmtResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Clone(
    _In_ const MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _Outptr_ MSFT_nxOMSKeyMgmtResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Post(
    _In_ const MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSKeyMgmtResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSKeyMgmtResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSKeyMgmtResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSKeyMgmtResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSKeyMgmtResource_Self MSFT_nxOMSKeyMgmtResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSKeyMgmtResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_Unload(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_EnumerateInstances(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_GetInstance(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSKeyMgmtResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_CreateInstance(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSKeyMgmtResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_ModifyInstance(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSKeyMgmtResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_DeleteInstance(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSKeyMgmtResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSKeyMgmtResource* instanceName,
    _In_opt_ const MSFT_nxOMSKeyMgmtResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSKeyMgmtResource* instanceName,
    _In_opt_ const MSFT_nxOMSKeyMgmtResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSKeyMgmtResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxOMSKeyMgmtResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSKeyMgmtResource* instanceName,
    _In_opt_ const MSFT_nxOMSKeyMgmtResource_SetTargetResource* in);


#endif /* _MSFT_nxOMSKeyMgmtResource_h */

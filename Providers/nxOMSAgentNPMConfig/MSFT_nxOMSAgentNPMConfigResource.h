/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSAgentNPMConfigResource_h
#define _MSFT_nxOMSAgentNPMConfigResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxOMSAgentNPMConfigResource.h"

/*
**==============================================================================
**
** MSFT_nxOMSAgentNPMConfigResource [MSFT_nxOMSAgentNPMConfigResource]
**
** Keys:
**    ConfigType
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentNPMConfigResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxOMSAgentNPMConfigResource properties */
    /*KEY*/ MI_ConstStringField ConfigType;
    MI_ConstStringField ConfigID;
    MI_ConstStringField Contents;
    MI_ConstStringField Ensure;
    MI_ConstStringField ContentChecksum;
}
MSFT_nxOMSAgentNPMConfigResource;

typedef struct _MSFT_nxOMSAgentNPMConfigResource_Ref
{
    MSFT_nxOMSAgentNPMConfigResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentNPMConfigResource_Ref;

typedef struct _MSFT_nxOMSAgentNPMConfigResource_ConstRef
{
    MI_CONST MSFT_nxOMSAgentNPMConfigResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentNPMConfigResource_ConstRef;

typedef struct _MSFT_nxOMSAgentNPMConfigResource_Array
{
    struct _MSFT_nxOMSAgentNPMConfigResource** data;
    MI_Uint32 size;
}
MSFT_nxOMSAgentNPMConfigResource_Array;

typedef struct _MSFT_nxOMSAgentNPMConfigResource_ConstArray
{
    struct _MSFT_nxOMSAgentNPMConfigResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSAgentNPMConfigResource_ConstArray;

typedef struct _MSFT_nxOMSAgentNPMConfigResource_ArrayRef
{
    MSFT_nxOMSAgentNPMConfigResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentNPMConfigResource_ArrayRef;

typedef struct _MSFT_nxOMSAgentNPMConfigResource_ConstArrayRef
{
    MSFT_nxOMSAgentNPMConfigResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentNPMConfigResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSAgentNPMConfigResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Construct(
    _Out_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSAgentNPMConfigResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Clone(
    _In_ const MSFT_nxOMSAgentNPMConfigResource* self,
    _Outptr_ MSFT_nxOMSAgentNPMConfigResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSAgentNPMConfigResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSAgentNPMConfigResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Destruct(_Inout_ MSFT_nxOMSAgentNPMConfigResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Delete(_Inout_ MSFT_nxOMSAgentNPMConfigResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Post(
    _In_ const MSFT_nxOMSAgentNPMConfigResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Set_ConfigType(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetPtr_ConfigType(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Clear_ConfigType(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Set_ConfigID(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetPtr_ConfigID(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Clear_ConfigID(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Set_Contents(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetPtr_Contents(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Clear_Contents(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Set_Ensure(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetPtr_Ensure(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Clear_Ensure(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Set_ContentChecksum(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetPtr_ContentChecksum(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_Clear_ContentChecksum(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentNPMConfigResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentNPMConfigResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSAgentNPMConfigResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxOMSAgentNPMConfigResource_ConstRef OutputResource;
}
MSFT_nxOMSAgentNPMConfigResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Construct(
    _Out_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Clone(
    _In_ const MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _Outptr_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Post(
    _In_ const MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentNPMConfigResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentNPMConfigResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSAgentNPMConfigResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxOMSAgentNPMConfigResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Construct(
    _Out_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Clone(
    _In_ const MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _Outptr_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Post(
    _In_ const MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentNPMConfigResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentNPMConfigResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSAgentNPMConfigResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxOMSAgentNPMConfigResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Construct(
    _Out_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Clone(
    _In_ const MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _Outptr_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Post(
    _In_ const MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentNPMConfigResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentNPMConfigResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSAgentNPMConfigResource_Self MSFT_nxOMSAgentNPMConfigResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSAgentNPMConfigResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_Unload(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_EnumerateInstances(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_GetInstance(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_CreateInstance(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_ModifyInstance(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_DeleteInstance(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* instanceName,
    _In_opt_ const MSFT_nxOMSAgentNPMConfigResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* instanceName,
    _In_opt_ const MSFT_nxOMSAgentNPMConfigResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentNPMConfigResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxOMSAgentNPMConfigResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSAgentNPMConfigResource* instanceName,
    _In_opt_ const MSFT_nxOMSAgentNPMConfigResource_SetTargetResource* in);


#endif /* _MSFT_nxOMSAgentNPMConfigResource_h */

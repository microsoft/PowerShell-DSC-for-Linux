/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSPerfCounterResource_h
#define _MSFT_nxOMSPerfCounterResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxOMSPerfCounterObject.h"
#include "MSFT_nxOMSPerfCounterResource.h"

/*
**==============================================================================
**
** MSFT_nxOMSPerfCounterResource [MSFT_nxOMSPerfCounterResource]
**
** Keys:
**    Name
**    WorkspaceID
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSPerfCounterResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxOMSPerfCounterResource properties */
    /*KEY*/ MI_ConstStringField Name;
    /*KEY*/ MI_ConstStringField WorkspaceID;
    MI_ConstUint16Field HeartbeatIntervalSeconds;
    MSFT_nxOMSPerfCounterObject_ConstArrayRef PerfCounterObject;
}
MSFT_nxOMSPerfCounterResource;

typedef struct _MSFT_nxOMSPerfCounterResource_Ref
{
    MSFT_nxOMSPerfCounterResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterResource_Ref;

typedef struct _MSFT_nxOMSPerfCounterResource_ConstRef
{
    MI_CONST MSFT_nxOMSPerfCounterResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterResource_ConstRef;

typedef struct _MSFT_nxOMSPerfCounterResource_Array
{
    struct _MSFT_nxOMSPerfCounterResource** data;
    MI_Uint32 size;
}
MSFT_nxOMSPerfCounterResource_Array;

typedef struct _MSFT_nxOMSPerfCounterResource_ConstArray
{
    struct _MSFT_nxOMSPerfCounterResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSPerfCounterResource_ConstArray;

typedef struct _MSFT_nxOMSPerfCounterResource_ArrayRef
{
    MSFT_nxOMSPerfCounterResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterResource_ArrayRef;

typedef struct _MSFT_nxOMSPerfCounterResource_ConstArrayRef
{
    MSFT_nxOMSPerfCounterResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSPerfCounterResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Construct(
    _Out_ MSFT_nxOMSPerfCounterResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSPerfCounterResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Clone(
    _In_ const MSFT_nxOMSPerfCounterResource* self,
    _Outptr_ MSFT_nxOMSPerfCounterResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSPerfCounterResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSPerfCounterResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Destruct(_Inout_ MSFT_nxOMSPerfCounterResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Delete(_Inout_ MSFT_nxOMSPerfCounterResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Post(
    _In_ const MSFT_nxOMSPerfCounterResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Set_Name(
    _Inout_ MSFT_nxOMSPerfCounterResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetPtr_Name(
    _Inout_ MSFT_nxOMSPerfCounterResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Clear_Name(
    _Inout_ MSFT_nxOMSPerfCounterResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Set_WorkspaceID(
    _Inout_ MSFT_nxOMSPerfCounterResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetPtr_WorkspaceID(
    _Inout_ MSFT_nxOMSPerfCounterResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Clear_WorkspaceID(
    _Inout_ MSFT_nxOMSPerfCounterResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Set_HeartbeatIntervalSeconds(
    _Inout_ MSFT_nxOMSPerfCounterResource* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HeartbeatIntervalSeconds)->value = x;
    ((MI_Uint16Field*)&self->HeartbeatIntervalSeconds)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Clear_HeartbeatIntervalSeconds(
    _Inout_ MSFT_nxOMSPerfCounterResource* self)
{
    memset((void*)&self->HeartbeatIntervalSeconds, 0, sizeof(self->HeartbeatIntervalSeconds));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Set_PerfCounterObject(
    _Inout_ MSFT_nxOMSPerfCounterResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSPerfCounterObject * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetPtr_PerfCounterObject(
    _Inout_ MSFT_nxOMSPerfCounterResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSPerfCounterObject * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_Clear_PerfCounterObject(
    _Inout_ MSFT_nxOMSPerfCounterResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSPerfCounterResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSPerfCounterResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSPerfCounterResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxOMSPerfCounterResource_ConstRef OutputResource;
}
MSFT_nxOMSPerfCounterResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSPerfCounterResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Construct(
    _Out_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSPerfCounterResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Clone(
    _In_ const MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _Outptr_ MSFT_nxOMSPerfCounterResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Post(
    _In_ const MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSPerfCounterResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSPerfCounterResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSPerfCounterResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxOMSPerfCounterResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSPerfCounterResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Construct(
    _Out_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSPerfCounterResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Clone(
    _In_ const MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _Outptr_ MSFT_nxOMSPerfCounterResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Post(
    _In_ const MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSPerfCounterResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSPerfCounterResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSPerfCounterResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSPerfCounterResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxOMSPerfCounterResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSPerfCounterResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Construct(
    _Out_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSPerfCounterResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Clone(
    _In_ const MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _Outptr_ MSFT_nxOMSPerfCounterResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Post(
    _In_ const MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSPerfCounterResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSPerfCounterResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSPerfCounterResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSPerfCounterResource_Self MSFT_nxOMSPerfCounterResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSPerfCounterResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_Unload(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_EnumerateInstances(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_GetInstance(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSPerfCounterResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_CreateInstance(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSPerfCounterResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_ModifyInstance(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSPerfCounterResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_DeleteInstance(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSPerfCounterResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSPerfCounterResource* instanceName,
    _In_opt_ const MSFT_nxOMSPerfCounterResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSPerfCounterResource* instanceName,
    _In_opt_ const MSFT_nxOMSPerfCounterResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSPerfCounterResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxOMSPerfCounterResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSPerfCounterResource* instanceName,
    _In_opt_ const MSFT_nxOMSPerfCounterResource_SetTargetResource* in);


#endif /* _MSFT_nxOMSPerfCounterResource_h */

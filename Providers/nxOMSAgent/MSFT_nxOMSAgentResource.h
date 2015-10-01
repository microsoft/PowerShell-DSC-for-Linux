/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSAgentResource_h
#define _MSFT_nxOMSAgentResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxOMSPerfObject.h"
#include "MSFT_nxOMSAgentResource.h"

/*
**==============================================================================
**
** MSFT_nxOMSAgentResource [MSFT_nxOMSAgentResource]
**
** Keys:
**    PerfObject
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxOMSAgentResource properties */
    MI_ConstUint16Field HeartbeatIntervalSeconds;
    /*KEY*/ MSFT_nxOMSPerfObject_ConstArrayRef PerfObject;
}
MSFT_nxOMSAgentResource;

typedef struct _MSFT_nxOMSAgentResource_Ref
{
    MSFT_nxOMSAgentResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentResource_Ref;

typedef struct _MSFT_nxOMSAgentResource_ConstRef
{
    MI_CONST MSFT_nxOMSAgentResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentResource_ConstRef;

typedef struct _MSFT_nxOMSAgentResource_Array
{
    struct _MSFT_nxOMSAgentResource** data;
    MI_Uint32 size;
}
MSFT_nxOMSAgentResource_Array;

typedef struct _MSFT_nxOMSAgentResource_ConstArray
{
    struct _MSFT_nxOMSAgentResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSAgentResource_ConstArray;

typedef struct _MSFT_nxOMSAgentResource_ArrayRef
{
    MSFT_nxOMSAgentResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentResource_ArrayRef;

typedef struct _MSFT_nxOMSAgentResource_ConstArrayRef
{
    MSFT_nxOMSAgentResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSAgentResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSAgentResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Construct(
    _Out_ MSFT_nxOMSAgentResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSAgentResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Clone(
    _In_ const MSFT_nxOMSAgentResource* self,
    _Outptr_ MSFT_nxOMSAgentResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSAgentResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSAgentResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Destruct(_Inout_ MSFT_nxOMSAgentResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Delete(_Inout_ MSFT_nxOMSAgentResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Post(
    _In_ const MSFT_nxOMSAgentResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Set_HeartbeatIntervalSeconds(
    _Inout_ MSFT_nxOMSAgentResource* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HeartbeatIntervalSeconds)->value = x;
    ((MI_Uint16Field*)&self->HeartbeatIntervalSeconds)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Clear_HeartbeatIntervalSeconds(
    _Inout_ MSFT_nxOMSAgentResource* self)
{
    memset((void*)&self->HeartbeatIntervalSeconds, 0, sizeof(self->HeartbeatIntervalSeconds));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Set_PerfObject(
    _Inout_ MSFT_nxOMSAgentResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSPerfObject * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetPtr_PerfObject(
    _Inout_ MSFT_nxOMSAgentResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSPerfObject * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_Clear_PerfObject(
    _Inout_ MSFT_nxOMSAgentResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSAgentResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxOMSAgentResource_ConstRef OutputResource;
}
MSFT_nxOMSAgentResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSAgentResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Construct(
    _Out_ MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSAgentResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Clone(
    _In_ const MSFT_nxOMSAgentResource_GetTargetResource* self,
    _Outptr_ MSFT_nxOMSAgentResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Post(
    _In_ const MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxOMSAgentResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSAgentResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxOMSAgentResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSAgentResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Construct(
    _Out_ MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSAgentResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Clone(
    _In_ const MSFT_nxOMSAgentResource_TestTargetResource* self,
    _Outptr_ MSFT_nxOMSAgentResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Post(
    _In_ const MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSAgentResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSAgentResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSAgentResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxOMSAgentResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSAgentResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Construct(
    _Out_ MSFT_nxOMSAgentResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSAgentResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Clone(
    _In_ const MSFT_nxOMSAgentResource_SetTargetResource* self,
    _Outptr_ MSFT_nxOMSAgentResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Post(
    _In_ const MSFT_nxOMSAgentResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSAgentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSAgentResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSAgentResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSAgentResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSAgentResource_Self MSFT_nxOMSAgentResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSAgentResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_Unload(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_EnumerateInstances(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_GetInstance(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_CreateInstance(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_ModifyInstance(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_DeleteInstance(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSAgentResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSAgentResource* instanceName,
    _In_opt_ const MSFT_nxOMSAgentResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSAgentResource* instanceName,
    _In_opt_ const MSFT_nxOMSAgentResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSAgentResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxOMSAgentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSAgentResource* instanceName,
    _In_opt_ const MSFT_nxOMSAgentResource_SetTargetResource* in);


#endif /* _MSFT_nxOMSAgentResource_h */

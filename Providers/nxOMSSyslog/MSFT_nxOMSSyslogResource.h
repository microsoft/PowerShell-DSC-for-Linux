/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSSyslogResource_h
#define _MSFT_nxOMSSyslogResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxOMSSyslogSource.h"
#include "MSFT_nxOMSSyslogResource.h"

/*
**==============================================================================
**
** MSFT_nxOMSSyslogResource [MSFT_nxOMSSyslogResource]
**
** Keys:
**    SyslogSource
**    WorkspaceID
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSSyslogResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxOMSSyslogResource properties */
    /*KEY*/ MSFT_nxOMSSyslogSource_ConstArrayRef SyslogSource;
    /*KEY*/ MI_ConstStringField WorkspaceID;
}
MSFT_nxOMSSyslogResource;

typedef struct _MSFT_nxOMSSyslogResource_Ref
{
    MSFT_nxOMSSyslogResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogResource_Ref;

typedef struct _MSFT_nxOMSSyslogResource_ConstRef
{
    MI_CONST MSFT_nxOMSSyslogResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogResource_ConstRef;

typedef struct _MSFT_nxOMSSyslogResource_Array
{
    struct _MSFT_nxOMSSyslogResource** data;
    MI_Uint32 size;
}
MSFT_nxOMSSyslogResource_Array;

typedef struct _MSFT_nxOMSSyslogResource_ConstArray
{
    struct _MSFT_nxOMSSyslogResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSSyslogResource_ConstArray;

typedef struct _MSFT_nxOMSSyslogResource_ArrayRef
{
    MSFT_nxOMSSyslogResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogResource_ArrayRef;

typedef struct _MSFT_nxOMSSyslogResource_ConstArrayRef
{
    MSFT_nxOMSSyslogResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSSyslogResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Construct(
    _Out_ MSFT_nxOMSSyslogResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSSyslogResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Clone(
    _In_ const MSFT_nxOMSSyslogResource* self,
    _Outptr_ MSFT_nxOMSSyslogResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSSyslogResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSSyslogResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Destruct(_Inout_ MSFT_nxOMSSyslogResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Delete(_Inout_ MSFT_nxOMSSyslogResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Post(
    _In_ const MSFT_nxOMSSyslogResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Set_SyslogSource(
    _Inout_ MSFT_nxOMSSyslogResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSSyslogSource * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetPtr_SyslogSource(
    _Inout_ MSFT_nxOMSSyslogResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSSyslogSource * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Clear_SyslogSource(
    _Inout_ MSFT_nxOMSSyslogResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Set_WorkspaceID(
    _Inout_ MSFT_nxOMSSyslogResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetPtr_WorkspaceID(
    _Inout_ MSFT_nxOMSSyslogResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_Clear_WorkspaceID(
    _Inout_ MSFT_nxOMSSyslogResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_nxOMSSyslogResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSSyslogResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSSyslogResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxOMSSyslogResource_ConstRef OutputResource;
}
MSFT_nxOMSSyslogResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSSyslogResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Construct(
    _Out_ MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSSyslogResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Clone(
    _In_ const MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _Outptr_ MSFT_nxOMSSyslogResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Post(
    _In_ const MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxOMSSyslogResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSSyslogResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSSyslogResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSSyslogResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxOMSSyslogResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSSyslogResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Construct(
    _Out_ MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSSyslogResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Clone(
    _In_ const MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _Outptr_ MSFT_nxOMSSyslogResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Post(
    _In_ const MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSSyslogResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSSyslogResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSSyslogResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSSyslogResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxOMSSyslogResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSSyslogResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Construct(
    _Out_ MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSSyslogResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Clone(
    _In_ const MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _Outptr_ MSFT_nxOMSSyslogResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Post(
    _In_ const MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSSyslogResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSSyslogResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSSyslogResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSSyslogResource_Self MSFT_nxOMSSyslogResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSSyslogResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_Unload(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_EnumerateInstances(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_GetInstance(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSSyslogResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_CreateInstance(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSSyslogResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_ModifyInstance(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSSyslogResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_DeleteInstance(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSSyslogResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSSyslogResource* instanceName,
    _In_opt_ const MSFT_nxOMSSyslogResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSSyslogResource* instanceName,
    _In_opt_ const MSFT_nxOMSSyslogResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSSyslogResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxOMSSyslogResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSSyslogResource* instanceName,
    _In_opt_ const MSFT_nxOMSSyslogResource_SetTargetResource* in);


#endif /* _MSFT_nxOMSSyslogResource_h */

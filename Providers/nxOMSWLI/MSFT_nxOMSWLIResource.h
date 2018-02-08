/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSWLIResource_h
#define _MSFT_nxOMSWLIResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxOMSWLIResource.h"

/*
**==============================================================================
**
** MSFT_nxOMSWLIResource [MSFT_nxOMSWLIResource]
**
** Keys:
**    WorkspaceId
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSWLIResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxOMSWLIResource properties */
    /*KEY*/ MI_ConstStringField WorkspaceId;
    MI_ConstStringField Configuration;
}
MSFT_nxOMSWLIResource;

typedef struct _MSFT_nxOMSWLIResource_Ref
{
    MSFT_nxOMSWLIResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSWLIResource_Ref;

typedef struct _MSFT_nxOMSWLIResource_ConstRef
{
    MI_CONST MSFT_nxOMSWLIResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSWLIResource_ConstRef;

typedef struct _MSFT_nxOMSWLIResource_Array
{
    struct _MSFT_nxOMSWLIResource** data;
    MI_Uint32 size;
}
MSFT_nxOMSWLIResource_Array;

typedef struct _MSFT_nxOMSWLIResource_ConstArray
{
    struct _MSFT_nxOMSWLIResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSWLIResource_ConstArray;

typedef struct _MSFT_nxOMSWLIResource_ArrayRef
{
    MSFT_nxOMSWLIResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSWLIResource_ArrayRef;

typedef struct _MSFT_nxOMSWLIResource_ConstArrayRef
{
    MSFT_nxOMSWLIResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSWLIResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSWLIResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Construct(
    _Out_ MSFT_nxOMSWLIResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSWLIResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Clone(
    _In_ const MSFT_nxOMSWLIResource* self,
    _Outptr_ MSFT_nxOMSWLIResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSWLIResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSWLIResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Destruct(_Inout_ MSFT_nxOMSWLIResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Delete(_Inout_ MSFT_nxOMSWLIResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Post(
    _In_ const MSFT_nxOMSWLIResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Set_WorkspaceId(
    _Inout_ MSFT_nxOMSWLIResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetPtr_WorkspaceId(
    _Inout_ MSFT_nxOMSWLIResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Clear_WorkspaceId(
    _Inout_ MSFT_nxOMSWLIResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Set_Configuration(
    _Inout_ MSFT_nxOMSWLIResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetPtr_Configuration(
    _Inout_ MSFT_nxOMSWLIResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_Clear_Configuration(
    _Inout_ MSFT_nxOMSWLIResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_nxOMSWLIResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSWLIResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSWLIResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxOMSWLIResource_ConstRef OutputResource;
}
MSFT_nxOMSWLIResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSWLIResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Construct(
    _Out_ MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSWLIResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Clone(
    _In_ const MSFT_nxOMSWLIResource_GetTargetResource* self,
    _Outptr_ MSFT_nxOMSWLIResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Post(
    _In_ const MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxOMSWLIResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSWLIResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSWLIResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSWLIResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxOMSWLIResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSWLIResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Construct(
    _Out_ MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSWLIResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Clone(
    _In_ const MSFT_nxOMSWLIResource_TestTargetResource* self,
    _Outptr_ MSFT_nxOMSWLIResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Post(
    _In_ const MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSWLIResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSWLIResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSWLIResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSWLIResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxOMSWLIResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSWLIResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Construct(
    _Out_ MSFT_nxOMSWLIResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSWLIResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Clone(
    _In_ const MSFT_nxOMSWLIResource_SetTargetResource* self,
    _Outptr_ MSFT_nxOMSWLIResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Post(
    _In_ const MSFT_nxOMSWLIResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSWLIResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSWLIResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSWLIResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSWLIResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSWLIResource_Self MSFT_nxOMSWLIResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSWLIResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_Unload(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_EnumerateInstances(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_GetInstance(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSWLIResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_CreateInstance(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSWLIResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_ModifyInstance(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSWLIResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_DeleteInstance(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSWLIResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSWLIResource* instanceName,
    _In_opt_ const MSFT_nxOMSWLIResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSWLIResource* instanceName,
    _In_opt_ const MSFT_nxOMSWLIResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSWLIResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxOMSWLIResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSWLIResource* instanceName,
    _In_opt_ const MSFT_nxOMSWLIResource_SetTargetResource* in);


#endif /* _MSFT_nxOMSWLIResource_h */

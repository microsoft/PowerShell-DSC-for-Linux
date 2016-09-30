/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxAutomationWorkerResource_h
#define _MSFT_nxAutomationWorkerResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxAutomationWorkerResource.h"

/*
**==============================================================================
**
** MSFT_nxAutomationWorkerResource [MSFT_nxAutomationWorkerResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorkerResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxAutomationWorkerResource properties */
    /*KEY*/ MI_ConstStringField Name;
}
MSFT_nxAutomationWorkerResource;

typedef struct _MSFT_nxAutomationWorkerResource_Ref
{
    MSFT_nxAutomationWorkerResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorkerResource_Ref;

typedef struct _MSFT_nxAutomationWorkerResource_ConstRef
{
    MI_CONST MSFT_nxAutomationWorkerResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorkerResource_ConstRef;

typedef struct _MSFT_nxAutomationWorkerResource_Array
{
    struct _MSFT_nxAutomationWorkerResource** data;
    MI_Uint32 size;
}
MSFT_nxAutomationWorkerResource_Array;

typedef struct _MSFT_nxAutomationWorkerResource_ConstArray
{
    struct _MSFT_nxAutomationWorkerResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxAutomationWorkerResource_ConstArray;

typedef struct _MSFT_nxAutomationWorkerResource_ArrayRef
{
    MSFT_nxAutomationWorkerResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorkerResource_ArrayRef;

typedef struct _MSFT_nxAutomationWorkerResource_ConstArrayRef
{
    MSFT_nxAutomationWorkerResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorkerResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxAutomationWorkerResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_Construct(
    _Out_ MSFT_nxAutomationWorkerResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxAutomationWorkerResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_Clone(
    _In_ const MSFT_nxAutomationWorkerResource* self,
    _Outptr_ MSFT_nxAutomationWorkerResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxAutomationWorkerResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxAutomationWorkerResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_Destruct(_Inout_ MSFT_nxAutomationWorkerResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_Delete(_Inout_ MSFT_nxAutomationWorkerResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_Post(
    _In_ const MSFT_nxAutomationWorkerResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_Set_Name(
    _Inout_ MSFT_nxAutomationWorkerResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetPtr_Name(
    _Inout_ MSFT_nxAutomationWorkerResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_Clear_Name(
    _Inout_ MSFT_nxAutomationWorkerResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorkerResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorkerResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAutomationWorkerResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxAutomationWorkerResource_ConstRef OutputResource;
}
MSFT_nxAutomationWorkerResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAutomationWorkerResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Construct(
    _Out_ MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAutomationWorkerResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Clone(
    _In_ const MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _Outptr_ MSFT_nxAutomationWorkerResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Post(
    _In_ const MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorkerResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorkerResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAutomationWorkerResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxAutomationWorkerResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAutomationWorkerResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Construct(
    _Out_ MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAutomationWorkerResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Clone(
    _In_ const MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _Outptr_ MSFT_nxAutomationWorkerResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Post(
    _In_ const MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxAutomationWorkerResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorkerResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorkerResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAutomationWorkerResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxAutomationWorkerResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAutomationWorkerResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Construct(
    _Out_ MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAutomationWorkerResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Clone(
    _In_ const MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _Outptr_ MSFT_nxAutomationWorkerResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Post(
    _In_ const MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _In_ const MSFT_nxAutomationWorkerResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorkerResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAutomationWorkerResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorkerResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxAutomationWorkerResource_Self MSFT_nxAutomationWorkerResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_Load(
    _Outptr_result_maybenull_ MSFT_nxAutomationWorkerResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_Unload(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_EnumerateInstances(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_GetInstance(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorkerResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_CreateInstance(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorkerResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_ModifyInstance(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorkerResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_DeleteInstance(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorkerResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAutomationWorkerResource* instanceName,
    _In_opt_ const MSFT_nxAutomationWorkerResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAutomationWorkerResource* instanceName,
    _In_opt_ const MSFT_nxAutomationWorkerResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorkerResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxAutomationWorkerResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAutomationWorkerResource* instanceName,
    _In_opt_ const MSFT_nxAutomationWorkerResource_SetTargetResource* in);


#endif /* _MSFT_nxAutomationWorkerResource_h */

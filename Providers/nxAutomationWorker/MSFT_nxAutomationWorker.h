/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxAutomationWorker_h
#define _MSFT_nxAutomationWorker_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxAutomationWorker.h"

/*
**==============================================================================
**
** MSFT_nxAutomationWorker [MSFT_nxAutomationWorker]
**
** Keys:
**    DestinationPath
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorker /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxAutomationWorker properties */
    /*KEY*/ MI_ConstStringField DestinationPath;
}
MSFT_nxAutomationWorker;

typedef struct _MSFT_nxAutomationWorker_Ref
{
    MSFT_nxAutomationWorker* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorker_Ref;

typedef struct _MSFT_nxAutomationWorker_ConstRef
{
    MI_CONST MSFT_nxAutomationWorker* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorker_ConstRef;

typedef struct _MSFT_nxAutomationWorker_Array
{
    struct _MSFT_nxAutomationWorker** data;
    MI_Uint32 size;
}
MSFT_nxAutomationWorker_Array;

typedef struct _MSFT_nxAutomationWorker_ConstArray
{
    struct _MSFT_nxAutomationWorker MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxAutomationWorker_ConstArray;

typedef struct _MSFT_nxAutomationWorker_ArrayRef
{
    MSFT_nxAutomationWorker_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorker_ArrayRef;

typedef struct _MSFT_nxAutomationWorker_ConstArrayRef
{
    MSFT_nxAutomationWorker_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAutomationWorker_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxAutomationWorker_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_Construct(
    _Out_ MSFT_nxAutomationWorker* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxAutomationWorker_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_Clone(
    _In_ const MSFT_nxAutomationWorker* self,
    _Outptr_ MSFT_nxAutomationWorker** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxAutomationWorker_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxAutomationWorker_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_Destruct(_Inout_ MSFT_nxAutomationWorker* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_Delete(_Inout_ MSFT_nxAutomationWorker* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_Post(
    _In_ const MSFT_nxAutomationWorker* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_Set_DestinationPath(
    _Inout_ MSFT_nxAutomationWorker* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetPtr_DestinationPath(
    _Inout_ MSFT_nxAutomationWorker* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_Clear_DestinationPath(
    _Inout_ MSFT_nxAutomationWorker* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorker.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorker_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAutomationWorker_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxAutomationWorker_ConstRef OutputResource;
}
MSFT_nxAutomationWorker_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAutomationWorker_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Construct(
    _Out_ MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAutomationWorker_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Clone(
    _In_ const MSFT_nxAutomationWorker_GetTargetResource* self,
    _Outptr_ MSFT_nxAutomationWorker_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Destruct(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Delete(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Post(
    _In_ const MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxAutomationWorker_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorker.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorker_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAutomationWorker_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxAutomationWorker_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAutomationWorker_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Construct(
    _Out_ MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAutomationWorker_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Clone(
    _In_ const MSFT_nxAutomationWorker_TestTargetResource* self,
    _Outptr_ MSFT_nxAutomationWorker_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Destruct(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Delete(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Post(
    _In_ const MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxAutomationWorker_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorker.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAutomationWorker_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAutomationWorker_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxAutomationWorker_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAutomationWorker_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Construct(
    _Out_ MSFT_nxAutomationWorker_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAutomationWorker_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Clone(
    _In_ const MSFT_nxAutomationWorker_SetTargetResource* self,
    _Outptr_ MSFT_nxAutomationWorker_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Destruct(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Delete(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Post(
    _In_ const MSFT_nxAutomationWorker_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self,
    _In_ const MSFT_nxAutomationWorker* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAutomationWorker_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAutomationWorker_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxAutomationWorker provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxAutomationWorker_Self MSFT_nxAutomationWorker_Self;

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_Load(
    _Outptr_result_maybenull_ MSFT_nxAutomationWorker_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_Unload(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_EnumerateInstances(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_GetInstance(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorker* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_CreateInstance(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorker* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_ModifyInstance(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorker* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_DeleteInstance(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAutomationWorker* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAutomationWorker* instanceName,
    _In_opt_ const MSFT_nxAutomationWorker_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAutomationWorker* instanceName,
    _In_opt_ const MSFT_nxAutomationWorker_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxAutomationWorker_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxAutomationWorker_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAutomationWorker* instanceName,
    _In_opt_ const MSFT_nxAutomationWorker_SetTargetResource* in);


#endif /* _MSFT_nxAutomationWorker_h */

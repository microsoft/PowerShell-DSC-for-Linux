/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSGenerateInventoryMofResource_h
#define _MSFT_nxOMSGenerateInventoryMofResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxOMSGenerateInventoryMofInstance.h"
#include "MSFT_nxOMSGenerateInventoryMofResource.h"

/*
**==============================================================================
**
** MSFT_nxOMSGenerateInventoryMofResource [MSFT_nxOMSGenerateInventoryMofResource]
**
** Keys:
**    FeatureName
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSGenerateInventoryMofResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxOMSGenerateInventoryMofResource properties */
    /*KEY*/ MI_ConstStringField FeatureName;
    MI_ConstBooleanField Enable;
    MSFT_nxOMSGenerateInventoryMofInstance_ConstArrayRef Instances;
    MI_ConstUint64Field RunIntervalInSeconds;
    MI_ConstStringField Tag;
    MI_ConstStringField Format;
    MI_ConstStringField FilterType;
    MI_ConstStringAField Configuration;
}
MSFT_nxOMSGenerateInventoryMofResource;

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_Ref
{
    MSFT_nxOMSGenerateInventoryMofResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofResource_Ref;

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_ConstRef
{
    MI_CONST MSFT_nxOMSGenerateInventoryMofResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofResource_ConstRef;

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_Array
{
    struct _MSFT_nxOMSGenerateInventoryMofResource** data;
    MI_Uint32 size;
}
MSFT_nxOMSGenerateInventoryMofResource_Array;

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_ConstArray
{
    struct _MSFT_nxOMSGenerateInventoryMofResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSGenerateInventoryMofResource_ConstArray;

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_ArrayRef
{
    MSFT_nxOMSGenerateInventoryMofResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofResource_ArrayRef;

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_ConstArrayRef
{
    MSFT_nxOMSGenerateInventoryMofResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSGenerateInventoryMofResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Construct(
    _Out_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSGenerateInventoryMofResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clone(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* self,
    _Outptr_ MSFT_nxOMSGenerateInventoryMofResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSGenerateInventoryMofResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSGenerateInventoryMofResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Destruct(_Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Delete(_Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Post(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_FeatureName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetPtr_FeatureName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_FeatureName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_Enable(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enable)->value = x;
    ((MI_BooleanField*)&self->Enable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_Enable(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    memset((void*)&self->Enable, 0, sizeof(self->Enable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_Instances(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSGenerateInventoryMofInstance * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetPtr_Instances(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_reads_opt_(size) const MSFT_nxOMSGenerateInventoryMofInstance * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_Instances(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_RunIntervalInSeconds(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->RunIntervalInSeconds)->value = x;
    ((MI_Uint64Field*)&self->RunIntervalInSeconds)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_RunIntervalInSeconds(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    memset((void*)&self->RunIntervalInSeconds, 0, sizeof(self->RunIntervalInSeconds));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_Tag(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetPtr_Tag(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_Tag(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_Format(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetPtr_Format(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_Format(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_FilterType(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetPtr_FilterType(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_FilterType(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Set_Configuration(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetPtr_Configuration(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Clear_Configuration(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** MSFT_nxOMSGenerateInventoryMofResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSGenerateInventoryMofResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxOMSGenerateInventoryMofResource_ConstRef OutputResource;
}
MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Construct(
    _Out_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Clone(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _Outptr_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Post(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxOMSGenerateInventoryMofResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSGenerateInventoryMofResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Construct(
    _Out_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Clone(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _Outptr_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Post(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSGenerateInventoryMofResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxOMSGenerateInventoryMofResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Construct(
    _Out_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Clone(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _Outptr_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Post(
    _In_ const MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxOMSGenerateInventoryMofResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSGenerateInventoryMofResource_Self MSFT_nxOMSGenerateInventoryMofResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSGenerateInventoryMofResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Unload(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_EnumerateInstances(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_GetInstance(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_CreateInstance(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_ModifyInstance(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_DeleteInstance(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* instanceName,
    _In_opt_ const MSFT_nxOMSGenerateInventoryMofResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* instanceName,
    _In_opt_ const MSFT_nxOMSGenerateInventoryMofResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxOMSGenerateInventoryMofResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxOMSGenerateInventoryMofResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxOMSGenerateInventoryMofResource* instanceName,
    _In_opt_ const MSFT_nxOMSGenerateInventoryMofResource_SetTargetResource* in);


#endif /* _MSFT_nxOMSGenerateInventoryMofResource_h */

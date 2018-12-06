/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxNopResource_h
#define _MSFT_nxNopResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxNopResource.h"

/*
**==============================================================================
**
** MSFT_nxNopResource [MSFT_nxNopResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxNopResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* MSFT_nxNopResource properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Value;
    MI_ConstStringField Ensure;
}
MSFT_nxNopResource;

typedef struct _MSFT_nxNopResource_Ref
{
    MSFT_nxNopResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxNopResource_Ref;

typedef struct _MSFT_nxNopResource_ConstRef
{
    MI_CONST MSFT_nxNopResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxNopResource_ConstRef;

typedef struct _MSFT_nxNopResource_Array
{
    struct _MSFT_nxNopResource** data;
    MI_Uint32 size;
}
MSFT_nxNopResource_Array;

typedef struct _MSFT_nxNopResource_ConstArray
{
    struct _MSFT_nxNopResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxNopResource_ConstArray;

typedef struct _MSFT_nxNopResource_ArrayRef
{
    MSFT_nxNopResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxNopResource_ArrayRef;

typedef struct _MSFT_nxNopResource_ConstArrayRef
{
    MSFT_nxNopResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxNopResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxNopResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Construct(
    MSFT_nxNopResource* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_nxNopResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clone(
    const MSFT_nxNopResource* self,
    MSFT_nxNopResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxNopResource_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxNopResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Destruct(MSFT_nxNopResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Delete(MSFT_nxNopResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Post(
    const MSFT_nxNopResource* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_ResourceId(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_ResourceId(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_ResourceId(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_SourceInfo(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_SourceInfo(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_SourceInfo(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_Requires(
    MSFT_nxNopResource* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_Requires(
    MSFT_nxNopResource* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_Requires(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_ModuleName(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_ModuleName(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_ModuleName(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_ModuleVersion(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_ModuleVersion(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_ModuleVersion(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_ConfigurationName(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_ConfigurationName(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_ConfigurationName(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_Name(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_Name(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_Name(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_Value(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_Value(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_Value(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Set_Ensure(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetPtr_Ensure(
    MSFT_nxNopResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_Clear_Ensure(
    MSFT_nxNopResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** MSFT_nxNopResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxNopResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxNopResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxNopResource_ConstRef OutputResource;
}
MSFT_nxNopResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxNopResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Construct(
    MSFT_nxNopResource_GetTargetResource* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_nxNopResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Clone(
    const MSFT_nxNopResource_GetTargetResource* self,
    MSFT_nxNopResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Destruct(
    MSFT_nxNopResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Delete(
    MSFT_nxNopResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Post(
    const MSFT_nxNopResource_GetTargetResource* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Set_MIReturn(
    MSFT_nxNopResource_GetTargetResource* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Clear_MIReturn(
    MSFT_nxNopResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Set_InputResource(
    MSFT_nxNopResource_GetTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_SetPtr_InputResource(
    MSFT_nxNopResource_GetTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Clear_InputResource(
    MSFT_nxNopResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Set_Flags(
    MSFT_nxNopResource_GetTargetResource* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Clear_Flags(
    MSFT_nxNopResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Set_OutputResource(
    MSFT_nxNopResource_GetTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_SetPtr_OutputResource(
    MSFT_nxNopResource_GetTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_GetTargetResource_Clear_OutputResource(
    MSFT_nxNopResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxNopResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxNopResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxNopResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxNopResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxNopResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Construct(
    MSFT_nxNopResource_TestTargetResource* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_nxNopResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Clone(
    const MSFT_nxNopResource_TestTargetResource* self,
    MSFT_nxNopResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Destruct(
    MSFT_nxNopResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Delete(
    MSFT_nxNopResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Post(
    const MSFT_nxNopResource_TestTargetResource* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Set_MIReturn(
    MSFT_nxNopResource_TestTargetResource* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Clear_MIReturn(
    MSFT_nxNopResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Set_InputResource(
    MSFT_nxNopResource_TestTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_SetPtr_InputResource(
    MSFT_nxNopResource_TestTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Clear_InputResource(
    MSFT_nxNopResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Set_Flags(
    MSFT_nxNopResource_TestTargetResource* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Clear_Flags(
    MSFT_nxNopResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Set_Result(
    MSFT_nxNopResource_TestTargetResource* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Clear_Result(
    MSFT_nxNopResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Set_ProviderContext(
    MSFT_nxNopResource_TestTargetResource* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_TestTargetResource_Clear_ProviderContext(
    MSFT_nxNopResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxNopResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxNopResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxNopResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxNopResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxNopResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Construct(
    MSFT_nxNopResource_SetTargetResource* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_nxNopResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Clone(
    const MSFT_nxNopResource_SetTargetResource* self,
    MSFT_nxNopResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Destruct(
    MSFT_nxNopResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Delete(
    MSFT_nxNopResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Post(
    const MSFT_nxNopResource_SetTargetResource* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Set_MIReturn(
    MSFT_nxNopResource_SetTargetResource* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Clear_MIReturn(
    MSFT_nxNopResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Set_InputResource(
    MSFT_nxNopResource_SetTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_SetPtr_InputResource(
    MSFT_nxNopResource_SetTargetResource* self,
    const MSFT_nxNopResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Clear_InputResource(
    MSFT_nxNopResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Set_ProviderContext(
    MSFT_nxNopResource_SetTargetResource* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Clear_ProviderContext(
    MSFT_nxNopResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Set_Flags(
    MSFT_nxNopResource_SetTargetResource* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxNopResource_SetTargetResource_Clear_Flags(
    MSFT_nxNopResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxNopResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxNopResource_Self MSFT_nxNopResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_Load(
    MSFT_nxNopResource_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_Unload(
    MSFT_nxNopResource_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_EnumerateInstances(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_GetInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_CreateInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_ModifyInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_DeleteInstance(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_nxNopResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_Invoke_GetTargetResource(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_nxNopResource* instanceName,
    const MSFT_nxNopResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_Invoke_TestTargetResource(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_nxNopResource* instanceName,
    const MSFT_nxNopResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxNopResource_Invoke_SetTargetResource(
    MSFT_nxNopResource_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_nxNopResource* instanceName,
    const MSFT_nxNopResource_SetTargetResource* in);


#endif /* _MSFT_nxNopResource_h */

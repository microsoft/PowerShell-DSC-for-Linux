/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_nxScriptResource_h
#define _OMI_nxScriptResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "OMI_nxScriptResource.h"

/*
**==============================================================================
**
** OMI_nxScriptResource [OMI_nxScriptResource]
**
** Keys:
**    GetScript
**    SetScript
**    TestScript
**
**==============================================================================
*/

typedef struct _OMI_nxScriptResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* OMI_nxScriptResource properties */
    /*KEY*/ MI_ConstStringField GetScript;
    /*KEY*/ MI_ConstStringField SetScript;
    /*KEY*/ MI_ConstStringField TestScript;
    MI_ConstStringField User;
    MI_ConstStringField Group;
    MI_ConstStringField Result;
}
OMI_nxScriptResource;

typedef struct _OMI_nxScriptResource_Ref
{
    OMI_nxScriptResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxScriptResource_Ref;

typedef struct _OMI_nxScriptResource_ConstRef
{
    MI_CONST OMI_nxScriptResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxScriptResource_ConstRef;

typedef struct _OMI_nxScriptResource_Array
{
    struct _OMI_nxScriptResource** data;
    MI_Uint32 size;
}
OMI_nxScriptResource_Array;

typedef struct _OMI_nxScriptResource_ConstArray
{
    struct _OMI_nxScriptResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_nxScriptResource_ConstArray;

typedef struct _OMI_nxScriptResource_ArrayRef
{
    OMI_nxScriptResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxScriptResource_ArrayRef;

typedef struct _OMI_nxScriptResource_ConstArrayRef
{
    OMI_nxScriptResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxScriptResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_nxScriptResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Construct(
    _Out_ OMI_nxScriptResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &OMI_nxScriptResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Clone(
    _In_ const OMI_nxScriptResource* self,
    _Outptr_ OMI_nxScriptResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_nxScriptResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_nxScriptResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Destruct(_Inout_ OMI_nxScriptResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Delete(_Inout_ OMI_nxScriptResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Post(
    _In_ const OMI_nxScriptResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Set_GetScript(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetPtr_GetScript(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Clear_GetScript(
    _Inout_ OMI_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Set_SetScript(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetPtr_SetScript(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Clear_SetScript(
    _Inout_ OMI_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Set_TestScript(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetPtr_TestScript(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Clear_TestScript(
    _Inout_ OMI_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Set_User(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetPtr_User(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Clear_User(
    _Inout_ OMI_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Set_Group(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetPtr_Group(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Clear_Group(
    _Inout_ OMI_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Set_Result(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetPtr_Result(
    _Inout_ OMI_nxScriptResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_Clear_Result(
    _Inout_ OMI_nxScriptResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** OMI_nxScriptResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _OMI_nxScriptResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_nxScriptResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ OMI_nxScriptResource_ConstRef OutputResource;
}
OMI_nxScriptResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_nxScriptResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Construct(
    _Out_ OMI_nxScriptResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &OMI_nxScriptResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Clone(
    _In_ const OMI_nxScriptResource_GetTargetResource* self,
    _Outptr_ OMI_nxScriptResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Destruct(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Delete(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Post(
    _In_ const OMI_nxScriptResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Set_MIReturn(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Clear_MIReturn(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Set_InputResource(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Clear_InputResource(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Set_Flags(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Clear_Flags(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Set_OutputResource(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_GetTargetResource_Clear_OutputResource(
    _Inout_ OMI_nxScriptResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** OMI_nxScriptResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _OMI_nxScriptResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_nxScriptResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
OMI_nxScriptResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_nxScriptResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Construct(
    _Out_ OMI_nxScriptResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &OMI_nxScriptResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Clone(
    _In_ const OMI_nxScriptResource_TestTargetResource* self,
    _Outptr_ OMI_nxScriptResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Destruct(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Delete(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Post(
    _In_ const OMI_nxScriptResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Set_MIReturn(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Clear_MIReturn(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Set_InputResource(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Clear_InputResource(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Set_Flags(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Clear_Flags(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Set_Result(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Clear_Result(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Set_ProviderContext(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ OMI_nxScriptResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_nxScriptResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _OMI_nxScriptResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_nxScriptResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
OMI_nxScriptResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_nxScriptResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Construct(
    _Out_ OMI_nxScriptResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &OMI_nxScriptResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Clone(
    _In_ const OMI_nxScriptResource_SetTargetResource* self,
    _Outptr_ OMI_nxScriptResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Destruct(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Delete(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Post(
    _In_ const OMI_nxScriptResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Set_MIReturn(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Clear_MIReturn(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Set_InputResource(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self,
    _In_ const OMI_nxScriptResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Clear_InputResource(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Set_ProviderContext(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Set_Flags(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxScriptResource_SetTargetResource_Clear_Flags(
    _Inout_ OMI_nxScriptResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_nxScriptResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_nxScriptResource_Self OMI_nxScriptResource_Self;

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_Load(
    _Outptr_result_maybenull_ OMI_nxScriptResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_Unload(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_EnumerateInstances(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_GetInstance(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxScriptResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_CreateInstance(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxScriptResource* newInstance);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_ModifyInstance(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxScriptResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_DeleteInstance(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxScriptResource* instanceName);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_Invoke_GetTargetResource(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const OMI_nxScriptResource* instanceName,
    _In_opt_ const OMI_nxScriptResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_Invoke_TestTargetResource(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const OMI_nxScriptResource* instanceName,
    _In_opt_ const OMI_nxScriptResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL OMI_nxScriptResource_Invoke_SetTargetResource(
    _In_opt_ OMI_nxScriptResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const OMI_nxScriptResource* instanceName,
    _In_opt_ const OMI_nxScriptResource_SetTargetResource* in);


#endif /* _OMI_nxScriptResource_h */

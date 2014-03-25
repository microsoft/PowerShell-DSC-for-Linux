/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxServiceResource_h
#define _MSFT_nxServiceResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxServiceResource.h"

/*
**==============================================================================
**
** MSFT_nxServiceResource [MSFT_nxServiceResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxServiceResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxServiceResource properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Controller;
    MI_ConstBooleanField Enabled;
    MI_ConstStringField State;
    MI_ConstBooleanField IsEnabled;
    MI_ConstStringField Status;
    MI_ConstStringField Path;
}
MSFT_nxServiceResource;

typedef struct _MSFT_nxServiceResource_Ref
{
    MSFT_nxServiceResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxServiceResource_Ref;

typedef struct _MSFT_nxServiceResource_ConstRef
{
    MI_CONST MSFT_nxServiceResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxServiceResource_ConstRef;

typedef struct _MSFT_nxServiceResource_Array
{
    struct _MSFT_nxServiceResource** data;
    MI_Uint32 size;
}
MSFT_nxServiceResource_Array;

typedef struct _MSFT_nxServiceResource_ConstArray
{
    struct _MSFT_nxServiceResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxServiceResource_ConstArray;

typedef struct _MSFT_nxServiceResource_ArrayRef
{
    MSFT_nxServiceResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxServiceResource_ArrayRef;

typedef struct _MSFT_nxServiceResource_ConstArrayRef
{
    MSFT_nxServiceResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxServiceResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxServiceResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Construct(
    _Out_ MSFT_nxServiceResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxServiceResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clone(
    _In_ const MSFT_nxServiceResource* self,
    _Outptr_ MSFT_nxServiceResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxServiceResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxServiceResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Destruct(_Inout_ MSFT_nxServiceResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Delete(_Inout_ MSFT_nxServiceResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Post(
    _In_ const MSFT_nxServiceResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Set_Name(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetPtr_Name(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clear_Name(
    _Inout_ MSFT_nxServiceResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Set_Controller(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetPtr_Controller(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clear_Controller(
    _Inout_ MSFT_nxServiceResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Set_Enabled(
    _Inout_ MSFT_nxServiceResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clear_Enabled(
    _Inout_ MSFT_nxServiceResource* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Set_State(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetPtr_State(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clear_State(
    _Inout_ MSFT_nxServiceResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Set_IsEnabled(
    _Inout_ MSFT_nxServiceResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsEnabled)->value = x;
    ((MI_BooleanField*)&self->IsEnabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clear_IsEnabled(
    _Inout_ MSFT_nxServiceResource* self)
{
    memset((void*)&self->IsEnabled, 0, sizeof(self->IsEnabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Set_Status(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetPtr_Status(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clear_Status(
    _Inout_ MSFT_nxServiceResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Set_Path(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetPtr_Path(
    _Inout_ MSFT_nxServiceResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_Clear_Path(
    _Inout_ MSFT_nxServiceResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

/*
**==============================================================================
**
** MSFT_nxServiceResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxServiceResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxServiceResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxServiceResource_ConstRef OutputResource;
}
MSFT_nxServiceResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxServiceResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Construct(
    _Out_ MSFT_nxServiceResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxServiceResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Clone(
    _In_ const MSFT_nxServiceResource_GetTargetResource* self,
    _Outptr_ MSFT_nxServiceResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Post(
    _In_ const MSFT_nxServiceResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxServiceResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxServiceResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxServiceResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxServiceResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxServiceResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxServiceResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Construct(
    _Out_ MSFT_nxServiceResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxServiceResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Clone(
    _In_ const MSFT_nxServiceResource_TestTargetResource* self,
    _Outptr_ MSFT_nxServiceResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Post(
    _In_ const MSFT_nxServiceResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxServiceResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxServiceResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxServiceResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxServiceResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxServiceResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxServiceResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Construct(
    _Out_ MSFT_nxServiceResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxServiceResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Clone(
    _In_ const MSFT_nxServiceResource_SetTargetResource* self,
    _Outptr_ MSFT_nxServiceResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Post(
    _In_ const MSFT_nxServiceResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self,
    _In_ const MSFT_nxServiceResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxServiceResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxServiceResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxServiceResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxServiceResource_Self MSFT_nxServiceResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_Load(
    _Outptr_result_maybenull_ MSFT_nxServiceResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_Unload(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_EnumerateInstances(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_GetInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_CreateInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_ModifyInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_DeleteInstance(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxServiceResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MSFT_nxServiceResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MSFT_nxServiceResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxServiceResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MSFT_nxServiceResource_SetTargetResource* in);


#endif /* _MSFT_nxServiceResource_h */

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxExecResource_h
#define _MSFT_nxExecResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxExecResource.h"

/*
**==============================================================================
**
** MSFT_nxExecResource [MSFT_nxExecResource]
**
** Keys:
**    Command
**
**==============================================================================
*/

typedef struct _MSFT_nxExecResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxExecResource properties */
    /*KEY*/ MI_ConstStringField Command;
    MI_ConstStringField Environment;
    MI_ConstBooleanField Shell;
    MI_ConstUint16Field Returncode;
    MI_ConstUint32Field Timeout;
    MI_ConstStringField User;
    MI_ConstStringField Group;
    MI_ConstStringField TestCommand;
}
MSFT_nxExecResource;

typedef struct _MSFT_nxExecResource_Ref
{
    MSFT_nxExecResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxExecResource_Ref;

typedef struct _MSFT_nxExecResource_ConstRef
{
    MI_CONST MSFT_nxExecResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxExecResource_ConstRef;

typedef struct _MSFT_nxExecResource_Array
{
    struct _MSFT_nxExecResource** data;
    MI_Uint32 size;
}
MSFT_nxExecResource_Array;

typedef struct _MSFT_nxExecResource_ConstArray
{
    struct _MSFT_nxExecResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxExecResource_ConstArray;

typedef struct _MSFT_nxExecResource_ArrayRef
{
    MSFT_nxExecResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxExecResource_ArrayRef;

typedef struct _MSFT_nxExecResource_ConstArrayRef
{
    MSFT_nxExecResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxExecResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxExecResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Construct(
    _Out_ MSFT_nxExecResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxExecResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clone(
    _In_ const MSFT_nxExecResource* self,
    _Outptr_ MSFT_nxExecResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxExecResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxExecResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Destruct(_Inout_ MSFT_nxExecResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Delete(_Inout_ MSFT_nxExecResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Post(
    _In_ const MSFT_nxExecResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_Command(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetPtr_Command(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_Command(
    _Inout_ MSFT_nxExecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_Environment(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetPtr_Environment(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_Environment(
    _Inout_ MSFT_nxExecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_Shell(
    _Inout_ MSFT_nxExecResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Shell)->value = x;
    ((MI_BooleanField*)&self->Shell)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_Shell(
    _Inout_ MSFT_nxExecResource* self)
{
    memset((void*)&self->Shell, 0, sizeof(self->Shell));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_Returncode(
    _Inout_ MSFT_nxExecResource* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Returncode)->value = x;
    ((MI_Uint16Field*)&self->Returncode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_Returncode(
    _Inout_ MSFT_nxExecResource* self)
{
    memset((void*)&self->Returncode, 0, sizeof(self->Returncode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_Timeout(
    _Inout_ MSFT_nxExecResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Timeout)->value = x;
    ((MI_Uint32Field*)&self->Timeout)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_Timeout(
    _Inout_ MSFT_nxExecResource* self)
{
    memset((void*)&self->Timeout, 0, sizeof(self->Timeout));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_User(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetPtr_User(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_User(
    _Inout_ MSFT_nxExecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_Group(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetPtr_Group(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_Group(
    _Inout_ MSFT_nxExecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Set_TestCommand(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetPtr_TestCommand(
    _Inout_ MSFT_nxExecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_Clear_TestCommand(
    _Inout_ MSFT_nxExecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** MSFT_nxExecResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxExecResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxExecResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxExecResource_ConstRef OutputResource;
}
MSFT_nxExecResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxExecResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Construct(
    _Out_ MSFT_nxExecResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxExecResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Clone(
    _In_ const MSFT_nxExecResource_GetTargetResource* self,
    _Outptr_ MSFT_nxExecResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Post(
    _In_ const MSFT_nxExecResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxExecResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxExecResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxExecResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxExecResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxExecResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxExecResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Construct(
    _Out_ MSFT_nxExecResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxExecResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Clone(
    _In_ const MSFT_nxExecResource_TestTargetResource* self,
    _Outptr_ MSFT_nxExecResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Post(
    _In_ const MSFT_nxExecResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxExecResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxExecResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxExecResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxExecResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxExecResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxExecResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Construct(
    _Out_ MSFT_nxExecResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxExecResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Clone(
    _In_ const MSFT_nxExecResource_SetTargetResource* self,
    _Outptr_ MSFT_nxExecResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Post(
    _In_ const MSFT_nxExecResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self,
    _In_ const MSFT_nxExecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxExecResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxExecResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxExecResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxExecResource_Self MSFT_nxExecResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_Load(
    _Outptr_result_maybenull_ MSFT_nxExecResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_Unload(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_EnumerateInstances(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_GetInstance(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxExecResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_CreateInstance(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxExecResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_ModifyInstance(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxExecResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_DeleteInstance(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxExecResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxExecResource* instanceName,
    _In_opt_ const MSFT_nxExecResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxExecResource* instanceName,
    _In_opt_ const MSFT_nxExecResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxExecResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxExecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxExecResource* instanceName,
    _In_opt_ const MSFT_nxExecResource_SetTargetResource* in);


#endif /* _MSFT_nxExecResource_h */

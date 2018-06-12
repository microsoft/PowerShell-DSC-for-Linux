/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_ChefInSpecResource_h
#define _MSFT_ChefInSpecResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_Credential.h"
#include "InSpec_Results.h"
#include "MSFT_ChefInSpecResource.h"

/*
**==============================================================================
**
** MSFT_ChefInSpecResource [MSFT_ChefInSpecResource]
**
** Keys:
**    Name
**    GithubPath
**
**==============================================================================
*/

typedef struct _MSFT_ChefInSpecResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    MI_ConstStringAField DependsOn;
    MI_ConstStringField ModuleName;
    MI_ConstStringField ModuleVersion;
    MI_ConstStringField ConfigurationName;
    MSFT_Credential_ConstRef PsDscRunAsCredential;
    /* MSFT_ChefInSpecResource properties */
    /*KEY*/ MI_ConstStringField Name;
    /*KEY*/ MI_ConstStringField GithubPath;
    InSpec_Results_ConstRef Result;
}
MSFT_ChefInSpecResource;

typedef struct _MSFT_ChefInSpecResource_Ref
{
    MSFT_ChefInSpecResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ChefInSpecResource_Ref;

typedef struct _MSFT_ChefInSpecResource_ConstRef
{
    MI_CONST MSFT_ChefInSpecResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ChefInSpecResource_ConstRef;

typedef struct _MSFT_ChefInSpecResource_Array
{
    struct _MSFT_ChefInSpecResource** data;
    MI_Uint32 size;
}
MSFT_ChefInSpecResource_Array;

typedef struct _MSFT_ChefInSpecResource_ConstArray
{
    struct _MSFT_ChefInSpecResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_ChefInSpecResource_ConstArray;

typedef struct _MSFT_ChefInSpecResource_ArrayRef
{
    MSFT_ChefInSpecResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ChefInSpecResource_ArrayRef;

typedef struct _MSFT_ChefInSpecResource_ConstArrayRef
{
    MSFT_ChefInSpecResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ChefInSpecResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_ChefInSpecResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Construct(
    _Out_ MSFT_ChefInSpecResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_ChefInSpecResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clone(
    _In_ const MSFT_ChefInSpecResource* self,
    _Outptr_ MSFT_ChefInSpecResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_ChefInSpecResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_ChefInSpecResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Destruct(_Inout_ MSFT_ChefInSpecResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Delete(_Inout_ MSFT_ChefInSpecResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Post(
    _In_ const MSFT_ChefInSpecResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_ResourceId(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_ResourceId(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_ResourceId(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_SourceInfo(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_SourceInfo(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_SourceInfo(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_DependsOn(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_DependsOn(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_DependsOn(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_ModuleName(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_ModuleName(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_ModuleName(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_ModuleVersion(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_ModuleVersion(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_ModuleVersion(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_ConfigurationName(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_ConfigurationName(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_ConfigurationName(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_PsDscRunAsCredential(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_PsDscRunAsCredential(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_PsDscRunAsCredential(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_Name(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_Name(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_Name(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_GithubPath(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_GithubPath(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_GithubPath(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Set_Result(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_ const InSpec_Results* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetPtr_Result(
    _Inout_ MSFT_ChefInSpecResource* self,
    _In_ const InSpec_Results* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_Clear_Result(
    _Inout_ MSFT_ChefInSpecResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

/*
**==============================================================================
**
** MSFT_ChefInSpecResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_ChefInSpecResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_ChefInSpecResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_ChefInSpecResource_ConstRef OutputResource;
}
MSFT_ChefInSpecResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_ChefInSpecResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Construct(
    _Out_ MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_ChefInSpecResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Clone(
    _In_ const MSFT_ChefInSpecResource_GetTargetResource* self,
    _Outptr_ MSFT_ChefInSpecResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Destruct(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Delete(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Post(
    _In_ const MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_ChefInSpecResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_ChefInSpecResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_ChefInSpecResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_ChefInSpecResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_ChefInSpecResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_ChefInSpecResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Construct(
    _Out_ MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_ChefInSpecResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Clone(
    _In_ const MSFT_ChefInSpecResource_TestTargetResource* self,
    _Outptr_ MSFT_ChefInSpecResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Destruct(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Delete(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Post(
    _In_ const MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_ChefInSpecResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_ChefInSpecResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_ChefInSpecResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_ChefInSpecResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_ChefInSpecResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_ChefInSpecResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Construct(
    _Out_ MSFT_ChefInSpecResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_ChefInSpecResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Clone(
    _In_ const MSFT_ChefInSpecResource_SetTargetResource* self,
    _Outptr_ MSFT_ChefInSpecResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Destruct(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Delete(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Post(
    _In_ const MSFT_ChefInSpecResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self,
    _In_ const MSFT_ChefInSpecResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ChefInSpecResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_ChefInSpecResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_ChefInSpecResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_ChefInSpecResource_Self MSFT_ChefInSpecResource_Self;

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_Load(
    _Outptr_result_maybenull_ MSFT_ChefInSpecResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_Unload(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_EnumerateInstances(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_GetInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_CreateInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_ModifyInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_DeleteInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MSFT_ChefInSpecResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MSFT_ChefInSpecResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_ChefInSpecResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MSFT_ChefInSpecResource_SetTargetResource* in);


#endif /* _MSFT_ChefInSpecResource_h */

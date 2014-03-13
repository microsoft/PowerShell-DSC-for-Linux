/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Linux_File_h
#define _Linux_File_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "Linux_File.h"

/*
**==============================================================================
**
** Linux_File [Linux_File]
**
** Keys:
**    DestinationPath
**
**==============================================================================
*/

typedef struct _Linux_File /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* Linux_File properties */
    /*KEY*/ MI_ConstStringField DestinationPath;
    MI_ConstStringField SourcePath;
    MI_ConstStringField Ensure;
    MI_ConstStringField Type;
    MI_ConstStringField Contents;
    MI_ConstStringField Checksum;
    MI_ConstStringField Recurse;
    MI_ConstStringField Force;
    MI_ConstStringField Links;
    MI_ConstStringField Group;
    MI_ConstStringField Mode;
    MI_ConstStringField Owner;
    MI_ConstDatetimeField CreatedDate;
    MI_ConstDatetimeField ModifiedDate;
}
Linux_File;

typedef struct _Linux_File_Ref
{
    Linux_File* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Linux_File_Ref;

typedef struct _Linux_File_ConstRef
{
    MI_CONST Linux_File* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Linux_File_ConstRef;

typedef struct _Linux_File_Array
{
    struct _Linux_File** data;
    MI_Uint32 size;
}
Linux_File_Array;

typedef struct _Linux_File_ConstArray
{
    struct _Linux_File MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Linux_File_ConstArray;

typedef struct _Linux_File_ArrayRef
{
    Linux_File_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Linux_File_ArrayRef;

typedef struct _Linux_File_ConstArrayRef
{
    Linux_File_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Linux_File_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Linux_File_rtti;

MI_INLINE MI_Result MI_CALL Linux_File_Construct(
    _Out_ Linux_File* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &Linux_File_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clone(
    _In_ const Linux_File* self,
    _Outptr_ Linux_File** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Linux_File_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Linux_File_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Linux_File_Destruct(_Inout_ Linux_File* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_Delete(_Inout_ Linux_File* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_Post(
    _In_ const Linux_File* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_DestinationPath(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_DestinationPath(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_DestinationPath(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_SourcePath(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_SourcePath(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_SourcePath(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Ensure(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Ensure(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Ensure(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Type(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Type(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Type(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Contents(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Contents(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Contents(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Checksum(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Checksum(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Checksum(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Recurse(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Recurse(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Recurse(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Force(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Force(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Force(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Links(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Links(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Links(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Group(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Group(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Group(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Mode(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Mode(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Mode(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_Owner(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetPtr_Owner(
    _Inout_ Linux_File* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_Owner(
    _Inout_ Linux_File* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_CreatedDate(
    _Inout_ Linux_File* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->CreatedDate)->value = x;
    ((MI_DatetimeField*)&self->CreatedDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_CreatedDate(
    _Inout_ Linux_File* self)
{
    memset((void*)&self->CreatedDate, 0, sizeof(self->CreatedDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_Set_ModifiedDate(
    _Inout_ Linux_File* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ModifiedDate)->value = x;
    ((MI_DatetimeField*)&self->ModifiedDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_Clear_ModifiedDate(
    _Inout_ Linux_File* self)
{
    memset((void*)&self->ModifiedDate, 0, sizeof(self->ModifiedDate));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Linux_File.GetTargetResource()
**
**==============================================================================
*/

typedef struct _Linux_File_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ Linux_File_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ Linux_File_ConstRef OutputResource;
}
Linux_File_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl Linux_File_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Construct(
    _Out_ Linux_File_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &Linux_File_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Clone(
    _In_ const Linux_File_GetTargetResource* self,
    _Outptr_ Linux_File_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Destruct(
    _Inout_ Linux_File_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Delete(
    _Inout_ Linux_File_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Post(
    _In_ const Linux_File_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Set_MIReturn(
    _Inout_ Linux_File_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Clear_MIReturn(
    _Inout_ Linux_File_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Set_InputResource(
    _Inout_ Linux_File_GetTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_SetPtr_InputResource(
    _Inout_ Linux_File_GetTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Clear_InputResource(
    _Inout_ Linux_File_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Set_Flags(
    _Inout_ Linux_File_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Clear_Flags(
    _Inout_ Linux_File_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Set_OutputResource(
    _Inout_ Linux_File_GetTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_SetPtr_OutputResource(
    _Inout_ Linux_File_GetTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_GetTargetResource_Clear_OutputResource(
    _Inout_ Linux_File_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** Linux_File.TestTargetResource()
**
**==============================================================================
*/

typedef struct _Linux_File_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ Linux_File_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
Linux_File_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl Linux_File_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Construct(
    _Out_ Linux_File_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &Linux_File_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Clone(
    _In_ const Linux_File_TestTargetResource* self,
    _Outptr_ Linux_File_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Destruct(
    _Inout_ Linux_File_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Delete(
    _Inout_ Linux_File_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Post(
    _In_ const Linux_File_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Set_MIReturn(
    _Inout_ Linux_File_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Clear_MIReturn(
    _Inout_ Linux_File_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Set_InputResource(
    _Inout_ Linux_File_TestTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_SetPtr_InputResource(
    _Inout_ Linux_File_TestTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Clear_InputResource(
    _Inout_ Linux_File_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Set_Flags(
    _Inout_ Linux_File_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Clear_Flags(
    _Inout_ Linux_File_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Set_Result(
    _Inout_ Linux_File_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Clear_Result(
    _Inout_ Linux_File_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Set_ProviderContext(
    _Inout_ Linux_File_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_TestTargetResource_Clear_ProviderContext(
    _Inout_ Linux_File_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Linux_File.SetTargetResource()
**
**==============================================================================
*/

typedef struct _Linux_File_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ Linux_File_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
Linux_File_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl Linux_File_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Construct(
    _Out_ Linux_File_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &Linux_File_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Clone(
    _In_ const Linux_File_SetTargetResource* self,
    _Outptr_ Linux_File_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Destruct(
    _Inout_ Linux_File_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Delete(
    _Inout_ Linux_File_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Post(
    _In_ const Linux_File_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Set_MIReturn(
    _Inout_ Linux_File_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Clear_MIReturn(
    _Inout_ Linux_File_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Set_InputResource(
    _Inout_ Linux_File_SetTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_SetPtr_InputResource(
    _Inout_ Linux_File_SetTargetResource* self,
    _In_ const Linux_File* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Clear_InputResource(
    _Inout_ Linux_File_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Set_ProviderContext(
    _Inout_ Linux_File_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Clear_ProviderContext(
    _Inout_ Linux_File_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Set_Flags(
    _Inout_ Linux_File_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Linux_File_SetTargetResource_Clear_Flags(
    _Inout_ Linux_File_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Linux_File provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Linux_File_Self Linux_File_Self;

MI_EXTERN_C void MI_CALL Linux_File_Load(
    _Outptr_result_maybenull_ Linux_File_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Linux_File_Unload(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Linux_File_EnumerateInstances(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Linux_File_GetInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Linux_File_CreateInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* newInstance);

MI_EXTERN_C void MI_CALL Linux_File_ModifyInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Linux_File_DeleteInstance(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Linux_File* instanceName);

MI_EXTERN_C void MI_CALL Linux_File_Invoke_GetTargetResource(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Linux_File* instanceName,
    _In_opt_ const Linux_File_GetTargetResource* in);

MI_EXTERN_C void MI_CALL Linux_File_Invoke_TestTargetResource(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Linux_File* instanceName,
    _In_opt_ const Linux_File_TestTargetResource* in);

MI_EXTERN_C void MI_CALL Linux_File_Invoke_SetTargetResource(
    _In_opt_ Linux_File_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Linux_File* instanceName,
    _In_opt_ const Linux_File_SetTargetResource* in);


#endif /* _Linux_File_h */

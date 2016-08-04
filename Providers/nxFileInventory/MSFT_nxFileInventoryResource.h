/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxFileInventoryResource_h
#define _MSFT_nxFileInventoryResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxFileInventoryResource.h"

/*
**==============================================================================
**
** MSFT_nxFileInventoryResource [MSFT_nxFileInventoryResource]
**
** Keys:
**    DestinationPath
**
**==============================================================================
*/

typedef struct _MSFT_nxFileInventoryResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxFileInventoryResource properties */
    /*KEY*/ MI_ConstStringField DestinationPath;
    MI_ConstBooleanField Recurse;
    MI_ConstBooleanField UseSudo;
    MI_ConstStringField Links;
    MI_ConstStringField Checksum;
    MI_ConstStringField Type;
    MI_ConstUint32Field MaxContentsReturnable;
    MI_ConstUint64Field MaxOutputSize;
    MI_ConstStringField Contents;
    MI_ConstDatetimeField ModifiedDate;
    MI_ConstDatetimeField CreatedDate;
    MI_ConstStringField Mode;
    MI_ConstStringField Group;
    MI_ConstStringField Owner;
    MI_ConstUint64Field FileSize;
}
MSFT_nxFileInventoryResource;

typedef struct _MSFT_nxFileInventoryResource_Ref
{
    MSFT_nxFileInventoryResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFileInventoryResource_Ref;

typedef struct _MSFT_nxFileInventoryResource_ConstRef
{
    MI_CONST MSFT_nxFileInventoryResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFileInventoryResource_ConstRef;

typedef struct _MSFT_nxFileInventoryResource_Array
{
    struct _MSFT_nxFileInventoryResource** data;
    MI_Uint32 size;
}
MSFT_nxFileInventoryResource_Array;

typedef struct _MSFT_nxFileInventoryResource_ConstArray
{
    struct _MSFT_nxFileInventoryResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxFileInventoryResource_ConstArray;

typedef struct _MSFT_nxFileInventoryResource_ArrayRef
{
    MSFT_nxFileInventoryResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFileInventoryResource_ArrayRef;

typedef struct _MSFT_nxFileInventoryResource_ConstArrayRef
{
    MSFT_nxFileInventoryResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFileInventoryResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxFileInventoryResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Construct(
    _Out_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxFileInventoryResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clone(
    _In_ const MSFT_nxFileInventoryResource* self,
    _Outptr_ MSFT_nxFileInventoryResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxFileInventoryResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxFileInventoryResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Destruct(_Inout_ MSFT_nxFileInventoryResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Delete(_Inout_ MSFT_nxFileInventoryResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Post(
    _In_ const MSFT_nxFileInventoryResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_DestinationPath(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_DestinationPath(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_DestinationPath(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Recurse(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Recurse)->value = x;
    ((MI_BooleanField*)&self->Recurse)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Recurse(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    memset((void*)&self->Recurse, 0, sizeof(self->Recurse));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_UseSudo(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->UseSudo)->value = x;
    ((MI_BooleanField*)&self->UseSudo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_UseSudo(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    memset((void*)&self->UseSudo, 0, sizeof(self->UseSudo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Links(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_Links(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Links(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Checksum(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_Checksum(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Checksum(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Type(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_Type(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Type(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_MaxContentsReturnable(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxContentsReturnable)->value = x;
    ((MI_Uint32Field*)&self->MaxContentsReturnable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_MaxContentsReturnable(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    memset((void*)&self->MaxContentsReturnable, 0, sizeof(self->MaxContentsReturnable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_MaxOutputSize(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxOutputSize)->value = x;
    ((MI_Uint64Field*)&self->MaxOutputSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_MaxOutputSize(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    memset((void*)&self->MaxOutputSize, 0, sizeof(self->MaxOutputSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Contents(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_Contents(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Contents(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_ModifiedDate(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ModifiedDate)->value = x;
    ((MI_DatetimeField*)&self->ModifiedDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_ModifiedDate(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    memset((void*)&self->ModifiedDate, 0, sizeof(self->ModifiedDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_CreatedDate(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->CreatedDate)->value = x;
    ((MI_DatetimeField*)&self->CreatedDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_CreatedDate(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    memset((void*)&self->CreatedDate, 0, sizeof(self->CreatedDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Mode(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_Mode(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Mode(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Group(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_Group(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Group(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_Owner(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetPtr_Owner(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_Owner(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Set_FileSize(
    _Inout_ MSFT_nxFileInventoryResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->FileSize)->value = x;
    ((MI_Uint64Field*)&self->FileSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_Clear_FileSize(
    _Inout_ MSFT_nxFileInventoryResource* self)
{
    memset((void*)&self->FileSize, 0, sizeof(self->FileSize));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxFileInventoryResource.InventoryTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxFileInventoryResource_InventoryTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxFileInventoryResource_ConstRef InputResource;
    /*OUT*/ MSFT_nxFileInventoryResource_ConstArrayRef inventory;
}
MSFT_nxFileInventoryResource_InventoryTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxFileInventoryResource_InventoryTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Construct(
    _Out_ MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxFileInventoryResource_InventoryTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Clone(
    _In_ const MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _Outptr_ MSFT_nxFileInventoryResource_InventoryTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Destruct(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Delete(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Post(
    _In_ const MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Set_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Set_inventory(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _In_reads_opt_(size) const MSFT_nxFileInventoryResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_SetPtr_inventory(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self,
    _In_reads_opt_(size) const MSFT_nxFileInventoryResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_InventoryTargetResource_Clear_inventory(
    _Inout_ MSFT_nxFileInventoryResource_InventoryTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_nxFileInventoryResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxFileInventoryResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxFileInventoryResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxFileInventoryResource_ConstRef OutputResource;
}
MSFT_nxFileInventoryResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxFileInventoryResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Construct(
    _Out_ MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxFileInventoryResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Clone(
    _In_ const MSFT_nxFileInventoryResource_GetTargetResource* self,
    _Outptr_ MSFT_nxFileInventoryResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Post(
    _In_ const MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxFileInventoryResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxFileInventoryResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxFileInventoryResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxFileInventoryResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxFileInventoryResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxFileInventoryResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Construct(
    _Out_ MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxFileInventoryResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Clone(
    _In_ const MSFT_nxFileInventoryResource_TestTargetResource* self,
    _Outptr_ MSFT_nxFileInventoryResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Post(
    _In_ const MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxFileInventoryResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxFileInventoryResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxFileInventoryResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxFileInventoryResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxFileInventoryResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxFileInventoryResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Construct(
    _Out_ MSFT_nxFileInventoryResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxFileInventoryResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Clone(
    _In_ const MSFT_nxFileInventoryResource_SetTargetResource* self,
    _Outptr_ MSFT_nxFileInventoryResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Post(
    _In_ const MSFT_nxFileInventoryResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self,
    _In_ const MSFT_nxFileInventoryResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFileInventoryResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxFileInventoryResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxFileInventoryResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxFileInventoryResource_Self MSFT_nxFileInventoryResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_Load(
    _Outptr_result_maybenull_ MSFT_nxFileInventoryResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_Unload(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_EnumerateInstances(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_GetInstance(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileInventoryResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_CreateInstance(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileInventoryResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_ModifyInstance(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileInventoryResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_DeleteInstance(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFileInventoryResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_Invoke_InventoryTargetResource(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFileInventoryResource* instanceName,
    _In_opt_ const MSFT_nxFileInventoryResource_InventoryTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFileInventoryResource* instanceName,
    _In_opt_ const MSFT_nxFileInventoryResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFileInventoryResource* instanceName,
    _In_opt_ const MSFT_nxFileInventoryResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxFileInventoryResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxFileInventoryResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFileInventoryResource* instanceName,
    _In_opt_ const MSFT_nxFileInventoryResource_SetTargetResource* in);


#endif /* _MSFT_nxFileInventoryResource_h */

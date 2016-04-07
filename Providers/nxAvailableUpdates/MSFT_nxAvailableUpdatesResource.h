/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxAvailableUpdatesResource_h
#define _MSFT_nxAvailableUpdatesResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxAvailableUpdatesResource.h"

/*
**==============================================================================
**
** MSFT_nxAvailableUpdatesResource [MSFT_nxAvailableUpdatesResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxAvailableUpdatesResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxAvailableUpdatesResource properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField BuildDate;
    MI_ConstStringField Repository;
    MI_ConstStringField Version;
    MI_ConstStringField Architecture;
}
MSFT_nxAvailableUpdatesResource;

typedef struct _MSFT_nxAvailableUpdatesResource_Ref
{
    MSFT_nxAvailableUpdatesResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAvailableUpdatesResource_Ref;

typedef struct _MSFT_nxAvailableUpdatesResource_ConstRef
{
    MI_CONST MSFT_nxAvailableUpdatesResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAvailableUpdatesResource_ConstRef;

typedef struct _MSFT_nxAvailableUpdatesResource_Array
{
    struct _MSFT_nxAvailableUpdatesResource** data;
    MI_Uint32 size;
}
MSFT_nxAvailableUpdatesResource_Array;

typedef struct _MSFT_nxAvailableUpdatesResource_ConstArray
{
    struct _MSFT_nxAvailableUpdatesResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxAvailableUpdatesResource_ConstArray;

typedef struct _MSFT_nxAvailableUpdatesResource_ArrayRef
{
    MSFT_nxAvailableUpdatesResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAvailableUpdatesResource_ArrayRef;

typedef struct _MSFT_nxAvailableUpdatesResource_ConstArrayRef
{
    MSFT_nxAvailableUpdatesResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxAvailableUpdatesResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxAvailableUpdatesResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Construct(
    _Out_ MSFT_nxAvailableUpdatesResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxAvailableUpdatesResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Clone(
    _In_ const MSFT_nxAvailableUpdatesResource* self,
    _Outptr_ MSFT_nxAvailableUpdatesResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxAvailableUpdatesResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxAvailableUpdatesResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Destruct(_Inout_ MSFT_nxAvailableUpdatesResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Delete(_Inout_ MSFT_nxAvailableUpdatesResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Post(
    _In_ const MSFT_nxAvailableUpdatesResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Set_Name(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetPtr_Name(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Clear_Name(
    _Inout_ MSFT_nxAvailableUpdatesResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Set_BuildDate(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetPtr_BuildDate(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Clear_BuildDate(
    _Inout_ MSFT_nxAvailableUpdatesResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Set_Repository(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetPtr_Repository(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Clear_Repository(
    _Inout_ MSFT_nxAvailableUpdatesResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Set_Version(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetPtr_Version(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Clear_Version(
    _Inout_ MSFT_nxAvailableUpdatesResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Set_Architecture(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetPtr_Architecture(
    _Inout_ MSFT_nxAvailableUpdatesResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_Clear_Architecture(
    _Inout_ MSFT_nxAvailableUpdatesResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MSFT_nxAvailableUpdatesResource.InventoryTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAvailableUpdatesResource_InventoryTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAvailableUpdatesResource_ConstRef InputResource;
    /*OUT*/ MSFT_nxAvailableUpdatesResource_ConstArrayRef inventory;
}
MSFT_nxAvailableUpdatesResource_InventoryTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAvailableUpdatesResource_InventoryTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Construct(
    _Out_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAvailableUpdatesResource_InventoryTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Clone(
    _In_ const MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _Outptr_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Destruct(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Delete(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Post(
    _In_ const MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Set_inventory(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _In_reads_opt_(size) const MSFT_nxAvailableUpdatesResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_SetPtr_inventory(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self,
    _In_reads_opt_(size) const MSFT_nxAvailableUpdatesResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_InventoryTargetResource_Clear_inventory(
    _Inout_ MSFT_nxAvailableUpdatesResource_InventoryTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_nxAvailableUpdatesResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAvailableUpdatesResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAvailableUpdatesResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxAvailableUpdatesResource_ConstRef OutputResource;
}
MSFT_nxAvailableUpdatesResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAvailableUpdatesResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Construct(
    _Out_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAvailableUpdatesResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Clone(
    _In_ const MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _Outptr_ MSFT_nxAvailableUpdatesResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Post(
    _In_ const MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxAvailableUpdatesResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAvailableUpdatesResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAvailableUpdatesResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxAvailableUpdatesResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAvailableUpdatesResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Construct(
    _Out_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAvailableUpdatesResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Clone(
    _In_ const MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _Outptr_ MSFT_nxAvailableUpdatesResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Post(
    _In_ const MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxAvailableUpdatesResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxAvailableUpdatesResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxAvailableUpdatesResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxAvailableUpdatesResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxAvailableUpdatesResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxAvailableUpdatesResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Construct(
    _Out_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxAvailableUpdatesResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Clone(
    _In_ const MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _Outptr_ MSFT_nxAvailableUpdatesResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Post(
    _In_ const MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _In_ const MSFT_nxAvailableUpdatesResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxAvailableUpdatesResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxAvailableUpdatesResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxAvailableUpdatesResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxAvailableUpdatesResource_Self MSFT_nxAvailableUpdatesResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_Load(
    _Outptr_result_maybenull_ MSFT_nxAvailableUpdatesResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_Unload(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_EnumerateInstances(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_GetInstance(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAvailableUpdatesResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_CreateInstance(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAvailableUpdatesResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_ModifyInstance(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAvailableUpdatesResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_DeleteInstance(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxAvailableUpdatesResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_Invoke_InventoryTargetResource(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAvailableUpdatesResource* instanceName,
    _In_opt_ const MSFT_nxAvailableUpdatesResource_InventoryTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAvailableUpdatesResource* instanceName,
    _In_opt_ const MSFT_nxAvailableUpdatesResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAvailableUpdatesResource* instanceName,
    _In_opt_ const MSFT_nxAvailableUpdatesResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxAvailableUpdatesResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxAvailableUpdatesResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxAvailableUpdatesResource* instanceName,
    _In_opt_ const MSFT_nxAvailableUpdatesResource_SetTargetResource* in);


#endif /* _MSFT_nxAvailableUpdatesResource_h */

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxPackageResource_h
#define _MSFT_nxPackageResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxPackageResource.h"

/*
**==============================================================================
**
** MSFT_nxPackageResource [MSFT_nxPackageResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxPackageResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxPackageResource properties */
    MI_ConstStringField Ensure;
    MI_ConstStringField PackageManager;
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField FilePath;
    MI_ConstBooleanField PackageGroup;
    MI_ConstStringField Arguments;
    MI_ConstUint32Field ReturnCode;
    MI_ConstStringField PackageDescription;
    MI_ConstStringField Publisher;
    MI_ConstStringField InstalledOn;
    MI_ConstUint32Field Size;
    MI_ConstStringField Version;
    MI_ConstBooleanField Installed;
    MI_ConstStringField Architecture;
}
MSFT_nxPackageResource;

typedef struct _MSFT_nxPackageResource_Ref
{
    MSFT_nxPackageResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxPackageResource_Ref;

typedef struct _MSFT_nxPackageResource_ConstRef
{
    MI_CONST MSFT_nxPackageResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxPackageResource_ConstRef;

typedef struct _MSFT_nxPackageResource_Array
{
    struct _MSFT_nxPackageResource** data;
    MI_Uint32 size;
}
MSFT_nxPackageResource_Array;

typedef struct _MSFT_nxPackageResource_ConstArray
{
    struct _MSFT_nxPackageResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxPackageResource_ConstArray;

typedef struct _MSFT_nxPackageResource_ArrayRef
{
    MSFT_nxPackageResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxPackageResource_ArrayRef;

typedef struct _MSFT_nxPackageResource_ConstArrayRef
{
    MSFT_nxPackageResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxPackageResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxPackageResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Construct(
    _Out_ MSFT_nxPackageResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxPackageResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clone(
    _In_ const MSFT_nxPackageResource* self,
    _Outptr_ MSFT_nxPackageResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxPackageResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxPackageResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Destruct(_Inout_ MSFT_nxPackageResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Delete(_Inout_ MSFT_nxPackageResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Post(
    _In_ const MSFT_nxPackageResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Ensure(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_Ensure(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Ensure(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_PackageManager(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_PackageManager(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_PackageManager(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Name(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_Name(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Name(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_FilePath(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_FilePath(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_FilePath(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_PackageGroup(
    _Inout_ MSFT_nxPackageResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->PackageGroup)->value = x;
    ((MI_BooleanField*)&self->PackageGroup)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_PackageGroup(
    _Inout_ MSFT_nxPackageResource* self)
{
    memset((void*)&self->PackageGroup, 0, sizeof(self->PackageGroup));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Arguments(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_Arguments(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Arguments(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_ReturnCode(
    _Inout_ MSFT_nxPackageResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ReturnCode)->value = x;
    ((MI_Uint32Field*)&self->ReturnCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_ReturnCode(
    _Inout_ MSFT_nxPackageResource* self)
{
    memset((void*)&self->ReturnCode, 0, sizeof(self->ReturnCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_PackageDescription(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_PackageDescription(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_PackageDescription(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Publisher(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_Publisher(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Publisher(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_InstalledOn(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_InstalledOn(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_InstalledOn(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Size(
    _Inout_ MSFT_nxPackageResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Size)->value = x;
    ((MI_Uint32Field*)&self->Size)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Size(
    _Inout_ MSFT_nxPackageResource* self)
{
    memset((void*)&self->Size, 0, sizeof(self->Size));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Version(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_Version(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Version(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Installed(
    _Inout_ MSFT_nxPackageResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Installed)->value = x;
    ((MI_BooleanField*)&self->Installed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Installed(
    _Inout_ MSFT_nxPackageResource* self)
{
    memset((void*)&self->Installed, 0, sizeof(self->Installed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Set_Architecture(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetPtr_Architecture(
    _Inout_ MSFT_nxPackageResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_Clear_Architecture(
    _Inout_ MSFT_nxPackageResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

/*
**==============================================================================
**
** MSFT_nxPackageResource.InventoryTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxPackageResource_InventoryTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxPackageResource_ConstRef InputResource;
    /*OUT*/ MSFT_nxPackageResource_ConstArrayRef inventory;
}
MSFT_nxPackageResource_InventoryTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxPackageResource_InventoryTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Construct(
    _Out_ MSFT_nxPackageResource_InventoryTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxPackageResource_InventoryTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Clone(
    _In_ const MSFT_nxPackageResource_InventoryTargetResource* self,
    _Outptr_ MSFT_nxPackageResource_InventoryTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Destruct(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Delete(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Post(
    _In_ const MSFT_nxPackageResource_InventoryTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Set_InputResource(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Set_inventory(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self,
    _In_reads_opt_(size) const MSFT_nxPackageResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_SetPtr_inventory(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self,
    _In_reads_opt_(size) const MSFT_nxPackageResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_InventoryTargetResource_Clear_inventory(
    _Inout_ MSFT_nxPackageResource_InventoryTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_nxPackageResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxPackageResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxPackageResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxPackageResource_ConstRef OutputResource;
}
MSFT_nxPackageResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxPackageResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Construct(
    _Out_ MSFT_nxPackageResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxPackageResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Clone(
    _In_ const MSFT_nxPackageResource_GetTargetResource* self,
    _Outptr_ MSFT_nxPackageResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Post(
    _In_ const MSFT_nxPackageResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxPackageResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxPackageResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxPackageResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxPackageResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxPackageResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxPackageResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Construct(
    _Out_ MSFT_nxPackageResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxPackageResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Clone(
    _In_ const MSFT_nxPackageResource_TestTargetResource* self,
    _Outptr_ MSFT_nxPackageResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Post(
    _In_ const MSFT_nxPackageResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxPackageResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxPackageResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxPackageResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxPackageResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxPackageResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxPackageResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Construct(
    _Out_ MSFT_nxPackageResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxPackageResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Clone(
    _In_ const MSFT_nxPackageResource_SetTargetResource* self,
    _Outptr_ MSFT_nxPackageResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Post(
    _In_ const MSFT_nxPackageResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self,
    _In_ const MSFT_nxPackageResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxPackageResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxPackageResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxPackageResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxPackageResource_Self MSFT_nxPackageResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_Load(
    _Outptr_result_maybenull_ MSFT_nxPackageResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_Unload(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_EnumerateInstances(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_GetInstance(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxPackageResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_CreateInstance(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxPackageResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_ModifyInstance(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxPackageResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_DeleteInstance(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxPackageResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_Invoke_InventoryTargetResource(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxPackageResource* instanceName,
    _In_opt_ const MSFT_nxPackageResource_InventoryTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxPackageResource* instanceName,
    _In_opt_ const MSFT_nxPackageResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxPackageResource* instanceName,
    _In_opt_ const MSFT_nxPackageResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxPackageResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxPackageResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxPackageResource* instanceName,
    _In_opt_ const MSFT_nxPackageResource_SetTargetResource* in);


#endif /* _MSFT_nxPackageResource_h */

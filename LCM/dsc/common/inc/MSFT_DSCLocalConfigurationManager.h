/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_DSCLocalConfigurationManager_h
#define _MSFT_DSCLocalConfigurationManager_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_DSCMetaConfiguration.h"

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager [MSFT_DSCLocalConfigurationManager]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager
{
    MI_Instance __instance;
    /* MSFT_DSCLocalConfigurationManager properties */
}
MSFT_DSCLocalConfigurationManager;

typedef struct _MSFT_DSCLocalConfigurationManager_Ref
{
    MSFT_DSCLocalConfigurationManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigurationManager_Ref;

typedef struct _MSFT_DSCLocalConfigurationManager_ConstRef
{
    MI_CONST MSFT_DSCLocalConfigurationManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigurationManager_ConstRef;

typedef struct _MSFT_DSCLocalConfigurationManager_Array
{
    struct _MSFT_DSCLocalConfigurationManager** data;
    MI_Uint32 size;
}
MSFT_DSCLocalConfigurationManager_Array;

typedef struct _MSFT_DSCLocalConfigurationManager_ConstArray
{
    struct _MSFT_DSCLocalConfigurationManager MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_DSCLocalConfigurationManager_ConstArray;

typedef struct _MSFT_DSCLocalConfigurationManager_ArrayRef
{
    MSFT_DSCLocalConfigurationManager_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigurationManager_ArrayRef;

typedef struct _MSFT_DSCLocalConfigurationManager_ConstArrayRef
{
    MSFT_DSCLocalConfigurationManager_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigurationManager_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_DSCLocalConfigurationManager_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_DSCLocalConfigurationManager_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_DSCLocalConfigurationManager_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_DSCLocalConfigurationManager_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_Destruct(_Inout_ MSFT_DSCLocalConfigurationManager* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_Delete(_Inout_ MSFT_DSCLocalConfigurationManager* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_Post(
    _In_ const MSFT_DSCLocalConfigurationManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.SendConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_SendConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField ConfigurationData;
    /*IN*/ MI_ConstBooleanField force;
}
MSFT_DSCLocalConfigurationManager_SendConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_SendConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_SendConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_SendConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Set_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_SetPtr_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Clear_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Set_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->force)->value = x;
    ((MI_BooleanField*)&self->force)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfiguration_Clear_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfiguration* self)
{
    memset((void*)&self->force, 0, sizeof(self->force));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.SendConfigurationApply()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_SendConfigurationApply
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField ConfigurationData;
    /*IN*/ MI_ConstBooleanField force;
}
MSFT_DSCLocalConfigurationManager_SendConfigurationApply;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_SendConfigurationApply_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Set_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_SetPtr_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Clear_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Set_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->force)->value = x;
    ((MI_BooleanField*)&self->force)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Clear_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendConfigurationApply* self)
{
    memset((void*)&self->force, 0, sizeof(self->force));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.GetConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_GetConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField configurationData;
    /*OUT*/ OMI_BaseResource_ConstArrayRef configurations;
}
MSFT_DSCLocalConfigurationManager_GetConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_GetConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_GetConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_GetConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Set_configurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_SetPtr_configurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Clear_configurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Set_configurations(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _In_reads_opt_(size) const OMI_BaseResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_SetPtr_configurations(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self,
    _In_reads_opt_(size) const OMI_BaseResource * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetConfiguration_Clear_configurations(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.TestConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_TestConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField configurationData;
    /*OUT*/ MI_ConstBooleanField InDesiredState;
    /*OUT*/ MI_ConstStringAField ResourceId;
}
MSFT_DSCLocalConfigurationManager_TestConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_TestConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_TestConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_TestConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_configurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_SetPtr_configurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Clear_configurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_InDesiredState(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->InDesiredState)->value = x;
    ((MI_BooleanField*)&self->InDesiredState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Clear_InDesiredState(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self)
{
    memset((void*)&self->InDesiredState, 0, sizeof(self->InDesiredState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Set_ResourceId(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_SetPtr_ResourceId(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_TestConfiguration_Clear_ResourceId(
    _Inout_ MSFT_DSCLocalConfigurationManager_TestConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.ApplyConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_ApplyConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField force;
}
MSFT_DSCLocalConfigurationManager_ApplyConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_ApplyConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Set_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->force)->value = x;
    ((MI_BooleanField*)&self->force)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Clear_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_ApplyConfiguration* self)
{
    memset((void*)&self->force, 0, sizeof(self->force));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.SendMetaConfigurationApply()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField ConfigurationData;
}
MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Set_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_SetPtr_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Clear_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.GetMetaConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_GetMetaConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MSFT_DSCMetaConfiguration_ConstRef MetaConfiguration;
}
MSFT_DSCLocalConfigurationManager_GetMetaConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Set_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_SetPtr_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Clear_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.RollBack()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_RollBack
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8Field configurationNumber;
}
MSFT_DSCLocalConfigurationManager_RollBack;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_RollBack_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_RollBack* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_RollBack_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_RollBack* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_RollBack** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_RollBack* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_RollBack* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_RollBack* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_RollBack* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_RollBack* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Set_configurationNumber(
    _Inout_ MSFT_DSCLocalConfigurationManager_RollBack* self,
    _In_ MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->configurationNumber)->value = x;
    ((MI_Uint8Field*)&self->configurationNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_RollBack_Clear_configurationNumber(
    _Inout_ MSFT_DSCLocalConfigurationManager_RollBack* self)
{
    memset((void*)&self->configurationNumber, 0, sizeof(self->configurationNumber));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.PerformRequiredConfigurationChecks()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Set_Flags(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Clear_Flags(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.StopConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_StopConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField force;
}
MSFT_DSCLocalConfigurationManager_StopConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_StopConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_StopConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_StopConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_StopConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_StopConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_StopConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_StopConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_StopConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Set_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_StopConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->force)->value = x;
    ((MI_BooleanField*)&self->force)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_StopConfiguration_Clear_force(
    _Inout_ MSFT_DSCLocalConfigurationManager_StopConfiguration* self)
{
    memset((void*)&self->force, 0, sizeof(self->force));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.PerformInventory()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_PerformInventory
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_DSCLocalConfigurationManager_PerformInventory;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_PerformInventory_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventory_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_PerformInventory* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_PerformInventory_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventory_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_PerformInventory* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_PerformInventory** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventory_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventory* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventory_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventory* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventory_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_PerformInventory* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventory_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventory* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventory_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventory* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager.PerformInventoryOOB()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigurationManager_PerformInventoryOOB
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField InventoryMOFPath;
}
MSFT_DSCLocalConfigurationManager_PerformInventoryOOB;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Construct(
    _Out_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Clone(
    _In_ const MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self,
    _Outptr_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Destruct(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Delete(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Post(
    _In_ const MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Set_InventoryMOFPath(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_SetPtr_InventoryMOFPath(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigurationManager_PerformInventoryOOB_Clear_InventoryMOFPath(
    _Inout_ MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigurationManager provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_DSCLocalConfigurationManager_Self MSFT_DSCLocalConfigurationManager_Self;

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Load(
    _Outptr_result_maybenull_ MSFT_DSCLocalConfigurationManager_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Unload(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_TestConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_ApplyConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_SendMetaConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_GetMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_RollBack(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_RollBack* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformRequiredConfigurationChecks(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_StopConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformInventory(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventory* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformInventoryOOB(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformInventoryOOB* in);


#endif /* _MSFT_DSCLocalConfigurationManager_h */

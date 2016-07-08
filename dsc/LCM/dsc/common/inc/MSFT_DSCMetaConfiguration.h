/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_DSCMetaConfiguration_h
#define _MSFT_DSCMetaConfiguration_h

#include <MI.h>
#include "MSFT_BaseCredential.h"
#include "MSFT_KeyValuePair.h"

/*
**==============================================================================
**
** MSFT_DSCMetaConfiguration [MSFT_DSCMetaConfiguration]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_DSCMetaConfiguration
{
    MI_Instance __instance;
    /* MSFT_DSCMetaConfiguration properties */
    MI_ConstUint32Field ConfigurationModeFrequencyMins;
    MI_ConstBooleanField RebootNodeIfNeeded;
    MI_ConstStringField ConfigurationMode;
    MSFT_Credential_ConstRef Credential;
    MI_ConstStringField RefreshMode;
    MI_ConstStringField CertificateID;
    MI_ConstStringField ConfigurationID;
    MI_ConstStringField DownloadManagerName;
    MSFT_KeyValuePair_ConstArrayRef DownloadManagerCustomData;
    MI_ConstUint32Field RefreshFrequencyMins;
    MI_ConstBooleanField AllowModuleOverwrite;
    MI_ConstStringField LocalConfigurationManagerState;
}
MSFT_DSCMetaConfiguration;

typedef struct _MSFT_DSCMetaConfiguration_Ref
{
    MSFT_DSCMetaConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCMetaConfiguration_Ref;

typedef struct _MSFT_DSCMetaConfiguration_ConstRef
{
    MI_CONST MSFT_DSCMetaConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCMetaConfiguration_ConstRef;

typedef struct _MSFT_DSCMetaConfiguration_Array
{
    struct _MSFT_DSCMetaConfiguration** data;
    MI_Uint32 size;
}
MSFT_DSCMetaConfiguration_Array;

typedef struct _MSFT_DSCMetaConfiguration_ConstArray
{
    struct _MSFT_DSCMetaConfiguration MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_DSCMetaConfiguration_ConstArray;

typedef struct _MSFT_DSCMetaConfiguration_ArrayRef
{
    MSFT_DSCMetaConfiguration_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCMetaConfiguration_ArrayRef;

typedef struct _MSFT_DSCMetaConfiguration_ConstArrayRef
{
    MSFT_DSCMetaConfiguration_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCMetaConfiguration_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_DSCMetaConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Construct(
    _Out_ MSFT_DSCMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_DSCMetaConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clone(
    _In_ const MSFT_DSCMetaConfiguration* self,
    _Outptr_ MSFT_DSCMetaConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_DSCMetaConfiguration_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_DSCMetaConfiguration_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Destruct(_Inout_ MSFT_DSCMetaConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Delete(_Inout_ MSFT_DSCMetaConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Post(
    _In_ const MSFT_DSCMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_ConfigurationModeFrequencyMins(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ConfigurationModeFrequencyMins)->value = x;
    ((MI_Uint32Field*)&self->ConfigurationModeFrequencyMins)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_ConfigurationModeFrequencyMins(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    memset((void*)&self->ConfigurationModeFrequencyMins, 0, sizeof(self->ConfigurationModeFrequencyMins));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_RebootNodeIfNeeded(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->RebootNodeIfNeeded)->value = x;
    ((MI_BooleanField*)&self->RebootNodeIfNeeded)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_RebootNodeIfNeeded(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    memset((void*)&self->RebootNodeIfNeeded, 0, sizeof(self->RebootNodeIfNeeded));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_ConfigurationMode(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_ConfigurationMode(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_ConfigurationMode(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_Credential(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_Credential(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_Credential(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_RefreshMode(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_RefreshMode(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_RefreshMode(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_CertificateID(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_CertificateID(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_CertificateID(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_ConfigurationID(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_ConfigurationID(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_ConfigurationID(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_DownloadManagerName(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_DownloadManagerName(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_DownloadManagerName(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_DownloadManagerCustomData(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_DownloadManagerCustomData(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_DownloadManagerCustomData(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_RefreshFrequencyMins(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->RefreshFrequencyMins)->value = x;
    ((MI_Uint32Field*)&self->RefreshFrequencyMins)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_RefreshFrequencyMins(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    memset((void*)&self->RefreshFrequencyMins, 0, sizeof(self->RefreshFrequencyMins));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_AllowModuleOverwrite(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->AllowModuleOverwrite)->value = x;
    ((MI_BooleanField*)&self->AllowModuleOverwrite)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_AllowModuleOverwrite(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    memset((void*)&self->AllowModuleOverwrite, 0, sizeof(self->AllowModuleOverwrite));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_LocalConfigurationManagerState(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_LocalConfigurationManagerState(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_LocalConfigurationManagerState(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}


#endif /* _MSFT_DSCMetaConfiguration_h */

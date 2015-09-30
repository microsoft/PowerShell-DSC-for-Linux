/* @migen@ */
/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _MSFT_DSCMetaConfiguration_h
#define _MSFT_DSCMetaConfiguration_h

#include <MI.h>
#include "MSFT_Credential.h"
#include "MSFT_KeyValuePair.h"
#include "OMI_ConfigurationDownloadManager.h"
#include "OMI_ResourceModuleManager.h"
#include "OMI_ReportManager.h"
#include "MSFT_PartialConfiguration.h"

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
    OMI_ConfigurationDownloadManager_ConstArrayRef ConfigurationDownloadManagers;
    OMI_ResourceModuleManager_ConstArrayRef ResourceModuleManagers;
    OMI_ReportManager_ConstArrayRef ReportManagers;
    MSFT_PartialConfiguration_ConstArrayRef PartialConfigurations;
    MI_ConstStringField ActionAfterReboot;
    MI_ConstStringAField DebugMode;
    MI_ConstStringField LCMVersion;
    MI_ConstStringAField LCMCompatibleVersions;
    MI_ConstStringField LCMState;
    MI_ConstStringField LCMStateDetail;
    MI_ConstUint32Field StatusRetentionTimeInDays;
    MI_ConstStringField AgentId;
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

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_ConfigurationDownloadManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const OMI_ConfigurationDownloadManager * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_ConfigurationDownloadManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const OMI_ConfigurationDownloadManager * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_ConfigurationDownloadManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_ResourceModuleManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const OMI_ResourceModuleManager * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_ResourceModuleManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const OMI_ResourceModuleManager * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_ResourceModuleManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_ReportManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const OMI_ReportManager * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_ReportManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const OMI_ReportManager * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_ReportManagers(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_PartialConfigurations(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MSFT_PartialConfiguration * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_PartialConfigurations(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MSFT_PartialConfiguration * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_PartialConfigurations(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_ActionAfterReboot(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_ActionAfterReboot(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_ActionAfterReboot(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_DebugMode(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_DebugMode(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_DebugMode(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_LCMVersion(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_LCMVersion(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_LCMVersion(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_LCMCompatibleVersions(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_LCMCompatibleVersions(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_LCMCompatibleVersions(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_LCMState(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_LCMState(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_LCMState(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_LCMStateDetail(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_LCMStateDetail(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_LCMStateDetail(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_StatusRetentionTimeInDays(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->StatusRetentionTimeInDays)->value = x;
    ((MI_Uint32Field*)&self->StatusRetentionTimeInDays)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_StatusRetentionTimeInDays(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    memset((void*)&self->StatusRetentionTimeInDays, 0, sizeof(self->StatusRetentionTimeInDays));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Set_AgentId(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_SetPtr_AgentId(
    _Inout_ MSFT_DSCMetaConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCMetaConfiguration_Clear_AgentId(
    _Inout_ MSFT_DSCMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}


#endif /* _MSFT_DSCMetaConfiguration_h */

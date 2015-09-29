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
#ifndef _MSFT_DSCLocalConfigManager_h
#define _MSFT_DSCLocalConfigManager_h

#include <MI.h>
#include "MSFT_BaseResourceConfiguration.h"
#include "MSFT_DSCMetaConfiguration.h"

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager [MSFT_DSCLocalConfigManager]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager
{
    MI_Instance __instance;
    /* MSFT_DSCLocalConfigManager properties */
}
MSFT_DSCLocalConfigManager;

typedef struct _MSFT_DSCLocalConfigManager_Ref
{
    MSFT_DSCLocalConfigManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigManager_Ref;

typedef struct _MSFT_DSCLocalConfigManager_ConstRef
{
    MI_CONST MSFT_DSCLocalConfigManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigManager_ConstRef;

typedef struct _MSFT_DSCLocalConfigManager_Array
{
    struct _MSFT_DSCLocalConfigManager** data;
    MI_Uint32 size;
}
MSFT_DSCLocalConfigManager_Array;

typedef struct _MSFT_DSCLocalConfigManager_ConstArray
{
    struct _MSFT_DSCLocalConfigManager MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_DSCLocalConfigManager_ConstArray;

typedef struct _MSFT_DSCLocalConfigManager_ArrayRef
{
    MSFT_DSCLocalConfigManager_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigManager_ArrayRef;

typedef struct _MSFT_DSCLocalConfigManager_ConstArrayRef
{
    MSFT_DSCLocalConfigManager_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCLocalConfigManager_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_DSCLocalConfigManager_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Construct(
    _Out_ MSFT_DSCLocalConfigManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_DSCLocalConfigManager_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Clone(
    _In_ const MSFT_DSCLocalConfigManager* self,
    _Outptr_ MSFT_DSCLocalConfigManager** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_DSCLocalConfigManager_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_DSCLocalConfigManager_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Destruct(_Inout_ MSFT_DSCLocalConfigManager* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Delete(_Inout_ MSFT_DSCLocalConfigManager* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Post(
    _In_ const MSFT_DSCLocalConfigManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.SendConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_SendConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField ConfigurationData;
}
MSFT_DSCLocalConfigManager_SendConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_SendConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigManager_SendConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_SendConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigManager_SendConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigManager_SendConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigManager_SendConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Set_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_SetPtr_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfiguration_Clear_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.SendConfigurationApply()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_SendConfigurationApply
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField ConfigurationData;
}
MSFT_DSCLocalConfigManager_SendConfigurationApply;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_SendConfigurationApply_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Construct(
    _Out_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_SendConfigurationApply_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Clone(
    _In_ const MSFT_DSCLocalConfigManager_SendConfigurationApply* self,
    _Outptr_ MSFT_DSCLocalConfigManager_SendConfigurationApply** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Post(
    _In_ const MSFT_DSCLocalConfigManager_SendConfigurationApply* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Set_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_SetPtr_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApply_Clear_ConfigurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApply* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.SendConfigurationWhatIf()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_SendConfigurationWhatIf
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField configurationData;
}
MSFT_DSCLocalConfigManager_SendConfigurationWhatIf;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Construct(
    _Out_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Clone(
    _In_ const MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self,
    _Outptr_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Post(
    _In_ const MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Set_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_SetPtr_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationWhatIf_Clear_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.SendConfigurationApplyQuick()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField configurationData;
}
MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Construct(
    _Out_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Clone(
    _In_ const MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self,
    _Outptr_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Post(
    _In_ const MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Set_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_SetPtr_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick_Clear_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.GetConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_GetConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField configurationData;
}
MSFT_DSCLocalConfigManager_GetConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_GetConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigManager_GetConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_GetConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigManager_GetConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigManager_GetConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigManager_GetConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Set_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_SetPtr_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfiguration_Clear_configurationData(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.GetConfigurationHistory()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_GetConfigurationHistory
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field configurationNumber;
}
MSFT_DSCLocalConfigManager_GetConfigurationHistory;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_GetConfigurationHistory_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Construct(
    _Out_ MSFT_DSCLocalConfigManager_GetConfigurationHistory* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_GetConfigurationHistory_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Clone(
    _In_ const MSFT_DSCLocalConfigManager_GetConfigurationHistory* self,
    _Outptr_ MSFT_DSCLocalConfigManager_GetConfigurationHistory** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfigurationHistory* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfigurationHistory* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Post(
    _In_ const MSFT_DSCLocalConfigManager_GetConfigurationHistory* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfigurationHistory* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfigurationHistory* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Set_configurationNumber(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfigurationHistory* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->configurationNumber)->value = x;
    ((MI_Uint16Field*)&self->configurationNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetConfigurationHistory_Clear_configurationNumber(
    _Inout_ MSFT_DSCLocalConfigManager_GetConfigurationHistory* self)
{
    memset((void*)&self->configurationNumber, 0, sizeof(self->configurationNumber));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.ApplyConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_ApplyConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_DSCLocalConfigManager_ApplyConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_ApplyConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_ApplyConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigManager_ApplyConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_ApplyConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_ApplyConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigManager_ApplyConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigManager_ApplyConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_ApplyConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_ApplyConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_ApplyConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_ApplyConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_ApplyConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigManager_ApplyConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_ApplyConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_ApplyConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_ApplyConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_ApplyConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.PullConfigurationNow()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_PullConfigurationNow
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_DSCLocalConfigManager_PullConfigurationNow;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_PullConfigurationNow_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_PullConfigurationNow_Construct(
    _Out_ MSFT_DSCLocalConfigManager_PullConfigurationNow* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_PullConfigurationNow_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_PullConfigurationNow_Clone(
    _In_ const MSFT_DSCLocalConfigManager_PullConfigurationNow* self,
    _Outptr_ MSFT_DSCLocalConfigManager_PullConfigurationNow** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_PullConfigurationNow_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_PullConfigurationNow* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_PullConfigurationNow_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_PullConfigurationNow* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_PullConfigurationNow_Post(
    _In_ const MSFT_DSCLocalConfigManager_PullConfigurationNow* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_PullConfigurationNow_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_PullConfigurationNow* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_PullConfigurationNow_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_PullConfigurationNow* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.SendMetaConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_SendMetaConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_DSCMetaConfiguration_ConstRef MetaConfiguration;
}
MSFT_DSCLocalConfigManager_SendMetaConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_SendMetaConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_SendMetaConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigManager_SendMetaConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigManager_SendMetaConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigManager_SendMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Set_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_SetPtr_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_SendMetaConfiguration_Clear_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigManager_SendMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.GetMetaConfiguration()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_GetMetaConfiguration
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MSFT_DSCMetaConfiguration_ConstRef MetaConfiguration;
}
MSFT_DSCLocalConfigManager_GetMetaConfiguration;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_GetMetaConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Construct(
    _Out_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_GetMetaConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Clone(
    _In_ const MSFT_DSCLocalConfigManager_GetMetaConfiguration* self,
    _Outptr_ MSFT_DSCLocalConfigManager_GetMetaConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Post(
    _In_ const MSFT_DSCLocalConfigManager_GetMetaConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Set_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_SetPtr_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self,
    _In_ const MSFT_DSCMetaConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_GetMetaConfiguration_Clear_MetaConfiguration(
    _Inout_ MSFT_DSCLocalConfigManager_GetMetaConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.RollBack()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_RollBack
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8Field configurationNumber;
}
MSFT_DSCLocalConfigManager_RollBack;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_RollBack_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Construct(
    _Out_ MSFT_DSCLocalConfigManager_RollBack* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_RollBack_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Clone(
    _In_ const MSFT_DSCLocalConfigManager_RollBack* self,
    _Outptr_ MSFT_DSCLocalConfigManager_RollBack** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_RollBack* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_RollBack* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Post(
    _In_ const MSFT_DSCLocalConfigManager_RollBack* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_RollBack* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_RollBack* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Set_configurationNumber(
    _Inout_ MSFT_DSCLocalConfigManager_RollBack* self,
    _In_ MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->configurationNumber)->value = x;
    ((MI_Uint8Field*)&self->configurationNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_RollBack_Clear_configurationNumber(
    _Inout_ MSFT_DSCLocalConfigManager_RollBack* self)
{
    memset((void*)&self->configurationNumber, 0, sizeof(self->configurationNumber));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.Cancel()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_Cancel
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_DSCLocalConfigManager_Cancel;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_Cancel_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Cancel_Construct(
    _Out_ MSFT_DSCLocalConfigManager_Cancel* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_Cancel_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Cancel_Clone(
    _In_ const MSFT_DSCLocalConfigManager_Cancel* self,
    _Outptr_ MSFT_DSCLocalConfigManager_Cancel** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Cancel_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_Cancel* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Cancel_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_Cancel* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Cancel_Post(
    _In_ const MSFT_DSCLocalConfigManager_Cancel* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Cancel_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_Cancel* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Cancel_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_Cancel* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.Suspend()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_Suspend
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Force;
}
MSFT_DSCLocalConfigManager_Suspend;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_Suspend_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Construct(
    _Out_ MSFT_DSCLocalConfigManager_Suspend* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_Suspend_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Clone(
    _In_ const MSFT_DSCLocalConfigManager_Suspend* self,
    _Outptr_ MSFT_DSCLocalConfigManager_Suspend** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_Suspend* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_Suspend* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Post(
    _In_ const MSFT_DSCLocalConfigManager_Suspend* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_Suspend* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_Suspend* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Set_Force(
    _Inout_ MSFT_DSCLocalConfigManager_Suspend* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Force)->value = x;
    ((MI_BooleanField*)&self->Force)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Suspend_Clear_Force(
    _Inout_ MSFT_DSCLocalConfigManager_Suspend* self)
{
    memset((void*)&self->Force, 0, sizeof(self->Force));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager.Resume()
**
**==============================================================================
*/

typedef struct _MSFT_DSCLocalConfigManager_Resume
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_DSCLocalConfigManager_Resume;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCLocalConfigManager_Resume_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Resume_Construct(
    _Out_ MSFT_DSCLocalConfigManager_Resume* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCLocalConfigManager_Resume_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Resume_Clone(
    _In_ const MSFT_DSCLocalConfigManager_Resume* self,
    _Outptr_ MSFT_DSCLocalConfigManager_Resume** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Resume_Destruct(
    _Inout_ MSFT_DSCLocalConfigManager_Resume* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Resume_Delete(
    _Inout_ MSFT_DSCLocalConfigManager_Resume* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Resume_Post(
    _In_ const MSFT_DSCLocalConfigManager_Resume* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Resume_Set_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_Resume* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCLocalConfigManager_Resume_Clear_MIReturn(
    _Inout_ MSFT_DSCLocalConfigManager_Resume* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DSCLocalConfigManager provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_DSCLocalConfigManager_Self MSFT_DSCLocalConfigManager_Self;

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Load(
    _Outptr_result_maybenull_ MSFT_DSCLocalConfigManager_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Unload(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfigurationApply* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfigurationWhatIf(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfigurationWhatIf* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendConfigurationApplyQuick(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendConfigurationApplyQuick* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_GetConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_GetConfigurationHistory(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_GetConfigurationHistory* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_ApplyConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_ApplyConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_PullConfigurationNow(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_PullConfigurationNow* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_SendMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_SendMetaConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_GetMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_GetMetaConfiguration* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_RollBack(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_RollBack* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_Cancel(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_Cancel* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_Suspend(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_Suspend* in);

MI_EXTERN_C void MI_CALL MSFT_DSCLocalConfigManager_Invoke_Resume(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_Resume* in);


#endif /* _MSFT_DSCLocalConfigManager_h */

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
#ifndef _MSFT_PartialConfiguration_h
#define _MSFT_PartialConfiguration_h

#include <MI.h>
#include "OMI_MetaConfigurationResource.h"

/*
**==============================================================================
**
** MSFT_PartialConfiguration [MSFT_PartialConfiguration]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_PartialConfiguration /* extends OMI_MetaConfigurationResource */
{
    MI_Instance __instance;
    /* OMI_MetaConfigurationResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    /* MSFT_PartialConfiguration properties */
    MI_ConstStringField Description;
    MI_ConstStringAField ExclusiveResources;
    MI_ConstStringAField ConfigurationSource;
    MI_ConstStringAField ResourceModuleSource;
    MI_ConstStringAField DependsOn;
    MI_ConstStringField RefreshMode;
}
MSFT_PartialConfiguration;

typedef struct _MSFT_PartialConfiguration_Ref
{
    MSFT_PartialConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_PartialConfiguration_Ref;

typedef struct _MSFT_PartialConfiguration_ConstRef
{
    MI_CONST MSFT_PartialConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_PartialConfiguration_ConstRef;

typedef struct _MSFT_PartialConfiguration_Array
{
    struct _MSFT_PartialConfiguration** data;
    MI_Uint32 size;
}
MSFT_PartialConfiguration_Array;

typedef struct _MSFT_PartialConfiguration_ConstArray
{
    struct _MSFT_PartialConfiguration MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_PartialConfiguration_ConstArray;

typedef struct _MSFT_PartialConfiguration_ArrayRef
{
    MSFT_PartialConfiguration_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_PartialConfiguration_ArrayRef;

typedef struct _MSFT_PartialConfiguration_ConstArrayRef
{
    MSFT_PartialConfiguration_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_PartialConfiguration_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_PartialConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Construct(
    _Out_ MSFT_PartialConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_PartialConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clone(
    _In_ const MSFT_PartialConfiguration* self,
    _Outptr_ MSFT_PartialConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_PartialConfiguration_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_PartialConfiguration_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Destruct(_Inout_ MSFT_PartialConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Delete(_Inout_ MSFT_PartialConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Post(
    _In_ const MSFT_PartialConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_ResourceId(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_ResourceId(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_ResourceId(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_SourceInfo(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_SourceInfo(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_SourceInfo(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_Description(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_Description(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_Description(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_ExclusiveResources(
    _Inout_ MSFT_PartialConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_ExclusiveResources(
    _Inout_ MSFT_PartialConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_ExclusiveResources(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_ConfigurationSource(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_ConfigurationSource(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_ConfigurationSource(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_ResourceModuleSource(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_ResourceModuleSource(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_ResourceModuleSource(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_DependsOn(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_DependsOn(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_DependsOn(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Set_RefreshMode(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_SetPtr_RefreshMode(
    _Inout_ MSFT_PartialConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_PartialConfiguration_Clear_RefreshMode(
    _Inout_ MSFT_PartialConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}


#endif /* _MSFT_PartialConfiguration_h */

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
#ifndef _MSFT_FileDirectoryConfiguration_h
#define _MSFT_FileDirectoryConfiguration_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_Credential.h"
#include "MSFT_FileDirectoryConfiguration.h"

/*
**==============================================================================
**
** MSFT_FileDirectoryConfiguration [MSFT_FileDirectoryConfiguration]
**
** Keys:
**    DestinationPath
**
**==============================================================================
*/
typedef struct _MSFT_FileDirectoryConfiguration_ConstArray
{
    struct _MSFT_FileDirectoryConfiguration MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_FileDirectoryConfiguration_ConstArray;

typedef struct _MSFT_FileDirectoryConfiguration_ConstArrayRef
{
    MSFT_FileDirectoryConfiguration_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
} 
MSFT_FileDirectoryConfiguration_ConstArrayRef;

typedef struct _MSFT_FileDirectoryConfiguration /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_FileDirectoryConfiguration properties */
    /*KEY*/ MI_ConstStringField DestinationPath;
    MI_ConstStringField Ensure;
    MI_ConstStringField Type;
    MI_ConstStringField SourcePath;
    MI_ConstStringField Contents;
    MI_ConstStringField Checksum;
    MI_ConstBooleanField Recurse;
    MI_ConstBooleanField Force;
    MSFT_Credential_ConstRef Credential;
    MI_ConstDatetimeField CreatedDate;
    MI_ConstDatetimeField ModifiedDate;
    MI_ConstStringAField Attributes;
    MI_ConstUint64Field Size;
    MSFT_FileDirectoryConfiguration_ConstArrayRef SubItems;
    MI_ConstBooleanField MatchSource;
}
MSFT_FileDirectoryConfiguration;

typedef struct _MSFT_FileDirectoryConfiguration_Ref
{
    MSFT_FileDirectoryConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_FileDirectoryConfiguration_Ref;

typedef struct _MSFT_FileDirectoryConfiguration_ConstRef
{
    MI_CONST MSFT_FileDirectoryConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_FileDirectoryConfiguration_ConstRef;

typedef struct _MSFT_FileDirectoryConfiguration_Array
{
    struct _MSFT_FileDirectoryConfiguration** data;
    MI_Uint32 size;
}
MSFT_FileDirectoryConfiguration_Array;



typedef struct _MSFT_FileDirectoryConfiguration_ArrayRef
{
    MSFT_FileDirectoryConfiguration_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_FileDirectoryConfiguration_ArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_FileDirectoryConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Construct(
    _Out_ MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_FileDirectoryConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clone(
    _In_ const MSFT_FileDirectoryConfiguration* self,
    _Outptr_ MSFT_FileDirectoryConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_FileDirectoryConfiguration_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_FileDirectoryConfiguration_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Destruct(_Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Delete(_Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Post(
    _In_ const MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_DestinationPath(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_DestinationPath(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_DestinationPath(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Ensure(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_Ensure(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Ensure(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Type(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_Type(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Type(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_SourcePath(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_SourcePath(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_SourcePath(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Contents(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_Contents(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Contents(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Checksum(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_Checksum(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Checksum(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Recurse(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Recurse)->value = x;
    ((MI_BooleanField*)&self->Recurse)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Recurse(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    memset((void*)&self->Recurse, 0, sizeof(self->Recurse));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Force(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Force)->value = x;
    ((MI_BooleanField*)&self->Force)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Force(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    memset((void*)&self->Force, 0, sizeof(self->Force));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Credential(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_Credential(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Credential(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_CreatedDate(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->CreatedDate)->value = x;
    ((MI_DatetimeField*)&self->CreatedDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_CreatedDate(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    memset((void*)&self->CreatedDate, 0, sizeof(self->CreatedDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_ModifiedDate(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ModifiedDate)->value = x;
    ((MI_DatetimeField*)&self->ModifiedDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_ModifiedDate(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    memset((void*)&self->ModifiedDate, 0, sizeof(self->ModifiedDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Attributes(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_Attributes(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Attributes(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_Size(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Size)->value = x;
    ((MI_Uint64Field*)&self->Size)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_Size(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    memset((void*)&self->Size, 0, sizeof(self->Size));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_SubItems(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_reads_opt_(size) const MSFT_FileDirectoryConfiguration * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetPtr_SubItems(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_reads_opt_(size) const MSFT_FileDirectoryConfiguration * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_SubItems(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Set_MatchSource(
    _Inout_ MSFT_FileDirectoryConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->MatchSource)->value = x;
    ((MI_BooleanField*)&self->MatchSource)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_Clear_MatchSource(
    _Inout_ MSFT_FileDirectoryConfiguration* self)
{
    memset((void*)&self->MatchSource, 0, sizeof(self->MatchSource));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_FileDirectoryConfiguration.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_FileDirectoryConfiguration_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_FileDirectoryConfiguration_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_FileDirectoryConfiguration_ConstRef OutputResource;
}
MSFT_FileDirectoryConfiguration_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_FileDirectoryConfiguration_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Construct(
    _Out_ MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_FileDirectoryConfiguration_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Clone(
    _In_ const MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _Outptr_ MSFT_FileDirectoryConfiguration_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Destruct(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Delete(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Post(
    _In_ const MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Set_Flags(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_FileDirectoryConfiguration.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_FileDirectoryConfiguration_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_FileDirectoryConfiguration_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_FileDirectoryConfiguration_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_FileDirectoryConfiguration_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Construct(
    _Out_ MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_FileDirectoryConfiguration_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Clone(
    _In_ const MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _Outptr_ MSFT_FileDirectoryConfiguration_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Destruct(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Delete(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Post(
    _In_ const MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Set_Flags(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Set_Result(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Clear_Result(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_FileDirectoryConfiguration_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_FileDirectoryConfiguration.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_FileDirectoryConfiguration_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_FileDirectoryConfiguration_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_FileDirectoryConfiguration_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_FileDirectoryConfiguration_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Construct(
    _Out_ MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_FileDirectoryConfiguration_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Clone(
    _In_ const MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _Outptr_ MSFT_FileDirectoryConfiguration_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Destruct(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Delete(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Post(
    _In_ const MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _In_ const MSFT_FileDirectoryConfiguration* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Set_Flags(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_FileDirectoryConfiguration_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_FileDirectoryConfiguration_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_FileDirectoryConfiguration provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_FileDirectoryConfiguration_Self MSFT_FileDirectoryConfiguration_Self;

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_Load(
    _Outptr_result_maybenull_ MSFT_FileDirectoryConfiguration_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_Unload(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_EnumerateInstances(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_GetInstance(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_FileDirectoryConfiguration* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_CreateInstance(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_FileDirectoryConfiguration* newInstance);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_ModifyInstance(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_FileDirectoryConfiguration* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_DeleteInstance(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_FileDirectoryConfiguration* instanceName);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_Invoke_GetTargetResource(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_FileDirectoryConfiguration* instanceName,
    _In_opt_ const MSFT_FileDirectoryConfiguration_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_Invoke_TestTargetResource(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_FileDirectoryConfiguration* instanceName,
    _In_opt_ const MSFT_FileDirectoryConfiguration_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_FileDirectoryConfiguration_Invoke_SetTargetResource(
    _In_opt_ MSFT_FileDirectoryConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_FileDirectoryConfiguration* instanceName,
    _In_opt_ const MSFT_FileDirectoryConfiguration_SetTargetResource* in);


#endif /* _MSFT_FileDirectoryConfiguration_h */

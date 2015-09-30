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
#ifndef _MSFT_WebDownloadManager_h
#define _MSFT_WebDownloadManager_h

#include <MI.h>
#include "OMI_ConfigurationDownloadManager.h"

/*
**==============================================================================
**
** MSFT_WebDownloadManager [MSFT_WebDownloadManager]
**
** Keys:
**    ServerURL
**
**==============================================================================
*/

typedef struct _MSFT_WebDownloadManager /* extends OMI_ConfigurationDownloadManager */
{
    MI_Instance __instance;
    /* OMI_MetaConfigurationResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    MI_ConstStringField ModuleName;
    MI_ConstStringField ModuleVersion;
    /* OMI_ConfigurationDownloadManager properties */
    MI_ConstStringField Name;
    /* MSFT_WebDownloadManager properties */
    /*KEY*/ MI_ConstStringField ServerURL;
    MI_ConstStringField CertificateID;
    MI_ConstBooleanField AllowUnsecureConnection;
}
MSFT_WebDownloadManager;

typedef struct _MSFT_WebDownloadManager_Ref
{
    MSFT_WebDownloadManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WebDownloadManager_Ref;

typedef struct _MSFT_WebDownloadManager_ConstRef
{
    MI_CONST MSFT_WebDownloadManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WebDownloadManager_ConstRef;

typedef struct _MSFT_WebDownloadManager_Array
{
    struct _MSFT_WebDownloadManager** data;
    MI_Uint32 size;
}
MSFT_WebDownloadManager_Array;

typedef struct _MSFT_WebDownloadManager_ConstArray
{
    struct _MSFT_WebDownloadManager MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_WebDownloadManager_ConstArray;

typedef struct _MSFT_WebDownloadManager_ArrayRef
{
    MSFT_WebDownloadManager_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WebDownloadManager_ArrayRef;

typedef struct _MSFT_WebDownloadManager_ConstArrayRef
{
    MSFT_WebDownloadManager_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WebDownloadManager_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_WebDownloadManager_rtti;

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Construct(
    _Out_ MSFT_WebDownloadManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_WebDownloadManager_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clone(
    _In_ const MSFT_WebDownloadManager* self,
    _Outptr_ MSFT_WebDownloadManager** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_WebDownloadManager_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_WebDownloadManager_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Destruct(_Inout_ MSFT_WebDownloadManager* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Delete(_Inout_ MSFT_WebDownloadManager* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Post(
    _In_ const MSFT_WebDownloadManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_ResourceId(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_SetPtr_ResourceId(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_ResourceId(
    _Inout_ MSFT_WebDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_SourceInfo(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_SetPtr_SourceInfo(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_SourceInfo(
    _Inout_ MSFT_WebDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_ModuleName(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_SetPtr_ModuleName(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_ModuleName(
    _Inout_ MSFT_WebDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_ModuleVersion(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_SetPtr_ModuleVersion(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_ModuleVersion(
    _Inout_ MSFT_WebDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_Name(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_SetPtr_Name(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_Name(
    _Inout_ MSFT_WebDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_ServerURL(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_SetPtr_ServerURL(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_ServerURL(
    _Inout_ MSFT_WebDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_CertificateID(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_SetPtr_CertificateID(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_CertificateID(
    _Inout_ MSFT_WebDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Set_AllowUnsecureConnection(
    _Inout_ MSFT_WebDownloadManager* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->AllowUnsecureConnection)->value = x;
    ((MI_BooleanField*)&self->AllowUnsecureConnection)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_WebDownloadManager_Clear_AllowUnsecureConnection(
    _Inout_ MSFT_WebDownloadManager* self)
{
    memset((void*)&self->AllowUnsecureConnection, 0, sizeof(self->AllowUnsecureConnection));
    return MI_RESULT_OK;
}


#endif /* _MSFT_WebDownloadManager_h */

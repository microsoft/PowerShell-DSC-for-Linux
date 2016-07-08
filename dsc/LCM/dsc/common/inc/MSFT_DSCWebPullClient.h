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
#ifndef _MSFT_DSCWebPullClient_h
#define _MSFT_DSCWebPullClient_h

#include <MI.h>
#include "MSFT_BaseCredential.h"
#include "MSFT_KeyValuePair.h"
#include "MSFT_ModuleSpecification.h"

/*
**==============================================================================
**
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_DSCWebPullClient
{
    MI_Instance __instance;
    /* MSFT_DSCWebPullClient properties */
}
MSFT_DSCWebPullClient;

typedef struct _MSFT_DSCWebPullClient_Ref
{
    MSFT_DSCWebPullClient* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCWebPullClient_Ref;

typedef struct _MSFT_DSCWebPullClient_ConstRef
{
    MI_CONST MSFT_DSCWebPullClient* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCWebPullClient_ConstRef;

typedef struct _MSFT_DSCWebPullClient_Array
{
    struct _MSFT_DSCWebPullClient** data;
    MI_Uint32 size;
}
MSFT_DSCWebPullClient_Array;

typedef struct _MSFT_DSCWebPullClient_ConstArray
{
    struct _MSFT_DSCWebPullClient MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_DSCWebPullClient_ConstArray;

typedef struct _MSFT_DSCWebPullClient_ArrayRef
{
    MSFT_DSCWebPullClient_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCWebPullClient_ArrayRef;

typedef struct _MSFT_DSCWebPullClient_ConstArrayRef
{
    MSFT_DSCWebPullClient_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DSCWebPullClient_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_DSCWebPullClient_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_Construct(
    _Out_ MSFT_DSCWebPullClient* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_DSCWebPullClient_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_Clone(
    _In_ const MSFT_DSCWebPullClient* self,
    _Outptr_ MSFT_DSCWebPullClient** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_DSCWebPullClient_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_DSCWebPullClient_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_Destruct(_Inout_ MSFT_DSCWebPullClient* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_Delete(_Inout_ MSFT_DSCWebPullClient* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_Post(
    _In_ const MSFT_DSCWebPullClient* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MSFT_DSCWebPullClient.GetDSCAction()
**
**==============================================================================
*/

typedef struct _MSFT_DSCWebPullClient_GetDSCAction
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField FileHash;
    /*IN*/ MI_ConstStringField ConfigurationID;
    /*IN*/ MI_ConstBooleanField NotCompliant;
    /*IN*/ MI_ConstUint32Field StatusCode;
    /*IN*/ MSFT_Credential_ConstRef Credential;
    /*IN*/ MSFT_KeyValuePair_ConstArrayRef CustomData;
    /*OUT*/ MI_ConstStringField Result;
}
MSFT_DSCWebPullClient_GetDSCAction;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCWebPullClient_GetDSCAction_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Construct(
    _Out_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCWebPullClient_GetDSCAction_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clone(
    _In_ const MSFT_DSCWebPullClient_GetDSCAction* self,
    _Outptr_ MSFT_DSCWebPullClient_GetDSCAction** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Destruct(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Delete(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Post(
    _In_ const MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_MIReturn(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_MIReturn(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_FileHash(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_SetPtr_FileHash(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_FileHash(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_SetPtr_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_NotCompliant(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->NotCompliant)->value = x;
    ((MI_BooleanField*)&self->NotCompliant)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_NotCompliant(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    memset((void*)&self->NotCompliant, 0, sizeof(self->NotCompliant));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_StatusCode(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->StatusCode)->value = x;
    ((MI_Uint32Field*)&self->StatusCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_StatusCode(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    memset((void*)&self->StatusCode, 0, sizeof(self->StatusCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_SetPtr_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_SetPtr_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Set_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_SetPtr_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCAction_Clear_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** MSFT_DSCWebPullClient.GetDSCDocument()
**
**==============================================================================
*/

typedef struct _MSFT_DSCWebPullClient_GetDSCDocument
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField ConfigurationID;
    /*IN*/ MI_ConstStringField DestinationPath;
    /*IN*/ MSFT_Credential_ConstRef Credential;
    /*IN*/ MSFT_KeyValuePair_ConstArrayRef CustomData;
    /*OUT*/ MI_ConstStringField Result;
}
MSFT_DSCWebPullClient_GetDSCDocument;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCWebPullClient_GetDSCDocument_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Construct(
    _Out_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCWebPullClient_GetDSCDocument_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Clone(
    _In_ const MSFT_DSCWebPullClient_GetDSCDocument* self,
    _Outptr_ MSFT_DSCWebPullClient_GetDSCDocument** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Destruct(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Delete(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Post(
    _In_ const MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Set_MIReturn(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Clear_MIReturn(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Set_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_SetPtr_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Clear_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Set_DestinationPath(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_SetPtr_DestinationPath(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Clear_DestinationPath(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Set_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_SetPtr_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Clear_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Set_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_SetPtr_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Clear_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Set_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_SetPtr_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCDocument_Clear_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCDocument* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** MSFT_DSCWebPullClient.GetDSCModule()
**
**==============================================================================
*/

typedef struct _MSFT_DSCWebPullClient_GetDSCModule
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField ConfigurationID;
    /*IN*/ MI_ConstStringField DestinationPath;
    /*IN*/ MSFT_Credential_ConstRef Credential;
    /*IN*/ MSFT_KeyValuePair_ConstArrayRef CustomData;
    /*IN*/ MSFT_ModuleSpecification_ConstRef Module;
    /*OUT*/ MI_ConstStringField Result;
}
MSFT_DSCWebPullClient_GetDSCModule;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_DSCWebPullClient_GetDSCModule_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Construct(
    _Out_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_DSCWebPullClient_GetDSCModule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clone(
    _In_ const MSFT_DSCWebPullClient_GetDSCModule* self,
    _Outptr_ MSFT_DSCWebPullClient_GetDSCModule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Destruct(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Delete(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Post(
    _In_ const MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Set_MIReturn(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clear_MIReturn(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Set_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_SetPtr_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clear_ConfigurationID(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Set_DestinationPath(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_SetPtr_DestinationPath(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clear_DestinationPath(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Set_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_SetPtr_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_ const MSFT_Credential* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clear_Credential(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Set_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_SetPtr_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_reads_opt_(size) const MSFT_KeyValuePair * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clear_CustomData(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Set_Module(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_ const MSFT_ModuleSpecification* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_SetPtr_Module(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_ const MSFT_ModuleSpecification* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clear_Module(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Set_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_SetPtr_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DSCWebPullClient_GetDSCModule_Clear_Result(
    _Inout_ MSFT_DSCWebPullClient_GetDSCModule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

/*
**==============================================================================
**
** MSFT_DSCWebPullClient provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_DSCWebPullClient_Self MSFT_DSCWebPullClient_Self;

MI_EXTERN_C void MI_CALL MSFT_DSCWebPullClient_Load(
    _Outptr_result_maybenull_ MSFT_DSCWebPullClient_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DSCWebPullClient_Unload(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DSCWebPullClient_Invoke_GetDSCAction(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCWebPullClient* instanceName,
    _In_opt_ const MSFT_DSCWebPullClient_GetDSCAction* in);

MI_EXTERN_C void MI_CALL MSFT_DSCWebPullClient_Invoke_GetDSCDocument(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCWebPullClient* instanceName,
    _In_opt_ const MSFT_DSCWebPullClient_GetDSCDocument* in);

MI_EXTERN_C void MI_CALL MSFT_DSCWebPullClient_Invoke_GetDSCModule(
    _In_opt_ MSFT_DSCWebPullClient_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCWebPullClient* instanceName,
    _In_opt_ const MSFT_DSCWebPullClient_GetDSCModule* in);


#endif /* _MSFT_DSCWebPullClient_h */

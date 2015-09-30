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
#ifndef _MSFT_nxIPAddressResource_h
#define _MSFT_nxIPAddressResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxIPAddressResource.h"

/*
**==============================================================================
**
** MSFT_nxIPAddressResource [MSFT_nxIPAddressResource]
**
** Keys:
**    IPAddress
**    InterfaceName
**
**==============================================================================
*/

typedef struct _MSFT_nxIPAddressResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxIPAddressResource properties */
    /*KEY*/ MI_ConstStringField IPAddress;
    /*KEY*/ MI_ConstStringField InterfaceName;
    MI_ConstStringField BootProtocol;
    MI_ConstStringField DefaultGateway;
    MI_ConstStringField Ensure;
    MI_ConstUint32Field PrefixLength;
    MI_ConstStringField AddressFamily;
}
MSFT_nxIPAddressResource;

typedef struct _MSFT_nxIPAddressResource_Ref
{
    MSFT_nxIPAddressResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxIPAddressResource_Ref;

typedef struct _MSFT_nxIPAddressResource_ConstRef
{
    MI_CONST MSFT_nxIPAddressResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxIPAddressResource_ConstRef;

typedef struct _MSFT_nxIPAddressResource_Array
{
    struct _MSFT_nxIPAddressResource** data;
    MI_Uint32 size;
}
MSFT_nxIPAddressResource_Array;

typedef struct _MSFT_nxIPAddressResource_ConstArray
{
    struct _MSFT_nxIPAddressResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxIPAddressResource_ConstArray;

typedef struct _MSFT_nxIPAddressResource_ArrayRef
{
    MSFT_nxIPAddressResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxIPAddressResource_ArrayRef;

typedef struct _MSFT_nxIPAddressResource_ConstArrayRef
{
    MSFT_nxIPAddressResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxIPAddressResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxIPAddressResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Construct(
    _Out_ MSFT_nxIPAddressResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxIPAddressResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clone(
    _In_ const MSFT_nxIPAddressResource* self,
    _Outptr_ MSFT_nxIPAddressResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxIPAddressResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxIPAddressResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Destruct(_Inout_ MSFT_nxIPAddressResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Delete(_Inout_ MSFT_nxIPAddressResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Post(
    _In_ const MSFT_nxIPAddressResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Set_IPAddress(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetPtr_IPAddress(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clear_IPAddress(
    _Inout_ MSFT_nxIPAddressResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Set_InterfaceName(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetPtr_InterfaceName(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clear_InterfaceName(
    _Inout_ MSFT_nxIPAddressResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Set_BootProtocol(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetPtr_BootProtocol(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clear_BootProtocol(
    _Inout_ MSFT_nxIPAddressResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Set_DefaultGateway(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetPtr_DefaultGateway(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clear_DefaultGateway(
    _Inout_ MSFT_nxIPAddressResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Set_Ensure(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetPtr_Ensure(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clear_Ensure(
    _Inout_ MSFT_nxIPAddressResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Set_PrefixLength(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->PrefixLength)->value = x;
    ((MI_Uint32Field*)&self->PrefixLength)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clear_PrefixLength(
    _Inout_ MSFT_nxIPAddressResource* self)
{
    memset((void*)&self->PrefixLength, 0, sizeof(self->PrefixLength));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Set_AddressFamily(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetPtr_AddressFamily(
    _Inout_ MSFT_nxIPAddressResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_Clear_AddressFamily(
    _Inout_ MSFT_nxIPAddressResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

/*
**==============================================================================
**
** MSFT_nxIPAddressResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxIPAddressResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxIPAddressResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxIPAddressResource_ConstRef OutputResource;
}
MSFT_nxIPAddressResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxIPAddressResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Construct(
    _Out_ MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxIPAddressResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Clone(
    _In_ const MSFT_nxIPAddressResource_GetTargetResource* self,
    _Outptr_ MSFT_nxIPAddressResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Post(
    _In_ const MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxIPAddressResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxIPAddressResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxIPAddressResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxIPAddressResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxIPAddressResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxIPAddressResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Construct(
    _Out_ MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxIPAddressResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Clone(
    _In_ const MSFT_nxIPAddressResource_TestTargetResource* self,
    _Outptr_ MSFT_nxIPAddressResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Post(
    _In_ const MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxIPAddressResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxIPAddressResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxIPAddressResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxIPAddressResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxIPAddressResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxIPAddressResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Construct(
    _Out_ MSFT_nxIPAddressResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxIPAddressResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Clone(
    _In_ const MSFT_nxIPAddressResource_SetTargetResource* self,
    _Outptr_ MSFT_nxIPAddressResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Post(
    _In_ const MSFT_nxIPAddressResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self,
    _In_ const MSFT_nxIPAddressResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxIPAddressResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxIPAddressResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxIPAddressResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxIPAddressResource_Self MSFT_nxIPAddressResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_Load(
    _Outptr_result_maybenull_ MSFT_nxIPAddressResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_Unload(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_EnumerateInstances(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_GetInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_CreateInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_ModifyInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_DeleteInstance(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxIPAddressResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MSFT_nxIPAddressResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MSFT_nxIPAddressResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxIPAddressResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxIPAddressResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxIPAddressResource* instanceName,
    _In_opt_ const MSFT_nxIPAddressResource_SetTargetResource* in);


#endif /* _MSFT_nxIPAddressResource_h */

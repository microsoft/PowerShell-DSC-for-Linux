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
#ifndef _MSFT_nxFirewallResource_h
#define _MSFT_nxFirewallResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "MSFT_nxFirewallResource.h"

/*
**==============================================================================
**
** MSFT_nxFirewallResource [MSFT_nxFirewallResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxFirewallResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_nxFirewallResource properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField InterfaceName;
    MI_ConstStringField FirewallType;
    MI_ConstStringField Protocol;
    MI_ConstStringField Ensure;
    MI_ConstStringField AddressFamily;
    MI_ConstStringField Access;
    MI_ConstStringAField State;
    MI_ConstStringField Direction;
    MI_ConstStringField SourceHost;
    MI_ConstStringField SourcePort;
    MI_ConstStringField DestinationHost;
    MI_ConstStringField DestinationPort;
    MI_ConstStringField Position;
}
MSFT_nxFirewallResource;

typedef struct _MSFT_nxFirewallResource_Ref
{
    MSFT_nxFirewallResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFirewallResource_Ref;

typedef struct _MSFT_nxFirewallResource_ConstRef
{
    MI_CONST MSFT_nxFirewallResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFirewallResource_ConstRef;

typedef struct _MSFT_nxFirewallResource_Array
{
    struct _MSFT_nxFirewallResource** data;
    MI_Uint32 size;
}
MSFT_nxFirewallResource_Array;

typedef struct _MSFT_nxFirewallResource_ConstArray
{
    struct _MSFT_nxFirewallResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxFirewallResource_ConstArray;

typedef struct _MSFT_nxFirewallResource_ArrayRef
{
    MSFT_nxFirewallResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFirewallResource_ArrayRef;

typedef struct _MSFT_nxFirewallResource_ConstArrayRef
{
    MSFT_nxFirewallResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxFirewallResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxFirewallResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Construct(
    _Out_ MSFT_nxFirewallResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxFirewallResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clone(
    _In_ const MSFT_nxFirewallResource* self,
    _Outptr_ MSFT_nxFirewallResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxFirewallResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxFirewallResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Destruct(_Inout_ MSFT_nxFirewallResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Delete(_Inout_ MSFT_nxFirewallResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Post(
    _In_ const MSFT_nxFirewallResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_Name(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_Name(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_Name(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_InterfaceName(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_InterfaceName(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_InterfaceName(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_FirewallType(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_FirewallType(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_FirewallType(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_Protocol(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_Protocol(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_Protocol(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_Ensure(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_Ensure(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_Ensure(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_AddressFamily(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_AddressFamily(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_AddressFamily(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_Access(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_Access(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_Access(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_State(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_State(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_State(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_Direction(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_Direction(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_Direction(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_SourceHost(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_SourceHost(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_SourceHost(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_SourcePort(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_SourcePort(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_SourcePort(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_DestinationHost(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_DestinationHost(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_DestinationHost(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_DestinationPort(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_DestinationPort(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_DestinationPort(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Set_Position(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetPtr_Position(
    _Inout_ MSFT_nxFirewallResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_Clear_Position(
    _Inout_ MSFT_nxFirewallResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

/*
**==============================================================================
**
** MSFT_nxFirewallResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxFirewallResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxFirewallResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MSFT_nxFirewallResource_ConstRef OutputResource;
}
MSFT_nxFirewallResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxFirewallResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Construct(
    _Out_ MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxFirewallResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Clone(
    _In_ const MSFT_nxFirewallResource_GetTargetResource* self,
    _Outptr_ MSFT_nxFirewallResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Destruct(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Delete(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Post(
    _In_ const MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Set_Flags(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Set_OutputResource(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_GetTargetResource_Clear_OutputResource(
    _Inout_ MSFT_nxFirewallResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_nxFirewallResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxFirewallResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxFirewallResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
MSFT_nxFirewallResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxFirewallResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Construct(
    _Out_ MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxFirewallResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Clone(
    _In_ const MSFT_nxFirewallResource_TestTargetResource* self,
    _Outptr_ MSFT_nxFirewallResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Destruct(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Delete(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Post(
    _In_ const MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Set_InputResource(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Set_Flags(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Clear_Flags(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Set_Result(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Clear_Result(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxFirewallResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxFirewallResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _MSFT_nxFirewallResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_nxFirewallResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
MSFT_nxFirewallResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_nxFirewallResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Construct(
    _Out_ MSFT_nxFirewallResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_nxFirewallResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Clone(
    _In_ const MSFT_nxFirewallResource_SetTargetResource* self,
    _Outptr_ MSFT_nxFirewallResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Destruct(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Delete(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Post(
    _In_ const MSFT_nxFirewallResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Set_MIReturn(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Clear_MIReturn(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Set_InputResource(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self,
    _In_ const MSFT_nxFirewallResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Clear_InputResource(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Set_ProviderContext(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Set_Flags(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxFirewallResource_SetTargetResource_Clear_Flags(
    _Inout_ MSFT_nxFirewallResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_nxFirewallResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxFirewallResource_Self MSFT_nxFirewallResource_Self;

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_Load(
    _Outptr_result_maybenull_ MSFT_nxFirewallResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_Unload(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_EnumerateInstances(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_GetInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_CreateInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_ModifyInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_DeleteInstance(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxFirewallResource* instanceName);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MSFT_nxFirewallResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MSFT_nxFirewallResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL MSFT_nxFirewallResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_nxFirewallResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxFirewallResource* instanceName,
    _In_opt_ const MSFT_nxFirewallResource_SetTargetResource* in);


#endif /* _MSFT_nxFirewallResource_h */

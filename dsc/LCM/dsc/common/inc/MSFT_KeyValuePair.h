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
#ifndef _MSFT_KeyValuePair_h
#define _MSFT_KeyValuePair_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_KeyValuePair [MSFT_KeyValuePair]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _MSFT_KeyValuePair
{
    MI_Instance __instance;
    /* MSFT_KeyValuePair properties */
    /*KEY*/ MI_ConstStringField Key;
    MI_ConstStringField Value;
}
MSFT_KeyValuePair;

typedef struct _MSFT_KeyValuePair_Ref
{
    MSFT_KeyValuePair* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_KeyValuePair_Ref;

typedef struct _MSFT_KeyValuePair_ConstRef
{
    MI_CONST MSFT_KeyValuePair* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_KeyValuePair_ConstRef;

typedef struct _MSFT_KeyValuePair_Array
{
    struct _MSFT_KeyValuePair** data;
    MI_Uint32 size;
}
MSFT_KeyValuePair_Array;

typedef struct _MSFT_KeyValuePair_ConstArray
{
    struct _MSFT_KeyValuePair MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_KeyValuePair_ConstArray;

typedef struct _MSFT_KeyValuePair_ArrayRef
{
    MSFT_KeyValuePair_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_KeyValuePair_ArrayRef;

typedef struct _MSFT_KeyValuePair_ConstArrayRef
{
    MSFT_KeyValuePair_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_KeyValuePair_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_KeyValuePair_rtti;

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Construct(
    _Out_ MSFT_KeyValuePair* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_KeyValuePair_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Clone(
    _In_ const MSFT_KeyValuePair* self,
    _Outptr_ MSFT_KeyValuePair** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_KeyValuePair_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_KeyValuePair_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Destruct(_Inout_ MSFT_KeyValuePair* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Delete(_Inout_ MSFT_KeyValuePair* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Post(
    _In_ const MSFT_KeyValuePair* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Set_Key(
    _Inout_ MSFT_KeyValuePair* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_SetPtr_Key(
    _Inout_ MSFT_KeyValuePair* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Clear_Key(
    _Inout_ MSFT_KeyValuePair* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Set_Value(
    _Inout_ MSFT_KeyValuePair* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_SetPtr_Value(
    _Inout_ MSFT_KeyValuePair* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_KeyValuePair_Clear_Value(
    _Inout_ MSFT_KeyValuePair* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_KeyValuePair_h */

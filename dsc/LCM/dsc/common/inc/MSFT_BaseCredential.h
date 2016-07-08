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
#ifndef _MSFT_Credential_h
#define _MSFT_Credential_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_Credential [MSFT_Credential]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_Credential
{
    MI_Instance __instance;
    /* MSFT_Credential properties */
    MI_ConstStringField UserName;
    MI_ConstStringField Password;
}
MSFT_Credential;

typedef struct _MSFT_Credential_Ref
{
    MSFT_Credential* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Credential_Ref;

typedef struct _MSFT_Credential_ConstRef
{
    MI_CONST MSFT_Credential* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Credential_ConstRef;

typedef struct _MSFT_Credential_Array
{
    struct _MSFT_Credential** data;
    MI_Uint32 size;
}
MSFT_Credential_Array;

typedef struct _MSFT_Credential_ConstArray
{
    struct _MSFT_Credential MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Credential_ConstArray;

typedef struct _MSFT_Credential_ArrayRef
{
    MSFT_Credential_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Credential_ArrayRef;

typedef struct _MSFT_Credential_ConstArrayRef
{
    MSFT_Credential_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Credential_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Credential_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Credential_Construct(
    _Out_ MSFT_Credential* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_Credential_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Clone(
    _In_ const MSFT_Credential* self,
    _Outptr_ MSFT_Credential** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Credential_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Credential_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Destruct(_Inout_ MSFT_Credential* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Delete(_Inout_ MSFT_Credential* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Post(
    _In_ const MSFT_Credential* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Set_UserName(
    _Inout_ MSFT_Credential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_SetPtr_UserName(
    _Inout_ MSFT_Credential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Clear_UserName(
    _Inout_ MSFT_Credential* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Set_Password(
    _Inout_ MSFT_Credential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_SetPtr_Password(
    _Inout_ MSFT_Credential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Credential_Clear_Password(
    _Inout_ MSFT_Credential* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_Credential_h */


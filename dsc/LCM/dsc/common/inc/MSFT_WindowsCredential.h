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
#ifndef _MSFT_WindowsCredential_h
#define _MSFT_WindowsCredential_h

#include <MI.h>
#include "MSFT_BaseCredential.h"

/*
**==============================================================================
**
** MSFT_WindowsCredential [MSFT_WindowsCredential]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_WindowsCredential /* extends MSFT_BaseCredential */
{
    MI_Instance __instance;
    /* MSFT_BaseCredential properties */
    MI_ConstStringField UserName;
    MI_ConstStringField Password;
    /* MSFT_WindowsCredential properties */
    MI_ConstStringField Domain;
}
MSFT_WindowsCredential;

typedef struct _MSFT_WindowsCredential_Ref
{
    MSFT_WindowsCredential* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WindowsCredential_Ref;

typedef struct _MSFT_WindowsCredential_ConstRef
{
    MI_CONST MSFT_WindowsCredential* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WindowsCredential_ConstRef;

typedef struct _MSFT_WindowsCredential_Array
{
    struct _MSFT_WindowsCredential** data;
    MI_Uint32 size;
}
MSFT_WindowsCredential_Array;

typedef struct _MSFT_WindowsCredential_ConstArray
{
    struct _MSFT_WindowsCredential MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_WindowsCredential_ConstArray;

typedef struct _MSFT_WindowsCredential_ArrayRef
{
    MSFT_WindowsCredential_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WindowsCredential_ArrayRef;

typedef struct _MSFT_WindowsCredential_ConstArrayRef
{
    MSFT_WindowsCredential_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_WindowsCredential_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_WindowsCredential_rtti;

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Construct(
    _Out_ MSFT_WindowsCredential* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_WindowsCredential_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Clone(
    _In_ const MSFT_WindowsCredential* self,
    _Outptr_ MSFT_WindowsCredential** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_WindowsCredential_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_WindowsCredential_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Destruct(_Inout_ MSFT_WindowsCredential* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Delete(_Inout_ MSFT_WindowsCredential* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Post(
    _In_ const MSFT_WindowsCredential* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Set_UserName(
    _Inout_ MSFT_WindowsCredential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_SetPtr_UserName(
    _Inout_ MSFT_WindowsCredential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Clear_UserName(
    _Inout_ MSFT_WindowsCredential* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Set_Password(
    _Inout_ MSFT_WindowsCredential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_SetPtr_Password(
    _Inout_ MSFT_WindowsCredential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Clear_Password(
    _Inout_ MSFT_WindowsCredential* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Set_Domain(
    _Inout_ MSFT_WindowsCredential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_SetPtr_Domain(
    _Inout_ MSFT_WindowsCredential* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_WindowsCredential_Clear_Domain(
    _Inout_ MSFT_WindowsCredential* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}


#endif /* _MSFT_WindowsCredential_h */

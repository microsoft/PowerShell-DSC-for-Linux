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
#ifndef _MSFT_BaseResourceConfiguration_h
#define _MSFT_BaseResourceConfiguration_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_BaseResourceConfiguration [MSFT_BaseResourceConfiguration]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_BaseResourceConfiguration
{
    MI_Instance __instance;
    /* MSFT_BaseResourceConfiguration properties */
}
MSFT_BaseResourceConfiguration;

typedef struct _MSFT_BaseResourceConfiguration_Ref
{
    MSFT_BaseResourceConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseResourceConfiguration_Ref;

typedef struct _MSFT_BaseResourceConfiguration_ConstRef
{
    MI_CONST MSFT_BaseResourceConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseResourceConfiguration_ConstRef;

typedef struct _MSFT_BaseResourceConfiguration_Array
{
    struct _MSFT_BaseResourceConfiguration** data;
    MI_Uint32 size;
}
MSFT_BaseResourceConfiguration_Array;

typedef struct _MSFT_BaseResourceConfiguration_ConstArray
{
    struct _MSFT_BaseResourceConfiguration MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_BaseResourceConfiguration_ConstArray;

typedef struct _MSFT_BaseResourceConfiguration_ArrayRef
{
    MSFT_BaseResourceConfiguration_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseResourceConfiguration_ArrayRef;

typedef struct _MSFT_BaseResourceConfiguration_ConstArrayRef
{
    MSFT_BaseResourceConfiguration_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseResourceConfiguration_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_BaseResourceConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_BaseResourceConfiguration_Construct(
    _Out_ MSFT_BaseResourceConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_BaseResourceConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BaseResourceConfiguration_Clone(
    _In_ const MSFT_BaseResourceConfiguration* self,
    _Outptr_ MSFT_BaseResourceConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_BaseResourceConfiguration_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_BaseResourceConfiguration_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_BaseResourceConfiguration_Destruct(_Inout_ MSFT_BaseResourceConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BaseResourceConfiguration_Delete(_Inout_ MSFT_BaseResourceConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BaseResourceConfiguration_Post(
    _In_ const MSFT_BaseResourceConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}


#endif /* _MSFT_BaseResourceConfiguration_h */

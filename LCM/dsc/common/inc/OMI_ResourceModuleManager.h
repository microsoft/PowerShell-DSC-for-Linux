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
#ifndef _OMI_ResourceModuleManager_h
#define _OMI_ResourceModuleManager_h

#include <MI.h>
#include "OMI_MetaConfigurationResource.h"

/*
**==============================================================================
**
** OMI_ResourceModuleManager [OMI_ResourceModuleManager]
**
** Keys:
**
**==============================================================================
*/

typedef struct _OMI_ResourceModuleManager /* extends OMI_MetaConfigurationResource */
{
    MI_Instance __instance;
    /* OMI_MetaConfigurationResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    /* OMI_ResourceModuleManager properties */
}
OMI_ResourceModuleManager;

typedef struct _OMI_ResourceModuleManager_Ref
{
    OMI_ResourceModuleManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ResourceModuleManager_Ref;

typedef struct _OMI_ResourceModuleManager_ConstRef
{
    MI_CONST OMI_ResourceModuleManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ResourceModuleManager_ConstRef;

typedef struct _OMI_ResourceModuleManager_Array
{
    struct _OMI_ResourceModuleManager** data;
    MI_Uint32 size;
}
OMI_ResourceModuleManager_Array;

typedef struct _OMI_ResourceModuleManager_ConstArray
{
    struct _OMI_ResourceModuleManager MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_ResourceModuleManager_ConstArray;

typedef struct _OMI_ResourceModuleManager_ArrayRef
{
    OMI_ResourceModuleManager_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ResourceModuleManager_ArrayRef;

typedef struct _OMI_ResourceModuleManager_ConstArrayRef
{
    OMI_ResourceModuleManager_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ResourceModuleManager_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_ResourceModuleManager_rtti;

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Construct(
    _Out_ OMI_ResourceModuleManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &OMI_ResourceModuleManager_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Clone(
    _In_ const OMI_ResourceModuleManager* self,
    _Outptr_ OMI_ResourceModuleManager** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_ResourceModuleManager_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_ResourceModuleManager_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Destruct(_Inout_ OMI_ResourceModuleManager* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Delete(_Inout_ OMI_ResourceModuleManager* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Post(
    _In_ const OMI_ResourceModuleManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Set_ResourceId(
    _Inout_ OMI_ResourceModuleManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_SetPtr_ResourceId(
    _Inout_ OMI_ResourceModuleManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Clear_ResourceId(
    _Inout_ OMI_ResourceModuleManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Set_SourceInfo(
    _Inout_ OMI_ResourceModuleManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_SetPtr_SourceInfo(
    _Inout_ OMI_ResourceModuleManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ResourceModuleManager_Clear_SourceInfo(
    _Inout_ OMI_ResourceModuleManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _OMI_ResourceModuleManager_h */

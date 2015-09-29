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
#ifndef _TEST_Test2_h
#define _TEST_Test2_h

#include <MI.h>
#include "OMI_BaseResource.h"

/*
**==============================================================================
**
** TEST_Test2 [TEST_Test2]
**
** Keys:
**    Id1
**
**==============================================================================
*/

typedef struct _TEST_Test2 /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* TEST_Test2 properties */
    /*KEY*/ MI_ConstStringField Id1;
}
TEST_Test2;

typedef struct _TEST_Test2_Ref
{
    TEST_Test2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test2_Ref;

typedef struct _TEST_Test2_ConstRef
{
    MI_CONST TEST_Test2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test2_ConstRef;

typedef struct _TEST_Test2_Array
{
    struct _TEST_Test2** data;
    MI_Uint32 size;
}
TEST_Test2_Array;

typedef struct _TEST_Test2_ConstArray
{
    struct _TEST_Test2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TEST_Test2_ConstArray;

typedef struct _TEST_Test2_ArrayRef
{
    TEST_Test2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test2_ArrayRef;

typedef struct _TEST_Test2_ConstArrayRef
{
    TEST_Test2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TEST_Test2_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test2_Construct(
    _Out_ TEST_Test2* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &TEST_Test2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_Clone(
    _In_ const TEST_Test2* self,
    _Outptr_ TEST_Test2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TEST_Test2_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TEST_Test2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_Destruct(_Inout_ TEST_Test2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_Delete(_Inout_ TEST_Test2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_Post(
    _In_ const TEST_Test2* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_Set_Id1(
    _Inout_ TEST_Test2* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetPtr_Id1(
    _Inout_ TEST_Test2* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_Clear_Id1(
    _Inout_ TEST_Test2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** TEST_Test2.GetTargetResource()
**
**==============================================================================
*/

typedef struct _TEST_Test2_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_BaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ OMI_BaseResource_ConstRef OutputResource;
}
TEST_Test2_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl TEST_Test2_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Construct(
    _Out_ TEST_Test2_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &TEST_Test2_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Clone(
    _In_ const TEST_Test2_GetTargetResource* self,
    _Outptr_ TEST_Test2_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Destruct(
    _Inout_ TEST_Test2_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Delete(
    _Inout_ TEST_Test2_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Post(
    _In_ const TEST_Test2_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Set_MIReturn(
    _Inout_ TEST_Test2_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Clear_MIReturn(
    _Inout_ TEST_Test2_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Set_InputResource(
    _Inout_ TEST_Test2_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_SetPtr_InputResource(
    _Inout_ TEST_Test2_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Clear_InputResource(
    _Inout_ TEST_Test2_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Set_Flags(
    _Inout_ TEST_Test2_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Clear_Flags(
    _Inout_ TEST_Test2_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Set_OutputResource(
    _Inout_ TEST_Test2_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_SetPtr_OutputResource(
    _Inout_ TEST_Test2_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_GetTargetResource_Clear_OutputResource(
    _Inout_ TEST_Test2_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** TEST_Test2.TestTargetResource()
**
**==============================================================================
*/

typedef struct _TEST_Test2_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_BaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
TEST_Test2_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl TEST_Test2_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Construct(
    _Out_ TEST_Test2_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &TEST_Test2_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Clone(
    _In_ const TEST_Test2_TestTargetResource* self,
    _Outptr_ TEST_Test2_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Destruct(
    _Inout_ TEST_Test2_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Delete(
    _Inout_ TEST_Test2_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Post(
    _In_ const TEST_Test2_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Set_MIReturn(
    _Inout_ TEST_Test2_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Clear_MIReturn(
    _Inout_ TEST_Test2_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Set_InputResource(
    _Inout_ TEST_Test2_TestTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_SetPtr_InputResource(
    _Inout_ TEST_Test2_TestTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Clear_InputResource(
    _Inout_ TEST_Test2_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Set_Flags(
    _Inout_ TEST_Test2_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Clear_Flags(
    _Inout_ TEST_Test2_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Set_Result(
    _Inout_ TEST_Test2_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Clear_Result(
    _Inout_ TEST_Test2_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Set_ProviderContext(
    _Inout_ TEST_Test2_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_TestTargetResource_Clear_ProviderContext(
    _Inout_ TEST_Test2_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TEST_Test2.SetTargetResource()
**
**==============================================================================
*/

typedef struct _TEST_Test2_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_BaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
TEST_Test2_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl TEST_Test2_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Construct(
    _Out_ TEST_Test2_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &TEST_Test2_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Clone(
    _In_ const TEST_Test2_SetTargetResource* self,
    _Outptr_ TEST_Test2_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Destruct(
    _Inout_ TEST_Test2_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Delete(
    _Inout_ TEST_Test2_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Post(
    _In_ const TEST_Test2_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Set_MIReturn(
    _Inout_ TEST_Test2_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Clear_MIReturn(
    _Inout_ TEST_Test2_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Set_InputResource(
    _Inout_ TEST_Test2_SetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_SetPtr_InputResource(
    _Inout_ TEST_Test2_SetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Clear_InputResource(
    _Inout_ TEST_Test2_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Set_ProviderContext(
    _Inout_ TEST_Test2_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Clear_ProviderContext(
    _Inout_ TEST_Test2_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Set_Flags(
    _Inout_ TEST_Test2_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test2_SetTargetResource_Clear_Flags(
    _Inout_ TEST_Test2_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TEST_Test2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TEST_Test2_Self TEST_Test2_Self;

MI_EXTERN_C void MI_CALL TEST_Test2_Load(
    _Outptr_result_maybenull_ TEST_Test2_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TEST_Test2_Unload(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TEST_Test2_EnumerateInstances(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL TEST_Test2_GetInstance(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test2* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TEST_Test2_CreateInstance(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test2* newInstance);

MI_EXTERN_C void MI_CALL TEST_Test2_ModifyInstance(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test2* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TEST_Test2_DeleteInstance(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test2* instanceName);

MI_EXTERN_C void MI_CALL TEST_Test2_Invoke_GetTargetResource(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test2* instanceName,
    _In_opt_ const TEST_Test2_GetTargetResource* in);

MI_EXTERN_C void MI_CALL TEST_Test2_Invoke_TestTargetResource(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test2* instanceName,
    _In_opt_ const TEST_Test2_TestTargetResource* in);

MI_EXTERN_C void MI_CALL TEST_Test2_Invoke_SetTargetResource(
    _In_opt_ TEST_Test2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test2* instanceName,
    _In_opt_ const TEST_Test2_SetTargetResource* in);


#endif /* _TEST_Test2_h */

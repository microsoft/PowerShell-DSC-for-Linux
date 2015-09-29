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
#ifndef _TEST_Test3User_h
#define _TEST_Test3User_h

#include <MI.h>
#include "OMI_BaseResource.h"

/*
**==============================================================================
**
** TEST_Test3User [TEST_Test3User]
**
** Keys:
**    Id1
**
**==============================================================================
*/

typedef struct _TEST_Test3User /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* TEST_Test3User properties */
    /*KEY*/ MI_ConstStringField Id1;
}
TEST_Test3User;

typedef struct _TEST_Test3User_Ref
{
    TEST_Test3User* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test3User_Ref;

typedef struct _TEST_Test3User_ConstRef
{
    MI_CONST TEST_Test3User* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test3User_ConstRef;

typedef struct _TEST_Test3User_Array
{
    struct _TEST_Test3User** data;
    MI_Uint32 size;
}
TEST_Test3User_Array;

typedef struct _TEST_Test3User_ConstArray
{
    struct _TEST_Test3User MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TEST_Test3User_ConstArray;

typedef struct _TEST_Test3User_ArrayRef
{
    TEST_Test3User_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test3User_ArrayRef;

typedef struct _TEST_Test3User_ConstArrayRef
{
    TEST_Test3User_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TEST_Test3User_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TEST_Test3User_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test3User_Construct(
    _Out_ TEST_Test3User* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &TEST_Test3User_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_Clone(
    _In_ const TEST_Test3User* self,
    _Outptr_ TEST_Test3User** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TEST_Test3User_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TEST_Test3User_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_Destruct(_Inout_ TEST_Test3User* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_Delete(_Inout_ TEST_Test3User* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_Post(
    _In_ const TEST_Test3User* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_Set_Id1(
    _Inout_ TEST_Test3User* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetPtr_Id1(
    _Inout_ TEST_Test3User* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_Clear_Id1(
    _Inout_ TEST_Test3User* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** TEST_Test3User.GetTargetResource()
**
**==============================================================================
*/

typedef struct _TEST_Test3User_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_BaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ OMI_BaseResource_ConstRef OutputResource;
}
TEST_Test3User_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl TEST_Test3User_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Construct(
    _Out_ TEST_Test3User_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &TEST_Test3User_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Clone(
    _In_ const TEST_Test3User_GetTargetResource* self,
    _Outptr_ TEST_Test3User_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Destruct(
    _Inout_ TEST_Test3User_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Delete(
    _Inout_ TEST_Test3User_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Post(
    _In_ const TEST_Test3User_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Set_MIReturn(
    _Inout_ TEST_Test3User_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Clear_MIReturn(
    _Inout_ TEST_Test3User_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Set_InputResource(
    _Inout_ TEST_Test3User_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_SetPtr_InputResource(
    _Inout_ TEST_Test3User_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Clear_InputResource(
    _Inout_ TEST_Test3User_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Set_Flags(
    _Inout_ TEST_Test3User_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Clear_Flags(
    _Inout_ TEST_Test3User_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Set_OutputResource(
    _Inout_ TEST_Test3User_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_SetPtr_OutputResource(
    _Inout_ TEST_Test3User_GetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_GetTargetResource_Clear_OutputResource(
    _Inout_ TEST_Test3User_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** TEST_Test3User.TestTargetResource()
**
**==============================================================================
*/

typedef struct _TEST_Test3User_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_BaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
TEST_Test3User_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl TEST_Test3User_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Construct(
    _Out_ TEST_Test3User_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &TEST_Test3User_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Clone(
    _In_ const TEST_Test3User_TestTargetResource* self,
    _Outptr_ TEST_Test3User_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Destruct(
    _Inout_ TEST_Test3User_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Delete(
    _Inout_ TEST_Test3User_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Post(
    _In_ const TEST_Test3User_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Set_MIReturn(
    _Inout_ TEST_Test3User_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Clear_MIReturn(
    _Inout_ TEST_Test3User_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Set_InputResource(
    _Inout_ TEST_Test3User_TestTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_SetPtr_InputResource(
    _Inout_ TEST_Test3User_TestTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Clear_InputResource(
    _Inout_ TEST_Test3User_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Set_Flags(
    _Inout_ TEST_Test3User_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Clear_Flags(
    _Inout_ TEST_Test3User_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Set_Result(
    _Inout_ TEST_Test3User_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Clear_Result(
    _Inout_ TEST_Test3User_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Set_ProviderContext(
    _Inout_ TEST_Test3User_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_TestTargetResource_Clear_ProviderContext(
    _Inout_ TEST_Test3User_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TEST_Test3User.SetTargetResource()
**
**==============================================================================
*/

typedef struct _TEST_Test3User_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_BaseResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
TEST_Test3User_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl TEST_Test3User_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Construct(
    _Out_ TEST_Test3User_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &TEST_Test3User_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Clone(
    _In_ const TEST_Test3User_SetTargetResource* self,
    _Outptr_ TEST_Test3User_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Destruct(
    _Inout_ TEST_Test3User_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Delete(
    _Inout_ TEST_Test3User_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Post(
    _In_ const TEST_Test3User_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Set_MIReturn(
    _Inout_ TEST_Test3User_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Clear_MIReturn(
    _Inout_ TEST_Test3User_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Set_InputResource(
    _Inout_ TEST_Test3User_SetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_SetPtr_InputResource(
    _Inout_ TEST_Test3User_SetTargetResource* self,
    _In_ const OMI_BaseResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Clear_InputResource(
    _Inout_ TEST_Test3User_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Set_ProviderContext(
    _Inout_ TEST_Test3User_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Clear_ProviderContext(
    _Inout_ TEST_Test3User_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Set_Flags(
    _Inout_ TEST_Test3User_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TEST_Test3User_SetTargetResource_Clear_Flags(
    _Inout_ TEST_Test3User_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TEST_Test3User provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TEST_Test3User_Self TEST_Test3User_Self;

MI_EXTERN_C void MI_CALL TEST_Test3User_Load(
    _Outptr_result_maybenull_ TEST_Test3User_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TEST_Test3User_Unload(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TEST_Test3User_EnumerateInstances(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL TEST_Test3User_GetInstance(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test3User* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TEST_Test3User_CreateInstance(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test3User* newInstance);

MI_EXTERN_C void MI_CALL TEST_Test3User_ModifyInstance(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test3User* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TEST_Test3User_DeleteInstance(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TEST_Test3User* instanceName);

MI_EXTERN_C void MI_CALL TEST_Test3User_Invoke_GetTargetResource(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test3User* instanceName,
    _In_opt_ const TEST_Test3User_GetTargetResource* in);

MI_EXTERN_C void MI_CALL TEST_Test3User_Invoke_TestTargetResource(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test3User* instanceName,
    _In_opt_ const TEST_Test3User_TestTargetResource* in);

MI_EXTERN_C void MI_CALL TEST_Test3User_Invoke_SetTargetResource(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test3User* instanceName,
    _In_opt_ const TEST_Test3User_SetTargetResource* in);


#endif /* _TEST_Test3User_h */

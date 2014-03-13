/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_nxEnvironmentResource_h
#define _OMI_nxEnvironmentResource_h

#include <MI.h>
#include "OMI_BaseResource.h"
#include "OMI_nxEnvironmentResource.h"

/*
**==============================================================================
**
** OMI_nxEnvironmentResource [OMI_nxEnvironmentResource]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _OMI_nxEnvironmentResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* OMI_nxEnvironmentResource properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Value;
    MI_ConstStringField Ensure;
    MI_ConstBooleanField Path;
}
OMI_nxEnvironmentResource;

typedef struct _OMI_nxEnvironmentResource_Ref
{
    OMI_nxEnvironmentResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxEnvironmentResource_Ref;

typedef struct _OMI_nxEnvironmentResource_ConstRef
{
    MI_CONST OMI_nxEnvironmentResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxEnvironmentResource_ConstRef;

typedef struct _OMI_nxEnvironmentResource_Array
{
    struct _OMI_nxEnvironmentResource** data;
    MI_Uint32 size;
}
OMI_nxEnvironmentResource_Array;

typedef struct _OMI_nxEnvironmentResource_ConstArray
{
    struct _OMI_nxEnvironmentResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_nxEnvironmentResource_ConstArray;

typedef struct _OMI_nxEnvironmentResource_ArrayRef
{
    OMI_nxEnvironmentResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxEnvironmentResource_ArrayRef;

typedef struct _OMI_nxEnvironmentResource_ConstArrayRef
{
    OMI_nxEnvironmentResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_nxEnvironmentResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_nxEnvironmentResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Construct(
    _Out_ OMI_nxEnvironmentResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &OMI_nxEnvironmentResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Clone(
    _In_ const OMI_nxEnvironmentResource* self,
    _Outptr_ OMI_nxEnvironmentResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_nxEnvironmentResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_nxEnvironmentResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Destruct(_Inout_ OMI_nxEnvironmentResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Delete(_Inout_ OMI_nxEnvironmentResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Post(
    _In_ const OMI_nxEnvironmentResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Set_Name(
    _Inout_ OMI_nxEnvironmentResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetPtr_Name(
    _Inout_ OMI_nxEnvironmentResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Clear_Name(
    _Inout_ OMI_nxEnvironmentResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Set_Value(
    _Inout_ OMI_nxEnvironmentResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetPtr_Value(
    _Inout_ OMI_nxEnvironmentResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Clear_Value(
    _Inout_ OMI_nxEnvironmentResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Set_Ensure(
    _Inout_ OMI_nxEnvironmentResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetPtr_Ensure(
    _Inout_ OMI_nxEnvironmentResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Clear_Ensure(
    _Inout_ OMI_nxEnvironmentResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Set_Path(
    _Inout_ OMI_nxEnvironmentResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Path)->value = x;
    ((MI_BooleanField*)&self->Path)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_Clear_Path(
    _Inout_ OMI_nxEnvironmentResource* self)
{
    memset((void*)&self->Path, 0, sizeof(self->Path));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_nxEnvironmentResource.GetTargetResource()
**
**==============================================================================
*/

typedef struct _OMI_nxEnvironmentResource_GetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_nxEnvironmentResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ OMI_nxEnvironmentResource_ConstRef OutputResource;
}
OMI_nxEnvironmentResource_GetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_nxEnvironmentResource_GetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Construct(
    _Out_ OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &OMI_nxEnvironmentResource_GetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Clone(
    _In_ const OMI_nxEnvironmentResource_GetTargetResource* self,
    _Outptr_ OMI_nxEnvironmentResource_GetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Destruct(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Delete(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Post(
    _In_ const OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Set_MIReturn(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Clear_MIReturn(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Set_InputResource(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_SetPtr_InputResource(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Clear_InputResource(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Set_Flags(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Clear_Flags(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Set_OutputResource(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_SetPtr_OutputResource(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_GetTargetResource_Clear_OutputResource(
    _Inout_ OMI_nxEnvironmentResource_GetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** OMI_nxEnvironmentResource.TestTargetResource()
**
**==============================================================================
*/

typedef struct _OMI_nxEnvironmentResource_TestTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_nxEnvironmentResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint32Field Flags;
    /*OUT*/ MI_ConstBooleanField Result;
    /*OUT*/ MI_ConstUint64Field ProviderContext;
}
OMI_nxEnvironmentResource_TestTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_nxEnvironmentResource_TestTargetResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Construct(
    _Out_ OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &OMI_nxEnvironmentResource_TestTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Clone(
    _In_ const OMI_nxEnvironmentResource_TestTargetResource* self,
    _Outptr_ OMI_nxEnvironmentResource_TestTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Destruct(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Delete(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Post(
    _In_ const OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Set_MIReturn(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Clear_MIReturn(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Set_InputResource(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_SetPtr_InputResource(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Clear_InputResource(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Set_Flags(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Clear_Flags(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Set_Result(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Result)->value = x;
    ((MI_BooleanField*)&self->Result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Clear_Result(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self)
{
    memset((void*)&self->Result, 0, sizeof(self->Result));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Set_ProviderContext(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_TestTargetResource_Clear_ProviderContext(
    _Inout_ OMI_nxEnvironmentResource_TestTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_nxEnvironmentResource.SetTargetResource()
**
**==============================================================================
*/

typedef struct _OMI_nxEnvironmentResource_SetTargetResource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ OMI_nxEnvironmentResource_ConstRef InputResource;
    /*IN*/ MI_ConstUint64Field ProviderContext;
    /*IN*/ MI_ConstUint32Field Flags;
}
OMI_nxEnvironmentResource_SetTargetResource;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_nxEnvironmentResource_SetTargetResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Construct(
    _Out_ OMI_nxEnvironmentResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &OMI_nxEnvironmentResource_SetTargetResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Clone(
    _In_ const OMI_nxEnvironmentResource_SetTargetResource* self,
    _Outptr_ OMI_nxEnvironmentResource_SetTargetResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Destruct(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Delete(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Post(
    _In_ const OMI_nxEnvironmentResource_SetTargetResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Set_MIReturn(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Clear_MIReturn(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Set_InputResource(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_SetPtr_InputResource(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self,
    _In_ const OMI_nxEnvironmentResource* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Clear_InputResource(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Set_ProviderContext(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProviderContext)->value = x;
    ((MI_Uint64Field*)&self->ProviderContext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Clear_ProviderContext(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self)
{
    memset((void*)&self->ProviderContext, 0, sizeof(self->ProviderContext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Set_Flags(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Flags)->value = x;
    ((MI_Uint32Field*)&self->Flags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_nxEnvironmentResource_SetTargetResource_Clear_Flags(
    _Inout_ OMI_nxEnvironmentResource_SetTargetResource* self)
{
    memset((void*)&self->Flags, 0, sizeof(self->Flags));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_nxEnvironmentResource provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_nxEnvironmentResource_Self OMI_nxEnvironmentResource_Self;

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_Load(
    _Outptr_result_maybenull_ OMI_nxEnvironmentResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_Unload(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_EnumerateInstances(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_GetInstance(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxEnvironmentResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_CreateInstance(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxEnvironmentResource* newInstance);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_ModifyInstance(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxEnvironmentResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_DeleteInstance(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const OMI_nxEnvironmentResource* instanceName);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_Invoke_GetTargetResource(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const OMI_nxEnvironmentResource* instanceName,
    _In_opt_ const OMI_nxEnvironmentResource_GetTargetResource* in);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_Invoke_TestTargetResource(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const OMI_nxEnvironmentResource* instanceName,
    _In_opt_ const OMI_nxEnvironmentResource_TestTargetResource* in);

MI_EXTERN_C void MI_CALL OMI_nxEnvironmentResource_Invoke_SetTargetResource(
    _In_opt_ OMI_nxEnvironmentResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const OMI_nxEnvironmentResource* instanceName,
    _In_opt_ const OMI_nxEnvironmentResource_SetTargetResource* in);


#endif /* _OMI_nxEnvironmentResource_h */

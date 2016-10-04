/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSInventoryMOFInstance_h
#define _MSFT_nxOMSInventoryMOFInstance_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSInventoryMOFInstance [MSFT_nxOMSInventoryMOFInstance]
**
** Keys:
**    InstanceName
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSInventoryMOFInstance
{
    MI_Instance __instance;
    /* MSFT_nxOMSInventoryMOFInstance properties */
    /*KEY*/ MI_ConstStringField InstanceName;
    MI_ConstStringField ClassName;
    MI_ConstStringField Properties;
}
MSFT_nxOMSInventoryMOFInstance;

typedef struct _MSFT_nxOMSInventoryMOFInstance_Ref
{
    MSFT_nxOMSInventoryMOFInstance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSInventoryMOFInstance_Ref;

typedef struct _MSFT_nxOMSInventoryMOFInstance_ConstRef
{
    MI_CONST MSFT_nxOMSInventoryMOFInstance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSInventoryMOFInstance_ConstRef;

typedef struct _MSFT_nxOMSInventoryMOFInstance_Array
{
    struct _MSFT_nxOMSInventoryMOFInstance** data;
    MI_Uint32 size;
}
MSFT_nxOMSInventoryMOFInstance_Array;

typedef struct _MSFT_nxOMSInventoryMOFInstance_ConstArray
{
    struct _MSFT_nxOMSInventoryMOFInstance MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSInventoryMOFInstance_ConstArray;

typedef struct _MSFT_nxOMSInventoryMOFInstance_ArrayRef
{
    MSFT_nxOMSInventoryMOFInstance_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSInventoryMOFInstance_ArrayRef;

typedef struct _MSFT_nxOMSInventoryMOFInstance_ConstArrayRef
{
    MSFT_nxOMSInventoryMOFInstance_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSInventoryMOFInstance_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSInventoryMOFInstance_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Construct(
    _Out_ MSFT_nxOMSInventoryMOFInstance* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSInventoryMOFInstance_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Clone(
    _In_ const MSFT_nxOMSInventoryMOFInstance* self,
    _Outptr_ MSFT_nxOMSInventoryMOFInstance** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSInventoryMOFInstance_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSInventoryMOFInstance_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Destruct(_Inout_ MSFT_nxOMSInventoryMOFInstance* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Delete(_Inout_ MSFT_nxOMSInventoryMOFInstance* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Post(
    _In_ const MSFT_nxOMSInventoryMOFInstance* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Set_InstanceName(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_SetPtr_InstanceName(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Clear_InstanceName(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Set_ClassName(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_SetPtr_ClassName(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Clear_ClassName(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Set_Properties(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_SetPtr_Properties(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSInventoryMOFInstance_Clear_Properties(
    _Inout_ MSFT_nxOMSInventoryMOFInstance* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_nxOMSInventoryMOFInstance provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_nxOMSInventoryMOFInstance_Self MSFT_nxOMSInventoryMOFInstance_Self;

MI_EXTERN_C void MI_CALL MSFT_nxOMSInventoryMOFInstance_Load(
    _Outptr_result_maybenull_ MSFT_nxOMSInventoryMOFInstance_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSInventoryMOFInstance_Unload(
    _In_opt_ MSFT_nxOMSInventoryMOFInstance_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_nxOMSInventoryMOFInstance_EnumerateInstances(
    _In_opt_ MSFT_nxOMSInventoryMOFInstance_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_nxOMSInventoryMOFInstance_GetInstance(
    _In_opt_ MSFT_nxOMSInventoryMOFInstance_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSInventoryMOFInstance* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSInventoryMOFInstance_CreateInstance(
    _In_opt_ MSFT_nxOMSInventoryMOFInstance_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSInventoryMOFInstance* newInstance);

MI_EXTERN_C void MI_CALL MSFT_nxOMSInventoryMOFInstance_ModifyInstance(
    _In_opt_ MSFT_nxOMSInventoryMOFInstance_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSInventoryMOFInstance* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_nxOMSInventoryMOFInstance_DeleteInstance(
    _In_opt_ MSFT_nxOMSInventoryMOFInstance_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_nxOMSInventoryMOFInstance* instanceName);


#endif /* _MSFT_nxOMSInventoryMOFInstance_h */

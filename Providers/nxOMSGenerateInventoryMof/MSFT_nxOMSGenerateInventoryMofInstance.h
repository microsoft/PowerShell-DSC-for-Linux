/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSGenerateInventoryMofInstance_h
#define _MSFT_nxOMSGenerateInventoryMofInstance_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSGenerateInventoryMofInstance [MSFT_nxOMSGenerateInventoryMofInstance]
**
** Keys:
**    InstanceName
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSGenerateInventoryMofInstance
{
    MI_Instance __instance;
    /* MSFT_nxOMSGenerateInventoryMofInstance properties */
    /*KEY*/ MI_ConstStringField InstanceName;
    MI_ConstStringField ClassName;
    MI_ConstStringAField Properties;
}
MSFT_nxOMSGenerateInventoryMofInstance;

typedef struct _MSFT_nxOMSGenerateInventoryMofInstance_Ref
{
    MSFT_nxOMSGenerateInventoryMofInstance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofInstance_Ref;

typedef struct _MSFT_nxOMSGenerateInventoryMofInstance_ConstRef
{
    MI_CONST MSFT_nxOMSGenerateInventoryMofInstance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofInstance_ConstRef;

typedef struct _MSFT_nxOMSGenerateInventoryMofInstance_Array
{
    struct _MSFT_nxOMSGenerateInventoryMofInstance** data;
    MI_Uint32 size;
}
MSFT_nxOMSGenerateInventoryMofInstance_Array;

typedef struct _MSFT_nxOMSGenerateInventoryMofInstance_ConstArray
{
    struct _MSFT_nxOMSGenerateInventoryMofInstance MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSGenerateInventoryMofInstance_ConstArray;

typedef struct _MSFT_nxOMSGenerateInventoryMofInstance_ArrayRef
{
    MSFT_nxOMSGenerateInventoryMofInstance_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofInstance_ArrayRef;

typedef struct _MSFT_nxOMSGenerateInventoryMofInstance_ConstArrayRef
{
    MSFT_nxOMSGenerateInventoryMofInstance_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSGenerateInventoryMofInstance_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSGenerateInventoryMofInstance_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Construct(
    _Out_ MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSGenerateInventoryMofInstance_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Clone(
    _In_ const MSFT_nxOMSGenerateInventoryMofInstance* self,
    _Outptr_ MSFT_nxOMSGenerateInventoryMofInstance** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSGenerateInventoryMofInstance_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Destruct(_Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Delete(_Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Post(
    _In_ const MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Set_InstanceName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_SetPtr_InstanceName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Clear_InstanceName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Set_ClassName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_SetPtr_ClassName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Clear_ClassName(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Set_Properties(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_SetPtr_Properties(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSGenerateInventoryMofInstance_Clear_Properties(
    _Inout_ MSFT_nxOMSGenerateInventoryMofInstance* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}


#endif /* _MSFT_nxOMSGenerateInventoryMofInstance_h */

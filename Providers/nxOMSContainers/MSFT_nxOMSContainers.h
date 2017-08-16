/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSContainersProperty_h
#define _MSFT_nxOMSContainersProperty_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSContainersProperty [MSFT_nxOMSContainersProperty]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSContainersProperty
{
    MI_Instance __instance;
    /* MSFT_nxOMSContainersProperty properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Ensure;
}
MSFT_nxOMSContainersProperty;

typedef struct _MSFT_nxOMSContainersProperty_Ref
{
    MSFT_nxOMSContainersProperty* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSContainersProperty_Ref;

typedef struct _MSFT_nxOMSContainersProperty_ConstRef
{
    MI_CONST MSFT_nxOMSContainersProperty* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSContainersProperty_ConstRef;

typedef struct _MSFT_nxOMSContainersProperty_Array
{
    struct _MSFT_nxOMSContainersProperty** data;
    MI_Uint32 size;
}
MSFT_nxOMSContainersProperty_Array;

typedef struct _MSFT_nxOMSContainersProperty_ConstArray
{
    struct _MSFT_nxOMSContainersProperty MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSContainersProperty_ConstArray;

typedef struct _MSFT_nxOMSContainersProperty_ArrayRef
{
    MSFT_nxOMSContainersProperty_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSContainersProperty_ArrayRef;

typedef struct _MSFT_nxOMSContainersProperty_ConstArrayRef
{
    MSFT_nxOMSContainersProperty_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSContainersProperty_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSContainersProperty_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Construct(
    _Out_ MSFT_nxOMSContainersProperty* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSContainersProperty_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Clone(
    _In_ const MSFT_nxOMSContainersProperty* self,
    _Outptr_ MSFT_nxOMSContainersProperty** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSContainersProperty_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSContainersProperty_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Destruct(_Inout_ MSFT_nxOMSContainersProperty* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Delete(_Inout_ MSFT_nxOMSContainersProperty* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Post(
    _In_ const MSFT_nxOMSContainersProperty* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Set_Name(
    _Inout_ MSFT_nxOMSContainersProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_SetPtr_Name(
    _Inout_ MSFT_nxOMSContainersProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Clear_Name(
    _Inout_ MSFT_nxOMSContainersProperty* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Set_Ensure(
    _Inout_ MSFT_nxOMSContainersProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_SetPtr_Ensure(
    _Inout_ MSFT_nxOMSContainersProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSContainersProperty_Clear_Ensure(
    _Inout_ MSFT_nxOMSContainersProperty* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_nxOMSContainersProperty_h */

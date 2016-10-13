/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSDummyProperty_h
#define _MSFT_nxOMSDummyProperty_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSDummyProperty [MSFT_nxOMSDummyProperty]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSDummyProperty
{
    MI_Instance __instance;
    /* MSFT_nxOMSDummyProperty properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Ensure;
}
MSFT_nxOMSDummyProperty;

typedef struct _MSFT_nxOMSDummyProperty_Ref
{
    MSFT_nxOMSDummyProperty* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSDummyProperty_Ref;

typedef struct _MSFT_nxOMSDummyProperty_ConstRef
{
    MI_CONST MSFT_nxOMSDummyProperty* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSDummyProperty_ConstRef;

typedef struct _MSFT_nxOMSDummyProperty_Array
{
    struct _MSFT_nxOMSDummyProperty** data;
    MI_Uint32 size;
}
MSFT_nxOMSDummyProperty_Array;

typedef struct _MSFT_nxOMSDummyProperty_ConstArray
{
    struct _MSFT_nxOMSDummyProperty MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSDummyProperty_ConstArray;

typedef struct _MSFT_nxOMSDummyProperty_ArrayRef
{
    MSFT_nxOMSDummyProperty_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSDummyProperty_ArrayRef;

typedef struct _MSFT_nxOMSDummyProperty_ConstArrayRef
{
    MSFT_nxOMSDummyProperty_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSDummyProperty_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSDummyProperty_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Construct(
    _Out_ MSFT_nxOMSDummyProperty* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSDummyProperty_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Clone(
    _In_ const MSFT_nxOMSDummyProperty* self,
    _Outptr_ MSFT_nxOMSDummyProperty** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSDummyProperty_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSDummyProperty_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Destruct(_Inout_ MSFT_nxOMSDummyProperty* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Delete(_Inout_ MSFT_nxOMSDummyProperty* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Post(
    _In_ const MSFT_nxOMSDummyProperty* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Set_Name(
    _Inout_ MSFT_nxOMSDummyProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_SetPtr_Name(
    _Inout_ MSFT_nxOMSDummyProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Clear_Name(
    _Inout_ MSFT_nxOMSDummyProperty* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Set_Ensure(
    _Inout_ MSFT_nxOMSDummyProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_SetPtr_Ensure(
    _Inout_ MSFT_nxOMSDummyProperty* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSDummyProperty_Clear_Ensure(
    _Inout_ MSFT_nxOMSDummyProperty* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_nxOMSDummyProperty_h */

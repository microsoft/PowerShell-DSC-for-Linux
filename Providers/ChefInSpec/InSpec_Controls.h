/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _InSpec_Controls_h
#define _InSpec_Controls_h

#include <MI.h>

/*
**==============================================================================
**
** InSpec_Controls [InSpec_Controls]
**
** Keys:
**
**==============================================================================
*/

typedef struct _InSpec_Controls
{
    MI_Instance __instance;
    /* InSpec_Controls properties */
    MI_ConstStringField id;
    MI_ConstStringField profile_id;
    MI_ConstStringField profile_sha256;
    MI_ConstStringField status;
    MI_ConstStringField codec_desc;
    MI_ConstStringField message;
}
InSpec_Controls;

typedef struct _InSpec_Controls_Ref
{
    InSpec_Controls* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Controls_Ref;

typedef struct _InSpec_Controls_ConstRef
{
    MI_CONST InSpec_Controls* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Controls_ConstRef;

typedef struct _InSpec_Controls_Array
{
    struct _InSpec_Controls** data;
    MI_Uint32 size;
}
InSpec_Controls_Array;

typedef struct _InSpec_Controls_ConstArray
{
    struct _InSpec_Controls MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
InSpec_Controls_ConstArray;

typedef struct _InSpec_Controls_ArrayRef
{
    InSpec_Controls_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Controls_ArrayRef;

typedef struct _InSpec_Controls_ConstArrayRef
{
    InSpec_Controls_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Controls_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl InSpec_Controls_rtti;

MI_INLINE MI_Result MI_CALL InSpec_Controls_Construct(
    _Out_ InSpec_Controls* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &InSpec_Controls_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Clone(
    _In_ const InSpec_Controls* self,
    _Outptr_ InSpec_Controls** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL InSpec_Controls_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &InSpec_Controls_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Destruct(_Inout_ InSpec_Controls* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Delete(_Inout_ InSpec_Controls* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Post(
    _In_ const InSpec_Controls* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Set_id(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_SetPtr_id(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Clear_id(
    _Inout_ InSpec_Controls* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Set_profile_id(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_SetPtr_profile_id(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Clear_profile_id(
    _Inout_ InSpec_Controls* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Set_profile_sha256(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_SetPtr_profile_sha256(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Clear_profile_sha256(
    _Inout_ InSpec_Controls* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Set_status(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_SetPtr_status(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Clear_status(
    _Inout_ InSpec_Controls* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Set_codec_desc(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_SetPtr_codec_desc(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Clear_codec_desc(
    _Inout_ InSpec_Controls* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Set_message(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_SetPtr_message(
    _Inout_ InSpec_Controls* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Controls_Clear_message(
    _Inout_ InSpec_Controls* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}


#endif /* _InSpec_Controls_h */

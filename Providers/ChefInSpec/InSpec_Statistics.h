/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _InSpec_Statistics_h
#define _InSpec_Statistics_h

#include <MI.h>

/*
**==============================================================================
**
** InSpec_Statistics [InSpec_Statistics]
**
** Keys:
**
**==============================================================================
*/

typedef struct _InSpec_Statistics
{
    MI_Instance __instance;
    /* InSpec_Statistics properties */
    MI_ConstStringField duration;
}
InSpec_Statistics;

typedef struct _InSpec_Statistics_Ref
{
    InSpec_Statistics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Statistics_Ref;

typedef struct _InSpec_Statistics_ConstRef
{
    MI_CONST InSpec_Statistics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Statistics_ConstRef;

typedef struct _InSpec_Statistics_Array
{
    struct _InSpec_Statistics** data;
    MI_Uint32 size;
}
InSpec_Statistics_Array;

typedef struct _InSpec_Statistics_ConstArray
{
    struct _InSpec_Statistics MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
InSpec_Statistics_ConstArray;

typedef struct _InSpec_Statistics_ArrayRef
{
    InSpec_Statistics_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Statistics_ArrayRef;

typedef struct _InSpec_Statistics_ConstArrayRef
{
    InSpec_Statistics_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Statistics_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl InSpec_Statistics_rtti;

MI_INLINE MI_Result MI_CALL InSpec_Statistics_Construct(
    _Out_ InSpec_Statistics* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &InSpec_Statistics_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Statistics_Clone(
    _In_ const InSpec_Statistics* self,
    _Outptr_ InSpec_Statistics** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL InSpec_Statistics_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &InSpec_Statistics_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL InSpec_Statistics_Destruct(_Inout_ InSpec_Statistics* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Statistics_Delete(_Inout_ InSpec_Statistics* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Statistics_Post(
    _In_ const InSpec_Statistics* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Statistics_Set_duration(
    _Inout_ InSpec_Statistics* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Statistics_SetPtr_duration(
    _Inout_ InSpec_Statistics* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Statistics_Clear_duration(
    _Inout_ InSpec_Statistics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}


#endif /* _InSpec_Statistics_h */

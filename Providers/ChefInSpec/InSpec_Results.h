/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _InSpec_Results_h
#define _InSpec_Results_h

#include <MI.h>
#include "InSpec_Controls.h"
#include "InSpec_Statistics.h"

/*
**==============================================================================
**
** InSpec_Results [InSpec_Results]
**
** Keys:
**
**==============================================================================
*/

typedef struct _InSpec_Results
{
    MI_Instance __instance;
    /* InSpec_Results properties */
    InSpec_Controls_ConstArrayRef controls;
    MI_ConstStringField version;
    InSpec_Statistics_ConstRef statistics;
    MI_ConstStringField status;
}
InSpec_Results;

typedef struct _InSpec_Results_Ref
{
    InSpec_Results* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Results_Ref;

typedef struct _InSpec_Results_ConstRef
{
    MI_CONST InSpec_Results* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Results_ConstRef;

typedef struct _InSpec_Results_Array
{
    struct _InSpec_Results** data;
    MI_Uint32 size;
}
InSpec_Results_Array;

typedef struct _InSpec_Results_ConstArray
{
    struct _InSpec_Results MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
InSpec_Results_ConstArray;

typedef struct _InSpec_Results_ArrayRef
{
    InSpec_Results_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Results_ArrayRef;

typedef struct _InSpec_Results_ConstArrayRef
{
    InSpec_Results_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
InSpec_Results_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl InSpec_Results_rtti;

MI_INLINE MI_Result MI_CALL InSpec_Results_Construct(
    _Out_ InSpec_Results* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &InSpec_Results_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Clone(
    _In_ const InSpec_Results* self,
    _Outptr_ InSpec_Results** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL InSpec_Results_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &InSpec_Results_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Destruct(_Inout_ InSpec_Results* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Delete(_Inout_ InSpec_Results* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Post(
    _In_ const InSpec_Results* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Set_controls(
    _Inout_ InSpec_Results* self,
    _In_reads_opt_(size) const InSpec_Controls * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_SetPtr_controls(
    _Inout_ InSpec_Results* self,
    _In_reads_opt_(size) const InSpec_Controls * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Clear_controls(
    _Inout_ InSpec_Results* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Set_version(
    _Inout_ InSpec_Results* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_SetPtr_version(
    _Inout_ InSpec_Results* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Clear_version(
    _Inout_ InSpec_Results* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Set_statistics(
    _Inout_ InSpec_Results* self,
    _In_ const InSpec_Statistics* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_SetPtr_statistics(
    _Inout_ InSpec_Results* self,
    _In_ const InSpec_Statistics* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Clear_statistics(
    _Inout_ InSpec_Results* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Set_status(
    _Inout_ InSpec_Results* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_SetPtr_status(
    _Inout_ InSpec_Results* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL InSpec_Results_Clear_status(
    _Inout_ InSpec_Results* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}


#endif /* _InSpec_Results_h */

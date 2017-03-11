/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSSudoCustomLogObject_h
#define _MSFT_nxOMSSudoCustomLogObject_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSSudoCustomLogObject [MSFT_nxOMSSudoCustomLogObject]
**
** Keys:
**    LogName
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSSudoCustomLogObject
{
    MI_Instance __instance;
    /* MSFT_nxOMSSudoCustomLogObject properties */
    /*KEY*/ MI_ConstStringField LogName;
    MI_ConstStringAField FilePath;
}
MSFT_nxOMSSudoCustomLogObject;

typedef struct _MSFT_nxOMSSudoCustomLogObject_Ref
{
    MSFT_nxOMSSudoCustomLogObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSudoCustomLogObject_Ref;

typedef struct _MSFT_nxOMSSudoCustomLogObject_ConstRef
{
    MI_CONST MSFT_nxOMSSudoCustomLogObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSudoCustomLogObject_ConstRef;

typedef struct _MSFT_nxOMSSudoCustomLogObject_Array
{
    struct _MSFT_nxOMSSudoCustomLogObject** data;
    MI_Uint32 size;
}
MSFT_nxOMSSudoCustomLogObject_Array;

typedef struct _MSFT_nxOMSSudoCustomLogObject_ConstArray
{
    struct _MSFT_nxOMSSudoCustomLogObject MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSSudoCustomLogObject_ConstArray;

typedef struct _MSFT_nxOMSSudoCustomLogObject_ArrayRef
{
    MSFT_nxOMSSudoCustomLogObject_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSudoCustomLogObject_ArrayRef;

typedef struct _MSFT_nxOMSSudoCustomLogObject_ConstArrayRef
{
    MSFT_nxOMSSudoCustomLogObject_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSudoCustomLogObject_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSSudoCustomLogObject_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Construct(
    _Out_ MSFT_nxOMSSudoCustomLogObject* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSSudoCustomLogObject_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Clone(
    _In_ const MSFT_nxOMSSudoCustomLogObject* self,
    _Outptr_ MSFT_nxOMSSudoCustomLogObject** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSSudoCustomLogObject_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSSudoCustomLogObject_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Destruct(_Inout_ MSFT_nxOMSSudoCustomLogObject* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Delete(_Inout_ MSFT_nxOMSSudoCustomLogObject* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Post(
    _In_ const MSFT_nxOMSSudoCustomLogObject* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Set_LogName(
    _Inout_ MSFT_nxOMSSudoCustomLogObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_SetPtr_LogName(
    _Inout_ MSFT_nxOMSSudoCustomLogObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Clear_LogName(
    _Inout_ MSFT_nxOMSSudoCustomLogObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Set_FilePath(
    _Inout_ MSFT_nxOMSSudoCustomLogObject* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_SetPtr_FilePath(
    _Inout_ MSFT_nxOMSSudoCustomLogObject* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSudoCustomLogObject_Clear_FilePath(
    _Inout_ MSFT_nxOMSSudoCustomLogObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_nxOMSSudoCustomLogObject_h */

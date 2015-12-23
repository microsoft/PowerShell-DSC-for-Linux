/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSCustomLogObject_h
#define _MSFT_nxOMSCustomLogObject_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSCustomLogObject [MSFT_nxOMSCustomLogObject]
**
** Keys:
**    LogName
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSCustomLogObject
{
    MI_Instance __instance;
    /* MSFT_nxOMSCustomLogObject properties */
    /*KEY*/ MI_ConstStringField LogName;
    MI_ConstStringAField FilePath;
}
MSFT_nxOMSCustomLogObject;

typedef struct _MSFT_nxOMSCustomLogObject_Ref
{
    MSFT_nxOMSCustomLogObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSCustomLogObject_Ref;

typedef struct _MSFT_nxOMSCustomLogObject_ConstRef
{
    MI_CONST MSFT_nxOMSCustomLogObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSCustomLogObject_ConstRef;

typedef struct _MSFT_nxOMSCustomLogObject_Array
{
    struct _MSFT_nxOMSCustomLogObject** data;
    MI_Uint32 size;
}
MSFT_nxOMSCustomLogObject_Array;

typedef struct _MSFT_nxOMSCustomLogObject_ConstArray
{
    struct _MSFT_nxOMSCustomLogObject MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSCustomLogObject_ConstArray;

typedef struct _MSFT_nxOMSCustomLogObject_ArrayRef
{
    MSFT_nxOMSCustomLogObject_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSCustomLogObject_ArrayRef;

typedef struct _MSFT_nxOMSCustomLogObject_ConstArrayRef
{
    MSFT_nxOMSCustomLogObject_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSCustomLogObject_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSCustomLogObject_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Construct(
    _Out_ MSFT_nxOMSCustomLogObject* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSCustomLogObject_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Clone(
    _In_ const MSFT_nxOMSCustomLogObject* self,
    _Outptr_ MSFT_nxOMSCustomLogObject** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSCustomLogObject_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSCustomLogObject_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Destruct(_Inout_ MSFT_nxOMSCustomLogObject* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Delete(_Inout_ MSFT_nxOMSCustomLogObject* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Post(
    _In_ const MSFT_nxOMSCustomLogObject* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Set_LogName(
    _Inout_ MSFT_nxOMSCustomLogObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_SetPtr_LogName(
    _Inout_ MSFT_nxOMSCustomLogObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Clear_LogName(
    _Inout_ MSFT_nxOMSCustomLogObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Set_FilePath(
    _Inout_ MSFT_nxOMSCustomLogObject* self,
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

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_SetPtr_FilePath(
    _Inout_ MSFT_nxOMSCustomLogObject* self,
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

MI_INLINE MI_Result MI_CALL MSFT_nxOMSCustomLogObject_Clear_FilePath(
    _Inout_ MSFT_nxOMSCustomLogObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_nxOMSCustomLogObject_h */

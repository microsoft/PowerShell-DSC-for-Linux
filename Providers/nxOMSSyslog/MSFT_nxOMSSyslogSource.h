/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSSyslogSource_h
#define _MSFT_nxOMSSyslogSource_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSSyslogSource [MSFT_nxOMSSyslogSource]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSSyslogSource
{
    MI_Instance __instance;
    /* MSFT_nxOMSSyslogSource properties */
    MI_ConstStringField Facility;
    MI_ConstStringAField Severities;
}
MSFT_nxOMSSyslogSource;

typedef struct _MSFT_nxOMSSyslogSource_Ref
{
    MSFT_nxOMSSyslogSource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogSource_Ref;

typedef struct _MSFT_nxOMSSyslogSource_ConstRef
{
    MI_CONST MSFT_nxOMSSyslogSource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogSource_ConstRef;

typedef struct _MSFT_nxOMSSyslogSource_Array
{
    struct _MSFT_nxOMSSyslogSource** data;
    MI_Uint32 size;
}
MSFT_nxOMSSyslogSource_Array;

typedef struct _MSFT_nxOMSSyslogSource_ConstArray
{
    struct _MSFT_nxOMSSyslogSource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSSyslogSource_ConstArray;

typedef struct _MSFT_nxOMSSyslogSource_ArrayRef
{
    MSFT_nxOMSSyslogSource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogSource_ArrayRef;

typedef struct _MSFT_nxOMSSyslogSource_ConstArrayRef
{
    MSFT_nxOMSSyslogSource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSSyslogSource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSSyslogSource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Construct(
    _Out_ MSFT_nxOMSSyslogSource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSSyslogSource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Clone(
    _In_ const MSFT_nxOMSSyslogSource* self,
    _Outptr_ MSFT_nxOMSSyslogSource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSSyslogSource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSSyslogSource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Destruct(_Inout_ MSFT_nxOMSSyslogSource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Delete(_Inout_ MSFT_nxOMSSyslogSource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Post(
    _In_ const MSFT_nxOMSSyslogSource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Set_Facility(
    _Inout_ MSFT_nxOMSSyslogSource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_SetPtr_Facility(
    _Inout_ MSFT_nxOMSSyslogSource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Clear_Facility(
    _Inout_ MSFT_nxOMSSyslogSource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Set_Severities(
    _Inout_ MSFT_nxOMSSyslogSource* self,
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

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_SetPtr_Severities(
    _Inout_ MSFT_nxOMSSyslogSource* self,
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

MI_INLINE MI_Result MI_CALL MSFT_nxOMSSyslogSource_Clear_Severities(
    _Inout_ MSFT_nxOMSSyslogSource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_nxOMSSyslogSource_h */

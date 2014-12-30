/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_ModuleSpecification_h
#define _MSFT_ModuleSpecification_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_ModuleSpecification [MSFT_ModuleSpecification]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_ModuleSpecification
{
    MI_Instance __instance;
    /* MSFT_ModuleSpecification properties */
    MI_ConstStringField ModuleName;
    MI_ConstStringField ModuleVersion;
}
MSFT_ModuleSpecification;

typedef struct _MSFT_ModuleSpecification_Ref
{
    MSFT_ModuleSpecification* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ModuleSpecification_Ref;

typedef struct _MSFT_ModuleSpecification_ConstRef
{
    MI_CONST MSFT_ModuleSpecification* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ModuleSpecification_ConstRef;

typedef struct _MSFT_ModuleSpecification_Array
{
    struct _MSFT_ModuleSpecification** data;
    MI_Uint32 size;
}
MSFT_ModuleSpecification_Array;

typedef struct _MSFT_ModuleSpecification_ConstArray
{
    struct _MSFT_ModuleSpecification MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_ModuleSpecification_ConstArray;

typedef struct _MSFT_ModuleSpecification_ArrayRef
{
    MSFT_ModuleSpecification_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ModuleSpecification_ArrayRef;

typedef struct _MSFT_ModuleSpecification_ConstArrayRef
{
    MSFT_ModuleSpecification_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ModuleSpecification_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_ModuleSpecification_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Construct(
    _Out_ MSFT_ModuleSpecification* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_ModuleSpecification_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Clone(
    _In_ const MSFT_ModuleSpecification* self,
    _Outptr_ MSFT_ModuleSpecification** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_ModuleSpecification_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_ModuleSpecification_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Destruct(_Inout_ MSFT_ModuleSpecification* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Delete(_Inout_ MSFT_ModuleSpecification* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Post(
    _In_ const MSFT_ModuleSpecification* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Set_ModuleName(
    _Inout_ MSFT_ModuleSpecification* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_SetPtr_ModuleName(
    _Inout_ MSFT_ModuleSpecification* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Clear_ModuleName(
    _Inout_ MSFT_ModuleSpecification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Set_ModuleVersion(
    _Inout_ MSFT_ModuleSpecification* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_SetPtr_ModuleVersion(
    _Inout_ MSFT_ModuleSpecification* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ModuleSpecification_Clear_ModuleVersion(
    _Inout_ MSFT_ModuleSpecification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_ModuleSpecification_h */

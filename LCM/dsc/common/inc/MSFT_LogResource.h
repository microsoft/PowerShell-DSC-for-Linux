/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_LogResource_h
#define _MSFT_LogResource_h

#include <MI.h>
#include "OMI_BaseResource.h"

/*
**==============================================================================
**
** MSFT_LogResource [MSFT_LogResource]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_LogResource /* extends OMI_BaseResource */
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    /* MSFT_LogResource properties */
    MI_ConstStringField Message;
}
MSFT_LogResource;

typedef struct _MSFT_LogResource_Ref
{
    MSFT_LogResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogResource_Ref;

typedef struct _MSFT_LogResource_ConstRef
{
    MI_CONST MSFT_LogResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogResource_ConstRef;

typedef struct _MSFT_LogResource_Array
{
    struct _MSFT_LogResource** data;
    MI_Uint32 size;
}
MSFT_LogResource_Array;

typedef struct _MSFT_LogResource_ConstArray
{
    struct _MSFT_LogResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_LogResource_ConstArray;

typedef struct _MSFT_LogResource_ArrayRef
{
    MSFT_LogResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogResource_ArrayRef;

typedef struct _MSFT_LogResource_ConstArrayRef
{
    MSFT_LogResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_LogResource_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LogResource_Construct(
    _Out_ MSFT_LogResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_LogResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogResource_Clone(
    _In_ const MSFT_LogResource* self,
    _Outptr_ MSFT_LogResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_LogResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_LogResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_LogResource_Destruct(_Inout_ MSFT_LogResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogResource_Delete(_Inout_ MSFT_LogResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogResource_Post(
    _In_ const MSFT_LogResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogResource_Set_Message(
    _Inout_ MSFT_LogResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LogResource_SetPtr_Message(
    _Inout_ MSFT_LogResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LogResource_Clear_Message(
    _Inout_ MSFT_LogResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}


#endif /* _MSFT_LogResource_h */

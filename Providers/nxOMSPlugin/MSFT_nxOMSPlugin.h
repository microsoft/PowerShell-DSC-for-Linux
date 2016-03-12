/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSPlugin_h
#define _MSFT_nxOMSPlugin_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSPlugin [MSFT_nxOMSPlugin]
**
** Keys:
**    PluginName
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSPlugin
{
    MI_Instance __instance;
    /* MSFT_nxOMSPlugin properties */
    /*KEY*/ MI_ConstStringField PluginName;
    MI_ConstStringField Ensure;
}
MSFT_nxOMSPlugin;

typedef struct _MSFT_nxOMSPlugin_Ref
{
    MSFT_nxOMSPlugin* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPlugin_Ref;

typedef struct _MSFT_nxOMSPlugin_ConstRef
{
    MI_CONST MSFT_nxOMSPlugin* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPlugin_ConstRef;

typedef struct _MSFT_nxOMSPlugin_Array
{
    struct _MSFT_nxOMSPlugin** data;
    MI_Uint32 size;
}
MSFT_nxOMSPlugin_Array;

typedef struct _MSFT_nxOMSPlugin_ConstArray
{
    struct _MSFT_nxOMSPlugin MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSPlugin_ConstArray;

typedef struct _MSFT_nxOMSPlugin_ArrayRef
{
    MSFT_nxOMSPlugin_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPlugin_ArrayRef;

typedef struct _MSFT_nxOMSPlugin_ConstArrayRef
{
    MSFT_nxOMSPlugin_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPlugin_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSPlugin_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Construct(
    _Out_ MSFT_nxOMSPlugin* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSPlugin_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Clone(
    _In_ const MSFT_nxOMSPlugin* self,
    _Outptr_ MSFT_nxOMSPlugin** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSPlugin_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSPlugin_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Destruct(_Inout_ MSFT_nxOMSPlugin* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Delete(_Inout_ MSFT_nxOMSPlugin* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Post(
    _In_ const MSFT_nxOMSPlugin* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Set_PluginName(
    _Inout_ MSFT_nxOMSPlugin* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_SetPtr_PluginName(
    _Inout_ MSFT_nxOMSPlugin* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Clear_PluginName(
    _Inout_ MSFT_nxOMSPlugin* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Set_Ensure(
    _Inout_ MSFT_nxOMSPlugin* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_SetPtr_Ensure(
    _Inout_ MSFT_nxOMSPlugin* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPlugin_Clear_Ensure(
    _Inout_ MSFT_nxOMSPlugin* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _MSFT_nxOMSPlugin_h */

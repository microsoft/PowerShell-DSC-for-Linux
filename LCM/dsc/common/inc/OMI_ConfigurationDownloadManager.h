/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_ConfigurationDownloadManager_h
#define _OMI_ConfigurationDownloadManager_h

#include <MI.h>

/*
**==============================================================================
**
** OMI_ConfigurationDownloadManager [OMI_ConfigurationDownloadManager]
**
** Keys:
**
**==============================================================================
*/

typedef struct _OMI_ConfigurationDownloadManager
{
    MI_Instance __instance;
    /* OMI_ConfigurationDownloadManager properties */
    MI_ConstStringField Name;
}
OMI_ConfigurationDownloadManager;

typedef struct _OMI_ConfigurationDownloadManager_Ref
{
    OMI_ConfigurationDownloadManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ConfigurationDownloadManager_Ref;

typedef struct _OMI_ConfigurationDownloadManager_ConstRef
{
    MI_CONST OMI_ConfigurationDownloadManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ConfigurationDownloadManager_ConstRef;

typedef struct _OMI_ConfigurationDownloadManager_Array
{
    struct _OMI_ConfigurationDownloadManager** data;
    MI_Uint32 size;
}
OMI_ConfigurationDownloadManager_Array;

typedef struct _OMI_ConfigurationDownloadManager_ConstArray
{
    struct _OMI_ConfigurationDownloadManager MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_ConfigurationDownloadManager_ConstArray;

typedef struct _OMI_ConfigurationDownloadManager_ArrayRef
{
    OMI_ConfigurationDownloadManager_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ConfigurationDownloadManager_ArrayRef;

typedef struct _OMI_ConfigurationDownloadManager_ConstArrayRef
{
    OMI_ConfigurationDownloadManager_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ConfigurationDownloadManager_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_ConfigurationDownloadManager_rtti;

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_Construct(
    _Out_ OMI_ConfigurationDownloadManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &OMI_ConfigurationDownloadManager_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_Clone(
    _In_ const OMI_ConfigurationDownloadManager* self,
    _Outptr_ OMI_ConfigurationDownloadManager** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_ConfigurationDownloadManager_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_ConfigurationDownloadManager_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_Destruct(_Inout_ OMI_ConfigurationDownloadManager* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_Delete(_Inout_ OMI_ConfigurationDownloadManager* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_Post(
    _In_ const OMI_ConfigurationDownloadManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_Set_Name(
    _Inout_ OMI_ConfigurationDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_SetPtr_Name(
    _Inout_ OMI_ConfigurationDownloadManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ConfigurationDownloadManager_Clear_Name(
    _Inout_ OMI_ConfigurationDownloadManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}


#endif /* _OMI_ConfigurationDownloadManager_h */

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_ReportManager_h
#define _OMI_ReportManager_h

#include <MI.h>
#include "OMI_MetaConfigurationResource.h"

/*
**==============================================================================
**
** OMI_ReportManager [OMI_ReportManager]
**
** Keys:
**
**==============================================================================
*/

typedef struct _OMI_ReportManager /* extends OMI_MetaConfigurationResource */
{
    MI_Instance __instance;
    /* OMI_MetaConfigurationResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    /* OMI_ReportManager properties */
}
OMI_ReportManager;

typedef struct _OMI_ReportManager_Ref
{
    OMI_ReportManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ReportManager_Ref;

typedef struct _OMI_ReportManager_ConstRef
{
    MI_CONST OMI_ReportManager* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ReportManager_ConstRef;

typedef struct _OMI_ReportManager_Array
{
    struct _OMI_ReportManager** data;
    MI_Uint32 size;
}
OMI_ReportManager_Array;

typedef struct _OMI_ReportManager_ConstArray
{
    struct _OMI_ReportManager MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_ReportManager_ConstArray;

typedef struct _OMI_ReportManager_ArrayRef
{
    OMI_ReportManager_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ReportManager_ArrayRef;

typedef struct _OMI_ReportManager_ConstArrayRef
{
    OMI_ReportManager_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ReportManager_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_ReportManager_rtti;

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Construct(
    _Out_ OMI_ReportManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &OMI_ReportManager_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Clone(
    _In_ const OMI_ReportManager* self,
    _Outptr_ OMI_ReportManager** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_ReportManager_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_ReportManager_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Destruct(_Inout_ OMI_ReportManager* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Delete(_Inout_ OMI_ReportManager* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Post(
    _In_ const OMI_ReportManager* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Set_ResourceId(
    _Inout_ OMI_ReportManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_SetPtr_ResourceId(
    _Inout_ OMI_ReportManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Clear_ResourceId(
    _Inout_ OMI_ReportManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Set_SourceInfo(
    _Inout_ OMI_ReportManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_SetPtr_SourceInfo(
    _Inout_ OMI_ReportManager* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ReportManager_Clear_SourceInfo(
    _Inout_ OMI_ReportManager* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _OMI_ReportManager_h */

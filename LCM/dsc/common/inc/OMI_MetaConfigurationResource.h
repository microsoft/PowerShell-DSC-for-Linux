/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_MetaConfigurationResource_h
#define _OMI_MetaConfigurationResource_h

#include <MI.h>

/*
**==============================================================================
**
** OMI_MetaConfigurationResource [OMI_MetaConfigurationResource]
**
** Keys:
**
**==============================================================================
*/

typedef struct _OMI_MetaConfigurationResource
{
    MI_Instance __instance;
    /* OMI_MetaConfigurationResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    MI_ConstStringField ModuleName;
    MI_ConstStringField ModuleVersion;
}
OMI_MetaConfigurationResource;

typedef struct _OMI_MetaConfigurationResource_Ref
{
    OMI_MetaConfigurationResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_MetaConfigurationResource_Ref;

typedef struct _OMI_MetaConfigurationResource_ConstRef
{
    MI_CONST OMI_MetaConfigurationResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_MetaConfigurationResource_ConstRef;

typedef struct _OMI_MetaConfigurationResource_Array
{
    struct _OMI_MetaConfigurationResource** data;
    MI_Uint32 size;
}
OMI_MetaConfigurationResource_Array;

typedef struct _OMI_MetaConfigurationResource_ConstArray
{
    struct _OMI_MetaConfigurationResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_MetaConfigurationResource_ConstArray;

typedef struct _OMI_MetaConfigurationResource_ArrayRef
{
    OMI_MetaConfigurationResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_MetaConfigurationResource_ArrayRef;

typedef struct _OMI_MetaConfigurationResource_ConstArrayRef
{
    OMI_MetaConfigurationResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_MetaConfigurationResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_MetaConfigurationResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Construct(
    _Out_ OMI_MetaConfigurationResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &OMI_MetaConfigurationResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Clone(
    _In_ const OMI_MetaConfigurationResource* self,
    _Outptr_ OMI_MetaConfigurationResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_MetaConfigurationResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_MetaConfigurationResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Destruct(_Inout_ OMI_MetaConfigurationResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Delete(_Inout_ OMI_MetaConfigurationResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Post(
    _In_ const OMI_MetaConfigurationResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Set_ResourceId(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_SetPtr_ResourceId(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Clear_ResourceId(
    _Inout_ OMI_MetaConfigurationResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Set_SourceInfo(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_SetPtr_SourceInfo(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Clear_SourceInfo(
    _Inout_ OMI_MetaConfigurationResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Set_ModuleName(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_SetPtr_ModuleName(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Clear_ModuleName(
    _Inout_ OMI_MetaConfigurationResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Set_ModuleVersion(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_SetPtr_ModuleVersion(
    _Inout_ OMI_MetaConfigurationResource* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_MetaConfigurationResource_Clear_ModuleVersion(
    _Inout_ OMI_MetaConfigurationResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}


#endif /* _OMI_MetaConfigurationResource_h */

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_BaseResource_h
#define _OMI_BaseResource_h

#include <MI.h>

/*
**==============================================================================
**
** OMI_BaseResource [OMI_BaseResource]
**
** Keys:
**
**==============================================================================
*/

typedef struct _OMI_BaseResource
{
    MI_Instance __instance;
    /* OMI_BaseResource properties */
    MI_ConstStringField ResourceId;
    MI_ConstStringField SourceInfo;
    MI_ConstStringAField Requires;
    MI_ConstStringField ModuleName;
    MI_ConstStringField ModuleVersion;
    MI_ConstStringField ConfigurationName;
}
OMI_BaseResource;

typedef struct _OMI_BaseResource_Ref
{
    OMI_BaseResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_BaseResource_Ref;

typedef struct _OMI_BaseResource_ConstRef
{
    MI_CONST OMI_BaseResource* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_BaseResource_ConstRef;

typedef struct _OMI_BaseResource_Array
{
    struct _OMI_BaseResource** data;
    MI_Uint32 size;
}
OMI_BaseResource_Array;

typedef struct _OMI_BaseResource_ConstArray
{
    struct _OMI_BaseResource MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_BaseResource_ConstArray;

typedef struct _OMI_BaseResource_ArrayRef
{
    OMI_BaseResource_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_BaseResource_ArrayRef;

typedef struct _OMI_BaseResource_ConstArrayRef
{
    OMI_BaseResource_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_BaseResource_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_BaseResource_rtti;

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Construct(
    OMI_BaseResource* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &OMI_BaseResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clone(
    const OMI_BaseResource* self,
    OMI_BaseResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_BaseResource_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_BaseResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Destruct(OMI_BaseResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Delete(OMI_BaseResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Post(
    const OMI_BaseResource* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Set_ResourceId(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_SetPtr_ResourceId(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clear_ResourceId(
    OMI_BaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Set_SourceInfo(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_SetPtr_SourceInfo(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clear_SourceInfo(
    OMI_BaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Set_Requires(
    OMI_BaseResource* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_SetPtr_Requires(
    OMI_BaseResource* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clear_Requires(
    OMI_BaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Set_ModuleName(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_SetPtr_ModuleName(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clear_ModuleName(
    OMI_BaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Set_ModuleVersion(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_SetPtr_ModuleVersion(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clear_ModuleVersion(
    OMI_BaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Set_ConfigurationName(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_SetPtr_ConfigurationName(
    OMI_BaseResource* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clear_ConfigurationName(
    OMI_BaseResource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}


#endif /* _OMI_BaseResource_h */

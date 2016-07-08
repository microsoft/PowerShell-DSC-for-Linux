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
    _Out_ OMI_BaseResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &OMI_BaseResource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Clone(
    _In_ const OMI_BaseResource* self,
    _Outptr_ OMI_BaseResource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_BaseResource_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_BaseResource_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Destruct(_Inout_ OMI_BaseResource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Delete(_Inout_ OMI_BaseResource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_BaseResource_Post(
    _In_ const OMI_BaseResource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}


#endif /* _OMI_BaseResource_h */

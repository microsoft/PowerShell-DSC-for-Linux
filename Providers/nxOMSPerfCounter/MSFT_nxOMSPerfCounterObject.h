/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_nxOMSPerfCounterObject_h
#define _MSFT_nxOMSPerfCounterObject_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_nxOMSPerfCounterObject [MSFT_nxOMSPerfCounterObject]
**
** Keys:
**    ObjectName
**
**==============================================================================
*/

typedef struct _MSFT_nxOMSPerfCounterObject
{
    MI_Instance __instance;
    /* MSFT_nxOMSPerfCounterObject properties */
    /*KEY*/ MI_ConstStringField ObjectName;
    MI_ConstStringField InstanceName;
    MI_ConstBooleanField AllInstances;
    MI_ConstUint16Field IntervalSeconds;
    MI_ConstStringAField PerformanceCounter;
}
MSFT_nxOMSPerfCounterObject;

typedef struct _MSFT_nxOMSPerfCounterObject_Ref
{
    MSFT_nxOMSPerfCounterObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterObject_Ref;

typedef struct _MSFT_nxOMSPerfCounterObject_ConstRef
{
    MI_CONST MSFT_nxOMSPerfCounterObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterObject_ConstRef;

typedef struct _MSFT_nxOMSPerfCounterObject_Array
{
    struct _MSFT_nxOMSPerfCounterObject** data;
    MI_Uint32 size;
}
MSFT_nxOMSPerfCounterObject_Array;

typedef struct _MSFT_nxOMSPerfCounterObject_ConstArray
{
    struct _MSFT_nxOMSPerfCounterObject MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_nxOMSPerfCounterObject_ConstArray;

typedef struct _MSFT_nxOMSPerfCounterObject_ArrayRef
{
    MSFT_nxOMSPerfCounterObject_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterObject_ArrayRef;

typedef struct _MSFT_nxOMSPerfCounterObject_ConstArrayRef
{
    MSFT_nxOMSPerfCounterObject_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_nxOMSPerfCounterObject_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_nxOMSPerfCounterObject_rtti;

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Construct(
    _Out_ MSFT_nxOMSPerfCounterObject* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_nxOMSPerfCounterObject_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Clone(
    _In_ const MSFT_nxOMSPerfCounterObject* self,
    _Outptr_ MSFT_nxOMSPerfCounterObject** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_nxOMSPerfCounterObject_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_nxOMSPerfCounterObject_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Destruct(_Inout_ MSFT_nxOMSPerfCounterObject* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Delete(_Inout_ MSFT_nxOMSPerfCounterObject* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Post(
    _In_ const MSFT_nxOMSPerfCounterObject* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Set_ObjectName(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_SetPtr_ObjectName(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Clear_ObjectName(
    _Inout_ MSFT_nxOMSPerfCounterObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Set_InstanceName(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_SetPtr_InstanceName(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Clear_InstanceName(
    _Inout_ MSFT_nxOMSPerfCounterObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Set_AllInstances(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->AllInstances)->value = x;
    ((MI_BooleanField*)&self->AllInstances)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Clear_AllInstances(
    _Inout_ MSFT_nxOMSPerfCounterObject* self)
{
    memset((void*)&self->AllInstances, 0, sizeof(self->AllInstances));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Set_IntervalSeconds(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IntervalSeconds)->value = x;
    ((MI_Uint16Field*)&self->IntervalSeconds)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Clear_IntervalSeconds(
    _Inout_ MSFT_nxOMSPerfCounterObject* self)
{
    memset((void*)&self->IntervalSeconds, 0, sizeof(self->IntervalSeconds));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Set_PerformanceCounter(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_SetPtr_PerformanceCounter(
    _Inout_ MSFT_nxOMSPerfCounterObject* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_nxOMSPerfCounterObject_Clear_PerformanceCounter(
    _Inout_ MSFT_nxOMSPerfCounterObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}


#endif /* _MSFT_nxOMSPerfCounterObject_h */

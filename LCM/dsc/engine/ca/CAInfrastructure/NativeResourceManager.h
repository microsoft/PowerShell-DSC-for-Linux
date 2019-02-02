/**************************************************************************************************/
/*                                                                                                */
/* The NativeResourceManager is used to host and invoke (Test/Set/Get) native, non-WMI,           */
/* resources.                                                                                     */
/*                                                                                                */
/* Currently only Get is implemented.                                                             */
/*                                                                                                */
/**************************************************************************************************/

#ifndef _NATIVE_RESOURCE_MANAGER_H
#define _NATIVE_RESOURCE_MANAGER_H

#include "NativeResourceHostMiContext.h"
#include "pal/hashmap.h"

typedef struct _NativeResourceManager {
    struct {
        ProviderCallbackContext* resourceProviderContext;
        HashMap resourceProviderHashMap;
        MI_Boolean hashInited;
    } _private;
} NativeResourceManager;


MI_Result NativeResourceManager_New(_In_opt_ ProviderCallbackContext* resourceProviderContext, _Outptr_ NativeResourceManager** manager);

MI_Result NativeResourceManager_Delete(_In_ NativeResourceManager* manager);

MI_Result NativeResourceManager_GetNativeResouceProvider(_In_ NativeResourceManager* nativeResourceManager, 
                                                                    const _In_z_ MI_Char* providerPath, 
                                                                    const _In_z_ MI_Char* resourceProviderClassName, 
                                                                    _Outptr_ NativeResourceProvider** nativeResourceProvider);

#endif // _NATIVE_RESOURCE_MANAGER_H

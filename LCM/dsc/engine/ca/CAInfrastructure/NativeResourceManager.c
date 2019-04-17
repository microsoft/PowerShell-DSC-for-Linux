#include "DSC_Systemcalls.h"
#include "CAEngine.h"
#include "pal/strings.h"
#include "ModuleHandlerInternal.h"
#include "NativeResourceManager.h"
#include "EventWrapper.h"

typedef struct _NativeResourceManagerHashMapBucket
{
    struct _NativeResourceManagerHashMapBucket* next;
    MI_Char key[MAX_PATH]; // resource provider path
    NativeResourceProvider* resourceProvider;
} NativeResourceManagerHashMapBucket;

// This hash logic is taken from pal/hashmap.h->HashMap_HashProc_PalStringCaseInsensitive()
// only the difference is that this method is case sensitive. 
NITS_EXTERN_C size_t NativeResourceManager_Hash(const HashBucket* bucket_)
{
    const PAL_Char *source = ((NativeResourceManagerHashMapBucket*)bucket_)->key;

    /* fnv1-a hash, lowercase */
    size_t h = 2166136261u;

    for( ; *source; source++)
    {
        PAL_Char c = *source;
        h ^= c;
        h *= 16777619;
    }
    return h;
}

NITS_EXTERN_C int NativeResourceManager_HashMapEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    NativeResourceManagerHashMapBucket* bucket1 = (NativeResourceManagerHashMapBucket*)bucket1_;
    NativeResourceManagerHashMapBucket* bucket2 = (NativeResourceManagerHashMapBucket*)bucket2_;
    return Tcscasecmp(bucket1->key, bucket2->key) == 0;
}

NITS_EXTERN_C void NativeResourceManager_HashMapRelease(
    HashBucket* bucket_)
{
    NativeResourceManagerHashMapBucket* bucket = (NativeResourceManagerHashMapBucket*)bucket_;
    if (bucket->resourceProvider != NULL)
            NativeResourceProvider_Delete(bucket->resourceProvider);
    DSC_free(bucket);
}

MI_Result NativeResourceManager_New(_In_opt_ ProviderCallbackContext* resourceProviderContext, _Outptr_ NativeResourceManager** nativeResourceManager)
{
    MI_Result returnValue = MI_RESULT_OK;
    MI_Sint32 hashResult = MI_RESULT_OK;
    const size_t NUM_LISTS = 32; // number of buckets in hash map

    *nativeResourceManager = NULL;

    NativeResourceManager* nativeResourceManagerLocal = DSC_malloc(sizeof(NativeResourceManager), NitsHere());
    EH_Check_(nativeResourceManagerLocal != NULL, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);
    memset(nativeResourceManagerLocal, 0, sizeof(NativeResourceManager));

    nativeResourceManagerLocal->_private.resourceProviderContext = resourceProviderContext;
    hashResult = HashMap_Init(&nativeResourceManagerLocal->_private.resourceProviderHashMap,
                                NUM_LISTS,
                                NativeResourceManager_Hash, 
                                NativeResourceManager_HashMapEqual, 
                                NativeResourceManager_HashMapRelease);
    EH_Check_(hashResult == MI_RESULT_OK, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);
    nativeResourceManagerLocal->_private.hashInited = MI_TRUE;

    *nativeResourceManager = nativeResourceManagerLocal;

EH_UNWIND;
    if (returnValue != MI_RESULT_OK)
    {
        NativeResourceManager_Delete(nativeResourceManagerLocal);
    }

    return returnValue;
}

MI_Result NativeResourceManager_Delete(_In_ NativeResourceManager* manager)
{
    if (manager != NULL) {
        if (manager->_private.hashInited)
        {
            HashMap_Destroy(&manager->_private.resourceProviderHashMap);
        }

        DSC_free(manager);
    }

    return MI_RESULT_OK;
}

MI_Result NativeResourceManager_GetNativeResouceProvider(_In_ NativeResourceManager* nativeResourceManager, 
                                                                    const _In_z_ MI_Char* providerPath, 
                                                                    const _In_z_ MI_Char* resourceProviderClassName, 
                                                                    _Outptr_ NativeResourceProvider** nativeResourceProvider)
{
    MI_Result returnValue = MI_RESULT_OK;
    NativeResourceManagerHashMapBucket searchBucket;

    // Check if resource provider is already loaded.
    size_t keySize = sizeof(searchBucket.key)/sizeof(searchBucket.key[0]);
    Tcslcpy(searchBucket.key, providerPath, keySize);
    NativeResourceManagerHashMapBucket* bucket = 
                    (NativeResourceManagerHashMapBucket*)HashMap_Find(&nativeResourceManager->_private.resourceProviderHashMap, (const HashBucket*)&searchBucket);
    if (bucket == NULL) // resource provider is not loaded yet
    {
        NativeResourceProvider* nativeResourceProviderLocal = NULL;
        returnValue = NativeResourceProvider_New(providerPath, resourceProviderClassName, nativeResourceManager->_private.resourceProviderContext, &nativeResourceProviderLocal);
        EH_CheckResult_(returnValue, { DSC_LOG_ERROR("NativeResourceProvider_New failed (code = %d) for '%s'\n", returnValue, providerPath); });

        bucket = (NativeResourceManagerHashMapBucket*)DSC_malloc(sizeof(NativeResourceManagerHashMapBucket), NitsHere());
        EH_Check_(bucket != NULL, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);

        Tcslcpy(bucket->key, providerPath, keySize);
        bucket->resourceProvider = nativeResourceProviderLocal;
        HashMap_Insert(&nativeResourceManager->_private.resourceProviderHashMap, (HashBucket*)bucket);
    }

    *nativeResourceProvider = bucket->resourceProvider;

    EH_UNWIND;

    return returnValue;
}


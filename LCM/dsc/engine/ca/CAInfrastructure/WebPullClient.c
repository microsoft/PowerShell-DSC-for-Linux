#include <MI.h>
#include "DSC_Systemcalls.h"
//#include "LocalConfigManagerHelperForCA.h"
#include "EngineHelper.h"
#include "Resources_LCM.h"
#include <pal/format.h>
#include <pal/file.h>
#include <pal/dir.h>
#include <base/base64.h>
#include "CAEngine.h"
#include "CAEngineInternal.h"
#include "EventWrapper.h"
#include <ctype.h>

#if defined(_MSC_VER)

#include <WinCrypt.h>
#include <winhttp.h>
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201)
#include <sha2.h>
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif    

#else
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <curl/curl.h>
#include <base/conf.h>
#endif

#include "WebPullClient.h"

typedef struct ModuleClassList ModuleClassList;
struct ModuleClassList {
    ModuleClassList* next;
    MI_Char* moduleClass;
};

typedef struct ModuleVersionClassTuple ModuleVersionClassTuple;
struct ModuleVersionClassTuple {
    MI_Char* moduleVersion;
    ModuleClassList* first;
};

typedef struct ModuleTableEntry ModuleTableEntry;
struct ModuleTableEntry {
    ModuleTableEntry* next;
    MI_Char* moduleName;
    ModuleVersionClassTuple* moduleVersionClassTuple;
};

typedef struct ModuleTable ModuleTable;
struct ModuleTable {
    ModuleTableEntry* first;
};

static MI_Result GetModuleNameVersionTable(MI_Char* mofFileLocation, 
                                           ModuleTable* table,
                                           _Outptr_result_maybenull_ MI_Instance **extendedError);

struct Chunk 
{
    size_t size;
    char * data;
};

struct HeaderChunk 
{
    size_t size;
    char ** headerKeys;
    char ** headerValues;
};

static void InitHeaderChunk(struct HeaderChunk* chunk)
{
    chunk->size = 0;
    chunk->headerKeys = malloc(sizeof(char*));
    chunk->headerValues = malloc(sizeof(char*));

    if (chunk->headerKeys == NULL || chunk->headerValues == NULL)
    {
        fprintf(stderr, "Error: Out of memory in InitHeaderChunk");
        abort();
    }
}

static void CleanupHeaderChunk(struct HeaderChunk * chunk)
{
    size_t i;
    for (i = 0; i < chunk->size; ++i)
    {
        free(chunk->headerKeys[i]);
        free(chunk->headerValues[i]);
    }

    chunk->size = 0;
    free(chunk->headerKeys);
    free(chunk->headerValues);
    chunk->headerKeys = NULL;
    chunk->headerValues = NULL;
    
}

static MI_Result GetSSLOptions(struct SSLOptions * sslOptions, 
                               _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    Conf* conf;

    sslOptions->DoNotCheckCertificate = MI_FALSE;
    sslOptions->NoSSLv3 = MI_FALSE;
    sslOptions->cipherList[0] = '\0';
    
    conf = Conf_Open("/opt/omi/etc/dsc/dsc.conf");
    if (!conf)
    {
        return GetCimMIError(MI_RESULT_NOT_FOUND, extendedError, ID_PULL_DSCCONF_NOTOPENABLE);
    }

    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);
        if (r == -1)
        {
            Conf_Close(conf);
            return GetCimMIError1Param(MI_RESULT_NOT_FOUND, extendedError, ID_PULL_DSCCONF_NOTREADABLE, scs(Conf_Error(conf)));
        }

        if (r == 1)
        {
            break;
        }

        if (strcasecmp(key, "DoNotCheckCertificate") == 0)
        {
            if (strcasecmp(value, "true") == 0)
            {
                sslOptions->DoNotCheckCertificate = MI_TRUE;
            }
            else if (strcasecmp(value, "false") == 0)
            {
                sslOptions->DoNotCheckCertificate = MI_FALSE;           
            }
            else
            {
                Conf_Close(conf);
                return GetCimMIError2Params(MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_DSCCONF_INVALIDVALUE, key, value);
            }
        }
        else if (strcasecmp(key, "NoSSLv3") == 0)
        {
            if (strcasecmp(value, "true") == 0)
            {
                sslOptions->NoSSLv3 = MI_TRUE;
            }
            else if (strcasecmp(value, "false") == 0)
            {
                sslOptions->NoSSLv3 = MI_FALSE;         
            }
            else
            {
                Conf_Close(conf);
                return GetCimMIError2Params(MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_DSCCONF_INVALIDVALUE, key, value);
            }
        }
        else if (strcasecmp(key, "sslciphersuite") == 0)
        {
            size_t valueLength = strlen(value);
            if (valueLength > MAX_CIPHER_LIST_LENGTH)
            {
                Conf_Close(conf);
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_PULL_SSLCIPHERLISTTOOLONG);
            }
            memcpy(sslOptions->cipherList, value, valueLength);
            sslOptions->cipherList[valueLength] = '\0';
        }
        else
        {
            continue;
        }
    }

    return MI_RESULT_OK;

}

static size_t HeaderCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct HeaderChunk *chunk = (struct HeaderChunk *)userp; 
  char* colonPointer;
  long key_length;
  long value_length;
  char *charContents = (char*)calloc(realsize, 1);
  
  // We have to do a silly memcpy here because there's no safe version of "strstr", used below.
  memcpy(charContents, contents, realsize);

  // Parse out key+value
  colonPointer = strstr((char*)charContents, ":");
  if (colonPointer == NULL)
  {
      // Not a valid key/value header, ignore and return.
      free(charContents);
      return realsize;
  }

  key_length = (long)(colonPointer - charContents);
  value_length = realsize - key_length - 4;

  if (value_length < 0)
  {
      // Value doesn't exist or has an odd length. Ignore this header line.
      free(charContents);
      return realsize;
  }

  chunk->headerKeys = realloc(chunk->headerKeys, (chunk->size + 1) * sizeof(char*) );
  chunk->headerValues = realloc(chunk->headerValues, (chunk->size + 1) * sizeof(char*) );

  chunk->headerKeys[chunk->size] = malloc( key_length + 1 );
  chunk->headerValues[chunk->size] = malloc( value_length + 1);
  
  memcpy(chunk->headerKeys[chunk->size], charContents, key_length);
  chunk->headerKeys[chunk->size][key_length] = '\0';
  memcpy(chunk->headerValues[chunk->size], colonPointer + 2, value_length);
  chunk->headerValues[chunk->size][value_length] = '\0';

  chunk->size += 1;
  free(charContents);
  return realsize;
}
 
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct Chunk *mem = (struct Chunk *)userp;
 
  mem->data = realloc(mem->data, mem->size + realsize + 1);
  memcpy(&(mem->data[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->data[mem->size] = 0;
 
  return realsize;
}


MI_Char *GetSystemUuid();
MI_Boolean EscapeValue (_In_reads_z_(size) char *tokenValue, int startValue, int size, 
                    _Inout_ int *currentTokenStartValue,
                    _Inout_ int *currentTokenEndValue,
                    _Inout_ int *nextTokenValue);

void CleanupModuleVersionClassTuple(ModuleVersionClassTuple* moduleVersionClassTuple)
{
    ModuleClassList* current;
    ModuleClassList* previous;

    if (moduleVersionClassTuple == NULL)
    {
        return;
    }

    current = moduleVersionClassTuple->first;

    DSC_free(moduleVersionClassTuple->moduleVersion);

    while (current != NULL)
    {
        previous = current;
        current = current->next;
        DSC_free(previous->moduleClass);
        DSC_free(previous);
    }
    DSC_free(moduleVersionClassTuple);
}

void CleanupModuleTableEntry(ModuleTableEntry* moduleTableEntry)
{
    if (moduleTableEntry == NULL)
    {
        return;
    }

    CleanupModuleVersionClassTuple(moduleTableEntry->moduleVersionClassTuple);
    DSC_free(moduleTableEntry->moduleName);
    DSC_free(moduleTableEntry);
}

void CleanupModuleTable(ModuleTable moduleTable)
{
    ModuleTableEntry* current = moduleTable.first;
    ModuleTableEntry* previous;
    while (current != NULL)
    {
        previous = current;
        current = current->next;
        CleanupModuleTableEntry(previous);
    }
}

static int IsModuleVersionValidFormat(MI_Char* string)
{
    MI_Char c;

    if (string == NULL)
    {
        return 0;
    }

    // Make sure we don't have some garbage version number here.  It should be just numbers and decimals.
    while ( (c = *string) != '\0')
    {
        if (c == '0' ||
            c == '1' ||
            c == '2' ||
            c == '3' ||
            c == '4' ||
            c == '5' ||
            c == '6' ||
            c == '7' ||
            c == '8' ||
            c == '9' ||
            c == '.')
        {
            ++string;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

static ModuleTableEntry** ModuleTableContainsKey(ModuleTable* table, MI_Char* moduleNameToFind)
{
    ModuleTableEntry** current;

    if (table == NULL)
    {
        return NULL;
    }
    
    current = &table->first;
    while (*current != NULL)
    {
        if ( Tcscasecmp((*current)->moduleName, moduleNameToFind) == 0 )
        {
            return current;
        }
        else
        {
            current = &(*current)->next;
        }
    }

    return current;
}

static ModuleClassList** ClassListContainsClass(ModuleClassList** firstClassListElement, MI_Char* classNameToFind)
{
    ModuleClassList** current;

    current = firstClassListElement;
    while (*current != NULL)
    {
        if ( Tcscasecmp((*current)->moduleClass, classNameToFind) == 0 )
        {
            return current;
        }
        else
        {
            current = &(*current)->next;
        }
    }

    return current;
}

MI_Boolean ValidateChecksum(_In_z_ MI_Char *checksum, _In_z_ const MI_Char* path)
{
    MI_Uint8 buffer[BUFFER_SIZE_1KB]; // 1 KB at a time
    MI_Char *computedHash = NULL;
    size_t bytesRead;
    SHA256_CTX Ctx;
    char const alphabet[] = "0123456789ABCDEF";
    unsigned char hashedValue[SHA256TRANSFORM_DIGEST_LEN];    
    int iCount = 0;
    FILE * fp = NULL;
    if( checksum == NULL)
        return MI_FALSE;
    
    fp = File_OpenT(path, MI_T("r"));
    if( fp == NULL )
        return MI_FALSE;

#if defined(_MSC_VER)

    SHA256Init(&Ctx);
#else
    SHA256_Init(&Ctx);
#endif


    do
    {
        bytesRead = fread(buffer , 1, BUFFER_SIZE_1KB, fp);
        if( bytesRead > 0 )
        {
#if defined(_MSC_VER)

            SHA256Update
                (
                &Ctx,
                (unsigned char *)buffer,
                (MI_Uint32) bytesRead
                );
#else
            SHA256_Update
                (
                &Ctx,
                (unsigned char *)buffer,
                (MI_Uint32) bytesRead
                );
#endif        
        }
    }while( bytesRead >= BUFFER_SIZE_1KB );
#if defined(_MSC_VER)
    
        SHA256Final(&Ctx, hashedValue);    
#else
        SHA256_Final(hashedValue, &Ctx);
#endif
    
    File_Close(fp);
    // validate the checksum.
    // Use the buffer for memory
    computedHash = (MI_Char*) buffer;
    computedHash[SHA256TRANSFORM_DIGEST_LEN*2] = '\0';
    for(iCount=0; iCount < SHA256TRANSFORM_DIGEST_LEN; iCount++)
    {
        computedHash[2*iCount] = alphabet[ hashedValue[iCount]/16];
        computedHash[2*iCount+1] = alphabet[ hashedValue[iCount]%16];
    }    

    if( Tcscasecmp(checksum, (const MI_Char*)computedHash) != 0 )
        return MI_FALSE;

    return MI_TRUE;
    
}
MI_INLINE MI_Boolean IsValidUuid(_In_z_ MI_Char* systemUuid)
{
    MI_Uint32 len = 0;
    MI_Uint32 xCount = 0;     
    if( systemUuid == NULL)
    {
        return MI_FALSE;
    }
    len = (MI_Uint32)Tcslen(systemUuid);
    if( len != 36 )
        return MI_FALSE;
    //pattern 8-13-19-24 and all characters are hexadecimal. 
    for(xCount = 0; xCount <8; xCount++)
    {
        if(!isxdigit((unsigned char)systemUuid[xCount]))
            return MI_FALSE;
    }
    if(systemUuid[xCount] != MI_T('-'))
        return MI_FALSE;
    for(xCount = 9; xCount <13; xCount++)
    {
        if(!isxdigit((unsigned char)systemUuid[xCount]))
            return MI_FALSE;
    }
    if(systemUuid[xCount] != MI_T('-'))
        return MI_FALSE;
    for(xCount = 14; xCount <18; xCount++)
    {
        if(!isxdigit((unsigned char)systemUuid[xCount]))
            return MI_FALSE;
    }
    if(systemUuid[xCount] != MI_T('-'))
        return MI_FALSE;
    for(xCount = 19; xCount <23; xCount++)
    {
        if(!isxdigit((unsigned char)systemUuid[xCount]))
            return MI_FALSE;
    }
    if(systemUuid[xCount] != MI_T('-'))
        return MI_FALSE;
    for(xCount = 24; xCount <len; xCount++)
    {
        if(!isxdigit((unsigned char)systemUuid[xCount]))
            return MI_FALSE;
    }
    return MI_TRUE;
}

MI_Boolean ConnectionAllowed(_In_ MI_InstanceA *customParam, _In_z_ const MI_Char *serverName)
{
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    MI_Uint32 flags;
    MI_Uint32 xCount;
    for( xCount = 0; xCount < customParam->size ; xCount++)
    {
        r = MI_Instance_GetElement(customParam->data[xCount], MSFT_KEYVALUEPAIR_CLASS_KEY, &value, NULL, &flags, NULL);
        if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) && Tcscasecmp(value.string, AllowUnsecureConnectionParamName) == 0 )
        {
            r = MI_Instance_GetElement(customParam->data[xCount], MSFT_KEYVALUEPAIR_CLASS_VALUE, &value, NULL, &flags, NULL);
            if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) && Tcscasecmp(value.string, MI_T("TRUE")) == 0 )
            {
                return MI_TRUE;
            }
        }
    }
    //only https is allowed.
    if( Tcsncasecmp(serverName, MI_T("https"), 5) == 0 )
        return MI_TRUE;
    
    return MI_FALSE;
}
MI_Result GetMetaConfigParameters(_In_ MI_Instance *metaConfig, 
                                  _In_ MI_Char* partialConfigName,
                                  _Outptr_opt_result_maybenull_    MI_Instance **credential,
                                  _Inout_    MI_InstanceA *customParam,
                                  _Outptr_result_maybenull_z_ MI_Char **configurationID,
                                  _Outptr_result_maybenull_z_ MI_Char **certificateID,
                                  _Inout_updates_(URL_SIZE) MI_Char *url, 
                                  _Inout_updates_(SUBURL_SIZE) MI_Char *subUrl, 
                                  _Out_ MI_Uint32 *port, 
                                  _Out_ MI_Boolean *bIsHttps,
                                  _Out_ MI_Uint32* getActionStatusCode,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    MI_Value value2;
    MI_Value value3;
    MI_Char serverURL[MAX_URL_LENGTH];
    MI_Uint32 flags;
    MI_Uint32 xCount;
    MI_Char* configurationSource = NULL;
    MI_Boolean allowUnsecureConnection;
    MI_InstanceA customData;
    *credential = NULL;
    *extendedError = NULL;
    *getActionStatusCode = Success;
    *configurationID = NULL;
    *certificateID = NULL;
    *bIsHttps = MI_FALSE;
    *port = DEFAULT_SERVERPORT;
    *getActionStatusCode = Success;
    *extendedError = NULL;
    *serverURL = '\0';

    // 1. Get Configuration ID.
    r = MI_Instance_GetElement(metaConfig, MetaConfigConfigurationId, &value, NULL, &flags, NULL);
    if( r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
    {
        *getActionStatusCode = InvalidConfigurationIdInMetaConfig;
        r = GetCimMIError(r, extendedError, ID_PULL_CONFIGURATIONIDNOTSPECIFIED);
        return r;
    }

    /* We will use System UUID only if user has explicitly asked for.*/
    if( Tcscasecmp(value.string, UseSystemUUIDValue) == 0 )
    {
        //Get System GUID
        MI_Char *systemUuid = GetSystemUuid();
        if( systemUuid == NULL || !IsValidUuid(systemUuid))
        {
            *getActionStatusCode = InvalidConfigurationIdInMetaConfig;
            if( systemUuid) 
                DSC_free(systemUuid);
            r = GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULL_INVALIDCONFIGURATIONIDFORMAT, systemUuid);
            return r;            
        }
        *configurationID = systemUuid;
    }
    else
    {
        *configurationID = (MI_Char*)DSC_malloc((Tcslen(value.string)+1) * sizeof(MI_Char), NitsHere());
        if( *configurationID == NULL)
        {
            *getActionStatusCode = InvalidConfigurationIdInMetaConfig;
            r = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
            return r;              
        }
        memcpy(*configurationID, value.string, Tcslen(value.string)* sizeof(MI_Char));
        /* Validate the Uuid.*/
        if( !IsValidUuid(*configurationID))
        {
            *getActionStatusCode = InvalidConfigurationIdFormat;
            r = GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULL_INVALIDCONFIGURATIONIDFORMAT, *configurationID);
            DSC_free(*configurationID);             
            return r;            
        }
        
    }

    // 2. Get Credential.
    r = MI_Instance_GetElement(metaConfig, MetaConfig_Credential, &value, NULL, &flags, NULL);
    if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
    {
        *credential = value.instance;
    }     
    


    // If partialConfigName is defined, get the ConfigurationDownloadManagers, else get the DownloadManagerCustomData
    if ( partialConfigName != NULL )
    {
        r = MI_Instance_GetElement(metaConfig, MSFT_DSCMetaConfiguration_PartialConfigurations, &value, NULL, &flags, NULL);
        if (r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
        {
            return GetCimMIError(MI_RESULT_NO_SUCH_PROPERTY, extendedError, ID_PULL_NOPARTIALCONFIGS);
        }

        for (xCount = 0; xCount < value.instancea.size; ++xCount)
        {
            MI_Instance_GetElement(value.instancea.data[xCount], OMI_MetaConfigurationResource_ResourceId, &value2, NULL, &flags, NULL);
            if ( Tcscasecmp(value2.string, partialConfigName) == 0 )
            {
                // Found our partial config! Now let's get the configuration source
                MI_Instance_GetElement(value.instancea.data[xCount], MSFT_PartialConfiguration_ConfigurationSource, &value2, NULL, &flags, NULL);
                if (r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
                {
                    return GetCimMIError1Param(MI_RESULT_NO_SUCH_PROPERTY, extendedError, ID_PULL_NOCONFIGURATIONSOURCE, partialConfigName);
                }

                configurationSource = value2.string;
                break;
            }
        }
        if (configurationSource == NULL)
        {
            // Unable to find partial configuration with this name.
            return GetCimMIError1Param(MI_RESULT_NO_SUCH_PROPERTY, extendedError, ID_PULL_NOCONFIGURATIONSOURCE, partialConfigName);
        }

        r = MI_Instance_GetElement(metaConfig, MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers, &value, NULL, &flags, NULL);
        if (r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
        {
            // Unable to get the config download managers
            return GetCimMIError(MI_RESULT_NO_SUCH_PROPERTY, extendedError, ID_PULL_NOCONFIGDOWNLOADMANAGERS);
        }

        for (xCount = 0; xCount < value.instancea.size; ++xCount)
        {
            MI_Instance_GetElement(value.instancea.data[xCount], OMI_MetaConfigurationResource_ResourceId, &value2, NULL, &flags, NULL);   
            if ( Tcscasecmp(value2.string, configurationSource) == 0 )
            {
                // Found the WebDownloadManager with the proper resource ID.
                MI_Instance_GetElement(value.instancea.data[xCount], MI_T("ServerURL"), &value2, NULL, &flags, NULL);   
                if (r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
                {
                    return GetCimMIError1Param(MI_RESULT_NO_SUCH_PROPERTY, extendedError, ID_PULL_NOSERVERURL, value3.string);
                }

                memcpy(serverURL, value2.string, (Tcslen(value2.string) + 1) * sizeof(MI_Char));

                MI_Instance_GetElement(value.instancea.data[xCount], MI_T("CertificateID"), &value2, NULL, &flags, NULL);   
                if (r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
                {
                    memcpy(*certificateID, value2.string, Tcslen(value2.string) * sizeof(MI_Char));  
                }

                MI_Instance_GetElement(value.instancea.data[xCount], MI_T("AllowUnsecureConnection"), &value2, NULL, &flags, NULL);   
                if (r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
                {
                    allowUnsecureConnection = value2.boolean;
                }

                //Check if connection is secure and if unsecure user explicitly asks for it.
                if( Tcsncasecmp(serverURL, MI_T("https"), 5) != 0 && allowUnsecureConnection == MI_FALSE )
                {
                    *getActionStatusCode = InvalidDownloadManagerCustomDataInMetaConfig;
                    r = GetCimMIError1Param( MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_UNSECURECONNECTIONNOTALLOWED, serverURL);
                    return r;     
                }
            }
        }
    }
    else
    {
        // 3. Get custom arguments.
        r = MI_Instance_GetElement(metaConfig, MetaConfigDownloadManagerCustomData, &value, NULL, &flags, NULL);
        if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
        {
            customParam->size = value.instancea.size;
            customParam->data = value.instancea.data;
        }

        
        // 4. Get certificate ID.
        for( xCount =0; xCount < customParam->size; xCount++)
        {
            MI_Value value;
            MI_Uint32 flags;
            r = MI_Instance_GetElement(customParam->data[xCount], MSFT_KEYVALUEPAIR_CLASS_KEY, &value, NULL, &flags, NULL);
            if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) && Tcscasecmp(CertificateIdParamName, value.string) == 0 )
            {
                r = MI_Instance_GetElement(customParam->data[xCount], MSFT_KEYVALUEPAIR_CLASS_VALUE, &value, NULL, &flags, NULL);
                if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) )
                {
                    *certificateID = (MI_Char*)DSC_malloc((Tcslen(value.string)+1) * sizeof(MI_Char), NitsHere());
                    if( *certificateID == NULL)
                    {
                        *getActionStatusCode = InvalidConfigurationIdInMetaConfig;
                        r = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
                        if( *configurationID )
                            DSC_free(*configurationID);
                        *configurationID = NULL;
                        return r;              
                    }
                    memcpy(*certificateID, value.string, Tcslen(value.string)* sizeof(MI_Char));  
                    break;
                }
            }
        }         
    }

    if (*serverURL == '\0')
    {
        r = MI_Instance_GetElement(metaConfig, MetaConfigDownloadManagerCustomData, &value, NULL, &flags, NULL);
        if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
        {
            customData.size = value.instancea.size;
            customData.data = value.instancea.data;

            // Get Server Url.
            for( xCount =0; xCount < customData.size; xCount++)
            {
                MI_Value value;
                MI_Uint32 flags;
                r = MI_Instance_GetElement(customData.data[xCount], MSFT_KEYVALUEPAIR_CLASS_KEY, &value, NULL, &flags, NULL);
                if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) && Tcscasecmp(ServerUrlParamName, value.string) == 0 )
                {
                    r = MI_Instance_GetElement(customData.data[xCount], MSFT_KEYVALUEPAIR_CLASS_VALUE, &value, NULL, &flags, NULL);
                    if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) )
                    {
                        // Found ServerUrl in value.string
                        memcpy(serverURL, value.string, (Tcslen(value.string) + 1) * sizeof(MI_Char));
                        
                        //Check if connection is secure and if unsecure user explicitly asks for it.
                        if( !ConnectionAllowed(&customData, serverURL) )
                        {
                            *getActionStatusCode = InvalidDownloadManagerCustomDataInMetaConfig;
                            r = GetCimMIError1Param( MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_UNSECURECONNECTIONNOTALLOWED, serverURL);
                            return r;
                        }   
                        
                        break;
                    }
                }
            }
        }      
        else
        {
            // There's no DownloadManagerCustomData, AND there's no partial configuration.  We should be able to find WebDownloadManager, and only one!
            r = MI_Instance_GetElement(metaConfig, MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers, &value, NULL, &flags, NULL);
            if (r != MI_RESULT_OK || (flags & MI_FLAG_NULL) || value.instancea.size == 0)
            {
                // Unable to get the config download managers
                return GetCimMIError(MI_RESULT_NO_SUCH_PROPERTY, extendedError, ID_PULL_NOCONFIGDOWNLOADMANAGERS);
            }
         
            if (value.instancea.size > 1)
            {
                // Too many download managers defined, please set up partial configuration for this.
                return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_TOOMANYCONFIGDOWNLOADMANAGERS);
            }

            MI_Instance_GetElement(value.instancea.data[0], OMI_MetaConfigurationResource_ResourceId, &value3, NULL, &flags, NULL);   

            // Found the WebDownloadManager with the proper resource ID.
            MI_Instance_GetElement(value.instancea.data[0], MI_T("ServerURL"), &value2, NULL, &flags, NULL);   
            if (r != MI_RESULT_OK || (flags & MI_FLAG_NULL))
            {
                return GetCimMIError1Param(MI_RESULT_NO_SUCH_PROPERTY, extendedError, ID_PULL_NOSERVERURL, value3.string);
            }
            
            memcpy(serverURL, value2.string, (Tcslen(value2.string) + 1) * sizeof(MI_Char));

            MI_Instance_GetElement(value.instancea.data[0], MI_T("CertificateID"), &value2, NULL, &flags, NULL);   
            if (r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
            {
                memcpy(*certificateID, value2.string, Tcslen(value2.string) * sizeof(MI_Char));  
            }
            
            MI_Instance_GetElement(value.instancea.data[0], MI_T("AllowUnsecureConnection"), &value2, NULL, &flags, NULL);   
            if (r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
            {
                allowUnsecureConnection = value2.boolean;
            }
        }
    }

    if (*serverURL != '\0')
    {       
#if defined (_MSC_VER)                
        //format is: http://server:port/suburl or http://server/suburl
        if( swscanf_s(serverURL, MI_T("http://%99[^:]:%d/%199[^\n]"), url, URL_SIZE, port, subUrl, SUBURL_SIZE) == 3 || 
            swscanf_s(serverURL, MI_T("http://%99[^/]/%199[^\n]"), url, URL_SIZE, subUrl, SUBURL_SIZE) == 2 )
        {
            //success
        }
        //format is: http://server:port/suburl or http://server/suburl
        else if( swscanf_s(serverURL, MI_T("https://%99[^:]:%d/%199[^\n]"), url, URL_SIZE, port, subUrl, SUBURL_SIZE) == 3 || 
                 swscanf_s(serverURL, MI_T("https://%99[^/]/%199[^\n]"), url, URL_SIZE, subUrl, SUBURL_SIZE) == 2 )
        {
            //success
            *bIsHttps = MI_TRUE;
        }
#else
        if( sscanf(serverURL, MI_T("http://%99[^:]:%d/%199[^\n]"), url, port, subUrl) == 3 || 
            sscanf(serverURL, MI_T("http://%99[^/]/%199[^\n]"), url, subUrl) == 2 )
        {
            //success
        }
        //format is: http://server:port/suburl or http://server/suburl
        else if( sscanf(serverURL, MI_T("https://%99[^:]:%d/%199[^\n]"), url, port, subUrl) == 3 || 
                 sscanf(serverURL, MI_T("https://%99[^/]/%199[^\n]"), url, subUrl) == 2 )
        {
            //success
            *bIsHttps = MI_TRUE;
        }
#endif                      
    }
    else
    {
        // Not found
        *getActionStatusCode = InvalidDownloadManagerCustomDataInMetaConfig;
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);   
    }
    
    return MI_RESULT_OK;
   
}

MI_Char * GetGetActionBodyContent(_In_z_ const MI_Char *checksum, MI_Boolean nodeCompliant, 
                                _In_z_ const MI_Char *checksumAlgorithm, MI_Uint32 statusCode)
{
    const MI_Char *checksumName = MI_T("Checksum");
    const MI_Char *complianceName = MI_T("NodeCompliant");
    const MI_Char *algorithmName = MI_T("ChecksumAlgorithm");
    const MI_Char *statusCodeName = MI_T("StatusCode");
    const MI_Char *complianceStatus;
    MI_Char statusCodeValue[MAX_STATUSCODE_SIZE];
    size_t length;
    MI_Char *content = NULL;
    
    if( nodeCompliant == MI_TRUE)
    {
        complianceStatus = MI_T("TRUE");
    }
    else
    {
        complianceStatus = MI_T("FALSE");
    }
    Stprintf(statusCodeValue, MAX_STATUSCODE_SIZE, MI_T("%d"), statusCode);
    // Format should be:  {"Checksum":"ABCD","NodeCompliant":"False","ChecksumAlgorithm":"SHA-256", "StatusCode":"5"}

    length = sizeof( MI_T("{\"")) + Tcslen(checksumName) + sizeof(MI_T("\":\"")) + 
        Tcslen(checksum) + sizeof(MI_T("\",\"")) +
        Tcslen(complianceName) + sizeof(MI_T("\":\"")) +
        Tcslen(complianceStatus) + sizeof(MI_T("\",\"")) +
        Tcslen(algorithmName) + sizeof(MI_T("\":\"")) +
        Tcslen(checksumAlgorithm) +  sizeof(MI_T("\":\"")) +
        Tcslen(statusCodeName) + sizeof(MI_T("\":\"")) +
        Tcslen(statusCodeValue) + sizeof(MI_T("\"}")) + 1;

    content = (MI_Char *)DSC_malloc(length * sizeof(MI_Char), NitsHere());
    if( content == NULL )
    {
        return NULL;
    }

    Stprintf(content, length, MI_T("{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}"), checksumName, checksum, 
                            complianceName, complianceStatus, algorithmName, checksumAlgorithm, statusCodeName, statusCodeValue);
    return content;
}

int EscapeString(_In_reads_z_(size) char *tokenValue, int startValue, int size)
{
    int xCount = startValue;
    char *start = tokenValue;    
    while( xCount < size)
    {
        if( *(start+xCount) == '"')
        {
          return xCount-1;
        }
        if( (*(start+xCount) == '\\') && (xCount+1 < size) && (*(start+xCount+1) == '"'))
        xCount++;
    
        xCount++;
    }    
    return -1;
}

int EscapeArray (_In_reads_z_(size) char *tokenValue, int startValue, int size)
{
    int xCount = startValue;
    char *start = tokenValue; 
    int currentTokenStartValue = 0;
    int currentTokenEndValue = 0;
    int nextTokenValue = 0;
    // escape until we get ']'. It will be in format value[,]value*
    while( xCount < size)
    {
        if( *(start+xCount) == ']')
        {
          return xCount-1;
        }
        else if ( *(start+xCount) == ',')
            xCount++;
        else
        {
            if(!EscapeValue(tokenValue, xCount, size, &currentTokenStartValue, &currentTokenEndValue, &nextTokenValue))
            {
                return -1;
            }
            xCount = nextTokenValue;
        }
    }    
    return -1;
}

int EscapeObject (_In_reads_z_(size) char *tokenValue, int startValue, int size)
{
    int xCount = startValue;
    char *start = tokenValue; 
    int currentTokenStartValue = 0;
    int currentTokenEndValue = 0;    
    int nextTokenValue = 0;
    // escape until we get '}'. it will be in format {string:value};
    while( xCount < size)
    {
        if( *(start+xCount) == '}')
        {
          return xCount-1;
        }
        else if ( *(start+xCount) == ',')
            xCount++;
        else
        {
            if(!EscapeValue(tokenValue, xCount, size, &currentTokenStartValue, &currentTokenEndValue, &nextTokenValue))
            {
                return -1;
            }
            xCount = nextTokenValue;            
        }
        xCount++;
    }    
    return -1;
}

int EscapeNumber (_In_reads_z_(size) char *tokenValue, int startValue, int size)
{
    int xCount = startValue;
    char *start = tokenValue;  
    // escape until we get ":",",","}",}]". 
    while( xCount < size)
    {
        if( *(start+xCount) == ',' ||
            *(start+xCount) == '}'||
            *(start+xCount) == ']' )
        {
          return xCount-1;
        }
        xCount++;
    }    
    return -1;
}

MI_Boolean EscapeValue (_In_reads_z_(size) char *tokenValue, int startValue, int size, 
                    _Inout_ int *currentTokenStartValue,
                    _Inout_ int *currentTokenEndValue,
                    _Inout_ int *nextTokenValue)
{
    int xCount = startValue;
    char *start = tokenValue;     
    if( xCount < size)
        {
        if( *(start+xCount) == '"' ) // it is a string
        {
            *currentTokenStartValue = xCount +1;
            //TokenEnd
            *currentTokenEndValue = EscapeString(tokenValue, *currentTokenStartValue, size);
            *nextTokenValue = *currentTokenEndValue + 2;
        }
        else if( *(start+xCount) == '[' ) // it is an array
        {
            *currentTokenStartValue = xCount +1;
            *currentTokenEndValue = EscapeArray(tokenValue, *currentTokenStartValue, size);
            *nextTokenValue = *currentTokenEndValue + 2;
        }
        else if( *(start+xCount) == '{' ) // it is an object
        {
            *currentTokenStartValue = xCount +1;        
            *currentTokenEndValue = EscapeObject(tokenValue, *currentTokenStartValue, size);
            *nextTokenValue = *currentTokenEndValue + 2;
        }    
        else if( Strcasecmp(start+xCount, "true")) // it is value true
        {
            *currentTokenStartValue = xCount;        
            *currentTokenEndValue = xCount + 3;
            *nextTokenValue = *currentTokenEndValue + 1;
        }    
        else if( Strcasecmp(start+xCount, "false")) // it is value false
        {
            *currentTokenStartValue = xCount;        
            *currentTokenEndValue = xCount + 4;
            *nextTokenValue = *currentTokenEndValue + 1;
        }        
        else if( Strcasecmp(start+xCount, "null")) // it is value true
        {
            *currentTokenStartValue = xCount;        
            *currentTokenEndValue = xCount + 3;
            *nextTokenValue = *currentTokenEndValue + 1;
        }  
        else // it is a number
        {
            *currentTokenStartValue = xCount;    
            *currentTokenEndValue = EscapeNumber(tokenValue, *currentTokenStartValue, size);
            *nextTokenValue = *currentTokenEndValue + 2;
        }   
        if (*currentTokenEndValue == -1 || *currentTokenStartValue == -1)
            return MI_FALSE;     
        return MI_TRUE;        
    }
    return MI_FALSE;
}



MI_Boolean GetNextToken(_In_reads_z_(size) char *tokenValue, int startValue, int size, 
                    _Inout_ int *currentTokenStart,
                    _Inout_ int *currentTokenEnd,
                    _Inout_ int *currentTokenStartValue,
                    _Inout_ int *currentTokenEndValue,
                    _Inout_ int *nextTokenValue)
{
    int xCount = startValue;
    char *start = tokenValue;
    // TokenStart
    while( xCount < size)
    {
        if( *(start+xCount) == '"')
        {
          *currentTokenStart =  xCount+1;
        //TokenEnd
        *currentTokenEnd = EscapeString(tokenValue, *currentTokenStart, size);
        if (*currentTokenEnd == -1)
            return MI_FALSE; 
        
          break;
        }
        if( (*(start+xCount) == '\\') && (xCount+1 < size) && (*(start+xCount+1) == '"'))
        xCount++;
    
        xCount++;
    }
    if( xCount >= size )
        return MI_FALSE;

    xCount = *currentTokenEnd + 3;
    //TokenStartValue
    if( xCount >= size)
      return MI_FALSE;

    if(!EscapeValue(tokenValue, xCount, size, currentTokenStartValue , currentTokenEndValue, nextTokenValue))
        return MI_FALSE;
    
    return MI_TRUE;    
  
}


MI_Boolean GetGetActionData( _In_reads_z_(size) char *start, int size, _Out_ char** serverResponse)
{
    //Search for pattern "value":"<dommmm>", We don't support anything other than simple strings
    int xCount = 1; // escape first character
    int currentTokenStart = 0, currentTokenStartValue = 0;
    int currentTokenEnd = 0, currentTokenEndValue = 0;
    int nextTokenValue = -1;
    *serverResponse = NULL;
    while(xCount < size)
    {
        // get token Name
        if(!GetNextToken( start, xCount, size, &currentTokenStart, &currentTokenEnd, &currentTokenStartValue, &currentTokenEndValue, &nextTokenValue))
            return MI_FALSE;

        if(Strncmp(start+currentTokenStart,"value", currentTokenEnd-currentTokenStart+1) == 0)
        {
              //copy value here
              *serverResponse = (char*) DSC_malloc(currentTokenEndValue - currentTokenStartValue +2, NitsHere());
             if(*serverResponse)
             {
                memcpy(*serverResponse, start+currentTokenStartValue, currentTokenEndValue-currentTokenStartValue+1);
                return MI_TRUE;
             }
             return MI_FALSE;
        }
        xCount = nextTokenValue;
    }
    return MI_FALSE;
}

MI_Boolean ValidateContentTypeHeader(_Inout_updates_z_(size)  MI_Char *buffer, MI_Uint32 size, _In_z_ const MI_Char *header)
{
    MI_Uint32 startIndex = 0;
    MI_Char *start = buffer;
    MI_Char *firstOccurancePointer = NULL;
    while( start != NULL && *start != MI_T('\0') && startIndex < size)
    {
        firstOccurancePointer = Tcschr(start + startIndex, ';');
        if( firstOccurancePointer == NULL)
        {
            if( Tcscasecmp(start + startIndex, header) == 0 )
            {
                return MI_TRUE;
            }
            return MI_FALSE;
        }        
        if( (firstOccurancePointer - start >= size-1) ||  firstOccurancePointer < start)
        {
            return MI_FALSE;
        }
        start[ firstOccurancePointer - start] = MI_T('\0');
        if( Tcscasecmp(start + startIndex , header) == 0 )
        {
            return MI_TRUE;
        }
        startIndex = (MI_Uint32) (firstOccurancePointer - start + 1);
    }
    return MI_FALSE;
}


/* Caller will validate the content.*/
MI_Char *GetSystemUuid()
{
    MI_Char *systemUUid = NULL;
    FILE * fp = File_OpenT(product_uuid_path, MI_T("r"));
    if( fp == NULL )
        return NULL;

    systemUUid = (MI_Char*)DSC_malloc(JOB_UUID_LENGTH* sizeof(MI_Char), NitsHere());
    if( systemUUid == NULL)
    {
        File_Close(fp);
        return NULL;
    }  
    // Caller will validate the contents.
    fread(systemUUid , 1, JOB_UUID_LENGTH, fp);
            File_Close(fp);        
    return systemUUid;
        }        

MI_Result  IssueGetActionRequest( _In_z_ const MI_Char *configurationID, 
                                 _In_z_ const MI_Char *certificateID,
                                 _In_z_ const MI_Char *checkSum,
                                  _In_z_ struct SSLOptions sslOptions,
                                 _In_ MI_Boolean complianceStatus,
                                _In_ MI_Uint32 lastGetActionStatusCode,
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _In_reads_z_(URL_SIZE) const MI_Char *url,
                                _In_ MI_Uint32 port,
                                _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                MI_Boolean bIsHttps,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    const char *emptyString = "";
    char *bodyContent = NULL;
    const char *checkSumFinalValue = emptyString;
    RequestContainer requestParam = {0};
    MI_Char actionUrl[MAX_URL_LENGTH];
    char * getActionStatus = NULL;
    long responseCode;

    CURL *curl;
    CURLcode res;
    struct Chunk headerChunk;
    struct Chunk dataChunk;
    struct curl_slist *list = NULL;

    requestParam.serverOperation = OPERATION_GETACTION;
    if( checkSum != NULL)
        checkSumFinalValue = checkSum;  

    *result = NULL;

    DSC_EventWriteWebDownloadManagerDoActionServerUrl(configurationID, url);
    
    // Get body for GetAction request
    bodyContent = GetGetActionBodyContent(checkSumFinalValue, complianceStatus, AllowedChecksumAlgorithm, lastGetActionStatusCode);

    if( bodyContent == NULL )
    {
        *getActionStatusCode = DownloadManagerInitializationFailure;
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }    


    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    curl = curl_easy_init();
    if (!curl)
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOINITIALIZE);
    }

    if (bIsHttps)
    {
        Snprintf(actionUrl, MAX_URL_LENGTH, "https://%s:%d/%s/Action(ConfigurationId='%s')/GetAction", url, port, subUrl, configurationID);
        curl_easy_setopt(curl, CURLOPT_URL, actionUrl);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        if (sslOptions.DoNotCheckCertificate == MI_TRUE)
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        }
    }
    else
    {
        Snprintf(actionUrl, MAX_URL_LENGTH, "http://%s:%d/%s/Action(ConfigurationId='%s')/GetAction", url, port, subUrl, configurationID);
        curl_easy_setopt(curl, CURLOPT_URL, actionUrl);
    }

    headerChunk.data = (char *)malloc(1);
    headerChunk.size = 0;
    dataChunk.data = (char *)malloc(1);
    dataChunk.size = 0;


    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json; charset=utf-8");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyContent);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerChunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataChunk);
    
    if (sslOptions.cipherList[0] != '\0')
    {
        res = curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, sslOptions.cipherList);
        if (res != CURLE_OK)
        {
            *getActionStatusCode = GetDscActionCommandFailure;
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOSETCIPHERLIST);
        }
    }

    if (sslOptions.NoSSLv3 == MI_TRUE)
    {
        res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
        if (res != CURLE_OK)
        {
            *getActionStatusCode = GetDscActionCommandFailure;
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOSETNOSSLV3);
        }
    }
    

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        free(headerChunk.data);
        free(dataChunk.data);
        return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_CURLPERFORMFAILED, url, curl_easy_strerror(res));
    }      

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    curl_slist_free_all(list);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (responseCode != HTTP_SUCCESS_CODE)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        free(headerChunk.data);
        free(dataChunk.data);
        return GetCimMIError1Param(r, extendedError, ID_PULL_GETACTIONFAILED, webPulginName); 
    }    

    GetGetActionData(dataChunk.data, dataChunk.size, &getActionStatus);
    
    free(headerChunk.data);
    free(dataChunk.data);
    

    if( getActionStatus == NULL)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULL_GETACTIONFAILED, webPulginName);         
    }    
    if (! (Strcasecmp( getActionStatus, GetActionResultOk) == 0 ||
        Strcasecmp( getActionStatus, GetActionResultGetConfiguration) == 0 ) )
    {
    
        *getActionStatusCode = GetDscActionCommandFailure;
        r = GetCimMIError2Params(MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_GETACTIONUNEXPECTEDRESULT, getActionStatus, url);
        DSC_free(getActionStatus);
        return r;
    }

    *result = getActionStatus;
    *getActionStatusCode = Success;       
    DSC_EventWriteWebDownloadManagerDoActionGetCall(configurationID, requestParam.u.action.getActionStatus);
    
    return MI_RESULT_OK;
}

MI_Result  IssueGetConfigurationRequest( _In_z_ const MI_Char *configurationID,
                                _In_z_ const MI_Char *certificateID,
                                _In_z_ const MI_Char *directoryPath, 
                                         _In_z_ struct SSLOptions sslOptions,
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _In_reads_z_(URL_SIZE) const MI_Char *url,
                                _In_ MI_Uint32 port,
                                _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                MI_Boolean bIsHttps,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char *outputResult = (MI_Char*)DSC_malloc((Tcslen(MI_T("OK"))+1) * sizeof(MI_Char), NitsHere());

    CURL *curl;
    CURLcode res;
    struct HeaderChunk headerChunk;
    struct Chunk dataChunk;
    char configurationUrl[MAX_URL_LENGTH];
    long responseCode;
    size_t i;
    char* checksumResponse = NULL;
    char* checksumAlgorithmResponse = NULL;

    *result = NULL;
    if( outputResult == NULL )
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }    
    DSC_EventWriteGetDscDocumentWebDownloadManagerServerUrl(configurationID, url);    
    Stprintf(outputResult,3, MI_T("OK"));

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (!curl)
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOINITIALIZE);
    }
    
    if (bIsHttps)
    {
        Snprintf(configurationUrl, MAX_URL_LENGTH, "https://%s:%d/%s/Action(ConfigurationId='%s')/ConfigurationContent", url, port, subUrl, configurationID);
        curl_easy_setopt(curl, CURLOPT_URL, configurationUrl);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        if (sslOptions.DoNotCheckCertificate == MI_TRUE)
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        }
    }    
    else
    {
        Snprintf(configurationUrl, MAX_URL_LENGTH, "http://%s:%d/%s/Action(ConfigurationId='%s')/ConfigurationContent", url, port, subUrl, configurationID);
        curl_easy_setopt(curl, CURLOPT_URL, configurationUrl);
    }

    InitHeaderChunk(&headerChunk);
    dataChunk.data = (char *)malloc(1);
    dataChunk.size = 0;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerChunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataChunk);

    
    if (sslOptions.cipherList[0] != '\0')
    {
        res = curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, sslOptions.cipherList);
        if (res != CURLE_OK)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOSETCIPHERLIST);
        }
    }

    if (sslOptions.NoSSLv3 == MI_TRUE)
    {
        res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
        if (res != CURLE_OK)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOSETNOSSLV3);
        }
    }

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        CleanupHeaderChunk(&headerChunk);
        free(dataChunk.data);
        DSC_free(outputResult);
        return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_CURLPERFORMFAILED, url, curl_easy_strerror(res));
    }      

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (responseCode != HTTP_SUCCESS_CODE)
    {
        MI_Char statusCodeValue[MAX_STATUSCODE_SIZE] = {0};
        *getActionStatusCode = GetConfigurationCommandFailure;
        CleanupHeaderChunk(&headerChunk);
        free(dataChunk.data);
        DSC_free(outputResult);
        Stprintf(statusCodeValue, MAX_STATUSCODE_SIZE, MI_T("%d"), responseCode);
        return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_SERVERHTTPERRORCODE, url, statusCodeValue);
    }

    for (i = 0; i < headerChunk.size; ++i)
    {
        if (checksumResponse != NULL && checksumAlgorithmResponse != NULL)
        {
            break;
        }
        
        if ( Tcscasecmp(headerChunk.headerKeys[i], "Checksum") == 0 )
        {
            checksumResponse = headerChunk.headerValues[i];
        }
        else if ( Tcscasecmp(headerChunk.headerKeys[i], "ChecksumAlgorithm") == 0 )
        {
            checksumAlgorithmResponse = headerChunk.headerValues[i];
        }
    }
    if (checksumResponse == NULL || checksumAlgorithmResponse == NULL)
    {
        *getActionStatusCode = InvalidChecksumAlgorithm;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_INVALIDRESPONSEFROMSERVER);
    }
    
    if( Tcscasecmp(checksumAlgorithmResponse, AllowedChecksumAlgorithm) != 0 )
    {
        *getActionStatusCode = InvalidChecksumAlgorithm;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_INVALIDCHECKSUMALGORITHM);
    }

    if( dataChunk.size > 0 )
    {
        FILE *fp = File_OpenT(directoryPath, MI_T("a"));
        if(fp == NULL)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, 
                                       ID_PULL_CONFIGURATIONSAVEFAILED, directoryPath);
        }
        fwrite( dataChunk.data, 1, dataChunk.size, fp);
        File_Close(fp);
    }
    
    if( !ValidateChecksum(checksumResponse, directoryPath) )
    {
        DSC_EventWriteWebDownloadManagerGetDocChecksumValidation(NULL, NULL);
        *getActionStatusCode = ConfigurationChecksumValidationFailure;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CHECKSUMMISMATCH);
    }
    
    DSC_EventWriteLCMPullConfigurationChecksumValidationResult(configurationID, (MI_Uint32)MI_RESULT_OK);
    
    //Create checksumFile
    {
        MI_Char checksumFileName[MAX_URL_LENGTH];
        FILE *fp = NULL;
        Stprintf(checksumFileName, MAX_URL_LENGTH,MI_T("%s.checksum"), directoryPath);
        fp = File_OpenT(checksumFileName,MI_T("w"));
        if( fp != NULL )
        {
            fwrite(checksumResponse, 1, Strlen(checksumResponse), fp);
            File_Close(fp);
        }
        else
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            DSC_free(outputResult);
            return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULLGETCONFIGURATION_CHECKSUMSAVEFAILED, checksumFileName);            
        }
    }

    CleanupHeaderChunk(&headerChunk);
    free(dataChunk.data);

    *result = outputResult;
    DSC_EventWriteWebDownloadManagerGetDocGetCall(configurationID, *result );

    return MI_RESULT_OK;
}

MI_Result GetUrlParam(_In_ MI_InstanceA *customData, 
    _Inout_updates_(URL_SIZE) MI_Char *url, 
    _Inout_updates_(SUBURL_SIZE) MI_Char *subUrl, 
    _Out_ MI_Uint32 *port, 
    _Out_ MI_Boolean *bIsHttps,
    _Out_ MI_Uint32* getActionStatusCode,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 xCount = 0;
    MI_Result r = MI_RESULT_OK;
    *bIsHttps = MI_FALSE;
    *port = DEFAULT_SERVERPORT;
    *getActionStatusCode = Success;
    *extendedError = NULL;

    // Get Server Url.
    for( xCount =0; xCount < customData->size; xCount++)
    {
        MI_Value value;
        MI_Uint32 flags;
        r = MI_Instance_GetElement(customData->data[xCount], MSFT_KEYVALUEPAIR_CLASS_KEY, &value, NULL, &flags, NULL);
        if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) && Tcscasecmp(ServerUrlParamName, value.string) == 0 )
        {
            r = MI_Instance_GetElement(customData->data[xCount], MSFT_KEYVALUEPAIR_CLASS_VALUE, &value, NULL, &flags, NULL);
            if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) )
            {
                //Check if connection is secure and if unsecure user explicitly asks for it.
                if( !ConnectionAllowed(customData, value.string) )
                {
                    *getActionStatusCode = InvalidDownloadManagerCustomDataInMetaConfig;
                    r = GetCimMIError1Param( MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_UNSECURECONNECTIONNOTALLOWED, value.string);
                    return r;   
                }            
#if defined (_MSC_VER)                
                //format is: http://server:port/suburl or http://server/suburl
                if( swscanf_s(value.string, MI_T("http://%99[^:]:%d/%199[^\n]"), url, URL_SIZE, port, subUrl, SUBURL_SIZE) == 3 || 
                    swscanf_s(value.string, MI_T("http://%99[^/]/%199[^\n]"), url, URL_SIZE, subUrl, SUBURL_SIZE) == 2 )
                {
                    //success
                }
                //format is: http://server:port/suburl or http://server/suburl
                else if( swscanf_s(value.string, MI_T("https://%99[^:]:%d/%199[^\n]"), url, URL_SIZE, port, subUrl, SUBURL_SIZE) == 3 || 
                    swscanf_s(value.string, MI_T("https://%99[^/]/%199[^\n]"), url, URL_SIZE, subUrl, SUBURL_SIZE) == 2 )
                {
                    //success
                    *bIsHttps = MI_TRUE;
                }
#else
                if( sscanf(value.string, MI_T("http://%99[^:]:%d/%199[^\n]"), url, port, subUrl) == 3 || 
                    sscanf(value.string, MI_T("http://%99[^/]/%199[^\n]"), url, subUrl) == 2 )
                {
                    //success
                }
                //format is: http://server:port/suburl or http://server/suburl
                else if( sscanf(value.string, MI_T("https://%99[^:]:%d/%199[^\n]"), url, port, subUrl) == 3 || 
                    sscanf(value.string, MI_T("https://%99[^/]/%199[^\n]"), url, subUrl) == 2 )
                {
                    //success
                    *bIsHttps = MI_TRUE;
                }
#endif                      
                break;
            }
        }
    }    

    if(  xCount >= customData->size ) // Not found
    {
        *getActionStatusCode = InvalidDownloadManagerCustomDataInMetaConfig;
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);   
    }
    return MI_RESULT_OK;
}
    


MI_Result GetRequestParam(_In_ MI_Instance *metaConfig, 
                          _In_ MI_Char * partialConfigName,
                          _Inout_updates_(URL_SIZE) MI_Char *url,
                          _Inout_updates_(SUBURL_SIZE) MI_Char *subUrl,
                          _Out_ MI_Uint32 *port,
                          _Out_ MI_Boolean *bIsHttps,
                          _Outptr_result_maybenull_z_ MI_Char **configurationID,
                          _Outptr_result_maybenull_z_ MI_Char **certificateID,
                          _Out_ MI_Uint32* getActionStatusCode,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Instance *credential = NULL;
    MI_InstanceA customParam = {0};
    *bIsHttps = MI_FALSE;
     //Get meta configuration elements
    r = GetMetaConfigParameters(metaConfig, partialConfigName, &credential, &customParam, configurationID, certificateID, url, subUrl, port, bIsHttps, getActionStatusCode, extendedError);
    return r;
}

MI_Result CreateTmpDirectoryPath(_Outptr_result_maybenull_z_  MI_Char** directoryPath, _Outptr_result_maybenull_z_  MI_Char** fileLocation)
{
    MI_Char *path;
   if( TempnamT(&path) )
       return MI_RESULT_FAILED;
   
   if( path != NULL)
   { 
       int result = MkdirT(path, 777); // 777 is standard permission on directory for Linux.
       if( result == 0 )
       {
            MI_Char *filePath = (MI_Char*) DSC_malloc(MAX_URL_LENGTH * sizeof(MI_Char), NitsHere());
            if( filePath == NULL )
            {
                free(path);
                return MI_RESULT_FAILED;
            }
#if defined(_MSC_VER)            
            Stprintf(filePath, MAX_URL_LENGTH, MI_T("%T\\localhost.mof"), path);
#else
            Stprintf(filePath, MAX_URL_LENGTH, MI_T("%T/localhost.mof"), path);
#endif
            *fileLocation = filePath;
            *directoryPath = path;
            return MI_RESULT_OK;
       }
   }
   return MI_RESULT_FAILED;
}

MI_Result  IssueGetModuleRequest( _In_z_ const MI_Char *configurationID, 
                                  _In_z_ const MI_Char *moduleName,
                                  _In_z_ const MI_Char *moduleVersion,
                                  _In_z_ const MI_Char *certificateID,
                                  _In_z_ const MI_Char *filePath,
                                  _In_z_ struct SSLOptions sslOptions,
                                  _Outptr_result_maybenull_z_  MI_Char** result,
                                  _Out_ MI_Uint32* getActionStatusCode,
                                  _In_reads_z_(URL_SIZE) const MI_Char *url,
                                  _In_ MI_Uint32 port,
                                  _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                  MI_Boolean bIsHttps,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char *outputResult = (MI_Char*)DSC_malloc((Tcslen(MI_T("OK"))+1) * sizeof(MI_Char), NitsHere());

    CURL *curl;
    CURLcode res;
    struct HeaderChunk headerChunk;
    struct Chunk dataChunk;
    char configurationUrl[MAX_URL_LENGTH];
    long responseCode;
    size_t i;
    char* checksumResponse = NULL;
    char* checksumAlgorithmResponse = NULL;

    *result = NULL;
    if( outputResult == NULL )
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    DSC_EventWriteGetDscDocumentWebDownloadManagerServerUrl(configurationID, url);
    Stprintf(outputResult,3, MI_T("OK"));
    
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (!curl)
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOINITIALIZE);
    }

    InitHeaderChunk(&headerChunk);
    dataChunk.data = (char *)malloc(1);
    dataChunk.size = 0;

    if (bIsHttps)
    {
        Snprintf(configurationUrl, MAX_URL_LENGTH, "https://%s:%d/%s/Module(ConfigurationId='%s',ModuleName='%s',ModuleVersion='%s')/ModuleContent", url, port, subUrl, configurationID, moduleName, moduleVersion);
        curl_easy_setopt(curl, CURLOPT_URL, configurationUrl);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        if (sslOptions.DoNotCheckCertificate == MI_TRUE)
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        }
    }
    else
    {
        Snprintf(configurationUrl, MAX_URL_LENGTH, "http://%s:%d/%s/Module(ConfigurationId='%s',ModuleName='%s',ModuleVersion='%s')/ModuleContent", url, port, subUrl, configurationID, moduleName, moduleVersion);
        curl_easy_setopt(curl, CURLOPT_URL, configurationUrl);
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerChunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataChunk);

    if (sslOptions.cipherList[0] != '\0')
    {
        res = curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, sslOptions.cipherList);
        if (res != CURLE_OK)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOSETCIPHERLIST);
        }
    }

    if (sslOptions.NoSSLv3 == MI_TRUE)
    {
        res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
        if (res != CURLE_OK)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CURLFAILEDTOSETNOSSLV3);
        }
    }

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        CleanupHeaderChunk(&headerChunk);
        free(dataChunk.data);
        DSC_free(outputResult);
        return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_CURLPERFORMFAILED, url, curl_easy_strerror(res));
    }      

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (responseCode != HTTP_SUCCESS_CODE)
    {
        MI_Char statusCodeValue[MAX_STATUSCODE_SIZE] = {0};
        *getActionStatusCode = GetConfigurationCommandFailure;
        CleanupHeaderChunk(&headerChunk);
        free(dataChunk.data);
        DSC_free(outputResult);
        Stprintf(statusCodeValue, MAX_STATUSCODE_SIZE, MI_T("%d"), responseCode);
        return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_SERVERHTTPERRORCODEMODULE, url, statusCodeValue);
    }

    for (i = 0; i < headerChunk.size; ++i)
    {
        if (checksumResponse != NULL && checksumAlgorithmResponse != NULL)
        {
            break;
        }

        if ( Tcscasecmp(headerChunk.headerKeys[i], "Checksum") == 0 )
        {
            checksumResponse = headerChunk.headerValues[i];
        }
        else if ( Tcscasecmp(headerChunk.headerKeys[i], "ChecksumAlgorithm") == 0 )
        {
            checksumAlgorithmResponse = headerChunk.headerValues[i];
        }
    }
    if (checksumResponse == NULL || checksumAlgorithmResponse == NULL)
    {
        *getActionStatusCode = InvalidChecksumAlgorithm;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_INVALIDRESPONSEFROMSERVER);
    }

    if( Tcscasecmp(checksumAlgorithmResponse, AllowedChecksumAlgorithm) != 0 )
    {      
        *getActionStatusCode = InvalidChecksumAlgorithm;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_INVALIDCHECKSUMALGORITHM);
    }
    
    if( dataChunk.size > 0 )
    {
        FILE *fp = File_OpenT(filePath, MI_T("a"));
        if(fp == NULL)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, 
                                       ID_PULL_CONFIGURATIONSAVEFAILED, filePath);
        }
        fwrite( dataChunk.data, 1, dataChunk.size, fp);
        File_Close(fp);
    }

    if( !ValidateChecksum(checksumResponse, filePath) )
    {
        DSC_EventWriteWebDownloadManagerGetDocChecksumValidation(NULL, NULL);
        *getActionStatusCode = ConfigurationChecksumValidationFailure;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CHECKSUMMISMATCH);
    }


    
    DSC_EventWriteLCMPullConfigurationChecksumValidationResult(configurationID, (MI_Uint32)MI_RESULT_OK);
  
    //Create checksumFile
    {
        MI_Char checksumFileName[MAX_URL_LENGTH];
        FILE *fp = NULL;
        Stprintf(checksumFileName, MAX_URL_LENGTH,MI_T("%s.checksum"), filePath);
        fp = File_OpenT(checksumFileName,MI_T("w"));
        if( fp != NULL )
        {
            fwrite(checksumResponse, 1, Strlen(checksumResponse), fp);
            File_Close(fp);
        }
        else
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            DSC_free(outputResult);
            return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULLGETCONFIGURATION_CHECKSUMSAVEFAILED, checksumFileName);            
        }
    }

    CleanupHeaderChunk(&headerChunk);
    free(dataChunk.data);

    *result = outputResult;
    DSC_EventWriteWebDownloadManagerGetDocGetCall(configurationID, *result );

    return MI_RESULT_OK;
}

MI_Result MI_CALL Pull_GetModules(const MI_Char *configurationID, 
                                  const MI_Char *certificateID,
                                  MI_Char* directoryPath,
                                  MI_Char* fileName,
                                  _In_z_ struct SSLOptions sslOptions,
                                  MI_Char** result,                               
                                  MI_Uint32* getActionStatusCode,
                                  MI_Boolean bAllowedModuleOverride,
                                  _In_reads_z_(URL_SIZE) const MI_Char *url,
                                  _In_ MI_Uint32 port,
                                  _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                  MI_Boolean bIsHttps,
                                  MI_Instance **extendedError)
{
    ModuleTable moduleTable;
    ModuleTableEntry* current;
    MI_Result r;
    int retval;
    char zipPath[MAX_URL_LENGTH];
    char stringBuffer[MAX_URL_LENGTH];

    moduleTable.first = NULL;
    r = GetModuleNameVersionTable(fileName, &moduleTable, extendedError);
    if (r != MI_RESULT_OK)
    {
        CleanupModuleTable(moduleTable);
        return r;
    }

    // moduleTable now has the modules we need to pull
    current = moduleTable.first;
    while (current != NULL)
    {
        Snprintf(zipPath, MAX_URL_LENGTH, "%s/%s_%s.zip", directoryPath, current->moduleName, current->moduleVersionClassTuple->moduleVersion);
        r = IssueGetModuleRequest(configurationID, 
                                  current->moduleName, 
                                  current->moduleVersionClassTuple->moduleVersion,
                                  certificateID,
                                  zipPath,
                                  sslOptions,
                                  result,
                                  getActionStatusCode,
                                  url,
                                  port,
                                  subUrl,
                                  bIsHttps,
                                  extendedError);

        if (r != MI_RESULT_OK)
        {
            CleanupModuleTable(moduleTable);
            return r;
        }

        Snprintf(stringBuffer, MAX_URL_LENGTH, "%s %s", "/opt/microsoft/dsc/Scripts/InstallModule.py", zipPath);
        retval = system(stringBuffer);
        
        if (retval != 0)
        {
            if (retval == -1 && errno == ECHILD)
            {
                // This is an OK condition.  We weren't able to find the child process to reap after it completes.
            }
            else
            {
                // Attempt to remove the module as a last resort.  If it fails too, a reinstall may be necessary.
                Snprintf(stringBuffer, MAX_URL_LENGTH, "%s %s", "/opt/microsoft/dsc/Scripts/RemoveModule.py", current->moduleName);
                retval = system(stringBuffer); 
                if ( retval == 0 || (retval == -1 && errno == ECHILD) )
                {
                    r = GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_INSTALLMODULEFAILED, current->moduleName, current->moduleVersionClassTuple->moduleVersion);
                }
                else
                {
                    r = GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_INSTALLMODULEANDREMOVEMODULEFAILED, current->moduleName, current->moduleVersionClassTuple->moduleVersion);
                }

                CleanupModuleTable(moduleTable);
                return r;
            }
        }

        current = current->next;
    }

    CleanupModuleTable(moduleTable);

    return MI_RESULT_OK;

}

MI_Result MI_CALL Pull_GetConfigurationWebDownloadManager(_In_ LCMProviderContext *lcmContext,
                                                          _In_ MI_Instance *metaConfig,
                                                          _In_opt_z_ MI_Char *partialConfigName,
                                                          _Outptr_result_maybenull_z_  MI_Char** mofFileName,
                                                          _Outptr_result_maybenull_z_  MI_Char** result,
                                                          _Out_ MI_Uint32* getActionStatusCode,
                                                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char *configurationID = NULL;
    MI_Char *certificateID = NULL;
    MI_Char *directoryPath = NULL;
    MI_Char *fileName = NULL;
    MI_Char url[URL_SIZE] = {0};
    MI_Char subUrl[SUBURL_SIZE] = {0};
    MI_Uint32 port = DEFAULT_SERVERPORT;
    MI_Boolean bIsHttps = MI_FALSE;
    MI_Value value;
    MI_Uint32 flags;
    MI_Boolean bAllowedModuleOverride;
    struct SSLOptions sslOptions;

    if( metaConfig == NULL )
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    r = GetRequestParam(metaConfig, partialConfigName, (MI_Char*)url, (MI_Char*)subUrl, &port, &bIsHttps, &configurationID, &certificateID, getActionStatusCode, extendedError);
    //Get meta configuration elements
    if( r != MI_RESULT_OK)
    {
        return r;
    }

    // Validate if URL was correct.
    if( url[0] == MI_T('\0') || subUrl[0] == MI_T('\0') )
    {
        DSC_free(configurationID);
        *getActionStatusCode = InvalidDownloadManagerCustomDataInMetaConfig;
        r = GetCimMIError( MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_INVALIDURLINCUSTOMDATA);
        return r;
    }    
    r = CreateTmpDirectoryPath(&directoryPath, &fileName);
    if( r != MI_RESULT_OK)
    {
        DSC_free(configurationID);
        r = GetCimMIError( r, extendedError, ID_LCMHELPER_CREATE_CONFDIR_FAILED);
        return r;
    }

    // Get our supported SSL options if there are any
    r = GetSSLOptions(&sslOptions, extendedError);
    if( r != MI_RESULT_OK)
    {
        DSC_free(configurationID);
        DSC_free(fileName);  
        free(directoryPath);
        return r;
    }

    DSC_EventWriteLCMPullGetConfigAttempt( webPulginName, configurationID);    
    // Issue Get Action Request
    r = IssueGetConfigurationRequest( configurationID,  certificateID, fileName, sslOptions, result, 
                    getActionStatusCode, url, port, subUrl, bIsHttps, extendedError);
      
    if( r != MI_RESULT_OK)
    {
        DSC_free(configurationID);
        DSC_free(fileName);  
        free(directoryPath);
        return r;
    }

    r = MI_Instance_GetElement(metaConfig, MSFT_DSCMetaConfiguration_AllowModuleOverwrite, &value, NULL, &flags, NULL);
    if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) && value.boolean == MI_TRUE)
    {
        bAllowedModuleOverride = MI_TRUE;
    }

    r = Pull_GetModules(configurationID,  certificateID, directoryPath, fileName, sslOptions, result, getActionStatusCode, bAllowedModuleOverride, url, port, subUrl, bIsHttps, extendedError);
    if( r != MI_RESULT_OK)
    {
         DSC_free(configurationID);
         free(directoryPath);
         DSC_free(fileName);
         return r;
    }

    DSC_free(configurationID);
    free(directoryPath);
    *mofFileName = fileName;
    DSC_EventWriteLCMPullGetConfigSuccess(webPulginName);    
    return MI_RESULT_OK;
}


                                 
MI_Result MI_CALL Pull_GetActionWebDownloadManager(_In_ LCMProviderContext *lcmContext,
                                                   _In_ MI_Instance *metaConfig,
                                                   _In_opt_z_ MI_Char *partialConfigName,
                                                   _In_z_ const MI_Char *checkSum,
                                                   _In_ MI_Boolean complianceStatus,
                                                   _In_ MI_Uint32 lastGetActionStatusCode,
                                                   _Outptr_result_maybenull_z_  MI_Char** result,
                                                   _Out_ MI_Uint32* getActionStatusCode,
                                                   _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char *configurationID = NULL;
    MI_Char *certificateID = NULL;
    MI_Char url[URL_SIZE] = {0};
    MI_Char subUrl[SUBURL_SIZE] = {0};
    MI_Uint32 port = DEFAULT_SERVERPORT;
    MI_Boolean bIsHttps = MI_FALSE;
    MI_Char *tmpChecksum = NULL;
    struct SSLOptions sslOptions;
    
    if( metaConfig == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    tmpChecksum = (MI_Char*)DSC_malloc( (Tcslen(checkSum) +1) * sizeof(MI_Char), NitsHere());
    if( tmpChecksum == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memcpy(tmpChecksum, checkSum, (Tcslen(checkSum) + 1)* sizeof(MI_Char));

    r = GetRequestParam(metaConfig, partialConfigName, (MI_Char*)url, (MI_Char*)subUrl, &port, &bIsHttps, &configurationID, &certificateID, getActionStatusCode, extendedError);
    if( r != MI_RESULT_OK)
    {
        DSC_free(tmpChecksum);
        return r;
    }

    // Validate if URL was correct.
    if( url[0] == MI_T('\0') || subUrl[0] == MI_T('\0') )
    {
        DSC_free(configurationID);
        *getActionStatusCode = InvalidDownloadManagerCustomDataInMetaConfig;
        r = GetCimMIError( MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_INVALIDURLINCUSTOMDATA);
        DSC_free(tmpChecksum);
        return r;
    }    

    // Get our supported SSL options if there are any
    r = GetSSLOptions(&sslOptions, extendedError);
    if( r != MI_RESULT_OK)
    {
        DSC_free(configurationID);
        DSC_free(tmpChecksum);
        return r;
    }

    DSC_EventWriteLCMPullGetActionAttempt( webPulginName, configurationID, tmpChecksum, complianceStatus);    
    // Issue Get Action Request
    r = IssueGetActionRequest( configurationID, certificateID, tmpChecksum, sslOptions, complianceStatus, lastGetActionStatusCode, result, 
                    getActionStatusCode, url, port, subUrl, bIsHttps, extendedError);

    DSC_free(configurationID);
    DSC_free(tmpChecksum);
    if( r != MI_RESULT_OK)
    {
        return r;
    }     
    DSC_EventWriteLCMPullGetActionSuccess(*result, webPulginName);    
    
    return MI_RESULT_OK;
}

static int CompareVersions(MI_Char* a, MI_Char* b)
{
    MI_Char* a_token;
    MI_Char* a_next_token;
    long a_val;

    MI_Char* b_token;
    MI_Char* b_next_token;
    long b_val;

    a_token = Strtok(a, ".", &a_next_token);
    b_token = Strtok(b, ".", &b_next_token);

    if (a_token == NULL || b_token == NULL)
    {
        if (a_token == NULL && b_token == NULL)
        {
            return 0;
        }
        else if (a_token == NULL)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    a_val = Strtol(a,0,10);
    b_val = Strtol(b,0,10);
    if ( a_val != b_val )
    {
        return a_val - b_val;
    }
    else
    {
        return CompareVersions(a_next_token, b_next_token);
    }
}

static int IsModuleInstalled(MI_Char* moduleName, MI_Char* moduleVersion)
{
    int bytesRead;
    size_t tmpLength;
    MI_Char buffer[MAX_URL_LENGTH];
    MI_Char buffer2[MAX_URL_LENGTH];
    FILE * fp;

    if (Tcscasecmp(MI_T("nx"), moduleName) == 0)
    {
        // The nx module is installed by default
        return 1;
    }

    Snprintf(buffer, MAX_URL_LENGTH, "/opt/microsoft/dsc/modules/%s/VERSION", moduleName);
    
    fp = File_OpenT(buffer, MI_T("r"));
    if( fp == NULL )
    {
        return 0;
    }

    bytesRead = fread(buffer, 1, MAX_URL_LENGTH, fp);
    buffer[bytesRead] = '\0';

    File_Close(fp);

    if (bytesRead == 0)
    {
        // Unable to read VERSION.
        return 0;
    }

    if (bytesRead == MAX_URL_LENGTH)
    {
        // Invalid version size.  It shouldn't be this long!
        return 0;
    }
    
    // Since we're going to be tokenizing moduleVersion, we should make a copy of it.
    tmpLength = Tcslen(moduleVersion) + 1;
    memcpy(buffer2, moduleVersion, tmpLength);

    // If the installed version (buffer) is less than the parsed moduleVersion, we need the latest version.    
    if (CompareVersions(buffer, buffer2) < 0)
    {
        return 0;
    }

    return 1;
}

// Remove from the table modules that are installed with a version greater than or equal to the requested version
static MI_Result FilterUsingCachedModules(ModuleTable* table)
{
    ModuleTableEntry** pointsToCurrent = &table->first;
    ModuleTableEntry* current;
    ModuleTableEntry* next;

    while (*pointsToCurrent != NULL)
    {
        current = *pointsToCurrent;
        next = current->next;

        // if module is installed, remove it from list
        if ( IsModuleInstalled( current->moduleName, current->moduleVersionClassTuple->moduleVersion ) == 1 )
        {
            *pointsToCurrent = next;
            CleanupModuleTableEntry(current);
        }
        else
        {
            pointsToCurrent = &current->next;
        }
    }

    return MI_RESULT_OK;
}

static MI_Result GetModuleNameVersionTable(MI_Char* mofFileLocation, 
                                           ModuleTable* table,
                                           _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_InstanceA *miInstanceArray = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 contentSize;
    MI_Uint32 readBytes;
    MI_ClassA miClassArray = {0};
    MI_Application *miApp = NULL;
    MI_Deserializer deserializer;
    MI_OperationOptions options;
    MI_Value moduleName;
    MI_Value moduleVersion;
    int i;    
    size_t tmpLength;
    ModuleTableEntry* current;
    ModuleTableEntry** foundEntry;
    ModuleClassList** foundClassEntry;
    
    miApp = (MI_Application *) DSC_malloc( sizeof(MI_Application), NitsHere());
    memset(miApp,  0, sizeof(MI_Application));
    r = DSC_MI_Application_Initialize(0, NULL, NULL, miApp);   
    if( r != MI_RESULT_OK)
    {
        DSC_free(miApp);
        return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULL_INITIALIZEMODULETABLEFAILED, "App Init failed");
    }      
    
    memset(&deserializer, 0, sizeof(MI_Deserializer));    
    memset(&options, 0, sizeof(MI_OperationOptions));

    r = DSC_MI_Application_NewOperationOptions(miApp, MI_FALSE, &options);
    if (r != MI_RESULT_OK)
    {
        DSC_free(miApp);
        return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULL_INITIALIZEMODULETABLEFAILED, "Setting NewOperationOptions failed");
    }

    r = DSC_MI_OperationOptions_SetString(&options, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, MOFCODEC_SCHEMA_VALIDATION_IGNORE, 0);
    if (r!=MI_RESULT_OK )
    {
        DSC_free(miApp);
        return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULL_INITIALIZEMODULETABLEFAILED, "Setting OperationOptions string Failed");
    }

    r = DSC_MI_Application_NewDeserializer_Mof(miApp, 0, MOFCODEC_FORMAT, &deserializer);
    if (r!=MI_RESULT_OK )
    {
        DSC_free(miApp);
        return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULL_INITIALIZEMODULETABLEFAILED, "Creating New Deserializer Failed");
    }

    r = ReadFileContent(mofFileLocation, &pbuffer, &contentSize, &extendedError);
    if(r != MI_RESULT_OK)
    {
        DSC_free(miApp);
        return r;
    }   
    miClassArray.size = 0;
    miClassArray.data = NULL;

    r = MI_Deserializer_DeserializeInstanceArray(&deserializer, 0, &options, 0, pbuffer, contentSize, &miClassArray, &readBytes, &miInstanceArray, extendedError);
    if (r != MI_RESULT_OK)
    {
        return r;
    }

    if(pbuffer)
    {
        DSC_free(pbuffer);
        pbuffer = NULL;
    }

    
    for (i = 0; i < miInstanceArray->size; ++i)
    {
        // compare classname with BASE_DOCUMENT_CLASSNAME.  Skip if same
        if ( Tcscasecmp( miInstanceArray->data[i]->classDecl->name , BASE_DOCUMENT_CLASSNAME) != 0 )
        {

            r = DSC_MI_Instance_GetElement(miInstanceArray->data[i], MI_T("ModuleName"), &moduleName, NULL, NULL, NULL);
            if (r != MI_RESULT_OK )
            {
                continue;
            }

            r = DSC_MI_Instance_GetElement(miInstanceArray->data[i], MI_T("ModuleVersion"), &moduleVersion, NULL, NULL, NULL);
            if (r != MI_RESULT_OK )
            {
                continue;
            }

            if ( IsModuleVersionValidFormat(moduleVersion.string) == 1 )
            {
                
                // foundEntry will be a pointer to the "next" or "first" pointer that points to the ModuleTableEntry we want
                foundEntry = ModuleTableContainsKey(table, moduleName.string);
                if ( *foundEntry != NULL )
                {
                    // Find VersionClass tuple, append new class if necessary, update version if necessary

                    // compare version? Windows doesn't.
                    // current->moduleVersionClassTuple->moduleVersion

                    // See if class is in the class list.  If it isn't, add it. if it is, do nothing
                    foundClassEntry = ClassListContainsClass(&current->moduleVersionClassTuple->first, miInstanceArray->data[i]->classDecl->name );
                    if (*foundClassEntry == NULL)
                    {
                        *foundClassEntry = (ModuleClassList*) DSC_malloc(sizeof(ModuleClassList), NitsHere());
                        (*foundClassEntry)->next = NULL;

                        // Copy class name
                        tmpLength = Tcslen(miInstanceArray->data[i]->classDecl->name) + 1;
                        (*foundClassEntry)->moduleClass = (MI_Char*)DSC_malloc(sizeof(MI_Char) * tmpLength, NitsHere());
                        memcpy((*foundClassEntry)->moduleClass, miInstanceArray->data[i]->classDecl->name, tmpLength);
                    }
                }
                else
                {
                    *foundEntry = (ModuleTableEntry*) DSC_malloc(sizeof(ModuleTableEntry), NitsHere());
                    current = *foundEntry;
                    current->next = NULL;

                    // Copy module name
                    tmpLength = Tcslen(moduleName.string) + 1;
                    current->moduleName = (MI_Char*)DSC_malloc(sizeof(MI_Char) * tmpLength, NitsHere());
                    memcpy(current->moduleName, moduleName.string, tmpLength);

                    current->moduleVersionClassTuple = (ModuleVersionClassTuple*) DSC_malloc(sizeof(ModuleVersionClassTuple), NitsHere());

                    // Copy module version
                    tmpLength = Tcslen(moduleVersion.string) + 1;
                    current->moduleVersionClassTuple->moduleVersion = (MI_Char*)DSC_malloc(sizeof(MI_Char) * tmpLength, NitsHere());
                    memcpy(current->moduleVersionClassTuple->moduleVersion, moduleVersion.string, tmpLength);

                    current->moduleVersionClassTuple->first = (ModuleClassList*) DSC_malloc(sizeof(ModuleClassList), NitsHere());
                    current->moduleVersionClassTuple->first->next = NULL;
                    
                    // Copy class name
                    tmpLength = Tcslen(miInstanceArray->data[i]->classDecl->name) + 1;
                    current->moduleVersionClassTuple->first->moduleClass = (MI_Char*)DSC_malloc(sizeof(MI_Char) * tmpLength, NitsHere());
                    memcpy(current->moduleVersionClassTuple->first->moduleClass, miInstanceArray->data[i]->classDecl->name, tmpLength);

                }
            }
            else
            {
                // Error: Invalid version for module.
                MI_Deserializer_Close(&deserializer);
                MI_OperationOptions_Delete(&options);
                CleanUpDeserializerInstanceCache(miInstanceArray);
                return GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULL_INVALIDMODULEVERSION, moduleVersion.string, moduleName.string);
            }
        }
    }

    r = FilterUsingCachedModules(table);

    MI_Deserializer_Close(&deserializer);
    MI_OperationOptions_Delete(&options);

    CleanUpDeserializerInstanceCache(miInstanceArray);

    return MI_RESULT_OK;
}



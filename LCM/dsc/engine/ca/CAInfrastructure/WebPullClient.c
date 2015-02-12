#include <MI.h>
#include "DSC_Systemcalls.h"
//#include "LocalConfigManagerHelperForCA.h"
#include "EngineHelper.h"
#include "Resources_LCM.h"
#include "http/httpcommon.h"
#include "http/httpclient.h"
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
                                           ModuleTable* table);
void HandleStatus(_In_ HttpClient *http, _In_ void *callbackData, MI_Result result);
MI_Boolean HandleResponse( _In_ HttpClient *http, _In_ void *callbackData, _In_ const HttpClientResponseHeader *headers,
                           MI_Sint64 contentSize, MI_Boolean lastChunk, _In_ Page**data);

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
                                  _Outptr_opt_result_maybenull_    MI_Instance **credential,
                                  _Inout_    MI_InstanceA *customParam,
                                  _Outptr_result_maybenull_z_ MI_Char **configurationID,
                                  _Outptr_result_maybenull_z_ MI_Char **certificateID,
                                  _Out_ MI_Uint32* getActionStatusCode,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    MI_Value value;
    MI_Uint32 flags;
    MI_Uint32 xCount;
    *credential = NULL;
    *extendedError = NULL;
    *getActionStatusCode = Success;
    *configurationID = NULL;
    *certificateID = NULL;

     // 1. Get Credential.
    r = MI_Instance_GetElement(metaConfig, MetaConfig_Credential, &value, NULL, &flags, NULL);
    if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
    {
        *credential = value.instance;
    }     

    // 2. Get custom arguments.
    r = MI_Instance_GetElement(metaConfig, MetaConfigDownloadManagerCustomData, &value, NULL, &flags, NULL);
    if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
    {
        customParam->size = value.instancea.size;
        customParam->data = value.instancea.data;
    }      
    // 3. Get Configuration ID.
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


MI_Result ValidateGetActionResult(_In_ RequestContainer *requestParam,
                                         _In_z_ const MI_Char * url,
                                         _Inout_ MI_Uint32* getActionStatusCode,
                                         _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    // We got something from server, validate it.
    if(extendedError)
        *extendedError  = NULL;
    if( requestParam->internalError != NULL)
    {
        *getActionStatusCode = requestParam->statusCode;
        if( requestParam->u.action.getActionStatus) 
            DSC_free(requestParam->u.action.getActionStatus);   
        *extendedError = requestParam->internalError;
        return requestParam->internalErrorResult;
    }
    if( requestParam->httpResponseResult != MI_RESULT_OK || requestParam->statusCode != Success)
    {
        MI_Uint32 response = requestParam->httpResponseResult == MI_RESULT_OK ? MI_RESULT_FAILED : requestParam->httpResponseResult;        
        *getActionStatusCode = GetDscActionCommandFailure;
        if( requestParam->u.action.getActionStatus) 
            DSC_free(requestParam->u.action.getActionStatus);
        
        if( requestParam->httpError != HTTP_SUCCESS_CODE )
        {
            MI_Char statusCodeValue[MAX_STATUSCODE_SIZE] = {0};
            Stprintf(statusCodeValue, MAX_STATUSCODE_SIZE, MI_T("%d"), requestParam->httpError);
            r = GetCimMIError2Params( response, extendedError, ID_PULLGETACTION_BADRESPONSE, statusCodeValue, url);
            return r;
        }        
        return GetCimMIError1Param(response, extendedError, ID_PULL_GETACTIONFAILED, webPulginName); 
    }
    if( requestParam->u.action.getActionStatus == NULL)
    {
        MI_Uint32 response = requestParam->httpResponseResult == MI_RESULT_OK ? MI_RESULT_FAILED : requestParam->httpResponseResult;    
        *getActionStatusCode = GetDscActionCommandFailure;
        return GetCimMIError1Param(response, extendedError, ID_PULL_GETACTIONFAILED, webPulginName);         
    }

    // output should be either "OK" or "GETCONFIGURATION"
    if (! (Strcasecmp( requestParam->u.action.getActionStatus, GetActionResultOk) == 0 ||
        Strcasecmp( requestParam->u.action.getActionStatus, GetActionResultGetConfiguration) == 0 ) )
    {
        MI_Char *actionStatus = NULL;
#if defined(_MSC_VER)
        AsciiToUCS2(requestParam->u.action.getActionStatus, &actionStatus);

#else
        actionStatus = requestParam->u.action.getActionStatus;
#endif
        *getActionStatusCode = GetDscActionCommandFailure;
        r = GetCimMIError2Params(MI_RESULT_INVALID_PARAMETER, extendedError, ID_PULL_GETACTIONUNEXPECTEDRESULT, actionStatus, url);
#if defined(_MSC_VER)        
        DSC_free(actionStatus);
#endif
        DSC_free(requestParam->u.action.getActionStatus);
        return r;
    }    
    return MI_RESULT_OK;
}


MI_Result ValidateGetConfigurationResult(_In_ RequestContainer *requestParam,
                                         _In_z_ const MI_Char * url,
                                         _Inout_ MI_Uint32* getActionStatusCode,
                                         _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    if(extendedError)
        *extendedError  = NULL;    
    // We got something from server, validate it.
    if( requestParam->internalError != NULL)
    {
        *getActionStatusCode = requestParam->statusCode;
        if( requestParam->u.config.checkSumAlgorithm) 
            DSC_free(requestParam->u.config.checkSumAlgorithm);
        if( requestParam->u.config.checkSum)
            DSC_free(requestParam->u.config.checkSum);   

        *extendedError = requestParam->internalError;
        return requestParam->internalErrorResult;
    }    
    if( requestParam->httpResponseResult != MI_RESULT_OK || requestParam->statusCode != Success)
    {
        MI_Uint32 response = requestParam->httpResponseResult == MI_RESULT_OK ? MI_RESULT_FAILED : requestParam->httpResponseResult;    
        *getActionStatusCode = GetConfigurationCommandFailure;
        if( requestParam->u.config.checkSumAlgorithm) 
            DSC_free(requestParam->u.config.checkSumAlgorithm);
        if( requestParam->u.config.checkSum)
            DSC_free(requestParam->u.config.checkSum);   

        if( requestParam->httpError != HTTP_SUCCESS_CODE )
        {
            MI_Char statusCodeValue[MAX_STATUSCODE_SIZE] = {0};             
            Stprintf(statusCodeValue, MAX_STATUSCODE_SIZE, MI_T("%d"), requestParam->httpError);
            r = GetCimMIError2Params(response , extendedError, ID_PULLGETCONFIGURATION_BADRESPONSE, statusCodeValue, url);    
            return r;            
        }
        return GetCimMIError1Param(response, extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);   
    }    

    if( requestParam->u.config.checkSumAlgorithm == NULL || requestParam->u.config.checkSum == NULL)
    {
        MI_Uint32 resourceId = requestParam->u.config.checkSumAlgorithm == NULL ? ID_PULLGETCONFIGURATION_NULLCHECKSUMALGORITHM : ID_PULLGETCONFIGURATION_NULLCHECKSUM;       
        *getActionStatusCode = GetConfigurationCommandFailure;
        if( requestParam->u.config.checkSumAlgorithm) 
            DSC_free(requestParam->u.config.checkSumAlgorithm);
        if( requestParam->u.config.checkSum)
            DSC_free(requestParam->u.config.checkSum);   
        r = GetCimMIError1Param(MI_RESULT_FAILED, extendedError, resourceId, url);    
        return r;
    }
    // Check checksum algorithm. 
    if( Tcscasecmp(requestParam->u.config.checkSumAlgorithm, AllowedChecksumAlgorithm) != 0 )
    {             
        *getActionStatusCode = InvalidChecksumAlgorithm;
        GetCimMIError2Params(MI_RESULT_FAILED, extendedError, ID_PULLGETCONFIGURATION_INVALIDCHECKSUMALGORITHM, url, requestParam->u.config.checkSumAlgorithm);                
        if( requestParam->u.config.checkSumAlgorithm) 
            DSC_free(requestParam->u.config.checkSumAlgorithm);
        if( requestParam->u.config.checkSum)
            DSC_free(requestParam->u.config.checkSum);   
        return MI_RESULT_FAILED;
    }
    //Validate checksum
    if( !ValidateChecksum(requestParam->u.config.checkSum, requestParam->u.config.directoryPath) )
    {
        DSC_EventWriteWebDownloadManagerGetDocChecksumValidation(NULL, NULL);
        *getActionStatusCode = ConfigurationChecksumValidationFailure;
        if( requestParam->u.config.checkSumAlgorithm) 
            DSC_free(requestParam->u.config.checkSumAlgorithm);
        if( requestParam->u.config.checkSum)
            DSC_free(requestParam->u.config.checkSum);               
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_PULL_CHECKSUMMISMATCH);
    }
    return MI_RESULT_OK;
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

#if defined(_MSC_VER)

MI_Char *GetSystemUuid()
{
    MI_Application app = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Char *resultSystemUuid = NULL;

    r = DSC_MI_Application_Initialize(0, NULL, NULL, &app);   
    if( r != MI_RESULT_OK)
    {
       return resultSystemUuid;
    }  

    r = DSC_MI_Application_NewSession(&app, NULL, NULL, NULL, NULL, NULL, &session);
    if (r != MI_RESULT_OK)
    {
        MI_Application_Close(&app);
       return resultSystemUuid;
    }        
    {
       const MI_Instance *resultInstance = NULL;
        MI_Boolean moreResults = MI_TRUE;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;
        MI_Value value;
        MI_Uint32 flags;
        MI_Session_EnumerateInstances(&session, 0, NULL, MI_T("root\\cimv2"), MI_T("Win32_ComputerSystemProduct"), MI_FALSE, NULL, &operation);
        r = MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        // We are interested in only 1st instance.
        if( r == MI_RESULT_OK && result == MI_RESULT_OK && resultInstance != NULL )
        {
            r = MI_Instance_GetElement(resultInstance, MI_T("UUID"), &value, NULL, &flags, NULL);
            if( r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) )
            {
                resultSystemUuid = (MI_Char*)DSC_malloc( (Tcslen(value.string)+1)* sizeof(MI_Char), NitsHere());
                if( resultSystemUuid )
                    memcpy(resultSystemUuid, value.string, (Tcslen(value.string)+1)* sizeof(MI_Char));
            }
        }
        MI_Operation_Close(&operation);
        MI_Session_Close(&session, NULL, NULL);
        MI_Application_Close(&app);
    }
    return resultSystemUuid;
    
}


void ProcessResponseHeaders( _In_ RequestContainer *requestParam, void *info, DWORD length)
{
    DWORD bufferLength = 2048;
    MI_Char buffer[2048] = {0};
    if(!WinHttpQueryHeaders((HINTERNET)requestParam->httpRequest, WINHTTP_QUERY_CONTENT_TYPE, WINHTTP_HEADER_NAME_BY_INDEX, buffer, &bufferLength, WINHTTP_NO_HEADER_INDEX) )
    {
            requestParam->internalErrorResult = GetCimWin32Error1Param(GetLastError(), &requestParam->internalError, 
                        ID_PULL_GETACTIONFAILED, webPulginName);
            requestParam->statusCode = GetDscActionCommandFailure;      
            return;        
    }
    //buffer[ Strlen(buffer)] = '\0';
    if( requestParam->serverOperation == OPERATION_GETACTION )
    {
        if( !ValidateContentTypeHeader(buffer, bufferLength, MI_T("application/json")))
        {
            requestParam->internalErrorResult = GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, 
                        ID_PULL_GETACTIONFAILED, webPulginName);
            requestParam->statusCode = GetDscActionCommandFailure;      
            return;            
        }
    }
    else if( requestParam->serverOperation == OPERATION_GETCONFIGURATION )
    {
        MI_Uint32 dwSize = 0;      
        if( !ValidateContentTypeHeader(buffer, bufferLength, MI_T("application/octet-stream")))
        {
            requestParam->internalErrorResult = GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, 
                        ID_PULL_GETACTIONFAILED, webPulginName);
            requestParam->statusCode = GetDscActionCommandFailure;      
            return;            
        }        
        // Get Checksum value;
        if(!WinHttpQueryHeaders((HINTERNET)requestParam->httpRequest, WINHTTP_QUERY_CUSTOM, checkSumName, NULL, (LPDWORD)&dwSize , WINHTTP_NO_HEADER_INDEX))
        {
            if( GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            {
                // Caller will validate the result, ignore it here.
                return;
            }
        }
        requestParam->u.config.checkSum = (MI_Char*) DSC_malloc(dwSize+sizeof(MI_Char), NitsHere());
        if( requestParam->u.config.checkSum == NULL)
        {
            requestParam->statusCode = GetConfigurationCommandFailure;
            requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, ID_ENGINEHELPER_MEMORY_ERROR);
            return;
        }
        if( !WinHttpQueryHeaders((HINTERNET)requestParam->httpRequest, WINHTTP_QUERY_CUSTOM, checkSumName, requestParam->u.config.checkSum, 
                (LPDWORD)&dwSize , WINHTTP_NO_HEADER_INDEX))
        {
            DSC_free(requestParam->u.config.checkSum);
            requestParam->u.config.checkSum = NULL;
            // Caller will validate the result, ignore it here.
        }  

        // Get Checksum algorithm;
        if(!WinHttpQueryHeaders((HINTERNET)requestParam->httpRequest, WINHTTP_QUERY_CUSTOM, checksumAlgorithmName, NULL, (LPDWORD)&dwSize , WINHTTP_NO_HEADER_INDEX))
        {
            if( GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            {
                // Caller will validate the result, ignore it here.
                return;
            }
        }
        requestParam->u.config.checkSumAlgorithm = (MI_Char*) DSC_malloc(dwSize+ sizeof(MI_Char), NitsHere());
        if( requestParam->u.config.checkSumAlgorithm == NULL)
        {
            requestParam->statusCode = GetConfigurationCommandFailure;
            requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, ID_ENGINEHELPER_MEMORY_ERROR);
            return;
        }
        if( !WinHttpQueryHeaders((HINTERNET)requestParam->httpRequest, WINHTTP_QUERY_CUSTOM, checksumAlgorithmName, requestParam->u.config.checkSumAlgorithm, 
                (LPDWORD)&dwSize , WINHTTP_NO_HEADER_INDEX))
        {
            DSC_free(requestParam->u.config.checkSumAlgorithm);
            requestParam->u.config.checkSumAlgorithm = NULL;
            return;
            // Caller will validate the result, ignore it here.
        }           
    }
}

void ProcessResponseData( _In_ RequestContainer *requestParam, void *info, DWORD length)
{
    if( requestParam->serverOperation == OPERATION_GETACTION )
    {
        char *buffer = DSC_malloc(*((LPDWORD)info), NitsHere());
        if( buffer == NULL)
        {
            requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, 
                        ID_ENGINEHELPER_MEMORY_ERROR);
            requestParam->statusCode = GetDscActionCommandFailure;
            return;

        }
        if (!WinHttpReadData((HINTERNET)requestParam->httpRequest, buffer, *((LPDWORD)info), NULL))
        {
            DSC_free(buffer);
            requestParam->internalErrorResult = GetCimWin32Error1Param(GetLastError(), &requestParam->internalError, 
                        ID_PULL_GETACTIONFAILED, webPulginName);
            requestParam->statusCode = GetDscActionCommandFailure;      
            return;            
        }
        if( !GetGetActionData(buffer, *((LPDWORD)info), &requestParam->u.action.getActionStatus) )
        {
            GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, ID_PULL_GETACTIONFAILED, webPulginName);  
            DSC_free(buffer);
            requestParam->statusCode = GetDscActionCommandFailure;
            return;
        }
        DSC_free(buffer);
        if( requestParam->u.action.getActionStatus == NULL )
        {
            requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, 
                        ID_ENGINEHELPER_MEMORY_ERROR);
            requestParam->statusCode = GetDscActionCommandFailure;
            return;
            
        }        
    }
    else if( requestParam->serverOperation == OPERATION_GETCONFIGURATION )
    {
        size_t dataSize =*((LPDWORD)info);
        char *buffer = DSC_malloc(*((LPDWORD)info), NitsHere());
        if( buffer == NULL)
        {
            requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, 
                        ID_ENGINEHELPER_MEMORY_ERROR);
            requestParam->statusCode = GetConfigurationCommandFailure;
            return;

        }
        if (!WinHttpReadData((HINTERNET)requestParam->httpRequest, buffer, *((LPDWORD)info), NULL))
        {
            DSC_free(buffer);
            requestParam->internalErrorResult = GetCimWin32Error1Param(GetLastError(), &requestParam->internalError, 
                        ID_PULLGETCONFIGURATIONFAILED, webPulginName);
            requestParam->statusCode = GetConfigurationCommandFailure;      
            return;            
        }   
        {
            FILE *fp = File_OpenT(requestParam->u.config.directoryPath, MI_T("a"));
            if(fp == NULL)
            {
                DSC_free(buffer);
                requestParam->internalErrorResult = GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, 
                                            ID_PULL_CONFIGURATIONSAVEFAILED, requestParam->u.config.directoryPath);
                requestParam->statusCode = GetConfigurationCommandFailure;
                DSC_EventWriteWebDownloadManagerGetDocFileSave(NULL, requestParam->u.config.directoryPath);
                return;            
            }
            fwrite( (char*)buffer, 1, dataSize, fp);
            File_Close(fp);        
        }
        
    }    
}


void CALLBACK WinHTTP_Callback(HINTERNET handle, DWORD_PTR context, DWORD code, void *info, DWORD length)
{
    RequestContainer *requestParam = (RequestContainer *) context;
    if (code == WINHTTP_CALLBACK_STATUS_DATA_AVAILABLE)
    {
        if( requestParam->statusCode == Success)
            ProcessResponseData(requestParam, info, length);
        Sem_Post(&requestParam->httpRequestDoneEvent, 1 );        
    }
    else if (code == WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE)
    {
        ProcessResponseHeaders(requestParam, info, length);
        // ask for data
        if(!WinHttpQueryDataAvailable((HINTERNET)requestParam->httpRequest, NULL) )
        {
            if( requestParam->serverOperation == OPERATION_GETACTION )
            {
                requestParam->internalErrorResult = GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, 
                            ID_PULL_GETACTIONFAILED, webPulginName);
                requestParam->statusCode = GetDscActionCommandFailure;      
            }
            else
            {
                requestParam->internalErrorResult = GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, 
                            ID_PULLGETCONFIGURATIONFAILED, webPulginName);
                requestParam->statusCode = GetConfigurationCommandFailure;                   
            }
            return;
        }        
        
    }
    else if (code == WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE)
    {
        // Ask for response
        if(!WinHttpReceiveResponse((HINTERNET)requestParam->httpRequest, NULL))
        {
            // Error condition
        }
    }
    else if (code == WINHTTP_CALLBACK_STATUS_READ_COMPLETE)
    {
        // Successfully read.
        // Sem_Post(&requestParam->httpRequestDoneEvent, 1 );
    }
    else if (code == WINHTTP_CALLBACK_STATUS_CLOSE_COMPLETE)
    {
        //Sem_Post(&requestParam->httpRequestDoneEvent, 1 );        
    }
    else if (code == WINHTTP_CALLBACK_STATUS_REQUEST_ERROR)
    {        
        WINHTTP_ASYNC_RESULT *result = (WINHTTP_ASYNC_RESULT*)info;
        if( requestParam->statusCode == Success)
        {
            if( requestParam->serverOperation == OPERATION_GETACTION )
            {
                requestParam->statusCode = GetDscActionCommandFailure;
                GetCimWin32Error1Param(result->dwError, &requestParam->internalError, ID_PULL_GETACTIONFAILED, webPulginName);
            }
            else if( requestParam->serverOperation == OPERATION_GETCONFIGURATION )
            {
                requestParam->statusCode = GetConfigurationCommandFailure;
                 GetCimWin32Error1Param(result->dwError, &requestParam->internalError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);
            }
            Sem_Post(&requestParam->httpRequestDoneEvent, 1 );        
        }
    }
    else if ( code == WINHTTP_CALLBACK_STATUS_SECURE_FAILURE)
    {
        // security error
        if( requestParam->statusCode == Success)
        {
            if( requestParam->serverOperation == OPERATION_GETACTION )
            {
                requestParam->statusCode = GetDscActionCommandFailure;
                GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, ID_PULL_GETACTIONFAILED, webPulginName);
            }
            else if( requestParam->serverOperation == OPERATION_GETCONFIGURATION )
            {
                requestParam->statusCode = GetConfigurationCommandFailure;
                 GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);
            }            
            Sem_Post(&requestParam->httpRequestDoneEvent, 1 );  
        }
    }
    // ignore these status
    else if( code == WINHTTP_CALLBACK_STATUS_RESOLVING_NAME ||
             code == WINHTTP_CALLBACK_STATUS_NAME_RESOLVED ||
             code == WINHTTP_CALLBACK_STATUS_CONNECTING_TO_SERVER ||
             code == WINHTTP_CALLBACK_STATUS_CONNECTED_TO_SERVER ||
             code == WINHTTP_CALLBACK_STATUS_SENDING_REQUEST || 
             code == WINHTTP_CALLBACK_STATUS_REQUEST_SENT ||
             code == WINHTTP_CALLBACK_STATUS_CLOSING_CONNECTION ||
             code == WINHTTP_CALLBACK_STATUS_CONNECTION_CLOSED ||
             code == WINHTTP_CALLBACK_STATUS_HANDLE_CREATED ||
             code == WINHTTP_CALLBACK_STATUS_HANDLE_CLOSING ||
             code == WINHTTP_CALLBACK_STATUS_INTERMEDIATE_RESPONSE ||
             code == WINHTTP_CALLBACK_STATUS_NAME_RESOLVED ||
             code == WINHTTP_CALLBACK_STATUS_READ_COMPLETE ||
             code == WINHTTP_CALLBACK_STATUS_RECEIVING_RESPONSE ||
             code == WINHTTP_CALLBACK_STATUS_REDIRECT || 
             code == WINHTTP_CALLBACK_STATUS_REQUEST_SENT ||
             code == WINHTTP_CALLBACK_STATUS_RESPONSE_RECEIVED ||
             code == WINHTTP_CALLBACK_STATUS_WRITE_COMPLETE ||
             code == WINHTTP_CALLBACK_STATUS_GETPROXYFORURL_COMPLETE )
    {
    }
             
}

MI_Result AddCertificateToRequest(HINTERNET handle, _In_z_ const MI_Char *certificateID, _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    HCERTSTORE hStoreHandle = NULL;
    PCCERT_CONTEXT pCert = NULL;
    CRYPT_DATA_BLOB blob;
    DWORD dwBinaryLen = 0;
    BYTE* pbHashBlob = NULL;
    if(extendedError)
        *extendedError = NULL;

    if(CryptStringToBinary(certificateID, 0, CRYPT_STRING_HEX, NULL, &dwBinaryLen, NULL, NULL) && 
        dwBinaryLen > 0)
    {
        // Create a buffer for the byte hash
        pbHashBlob = (BYTE *)DSC_malloc(dwBinaryLen, NitsHere());

        if(pbHashBlob)
        {            
            if(!CryptStringToBinary(certificateID, 0, CRYPT_STRING_HEX, pbHashBlob, &dwBinaryLen, 
                NULL, NULL))
            {
                DSC_free(pbHashBlob);
                pbHashBlob = NULL;

                return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_STORE_UNOPENED);
            }
        }
    }
    else
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_STORE_UNOPENED);
    }

    blob.cbData = dwBinaryLen;
    blob.pbData = pbHashBlob;    
    
    hStoreHandle = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0, CERT_SYSTEM_STORE_LOCAL_MACHINE, L"My");
    if(hStoreHandle == NULL)
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_STORE_UNOPENED);
    }   
    // Get a certificate that matches the search criteria (Thumbprint could be MD5 or SHA1 but
    // MD5 has been cracked so most often it'll be SHA1 so check it first)
    pCert = CertFindCertificateInStore(hStoreHandle, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING , 0, 
        CERT_FIND_SHA1_HASH, &blob, NULL);

    if(!pCert)
    {
        pCert = CertFindCertificateInStore(hStoreHandle, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, 
            CERT_FIND_MD5_HASH, &blob, NULL);
    }    
    DSC_free(pbHashBlob);
    pbHashBlob = NULL;

    if(!pCert)
    {
        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_CERT_NOTFOUND);
    }    
    if(!WinHttpSetOption(handle, WINHTTP_OPTION_CLIENT_CERT_CONTEXT, (LPVOID) pCert, sizeof(CERT_CONTEXT)))
    {
        if(pCert)
        {
            CertFreeCertificateContext(pCert);
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
        }        
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_CERT_NOTFOUND);
    }

    if(pCert)
    {
        CertFreeCertificateContext(pCert);
    }

    if(hStoreHandle)
    {
        CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
    }
    return MI_RESULT_OK;
}


MI_Result GetGetConfigurationHttpConnection(_Inout_ RequestContainer *requestParam,  _In_reads_z_(URL_SIZE) const MI_Char *url, _In_ MI_Uint32 port, MI_Boolean bIsHttps,
                            _In_z_ const MI_Char *certificateID, _In_z_ const MI_Char *configurationUrl, _In_ MI_Uint32 requestFlags, 
                            _Out_ MI_Uint32* getActionStatusCode, _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    *getActionStatusCode = Success;
    if(extendedError)
        *extendedError = NULL;    
    
    /* Create http session*/
    requestParam->httpSession = WinHttpOpen(0, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            WINHTTP_FLAG_ASYNC);  
    if( requestParam->httpSession == NULL)
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);
    }

    /* Create http connection with the server*/
    requestParam->httpConnection = WinHttpConnect(requestParam->httpSession,
        url,
        (INTERNET_PORT)port,
        0); // reserved    
    if( requestParam->httpConnection == NULL)
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        WinHttpCloseHandle(requestParam->httpSession);
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);
    }   


    /* Create winhttp request*/
    requestParam->httpRequest = WinHttpOpenRequest(requestParam->httpConnection,
        MI_T("GET"), 
        configurationUrl,
        0, // use HTTP version 1.1
        WINHTTP_NO_REFERER, 
        NULL,
        requestFlags); // flags    

    if( requestParam->httpRequest == NULL)
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        WinHttpCloseHandle(requestParam->httpConnection);
        WinHttpCloseHandle(requestParam->httpSession);
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);
    }        

    /* Set the status callbacks to the request*/
    if(WINHTTP_INVALID_STATUS_CALLBACK == WinHttpSetStatusCallback(requestParam->httpRequest, WinHTTP_Callback, WINHTTP_CALLBACK_FLAG_ALL_NOTIFICATIONS, 0))
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        WinHttpCloseHandle(requestParam->httpConnection);
        WinHttpCloseHandle(requestParam->httpSession);
        WinHttpCloseHandle(requestParam->httpRequest);
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);          
    }
    /*Add certificate if needed*/
    if( bIsHttps && certificateID)
    {
        r = AddCertificateToRequest(requestParam->httpRequest, certificateID, extendedError);
        if( r != MI_RESULT_OK)
        {
            *getActionStatusCode = DownloadManagerInitializationFailure;
            WinHttpCloseHandle(requestParam->httpConnection);
            WinHttpCloseHandle(requestParam->httpSession);
            WinHttpCloseHandle(requestParam->httpRequest);        
            return r;
        }
    }    
    return MI_RESULT_OK;
}

MI_Result GetGetActionHttpConnection(_Inout_ RequestContainer *requestParam,  _In_reads_z_(URL_SIZE) const MI_Char *url, _In_ MI_Uint32 port, MI_Boolean bIsHttps,
                            _In_z_ const MI_Char *certificateID, _In_z_ const MI_Char *actionUrl, _In_ MI_Uint32 requestFlags, _In_z_ MI_Char *requestHeader, 
                            _Out_ MI_Uint32* getActionStatusCode, _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    *getActionStatusCode = Success;
    if(extendedError)
        *extendedError = NULL;
    
    /* Create http session*/
    requestParam->httpSession = WinHttpOpen(0, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            WINHTTP_FLAG_ASYNC);  
    if( requestParam->httpSession == NULL)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULL_GETACTIONFAILED, webPulginName);
    }

    /* Create http connection with the server*/
    requestParam->httpConnection = WinHttpConnect(requestParam->httpSession,
        url,
        (INTERNET_PORT)port,
        0); // reserved    
    if( requestParam->httpConnection == NULL)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        WinHttpCloseHandle(requestParam->httpSession);
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULL_GETACTIONFAILED, webPulginName);
    }   

    /* Create winhttp request*/
    requestParam->httpRequest = WinHttpOpenRequest(requestParam->httpConnection,
        MI_T("POST"), 
        actionUrl,
        0, // use HTTP version 1.1
        WINHTTP_NO_REFERER, 
        NULL,
        requestFlags); // flags    

    if( requestParam->httpRequest == NULL)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        WinHttpCloseHandle(requestParam->httpConnection);
        WinHttpCloseHandle(requestParam->httpSession); 
        WinHttpCloseHandle(requestParam->httpRequest); 
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULL_GETACTIONFAILED, webPulginName);
    }        
    /*Add certificate if needed*/
    if( bIsHttps && certificateID)
    {
        r = AddCertificateToRequest(requestParam->httpRequest, certificateID, extendedError);
        if( r != MI_RESULT_OK)
        {
            WinHttpCloseHandle(requestParam->httpConnection);
            WinHttpCloseHandle(requestParam->httpSession); 
            WinHttpCloseHandle(requestParam->httpRequest);             
            *getActionStatusCode = DownloadManagerInitializationFailure;
            return r;
        }        
    }

    /* Add the headers that are requested.*/
    if(!WinHttpAddRequestHeaders(requestParam->httpRequest, requestHeader, (DWORD)-1L, WINHTTP_ADDREQ_FLAG_ADD))
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        WinHttpCloseHandle(requestParam->httpConnection);
        WinHttpCloseHandle(requestParam->httpSession); 
        WinHttpCloseHandle(requestParam->httpRequest); 
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULL_GETACTIONFAILED, webPulginName);        
    }

    /* Set the status callbacks to the request*/
    if(WINHTTP_INVALID_STATUS_CALLBACK == WinHttpSetStatusCallback(requestParam->httpRequest, WinHTTP_Callback, WINHTTP_CALLBACK_FLAG_ALL_NOTIFICATIONS, 0))
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        WinHttpCloseHandle(requestParam->httpConnection);
        WinHttpCloseHandle(requestParam->httpSession); 
        WinHttpCloseHandle(requestParam->httpRequest);         
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULL_GETACTIONFAILED, webPulginName);          
    }    
    return MI_RESULT_OK;
}


MI_Result  IssueGetActionRequest( _In_z_ const MI_Char *configurationID, 
                                 _In_z_ const MI_Char *certificateID,
                                 _In_z_ const MI_Char *checkSum,
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
    MI_Char *bodyContent = NULL;
    char *bodyContentAscii = NULL;
    DWORD bodyContentLength;
    const MI_Char *emptyString = MI_T("");
    const MI_Char *checkSumFinalValue = emptyString;
    MI_Char requestHeader[MAX_PATH];
    RequestContainer requestParam = {0};
    MI_Char actionUrl[MAX_URL_LENGTH];
    int dwWaitResult;
    MI_Uint32 requestFlags = 0;

    if(extendedError)
        *extendedError  = NULL;

    if( bIsHttps)
        requestFlags = WINHTTP_FLAG_SECURE;
    requestParam.serverOperation = OPERATION_GETACTION;
    if( checkSum != NULL)
    checkSumFinalValue = checkSum;  
    *result = NULL;

    DSC_EventWriteWebDownloadManagerDoActionServerUrl(configurationID, url);
    if( certificateID != NULL)
    {
        DSC_EventWriteWebDownloadManagerDoActionCertId(configurationID, certificateID);
    }
    
    bodyContent = GetGetActionBodyContent(checkSumFinalValue, complianceStatus, AllowedChecksumAlgorithm, lastGetActionStatusCode);
    if( bodyContent == NULL )
    {
        *getActionStatusCode = DownloadManagerInitializationFailure;
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);

    }    
    if(UCS2ToAscii(bodyContent,&bodyContentAscii))
    {
        DSC_free(bodyContent);
        *getActionStatusCode = DownloadManagerInitializationFailure;
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);        
    }
    DSC_free(bodyContent);
    bodyContentLength = (DWORD)Strlen(bodyContentAscii);
    Stprintf(requestHeader, MAX_PATH, MI_T("Accept: application/json\r\nContent-Type: application/json;charset=utf-8\r\nContent-Length: %d"), bodyContentLength);
    Stprintf(actionUrl, MAX_URL_LENGTH, MI_T("/%S/Action(ConfigurationId='%S')/GetAction"),subUrl, configurationID);  

    r = GetGetActionHttpConnection(&requestParam, url, port, bIsHttps, certificateID, actionUrl, requestFlags, requestHeader, getActionStatusCode, extendedError);
    if( r != MI_RESULT_OK)
    {
        DSC_free(bodyContentAscii);
        DSC_EventWriteWebDownloadManagerDoActionHttpClient(configurationID, NULL);
        return r;
    }

    /* Initialize Semaphore*/
    if(Sem_Init_Injected(&requestParam.httpRequestDoneEvent, SEM_USER_ACCESS_DEFAULT, 1, NitsHere()) == -1)
    {
        *getActionStatusCode = DownloadManagerInitializationFailure;
        DSC_free(bodyContentAscii);
        WinHttpCloseHandle(requestParam.httpConnection);
        WinHttpCloseHandle(requestParam.httpSession);
        WinHttpCloseHandle(requestParam.httpRequest);        
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_INIT_FILECRITSEC_FAILED);
    }      
    DSC_EventWriteWebDownloadManagerDoActionGetUrl(configurationID, subUrl);
    /* Send the request.*/
    if (!WinHttpSendRequest(requestParam.httpRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, bodyContentAscii, bodyContentLength, bodyContentLength, (DWORD_PTR)&requestParam))
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        DSC_free(bodyContentAscii);
        WinHttpCloseHandle(requestParam.httpConnection);
        WinHttpCloseHandle(requestParam.httpSession);
        WinHttpCloseHandle(requestParam.httpRequest);
        Sem_Destroy(&requestParam.httpRequestDoneEvent);
        DSC_EventWriteWebDownloadManagerDoActionGetCall(configurationID, NULL);
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULL_GETACTIONFAILED, webPulginName);  
    }    
    /* Wait for call to complete*/
    Sem_TimedWait(&requestParam.httpRequestDoneEvent, (int)0);
    dwWaitResult = Sem_Wait(&requestParam.httpRequestDoneEvent);

    
    DSC_free(bodyContentAscii);
    WinHttpCloseHandle(requestParam.httpConnection);
    WinHttpCloseHandle(requestParam.httpSession);
    WinHttpCloseHandle(requestParam.httpRequest);  
    Sem_Destroy(&requestParam.httpRequestDoneEvent);
    
    if (dwWaitResult != 0)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_FAILED_TO_WAIT_EVENT);
    }    
    /* Process results*/
    r = ValidateGetActionResult(&requestParam, url, getActionStatusCode, extendedError);
    if( r != MI_RESULT_OK)
    {
        DSC_EventWriteWebDownloadManagerDoActionGetCall(configurationID, NULL);
        return r;
    }    
    
    // Set result as MI_Char
    if(AsciiToUCS2(requestParam.u.action.getActionStatus, result) )
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        DSC_free(requestParam.u.action.getActionStatus);
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    DSC_free(requestParam.u.action.getActionStatus);
    *getActionStatusCode = Success;       
    DSC_EventWriteWebDownloadManagerDoActionGetCall(configurationID, *result);    
    return MI_RESULT_OK;
    
}

MI_Result  IssueGetConfigurationRequest( _In_z_ const MI_Char *configurationID,
                                _In_z_ const MI_Char *certificateID,
                                _In_z_ const MI_Char *directoryPath, 
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _In_reads_z_(URL_SIZE) const MI_Char *url,
                                _In_ MI_Uint32 port,
                                _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                MI_Boolean bIsHttps,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    RequestContainer requestParam = {0};
    MI_Char configurationUrl[MAX_URL_LENGTH];
    int dwWaitResult;
    MI_Char *outputResult = (MI_Char*)DSC_malloc((Tcslen(MI_T("OK"))+1) * sizeof(MI_Char), NitsHere());
    MI_Uint32 requestFlags = 0;

    if(extendedError)
        *extendedError  = NULL;    

    if( bIsHttps)
        requestFlags = WINHTTP_FLAG_SECURE;

    requestParam.serverOperation = OPERATION_GETCONFIGURATION;    
    if( certificateID != NULL)
    {
        DSC_EventWriteWebDownloadManagerDoActionCertId(configurationID, certificateID);
    }    
    *result = NULL;
    if( outputResult == NULL )
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }    
    DSC_EventWriteGetDscDocumentWebDownloadManagerServerUrl(configurationID, url);    
    Stprintf(outputResult,3, MI_T("OK"));
    requestParam.u.config.directoryPath = directoryPath;
    Stprintf(configurationUrl, MAX_URL_LENGTH, MI_T("/%S/Action(ConfigurationId='%S')/ConfigurationContent"),subUrl, configurationID);

    r = GetGetConfigurationHttpConnection(&requestParam, url, port, bIsHttps, certificateID, configurationUrl, requestFlags, getActionStatusCode, extendedError);
    if( r != MI_RESULT_OK)
    {
        DSC_EventWriteWebDownloadManagerGetDocHttpClient(configurationID, NULL);
        return r;        
    }
    /* Initialize Semaphore*/
    if(Sem_Init_Injected(&requestParam.httpRequestDoneEvent, SEM_USER_ACCESS_DEFAULT, 1, NitsHere()) == -1)
    {
        *getActionStatusCode = DownloadManagerInitializationFailure;
        DSC_free(outputResult);
        WinHttpCloseHandle(requestParam.httpConnection);
        WinHttpCloseHandle(requestParam.httpSession);
        WinHttpCloseHandle(requestParam.httpRequest);        
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_LCMHELPER_INIT_FILECRITSEC_FAILED);
    }      
    DSC_EventWriteWebDownloadManagerGetDocGetUrl(configurationID, subUrl);
    /* Send the request.*/
    if (!WinHttpSendRequest(requestParam.httpRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, (DWORD_PTR)&requestParam))
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        DSC_free(outputResult);
        WinHttpCloseHandle(requestParam.httpConnection);
        WinHttpCloseHandle(requestParam.httpSession);
        WinHttpCloseHandle(requestParam.httpRequest);
        Sem_Destroy(&requestParam.httpRequestDoneEvent);
        return GetCimWin32Error1Param(GetLastError(), extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);  
    }    
    /* Wait for call to complete*/
    Sem_TimedWait(&requestParam.httpRequestDoneEvent, (int)0);
    dwWaitResult = Sem_Wait(&requestParam.httpRequestDoneEvent);
    
    WinHttpCloseHandle(requestParam.httpConnection);
    WinHttpCloseHandle(requestParam.httpSession);
    WinHttpCloseHandle(requestParam.httpRequest);  
    Sem_Destroy(&requestParam.httpRequestDoneEvent);
    
    if (dwWaitResult != 0)
    {
        DSC_free(outputResult);
        *getActionStatusCode = GetConfigurationCommandFailure;
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_FAILED_TO_WAIT_EVENT);
    }
    /* Validate results*/
    r = ValidateGetConfigurationResult(&requestParam, url, getActionStatusCode, extendedError);
    DSC_EventWriteLCMPullConfigurationChecksumValidationResult(configurationID, (MI_Uint32)r);    
    if( r != MI_RESULT_OK)
    {
        DSC_free(outputResult);
        DSC_EventWriteWebDownloadManagerGetDocGetCall(configurationID, NULL);
        return r;
    }    
    if( requestParam.u.config.checkSumAlgorithm) 
        DSC_free(requestParam.u.config.checkSumAlgorithm); 

    //Create checksumFile
    {
        MI_Char checksumFileName[MAX_URL_LENGTH];
        FILE *fp = NULL;
        Stprintf(checksumFileName, MAX_URL_LENGTH,MI_T("%S.checksum"), directoryPath);
        fp = File_OpenT(checksumFileName,MI_T("w"));
        if( fp != NULL )
        {
            fwrite(requestParam.u.config.checkSum, 1, Tcslen(requestParam.u.config.checkSum) * sizeof(MI_Char), fp);
            File_Close(fp);
        }
        else
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            if( requestParam.u.config.checkSum)
                DSC_free(requestParam.u.config.checkSum);   
            DSC_free(outputResult);
            DSC_EventWriteWebDownloadManagerGetDocFileSave(configurationID, checksumFileName);
            return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULLGETCONFIGURATION_CHECKSUMSAVEFAILED, checksumFileName);            
        }
    }    
    if( requestParam.u.config.checkSum)
    {
        DSC_free(requestParam.u.config.checkSum);
    }

    *result = outputResult;
    DSC_EventWriteWebDownloadManagerGetDocGetCall(configurationID, *result );
    return MI_RESULT_OK;    
}


#else

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

MI_Boolean HandleGetConfigurationResponse( _In_ void *callbackData, _In_ const HttpClientResponseHeader *headers,
                MI_Sint64 contentSize, MI_Boolean lastChunk, _In_ Page**data)
{
    MI_Uint32 xCount;
    RequestContainer * requestParam = (RequestContainer*) callbackData;
    requestParam->statusCode = Success;
    if( headers)
    {
       requestParam->httpError = headers->httpError;
       if( headers->httpError != HTTP_SUCCESS_CODE ) //Status_OK
       {
            return MI_FALSE;
       }        
        for(  xCount = 0; xCount < headers->sizeHeaders; xCount++)
        {
            if(Strcasecmp(headers->headers[xCount].name, checkSumName) == 0 ) 
            {
                requestParam->u.config.checkSum = (char*) DSC_malloc(Strlen(headers->headers[xCount].value)+1, NitsHere());
                if( requestParam->u.config.checkSum == NULL)
                {
                    requestParam->statusCode = GetConfigurationCommandFailure;
                    requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, ID_ENGINEHELPER_MEMORY_ERROR);
                    return MI_FALSE;
                }
                memcpy(requestParam->u.config.checkSum, headers->headers[xCount].value, Strlen(headers->headers[xCount].value));
            }
            else if(Strcasecmp(headers->headers[xCount].name, checksumAlgorithmName) == 0 ) 
            {
                requestParam->u.config.checkSumAlgorithm = (char*) DSC_malloc(Strlen(headers->headers[xCount].value) +1, NitsHere());
                if( requestParam->u.config.checkSumAlgorithm == NULL)
                {
                    requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, ID_ENGINEHELPER_MEMORY_ERROR);
                    requestParam->statusCode = GetConfigurationCommandFailure;
                    return MI_FALSE;
                }
                memcpy(requestParam->u.config.checkSumAlgorithm, headers->headers[xCount].value, Strlen(headers->headers[xCount].value));                
            }
        }
    }

    if( data && *data)
    {
        size_t dataSize =(*data)->u.s.size;
        FILE *fp = File_OpenT(requestParam->u.config.directoryPath, MI_T("a"));
        if(fp == NULL)
        {
            requestParam->internalErrorResult = GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, 
                                        ID_PULL_CONFIGURATIONSAVEFAILED, requestParam->u.config.directoryPath);
            requestParam->statusCode = GetConfigurationCommandFailure;
            return MI_FALSE;            
        }
        fwrite( (char*)((*data)+1), 1, dataSize, fp);
        File_Close(fp);
    }
    return MI_TRUE;
}

MI_Boolean HandleGetModuleResponse( _In_ void *callbackData, _In_ const HttpClientResponseHeader *headers,
                MI_Sint64 contentSize, MI_Boolean lastChunk, _In_ Page**data)
{
    MI_Uint32 xCount;
    RequestContainer * requestParam = (RequestContainer*) callbackData;
    requestParam->statusCode = Success;
    if( headers)
    {
       requestParam->httpError = headers->httpError;
       if( headers->httpError != HTTP_SUCCESS_CODE ) //Status_OK
       {
            return MI_FALSE;
       }        
        for(  xCount = 0; xCount < headers->sizeHeaders; xCount++)
        {
            if(Strcasecmp(headers->headers[xCount].name, checkSumName) == 0 ) 
            {
                requestParam->u.config.checkSum = (char*) DSC_malloc(Strlen(headers->headers[xCount].value)+1, NitsHere());
                if( requestParam->u.config.checkSum == NULL)
                {
                    requestParam->statusCode = GetConfigurationCommandFailure;
                    requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, ID_ENGINEHELPER_MEMORY_ERROR);
                    return MI_FALSE;
                }
                memcpy(requestParam->u.config.checkSum, headers->headers[xCount].value, Strlen(headers->headers[xCount].value));
            }
            else if(Strcasecmp(headers->headers[xCount].name, checksumAlgorithmName) == 0 ) 
            {
                requestParam->u.config.checkSumAlgorithm = (char*) DSC_malloc(Strlen(headers->headers[xCount].value) +1, NitsHere());
                if( requestParam->u.config.checkSumAlgorithm == NULL)
                {
                    requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, ID_ENGINEHELPER_MEMORY_ERROR);
                    requestParam->statusCode = GetConfigurationCommandFailure;
                    return MI_FALSE;
                }
                memcpy(requestParam->u.config.checkSumAlgorithm, headers->headers[xCount].value, Strlen(headers->headers[xCount].value));                
            }
        }
    }

    if( data && *data)
    {
        size_t dataSize =(*data)->u.s.size;
        FILE *fp = File_OpenT(requestParam->u.config.directoryPath, MI_T("a"));
        if(fp == NULL)
        {
            requestParam->internalErrorResult = GetCimMIError1Param(MI_RESULT_FAILED, &requestParam->internalError, 
                                        ID_PULL_CONFIGURATIONSAVEFAILED, requestParam->u.config.directoryPath);
            requestParam->statusCode = GetConfigurationCommandFailure;
            return MI_FALSE;            
        }
        fwrite( (char*)((*data)+1), 1, dataSize, fp);
        File_Close(fp);
    }
    return MI_TRUE;
}

MI_Result  IssueGetActionRequest( _In_z_ const MI_Char *configurationID, 
                                 _In_z_ const MI_Char *certificateID,
                                 _In_z_ const MI_Char *checkSum,
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
    const char *header1 = "Accept: application/json";
    const char *header2 = "Content-Type: application/json; charset=utf-8";
    size_t bodyContentLength;
    const char *header_strings[3] = {0};
    char contentLengthHeader[DEFAULT_MEMORY_SIZE];
    HttpClient *http = NULL;
    int i =0;
    char *bodyContent = NULL;
    const char *checkSumFinalValue = emptyString;
    RequestContainer requestParam = {0};
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
    bodyContentLength = Strlen(bodyContent);
    Snprintf(contentLengthHeader, DEFAULT_MEMORY_SIZE, "Content-Length: %d", bodyContentLength);
    //Form headers
    header_strings[0] = header1;
    header_strings[1] = header2;
    header_strings[2] = (const char*)contentLengthHeader;    

    // Create Connector object
    r = HttpClient_New_Connector( &http, NULL, url, (unsigned short)port, bIsHttps, HandleStatus, HandleResponse, (void*)&requestParam, NULL, NULL, NULL);
    if( r != MI_RESULT_OK)
    {
        *getActionStatusCode = GetDscActionCommandFailure;
        DSC_free(bodyContent);
        return GetCimMIError1Param(r, extendedError, ID_PULL_GETACTIONFAILED, webPulginName);
    }

    //Create the request.
    {
        char actionUrl[MAX_URL_LENGTH];
        HttpClientRequestHeaders headers ;
        Page *rsp = (Page*) DSC_malloc(sizeof(Page) + bodyContentLength, NitsHere());
        headers.data = (const char *const*) header_strings;
        headers.size = 3;        
        if( rsp == NULL )
        {
            *getActionStatusCode = DownloadManagerInitializationFailure;
            DSC_free(bodyContent);
            HttpClient_Delete(http);
            return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);            
        }
        
        rsp->u.s.size = (MI_Uint32)bodyContentLength;
        memcpy(rsp+1, bodyContent, bodyContentLength);
        Snprintf(actionUrl, MAX_URL_LENGTH, "/%s/Action(ConfigurationId='%s')/GetAction",subUrl, configurationID);
        r = HttpClient_StartRequest(http, "POST", actionUrl, &headers, &rsp);
        if( r != MI_RESULT_OK)
        {
            *getActionStatusCode = GetDscActionCommandFailure;
            DSC_free(bodyContent);
            DSC_free(rsp);
            HttpClient_Delete(http);
            return GetCimMIError1Param(r, extendedError, ID_PULL_GETACTIONFAILED, webPulginName);            
        }
         DSC_EventWriteWebDownloadManagerDoActionGetUrl(configurationID, subUrl);
        for( i =0; i < 10000 && !requestParam.httpResponseReveived;i++)
            HttpClient_Run(http, HTTP_CONNECTION_TIMEOUT * 1000);    

        HttpClient_Delete(http);
        DSC_free(rsp);
    }
    DSC_free(bodyContent);
    r = ValidateGetActionResult(&requestParam, url, getActionStatusCode, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }
    // Set result as MI_Char
    {
#if defined(CONFIG_ENABLE_WCHAR) 
        AsciiToUCS2(requestParam.u.action.getActionStatus, result);
        DSC_free(requestParam.u.action.getActionStatus);
#else
        *result = requestParam.u.action.getActionStatus;

#endif
    }
    *getActionStatusCode = Success;
    DSC_EventWriteWebDownloadManagerDoActionGetCall(configurationID, requestParam.u.action.getActionStatus);
    return MI_RESULT_OK;
    
}

void HandleStatus(_In_ HttpClient *http, _In_ void *callbackData, MI_Result result)
{
    RequestContainer * requestParam = (RequestContainer*) callbackData;

    requestParam->httpResponseResult = result;
    requestParam->httpResponseReveived = MI_TRUE;
}

MI_Boolean HandleResponse( _In_ HttpClient *http, _In_ void *callbackData, _In_ const HttpClientResponseHeader *headers,
                MI_Sint64 contentSize, MI_Boolean lastChunk, _In_ Page**data)
{
    RequestContainer * requestParam = (RequestContainer*) callbackData;
    if(requestParam->serverOperation == OPERATION_GETACTION )
    {
        // Headers are not important
        if(headers)
        {
            requestParam->httpError = headers->httpError;
           if( headers->httpError != HTTP_SUCCESS_CODE ) //Status_OK
           {
                return MI_FALSE;
           }
        }
        if( data && *data)
        {
            GetGetActionData((char*)((*data)+1), (*data)->u.s.size, &requestParam->u.action.getActionStatus);
            if( requestParam->u.action.getActionStatus == NULL )
            {
                requestParam->internalErrorResult = GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, &requestParam->internalError, 
                            ID_ENGINEHELPER_MEMORY_ERROR);
                requestParam->statusCode = GetDscActionCommandFailure;
                return MI_FALSE;
            }
        }
        return MI_TRUE;
    }
    else if(requestParam->serverOperation == OPERATION_GETCONFIGURATION )
    {
        return HandleGetConfigurationResponse(callbackData, headers, contentSize, lastChunk, data);
    }
    else if(requestParam->serverOperation == OPERATION_GETMODULE )
    {
        return HandleGetModuleResponse(callbackData, headers, contentSize, lastChunk, data);
    }
    else
    {
        // unrecognized operation
        return MI_FALSE;
    }
}

MI_Result  IssueGetConfigurationRequest( _In_z_ const MI_Char *configurationID, 
                                _In_z_ const MI_Char *certificateID,
                                _In_z_ const MI_Char *directoryPath, 
                                _Outptr_result_maybenull_z_  MI_Char** result,
                                _Out_ MI_Uint32* getActionStatusCode,
                                _In_reads_z_(URL_SIZE) const MI_Char *url,
                                _In_ MI_Uint32 port,
                                _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                MI_Boolean bIsHttps,
                                _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    RequestContainer requestParam = {0};  
    HttpClient  *http = NULL;
    int i=0;
    MI_Char *outputResult = (MI_Char*)DSC_malloc((Tcslen(MI_T("OK"))+1) * sizeof(MI_Char), NitsHere());
    requestParam.serverOperation = OPERATION_GETCONFIGURATION;  
    *result = NULL;
    if( outputResult == NULL )
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    DSC_EventWriteGetDscDocumentWebDownloadManagerServerUrl(configurationID, url);
    Stprintf(outputResult,3, MI_T("OK"));
    requestParam.u.config.directoryPath = directoryPath;
    r = HttpClient_New_Connector( &http, NULL, url, (unsigned short)port, bIsHttps, HandleStatus, HandleResponse, (void*)&requestParam, NULL, NULL, NULL);
    if( r != MI_RESULT_OK)
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        DSC_free(outputResult);
        return GetCimMIError1Param(r, extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);
    }
    //Create Request
    {
        char configurationUrl[MAX_URL_LENGTH];
        Snprintf(configurationUrl, MAX_URL_LENGTH, "/%s/Action(ConfigurationId='%s')/ConfigurationContent",subUrl, configurationID);
        r = HttpClient_StartRequest(http, "GET", configurationUrl, NULL, NULL);
        if( r != MI_RESULT_OK)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            HttpClient_Delete(http);
            DSC_free(outputResult);
            return GetCimMIError1Param(r, extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);          
        }
         DSC_EventWriteWebDownloadManagerGetDocGetUrl(configurationID, subUrl);
        for( i =0; i < 10000 && !requestParam.httpResponseReveived ; i++)
             HttpClient_Run(http, HTTP_CONNECTION_TIMEOUT * 1000);  
        
        HttpClient_Delete(http);        
    }

    r = ValidateGetConfigurationResult(&requestParam, url, getActionStatusCode, extendedError);
    DSC_EventWriteLCMPullConfigurationChecksumValidationResult(configurationID, (MI_Uint32)r);        
    if( r != MI_RESULT_OK)
    {
        DSC_free(outputResult);
        return r;
    }
    if( requestParam.u.config.checkSumAlgorithm) 
        DSC_free(requestParam.u.config.checkSumAlgorithm);    
  
    //Create checksumFile
    {
        MI_Char checksumFileName[MAX_URL_LENGTH];
        FILE *fp = NULL;
        Stprintf(checksumFileName, MAX_URL_LENGTH,MI_T("%s.checksum"), directoryPath);
        fp = File_OpenT(checksumFileName,MI_T("w"));
        if( fp != NULL )
        {
            fwrite(requestParam.u.config.checkSum, 1, Strlen(requestParam.u.config.checkSum), fp);
            File_Close(fp);
        }
        else
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            if( requestParam.u.config.checkSum)
                DSC_free(requestParam.u.config.checkSum);   
            DSC_free(outputResult);
            return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULLGETCONFIGURATION_CHECKSUMSAVEFAILED, checksumFileName);            
        }
    }

    if( requestParam.u.config.checkSum)
        DSC_free(requestParam.u.config.checkSum);       
    *result = outputResult;
    DSC_EventWriteWebDownloadManagerGetDocGetCall(configurationID, *result );
    return MI_RESULT_OK;
}

#endif

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
    r = GetMetaConfigParameters(metaConfig, &credential, &customParam, configurationID, certificateID, getActionStatusCode, extendedError);
    if( r != MI_RESULT_OK)
    {
        return r;
    }
    r = GetUrlParam(&customParam, url, subUrl, port, bIsHttps, getActionStatusCode, extendedError);
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
                                  _Outptr_result_maybenull_z_  MI_Char** result,
                                  _Out_ MI_Uint32* getActionStatusCode,
                                  _In_reads_z_(URL_SIZE) const MI_Char *url,
                                  _In_ MI_Uint32 port,
                                  _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                  MI_Boolean bIsHttps,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    RequestContainer requestParam = {0};  
    HttpClient  *http = NULL;
    int i=0;
    MI_Char *outputResult = (MI_Char*)DSC_malloc((Tcslen(MI_T("OK"))+1) * sizeof(MI_Char), NitsHere());
    requestParam.serverOperation = OPERATION_GETMODULE;  
    *result = NULL;
    if( outputResult == NULL )
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        return GetCimMIError(r, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    DSC_EventWriteGetDscDocumentWebDownloadManagerServerUrl(configurationID, url);
    Stprintf(outputResult,3, MI_T("OK"));
    

    requestParam.u.config.directoryPath = filePath;
    r = HttpClient_New_Connector( &http, NULL, url, (unsigned short)port, bIsHttps, HandleStatus, HandleResponse, (void*)&requestParam, NULL, NULL, NULL);
    if( r != MI_RESULT_OK)
    {
        *getActionStatusCode = GetConfigurationCommandFailure;
        DSC_free(outputResult);
        return GetCimMIError1Param(r, extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);
    }
    //Create Request
    {
        char configurationUrl[MAX_URL_LENGTH];
        Snprintf(configurationUrl, MAX_URL_LENGTH, "/%s/Module(ConfigurationId='%s',ModuleName='%s',ModuleVersion='%s')/ModuleContent",subUrl, configurationID, moduleName, moduleVersion);
        r = HttpClient_StartRequest(http, "GET", configurationUrl, NULL, NULL);
        if( r != MI_RESULT_OK)
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            HttpClient_Delete(http);
            DSC_free(outputResult);
            return GetCimMIError1Param(r, extendedError, ID_PULLGETCONFIGURATIONFAILED, webPulginName);          
        }
         DSC_EventWriteWebDownloadManagerGetDocGetUrl(configurationID, subUrl);
        for( i =0; i < 10000 && !requestParam.httpResponseReveived ; i++)
             HttpClient_Run(http, HTTP_CONNECTION_TIMEOUT * 1000);  
        
        HttpClient_Delete(http);        
    }

    r = ValidateGetConfigurationResult(&requestParam, url, getActionStatusCode, extendedError);
    DSC_EventWriteLCMPullConfigurationChecksumValidationResult(configurationID, (MI_Uint32)r);        
    if( r != MI_RESULT_OK)
    {
        DSC_free(outputResult);
        return r;
    }
    if( requestParam.u.config.checkSumAlgorithm) 
        DSC_free(requestParam.u.config.checkSumAlgorithm);    
  
    //Create checksumFile
    {
        MI_Char checksumFileName[MAX_URL_LENGTH];
        FILE *fp = NULL;
        Stprintf(checksumFileName, MAX_URL_LENGTH,MI_T("%s.checksum"), filePath);
        fp = File_OpenT(checksumFileName,MI_T("w"));
        if( fp != NULL )
        {
            fwrite(requestParam.u.config.checkSum, 1, Strlen(requestParam.u.config.checkSum), fp);
            File_Close(fp);
        }
        else
        {
            *getActionStatusCode = GetConfigurationCommandFailure;
            if( requestParam.u.config.checkSum)
                DSC_free(requestParam.u.config.checkSum);   
            DSC_free(outputResult);
            return GetCimMIError1Param(MI_RESULT_FAILED, extendedError, ID_PULLGETCONFIGURATION_CHECKSUMSAVEFAILED, checksumFileName);            
        }
    }

    if( requestParam.u.config.checkSum)
        DSC_free(requestParam.u.config.checkSum);       
    *result = outputResult;
    DSC_EventWriteWebDownloadManagerGetDocGetCall(configurationID, *result );
    return MI_RESULT_OK;
}

MI_Result MI_CALL Pull_GetModules(const MI_Char *configurationID, 
                                  const MI_Char *certificateID,
                                  MI_Char* directoryPath,
                                  MI_Char* fileName,
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
    r = GetModuleNameVersionTable(fileName, &moduleTable);
    if (r != MI_RESULT_OK)
    {
        CleanupModuleTable(moduleTable);
        DSC_free(fileName);
        free(directoryPath);
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
            DSC_free(fileName);
            free(directoryPath);
            return r;
        }

        Snprintf(stringBuffer, MAX_URL_LENGTH, "%s %s", "/opt/microsoft/dsc/Scripts/InstallModule.py", zipPath);
        retval = system(stringBuffer);

        if (retval != 0)
        {
            CleanupModuleTable(moduleTable);
            DSC_free(fileName);
            free(directoryPath);
            return MI_RESULT_FAILED; 
        }

        current = current->next;
    }

    CleanupModuleTable(moduleTable);

    return MI_RESULT_OK;

}

MI_Result MI_CALL Pull_GetConfigurationWebDownloadManager(_In_ LCMProviderContext *lcmContext,
                                _In_ MI_Instance *metaConfig,
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

    if( metaConfig == NULL )
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    r = GetRequestParam(metaConfig, (MI_Char*)url, (MI_Char*)subUrl, &port, &bIsHttps, &configurationID, &certificateID, getActionStatusCode, extendedError);
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
    DSC_EventWriteLCMPullGetConfigAttempt( webPulginName, configurationID);    
    // Issue Get Action Request
    r = IssueGetConfigurationRequest( configurationID,  certificateID, fileName, result, 
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

    r = Pull_GetModules(configurationID,  certificateID, directoryPath, fileName, result, getActionStatusCode, bAllowedModuleOverride, url, port, subUrl, bIsHttps, extendedError);
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
    
    if( metaConfig == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    tmpChecksum = (MI_Char*)DSC_malloc( (Tcslen(checkSum) +1) * sizeof(MI_Char), NitsHere());
    if( tmpChecksum == NULL)
    {
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
    }
    memcpy(tmpChecksum, checkSum, Tcslen(checkSum)* sizeof(MI_Char));

    r = GetRequestParam(metaConfig, (MI_Char*)url, (MI_Char*)subUrl, &port, &bIsHttps, &configurationID, &certificateID, getActionStatusCode, extendedError);
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
    DSC_EventWriteLCMPullGetActionAttempt( webPulginName, configurationID, tmpChecksum, complianceStatus);    
    // Issue Get Action Request
    r = IssueGetActionRequest( configurationID, certificateID, tmpChecksum, complianceStatus, lastGetActionStatusCode, result, 
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
                                           ModuleTable* table)
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
    MI_Instance *extendedError;
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
        return MI_RESULT_FAILED;
    }      
    
    memset(&deserializer, 0, sizeof(MI_Deserializer));    
    memset(&options, 0, sizeof(MI_OperationOptions));

    r = DSC_MI_Application_NewOperationOptions(miApp, MI_FALSE, &options);
    if (r != MI_RESULT_OK)
    {
        DSC_free(miApp);
        return MI_RESULT_FAILED;
    }

    r = DSC_MI_OperationOptions_SetString(&options, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, MOFCODEC_SCHEMA_VALIDATION_IGNORE, 0);
    if (r!=MI_RESULT_OK )
    {
        DSC_free(miApp);
        return MI_RESULT_FAILED;
    }

    r = DSC_MI_Application_NewDeserializer_Mof(miApp, 0, MOFCODEC_FORMAT, &deserializer);
    if (r!=MI_RESULT_OK )
    {
        DSC_free(miApp);
        return MI_RESULT_FAILED;
    }

    r = ReadFileContent(mofFileLocation, &pbuffer, &contentSize, &extendedError);
    if(r != MI_RESULT_OK)
    {
        DSC_free(miApp);
        return r;
    }   
    miClassArray.size = 0;
    miClassArray.data = NULL;

    r = MI_Deserializer_DeserializeInstanceArray(&deserializer, 0, &options, 0, pbuffer, contentSize, &miClassArray, &readBytes, &miInstanceArray, &extendedError);
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
                // Error: Invalid version for module
            }
        }
    }

    r = FilterUsingCachedModules(table);

    MI_Deserializer_Close(&deserializer);
    MI_OperationOptions_Delete(&options);

    CleanUpDeserializerInstanceCache(miInstanceArray);

    return MI_RESULT_OK;
}


void SaveModule()
{
}

void IssueRequest()
{
}


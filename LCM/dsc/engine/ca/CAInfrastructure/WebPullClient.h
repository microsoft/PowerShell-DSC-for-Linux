/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef __WEBPULLCLIENT_H_
#define __WEBPULLCLIENT_H_

#define MAX_SSLOPTION_STRING_LENGTH 4096

struct SSLOptions
{
    MI_Boolean DoNotCheckCertificate;
    MI_Boolean NoSSLv3;
    char cipherList[MAX_SSLOPTION_STRING_LENGTH + 1];
    char CABundle[MAX_SSLOPTION_STRING_LENGTH + 1];
    char Proxy[MAX_SSLOPTION_STRING_LENGTH + 1];
};

enum GetActionStatusCodeTypes
{
    Success = 0,
    DownloadManagerInitializationFailure = 1,
    GetConfigurationCommandFailure = 2,
    UnexpectedGetConfigurationResponseFromServer = 3,
    ConfigurationChecksumFileReadFailure = 4,
    ConfigurationChecksumValidationFailure = 5,
    InvalidConfigurationFile = 6,
    AvailableModulesCheckFailure = 7,
    InvalidConfigurationIdInMetaConfig = 8,
    InvalidDownloadManagerCustomDataInMetaConfig = 9,
    GetDscModuleCommandFailure = 10,
    GetDscModuleInvalidOutput = 11,
    ModuleChecksumFileNotFound = 12,
    InvalidModuleFile = 13,
    ModuleChecksumValidationFailure = 14,
    ModuleExtractionFailure = 15,
    ModuleValidationFailure = 16,
    InvalidDownloadedModule = 17,
    ConfigurationFileNotFound = 18,
    MultipleConfigurationFilesFound = 19,
    ConfigurationChecksumFileNotFound = 20,
    ModuleNotFound = 21,
    InvalidModuleVersionFormat = 22,
    InvalidConfigurationIdFormat = 23,
    GetDscActionCommandFailure = 24,
    InvalidChecksumAlgorithm = 25,
};

enum ServerOperation
{
    OPERATION_GETACTION = 1,
    OPERATION_GETCONFIGURATION = 2,
    OPERATION_GETMODULE = 3
};

typedef struct _RequestContainer
{
    // common
    MI_Uint32 serverOperation;
    MI_Boolean httpResponseReveived;
    MI_Result httpResponseResult;
    MI_Uint32 httpError;
    MI_Result internalErrorResult;
    MI_Instance *internalError;
    MI_Uint32 statusCode;    

    //GetAction specific.
    union
    {
        struct _action
        {
            char *getActionStatus;
        }
        action;
        struct _config
        {
            const MI_Char *directoryPath;
            MI_Char *checkSum;
            MI_Char *checkSumAlgorithm;
        }
        config;
    }
    u;
    
} RequestContainer;

#define DEFAULT_SERVERPORT 80
#define MAX_STATUSCODE_SIZE 32
#define DEFAULT_MEMORY_SIZE 100
#define MAX_URL_LENGTH 512
#define HTTP_CONNECTION_TIMEOUT 60
#define HTTP_SUCCESS_CODE 200
#define BUFFER_SIZE_1KB 1024
#define URL_SIZE 100
#define SUBURL_SIZE 200

//Meta Config
#define MetaConfigConfigurationId  MI_T("ConfigurationID")
#define UseSystemUUIDValue MI_T("UseSystemUUID")
#define MetaConfigDownloadManagerName MI_T("DownloadManagerName")
#define MetaConfigDownloadManagerCustomData MI_T("DownloadManagerCustomData")
#define MetaConfig_Credential MI_T("Credential")
#define MetaConfig_CertificateID MI_T("CertificateID")
#define MetaConfigAllowModuleOverwrite MI_T("AllowModuleOverwrite")


//Web config
#define ServerUrlParamName MI_T("serverurl")
#define AllowUnsecureConnectionParamName MI_T("allowunsecureconnection")
#define CertificateIdParamName MI_T("CertificateID")
#define AllowedChecksumAlgorithm MI_T("SHA-256")
#define GetActionResultOk "OK"
#define GetActionResultGetConfiguration "GETCONFIGURATION"
#define product_uuid_path MI_T("/sys/class/dmi/id/product_uuid")
#define checkSumName MI_T("Checksum")
#define checksumAlgorithmName MI_T("ChecksumAlgorithm")
#define webPulginName MI_T("WebDownloadManager")

MI_Result GetUrlParam(_In_ MI_InstanceA *customData, 
                      _Inout_updates_(URL_SIZE) MI_Char *url, 
                      _Inout_updates_(SUBURL_SIZE) MI_Char *subUrl, 
                      _Out_ MI_Uint32 *port, 
                      _Out_ MI_Boolean *bIsHttps,
                      _Out_ MI_Uint32* getActionStatusCode,
                      _Outptr_result_maybenull_ MI_Instance **extendedError);

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
                                  _Outptr_result_maybenull_ OverAllGetActionResponse** serverAssignedConfigurations,
                                  _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result  IssueGetConfigurationRequest( _In_z_ const MI_Char *configurationID, 
                                         _In_z_ const MI_Char *certificateID,
                                         _In_z_ const MI_Char *directoryPath, 
                                         _Outptr_result_maybenull_z_  MI_Char** result,
                                         _Out_ MI_Uint32* getActionStatusCode,
                                         _In_reads_z_(URL_SIZE) const MI_Char *url,
                                         _In_ MI_Uint32 port,
                                         _In_reads_z_(SUBURL_SIZE) const MI_Char *subUrl,
                                         MI_Boolean bIsHttps,
                                         _In_opt_z_ MI_Char *assignedConfiguration,
                                         _Outptr_result_maybenull_ MI_Instance **extendedError);


MI_Result MI_CALL Pull_GetModules(_Out_ MI_Uint32 * numModulesInstalled,
                                  const MI_Char *configurationID,
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
                                  MI_Instance **extendedError);




#endif

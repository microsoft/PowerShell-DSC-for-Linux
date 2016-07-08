/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

#if defined(_MSC_VER)
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28252 28253 28957) //public winbase.h is giving errors about lock methods hence disabling it
#endif /* _PREFAST_ */

#include <windows.h>
#include <lmcons.h>         // for UNLEN/PWLEN

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */


#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26061 26071  26036) //public strsafe.h is giving errors about some of the methods hence disabling it
#endif /* _PREFAST_ */

#include <strsafe.h>
#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

#else
#include <base/base64.h>
#include <base/paths.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

#endif

#include "DSC_Systemcalls.h"
#include "EngineHelper.h"
#include "CACrypto.h"
#include "PAL_Extension.h"
#include "Resources_LCM.h"
#include "EventWrapper.h"

#if defined(_MSC_VER)


MI_Result MI_CALL Decrypt(_In_z_ const MI_Char *certificateid,
                          _In_z_ const MI_Char *cipher,
                          _Outptr_result_maybenull_z_  MI_Char** result,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result r = MI_RESULT_OK;
    HCERTSTORE hStoreHandle = NULL;
    PCCERT_CONTEXT pCert = NULL;
    HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hCryptProv;
    DWORD dwKeySpec = 0;
    BOOL fCallerFreeProv = FALSE;
    HCRYPTKEY hPrivateKey;
    DWORD dwDecryptedLen = 0;
    DWORD dwEncodedLen = 0;
    DWORD dwBinaryLen = 0;
    BYTE* pbData = NULL;
    DWORD dwCharCount = 0;
    DWORD dwCipherLen = 0;

    BYTE* pbHashBlob = NULL;
    CRYPT_DATA_BLOB blob;

    if (extendedError == NULL || certificateid == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *extendedError = NULL;	// Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

    if (result)
    {
        *result = NULL;
    }

    if(CryptStringToBinary(certificateid, 0, CRYPT_STRING_HEX, NULL, &dwBinaryLen, NULL, NULL) &&
        dwBinaryLen > 0)
    {
        // Create a buffer for the byte hash
        pbHashBlob = (BYTE *)DSC_malloc(dwBinaryLen, NitsHere());

        if(pbHashBlob)
        {
            if(!CryptStringToBinary(certificateid, 0, CRYPT_STRING_HEX, pbHashBlob, &dwBinaryLen,
                NULL, NULL))
            {
                DSC_free(pbHashBlob);
                pbHashBlob = NULL;

                return MI_RESULT_INVALID_PARAMETER;
            }
        }
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    blob.cbData = dwBinaryLen;
    blob.pbData = pbHashBlob;

    // Open the certificate store
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

    if(!pCert)
    {
        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        DSC_free(pbHashBlob);
        pbHashBlob = NULL;

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_CERT_NOTFOUND);
    }

    DSC_free(pbHashBlob);
    pbHashBlob = NULL;

    // Acquire the Private Key
    if(!CryptAcquireCertificatePrivateKey(pCert, CRYPT_ACQUIRE_SILENT_FLAG | CRYPT_ACQUIRE_COMPARE_KEY_FLAG, 0,
        &hCryptProv, &dwKeySpec, &fCallerFreeProv))
    {
        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_GET_PRIVATE_KEY_FAILED);
    }

    // Get Private Key
    if(!CryptGetUserKey(hCryptProv, dwKeySpec, &hPrivateKey))
    {
        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_GET_PRIVATE_KEY_FAILED);
    }

    dwCipherLen = (DWORD)wcslen(cipher);

    // Convert the base64 encoded string to a byte array
    if(!CryptStringToBinary(cipher, dwCipherLen, CRYPT_STRING_BASE64, NULL, &dwEncodedLen,
        NULL, NULL) && dwEncodedLen > 0)
    {
        int lastError = GetLastError();

        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimWin32Error(lastError, extendedError, ID_CA_CRYPTO_DECRYPTION_FAILED);
    }

    // Create a buffer for encoded/encrypted data.
    pbData = (BYTE *)DSC_malloc(dwEncodedLen, NitsHere());

    if(!pbData)
    {
        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError,
            ID_CA_CRYPTO_DECRYPTED_MALLOC_FAILED);
    }

    if(!CryptStringToBinary(cipher, dwCipherLen, CRYPT_STRING_BASE64, pbData, &dwEncodedLen,
        NULL, NULL))
    {
        int lastError = GetLastError();

        if(pbData)
        {
            DSC_free(pbData);
            pbData = NULL;
        }

        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimWin32Error(lastError, extendedError, ID_CA_CRYPTO_DECRYPTION_FAILED);
    }

    dwDecryptedLen = dwEncodedLen;

    // Decrypt data
    if(!CryptDecrypt(hPrivateKey, 0, TRUE, 0, pbData, &dwDecryptedLen))
    {
        int lastError = GetLastError();

        if(pbData)
        {
            DSC_free(pbData);
            pbData = NULL;
        }

        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimWin32Error(lastError, extendedError, ID_CA_CRYPTO_DECRYPTION_FAILED);
    }

    dwCharCount = (DWORD)wcslen((wchar_t *)pbData);

    // Verify that the password is not larger than the max possible password
    if(!(dwCharCount > 0) || dwCharCount > PWLEN )
    {
        int lastError = GetLastError();

        if(pbData)
        {
            DSC_free(pbData);
            pbData = NULL;
        }

        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimWin32Error(lastError, extendedError, ID_CA_CRYPTO_DECRYPTION_FAILED);
    }

    *result = (MI_Char*)DSC_malloc(sizeof(MI_Char) * (dwCharCount+1), NitsHere());

    if(*result)
    {
        memcpy(*result, pbData, sizeof(MI_Char) * (dwCharCount+1));

        r = MI_RESULT_OK;
    }
    else
    {
        if(pbData)
        {
            DSC_free(pbData);
            pbData = NULL;
        }

        if(pCert)
        {
            CertFreeCertificateContext(pCert);
            pCert = NULL;
        }

        if(hStoreHandle)
        {
            CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
            hStoreHandle = NULL;
        }

        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError,
            ID_CA_CRYPTO_DECRYPTED_MALLOC_FAILED);
    }

    if(pbData)
    {
        DSC_free(pbData);
        pbData = NULL;
    }

    if(pCert)
    {
        CertFreeCertificateContext(pCert);
    }

    if(hStoreHandle)
    {
        CertCloseStore(hStoreHandle, CERT_CLOSE_STORE_CHECK_FLAG);
    }

    return r;
}

#else

// support decryption for non-windows here.

int Decrypt_Base64DecCallback( const void *data, size_t size, void *callbackData)
{
    MI_Uint8A *oldData = (MI_Uint8A*)callbackData;
    size_t newLen = oldData->size + size;
    // oldData->size is a Uint32. Fail if newLen would be truncated later on
    if (newLen > 0xFFFFFFFF)
        return -1;
    char *newData = (char*)DSC_malloc(newLen, NitsHere());
    if(newData == NULL)
        return -1;
    memcpy(newData, oldData->data, oldData->size * sizeof(MI_Char));
    memcpy(newData+oldData->size, data, size);
    DSC_free(oldData->data);
    oldData->data = (MI_Uint8*)newData;
    oldData->size = newLen;
    return 0;
}

MI_Boolean DecodeBase64(_In_z_ const void *data, size_t size, _Outptr_result_z_ char **decodedBuffer, _Out_ size_t *decodedBufferLength)
{
    MI_Uint8A strArray = {0};
    *decodedBuffer = NULL;
    int decodedSize = Base64Dec(data, size, Decrypt_Base64DecCallback, (void*) &strArray);
    if( decodedSize == -1 )
    {
        if( strArray.data != NULL)
            DSC_free(strArray.data);
        return MI_FALSE;
    }

    *decodedBuffer = (char*)strArray.data;
    *decodedBufferLength = strArray.size;
    return MI_TRUE;

}

MI_Result MI_CALL Decrypt(_In_z_ const MI_Char *certificateid,
                          _In_z_ const MI_Char *cipher,
                          _Outptr_result_maybenull_z_  MI_Char** result,
                          _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Char cerFilePath[CER_PATH_LENGTH];
    EVP_PKEY *privKey;
    char *decodedBuffer = NULL;
    char *decryptedBuffer = NULL;
    int  decryptedBufferLength = 0;
    size_t decodedBufferLength = 0;
    int xCount = 0;


    // Open file to read the private key.
    FILE *fp = NULL;
    if( *result)
    {
       *result = NULL;
    }
    if( *extendedError)
    {
       *extendedError = NULL;
    }
    Stprintf(cerFilePath, CER_PATH_LENGTH, MI_T("%s/%s"), CONFIG_CERTSDIR, certificateid) ;
    fp = File_OpenT(cerFilePath, MI_T("r"));
    if( fp == NULL)
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_STORE_UNOPENED);
    }

    OpenSSL_add_all_algorithms();
    // Read private key
    privKey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
    fclose(fp);
    if (privKey == NULL )
    {
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_CERT_NOTFOUND);
    }
    // Decode BASE64 encoding.
    if(!DecodeBase64(cipher, Tcslen(cipher), &decodedBuffer, &decodedBufferLength) )
    {
        EVP_PKEY_free(privKey);
        GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_DECRYPTION_FAILED);
    }
    // Reverse the value.
    for( xCount = 0; xCount < (int)decodedBufferLength/2; xCount++)
    {
        char temp = decodedBuffer[xCount];
        decodedBuffer[xCount] = decodedBuffer[ decodedBufferLength - 1 - xCount];
        decodedBuffer[decodedBufferLength - 1 - xCount] = temp;
    }
    //Allocate buffer for decryption
    decryptedBuffer = (char*) DSC_malloc( RSA_size(privKey->pkey.rsa) , NitsHere());
    if( decryptedBuffer == NULL)
    {
        EVP_PKEY_free(privKey);
        DSC_free(decodedBuffer);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_CA_CRYPTO_DECRYPTED_MALLOC_FAILED);

    }

    // Decrypt the buffer using private key.
    decryptedBufferLength = RSA_private_decrypt(decodedBufferLength, (unsigned const char*)decodedBuffer, (unsigned char*)decryptedBuffer, privKey->pkey.rsa, RSA_PKCS1_PADDING);
    EVP_PKEY_free(privKey);
    DSC_free(decodedBuffer);

    if( decryptedBufferLength == -1 )
    {
        DSC_free(decryptedBuffer);
        return GetCimMIError(MI_RESULT_FAILED, extendedError, ID_CA_CRYPTO_DECRYPTION_FAILED);
    }
#if !defined(CONFIG_ENABLE_WCHAR)
    // The buffer could be coming from machines which encrypted password as unicode
    // We have to check that and convert it to ASCII.
    for( xCount = 0; xCount < decryptedBufferLength/2; xCount++)
    {
        if(decryptedBuffer[2*xCount+1] != '\0')
        {
            break;
        }
    }
    if( xCount == 0 ) // it is plain ASCII string
    {
       *result = decryptedBuffer;
    }
    else if( xCount == decryptedBufferLength/2) // it is unicode string that can be converted to ASCII string
    {
        for( xCount = 0; xCount < decryptedBufferLength/2; xCount++)
        {
            decryptedBuffer[xCount] = decryptedBuffer[2*xCount];
        }
        decryptedBuffer[xCount] = '\0';
        *result = decryptedBuffer;
    }
    else //Invalid password
    {
        DSC_free(decodedBuffer);
        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_CA_CRYPTO_DECRYPTED_MALLOC_FAILED);

    }
#else
    *result = decryptedBuffer;
#endif

    return MI_RESULT_OK;
}

#endif


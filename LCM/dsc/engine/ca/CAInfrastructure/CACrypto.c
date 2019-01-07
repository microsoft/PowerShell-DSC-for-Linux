/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

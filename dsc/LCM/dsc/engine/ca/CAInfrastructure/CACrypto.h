/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _CACRYPTO_H
#define _CACRYPTO_H
#include <nits.h>

#include "MI.h"
#include "ModuleHandler.h"

#if defined(_MSC_VER)
#include <wincrypt.h>
#endif

#define CER_PATH_LENGTH 512

#ifdef __cplusplus
extern "C"
{
#endif

MI_Result MI_CALL Decrypt(_In_z_ const MI_Char *certificateid,
                          _In_z_ const MI_Char *cipher,
                          _Outptr_result_maybenull_z_  MI_Char** result,
                          _Outptr_result_maybenull_ MI_Instance **extendedError);

#ifdef __cplusplus
                                  
}
                                  
#endif

#endif //_CACRYPTO_H

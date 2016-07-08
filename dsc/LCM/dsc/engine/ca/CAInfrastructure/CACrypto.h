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

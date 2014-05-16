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

#ifndef _mof_instance_utility_h
#define _mof_instance_utility_h

#include <MI.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
**==============================================================================
**
** Utilities creates instance
**
**==============================================================================
*/
MI_Result MI_CALL Mof_Instance_New(
    _In_ const MI_ClassDecl* classDecl,
    _Outptr_result_maybenull_ MI_Instance **instance);

MI_Result MI_CALL Mof_Instance_InitDynamic(
    _In_z_ const MI_Char* className,
    _In_ MI_Uint32 metaType,
    _Outptr_result_maybenull_ MI_Instance** self);

MI_Result MI_CALL Mof_Instance_Construct(
    _In_ const MI_ClassDecl* classDecl,
    __out MI_Instance* instance);

#ifdef __cplusplus
}
#endif

#endif /* _mof_instance_utility_h */

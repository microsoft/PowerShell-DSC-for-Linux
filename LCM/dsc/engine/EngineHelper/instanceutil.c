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

#include "instanceutil.h"
#include <Common/instance.h>

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_New(
    const MI_ClassDecl* classDecl,
    MI_Instance **instance)
{
    return Instance_New(classDecl, instance);
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_InitDynamic(
    const MI_Char* className,
    MI_Uint32 metaType,
    MI_Instance** self)
{
    return Instance_InitDynamic(self, className, metaType);
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_Construct(
    const MI_ClassDecl* classDecl,
    MI_Instance* instance)
{
    return Instance_Construct(classDecl, instance);
}

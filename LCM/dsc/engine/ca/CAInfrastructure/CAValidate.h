
/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
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
#ifndef __CAVALIDATE_H_
#define __CAVALIDATE_H_

#include <nits.h>
#include "MI.h"
#include <EngineHelper.h>
#include <Resources_LCM.h>
#include <DSC_Systemcalls.h>

MI_Result ValidateIfDuplicatedInstances(
    _In_ MI_InstanceA *instanceA,
    _Outptr_result_maybenull_ MI_Instance **extendedError);


#endif //__CAVALIDATE_H_

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

#ifndef __ENGINEHELPER_H_
#define __ENGINEHELPER_H_

#include <pal/strings.h>
#include <pal/sem.h>
#include <pal/thread.h>
#include <pal/lock.h>
#include <pal/memory.h>
#include <pal/math.h>
#include <pal/file.h>
#include <pal/atomic.h>
#include <pal/format.h>
#include <pal/cpu.h>
#include <pal/sleep.h>
#include <pal/intlstr.h>
#include <pal/alloc.h>

#include "EngineHelperInternal.h"
#include "PAL_Extension.h"

typedef struct _Loc_Mapping
{
    MI_Uint32 locId;
    Intlstr (*LocFunctionZeroArgs)() ;
    Intlstr (*LocFunctionOneArgs)(MI_Char *) ;
    Intlstr (*LocFunctionTwoArgs)(MI_Char *, MI_Char *) ;
    Intlstr (*LocFunctionThreeArgs)(MI_Char *, MI_Char *, MI_Char *) ;
    Intlstr (*LocFunctionFourArgs)(MI_Char *, MI_Char *, MI_Char *, MI_Char *) ;    

} Loc_Mapping;

void GetResourceString1Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1, _Inout_ Intlstr *resStr);
void GetResourceString2Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1,
                               _In_z_ const MI_Char * param2,_Inout_ Intlstr *resStr);
void GetResourceString3Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1,
              _In_z_ const MI_Char * param2, _In_z_ const MI_Char * param3,_Inout_ Intlstr *resStr);

void GetResourceString4Param( _In_ MI_Uint32 errorStringId, _In_z_ const MI_Char * param1, 
               _In_z_ const MI_Char * param2, _In_z_ const MI_Char * param3,  _In_z_ const MI_Char * param4, _Inout_ Intlstr *resStr);





extern BaseResourceConfiguration g_BaseResourceConfiguration[];
extern JobInformation g_JobInformation;

#endif //__ENGINEHELPER_H_

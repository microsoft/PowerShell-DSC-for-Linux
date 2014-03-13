
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


#ifndef _strings_h_
#define _strings_h_


#include <pal/intlstr.h>
#include "PAL_Extension.Format.Placeholders.h"



#define INTERNAL_Intlstr_Define0( id, name, text)  \
    Intlstr_Define0(id, name, text)

#define INTERNAL_Intlstr_Define1( id, name,  parameter1_type, parameter1_name,text)  \
    Intlstr_Define1(id, name,  parameter1_type, parameter1_name, text)

#define INTERNAL_Intlstr_Define2( id, name,  parameter1_type, parameter1_name, parameter2_type, parameter2_name,text)  \
    Intlstr_Define2(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, text)

#define INTERNAL_Intlstr_Define3( id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text)  \
    Intlstr_Define3(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text)

#define INTERNAL_Intlstr_Define4( id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, parameter4_type, parameter4_name, text) \
    Intlstr_Define4(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, parameter4_type, parameter4_name, text)


#include "strings.inc" 

#undef INTERNAL_Intlstr_Define0
#undef INTERNAL_Intlstr_Define1
#undef INTERNAL_Intlstr_Define2
#undef INTERNAL_Intlstr_Define3
#undef INTERNAL_Intlstr_Define4



#define INTERNAL_Intlstr_Define0( id, name, text) {id, GEN_XFPTR(GEN_HASH(GEN_SUF(id))), NULL, NULL, NULL, NULL }, 

#define INTERNAL_Intlstr_Define1( id, name,  parameter1_type, parameter1_name,text) {id, NULL, GEN_XFPTR(GEN_HASH(GEN_SUF(id))), NULL, NULL, NULL }, 

#define INTERNAL_Intlstr_Define2( id, name,  parameter1_type, parameter1_name, parameter2_type, parameter2_name,text) {id, NULL, NULL, GEN_XFPTR(GEN_HASH(GEN_SUF(id))), NULL, NULL }, 

#define INTERNAL_Intlstr_Define3( id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text) {id, NULL, NULL, NULL, GEN_XFPTR(GEN_HASH(GEN_SUF(id))), NULL }, 

#define INTERNAL_Intlstr_Define4( id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, parameter4_type, parameter4_name, text) {id, NULL, NULL, NULL, NULL, GEN_XFPTR(GEN_HASH(GEN_SUF(id))) },  

Loc_Mapping g_LocMappingTable[] = {
    #include "strings.inc"  
};

MI_Uint32 g_LocMappingTableSize = sizeof(g_LocMappingTable)/sizeof(Loc_Mapping);


#endif /* !defined(_strings_h_) */


/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef _strings_h_
#define _strings_h_


#include <pal/intlstr.h>
#include "PAL_Extension.Format.Placeholders.h"



#define INTERNAL_Intlstr_Define0( id, name,text)  \
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
#define ID_UNDEFINEDERROR_NOPARAM 60000
#define ID_UNDEFINEDERROR_ONEPARAM 60001
#define ID_UNDEFINEDERROR_TWOPARAM 60002
#define ID_UNDEFINEDERROR_THREEPARAM 60003
#define ID_UNDEFINEDERROR_FOURPARAM 60004

INTERNAL_Intlstr_Define1( ID_UNDEFINEDERROR_NOPARAM, ID_UNDEFINEDERROR_NOPARAM,
     _In_z_ const PAL_Char*, firstString,
    "Undefined error id " Intlstr_tstr(1) "." )

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

Loc_Mapping g_UndefinedMessageTable[] = 
{
INTERNAL_Intlstr_Define1( ID_UNDEFINEDERROR_NOPARAM, ID_UNDEFINEDERROR_NOPARAM,
     _In_z_ const PAL_Char*, firstString,
    "Undefined error id " Intlstr_tstr(1) "." )
};

#endif /* !defined(_strings_h_) */

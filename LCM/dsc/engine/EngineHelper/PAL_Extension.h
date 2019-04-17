/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _pal_extension_h
#define _pal_extension_h

#include <stdio.h>
#include <pal/palcommon.h>
#include <pal/file.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct _Internal_DirEnt 
{
    TChar name[PAL_MAX_PATH_SIZE];
    int isDir;
}
Internal_DirEnt;

typedef struct _Internal_Dir Internal_Dir;

#define SHA256TRANSFORM_DIGEST_LEN 32

PAL_BEGIN_EXTERNC

FILE* File_OpenW(
    _In_z_ const wchar_t* path,
    _In_z_ const wchar_t* mode);

int File_RemoveW(
    _In_z_ const wchar_t* path);


int File_TouchW(
    _In_z_ const wchar_t* path);

int UCS2ToAscii( _In_z_ const wchar_t *input,
                  _Outptr_result_z_ char **output);


int AsciiToUCS2(_In_z_ char *input, 
            _Outptr_result_z_ wchar_t **output);


int File_CopyT(_In_z_ const PAL_Char* src, _In_z_ const PAL_Char* dest);


int File_Exist( 
        _In_z_ const char *path);

int File_ExistW(
        _In_z_ const wchar_t *path);

int Directory_Exist( 
        _In_z_ const char *path);

int Directory_ExistW(
        _In_z_ const wchar_t *path);

int TempnamW(
        _Outptr_result_maybenull_z_ wchar_t **output );

int Tempnam(
        _Outptr_result_maybenull_z_ char **output );


int MkdirW(_In_z_ const wchar_t *path, int mode);

Internal_Dir* Internal_Dir_Open(_In_z_ const TChar* path, NitsCallSite cs);

Internal_DirEnt* Internal_Dir_Read(_In_ Internal_Dir* dir,  _In_opt_z_ TChar *fileEndsWith);

int Internal_Dir_Close(Internal_Dir* dir);

int Directory_Remove( _In_z_ TChar *path);

char* Generate_UUID(NitsCallSite cs);

int GetComputerHostName(_Inout_updates_z_(length) TChar *buffer, unsigned int length);

void PAL_SHA256Transform(_In_ void * pInputValue,
    _In_ unsigned int valueLength,
    _Out_ unsigned char hashedValue[SHA256TRANSFORM_DIGEST_LEN]);



PAL_INLINE FILE* File_OpenT(
    _In_z_ const TChar* path,
    _In_z_ const TChar* mode
    )
{
#if defined(CONFIG_ENABLE_WCHAR)
    return File_OpenW(path, mode);
#else
    return File_Open(path, mode);
#endif
}

PAL_INLINE int File_RemoveT(
    _In_z_ const TChar* path
    )
{
#if defined(CONFIG_ENABLE_WCHAR)
    return File_RemoveW(path);
#else
    return File_Remove(path);
#endif
}

PAL_INLINE int File_TouchT(
    _In_z_ const TChar* path
    )
{
#if defined(CONFIG_ENABLE_WCHAR)
    return File_TouchW(path);
#else
    return File_Touch(path);
#endif
}

PAL_INLINE int File_ExistT(
    _In_z_ const TChar* path
    )
{
#if defined(CONFIG_ENABLE_WCHAR)
    return File_ExistW(path);
#else
    return File_Exist(path);
#endif
}

PAL_INLINE int Directory_ExistT(
    _In_z_ const TChar* path
    )
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Directory_ExistW(path);
#else
    return Directory_Exist(path);
#endif
}

PAL_INLINE int MkdirT(
    _In_z_ const TChar* path,
    int mode
    )
{
#if defined(CONFIG_ENABLE_WCHAR)
    return MkdirW(path, mode);
#else
    return mkdir(path, mode);
#endif
}

PAL_INLINE int TempnamT(
     _Outptr_result_maybenull_z_ TChar **output 
    )
{
#if defined(CONFIG_ENABLE_WCHAR)
    return TempnamW(output);
#else
    return Tempnam(output);
#endif
}


// Intlstr.h

/*
**==============================================================================
**
** Intlstr_Define4/5 macros for translating user-provided localized string templates
** into OS-specific Intlstr_<stringname> helper functions
**
**==============================================================================
*/

#if defined(_MSC_VER)

    #define Intlstr_Define4(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, parameter4_type, parameter4_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name, parameter3_type parameter3_name, parameter4_type parameter4_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_FormatMessage(_INTLSTR_DOMAIN, id, parameter1_name, parameter2_name, parameter3_name, parameter4_name)); \
        } 

#elif defined(CONFIG_ENABLE_GETTEXT)

    #define Intlstr_Define4(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, parameter4_type, parameter4_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name, parameter3_type parameter3_name, parameter4_type parameter4_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_gettext_and_snprintf(_INTLSTR_DOMAIN, id, text, parameter1_name, parameter2_name, parameter3_name, parameter4_name)); \
        }

#else

    #define Intlstr_Define4(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, parameter4_type, parameter4_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name, parameter3_type parameter3_name, parameter4_type parameter4_name) \
        { \
            return _Intlstr_ReturnFormattedString(Stprintf_StrDup(PAL_T(text), parameter1_name, parameter2_name, parameter3_name, parameter4_name)); \
        }

#endif



#endif

PAL_END_EXTERNC

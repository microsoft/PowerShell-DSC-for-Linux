/*============================================================================
 * Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *============================================================================
 */
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28252 28253) //public wchar.h is giving errors about memcopy methods hence disabling it
#endif /* _PREFAST_ */

#include "mofcommon.h"
#include "types.h"
#include "buffer.h"
#include "utility.h"
#include "mof.qualifiers.h"
#include <pal/format.h>

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

#if defined (_MSC_VER) && defined(CONFIG_ENABLE_WCHAR)
#define UTIL_Szprintf formatmessage
#define UTIL_Vszprintf Vformatmessage

/* Call FormatMessage on windows platform to format localization string */
int Vformatmessage(
    _Out_writes_z_(size) wchar_t* buffer, 
    _In_ size_t size, 
    _In_z_ const wchar_t* format, 
    va_list ap)
{
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26036)
#endif /* _PREFAST_ */
    return (int)FormatMessageW(FORMAT_MESSAGE_FROM_STRING, format, 0, 0, buffer, (DWORD)size, &ap);
#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */
}

int formatmessage(
    _Out_writes_z_(size) wchar_t* buffer, 
    _In_ size_t size, 
    _In_z_ const wchar_t* format, 
    ...)
{
    int r;
    va_list ap;
    memset(&ap, 0, sizeof(ap));
    va_start(ap, format);
    r = Vformatmessage(buffer, size, format, ap);
    va_end(ap);
    return r;
}

#else
#define UTIL_Szprintf Stprintf
#define UTIL_Vszprintf Vstprintf
#endif

/*=============================================================================
**
** Global qualifiers definition, generated by moftool.exe
**
=============================================================================*/
MI_Boolean gQualval0 = MI_TRUE;
MI_Boolean gQualval1 = MI_FALSE;
MI_Char*   gQualval2 = MI_T("Bag");
MI_Uint32  gQualval3 = 0;
MI_Uint32  gQualval4 = 0;
MI_Char*   gQualval5 = MI_T("CurrentContext");
MI_QualifierDecl gQualifiers[] = {
    {MI_T("Association"), 0x00000000, 0x00000010, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Indication"), 0x00000000, 0x00000021, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Abstract"), 0x00000000, 0x00000031, 0x00000280, 0x00000000, (void*)&gQualval1},
    {MI_T("Aggregate"), 0x00000000, 0x00000040, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Aggregation"), 0x00000000, 0x00000010, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("ArrayType"), 0x0000000D, 0x0000000C, 0x00000500, 0x00000000, (void*)&gQualval2},
    {MI_T("BitMap"), 0x0000001D, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("BitValues"), 0x0000001D, 0x0000000E, 0x00000C80, 0x00000000, NULL},
    {MI_T("ClassConstraint"), 0x0000001D, 0x00000031, 0x00000000, 0x00000000, NULL},
    {MI_T("Composition"), 0x00000000, 0x00000010, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Correlatable"), 0x0000001D, 0x00000004, 0x00000000, 0x00000000, NULL},
    {MI_T("Counter"), 0x00000000, 0x0000000E, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("Deprecated"), 0x0000001D, 0x0000007F, 0x00000280, 0x00000000, NULL},
    {MI_T("Description"), 0x0000000D, 0x0000007F, 0x00000C80, 0x00000000, NULL},
    {MI_T("DisplayName"), 0x0000000D, 0x0000007F, 0x00000C80, 0x00000000, NULL},
    {MI_T("DN"), 0x00000000, 0x0000000E, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("EmbeddedInstance"), 0x0000000D, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("EmbeddedObject"), 0x00000000, 0x0000000E, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Exception"), 0x00000000, 0x00000021, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Experimental"), 0x00000000, 0x0000007F, 0x00000280, 0x00000000, (void*)&gQualval1},
    {MI_T("Gauge"), 0x00000000, 0x0000000E, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("In"), 0x00000000, 0x00000008, 0x00000500, 0x00000000, (void*)&gQualval0},
    {MI_T("IsPUnit"), 0x00000000, 0x0000000E, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("Key"), 0x00000000, 0x00000044, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("MappingStrings"), 0x0000001D, 0x0000007F, 0x00000000, 0x00000000, NULL},
    {MI_T("Max"), 0x00000005, 0x00000040, 0x00000000, 0x00000000, NULL},
    {MI_T("MaxLen"), 0x00000005, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("MaxValue"), 0x00000008, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("MethodConstraint"), 0x0000001D, 0x00000002, 0x00000000, 0x00000000, NULL},
    {MI_T("Min"), 0x00000005, 0x00000040, 0x00000000, 0x00000000, (void*)&gQualval3},
    {MI_T("MinLen"), 0x00000005, 0x0000000E, 0x00000000, 0x00000000, (void*)&gQualval4},
    {MI_T("MinValue"), 0x00000008, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("ModelCorrespondence"), 0x0000001D, 0x0000007F, 0x00000000, 0x00000000, NULL},
    {MI_T("Nonlocal"), 0x0000000D, 0x00000040, 0x00000000, 0x00000000, NULL},
    {MI_T("NonlocalType"), 0x0000000D, 0x00000040, 0x00000000, 0x00000000, NULL},
    {MI_T("NullValue"), 0x0000000D, 0x00000004, 0x00000500, 0x00000000, NULL},
    {MI_T("Octetstring"), 0x00000000, 0x0000000E, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Out"), 0x00000000, 0x00000008, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Override"), 0x0000000D, 0x00000046, 0x00000280, 0x00000000, NULL},
    {MI_T("Propagated"), 0x0000000D, 0x00000004, 0x00000500, 0x00000000, NULL},
    {MI_T("PropertyConstraint"), 0x0000001D, 0x00000044, 0x00000000, 0x00000000, NULL},
    {MI_T("PUnit"), 0x0000000D, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("Read"), 0x00000000, 0x00000004, 0x00000000, 0x00000000, (void*)&gQualval0},
    {MI_T("Required"), 0x00000000, 0x0000004E, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Revision"), 0x0000000D, 0x00000031, 0x00000C80, 0x00000000, NULL},
    {MI_T("Schema"), 0x0000000D, 0x00000006, 0x00000D00, 0x00000000, NULL},
    {MI_T("Source"), 0x0000000D, 0x00000031, 0x00000000, 0x00000000, NULL},
    {MI_T("SourceType"), 0x0000000D, 0x00000071, 0x00000000, 0x00000000, NULL},
    {MI_T("Static"), 0x00000000, 0x00000006, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Terminal"), 0x00000000, 0x00000031, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("UMLPackagePath"), 0x0000000D, 0x00000031, 0x00000000, 0x00000000, NULL},
    {MI_T("Units"), 0x0000000D, 0x0000000E, 0x00000C80, 0x00000000, NULL},
    {MI_T("ValueMap"), 0x0000001D, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("Values"), 0x0000001D, 0x0000000E, 0x00000C80, 0x00000000, NULL},
    {MI_T("Version"), 0x0000000D, 0x00000031, 0x00000A80, 0x00000000, NULL},
    {MI_T("Weak"), 0x00000000, 0x00000040, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("Write"), 0x00000000, 0x00000004, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("Alias"), 0x0000000D, 0x00000046, 0x00000C80, 0x00000000, NULL},
    {MI_T("Delete"), 0x00000000, 0x00000050, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("DisplayDescription"), 0x0000000D, 0x0000007F, 0x00000C80, 0x00000000, NULL},
    {MI_T("Expensive"), 0x00000000, 0x0000007F, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("Ifdeleted"), 0x00000000, 0x00000050, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("Invisible"), 0x00000000, 0x00000057, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("Large"), 0x00000000, 0x00000005, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("PropertyUsage"), 0x0000000D, 0x00000004, 0x00000000, 0x00000000, (void*)&gQualval5},
    {MI_T("Provider"), 0x0000000D, 0x0000007F, 0x00000000, 0x00000000, NULL},
    {MI_T("SyntaxType"), 0x0000000D, 0x0000004E, 0x00000000, 0x00000000, NULL},
    {MI_T("Syntax"), 0x0000000D, 0x0000004E, 0x00000000, 0x00000000, NULL},
    {MI_T("TriggerType"), 0x0000000D, 0x00000077, 0x00000000, 0x00000000, NULL},
    {MI_T("UnknownValues"), 0x0000001D, 0x00000004, 0x00000500, 0x00000000, NULL},
    {MI_T("UnsupportedValues"), 0x0000001D, 0x00000004, 0x00000500, 0x00000000, NULL},
    
    /* MSFT customized qualifiers */
    {MI_T("Stream"), 0x00000000, 0x0000000A, 0x00000500, 0x00000000, (void*)&gQualval1},
    {MI_T("ClassVersion"), 0x0000000D, 0x00000031, 0x00000280, 0x00000000, NULL},
    
    /* WMI specific qualifiers */
    {MI_T("Amendment"), 0x00000000, 0x00000001, 0x00000500, 0x00000000, (void*)&gQualval0},
    {MI_T("Bypass_GetObject"), 0x00000000, 0x00000002, 0x00000280, 0x00000000, (void*)&gQualval1},
    {MI_T("CIM_Key"), 0x00000000, 0x00000004, 0x00000000, 0x00000000, (void*)&gQualval1},
    {MI_T("CIMType"), 0x0000000D, 0x0000000E, 0x00000000, 0x00000000, NULL},
    {MI_T("ClassContext"), 0x0000000D, 0x00000001, 0x00000000, 0x00000000, NULL},
    {MI_T("Deprecated"), 0x00000000, 0x00000005, 0x00000000, 0x00000000, NULL},
    {MI_T("Display"), 0x00000000, 0x00000005, 0x00000000, 0x00000000, NULL},
    {MI_T("Dynamic"), 0x00000000, 0x00000005, 0x00000000, 0x00000000, (void*)&gQualval0},
    {MI_T("DynProps"), 0x00000000, 0x00000001, 0x00000000, 0x00000000, (void*)&gQualval0},
    {MI_T("ID"), 0x00000006, 0x0000000C, 0x00000500, 0x00000000, NULL},
    {MI_T("Implemented"), 0x00000000, 0x00000002, 0x00000280, 0x00000000, NULL},
    {MI_T("Locale"), 0x00000006, 0x00000001, 0x00000280, 0x00000000, NULL},
    {MI_T("Optional"), 0x00000000, 0x00000008, 0x00000280, 0x00000000, NULL},
    {MI_T("Privileges"), 0x0000001D, 0x00000006, 0x00000000, 0x00000000, NULL},
    {MI_T("PropertyContext"), 0x0000000D, 0x00000004, 0x00000000, 0x00000000, NULL},
    {MI_T("Provider"), 0x0000000D, 0x00000001, 0x00000000, 0x00000000, NULL},
    {MI_T("Singleton"), 0x00000000, 0x00000001, 0x00000000, 0x00000000, (void*)&gQualval0},
    {MI_T("Static"), 0x00000000, 0x00000002, 0x00000000, 0x00000000, NULL},
    {MI_T("SubType"), 0x0000000D, 0x00000004, 0x00000000, 0x00000000, NULL},
    {MI_T("UUID"), 0x0000000D, 0x00000001, 0x00000000, 0x00000000, NULL},
    {MI_T("WritePrivileges"), 0x0000001D, 0x00000004, 0x00000000, 0x00000000, NULL},

    /* DSC specific qualifiers */
    {MI_T("FriendlyName"), 0x0000000D, 0x00000001, 0x00000280, 0x00000000, NULL},
    {NULL, 0, 0, 0, 0, NULL},
};

/*=============================================================================
**
** Get character from UTF16 Big Endian buffer
**
=============================================================================*/
int mof_getUTF16bechar(void * data)
{
    /* Read byte by byte to avoid memory alignment issue,
       one wide character could span 2 pages,
       some platform might have problem.*/
    /* Does not support two 16bit UTF16BE character(s) */
    char *p = (char*)data;
    int c = p[0];
    int d = p[1];
    c += d << 8;
    return c;
}

/*=============================================================================
**
** Get character from buffer
**
=============================================================================*/
int mof_getchar(MOF_Encoding e, void * data)
{
    if (e.u)
    {
        if (e.t == UTF16LE || e.t == UNI)
        {
            /* Read byte by byte to avoid memory alignment issue,
               one wide character could span 2 pages,
               some platform might have problem.*/
            return *(wchar_t*)data;
        }
        else
        {
            return mof_getUTF16bechar(data);
        }
    }
    else
    {
        return (*(char*)data);
    }
}

/*=============================================================================
**
** Move to next char of buffer
**
=============================================================================*/
void * mof_nextcharofbuf(MI_Boolean u, void * data)
{
    char* p = (char *)data;
    return (u) ? p + sizeof(wchar_t) : p + sizeof(char);
}


/*=============================================================================
**
** Move to next char of mof buffer;
** return 0 means either reach to the end of buf or null terminator of string
**
=============================================================================*/
_Use_decl_annotations_
int mof_nextchar(MOF_Buffer * b)
{
    int c;
    char* p = (char *)b->cur;
    MOF_Encoding e = b->e;
    /* check current char */
    c = mof_getchar(e, b->cur);
    if (c == '\n')
    {
        b->charPosOfLine = 0;
        b->lineNo ++;
    }
    else
    {
        b->charPosOfLine ++;
    }

    b->cur = (e.u) ? p+sizeof(wchar_t) : p+sizeof(char);
    if (b->cur >= b->end)
    {
        return 0;
    }
    return mof_getchar(e, b->cur);
}

/*=============================================================================
**
** Move to next char of mof buffer; Increase length
**
=============================================================================*/
_Use_decl_annotations_
int mof_nextcharn(MOF_Buffer * b, size_t *len)
{
    (*len)++;
    return mof_nextchar(b);
}


/*=============================================================================
**
** Reach to the end of the buffer?
**
=============================================================================*/
_Use_decl_annotations_
MI_Boolean mof_eof(MOF_Buffer * b)
{
    if (b->cur >= b->end) return MI_TRUE;
    if (b->e.u)
    {
        /* In case of buffer size is not aligned with sizeof(wchar_t) */
        ptrdiff_t pnextchar = ((ptrdiff_t)b->cur) + sizeof(wchar_t);
        if (pnextchar > (ptrdiff_t)b->end) return MI_TRUE;
    }
    return (mof_getchar(b->e, b->cur) == 0);
}

_Use_decl_annotations_
MI_Boolean mof_neof(MOF_Buffer * b)
{
    return !mof_eof(b);
}

/*=============================================================================
**
** Utilities of check current char
**
=============================================================================*/
MI_Boolean mof_isdoulbequotes(MOF_Encoding e, void * data)
{
    return mof_getchar(e, data) == '"';
}

MI_Boolean mof_isbackslash(MOF_Encoding e, void * data)
{
    return mof_getchar(e, data) == '\\';
}

MI_Boolean mof_isminus(MOF_Encoding e, void * data)
{
    return mof_getchar(e, data) == '-';
}

MI_Boolean mof_isplus(MOF_Encoding e, void * data)
{
    return mof_getchar(e, data) == '+';
}

MI_Boolean mof_isdigit(MOF_Encoding e, void * data)
{
    return isdigit(mof_getchar(e, data)) != 0;
}

/*=============================================================================
**
** Is current char a space
**
=============================================================================*/
MI_Boolean mof_isspace(MOF_Encoding e, void * data)
{
    /* todo: switch to char(s) comparison */
    return isspace(mof_getchar(e, data)) != 0;
}

/*=============================================================================
**
** Is current char alphabit [a-zA-Z]
**
=============================================================================*/
MI_Boolean mof_isalpha(MOF_Encoding e, void * data)
{
    return isalpha(mof_getchar(e, data)) != 0;
}

/*=============================================================================
**
** Is current char a numeric [0-9]
**
=============================================================================*/
MI_Boolean mof_isalnum(MOF_Encoding e, void * data)
{
    return isalnum(mof_getchar(e, data)) != 0;
}

/*=============================================================================
**
** Is current char a '_'
**
=============================================================================*/
MI_Boolean mof_isunderscore(MOF_Encoding e, void * data)
{
    return mof_getchar(e, data) == (int)'_';
}


/*=============================================================================
**
** Get current buffer pointer location, i.e., number of characters from
** beginning of the buffer.
**
=============================================================================*/
_Use_decl_annotations_
size_t mof_offset(MI_Boolean unicode, void * orgdata, void *curdata)
{
    return (unicode) ? ((wchar_t*)curdata - (wchar_t*)orgdata) : ((char*)curdata - (char*)orgdata);
}


/*=============================================================================
**
** Generate hashcode for string in format of following
** 0x00[F][L][N]
**      F- first char in lower case
**      L- last char in lower case
**      N- string length
**
=============================================================================*/
_Use_decl_annotations_
void mof_getcode(MI_Boolean unicode, MOF_StringLen *r)
{
    size_t len = r->len;
    unsigned int code = 0;
    int c;
    
    c = unicode ? PAL_tolower(r->str.wstr[0]) : PAL_tolower(r->str.str[0]);
    code += (c << 16);
    c = unicode ? PAL_tolower(r->str.wstr[len -1]) : PAL_tolower(r->str.str[len -1]);
    code += (c << 8);
    code += (unsigned char)(len);
    r->code = code;
}

/*=============================================================================
**
** Case insensitive comparison of strings
**
=============================================================================*/
_Use_decl_annotations_
int mof_ncasecmp(MI_Boolean u, void *s1, void * s2, size_t n)
{
    return (u) ? Wcsncasecmp((wchar_t*)s1, (wchar_t*)s2, n) : Strncasecmp((char*)s1, (char*)s2, n);
}

/*=============================================================================
**
** Convert string to unsigned long integer
**
=============================================================================*/
_Use_decl_annotations_
MI_Boolean mof_strtoul(MI_Boolean unicode, void * data, int radix, void * endchar, unsigned long *result)
{
    if (unicode)
    {
        wchar_t * end;
        *result = wcstoul((wchar_t*)data, &end, radix);
        if (endchar)
        {
            if (*end != *((wchar_t*)endchar)) return MI_FALSE;
        }
        else if ((void*)end == data) return MI_FALSE;
    }
    else
    {
        char * end;
        *result = strtoul((char*)data, &end, radix);
        if (endchar)
        {
            if (*end != *((char*)endchar)) return MI_FALSE;
        }
        else if ((void*)end == data) return MI_FALSE;
    }
    return MI_TRUE;
}

void * mof_getprevcharpos(MI_Boolean unicode, void * data)
{
    char* p = (char *)data;
    return (unicode) ? p-sizeof(wchar_t) : p-sizeof(char);
}

/*=============================================================================
**
** Convert string to double
**
=============================================================================*/
_Use_decl_annotations_
MI_Real64 mof_strtod(MI_Boolean unicode, void * data)
{
    if (unicode)
    {
        return wcstod((wchar_t*)data, NULL);
    }
    else
    {
        return strtod((char*)data, NULL);
    }
}


/*=============================================================================
**
** Convert string to MI_Sint64
**
=============================================================================*/
_Use_decl_annotations_
MI_Sint64 mof_strtoll(MI_Boolean unicode, void * data, void ** endchar, int base)
{
    if (unicode)
    {
        return Wcstoll((wchar_t*)data, (wchar_t**)endchar, base);
    }
    else
    {
        return Strtoll((char*)data, (char**)endchar, base);
    }
}

/*=============================================================================
**
** Convert string to unsigned int
**
=============================================================================*/
_Use_decl_annotations_
MI_Sint64 mof_strtoull(MI_Boolean unicode, void * data, void ** endchar, int base)
{
    if (unicode)
    {
#if defined(_MSC_VER)        
        return (MI_Sint64)Wcstoull((wchar_t*)data, (wchar_t**)endchar, base);
#else
        return (MI_Sint64)Tcstoull((TChar*)data, (TChar**)endchar, base);
#endif

    }
    else
    {
        return (MI_Sint64)Strtoull((char*)data, (char**)endchar, base);
    }
}

/*=============================================================================
**
** Convert UTF16 big endian string to little endian
** !!Only support characters of one wchar_t !!
** !!characters represented by two wchar_t(s) to be supported!!
**
=============================================================================*/
_Use_decl_annotations_
int mof_converttoUTF16LE(MOF_State * state, MOF_StringLen *r)
{
    MOF_Encoding e = state->buf.e;
    if (e.u)
    {
        if(e.t == UTF16BE || e.t == UNIBE)
        {
            wchar_t * s = (wchar_t *)r->str.data;
            wchar_t * d;
            size_t i = 0;
            r->str.data = Batch_Get(state->batch, r->len * sizeof(wchar_t));
            if (r->str.data == NULL)
            {
                yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
                return -1;
            }
            d = (wchar_t *)r->str.data;
            while(i < r->len)
            {
                d[i] = (wchar_t)mof_getUTF16bechar(s);
                i++;
                s++;
            }
        }
    }
    return 0;
}

_Use_decl_annotations_
MI_Result mof_setupbuffer(void * data, size_t nBytes, Batch *batch, MOF_Buffer * b)
{
    MOF_ENCODING_TYPE e = ANSI;
    unsigned char *p = (unsigned char *)data;
    memset(b, 0, sizeof(MOF_Buffer));

    _Analysis_assume_(nBytes >= 4);
    {        
        unsigned char c1 = p[0];
        unsigned char c2 = p[1];
        unsigned char c3 = p[2];
        unsigned char c4 = p[3];
        if (c1 == 0xFE && c2 == 0xFF)
        {
            e = UTF16BE;
        }
        else if (c1 == 0xFF && c2 == 0xFE)
        {
            if (c3 == 0 && c4 == 0) // UTF-32 LE
            {
                return MI_RESULT_NOT_SUPPORTED;
            }
            // UTF-16 LE
            e = UTF16LE;
        }
        else if (c1 == 0xEF && c2 == 0xBB && c3 == 0xBF) // UTF-8
        {
            e = UTF8;
        }
        else if (c1 == 0 && c2 == 0 && c3 == 0xFE && c4 == 0xFF) // UTF-32 BE
        {
            return MI_RESULT_NOT_SUPPORTED;
        }
        else if (c1 > 0 && c2 == 0)
        {
            e = UNI;
        }
        else if (c1 == 0 && c2 > 0)
        {
            e = UNIBE;
        }
        else if (c1 ==0 && c2 == 0)
        {
            return MI_RESULT_NOT_SUPPORTED;
        }

        b->e.t = e;
        b->e.o = 0;
        switch(e)
        {
        case UTF8:
            b->e.o = 3;
        case ANSI:
            b->e.u = MI_FALSE;
            break;
        case UTF16LE:
        case UTF16BE:
            b->e.o = 2;
        case UNI:
        case UNIBE:
            b->e.u = MI_TRUE;
            break;
        }
    }
#if !defined(_MSC_VER) 
    /* wchar_t in unix is 4 bytes. Buffer may be coming from windows with proper encoding of UTF-16 ( 2 bytes).
            Once we determine the encoding we appropriately convert it to ASCII on linux. We can't handle 
            characters in unix that doesn't fall under 0<=x<=255. We reject the requests in those cases.*/
    if( b->e.u )
    {
        size_t xCount = 0;
        unsigned short *tempBuf = (unsigned short *) ((unsigned char*)data + b->e.o);
        unsigned char *nullPointer = ((unsigned char*)data + b->e.o + 1);
        // convert UTF to ASCII
        if(( nBytes%2) || !batch)
        {
            return MI_RESULT_NOT_SUPPORTED;
        }
        if( b->e.t == UTF16BE || b->e.t == UNIBE )
        {
            tempBuf = (unsigned short *) ((unsigned char*)data + b->e.o + 1);
            nullPointer = ((unsigned char*)data + b->e.o);
        }
        nBytes = (nBytes-2)/2;
        // allocate memory to hold ascii
        p = (unsigned char*) Batch_Get(batch, nBytes);
        if (p == NULL) return MI_RESULT_SERVER_LIMITS_EXCEEDED;        
        for(; xCount < nBytes; xCount++ )
        {
            if( *nullPointer != '\0' )
                return MI_RESULT_NOT_SUPPORTED;
            
            p[xCount] = (unsigned char) tempBuf[xCount];
            nullPointer +=2;
        }
        b->e.u = MI_FALSE;
        b->e.o = 0;
        b->e.t = ANSI;
    }
#endif
    if(b->e.u && (ptrdiff_t)(p) % (sizeof(wchar_t)) != 0)
    {
        /* Buffer is not alighed with sizeof(wchar_t) */
        /* Need to copy input buffer to alighed memory */   
        if (batch)
        {
            p = (unsigned char*)Batch_Get(batch, nBytes);
            if (p == NULL) return MI_RESULT_SERVER_LIMITS_EXCEEDED;
            memcpy(p, data, nBytes);
        }
        else
        {
            return MI_RESULT_NOT_SUPPORTED;
        }
    }
    b->buf = p;
    b->len = (MI_Uint32)nBytes;
    b->end = p + b->len;
    b->cur = ((char *)b->buf) + b->e.o;
    b->lineNo = 1; /* lineno start from 1 */
    return MI_RESULT_OK;
}

void mof_setupbuffer_intl(
    _In_reads_bytes_(nBytes) void * data,
    _In_ size_t nBytes,
    _In_ MOF_Encoding e,
    _Inout_ MOF_Buffer * b)
{
    unsigned char *p = (unsigned char *)data;
    b->buf = p;
    b->len = (MI_Uint32)nBytes;
    b->end = p + b->len;
    b->e = e;
    b->cur = b->buf;
}

MI_Boolean mof_match(MOF_Encoding e, _In_ MOF_StringLen *data, _In_ MOF_StringLen *pattern)
{
    unsigned char cset[256];
    MOF_Buffer d = {0}, p ={0};
    if (!(data->str.data) || !(pattern->str.data))
    {
        return MI_FALSE;
    }

    /* setup buffers for matching */
    {
        size_t ds = data->len * (e.u ? sizeof(wchar_t) : sizeof(char));
        size_t ps = pattern->len * (e.u ? sizeof(wchar_t) : sizeof(char));
        mof_setupbuffer_intl(data->str.data, ds, e, &d);
        mof_setupbuffer_intl(pattern->str.data, ps, e, &p);
    }

    while (mof_neof(&p))
    {
        int c = mof_getchar(p.e, p.cur);
        switch(c)
        {
        case '[':
            // a set, find ']', and read one more char, a char after ']' could be '*', '?', '+'
            // only support [x-ym-n] [xyz]
            {
                int c1, c2, c3;
                int ci;
                memset(cset, 0, 256*sizeof(unsigned char));
                c1 = mof_nextchar(&p);
                while(mof_neof(&p) && (c1 != ']'))
                {
                    c2 = mof_nextchar(&p);
                    if (isalnum(c1) && c2 == '-')
                    {
                        c3 = mof_nextchar(&p);
                        for (ci = c1; ci <= c3; ci++)
                        {
                            cset[ci] = 1;
                        }
                    }
                    else
                    {
                        _Analysis_assume_(c1 < 256);
                        _Analysis_assume_(c2 < 256);
                        cset[c1] = cset[c2] = 1;
                    }
                    c1 = mof_nextchar(&p);
                }
                if (mof_eof(&p))
                {
                    return MI_FALSE;
                }
                c1 = mof_nextchar(&p);
                switch(c1)
                {
                case '*':// 0+ match
                    {
                        while(mof_neof(&d))
                        {
                            if (cset[mof_getchar(d.e, d.cur)] != 1)
                                break;
                            mof_nextchar(&d);
                        }
                    }
                    mof_nextchar(&p);
                    break;
                case '+':// 1+ match
                    {
                        int dc;
                        if (mof_eof(&d))
                            return MI_FALSE;

                        // match first char
                        if (cset[mof_getchar(d.e, d.cur)] != 1)
                        {
                            return MI_FALSE;
                        }

                        dc = mof_nextchar(&d);
                        while(mof_neof(&d))
                        {
                            if (cset[dc] != 1)
                                break;
                            dc = mof_nextchar(&d);
                        }
                    }
                    mof_nextchar(&p);
                    break;
                case '?':// 0 or 1 match
                    {
                        if (mof_neof(&d))
                        {
                            if (cset[mof_getchar(d.e, d.cur)] == 1)
                            {
                                mof_nextchar(&d);
                            }
                        }
                    }
                    mof_nextchar(&p);
                    break;
                default: // 1 match
                    {
                        if (mof_eof(&d))
                            return MI_FALSE;

                        // have to match one char
                        if (cset[mof_getchar(d.e, d.cur)] != 1)
                        {
                            return MI_FALSE;
                        }
                        mof_nextchar(&d);
                    }
                    break;
                }
            }
            break;
        case '(':
            // only support '()?' pattern which at the end, for realvalue only
            {
                if (mof_neof(&d))
                {
                    MOF_StringLen d2;
                    MOF_StringLen p2;
                    d2.str.data = d.cur;
                    d2.len = data->len - mof_offset(d.e.u, data->str.data, d.cur);
                    mof_nextchar(&p);
                    p2.str.data = p.cur;
                    p2.len = pattern->len - mof_offset(p.e.u, pattern->str.data, p.cur) -2;
                    return mof_match(e, &d2, &p2);
                }
                else // in this case, it is matched
                {
                    return MI_TRUE;
                }
            }
            break;
        default:
            // single char match
            {
                if (mof_eof(&d))
                    return MI_FALSE;
                if (c != mof_getchar(d.e, d.cur))
                    return MI_FALSE;
                mof_nextchar(&d);
                mof_nextchar(&p);
            }
            break;
        }
    }

    if (mof_eof(&p) && mof_eof(&d)) return MI_TRUE;
    return MI_FALSE;
}

void* MOF_Realloc(Batch* batch, void* ptr, size_t orgsize, size_t size)
{
    void * p;
    void * q;
    if (!batch)
        return NULL;

    if (!ptr)
        return Batch_GetClear(batch, size);

    p = Batch_Get(batch, size);

    if (!p)
        return NULL;
    
    memcpy(p, ptr, orgsize);

    q = (char*)p + orgsize;
    memset(q, 0, size-orgsize);
    return p;
}


/*
**==============================================================================
**
** Error handling functions
**
**==============================================================================
*/
_Use_decl_annotations_
void moferror(MOF_ErrorHandler *errhandler, const char* msg)
{
    /* 
     * There is no way to inject a localization string identifier before
     * calling this function (it is called from generated code). So instead,
     * we map the set of known strings to identifiers below.
     */
    if (strcmp(msg, "syntax error") == 0)
    {
        yyerrorf(errhandler, ID_SYNTAX_ERROR, msg, MI_T(""));
    }
    else if (strcmp(msg, "yacc stack overflow") == 0)
    {
        yyerrorf(errhandler, ID_PARSER_STACK_OVERFLOW, "", msg);
    }
    else
    {
        yyerrorf(errhandler, ID_INTERNAL_ERROR, msg, MI_T(""));
    }
}

/* fill up the error details */
#define MSG_BUF_SIZE 256
#define CONTENT_SIZE 16
_Post_z_
MI_Char* geterrordetails(_In_ MOF_State *state)
{
    MI_Char buf[MSG_BUF_SIZE];
    const MI_Char* fileName = state->path;
    const MI_Char* format = NULL;
    MI_Char* targetBuf = state->errhandler->errormsg;
    MI_Char* currentBuf = targetBuf;
    int nTargetBufLength = MI_COUNT(state->errhandler->errormsg);
    int n;
    if (fileName)
    {
        /* Always success */
        format = state->errhandler->stringLookup(
            ID_ERROR_DETAILS_INCLUDED_FILE,
            buf,
            MI_COUNT(buf));
        n = UTIL_Szprintf(currentBuf, nTargetBufLength, format, fileName, state->buf.lineNo, state->buf.charPosOfLine);
    }
    else
    {
        /* Always success */
        format = state->errhandler->stringLookup(
            ID_ERROR_DETAILS,
            buf,
            MI_COUNT(buf));
        n = UTIL_Szprintf(currentBuf, nTargetBufLength, format, state->buf.lineNo, state->buf.charPosOfLine);
    }
    if (n >= nTargetBufLength)
    {
        return targetBuf;
    }
    currentBuf += n;
    format = state->errhandler->stringLookup(
        ID_ERROR_DETAILS_CONTENT,
        buf,
        MI_COUNT(buf));
    nTargetBufLength -= n;
    {
        MI_Char tempbuf[CONTENT_SIZE*2 + 2] = {0};
        mof_fillbuf(&state->buf, tempbuf, MI_COUNT(tempbuf));
        UTIL_Szprintf(currentBuf, nTargetBufLength, format, tempbuf);
    }
    return targetBuf;
}

_Use_decl_annotations_
void yyerrorf(MOF_ErrorHandler *errhandler, int id, const char * fmt, ...)
{
    MI_Char buf[MSG_BUF_SIZE];
    int n;
    va_list ap;
    MI_Char* errorDetails;
    MI_Char* format;
    MI_UNREFERENCED_PARAMETER(fmt);
    if (!errhandler)
    {
        return;
    }
    format = errhandler->stringLookup(
        id,
        errhandler->errormsg,
        MI_COUNT(errhandler->errormsg));

    
    /* Dump error message */
    memset(&ap, 0, sizeof(ap));
    va_start(ap, fmt);
    n = UTIL_Vszprintf(buf, MI_COUNT(buf), format, ap);
    va_end(ap);

    /* Dump mof buffer details */
    if (errhandler->state)
    {
        errorDetails = geterrordetails((MOF_State*)errhandler->state);
        Stprintf(buf + n, MI_COUNT(buf) - n, MI_T("%T"), errorDetails);
    }

    /* Report final error */
    ReportFinalError(errhandler, id, buf);
}

_Use_decl_annotations_
void yywarnf(MOF_ErrorHandler *errhandler, int id, const char *fmt, ...)
{
    MI_UNREFERENCED_PARAMETER(errhandler);
    MI_UNREFERENCED_PARAMETER(id);
    MI_UNREFERENCED_PARAMETER(fmt);
#if 0
    MOF_State * state = (MOF_State *)mofstate;
#if defined(_MSC_VER)
    wchar_t* wformat = NULL;
    if (state->stringLookup)
    {
        wformat = state->stringLookup(
            id,
            state->errormsg,
            MI_COUNT(state->errormsg));
    }
    if (wformat)
    {
        wchar_t buf[1024];
        int n;
        va_list ap;

        n = _snwprintf_s(buf, MI_COUNT(buf), _TRUNCATE, L"%S(%u): ", 
            state->path, state->buf.lineNo);
        va_start(ap, format);
        _vsnwprintf_s(buf + n, MI_COUNT(buf) - n, _TRUNCATE, wformat, ap);
        va_end(ap);

        if (state->warningCallback)
            (*state->warningCallback)(NULL, buf, state->warningCallbackData);
    }
    else
#endif
    {
        char buf[1024];
        int n;
        va_list ap;
	memset(&ap, 0, sizeof(ap));

        MI_UNUSED(id);

        n = Snprintf(buf, sizeof(buf), "%s(%u): ", state->path, 
            state->buf.lineNo);
        va_start(ap, format);
        Vsnprintf(buf + n, sizeof(buf) - n, format, ap);
        va_end(ap);

        if (state->warningCallback)
            (*state->warningCallback)(buf, NULL, state->warningCallbackData);

        PtrArray_Append(state, &state->warnings, Batch_Strdup(state->batch, buf));
    }
#endif
}

_Use_decl_annotations_
void ReportFinalError(
    MOF_ErrorHandler* errhandler,
    int id,
    MI_Char* formattedMSG)
{
    MI_Uint32 errorCode = MI_RESULT_FAILED;
    MI_Uint16 errorCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
    const MI_Char* errorType = MI_RESULT_TYPE_MI;
    switch (id)
    {
    case ID_OUT_OF_MEMORY:
#if defined(_MSC_VER)
        errorCode = (MI_Uint32)E_OUTOFMEMORY;
        errorType = MI_RESULT_TYPE_HRESULT;
#else
        errorCode = ENOMEM;
        errorType = MI_T("STDC"); /* todo: Fixup error type for non-win */
#endif
        errorCategory = MI_ERRORCATEGORY_LIMITS_EXCEEDED;
        break;
    case ID_CREATE_PARSER_FAILED:
        break;
    case ID_PARAMETER_INVALID_OPTIONS_VALUE:
    case ID_PARAMETER_INVALID_VALUE_STRING:
    case ID_PARAMETER_INVALID_VALUE_NULL:
    case ID_PARAMETER_INVALID_VALUE_UNEXPECTED_INTEGER:
    case ID_PARAMETER_INVALID_VALUE_OUT_OF_RANGE_INTEGER:
    case ID_PARAMETER_INVALID_BUFFER:
        errorCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    default:
        errorCategory = MI_ERRORCATEGORY_SYNTAX_ERROR;
        errorType = MI_RESULT_TYPE_MOF_PARSER;
        errorCode = id;
        break;
    }
    if (errhandler->onError)
    {
        errhandler->onError(
            errhandler->onErrorContext,
            errorCode,
            errorCategory,
            errorType,
            formattedMSG);
    }
}

_Use_decl_annotations_
void mof_fillbuf(
    MOF_Buffer* b,
    MI_Char *buf,
    MI_Uint32 size)
{
    static MI_Uint32 snprefix = 8;
    MI_Uint32 i = 0;
    MI_Uint32 n = size - snprefix - 2;
    char * bufstart = (char*)b->buf + b->e.o;
    MI_Uint32 o = (MI_Uint32)mof_offset(b->e.u, bufstart, b->cur);
    MI_Uint32 bs = (o > n) ? n : o;
    MI_Uint32 tmax = bs + snprefix;
    MI_Uint32 bbytes = (b->e.u) ? bs * sizeof(wchar_t) : bs * sizeof(char);
    char *newCur = (char*)b->cur -bbytes;
    MOF_Buffer temp;
    MI_Boolean flaged = MI_FALSE;
    memcpy(&temp, b, sizeof(MOF_Buffer));
    temp.cur = newCur;
    _Analysis_assume_(size > 2);
    while (i < (size - 2))
    {
        if ((i >= tmax) || mof_eof(&temp))
        {
            break;
        }
        if (i == bs)
        {
            buf[i++] = '^';
            flaged = MI_TRUE;
        }
        if (i < tmax)
        {
            buf[i++] = (MI_Char)mof_getchar(temp.e, temp.cur);
        }
        mof_nextchar(&temp);
    }
    if (!flaged)
    {
        buf[i++] = '^';
    }
    buf[i] = 0;
}

void* mof_setchar(MI_Boolean unicode, _In_ void * data, int c)
{
    if (unicode)
    {
        wchar_t* p = (wchar_t*)data;
        *p = (wchar_t)c;
        return (p+1);
    }
    else
    {
        char* p = (char*)data;
        *p = (char)c;
        return (p+1);
    }
}

MI_Boolean _mof_ishex(int c)
{
    if (c <= '9' && c >= '0') return MI_TRUE;
    if (c <= 'F' && c >= 'A') return MI_TRUE;
    if (c <= 'f' && c >= 'a') return MI_TRUE;
    return MI_FALSE;
}

MI_Boolean mof_isvalidhexstring(MI_Boolean unicode, void * data, size_t length)
{
    size_t i = 0;
    for (; i < length; i++)
    {
        if (MI_FALSE == _mof_ishex(unicode ? ((wchar_t*)data)[i] : ((char*)data)[i]))
            return MI_FALSE;
    }
    return MI_TRUE;
}


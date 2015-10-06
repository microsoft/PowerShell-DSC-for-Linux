/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <MI.h>
#include "DSC_Systemcalls.h"
#include "EventWrapper.h"


#if defined(_MSC_VER)
#include "Win32_EngineHelper.h"
ConfigurationDetails g_ConfigurationDetails = { 0, 0, MI_FALSE };
#else
#include <pal/cpu.h>
ConfigurationDetails g_ConfigurationDetails;
static FILE *_DSCos;
static Log_Level _DSClevel = OMI_WARNING;
#define FMTSIZE 1024
#endif 


/* Windows Functionas*/
#if defined(_MSC_VER)


unsigned long DSC_EventRegister()
{
    return EventRegisterMicrosoft_Windows_DSC();
}

unsigned long DSC_EventUnRegister()
{
    return EventUnregisterMicrosoft_Windows_DSC();
}

#else

/* Non-windows implementation*/
static const char* _levelDSCStrings[] =
{
    "FATAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
    "VERBOSE",
};

#define TIMESTAMP_SIZE 128

static int _GetDSCTimeStamp(_Pre_writable_size_(TIMESTAMP_SIZE) char buf[TIMESTAMP_SIZE])
{
    MI_Uint64 usec = (MI_Uint64) CPU_GetTimeStamp();
    time_t t = usec / 1000000;
    struct tm tm;
    localtime_r(&t, &tm);
    snprintf(
        buf,
        TIMESTAMP_SIZE,
        "%02u/%02u/%02u %02u:%02u:%02u",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec);
    return 0;
}

static void _PutDSCHeader(
    FILE* os, 
    const char* file, 
    unsigned int line, 
    Log_Level level)
{
    char buf[TIMESTAMP_SIZE];

    _GetDSCTimeStamp(buf);
    Ftprintf(os, ZT("%s: "), scs(buf));
    Ftprintf(os, ZT("%s: "), scs(_levelDSCStrings[(int)level]));

    if (file)
        Ftprintf(os, ZT("%s(%u): "), scs(file), line);
}


int DSCLog_VPut(
    Log_Level level,
    const char* file,
    MI_Uint32 line,
    const ZChar* format,
    va_list ap)
{
    if (!_DSCos || level > _DSClevel)
        return 0;

    file = scs(file);

    _PutDSCHeader(_DSCos, file, line, level);

    Vftprintf(_DSCos, format, ap);

    Ftprintf(_DSCos,ZT("\n"));
    fflush(_DSCos);
    return 1;
}

void DSCFilePutLog(
    int priority,
    int eventId,
    const char * file,
    int line,
    const PAL_Char* format,
    ...)
{
    if ((unsigned int)priority > OMI_VERBOSE)
        return;

    if (priority <= _DSClevel)
    {
        TChar fmt[FMTSIZE];
        va_list ap;

        Stprintf(fmt, FMTSIZE, PAL_T("EventId=%d Priority=%s "), priority, _levelDSCStrings[priority]);
        Tcslcat(fmt, format, FMTSIZE);
                
        va_start(ap, format);
        DSCLog_VPut((Log_Level)priority, file, line, fmt, ap);
        va_end(ap);        
    }    
}


void DSCLog_Close()
{
    if (_DSCos && _DSCos != stderr)
    {
        fclose(_DSCos);
        _DSCos = NULL;
    }
}

MI_Result DSCLog_Open(
    const ZChar* path,
    Log_Level level)
{
    if (!path || _DSCos)
        return MI_RESULT_FAILED;

    _DSClevel = level;    
#if (MI_CHAR_TYPE == 1)
    {
        _DSCos = fopen(path, "a");

        if (!_DSCos)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }
#else
    {
        char path7[PAL_MAX_PATH_SIZE];
        if (StrWcslcpy(path7, path, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return MI_RESULT_FAILED;
        
        _DSCos = fopen(path7, "a");

        if (!_DSCos)
        {
            return MI_RESULT_FAILED;
        }

        return MI_RESULT_OK;
    }
#endif
}


unsigned long DSC_EventRegister()
{
    char logpath[PAL_MAX_PATH_SIZE];
#if defined(BUILD_OMS)
    Strlcpy(logpath, "/var/opt/microsoft/omsconfig", PAL_MAX_PATH_SIZE);
    Strlcat(logpath, "/", PAL_MAX_PATH_SIZE);
    Strlcat(logpath, "omsconfig.log", PAL_MAX_PATH_SIZE);
#else
    Strlcpy(logpath, OMI_GetPath(ID_LOGDIR), PAL_MAX_PATH_SIZE);
    Strlcat(logpath, "/", PAL_MAX_PATH_SIZE);
    Strlcat(logpath, "dsc.log", PAL_MAX_PATH_SIZE);
#endif
    DSCLog_Open(logpath, OMI_VERBOSE);
    return 0;
}

unsigned long DSC_EventUnRegister()
{
    DSCLog_Close();
    return 0;
}
#endif

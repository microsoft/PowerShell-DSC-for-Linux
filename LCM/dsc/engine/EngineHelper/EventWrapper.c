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
#include <pal/cpu.h>
#include <unistd.h>

ConfigurationDetails g_ConfigurationDetails;
static FILE *_DSCLogFile;
static FILE *_DSCDetailedLogFile;
static Log_Level _DSCLogLevel = OMI_WARNING;
static Log_Level _DSCDetailedLogLevel = OMI_VERBOSE;

#define FMTSIZE 1024
#define MSGSIZE 4096
#define TIMESTAMP_SIZE 128

static const char* _levelDSCStrings[] =
{
    "FATAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
    "VERBOSE",
};


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
    FILE * logFile,
    Log_Level level,
    Log_Level maxLevel,
    const char* file,
    MI_Uint32 line,
    const ZChar* format,
    va_list ap)
{
    if (!logFile || level > maxLevel)
        return 0;

    file = scs(file);

    _PutDSCHeader(logFile, file, line, level);

    Vftprintf(logFile, format, ap);

    Ftprintf(logFile,ZT("\n"));
    fflush(logFile);
    return 1;
}

void DSCFileVPutTelemetry(
        Log_Level level,
        int eventId,
        const char* file,
        MI_Uint32 line,
        const ZChar* format,
        va_list ap
    )
{
    FILE *telemetry_file = fopen("/var/opt/microsoft/omsconfig/status/omsconfighost", "a");

    if (telemetry_file == NULL)
        return;

    char timestamp_buffer[TIMESTAMP_SIZE];
    _GetDSCTimeStamp(timestamp_buffer);

    int current_pid = getpid();

    Ftprintf(telemetry_file, PAL_T("<OMSCONFIGLOG>[%s] [%d] [%s] [%d] [%s:%d] "), timestamp_buffer, current_pid, _levelDSCStrings[level], eventId, file, line);
    Vftprintf(telemetry_file, format, ap);
    Ftprintf(telemetry_file, PAL_T("</OMSCONFIGLOG>\n"));

    fflush(telemetry_file);
    fclose(telemetry_file);
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

    if (priority <= _DSCDetailedLogLevel)
    {
        TChar fmt[FMTSIZE];
        va_list ap;

        Stprintf(fmt, FMTSIZE, PAL_T("EventId=%d Priority=%s "), priority, _levelDSCStrings[priority]);
        Tcslcat(fmt, format, FMTSIZE);
                
        va_start(ap, format);
        // Write warning and error level logs
        DSCLog_VPut(_DSCLogFile, (Log_Level)priority, _DSCLogLevel, file, line, fmt, ap);
        va_end(ap);

        va_start(ap, format);
        // Write all the logs
        DSCLog_VPut(_DSCDetailedLogFile, (Log_Level)priority, _DSCDetailedLogLevel, file, line, fmt, ap);
        va_end(ap);

        if (priority <= OMI_WARNING)
        {
            va_start(ap, format);
            DSCFileVPutTelemetry(priority, eventId, file, line, format, ap);
            va_end(ap);
        }
    }
}

void DSCFilePutTelemetry(
    int priority,
    int eventId,
    const char * file,
    int line,
    const PAL_Char* format,
    ...)
{
    FILE *telemetry_file = fopen("/var/opt/microsoft/omsconfig/status/omsconfighost", "a");

    if (telemetry_file == NULL)
        return;

    va_list ap;

    char timestamp_buffer[TIMESTAMP_SIZE];
    _GetDSCTimeStamp(timestamp_buffer);

    int current_pid = getpid();

    va_start(ap, format);
    Ftprintf(telemetry_file, PAL_T("<OMSCONFIGLOG>[%s] [%d] [%s] [%d] [%s:%d] "), timestamp_buffer, current_pid, _levelDSCStrings[priority], eventId, file, line);
    Vftprintf(telemetry_file, format, ap);
    Ftprintf(telemetry_file, PAL_T("</OMSCONFIGLOG>\n"));
    va_end(ap);

    fflush(telemetry_file);
    fclose(telemetry_file);
}

void DSCLog_Close()
{
    if (_DSCLogFile && _DSCLogFile != stderr)
    {
        fclose(_DSCLogFile);
        _DSCLogFile = NULL;
    }

    if (_DSCDetailedLogFile && _DSCDetailedLogFile != stderr)
    {
        fclose(_DSCDetailedLogFile);
        _DSCDetailedLogFile = NULL;
    }
}

MI_Result DSCLog_Open(
    const ZChar* path,
    FILE ** logFile)
{
    if (!path || logFile == NULL || *logFile)
        return MI_RESULT_FAILED;

#if (MI_CHAR_TYPE == 1)
    {
        *logFile = fopen(path, "a");

        if (*logFile == NULL)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }
#else
    {
        char path7[PAL_MAX_PATH_SIZE];
        if (StrWcslcpy(path7, path, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return MI_RESULT_FAILED;
        
        *logFile = fopen(path7, "a");

        if (*logFile == NULL)
        {
            return MI_RESULT_FAILED;
        }

        return MI_RESULT_OK;
    }
#endif
}

unsigned long DSC_EventRegister()
{
    char logPath[PAL_MAX_PATH_SIZE];
    char detailedLogPath[PAL_MAX_PATH_SIZE];

#if defined(BUILD_OMS)
    Strlcpy(logPath, "/var/opt/microsoft/omsconfig", PAL_MAX_PATH_SIZE);
    Strlcat(logPath, "/", PAL_MAX_PATH_SIZE);
    Strlcpy(detailedLogPath, logPath, PAL_MAX_PATH_SIZE);
    Strlcat(logPath, "omsconfig.log", PAL_MAX_PATH_SIZE);
    Strlcat(detailedLogPath, "omsconfigdetailed.log", PAL_MAX_PATH_SIZE);
#else
    Strlcpy(logPath, OMI_GetPath(ID_LOGDIR), PAL_MAX_PATH_SIZE);
    Strlcat(logPath, "/", PAL_MAX_PATH_SIZE);
    Strlcpy(detailedLogPath, logPath, PAL_MAX_PATH_SIZE);
    Strlcat(logPath, "dsc.log", PAL_MAX_PATH_SIZE);
    Strlcat(detailedLogPath, "dscdetailed.log", PAL_MAX_PATH_SIZE);
#endif
    DSCLog_Open(logPath, &_DSCLogFile);
    DSCLog_Open(detailedLogPath, &_DSCDetailedLogFile);
    return 0;
}

unsigned long DSC_EventUnRegister()
{
    DSCLog_Close();
    return 0;
}

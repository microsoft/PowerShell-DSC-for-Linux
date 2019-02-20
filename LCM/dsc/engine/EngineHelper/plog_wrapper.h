/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __PLOGWRAPPER_H_
#define __PLOGWRAPPER_H_

enum // Define log instances. Default is 0 and is omitted from this enum.
{
    OmsConfigDetailed = 1
};

typedef enum _DSC_Log_Level
{
    DSC_LOG_FATAL = 0,
    DSC_LOG_ERROR,
    DSC_LOG_WARNING,
    DSC_LOG_INFO,
    DSC_LOG_DEBUG,
    DSC_LOG_VERBOSE
}
DSC_Log_Level;

#ifdef __cplusplus
extern "C" {
#endif

unsigned long DSC_PLog_Register();
unsigned long DSC_PLog_Unregister();
unsigned long DSC_PLog_Write(DSC_Log_Level p_level, int p_line_number, const char * p_file_name, const char * p_message);

#ifdef __cplusplus
}
#endif

#endif //__PLOGWRAPPER_H_

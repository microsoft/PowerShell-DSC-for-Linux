/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// #include "plog_wrapper.h"
#include "EventWrapper.h"
#include <plog/Log.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

unsigned long DSC_PLog_Register()
{
   plog::init(plog::warning, "/opt/dsc/output/omsconfig.log");
   plog::init<OmsConfigDetailed>(plog::verbose, "/opt/dsc/output/omsconfigdetailed.log");

   return 0;
}

unsigned long DSC_PLog_Unregister()
{
   // no need to do anything
   return 0;
}

unsigned long DSC_PLog_Write(DSC_Log_Level p_level, int p_line_number, const char * p_file_name, const char * p_message)
{
   switch(p_level)
   {
      case DSC_LOG_FATAL_LEVEL:
      {
         LOG_FATAL << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         LOG_FATAL_(OmsConfigDetailed) << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         break;
      }
      case DSC_LOG_ERROR_LEVEL:
      {
         LOG_ERROR << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         LOG_ERROR_(OmsConfigDetailed) << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         break;
      }
      case DSC_LOG_WARNING_LEVEL:
      {
         LOG_WARNING << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         LOG_WARNING_(OmsConfigDetailed) << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         break;
      }
      case DSC_LOG_INFO_LEVEL:
      {
         LOG_INFO << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         LOG_INFO_(OmsConfigDetailed) << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         break;
      }
      case DSC_LOG_DEBUG_LEVEL:
      {
         LOG_DEBUG << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         LOG_DEBUG_(OmsConfigDetailed) << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         break;
      }
      case DSC_LOG_VERBOSE_LEVEL:
      {
         LOG_VERBOSE << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         LOG_VERBOSE_(OmsConfigDetailed) << "[" << p_file_name << ":" << p_line_number << "] " << p_message;
         break;
      }
   }

   return 0;
}

#ifdef __cplusplus
}
#endif

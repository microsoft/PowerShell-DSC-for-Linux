/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _CALOG_H_
#define  _CALOG_H_

#include "MI.h"
#define VERBOSE_FORMAT                  MI_T("[%S]:         %-16S   [%S] %S") //For example : [DeviceName]: LCM: [StartResource]   [Package]SQL
#define MAX_COMPUTERNAME_LENGTH         15
#define CA_DEVICE_NAME_SIZE             MAX_COMPUTERNAME_LENGTH+1    //Maximum computer name length is 15 as per msdn
#define TOKENIZED_MESSAGE_PADDING       50     //Additional buffer space since the strings occupy length as present in the verbose format.
#define WHATIFMESSAGE_STARTINDEX        9      // This is the index where the content in the whatif message starts - Any whatif message from the provider goes like "whatif : <message>"

typedef struct _CAJobInformation
{
     MI_Char deviceName[CA_DEVICE_NAME_SIZE];
     
    
} CAJobInformation;


#ifdef __cplusplus
extern "C"
{
#endif


void MI_CALL LogCAWhatIfMessage( _In_ void *provContext, _In_z_ const MI_Char *message);

MI_Boolean MI_CALL CAWhatIfEnabled(_In_ void *provContext);

void MI_CALL LogCAWriteMIError(
    _In_ void *provContext,
    _In_ MI_Instance* instanceMIError);

const MI_Char *  MI_CALL LogCADebugMessage(
    _In_ void *provContext,
    _In_opt_z_ const MI_Char *message);

const MI_Char *  MI_CALL LogCAVerboseMessage(
    _In_ void *provContext,
    _In_opt_z_ const MI_Char *message);

void MI_CALL LogCAWarningMessage(
    _In_ void *provContext,
    _In_opt_z_ const MI_Char *message);

void MI_CALL LogCAProgressMessage(
    _In_ void *provContext,
    _In_z_ const MI_Char *activity,
    _In_z_ const MI_Char * currentOperation,
    _In_z_ const MI_Char * statusDescroption,
    _In_ MI_Uint32 percentComplete,
    _In_ MI_Uint32 secondsRemaining);

const MI_Char * GetResourceIdFromConext(_In_ void *provContext);

void CALogSetJobDeviceName();


#ifdef __cplusplus
                                  
}
                                  
#endif


#endif //_CALOG_H_

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

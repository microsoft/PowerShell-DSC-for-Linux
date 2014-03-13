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


#include "DSC_Systemcalls.h"
#include "EngineHelper.h"



#define _CA_IMPORT_ 1
#include "CALog.h"

#if defined(_MSC_VER)
#include <sal.h>
#endif

CAJobInformation g_CAJobInformation={EMPTY_STRING};
MI_Boolean CAWhatIfEnabled(_In_ void *provContext)
{
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
    LCMProviderContext *lcmContext = providerContext->lcmProviderContext;   
    return (lcmContext->executionMode & LCM_SETFLAGS_ENABLEWHATIF) ? MI_TRUE:MI_FALSE;
    
}
//Logs the Whatif messages that arrive from the provider.
void LogCAWhatIfMessage( _In_ void *provContext, _In_z_ const MI_Char *message)
{
    if(message != NULL && provContext != NULL)
    {
        ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
        LCMProviderContext *lcmContext = providerContext->lcmProviderContext;
        if((lcmContext->executionMode & LCM_EXECUTIONMODE_ONLINE) && lcmContext->context)
        {
            MI_Char *fullMessage = NULL;
            size_t msgLen;
            //The message arrived contains whatif : <actualmessage> , and we need to truncate it to the start of the actual message first.
            const MI_Char * truncatedMsg=(Tcslen(message)<WHATIFMESSAGE_STARTINDEX)?message:message+WHATIFMESSAGE_STARTINDEX;
            msgLen = Tcslen(truncatedMsg) + Tcslen(providerContext->resourceId) + Tcslen(EMPTY_STRING) +Tcslen(VERBOSE_FORMAT) + Tcslen(g_CAJobInformation.deviceName)+TOKENIZED_MESSAGE_PADDING; 
            
            fullMessage = (MI_Char*) DSC_malloc(sizeof(MI_Char)*msgLen, NitsHere());

            if( fullMessage)
            {
                //Full message looks like "What if: [PS3319275115]:                                 [[WindowsFeature]x] Continue with removal?"
                if(Stprintf(fullMessage, msgLen,VERBOSE_FORMAT , g_CAJobInformation.deviceName, EMPTY_STRING,  providerContext->resourceId, truncatedMsg) > 0 )
                {
                    MI_Boolean flag;
                    //Changed it from should process to prompt user since shouldprocess is being done within the provider. Here we just output the message.
                    MI_Context_PromptUser((MI_Context*) lcmContext->context,fullMessage, MI_PROMPTTYPE_NORMAL,&flag);
                }
                
                DSC_free(fullMessage);
                    
            }
        }
    }
}

void LogCAWriteMIError(
    _In_ void *provContext,
    _In_ MI_Instance* instanceMIError)
{
    MI_Result result = MI_RESULT_OK;
    MI_Boolean flag = FALSE;

    if (provContext != NULL && instanceMIError != NULL)
    {
        ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
        LCMProviderContext *lcmContext = providerContext->lcmProviderContext;

        if((lcmContext->executionMode & LCM_EXECUTIONMODE_ONLINE) && lcmContext->context)
        {
            result = MI_Context_WriteCimError((MI_Context*) lcmContext->context, instanceMIError, &flag);

            if (result != MI_RESULT_OK)
            {
                // Ignore the failure, this doesn't impact the functionality.
            }
        }
    }
}

const MI_Char *  LogCADebugMessage(_In_ void *provContext,_In_opt_z_ const MI_Char *message)
{
    MI_Result result = MI_RESULT_OK;
    if(message != NULL && provContext != NULL)
    {
        ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
        LCMProviderContext *lcmContext = providerContext->lcmProviderContext;


        if((lcmContext->executionMode & LCM_EXECUTIONMODE_ONLINE) && lcmContext->context)
        {
             MI_Char *fullMessage = NULL;
            size_t msgLen;
            msgLen = Tcslen(message) + Tcslen(providerContext->resourceId) + Tcslen(VERBOSE_FORMAT)+Tcslen(EMPTY_STRING)+Tcslen(g_CAJobInformation.deviceName)+TOKENIZED_MESSAGE_PADDING; //'ResourceId': <message>\0
            fullMessage = (MI_Char*) DSC_malloc(sizeof(MI_Char)*msgLen, NitsHere());

            if(fullMessage != NULL)
            {
                if(Stprintf(fullMessage, msgLen,VERBOSE_FORMAT , g_CAJobInformation.deviceName, EMPTY_STRING, providerContext->resourceId, message) >0 )
                {
                    result = MI_Context_WriteDebug((MI_Context*) lcmContext->context, fullMessage);

                    if(result != MI_RESULT_OK)
                    {
                        // Ignore the failure, this doesn't impact the functionality.
                    }
                }
                //Return the message since the event is output from the parent rfunction
                return fullMessage;
            }
        }
    }
    return NULL;
}

const MI_Char *  LogCAVerboseMessage(_In_ void *provContext,_In_opt_z_ const MI_Char *message)
{
    MI_Result result = MI_RESULT_OK;
    if(message != NULL && provContext != NULL)
    {
        ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
        LCMProviderContext *lcmContext = providerContext->lcmProviderContext;
        MI_Boolean whatifEnabled=CAWhatIfEnabled(provContext);     
        if((lcmContext->executionMode & LCM_EXECUTIONMODE_ONLINE) && lcmContext->context)
        {
            MI_Char *fullMessage = NULL;
            size_t msgLen;
			msgLen = Tcslen(message) + Tcslen(providerContext->resourceId) + Tcslen(VERBOSE_FORMAT) + Tcslen(EMPTY_STRING) + Tcslen(g_CAJobInformation.deviceName) + TOKENIZED_MESSAGE_PADDING; //'ResourceId': <message>\0
            fullMessage = (MI_Char*) DSC_malloc(sizeof(MI_Char)*msgLen, NitsHere());

            if(fullMessage != NULL)
            {
				if (Stprintf(fullMessage, msgLen, VERBOSE_FORMAT,g_CAJobInformation.deviceName, EMPTY_STRING, providerContext->resourceId, message) >0)
                {
                    if(!whatifEnabled)
                    {
                        result = MI_Context_WriteVerbose((MI_Context*) lcmContext->context, fullMessage);
                    }
                    if(result != MI_RESULT_OK)
                    {
                        // Ignore the failure, this doesn't impact the functionality.
                    }
                }

                return fullMessage;
            }
        }
    }
    return NULL;
}

void LogCAWarningMessage(_In_ void *provContext,_In_opt_z_ const MI_Char *message)
{
    MI_Result result = MI_RESULT_OK;
        
    if(message != NULL && provContext != NULL)
    {
        ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
        LCMProviderContext *lcmContext = providerContext->lcmProviderContext;
        

        if((lcmContext->executionMode & LCM_EXECUTIONMODE_ONLINE) && lcmContext->context)
        {
            MI_Char *fullMessage = NULL;
            size_t msgLen; 
            msgLen = Tcslen(message) + Tcslen(providerContext->resourceId) + Tcslen(VERBOSE_FORMAT)+Tcslen(EMPTY_STRING)+Tcslen(g_CAJobInformation.deviceName)+TOKENIZED_MESSAGE_PADDING; //DeviceName: LCM:  \t   \t   [Package]SQL
            fullMessage = (MI_Char*) DSC_malloc(sizeof(MI_Char)*msgLen, NitsHere());

            if( fullMessage!=NULL)
            {                
                if(Stprintf(fullMessage, msgLen,VERBOSE_FORMAT , g_CAJobInformation.deviceName, EMPTY_STRING, providerContext->resourceId, message) >0 )
                {
                    result = MI_Context_WriteWarning((MI_Context*) lcmContext->context, fullMessage);

                    if(result != MI_RESULT_OK)
                    {
                        // Ignore the failure, this doesn't impact the functionality.
                    }
                }

                DSC_free(fullMessage);
            }
        }
    }
}

void LogCAProgressMessage(
    _In_ void *provContext,
    _In_z_ const MI_Char *activity,
    _In_z_ const MI_Char * currentOperation,
    _In_z_ const MI_Char * statusDescroption,
    _In_ MI_Uint32 percentComplete,
    _In_ MI_Uint32 secondsRemaining)
{
    MI_Result result = MI_RESULT_OK;
        
    if(activity != NULL && currentOperation != NULL && statusDescroption != NULL)
    {
        ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
        LCMProviderContext *lcmContext = providerContext->lcmProviderContext;


        if((lcmContext->executionMode & LCM_EXECUTIONMODE_ONLINE) && lcmContext->context)
        {
            result = MI_Context_WriteProgress(
                (MI_Context*) lcmContext->context, 
                activity, 
                currentOperation, 
                statusDescroption, 
                percentComplete, 
                secondsRemaining);

            if(result != MI_RESULT_OK)
            {
                // Ignore it...
            }
        }

    }

}


const MI_Char * GetResourceIdFromConext(_In_ void *provContext)
{
    ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
    return providerContext->resourceId;
}
void CALogSetJobDeviceName()
{
   
    MI_Uint32 jobInfoCompNameLen=CA_DEVICE_NAME_SIZE;
    int result = 0;
#if defined(_MSC_VER)
    result = !GetComputerName(g_CAJobInformation.deviceName, (LPDWORD)&jobInfoCompNameLen);
#else
    result = gethostname(g_CAJobInformation.deviceName, jobInfoCompNameLen); 
#endif

    if (result != MI_FALSE) 
    {
            Stprintf(g_CAJobInformation.deviceName, CA_DEVICE_NAME_SIZE, EMPTY_STRING);
            return;
    }


}




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
#include "WebPullClientInvoker.h"
#include "PAL_Extension.h"
#include "EngineHelper.h"
#include "Resources_LCM.h"
#include "WebPullClient.h"

void GetDSCAction(_In_ MI_Context* context, _In_opt_ const MSFT_DSCWebPullClient_GetDSCAction* in)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char url[URL_SIZE] = {0};
    MI_Char subUrl[SUBURL_SIZE] = {0};
    MI_Uint32 port;
    MI_Instance *extendedError = NULL;
    MI_Boolean bIsHttps;
    MI_Uint32 getActionStatusCode;
    MI_Value value;
    MI_Uint32 flags;
    MI_Char *result = NULL;
    MSFT_DSCWebPullClient_GetDSCAction out; 

    if( !in->CustomData.exists || !in->ConfigurationID.exists || !in->FileHash.exists || !in->NotCompliant.exists || !in->StatusCode.exists )
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }       
    r = MSFT_DSCWebPullClient_GetDSCAction_Construct(&out, context);
    if( r != MI_RESULT_OK)
    {       
        MI_PostResult(context, r);
        return;         
    }
    r = MI_Instance_GetElement(&in->__instance, MI_T("CustomData"), &value, NULL, &flags, NULL);
    if( r != MI_RESULT_OK || (flags & MI_FLAG_NULL) || value.instancea.size == 0)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);      
        return;        
    }
    r = GetUrlParam(&value.instancea, url, subUrl, &port, &bIsHttps, &getActionStatusCode, &extendedError);
    if( r != MI_RESULT_OK)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);        
        MI_PostCimError(context, extendedError);
        MI_Instance_Delete(extendedError);       
        return;
    }
    r = IssueGetActionRequest(in->ConfigurationID.value, 
                              NULL, //For certificateID        
                              in->FileHash.value, 
                              in->NotCompliant.value, 
                              in->StatusCode.value, 
                              &result,
                              &getActionStatusCode,
                              url,
                              port,
                              subUrl,
                              bIsHttps,
                              &extendedError);  

    if( r != MI_RESULT_OK)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);        
        MI_PostCimError(context, extendedError);
        MI_Instance_Delete(extendedError);
        return;        
    }

    r = MSFT_DSCWebPullClient_GetDSCAction_SetPtr_Result(&out, result);
    if( r != MI_RESULT_OK)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);        
        MI_PostResult(context, r);
        return;        
    }    
    MSFT_DSCWebPullClient_GetDSCAction_Set_MIReturn(&out, 0 );
    r = MSFT_DSCWebPullClient_GetDSCAction_Post(&out, context);
    DSC_free(result);
    MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);  
    MI_PostResult(context, r);
}

void GetDSCDocument(_In_ MI_Context* context, _In_opt_ const MSFT_DSCWebPullClient_GetDSCDocument* in)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char url[URL_SIZE] = {0};
    MI_Char subUrl[SUBURL_SIZE] = {0};
    MI_Uint32 port;
    MI_Instance *extendedError = NULL;
    MI_Boolean bIsHttps;
    MI_Uint32 getActionStatusCode;
    MI_Value value;
    MI_Uint32 flags;
    MI_Char *result = NULL;
    MSFT_DSCWebPullClient_GetDSCAction out;

    if( !in->CustomData.exists || !in->ConfigurationID.exists || !in->DestinationPath.exists)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }     
    r = MSFT_DSCWebPullClient_GetDSCAction_Construct(&out, context);
    if( r != MI_RESULT_OK)
    {        
        MI_PostResult(context, r);
        return;         
    }
    r = MI_Instance_GetElement(&in->__instance, MI_T("CustomData"), &value, NULL, &flags, NULL);
    if( r != MI_RESULT_OK || (flags & MI_FLAG_NULL) || value.instancea.size == 0)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);       
       return;        
    }
    r = GetUrlParam(&value.instancea, url, subUrl, &port, &bIsHttps, &getActionStatusCode, &extendedError);
    if( r != MI_RESULT_OK)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);        
        MI_PostCimError(context, extendedError);
        MI_Instance_Delete(extendedError);               
        return;
    }
    r = IssueGetConfigurationRequest(in->ConfigurationID.value, 
                              NULL, //For certificateID
                              in->DestinationPath.value, 
                              &result,
                              &getActionStatusCode,
                              url,
                              port,
                              subUrl,
                              bIsHttps,
                              &extendedError);        

    if( r != MI_RESULT_OK)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);        
        MI_PostCimError(context, extendedError);
        MI_Instance_Delete(extendedError);
        return;        
    }

    r = MSFT_DSCWebPullClient_GetDSCAction_SetPtr_Result(&out, result);
    if( r != MI_RESULT_OK)
    {
        MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);        
        MI_PostResult(context, r);
        return;        
    }    
    MSFT_DSCWebPullClient_GetDSCAction_Set_MIReturn(&out, 0 );
    r = MSFT_DSCWebPullClient_GetDSCAction_Post(&out, context);
    DSC_free(result);
    MSFT_DSCWebPullClient_GetDSCAction_Destruct(&out);  
    MI_PostResult(context, r);    
}

void GetDSCModule(_In_ MI_Context* context, _In_opt_ const MSFT_DSCWebPullClient_GetDSCModule* in)
{
}

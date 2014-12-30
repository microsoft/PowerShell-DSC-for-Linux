#include <MI.h>
#include "DSC_Systemcalls.h"
#include "WebPullClientInvoker.h"
#include "PAL_Extension.h"
#include "EngineHelper.h"
#include "Resources_LCM.h"

#if defined(_MSC_VER)
#include <winhttp.h>
#endif

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

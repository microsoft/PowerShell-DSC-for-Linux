#include "EngineHelperInternal.h"
#include "RegistrationManager.h"
#include "RegistrationManagerHelper.h"
#include "pal/strings.h"
#include "pal/memory.h"
#include "PAL_Extension.h"
#include "DSC_Systemcalls.h"
#include "Resources_LCM.h"

extern MI_Char* RunCommand(const MI_Char* command);

/*This method creates an instance of RegistrationManager*/
MI_Result MI_CALL RegistrationManager_New(
    _Outptr_ RegistrationManager** out,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Result result;
    RegistrationManager* self = NULL;
    MI_Char* agentId = NULL;
    MI_Boolean shouldGenerateAgentId = MI_FALSE;
    
    if (cimErrorDetails)
    {
        *cimErrorDetails = NULL;
    }

    self = calloc(1, sizeof(RegistrationManager));
    EH_Check_(self, result = MI_RESULT_SERVER_LIMITS_EXCEEDED);

    // Get Agent Id from Registry 
    result = GetAgentIdFromRegistry(&agentId, &shouldGenerateAgentId);
    EH_CheckResult(result);
    if (shouldGenerateAgentId)
    {
        agentId = RunCommand("cat /proc/sys/kernel/random/uuid | awk '{print toupper($0)}' | tr -d \"\n\"");
        self->agentId = agentId;
        result = WriteAgentIdToRegistry(self->agentId, cimErrorDetails);
    }
    else
    {
        self->agentId = agentId;
    }

    PopulateServerURLs(self, cimErrorDetails);    

    *out = self;
    return MI_RESULT_OK;

EH_UNWIND:
    if( self)
    {
        free(self);
    }   
    return result;    
    
}

/* Destroy an instance of RegistrationManager.*/
void MI_CALL RegistrationManager_Destroy(
    _Inout_ RegistrationManager* self)
{
    MI_Uint32 i = 0;
        if (self != NULL)
        {
	    for (i = 0; i < self->numberOfServerURLs; i++)
	    {
		if (self->serverURLs[i] != NULL)
		{
		    DSC_free(self->serverURLs[i]);
		}
		if (self->serverCertificateThumbprints[i] != NULL)
		{
		    DSC_free(self->serverCertificateThumbprints[i]);
		}
	    }
	    self->numberOfServerURLs = 0;

	    DSC_free(self->agentId);
	    free(self);
	    self = NULL;
        }
}

/* This is the only method currently exposed by Registration Manager.
     Caller providers its context and the item that represents the requests. */
MI_Result MI_CALL RegistrationManager_RunRequest(
                                    _In_ RegistrationManager* self,
                                     _In_ RegistrationRequest *item,
                                     _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if( item == NULL || self == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    return RegistrationManager_HandleRequest(self, item, cimErrorDetails);
}

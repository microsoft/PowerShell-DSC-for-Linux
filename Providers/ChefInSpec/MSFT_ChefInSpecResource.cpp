/* @migen@ */
#include <MI.h>
#include "MSFT_ChefInSpecResource.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "json.c"
#include <unistd.h>

MI_EXTERN_C MI_CONST MI_ClassDecl InSpec_Results_rtti;
const char *g_ChefInSpecStore = "/tmp/ChefInSpec";
MI_Char* RunCommand(const MI_Char* command)
{
    MI_Char* result = NULL;
    FILE * fp;
    const int bufferSize = 5000;
    char buffer[bufferSize * 10 + 1];
    char curBuffer[bufferSize + 1];
    size_t cur_loc = 0;
    size_t count = 0;
    int status;

    curBuffer[bufferSize] = '\0';
    
    fp = popen(command, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    while (fgets(curBuffer, 5000, fp) != NULL)
    {
        count = strlen(curBuffer);
        if (count + cur_loc > bufferSize * 10)
          {
            break;
          }
        memcpy(buffer + cur_loc, curBuffer, count);
        cur_loc += count;
        
    }

    buffer[cur_loc] = '\0';
    
    pclose(fp);
    result = (MI_Char*)malloc((cur_loc + 1) * sizeof(MI_Char*));
    memcpy(result, buffer, cur_loc + 1);

    return result;
}

void MI_CALL MSFT_ChefInSpecResource_Load(
    _Outptr_result_maybenull_ MSFT_ChefInSpecResource_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);
    if(!access(g_ChefInSpecStore, 0 ))
    {
        mkdir(g_ChefInSpecStore, S_IRWXU);
    } 
    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_ChefInSpecResource_Unload(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_ChefInSpecResource_EnumerateInstances(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_ChefInSpecResource_GetInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_ChefInSpecResource_CreateInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_ChefInSpecResource_ModifyInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_ChefInSpecResource_DeleteInstance(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ChefInSpecResource* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}


void ProcessStatistics( json_value *jsonvalue, MI_Instance *instance)
{
   for(int x=0; x < jsonvalue->u.object.length; x++){
        if(strcmp(jsonvalue->u.object.values[x].name, "duration") == 0)
        {
            char output[50];
            snprintf(output, 50, "%f", jsonvalue->u.object.values[x].value->u.dbl);
            MI_Value value;
            value.string = output;
            MI_Instance_SetElement(instance, jsonvalue->u.object.values[x].name, &value, MI_STRING, 0 );
        }
   } 
}
void ProcessControls( json_value *jsonvalue, MI_Instance *instance)
{
   for(int x=0; x < jsonvalue->u.object.length; x++){
        MI_Value value;
        if(strcmp(jsonvalue->u.object.values[x].name, "id") == 0)
        {
            value.string = jsonvalue->u.object.values[x].value->u.string.ptr;
            MI_Instance_SetElement(instance, jsonvalue->u.object.values[x].name, &value, MI_STRING, 0 );
        }
        else if(strcmp(jsonvalue->u.object.values[x].name, "profile_id") == 0)
        {
            value.string = jsonvalue->u.object.values[x].value->u.string.ptr;
            MI_Instance_SetElement(instance, jsonvalue->u.object.values[x].name, &value, MI_STRING, 0 );
        }
        else if(strcmp(jsonvalue->u.object.values[x].name, "profile_sha256") == 0)
        {
            value.string = jsonvalue->u.object.values[x].value->u.string.ptr;
            MI_Instance_SetElement(instance, jsonvalue->u.object.values[x].name, &value, MI_STRING, 0 );
        }
        else if(strcmp(jsonvalue->u.object.values[x].name, "status") == 0)
        {
            value.string = jsonvalue->u.object.values[x].value->u.string.ptr;
            MI_Instance_SetElement(instance, jsonvalue->u.object.values[x].name, &value, MI_STRING, 0 );
        }
        else if(strcmp(jsonvalue->u.object.values[x].name, "code_desc") == 0)
        {
            value.string = jsonvalue->u.object.values[x].value->u.string.ptr;
            MI_Instance_SetElement(instance, "codec_desc", &value, MI_STRING, 0 );
        }
        else if(strcmp(jsonvalue->u.object.values[x].name, "message") == 0)
        {
            value.string = jsonvalue->u.object.values[x].value->u.string.ptr;
            MI_Instance_SetElement(instance, jsonvalue->u.object.values[x].name, &value, MI_STRING, 0 );
        }
   } 
}

MI_Result InstallPolicyIfNeeded(char * name, char *githubPath)
{
    char policyLocalPath[200];
    snprintf(policyLocalPath, 200, "%s/%s", g_ChefInSpecStore, name);
    //check if path exists
    if(access(policyLocalPath, 0 ))
    {
         char policyGitCommand[500];
         snprintf(policyGitCommand, 500, "/tmp/GitClonePolicy.sh %s %s", githubPath, policyLocalPath);
         RunCommand(policyGitCommand);
    }
    

}
void MI_CALL MSFT_ChefInSpecResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MSFT_ChefInSpecResource_GetTargetResource* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);
  
    MI_Result r = MI_RESULT_FAILED;
    if(! (in->InputResource.exists && in->InputResource.value->Name.exists))
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
    }
    if(! (in->InputResource.exists && in->InputResource.value->GithubPath.exists))
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
    }
    r = InstallPolicyIfNeeded((char*)in->InputResource.value->Name.value, (char*)in->InputResource.value->GithubPath.value);
    MSFT_ChefInSpecResource_GetTargetResource out;
    MSFT_ChefInSpecResource_GetTargetResource_Construct(&out, context);
    MSFT_ChefInSpecResource_GetTargetResource_Set_MIReturn(&out, 0 );
//    RunCommand("'/usr/bin/inspec exec /home/nitin/InSpecProfiles/linux-baseline --reporter=json-min:/tmp/output.json'");
    char policyRunCommand[500];
    snprintf(policyRunCommand, 500, "/tmp/runinspec.sh %s %s /tmp/output.json", g_ChefInSpecStore, in->InputResource.value->Name.value );
      RunCommand(policyRunCommand);
    // REad file
    struct stat filestatus;
    stat("/tmp/output.json", &filestatus);
    int file_size = filestatus.st_size;
    char * file_contents = (char*)malloc(filestatus.st_size);
    FILE * fp = fopen("/tmp/output.json","rt");
    fread(file_contents, file_size, 1, fp);
    fclose(fp);
    json_char *json = (json_char*)file_contents;
    json_value *jsonvalue = json_parse(json, file_size);
    MI_Instance *outputObject = NULL;
    MI_Context_NewInstance(context, &MSFT_ChefInSpecResource_rtti, &outputObject);
    MI_Value value;
    MI_Instance *inspec_Results = NULL;
    MI_Context_NewInstance(context, &InSpec_Results_rtti, &inspec_Results);
    MI_Instance *inspec_Statistics = NULL;
    MI_Context_NewInstance(context, &InSpec_Statistics_rtti, &inspec_Statistics);
    for(int x=0; x < jsonvalue->u.object.length; x++){
        if(strcmp(jsonvalue->u.object.values[x].name, "version") == 0)
        {
 	    value.string = jsonvalue->u.object.values[x].value->u.string.ptr;
	    MI_Instance_SetElement(inspec_Results, jsonvalue->u.object.values[x].name, &value, MI_STRING ,0);
        }
        else if(strcmp(jsonvalue->u.object.values[x].name, "statistics") == 0)
        {
             ProcessStatistics(jsonvalue->u.object.values[x].value, inspec_Statistics); 
             value.instance = inspec_Statistics;
             MI_Instance_SetElement(inspec_Results, jsonvalue->u.object.values[x].name, &value, MI_INSTANCE, 0 );
        }
        else if(strcmp(jsonvalue->u.object.values[x].name, "controls") == 0)
        {
             MI_Instance **inspec_Controls = NULL;
             json_value *controlValue = jsonvalue->u.object.values[x].value;
             if(controlValue->u.array.length > 0 )
             {
                 inspec_Controls = (MI_Instance**) malloc(controlValue->u.array.length * sizeof(MI_Instance*));
                 for(int y=0; y<controlValue->u.array.length; y++){
                     MI_Context_NewInstance(context, &InSpec_Controls_rtti, &inspec_Controls[y]);
                     ProcessControls(controlValue->u.array.values[y], inspec_Controls[y]); 
                 }
                 value.instancea.data = inspec_Controls;
                 value.instancea.size = controlValue->u.array.length;
                 MI_Instance_SetElement(inspec_Results, jsonvalue->u.object.values[x].name, &value, MI_INSTANCEA, 0 );
             }
        }
    }

    value.instance = inspec_Results;
    MI_Instance_SetElement(outputObject, "Result", &value, MI_INSTANCE, 0 );

    value.instance = outputObject;
    MI_Instance_SetElement(&out.__instance, "OutputResource", &value, MI_INSTANCE, 0 );
    MSFT_ChefInSpecResource_GetTargetResource_Post(&out, context);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_ChefInSpecResource_Invoke_TestTargetResource(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MSFT_ChefInSpecResource_TestTargetResource* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_ChefInSpecResource_Invoke_SetTargetResource(
    _In_opt_ MSFT_ChefInSpecResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_ChefInSpecResource* instanceName,
    _In_opt_ const MSFT_ChefInSpecResource_SetTargetResource* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}


/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <nits.h>
#include "../../common/NitsPriority.h"
#include <MI.h>
#include <pal/file.h>
#include <pal/strings.h>
#include <PAL_Extension.h>
#include <EngineHelperInternal.h>

using namespace std;

#ifdef _MSC_VER
#define TEST_CONFIG_FILE MI_T("testLCM.mof")
#define TEST_GET_CONFIG_FILE MI_T("testLCMGet.mof")
#define LCM_PRO_NAMESPACE MI_T("root/Microsoft/Windows/DesiredStateConfiguration")
#define LCM_CLASSNAME MI_T("MSFT_DSCLocalConfigurationManager")
#define LCM_SETMETHODNAME MI_T("SendConfigurationApply")
#define LCM_GETMETHODNAME MI_T("GetConfiguration")
#define LCML_GETMETHODOUTPARAM MI_T("configurations")
#define LCM_SETMETACONFIGMETHODNAME MI_T("SendMetaConfiguration")
#define CONFIGURATION_PENDING MI_T("%windir%\\System32\\Configuration\\Pending.mof")
#else
#define TEST_CONFIG_FILE CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/testLCM2.mof")
#define TEST_GET_CONFIG_FILE CONFIG_SRCDIR MI_T("/dsc/tests/Engine/E2E") MI_T("/testLCMGet2.mof")
#define LCM_PRO_NAMESPACE MI_T("dsc")
#define LCM_CLASSNAME MI_T("MSFT_DSCLocalConfigurationManager")
#define LCM_SETMETHODNAME MI_T("SendConfigurationApply")
#define LCM_GETMETHODNAME MI_T("GetConfiguration")
#define LCML_GETMETHODOUTPARAM MI_T("configurations")
#define LCM_SETMETACONFIGMETHODNAME MI_T("SendMetaConfiguration")
#define CONFIGURATION_PENDING CONFIG_SYSCONFDIR MI_T("/dsc/configuration/Pending.mof")
#endif

MI_Result DeleteConfig(_In_z_ const MI_Char * pwszFileName)
{
//    MI_Result result;
    MI_Char *fileFull;
//    MI_Instance **cimError = NULL;
    
#ifdef _MSC_VER    
    MI_Uint32 dwReturnSizeInitial = 0;
    size_t pathSize;

    dwReturnSizeInitial = ExpandEnvironmentStrings(pwszFileName, NULL, 0);         

    fileFull = (MI_Char*)malloc(dwReturnSizeInitial* sizeof(MI_Char));

    pathSize = ExpandEnvironmentStrings(pwszFileName, fileFull, dwReturnSizeInitial);

#else
    fileFull = (MI_Char*)pwszFileName;
#endif

    if(File_ExistT(fileFull) == 0)
    {
        if(!File_RemoveT(fileFull))
        {

#ifdef _MSC_VER    
            free(fileFull);
#endif
            return MI_RESULT_FAILED;
        }
    }
#ifdef _MSC_VER    
    free(fileFull);
#endif
    return MI_RESULT_OK;
}

/* caller will need to release the memory  for content buffer */
MI_Result ReadTestFile(_In_z_ const MI_Char *pFileName,
                          _Outptr_result_buffer_maybenull_(*pBufferSize) MI_Uint8 ** pBuffer, 
                          _Out_ MI_Uint32 * pBufferSize)
{
    FILE *fp;
    size_t result;
    unsigned long fileLen;
    size_t nSizeWritten;

    *pBuffer = 0;
    *pBufferSize = 0;
    fp = File_OpenT(pFileName, MI_T("rb"));
    if( fp == NULL)
    {
        return MI_RESULT_FAILED;
    }
    
    // Get File size
    result = fseek(fp, 0, SEEK_END);
    if(result)
    {
        File_Close(fp);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    fileLen = ftell(fp);  
    result = fseek(fp, 0, SEEK_SET);
    if(result)
    {
        File_Close(fp);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    *pBuffer = (MI_Uint8*)malloc(fileLen);
    if(result)
    {
        File_Close(fp);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    // Read the contents

#if defined(_MSC_VER)
            nSizeWritten = (long)fread(*pBuffer, 1, fileLen, fp);
#else
            nSizeWritten = fread(*pBuffer, 1, fileLen, fp);
#endif

    File_Close(fp);
    if( nSizeWritten != fileLen)
    {
        free(*pBuffer);
        *pBuffer = NULL;
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;        
    }
    *pBufferSize = (MI_Uint32)fileLen;
    return MI_RESULT_OK;
}

MI_Result GetGetMethodResult(_In_ MI_Operation *operation,
                              _Inout_ MI_Value *outputValue)
{
    MI_Result r = MI_RESULT_OK;
    MI_Result innerR = MI_RESULT_OK;
    const MI_Instance* outInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails = NULL;  
    MI_Instance *errorInfo;

    /*Get the operation result*/
    r = MI_Operation_GetInstance(operation, &outInstance, &moreResults, &result, &errorMessage, &completionDetails);
    if( result != MI_RESULT_OK)
    {
        r = result;
    }    
    
    if( r != MI_RESULT_OK)
    {
        if( completionDetails != NULL)
        {
            innerR = MI_Instance_Clone( completionDetails, &errorInfo);
        }
        if( innerR != MI_RESULT_OK || completionDetails == NULL)
        {
            return MI_RESULT_FAILED; //MI_Utilities_CimErrorFromErrorCode( (MI_Uint32)r, MI_RESULT_TYPE_MI, L"Get error detail failed", &errorInfo);
        }
        return r;
    }

    /*Get configurations  property*/
    r = MI_Instance_GetElement(outInstance, LCML_GETMETHODOUTPARAM, outputValue, NULL, NULL, NULL);

    return r;
                                
}

typedef struct _PSSemanticsProgress
{
    unsigned int wait;    
    MI_Uint32 writeMessageCount;
    BOOL writeProgressCount;
    
} PSSemanticsProgress;


void MI_CALL TestWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
             MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    PSSemanticsProgress *report = (PSSemanticsProgress*) callbackContext;
    report->writeMessageCount++;
}

void MI_CALL TestWriteProgress(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
    _In_z_   const MI_Char *activity,
    _In_z_   const MI_Char *currentOperation,
    _In_z_   const MI_Char *statusDescription,
             MI_Uint32 percentageComplete,
             MI_Uint32 secondsRemaining)
{
    PSSemanticsProgress *report = (PSSemanticsProgress*) callbackContext;
    report->writeProgressCount++;

}

NitsDRTTest(TestLCMSendConfigurationApplyE2E)

    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    PSSemanticsProgress progressReport = {0};
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 size;

    callbacks.writeMessage = TestWriteMessage;
    callbacks.writeProgress = TestWriteProgress;
    progressReport.wait = 0;
    callbacks.callbackContext = (void*) &progressReport;
    
    // Start without a pending configuration file otherwise the test will eventually fail
    // during fault injection tests.
    DeleteConfig(CONFIGURATION_PENDING);

    if( NitsCompare(ReadTestFile(TEST_GET_CONFIG_FILE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {

            value.uint8a.data = pbuffer;
            value.uint8a.size = size;
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement configurationdata failed")))
                {
                    value.boolean = MI_FALSE;
                    if(NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement force failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession failed.")))
                        {
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, LCM_SETMETHODNAME, NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                                {
#if defined(_MSC_VER)
                                    NitsAssert(progressReport.writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
                                    NitsAssert(progressReport.writeProgressCount > 0, MI_T("WriteProgress Count is 0."));                                
#endif
                                }
                            }
                            MI_Operation_Close(&operation);
                            MI_Session_Close(&session, NULL, NULL);
                        }
                    }
                }
                MI_Instance_Delete(parameter);
            }

            MI_Application_Close(&application);
        }
    }

    //clear the pending.mof. 
    DeleteConfig(CONFIGURATION_PENDING);

NitsEndTest

NitsDRTTest(TestLCMGetConfigurationApplyE2E)

    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    MI_Result resultCode;
    MI_Value outValue;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 size;
    MI_Uint32 elementCount =0;
    const MI_Char *elementName = NULL;
    MI_Value elementValue;
    MI_Type elementType;
    MI_Uint32 flag = 0;

#ifdef _MSC_VER
    const MI_Char *fileElementsNames[] = 
    { MI_T("DestinationPath"), MI_T("Ensure"), MI_T("Type"), MI_T("SourcePath"), MI_T("Contents"), MI_T("Checksum"),
    MI_T("Recurse"), MI_T("Force"), MI_T("Credential"), MI_T("CreatedDate"), MI_T("ModifiedDate"), MI_T("Attributes"), MI_T("Size"), MI_T("SubItems"), MI_T("MatchSource")};
    const MI_Uint32 fileElementsNamesCount = 15; //this is total elements in above array.
#else
    const MI_Char *testElementsNames[] = { MI_T("Id1"), MI_T("Id2")};
    const MI_Uint32 testElementsNamesCount = 2; // this is total elements in above array.
#endif

    if( NitsCompare(ReadTestFile(TEST_GET_CONFIG_FILE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {

            value.uint8a.data = pbuffer;
            value.uint8a.size = size;
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("configurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement failed")))
                {
                    if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession failed.")))
                    {
                        MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, LCM_GETMETHODNAME, NULL, parameter, NULL, &operation);
                        resultCode = GetGetMethodResult(&operation, &outValue);
                        
                        NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_operation_getInstance get result error"));
                        if(resultCode == MI_RESULT_OK)
                        {
                            if(NitsCompare(outValue.instancea.size, 1, MI_T("wrong number of instnace returned")))
                            {

                                MI_Instance_GetElementCount(outValue.instancea.data[0], &elementCount);
                                for(MI_Uint32 i = 0; i < elementCount; i++)
                                {
                                    bool exist = false;                                    
                                    MI_Instance_GetElementAt(outValue.instancea.data[0], i, &elementName, &elementValue, &elementType, &flag);
#ifdef _MSC_VER
                                    for( MI_Uint32 jCount = 0; jCount < fileElementsNamesCount; jCount++)
                                    {
                                       if( Tcscasecmp(elementName, fileElementsNames[jCount]) == 0 )
                                        {
                                            exist = true;
                                            break;
                                        }
                                    }
#else
                                    for(MI_Uint32 jCount = 0; jCount < testElementsNamesCount; jCount++)
                                    {
                                        if( Tcscasecmp(elementName, testElementsNames[jCount]) == 0 )
                                        {
                                            exist = true;
                                            break;
                                        }
                                    }
#endif
                                    if(!NitsCompare(exist, true, MI_T("found unknown element")))
                                        TTRACE(elementName);
                                }
                            }
                        }
                        MI_Operation_Close(&operation);
                        MI_Session_Close(&session, NULL, NULL);
                    }
                }
                MI_Instance_Delete(parameter);
            }

            MI_Application_Close(&application);
        }
    }

NitsEndTest


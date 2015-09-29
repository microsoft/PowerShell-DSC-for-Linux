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
#include <pal/format.h>
#include <pal/strings.h>
#include <PAL_Extension.h>
#include <EngineHelperInternal.h>

#include <ModuleHandler.h>
#include <CAEngine.h>
#include <MSFT_DSCMetaConfiguration.h>
#include <lcm.traps.h>
// #include <EtwWaiter.h>

enum methodNames
{
    enum_SendConfiguration = 1,
    enum_SendConfigurationApply = 2,
    enum_GetConfiguration = 3,
    enum_TestConfiguration = 4,
    enum_ApplyConfiguration = 5,
    enum_SendMetaConfigurationApply = 6,
    enum_GetMetaConfiguration = 7,
    enum_RollBack = 8,
    enum_PerformRequiredConfigurationChecks = 9,
    enum_StopConfiguration = 10
} ;

typedef struct _PSSemanticsProgress
{
    unsigned int wait;    
    MI_Uint32 writeMessageCount;
    BOOL writeProgressCount;
    enum methodNames methodToCall; 
    /* 1 = SendConfiguration
         * 2 = SendConfigurationApply
         * 3 = GetConfiguration
         * 4 = TestConfiguration
         * 5 = ApplyConfiguration
         * 6 = SendMetaConfigurationApply
         * 7 = GetMetaConfiguration
         * 8 = RollBack
         * 9 = PerformRequiredConfigurationChecks
         * 10 = StopConfiguration
         */
    
} PSSemanticsProgress;


void RunSendConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport);
void RunGetMetaConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport);
void RunSendMetaConfigurationApply(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport);
void RunApplyConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport);
void RunTestConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport);
void RunGetConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport);
void RunSendConfigurationApply(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport);
void RunStopConfiguration();


struct Ptr
{
    void *ptr;
};

Ptr PtrVal = {NULL};


using namespace std;

//===========================
//
//helper to read file
//
//===============================
#ifdef _MSC_VER
    #define TEST_CONFIG_FILE MI_T("testLCM.mof")
    #define TEST_META_CONFIG_MOF MI_T("testMetaConfig.mof")
    #define TEST_STOPMOF        MI_T("Test_Stop.mof")
    #define TEST_CER_PASSWORD_FILE    MI_T("unittest_password.cer")
    #define TEST_NONINDEPENDENT_INDEPENDENTRESOURCES MI_T("TestNonDependent_1.mof")
    #define TEST_NONINDEPENDENT_MIXEDMODE MI_T("TestNonDependent_2.mof")
    #define TEST_NONINDEPENDENT_SEQUENCEFASTFAIL MI_T("TestNonDependent_3.mof")
    #define TEST_NONINDEPENDENT_SEQUENCELATEFAIL MI_T("TestNonDependent_4.mof")
    #define LCM_PRO_NAMESPACE MI_T("root/Microsoft/Windows/DesiredStateConfiguration")
    #define FMT MI_T("%S\\%S")
    #define TESTCONFIGURATION_LOCATION MI_T("%windir%\\System32\\Configuration")
    #define CONFIGURATION_PENDING MI_T("%windir%\\System32\\Configuration\\Pending.mof")
    #define CONFIGURATION_CURRENT MI_T("%windir%\\System32\\Configuration\\Current.mof")
    #define CONFIGURATION_CURRENT_CHECKSUM MI_T("%windir%\\System32\\Configuration\\Current.mof.checksum")
    #define CONFIGURATION_PREVIOUS MI_T("%windir%\\System32\\Configuration\\Previous.mof")
    #define METACONFIG_LOCATION_MOF MI_T("%windir%\\system32\\configuration\\MetaConfig.mof")
#else
    #define TEST_CONFIG_FILE CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/testLCM2.mof")
    #define TEST_META_CONFIG_MOF CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/testMetaConfig.mof")
    #define TEST_STOPMOF        CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/Test_Stop.mof")
    #define TEST_CER_PASSWORD_FILE    CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/unittest_password.cer")
    #define TEST_NONINDEPENDENT_INDEPENDENTRESOURCES CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/TestNonDependent_1.mof")
    #define TEST_NONINDEPENDENT_MIXEDMODE CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/TestNonDependent_2.mof")
    #define TEST_NONINDEPENDENT_SEQUENCEFASTFAIL CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/TestNonDependent_3.mof")
    #define TEST_NONINDEPENDENT_SEQUENCELATEFAIL CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/TestNonDependent_4.mof")
    #define LCM_PRO_NAMESPACE MI_T("dsc")
    #define FMT MI_T("%s/%s")
    #define TESTCONFIGURATION_LOCATION CONFIG_SYSCONFDIR
    #define CONFIGURATION_PENDING CONFIG_SYSCONFDIR MI_T("/dsc/configuration/Pending.mof")
    #define CONFIGURATION_CURRENT CONFIG_SYSCONFDIR MI_T("/dsc/configuration/Current.mof")
    #define CONFIGURATION_CURRENT_CHECKSUM CONFIG_SYSCONFDIR MI_T("/dsc/configuration/Current.mof.checksum") 
    #define CONFIGURATION_PREVIOUS CONFIG_SYSCONFDIR MI_T("/dsc/configuration/Previous.mof")
    #define METACONFIG_LOCATION_MOF CONFIG_SYSCONFDIR MI_T("/dsc/configuration/MetaConfig.mof")
    #define DSCCORE_LIB CONFIG_LIBDIR MI_T("/libdsccore.so")
    #define CRONTAB MI_T("/etc/crontab")
    #define CRONTABBAK MI_T("/etc/crontab.bak")
    #define TEST_CRONTAB1 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/Test_crontab1")
    #define TEST_CRONTAB2 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/Test_crontab2")
    #define RESULT_CRONTAB CONFIG_SRCDIR MI_T("/dsc/tests/Engine/LCM") MI_T("/Result_crontab")
#endif


#define LCM_CLASSNAME MI_T("MSFT_DSCLocalConfigurationManager")
#define LCM_SETMETACONFIGMETHODNAME MI_T("SendMetaConfiguration")
#define LCM_SETMETHODNAME MI_T("SendConfigurationApply")
#define META_CONFIG_PULL MI_T("instance of MSFT_DSCMetaConfiguration\n{\n    ConfigurationID=\"be2e692d-9e96-486d-92d0-bd2164e2692b\";\n    RefreshFrequencyMins = 9000;\n    DownloadManagerName=\"FileDownloadManager\";\n  ConfigurationModeFrequencyMins = 9000;\n};\n")
#define META_CONFIG_PULL_UUID MI_T("instance of MSFT_DSCMetaConfiguration\n{\n    DownloadManagerName=\"FileDownloadManager\";\n  ConfigurationID=\"UseSystemUUID\";\nRefreshFrequencyMins = 9000;\n    ConfigurationModeFrequencyMins = 9000;\n};\n")
#define META_CONFIG_WEBDOWNLOAD_PULL MI_T("instance of MSFT_KeyValuePair as $keyvaluepair1\n{\n    Key=\"ServerUrl\";\n    value=\"http://localhost:8080/PSDSCPullServer/PSDSCPullServer.svc\";\n};\n instance of MSFT_KeyValuePair as $keyvaluepair2\n{\n      key=\"AllowUnsecureConnection\";\n      value = \"TRUE\";\n};\n\n instance of MSFT_DSCMetaConfiguration\n{\n    ConfigurationID=\"d017d2f9-f6c6-4b5c-9ce1-a3bc94ac5d40\";\n    DownloadManagerCustomData = {$keyvaluepair1,$keyvaluepair2};\n    RefreshFrequencyMins = 9000;\n    DownloadManagerName=\"WebDownloadManager\";\n  ConfigurationModeFrequencyMins = 9000;\n};\n")

#define TEST_MODULE1 MI_T("%windir%\\System32\\WindowsPowershell\\v1.0\\modules\\PsModuleForTestModuleForPull")
#define TEST_MODULE2 MI_T("%windir%\\System32\\WindowsPowershell\\v1.0\\modules\\PsModuleForTestModuleForPull2")

#if defined(_MSC_VER)    
EXTERN_C __declspec(selectany) const GUID S_DscCoreR = {0x50df9e12, 0xa8c4, 0x4939, {0xb2, 0x81, 0x47, 0xe1, 0x32, 0x5b, 0xa6, 0x3e}};
#endif

#define CONFIGFORCESTOPPED_EventID  0x1022
#define CONFIGFORCESCANCELED_EventID  0x1019

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
    if(*pBuffer == NULL)
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

MI_Result CopyConfig(_In_ const MI_Char * pwszFileName, NitsTrapHandle h)

{
    MI_Result result;
    MI_Char *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(pwszFileName, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(File_CopyT(TEST_CONFIG_FILE, fileFull) != 0)
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

MI_Result CopyMetaConfigLocally(NitsTrapHandle h)
{
    MI_Result result;
    MI_Char *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(File_CopyT(fileFull, TEST_META_CONFIG_MOF) != 0)
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

MI_Result SaveFile(_In_z_ const MI_Char* filePath,
                   _In_reads_bytes_(dataSize) const MI_Uint8* ConfigData,
                   MI_Uint32 dataSize)
{
    FILE *fp;
    size_t result;    
    fp = File_OpenT(filePath, MI_T("wb"));
    if( fp == NULL)
    {
        return MI_RESULT_FAILED;
    }
    result = fwrite(ConfigData, 1, dataSize, fp);
    File_Close(fp);
    if( result != dataSize)
    {
        return MI_RESULT_FAILED;
    }
    return MI_RESULT_OK;

}

MI_Result UpdateMetaConfigForPull(NitsTrapHandle h)
{
    MI_Char *fileFull;
    MI_Result result;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);
    const MI_Uint8 *configData =    (const MI_Uint8 *) META_CONFIG_PULL;
    MI_Uint32 bufferSize = Tcslen(META_CONFIG_PULL) * sizeof(MI_Char);
    File_RemoveT(fileFull);    
    return SaveFile(fileFull, configData, bufferSize);
}

MI_Result UpdateMetaConfigForPullUsingUUID(NitsTrapHandle h)
{
    MI_Char *fileFull;
    MI_Result result;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);
    const MI_Uint8 *configData =    (const MI_Uint8 *) META_CONFIG_PULL_UUID;
    MI_Uint32 bufferSize = Tcslen(META_CONFIG_PULL_UUID) * sizeof(MI_Char);
    File_RemoveT(fileFull);    
    return SaveFile(fileFull, configData, bufferSize);
}


MI_Result UpdateMetaConfigForWebServerPull(NitsTrapHandle h)
{
    MI_Char *fileFull;
    MI_Result result;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);
    const MI_Uint8 *configData =    (const MI_Uint8 *) META_CONFIG_WEBDOWNLOAD_PULL;
    MI_Uint32 bufferSize = Tcslen(META_CONFIG_WEBDOWNLOAD_PULL) * sizeof(MI_Char);
    File_RemoveT(fileFull);    
    return SaveFile(fileFull, configData, bufferSize);
}



MI_Result CopyMetaConfig(NitsTrapHandle h)
{
    MI_Result result;
    MI_Char *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(File_CopyT(TEST_META_CONFIG_MOF, fileFull) != 0)
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}


MI_Result DeleteConfig(_In_ const MI_Char * pwszFileName, NitsTrapHandle h)
{
    MI_Result result;
    MI_Char *fileFull;
    MI_Instance *cimError = NULL;
    result = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(pwszFileName, &fileFull, &cimError);

    //The error might be caused by nits fault injection
    NitsIgnoringError();

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    if(File_ExistT(fileFull) == 0)
    {
        if(!File_RemoveT(fileFull))
        {
            return MI_RESULT_FAILED;
        }
    }

    return MI_RESULT_OK;
}

void RecursivelyDeleteDirectory(_In_z_ MI_Char *directoryPath)
{
    MI_Char pathTempVar[MAX_PATH];
    Internal_Dir *dirHandle = NULL;
    Internal_DirEnt *dirEntry = NULL;
    dirHandle = Internal_Dir_Open(directoryPath, NitsMakeCallSite(-3, NULL, NULL, 0) );
    if( dirHandle != NULL )
    {
        dirEntry =  Internal_Dir_Read(dirHandle, NULL);
        
        while (dirEntry != NULL )
        {
            if(Stprintf(pathTempVar, MAX_PATH, FMT, directoryPath, dirEntry->name) > 0 )
            {
                if(Tcscasecmp(MI_T(".."), dirEntry->name) == 0 ||
                   Tcscasecmp(MI_T("."), dirEntry->name)==0 )
                {
                }
                else if(dirEntry->isDir)
                {
                    RecursivelyDeleteDirectory(pathTempVar);
                }
                else
                {
                    File_RemoveT(pathTempVar);
                }                    
            }
            dirEntry =  Internal_Dir_Read(dirHandle, NULL); //Next
        }
        
        Internal_Dir_Close( dirHandle);
    }
    Directory_Remove(directoryPath);
}

NitsSetup0(InitLCM, Ptr)
    MI_Instance *cimErrorDetails = NULL;
#ifdef _MSC_VER
    NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", LCMTraps);
#else
    NitsTrapHandle h = NitsOpenTrap(DSCCORE_LIB, LCMTraps);
#endif
    NitsAssert(h != NULL, MI_T("Failed to load LCMTraps!"));
    NitsContext()->_Ptr->ptr = h;
    
    DeleteConfig(CONFIGURATION_CURRENT, h);
    MI_Result miResult = NitsGetTrap(h, LCMTraps, _LCMTest_InitHandler)(MI_T("MyMethod"), &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to initialize LCM!"));
NitsEndSetup

NitsCleanup(InitLCM)
    MI_Instance *cimErrorDetails = NULL;
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;
    MI_Result miResult = NitsGetTrap(h, LCMTraps, _LCMTest_UnInitHandler)(&cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to uninitialize LCM!"));

    if (h != NULL)
        NitsCloseTrap(h);
NitsEndCleanup

NitsSetup0(InitLCMWithoutHandler, Ptr)
    MI_Instance *cimErrorDetails = NULL;
#ifdef _MSC_VER
    NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", LCMTraps);
#else
    NitsTrapHandle h = NitsOpenTrap(DSCCORE_LIB, LCMTraps);
#endif
    NitsAssert(h != NULL, MI_T("Failed to load LCMTraps!"));
    NitsContext()->_Ptr->ptr = h;
    // create meta config with certificate information.
    MI_Result miResult  = CopyMetaConfigLocally(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(MI_T("Failed to take backup of metaConfig!"));
    }
    miResult = UpdateMetaConfigForPull(h);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Unable to update the meta configuration for certificate."));    
    //Delete current configuration
    DeleteConfig(CONFIGURATION_CURRENT, h);
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_InitHandler)(MI_T("MyMethod"), &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to initialize LCM!"));   
NitsEndSetup

NitsCleanup(InitLCMWithoutHandler)
    MI_Instance *cimErrorDetails = NULL;
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;
    MI_Result miResult  = CopyMetaConfig(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(MI_T("Failed to copy back original meta config!"));
    } 

    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_UnInitHandler)(&cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to uninitialize LCM!"));    
    if (h != NULL)
        NitsCloseTrap(h);
NitsEndCleanup

NitsDRTTest1(TestSendConfigurationApply, InitLCMWithoutHandler, PtrVal)

    PSSemanticsProgress progressReport = {0};
    // test against the following.
    // 1 = SendConfiguration
    // 2 = SendConfigurationApply
    // 3 = GetConfiguration
    // 4 = TestConfiguration
    // 5 = ApplyConfiguration
    // 6 = SendMetaConfigurationApply
    // 7 = GetMetaConfiguration
    // 8 = RollBack
    // 9 = PerformRequiredConfigurationChecks
    // 10 = StopConfiguration
    
    for( MI_Uint32 xCount = 1; xCount < 11; xCount++)
    {
        if( xCount != enum_RollBack && xCount != enum_StopConfiguration)
        {
            progressReport.wait = 0;
            progressReport.writeMessageCount = 0;
            progressReport.writeProgressCount = 0;
            progressReport.methodToCall = (methodNames)xCount;            
            RunSendConfigurationApply(TRUE, &progressReport);        
        }
    }

NitsEndTest

NitsDRTTest1(TestSendConfiguration, InitLCMWithoutHandler, PtrVal)

    PSSemanticsProgress progressReport = {0};
    // test against the following.
    // 1 = SendConfiguration
    // 2 = SendConfigurationApply
    // 3 = GetConfiguration
    // 4 = TestConfiguration
    // 5 = ApplyConfiguration
    // 6 = SendMetaConfigurationApply
    // 7 = GetMetaConfiguration
    // 8 = RollBack
    // 9 = PerformRequiredConfigurationChecks
    // 10 = StopConfiguration
    
    for( MI_Uint32 xCount = 1; xCount < 11; xCount++)
    {
        if( xCount != enum_RollBack && xCount != enum_StopConfiguration)
        {
            progressReport.wait = 0;
            progressReport.writeMessageCount = 0;
            progressReport.writeProgressCount = 0;
            progressReport.methodToCall = (methodNames)xCount;            
            RunSendConfiguration(TRUE, &progressReport);        
        }
    }

NitsEndTest

NitsDRTTest1(TestGetConfiguration, InitLCMWithoutHandler, PtrVal)

    PSSemanticsProgress progressReport = {0};
    // test against the following.
    // 1 = SendConfiguration
    // 2 = SendConfigurationApply
    // 3 = GetConfiguration
    // 4 = TestConfiguration
    // 5 = ApplyConfiguration
    // 6 = SendMetaConfigurationApply
    // 7 = GetMetaConfiguration
    // 8 = RollBack
    // 9 = PerformRequiredConfigurationChecks
    // 10 = StopConfiguration
    
    for( MI_Uint32 xCount = 1; xCount < 11; xCount++)
    {
        if( xCount != enum_RollBack && xCount != enum_StopConfiguration)
        {
            progressReport.wait = 0;
            progressReport.writeMessageCount = 0;
            progressReport.writeProgressCount = 0;
            progressReport.methodToCall = (methodNames)xCount;            
            RunGetConfiguration(TRUE, &progressReport);        
        }
    }

NitsEndTest

NitsDRTTest1(TestApplyConfiguration, InitLCMWithoutHandler, PtrVal)

    PSSemanticsProgress progressReport = {0};
    // test against the following.
    // 1 = SendConfiguration
    // 2 = SendConfigurationApply
    // 3 = GetConfiguration
    // 4 = TestConfiguration
    // 5 = ApplyConfiguration
    // 6 = SendMetaConfigurationApply
    // 7 = GetMetaConfiguration
    // 8 = RollBack
    // 9 = PerformRequiredConfigurationChecks
    // 10 = StopConfiguration
     
    for( MI_Uint32 xCount = 1; xCount < 11; xCount++)
    {
        if( xCount != enum_RollBack && xCount != enum_StopConfiguration)
        {
            progressReport.wait = 0;
            progressReport.writeMessageCount = 0;
            progressReport.writeProgressCount = 0;
            progressReport.methodToCall = (methodNames)xCount;            
            RunApplyConfiguration(TRUE, &progressReport);        
        }
    }

NitsEndTest

NitsDRTTest1(TestGetMetaConfiguration, InitLCMWithoutHandler, PtrVal)

    PSSemanticsProgress progressReport = {0};
    // test against the following.
    // 1 = SendConfiguration
    // 2 = SendConfigurationApply
    // 3 = GetConfiguration
    // 4 = TestConfiguration
    // 5 = ApplyConfiguration
    // 6 = SendMetaConfigurationApply
    // 7 = GetMetaConfiguration
    // 8 = RollBack
    // 9 = PerformRequiredConfigurationChecks
    // 10 = StopConfiguration
    
    for( MI_Uint32 xCount = 1; xCount < 11; xCount++)
    {
        if( xCount != enum_RollBack && xCount != enum_StopConfiguration)
        {
            progressReport.wait = 0;
            progressReport.writeMessageCount = 0;
            progressReport.writeProgressCount = 0;
            progressReport.methodToCall = (methodNames)xCount;            
            RunGetMetaConfiguration(TRUE, &progressReport);        
        }
    }

NitsEndTest

typedef struct _TESTMI_Container
{
    MI_Application *application;
    MI_Session *session;
    MI_Operation *operation;
    MI_Uint32 messageReceived;
} TESTMI_Container;

void MI_CALL TestStopConfigurationWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
             MI_Uint32 channel,
    _In_z_   const MI_Char *message)

{
    // call stop configuration here.
    MI_Instance *parameter = NULL;
    MI_Value value;
//    const MI_Instance *result;
//    const MI_Instance *extendedInfo;
//    MI_Boolean moreResults;
//    MI_Result resultCode;
//    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    TESTMI_Container *messageContainer = (TESTMI_Container *)callbackContext;
    MI_Char matchString[] = MI_T("Executing Set for Class TEST_Stop");
    MI_Uint32 matchStringLength= sizeof(matchString)/sizeof(MI_Char);
    MI_Uint32 messageLen = Tcslen(message);
    TTRACE(MI_T("begin TestStopConfigurationWriteMessage"));
    
    if( messageLen > matchStringLength && Tcscasecmp(matchString, message+messageLen-matchStringLength+1) == 0 )
    {
        TTRACE(MI_T("********** TestStopConfigurationWriteMessage**********"));        
       messageContainer->messageReceived = 1;
        if( NitsCompare(MI_Application_NewInstance(messageContainer->application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
        {
            value.boolean = true;            
            if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
            {               
                MI_Session_Invoke(messageContainer->session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("StopConfiguration"), NULL, parameter, &callbacks, messageContainer->operation);
            }
            MI_Instance_Delete(parameter);
        }
    }
}

NitsDRTCommonTest1(TestStopConfiguration, InitLCMWithoutHandler, PtrVal)
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    MI_Uint32 size;
    MI_Uint8 *pbuffer = NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    TESTMI_Container messageContainer = {0};
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
   

    if( NitsCompare(ReadTestFile(TEST_STOPMOF, &pbuffer, &size), S_OK, MI_T("Read Stop Test File Failed.")) )
    {
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                value.boolean = true;            
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                {
                    value.uint8a.data= pbuffer;   
                    value.uint8a.size = size;
                    if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                                MI_T("MI_Application_NewSession failed.")))
                        {                
                            callbacks.writeMessage = TestStopConfigurationWriteMessage;
                            messageContainer.application = &application;
                            messageContainer.session = &session;
                            messageContainer.messageReceived = 0;
                            messageContainer.operation = NULL;
                            callbacks.callbackContext = (void*) &messageContainer;
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("SendConfigurationApply"), NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                NitsCompare(resultCode, MI_RESULT_OK, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
                            }       
                            if(messageContainer.operation != NULL)
                            {
                                if( NitsCompare(MI_Operation_GetInstance(messageContainer.operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")) )
                                {
                                    NitsCompare(resultCode, MI_RESULT_OK, MI_T("Expected success code but got a failure code"));
                                }                                 
                                MI_Operation_Close( messageContainer.operation);
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
#ifdef _MSC_VER
    NitsCompare(messageContainer.messageReceived, 1, MI_T("WriteMessage with expected value not found."));
#endif
NitsEndTest

NitsDRTCommonTest1(TestLCM_Pull_GetConfiguration, InitLCMWithoutHandler, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult = MI_RESULT_OK;
    NitsTrapHandle h = NitsContext()->_InitLCMWithoutHandler->_Ptr->ptr;

    //miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_GetConfiguration)(&cimErrorDetails);
    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull configuration failed"));

    MI_Char *fileFull; 
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_CURRENT_CHECKSUM, &fileFull, &cimErrorDetails);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call ExpandPath for checksum file failed"));
   

    File_RemoveT(fileFull);
    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull configuration failed"));    

NitsEndTest

NitsDRTCommonTest1(TestLCM_Pull_ExecuteWithHandler, InitLCMWithoutHandler, PtrVal)
//    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult = MI_RESULT_OK;
    NitsTrapHandle h = NitsContext()->_InitLCMWithoutHandler->_Ptr->ptr;

    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull Execute failed"));

NitsEndTest

NitsSetup0(InitLCMForUUID, Ptr)
    MI_Instance *cimErrorDetails = NULL;
#ifdef _MSC_VER
    NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", LCMTraps);
#else
    NitsTrapHandle h = NitsOpenTrap(DSCCORE_LIB, LCMTraps);
#endif
    NitsAssert(h != NULL, MI_T("Failed to load LCMTraps!"));
    NitsContext()->_Ptr->ptr = h;
    // create meta config with certificate information.
    MI_Result miResult  = CopyMetaConfigLocally(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(MI_T("Failed to take backup of metaConfig!"));
    }
    miResult = UpdateMetaConfigForPullUsingUUID(h);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Unable to update the meta configuration for certificate."));    
    //Delete current configuration
    DeleteConfig(CONFIGURATION_CURRENT, h);    
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_InitHandler)(MI_T("MyMethod"), &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to initialize LCM!"));   

NitsEndSetup

NitsCleanup(InitLCMForUUID)
    MI_Instance *cimErrorDetails = NULL;
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;
    MI_Result miResult  = CopyMetaConfig(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(MI_T("Failed to copy back original meta config!"));
    } 

    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_UnInitHandler)(&cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to uninitialize LCM!"));    
    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

NitsDRTCommonTest1(TestLCM_Pull_GetConfigurationUsingUUID, InitLCMForUUID, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult = MI_RESULT_OK;
    NitsTrapHandle h = NitsContext()->_InitLCMForUUID->_Ptr->ptr;

    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull configuration failed"));

    MI_Char *fileFull; 
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_CURRENT_CHECKSUM, &fileFull, &cimErrorDetails);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call ExpathPath for checksum file failed"));
   

    File_RemoveT(fileFull);
    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull configuration failed"));    

NitsEndTest


NitsDRTCommonTest1(TestLCM_Pull_ExecuteWithoutHandler, InitLCMWithoutHandler, PtrVal)
//    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult = MI_RESULT_OK;
    NitsTrapHandle h = NitsContext()->_InitLCMWithoutHandler->_Ptr->ptr;

    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull Execute failed"));

NitsEndTest


NitsSetup0(InitLCMPull, Ptr)
    MI_Instance *cimErrorDetails = NULL;
#ifdef _MSC_VER
    NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", LCMTraps);
#else
    NitsTrapHandle h = NitsOpenTrap(DSCCORE_LIB, LCMTraps);
#endif
    NitsAssert(h != NULL, MI_T("Failed to load LCMTraps!"));
    NitsContext()->_Ptr->ptr = h;
    // create meta config with certificate information.
    MI_Result miResult  = CopyMetaConfigLocally(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(MI_T("Failed to take backup of metaConfig!"));
    }
    miResult = UpdateMetaConfigForWebServerPull(h);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Unable to update the meta configuration for certificate."));    
    //Delete current configuration
    DeleteConfig(CONFIGURATION_CURRENT, h);    
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_InitHandler)(MI_T("MyMethod"), &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to initialize LCM!"));   
    //Delete modules
    MI_Char * modulePath1 = NULL;
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULE1, &modulePath1, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand pending path failed"));    
    RecursivelyDeleteDirectory(modulePath1);
    MI_Char * modulePath2 = NULL;
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TEST_MODULE2, &modulePath2, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand pending path failed"));    
    RecursivelyDeleteDirectory(modulePath2);    

NitsEndSetup

NitsCleanup(InitLCMPull)
    MI_Instance *cimErrorDetails = NULL;
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;
    MI_Result miResult  = CopyMetaConfig(h);
    if( miResult != MI_RESULT_OK )
    {
        TTRACE(MI_T("Failed to copy back original meta config!"));
    } 

    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_UnInitHandler)(&cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to uninitialize LCM!"));    
    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

MI_Boolean IsServerSKU(NitsTrapHandle h)
{
    MI_Boolean isServerSKU = MI_FALSE;
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
//    volatile unsigned int count = 0;    
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, MI_T("MI_Application function table should not be NULL")))
    {
        if (NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession returns OK")) &&
            NitsAssert(session.ft != NULL, MI_T("MI_Session function table should not be NULL")))
        {
            MI_Session_EnumerateInstances(&session, 0, NULL, MI_T("root\\cimv2"), MI_T("Win32_OperatingSystem"), MI_FALSE, NULL, &operation);
            NitsAssert(operation.ft != NULL, MI_T("operation function table null"));
            const MI_Instance *instance = NULL;
            MI_Boolean moreResults = MI_TRUE;
            MI_Result result = MI_RESULT_FAILED;
            const MI_Char *errorMessage;
            const MI_Instance *errorDetail;
            while(moreResults == MI_TRUE)
            {
                MI_Operation_GetInstance(&operation, &instance, &moreResults, &result, &errorMessage, &errorDetail);
            }
            if(NitsAssert(result == MI_RESULT_OK, MI_T("Operation failed")) && instance != NULL)
            {
                MI_Value value;
                MI_Type type;
//                MI_Uint32 flags = 0;            
                result = MI_Instance_GetElement(instance, MI_T("producttype"), &value, &type, NULL, NULL);
                if(NitsAssert(result == MI_RESULT_OK, MI_T("Failed")) && NitsAssert(type == MI_UINT32, MI_T("Unexpected type")))
                {
                    if(value.uint32 != 1 )
                    {
                        // we want to run the test only on Blue
                        result = MI_Instance_GetElement(instance, MI_T("version"), &value, &type, NULL, NULL);
                        if(NitsAssert(result == MI_RESULT_OK, MI_T("Failed")) && NitsAssert(type == MI_STRING, MI_T("Unexpected type")))
                        {
                            if(Tcscasecmp(value.string, MI_T("6.3")) >= 0 )
                                isServerSKU = MI_TRUE;
                        }
                    }
                }
            }


            MI_Operation_Cancel(&operation, MI_REASON_NONE);
            MI_Operation_Close(&operation);

            MI_Session_Close(&session, NULL, NULL);
        }

        MI_Application_Close(&application);
    }    
    return isServerSKU;
}

NitsTestSetTimeout(TestLCM_Pull_Execute, 600)
NitsDRTCommonTest1(TestLCM_Pull_Execute, InitLCMPull, PtrVal)
//    MI_Instance *cimErrorDetails = NULL;
    MI_Result miResult = MI_RESULT_OK;
    NitsTrapHandle h = NitsContext()->_InitLCMPull->_Ptr->ptr;
#ifdef _MSC_VER
    if( IsServerSKU(h))
    {
        //Sleep(2000);

        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );

        NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull configuration failed"));
    }
    else
    {
        TTRACE(MI_T("Skipping the test as this is client SKU."));
    }
#else
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_LCM_Pull_Execute)( );
        NitsCompare(miResult, MI_RESULT_OK, MI_T("Call pull configuration failed"));
#endif

NitsEndTest

NitsDRTCommonTest1(TestSetConfig, InitLCM, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 size;
    MI_Result miResult = ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("ReadTestFile Failed"));
    NitsTrapHandle h = NitsContext()->_InitLCM->_Ptr->ptr;

    // Start without a pending configuration file otherwise the test will eventually fail
    // during fault injection tests.
    DeleteConfig(CONFIGURATION_PENDING, h);
    DeleteConfig(METACONFIG_LOCATION_MOF, h);

    if(miResult == MI_RESULT_OK)
    {
        miResult = NitsGetTrap(h, LCMTraps, _LCMTest_CallSetConfiguration)(pbuffer, size, LCM_SETFLAGS_DEFAULT, MI_FALSE, NULL, &cimErrorDetails);
    }

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call set configuration failed"));

    MI_Char * pendingPath = NULL;
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_PENDING, &pendingPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand pending path failed"));
    if(pendingPath == NULL)
    {
        return;
    }
    NitsAssert(File_ExistT(pendingPath) == -1, MI_T("pending file still exist"));
    MI_Char * currentPath = NULL;
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_CURRENT, &currentPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand current path failed"));
    if(currentPath == NULL)
    {
        return;
    }
    NitsAssert(File_ExistT(currentPath) != -1, MI_T("current file does not exist"));
    MI_Char * metaConfigPath = NULL;
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(METACONFIG_LOCATION_MOF, &metaConfigPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand meta config path failed"));
    if(metaConfigPath == NULL)
    {
        return;
    }

        NitsAssert(File_ExistT(metaConfigPath) != -1, MI_T("meta config file does not exist"));
        MI_Char * currentLCMStatusCodeHistory = NULL;
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_GetLCMStatusCodeHistory)(&currentLCMStatusCodeHistory, &cimErrorDetails);
        NitsCompare(miResult, MI_RESULT_OK, MI_T("get lcm status code history failed"));
        NitsAssert(currentLCMStatusCodeHistory != NULL, MI_T("lcm status code history is null"));
        NitsCompareString(currentLCMStatusCodeHistory, MI_T("0,1,0,"), MI_T("lcm status code history is different from expected"));

NitsEndTest

NitsDRTCommonTest1(TestSetConfigPendingExist, InitLCM, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 size;
    MI_Result miResult = ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size);
    NitsTrapHandle h = NitsContext()->_InitLCM->_Ptr->ptr;

    NitsAssert(miResult == MI_RESULT_OK, MI_T("ReadTestFile Failed"));

    CopyConfig(CONFIGURATION_PENDING, h);

    MI_Char * pendingPath = NULL;
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_PENDING, &pendingPath, &cimErrorDetails);
    if(!NitsAssert(miResult == MI_RESULT_OK, MI_T("expand pending path failed")))
    {
        NitsReturn;
    }
    if(pendingPath == NULL)
    {
        return;
    }

    if(!NitsAssert(File_ExistT(pendingPath) != -1, MI_T("pending file should exist for the negative tests.")))
    {
        NitsReturn;
    }

    if(miResult == MI_RESULT_OK)
    {
        miResult = NitsGetTrap(h, LCMTraps, _LCMTest_CallSetConfiguration)(pbuffer, size, LCM_SETFLAGS_DEFAULT, MI_FALSE, NULL, &cimErrorDetails);
    }

    NitsAssert(miResult != MI_RESULT_OK, MI_T("Call set configuration should fail when pending exists"));

    DeleteConfig(CONFIGURATION_PENDING, h);
    NitsAssert(File_ExistT(pendingPath) == -1, MI_T("pending file should be deleted by cleanup."));

        MI_Char * currentLCMStatusCodeHistory = NULL;
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_GetLCMStatusCodeHistory)(&currentLCMStatusCodeHistory, &cimErrorDetails);
        NitsCompare(miResult, MI_RESULT_OK, MI_T("get lcm status code history failed"));
        NitsAssert(currentLCMStatusCodeHistory != NULL, MI_T("lcm status code history is null"));
        NitsCompareString(currentLCMStatusCodeHistory, MI_T("0,1,0,"), MI_T("lcm status code history is different from expected"));

NitsEndTest

NitsDRTCommonTest1(TestSetConfigWithoutCurrent, InitLCM, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 size;
    MI_Result miResult = ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size);
    NitsTrapHandle h = NitsContext()->_InitLCM->_Ptr->ptr;
    MI_Char * pendingPath = NULL;
    MI_Char * currentPath = NULL;
    MI_Char * previousPath = NULL;
    MI_Char * dirPath = NULL;

    NitsAssert(miResult == MI_RESULT_OK, MI_T("ReadTestFile Failed"));    

    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_PENDING, &pendingPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand pending path failed"));
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_CURRENT, &currentPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand current path failed"));
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_PREVIOUS, &previousPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand previous path failed"));
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(TESTCONFIGURATION_LOCATION, &dirPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand config directory path failed"));

    if(pendingPath == NULL || currentPath == NULL || previousPath == NULL || dirPath == NULL)
    {
        return;
    }

    DeleteConfig(CONFIGURATION_PENDING, h);
    NitsAssert(File_ExistT(pendingPath) == -1, MI_T("pending file should be deleted by cleanup."));
    DeleteConfig(CONFIGURATION_CURRENT, h);
    NitsAssert(File_ExistT(currentPath) == -1, MI_T("pending file should be deleted by cleanup."));
    DeleteConfig(CONFIGURATION_PREVIOUS, h);
    NitsAssert(File_ExistT(previousPath) == -1, MI_T("pending file should be deleted by cleanup."));

    if(miResult == MI_RESULT_OK)
    {
        miResult = NitsGetTrap(h, LCMTraps, _LCMTest_CallSetConfiguration)(pbuffer, size, LCM_SETFLAGS_DEFAULT, MI_FALSE, NULL, &cimErrorDetails);
    }

    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call set configuration failed"));

    NitsAssert(File_ExistT(pendingPath) == -1, MI_T("pending file still exist"));
    NitsAssert(File_ExistT(currentPath) != -1, MI_T("current file does not exist"));

        MI_Char * currentLCMStatusCodeHistory = NULL;
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_GetLCMStatusCodeHistory)(&currentLCMStatusCodeHistory, &cimErrorDetails);
        NitsCompare(miResult, MI_RESULT_OK, MI_T("get lcm status code history failed"));
        NitsAssert(currentLCMStatusCodeHistory != NULL, MI_T("lcm status code history is null"));
        NitsCompareString(currentLCMStatusCodeHistory, MI_T("0,1,0,"), MI_T("lcm status code history is different from expected"));

NitsEndTest

NitsDRTCommonTest1(TestConsistencyEngine, InitLCM, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Char * pendingPath = NULL;
    MI_Char * currentPath = NULL;
    MI_Result miResult = MI_RESULT_OK;
    NitsTrapHandle h = NitsContext()->_InitLCM->_Ptr->ptr;

        DeleteConfig(CONFIGURATION_PENDING, h);
    DeleteConfig(CONFIGURATION_PREVIOUS, h);
    DeleteConfig(METACONFIG_LOCATION_MOF, h);

    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_PENDING, &pendingPath, &cimErrorDetails);
    if(!NitsAssert(miResult == MI_RESULT_OK, MI_T("expand pending path failed")))
    {
        NitsReturn;
    }
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_CURRENT, &currentPath, &cimErrorDetails);
    if(!NitsAssert(miResult == MI_RESULT_OK, MI_T("expand current path failed")))
    {
        NitsReturn;
    }
    if(pendingPath == NULL || currentPath == NULL)
    {
        return;
    }

    //Delete current
    File_RemoveT(currentPath );
    //copy to Pending
    if(NitsAssert(File_CopyT(TEST_CONFIG_FILE, pendingPath) == 0, MI_T("CopyFile failed")))
    {
        if(NitsCompare(NitsGetTrap(h, LCMTraps, _LCMTest_CallConsistencyEngine)(NULL, 1, &cimErrorDetails), MI_RESULT_OK, MI_T("CallConsistencyEngine failed")))
        {
            NitsAssert( File_ExistT(pendingPath) == -1 , MI_T("Pending file still exist"));
            NitsAssert( File_ExistT(currentPath) == 0 , MI_T("Current file does not exist"));            
        }
    }

    File_RemoveT(pendingPath);

        MI_Char * currentLCMStatusCodeHistory = NULL;
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_GetLCMStatusCodeHistory)(&currentLCMStatusCodeHistory, &cimErrorDetails);
        NitsCompare(miResult, MI_RESULT_OK, MI_T("get lcm status code history failed"));
        NitsAssert(currentLCMStatusCodeHistory != NULL, MI_T("lcm status code history is null"));
        NitsCompareString(currentLCMStatusCodeHistory, MI_T("0,1,0,"), MI_T("lcm status code history is different from expected"));

NitsEndTest

NitsDRTCommonTest1(TestSendConfiguration_SaveToPendingOnly, InitLCM, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Char * pendingPath = NULL;
    MI_Char * currentPath = NULL;
    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 size = 0;
    NitsTrapHandle h = NitsContext()->_InitLCM->_Ptr->ptr;
    MI_Result miResult = ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("ReadTestFile Failed"));

    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_PENDING, &pendingPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand pending path failed"));
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_ExpandPath)(CONFIGURATION_CURRENT, &currentPath, &cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("expand current path failed"));
    if(pendingPath == NULL || currentPath == NULL)
    {
        return;
    }

    //Delete current
    File_RemoveT(currentPath );
    File_RemoveT(pendingPath );
    if(NitsCompare(NitsGetTrap(h, LCMTraps, _LCMTest_CallSetConfiguration)(pbuffer, size, LCM_SETFLAGS_SAVETOPENDINGONLY, MI_FALSE, NULL, &cimErrorDetails), MI_RESULT_OK, MI_T("CallSetConfiguration failed")))
    {
        NitsAssert( File_ExistT(pendingPath) == 0 , MI_T("Pending file does not exist"));
        NitsAssert( File_ExistT(currentPath) == -1 , MI_T("Current file still exist"));            
    }
    File_RemoveT(pendingPath);

        MI_Char * currentLCMStatusCodeHistory = NULL;
        miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_GetLCMStatusCodeHistory)(&currentLCMStatusCodeHistory, &cimErrorDetails);
        NitsCompare(miResult, MI_RESULT_OK, MI_T("get lcm status code history failed"));
        NitsAssert(currentLCMStatusCodeHistory != NULL, MI_T("lcm status code history is null"));
        NitsCompareString(currentLCMStatusCodeHistory, MI_T("0,1,0,"), MI_T("lcm status code history is different from expected"));

NitsEndTest

void MI_CALL TestWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
             MI_Uint32 channel,
    _In_z_   const MI_Char *message);

void RunSendConfigurationApply(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    MI_Uint32 size;
    MI_Uint8 *pbuffer = NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
   
    if( NitsCompare(ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                value.boolean = true;            
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                {
                    value.uint8a.data= pbuffer;   
                    value.uint8a.size = size;
                    if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                                MI_T("MI_Application_NewSession failed.")))
                        {                
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("SendConfigurationApply"), NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(bRunFirstTime)
                                {
                                    if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                                    {
#ifdef _MSC_VER
                                        NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                                    }
                                }
                                else
                                {
                                    //We expect a failure here.
                                    NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
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
}

void RunGetConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    MI_Uint32 size;
    MI_Uint8 *pbuffer = NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
   
    if( NitsCompare(ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                value.uint8a.data= pbuffer;   
                value.uint8a.size = size;
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                {
                    if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                            MI_T("MI_Application_NewSession failed.")))
                    {                
                        MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("GetConfiguration"), NULL, parameter, &callbacks, &operation);
                        if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                        {
                            if(bRunFirstTime)
                            {
                                if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                                {
#ifdef _MSC_VER
                                    NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                                }
                            }
                            else
                            {
                                //We expect a failure here.
                                NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
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
}

void RunTestConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
//    MI_Value value;
    MI_Uint32 size;
    MI_Uint8 *pbuffer = NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
   
    if( NitsCompare(ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                        MI_T("MI_Application_NewSession failed.")))
                {                
                    MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("TestConfiguration"), NULL, parameter, &callbacks, &operation);
                    if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                    {
                        if(bRunFirstTime)
                        {
                            if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                            {
#ifdef _MSV_VER
                                NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                            }
                        }
                        else
                        {
                            //We expect a failure here.
                            NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
                        }
                    }
                    MI_Operation_Close(&operation);
                    MI_Session_Close(&session, NULL, NULL);
                }
                MI_Instance_Delete(parameter);
            }

            MI_Application_Close(&application);
        }    
    }
}

void RunApplyConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
//    MI_Value value;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
    if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
    {
        if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
        {
            if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                    MI_T("MI_Application_NewSession failed.")))
            {                
                MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("ApplyConfiguration"), NULL, NULL, &callbacks, &operation);
                if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                {
                    if(bRunFirstTime)
                    {
                        if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                        {
#ifdef _MSC_VER
                            NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                        }
                    }
                    else
                    {
                        //We expect a failure here.
                        NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
                    }
                }
                MI_Operation_Close(&operation);
                MI_Session_Close(&session, NULL, NULL);
                }
            MI_Instance_Delete(parameter);
        }

        MI_Application_Close(&application);
    }    
}

void RunSendMetaConfigurationApply(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    MI_Uint32 size;
    MI_Uint8 *pbuffer = NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
   
    if( NitsCompare(ReadTestFile(TEST_META_CONFIG_MOF, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                value.uint8a.data= pbuffer;   
                value.uint8a.size = size;
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                {
                    if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                            MI_T("MI_Application_NewSession failed.")))
                    {                
                        MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("SendMetaConfigurationApply"), NULL, parameter, &callbacks, &operation);
                        if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                        {
                            if(bRunFirstTime)
                            {
                                if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                                {
#ifdef _MSC_VER
                                    NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                                }
                            }
                            else
                            {
                                //We expect a failure here.
                                NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
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
}

void RunGetMetaConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
//    MI_Value value;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
    if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
    {
        if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
        {
            if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                    MI_T("MI_Application_NewSession failed.")))
            {                
                MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("GetMetaConfiguration"), NULL, NULL, &callbacks, &operation);
                if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                {
                    if(bRunFirstTime)
                    {
                        if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                        {
#ifdef _MSC_VER
                            NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                        }
                    }
                    else
                    {
                        //We expect a failure here.
                        NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
                    }
                }
                MI_Operation_Close(&operation);
                MI_Session_Close(&session, NULL, NULL);
                }
            MI_Instance_Delete(parameter);
        }

        MI_Application_Close(&application);
    }    
}

void RunSendConfiguration(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    MI_Uint32 size;
    MI_Uint8 *pbuffer = NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage; 
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
   
    if( NitsCompare(ReadTestFile(TEST_CONFIG_FILE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                value.boolean = true;            
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                {
                    value.uint8a.data= pbuffer;   
                    value.uint8a.size = size;
                    if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                                MI_T("MI_Application_NewSession failed.")))
                        {                
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("SendConfiguration"), NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(bRunFirstTime)
                                {
                                    if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                                    {
#ifdef _MSC_VER
                                        NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                                    }
                                }
                                else
                                {
                                    //We expect a failure here.
                                    NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
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
}


void RunRequiredConfigurationChecks(MI_Boolean bRunFirstTime, PSSemanticsProgress *progressReport)
{
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
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    if(bRunFirstTime)
    {
        callbacks.writeMessage = TestWriteMessage;
    }
    callbacks.callbackContext = (void*) progressReport;
   
        
    if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
    {
        if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
        {
            value.uint32 = 1;            
            if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("Flags"), &value, MI_UINT32, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement Flags failed")))
            {
                if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, 
                        MI_T("MI_Application_NewSession failed.")))
                {                
                    MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, MI_T("PerformRequiredConfigurationChecks"), NULL, parameter, &callbacks, &operation);
                    if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                    {
                        if(bRunFirstTime)
                        {
                            if(NitsCompare(resultCode, MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned error")))
                            {
#ifdef _MSC_VER
                                NitsAssert(progressReport->writeMessageCount > 0, MI_T("WriteMessage Count is 0."));
#endif
                            }
                        }
                        else
                        {
                            //We expect a failure here.
                            NitsAssert(resultCode == MI_RESULT_FAILED, MI_T("Expected a failure MI_RESULT_FAILED but either got a success or different result code"));
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

void MI_CALL TestWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
             MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    PSSemanticsProgress *report = (PSSemanticsProgress*) callbackContext;
    report->writeMessageCount++;

    // Now here start another operation that should fail.
    if( report->methodToCall == enum_SendConfiguration)
    {
        RunSendConfiguration(FALSE, report);
    }
    else if( report->methodToCall == enum_SendConfigurationApply)
    {
        RunSendConfigurationApply(FALSE, report);
    }
    else if( report->methodToCall == enum_GetConfiguration)
    {
        RunGetConfiguration(FALSE,report);
    }
    else if( report->methodToCall == enum_TestConfiguration)
    {
        RunTestConfiguration(FALSE, report);
    }
    else if( report->methodToCall == enum_ApplyConfiguration)
    {
        RunApplyConfiguration(FALSE, report);
    }
    else if( report->methodToCall == enum_SendMetaConfigurationApply)
    {
        RunSendMetaConfigurationApply(FALSE, report);
    }
    else if( report->methodToCall == enum_GetMetaConfiguration)
    {
        RunGetMetaConfiguration(FALSE, report);
    }
    else if( report->methodToCall == enum_RollBack)
    {
        // RunRollBack(FALSE);
    }
    else if( report->methodToCall == enum_SendConfiguration)
    {
        RunSendConfiguration(FALSE, report);
    }
    else if( report->methodToCall == enum_PerformRequiredConfigurationChecks)
    {
        RunRequiredConfigurationChecks(FALSE, report);        
    }
    else if( report->methodToCall == enum_StopConfiguration)
    {
        // RunStopConfiguration(FALSE);
    }
}


NitsDRTTest1(TestPerformRequiredConfigurationChecks, InitLCMWithoutHandler, PtrVal)

    PSSemanticsProgress progressReport = {0};
    progressReport.wait = 0;
    progressReport.writeMessageCount = 0;
    progressReport.writeProgressCount = 0;
    progressReport.methodToCall = enum_PerformRequiredConfigurationChecks;

    RunRequiredConfigurationChecks(TRUE, &progressReport);

NitsEndTest


const MI_Char *g_ResourcePatternWriteMessage[4] = {MI_T(" 10"), MI_T(" 11"), MI_T(" 12"), MI_T(" 13")};
const MI_Char *g_ResourcePatternWriteError[4] = {MI_T("10"), MI_T("11"), MI_T("12"), MI_T("13")};


typedef struct _TestNonDependentProgress
{
    unsigned int wait;    
    MI_Uint32 writeMessageValues[4];
    MI_Uint32 writeErrorValues[4];
    
    
} TestNonDependentProgress;


void MI_CALL TestNonDependentWriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
             MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    TTRACE(MI_T(">> WriteMessage"));
    TestNonDependentProgress *report = (TestNonDependentProgress*) callbackContext;

    for(MI_Uint32 iCount = 0 ; iCount < 4; iCount++)
    {
        MI_Char *val = Tcsstr(message, g_ResourcePatternWriteMessage[iCount]);
        if( val != NULL)

        {
            NitsAssert(report->writeMessageValues[iCount] != 0, MI_T("WriteMessage value was expected to be set already."));
            report->writeMessageValues[iCount] = 0;
            break;
        }
    }

    TTRACE(message);
    TTRACE(MI_T("<< WriteMessage"));    
}

void MI_CALL TestNonDependentWriteError(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
    _In_ MI_Instance *instance,
    _In_ MI_Result (MI_CALL * writeErrorResult)(_In_ MI_Operation *operation, MI_OperationCallback_ResponseType response))
{ 
    TTRACE(MI_T(">> WriteError"));
    TestNonDependentProgress *report = (TestNonDependentProgress*) callbackContext;
    MI_Value value;
    MI_Uint32 flags;
    if(MI_Instance_GetElement(instance, MI_T("Message"), &value, NULL, &flags, NULL) == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
    {
        TTRACE(value.string);

        for(MI_Uint32 iCount = 0 ; iCount < 4; iCount++)
        {
            MI_Char *val = Tcsstr(value.string, g_ResourcePatternWriteError[iCount]);
            if( val != NULL)
            {
                NitsAssert(report->writeErrorValues[iCount] != 0, MI_T("writeError value was expected to be set already."));                
                report->writeErrorValues[iCount] = 0;
                break;
            }
        }

    }
    if(writeErrorResult)
    {
        writeErrorResult(operation, MI_OperationCallback_ResponseType_Yes);
    }
    TTRACE(MI_T("<< WriteError"));
}

NitsSetup0(InitLCMNonDependent, Ptr)
//    MI_Instance *cimErrorDetails = NULL;
#ifdef _MSC_VER
    NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", LCMTraps);
#else
    NitsTrapHandle h = NitsOpenTrap(DSCCORE_LIB, LCMTraps);
#endif
    NitsAssert(h != NULL, MI_T("Failed to load LCMTraps!"));
    NitsContext()->_Ptr->ptr = h;

NitsEndSetup

NitsCleanup(InitLCMNonDependent)
//    MI_Instance *cimErrorDetails = NULL;
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;

    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

NitsTestSetTimeout(TestNonDependent_IndependentResources, 600)
NitsDRTTest1(TestNonDependent_IndependentResources, InitLCMNonDependent, PtrVal)

    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_Instance *parameter = NULL;
    MI_Value value;
    const MI_Instance *result;
    const MI_Instance *extendedInfo = NULL;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage = NULL; 
    TestNonDependentProgress progressReport = {0};
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    NitsTrapHandle h = NitsContext()->_InitLCMNonDependent->_Ptr->ptr;   

    MI_Uint8 *pbuffer = NULL;
    MI_Uint32 size;
   
    callbacks.writeMessage = TestNonDependentWriteMessage;
    callbacks.writeError = TestNonDependentWriteError;
    progressReport.wait = 0;
    callbacks.callbackContext = (void*) &progressReport;  

    //Test1

    progressReport.writeMessageValues[0] = 10;
    progressReport.writeMessageValues[1] = 11;
    progressReport.writeMessageValues[2] = 12;
    progressReport.writeMessageValues[3] = 0;   
    progressReport.writeErrorValues[0] = 10;
    progressReport.writeErrorValues[1] = 11;
    progressReport.writeErrorValues[2] = 12;
    progressReport.writeErrorValues[3] = 0;     
    // Start without a pending configuration file otherwise the test will eventually fail
    // during fault injection tests.
    
    TTRACE(MI_T("****    TestNonDependent_1.mof    ****"));
    DeleteConfig(CONFIGURATION_PENDING, h);

    if( NitsCompare(ReadTestFile(TEST_NONINDEPENDENT_INDEPENDENTRESOURCES, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {

            value.uint8a.data = pbuffer;
            value.uint8a.size = size;
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement configurationdata failed")))
                {
                    value.boolean = MI_TRUE;
                    if(NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement force failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession failed.")))
                        {
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, LCM_SETMETHODNAME, NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(NitsAssert(resultCode != MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned success. This is unexpected.")))
                                {
                                    if( errorMessage)
                                        TTRACE(errorMessage);
                                    else
                                    {
                                        MI_Value value;
                                        MI_Uint32 flags;
                                        if(MI_Instance_GetElement(extendedInfo, MI_T("Message"), &value, NULL, &flags, NULL) == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
                                        {
                                            TTRACE(value.string);
                                        }
                                    }
                                    for(MI_Uint32 iCount = 0 ; iCount < 4; iCount++)
                                    {
                                        NitsCompare(progressReport.writeMessageValues[iCount], 0, MI_T("WriteMessage not called as expected. Run the test with -trace option."));
                                        NitsCompare(progressReport.writeErrorValues[iCount], 0, MI_T("WriteError not called as expected. Run the test with -trace option."))     ;                                       
                                    }                           
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
    DeleteConfig(CONFIGURATION_PENDING, h);

    //Test2
    progressReport.writeMessageValues[0] = 0;
    progressReport.writeMessageValues[1] = 11;
    progressReport.writeMessageValues[2] = 12;
    progressReport.writeMessageValues[3] = 0;   
    progressReport.writeErrorValues[0] = 0;
    progressReport.writeErrorValues[1] = 11;
    progressReport.writeErrorValues[2] = 12;
    progressReport.writeErrorValues[3] = 0;   
    // Start without a pending configuration file otherwise the test will eventually fail
    // during fault injection tests.
    TTRACE(MI_T("****    TestNonDependent_2.mof    ****"));    
    DeleteConfig(CONFIGURATION_PENDING, h);

    if( NitsCompare(ReadTestFile(TEST_NONINDEPENDENT_MIXEDMODE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {

            value.uint8a.data = pbuffer;
            value.uint8a.size = size;
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement configurationdata failed")))
                {
                    value.boolean = MI_TRUE;
                    if(NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement force failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession failed.")))
                        {
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, LCM_SETMETHODNAME, NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(NitsAssert(resultCode != MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned success. This is unexpected.")))
                                {
                                    if( errorMessage)
                                        TTRACE(errorMessage);
                                    else
                                    {
                                        MI_Value value;
                                        MI_Uint32 flags;
                                        if(MI_Instance_GetElement(extendedInfo, MI_T("Message"), &value, NULL, &flags, NULL) == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
                                        {
                                            TTRACE(value.string);
                                        }
                                    }                               
                                    for(MI_Uint32 iCount = 0 ; iCount < 4; iCount++)
                                    {
                                        NitsCompare(progressReport.writeMessageValues[iCount], 0, MI_T("WriteMessage not called as expected. Run the test with -trace option."));
                                        NitsCompare(progressReport.writeErrorValues[iCount], 0, MI_T("WriteError not called as expected. Run the test with -trace option.")); 
                                    }                           
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
    DeleteConfig(CONFIGURATION_PENDING, h);    

    //Test3
    progressReport.writeMessageValues[0] = 0;
    progressReport.writeMessageValues[1] = 11;
    progressReport.writeMessageValues[2] = 0;
    progressReport.writeMessageValues[3] = 13;   
    progressReport.writeErrorValues[0] = 0;
    progressReport.writeErrorValues[1] = 11;
    progressReport.writeErrorValues[2] = 0;
    progressReport.writeErrorValues[3] = 13;   

    // Start without a pending configuration file otherwise the test will eventually fail
    // during fault injection tests.
    TTRACE(MI_T("****    TestNonDependent_3.mof    ****"));    
    DeleteConfig(CONFIGURATION_PENDING, h);

    if( NitsCompare(ReadTestFile(TEST_NONINDEPENDENT_SEQUENCEFASTFAIL, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {

            value.uint8a.data = pbuffer;
            value.uint8a.size = size;
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement configurationdata failed")))
                {
                    value.boolean = MI_TRUE;
                    if(NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement force failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession failed.")))
                        {
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, LCM_SETMETHODNAME, NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(NitsAssert(resultCode != MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned success. This is unexpected.")))
                                {
                                    if( errorMessage)
                                        TTRACE(errorMessage);
                                    else
                                    {
                                        MI_Value value;
                                        MI_Uint32 flags;
                                        if(MI_Instance_GetElement(extendedInfo, MI_T("Message"), &value, NULL, &flags, NULL) == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
                                        {
                                            TTRACE(value.string);
                                        }
                                    }                               
                                    for(MI_Uint32 iCount = 0 ; iCount < 4; iCount++)
                                    {
                                        NitsCompare(progressReport.writeMessageValues[iCount], 0, MI_T("WriteMessage not called as expected. Run the test with -trace option."));
                                        NitsCompare(progressReport.writeErrorValues[iCount], 0, MI_T("WriteError not called as expected. Run the test with -trace option.")); 
                                    }                           
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
    DeleteConfig(CONFIGURATION_PENDING, h); 

    //Test4
    progressReport.writeMessageValues[0] = 10;
    progressReport.writeMessageValues[1] = 11;
    progressReport.writeMessageValues[2] = 12;
    progressReport.writeMessageValues[3] = 13;   
    progressReport.writeErrorValues[0] = 10;
    progressReport.writeErrorValues[1] = 0;
    progressReport.writeErrorValues[2] = 12;
    progressReport.writeErrorValues[3] = 0;   

    // Start without a pending configuration file otherwise the test will eventually fail
    // during fault injection tests.
    TTRACE(MI_T("****    TestNonDependent_4.mof    ****"));    
    DeleteConfig(CONFIGURATION_PENDING, h);

    if( NitsCompare(ReadTestFile(TEST_NONINDEPENDENT_SEQUENCELATEFAIL, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {

            value.uint8a.data = pbuffer;
            value.uint8a.size = size;
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement configurationdata failed")))
                {
                    value.boolean = MI_TRUE;
                    if(NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement force failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession failed.")))
                        {
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, LCM_SETMETHODNAME, NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(NitsAssert(resultCode != MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned success. This is unexpected.")))
                                {
                                    if( errorMessage)
                                        TTRACE(errorMessage);
                                    else
                                    {
                                        MI_Value value;
                                        MI_Uint32 flags;
                                        if(MI_Instance_GetElement(extendedInfo, MI_T("Message"), &value, NULL, &flags, NULL) == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
                                        {
                                            TTRACE(value.string);
                                        }
                                    }                                 
                                    for(MI_Uint32 iCount = 0 ; iCount < 4; iCount++)
                                    {
                                        NitsCompare(progressReport.writeMessageValues[iCount], 0, MI_T("WriteMessage not called as expected. Run the test with -trace option."));
                                        NitsCompare(progressReport.writeErrorValues[iCount], 0, MI_T("WriteError not called as expected. Run the test with -trace option.")); 
                                    }                           
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
    DeleteConfig(CONFIGURATION_PENDING, h);   

    //Test5
    progressReport.writeMessageValues[0] = 0;
    progressReport.writeMessageValues[1] = 11;
    progressReport.writeMessageValues[2] = 12;
    progressReport.writeMessageValues[3] = 0;   
    progressReport.writeErrorValues[0] = 0;
    progressReport.writeErrorValues[1] = 11;
    progressReport.writeErrorValues[2] = 12;
    progressReport.writeErrorValues[3] = 0;   
    // Start without a pending configuration file otherwise the test will eventually fail
    // during fault injection tests.
    TTRACE(MI_T("****    TestNonDependent_5.mof    ****"));    
    DeleteConfig(CONFIGURATION_PENDING, h);

    if( NitsCompare(ReadTestFile(TEST_NONINDEPENDENT_MIXEDMODE, &pbuffer, &size), S_OK, MI_T("ReadTestFile Failed.")) )
    {
        
        if( NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("MI_Application_Initialize failed.")))
        {

            value.uint8a.data = pbuffer;
            value.uint8a.size = size;
            if( NitsCompare(MI_Application_NewInstance(&application, MI_T("__Parameter"), NULL, &parameter), MI_RESULT_OK, MI_T("MI_Application_NewParameterSet failed")))
            {
                if( NitsCompare(MI_Instance_AddElement(parameter, MI_T("ConfigurationData"), &value, MI_UINT8A, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement configurationdata failed")))
                {
                    value.boolean = MI_TRUE;
                    if(NitsCompare(MI_Instance_AddElement(parameter, MI_T("force"), &value, MI_BOOLEAN, 0), MI_RESULT_OK, MI_T("MI_Instance_AddElement force failed")))
                    {
                        if( NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, MI_T("MI_Application_NewSession failed.")))
                        {
                            MI_Session_Invoke(&session, 0, 0, LCM_PRO_NAMESPACE, LCM_CLASSNAME, LCM_SETMETHODNAME, NULL, parameter, &callbacks, &operation);
                            if( NitsCompare(MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo), MI_RESULT_OK, MI_T("MI_Operation_GetInstance failed")))
                            {
                                if(NitsAssert(resultCode != MI_RESULT_OK, MI_T("MI_Operation_GetInstance returned success. This is unexpected.")))
                                {
                                    if( errorMessage)
                                        TTRACE(errorMessage);
                                    else
                                    {
                                        MI_Value value;
                                        MI_Uint32 flags;
                                        if(MI_Instance_GetElement(extendedInfo, MI_T("Message"), &value, NULL, &flags, NULL) == MI_RESULT_OK && !(flags & MI_FLAG_NULL))
                                        {
                                            TTRACE(value.string);
                                        }
                                    }                               
                                    for(MI_Uint32 iCount = 0 ; iCount < 4; iCount++)
                                    {
                                        NitsCompare(progressReport.writeMessageValues[iCount], 0, MI_T("WriteMessage not called as expected. Run the test with -trace option."));
                                        NitsCompare(progressReport.writeErrorValues[iCount], 0, MI_T("WriteError not called as expected. Run the test with -trace option.")); 
                                    }                           
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
    DeleteConfig(CONFIGURATION_PENDING, h);      

NitsEndTest

/************************************************************************************************
 ** Following tests only compiles and runs in linux
 ************************************************************************************************/
#ifndef _MSC_VER
NitsDRTLinuxTest1(TestRegisterTask, InitLCM, PtrVal)
    MI_Instance *cimErrorDetails = NULL;
    MI_Instance *metaConfigInstance = NULL;
    NitsTrapHandle h = NitsContext() -> _InitLCM -> _Ptr->ptr;
    MI_Result miResult = MI_RESULT_OK;

        // Copy /etc/crontab to /etc/crontab.bak
        File_CopyT(CRONTAB, CRONTABBAK);


        // test 1: add new task

        // Copy ./testcrontab to /etc/crontab
        File_CopyT(TEST_CRONTAB1, CRONTAB);
        
    // Load current meta configuration
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_GetMetaConfig)((MSFT_DSCMetaConfiguration **)&metaConfigInstance);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call GetMetaConfig failed."));

    // Call RegisterTask
    const MI_Char * propName = MI_T("RefreshFrequencyMins");
    const MI_Char * taskName = MI_T("Consistency");             // conformitive to result_crontab* files
    MI_Uint32 defaultValue = 15;        // default refresh frequency mins
    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_RegisterTask)(metaConfigInstance, propName, taskName, defaultValue, &cimErrorDetails);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call RegisterTask failed."));

        // Validate content of /etc/crontab is identical to result_crontab1
        MI_Uint8 * actualFileContent, * expectedFileContent;
        MI_Uint32 actualFileLength, expectedFileLength;

        miResult = ReadTestFile(CRONTAB, &actualFileContent, &actualFileLength);
        miResult = ReadTestFile(RESULT_CRONTAB, &expectedFileContent, &expectedFileLength);
        NitsCompare(actualFileLength, expectedFileLength, MI_T("actual crontab file's length is not equal to expected one"));
    for (MI_Uint32 i = 0; i < actualFileLength; i++)
        {
        NitsCompare(actualFileContent[i], expectedFileContent[i], MI_T("actual crontab file's content is not equal to expected one"));
    }
        
        // test 2: task already exists

        // Copy ./testcrontab to /etc/crontab
        File_CopyT(TEST_CRONTAB2, CRONTAB);

    // Load current meta configuration
    miResult = NitsGetTrap(h, LCMTraps, _LCMTest_GetMetaConfig)((MSFT_DSCMetaConfiguration **)&metaConfigInstance);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call GetMetaConfig failed."));

    // Call RegisterTask
    miResult = NitsGetTrap(h, LCMTraps, _LCMTEST_RegisterTask)(metaConfigInstance, propName, taskName, defaultValue, &cimErrorDetails);
    NitsCompare(miResult, MI_RESULT_OK, MI_T("Call RegisterTask failed."));

        // Validate content of /etc/crontab is identical to result_crontab2
        miResult = ReadTestFile(CRONTAB, &actualFileContent, &actualFileLength);
        miResult = ReadTestFile(RESULT_CRONTAB, &expectedFileContent, &expectedFileLength);
        NitsCompare(actualFileLength, expectedFileLength, MI_T("actual crontab file's length is not equal to expected one"));
    for (MI_Uint32 i = 0; i < actualFileLength; i++)
        {
        NitsCompare(actualFileContent[i], expectedFileContent[i], MI_T("actual crontab file's content is not equal to expected one"));
    }
        
        // Copy /etc/crontab.bak /etc/crontab
        File_CopyT(CRONTABBAK, CRONTAB);
        File_RemoveT(CRONTABBAK);

NitsEndTest
#endif

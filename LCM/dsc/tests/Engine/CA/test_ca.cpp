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
#include <EngineHelperInternal.h>
#include <pal/format.h>
#include <pal/shlib.h>
#include <ModuleHandler.h>
#include <CAEngine.h>
#include <lcm.traps.h>
#include "../../common/NitsPriority.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _MSC_VER
    #include <direct.h>
    #define _GetCurrentDir _wgetcwd
    #define TEST_DOCUMENT_NAME MI_T("testinstance.mof")
    #define TEST_DEPENDENCY_1 MI_T("DependencyResolver1.mof")
    #define TEST_DEPENDENCY_2 MI_T("DependencyResolver2.mof")
    #define TEST_DEPENDENCY_3 MI_T("DependencyResolver3.mof")
    #define TEST_DEPENDENCY_4 MI_T("DependencyResolver4.mof")
    #define TEST_DEPENDENCY_5 MI_T("DependencyResolver5.mof")
    #define TEST_DEPENDENCY_6 MI_T("DependencyResolver6.mof")
    #define TEST_DEPENDENCY_7 MI_T("DependencyResolver7.mof")
    #define TEST_DEPENDENCY_8 MI_T("DependencyResolver8.mof")
    #define TEST_DEPENDENCY_9 MI_T("DependencyResolver9.mof")
    #define TEST_DEPENDENCY_10 MI_T("DependencyResolver10.mof")
    #define TEST_DEPENDENCY_11 MI_T("DependencyResolver11.mof")
    #define TEST_DEPENDENCY_12 MI_T("DependencyResolver12.mof")
    #define FMT MI_T("%S\\%S")
#else
    #include <unistd.h>
    #define _GetCurrentDir getcwd
    #define TEST_DOCUMENT_NAME CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/testinstance.mof")
    #define TEST_DEPENDENCY_1 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver1.mof")
    #define TEST_DEPENDENCY_2 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver2.mof")
    #define TEST_DEPENDENCY_3 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver3.mof")
    #define TEST_DEPENDENCY_4 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver4.mof")
    #define TEST_DEPENDENCY_5 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver5.mof")
    #define TEST_DEPENDENCY_6 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver6.mof")
    #define TEST_DEPENDENCY_7 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver7.mof")
    #define TEST_DEPENDENCY_8 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver8.mof")
    #define TEST_DEPENDENCY_9 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver9.mof")
    #define TEST_DEPENDENCY_10 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver10.mof")
    #define TEST_DEPENDENCY_11 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver11.mof")
    #define TEST_DEPENDENCY_12 CONFIG_SRCDIR MI_T("/dsc/tests/Engine/CA") MI_T("/DependencyResolver12.mof")
    #define FMT MI_T("%s/%s")
    #define DSCCORE_LIB CONFIG_LIBDIR MI_T("/libdsccore.so")
#endif

using namespace std;

struct Ptr
{
    void *ptr;
};

Ptr PtrVal = {NULL};
NitsSetup0(InitCA, Ptr)
    MI_Instance *cimErrorDetails = NULL;
#ifdef _MSC_VER
    NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", CATraps);
#else
    NitsTrapHandle h = NitsOpenTrap(DSCCORE_LIB, CATraps);
#endif
    if (NitsAssert(h != NULL, MI_T("Failed to load CATraps!")))
    {
        NitsContext()->_Ptr->ptr = h;
        MI_Result miResult = NitsGetTrap(h, CATraps, _CATest_InitCAHandler)(&cimErrorDetails);
        NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to initialize CA!"));
    }
NitsEndSetup

NitsCleanup(InitCA)
    MI_Instance *cimErrorDetails = NULL;
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;
    MI_Result miResult = NitsGetTrap(h, CATraps, _CATest_UnInitCAHandler)(&cimErrorDetails);
    NitsAssert(miResult == MI_RESULT_OK, MI_T("Failed to initialize LCM!"));   
    if (h != NULL)
        NitsCloseTrap(h);
NitsEndCleanup


//==============================================================================
//
// SendConfigurationApply()
//
//==============================================================================
NitsDRTCommonTest1(TestSendConfigurationApply, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    ModuleManager *moduleManager = NULL;
    MI_InstanceA resourceInstances = {0};
    MI_Instance *documentIns = NULL;
    LCMProviderContext lcmContext = {0};
    MI_Uint32 resultStatus = 0;
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);

    lcmContext.executionMode = 0;
    lcmContext.context = NULL;

    if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
       NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
       NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null") ))
    {
            //Load it here
#if defined(_MSC_VER)
        MI_Char binaryPath[MAX_PATH];
        MI_Char finalPath[MAX_PATH];
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DOCUMENT_NAME);
        }
        MI_Result r = NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath,  &extendedError, &resourceInstances, &documentIns);
#else
        MI_Result r = NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DOCUMENT_NAME, &extendedError, &resourceInstances, &documentIns);
#endif
        NitsCompare(r, MI_RESULT_OK, MI_T("LoadInstanceDocumentFromLocation Failed"));
        //Send configuration
        if(r == MI_RESULT_OK && NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
        {
            NitsCompare(NitsGetTrap(h, CATraps, _CATest_SendConfigurationApply)(&lcmContext, 0, &resourceInstances, moduleManager, documentIns, &resultStatus, &extendedError), MI_RESULT_OK, MI_T("SendConfigurationApply failed."));
        }
        moduleManager->ft->Close(moduleManager,&extendedError);
    }
    if( extendedError != NULL)
    {
        MI_Instance_Delete(extendedError);
    }
NitsEndTest


//==============================================================================
//
//GetConfiguration()
//
//==============================================================================
NitsDRTCommonTest1(TestGetConfiguration, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    ModuleManager *moduleManager = NULL;
    MI_InstanceA resourceInstances = {0};
    MI_Instance *documentIns = NULL;
    MI_InstanceA outInstances = {0};
    LCMProviderContext lcmContext = {0};
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);


    lcmContext.executionMode = 0;
    lcmContext.context = NULL;   

    if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
           NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
           NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
    {
#if defined(_MSC_VER)
        MI_Char binaryPath[MAX_PATH];
        MI_Char finalPath[MAX_PATH];            
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath,TEST_DOCUMENT_NAME);
        }
        //Load it here 
        NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("LoadInstanceDocumentFromLocation Failed"));
#else
        NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DOCUMENT_NAME, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("LoadInstanceDocumentFromLocation Failed"));
#endif
        //Send configuration
        if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
        {
            NitsCompare(NitsGetTrap(h, CATraps, _CATest_GetConfiguration)(&lcmContext, 0, &resourceInstances, moduleManager, documentIns, &outInstances, &extendedError), MI_RESULT_OK, MI_T("GetConfiguration failed."));
            if(NitsAssert(outInstances.size == 1, MI_T("Expected 1 instances.")))
            {
                moduleManager->ft->Close(moduleManager,&extendedError);
            }
        }
    }
    if( extendedError != NULL)
    {
        MI_Instance_Delete(extendedError);
    }
NitsEndTest


//==============================================================================
//
//ResolveDependencies()
//
//==============================================================================
NitsDRTCommonTest1(TestResolveDependencies, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    MI_Uint32 xCount = 0;
    ModuleManager *moduleManager = NULL;
    MI_InstanceA resourceInstances = {0};
    MI_Instance *documentIns = NULL;
    ExecutionOrderContainer container = {0};
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);
#if defined(_MSC_VER)
        MI_Char binaryPath[MAX_PATH];
        MI_Char finalPath[MAX_PATH];
#endif

    //Test1: Check document with no dependencies
    if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
       NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
       NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
    {

#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_1);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_1, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver1.mof")))
                {
                    if( NitsCompare(container.executionListSize, 8, MI_T("DependencyResolver1.mof: Expected container.executionListSize to be 8")) )
                    {
                        // List should be: 0,1,2,3,4,5,6,7
                        for( xCount = 0 ; xCount < container.executionListSize; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, xCount, MI_T("resourceIndex not as expected."));
                        }
                    }
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);
            }
        }

        //Test2: Check document with single linear dependencies.
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_2);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_2, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver2.mof")))
                {
                    // List should be: 7,6,5,4,3,2,1,0
                    if( NitsCompare(container.executionListSize, 8, MI_T("DependencyResolver2.mof: Expected container.executionListSize to be 8")) )
                    {
                        for( xCount = 0 ; xCount < container.executionListSize; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, container.executionListSize - xCount - 1, MI_T("resourceIndex not as expected."));
                        }
                    }                    
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);   
            }
        }

        //Test3: Check document with single linear dependencies, 1st node has no dependency.
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_3);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_3, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
                {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver3.mof")))
                {
                    // List should be 0, 7,6,5,4,3,2,1,0
                    if( NitsCompare(container.executionListSize, 8, MI_T("DependencyResolver3.mof: Expected container.executionListSize to be 8")) )
                    {
                        NitsCompare( container.ExecutionList[0].resourceIndex, 0, MI_T("resourceIndex not as expected."));
                        for( xCount = 1 ; xCount < container.executionListSize; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, container.executionListSize - xCount , MI_T("resourceIndex not as expected."));
                        }
                    }                      
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);  
            }
        }
        //Test4: Check document with two trees.
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_4);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_4, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver4.mof")))
                {
                               
                    // List should be 3,2,1,0,   7,6,5,4
                    if( NitsCompare(container.executionListSize, 8, MI_T("DependencyResolver4.mof: Expected container.executionListSize to be 8")) )
                    {
                        for( xCount = 0 ; xCount < 4; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, 4 - xCount - 1, MI_T("resourceIndex not as expected."));
                        }
                        for( xCount = 4 ; xCount < container.executionListSize; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, container.executionListSize - xCount + 3, MI_T("resourceIndex not as expected."));
                        }                        

                    }                     
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);         
            }
        }

        //Test5: Check document with two trees and two independent nodes defined at the beginning.
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_5);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_5, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver5.mof")))
                {
                               
                    // List should be 0,1,4,3,2,7,6,5
                    if( NitsCompare(container.executionListSize, 8, MI_T("DependencyResolver5.mof: Expected container.executionListSize to be 8")) )
                    {
                        for( xCount = 0 ; xCount < 2; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, xCount, MI_T("resourceIndex not as expected."));
                        }
                        for( xCount = 2 ; xCount < 5; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, container.executionListSize - xCount - 2, MI_T("resourceIndex not as expected."));
                        }  
                        for( xCount = 5 ; xCount < container.executionListSize; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, container.executionListSize - xCount +4, MI_T("resourceIndex not as expected."));
                        }                          

                    }                       
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);     
            }
        }

        //Test6: Check document with single linear dependencies.
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_6);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_6, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver6.mof")))
                {
                    // List should be 1,0
                    if( NitsCompare(container.executionListSize, 2, MI_T("DependencyResolver6.mof: Expected container.executionListSize to be 2")) )
                    {
                            NitsCompare( container.ExecutionList[0].resourceIndex, 1, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[1].resourceIndex, 0, MI_T("resourceIndex not as expected."));
                    }      
                }        
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);
            }
        }

        //Test7: linear dependency.
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_7);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_7, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver7.mof")))
                {
                    // List should be 0,1
                    if( NitsCompare(container.executionListSize, 2, MI_T("DependencyResolver7.mof: Expected container.executionListSize to be 2")) )
                    {
                            NitsCompare( container.ExecutionList[0].resourceIndex, 0, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[1].resourceIndex, 1, MI_T("resourceIndex not as expected."));
                    }      
                }                      
                    
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);         
            }
        }

        //Test8: Check cyclic dependency for single node..
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_8);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_8, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_FAILED, MI_T("ResolveDependency either succeeded or failed with wrong error code for DependencyResolver8.mof. Expected failure code is MI_RESULT_FAILED.")))
                {     
                    MI_Instance_Delete(extendedError);
                    extendedError = NULL;                    
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);         
            }
        }

        //Test9: Check cyclic dependency between two nodes..
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_9);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_9, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_FAILED, MI_T("ResolveDependency either succeeded or failed with wrong error code for DependencyResolver9.mof. Expected failure code is MI_RESULT_FAILED.")))
                {  
                    MI_Instance_Delete(extendedError);
                    extendedError = NULL;
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);         
            }
        }

        //Test10: Check document with 1 tree and two independent objects in list.
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_10);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_10, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver10.mof")))
                {
                    if( NitsCompare(container.executionListSize, 5, MI_T("DependencyResolver10.mof: Expected container.executionListSize to be 5")))
                    {
                        // List should be: 0,1,2,3,4
                        for( xCount = 0 ; xCount < container.executionListSize; xCount++)
                        {
                            NitsCompare( container.ExecutionList[xCount].resourceIndex, xCount, MI_T("resourceIndex not as expected."));
                        }
                    }                    
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);         
            }
        }

        //Test11: Check document with 1 complexe tree. 
        //                 ->E ->
        //          ->C
        //                  ->F ->
        //   a->b                           H
        //          -> D->G ->
        // Execution order is: H , E, F ,C , G, D ,B , A
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_11);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_11, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver11.mof")))
                {
                    if( NitsCompare(container.executionListSize, 8, MI_T("DependencyResolver11.mof: Expected container.executionListSize to be 8")) )
                    {
                        // List should be: 7,4,5,2,6,3,1,0
                            NitsCompare( container.ExecutionList[0].resourceIndex, 7, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[1].resourceIndex, 4, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[2].resourceIndex, 5, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[3].resourceIndex, 2, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[4].resourceIndex, 6, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[5].resourceIndex, 3, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[6].resourceIndex, 1, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[7].resourceIndex, 0, MI_T("resourceIndex not as expected."));                          
                    }                        
                        
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);         
            }
        }

        //Test12: Check document with 1 complexe tree. 
        //                
        //     A ->    ->D  
        //            C       
        //     B->     ->E            
        //          
        // Execution order is: H , E, F ,C , G, D ,B , A
#if defined(_MSC_VER)
        if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DEPENDENCY_12);
        }
        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#else

        if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, TEST_DEPENDENCY_12, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("ResolveDependency Test 1: LoadInstanceDocumentFromLocation Failed")))
#endif
        {
            //Send configuration
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                if(NitsCompare(NitsGetTrap(h, CATraps, _CATest_ResolveDependency)(&resourceInstances, &container, &extendedError), MI_RESULT_OK, MI_T("ResolveDependency Failed for DependencyResolver12.mof")))
                {
                    if( NitsCompare(container.executionListSize, 5, MI_T("DependencyResolver12.mof: Expected container.executionListSize to be 5")) )
                    {
                        // List should be: 3,4,2,0,1
                            NitsCompare( container.ExecutionList[0].resourceIndex, 3, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[1].resourceIndex, 4, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[2].resourceIndex, 2, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[3].resourceIndex, 0, MI_T("resourceIndex not as expected."));
                            NitsCompare( container.ExecutionList[4].resourceIndex, 1, MI_T("resourceIndex not as expected."));
                    }                        
                        
                }
                NitsGetTrap(h, CATraps, _CATest_FreeExecutionOrderContainer)(&container);         
            }
        }          
        moduleManager->ft->Close(moduleManager,&extendedError);
    }
    if( extendedError != NULL)
    {
        MI_Instance_Delete(extendedError);
    }
NitsEndTest


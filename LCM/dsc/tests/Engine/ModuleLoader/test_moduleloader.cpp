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
#include <pal/format.h>
#include <pal/strings.h>
#include <EngineHelperInternal.h>

#include <ModuleHandler.h>
#include <CAEngine.h>

#include <lcm.traps.h>

#include <stdio.h>  /* defines FILENAME_MAX */

using namespace std;

#ifdef _MSC_VER
    #include <direct.h>
    #define _GetCurrentDir _wgetcwd
    #define TEST_DOCUMENT_LOCATION MI_T("testModuleLoader.mof")
    #define FMT MI_T("%S\\%S")
#else
    #include <unistd.h>
    #define _GetCurrentDir getcwd
    #define TEST_DOCUMENT_LOCATION MI_T("dsc/tests/Engine/ModuleLoader/testModuleLoader2.mof")
    #define FMT MI_T("%s/%s")
    #define DSCCORE_LIB CONFIG_LIBDIR MI_T("/libdsccore.so")
#endif

struct Ptr
{
    void *ptr;
};
Ptr PtrVal = {NULL};

NitsSetup0(InitCA, Ptr)
#ifdef _MSC_VER
    NitsTrapHandle h = NitsOpenTrap("DSCCore.dll", CATraps);
#else
    NitsTrapHandle h = NitsOpenTrap(DSCCORE_LIB, CATraps);
#endif
    NitsAssert(h != NULL, MI_T("Failed to load CATraps!"));
    NitsContext()->_Ptr->ptr = h;

NitsEndSetup

NitsCleanup(InitCA)
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;

    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

//==============================================================================
//
// InitializeModuleManager()
//
//==============================================================================
NitsDRTCommonTest1(TestInitializeModuleManager, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    MI_Uint32 xCount = 0;
    ModuleManager *moduleManager = NULL;
    MI_InstanceA resourceInstances = {0};
    ModuleLoaderObject *moduleLoader = NULL;
    MI_Boolean bTest1Found = MI_FALSE;
    MI_Boolean bTest2Found = MI_FALSE;
    MI_Boolean bTest3UserFound = MI_FALSE;
    MI_Instance *documentIns = NULL;
    MI_Char binaryPath[MAX_PATH];
    MI_Char finalPath[MAX_PATH];
    MI_Value className ;    
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
    {
        MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);
        if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
           NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
           NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
        {
            Stprintf(finalPath, MAX_PATH, FMT, binaryPath, TEST_DOCUMENT_LOCATION);
            NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("LoadInstanceDocumentFromLocation Failed"));
            // Validate modules
            moduleLoader = (ModuleLoaderObject*)moduleManager->reserved2;
            if( NitsAssert(moduleLoader, MI_T("ModuleLoader can't be NULL")))
            {
                // Validate class TEST_Test1
                for( xCount = 0 ; xCount < moduleLoader->schemaCount && (bTest1Found == MI_FALSE || bTest2Found == MI_FALSE || bTest3UserFound == MI_FALSE) ; xCount++)
                {
                    if( Tcscasecmp(MI_T("TEST_Test1"), (moduleLoader->providerSchema[xCount])->classDecl->name) == 0 )
                    {
                        //find its mapping and get registration object.
                        if (NitsAssert((int) moduleLoader->schemaToRegistrationMapping[xCount] !=  -1, MI_T("Registration mapping for TEST_Test1 class not found")))
                        {
                            if( NitsAssert(moduleLoader->regisrationCount >= moduleLoader->schemaToRegistrationMapping[xCount], MI_T("Wrong Registration mapping for TEST_Test1 class.")))
                            {
                                //check class name
                                if(NitsCompare( MI_Instance_GetElement(moduleLoader->registrationSchema[ moduleLoader->schemaToRegistrationMapping[xCount] ], MI_T("className"), &className, NULL, NULL, NULL),
                                                 MI_RESULT_OK, MI_T("Class Name not found. Expected TEST_Test1")))
                                {
                                    NitsAssert(Tcscasecmp((moduleLoader->providerSchema[xCount])->classDecl->name, className.string) == 0, MI_T("Class Name expected TEST_Test1"));
                                }
                            }
                        }
                        bTest1Found = MI_TRUE;
                        continue;
                    }
                    else if( Tcscasecmp(MI_T("TEST_Test2"), (moduleLoader->providerSchema[xCount])->classDecl->name) == 0 )
                    {
                        //find its mapping and get registration object.
                        if (NitsAssert((int) moduleLoader->schemaToRegistrationMapping[xCount] !=  -1, MI_T("Registration mapping for TEST_Test2 class not found")))
                        {
                            if( NitsAssert(moduleLoader->regisrationCount >= moduleLoader->schemaToRegistrationMapping[xCount], MI_T("Wrong Registration mapping for TEST_Test2 class.")))
                            {
                                //check class name
                                if(NitsCompare( MI_Instance_GetElement(moduleLoader->registrationSchema[ moduleLoader->schemaToRegistrationMapping[xCount] ], MI_T("className"), &className, NULL, NULL, NULL),
                                                 MI_RESULT_OK, MI_T("Class Name not found. Expected TEST_Test2")))
                                {
                                    NitsAssert(Tcscasecmp((moduleLoader->providerSchema[xCount])->classDecl->name, className.string) == 0, MI_T("Class Name expected TEST_Test2"));
                                }
                            }
                        }
                        bTest2Found = MI_TRUE;
                        continue;

                    }
                    else if( Tcscasecmp(MI_T("TEST_Test3User"), (moduleLoader->providerSchema[xCount])->classDecl->name) == 0 )
                    {
                        //find its mapping and get registration object.
                        if (NitsAssert((int) moduleLoader->schemaToRegistrationMapping[xCount] !=  -1, MI_T("Registration mapping for TEST_Test3User class not found")))
                        {
                            if( NitsAssert(moduleLoader->regisrationCount >= moduleLoader->schemaToRegistrationMapping[xCount], MI_T("Wrong Registration mapping for TEST_Test3User class.")))
                            {
                                //check class name
                                if(NitsCompare( MI_Instance_GetElement(moduleLoader->registrationSchema[ moduleLoader->schemaToRegistrationMapping[xCount] ], MI_T("className"), &className, NULL, NULL, NULL),
                                                 MI_RESULT_OK, MI_T("Class Name not found. Expected TEST_Test3User")))
                                {
                                    NitsAssert(Tcscasecmp((moduleLoader->providerSchema[xCount])->classDecl->name, className.string) == 0, MI_T("Class Name expected TEST_Test3User"));
                                }
                            }
                        }
                        bTest3UserFound = MI_TRUE;
                        continue;

                    }
                }
                NitsAssert( bTest1Found == MI_TRUE, MI_T("Class TEST_Test1 not found in schema files")) ;
                NitsAssert( bTest2Found == MI_TRUE, MI_T("Class TEST_Test2 not found in schema files")) ;
                        NitsAssert( bTest3UserFound == MI_TRUE, MI_T("Class TEST_Test3User not found in schema files")) ;
            }
            NitsCompare(NitsGetTrap(h, CATraps, _CATest_Close)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("ModuleManager Close Failed"));
            
        }
        if( extendedError != NULL)
        {
            MI_Instance_Delete(extendedError);
        } 
    }

NitsEndTest


//==============================================================================
//
// CloseModuleManager()
//
//==============================================================================

NitsDRTCommonTest1(TestCloseModuleManager, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    ModuleManager *moduleManager = NULL;
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);
    if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
       NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
       NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
    {
        //Close it here 
        NitsCompare(NitsGetTrap(h, CATraps, _CATest_Close)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("ModuleManager Close Failed"));
    }
    if( extendedError != NULL)
    {
        MI_Instance_Delete(extendedError);
    } 

NitsEndTest



//==============================================================================
//
// LoadInstanceDocumentFromLocation()
//
//==============================================================================

NitsDRTCommonTest1(TestLoadInstanceDocumentFromLocation, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    ModuleManager *moduleManager = NULL;
    MI_InstanceA resourceInstances = {0};
    MI_Instance *documentIns = NULL;
    MI_Char binaryPath[MAX_PATH];
    MI_Char finalPath[MAX_PATH];
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);

    if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
    {
        Stprintf(finalPath, MAX_PATH, FMT, binaryPath,TEST_DOCUMENT_LOCATION);

        if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
           NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
           NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
        {
            //Load it here 
            if(NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("LoadInstanceDocumentFromLocation Failed")))
            {
                if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
                {
                    // We should get two instances and 1 instance of document
                    NitsAssert(documentIns != NULL, MI_T("No document instnace found"));
                    NitsAssert(resourceInstances.size == 2, MI_T("2 resources expected"));
                }
            }
            NitsCompare(NitsGetTrap(h, CATraps, _CATest_Close)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("ModuleManager Close Failed"));                    
        }
        if( extendedError != NULL)
        {
            MI_Instance_Delete(extendedError);
        } 
    }

NitsEndTest

//==============================================================================
//
// GetRegistrationInstance()
//
//==============================================================================

NitsDRTCommonTest1(TestGetRegistrationInstance, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    ModuleManager *moduleManager = NULL;
    const MI_Instance *registrationInstance = NULL;
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);
    if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
       NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
       NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
    {
        NitsCompare(NitsGetTrap(h, CATraps, _CATest_GetRegistrationInstance)(moduleManager, MI_T("TEST_Test2"), &registrationInstance, &extendedError), MI_RESULT_OK, MI_T("GetRegistrationInstance failed."));
        // We should get two instances and 1 instance of document
        NitsAssert(registrationInstance != NULL, MI_T("No registration instnace found"));
        NitsCompare(NitsGetTrap(h, CATraps, _CATest_Close)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("ModuleManager Close Failed"));                    
    }
    if( extendedError != NULL)
    {
        MI_Instance_Delete(extendedError);
    } 

NitsEndTest


//==============================================================================
//
// GetProviderCompatibleInstance()
//
//==============================================================================

NitsDRTCommonTest1(TestGetProviderCompatibleInstance, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    ModuleManager *moduleManager = NULL;
    MI_InstanceA resourceInstances = {0};
    MI_Instance *outInstance = NULL;
    MI_Instance *documentIns = NULL;
    MI_Char binaryPath[MAX_PATH];
    MI_Char finalPath[MAX_PATH];
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);
    if(NitsAssert(_GetCurrentDir(binaryPath, MAX_PATH) != NULL, MI_T("_GetCurrentDir Failed")))
    {
        Stprintf(finalPath, MAX_PATH, FMT, binaryPath,TEST_DOCUMENT_LOCATION);

        if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
           NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
           NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
        {
            //Load it here 
            NitsCompare(NitsGetTrap(h, CATraps, _CATEST_LoadInstanceDocumentFromLocation)(moduleManager, 0, finalPath, &extendedError, &resourceInstances, &documentIns), MI_RESULT_OK, MI_T("LoadInstanceDocumentFromLocation Failed"));
            if( NitsAssert((ModuleLoaderObject*)moduleManager->reserved2, MI_T("ModuleLoader can't be NULL")))
            {
                // We should get two instances 
                if(NitsAssert(resourceInstances.size == 2, MI_T("2 resources expected")))
                {
                    NitsCompare(NitsGetTrap(h, CATraps, _CATest_GetProviderCompatibleInstance)(moduleManager, resourceInstances.data[0], &outInstance , &extendedError), MI_RESULT_OK, MI_T("GetProviderCompatibleInstance Failed"));
                    NitsAssert(outInstance!= NULL, MI_T("GetProviderCompatibleInstance outInstance is NULL"));
                    //Check for resourceId property, should not exist.
                    NitsCompare(MI_Instance_GetElement(outInstance, MI_T("ResourceId"), NULL, NULL, NULL, NULL), MI_RESULT_NO_SUCH_PROPERTY, MI_T("GetProviderCompatibleInstance Error for ResourceID expected is MI_RESULT_NO_SUCH_PROPERTY"));        
                }
            }
            NitsCompare(NitsGetTrap(h, CATraps, _CATest_Close)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("ModuleManager Close Failed"));                    
        }
        if( extendedError != NULL)
        {
            MI_Instance_Delete(extendedError);
        } 
    }

NitsEndTest

//==============================================================================
//
// Update()
//
//==============================================================================

NitsDRTCommonTest1(TestUpdate, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    MI_Uint32 xCount = 0;
    ModuleManager *moduleManager = NULL;
    ModuleLoaderObject *moduleLoader = NULL;
    MI_Boolean bTest1Found = MI_FALSE;
    MI_Boolean bTest2Found = MI_FALSE;
    MI_Value className ;    
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;
    
    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);
    if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
       NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
       NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
    {
        //Update it
        if(NitsCompare( NitsGetTrap(h, CATraps, _CATest_Update)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("Update API Failed")))
        {
            // Validate modules
            moduleLoader = (ModuleLoaderObject*)moduleManager->reserved2;
            if( NitsAssert(moduleLoader, MI_T("ModuleLoader can't be NULL")))
            {
                // Validate class TEST_Test1
                for( xCount = 0 ; xCount < moduleLoader->schemaCount && (bTest1Found == MI_FALSE || bTest2Found == MI_FALSE) ; xCount++)
                {
                    if( Tcscasecmp(MI_T("TEST_Test1"), (moduleLoader->providerSchema[xCount])->classDecl->name) == 0 )
                    {
                        //find its mapping and get registration object.
                        if (NitsAssert((int) moduleLoader->schemaToRegistrationMapping[xCount] !=  -1, MI_T("Registration mapping for TEST_Test1 class not found")))
                        {
                            if( NitsAssert(moduleLoader->regisrationCount >= moduleLoader->schemaToRegistrationMapping[xCount], MI_T("Wrong Registration mapping for TEST_Test1 class.")))
                            {
                                //check class name
                                if(NitsCompare( MI_Instance_GetElement(moduleLoader->registrationSchema[ moduleLoader->schemaToRegistrationMapping[xCount] ], MI_T("className"), &className, NULL, NULL, NULL),
                                                 MI_RESULT_OK, MI_T("Class Name not found. Expected TEST_Test1")))
                                {
                                    NitsAssert(Tcscasecmp((moduleLoader->providerSchema[xCount])->classDecl->name, className.string) == 0, MI_T("Class Name expected TEST_Test1"));
                                }
                            }
                        }
                        bTest1Found = MI_TRUE;
                        continue;
                    }
                    else if( Tcscasecmp(MI_T("TEST_Test2"), (moduleLoader->providerSchema[xCount])->classDecl->name) == 0 )
                    {
                        //find its mapping and get registration object.
                        if (NitsAssert((int) moduleLoader->schemaToRegistrationMapping[xCount] !=  -1, MI_T("Registration mapping for TEST_Test2 class not found")))
                        {
                            if( NitsAssert(moduleLoader->regisrationCount >= moduleLoader->schemaToRegistrationMapping[xCount], MI_T("Wrong Registration mapping for TEST_Test2 class.")))
                            {
                                //check class name
                                if(NitsCompare( MI_Instance_GetElement(moduleLoader->registrationSchema[ moduleLoader->schemaToRegistrationMapping[xCount] ], MI_T("className"), &className, NULL, NULL, NULL),
                                                 MI_RESULT_OK, MI_T("Class Name not found. Expected TEST_Test2")))
                                {
                                    NitsAssert(Tcscasecmp((moduleLoader->providerSchema[xCount])->classDecl->name, className.string) == 0, MI_T("Class Name expected TEST_Test2"));
                                }
                            }
                        }
                        bTest2Found = MI_TRUE;
                        continue;

                    }
                }
                NitsAssert( bTest1Found == MI_TRUE, MI_T("Class TEST_Test1 not found in schema files")) ;
                NitsAssert( bTest2Found == MI_TRUE, MI_T("Class TEST_Test2 not found in schema files")) ;
            }
        }
        NitsCompare(NitsGetTrap(h, CATraps, _CATest_Close)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("ModuleManager Close Failed"));                            
    }
    if( extendedError != NULL)
    {
        MI_Instance_Delete(extendedError);
    } 

NitsEndTest

NitsDRTCommonTest1(TestBaseConfigSchema, InitCA, PtrVal)

    MI_Instance *extendedError = NULL;
    ModuleManager *moduleManager = NULL;
    ModuleLoaderObject *moduleLoader = NULL;
    MI_ClassA coreSchemas = {0};
    NitsTrapHandle h = NitsContext()->_InitCA->_Ptr->ptr;

    MI_Result r = NitsGetTrap(h, CATraps, _CATest_InitializeModuleManager)(0, &extendedError, &moduleManager);
    if(NitsCompare(r, MI_RESULT_OK, MI_T("InitializeModuleManager failed")) && 
       NitsAssert(moduleManager != NULL, MI_T("ModuleManager is NULL")) &&
       NitsAssert(moduleManager->ft != NULL, MI_T("ModuleManager function table is null")) )
    {
        //this is bootstrap for update api.
         NitsCompare( NitsGetTrap(h, CATraps, _CATest_Update)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("Update API Failed"));
         moduleLoader = (ModuleLoaderObject*)moduleManager->reserved2;
         if( NitsAssert(moduleLoader, MI_T("ModuleLoader can't be NULL")))
         {
             r = NitsGetTrap(h, CATraps, _CATest_GetCoreSchema)(moduleLoader->application,  moduleLoader->deserializer, moduleLoader->options, &coreSchemas, &extendedError);
            
             NitsAssert( r == MI_RESULT_OK, MI_T(" load core schemas failed"));
             r = NitsGetTrap(h, CATraps, _CATest_ValidateInfrastructureSchema)(&coreSchemas, &extendedError);
             NitsAssert( r == MI_RESULT_OK, MI_T(" Validate core schemas failed"));
         }
        NitsCompare(NitsGetTrap(h, CATraps, _CATest_Close)(moduleManager, &extendedError), MI_RESULT_OK, MI_T("ModuleManager Close Failed"));                     

    }

    if( extendedError != NULL)
    {
        MI_Instance_Delete(extendedError);
    } 

NitsEndTest


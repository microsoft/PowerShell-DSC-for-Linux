#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <pal/strings.h>
#include "DSC_Systemcalls.h"
#include "PAL_Extension.h"
#include "CAEngine.h"
#include "EventWrapper.h"
#include "NativeResourceProviderMiModule.h"
#include <errno.h>


/**************************************************************************************************/
/*                                                                                                */
/* Implementation of MI_Server for native resource providers.                                     */
/*                                                                                                */
/**************************************************************************************************/

typedef struct MI_EXPORT {
    MI_Server _base;
    struct {
        MI_ServerFT      serverFT;
        MI_ContextFT     contextFT;
        MI_InstanceFT    instanceFT;
        MI_PropertySetFT propertySetFT;
        MI_FilterFT      filterFT;
    } _private;
} NativeResourceHostMiServer;

static MI_Result MI_CALL NativeResourceHostMiServer_GetVersion(_Out_ MI_Uint32* version)
{
    if (version == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    *version = MI_VERSION;

    return MI_RESULT_OK;
}

static MI_Result MI_CALL NativeResourceHostMiServer_GetSystemName(const MI_Char** systemName)
{
    static MI_Char computerName[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };

    if (systemName == NULL)
        return MI_RESULT_INVALID_PARAMETER;
    *systemName = NULL;

    MI_Result returnValue = MI_RESULT_OK;

    if (*computerName == 0)
    {
        #if defined(_MSC_VER)
        DWORD length = _countof(computerName);
        BOOL success = GetComputerNameExW(ComputerNameNetBIOS, computerName, &length);

		if(!success)
        {
            MI_Uint32 errorCode = GetLastError();
            DSC_EventGettingTheHostNameFailed(errorCode);
            EH_Check_(success, returnValue = MI_RESULT_FAILED);
        }
        #else
        int result = GetComputerHostName(computerName, MAX_COMPUTERNAME_LENGTH);
		if (result != 0)
		{
			MI_Uint32 errorCode = errno;
			DSC_EventGettingTheHostNameFailed(errorCode);
			EH_Check_(result == 0, returnValue = MI_RESULT_FAILED);
		}
        #endif

    }
    *systemName = computerName;

EH_UNWIND;
    return returnValue;
}

static MI_Result NativeResourceHostMiServer_New(_Outptr_ MI_Server** server)
{
    if (server == NULL)
        return MI_RESULT_INVALID_PARAMETER;
    *server = NULL;

    MI_Result returnValue = MI_RESULT_OK;

    NativeResourceHostMiServer* nativeResourceHostMiServer = DSC_malloc(sizeof(NativeResourceHostMiServer), NitsHere());
    EH_Check_(nativeResourceHostMiServer != NULL, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);
    memset(nativeResourceHostMiServer, 0, sizeof(NativeResourceHostMiServer));

    nativeResourceHostMiServer->_private.serverFT.GetVersion = NativeResourceHostMiServer_GetVersion;
    nativeResourceHostMiServer->_private.serverFT.GetSystemName = NativeResourceHostMiServer_GetSystemName;
    nativeResourceHostMiServer->_base.serverFT = &nativeResourceHostMiServer->_private.serverFT;
    nativeResourceHostMiServer->_base.contextFT = &nativeResourceHostMiServer->_private.contextFT;
    nativeResourceHostMiServer->_base.instanceFT = &nativeResourceHostMiServer->_private.instanceFT;
    nativeResourceHostMiServer->_base.propertySetFT = &nativeResourceHostMiServer->_private.propertySetFT;
    nativeResourceHostMiServer->_base.filterFT = &nativeResourceHostMiServer->_private.filterFT;

    *server = (MI_Server*) nativeResourceHostMiServer;

EH_UNWIND;
    return returnValue;
}

static MI_Result NativeResourceHostMiServer_Delete(_Outptr_ MI_Server* server)
{
    if (server != NULL)
        DSC_free(server);

    return MI_RESULT_OK;
}

/**************************************************************************************************/
/*                                                                                                */
/* Implementation of NativeResourceProviderMiModule                                               */
/*                                                                                                */
/**************************************************************************************************/

MI_Result NativeResourceProviderMiModule_New(const _In_z_ MI_Char *nativeResourceProviderPath,
                                            _Outptr_ NativeResourceProviderMiModule** module)
{
    typedef MI_Module* (MI_MAIN_CALL* MI_ModuleMainFunction)(MI_Server*);

    if (module == NULL)
        return MI_RESULT_INVALID_PARAMETER;
    *module = NULL;

    MI_Result returnValue = MI_RESULT_OK;

    NativeResourceProviderMiModule* nativeResourceProviderMiModule = NULL;
    MI_Server* miServer = NULL;
    MI_Boolean versionMatch = MI_FALSE;
    MI_Uint32 miModuleVersion;
    MI_Uint32 errorCode = 0;

    nativeResourceProviderMiModule= DSC_malloc(sizeof(NativeResourceProviderMiModule), NitsHere());
    EH_Check_(nativeResourceProviderMiModule != NULL, returnValue = MI_RESULT_SERVER_LIMITS_EXCEEDED);
    memset(nativeResourceProviderMiModule, 0, sizeof(NativeResourceProviderMiModule));

    //TODO: Add searching nativeResourceProviderPath for dependent dlls for Linux
    nativeResourceProviderMiModule->_private.moduleHandle = dlopen(nativeResourceProviderPath, RTLD_LAZY | RTLD_DEEPBIND);
    EH_Check_(nativeResourceProviderMiModule->_private.moduleHandle != NULL, returnValue = MI_RESULT_NOT_FOUND); // TODO - Get actual error using GetLastError

    MI_ModuleMainFunction resourceProviderMainFunction = (MI_ModuleMainFunction) dlsym(nativeResourceProviderMiModule->_private.moduleHandle, "MI_Main");
    EH_Check_(resourceProviderMainFunction != NULL, returnValue = MI_RESULT_METHOD_NOT_FOUND); // TODO - Get actual error using GetLastError

    returnValue = NativeResourceHostMiServer_New(&miServer);
    EH_CheckResult(returnValue);

    // NOTE: the MiModule returned by the main function in the provider is statically allocated and should not be freed.
    nativeResourceProviderMiModule->miModule = resourceProviderMainFunction(miServer);
#if defined(_MSC_VER)
    errorCode = GetLastError();
#else
    // TODO: get the actual error code on Linux
    errorCode = MI_RESULT_METHOD_NOT_FOUND;
#endif
    EH_Check_(nativeResourceProviderMiModule->miModule != NULL, returnValue = errorCode);

    // Check for major version mismatch. We don't know how to handle future adapters so we bail out.
    miModuleVersion = ((nativeResourceProviderMiModule->miModule)->version >> 16);
    versionMatch = miModuleVersion == MI_MAJOR;
    if (!versionMatch)
    {
        DSC_EventMIModuleVersionMisMatch(MI_MAJOR, miModuleVersion);
    }
    EH_Check_(versionMatch, returnValue = MI_RESULT_NOT_SUPPORTED);
    *module = nativeResourceProviderMiModule;
    DSC_EventWriteLoadingDLLSucceeded(nativeResourceProviderPath);

EH_UNWIND;

    NativeResourceHostMiServer_Delete(miServer);
    if (returnValue != MI_RESULT_OK)
        NativeResourceProviderMiModule_Delete(nativeResourceProviderMiModule);

    return returnValue;
}

MI_Result NativeResourceProviderMiModule_Delete(_In_ NativeResourceProviderMiModule* module)
{
    if (module != NULL) {
        #if defined(_MSC_VER)
        FreeLibrary(module->_private.moduleHandle);
        #else
        if (module->_private.moduleHandle)
        {
            dlclose(module->_private.moduleHandle);
        }
        #endif
        DSC_free(module);
    }

    return MI_RESULT_OK;
}

MI_Result NativeResourceProviderMiModule_HasClassDecl(const _In_ NativeResourceProviderMiModule* module,
                                                                const _In_z_ MI_Char *className)
{
    MI_ClassDecl * classDecl = 0;
    return NativeResourceProviderMiModule_GetClassDecl(module, className , (const MI_ClassDecl**)&classDecl);
}

MI_Result NativeResourceProviderMiModule_GetSchemaDecls(const _In_ NativeResourceProviderMiModule* module,
                                                                    const _In_z_ MI_Char *className,
                                                                    _Outptr_ const MI_SchemaDecl** schema)
{
    if (schema == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    *schema = module->miModule->schemaDecl;
    return MI_RESULT_OK;
}


MI_Result NativeResourceProviderMiModule_GetClassDecl(const _In_ NativeResourceProviderMiModule* module,
                                                                const _In_z_ MI_Char *className,
                                                                _Outptr_ const MI_ClassDecl** classDecl)
{
    if (classDecl == NULL)
        return MI_RESULT_INVALID_PARAMETER;
    *classDecl = NULL;

    const MI_SchemaDecl* schema = module->miModule->schemaDecl;

    MI_Uint32 i;
    for (i = 0; i != schema->numClassDecls; i++)
    {
        const MI_ClassDecl* c = schema->classDecls[i];
        if (!c) // end of array
            break;
    }

    for (i = 0; i != schema->numClassDecls; i++)
    {
        const MI_ClassDecl* c = schema->classDecls[i];

        if (!c) // end of array
            break;

        DSC_LOG_INFO("Comparing class '%s' with '%s'", c->name, className);
        if (Tcscasecmp(c->name, className) == 0)
        {
            *classDecl = c;
            DSC_EventGettingTheSchemaSucceeded(className);
            return MI_RESULT_OK;
        }
    }
    DSC_EventGettingTheClassDeclFailed(className);
    return MI_RESULT_NOT_FOUND;
}

MI_Uint32 ComputeCimNameHash(const MI_Char* name)
{
    const MI_Uint8 ToLowerTable[256] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,     0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,     0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,     0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,     0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
        0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,     0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,     0x78, 0x79, 0x7A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,     0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,     0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,     0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,     0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,     0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
        0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,     0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,     0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
        0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,     0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
        0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,     0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
        0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,     0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
    };

    MI_Uint32 n = (MI_Uint32)Tcslen(name);

    if (n == 0)
        return 0;

    return ToLowerTable[(MI_Uint8)name[0]] << 16 | ToLowerTable[(MI_Uint8)name[n - 1]] << 8 | n;
}

MI_Result NativeResourceProviderMiModule_GetMethodDecl(const _In_ MI_ClassDecl* classDecl,
                                                                  const _In_z_ MI_Char *methodName,
                                                                  _Outptr_  const MI_MethodDecl** methodDecl)
{
    if (methodDecl == NULL)
        return MI_RESULT_INVALID_PARAMETER;
    *methodDecl = NULL;

    MI_Uint32 code = ComputeCimNameHash(methodName);

    MI_Uint32 i;
    for (i = 0; i < classDecl->numMethods; i++)
    {
        if (classDecl->methods[i]->code == code && Tcscasecmp(classDecl->methods[i]->name, methodName) == 0)
        {
            *methodDecl = classDecl->methods[i];
            DSC_EventGettingTheMethodDeclSucceeded(methodName);
            return MI_RESULT_OK;
        }
    }
    DSC_EventGettingTheMethodDeclSucceeded(methodName);
    return MI_RESULT_NOT_FOUND;
}


/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define _IMPL 1

#include <mi.h>
#include <micodec.h>
#include <stdlib.h>
#include < vcclr.h >
#include "CAPSProviderHandlerAdapter.h"
#include "..\CALogInfrastructure\CALog.h"
#include <windows.h>
#include <malloc.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;
using namespace System::Security;
using namespace Microsoft::PowerShell::DesiredStateConfiguration::Internal;

#pragma unmanaged
__inline void *Malloc_Core(size_t length)
{
    return malloc(length);
}

#pragma managed

ref class PlugInStreamsHandler : IStreamsHandler
{
    static const int MaxMessageSize = 8 * 1024;

    static PlugInStreamsHandler()
    {
        CALogSetJobDeviceName();
    }

public:

    // The Context information from CA is passed to CLI layer,
    // this context information would be passed back to CA layer
    // when different stream and whatif messages are written
    // to the CA logging infrstructure.
    void *callbackContext;

    virtual bool WhatIfEnabled()
    {
        return CAWhatIfEnabled(callbackContext)?true:false;
    }

    virtual void WriteWhatIfMessage(String^ message)
    {
        try
        {
            for (int i = 0; i < message->Length; i += MaxMessageSize)
            {
                IntPtr nativeMessage = Marshal::StringToHGlobalUni(message->Substring(i, min(message->Length - i, MaxMessageSize)));
                LogCAWhatIfMessage(callbackContext, static_cast<const MI_Char*>(safe_cast<void*>(nativeMessage)));
                Marshal::FreeHGlobal(nativeMessage);
            }
        }
        catch (OutOfMemoryException^)
        {
        }
    }

    virtual void WriteMIError(
        IntPtr instanceMIError)
    {
        try
        {
            LogCAWriteMIError(
                callbackContext,
                static_cast<MI_Instance*>(safe_cast<void*>(instanceMIError)));
        }
        catch (OutOfMemoryException^) { }
    }

    virtual void WriteDebugMessage(String^ message)
    {
        try
        {
            MI_Char* nativeResourceId = const_cast<MI_Char*>(GetResourceIdFromConext(callbackContext));
            String^ resourceId = Marshal::PtrToStringUni(static_cast<IntPtr>(nativeResourceId));
            for (int i = 0; i < message->Length; i += MaxMessageSize)
            {
                IntPtr nativeMessage = Marshal::StringToHGlobalUni(message->Substring(i, min(message->Length - i, MaxMessageSize)));
                MI_Char* fullMessage=const_cast<MI_Char*>(LogCADebugMessage(callbackContext, static_cast<const MI_Char*>(safe_cast<void*>(nativeMessage))));
                if(fullMessage!=NULL)
                {
                        String^ fullMessageManaged = Marshal::PtrToStringUni(static_cast<IntPtr>(fullMessage));
                        IntPtr fullMessagePointer = Marshal::StringToHGlobalUni(fullMessageManaged);
                        S_DscCoreR::EventWriteDebugMessageFromPsProvider(S_DscCoreR::JobGuidString,resourceId, fullMessageManaged);
                        Marshal::FreeHGlobal(fullMessagePointer);
                }
                Marshal::FreeHGlobal(nativeMessage);
            }
        }
        catch (OutOfMemoryException^)
        {
        }
    }

    virtual void WriteVerboseMessage(String^ message)
    {
        try
        {
            MI_Char* nativeResourceId = const_cast<MI_Char*>(GetResourceIdFromConext(callbackContext));
            String^ resourceId = Marshal::PtrToStringUni(static_cast<IntPtr>(nativeResourceId));

            for (int i = 0; i < message->Length; i += MaxMessageSize)
            {
                IntPtr nativeMessage = Marshal::StringToHGlobalUni(message->Substring(i, min(message->Length - i, MaxMessageSize)));
                MI_Char* fullMessage=const_cast<MI_Char*>(LogCAVerboseMessage(callbackContext, static_cast<const MI_Char*>(safe_cast<void*>(nativeMessage))));
                if(fullMessage!=NULL)
                {
                        String^ fullMessageManaged = Marshal::PtrToStringUni(static_cast<IntPtr>(fullMessage));
                        IntPtr fullMessagePointer = Marshal::StringToHGlobalUni(fullMessageManaged);
                        S_DscCoreR::EventWriteVerboseMessageFromPsProvider(S_DscCoreR::JobGuidString,resourceId, fullMessageManaged);
                        Marshal::FreeHGlobal(fullMessagePointer);

                }

                Marshal::FreeHGlobal(nativeMessage);

            }
        }
        catch (OutOfMemoryException^)
        {
        }
    }

    virtual void WriteWarningMessage(String^ message)
    {
        try
        {
            for (int i = 0; i < message->Length; i += MaxMessageSize)
            {
                IntPtr nativeMessage = Marshal::StringToHGlobalUni(message->Substring(i, min(message->Length - i, MaxMessageSize)));
                LogCAWarningMessage(callbackContext, static_cast<const MI_Char*>(safe_cast<void*>(nativeMessage)));
            }
        }
        catch (OutOfMemoryException^)
        {
        }
    }

    virtual void WriteProgressMessage(
        String^ activity,
        String^ currentOperation,
        String^ statusDescription,
        unsigned int percentComplete,
        unsigned int secondsRemaining)
    {
        IntPtr nativeActivity = IntPtr::Zero, nativeCurrentOperation = IntPtr::Zero, nativeStatusDescription = IntPtr::Zero;

        try
        {
            nativeActivity = Marshal::StringToHGlobalUni(activity);
            nativeCurrentOperation = Marshal::StringToHGlobalUni(currentOperation);
            nativeStatusDescription = Marshal::StringToHGlobalUni(statusDescription);

            if (nativeActivity != IntPtr::Zero &&
                nativeCurrentOperation != IntPtr::Zero &&
                nativeStatusDescription != IntPtr::Zero)
            {
                LogCAProgressMessage(
                    callbackContext,
                    static_cast<const MI_Char*>(safe_cast<void*>(nativeActivity)),
                    static_cast<const MI_Char*>(safe_cast<void*>(nativeCurrentOperation)),
                    static_cast<const MI_Char*>(safe_cast<void*>(nativeStatusDescription)),
                    percentComplete,
                    secondsRemaining);
            }
        }
        catch (OutOfMemoryException^)
        {
        }
        finally
        {
            if (nativeActivity != IntPtr::Zero)
            {
                Marshal::FreeHGlobal(nativeActivity);
            }

            if (nativeCurrentOperation != IntPtr::Zero)
            {
                Marshal::FreeHGlobal(nativeCurrentOperation);
            }

            if (nativeStatusDescription != IntPtr::Zero)
            {
                Marshal::FreeHGlobal(nativeStatusDescription);
            }
        }
    }
};

_Always_(_Ret_range_(==, result))
MI_Result GetCimMIError(
    MI_Result result ,
    _In_ Exception^ exception,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    IntPtr messagePtr = Marshal::StringToHGlobalUni(exception->Message);
    MI_Utilities_CimErrorFromErrorCode((MI_Uint32)result, MI_RESULT_TYPE_MI, (MI_Char*)messagePtr.ToPointer(), cimErrorDetails);
    Marshal::FreeHGlobal(messagePtr);
    return result;
}

MI_Result MI_CALL Get(
    _In_ void *provContext,
    _In_ MI_Instance *instance,
    _In_ const MI_Instance *regInstance,
    _Outptr_result_maybenull_ MI_Instance **outputInstance,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    try
    {
        if (provContext != nullptr && regInstance != nullptr && instance != nullptr)
        {
            IntPtr  outputInstanceHandle = IntPtr::Zero;
            IntPtr  errorInstanceHandle = IntPtr::Zero;
            IntPtr  instanceHandle( safe_cast<IntPtr>(instance));
            IntPtr  instanceHandle2 ( safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void*>(regInstance))));

            ResourceProviderAdapter psProviderHandler;

            PlugInStreamsHandler^ plugInStreamsHandler;
            plugInStreamsHandler = gcnew PlugInStreamsHandler();
            plugInStreamsHandler->callbackContext = provContext;

            UInt32 psTestResult = psProviderHandler.GetTargetResource(
                instanceHandle,
                instanceHandle2,
                plugInStreamsHandler,
                outputInstanceHandle,
                errorInstanceHandle);
            MI_Instance *returnedInstance = static_cast<MI_Instance*>(safe_cast<void*>(outputInstanceHandle));
            MI_Instance_Clone(returnedInstance, outputInstance);

            if (extendedError == NULL)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

            if (psTestResult != 0 && errorInstanceHandle != IntPtr::Zero)
            {
                MI_Instance *errorInstance = static_cast<MI_Instance*>(safe_cast<void*>(errorInstanceHandle));
                *extendedError = errorInstance ;
            }

            return safe_cast<MI_Result>(psTestResult);
        }
    }
    catch (Exception^ ex)
    {
        GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
    }

    *outputInstance = NULL;
    return MI_RESULT_FAILED;
}

MI_Result MI_CALL Set(
    _In_ void *provContext,
    _In_ MI_Instance *instance,
    _In_ const MI_Instance *regInstance,
    _Inout_ MI_Uint32 *resultStatus,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    UInt32 psSetResult = 0;

    try
    {
        IntPtr  instanceHandle( safe_cast<IntPtr>(instance));
        IntPtr  errorInstanceHandle = IntPtr::Zero;
        IntPtr  instanceHandle2 ( safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void*>(regInstance))));
        UInt32 tempResultStatus ;

        ResourceProviderAdapter psProviderHandler;

        PlugInStreamsHandler^ plugInStreamsHandler;
        plugInStreamsHandler = gcnew PlugInStreamsHandler();
        plugInStreamsHandler->callbackContext = provContext;

        psSetResult = psProviderHandler.SetTargetResource(
            instanceHandle,
            instanceHandle2,
            plugInStreamsHandler,
            tempResultStatus,
            errorInstanceHandle);
        if (psSetResult == 0 )
        {
            *resultStatus = safe_cast<MI_Uint32>(tempResultStatus);
        }

        if (extendedError == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

        if (psSetResult != 0 && errorInstanceHandle != IntPtr::Zero)
        {
            MI_Instance *errorInstance = static_cast<MI_Instance*>(safe_cast<void*>(errorInstanceHandle));
            if ( extendedError)
            {
                *extendedError = errorInstance ;
            }
            else
            {
                MI_Instance_Delete(errorInstance);
            }
        }
    }
    catch (Exception^ ex)
    {
        return GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
    }

    return safe_cast<MI_Result>(psSetResult);
}

MI_Result MI_CALL Test(
    _In_ void *provContext,
    _In_ MI_Instance *instance,
    _In_ const MI_Instance *regInstance,
    _Inout_ MI_Uint32 *resultStatus,
    _Out_ MI_Boolean *testResult,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    UInt32 psTestResult = 0;

    try
    {
        IntPtr  instanceHandle( safe_cast<IntPtr>(instance));
        IntPtr  errorInstanceHandle = IntPtr::Zero;
        IntPtr  instanceHandle2 ( safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void*>(regInstance))));
        Boolean boolValue = false;
        UInt32 tempResultStatus ;

        ResourceProviderAdapter psProviderHandler;
        PlugInStreamsHandler^ plugInStreamsHandler;
        plugInStreamsHandler = gcnew PlugInStreamsHandler();
        plugInStreamsHandler->callbackContext = provContext;

        psTestResult = psProviderHandler.TestTargetResource(
            instanceHandle,
            instanceHandle2,
            plugInStreamsHandler,
            tempResultStatus,
            boolValue,
            errorInstanceHandle);
        if (psTestResult == 0)
        {
            *resultStatus = safe_cast<MI_Uint32>(tempResultStatus);

            if (boolValue == true)
            {
                *testResult = MI_TRUE;
            }
            else
            {
                *testResult = MI_FALSE;
            }

            return MI_RESULT_OK ;
        }

        if (extendedError == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

        if (psTestResult != 0 && errorInstanceHandle != IntPtr::Zero)
        {
            MI_Instance *errorInstance = static_cast<MI_Instance*>(safe_cast<void*>(errorInstanceHandle));
            if ( extendedError)
            {
                *extendedError = errorInstance ;
            }
            else
            {
                MI_Instance_Delete(errorInstance);
            }
        }
    }
    catch (Exception^ ex)
    {
        return GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
    }

    return safe_cast<MI_Result>(psTestResult);
}

MI_Result  MI_CALL StopCurrentPSConfiguration(
     _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    try
    {
        *extendedError = NULL;
        ResourceProviderAdapter::StopTargetResource();
    }
    catch (Exception^ ex)
    {
        return GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
    }

    return MI_RESULT_OK;
}

MI_Result MI_CALL GetResourceProvider(
    _In_ MI_StringA *classNameA,
    _In_ MI_StringA *moduleNameA,
    _In_ MI_StringA *moduleVersionA,
    _Inout_ MI_StringA *providerNames,
    _Inout_ MI_StringA *mofPaths,
    _Inout_ MI_ClassA *miClassArray,
    _Inout_ MI_InstanceA *registrationInstances,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _In_z_ MI_Char * jobIdNative)
{
    UInt32 result = 0;

    try
    {
        array<IntPtr> ^psProviderSchema = nullptr;
        array<IntPtr>  ^registrationInstanceHandles = nullptr;
        array<String^> ^providerNamesNative = nullptr;
        array<String^> ^mofPathsNative = nullptr;
        IntPtr  errorInstanceHandle = IntPtr::Zero;
        MI_Uint32 xCount = 0;

        ResourceProviderAdapter^ psProviderHandler;
        psProviderHandler = gcnew ResourceProviderAdapter();

        ResourceProviderMetaData^ resourceProviderMetaData;
        resourceProviderMetaData = gcnew ResourceProviderMetaData();

        String^ jobGuidStringLocal=gcnew String(jobIdNative);
        S_DscCoreR::JobGuidString=jobGuidStringLocal;
        /*ClassName */
        array<String^> ^managedClassNames = gcnew array<String^>(classNameA->size);
        for (xCount = 0; xCount < classNameA->size; xCount++)
        {
            managedClassNames[xCount] = Marshal::PtrToStringUni(safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void *>(classNameA->data[xCount]))));
        }

        /*ModuleName*/
        array<String^> ^managedModuleNames = gcnew array<String^>(moduleNameA->size);
        for (xCount = 0; xCount < moduleNameA->size; xCount++)
        {
            managedModuleNames[xCount] = Marshal::PtrToStringUni(safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void *>(moduleNameA->data[xCount]))));
        }

        /*ModuleVersion*/
        array<String^> ^managedModuleVersion = gcnew array<String^>(moduleVersionA->size);
        for (xCount = 0; xCount < moduleVersionA->size; xCount++)
        {
            managedModuleVersion[xCount] = Marshal::PtrToStringUni(safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void *>(moduleVersionA->data[xCount]))));
        }

        S_DscCoreR::EventWriteMessageGetSchemaPath(S_DscCoreR::JobGuidString);

        resourceProviderMetaData->ManagedClassNames = managedClassNames;
        resourceProviderMetaData->ManagedModuleNames = managedModuleNames;
        resourceProviderMetaData->ManagedModuleVersions = managedModuleVersion;
        resourceProviderMetaData->ProviderNames = providerNamesNative;
        resourceProviderMetaData->MofFileLocations = mofPathsNative;
        resourceProviderMetaData->PsProviderSchema = psProviderSchema;
        resourceProviderMetaData->RegistrationInstanceHandles = registrationInstanceHandles;
        resourceProviderMetaData->ErrorInstanceHandle = errorInstanceHandle;

        result = psProviderHandler->GetResourceProvider(resourceProviderMetaData);

        providerNamesNative = resourceProviderMetaData->ProviderNames;
        mofPathsNative = resourceProviderMetaData->MofFileLocations;
        psProviderSchema = resourceProviderMetaData->PsProviderSchema;
        registrationInstanceHandles = resourceProviderMetaData->RegistrationInstanceHandles;
        errorInstanceHandle = resourceProviderMetaData->ErrorInstanceHandle;

        if (result == 0)
        {
            //form classes
            miClassArray->data = static_cast<MI_Class**>(Malloc_Core(psProviderSchema->Length * sizeof(MI_Class*)));
            miClassArray->size = psProviderSchema->Length;
            for (MI_Sint32 xCount = 0 ; xCount < psProviderSchema->Length; xCount++)
            {
                miClassArray->data[xCount] = static_cast<MI_Class*>(safe_cast<void*>(psProviderSchema[xCount]));
            }

            //form instances
            registrationInstances->data = static_cast<MI_Instance**>(Malloc_Core(registrationInstanceHandles->Length * sizeof(MI_Instance*)));
            registrationInstances->size = registrationInstanceHandles->Length;
            for (MI_Sint32 xCount = 0 ; xCount < registrationInstanceHandles->Length; xCount++)
            {
                registrationInstances->data[xCount] = static_cast<MI_Instance*>(safe_cast<void*>(registrationInstanceHandles[xCount]));
            }

            //form paths
            mofPaths->size = mofPathsNative->Length;
            mofPaths->data =static_cast<MI_Char**>(Malloc_Core(mofPathsNative->Length * sizeof(MI_Char*)));
            for (MI_Sint32 xCount = 0 ; xCount < mofPathsNative->Length; xCount++)
            {
                pin_ptr<const wchar_t> lpPaths = PtrToStringChars(mofPathsNative[xCount]);
                mofPaths->data[xCount] = static_cast<MI_Char*>(Malloc_Core( (mofPathsNative[xCount]->Length + 1 ) * sizeof(MI_Char)));
                memcpy(mofPaths->data[xCount], lpPaths, mofPathsNative[xCount]->Length * sizeof(MI_Char));
                (mofPaths->data[xCount])[mofPathsNative[xCount]->Length] = L'\0';
            }

            providerNames->size = providerNamesNative->Length;
            providerNames->data =static_cast<MI_Char**>(Malloc_Core(providerNamesNative->Length * sizeof(MI_Char*)));
            for (MI_Sint32 xCount = 0 ; xCount < providerNamesNative->Length; xCount++)
            {
                pin_ptr<const wchar_t> lpPaths = PtrToStringChars(providerNamesNative[xCount]);
                providerNames->data[xCount] = static_cast<MI_Char*>(Malloc_Core( (providerNamesNative[xCount]->Length + 1 ) * sizeof(MI_Char)));
                memcpy(providerNames->data[xCount], lpPaths, providerNamesNative[xCount]->Length * sizeof(MI_Char));
                (providerNames->data[xCount])[providerNamesNative[xCount]->Length] = L'\0';
            }
        }
        else
        {
            if (extendedError == NULL)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

            if (errorInstanceHandle != IntPtr::Zero)
            {
                MI_Instance *errorInstance = static_cast<MI_Instance*>(safe_cast<void*>(errorInstanceHandle));
                *extendedError = errorInstance;
            }
        }
    }
    catch (Exception^ ex)
    {
        GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
        result = MI_RESULT_FAILED;
    }

    return safe_cast<MI_Result>(result);
}

MI_Result MI_CALL Pull_GetConfiguration_ManagedPlugin(
    _In_ void *provContext,
    _In_ MI_Instance *metaConfig,
    _Outptr_result_maybenull_z_  MI_Char** mofFileName,
    _Outptr_result_maybenull_z_  MI_Char** result,
    _Out_ MI_Uint32* getActionStatusCode,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _In_ MI_Char* jobIdNative)
{
    UInt32 psResult = 0;

    try
    {
        if (extendedError == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

        if (provContext == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }

        UInt32 tempGetActionStatusCode;

        IntPtr  metaConfigHandle(safe_cast<IntPtr>(metaConfig));
        IntPtr  errorInstanceHandle = IntPtr::Zero;
        String^ jobGuidStringLocal=gcnew String(jobIdNative);
        S_DscCoreR::JobGuidString=jobGuidStringLocal;
        String^ outputResult = nullptr;
        String^ outputFileName = nullptr;
        psResult = DownloadManagerBase::GetDscDocument(
                                    metaConfigHandle,
                                    errorInstanceHandle,
                                    outputFileName,
                                    outputResult,
                                    tempGetActionStatusCode);
        *getActionStatusCode = safe_cast<MI_Uint32>(tempGetActionStatusCode);
        if (psResult == 0)
        {
            pin_ptr<const wchar_t> lpPaths = PtrToStringChars(outputResult);
            *result = static_cast<MI_Char*>(Malloc_Core( (outputResult->Length + 1 ) * sizeof(MI_Char)));
            memcpy(*result, lpPaths, outputResult->Length * sizeof(MI_Char));
            (*result)[outputResult->Length] = L'\0';
            if (outputFileName != nullptr)
            {
                pin_ptr<const wchar_t> lpPaths = PtrToStringChars(outputFileName);
                *mofFileName = static_cast<MI_Char*>(Malloc_Core( (outputFileName->Length + 1 ) * sizeof(MI_Char)));
                memcpy(*mofFileName, lpPaths, outputFileName->Length * sizeof(MI_Char));
                (*mofFileName)[outputFileName->Length] = L'\0';
            }
        }

        if (extendedError == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

        if (psResult != 0 && errorInstanceHandle != IntPtr::Zero)
        {
            MI_Instance *errorInstance = static_cast<MI_Instance*>(safe_cast<void*>(errorInstanceHandle));
            *extendedError = errorInstance;
        }
    }
    catch (Exception^ ex)
    {
        GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
        psResult = MI_RESULT_FAILED;
    }

    return safe_cast<MI_Result>(psResult);
}

MI_Result MI_CALL Pull_GetAction_ManagedPlugin(
    _In_ void *provContext,
    _In_ MI_Instance *metaConfig,
    _In_z_ const MI_Char *checkSum,
    _In_ MI_Boolean complianceStatus,
    _In_ MI_Uint32 lastGetActionStatusCode,
    _Outptr_result_maybenull_z_  MI_Char** result,
    _Out_ MI_Uint32 *getActionStatusCode,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _In_ MI_Char* jobIdNative)
{
    UInt32 psResult = 0;

    try
    {
        if (extendedError == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }

        *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

        if (provContext == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }

        String^ jobGuidStringLocal=gcnew String(jobIdNative);
        S_DscCoreR::JobGuidString=jobGuidStringLocal;

        UInt32 tempGetActionStatusCode;
        IntPtr  metaConfigHandle( safe_cast<IntPtr>(metaConfig));
        IntPtr  errorInstanceHandle = IntPtr::Zero;
        String^ checkSumNative = Marshal::PtrToStringUni(safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void*>(checkSum))));

        String^ outputResult = nullptr;
        Boolean boolValue = false;
        if (complianceStatus == MI_TRUE)
        {
            boolValue = true;
        }

        psResult = DownloadManagerBase::GetDscAction(
                                    metaConfigHandle,
                                    checkSumNative,
                                    boolValue,
                                    lastGetActionStatusCode,
                                    errorInstanceHandle,
                                    outputResult,
                                    tempGetActionStatusCode);
        *getActionStatusCode = safe_cast<MI_Uint32>(tempGetActionStatusCode);
        if (psResult == 0)
        {
            pin_ptr<const wchar_t> lpPaths = PtrToStringChars(outputResult);
            *result = static_cast<MI_Char*>(Malloc_Core( (outputResult->Length + 1 ) * sizeof(MI_Char)));
            memcpy(*result, lpPaths, outputResult->Length * sizeof(MI_Char));
            (*result)[outputResult->Length] = L'\0';
        }

        if (extendedError == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

        if (psResult != 0 && errorInstanceHandle != IntPtr::Zero)
        {
            MI_Instance *errorInstance = static_cast<MI_Instance*>(safe_cast<void*>(errorInstanceHandle));
            *extendedError = errorInstance;
        }
    }
    catch (Exception^ ex)
    {
        GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
        psResult = MI_RESULT_FAILED;
    }

    return safe_cast<MI_Result>(psResult);
}

MI_Result MI_CALL Pull_GetModules_ManagedPlugin(_In_ void *provContext, 
                                                      _In_ MI_Instance *metaConfig, 
                                                      _In_z_  MI_Char* downloadLocation,
                                                      _In_z_  MI_Char* mofFileName,
                                                      _In_ MI_Boolean allowModuleOverwrite,
                                                      _Out_ MI_Uint32* getActionStatusCode,
                                                      _Outptr_result_maybenull_ MI_Instance **extendedError,
                                                      _In_ MI_Char* jobIdNative)
{
    UInt32 psResult = 0;

    try
    {
        if (extendedError == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }

        *extendedError = NULL;      // Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.

        if (provContext == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }

        String^ jobGuidStringLocal=gcnew String(jobIdNative);
        S_DscCoreR::JobGuidString=jobGuidStringLocal;

        UInt32 tempGetActionStatusCode;
        IntPtr  metaConfigHandle( safe_cast<IntPtr>(metaConfig));
        IntPtr  errorInstanceHandle = IntPtr::Zero;
        String^ downloadLocationNative = Marshal::PtrToStringUni(safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void*>(downloadLocation))));
        String^ mofFileNameNative = Marshal::PtrToStringUni(safe_cast<IntPtr>(const_cast<void*>(safe_cast<const void*>(mofFileName))));

        Boolean boolValue = allowModuleOverwrite == MI_TRUE? true:false;

        psResult = DownloadManagerBase::GetDscModule(
                                    metaConfigHandle,
                                    downloadLocationNative,
                                    mofFileNameNative,
                                    boolValue,
                                    errorInstanceHandle,
                                    tempGetActionStatusCode
                                    );
        *getActionStatusCode = safe_cast<MI_Uint32>(tempGetActionStatusCode);


        if (psResult != 0 && errorInstanceHandle != IntPtr::Zero)
        {
            MI_Instance *errorInstance = static_cast<MI_Instance*>(safe_cast<void*>(errorInstanceHandle));
            *extendedError = errorInstance;
        }
    }
    catch (Exception^ ex)
    {
        GetCimMIError(MI_RESULT_FAILED, ex, extendedError);
        psResult = MI_RESULT_FAILED;
    }

    return safe_cast<MI_Result>(psResult);
}

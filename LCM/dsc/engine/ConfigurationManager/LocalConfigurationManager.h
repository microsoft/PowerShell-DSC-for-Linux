/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _LOCALCONFIGURATIONMANAGER_H
#define _LOCALCONFIGURATIONMANAGER_H

void UnloadFromProvider(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context);


void Invoke_SendConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfiguration* in);

void Invoke_SendConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendConfigurationApply* in);

void Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetConfiguration* in);

void Invoke_ApplyConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_ApplyConfiguration* in);

void Invoke_SendMetaConfigurationApply(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply* in);

void Invoke_GetMetaConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_GetMetaConfiguration* in);

void Invoke_RollBack(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_RollBack* in);

void Invoke_TestConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_TestConfiguration* in);

void Invoke_PerformRequiredConfigurationChecks(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* in);

void Invoke_StopConfiguration(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_StopConfiguration* in);

typedef struct _Context_Invoke_Basic
{
    MI_Context *context;
    const MI_Char* methodName;
    MI_Uint32 flag;
    MI_Boolean force;
    MI_ConstUint8A data;
    MI_Char * stringdata;
    MI_Boolean dataExist;
    
} Context_Invoke_Basic;

#endif

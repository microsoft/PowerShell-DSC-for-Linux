/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _DSC_HOST_H
#define _DSC_HOST_H

#include "MI.h"
#include "parson.h"

// DSC Host Version Information
const MI_Uint32 MajorVersion = 1;
const MI_Uint32 MinorVersion = 0;
const MI_Uint32 BuildVersion = 0000;

#define DSCHOST_VERSION_BUFF_SIZE   512
#define DSCHOST_STR_BUFFER_SIZE   512
#define DSCHOST_PID_FILE_PATH "/opt/dsc/bin/dsc_host.pid"

typedef enum _DscSupportedOperation
{
    DscSupportedOperation_NOP = 0,
    DscSupportedOperation_SendConfiguration,
    DscSupportedOperation_SendConfigurationApply,
    DscSupportedOperation_GetConfiguration,
    DscSupportedOperation_ApplyConfiguration,
    DscSupportedOperation_SendMetaConfigurationApply,
    DscSupportedOperation_GetMetaConfiguration,
    DscSupportedOperation_RollBack,
    DscSupportedOperation_TestConfiguration,
    DscSupportedOperation_PerformRequiredConfigurationChecks,
    DscSupportedOperation_StopConfiguration,
    DscSupportedOperation_PerformInventory,
    DscSupportedOperation_PerformInventoryOOB
} DscSupportedOperation;

#define DSC_OPERATION_SEND_CONFIGURATION_STR MI_T("SendConfiguration")
#define DSC_OPERATION_SEND_CONFIGURATION_APPLY_STR MI_T("SendConfigurationApply")
#define DSC_OPERATION_GET_CONFIGURATION_STR MI_T("GetConfiguration")
#define DSC_OPERATION_APPLY_CONFIGURATION_STR MI_T("ApplyConfiguration")
#define DSC_OPERATION_SEND_METACONFIGURATION_APPLY_STR MI_T("SendMetaConfigurationApply")
#define DSC_OPERATION_GET_METACONFIGURATION_STR MI_T("GetMetaConfiguration")
#define DSC_OPERATION_ROLLBACK_STR MI_T("RollBack")
#define DSC_OPERATION_TEST_CONFIGURATION_STR MI_T("TestConfiguration")
#define DSC_OPERATION_PERFORM_REQUIRED_CONFIGURATION_CHECKS_STR MI_T("PerformRequiredConfigurationChecks")
#define DSC_OPERATION_STOP_CONFIGURATION_STR MI_T("StopConfiguration")
#define DSC_OPERATION_PERFORM_INVENTORY_STR MI_T("PerformInventory")
#define DSC_OPERATION_PERFORM_INVENTORY_OOB_STR MI_T("PerformInventoryOOB")

#endif

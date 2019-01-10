///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// This file is implementing a separate version of what we have in MSFT_DSCLocalConfigurationManager.c
// The new implementation assumes there is no OMI server and is the code is expected to be used by dsc_host.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DSC_OPERAIONS_H
#define _DSC_OPERAIONS_H

#include "MI.h"
// #include "dsc_operation_context.h"

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

#define DSC_OPERATION_GET_CONFIGURATION_STR MI_T("GetConfiguration")
#define DSC_OPERATION_TEST_CONFIGURATION_STR MI_T("TestConfiguration")
#define DSC_OPERATION_PERFORM_INVENTORY_STR MI_T("PerformInventory")
#define DSC_OPERATION_PERFORM_INVENTORY_OOB_STR MI_T("PerformInventoryOOB")
#define DSC_OPERATION_SEND_CONFIGURATION_STR MI_T("SendConfiguration")
#define DSC_OPERATION_SEND_CONFIGURATION_APPLY_STR MI_T("SendConfigurationApply")
#define DSC_OPERATION_SEND_METACONFIGURATION_APPLY_STR MI_T("SendMetaConfigurationApply")
#define DSC_OPERATION_GET_METACONFIGURATION_STR MI_T("GetMetaConfiguration")
#define DSC_OPERATION_APPLY_CONFIGURATION_STR MI_T("ApplyConfiguration")

#endif

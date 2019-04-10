#ifndef _DSC_HOST_H
#define _DSC_HOST_H

#include "MI.h"
#include "parson.h"

// DSC Host Version Information
const MI_Uint32 MajorVersion = 2;
const MI_Uint32 MinorVersion = 0;
const MI_Uint32 BuildVersion = 0000;

#define DSCHOST_VERSION_BUFF_SIZE   512
#define DSCHOST_STR_BUFFER_SIZE   512

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

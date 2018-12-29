#ifndef _DSC_HOST_H
#define _DSC_HOST_H

#include <MI.h>

// DSC Host Version Information
const MI_Uint32 MajorVersion = 1;
const MI_Uint32 MinorVersion = 0;
const MI_Uint32 BuildVersion = 0000;

#define DSCHOST_VERSION_BUFF_SIZE   516

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

#endif

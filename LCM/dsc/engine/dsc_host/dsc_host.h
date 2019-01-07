#ifndef _DSC_HOST_H
#define _DSC_HOST_H

#include "MI.h"
#include "dsc_operations.h"
#include "parson.h"

// DSC Host Version Information
const MI_Uint32 MajorVersion = 1;
const MI_Uint32 MinorVersion = 0;
const MI_Uint32 BuildVersion = 0000;

#define DSCHOST_VERSION_BUFF_SIZE   516

MI_Result  Print_JSON_Value (
        JSON_Value** p_root_value
    );

#endif

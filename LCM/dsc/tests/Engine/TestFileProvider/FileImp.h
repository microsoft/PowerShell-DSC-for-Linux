/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#ifndef __FILEIMP_H
#define __FILEIMP_H


void Invoke_GetTargetResource(_In_ MI_Context* context,_In_opt_ const MSFT_FileDirectoryConfiguration* in );
void Invoke_SetTargetResource(_In_ MI_Context* context,_In_opt_ const MSFT_FileDirectoryConfiguration* in );
void Invoke_TestTargetResource(_In_ MI_Context* context,_In_opt_ const MSFT_FileDirectoryConfiguration* in );

#endif

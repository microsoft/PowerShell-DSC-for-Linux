#pragma once

#include <MI.h>
#include "MSFT_DSCWebPullClient.h"

void GetDSCAction(_In_ MI_Context* context, _In_opt_ const MSFT_DSCWebPullClient_GetDSCAction* in);

void GetDSCDocument(_In_ MI_Context* context, _In_opt_ const MSFT_DSCWebPullClient_GetDSCDocument* in);

void GetDSCModule(_In_ MI_Context* context, _In_opt_ const MSFT_DSCWebPullClient_GetDSCModule* in);


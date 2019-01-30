#pragma once

#define DSC_WORKER_DEBUG_ENABLED 0

#define DSC_WORKER_DEBUG(print_call) \
 { if (DSC_WORKER_DEBUG_ENABLED) print_call; }

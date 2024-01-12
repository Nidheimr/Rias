#pragma once

#include "rias_impl.h"

// --------------------------------
// Memory function hijack
// --------------------------------

#ifndef RIAS_DONT_HIJACK_MEMORY

#define malloc(size) rias_malloc(__FILE__, __func__, __LINE__, size)
#define calloc(num, size) rias_calloc(__FILE__, __func__, __LINE__, num, size)
#define realloc(address, newsize) rias_realloc(__FILE__, __func__, __LINE__, address, newsize)
#define free(address) rias_free(address)

#endif

#pragma once

#include "rias_impl.h"
#include <stdlib.h>

// --------------------------------
// Memory function hijack
// --------------------------------

#ifndef RIAS_DONT_HIJACK_MEMORY

#define malloc(size) r_malloc(__FILE__, __func__, __LINE__, size)
#define calloc(num, size) r_calloc(__FILE__, __func__, __LINE__, num, size)
#define realloc(address, newsize) r_realloc(__FILE__, __func__, __LINE__, address, newsize)
#define free(address) r_free(address)

#endif

// --------------------------------
// Main function hijack
// --------------------------------

#ifndef RIAS_DONT_HIJACK_MAIN

extern int r_main(int, char*[]);

int main(int argc, char* argv[])
{
    r_init_allocations();

    int ret = r_main(argc, argv);
    
    r_dump_leaks();
    r_destroy_allocations();

    return ret;
}

#define main(...) r_main(int argc, char* argv[])

#endif

#pragma once

// --------------------------------
// Functions
// --------------------------------

#include <stddef.h>

void* rias_malloc(const char* file, const char* func, int line, size_t size);
void* rias_calloc(const char* file, const char* func, int line, int num, int size);
void* rias_realloc(const char* file, const char* func, int line, void* address, int newsize);
void  rias_free(void* address);

void  rias_initialise();
void  rias_dump_leaks_and_terminate();

#pragma once

// --------------------------------
// Functions
// --------------------------------

#include <stddef.h>

void* r_malloc(const char* file, const char* func, int line, size_t size);
void* r_calloc(const char* file, const char* func, int line, int num, int size);
void* r_realloc(const char* file, const char* func, int line, void* address, int newsize);
void  r_free(void* address);

void  r_init_allocations();
void  r_destroy_allocations();
void  r_dump_leaks();

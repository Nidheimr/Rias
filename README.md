# Rias

## Overview

Rias is a library that provides the ability to track memory allocations and deallocations, dumping any leaks at the end of the program.

## Building

### Windows

Add `rias_impl.c` to your project and compile it with your program, then use the headers as normal.

**OR**

Build the project and link the resulting library to your program, then use the headers as normal.

## Usage

Include `rias.h` wherever you plan on using memory functions.

By default, Rias will define over the C memory functions, meaning after including, you do not need to do replace any existing C memory functions.

There is some setup in the main function however.

At the very start of the main function, use `rias_initialise();` to begin tracking allocations.

At the very end of the main function, before the return, use `rias_dump_leaks_and_terminate();` to print all memory leaks, if any.

### Disable Memory Function Hijacking

If you do not want Rias to define over memory functions, you can define this before Rias is included:

```c
#define RIAS_DONT_HIJACK_MEMORY
```

***WARNING:*** *If you choose to do this in file, as opposed to a compiler definition, you will need to do this before every include of `rias.h`.*

Then, you can use the Rias memory functions:

```c
void* rias_malloc(const char* file, const char* func, int line, size_t size);
void* rias_calloc(const char* file, const char* func, int line, int num, int size);
void* rias_realloc(const char* file, const char* func, void* address, int newsize);
void  rias_free(void* address);
```

Note, each of these functions take file, function, and line parameters; these are used for tracking where (de)allocations happen. If you use them manually, you can put whatever you want in them, or use `NULL` (or 0 for line) to ignore them.

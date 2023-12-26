# Rias

## Overview

Rias is a small memory manager/leak detector for C that I wrote, because I get paranoid about memory leaks. It is nowhere near perfect and probably very inefficient on both memory and processing. But it works, so hey.

## Installation

Add `rias_impl.c` to your project and compile it with your program, then use the headers as normal.

**OR**

Build the project and link the resulting library to your program, then use the headers as normal.

**THEN**

You must include `rias.h` into the file with your main function, and any other file that plans on using memory functions. You may use this header instead of `stdlib.h` as it is implicitely included.

## Configuration

By default, Rias will define over the C memory functions and the main function, meaning after including, you do not need to do anything else.

### Disable Main Hijacking

If you do not want Rias to define over the main function, you can define this before Rias is included:

```c
#define RIAS_DONT_HIJACK_MAIN
```

***WARNING:*** *If you choose to do this in file, as opposed to a compiler definition, you will need to do this before every include of `rias.h`.*

However, for Rias to properly function without hijacking main you must do the following:

```c
int main()
{
	// start of main: initialise
	r_init_allocations();
	
	// ... your code ...
	
	// end of main: dump leaks and terminate
	r_dump_leaks();
	r_destroy_allocations();
	
	return 0;
}
```

### Disable Memory Function Hijacking

If you do not want Rias to define over memory functions, you can define this before Rias is included:

```c
#define RIAS_DONT_HIJACK_MEMORY
```

***WARNING:*** *If you choose to do this in file, as opposed to a compiler definition, you will need to do this before every include of `rias.h`.*

Then, you can use the Rias memory functions:

```c
void* r_malloc(const char* file, const char* func, int line, size_t size);
void* r_calloc(const char* file, const char* func, int line, int num, int size);
void* r_realloc(const char* file, const char* func, void* address, int newsize);
void r_free(void* address);
```

Note, each of these functions take file, function, and line parameters; these are used for tracking where (de)allocations happen. If you use them manually, you can put whatever you want in them, or use `NULL` (or 0 for line) to ignore them.

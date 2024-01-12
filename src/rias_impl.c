#include "rias_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME 256
#define MAX_FUNC_NAME 64

// --------------------------------
// Allocation tracking
// --------------------------------

typedef struct allocation allocation_t;
struct allocation
{
    void*  address;
    size_t size;
    
    char   file[MAX_FILE_NAME];
    char   func[MAX_FUNC_NAME];
    int    line;

    allocation_t* next;
};

allocation_t* alloc_head = NULL;

void allocate(void* address, size_t size, const char* file, const char* func, int line)
{
    allocation_t* end = alloc_head;
    while (end != NULL)
    {
        if (end->next != NULL)
        {
            end = end->next;
            continue;
        }

        end->next = malloc(sizeof(allocation_t));
        end->next->address = address;
        end->next->size = size;
        end->next->line = line;
        end->next->next = NULL;
        
        char* unknown = "?";
        strcpy_s(end->next->file, MAX_FILE_NAME, file == NULL ? unknown : file);
        strcpy_s(end->next->func, MAX_FUNC_NAME, func == NULL ? unknown : func);
        
        end = NULL;
    }
}

void deallocate(void* address)
{
    allocation_t* prev = alloc_head;
    allocation_t* cur = alloc_head->next;
    while (cur != NULL)
    {
        if (cur->address != address)
        {
            prev = cur;
            cur = cur->next;
            continue;
        }

        prev->next = cur->next;
        free(cur);

        cur = NULL;
    }
}

void destroy_allocations()
{
    allocation_t* end = alloc_head->next;
    while (end != NULL)
    {
        allocation_t* cur = end;
        end = end->next;
        free(cur);
    }

    free(alloc_head);
}

// --------------------------------
// Stdlib wrappers
// --------------------------------

void* rias_malloc(const char* file, const char* func, int line, size_t size)
{
    void* naddr = malloc(size);
 
    if (naddr != NULL)
    {
        allocate(naddr, size, file, func, line);
    }

    return naddr;
}

void* rias_calloc(const char* file, const char* func, int line, int num, int size)
{
    void* naddr = calloc(num, size);
    
    if (naddr != NULL)
    {
        allocate(naddr, size, file, func, line);
    }

    return naddr;
}

void* rias_realloc(const char* file, const char* func, int line, void* address, int newsize)
{
    void* naddr = realloc(address, newsize);
    
    if (naddr != NULL)
    {
        deallocate(address);
        allocate(naddr, newsize, file, func, line);
    }

    return naddr;
}

void rias_free(void* address)
{
    if (address != NULL)
    {
        deallocate(address);
    }

    free(address);
}

// --------------------------------
// Lifetime
// --------------------------------

void rias_initialise()
{
    alloc_head = malloc(sizeof(allocation_t));
    alloc_head->next = NULL;
}

void rias_dump_leaks_and_terminate()
{
    allocation_t* cur = alloc_head->next;
    
    if (cur == NULL)
    {
        printf("\nRias -> No memory leaks detected.\n\n");
        return;
    }

    printf("\nRias -> The following allocations are not deallocated\n");
    printf("-----------------------------------------------------\n");
    while (cur != NULL)
    {
        printf("-> %zu bytes at %p (allocated: %s:%d %s)\n", cur->size, cur->address, cur->file, cur->line, cur->func);
        cur = cur->next;
    }
    printf("\n");

    destroy_allocations();
}

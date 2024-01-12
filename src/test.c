#include "rias.h"
#include "rias_impl.h"

// TEST: main hijack
int main()
{
    rias_initialise();

    // TEST: hijacked malloc
    int* m = malloc(sizeof(int));

    // TEST: hijacked calloc
    int* c = calloc(1, sizeof(int));

    // TEST: hijacked realloc
    int* r = malloc(sizeof(int));
    r = realloc(r, 2 * sizeof(int));

    // TEST: hijacked free
    free(c);
    free(r);

    // TEST: purposely leak m

    rias_dump_leaks_and_terminate();
    return 0;
}

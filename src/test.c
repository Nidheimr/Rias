#include "rias.h"

// TEST: main hijack
int main()
{
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

    return 0;
}

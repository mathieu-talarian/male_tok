#include "malloc.h"

void *small_realloc(t_chunk *ptr, size_t size)
{
    if (D)
        printf("Small realloc\n");

    return NULL;
}
#include "malloc.h"

static void *s_realloc(void *ptr, size_t size, t_zone *zone, t_chunk *chunk)
{
    return NULL;
}

void *small_realloc(void *ptr, t_chunk *chunk, size_t size)
{
    t_zone *zone;
    if (D)
        printf("Small realloc\n");
    if ((zone = find_zone(g_env.small, chunk)))
        return s_realloc(ptr, size, zone, chunk);
    return NULL;
}
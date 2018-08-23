#include "malloc.h"

void *small_m(size_t size)
{
    printf("SMALL MALLOC | %zu\n", g_env.small->head->size);
    void *ret;

    if ((ret = search_free_chunk(g_env.small, SMALL, size)) != NULL)
        return ret;
    return (expand_zone(g_env.small, SMALL, size));
}
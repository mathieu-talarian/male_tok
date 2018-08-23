#include "malloc.h"

void *tiny_m(size_t size)
{
    printf("TINY MALLOC | %zu\n", g_env.tiny->head->size);
    void *ret;

    if ((ret = search_free_chunk(g_env.tiny, TINY, size)) != NULL)
        return ret;
    return (expand_zone(g_env.tiny, TINY, size));
}
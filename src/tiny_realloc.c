#include "malloc.h"

static void *t_realloc(void *ptr, size_t size, t_zone *zone, t_chunk *chunk)
{
    if (size <= chunk->size && size <= T_MSIZE)
        return split_block(zone, chunk, TINY, size);
    if (size <= T_MSIZE)
        if (chunk->next && IS_FREE(chunk->next->free) && have_enough_space(chunk, size))
            return (fusion_block(zone, chunk, TINY, size));
    return NULL;
}

void *tiny_realloc(void *ptr, t_chunk *chunk, size_t size)
{
    t_zone *zone;

    if (D)
        printf("Tiny realloc\n");
    if ((zone = find_zone(g_env.tiny, ptr)))
        return t_realloc(ptr, size, zone, chunk);
    return NULL;
}
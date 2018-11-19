#include "malloc.h"

static void *t_realloc(void *ptr, size_t size, t_zone *zone, t_chunk *chunk)
{
    if (size <= chunk->size && size <= TINY_MAX_SIZE)
        return split_block(zone, chunk, TINY, size);
    if (size <= TINY_MAX_SIZE)
        if (chunk->next && chunk->next->free && have_enough_space(chunk, size))
            return (fusion_block(zone, chunk, TINY, size));
    return move_and_free(ptr, chunk->size, size);
}

void *tiny_realloc(void *ptr, t_chunk *chunk, size_t size)
{
    t_zone *zone;

    if ((zone = find_zone(g_env.tiny_zone, chunk)))
        return t_realloc(ptr, size, zone, chunk);
    return NULL;
}

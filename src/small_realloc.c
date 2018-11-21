#include "malloc.h"

static void *s_realloc(void *ptr, size_t size, t_zone *zone, t_chunk *chunk)
{
    if (size <= chunk->size && size <= SMALL_MAX_SIZE)
        return split_block(zone, chunk, SMALL, size);
    if (size <= SMALL_MAX_SIZE)
        if (chunk->next && chunk->next->free && have_enough_space(chunk, size))
            return (fusion_block(zone, chunk, SMALL, size));
    return move_and_free(ptr, chunk->size, size);
}

void *small_realloc(void *ptr, t_chunk *chunk, size_t size)
{
    t_zone *zone;

    if ((zone = find_zone(g_env.small_zone, chunk)))
        return s_realloc(ptr, size, zone, chunk);
    return NULL;
}
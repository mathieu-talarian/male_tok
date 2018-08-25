#include "malloc.h"

static void *s_realloc(void *ptr, size_t size, t_zone *zone, t_chunk *chunk)
{
    if (D)
        printf("%p\n", zone);
    if (size <= chunk->size && size <= S_MSIZE)
        return split_block(zone, chunk, SMALL, size);
    if (size <= S_MSIZE)
        if (chunk->next && IS_FREE(chunk->next->free) && have_enough_space(chunk, size))
            return (fusion_block(zone, chunk, SMALL, size));
    return move_and_free(ptr, chunk->size, size);
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
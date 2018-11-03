#include "malloc.h"

void* _tiny_small_malloc(t_zone* zone, int type, size_t size)
{
    void* returned_addr;

    if ((returned_addr = search_free_chunk(zone, type, size)) != NULL)
        return returned_addr;
    return expand_zone(zone, type, size);
}

void* tiny_small_malloc(size_t size)
{
    return size <= T_MSIZE ? _tiny_small_malloc(g_env.tiny_zone, TINY, size) : _tiny_small_malloc(g_env.small_zone, SMALL, size);
}
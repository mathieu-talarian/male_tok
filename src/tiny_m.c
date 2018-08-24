#include "malloc.h"

void *tiny_m(size_t size)
{
    void *ret;

    if (D)
        printf("Tiny malloc | %d\n", ++g_cpt[TINY]);
    if ((ret = search_free_chunk(g_env.tiny, TINY, size)) != NULL)
        return ret;
    return (expand_zone(g_env.tiny, TINY, size));
}
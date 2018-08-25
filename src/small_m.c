#include "malloc.h"

void *small_m(size_t size)
{
    void *ret;

    if (D)
        printf("Small malloc | %d\n", ++g_cpt[SMALL]);
    if ((ret = search_free_chunk(g_env.small, SMALL, size)) != NULL)
        return ret;
    return (expand_zone(g_env.small, SMALL, size));
}
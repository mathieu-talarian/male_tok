#include "malloc.h"

static size_t set_tiny_zone()
{
    size_t r;
    size_t q;
    size_t size;

    q = T_RSIZE / PS;
    r = (T_RSIZE % PS) ? 1 : 0;
    size = (q + r) * PS;
    printf("%zu", size);
    while ((size - sizeof(t_zone)) / (T_MSIZE + sizeof(t_chunk)) < 100)
        size += PS;
    printf("%lu, %lu\n", sizeof(t_zone), sizeof(t_chunk));
    printf("%zu - %zu - %zu", q, r, size);
    return 0;
}

static void *set_tiny()
{
    Z *zone;
    size_t size;

    size = set_tiny_zone();
    return NULL;
}

int init_env()
{
    g_env.pagesize = getpagesize();
    printf("%zu\n", E.pagesize);
    set_tiny();
    return 0;
}

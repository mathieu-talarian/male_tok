#include "malloc.h"

t_env g_env = {0, 0, NULL, NULL, NULL};
int   g_cpt[3] = {0, 0, 0};

int init_env()
{
    g_env.pagesize = getpagesize();
    g_env.initialized = 1;
    g_env.tiny_zone = set_zone(TINY);
    g_env.small_zone = set_zone(SMALL);
    return 1;
}

static inline t_malloc_function get_function(size_t size)
{
    if (!g_env.initialized)
        init_env();
    return size <= SMALL_MAX_SIZE ? tiny_small_malloc : large_malloc;
}

/** malloc */
void *ft_malloc(size_t size)
{
    return size == 0 ? NULL : get_function(size)(size);
}

#include "malloc.h"

t_env g_env = { 0, 0, 0, NULL, NULL, NULL };
int g_cpt[3] = { 0, 0, 0 };

static inline t_malloc_function
get_function(size_t size)
{
    g_env.initialized == 0 ? init_env() : _;
    return size <= S_MSIZE ? tiny_small_malloc : large_malloc;
}

/** malloc */
void* ft_malloc(size_t size)
{
    return size == 0 ? NULL : get_function(size)(size);
}
#include "malloc.h"

t_env g_env = { 0, 0, 0, NULL, NULL, NULL };
int g_cpt[3] = { 0, 0, 0 };

static inline t_malloc_function
get_function(size_t size)
{
    return size <= S_MSIZE ? tiny_small_malloc : large_m;
}

/** malloc */
void* ft_malloc(size_t size)
{
    if (size == 0)
        return (NULL);
    if (g_env.initialized == 0) {
        if (!debug())
            return (NULL);
        if (!init_env())
            return (NULL);
    }
    return get_function(size)(size);
}
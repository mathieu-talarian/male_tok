#include "malloc.h"

t_env g_env = {0, 0, NULL};

static int get_type(size_t size)
{
    if (size <= T_MSIZE)
        return TINY;
    if (size <= S_MSIZE)
        return SMALL;
    return LARGE;
}

void *ft_malloc(size_t size)
{
    void *ret;

    if (size == 0)
        return (NULL);
    if (g_env.tiny == NULL)
    {
        if (!init_env())
            return (NULL);
        if (!debug())
            return (NULL);
    }
    g_env.func_m[get_type(size)](size);
    return NULL;
}
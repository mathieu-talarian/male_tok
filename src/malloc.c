#include "malloc.h"

t_env g_env = {NULL, NULL, NULL};

void *ft_malloc(size_t size)
{
    void *ret;

    if (size == 0)
        return (NULL);
    if (g_env.tiny == NULL)
    {
        if (!init_env())
        {
            return (NULL);
        }
    }
    return NULL;
}
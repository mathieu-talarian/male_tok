#include "malloc.h"

static inline void *_large_malloc(size_t size)
{
    t_chunk *cur;
    t_chunk *new;

    cur = g_env.large_zone;
    size = (((size + sizeof(t_chunk)) / g_env.pagesize) + 1) * g_env.pagesize;
    if ((new = map(size)) != NULL)
    {
        new->size = size - sizeof(t_chunk);
        new->free = 0;
        FREE_IT(new->free);
        new->next = NULL;
        new->previous = NULL;
        if (cur)
        {
            while (cur->next)
                cur = cur->next;
            cur->next = new;
            new->previous = cur;
        }
        else
            g_env.large_zone = new;
        return ((void *) (new + 1));
    }
    return (NULL);
}

void *large_malloc(size_t size)
{
    return (_large_malloc(size));
}

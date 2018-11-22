#include "malloc.h"

static inline void *_ft_realloc(void *ptr, size_t size)
{
    t_chunk *chunk;
    void *   addr;

    pthread_mutex_lock(&g_mutex);
    if (!g_env.initialized && !init_env())
    {
        pthread_mutex_unlock(&g_mutex);
        return NULL;
    }
    addr = NULL;
    chunk = ((t_chunk *) ptr - 1);
    if ((addr = tiny_realloc(ptr, chunk, size)))
        ;
    else if ((addr = small_realloc(ptr, chunk, size)))
        ;
    else if ((addr = large_realloc(ptr, chunk, size)))
        ;
    pthread_mutex_unlock(&g_mutex);
    return (addr);
}

void *ft_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return malloc(size);
    if (!size)
    {
        FREE(ptr);
        return NULL;
    }
    return _ft_realloc(ptr, size);
}

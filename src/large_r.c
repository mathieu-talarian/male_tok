#include "malloc.h"

static void *l_realloc(void *ptr, size_t size, t_chunk *chunk)
{
    if (size <= chunk->size)
        return ptr;
        return (move_and_free(ptr, chunk->size, size));
}

void *large_realloc(void *ptr, t_chunk *chunk, size_t size)
{
    if (D)
        printf("Large realloc\n");
    if (in_chunk(g_env.large, chunk))
        return l_realloc(ptr, size, chunk);
    return NULL;
}

#include "malloc.h"

typedef size_t (*t_zone_size)();

static size_t set_tiny_zone()
{
    size_t r;
    size_t q;
    size_t size;

    q = T_RSIZE / PS;
    r = (T_RSIZE % PS) ? 1 : 0;
    size = (q + r) * PS;
    while ((size - sizeof(t_zone)) / (T_MSIZE + sizeof(t_chunk)) < 100)
        size += PS;
    return (size);
}

static size_t set_small_zone()
{
    size_t q;
    size_t r;
    size_t size;

    q = S_RSIZE / PS;
    r = (S_RSIZE % PS) ? 1 : 0;
    size = (q + r) * PS;
    while ((size - sizeof(t_zone)) / (T_MSIZE + sizeof(t_chunk)) < 100)
        size += PS;
    return (size);
}

t_zone_size g_functions_size[2] = { set_tiny_zone, set_small_zone };

static inline t_zone* _set_zone(t_zone** zone, size_t size)
{
    (*zone)->next = NULL;
    (*zone)->previous = NULL;
    (*zone)->head = (void*)((*zone) + 1);
    (*zone)->head->size = size - sizeof(t_zone) - sizeof(t_chunk);
    (*zone)->head->free = 0;
    FREE_IT((*zone)->head->free);
    (*zone)->head->next = NULL;
    (*zone)->head->previous = NULL;
    (*zone)->tail = (*zone)->head;
    return (*zone);
}

t_zone* set_zone(MALLOC_TYPE type)
{
    t_zone* zone;
    size_t size;

    zone = NULL;
    size = g_functions_size[type]();
    if ((zone = map(size)) == NULL)
        return NULL;
    return _set_zone(&zone, size);
}
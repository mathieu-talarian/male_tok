#include "malloc.h"

typedef size_t (*t_zone_size)();

static inline size_t set_tiny_zone()
{
    size_t r;
    size_t q;
    size_t size;

    q = TINY_PAGE_SIZE / PS;
    r = (TINY_PAGE_SIZE % PS) ? 1 : 0;
    size = (q + r) * PS;
    while ((size - sizeof(t_zone)) / (TINY_MAX_SIZE + sizeof(t_chunk)) < 100)
        size += PS;
    return (size);
}

static inline size_t set_small_zone()
{
    size_t q;
    size_t r;
    size_t size;

    q = SMALL_PAGE_SIZE / PS;
    r = !(SMALL_PAGE_SIZE % PS);
    size = (q + r) * PS;
    while ((size - sizeof(t_zone)) / (SMALL_MAX_SIZE + sizeof(t_chunk)) < 100)
        size += PS;
    return (size);
}

t_zone_size g_functions_size[2] = {set_tiny_zone, set_small_zone};

static inline t_zone *_set_zone(t_zone **zone, size_t size)
{
    (*zone)->next = NULL;
    (*zone)->previous = NULL;
    (*zone)->head = (void *) ((*zone) + 1);
    (*zone)->head->size = size - sizeof(t_zone) - sizeof(t_chunk);
    (*zone)->head->free = 1;
    (*zone)->head->next = NULL;
    (*zone)->head->previous = NULL;
    (*zone)->tail = (*zone)->head;
    return (*zone);
}

t_zone *set_zone(MALLOC_TYPE type)
{
    t_zone *zone;
    size_t  size;

    zone = NULL;
    size = g_functions_size[type]();
    if ((zone = map(size)) == NULL)
        return NULL;
    return _set_zone(&zone, size);
}
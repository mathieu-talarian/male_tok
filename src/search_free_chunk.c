#include "malloc.h"

void *fusion_block(t_zone *current_zone, t_chunk *chunk, int t, size_t size)
{
    t_chunk *tmp;

    tmp = chunk->next;
    chunk->size += tmp->size + sizeof(t_chunk);
    chunk->next = tmp->next;
    if (chunk->next)
        chunk->next->previous = chunk;
    else
        current_zone->tail = chunk;
    return (split_block(current_zone, chunk, t, size));
}

size_t _res(int t)
{
    if (t == TINY)
        return 16;
    else if (t == SMALL)
        return TINY_MAX_SIZE;
    else
        return SMALL_MAX_SIZE;
}

void build_new_chunk(t_zone **current_zone, t_chunk **current_chunk, size_t size)
{
    t_chunk *new;
    new = (void *) (*current_chunk) + sizeof(t_chunk) + size;
    new->free = 1;
    new->next = (*current_chunk)->next;
    if (new->next)
        new->next->previous = new;
    else if (current_zone)
        (*current_zone)->tail = new;
    new->size = (*current_chunk)->size - size - sizeof(t_chunk);
    (*current_chunk)->next = new;
    new->previous = (*current_chunk);
    (*current_chunk)->size = size;
}

void *split_block(t_zone *current_zone, t_chunk *current_chunk, int t, size_t size)
{
    t_chunk *new;
    size_t res;

    res = _res(t);
    if (current_chunk->size > size + sizeof(t_chunk) + res)
        build_new_chunk(&current_zone, &current_chunk, size);
    current_chunk->free = 0;
    return (void *) (current_chunk + 1);
}

void *search_free_chunk(t_zone *zone, int t, size_t size)
{
    t_zone *  current_zone;
    t_chunk **indirect;

    current_zone = zone;
    current_zone ? indirect = &current_zone->head : _;
    while (current_zone)
    {
        while ((*indirect)->free != 1 && (*indirect)->size <= size)
            indirect = &(*indirect)->next;
        return (*indirect) ? split_block(current_zone, (*indirect), t, size) :
                             search_free_chunk(current_zone->next, t, size);
    }
    return (NULL);
}
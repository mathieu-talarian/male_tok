#include "malloc.h"

size_t have_enough_space(t_chunk *chunk, size_t size)
{
    return ((chunk->size + chunk->next->size + sizeof(t_chunk)) >= size) ? 1 : 0;
}

void *find_zone(t_zone *head, t_chunk *searched)
{
    t_zone *current_zone;

    current_zone = head;
    while (current_zone)
    {
        if (current_zone->head <= searched && current_zone->tail >= searched)
        {
            if (in_chunk(current_zone->head, searched))
                return current_zone;
            else
                return NULL;
        }
        current_zone = current_zone->next;
    }
    return NULL;
}

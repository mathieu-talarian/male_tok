#include "malloc.h"

void* expand_zone(t_zone* zone, int type, size_t size)
{
    t_zone* current_zone;
    t_zone* new_zone;

    new_zone = NULL;
    current_zone = zone;

    if ((new_zone = set_zone(type)) == NULL)
        return NULL;
    while (current_zone->next)
        current_zone = current_zone->next;
    current_zone->next = new_zone;
    new_zone->previous = current_zone;
    return (split_block(new_zone, new_zone->head, type, size));
}
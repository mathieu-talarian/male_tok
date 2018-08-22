#include "malloc.h"

#define CZ current_zone
#define NZ new_zone

void *expand_zone(t_zone *zone, int type, size_t size)
{
    t_zone *current_zone;
    t_zone *new_zone;

    NZ = NULL;
    CZ = zone;
    while (CZ->next)
        CZ = CZ->next;
    if ((NZ = set_tiny()))
    {
        CZ->next = NZ;
        NZ->previous = CZ;
        return (split_block(NZ, NZ->head, type, size));
    }
    return NULL;
}
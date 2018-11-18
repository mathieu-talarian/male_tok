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
            {
                return current_zone;
            }
            else
                return NULL;
        }
        current_zone = current_zone->next;
    }
    return NULL;
}

void *realloc_copy_mem(void *new_ptr, void *old_ptr, size_t old_size, size_t new_size)
{
    char *d;
    char *s;

    d = (char *) new_ptr;
    s = (char *) old_ptr;
    if (d && s)
    {
        while (old_size && new_size)
        {
            *d = *s;
            d++;
            s++;
            old_size--;
            new_size--;
        }
    }
    return (new_ptr);
}

void *move_and_free(void *ptr, size_t old_size, size_t new_size)
{
    void *new;

    new = MALLOC(new_size);
    new = realloc_copy_mem(new, ptr, old_size, new_size);
    FREE(ptr);
    return (new);
}

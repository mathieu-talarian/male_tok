#include "malloc.h"

void *fusion_block(t_zone *cz, t_chunk *chunk, int t, size_t size)
{
    t_chunk *tmp;

    printf("%p\n", cz);
    tmp = chunk->next;
    chunk->size += tmp->size + sizeof(t_chunk);
    chunk->next = tmp->next;
    if (chunk->next)
        chunk->next->previous = chunk;
    else
        cz->tail = chunk;
    return NULL;
}

void *split_block(t_zone *cz, t_chunk *cc, int t, size_t size)
{
    t_chunk *new;
    size_t res;

    if (D)
        printf("split block | t = %d | p = %d\n", t, g_cpt[t]);
    if (t == TINY)
        res = 16;
    else if (t == SMALL)
        res = T_MSIZE;
    else
        res = S_MSIZE;
    if (cc->size > size + sizeof(t_chunk) + res)
    {
        new = (void *)cc + sizeof(t_chunk) + size;
        new->free = 0;
        FREE_IT(new->free);
        new->next = cc->next;
        if (new->next)
            new->next->previous = new;
        else if (cz)
            cz->tail = new;
        new->size = cc->size - size - sizeof(t_chunk);
        cc->next = new;
        new->previous = cc;
        cc->size = size;
    }
    UNFREE_IT(cc->free);
    return (void *)(cc + 1);
}

void *search_free_chunk(t_zone *zone, int t, size_t size)
{
    t_zone *cz;  // current zone
    t_chunk *cc; // current chunk

    cz = zone;
    if (cz)
        cc = cz->head;
    while (cz)
    {
        while (cc)
        {
            if (IS_FREE(cc->free) && cc->size >= size)
                return split_block(cz, cc, t, size);
            cc = cc->next;
        }
        cz = cz->next;
        if (cz)
            cc = cz->head;
    }
    return (NULL);
}
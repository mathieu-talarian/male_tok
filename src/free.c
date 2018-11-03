#include "malloc.h"

int in_chunk(t_chunk* z_head, t_chunk* searched_chunk)
{
    t_chunk* cc;

    cc = z_head;
    while (cc) {
        if (D)
            printf("%p | %p\n", cc, searched_chunk);
        if (cc == searched_chunk) {
            FREE_IT(cc->free);
            return 1;
        }
        cc = cc->next;
    }
    return 0;
}

static int in_zone(t_zone* head, t_chunk* chunk)
{
    t_zone* current_zone;

    current_zone = head;
    if (D)
        printf("in zone\n");
    while (current_zone) {
        if (D)
            printf("%p | %p | %p | %d\n", current_zone->head, current_zone->tail,
                chunk, current_zone->head <= chunk);
        if (current_zone->head <= chunk && chunk <= current_zone->tail)
            return in_chunk(current_zone->head, chunk) ? 1 : 0;
        current_zone = current_zone->next;
    }
    return 0;
}

static int check_zone(t_chunk* chunk)
{
    return (in_zone(g_env.tiny, chunk) || in_zone(g_env.small, chunk));
}

static void unmap_chunk(t_chunk* current)
{
    t_chunk* next;
    t_chunk* previous;

    previous = current->previous;
    next = current->next;
    if (previous)
        previous->next = next;
    if (next)
        next->previous = previous;
    if (g_env.large == current)
        g_env.large = current->next;
    unmap((void*)current, current->size + sizeof(t_chunk));
    if (!previous && !next)
        g_env.large = NULL;
}

void ft_free(void* ptr)
{
    if (D)
        printf("ft_free\n");
    t_chunk* chunk;

    if (!ptr)
        return;
    chunk = ((t_chunk*)ptr - 1);
    if (check_zone(chunk)) {
        FREE_IT(chunk->free);
        // defrag();
    } else if (in_chunk(g_env.large, chunk)) {
        unmap_chunk(chunk);
        // large malloc -> munmap
    }
    return;
}
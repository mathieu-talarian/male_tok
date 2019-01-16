/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:08:17 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 18:31:44 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline t_chunk *build_large_chunk(t_chunk **new, size_t size)
{
    t_chunk **indirect;

    indirect = &g_env.large_zone;
    (*new)->size = size - sizeof(t_chunk);
    (*new)->free = 1;
    (*new)->next = NULL;
    (*new)->previous = NULL;
    if (*indirect)
    {
        while ((*indirect)->next)
            indirect = &(*indirect)->next;
        (*indirect)->next = (*new);
        (*indirect)->previous = (*indirect);
    }
    else
        g_env.large_zone = (*new);
    return (void *) ((*indirect) + 1);
}

static inline void *re_large_malloc(size_t size)
{
    t_chunk *new;

    size = (((size + sizeof(t_chunk)) / g_env.pagesize) + 1) * g_env.pagesize;
    if ((new = map(size)) == NULL)
        return (NULL);
    return ((void *) build_large_chunk(&new, size));
}

void *large_malloc(size_t size)
{
    return (re_large_malloc(size));
}

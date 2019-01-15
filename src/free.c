/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:00:22 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 18:08:01 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			munmap_zone(t_zone **zone)
{
	t_zone		*prev;
	t_zone		*next;

	prev = (*zone)->previous;
	next = (*zone)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->previous = prev;
	unmap((*zone), (*zone)->head->size + sizeof(t_zone) + sizeof(t_chunk));
}

void			re_zone(t_zone **zone, t_chunk **chunk)
{
	if (!(*chunk)->next)
		(*zone)->tail = (*chunk);
	if (!(*chunk)->previous)
		(*zone)->head = (*chunk);
	if ((*zone)->head == (*zone)->tail && (*zone)->previous)
		munmap_zone(zone);
}

void			prev_defrag(t_chunk **chunk, t_chunk **prev)
{
	(*prev) = (*chunk)->previous;
	(*prev)->size += (*chunk)->size + sizeof(t_chunk);
	(*prev)->next = (*chunk)->next;
	if ((*chunk)->next)
		(*chunk)->next->previous = (*prev);
	(*chunk) = (*prev);
}

void			next_defrag(t_chunk **chunk)
{
	t_chunk		*next;

	next = (*chunk)->next;
	(*chunk)->size += next->size + sizeof(t_chunk);
	(*chunk)->next = next->next;
	if (next->next != NULL)
		next->next->previous = (*chunk);
}

int				defrag(t_zone *zone, t_chunk *chunk)
{
	if (chunk->previous && chunk->previous->free)
		prev_defrag(&chunk, &chunk->previous);
	if (chunk->next && chunk->next->free)
		next_defrag(&chunk);
	re_zone(&zone, &chunk);
	return (1);
}

int				in_chunk(t_chunk *z_head, t_chunk *searched_chunk)
{
	t_chunk		**indirect;

	indirect = &z_head;
	while ((*indirect) != searched_chunk)
	{
		if (!(*indirect))
			return (0);
		(*indirect) = (*indirect)->next;
	}
	return (1);
}

static t_zone	*in_zone(t_zone *head, t_chunk *chunk)
{
	t_zone		**indirect;

	indirect = &head;
	while ((*indirect)->head < chunk && chunk < (*indirect)->tail)
	{
		if (!(*indirect))
			return (NULL);
		indirect = &(*indirect)->next;
	}
	return (in_chunk((*indirect)->head, chunk) ? (*indirect) : NULL);
}

static t_zone	*check_zone(t_chunk *chunk)
{
	t_zone		*ret;

	ret = in_zone(g_env.tiny_zone, chunk);
	return (ret ? ret : in_zone(g_env.small_zone, chunk));
}

static void		unmap_chunk(t_chunk *current)
{
	t_chunk		*next;
	t_chunk		*previous;

	previous = current->previous;
	next = current->next;
	if (previous)
		previous->next = next;
	if (next)
		next->previous = previous;
	if (g_env.large_zone == current)
		g_env.large_zone = current->next;
	unmap((void *)current, current->size + sizeof(t_chunk));
	if (!previous && !next)
		g_env.large_zone = NULL;
}

void			ft_free(void *ptr)
{
	t_chunk		*chunk;
	t_zone		*zone;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	chunk = ((t_chunk *)ptr - 1);
	if ((zone = check_zone(chunk)))
	{
		chunk->free = 1;
		defrag(zone, chunk);
	}
	else if (in_chunk(g_env.large_zone, chunk))
		unmap_chunk(chunk);
	pthread_mutex_unlock(&g_mutex);
}

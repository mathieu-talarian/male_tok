/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:55:00 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 18:56:27 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		have_enough_space(t_chunk *chunk, size_t size)
{
	return ((chunk->size + chunk->next->size + sizeof(t_chunk)) >= size);
}

void		*find_zone(t_zone *head, t_chunk *searched)
{
	t_zone	**indirect;

	indirect = &head;
	while ((*indirect)->head < searched && searched < (*indirect)->tail)
	{
		if (!(*indirect))
			return (NULL);
		indirect = &(*indirect)->next;
	}
	return (in_chunk((*indirect)->head, searched) ? (*indirect) : NULL);
}

void		*move_and_free(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;
	size_t	min;

	pthread_mutex_unlock(&g_mutex);
	new = MALLOC(new_size);
	pthread_mutex_lock(&g_mutex);
	min = old_size <= new_size ? old_size : new_size;
	new = ft_memcpy(new, ptr, min);
	pthread_mutex_unlock(&g_mutex);
	FREE(ptr);
	pthread_mutex_lock(&g_mutex);
	return (new);
}

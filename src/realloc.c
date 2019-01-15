/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:52:50 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 18:54:52 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void	*re_ft_realloc(void *ptr, size_t size)
{
	t_chunk			*chunk;
	void			*addr;

	pthread_mutex_lock(&g_mutex);
	if (!g_env.initialized && !init_env())
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	addr = NULL;
	chunk = ((t_chunk *)ptr - 1);
	if ((addr = tiny_realloc(ptr, chunk, size)))
		;
	else if ((addr = small_realloc(ptr, chunk, size)))
		;
	else if ((addr = large_realloc(ptr, chunk, size)))
		;
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}

void				*ft_realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		FREE(ptr);
		return (NULL);
	}
	return (re_ft_realloc(ptr, size));
}

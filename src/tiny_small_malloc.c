/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_small_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 19:29:23 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 19:32:20 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*tiny_small_malloc_(t_zone *zone, int type, size_t size)
{
	void			*returned_addr;

	return ((returned_addr = search_free_chunk(zone, type, size)) ? \
			returned_addr : expand_zone(zone, type, size));
}

void				*tiny_small_malloc(size_t size)
{
	return (size <= TINY_MAX_SIZE ? \
			tiny_small_malloc_(g_env.tiny_zone, TINY, size) : \
			tiny_small_malloc_(g_env.small_zone, SMALL, size));
}

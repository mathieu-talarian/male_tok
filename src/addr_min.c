/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addr_min.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 19:11:27 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 19:29:06 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void		*min_(void *a, void *b, void *c, unsigned long long min)
{
	if (min == (unsigned long long)a)
		return (a);
	else if (min == (unsigned long long)b)
		return (b);
	else if (min == (unsigned long long)c)
		return (c);
	return (NULL);
}

void					*addr_min(void *tiny, void *small, void *large)
{
	unsigned long long	t;
	unsigned long long	s;
	unsigned long long	l;
	unsigned long long	max;

	t = 0;
	s = 0;
	l = 0;
	max = (unsigned long long)tiny + \
			(unsigned long long)small + \
			(unsigned long long)large + \
			1;
	t = tiny ? (unsigned long long)tiny : max;
	s = small ? (unsigned long long)small : max;
	l = large ? (unsigned long long)large : max;
	if (t == s == l)
		return (NULL);
	return (min_(tiny, small, large, min(t, s, l)));
}

void					print_zones(unsigned long long *total)
{
	void				*min_addr;
	t_zone				*tiny_head;
	t_zone				*small_head;
	t_chunk				*large_head;

	tiny_head = g_env.tiny_zone;
	small_head = g_env.small_zone;
	large_head = g_env.large_zone;
	while ((min_addr = addr_min(tiny_head, small_head, large_head)))
	{
		if (min_addr == tiny_head)
			printf_zone_infos(&tiny_head, total, TINY);
		else if (min_addr == small_head)
			printf_zone_infos(&small_head, total, SMALL);
		else if (min_addr == large_head)
			printf_large_infos(&large_head, total);
	}
}

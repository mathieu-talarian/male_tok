/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:48:13 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 18:49:13 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			unmap(void *ptr, size_t size)
{
	return (munmap(ptr, size));
}

void		*map(size_t size)
{
	void	*ret;

	if ((ret = mmap(NULL, size, FLAGS, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (ret);
}

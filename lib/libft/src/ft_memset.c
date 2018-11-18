/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:01:27 by mmoullec          #+#    #+#             */
/*   Updated: 2016/03/21 18:15:10 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *str, int c, size_t n)
{
	char	*s;
	size_t	i;

	s = (char*)str;
	i = 0;
	while (i < n)
	{
		s[i] = (char)c;
		i++;
	}
	return (s);
}
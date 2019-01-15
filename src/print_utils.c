/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:10:15 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 19:24:50 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	add_len(unsigned long long add)
{
	int		len;

	len = 0;
	while (add)
	{
		add /= 16;
		len++;
	}
	return (len);
}

static char	*nbr_to_hex_str(unsigned long long add)
{
	char	*str;
	int		i;
	int		r;
	char	*dt;

	i = add_len(add);
	dt = "0123456789abcdef";
	str = map(i + 1);
	str[i] = 0;
	while (add)
	{
		i--;
		r = add % 16;
		str[i] = dt[r];
		add /= 16;
	}
	return (str);
}

void		print_mem_addr(void *add)
{
	char	*str;

	ft_putstr("0x");
	str = nbr_to_hex_str((unsigned long long)add);
	ft_putstr(str);
	munmap(str, ft_strlen(str) + 1);
}

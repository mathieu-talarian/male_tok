/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 19:13:36 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 19:16:03 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_total(unsigned long long total)
{
	ft_putstr("Total : ");
	ft_putnbr_ull_endl(total);
}

void		ft_show_alloc_mem(void)
{
	unsigned long long total_cpt;

	total_cpt = 0;
	print_zones(&total_cpt);
	print_total(total_cpt);
}

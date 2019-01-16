/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 19:20:50 by mmoullec          #+#    #+#             */
/*   Updated: 2019/01/15 19:36:23 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

unsigned long long min(unsigned long long a, unsigned long long b, unsigned long long c)
{
    a = a < b ? a : b;
    a = a < c ? a : c;
    return (a);
}

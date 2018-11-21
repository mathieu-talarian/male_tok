/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_b_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:25:48 by mmoullec          #+#    #+#             */
/*   Updated: 2018/11/21 19:51:40 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void printf_chunk_infos(t_chunk *chunk, UL *total)
{
    print_mem_addr((void *) (chunk + 1));
    ft_putstr(" - ");
    print_mem_addr((void *) (chunk + 1) + chunk->size);
    ft_putstr(" : ");
    ft_putnbr_ull(chunk->size);
    if (chunk->size > 1)
        ft_putendl(" octets");
    else
        ft_putendl(" octet");
    *total += chunk->size;
}

void printf_zone_infos(t_zone **zone, UL *total, int type)
{
    t_chunk *chunk;
    size_t   size;
    t_zone * z;

    z = *zone;
    size = 0;
    chunk = z->head;
    type == TINY ? ft_putstr("TINY : ") : ft_putstr("SMALL : ");
    print_mem_addr((void *) zone);
    ft_putchar('\n');
    while (chunk)
    {
        if (!chunk->free)
            printf_chunk_infos(chunk, total);
        chunk = chunk->next;
    }
    ft_putendl("");
    *zone = z->next;
}

void printf_large_infos(t_chunk **chunk, unsigned long long *total)
{
    ft_putstr("LARGE : ");
    print_mem_addr((void *) *chunk);
ft_putendl("");
    printf_chunk_infos(*chunk, total);
    ft_putendl("");
    *chunk = (*chunk)->next;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:20:58 by mmoullec          #+#    #+#             */
/*   Updated: 2018/11/21 19:48:45 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void print_total(unsigned long long total)
{
    ft_putstr("Total : ");
    ft_putnbr_ull_endl(total);
}

static unsigned long long min(unsigned long long a, unsigned long long b, unsigned long long c)
{
    asm("cmp   %1,%0\n"
        "cmova %1,%0\n"
        "cmp   %2,%0\n"
        "cmova %2,%0\n"
        : "+r"(a)
        : "r"(b), "r"(c));
    return (a);
}

static inline void *_min(void *a, void *b, void *c, UL min)
{
    if (min == (unsigned long long) a)
        return a;
    else if (min == (unsigned long long) b)
        return b;
    else if (min == (unsigned long long) c)
        return c;
    return NULL;
}

static void *addr_min(void *tiny, void *small, void *large)
{
    UL t;
    UL s;
    UL l;
    UL max;

    t = 0;
    s = 0;
    l = 0;
    max = (UL) tiny + (UL) small + (UL) large + 1;
    t = tiny ? (UL) tiny : max;
    s = small ? (UL) small : max;
    l = large ? (UL) large : max;
    if (t == s == l)
        return NULL;
    return _min(tiny, small, large, min(t, s, l));
}

static void print_zones(unsigned long long *total)
{
    void *   min_addr;
    t_zone * tiny_head;
    t_zone * small_head;
    t_chunk *large_head;

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

void ft_show_alloc_mem()
{
    unsigned long long total_cpt;

    total_cpt = 0;
    print_zones(&total_cpt);
    print_total(total_cpt);
}

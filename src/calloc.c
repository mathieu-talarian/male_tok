/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:14:40 by mmoullec          #+#    #+#             */
/*   Updated: 2018/11/22 02:22:44 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *ft_calloc(size_t nb, size_t size)
{
    void *ptr;

    ptr = malloc(nb * size);
    ft_bzero(ptr, nb * size);
    return (ptr);
}
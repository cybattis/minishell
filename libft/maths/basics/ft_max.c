/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:53:18 by njennes           #+#    #+#             */
/*   Updated: 2022/04/04 15:53:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_maxui(size_t a, size_t b)
{
	if (a >= b)
		return (a);
	return (b);
}

uint64_t	ft_maxi(uint64_t a, uint64_t b)
{
	if (a >= b)
		return (a);
	return (b);
}

double	ft_maxf(double a, double b)
{
	if (a >= b)
		return (a);
	return (b);
}

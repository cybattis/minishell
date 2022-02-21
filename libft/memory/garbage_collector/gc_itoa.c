/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:22:09 by njennes           #+#    #+#             */
/*   Updated: 2021/11/04 14:22:15 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_init_itoa(int *negative, long n, long *ncpy)
{
	*negative = 0;
	*ncpy = n;
	if (n < 0)
	{
		*negative = 1;
		*ncpy = -n;
	}
}

static int	ft_numlen(long n, int negative)
{
	int	result;

	result = 1;
	while (n > 9)
	{
		n /= 10;
		result++;
	}
	return (result + negative);
}

char	*gc_itoa(t_gc *gc, int n)
{
	int		negative;
	int		i;
	long	ncpy;
	char	*new;

	ft_init_itoa(&negative, n, &ncpy);
	new = gc_calloc(gc, ft_numlen(ncpy, negative) + 1, sizeof(char));
	i = ft_numlen(ncpy, negative);
	new[i--] = 0;
	if (ncpy == 0)
		new[0] = '0';
	while (ncpy > 0)
	{
		new[i--] = ncpy % 10 + '0';
		ncpy /= 10;
	}
	if (negative)
		new[0] = '-';
	return (new);
}

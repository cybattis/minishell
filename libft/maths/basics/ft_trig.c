/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:22:24 by                   #+#    #+#             */
/*   Updated: 2022/01/05 18:22:30 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static float	cos_mod(double x)
{
	double	result;
	double	den;
	double	pow;
	double	xx;
	int		i;

	result = 1;
	pow = x * x;
	xx = pow;
	den = 2;
	i = 1;
	while (i <= 10)
	{
		if (i % 2 == 1)
			result -= pow / den;
		else
			result += pow / den;
		pow *= xx;
		den *= (2 * i + 1) * (2 * i + 2);
		i++;
	}
	return (result);
}

double	ft_cos(double x)
{
	double	result;
	double	negative;

	negative = 1;
	x = ft_abs(x);
	x = ft_modf(x, TWO_PI);
	if (x > PI)
	{
		x -= PI;
		negative = -1;
	}
	result = cos_mod(x);
	return (result * negative);
}

double	ft_sin(double x)
{
	return (ft_cos(x - HALF_PI));
}

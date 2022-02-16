/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:46:33 by                   #+#    #+#             */
/*   Updated: 2022/01/09 14:47:31 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

double	ft_lerpf(double base, double height, double value)
{
	return (base + value * (height - base));
}

double	ft_ilerpf(double base, double height, double value)
{
	return ((value / base) / (height / base));
}

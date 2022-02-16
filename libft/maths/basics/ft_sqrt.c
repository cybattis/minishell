/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:37:08 by njennes           #+#    #+#             */
/*   Updated: 2021/08/18 14:40:11 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

double	ft_abs(double nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

double	ft_sqrt(double nb)
{
	double	guess;

	if (nb < 0)
		return (0);
	if (nb == 0)
		return (0);
	guess = 1.0;
	while (ft_abs(guess - ((nb / guess) + guess) / 2.0) > 0.005)
		guess = ((nb / guess) + guess) / 2.0;
	return (guess);
}

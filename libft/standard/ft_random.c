/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <cybattis@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 10:45:02 by                   #+#    #+#             */
/*   Updated: 2022/02/19 14:55:34 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

uint32_t	ft_randi(uint32_t min, uint32_t max)
{
	uint32_t	number;
	void		*ptr;
	size_t		i;

	ptr = malloc(1);
	if (!ptr)
		return (0);
	number = (uint32_t)ptr;
	i = 0;
	while (i < 5)
	{
		number &= 0x0000FFFFFFFFFFFF;
		number = number * number;
		i++;
	}
	free(ptr);
	return ((number % (max - min)) + min);
}

char	ft_randc(void)
{
	uint32_t	number;

	number = ft_randi(33, 126);
	return ((char)number);
}

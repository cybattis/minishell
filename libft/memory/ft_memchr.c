/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:11:14 by njennes           #+#    #+#             */
/*   Updated: 2021/11/04 14:11:27 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*scpy;

	scpy = s;
	i = 0;
	while (i < n && scpy[i] != (unsigned char)c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)&scpy[i]);
}

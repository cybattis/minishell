/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:00 by njennes           #+#    #+#             */
/*   Updated: 2021/11/04 14:26:06 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	totlen;

	totlen = ft_strlen(src) + ft_strlen(dst);
	if (dstsize <= ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	while (*dst != 0 && dstsize - 1 > 0)
	{
		dst++;
		dstsize--;
	}
	i = 0;
	while (src[i] != 0 && dstsize - 1 > 0)
	{
		dst[i] = src[i];
		i++;
		dstsize--;
	}
	dst[i] = 0;
	return (totlen);
}

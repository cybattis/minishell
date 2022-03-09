/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_from.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**gc_strarray_from(t_gc *gc, char **other, size_t size)
{
	size_t	i;
	char	**array;

	if (!other)
		return (gc_strarray_init(gc));
	array = gc_calloc(gc, size + 1, sizeof (char *));
	ft_memmove(array, other, size * sizeof (char *));
	i = 0;
	while (i < size)
	{
		array[i] = gc_strdup(gc, other[i]);
		i++;
	}
	return (array);
}

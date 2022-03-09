/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**gc_strarray_append(t_gc *gc, char **array, char *str)
{
	size_t	size;
	char	**new_array;

	if (!array || !str)
		return (array);
	size = gc_strarray_size(array);
	new_array = gc_calloc(gc, size + 2, sizeof (char *));
	ft_memmove(new_array, array, size * sizeof (char *));
	new_array[size] = gc_strdup(gc, str);
	gc_free(gc, array);
	return (new_array);
}

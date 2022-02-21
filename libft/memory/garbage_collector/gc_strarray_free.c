/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	gc_strarray_free(t_gc *gc, char **array)
{
	size_t	i;
	size_t	size;

	if (!array)
		return ;
	size = gc_strarray_size(array);
	printf("Freeing size of %lu\n", size);
	i = 0;
	while (i < size)
	{
		gc_free(gc, array[i]);
		i++;
	}
	gc_free(gc, array[i]);
	gc_free(gc, array);
}

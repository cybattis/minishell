/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:31:35 by njennes           #+#    #+#             */
/*   Updated: 2022/01/20 14:46:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_darray	darray_create(size_t item_size)
{
	t_darray	array;

	array.item_size = item_size;
	array.size = 0;
	array.capacity = 10;
	array.items = ft_calloc(array.capacity, array.item_size);
	return (array);
}

int	darray_exists(t_darray *array)
{
	return (array->items != NULL);
}

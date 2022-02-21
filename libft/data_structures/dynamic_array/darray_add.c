/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:31:35 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 16:41:39 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	darray_grow(t_darray *array)
{
	void	*new_arr;

	new_arr = ft_calloc(array->capacity * 2, array->item_size);
	if (!new_arr)
		return (0);
	ft_memmove(new_arr, array->items, array->capacity * array->item_size);
	free(array->items);
	array->items = new_arr;
	array->capacity *= 2;
	return (1);
}

int	darray_add(t_darray *array, void *element)
{
	void	*new_elem_loc;

	if (!darray_exists(array))
		return (0);
	new_elem_loc = array->items + array->size * array->item_size;
	if (array->size == array->capacity)
		if (!darray_grow(array))
			return (0);
	ft_memmove(new_elem_loc, element, array->item_size);
	array->size++;
	return (1);
}

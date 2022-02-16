/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:31:35 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 16:41:39 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	darray_remove(t_darray *array, size_t index)
{
	void	*from;
	void	*to;
	size_t	len;

	if (index >= array->size)
		return ;
	if (array->size == 1)
	{
		array->size = 0;
		return ;
	}
	from = array->items + index * array->item_size;
	to = from - array->item_size;
	len = (array->size - index) * array->item_size;
	ft_memmove(to, from, len);
	array->size--;
}

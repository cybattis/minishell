/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:31:35 by njennes           #+#    #+#             */
/*   Updated: 2022/01/20 14:46:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*darray_get(t_darray *array, size_t index)
{
	if (index >= array->size)
		return (NULL);
	return (array->items + index * array->item_size);
}

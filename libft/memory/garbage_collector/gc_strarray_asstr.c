/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_asstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	copy_into_str(char **array, size_t arr_size, char *str)
{
	size_t	str_size;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < arr_size)
	{
		str_size = ft_strlen(array[i]);
		ft_memmove(&str[j], array[i], str_size);
		j += str_size;
		str[j] = ' ';
		j++;
		i++;
	}
	str[j - 1] = 0;
}

char	*gc_strarray_asstr(t_gc *gc, char **array)
{
	size_t	i;
	size_t	arr_size;
	size_t	total_size;
	char	*str;

	if (!array || gc_strarray_size(array) == 0)
		return (gc_strdup(gc, ""));
	arr_size = gc_strarray_size(array);
	total_size = 0;
	i = 0;
	while (i < arr_size)
	{
		total_size += ft_strlen(array[i]) + 1;
		i++;
	}
	str = gc_calloc(gc, total_size, sizeof (char));
	copy_into_str(array, arr_size, str);
	return (str);
}

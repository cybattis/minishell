/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_fromstr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**gc_strarray_fromstr(t_gc *gc, char *str)
{
	char	**array;

	array = gc_strarray_init(gc);
	if (!str)
		return (array);
	array = gc_strarray_append(gc, array, str);
	return (array);
}
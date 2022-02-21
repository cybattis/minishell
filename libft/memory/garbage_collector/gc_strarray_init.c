/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 14:37:24 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**gc_strarray_init(t_gc *gc)
{
	char	**array;

	array = gc_calloc(gc, 1, sizeof (char *));
	return (array);
}

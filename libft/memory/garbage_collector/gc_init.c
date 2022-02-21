/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:48:09 by                   #+#    #+#             */
/*   Updated: 2022/01/20 15:52:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gc_init(t_gc *gc, int (*callback)(void *), void *param)
{
	if (!gc)
		return ;
	gc->callback = callback;
	gc->param = param;
	gc->capacity = 10;
	gc->ptrs_count = 0;
	gc->first_free = 0;
	gc->pointers = ft_calloc(gc->capacity, sizeof(void *));
	if (!gc->pointers)
		gc->capacity = 0;
}

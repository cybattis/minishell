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

#include "../../libft.h"

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

int	gc_grow(t_gc *gc)
{
	void	**new_ptr;

	if (!gc)
		return (0);
	new_ptr = ft_calloc(gc->capacity * 2, sizeof (void *));
	if (!new_ptr)
	{
		if (gc->callback)
			gc->callback(gc->param);
		return (0);
	}
	ft_memmove(new_ptr, gc->pointers, gc->capacity * sizeof(void *));
	free(gc->pointers);
	gc->pointers = new_ptr;
	gc->capacity *= 2;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:05:46 by                   #+#    #+#             */
/*   Updated: 2022/01/20 15:51:55 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	insert_ptr(t_gc *gc, void *ptr)
{
	size_t	i;

	if (!gc)
		return ;
	i = gc->first_free;
	gc->pointers[i] = ptr;
	while (i < gc->capacity && gc->pointers[i])
		i++;
	gc->first_free = i;
	gc->ptrs_count++;
}

void	*gc_calloc(t_gc *gc, size_t count, size_t size)
{
	void	*ptr;

	if (!gc)
		return (NULL);
	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		if (gc->callback)
			gc->callback(gc->param);
		return (NULL);
	}
	if (gc->ptrs_count == gc->capacity)
	{
		if (!gc_grow(gc))
		{
			free(ptr);
			if (gc->callback)
				gc->callback(gc->param);
			return (NULL);
		}
	}
	insert_ptr(gc, ptr);
	return (ptr);
}

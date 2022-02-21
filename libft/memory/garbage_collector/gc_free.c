/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/01/20 15:52:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gc_free(t_gc *gc, void *ptr)
{
	size_t	i;

	if (!gc)
		return ;
	i = 0;
	while (i < gc->capacity && gc->pointers[i] != ptr)
		i++;
	if (i < gc->capacity)
		gc->pointers[i] = NULL;
	else
		return ;
	if (gc->pointers[i] == NULL)
		return ;
	if (i < gc->first_free)
		gc->first_free = i;
	gc->ptrs_count--;
	free(ptr);
}

void	gc_clean(t_gc *gc)
{
	size_t	i;

	if (!gc)
		return ;
	i = 0;
	while (i < gc->capacity)
	{
		if (gc->pointers[i])
			free(gc->pointers[i]);
		i++;
	}
	free(gc->pointers);
}

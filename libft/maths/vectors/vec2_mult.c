/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:17:52 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec2	*vec2_multi(t_vec2 *self, long value)
{
	self->x *= value;
	self->y *= value;
	return (self);
}

t_vec2	*vec2_multf(t_vec2 *self, float value)
{
	self->x *= value;
	self->y *= value;
	return (self);
}

t_vec2	*vec2_multv2(t_vec2 *self, const t_vec2 vec)
{
	self->x *= vec.x;
	self->y *= vec.y;
	return (self);
}

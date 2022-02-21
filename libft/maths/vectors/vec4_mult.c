/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:59:33 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec4	*vec4_multi(t_vec4 *self, long value)
{
	self->x *= value;
	self->y *= value;
	self->z *= value;
	self->w *= value;
	return (self);
}

t_vec4	*vec4_multf(t_vec4 *self, float value)
{
	self->x *= value;
	self->y *= value;
	self->z *= value;
	self->w *= value;
	return (self);
}

t_vec4	*vec4_multv4(t_vec4 *self, const t_vec4 vec)
{
	self->x *= vec.x;
	self->y *= vec.y;
	self->z *= vec.z;
	self->w *= vec.w;
	return (self);
}

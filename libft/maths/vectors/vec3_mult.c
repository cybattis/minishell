/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:59:40 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	*vec3_multi(t_vec3 *self, long value)
{
	self->x *= value;
	self->y *= value;
	self->z *= value;
	return (self);
}

t_vec3	*vec3_multf(t_vec3 *self, float value)
{
	self->x *= value;
	self->y *= value;
	self->z *= value;
	return (self);
}

t_vec3	*vec3_multv3(t_vec3 *self, const t_vec3 vec)
{
	self->x *= vec.x;
	self->y *= vec.y;
	self->z *= vec.z;
	return (self);
}

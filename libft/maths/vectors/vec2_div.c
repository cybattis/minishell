/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:17:58 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_vec2	*vec2_divi(t_vec2 *self, long value)
{
	self->x /= value;
	self->y /= value;
	return (self);
}

t_vec2	*vec2_divf(t_vec2 *self, float value)
{
	self->x /= value;
	self->y /= value;
	return (self);
}

t_vec2	*vec2_divv2(t_vec2 *self, const t_vec2 vec)
{
	self->x /= vec.x;
	self->y /= vec.y;
	return (self);
}

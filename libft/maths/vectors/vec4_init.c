/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:59:35 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec4	vec4(float x, float y, float z, float w)
{
	t_vec4	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return (vec);
}

t_vec4	vec4_copy(t_vec4 old)
{
	t_vec4	vec;

	vec.x = old.x;
	vec.y = old.y;
	vec.z = old.z;
	vec.w = old.w;
	return (vec);
}

t_vec4	vec4_zero(void)
{
	t_vec4	vec;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	vec.w = 0;
	return (vec);
}

t_vec4	vec4_set(float value)
{
	t_vec4	vec;

	vec.x = value;
	vec.y = value;
	vec.z = value;
	vec.w = value;
	return (vec);
}

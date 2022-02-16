/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:59:45 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_vec2	vec2(float x, float y)
{
	t_vec2	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec2	vec2_copy(t_vec2 old)
{
	t_vec2	vec;

	vec.x = old.x;
	vec.y = old.y;
	return (vec);
}

t_vec2	vec2_zero(void)
{
	t_vec2	vec;

	vec.x = 0;
	vec.y = 0;
	return (vec);
}

t_vec2	vec2_set(float value)
{
	t_vec2	vec;

	vec.x = value;
	vec.y = value;
	return (vec);
}

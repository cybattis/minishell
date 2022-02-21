/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:59:39 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	*vec3_normalize(t_vec3 *vec)
{
	float	magnitude;

	magnitude = vec3_mag(*vec);
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
	return (vec);
}

t_vec3	vec3_normalized(t_vec3 vec)
{
	float	magnitude;
	t_vec3	normalized;

	magnitude = vec3_mag(vec);
	if (magnitude < 0.0001)
		return (vec3_zero());
	normalized.x = vec.x / magnitude;
	normalized.y = vec.y / magnitude;
	normalized.z = vec.z / magnitude;
	return (normalized);
}

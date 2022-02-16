/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:17:51 by                   #+#    #+#             */
/*   Updated: 2022/01/06 11:39:35 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_vec2	*vec2_normalize(t_vec2 *vec)
{
	float	magnitude;

	magnitude = vec2_mag(*vec);
	vec->x /= magnitude;
	vec->y /= magnitude;
	return (vec);
}

t_vec2	vec2_normalized(t_vec2 vec)
{
	float	magnitude;
	t_vec2	normalized;

	magnitude = vec2_mag(vec);
	normalized.x = vec.x / magnitude;
	normalized.y = vec.y / magnitude;
	return (normalized);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_clamp.c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:54:51 by                   #+#    #+#             */
/*   Updated: 2022/01/09 15:38:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_vec3	*vec3_clamp_max(t_vec3 *vec, int x, int y, int z)
{
	if (vec->x > x)
		vec->x = x;
	if (vec->y > y)
		vec->y = y;
	if (vec->z > z)
		vec->z = z;
	return (vec);
}

t_vec3	*vec3_clamp_min(t_vec3 *vec, int x, int y, int z)
{
	if (vec->x < x)
		vec->x = x;
	if (vec->y < y)
		vec->y = y;
	if (vec->z < z)
		vec->z = z;
	return (vec);
}

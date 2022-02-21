/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_lerpf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:51:20 by                   #+#    #+#             */
/*   Updated: 2022/01/09 14:52:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	vec3_lerpf(t_vec3 base, t_vec3 high, double value)
{
	t_vec3	vec;

	vec.x = ft_lerpf(base.x, high.x, value);
	vec.y = ft_lerpf(base.y, high.y, value);
	vec.z = ft_lerpf(base.z, high.z, value);
	return (vec);
}

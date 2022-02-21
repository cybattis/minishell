/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:20:20 by                   #+#    #+#             */
/*   Updated: 2022/01/06 12:41:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat4	mat4_scalef(float value)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = value;
	mat.m[1][1] = value;
	mat.m[2][2] = value;
	return (mat);
}

t_mat4	mat4_scalev3(t_vec3 vec)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = vec.x;
	mat.m[1][1] = vec.y;
	mat.m[2][2] = vec.z;
	return (mat);
}

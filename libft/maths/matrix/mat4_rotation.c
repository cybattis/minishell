/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:20:58 by                   #+#    #+#             */
/*   Updated: 2022/01/25 16:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_mat4	mat4_rotatex(t_mat4 self, float value)
{
	t_mat4	mat;

	mat = mat4_copy(self);
	mat.m[1][1] = ft_cos(value);
	mat.m[1][2] = -ft_sin(value);
	mat.m[2][1] = ft_sin(value);
	mat.m[2][2] = ft_cos(value);
	return (mat);
}

t_mat4	mat4_rotatey(t_mat4 self, float value)
{
	t_mat4	mat;

	mat = mat4_copy(self);
	mat.m[0][0] = ft_cos(value);
	mat.m[0][2] = ft_sin(value);
	mat.m[2][0] = -ft_sin(value);
	mat.m[2][2] = ft_cos(value);
	return (mat);
}

t_mat4	mat4_rotatez(t_mat4 self, float value)
{
	t_mat4	mat;

	mat = mat4_copy(self);
	mat.m[0][0] = ft_cos(value);
	mat.m[0][1] = -ft_sin(value);
	mat.m[1][0] = ft_sin(value);
	mat.m[1][1] = ft_cos(value);
	return (mat);
}

t_mat4	mat4_rotate_axis(float angle, t_vec3 axis)
{
	t_vec3	v;
	t_vec3	temp;
	double	c;
	double	s;
	t_mat4	result;

	c = ft_cos(angle);
	s = ft_sin(angle);
	v = vec3_normalized(axis);
	temp = vec3_copy(v);
	vec3_multf(&temp, 1 - c);
	result = mat4_identity();
	result.m[0][0] = c + temp.x * v.x;
	result.m[0][1] = temp.x * v.y + s * v.z;
	result.m[0][2] = temp.x * v.z - s * v.y;
	result.m[1][0] = temp.y * v.x - s * v.z;
	result.m[1][1] = c + temp.y * v.y;
	result.m[1][2] = temp.y * v.z + s * v.x;
	result.m[2][0] = temp.z * v.x + s * v.y;
	result.m[2][1] = temp.z * v.y - s * v.x;
	result.m[2][2] = c + temp.z * v.z;
	return (result);
}

t_mat4	mat4_rotate(t_vec3 vec)
{
	t_mat4	mat;

	mat = mat4_rotatey(mat4_identity(), vec.y);
	mat = mat4_multm4(mat, mat4_rotatez(mat4_identity(), vec.z));
	mat = mat4_multm4(mat, mat4_rotatex(mat4_identity(), vec.x));
	return (mat);
}

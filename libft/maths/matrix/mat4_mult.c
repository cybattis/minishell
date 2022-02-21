/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:19:04 by                   #+#    #+#             */
/*   Updated: 2022/01/06 12:41:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat4	*mat4_multi(t_mat4 *self, int value)
{
	self->m[0][0] *= value;
	self->m[0][1] *= value;
	self->m[0][2] *= value;
	self->m[0][3] *= value;
	self->m[1][0] *= value;
	self->m[1][1] *= value;
	self->m[1][2] *= value;
	self->m[1][3] *= value;
	self->m[2][0] *= value;
	self->m[2][1] *= value;
	self->m[2][2] *= value;
	self->m[2][3] *= value;
	self->m[3][0] *= value;
	self->m[3][1] *= value;
	self->m[3][2] *= value;
	self->m[3][3] *= value;
	return (self);
}

t_mat4	*mat4_multf(t_mat4 *self, float value)
{
	self->m[0][0] *= value;
	self->m[0][1] *= value;
	self->m[0][2] *= value;
	self->m[0][3] *= value;
	self->m[1][0] *= value;
	self->m[1][1] *= value;
	self->m[1][2] *= value;
	self->m[1][3] *= value;
	self->m[2][0] *= value;
	self->m[2][1] *= value;
	self->m[2][2] *= value;
	self->m[2][3] *= value;
	self->m[3][0] *= value;
	self->m[3][1] *= value;
	self->m[3][2] *= value;
	self->m[3][3] *= value;
	return (self);
}

t_vec4	mat4_multv4(t_mat4 self, t_vec4 other)
{
	t_vec4	vec;

	vec.x = self.m[0][0] * other.x + self.m[0][1] * other.y + \
			self.m[0][2] * other.z + self.m[0][3] * other.w;
	vec.y = self.m[1][0] * other.x + self.m[1][1] * other.y + \
			self.m[1][2] * other.z + self.m[1][3] * other.w;
	vec.z = self.m[2][0] * other.x + self.m[2][1] * other.y + \
			self.m[2][2] * other.z + self.m[2][3] * other.w;
	vec.w = self.m[3][0] * other.x + self.m[3][1] * other.y + \
			self.m[3][2] * other.z + self.m[3][3] * other.w;
	return (vec);
}

t_mat4	mat4_multm4(t_mat4 self, t_mat4 other)
{
	t_mat4	mat;
	float	sum;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		k = 0;
		while (k < 4)
		{
			j = 0;
			sum = 0;
			while (j < 4)
			{
				sum += self.m[i][j] * other.m[j][k];
				j++;
			}
			mat.m[i][k] = sum;
			k++;
		}
		i++;
	}
	return (mat);
}

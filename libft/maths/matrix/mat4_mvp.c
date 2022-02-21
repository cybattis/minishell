/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mvp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:59:07 by                   #+#    #+#             */
/*   Updated: 2022/01/06 12:41:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat4	mat4_translate(t_mat4 self, t_vec3 vec)
{
	t_mat4	mat;

	mat = mat4_copy(self);
	mat.m[0][3] = vec.x;
	mat.m[1][3] = vec.y;
	mat.m[2][3] = vec.z;
	return (mat);
}

t_mat4	mat4_ortho(t_proj proj)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = 2 / (proj.right - proj.left);
	mat.m[1][1] = 2 / (proj.top - proj.bot);
	mat.m[2][2] = -2 / (proj.far - proj.near);
	mat.m[0][3] = -(proj.right + proj.left) / (proj.right - proj.left);
	mat.m[1][3] = -(proj.top + proj.bot) / (proj.top - proj.bot);
	mat.m[2][3] = -(proj.far + proj.near) / (proj.far - proj.near);
	return (mat);
}

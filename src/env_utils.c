/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/08 12:07:13 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern char	**environ;

int	get_empty_var_index(void)
{
	size_t	i;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] == 0)
			return ((int)i);
		i++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/03/27 14:23:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "minishell.h"

int	get_empty_var_index(void)
{
	size_t	i;

	i = 0;
	while (g_minishell.env[i])
	{
		if (g_minishell.env[i][0] == 0)
			return ((int)i);
		i++;
	}
	return (-1);
}

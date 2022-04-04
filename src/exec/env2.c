/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/04/01 15:10:46 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "core.h"
#include "minishell.h"

int	env_var_index(const char *name);

char	*get_env(char *name)
{
	int		index;
	char	*value;

	index = env_var_index(name);
	if (index == -1)
		return (NULL);
	value = g_minishell.env[index];
	while (*value && *value != '=')
		value++;
	if (*value)
		value++;
	return (value);
}

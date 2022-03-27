/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/03/27 14:23:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <stdio.h>

extern char	**environ;

int	bt_env(void)
{
	size_t	i;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] != 0)
			printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

int	bt_unset(char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!is_envchar(args[i][j]))
				break ;
			j++;
		}
		if (args[i][j])
		{
			ft_dprintf(STDERR_FILENO, "minishell: unset: `%s':"
				" not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		unset_env_var(args[i]);
		i++;
	}
	return (1);
}
